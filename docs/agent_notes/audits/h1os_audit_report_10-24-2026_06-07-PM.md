# H1OS Codebase & Architecture Documentation Audit Report

**Target Firmware Version:** `2.4.0-dev`

**Audit Scope:** Complete `h1os` component (`include/`, `src/`, `ulp/`, `bootloader_components/`), `main/` showcase application (`main.c`, `screens/*`), `ERRATA.md`, and `docs/` (`architecture/A0–C4`, `drivers/00–07`, `README.md`, `CHANGELOG.md`).

## 1. Executive Summary & Audit Overview

A comprehensive line-by-line audit and refactoring pass was conducted across all 49 source/header files, 27 architecture/driver documentation files, and `ERRATA.md`. Following the consolidation of battery autonomy math directly into the `h1os` core (`sub_power`) and removal of redundant Level 2 cycle/ratio bloat, the semantic version has been bumped to **`2.4.0-dev`** and all identifiers have been aligned with the **Gump Naming Rule** (`naming.md`), **Engineering Lexicon** (`lexicon.md`), and **Embedded Coding Standards** (`coding.md`).

| Audit Category | Issues Found | Key Fixes Applied |
| :--- | :--- | :--- |
| **VBatt & Autonomy Math (`2.4.0-dev`)** | 7 | Consolidated battery math into `h1os` (`sub_power`) and bumped version to `2.4.0-dev`; removed redundant Level 2 ratios (`f_ulp`, `f_stub`, `f_app`, `active_draw_ma`) and cycle counters (`ulp_entry_ccount`, `ulp_exit_ccount`, `ulp_total_cycles`, `total_ulp_ms`, `total_wake_stub_ms`); replaced non-literal `"wall_draw_ma"` / `"wall-clock"` with Gump-proof `avg_draw_ma` / `elapsed_sec` / `elapsed_hours`; added Zero-Volt Cable Guard (`usb_conn && vbat < 3300 -> 4200 mV`); fixed 2-cycle ULP ring lookback (`lookback = (count >= 3) ? 2 : 1`); persisted `s_prev_bat_state` in `RTC_DATA_ATTR`; fixed NVS runtime load/save ordering. |
| **Wake / Sleep Cycles & ULP** | 5 | Fixed `REG_GET_BIT` bitmask vs shift bug on `RTC_CNTL_RDY_FOR_WAKEUP` in `ulp/main.c` (`REG_GET_FIELD`); expanded ULP button tap window from `50..800 ms` to `30..2500 ms` with 30 ms release debounce; fixed `sub_power_init_ulp()` call gating on wake flows; populated `sample.timestamp_sec` in `orch_wake_stub.c`; added button release drain in `sub_power_enter_deep_sleep_mode()` and isolated `HAL_PIN_EPD_DC` (`GPIO 10`) in `hal_io.c`. |
| **Threading, Startup/Shutdown & Low-Power** | 6 | Added `sub_rtc_init()` + `h1os_time_sync_rtc_to_system()` on bringup (disabling 32.768 kHz `CLKOUT` drain and syncing POSIX clock); cached `i2c_master_dev_handle_t` handles in `hal_i2c.c` (eliminating runtime heap churn); synchronized `sub_sdcard_unmount()` with async mount worker task; guarded `h1os_lvgl_has_pending_tasks()` with `lv_lock()`/`lv_unlock()`; wired `sub_audio_flush_frame()` on queue drain; fixed `-Wdouble-promotion` build blocker in `sub_display.cpp` and aligned `ORCH_TRINODE_SPAN_C` (`15.0f`) in `orch_flow.c`. |
| **Main Example Application** | 1 | Removed nested `h1os_lvgl_lock(100)` inside `app_on_splash()` (`main/main.c`) and unlocked the LVGL/240 MHz turbo lock across the 2-second splash viewing delay (`vTaskDelay(2000)`), allowing the CPU to drop to 80 MHz baseline. |
| **Errata & Architecture Docs** | 9 | Reclassified `ERR-S3` in `ERRATA.md` from a speculative silicon CDC defect to an ESP-IDF / register-ordering nuance (`R/W` vs `W1TC` on `RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR` and level-low comparator ordering); added **Errata E15** (3-Pin Symmetrical Center-Hot `[GND][+5V][GND]` Magnetic Pogo-Pin Charge Interface for 100% reverse-polarity protection); updated `A1`, `A2`, `A4`, `A5`, `A6`, `A7`, `A8`, `B1`, `B2`, `C2`, `00_overview.md`, `05_power.md`, `07_io.md`, `README.md`, and `CHANGELOG.md` to `2.4.0-dev`. |

