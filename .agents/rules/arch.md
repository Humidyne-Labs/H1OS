# Architecture and Codebase Rules

This rule enforces core development invariants across the **H1OS** firmware and ESP32-S3 Board Support Package.

## 1. Four-Layer Unidirectional Boundary Hierarchy

1. **Layer 1: HAL (`hal_*`)**
   - Stateless primitives directly manipulating hardware registers and ESP-IDF peripheral drivers.
   - ZERO application state, ZERO psychrometric math, and ZERO power-management decisions.

2. **Layer 2: Peripheral Subsystems (`sub_*`)**
   - Encapsulated drivers managing physical peripherals (`sub_display`, `sub_sensor`, `sub_rtc`, `sub_audio`, `sub_power`, `sub_sdcard`, `sub_nvs`).
   - May depend on Layer 1 (`hal_*`), NEVER on Layer 3 or Layer 4. Zero inter-subsystem cross-talk.

3. **Layer 3: Orchestrator & ULP (`orch_*`)**
   - Flow arbiter managing Flow A (<4 ms headless sensor sample bursts), Flow B (interactive UI sessions), psychrometric invariant math (`orch_math`), persistent state in RTC Slow Memory (`orch_state`), and the reactive ULP monitor.

4. **Layer 4: Application Lifecycle (`h1os_*`)**
   - Declarative application API (`h1os.h`), LVGL v9 engine bindings (`h1os_lvgl.h`), and POSIX time synchronization (`h1os_time.h`).

## 2. Hardware Invariants

- **Unidirectional Hierarchy:** Upper layers call lower layers; lower layers NEVER call up or cross-talk.
- **Power Latching:** `BAT_CTRL` (GPIO 17) is asserted in the 2nd-stage bootloader hook (`h1os_boot_hook`) within 25 ms and retained in deep sleep via RTC pad hold.
- **Zero-Heat Sensing:** Never poll the SHTC3 during active CPU operation. SHTC3 sampling occurs strictly in headless sample bursts (<10 ms) or via the ULP monitor to prevent PCB self-heating bias.
- **Documentation:** Public documentation resides in root or `docs/`, with engineering specs under `docs/architecture/` and `docs/drivers/`.
