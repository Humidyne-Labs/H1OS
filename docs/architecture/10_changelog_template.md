# Clean-Slate BSP: Change Log Template

All notable changes to the Clean-Slate ESP32-S3 BSP will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

---

## [Unreleased]

### Added
- **11-Document Architecture Suite (`docs/architecture/`):** Complete two-tier documentation system separating public developer manuals from private silicon engineering specifications (`00_documentation_system.md` through `10_changelog_template.md`).
- **ULP-RISC-V Hardware Sentinel (`05_layer3_ulp_sentinel.md`):** Autonomous RTC-domain coprocessor firmware managing battery ADC tripwire (`GPIO 4` / `ADC1_CH3`), hardware button debounce (`GPIO 0 & 18`), and real-time Zero-Hour wake arbitration via `GPIO 5` (`RTC_INT`).
- **Class-E Psychrometric Invariant Engine:** Thermodynamic reconstruction of ambient relative humidity and dew point using the August-Roche-Magnus vapor pressure invariant ($e$) and dynamic sliding ambient floor ($T_{\text{amb\_floor}} = \min(T_{\text{die}})$) with zero artificial polynomial curves.
- **Tri-Node Sensing Architecture:** Cross-referenced substrate thermal gradient tracking using SHTC3 die, internal MCU TSENS, and SSD1681 on-glass thermistor (`SPI Cmd 0x1B`).
- **Unified Single Binary & RTC Wake Stub:** Flow A executes as an ultra-fast `<4ms` RTC Wake Stub (`esp_wake_stub`) on Core 0 at 80 MHz, bypassing the 2nd-stage bootloader, flash cache, and FreeRTOS during periodic sensor logging.
- **Parasitic Leakage Isolation Protocol:** Hardware pad holding of `GPIO 11 (EPD_CS)` and `GPIO 9 (EPD_RST)` HIGH, Class-D audio amp power cut (`GPIO 42 PA_EN = 1`, `GPIO 46 PA_CTRL = 0`), and PCF85063A `CLKOUT` disable (`COF=111`).
- **Keep All Gates Open Policy:** Permanently energizes and latches the 3.3V power rails (`GPIO 17 BAT_CTRL = 1`, `GPIO 6 EPD_3V3_EN = 0`), relying on native sub-microamp IC sleep modes (Total quiescent draw: ~9 µA) to eliminate I2C bus clamping and RTC POR state loss.
- **Deferred Flash Frame Persistence:** Clean 16KB raw SPI flash partition (`epd_frame`) with dirty-tracking (`s_dirty`) that commits framebuffers strictly upon sleep or shutdown.

### Changed
- Re-indexed internal architectural documentation into a canonical 11-file suite numbered `00` through `10`.
- Standardized physical I2C pinout to `GPIO 47 (SDA)` and `GPIO 48 (SCL)` per verified hardware schematics.
- Refactored sensor ingestion into two distinct modules: pure physical I2C acquisition (`sub_sensor`) and pure psychrometric evaluation (`orch_math`).
- Renamed application sleep entry point to `bsp_app_sleep()` to match `bsp_app_start()`.
- Standardized stand-down sequence across both sleep and shutdown: `on_hook` -> `splash` -> `chime` -> `wait_busy` -> `sync_frame` -> `sleep/shutdown`.

### Fixed
- Fixed circular include errors between audio, splash, and base BSP headers by moving common types to Layer 1 `hal_types.h`.
- Fixed callback slot collision where internal display shutdown hooks were overwritten by user lifecycle callbacks.
- Fixed RTC Slow Memory exhaustion by moving the 5,000-byte E-Paper framebuffer out of RTC RAM and into SPI Flash.
- Fixed SPI Flash write spamming during active LVGL screen rendering.
- Fixed ES8311 unpowered bus clamping by maintaining 3.3V rail and using software power-down (Reg `0x0D`).
- Fixed Zero-Hour timer race conditions via ULP hardware arbitration on `GPIO 5` (`RTC_INT`).

### Deprecated
- Deprecated monolithic `bsp_common.c` and `bsp_sleep()` wrappers in favor of Layer 3 Orchestrator and Layer 4 `bsp_app_sleep()`.
- Deprecated synthetic thermal divider calibration code (`bsp_sensor_cal.c/.h`) in favor of Class-E thermodynamic invariant reconstruction.

---

## Versioning Guidelines
- **MAJOR (x.0.0)**: Breaking changes to public Layer 4 API (`bsp.h`, `bsp_app_config_t`).
- **MINOR (0.x.0)**: New peripheral features, additional telemetry metrics, or backward-compatible API additions.
- **PATCH (0.0.x)**: Bug fixes, timing optimizations in sub-execution, or hardware calibration tweaks.
