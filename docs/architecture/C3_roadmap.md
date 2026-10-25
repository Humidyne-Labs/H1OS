# H1OS Development Roadmap & Verification Milestones

This roadmap tracks the development of **H1OS** (E-Class Environmental Telemetry Instrument Operating System) for the Waveshare ESP32-S3 ePaper 1.54" V2.

Development follows the **Four Canonical Stages of Construction**:
> *"Pants, belt, suspenders, life jacket before hair brushing."*
1. **Stage 1: Core Architecture & Interface Contracts** (Architecture, Contracts, & Documentation)
2. **Stage 2: Legacy Deprecation & Cleanup** (Component Renaming, CMake Stripping, Stub Wiring)
3. **Stage 3: Subsystem Integration & Drivers** (Peripheral Hardware Drivers & Silicon Verification)
4. **Stage 4: Application & Presentation Layer** (LVGL 9 UI Polish, Chimes, Screen Layouts, & Benchmarking)

---

## 1. Stage 1: Core Architecture & Interface Contracts (Architecture & Documentation)

- [x] **1.1 Establish Two-Tier Documentation System**: Author architecture specifications capturing all 4 layers.
- [x] **1.2 Hardware Errata Call to Action**: Author and place `ERRATA.md` in repository root for PCB dev visibility.
- [x] **1.3 Master Architectural Consolidation Blueprint**: Create comprehensive blueprint capturing reactive ULP Monitor, ULP sleep-gating, interactive Flow B session, bootloader power latch, zero-volt cable guard, and minimal SD card scope.
- [x] **1.4 Architectural Audit & Reconciliation**: Reconcile all architecture specifications in `docs/architecture/` with the Master Blueprint:
   - [x] `A0_system_governance.md`: Update taxonomy, errata reference, and system principles.
  - [x] `A1_master_blueprint.md`: Detail 4-layer structure, subsystems (`sub_nvs`, `sub_sdcard`), ULP monitor, and interactive session.
  - [x] `A2_hal.md`: Document HAL interface contract policy, stateless button pin readers, and bootloader latch release rules.
  - [x] `A4_subsystems.md`: Detail `sub_nvs`, minimal `sub_sdcard`, Zero-Volt Cable Guard in `sub_power`, remove bespoke button driver.
  - [x] `A5_orchestrator.md`: Formalize interactive Flow B session, 80MHz DFS droop, ULP sleep-gating, Zero-Hour conflict avoidance, and 8-step sleep sequence.
  - [x] `A6_ulp_coprocessor.md`: Re-specify purely reactive ULP Monitor (no polling), tap/hold classification, ROM bootloader priming, zero-volt USB check.
  - [x] `B1_api_and_services.md`: Rebrand API to `h1os_*`, document LVGL v9 indev keypad, time services (`h1os_time`).
  - [x] `B2_state_machine.md`: Update Mermaid state and sequence diagrams for reactive ULP, Zero-Hour conflict suppression, and interactive session.
  - [x] `C2_lessons_learned.md`: Document Scaffolding Trap, LVGL indev vs bespoke button driver, reactive ULP monitor, and Zero-Hour math.
  - [x] `C3_roadmap.md`: Align roadmap with the 4 canonical construction stages.
  - [x] `C4_changelog_policy.md`: Format H1OS clean-slate release notes and link to root `CHANGELOG.md`.

---

## 2. Stage 2: Housekeeping & Scaffolding Purge

- [x] **2.1 Component & Namespace Rebranding**:
  - [x] Standardize on `components/h1os` for core system framework.
  - [x] Standardize bootloader hook component on `h1os_boot_hook`.
  - [x] Update root `CMakeLists.txt` and `components/h1os/CMakeLists.txt` to register component as `h1os`.
  - [x] Strip demo application CMake to strictly require: `REQUIRES h1os freertos lvgl`.
- [x] **2.2 Scaffolding & Obsolete Code Purge**:
  - [x] Delete legacy scaffolding: `bsp_common.c`, `bsp_power.c`, `bsp_button.c`, and obsolete headers.
  - [x] Migrate `bsp_sdcard.c` to minimal `sub_sdcard.c/.h` (file I/O, format, capacity checking).
  - [x] Migrate `bsp_time.c` to Layer 4 `h1os_time.c/.h`.
  - [x] Migrate `bsp_lvgl.cpp` to Layer 4 `h1os_lvgl.c/.h` with `LV_INDEV_TYPE_KEYPAD` binding.
  - [x] Implement `sub_nvs.c/.h` for non-volatile configuration storage.
- [x] **2.3 Interface Header Definition & Contract Wiring**:
  - [x] Ensure all Layer 1 (`hal_*`) and Layer 2 (`sub_*`) headers declare clean functional contracts.
  - [x] Wire drivers with clean implementations to achieve clean compile-level verification.
  - [x] Update `examples/H1OS/main/main.c` to include `<h1os.h>` and register `h1os_app_config_t`.

---

## 3. Stage 3: Subsystem Integration & Drivers (Hardware Drivers & Verification)

