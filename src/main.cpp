// Pinout wiring MH-ET Live D1 Minikit
//  Notes: Pin/Function/Physical Pin Number | Physical Pin Number, Function/Pin
//           o  normal pin
//          (o) Pin is in white silkscreen
//          ~   PWM/I2C/1 Wire Pin,    
//          x = Pin is being used.    
//    
//                                               /------------------------------------------------\
//                                              /  Wemos D1 mini32 (top view, USB at bottom)       \
//                                             /                                                    \
//                 GND  1|2   RST              |  GND o  | (o)  RST               IO1  (o) |  o GND  |        TXD:0  21|22 GND     
//                 N/C   |   SVP/ADC           |  N/C o  | (o)  A0                IO3  (o) |  x IO27 |        RXD:0    |24 ===VFD D4===  
//     ADC3/SVN/GPIO39   |6  ===VFD D3===      | IO39 o  | (x)  IO26              IO22~(o) |  x IO25 |        D1/SCL   |26 ===VFD D2===  
//         ADC1/GPIO35   |   D5/GPIO18/ SCK:0  | IO35 o  | (o)  IO18              IO21~(o) |  x IO32 |        D2/SDA   |28 ===VFD D0===  
//       ===VFD D1===   9|   D6/GPIO19/MISO:0  | IO33 x  | (o)  IO19              IO17 (x) |  x IO12 |  TBOLT_TX_PIN 29|30 ===VFD D6===  
//         ADC0/GPIO34   |   D7/GPIO23/MOSI:0  | IO34 o  | (o)  IO23              IO16 (x) |  x~IO4  |  TBOLT_RX_PIN 31|32 ===VFD WS===  
//       ===VFD D5===  13|   D8/GPIO5 /  CS:0  | IO14 x  | (o)  IO5               GND  (o) |  o~IO0  |           GND   |   PWM0:1  
//                 N/C   |   3v3               |  N/C o  | (o)  3v3               Vcc  (o) |  o~IO2  |           VCC   |   PWM0:0  
//     TXD:1/SD2/GPIO9   |18 ===VFD D7===      | IO9  o  |  X   IO13              IO15  o  |  o IO8  |           TD0   |   CLK     
//          CMD/GPIO11 19|20 GPIO10/SD3/RXD:1  | IO11 o  |  O   IO10              IO7   o  |  o IO6  |           SD0 39|40 SD1     
//                                             |                                                     |
//                                             |_                                                    |
//                                               |_                                                  |
//                                              O--| RST               | USB |                       |
//                                               |-                    |     |                       |
//                                               +--------------------^+-----+^----------------------+
// Update these pins to match your wiring.

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncUDP.h>
#include <ESPmDNS.h>
#include <lwip/def.h>
#include <TimeLib.h>
#include <stdarg.h>
#include <string.h>
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
constexpr uint8_t VFD_STROBE = 4;  // [IO4]
constexpr uint8_t VFD_D0 = 32;     // [IO32]
constexpr uint8_t VFD_D1 = 33;     // [IO33]
constexpr uint8_t VFD_D2 = 25;     // [IO25]
constexpr uint8_t VFD_D3 = 26;     // [IO26]
constexpr uint8_t VFD_D4 = 27;     // [IO27]
constexpr uint8_t VFD_D5 = 14;     // [IO14]
constexpr uint8_t VFD_D6 = 12;     // [IO12]
constexpr uint8_t VFD_D7 = 13;     // [IO13]

constexpr uint8_t DISPLAY_COLUMNS = 20;
constexpr uint8_t DISPLAY_ROWS = 2;
constexpr uint32_t DISPLAY_INTERVAL_MS = 500;
constexpr uint32_t RTC_SYNC_INTERVAL_MS = 1000;
constexpr uint32_t STATUS_HOLD_MS = 10000;
constexpr uint32_t SLEEP_SWAP_MS = 30000;
constexpr uint32_t SLEEP_IP_INTERVAL_MS = 120000;
constexpr uint32_t SLEEP_IP_DURATION_MS = 14500;
constexpr uint32_t TBOLT_DETECT_TIMEOUT_MS = 1500;
constexpr bool DATE_FORMAT_MDY = true;
constexpr bool CLOCK_UPDATE_WINDOW_ENABLED = true;
constexpr int16_t TIMEZONE_OFFSET_MINUTES = 0;          // local = UTC + offset
constexpr bool DST_ACTIVE = false;
constexpr uint16_t CLOCK_UPDATE_START_MINUTES = 120;    // 02:00 local
constexpr uint16_t CLOCK_UPDATE_WINDOW_MINUTES = 30;    // 30 minutes

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
uint32_t lastStatusChangeMs = 0;
uint32_t lastSleepSwitchMs = 0;
uint32_t lastIpShowMs = 0;
uint32_t ipShowStartMs = 0;
bool inSleepMode = false;
bool ipActive = false;
bool showSleepDate = false;

