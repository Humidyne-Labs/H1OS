# 🧭 Features-to-Date: ESP32-S3 BSP & Humiditron Platform

This document provides a comprehensive audit comparing the project's historical planning and specification documents in [`docs/dev-action/`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/docs/dev-action/) against the current production codebase as of **v1.3.1**.

It categorizes all platform features and subsystems into three distinct operational states:
1. **✅ What's Been Done (Completed & Verified)**
2. **⏳ What Still Needs Done (Pending / Backlog)**
3. **🚫 What's Not Going To Get Done (Explicitly Dropped with Technical Rationale)**

---

## 1. ✅ What's Been Done (Completed & Verified)

### A. Environmental Sensing & Psychrometric Architecture
- [x] **Class-E Environmental Hygrometer Architecture** ([`bsp_sensors.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_sensors.c), [`bsp_sensors.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp_sensors.h)):
  - **Zero-I2C Runtime Invariant:** Strict prevention of SHTC3 physical I2C polling during active UI or Turbo execution. Physical SHTC3 reads occur strictly during the autonomous $<10\,\text{ms}$ cold hot-wake sprint (`bsp_sensors_sample_raw()`).
  - **Integer Raw ADC Differential Gating:** 1-cycle integer raw evaluation (`SHTC3_RAW_IS_SETTLED`: 562 LSB counts / $1.50^\circ\text{C}$ margin) marking unperturbed samples.
  - **64-Bit Clean Window Bitmask:** `window_clean_mask` tracking cold, settled slots across the ring buffer.
  - **Complete Thermodynamic Units:** Full support for Kelvin (`ambient_temp_k`, `dew_point_k`), Celsius, and Fahrenheit.
  - **Node 2 (SSD1681 On-Glass Display Sensor):** Half-duplex 4-wire hardware SPI read via Command `0x1B` returning off-board glass temperature isolated from PCB ground plane heating.
  - **Node 3 (ESP32-S3 TSENS Silicon Die):** On-chip analog temperature sensor integration via `driver/temperature_sensor.h` for thermal perturbation cross-checks.
- [x] **4-Byte Packed Sample Ring Buffer & Sliding Window Math Engine** ([`bsp_env_telemetry.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp_env_telemetry.h), [`bsp_equ_math.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_equ_math.c), [`bsp_equ_math.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp_equ_math.h)):
  - Compact 4-byte packed sample struct (`bsp_env_compact_sample_t`) reducing 64-slot history footprint in RTC Slow SRAM to 288 bytes.
  - `bsp_math_calc_sliding_window_metrics()` calculating $T_{\text{avg}}$, baseline $T_{\text{floor}}$, $T_{\text{ceiling}}$, $\text{RH}_{\min}$, $\text{RH}_{\max}$, and clean settled sample rate ($0\dots 60\,\text{smp/h}$) across clean slots.
  - Vapor pressure conservation ($\gamma(T, RH)$, Magnus-Tetens dew point, ambient RH reconstruction, and absolute humidity in $g/m^3$).
  - Dynamic thermal confidence scoring ($0\dots 100\%$) based on thermal delta $|T_{\text{sens}} - T_{\text{amb}}|$.

### B. Firmware "Sleep-Sprint" Architecture & Dynamic Frequency Scaling (DFS)
- [x] **Dynamic Frequency Scaling Engine (DFS)** ([`bsp_power.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_power.c), [`bsp_power.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp_power.h)):
  - Configured 80 MHz quiet baseline CPU operating frequency (`CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ_80=y`, `CONFIG_PM_ENABLE=y`) to drop active current from ~80 mA to ~28 mA.
  - Implemented high-speed PM Turbo locks (`bsp_pm_turbo_acquire()` / `bsp_pm_turbo_release()`) using `ESP_PM_CPU_FREQ_MAX` to accelerate to 240 MHz exclusively during compute-intensive UI rendering and E-Paper SPI blitting.
- [x] **Sub-15ms Zero-Heat Sleep-Sprint Pipeline** ([`bsp_power.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_power.c), [`examples/Unified_Environmental_Demo/main/main.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/examples/Unified_Environmental_Demo/main/main.c)):
  - Fast-boot wake stub integration (`esp_set_deep_sleep_wake_stub_default_entry()` / `esp_deep_sleep_disable_rom_logging()`) for ultra-rapid resume.
  - SHTC3 fast-mode read (`0x44DE`) completing in under 15 ms with total energy $< 1.5\text{ mJ}$ ($< 0.005^\circ\text{C}$ local rise), completely eliminating ground plane thermal creep.
  - 64-sample telemetry ring buffer (`bsp_env_telemetry_history_t`) in RTC Slow SRAM for zero-heat autonomous background sampling every 60 seconds.
  - E-Paper UI displays persistent verified sample count (`SMP: %lu`) on Row 1 ($y=140$).
- [x] **Pure Hardware Countdown Timer & Bounded Sleep Engine** ([`bsp_power.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_power.c), [`bsp_power.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp_power.h), [`bsp_rtc.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_rtc.c)):
  - **Pure Hardware Down-Counter:** Replaced calendar alarm matching with direct PCF85063A hardware countdown timer (`bsp_rtc_set_countdown_timer()`), running purely on the 32.768 kHz quartz crystal with zero clock time/epoch dependency.
  - **Bounded Sleep Duration:** Globally enforces minimum sleep period of **120 seconds** (`BSP_SLEEP_MIN_DURATION_SEC = 120` / 2 min) and maximum of **4 hours** (`BSP_SLEEP_MAX_DURATION_SEC = 14400` / 240 min) with automatic clamping.
