

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncUDP.h>
#include <ESPmDNS.h>
#include <lwip/def.h>
#include <TimeLib.h>
#include <time.h>

#include "secrets.h"
#include "FutabaSD08FA.h"
#include "Thunderbolt.h"

// --------------------------------------------------------------------------------------
// User configuration (adjust to match your wiring and network)
// --------------------------------------------------------------------------------------
constexpr const char *WIFI_SSID = ssid;
constexpr const char *WIFI_PASS = password;
constexpr const char *WIFI_HOSTNAME = wifi_hostname;
constexpr char SOFTWARE_VERSION[] = "0.1.0";

// Thunderbolt TSIP UART on ESP32 (use any free HW serial pins on the devkit)
constexpr int TBOLT_RX_PIN = 16;  // Thunderbolt TX -> ESP32 RX
constexpr int TBOLT_TX_PIN = 17;  // Thunderbolt RX -> ESP32 TX
constexpr uint32_t TBOLT_BAUD = TSIP_BAUD_RATE;

// Futaba NA202SD08FA parallel interface pins (20x2 VFD)
// Update these to the GPIOs you actually wire.
constexpr uint8_t VFD_STROBE = 4;
constexpr uint8_t VFD_D0 = 32;
constexpr uint8_t VFD_D1 = 33;
constexpr uint8_t VFD_D2 = 25;
constexpr uint8_t VFD_D3 = 26;
constexpr uint8_t VFD_D4 = 27;
constexpr uint8_t VFD_D5 = 14;
constexpr uint8_t VFD_D6 = 12;
constexpr uint8_t VFD_D7 = 13;

constexpr uint8_t DISPLAY_COLUMNS = 20;
constexpr uint8_t DISPLAY_ROWS = 2;
constexpr uint32_t DISPLAY_INTERVAL_MS = 500;
constexpr uint32_t RTC_SYNC_INTERVAL_MS = 1000;

HardwareSerial thunderboltSerial(1);
Thunderbolt thunderbolt(thunderboltSerial);
FutabaSD08FA vfd(VFD_STROBE, VFD_D0, VFD_D1, VFD_D2, VFD_D3, VFD_D4, VFD_D5, VFD_D6, VFD_D7);
AsyncUDP ntpUdp;

class EspRtcFallback : public RTCFallBack {
public:
  const uint32_t getUnixTime() override {
    timeval tv{};
    gettimeofday(&tv, nullptr);
    return tv.tv_sec;
  }

  void setTime(time_t unixTime) override {
    timeval tv{.tv_sec = unixTime, .tv_usec = 0};
    settimeofday(&tv, nullptr);
    ::setTime(unixTime);
  }

  uint32_t getSyncInterval() override {
    return 60;
  }
};

EspRtcFallback rtcFallback;

uint32_t lastDisplayUpdate = 0;
uint32_t lastRtcSync = 0;
bool wifiReady = false;
bool ntpReady = false;

// --------------------------------------------------------------------------------------
// Helpers
// --------------------------------------------------------------------------------------

void showBootMessage(const char *msg) {
  char line[DISPLAY_COLUMNS + 1] = {0};
  vfd.clear();
  vfd.setCursor(0, 0);
  snprintf(line, sizeof(line), "GPSDO TB v%s", SOFTWARE_VERSION);
  vfd.print(line);
  vfd.setCursor(0, 1);
  vfd.print(msg);
}

void syncSystemClock() {
  // Keep ESP32 RTC and TimeLib aligned to Thunderbolt seconds.
  time_t gpsUnix = thunderbolt.getUnixTime();
  if (gpsUnix == 0) {
    return;
  }

  static time_t lastSet = 0;
  if (labs(gpsUnix - lastSet) > 0) {
    lastSet = gpsUnix;
    rtcFallback.setTime(gpsUnix);
  }
}

String healthToString(GPSHealth h) {
  switch (h) {
    case HLTH_DOING_FIXES:
      return "Locked";
    case HLTH_NO_GPSTIME:
      return "No time";
    case HLTH_PDOP_TOO_HIGH:
      return "Poor geom";
    case HLTH_SATELLITES_NONE:
      return "No sats";
    case HLTH_SATELLITES_ONE:
      return "1 sat";
    case HLTH_SATELLITES_TWO:
      return "2 sats";
    case HLTH_SATELLITES_THREE:
      return "3 sats";
    case HLTH_SATELLITES_OVERDETERMINED:
      return "Overdet";
    case HLTH_UNKNOWN:
    default:
      return "Init";
  }
}

