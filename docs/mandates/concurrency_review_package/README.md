# H1OS Dual-Core Concurrency & Lifecycle Architecture Review Package

## 1. Executive Summary & Review Objective

This package has been prepared for external systems engineering and embedded firmware architecture review. It addresses a fundamental design decision in **H1OS** on the **ESP32-S3** (dual Xtensa LX7 cores, 240 MHz):

> **How should the H1OS application lifecycle orchestrate the dual CPU cores during unattended periodic telemetry wakes (Flow B) and interactive user sessions to eliminate mutex contention, avoid electrophoretic display waveform conflicts, and maximize battery operating life?**

---

## 2. Silicon & Firmware Baseline

* **Target Hardware:** ESP32-S3 (Dual-Core Xtensa LX7, 8 MB Octal PSRAM, 8 MB Quad Flash).
* **Display Panel:** Waveshare 1.54" V2 E-Paper (SSD1681 controller, SPI DMA, 200x200 1-bit monochrome).
* **Display Physical Constraint:** SSD1681 requires **$300\text{ ms}$ (partial)** or **$1800\text{ ms}$ (full OTP)** to physically drive microcapsules with $\pm 15\text{V}$ waveforms. During this time, the display controller asserts `BUSY` HIGH and cannot accept SPI transactions.
* **Architectural Law (`AGENTS.md`, Invariant 4):**
  - **Core 0 (`PRO_CPU`):** System, FreeRTOS timer daemon, Wi-Fi PHY/MAC, LwIP TCP/IP stack, MQTTS/TLS, and sensors.
  - **Core 1 (`APP_CPU`):** Dedicated exclusively to the LVGL v9 presentation task (`h1os_lvgl_port_task`).

---

## 3. Package Manifest & Reading Order

| File | Purpose | Key Content |
| :--- | :--- | :--- |
| **`01_h1os_lifecycle_concurrency_rfc.md`** | Problem Foundation | Wake state ambiguity and initial mutex contention observations. |
| **`02_h1os_concurrency_solutions_plan.md`** | Authoritative Solutions | 4 concrete architectures, power calculations, Mermaid timing flows, and FreeRTOS barrier specs. |
| **`03_source_code_reference.md`** | Verbatim Silicon Context | Exact C/C++ code extracts of `h1os_lifecycle.c`, `h1os_lvgl.cpp`, and task pinning. |

---

## 4. Key Questions for the Reviewer

We request your engineering guidance on four specific design questions:

1. **Serialized vs Overlapped Execution:**
   - Should periodic Flow B wakes serialize network I/O and display refresh ($T_{\text{net}} + T_{\text{disp}} \approx 4.3\text{s}$), or overlap them in parallel ($\max(T_{\text{net}}, T_{\text{disp}}) \approx 2.5\text{s}$) to achieve $\sim 42\%$ battery energy savings?
2. **Double-Refresh Prevention:**
   - Because local SHTC3 sensor data is already present in RTC Slow Memory at boot, the local display can refresh immediately. How should inbound remote cloud data (e.g. weather forecast) be handled—via a bounded wait window (e.g. 1000 ms) before the physical waveform, or by updating the display only on the next cycle?
3. **Inter-Core UI Mutation Mechanism:**
   - Which paradigm is superior for application threads mutating LVGL state from Core 0:
     - **Option A:** Fine-grained, scoped mutex locks (`h1os_lvgl_lock(100)` / `h1os_lvgl_unlock()`).
     - **Option B:** Lock-free / Queue-based Actor pattern (`h1os_ui_post(callback, arg)`).
4. **Lifecycle API Contract (`h1os_lifecycle_t`):**
   - Is it preferable to keep a single `on_wake()` callback, or formally split it into two explicit phases: `on_sync()` (Core 0, zero locks) followed by `on_render()` (Core 1, UI only)?

---

**Prepared by Humidyne Labs / Humiditron Systems Engineering**  
SPDX-License-Identifier: MIT