## 2. VBatt Math & Empirical Autonomy Engine Consolidation (`2.4.0-dev`)

1. **Removal of Redundant Level 2 Math & Cycle Bloat (`sub_power.h/.c`, `orch_state.h/.c`, `orch_wake_stub.c`, `ulp/main.c`, `h1os_lifecycle.c`):**
   * **Audit Action:** Stripped out `total_ulp_ms`, `total_wake_stub_ms`, `f_ulp`, `f_stub`, `f_app`, `active_draw_ma`, `entry_ccount`, `exit_ccount`, `total_cycles`, and `rdcycle` CSR reads across the ULP binary, wake stub, RTC persisted state, NVS persistence keys, and `sub_power.h/.c`.
   * **Result:** Streamlined `sub_power_calc_autonomy()` to the lean 5-parameter signature (`initial_soc_x10`, `current_soc_x10`, `total_sleep_sec`, `total_app_ms`, `out_metrics`) computing single-level empirical average current draw (`avg_draw_ma`), consumed capacity (`mah_spent_lap`), and remaining autonomy days (`autonomy_days`) over total elapsed runtime (`elapsed_sec = total_sleep_sec + total_app_ms / 1000.0f`).

2. **Gump Naming Rule & Engineering Lexicon Compliance (`naming.md`, `lexicon.md`):**
   * **Audit Action:** Replaced `"wall_draw_ma"` / `"wall_sec"` / `"wall_hours"` / `"wall-clock"` with literal, Gump-proof identifiers: `avg_draw_ma`, `elapsed_sec`, `elapsed_hours`, and `"total elapsed runtime"`.
   * **Lexicon Cleanup:** Replaced prohibited jargon (`sentinel`, `neutralizes`, `fallback`) across `h1os.h`, `hal_types.h`, `orch_state.h/.c`, `orch_wake_stub.c`, `sub_power.c`, and `sub_display.cpp` with standard IEEE/embedded nomenclature (`Maximum enum value`, `State validation magic word`, `Clears and discharges`, `default_centi_c`).

3. **Cold-Boot NVS Runtime Wipe & Missing Shutdown Save (`h1os_lifecycle.c`):**
   * **Defect:** In `h1os_early_system_bringup()`, `orch_state_load_runtimes_from_nvs()` was called *before* `orch_flow_determine_wakeup()`. On every cold boot, `orch_flow_determine_wakeup()` called `orch_state_reset()`, wiping all NVS-restored battery autonomy counters (`total_sleep_sec`, `total_app_run_ms`, `initial_soc_x10`) back to `0`. Additionally, `execute_system_shutdown()` did not save final runtimes to NVS before cutting power.
   * **Fix:** Moved `orch_state_load_runtimes_from_nvs()` to execute *after* `orch_flow_determine_wakeup()` on `ORCH_FLOW_BOOT`, and added `st->total_app_run_ms` accumulation + `orch_state_save_runtimes_to_nvs()` inside `execute_system_shutdown()`.

4. **Missing Zero-Volt Cable Guard in `sub_power_get_battery_status()` (`sub_power.c`):**
   * **Defect:** When powered via USB without a battery attached, `ulp_last_vbat_mv` reads either `<100 mV` or `~1972 mV` (floating 200k/200k divider, `C2_lessons_learned.md` Section 4.10), causing `sub_power_get_battery_status()` to report `CHARGING (1.97V)` instead of forcing `4200 mV (100% CHARGED)`.
   * **Fix:** Added the Zero-Volt Cable Guard (`if (usb_conn && vbat < 3300U) vbat = 4200U;`) in `sub_power_get_battery_status()`.

5. **2-Cycle Ring Buffer Lookback in `sub_power_get_battery_status()` (`sub_power.c`):**
   * **Defect:** Architecture Doc `A8` Section 6.1 specifies comparing the newest sample $V_{\text{new}}$ against the sample from 2 cycles prior ($V_{\text{prev}}$) to evaluate the $+15\text{ mV}$ charging threshold, but `sub_power.c` only looked back 1 index (`newest_idx - 1`), halving sensitivity on slow charge curves.
   * **Fix:** Updated `prev_idx` to look back 2 samples when `count >= 3` (`uint32_t lookback = (count >= 3U) ? 2U : 1U; prev_idx = (newest_idx + 8U - lookback) % 8U;`).