struct StatusSnapshot {
  GPSHealth health = HLTH_UNKNOWN;
  int n_satellites = 0;
  uint16_t critical_alarms = 0;
  uint16_t minor_alarms = 0;
  ReceiverStatus rcvr_status = Unknown;
  DiscipliningMode disc_mode = Normal;
  DiscipliningActivity disc_activity = Inactive;
  bool wifi_ready = false;
  bool ntp_ready = false;
};

StatusSnapshot lastStatusSnapshot;
bool hasStatusSnapshot = false;

// --------------------------------------------------------------------------------------
// Helpers
// --------------------------------------------------------------------------------------

bool waitForThunderboltData(uint32_t timeoutMs) {
  const uint32_t start = millis();
  while (millis() - start < timeoutMs) {
    if (thunderboltSerial.available() > 0) {
      return true;
    }
    delay(10);
  }
  return false;
}

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

const char *healthToShortString(GPSHealth h) {
  switch (h) {
    case HLTH_DOING_FIXES:
      return "Lock";
    case HLTH_NO_GPSTIME:
      return "NoTm";
    case HLTH_PDOP_TOO_HIGH:
      return "PDOP";
    case HLTH_SATELLITES_NONE:
      return "NoSat";
    case HLTH_SATELLITES_ONE:
      return "1Sat";
    case HLTH_SATELLITES_TWO:
      return "2Sat";
    case HLTH_SATELLITES_THREE:
      return "3Sat";
    case HLTH_SATELLITES_OVERDETERMINED:
      return "Odet";
    case HLTH_UNKNOWN:
    default:
      return "Init";
  }
}

const char *netStatusLabel() {
  if (wifiReady && ntpReady) {
    return "NTP";
  }
  if (wifiReady) {
    return "WIFI";
  }
  return "OFF";
}

void writeLine(uint8_t row, const char *fmt, ...) {
  char line[DISPLAY_COLUMNS + 1] = {0};
  va_list args;
  va_start(args, fmt);
  vsnprintf(line, sizeof(line), fmt, args);
  va_end(args);
  const size_t len = strnlen(line, DISPLAY_COLUMNS);
  for (size_t idx = len; idx < DISPLAY_COLUMNS; idx++) {
    line[idx] = ' ';
  }
  line[DISPLAY_COLUMNS] = '\0';
  vfd.setCursor(0, row);
  vfd.print(line);
}

void writeCentered(uint8_t row, const char *text) {
  char line[DISPLAY_COLUMNS + 1] = {0};
  const size_t len = strnlen(text, DISPLAY_COLUMNS);
  const size_t start = (DISPLAY_COLUMNS > len) ? (DISPLAY_COLUMNS - len) / 2 : 0;
  for (size_t idx = 0; idx < DISPLAY_COLUMNS; idx++) {
    line[idx] = ' ';
  }
  if (len > 0 && start < DISPLAY_COLUMNS) {
    memcpy(line + start, text, len);
  }
  line[DISPLAY_COLUMNS] = '\0';
  vfd.setCursor(0, row);
  vfd.print(line);
}

uint16_t minutesSinceMidnight(const GPSTime &t) {
  int32_t minutes = static_cast<int32_t>(t.Hour) * 60 + static_cast<int32_t>(t.Minute);
  minutes += TIMEZONE_OFFSET_MINUTES;
  if (DST_ACTIVE) {
    minutes += 60;
  }
  minutes %= 1440;
  if (minutes < 0) {
    minutes += 1440;
  }
  return static_cast<uint16_t>(minutes);
}

bool isInClockUpdateWindow(const GPSTime &t) {
  if (!CLOCK_UPDATE_WINDOW_ENABLED || CLOCK_UPDATE_WINDOW_MINUTES == 0) {
    return false;
  }
  const uint16_t now = minutesSinceMidnight(t);
  const uint16_t start = CLOCK_UPDATE_START_MINUTES % (24u * 60u);
  const uint16_t end = (start + CLOCK_UPDATE_WINDOW_MINUTES) % (24u * 60u);
  if (start < end) {
    return now >= start && now < end;
  }
  return now >= start || now < end;
}

bool isClockworkStable(const GPSStatus &s) {
  const bool alarmsClear = (s.critical_alarms == 0) && (s.minor_alarms == 0);
  return wifiReady && ntpReady && alarmsClear && (s.health == HLTH_DOING_FIXES);
}

