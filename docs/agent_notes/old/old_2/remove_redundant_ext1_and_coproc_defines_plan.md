# Architecture Plan: Purge Redundant EXT1 Wake Fallback & Hardware Portability Guards

## 1. Technical Context & Assessment

### User Inquiries:
1. **"is this a redundant fall back to catch app wake from external interupts? if it is, remove it, we dont arm the app for interupts, just wake from ulp."**
   - **Verification:** **Yes, it is 100% redundant legacy fallback code.**
   - In early firmware iterations, the CPU armed direct EXT1 interrupts (`ESP_SLEEP_WAKEUP_EXT1`) to wake on GPIO 0, 18, and 5.
   - Under the current pure ULP event-driven architecture, deep sleep is entered via `sub_power_enter_deep_sleep_mode()` which sets `esp_sleep_enable_ulp_wakeup()`. The CPU core is **never** armed with `EXT1` during normal deep sleep transitions.
   - All tactile button presses and RTC timer/alarm interrupts are captured exclusively by the ULP RISC-V coprocessor in RTC slow memory, which then wakes the main Xtensa core via `ESP_SLEEP_WAKEUP_ULP`.
   - Therefore, the `else if (causes & BIT(ESP_SLEEP_WAKEUP_EXT1))` branch in `h1os_lifecycle.c` (lines 301–312) and its associated `debug_dump_ext1_wake_status()` helper (lines 143–151) are dead code and safe to completely delete.

2. **"coproc is always enabled, these defines sugest its compatable with other hardware, the code is 100% not."**
   - **Verification:** **Agreed.**
   - H1OS is custom firmware designed strictly for the H1 hardware (ESP32-S3 + ULP RISC-V coprocessor + SHTC3 + PCF85063A + ES8311 + NS4168 + SSD1681).
   - Sprinkling `#if CONFIG_ULP_COPROC_ENABLED` / `#else` / `#endif` across the codebase creates an illusion of generic portable hardware fallback that does not exist and can never execute.
   - Stripping these macro guards makes the code cleaner, faster to read, and accurately reflects our fixed hardware invariants.

---

## 2. Proposed Changes

### Primary Target: `components/h1os/src/h1os_lifecycle.c`
1. **Remove redundant EXT1 wake branch in `h1os_start()`:**
   - Delete `else if (causes & BIT(ESP_SLEEP_WAKEUP_EXT1)) { ... }` (lines 301–312).
   - Simplify wake cause classification:
     ```c
     if (is_wake) {
         causes = esp_sleep_get_wakeup_causes();
         if (causes & BIT(ESP_SLEEP_WAKEUP_ULP)) {
             button_woke = (ulp_last_wake_btn != 0);
             if (!button_woke) {
                 is_rtc_wake = true;
             }
         } else {
             /* Internal timer or other unattended wake */
             is_rtc_wake = true;
         }
     }
     ```
2. **Remove orphaned helper `debug_dump_ext1_wake_status()`:**
   - Delete `debug_dump_ext1_wake_status()` (lines 143–151).
3. **Strip obsolete `#if CONFIG_ULP_COPROC_ENABLED` guards:**
   - Line 34: Remove guard around `#include "ulp_h1os.h"`.
   - Line 103: Remove guard around `debug_dump_ulp_telemetry()`.
   - Line 173: Remove `#if CONFIG_ULP_COPROC_ENABLED` / `#else` in `h1os_log_flow_banner()`, removing the unreachable `#else` branch (`trigger_desc = "Direct Hardware Wake Event"`).
   - Line 237: Remove guard around `debug_dump_ulp_telemetry()`.
   - Line 295: Remove guard around ULP wake button check.

---

### Secondary Target (Consistency): `components/h1os/src/orch_flow.c`
- Line 40: Remove `#if CONFIG_ULP_COPROC_ENABLED` around `#include "ulp_h1os.h"`.
- Line 73: Remove `#if CONFIG_ULP_COPROC_ENABLED` around `st->ulp_dispatch_reason = (uint8_t)(ulp_dispatch_reason & 0xFF);`.

---

## 3. Verification & Build Steps
1. Apply edits to `components/h1os/src/h1os_lifecycle.c` (and optionally `orch_flow.c`).
2. Run development build:
   `& "C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1"; idf.py -B build_dev build`
3. Run production build:
   `& "C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1"; idf.py -B build_prod build`
4. Confirm 0 errors, 0 warnings, and clean git status.
5. Commit and push to `origin/E-Class-Dev-002`.
