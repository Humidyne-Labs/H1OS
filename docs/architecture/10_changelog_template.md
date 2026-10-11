# H1OS Change Log

All notable changes to the H1OS Operating System for the Waveshare ESP32-S3 ePaper 1.54" V2 will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

---

## [2.0.0-dev] - Clean-Slate Architecture Revision

### Added
- **11-Document Canonical Architecture Suite (`docs/architecture/`):** Complete two-tier documentation system separating public developer manuals from private silicon engineering specifications (`00_documentation_system.md` through `10_changelog_template.md`).
- **Four Canonical Construction Stages:** Established strict development order: Stage 1 (The Bones) $\rightarrow$ Stage 2 (Housekeeping & Purge) $\rightarrow$ Stage 3 (The Muscle) $\rightarrow$ Stage 4 (The Vanity).
- **Reactive ULP-RISC-V Bouncer (`05_layer3_ulp_sentinel.md`):** Purely event-driven coprocessor sentinel operating strictly while Xtensa is in deep sleep. Wakes on periodic timer or external interrupts on `GPIO 5` (PCF85063A Alarm), `GPIO 0/18` (Buttons), and `GPIO 4` (Battery ADC). Classifies short tap vs $>2.5\text{s}$ hold for ROM bootloader jump and power cut.
- **Zero-Hour Conflict Arbitration:** Real-time suppression of sub-execution timer when external RTC alarm is imminent, eliminating rapid back-to-back wakes.
- **Application Gating Protocol:** Hardware ownership is mutually exclusive: ULP is dormant when Flow B interactive session is active.
- **Interactive Flow B Session (30s):** Active user session with 80 MHz DFS power droop between clicks, resetting 30s inactivity timer on input before coordinating a 7-step stand-down to deep sleep.
- **Zero-Volt Cable Guard:** Intelligent battery ADC evaluation allowing continuous operation when running via USB cable ($V_{\text{bat}} \approx 0\text{mV}$) with `BAT_CTRL` asserted.
- **Bootloader Power Latch Hand-off:** Early power latching (`BAT_CTRL` GPIO 17) initiated in `h1os_boot_hook` (2nd-stage bootloader), with HAL and subsystem layers exposing only safe release wrappers.
- **Minimal SD Card Manager (`sub_sdcard`):** Streamlined subsystem limited to file I/O, format, and capacity checking.
- **Unified Public API (`h1os.h`):** Declarative configuration (`h1os_app_config_t`), lifecycle hooks (`on_wake`, `on_sleep`, `on_power_off`), and telemetry getters.
- **Public Errata Call to Action (`HARDWARE_ERRATA_AND_PCB_REV_GUIDE.md`):** Direct hardware documentation placed at repository root for PCB engineering visibility.

### Changed
- Rebranded entire codebase, namespace, types, and macros from `bsp_*` to `h1os_*`.
- Shifted button management during active wake from bespoke `sub_button` driver to native LVGL v9 keypad indev (`LV_INDEV_TYPE_KEYPAD`) querying stateless HAL pin readers.
- Standardized physical I2C pinout to `GPIO 47 (SDA)` and `GPIO 48 (SCL)` per verified hardware schematics.
- Refactored sensor ingestion into pure physical I2C acquisition (`sub_sensor`) and pure psychrometric evaluation (`orch_math`).
- Standardized 7-step hardware stand-down sequence across both sleep and shutdown: `on_hook` $\rightarrow$ `splash` $\rightarrow$ `chime` $\rightarrow$ `wait_busy` $\rightarrow$ `sync_frame` $\rightarrow$ `sleep/shutdown`.
- Deferred SPI Flash framebuffer writes to sleep and shutdown transitions only, eliminating flash wear during active rendering.

### Fixed
- Fixed circular include errors between audio, splash, and base headers by consolidating base types into Layer 1 `hal_types.h`.
- Fixed callback slot collision where internal display shutdown hooks were overwritten by user lifecycle callbacks.
- Fixed RTC Slow Memory exhaustion by moving the 5,000-byte E-Paper framebuffer out of RTC RAM and into dedicated SPI Flash (`epd_frame`, 16KB).
- Fixed ES8311 unpowered bus clamping by maintaining 3.3V rail and using software register `0x0D` power-down (<1.0 µA).
- Fixed Zero-Hour timer race conditions via ULP hardware arbitration on `GPIO 5` (`RTC_INT`).

### Deprecated / Removed
- Deprecated legacy scaffolding files: `bsp_common.c`, `bsp_power.c`, `bsp_button.c`, and monolithic `bsp_sleep()` wrappers.
- Removed obsolete `on_pxe` lifecycle hook in favor of standard Flow B interactive wake.
- Deprecated synthetic thermal divider calibration code (`bsp_sensor_cal.c/.h`) in favor of Class-E thermodynamic invariant reconstruction.

---

## Versioning Guidelines
- **MAJOR (x.0.0)**: Breaking changes to public Layer 4 API (`h1os.h`, `h1os_app_config_t`).
- **MINOR (0.x.0)**: New peripheral features, additional telemetry metrics, or backward-compatible API additions.
- **PATCH (0.0.x)**: Bug fixes, timing optimizations in sub-execution, or hardware calibration tweaks.