bool statusSnapshotChanged(const GPSStatus &s) {
  StatusSnapshot current;
  current.health = s.health;
  current.n_satellites = s.n_satellites;
  current.critical_alarms = s.critical_alarms;
  current.minor_alarms = s.minor_alarms;
  current.rcvr_status = s.rcvr_status;
  current.disc_mode = s.disc_mode;
  current.disc_activity = s.disc_activity;
  current.wifi_ready = wifiReady;
  current.ntp_ready = ntpReady;

  if (!hasStatusSnapshot) {
    lastStatusSnapshot = current;
    hasStatusSnapshot = true;
    return true;
  }

  const bool changed =
      current.health != lastStatusSnapshot.health ||
      current.n_satellites != lastStatusSnapshot.n_satellites ||
      current.critical_alarms != lastStatusSnapshot.critical_alarms ||
      current.minor_alarms != lastStatusSnapshot.minor_alarms ||
      current.rcvr_status != lastStatusSnapshot.rcvr_status ||
      current.disc_mode != lastStatusSnapshot.disc_mode ||
      current.disc_activity != lastStatusSnapshot.disc_activity ||
      current.wifi_ready != lastStatusSnapshot.wifi_ready ||
      current.ntp_ready != lastStatusSnapshot.ntp_ready;

  if (changed) {
    lastStatusSnapshot = current;
  }
  return changed;
}

void formatDate(char *out, size_t outSize, const GPSTime &t) {
  if (DATE_FORMAT_MDY) {
    snprintf(out, outSize, "%02u/%02u/%04u", t.Month, t.Day, t.Year);
  } else {
    snprintf(out, outSize, "%02u/%02u/%04u", t.Day, t.Month, t.Year);
  }
}

void showStatusScreen(const GPSTime &t, const GPSStatus &s) {
  writeLine(0, "%02u:%02u:%02u UTC S:%02d",
            t.Hour, t.Minute, t.Second, s.n_satellites);
  writeLine(1, "%04u-%02u-%02u %s %s",
            t.Year, t.Month, t.Day,
            healthToShortString(s.health), netStatusLabel());
}

void showSleepTimeScreen(const GPSTime &t) {
  char timeText[9] = {0};
  snprintf(timeText, sizeof(timeText), "%02u:%02u:%02u", t.Hour, t.Minute, t.Second);
  writeCentered(0, timeText);
  writeLine(1, "");
}

void showSleepDateScreen(const GPSTime &t) {
  char dateText[12] = {0};
  formatDate(dateText, sizeof(dateText), t);
  writeCentered(0, dateText);
  writeLine(1, "");
}

void showSleepIpScreen() {
  if (!wifiReady) {
    writeCentered(0, "NO WIFI");
    writeLine(1, "");
    return;
  }
  IPAddress ip = WiFi.localIP();
  char ipText[16] = {0};
  snprintf(ipText, sizeof(ipText), "%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);
  writeCentered(0, "IP ADDRESS");
  writeCentered(1, ipText);
}

void updateDisplay() {
  const GPSTime &t = thunderbolt.getGPSTime();
  const GPSStatus &s = thunderbolt.getStatus();
  const uint32_t now = millis();

  if (statusSnapshotChanged(s)) {
    lastStatusChangeMs = now;
  }

  const bool inUpdateWindow = isInClockUpdateWindow(t);
  const bool stable = isClockworkStable(s) && !inUpdateWindow;
  const bool holdStatus = (now - lastStatusChangeMs) < STATUS_HOLD_MS;

  if (!stable || holdStatus) {
    inSleepMode = false;
    ipActive = false;
    showStatusScreen(t, s);
    return;
  }

  if (!inSleepMode) {
    inSleepMode = true;
    showSleepDate = false;
    lastSleepSwitchMs = now;
    lastIpShowMs = now;
    ipShowStartMs = 0;
    ipActive = false;
  }

  if (ipActive && (now - ipShowStartMs >= SLEEP_IP_DURATION_MS)) {
    ipActive = false;
  }

  if (!ipActive && (now - lastIpShowMs >= SLEEP_IP_INTERVAL_MS)) {
    ipActive = true;
    ipShowStartMs = now;
    lastIpShowMs = now;
  }

  if (ipActive) {
    showSleepIpScreen();
    return;
  }

  if (now - lastSleepSwitchMs >= SLEEP_SWAP_MS) {
    showSleepDate = !showSleepDate;
    lastSleepSwitchMs = now;
  }

  if (showSleepDate) {
    showSleepDateScreen(t);
  } else {
    showSleepTimeScreen(t);
  }
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

void updateWifiStatus() {
  const bool connected = WiFi.status() == WL_CONNECTED;
  if (connected == wifiReady) {
    return;
  }
  wifiReady = connected;
  if (!wifiReady) {
    ntpReady = false;
    return;
  }
  startMdns();
  startNtpServer();
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
  if (waitForThunderboltData(TBOLT_DETECT_TIMEOUT_MS)) {
    thunderbolt.setPacketBroadcastMask(PBM_PRIMARY_TIMING_INFO | PBM_SUPPLEMENTAL_TIMING_INFO);
  }

  setupWifi();
  startMdns();
  startNtpServer();
}

void loop() {
  const bool gotPacket = thunderbolt.readSerial();

  updateWifiStatus();

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