6. **Non-Persisted `s_prev_bat_state` Across Deep Sleep (`h1os_lifecycle.c`):**
   * **Defect:** `static h1os_battery_state_t s_prev_bat_state = H1OS_BATTERY_DISCHARGING;` inside `h1os_get_telemetry()` resided in standard `.bss` RAM, resetting to `H1OS_BATTERY_DISCHARGING` on every deep-sleep wake and defeating the `state_transition_from_charge` lap-reset detector when unplugging a charger during sleep.
   * **Fix:** Qualified `s_prev_bat_state` with `RTC_DATA_ATTR` at file scope in `h1os_lifecycle.c`.

7. **Missing Final Flow B Sleep Slice Accounting (`h1os_lifecycle.c`, `sub_power.c`, `orch_wake_stub.c`):**
   * **Defect:** `h1os_early_system_bringup()` only called `sub_power_init_ulp()` when `flow == ORCH_FLOW_BOOT`, so the `else if (ulp_last_wake_cause == 3)` branch in `sub_power_init_ulp()` (which adds the final Flow B sleep slice to `st->total_sleep_sec`) never executed on wake.
   * **Fix:** Called `sub_power_init_ulp(st->sample_interval_sec)` on all flows in `h1os_early_system_bringup()`, computed `final_slice` dynamically from `st->flow_b_period_sec` and `st->sample_interval_sec` in `RTC_NOINIT_ATTR` state, and populated `sample.timestamp_sec = st->total_sleep_sec` on every Flow A burst in `orch_wake_stub.c`.

## 3. Wake / Sleep Cycles, ULP, & Wake Stub Fixes

1. **`REG_GET_BIT` Bitmask Bug on `RTC_CNTL_RDY_FOR_WAKEUP` (`ulp/main.c`):**
   * **Defect:** In `ulp/main.c` (`main()`), `!REG_GET_BIT(RTC_CNTL_LOW_POWER_ST_REG, RTC_CNTL_RDY_FOR_WAKEUP)` was used instead of `REG_GET_FIELD`. Because `RTC_CNTL_RDY_FOR_WAKEUP` is defined as the unshifted field mask `0x00000001` (whereas its bit position is `RTC_CNTL_RDY_FOR_WAKEUP_M = BIT(19)`), `REG_GET_BIT` checked bit 0 of `RTC_CNTL_LOW_POWER_ST_REG` instead of bit 19! If bit 0 was `0`, the ULP falsely concluded the main CPU was awake, disarmed `RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA`, and halted—permanently bricking deep-sleep wakeup.
   * **Fix:** Changed `main()` in `ulp/main.c` to `REG_GET_FIELD(RTC_CNTL_LOW_POWER_ST_REG, RTC_CNTL_RDY_FOR_WAKEUP)` (matching `ulp_disarm_and_wake_main()`).

2. **ULP Button Tap Dead Zone (`800..2500 ms`) & Release Bounce (`ulp/main.c`):**
   * **Defect:** `BUTTON_TAP_MIN_MS` was `50` and `BUTTON_TAP_MAX_MS` was `800`, while `BUTTON_HOLD_US` was `2,500,000` (2500 ms). Any user button press lasting between `800 ms` and `2500 ms` (or `30..50 ms`) was silently dropped, and no release debounce was performed before waking the main CPU.
   * **Fix:** Set `BUTTON_TAP_MIN_MS = 30` and `BUTTON_TAP_MAX_MS = 2500` in `ulp/main.c` and added a `30 ms` release-debounce check (`ulp_riscv_delay_us(BUTTON_DEBOUNCE_US); if (ulp_riscv_gpio_get_level(pin) != 0)`) to strictly enforce the Wake-on-Release rule.