- [x] **3.1 Layer 1 HAL Concrete Implementation**:
  - [x] `hal_io.c`: GPIO latching (`BAT_CTRL` GPIO 17), EPD rail control (`GPIO 6`), stateless button readers (`GPIO 0, 18`), pad hold management.
  - [x] `hal_i2c.c`: Mutex-protected master bus driver on GPIO 47/48 with bus recovery clock pulsing.
  - [x] `hal_spi.c`: DMA-backed 20MHz SPI Master bus for SSD1681 display updates and 2MHz half-duplex sensor read.
  - [x] `hal_flash.c`: Sector-aligned erase/read/write for `epd_frame` partition (16KB) with bounds checking.
- [x] **3.2 Layer 2 Subsystems Concrete Implementation**:
  - [x] `sub_sensor.c`: SHTC3 physical acquisition (`Wake` -> `Read` -> `Sleep`) and ESP32-S3 internal TSENS die temperature.
  - [x] `sub_rtc.c`: PCF85063A POSIX timekeeping, clock calibration, countdown timer on GPIO 5, remaining duration query.
  - [x] `sub_audio.c`: ES8311 22-register clock tree, CSM state polling, background FreeRTOS worker task (`h1os_audio_worker`), soft-mute ramp teardown.
  - [x] `sub_display.cpp`: SSD1681 dual-RAM Ping-Pong buffer (0x24/0x26), 159-byte partial LUT, GPIO 8 ISR semaphore, on-glass temperature (0x1B).
  - [x] `sub_power.c`: ADC1_CH3 calibrated battery sampling, LiPo OCV lookup, Zero-Volt Cable Guard logic, deep sleep EXT1 wake config.
  - [x] `sub_sdcard.c`: Basic SD SPI/MMC initialization, file I/O, format, and capacity checking.
  - [x] `sub_nvs.c`: NVS open, read/write blob, and commit routines.
- [x] **3.3 Layer 3 Pipeline & Orchestrator Implementation**:
  - [x] `orch_state.c`: RTC Slow Memory persistent state (<256 bytes), Tri-Node ring buffer, validity bitmasks.
  - [x] `orch_math.c`: Integer slope delta gating, E-Class psychrometrics (Vapor pressure $e$, Dew point $T_{\text{dew}}$, reconstructed $RH_{\text{amb}}$), EWMA filter.
  - [x] `orch_flow.c`: Flow A sample burst, Flow B interactive session with 80MHz DFS power droop, Zero-Hour conflict suppression, and sleep transition.
  - [x] `orch_display_sync.c`: Dirty-frame tracking, deferred SPI flash commit on sleep and shutdown.
- [x] **3.4 Layer 3 ULP-RISC-V Coprocessor Firmware**:
  - [x] Implement event-driven reactive ULP Monitor in RTC domain.
  - [x] GPIO 5 PCF85063A alarm wake handler.
  - [x] GPIO 0/18 button tap/hold classifier ($>2.5\text{s}$ bootloader priming / power cut).
  - [x] GPIO 4 ADC battery threshold with zero-volt USB bypass.

---

## 4. Stage 4: Application & Presentation Layer (LVGL 9 UI Polish & Benchmarking)

- [x] **4.1 LVGL 9 UI Integration**:
  - [x] Keypad indev binding: BOOT button toggles Screen 1 (Telemetry) $\leftrightarrow$ Screen 2 (Health).
  - [x] 1-bit packed binary fonts (`Montserrat-Bold` across 14, 16, 18, 20, 24, 32 pt with strong autohinting).
  - [x] Non-blocking display buffer flushing callback to `sub_display`.
- [x] **4.2 E-Class Hardware Benchmarking Architecture**:
  - [x] **Sub-Execution Timing**: Flow A on-time measurement hooks instrumented in `orch_wake_stub.c`.
  - [x] **Deep Sleep Quiescent Current**: Low-leakage pin invariants audited via RTC pad holds.
  - [x] **Partial Refresh Latency**: Fast partial update speed on electrophoretic panel supported in `sub_display.cpp`.
  - [x] **Zero-Hour Conflict Stress Test**: Race condition elimination verified in `orch_flow.c`.
  - [x] **Flash Endurance Audit**: SPI flash writes restricted strictly to sleep and shutdown in `orch_display_sync.c`.
  - [x] **Tri-Node Thermal Benchmark**: Cavity compensation architecture modeled in `orch_math.c`.
  - [x] **Benchmarking Protocol & Guide**: Documented in [`docs/architecture/C1_benchmarks_and_verification.md`](C1_benchmarks_and_verification.md).

---

## 5. Ongoing & Future Verification Matrix

| Subsystem / Feature | Target Verification | Status |
|---|---|---|
| **E-Paper Residual Charge Mitigation** | Auto full refresh after 6 partials to protect microcapsules | VERIFIED |
| **Storage Panel Whitening** | Drive panel full white before shutdown | VERIFIED |
| **MicroSD Rail Optimization** | Audit quiescent draw on battery vs unmounted | VERIFIED |
| **Asynchronous Audio Worker** | Decoupled non-blocking chimes via FreeRTOS queue | VERIFIED |
| **Dynamic Sleep Intervals** | User-configurable Flow A & B periods | VERIFIED |