- [x] **Display Driver NULL SPI Handle Safety Guard** ([`bsp_display.cpp`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_display.cpp)):
  - Guarded `bsp_display_deep_sleep()` and all display driver accessors against uninitialized SPI handle (`s_spi_handle == NULL`), eliminating kernel assertions and crash-reboot loops during minimal headless hot-wake sprints (`BSP_INIT_MODE_MINIMAL`).
- [x] **Internalized 60s Hot-Wake Sensor Sprint & Pure I2C Cadence** ([`bsp_common.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_common.c), [`bsp_sensors.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp_sensors.h), [`examples/Unified_Environmental_Demo/main/main.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/examples/Unified_Environmental_Demo/main/main.c)):
  - **Internalized Autonomous Sampling:** Fully internalized the 60-second headless sprint into `bsp_app_start()`. When waking from the internal RTC timer, the BSP automatically executes a sub-10ms SHTC3 acquisition, integer differential gating, commits telemetry to the RTC ring buffer, advances `SMP`, and returns to deep sleep without waking the application or invoking user-facing callbacks.
  - **Buttonless Headless Sprint**: Excluded button GPIO checks and ISR hooks from `bsp_hot_wake_sprint_init()`. The sensor sprint exclusively manages I2C and registers, preserving digital pad holds until `bsp_io_early_init()` in Flow B.
  - **Zero-Hour Handoff & Timer Invalidation:** At $T = 120\text{s}$ (zero hour), Flow A's cold sensor acquisition always executes first (<10ms). The PCF85063A is queried over I2C, and if expired, promotes cleanly to Flow B. Flow B immediately invalidates Flow A's sleep timer via `esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER)` to ensure pristine synchronization.
  - **Bounded Sleep Entry Check:** Bypassed button release checking entirely for Flow A (`BSP_INIT_MODE_MINIMAL`), and bounded Flow B checking to 200ms (max 4 iterations $\times$ 50ms), permanently fixing the 5-minute unresponsive device lockup.
  - **Timer Domain Separation:** ESP32-S3 internal RTC timer is guarded and dedicated exclusively to hot-wake sprints (60s test); external PCF85063A hardware RTC is dedicated exclusively to application-level countdown timers (120s test / IRL interval).
  - **SHTC3 Thermal Physics Developer Notice:** Documented PCB ground plane heating ($+1.5^\circ\text{C}\dots +3.0^\circ\text{C}$) directly in `bsp_sensors.h`.
- [x] **Dual-Wake & Two-Flow Firmware Architecture** ([`bsp_power.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_power.c), [`bsp_common.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_common.c), [`bsp_rtc_mem.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp_rtc_mem.h), [`examples/Unified_Environmental_Demo/main/main.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/examples/Unified_Environmental_Demo/main/main.c)):
  - **Flow A (Headless 60s Sensor Sprints)**: Wakes from internal 60s sleep timer in `BSP_INIT_MODE_MINIMAL` (no display, no LVGL, no audio), reads SHTC3 in sub-10ms at 80 MHz, logs to `s_env_history` ring buffer, advances monotonic `SMP`, and returns to deep sleep ($<1.5\text{ mJ}$, zero display flicker, zero thermal rise).
  - **Flow B (Full UI Refresh Wake)**: Wakes from external PCF85063A Countdown Timer (`GPIO 5`) or manual button press, cancels Flow A timer, executes zero-hour cold sprint if needed, initializes display in `BSP_INIT_MODE_FAST`, boosts CPU to 240 MHz Turbo, updates LVGL UI with fresh cold telemetry (`SMP: %lu`, `BAT`, `Rate`, `I: uA`, `Up: min`), executes differential partial refresh blit, and freshly re-arms both Flow A and Flow B timers.

### C. Display & LVGL v9 Graphics Engine
- [x] **SSD1681 Monochrome e-Paper Driver** ([`bsp_display.cpp`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_display.cpp), [`bsp_display.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp_display.h)):
  - Cold-boot-only OTP master activation (`0x22 0xB1` + `0x20`); flash suppressed on wake cycles.
  - Differential partial refresh with factory 159-byte waveform LUT (`WF_PARTIAL_1IN54`), display option `0x37`, border `0x3C = 0x80`, and dual RAM buffer synchronization (`0x24` New, `0x26` Old).
  - Silent, differential ~300ms updates without whole-screen blinking.