3. **Pre-Sleep Button Release Drain & `HAL_PIN_EPD_DC` Isolation (`sub_power.c`, `hal_io.c`):**
   * **Defect:** `sub_power_enter_deep_sleep_mode()` drained `HAL_PIN_RTC_INT` (`GPIO 5`) before arming ULP GPIO wakeup, but did not verify that `HAL_PIN_BUTTON_BOOT` (`GPIO 0`) and `HAL_PIN_BUTTON_POWER` (`GPIO 18`) were released HIGH. Additionally, `hal_io_isolate_sleep_pads()` did not hold `HAL_PIN_EPD_DC` (`GPIO 10`) HIGH during sleep as specified in `05_power.md`.
   * **Fix:** Added a 100 ms bounded wait for `BOOT` and `POWER` buttons to release HIGH in `sub_power_enter_deep_sleep_mode()`, and added `gpio_set_level(HAL_PIN_EPD_DC, 1); gpio_hold_en(HAL_PIN_EPD_DC);` (and corresponding `gpio_hold_dis(HAL_PIN_EPD_DC)` on wake) in `hal_io.c`.

4. **`orch_flow_execute_sleep()` Ignoring `sleep_sec` Parameter (`orch_flow.c`):**
   * **Defect:** When `st->flow_b_period_sec` was populated, `orch_flow_execute_sleep(uint32_t sleep_sec)` ignored a custom `sleep_sec` argument passed to `h1os_sleep(sleep_sec)`.
   * **Fix:** Updated `orch_flow_execute_sleep()` to honor `sleep_sec` when non-zero (`uint32_t flow_b_sec = (sleep_sec > 0) ? sleep_sec : ...`).

## 4. Threading, Clean Startup/Shutdown, & Low-Power Runtime Optimizations

1. **Missing `sub_rtc_init()` & POSIX Clock Sync on Bringup (`h1os_lifecycle.c`):**
   * **Defect:** Neither `sub_rtc_init()` nor `h1os_time_sync_rtc_to_system()` was called anywhere in `h1os_lifecycle.c` or `main.c`. Consequently, on cold battery boot the PCF85063A `CLKOUT` pin remained at its power-on default (oscillating at 32.768 kHz and leaking continuous current), the 12.5 pF crystal load capacitance (`CAP_SEL`) was never set, and the ESP32 POSIX clock stayed at 1970-01-01.
   * **Fix:** Added `if (sub_rtc_init() == ESP_OK) { (void)h1os_time_sync_rtc_to_system(); }` in `h1os_early_system_bringup()`.

2. **Runtime Heap Allocation Churn in `hal_i2c.c` (Rule 3 Violation):**
   * **Defect:** Every call to `hal_i2c_write()`, `hal_i2c_read()`, and `hal_i2c_write_read()` dynamically allocated and freed a new `i2c_master_dev_handle_t` via `i2c_master_bus_add_device()` / `i2c_master_bus_rm_device()`. During `sub_audio_init()` alone, this caused 35+ heap allocations and frees, violating `B3_firmware_standards.md` Rule 3 (Zero Runtime Dynamic Allocation).
   * **Fix:** Cached `i2c_master_dev_handle_t` handles for the onboard I2C peripherals (`HAL_I2C_ADDR_ES8311`, `HAL_I2C_ADDR_PCF85063`, `HAL_I2C_ADDR_SHTC3`) in `hal_i2c.c` and released them cleanly in `hal_i2c_deinit()`.

3. **Async MicroSD Mount vs Pre-Sleep Unmount Race (`sub_sdcard.c`):**
   * **Defect:** `sub_sdcard_mount_async()` spawns `sdcard_mount_worker_task` on Core 0. If `sub_sdcard_unmount()` is called while the worker task is still mid-mount, a race condition on `s_sd_card` and SDMMC host state can occur. Also, `host.command_timeout_ms = 3` (3 ms) was too aggressive for standard MicroSD cards that take 5–15 ms on `CMD0`/`ACMD41`.
   * **Fix:** Qualified `s_mount_task` as `volatile`, added a bounded wait loop in `sub_sdcard_unmount()` until `s_mount_task == NULL`, increased `command_timeout_ms` to `20` ms, and set `max_files = 5` per `06_sdcard.md`.

4. **Thread-Safe LVGL Pending Task Check (`h1os_lvgl.cpp`):**
   * **Defect:** `h1os_lvgl_has_pending_tasks()` read `s_lv_display->inv_p` and `s_lv_display->rendering_in_progress` from Core 0 without acquiring `lv_lock()`, racing with `lv_timer_handler()` on Core 1.
   * **Fix:** Wrapped the display refresh timer and invalidation checks in `h1os_lvgl_has_pending_tasks()` with `lv_lock()` and `lv_unlock()`.

