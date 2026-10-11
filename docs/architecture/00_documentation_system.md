# Document 00: Documentation System Architecture & Boundary Governance

## 1. Overview & Purpose
This document governs the **two-tier documentation system** of **H1OS** (Class-E Luxury Environmental Telemetry Instrument Operating System). It establishes a permanent, immutable boundary between **Public User-Facing Guides** (for application developers building products with H1OS) and **Internal Architectural Specifications** (for systems engineers maintaining core drivers, silicon pipelines, and coprocessor sentinels).

---

## 2. The Two-Tier System Architecture

```
h1os/ (Repository Root)
├── README.md                          <-- TIER 1: Public Gateway & Quickstart
├── HARDWARE_ERRATA_AND_PCB_REV_GUIDE.md<-- TIER 1: Hardware Errata & Call to Action
├── docs/
│   ├── USER_GUIDE.md                  <-- TIER 1: Developer Manual & API Guide
│   ├── PIN_MAP.md                     <-- TIER 1: Verified Electrical Pinout Table
│   ├── API_REFERENCE.md               <-- TIER 1: Public C/C++ Header Reference (h1os.h)
│   ├── perf_and_drivers/              <-- TIER 2: Hardware Bring-Up & Peripheral Truth
│   │   ├── 00_overview_and_hardware_matrix.md
│   │   ├── 01_shtc3_temp_humidity.md
│   │   ├── 02_pcf85063a_rtc.md
│   │   ├── 03_es8311_ns4168_audio.md
│   │   ├── 04_ssd1681_epaper_display.md
│   │   ├── 05_power_latch_and_battery_adc.md
│   │   ├── 06_microsd_fatfs.md
│   │   └── 07_tactile_buttons_and_led.md
│   │
│   └── architecture/                  <-- TIER 2: Internal Engineering Specs (11 Docs)
│       ├── 00_documentation_system.md<-- Doc 00: Governance & System Architecture [THIS FILE]
│       ├── 01_master_architecture.md  <-- Doc 01: 4-Layer Hierarchy, Philosophy & Boundaries
│       ├── 02_layer1_hal.md           <-- Doc 02: HAL, Pad Holds, Flash & Bus Drivers
│       ├── 03_layer2_subsystems.md    <-- Doc 03: Peripheral Subsystem Managers
│       ├── 04_layer3_orchestrator.md  <-- Doc 04: Flow Arbiter & Class-E Math Engine
│       ├── 05_layer3_ulp_sentinel.md  <-- Doc 05: ULP-RISC-V Coprocessor Hardware Bouncer
│       ├── 06_layer4_api.md           <-- Doc 06: Declarative Lifecycle & LVGL v9 Engine
│       ├── 07_flowchart_state_machine.md <-- Doc 07: Mermaid Execution State Flowcharts
│       ├── 08_lessons_learned_and_rationale.md <-- Doc 08: Post-Mortem & Scaffolding Purge
│       ├── 09_todo_roadmap.md         <-- Doc 09: Canonical Phased Construction Plan
│       ├── 10_changelog_template.md   <-- Doc 10: SemVer Release & ABI Tracking
│       └── 11_class_e_hardware_benchmarking.md <-- Doc 11: Benchmarking & Silicon Metrics
```

---

## 3. Strict Boundary Rules: What Goes Where

### Tier 1: Public-Facing Documentation (External)
**Audience:** Embedded software engineers building battery-powered telemetry instruments on top of H1OS.  
**Principle:** Focus on *capabilities, lifecycle declarations, and clean APIs*. Conceal register hacks, workarounds, and internal state buffers.

1. **`README.md` (Root):**
   - High-level overview, target hardware (Waveshare ESP32-S3 ePaper 1.54" V2).
   - Core specifications: Class-E zero-heat psychrometrics, 12 µA quiescent deep sleep, LVGL 9 support, 30s interactive sessions.
   - Quickstart guide (3-step build and flash).
   - High-level pin mapping summary table.
2. **`HARDWARE_ERRATA_AND_PCB_REV_GUIDE.md` (Root):**
   - Comprehensive technical errata detailing the 8 physical hardware defects of the Waveshare development board.
   - Stands as an unmissable call to action for the hardware designer for a future Rev B PCB.
3. **`docs/USER_GUIDE.md`:**
   - How to configure and start an application via `h1os_start()` and `h1os_lifecycle_t`.
   - How to draw on the electrophoretic display using LVGL 9 widgets and 1-bit typography.
   - How to read calibrated telemetry (`h1os_get_telemetry()`).
   - How to command orderly deep sleep (`h1os_sleep(sec)`) or power off (`h1os_shutdown()`).
4. **`docs/PIN_MAP.md`:**
   - Complete, verified hardware pinout table with electrical characteristics, direction, pull-up requirements, and peripheral mapping.
5. **`docs/API_REFERENCE.md`:**
   - Function signatures, parameter descriptions, return codes (`esp_err_t`), and data structs defined in the public Layer 4 header (`h1os.h`).

---

### Tier 2: Internal Engineering Architecture (Contributor-Only)
**Audience:** Core maintainers, firmware architects, and silicon engineers.  
**Principle:** Full transparency. Document exact register addresses, bus timing constraints, silicon landmines, and low-level workarounds in black-and-white detail.

- **Private Details Kept Inside `docs/architecture/` and `docs/perf_and_drivers/`:**
  - **Register-Level Hacks:** Why ES8311 Reg `0x0D` prevents bus clamping; why PCF85063A Reg `0x01` must write `COF=111` to silence the 32.768 kHz `CLKOUT` pin.
  - **Memory Layout & Offsets:** Exact layout of `RTC_SLOW_MEM` (<512 bytes), ULP toolchain memory reservations (`CONFIG_ULP_COPROC_RESERVE_MEM=2048`), and `epd_frame` partition sector alignments.
  - **ULP Gating Rule:** The ULP Coprocessor is gated exclusively by the main application. It runs **only** while the application is in deep sleep. Once Flow B wakes, the dual-core Xtensa and LVGL own the hardware completely; the ULP is suppressed to guarantee zero interference during active user interaction.
  - **Silicon Constraints:** Why SHTC3 on `GPIO 47/48` cannot be read by the ULP in deep sleep, and why `Flow A` Xtensa wake stub is the hardware-aligned solution.
  - **Post-Mortem Failures:** Documenting the legacy scaffolding trap, callback collisions, 5000-byte RTC memory exhaustions, and Zero-Hour dual-wake races so they are never repeated.

---

## 4. Maintenance & Synchronization Governance

1. **Zero-Drift Invariant:**
   - Any modification to public API function signatures in `06_layer4_api.md` **MUST** be mirrored in `docs/API_REFERENCE.md` and `docs/USER_GUIDE.md`.
   - Any pin reassignment in `02_layer1_hal.md` **MUST** be mirrored in `docs/PIN_MAP.md`.
2. **SemVer Semantic Versioning:**
   - Changes that alter `h1os_lifecycle_t` or public headers require a **MAJOR** version bump.
   - Internal architectural optimizations within Layer 1–3 that preserve Layer 4 ABI require a **MINOR** or **PATCH** version bump.
3. **Black-and-White Specification Standard:**
   - Every internal spec must state physical pin numbers, hex register addresses, timeout budgets in milliseconds, and memory allocations in bytes. Vague descriptions ("configure appropriately") are strictly forbidden.