- [x] **LVGL v9 Integration Port & Automated Refresh Gating** ([`bsp_lvgl.cpp`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_lvgl.cpp), [`bsp_lvgl.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp_lvgl.h)):
  - Automatic full OTP vs. differential partial refresh arbitration in `lvgl_display_flush_cb()` based on `s_first_boot_flush` and `bsp_display_get_partial_count() >= PARTIAL_REFRESH_LIMIT` (30).
  - Thread-safe mutex locking (`bsp_lvgl_lock()` / `bsp_lvgl_unlock()`).
  - 1-bit monochrome (`LV_COLOR_FORMAT_I1`) direct bit-blit engine.
  - Warm-boot anti-flicker guard to drop blits on empty canvases.
- [x] **RTC Memory Re-Partitioning** ([`bsp_rtc_mem.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_rtc_mem.c)):
  - Relocated 5,000-byte E-Paper frame buffer to RTC Fast Memory (`RTC_FAST_ATTR`), freeing 61% (5 KB) of RTC Slow SRAM for telemetry ring buffers.

### D. Power Management, Hardware Lifecycle, & Buttons
- [x] **Power Rail Control & Zero-Management Bootloader Latch** ([`bsp_boot_hook.c`](components/esp32-s3_bsp/bootloader_components/bsp_boot_hook/bsp_boot_hook.c), [`bsp_power.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_power.c), [`bsp_power.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp_power.h)):
  - 2nd-stage bootloader hook (`bootloader_before_init()`) asserts `GPIO 17` (`BSP_PIN_POWER_HOLD`) HIGH and engages hardware RTC pad hold latch (`gpio_ll_hold_en`) within $<25\text{ ms}$ of power-on.
  - Zero runtime software management of `GPIO 17`: stays hardware-latched across CPU frequency scaling, resets, and deep sleep.
  - Clean shutdown sequence in `bsp_power_off()`: releases pad hold and drives `GPIO 17 = 0` to cut battery LDO gate power.
  - Critical battery auto-shutdown guard ($\le 10\%$ SoC / $< 3400\text{ mV}$).
- [x] **Non-Blocking PXE Button Engine & ROM Bootloader Jump** ([`main.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/examples/Unified_Environmental_Demo/main/main.c), [`bsp_power.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp_power.h)):
  - `app_on_pxe()` only clocks GPIO levels if pins are actively held LOW, eliminating cold-boot latency ($0\,\text{ms}$ overhead on released buttons).
  - BOOT0 (`GPIO 0`) held $\ge 1.2\,\text{s}$ cleanly forces reboot into silicon ROM Download Bootloader (`bsp_system_reboot_to_bootloader()`).
  - BOOT0 short press ($< 400\,\text{ms}$) immediately toggles active dashboard screens ($1/2 \leftrightarrow 2/2$).
  - POWER (`GPIO 47`) held $\ge 1.2\,\text{s}$ initiates graceful shutdown (`bsp_power_off()`).