5. **Unused `sub_audio_flush_frame()` & Double-Promotion Build Blocker (`sub_audio.c`, `sub_display.cpp`, `orch_flow.c`):**
   * **Defect:** `sub_audio_flush_frame()` in `sub_audio.c` was marked `__unused` and never called after `audio_worker_task()` drained the queue. In `sub_display.cpp` (line 184), `(double)glass_cc / 100.0` used an unsuffixed double literal, and in `orch_flow.c` (line 42), `ORCH_TRINODE_SPAN_C` was `5.0f` instead of `15.0f` per `A7_sensor_psychrometrics.md`.
   * **Fix:** Wired `if (uxQueueMessagesWaiting(s_audio_queue) == 0) { (void)sub_audio_flush_frame(); }` in `audio_worker_task()`, fixed `(double)((float)glass_cc / 100.0f)` in `sub_display.cpp` (and implemented `sub_display_deinit()`), and updated `ORCH_TRINODE_SPAN_C` to `15.0f` in `orch_flow.c`.

## 5. Main Example Application Fixes (`main/main.c`)

* **Nested LVGL Lock & 2-Second 240 MHz CPU Hold in `app_on_splash()` (`main/main.c`):**
  * **Defect:** `h1os_lifecycle.c` acquires `h1os_lvgl_lock(1000)` (which acquires the 240 MHz CPU PM lock and recursive `lv_lock()`) before calling `h1os_trigger_splash(H1OS_SPLASH_BOOT)`. Inside `main/main.c`, `app_on_splash()` called `h1os_lvgl_lock(100)` a second time, rendered the splash image, called `h1os_lvgl_unlock()` once, and then slept for 2 seconds (`vTaskDelay(pdMS_TO_TICKS(2000))`) while the outer `h1os_lvgl_lock` was still held! This kept the ESP32-S3 pinned at 240 MHz for the entire 2-second delay, burning ~100 mJ of unnecessary battery energy and warming the enclosure on boot.
  * **Fix:** Removed the redundant nested lock in `app_on_splash()` and temporarily released `h1os_lvgl_unlock()` across `vTaskDelay(pdMS_TO_TICKS(2000))` before re-acquiring `h1os_lvgl_lock(1000)` for `app_on_boot()`.

## 6. Hardware Errata (`ERRATA.md`) & Architecture Documentation Updates (`docs.zip`)

1. **`ERR-S3` Reclassified (Not a Silicon Defect):**
   * Reclassified `ERR-S3` in `ERRATA.md` and `C2_lessons_learned.md` Section 4.6 from a speculative silicon *"Clock Domain Crossing (CDC) Wake Latch Bounce"* to an **ESP-IDF / Software Register-Ordering Nuance**. Specifically, `RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR` (Bit 30 of `RTC_CNTL_ULP_CP_TIMER_REG`) is a synchronous `R/W` reset bit rather than a self-clearing `W1TC` strobe, and RTC IO wakeups are level-sensitive (`GPIO_INTR_LOW_LEVEL`). Leaving Bit 30 set held the wake gate in reset (causing the sleep freeze), whereas clearing it before `RTC_GPIO_STATUS_W1TC_REG` or while `GPIO 5` `/INT` was still physically LOW caused immediate level re-latching.

2. **Added Errata E15 — 3-Pin Center-Hot Magnetic Pogo-Pin Charge Interface (`[GND] [VBUS +5V] [GND]`):**
   * Added **Errata E15** to `ERRATA.md` (Section 1 Index, Section 2 Engineering Analysis, and Section 3 Rev B BOM) specifying a flush 3-pin symmetrical magnetic pogo-pin charging interface with `+5.0V VBUS` on the center pin and `GND` on both outer flanking pins (`[GND]—[+5V]—[GND]`). This guarantees 100% geometric reverse-polarity immunity in either $0^\circ$ or $180^\circ$ orientation with zero rectifier diode drop, eliminates USB-C insertion wear and cable torque on the lightweight enclosure, and pairs with a `SP1003` TVS diode + resettable polyfuse on the center pin.

3. **Architecture & Driver Documentation (`2.4.0-dev`):**
   * Updated `A1`, `A2`, `A4`, `A5`, `A6`, `A7`, `A8`, `B1`, `B2`, `C2`, `00_overview.md`, `05_power.md`, `07_io.md`, `README.md`, and `CHANGELOG.md` to reflect `2.4.0-dev`, the single-level elapsed runtime `avg_draw_ma` autonomy engine, and full compliance with `naming.md`, `lexicon.md`, and `coding.md`.