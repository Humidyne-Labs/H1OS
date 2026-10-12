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
        ├── 00_system.md               <-- Governance & Doc Architecture [THIS FILE]
        ├── 01_master.md               <-- 4-Layer Hierarchy, Philosophy & Boundaries
        ├── 02_hal.md                  <-- HAL, Pad Holds, Flash & Bus Drivers
        ├── 03_subsystems.md           <-- Peripheral Subsystem Managers
        ├── 04_orchestrator.md         <-- Flow Arbiter & Class-E Math Engine
        ├── 05_ulp.md                  <-- ULP-RISC-V Coprocessor Hardware Monitor
        ├── 06_api.md                  <-- Declarative Lifecycle & LVGL v9 Engine
        ├── 07_state_machine.md        <-- Execution Flowcharts & State Machine
        ├── 08_lessons_learned.md      <-- Post-Mortem & Architectural Rationale
        ├── 09_roadmap.md              <-- Canonical Phased Construction Plan & Milestones
        ├── 10_changelog.md            <-- Release Policy & SemVer Management
        └── 11_benchmarks.md           <-- Class-E Hardware Benchmarking & Silicon Metrics
```

---

## 3. Strict Boundary Rules: What Goes Where

### Tier 1: Public Documentation (Root & `docs/`)
**Audience:** Embedded software engineers building battery-powered telemetry instruments on top of H1OS.  
**Principle:** Focus on capabilities, lifecycle declarations, pin definitions, and clean APIs.

### Tier 2: Internal Engineering Specifications (`docs/drivers/`, `docs/architecture/`)
**Audience:** Core BSP engineers and silicon architects.  
**Principle:** Document raw hardware physics, register behaviors, silicon quirks, FreeRTOS task designs, and low-level timings.