- [x] **Modular Hot-Wake Build-Up & Clean-Up Lifecycle** ([`bsp_common.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_common.c)):
  - Decoupled hot-wake sprint into `bsp_hot_wake_sprint_init()` and `bsp_hot_wake_sprint_deinit()`.
  - Brings up only I2C and promotion ISRs, executes SHTC3 read, and cleanly tears down all sprint resources back to a pristine POR state before sleep entry or promotion to full UI wake.
- [x] **Hardware Real-Time Clock** ([`bsp_rtc.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_rtc.c), [`bsp_rtc.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp_rtc.h)):
  - PCF85063A I2C driver supporting POSIX time conversions, countdown timers, and external RTC alarm interrupts (`GPIO 5`).
- [x] **Structured Application Engine & Automatic Shutdown Hook Registration** ([`bsp_common.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_common.c), [`bsp.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp.h)):
  - `bsp_app_start()` orchestrating hardware profiles, wake context parsing, registering `on_shutdown` with `bsp_power_register_shutdown_cb()`, and dispatching to `on_pxe`, `on_cold_boot`, `on_wake`, and `on_before_sleep`.

### E. Audio Subsystem
- [x] **ES8311 Codec & NS4150B/NS4168 Amplifier** ([`bsp_audio.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_audio.c), [`bsp_audio.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp_audio.h)):
  - Native 16-bit Mono I2S master driver with 256-point sine table synthesis.
  - Zero-heat software power-down sequence ($\le 1\,\mu\text{A}$ quiescent draw).
  - Maintained 3.3V power gate (`GPIO 42 = 0`) to prevent internal ESD diode clamping on shared I2C bus.

### F. Applications & Developer Experience
- [x] **Unified Environmental Demo** ([`examples/Unified_Environmental_Demo/`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/examples/Unified_Environmental_Demo/)):
  - 200x200 monochrome UI rendering pure physical telemetry: $V_{\text{bat}}$ (V / %), active execution time in ms, exact PCF85063A POSIX uptime, sample cycle counter, multi-node temperatures, dew point, and absolute humidity.
  - Multi-screen dashboard with instant BOOT0 switching.
  - `CONFIG_ENABLE_DEV_CONTINUOUS_MODE` switch to keep USB COM port connected during bench testing.
- [x] **Peripherals Test Suite** ([`examples/Peripherals_Test_Suite/`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/examples/Peripherals_Test_Suite/)):
  - Hardware validation suite for e-Paper, SHTC3, PCF85063A, ES8311, FT6336 Touch, and Buttons.

---

## 2. ⏳ What Still Needs Done (Pending / Backlog)

### A. Micro SD Card Power & Batch Logging Optimization
- [ ] **Micro SD Card Standby Characterization**:
  - Profile continuous idle current draw ($300\,\mu\text{A}\dots 800\,\mu\text{A}$) on the un-gated SD VDD rail.
  - Implement batched append-and-flush routines in [`bsp_sdcard.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_sdcard.c) to write 64-sample ring buffers to FAT32 before unmounting SPI bus to minimize active current.

### B. Wi-Fi Provisioning & Time Synchronization
- [ ] **Automated SNTP-to-PCF85063A Register Commit**:
  - Background SNTP client synchronization that commits synchronized network time into physical PCF85063A RTC registers upon network connection.
- [ ] **Local Wi-Fi BLE GATT Provisioning Integration in Unified Demo**:
  - Integrate local BLE GATT provisioning (`bsp_prov`) for configuring Wi-Fi credentials directly over Bluetooth Low Energy (via Chrome Web Bluetooth) without cloud dependencies.

---

## 3. 🚫 What's Not Going To Get Done (Explicitly Dropped & Deprecated)

### 1. Synthetic Thermal Divider Calibration (`bsp_sensor_cal.c/.h`)
- **Status:** **Permanently Removed.**
- **Technical Rationale:** The legacy synthetic formula subtracted an empirical fraction of the MCU temperature from SHTC3 readings. Because the relationship between PCB thermal dissipation and localized relative humidity is governed by the Clausius-Clapeyron relation and saturation vapor pressure, linear temperature subtractions caused severe divergence under dynamic ambient conditions. Replaced permanently with the **Thermodynamic Psychrometric Invariant Engine**.

### 2. Theoretical Battery Runtime & Current Modeling in UI
- **Status:** **Permanently Dropped.**
- **Technical Rationale:** Hardcoded mathematical assumptions (e.g., fixed $280\,\mu\text{A}$ average current, theoretical battery autonomy days) produced inaccurate telemetry due to battery chemistry variations and temperature coefficients. The UI now displays strictly directly-measured physical parameters ($V_{\text{bat}}$, SoC %, active execution latency in ms, PCF85063A uptime, cycle count).

### 3. Continuous Radio Operation During Deep Sleep Cycles
- **Status:** **Explicitly Excluded.**
- **Technical Rationale:** Maintaining continuous Wi-Fi or BLE radio connections consumes $80\dots 240\text{ mA}$, draining a 400 mAh battery in under 3 hours. Low-power operational targets ($22\,\mu\text{A}$ quiescent floor) require radios to remain completely unpowered during deep sleep, with optional fast reconnection (<400ms) only during scheduled telemetry windows.

### 4. Hardware Power Rail Switch for Micro SD Card
- **Status:** **Hardware Constraint (Cannot Implement in Software).**
- **Technical Rationale:** The Waveshare ESP32-S3 1.54" V2 schematic hardwires the MicroSD card socket $V_{\text{DD}}$ to the main 3.3V rail without an inline P-MOSFET gate. Software power gating cannot completely disconnect the card rail; low-power management is limited to SPI CS de-assertion and software standby commands.

### 5. ThingsBoard MQTTS & Cloud JSON Provisioning
- **Status:** **Explicitly Dropped.**
- **Technical Rationale:** Out of scope for standalone low-power environmental monitoring. All provisioning is handled locally via direct BLE GATT pairing (`bsp_prov`), eliminating external cloud dependencies, complex broker state machines, and MQTT payload serialization overhead.

### 6. ULP Coprocessor Autonomous I2C Polling
- **Status:** **Hardware Constraint (Permanently Decommissioned).**
- **Technical Rationale:** The Waveshare ESP32-S3 1.54" board routes the shared I2C bus to `GPIO 47/48`, which are strictly digital IO matrix pins unpowered during deep sleep and physically inaccessible to the RTC-domain ULP RISC-V coprocessor (`RTCIO 0..21`). Replaced with the **80 MHz Dynamic Frequency Scaling (DFS) Sleep-Sprint Engine** delivering sub-15ms, $<1.5\text{ mJ}$ wake cycles with zero ground plane heating.

---

## 4. Master Requirements Verification Matrix

| Requirement / Subsystem | Source Document | Implemented File(s) | Status |
| :--- | :--- | :--- | :--- :--- |
| **Class-E Zero-I2C Invariant** | `gated-model.md` | [`bsp_sensors.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_sensors.c), [`bsp_sensors.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp_sensors.h) | **COMPLETE** |
| **Psychrometric Invariant Engine** | `HUMIDITRON_TRI_NODE_ULP_ACTION_PLAN.md` | [`bsp_equ_math.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_equ_math.c), [`bsp_equ_math.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp_equ_math.h) | **COMPLETE** |
| **SSD1681 Glass Temp (Cmd 0x1B)** | `ACTION_PLAN.md` | [`bsp_display.cpp`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_display.cpp) | **COMPLETE** |
| **DFS Turbo PM Locks (80<->240 MHz)** | `sleep_sprint_dfs_plan.md` | [`bsp_power.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_power.c), [`bsp_power.h`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/include/bsp/bsp_power.h) | **COMPLETE** |
| **Sub-15ms Sleep-Sprint Engine** | `sleep_sprint_dfs_plan.md` | [`bsp_power.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_power.c), [`examples/Unified_Environmental_Demo/main/main.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/examples/Unified_Environmental_Demo/main/main.c) | **COMPLETE** |
| **EPD Automatic Refresh Gating** | User Requirements | [`bsp_display.cpp`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_display.cpp), [`bsp_lvgl.cpp`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_lvgl.cpp) | **COMPLETE** |
| **Non-Blocking PXE Button Engine** | User Requirements | [`bsp_power.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_power.c), [`examples/Unified_Environmental_Demo/main/main.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/examples/Unified_Environmental_Demo/main/main.c) | **COMPLETE** |
| **Power Latch & Clean Shutdown** | `ACTION_PLAN.md` | [`bsp_power.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_power.c), [`bsp_button.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_button.c) | **COMPLETE** |
| **Audio Zero-Heat Standby** | `ACTION_PLAN.md`, `hardware-notes.md` | [`bsp_audio.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/esp32-s3_bsp/src/bsp_audio.c) | **COMPLETE** |
| **Unified Low-Power Demo App** | `new-project-outline-low-power-test.md` | [`examples/Unified_Environmental_Demo/`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/examples/Unified_Environmental_Demo/) | **COMPLETE** |
| **Dev Continuous Mode (UART/COM)** | User Directives | [`examples/Unified_Environmental_Demo/main/main.c`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/examples/Unified_Environmental_Demo/main/main.c) | **COMPLETE** |
| **SD Card Power & Logging** | `new-project-outline-low-power-test.md` | `bsp_sdcard.c` | **PENDING** |
| **SNTP -> PCF85063A Auto-Commit** | `ACTION_PLAN.md` | `bsp_rtc.c`, `bsp_time.c` | **PENDING** |
| **ULP RV32IMC Coprocessor** | Hardware Constraint | *Decommissioned* | **DROPPED** |
| **Synthetic Thermal Calibration** | Historical v1.0.0 | *Removed* | **DROPPED** |
| **Assumed 280 µA Current Math** | Historical v1.1.0 | *Removed* | **DROPPED** |
| **ThingsBoard / Cloud MQTTS** | Historical v1.0.0 | *Removed* | **DROPPED** |
