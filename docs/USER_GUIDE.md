# 📖 H1OS Developer Guide & Reference Manual

**Target Hardware:** Waveshare ESP32-S3 ePaper 1.54" V2 (`ESP32-S3-PICO-1-N8R8`)  
**Operating System:** H1OS (Class-E Luxury Environmental Telemetry Operating System)  
**Supported Frameworks:** ESP-IDF `v6.1` | LVGL `v9.6.0`  
**License:** MIT  

---

## 📑 Table of Contents

1. [Architectural Overview & Philosophy](#1-architectural-overview--philosophy)
2. [Lifecycle Engine & Application Entry](#2-lifecycle-engine--application-entry)
3. [Flow A: Headless Sensor Sprint (<4ms Cadence)](#3-flow-a-headless-sensor-sprint-4ms-cadence)
4. [Flow B: Interactive UI Session (30s Inactivity Sleep)](#4-flow-b-interactive-ui-session-30s-inactivity-sleep)
5. [Class-E Psychrometric Invariant Engine](#5-class-e-psychrometric-invariant-engine)
6. [Display Architecture & LVGL v9 Integration](#6-display-architecture--lvgl-v9-integration)
7. [Persistent State & Flash Frame Synchronization](#7-persistent-state--flash-frame-synchronization)
8. [ULP-RISC-V Coprocessor Monitor](#8-ulp-risc-v-coprocessor-monitor)
9. [Complete Application Template](#9-complete-application-template)

---

## 1. Architectural Overview & Philosophy

H1OS is an instrument-grade operating system designed specifically for ultra-low-power environmental telemetry. It solves the critical flaw in conventional battery instruments: **sensor self-heating bias**.

```
┌────────────────────────────────────────────────────────────────────────┐
│                        FOUR-LAYER H1OS ARCHITECTURE                    │
├────────────────────────────────────────────────────────────────────────┤
│ Layer 4: Application API & Lifecycle (h1os.h, h1os_lvgl.h, h1os_time.h) │
├────────────────────────────────────────────────────────────────────────┤
│ Layer 3: Orchestration Engine & Coprocessor Monitor (orch_flow, ULP)   │
├────────────────────────────────────────────────────────────────────────┤
│ Layer 2: Peripheral Subsystems (sub_display, sub_sensor, sub_rtc...)   │
├────────────────────────────────────────────────────────────────────────┤
│ Layer 1: Hardware Abstraction Layer (hal_io, hal_i2c, hal_spi, flash)  │
└────────────────────────────────────────────────────────────────────────┘
```

### Core Invariants
1. **Zero-Heat Sensing:** High-frequency environmental sampling executes entirely in headless sprints (<4ms) before the chip can heat its cavity.
2. **Keep All Gates Open:** Critical power rails (`BAT_CTRL` GPIO 17, `EPD_3V3_EN` GPIO 6) remain latched and frozen via RTC pad holds during sleep to eliminate capacitor inrush spikes and bus clamping.
3. **No Polling in Deep Sleep:** The ULP-RISC-V coprocessor is event-driven; when the main Xtensa cores are awake, the ULP is completely gated off.
4. **Midnight-Agnostic Timing:** Wakes are governed strictly by the PCF85063A hardware countdown timer rather than calendar alarms to prevent day-rollover lockups.

---

## 2. Lifecycle Engine & Application Entry

Applications interface with H1OS through declarative lifecycle hooks defined in [`<h1os/h1os.h>`](../components/h1os/include/h1os/h1os.h):

```c
#include "h1os/h1os.h"

static void app_on_boot(void *user_data)
{
    ESP_LOGI("APP", "Cold boot initialized");
}

static void app_on_wake(const h1os_wake_context_t *ctx, void *user_data)
{
    ESP_LOGI("APP", "Woke from sleep (Causes bitmask: 0x%08lX)", (unsigned long)ctx->wakeup_causes);
}

static void app_on_pre_sleep(uint32_t sleep_sec, void *user_data)
{
    ESP_LOGI("APP", "Standing down for %lu seconds", (unsigned long)sleep_sec);
}

void app_main(void)
{
    h1os_lifecycle_t lifecycle = {
        .on_boot = app_on_boot,
        .on_wake = app_on_wake,
        .on_pre_sleep = app_on_pre_sleep,
        .on_shutdown = NULL,
        .session = {
            .inactivity_timeout_sec = 30,
            .enable_dfs_80mhz = true,
        },
    };

    h1os_start(&lifecycle);
}
```

---

## 3. Flow A: Headless Sensor Sprint (<4ms Cadence)

When internal timer wakeup occurs, H1OS executes Flow A without booting the secondary core, Wi-Fi stacks, or display drivers:
1. SHTC3 sensor wakes via fast I2C in RTC memory (<250 µs).
2. Reads 16-bit raw temperature and relative humidity (1 ms low-power conversion).
3. Updates the Tri-Node ring buffer and recalculates the vapor pressure invariant.
4. Returns directly to deep sleep in ~2.5 ms total on-time.

---

## 4. Flow B: Interactive UI Session (30s Inactivity Sleep)

When the user taps `BOOT` (GPIO 0) or `POWER` (GPIO 18), H1OS initiates Flow B:
- Spawns the LVGL v9 runtime task and renders the interactive screen.
- Starts a **30-second inactivity countdown**.
- Any button press resets the timer back to 30 seconds.
- When 30 seconds of inactivity elapse, the system executes the coordinated 8-step sleep transition sequence:
  1. Wait for LVGL pipeline to drain.
  2. Wait for electrophoretic panel `EPD_BUSY` falling edge.
  3. Wait 250 ms particle settling delay.
  4. Persist 5000-byte framebuffer to `epd_frame` SPI flash if dirty.
  5. Put SSD1681 into Deep Sleep Mode 1 (1.0 µA).
  6. Arm external PCF85063A countdown timer.
  7. Run Zero-Hour lookahead collision avoidance.
  8. Enter hardware deep sleep with RTC pad holds.

> **Note on RTC Countdown Wake:** If the system is woken by the external PCF85063A countdown timer purely to update the e-paper display, it renders the frame, flushes to the screen, and **immediately returns to deep sleep** without waiting 30 seconds.

---

## 5. Class-E Psychrometric Invariant Engine

H1OS avoids synthetic curve fitting by tracking physical thermodynamic invariants:
- **Saturation Vapor Pressure ($e_s$):**
  $$e_s(T) = 6.112 \cdot \exp\left(\frac{17.625 \cdot T}{243.04 + T}\right) \quad [\text{hPa}]$$
- **Vapor Pressure ($e$):**
  $$e = \frac{RH}{100} \cdot e_s(T) \quad [\text{hPa}]$$
- **True Dew Point ($T_{\text{dew}}$):**
  $$T_{\text{dew}} = \frac{243.04 \cdot \ln(e / 6.112)}{17.625 - \ln(e / 6.112)} \quad [^\circ\text{C}]$$
- **Ambient RH Reconstruction:**
  $$RH_{\text{ambient}} = 100 \cdot \frac{e}{e_s(T_{\text{ambient\_floor}})}$$

---

## 6. Display Architecture & Refresh Policy

- **Resolution:** 200×200 pixels monochrome (5000 bytes working RAM).
- **Format:** `LV_COLOR_FORMAT_I1` with 1-bit packed binary typography (`H1OS_FONT_14`, `H1OS_FONT_20`).
- **Full-Suite Bold Typography:** Build-time synthesized `Montserrat-Bold` and `DejaVuSans` with `--autohint-strong` bilevel rasterization, ensuring 2-to-3-pixel solid stems that eliminate hairline stroke erosion on 188 DPI glass.
- **Keypad Indev:** Hardware tactile buttons are exposed as `LV_INDEV_TYPE_KEYPAD`:
  - `BOOT` (GPIO 0): `LV_KEY_NEXT` (toggles screens / focuses objects).
  - `POWER` (GPIO 18): `LV_KEY_ENTER`.
- **Differential Partial Refresh:** Custom 159-byte partial LUT completes screen updates in ~300 ms without full-screen flicker.
- **Anti-Ghosting Threshold (6-Cycle Quota):** Automatically triggers a full OTP refresh after every 6 partial updates (`CONFIG_H1OS_EPD_PARTIAL_REFRESH_LIMIT`, default 6) to reset residual DC bias and restore peak pigment contrast. In battery operation with a 4-hour max sleep interval, 6 cycles guarantees a full refresh at least once every 24 hours ($6 \times 4\text{h} = 24\text{h}$) to meet manufacturer panel longevity requirements without redundant clock tracking.
- **Power-Off & Long-Term Storage Neutralization:** `h1os_shutdown()` (when `CONFIG_H1OS_EPD_CLEAN_WHITE_ON_SHUTDOWN=y`, default) and `h1os_shutdown_for_storage()` drive all microcapsules to clean white (`0xFF`) via a full OTP refresh before cutting battery power, preventing dye migration, charge accumulation, and permanent burn-in.

---

## 7. Persistent State & Flash Frame Synchronization

- **RTC Slow Memory:** State is preserved across deep sleep in `< 512 bytes` (`orch_persisted_state_t`), leaving 7.5 KB free for the ULP coprocessor.
- **Flash Frame Sync:** When the display is marked dirty, `orch_display_sync_save_if_dirty()` writes the 5000-byte frame to the raw `epd_frame` partition. On wake, `orch_display_sync_restore_to_framebuffer()` restores the prior frame for instantaneous differential updates.

---

## 8. ULP-RISC-V Coprocessor Monitor

While the main cores are in deep sleep, the ULP coprocessor runs autonomously in RTC Slow SRAM:
- **Brownout Threshold Detection:** Monitors battery voltage via ADC1 CH3 (GPIO 4); wakes the main CPU for emergency shutdown if $V_{\text{bat}} < 3.25\text{V}$.
- **Zero-Volt Cable Guard:** Ignores the brownout threshold if $V_{\text{bat}} < 100\text{mV}$ (indicates USB cable power with no battery connected).
- **Wake-on-Release Rule:** Waits for button release before waking the main Xtensa core, ensuring the main application starts with clean released input state.
- **Long-Press Classifier:** Classifies button holds $> 2.5\text{s}$ into bootloader mode (`BOOT`) or power cut (`POWER`).

---

## 9. Complete Application Template

See [`examples/H1OS/main/main.c`](../examples/H1OS/main/main.c) for a complete working reference application featuring dual-screen navigation, Montserrat typography, and multi-node telemetry.
