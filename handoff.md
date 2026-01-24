# Handoff

## Recent prompts / objectives
- 2026-01-21: Review GPS-DO repo, make PlatformIO build/libdeps paths OS-aware, move secrets.h into include/, create handoff.md.
- 2026-01-24: Investigate ESP32 reboot loop with no Thunderbolt connected; prevent assert reset.
- 2026-01-24: Avoid calling `setPacketBroadcastMask` when no GPS serial data is detected; revert library assert change.

## Recent commits (last 3)
- push all the important stuff
- created secrets.h.example
- Initial commit

## Completed milestones
- Config adjusted for OS-aware PlatformIO cache paths (via `pio_paths.py`).
- Secrets header moved to `include/` and docs updated.
- PlatformIO scripts stored in `scripts/` (e.g., `scripts/pio_paths.py`).
- Prevented reboot loop when Thunderbolt is disconnected by skipping `setPacketBroadcastMask` if no serial data is detected.

## Open questions
- Confirm Windows cache path location is correct (`%USERPROFILE%\AppData\Local\PlatformIO\GPSDO\...`).

## Known limitations / TODOs
- NTP stratum/leap indicator not tied to lock state (always stratum 1).
- No long-term holdover calibration; RTC drifts when GPS is lost.
- VFD and UART pin mappings are hard-coded in `src/main.cpp`.
