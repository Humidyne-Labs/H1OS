# Clean-Slate BSP: Development Roadmap & TODO Tracking

Use this template to track milestone progress, outstanding hardware validation steps, and layer-by-layer implementation phases.

---

## 1. Development Phases & Milestones

### Phase 0: Architecture & Unified Binary Setup
- [ ] **0.1 Single Unified Binary Configuration**: Target a single firmware image with early branching to avoid 2nd-stage bootloader overhead.
- [ ] **0.2 RTC Wake Stub Implementation**: Implement `esp_wake_stub` in IRAM/RTC SRAM to bypass flash cache and FreeRTOS during 60s sensor wakes (<5ms execution).
- [ ] **0.3 Hardware Pinout Freeze**: Standardize pinout to physical Waveshare v2 hardware: GPIO 47/48 (I2C), GPIO 8-13 (EPD SPI), GPIO 17 (BAT_CTRL), GPIO 18 (BAT_KEY).
- [ ] **0.4 ULP-RISC-V Real-Time Sentinel**: Implement background coprocessor firmware for autonomous battery tripwire (`ADC1_CH3`), button debounce (`GPIO 0/18`), and Zero-Hour conflict arbitration via `GPIO 5` (`RTC_INT`).

### Phase 1: Layer 1 HAL & Bus Infrastructure
- [ ] **1.1 `hal_types.h`**: Consolidate all GPIO pin numbers, hardware constants, error codes, and coordinate types.
- [ ] **1.2 `hal_io.c/.h`**: Implement early power latch locking (`BAT_CTRL` GPIO 17), EPD 3.3V rail control, and RTC pad hold routines.
- [ ] **1.3 `hal_i2c.c/.h`**: Implement thread-safe mutex-protected I2C Master bus driver on GPIO 47/48 with bus recovery clock pulsing.
- [ ] **1.4 `hal_spi.c/.h`**: Configure DMA-backed 20MHz SPI Master bus for SSD1681 display updates and 2MHz half-duplex sensor read.
- [ ] **1.5 `hal_flash.c/.h`**: Implement sector-aligned erase/read/write for the `epd_frame` partition (16KB) with bounds checking.
- [ ] **1.6 Phase 1 Unit Test**: Validate raw bus communication on target hardware.

---

### Phase 2: Layer 2 Hardware Subsystem Managers
- [ ] **2.1 `sub_display.cpp/.h`**:
  - [ ] Implement SSD1681 dual-RAM Ping-Pong buffer (0x24/0x26).
  - [ ] Integrate factory 159-byte partial waveform LUT.
  - [ ] Replace busy polling loop with FreeRTOS binary semaphore signaled by GPIO 7 ISR.
  - [ ] Implement on-glass temperature sensor readout (Command 0x1B).
- [ ] **2.2 `sub_sensor.c/.h`**:
  - [ ] Implement dedicated physical SHTC3 acquisition (`Wake` -> `Read` -> `Sleep`).
  - [ ] Implement ESP32-S3 internal TSENS analog die temperature read.
- [ ] **2.3 `sub_rtc.c/.h`**:
  - [ ] Implement PCF85063A POSIX timekeeping and clock calibration.
  - [ ] Implement hardware countdown timer configuration and interrupt clearing (`GPIO 5`).
  - [ ] Implement remaining countdown timer query for zero-hour conflict avoidance.
- [ ] **2.4 `sub_power.c/.h`**:
  - [ ] Implement calibrated battery voltage sampling (ADC1_CH3) with LiPo OCV lookup table.
  - [ ] Implement EXT1 deep sleep wake configuration and hardware sleep entry.
  - [ ] Implement physical power cut via `BAT_CTRL` de-assertion.
- [ ] **2.5 `sub_audio.c/.h`**:
  - [ ] Implement hardware synthesizer chime generation and standby mute line.

---

### Phase 3: Layer 3 System Pipeline & Orchestrator
- [ ] **3.1 `orch_state.h/.c`**:
  - [ ] Implement persistent state structure in RTC Slow Memory (<512 bytes).
  - [ ] Define 32-slot Tri-Node ring buffer (`orch_tri_node_sample_t`), sliding floor minimums, and validity bitmasks.
- [ ] **3.2 `orch_math.c/.h`**:
  - [ ] Implement integer slope delta gating ($0.05^\circ\text{C} - 0.20^\circ\text{C}$ plateau gate).
  - [ ] Implement Class-E thermodynamic invariant equations: Vapor Pressure ($e$), Dew Point ($T_{\text{dew}}$), and reconstructed Ambient RH ($RH_{\text{amb}}$).
  - [ ] Implement continuous recursive EWMA filter ($\alpha = 0.25\dots 0.35$).
- [ ] **3.3 `orch_flow.c/.h`**:
  - [ ] Implement **Flow A** zero-heat acquisition pipeline (Xtensa <10ms sprint or ULP-RISC-V @ 30µA).
  - [ ] Implement Thermal Lockout MUX gatekeeper ($\tau_{\text{lockout}} \ge 0.5 \times T_{\text{sleep}}$).
  - [ ] Implement zero-hour conflict guard math ($\Delta t_{\text{remaining}} \le T_{\text{sub}}$).
  - [ ] Implement **Flow B** (main application boot & wake) state restoration.
- [ ] **3.4 `orch_display_sync.c/.h`**:
  - [ ] Implement dirty-frame tracking to eliminate flash write spam during active UI operation.
  - [ ] Implement single flash commit on sleep and shutdown.

---

### Phase 4: Layer 4 User Application Lifecycle API
- [ ] **4.1 `bsp.h` Public Interface**:
  - [ ] Define declarative `bsp_app_config_t` with explicit lifecycle hooks.
  - [ ] Implement `bsp_app_start()` lifecycle dispatcher.
  - [ ] Implement `bsp_app_sleep()` stand-down sequence.
  - [ ] Implement `bsp_app_shutdown()` orderly power cut.
  - [ ] Implement `bsp_app_get_telemetry()` unified data getter (transparently gated by Thermal Lockout MUX).
- [ ] **4.2 LVGL Integration**:
  - [ ] Package dedicated 1-bit fonts (`MONTSERRAT_14_1BPP`, `MONTSERRAT_20_1BPP`).
  - [ ] Set up clean LVGL display driver flush callback feeding `sub_display`.

---

### Phase 5: Hardware Benchmarking & Class-E Validation
- [ ] **5.1 Sub-Execution Timing**: Measure Flow A on-time using oscilloscope on status pin (Target: < 10 ms).
- [ ] **5.2 Deep Sleep Quiescent Current**: Verify average standby current with Nordic Power Profiler (Target: < 15 µA).
- [ ] **5.3 Partial Refresh Latency**: Benchmark partial update speed on electrophoretic panel (Target: ~300 ms).
- [ ] **5.4 Zero-Hour Stress Test**: Verify no rapid double-wake occurs when sub-execution aligns with external RTC alarm.
- [ ] **5.5 Flash Endurance Audit**: Verify SPI flash writes occur strictly on sleep and shutdown.
- [ ] **5.6 Tri-Node Thermal Benchmark**: Run 3-hour test comparing SHTC3 die, MCU TSENS, and SSD1681 glass against an external NIST-traceable reference psychrometer.
- [ ] **5.7 Thermal Lockout Verification**: Verify that active LVGL display flushes do not pollute the ambient telemetry ring buffer.
