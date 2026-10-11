# Clean-Slate BSP: Development Roadmap & TODO Tracking

Use this template to track milestone progress, outstanding hardware validation steps, and layer-by-layer implementation phases.

---

## 1. Development Phases & Milestones

### Phase 0: Architecture & Unified Binary Setup
- [x] **0.1 Single Unified Binary Configuration**: Target a single firmware image with early branching to avoid 2nd-stage bootloader overhead.
- [x] **0.2 RTC Wake Stub Implementation**: Implement `esp_wake_stub` in IRAM/RTC SRAM to bypass flash cache and FreeRTOS during 60s sensor wakes (<5ms execution).
- [x] **0.3 Hardware Pinout Freeze**: Standardize pinout to physical Waveshare v2 hardware: GPIO 47/48 (I2C), GPIO 8-13 (EPD SPI), GPIO 17 (BAT_CTRL), GPIO 18 (BAT_KEY).
- [x] **0.4 ULP-RISC-V Real-Time Sentinel**: Implement background coprocessor firmware for autonomous battery tripwire (`ADC1_CH3`), button debounce (`GPIO 0/18`), and Zero-Hour conflict arbitration via `GPIO 5` (`RTC_INT`).

### Phase 1: Layer 1 HAL & Bus Infrastructure
- [x] **1.1 `hal_types.h`**: Consolidate all GPIO pin numbers, hardware constants, error codes, and coordinate types.
- [x] **1.2 `hal_io.c/.h`**: Implement early power latch locking (`BAT_CTRL` GPIO 17), EPD 3.3V rail control, and RTC pad hold routines.
- [x] **1.3 `hal_i2c.c/.h`**: Implement thread-safe mutex-protected I2C Master bus driver on GPIO 47/48 with bus recovery clock pulsing.
- [x] **1.4 `hal_spi.c/.h`**: Configure DMA-backed 20MHz SPI Master bus for SSD1681 display updates and 2MHz half-duplex sensor read.
- [x] **1.5 `hal_flash.c/.h`**: Implement sector-aligned erase/read/write for the `epd_frame` partition (16KB) with bounds checking.
- [x] **1.6 Phase 1 Unit Test**: Validate raw bus communication on target hardware (Clean build & link under ESP-IDF v6.1).

---

### Phase 2: Layer 2 Hardware Subsystem Managers
- [x] **2.1 `sub_display.cpp/.h`**:
  - [x] Implement SSD1681 dual-RAM Ping-Pong buffer (0x24/0x26).
  - [x] Integrate factory 159-byte partial waveform LUT.
  - [x] Replace busy polling loop with FreeRTOS binary semaphore signaled by GPIO 8 ISR.
  - [x] Implement on-glass temperature sensor readout (Command 0x1B).
- [x] **2.2 `sub_sensor.c/.h`**:
  - [x] Implement dedicated physical SHTC3 acquisition (`Wake` -> `Read` -> `Sleep`).
  - [x] Implement ESP32-S3 internal TSENS analog die temperature read.
- [x] **2.3 `sub_rtc.c/.h`**:
  - [x] Implement PCF85063A POSIX timekeeping and clock calibration.
  - [x] Implement hardware countdown timer configuration and interrupt clearing (`GPIO 5`).
  - [x] Implement remaining countdown timer query for zero-hour conflict avoidance.
- [x] **2.4 `sub_power.c/.h`**:
  - [x] Implement calibrated battery voltage sampling (ADC1_CH3) with 12 dB attenuation & LiPo OCV table.
  - [x] Implement EXT1 deep sleep wake configuration and hardware sleep entry.
  - [x] Implement physical power cut via `BAT_CTRL` de-assertion.
- [x] **2.5 `sub_audio.c/.h`**:
  - [x] Implement hardware synthesizer chime generation and standby mute line.

---

### Phase 3: Layer 3 System Pipeline & Orchestrator
- [x] **3.1 `orch_state.h/.c`**:
  - [x] Implement persistent state structure in RTC Slow Memory (<512 bytes).
  - [x] Define 32-slot Tri-Node ring buffer (`orch_tri_node_sample_t`), sliding floor minimums, and validity bitmasks.
- [x] **3.2 `orch_math.c/.h`**:
  - [x] Implement integer slope delta gating ($0.05^\circ\text{C} - 0.20^\circ\text{C}$ plateau gate).
  - [x] Implement Class-E thermodynamic invariant equations: Vapor Pressure ($e$), Dew Point ($T_{\text{dew}}$), and reconstructed Ambient RH ($RH_{\text{amb}}$).
  - [x] Implement continuous recursive EWMA filter ($\alpha = 0.25\dots 0.35$).
