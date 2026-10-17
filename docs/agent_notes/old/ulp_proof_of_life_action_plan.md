# Action Plan: Hardware Proof-of-Life Check (ULP Dual Wake)

**Target Silicon:** ESP32-S3-PICO-1-N8R8  
**Target Board:** Waveshare ESP32-S3 ePaper 1.54" V2  
**Branch:** `E-Class-Dev-002`  
**Governing Authority:** User Directive & Architecture Alignment  
**Date:** 2026-10-16  

---

## 1. Objective & Scope

Establish an isolated, dead-simple **Proof of Life** test to verify that the ESP32-S3 hardware and ULP-RISC-V coprocessor successfully wake from deep sleep on:
1. **Periodic Hardware Timer** (every 10 seconds), and
2. **External RTC GPIO Interrupts** (GPIO 0 / BOOT button, GPIO 18 / POWER button, GPIO 5 / RTC INT).

All complex H1OS subsystems (LVGL, SHTC3 sensors, SD card, audio synthesizer, state machines) will be completely bypassed so that zero peripheral side-effects or timing conflicts can interfere with low-power wake arbitration.

---

## 2. Root Cause Identified: Input Pad Hold (`rtc_gpio_hold_en`)

From the user's notebook and hardware audit:
- Calling `rtc_gpio_hold_en()` or `gpio_deep_sleep_hold_en()` on **input wake pins** locks the internal digital input buffer at the moment sleep is entered.
- When held, external electrical state transitions (e.g., pressing a tactile button pulling the pin to GND) cannot propagate through the frozen input buffer into the RTC GPIO level comparator.
- **The Golden Rule for Wake Inputs:** **Never enable pad hold on active wake inputs!** Pad hold is exclusively intended for output pins that must maintain static voltage levels (e.g. display CS/RST, PA mute).

---

## 3. Execution Plan

### Step 1: Discard Dirty Working Changes
Execute `git restore .` to revert `h1os_lifecycle.c`, `hal_io.c`, `sub_power.c`, and `components/h1os/ulp/main.c` back to clean commit `49147f8`.

### Step 2: Minimal ULP Firmware (`components/h1os/ulp/main.c`)
Replace `components/h1os/ulp/main.c` with a minimal, bulletproof wake observer:
- Retains all exported linker symbols so main application compiles cleanly.
- Reads `RTC_GPIO_STATUS_REG` immediately at entry.
- Reads live pin levels of GPIO 0, GPIO 18, and GPIO 5.
- Determines cause:
  - `cause = 1`: BOOT button (GPIO 0)
  - `cause = 2`: POWER button (GPIO 18)
  - `cause = 4`: External RTC Alarm (GPIO 5)
  - `cause = 3`: Periodic Timer tick (10s)
- Clears wake latches (`RTC_GPIO_STATUS_W1TC_REG` and `RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR`).
- Calls `ulp_riscv_wakeup_main_processor()`.
- Calls `ulp_riscv_halt()` to re-arm the sleep timer.

### Step 3: Minimal Main CPU Test Harness (`examples/H1OS/main/main.c`)
In `examples/H1OS/main/main.c`:
- In `app_main()`, bypass `h1os_start()` and run `proof_of_life_test()`:
  1. Inspect `esp_sleep_get_wakeup_cause()`.
  2. If woken by ULP (`ESP_SLEEP_WAKEUP_ULP`):
     - Output high-visibility banner to serial monitor:
       ```text
       ================================================================================
       [PROOF OF LIFE] MAIN CPU WOKEN BY ULP!
       Wake Count:      %lu
       Wake Cause:      %s (%lu)
       RTCIO Status:    0x%08lx
       Boot Button:     %lu
       ================================================================================
       ```
     - Delay 2 seconds.
  3. If Cold Boot:
     - Print initial banner.
     - Load ULP binary: `ulp_riscv_load_binary(ulp_h1os_bin_start, ...)`.
  4. Configure wake pins:
     - `GPIO 0` & `GPIO 18`: `rtc_gpio_init`, input mode, discrete pull-ups only (no internal pull-ups), **NO pad hold**.
     - `GPIO 5`: `rtc_gpio_init`, input mode, internal pull-up enabled, **NO pad hold**.
     - Arm `RTC_GPIO_PIN0_REG + 4 * pin`: `WAKEUP_ENABLE = 1`, `INT_TYPE = 4` (`LOW_LEVEL`).
  5. Program 10s timer: `ulp_set_wakeup_period(0, 10000000)`.
  6. Arm Dual Wake:
     - `ulp_riscv_cfg_t cfg = { .wakeup_source = ULP_RISCV_WAKEUP_SOURCE_GPIO };`
     - `ulp_riscv_config_and_run(&cfg);`
     - `SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN | RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);`
  7. Enable ULP wakeup of main CPU:
     - `esp_sleep_enable_ulp_wakeup();`
     - `esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);`
  8. Log pre-sleep armed register state and enter deep sleep:
     - `esp_deep_sleep_start();`

### Step 4: Build & Hardware Validation
1. Compile with `idf.py -B build_dev build` and verify clean build.
2. User flashes to hardware (`idf.py -p COM3 flash`).
3. User tests:
   - **Test A (Timer):** Do not press any buttons. Verify main CPU wakes every 10 seconds with `Wake Cause: TIMER TICK (3)`.
   - **Test B (GPIO Wake):** During sleep, press BOOT (GPIO 0). Verify main CPU wakes immediately with `Wake Cause: BOOT BUTTON (1)` and `RTCIO Status = 0x000001`.
   - **Test C (GPIO Wake):** During sleep, press POWER (GPIO 18). Verify main CPU wakes immediately with `Wake Cause: POWER BUTTON (2)` and `RTCIO Status = 0x040000`.
