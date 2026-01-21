# GPSDO (Trimble Thunderbolt + ESP32)

GPS disciplined oscillator project using a Trimble Thunderbolt receiver, an ESP32 (Wemos D1 mini),
and a Futaba NA202SD08FA VFD. The ESP32 reads TSIP timing data, keeps its RTC aligned to GPS,
serves NTP on the LAN, and shows status on the VFD.

## Features
- Trimble Thunderbolt TSIP parsing over UART
- VFD status display (20x2)
- RTC + TimeLib sync from GPS time
- NTP server over UDP 123
- mDNS service advertising `_ntp._udp` and DHCP hostname support
- Boot message includes software version

## GPS Week Rollover Fix
Older GPS week-number rollovers can cause the date to jump backward. We avoid that by using the
Thunderbolt's full date/time fields (from the primary timing packet) and converting to Unix/NTP
time on the ESP32. No 10-bit week math is used on the MCU, so the rollover does not break time.

## Build
```sh
pio run
```

Default environment is `wemos_d1_mini32` (see `platformio.ini`).

## Configuration
Create `include/secrets.h` (ignored by git) with your WiFi credentials and hostname:
```cpp
const char ssid[] = "YOUR_SSID";
const char password[] = "YOUR_PASSWORD";
const char wifi_hostname[] = "ntp";
```

With mDNS, the NTP server is reachable at `<wifi_hostname>.local` (e.g., `ntp.local`).

## Known Issues / Bugs
- NTP stratum/leap indicator is not yet tied to lock state (stratum is always set to 1).
- No long-term holdover calibration; when GPS is lost the ESP32 RTC drifts.
- VFD and UART pin mappings are hard-coded in `src/main.cpp`.
