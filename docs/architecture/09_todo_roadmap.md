# H1OS Development Roadmap & Canonical Construction Phases

This roadmap tracks the development of **H1OS** (Class-E Luxury Environmental Telemetry Instrument Operating System) for the Waveshare ESP32-S3 ePaper 1.54" V2.

Development follows the **Four Canonical Stages of Construction**:
> *"Pants, belt, suspenders, life jacket before hair brushing."*
1. **Stage 1: The Bones** (Architecture, Contracts, & Documentation)
2. **Stage 2: Housekeeping & Scaffolding Purge** (Component Renaming, CMake Stripping, Stub Wiring)
3. **Stage 3: The Muscle** (Peripheral Hardware Drivers & Silicon Verification)
4. **Stage 4: The Vanity** (LVGL 9 UI Polish, Chimes, Screen Layouts, & Benchmarking)

---

## Stage 1: The Bones (Architecture & Documentation)

- [x] **1.1 Establish Two-Tier Documentation System**: Author `docs/architecture/00` through `10` capturing all 4 layers.
- [x] **1.2 Hardware Errata Call to Action**: Author and place `HARDWARE_ERRATA_AND_PCB_REV_GUIDE.md` in repository root for PCB dev visibility.
- [x] **1.3 Master Architectural Consolidation Blueprint**: Create comprehensive blueprint capturing reactive ULP Bouncer, ULP sleep-gating, 30s Flow B session, bootloader power latch, zero-volt cable guard, and minimal SD card scope.
- [x] **1.4 Architectural Audit & Reconciliation**: Reconcile all 11 architecture specifications in `docs/architecture/` with the Master Blueprint:
  - [x] `00_documentation_system.md`: Update taxonomy, errata reference, and system principles.
  - [x] `01_master_architecture.md`: Detail 4-layer structure, missing subsystems (`sub_nvs`, `sub_sdcard`), ULP bouncer, and 30s session.
  - [x] `02_layer1_hal.md`: Document bone stubbing policy, stateless button pin readers, and bootloader latch release rules.
  - [x] `03_layer2_subsystems.md`: Detail `sub_nvs`, minimal `sub_sdcard`, Zero-Volt Cable Guard in `sub_power`, remove bespoke button driver.
  - [x] `04_layer3_orchestrator.md`: Formalize 30s interactive Flow B session, 80MHz DFS droop, ULP sleep-gating, Zero-Hour conflict avoidance, and 7-step stand-down sequence.
  - [x] `05_layer3_ulp_sentinel.md`: Re-specify purely reactive ULP Bouncer (no polling), tap/hold classification, ROM bootloader priming, zero-volt USB check.
  - [x] `06_layer4_api.md`: Rebrand API to `h1os_*`, document LVGL v9 indev keypad, time services (`h1os_time`), and remove obsolete `on_pxe`.
  - [x] `07_flowchart_state_machine.md`: Update Mermaid state and sequence diagrams for reactive ULP, Zero-Hour conflict suppression, and 30s session.
  - [x] `08_lessons_learned_and_rationale.md`: Document Scaffolding Trap, LVGL indev vs bespoke button driver, reactive ULP bouncer, and Zero-Hour math.
  - [x] `09_todo_roadmap.md`: Align roadmap with the 4 canonical construction stages.
  - [x] `10_changelog_template.md`: Format H1OS v2.0.0 clean-slate release notes.

---

## Stage 2: Housekeeping & Scaffolding Purge

- [ ] **2.1 Component & Namespace Rebranding**:
  - [ ] Rename `components/esp32-s3_bsp/` directory to `components/h1os/`.
  - [ ] Rename bootloader hook component from `bsp_boot_hook` to `h1os_boot_hook`.
  - [ ] Update root `CMakeLists.txt` and `components/h1os/CMakeLists.txt` to register component as `h1os`.
  - [ ] Strip demo application CMake to strictly require: `REQUIRES h1os freertos lvgl`.
- [ ] **2.2 Scaffolding & Obsolete Code Purge**:
  - [ ] Delete legacy scaffolding: `bsp_common.c`, `bsp_power.c`, `bsp_button.c`, and obsolete headers.
  - [ ] Migrate `bsp_sdcard.c` to minimal `sub_sdcard.c/.h` (file I/O, format, capacity checking).
  - [ ] Migrate `bsp_time.c` to Layer 4 `h1os_time.c/.h`.
  - [ ] Migrate `bsp_lvgl.cpp` to Layer 4 `h1os_lvgl.c/.h` with `LV_INDEV_TYPE_KEYPAD` binding.
  - [ ] Implement `sub_nvs.c/.h` for non-volatile configuration storage.
