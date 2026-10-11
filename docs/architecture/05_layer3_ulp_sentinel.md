# Layer 3: ULP-RISC-V Coprocessor & Hardware Sentinel Specification

## 1. Overview
The ULP-RISC-V Coprocessor acts as the autonomous, always-on **Hardware Sentinel** in the ESP32-S3 RTC domain. While the high-performance dual-core Xtensa LX7 processors sleep at ~12 µA quiescent current, the ULP coprocessor executes periodic micro-monitoring routines (~15–30 µA active for <500 µs), arbitrating hardware wake events and safeguarding the system.

---

## 2. Core Responsibilities & Silicon Boundaries

```
                      RTC DOMAIN (Always Powered @ 12 µA)
                    ═════════════════════════════════════
                                      │
                         [ULP-RISC-V Sentinel]
                                      │
        ┌─────────────────────────────┼─────────────────────────────┐
        │                             │                             │
        ▼                             ▼                             ▼
  [ADC1 Channel 3]              [RTCIO 5]                     [RTCIO 0 & 18]
  Battery Divider               PCF85063A INT                 Tactile Buttons
  • 12 dB Attenuation           • Edge / Level Detect         • 50ms Debounce
  • eFuse Curve Hand-Off        • Zero-Hour Arbiter           • Tap vs Long-Press
  • Brownout Tripwire (<3.25V)  • Suppresses Sub-Sprint       • Glitch Rejection
```

---

## 3. Autonomous Battery Guard & Brownout Tripwire

- **Physical Pin:** `GPIO 4` (`ADC1_CHANNEL_3`) connected via a 1:2 resistor divider (100kΩ / 100kΩ).
- **Gain / Attenuation:** Configured for `ADC_ATTEN_DB_12` (0 to 3.1V range, measuring battery voltage up to 4.3V).
- **Factory Calibration Integer Hand-Off:**
  Before entering deep sleep, the main Xtensa core reads factory eFuses and writes linear integer scaling factors into RTC Slow SRAM:
  $$V_{\text{bat\_mV}} = \left(\frac{\text{raw} \times m_{\text{scale}}}{4096}\right) \times 2 + b_{\text{offset}}$$
- **Execution Cadence:** Every 30 seconds.
- **Filtering:** 4-sample boxcar average + running EWMA to prevent RF transmit or electrophoretic pulse loads from causing false undervoltage trips.
- **Critical Threshold Action ($V_{\text{bat}} < 3.25\text{V}$):**
  1. Sets `ULP_DISPATCH_CRITICAL_SHUTDOWN` in `orch_persisted_state_t`.
  2. Wakes the main CPU to display an emergency low-battery icon on the e-paper panel.
  3. Releases `GPIO 17` (`BAT_CTRL`) to physically cut battery LDO power, preventing catastrophic LiPo cell discharge.

---

## 4. Zero-Hour Conflict Elimination (Hardware RTC Arbitration)

- **The Problem:** The internal sub-execution timer waking up seconds before the external PCF85063A calendar alarm, causing two wakes in rapid succession.
- **The ULP Solution:**
  1. The ULP monitors `GPIO 5` (`RTC_INT`).
  2. When the periodic sensor sample timer triggers, the ULP samples `GPIO 5` before waking the main CPU.
  3. **Arbitration Rules:**
     - If `GPIO 5` is **LOW (Alarm Expired / Active)**: The ULP skips the sensor sprint entirely, sets `ULP_DISPATCH_MAIN_WAKE`, and wakes the main CPU straight into Flow B (Full UI refresh).
     - If `GPIO 5` is **HIGH (No Alarm)**: The ULP sets `ULP_DISPATCH_SENSOR_SPRINT` and triggers `ulp_riscv_wakeup_main_processor()` to launch Core 0 into the <4ms Wake Stub.
  4. The main application never schedules competing wake timers; the ULP is the sole arbiter.

---

## 5. Intelligent Button Debounce & Event Classification

- **Monitored Pins:** `GPIO 0` (`BOOT0`) and `GPIO 18` (`BAT_KEY`).
- **Wake Mechanism:** Configured with `EXT1` edge-triggering directly to the ULP domain.
- **Filtering Logic:**
  - Glitch Filter: Signals < 20 ms are discarded without waking the main CPU.
  - Short Tap (50 ms – 1.0 s): Sets `ULP_DISPATCH_MAIN_WAKE` with `BTN_EVENT_TAP` flag.
  - Long Press (> 2.5 s): Sets `ULP_DISPATCH_CRITICAL_SHUTDOWN` or invokes recovery mode.

---

## 6. Shared Memory Interface (`shared_vars.h`)

The ULP program and the main application share a strict structure located at the base of `RTC_SLOW_MEM` (<512 bytes):

```c
#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef enum {
    ULP_DISPATCH_NONE = 0,
    ULP_DISPATCH_SENSOR_SPRINT,     // Prompt Core 0 into Flow A Wake Stub (<4ms)
    ULP_DISPATCH_MAIN_WAKE,         // Prompt Core 0/1 into Flow B (LVGL UI)
    ULP_DISPATCH_CRITICAL_SHUTDOWN  // Battery brownout tripwire (<3.25V)
} ulp_dispatch_reason_t;

typedef struct {
    // Dispatch control
    ulp_dispatch_reason_t dispatch_reason;
    uint32_t              ulp_wake_counter;
    
    // Battery Calibration & Health
    uint16_t              adc_cal_scale;    // From factory eFuses
    int16_t               adc_cal_offset;   // From factory eFuses
    uint16_t              filtered_vbat_mv; // Latest calibrated battery reading
    
    // Silicon Thermal Tracking
    int16_t               ulp_die_temp_raw; // Running TSENS register value
} ulp_shared_data_t;
```

---

## 7. Build Pipeline & Toolchain Integration
- **Source Location:** `components/esp32-s3_bsp/ulp/`
- **Compiler:** `riscv32-esp-elf-gcc` via ESP-IDF native `ulp_embed_binary()` CMake macro.
- **Memory Reservation:** `CONFIG_ULP_COPROC_RESERVE_MEM=2048` in `sdkconfig`.
- **Linking:** Output binary embedded as a byte array symbol (`_binary_ulp_main_bin_start`) and loaded during cold boot via `ulp_riscv_load_binary()`.