void updateDisplay() {
  const GPSTime &t = thunderbolt.getGPSTime();
  const GPSStatus &s = thunderbolt.getStatus();

  char line[DISPLAY_COLUMNS + 1] = {0};
  vfd.setCursor(0, 0);
  snprintf(line, sizeof(line), "%02u:%02u:%02u UTC S:%02d",
           t.Hour, t.Minute, t.Second, s.n_satellites);
  vfd.print(line);

  vfd.setCursor(0, 1);
  if (wifiReady && ntpReady) {
    IPAddress ip = WiFi.localIP();
    snprintf(line, sizeof(line), "%04u-%02u-%02u %s NTP %u.%u.%u.%u",
             t.Year, t.Month, t.Day,
             healthToString(s.health).c_str(),
             ip[0], ip[1], ip[2], ip[3]);
  } else if (wifiReady) {
    snprintf(line, sizeof(line), "%04u-%02u-%02u %s WiFi link",
             t.Year, t.Month, t.Day, healthToString(s.health).c_str());
  } else {
    snprintf(line, sizeof(line), "%04u-%02u-%02u %s WiFi off",
             t.Year, t.Month, t.Day, healthToString(s.health).c_str());
  }
  vfd.print(line);
}

void setupWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.setHostname(WIFI_HOSTNAME);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  unsigned long start = millis();
  showBootMessage("WiFi connect...");

  while (WiFi.status() != WL_CONNECTED && millis() - start < 15000) {
    delay(250);
  }

  wifiReady = WiFi.status() == WL_CONNECTED;
  if (!wifiReady) {
    showBootMessage("WiFi failed");
  } else {
    showBootMessage("WiFi OK");
  }
}

void startMdns() {
  if (!wifiReady) {
    return;
  }

  if (MDNS.begin(WIFI_HOSTNAME)) {
    MDNS.addService("ntp", "udp", 123);
  }
}

void handleNtpPacket(AsyncUDPPacket packet) {
  uint8_t reply[48] = {0};
  uint32_t secs = 0;
  uint32_t fract = 0;
  thunderbolt.now(&secs, &fract);

  // Copy originate timestamp from client (bytes 40-47 of request)
  memcpy(&reply[24], packet.data() + 40, 8);

  // LI=0, Version=4, Mode=4 (server)
  reply[0] = 0b00100100;
  reply[1] = 1;    // stratum (1 = primary ref)
  reply[2] = 4;    // poll interval
  reply[3] = 0xEC; // precision (~-20)

  const uint32_t refSec = htonl(secs);
  const uint32_t refFrac = htonl(fract);
  memcpy(&reply[16], &refSec, 4);   // reference timestamp seconds
  memcpy(&reply[20], &refFrac, 4);  // reference fraction

  memcpy(&reply[32], &refSec, 4);   // receive timestamp seconds
  memcpy(&reply[36], &refFrac, 4);  // receive fraction
  memcpy(&reply[40], &refSec, 4);   // transmit timestamp seconds
  memcpy(&reply[44], &refFrac, 4);  // transmit fraction

  packet.write(reply, sizeof(reply));
}

void startNtpServer() {
  if (!wifiReady) {
    return;
  }

  if (ntpUdp.listen(123)) {
    ntpUdp.onPacket([](AsyncUDPPacket packet) { handleNtpPacket(packet); });
    ntpReady = true;
  } else {
    ntpReady = false;
  }
}

// --------------------------------------------------------------------------------------
// Arduino setup / loop
// --------------------------------------------------------------------------------------
void setup() {
  Serial.begin(115200);
  delay(100);

  vfd.begin(DISPLAY_COLUMNS, DISPLAY_ROWS);
  showBootMessage("Booting...");

  thunderboltSerial.begin(TBOLT_BAUD, SERIAL_8N1, TBOLT_RX_PIN, TBOLT_TX_PIN);
  thunderbolt.registerFallback(rtcFallback);
  thunderbolt.setPacketBroadcastMask(PBM_PRIMARY_TIMING_INFO | PBM_SUPPLEMENTAL_TIMING_INFO);

  setupWifi();
  startMdns();
  startNtpServer();
}

void loop() {
  const bool gotPacket = thunderbolt.readSerial();

  if (gotPacket && millis() - lastRtcSync >= RTC_SYNC_INTERVAL_MS) {
    syncSystemClock();
    lastRtcSync = millis();
  }

  // Use RTC fallback if Thunderbolt stops talking.
  thunderbolt.processFallback();

  if (millis() - lastDisplayUpdate >= DISPLAY_INTERVAL_MS) {
    updateDisplay();
    lastDisplayUpdate = millis();
  }
}
