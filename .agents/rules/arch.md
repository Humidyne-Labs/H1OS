# Architecture and Codebase Rules

This rule enforces core development invariants across the **H1OS** (`v2.4.5-dev`) firmware and ESP32-S3 Board Support Package.

## 1. Four-Layer Unidirectional Boundary Hierarchy

1. **Layer 1: HAL (`hal_*`)**
   - Stateless primitives directly manipulating hardware registers and ESP-IDF peripheral drivers (`hal_io`, `hal_i2c`, `hal_spi`, `hal_adc`, `hal_i2s`, `hal_types`).
   - ZERO application state, ZERO psychrometric math, and ZERO power-management decisions.

2. **Layer 2: Peripheral Subsystems (`sub_*`)**
   - Encapsulated drivers managing physical peripherals (`sub_display`, `sub_rtc`, `sub_audio`, `sub_power`, `sub_sdcard`, `sub_nvs`).
   - May depend on Layer 1 (`hal_*`), NEVER on Layer 3 or Layer 4 (`orch_*` or `h1os_*`). Zero inter-subsystem cross-talk.
   - *Note:* `sub_sensor` is retired; SHTC3 and MCU die TSENS acquisition execute exclusively in Layer 3 `orch_wake_stub.c` to enforce zero-heat isolation.

3. **Layer 3: Orchestrator & ULP (`orch_*`)**
   - Flow arbiter (`orch_flow`) managing Flow A (`~18.5 ms` headless sensor sample bursts in `orch_wake_stub.c`), Flow B (parallel dual-core application & UI wakes), psychrometric invariant math (`orch_math`), persistent `648-byte` state in RTC Slow Memory (`orch_state`), and the Pure Event Mode ULP-RISC-V monitor (`ulp/main.c`).

4. **Layer 4: Application Lifecycle (`h1os_*`)**
   - Declarative application API & dual-core sleep barrier (`h1os.h`, `h1os_lifecycle.c`), Core 1 LVGL v9 engine & cross-core actor queue (`h1os_lvgl.h`, `h1os_ui_post`), and POSIX time synchronization (`h1os_time.h`).

## 2. Hardware & Concurrency Invariants

- **Unidirectional Hierarchy:** Upper layers call lower layers; lower layers NEVER call up or cross-talk.
- **Dual-Core Parallel Execution (`MANDATE-04`):** Core 0 runs `on_sync()` (wireless telemetry, SD/audio I/O) in parallel with Core 1's LVGL v9 layout and SSD1681 display refresh (`h1os_lvgl`, priority `5`). Sleep entry is gated by a static FreeRTOS `EventGroup` barrier (`BARRIER_SYNC_DONE | BARRIER_DISPLAY_DONE`).
- **Power Latching & Fatal Error Recovery (`MANDATE-06`):** `BAT_CTRL` (`GPIO 17`) is asserted in the 2nd-stage bootloader hook (`h1os_boot_hook`) within 25 ms and retained in deep sleep via RTC pad hold. Any fatal cold-boot initialization failure invokes `on_error()` and releases `GPIO 17` (`hal_io_release_power_latch()`) on battery power so a faulted board never drains the LiPo cell.
- **Zero-Heat Sensing:** Never poll the SHTC3 during active CPU operation. SHTC3 sampling occurs strictly in headless Flow A sample bursts (`orch_wake_stub.c`) to prevent PCB self-heating bias.
- **Documentation:** Public documentation resides in root or `docs/`, with engineering specs under `docs/architecture/` and `docs/drivers/`.