- [x] **3.3 `orch_flow.c/.h`**:
  - [x] Implement **Flow A** zero-heat acquisition pipeline (Xtensa <10ms sprint and ULP-RISC-V sentinel).
  - [x] Implement Thermal Lockout MUX gatekeeper ($\tau_{\text{lockout}} \ge 0.5 \times T_{\text{sleep}}$).
  - [x] Implement zero-hour conflict guard math ($\Delta t_{\text{remaining}} \le T_{\text{sub}}$).
  - [x] Implement **Flow B** (main application boot & wake) state restoration.
- [x] **3.4 `orch_display_sync.c/.h`**:
  - [x] Implement dirty-frame tracking to eliminate flash write spam during active UI operation.
  - [x] Implement single flash commit on sleep and shutdown.

---

### Phase 4: Layer 4 User Application Lifecycle API
- [x] **4.1 `bsp.h` Public Interface**:
  - [x] Define declarative `bsp_app_config_t` with explicit lifecycle hooks.
  - [x] Implement `bsp_app_start()` lifecycle dispatcher.
  - [x] Implement `bsp_app_sleep()` stand-down sequence.
  - [x] Implement `bsp_app_shutdown()` orderly power cut.
  - [x] Implement `bsp_app_get_telemetry()` unified data getter (transparently gated by Thermal Lockout MUX).
- [x] **4.2 LVGL Integration**:
  - [x] Package dedicated 1-bit fonts (`MONTSERRAT_14_1BPP`, `MONTSERRAT_20_1BPP`).
  - [x] Set up clean LVGL display driver flush callback feeding `sub_display`.
- [x] **4.3 Legacy Code Cleansing & Demo Revamp**:
  - [x] Purge 16 obsolete legacy files from `components/esp32-s3_bsp/` (`bsp_sensors.*`, `bsp_equ_math.*`, `bsp_env_telemetry.*`, `bsp_rtc.*`, `bsp_rtc_mem.*`, `bsp_i2c.*`, `bsp_display.*`, `bsp_audio.*`, `pinout.h`).
  - [x] Rewire core drivers (`bsp_common.c`, `bsp_power.c`, `bsp_button.c`, `bsp_sdcard.c`, `bsp_lvgl.cpp`, `bsp_time.c`) to clean 4-layer architecture.
  - [x] Modernize `examples/OSDemo/main/main.c` to use `bsp_app_get_telemetry()`.
  - [x] Verify complete clean build with Ninja & ESP-IDF v6.1 (`dev` preset).
- [x] **4.4 Low-Level Peripheral & Driver Verification (Hardware Truth Audit)**:
  - [x] Author comprehensive `docs/perf_and_drivers/` documentation directory covering all 7 physical subsystems.
  - [x] Audit & fix PCF85063A countdown timer prescaler bit shifts (`TCF` in bits `[4:3]`), remove bogus Control_2 `TIE` bit, and set 12.5pF crystal load capacitance in `Control_1`.
  - [x] Audit & fix SSD1681 159-byte partial LUT multi-register partitioning across `0x32`, `0x3F`, `0x03`, `0x04`, and `0x2C`.
  - [x] Implement differential Ping-Pong partial refresh sequence (`0x37`, `0x3C=0x80`, `0x22=0xCF`, `0x20`).
  - [x] Implement continuous CS hold and 2MHz half-duplex 3-wire read for on-glass thermistor (`0x1B`).
  - [x] Port complete 22-register ES8311 clock tree and 15-register zero-heat deep standby sequence (<1.0 µA).
  - [x] Align 13-point LiPo OCV lookup table with calibrated hardware reference.
  - [x] Enforce RTC peripheral power domain retention (`ESP_PD_DOMAIN_RTC_PERIPH`) in deep sleep to lock `BAT_CTRL` latch.
  - [x] Verify 100% clean compilation under ESP-IDF v6.1 with Ninja.

---

### Phase 5: Hardware Benchmarking & Class-E Validation
- [ ] **5.1 Sub-Execution Timing**: Measure Flow A on-time using oscilloscope on status pin (Target: < 10 ms).
- [ ] **5.2 Deep Sleep Quiescent Current**: Verify average standby current with Nordic Power Profiler (Target: < 15 µA).
- [ ] **5.3 Partial Refresh Latency**: Benchmark partial update speed on electrophoretic panel (Target: ~300 ms).
- [ ] **5.4 Zero-Hour Stress Test**: Verify no rapid double-wake occurs when sub-execution aligns with external RTC alarm.
- [ ] **5.5 Flash Endurance Audit**: Verify SPI flash writes occur strictly on sleep and shutdown.
- [ ] **5.6 Tri-Node Thermal Benchmark**: Run 3-hour test comparing SHTC3 die, MCU TSENS, and SSD1681 glass against an external NIST-traceable reference psychrometer.
- [ ] **5.7 Thermal Lockout Verification**: Verify that active LVGL display flushes do not pollute the ambient telemetry ring buffer.
