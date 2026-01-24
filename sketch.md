# GPSDO Project Sketch

## Overview
- PlatformIO Arduino project for an ESP32-based GPS Disciplined Oscillator (Trimble Thunderbolt).
- Primary entrypoints: `platformio.ini`, `src/main.cpp`, `src/secrets.h`.
- Hardware: Thunderbolt TSIP over UART + Futaba VFD display.

## Current Behavior
- Reads Thunderbolt timing/status over UART.
- Keeps ESP32 RTC + TimeLib synced to GPS time.
- Serves NTP over UDP port 123.
- Displays time/status on the VFD.

## Milestones (Recommended)
1) NTP service discoverable on LAN with a configurable hostname (mDNS + DHCP hostname).
  - Status report (serial & minimal HTTP in .data folder using SPLIFFS) for monitoring.
2) NTP quality signaling: adjust stratum/leap indicator based on Thunderbolt lock/health.

## Notes / Assumptions
- ESP32 environment is `wemos_d1_mini32`.
- `wifi_hostname` in `src/secrets.h` is the user-configurable hostname.
