# Document 00: Documentation System Architecture & Boundary Governance

## 1. Overview & Purpose
This document governs the **two-tier documentation system** of **H1OS** (Class-E Luxury Environmental Telemetry Instrument Operating System). It establishes a permanent boundary between **Public Repository & Developer Guides** (for application engineers building products with H1OS) and **Internal Architectural Specifications** (for systems engineers maintaining core drivers, silicon pipelines, and coprocessor monitors).

---

## 2. The Two-Tier System Architecture

```
h1os/ (Repository Root)
├── README.md                          <-- TIER 1: Public Gateway & Quickstart
├── ERRATA.md                          <-- TIER 1: Hardware Errata, Silicon Nuances & Rev B Guide
├── CHANGELOG.md                       <-- TIER 1: Authoritative SemVer Release & Modification Log
├── LICENSE                            <-- Software License (MIT)
├── LICENSE-CC-BY-4.0                  <-- Documentation License
│
└── docs/
    ├── guide.md                       <-- TIER 1: Developer Manual & Lifecycle Guide
    ├── pinout.md                      <-- TIER 1: Verified Electrical Pinout Table
    ├── api.md                         <-- TIER 1: Public Layer 4 API Reference
    ├── history.md                     <-- TIER 1: Curated Digest of Historical Engineering Archives
    │
    ├── drivers/                       <-- TIER 2: Hardware Bring-Up & Peripheral Specifications
    │   ├── 00_overview.md             <-- Peripheral Matrix & Bus Overview
    │   ├── 01_shtc3.md                <-- SHTC3 Relative Humidity & Temperature
    │   ├── 02_rtc.md                  <-- PCF85063A Real-Time Clock & Alarms
    │   ├── 03_audio.md                <-- ES8311 Codec & NS4168 Class-D Amp
    │   ├── 04_epaper.md               <-- SSD1681 1.54" E-Paper Panel & Waveforms
    │   ├── 05_power.md                <-- Power Latch, Battery ADC & Voltage Divider
    │   ├── 06_sdcard.md               <-- MicroSD FATFS Driver
    │   └── 07_io.md                   <-- Tactile Buttons & LED Indicators
    │
    └── architecture/                  <-- TIER 2: Internal Engineering Specs
        ├── A0_system_governance.md    <-- Governance & Doc Architecture [THIS FILE]
        ├── A1_master_blueprint.md     <-- 4-Layer Hierarchy, Philosophy & Boundaries
        ├── A2_hal.md                  <-- HAL, Pad Holds, Flash & Bus Drivers
        ├── A3_gpio_hold_and_sleep.md  <-- Silicon Hold Domains & Low-Power Sleep Architecture
        ├── A4_subsystems.md           <-- Peripheral Subsystem Managers
        ├── A5_orchestrator.md         <-- Flow Arbiter & Class-E Math Engine
        ├── A6_ulp_coprocessor.md      <-- ULP-RISC-V Coprocessor Hardware Monitor
        ├── A7_sensor_psychrometrics.md<-- Tri-Node Temperature & Psychrometric Sensor Operation
        ├── B1_api_and_services.md     <-- Declarative Lifecycle & LVGL v9 Engine
        ├── B2_state_machine.md        <-- Execution Flowcharts & State Machine
        ├── B3_firmware_standards.md   <-- Firmware Engineering, Safety Rules & Style
        ├── C1_benchmarks_and_verification.md <-- Hardware Benchmarking & Silicon Metrics
        ├── C2_lessons_learned.md      <-- Post-Mortem & Architectural Rationale
        ├── C3_roadmap.md              <-- Canonical Phased Construction Plan & Milestones
        └── C4_changelog_policy.md     <-- Release Policy & SemVer Management
```

---

## 3. Strict Boundary Rules: What Goes Where

### Tier 1: Public Documentation (Root & `docs/`)
**Audience:** Embedded software engineers building battery-powered telemetry instruments on top of H1OS.  
**Principle:** Focus on capabilities, lifecycle declarations, pin definitions, and clean APIs.

### Tier 2: Internal Engineering Specifications (`docs/drivers/`, `docs/architecture/`)
**Audience:** Core BSP engineers and silicon architects.  
**Principle:** Document raw hardware physics, register behaviors, silicon quirks, FreeRTOS task designs, and low-level timings.