- [ ] **2.3 Bone Stubbing & Header Wiring**:
  - [ ] Ensure all Layer 1 (`hal_*`) and Layer 2 (`sub_*`) headers declare clean functional contracts.
  - [ ] Stub drivers with null/placeholder implementations to achieve clean compile-level verification before driver muscle is written.
  - [ ] Update `examples/H1OS/main/main.c` to include `<h1os.h>` and register `h1os_app_config_t`.

---

## Stage 3: The Muscle (Hardware Drivers & Verification)

- [ ] **3.1 Layer 1 HAL Concrete Implementation**:
  - [ ] `hal_io.c`: GPIO latching (`BAT_CTRL` GPIO 17), EPD rail control (`GPIO 6`), stateless button readers (`GPIO 0, 18`), pad hold management.
  - [ ] `hal_i2c.c`: Mutex-protected master bus driver on GPIO 47/48 with bus recovery clock pulsing.
  - [ ] `hal_spi.c`: DMA-backed 20MHz SPI Master bus for SSD1681 display updates and 2MHz half-duplex sensor read.
  - [ ] `hal_flash.c`: Sector-aligned erase/read/write for `epd_frame` partition (16KB) with bounds checking.
- [ ] **3.2 Layer 2 Subsystems Concrete Implementation**:
  - [ ] `sub_display.cpp`: SSD1681 dual-RAM Ping-Pong buffer (0x24/0x26), 159-byte partial LUT, GPIO 8 ISR semaphore, on-glass temperature (0x1B).
  - [ ] `sub_sensor.c`: SHTC3 physical acquisition (`Wake` -> `Read` -> `Sleep`) and ESP32-S3 internal TSENS die temperature.
  - [ ] `sub_rtc.c`: PCF85063A POSIX timekeeping, clock calibration, countdown timer on GPIO 5, remaining duration query.
  - [ ] `sub_power.c`: ADC1_CH3 calibrated battery sampling, LiPo OCV lookup, Zero-Volt Cable Guard logic, deep sleep EXT1 wake config.
  - [ ] `sub_audio.c`: ES8311 22-register clock tree, chime synthesizer, and register 0x0D standby power-down.
  - [ ] `sub_sdcard.c`: Basic SD SPI/MMC initialization, file I/O, format, and capacity checking.
  - [ ] `sub_nvs.c`: NVS open, read/write blob, and commit routines.
- [ ] **3.3 Layer 3 Pipeline & Orchestrator Implementation**:
  - [ ] `orch_state.c`: RTC Slow Memory persistent state (<256 bytes), Tri-Node ring buffer, validity bitmasks.
  - [ ] `orch_math.c`: Integer slope delta gating, Class-E psychrometrics (Vapor pressure $e$, Dew point $T_{\text{dew}}$, reconstructed $RH_{\text{amb}}$), EWMA filter.
  - [ ] `orch_flow.c`: Flow A <10ms sprint, Flow B 30s interactive session with 80MHz DFS power droop, Zero-Hour conflict suppression, and 7-step stand-down.
  - [ ] `orch_display_sync.c`: Dirty-frame tracking, deferred SPI flash commit on sleep and shutdown.
- [ ] **3.4 Layer 3 ULP-RISC-V Coprocessor Firmware**:
  - [ ] Implement event-driven reactive ULP Bouncer in RTC domain.
  - [ ] GPIO 5 PCF85063A alarm wake handler.
  - [ ] GPIO 0/18 button tap/hold classifier ($>2.5\text{s}$ bootloader priming / power cut).
  - [ ] GPIO 4 ADC battery tripwire with zero-volt USB bypass.

---

## Stage 4: The Vanity (LVGL 9 UI Polish & Benchmarking)

- [ ] **4.1 LVGL 9 UI Integration**:
  - [ ] Keypad indev binding: BOOT button toggles Screen 1 (Telemetry) $\leftrightarrow$ Screen 2 (Health).
  - [ ] 1-bit packed binary fonts (`MONTSERRAT_14_1BPP`, `MONTSERRAT_20_1BPP`).
  - [ ] LVGL display buffer flushing callback to `sub_display`.
- [ ] **4.2 Class-E Hardware Benchmarking**:
  - [ ] **Sub-Execution Timing**: Measure Flow A on-time with oscilloscope on status pin (Target: < 10 ms).
  - [ ] **Deep Sleep Quiescent Current**: Verify standby current with power profiler (Target: < 15 µA).
  - [ ] **Partial Refresh Latency**: Benchmark partial update speed on electrophoretic panel (Target: ~300 ms).
  - [ ] **Zero-Hour Conflict Stress Test**: Verify no rapid double-wake occurs when sub-execution aligns with external RTC alarm.
  - [ ] **Flash Endurance Audit**: Verify SPI flash writes occur strictly on sleep and shutdown.
  - [ ] **Tri-Node Thermal Benchmark**: Compare SHTC3 die, MCU TSENS, and SSD1681 glass against reference psychrometer.
