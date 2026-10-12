# H1OS: Class-E Luxury Environmental Operating System

[![ESP-IDF](https://img.shields.io/badge/ESP--IDF-v6.1-blue.svg)](https://idf.espressif.com/)
[![Target](https://img.shields.io/badge/Hardware-Waveshare%20ESP32--S3--ePaper--1.54%20V2-green.svg)](https://www.waveshare.com)
[![Graphics](https://img.shields.io/badge/LVGL-v9.6.0-orange.svg)](https://lvgl.io/)
[![Version](https://img.shields.io/badge/H1OS-v2.0.0--dev-brightgreen.svg)](components/h1os/include/h1os/h1os.h)
[![Docs](https://img.shields.io/badge/Docs-User%20Guide-blue.svg)](docs/USER_GUIDE.md)
[![License](https://img.shields.io/badge/License-MIT-purple.svg)](LICENSE)

Production-grade, event-driven ambient operating system and peripheral architecture turning the **Waveshare ESP32-S3 ePaper 1.54" V2** development board (**ESP32-S3-PICO-1-N8R8**) into an **instrument-grade Class-E luxury hygrometer and environmental telemetry appliance** under **ESP-IDF v6.1**.

> 📘 **Looking for the developer guide?** See the full **[H1OS Developer Guide & Reference Manual](docs/USER_GUIDE.md)** and the **[Class-E Hardware Benchmarking Guide](docs/architecture/11_class_e_hardware_benchmarking.md)**.

---

## 📑 Table of Contents

1. [Hardware Specifications](#-hardware-specifications)
2. [Four-Layer Architectural Hierarchy](#-four-layer-architectural-hierarchy)
3. [Zero-Heat Sensing & Psychrometric Invariants](#-zero-heat-sensing--psychrometric-invariants)
4. [Hardware Pinout & Power Rail Map](#-hardware-pinout--power-rail-map)
5. [Declarative Application Lifecycle Engine](#-declarative-application-lifecycle-engine)
6. [Interactive Flow B & 30-Second Inactivity Sleep](#-interactive-flow-b--30-second-inactivity-sleep)
7. [ULP-RISC-V Coprocessor Monitor](#-ulp-risc-v-coprocessor-monitor)
8. [Dual-Plane E-Paper Persistence & Partial Refresh](#-dual-plane-e-paper-persistence--partial-refresh)
9. [Build Instructions](#-build-instructions)
10. [License](#-license)

---

## ⚡ Hardware Specifications

The Waveshare ESP32-S3 ePaper 1.54" V2 is an integrated, battery-powered IoT hardware platform featuring:

- **Compute Module**: Espressif Systems ESP32-S3-PICO-1-N8R8 (Xtensa® dual-core 32-bit LX7 @ up to 240 MHz, 8 MB Quad SPI Flash, 8 MB Octal PSRAM).
- **Bi-Stable Display**: 1.54-inch 200×200 pixel monochrome e-Paper display (Solomon Systech SSD1681 driver, 188 DPI). Maintains image state indefinitely with **zero static current draw**.
- **Environmental Sensor**: Sensirion SHTC3 (I2C `0x70`) high-precision relative humidity and temperature sensor.
- **Calendar Real-Time Clock**: NXP PCF85063A ultra-low power calendar RTC (I2C `0x51`) with 32.768 kHz crystal backup, programmable countdown timer, and alarms.
- **Audio Codec Subsystem**: Everest Semi ES8311 I2S codec + NS4168 Class-D mono power amplifier driving an onboard speaker.
- **Storage**: MicroSD card slot (1-bit SDMMC FATFS mode) + Onboard Flash partitions (`nvs`, `epd_frame`).
- **Power Architecture**: Discrete LDO battery power hold latch (`GPIO 17`), calibrated battery voltage ADC divider (`GPIO 4`, ADC1 CH3), and user status LED (`GPIO 3`).

---

## 🧠 Four-Layer Architectural Hierarchy

H1OS enforces a strict unidirectional dependency model: **Upper layers call lower layers; lower layers NEVER call up or cross-talk.**

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

---

## 🌡️ Zero-Heat Sensing & Psychrometric Invariants

H1OS resolves sensor self-heating bias by maintaining strict thermodynamic invariants:
1. **Flow A Headless Sensor Sprint (<4ms):** Wakes only the RTC Fast Memory stub to sample SHTC3 telemetry in ~2.5 ms before entering deep sleep, eliminating PCB thermal conduction into the cavity.
2. **True Invariant Tracking:** Uses August-Roche-Magnus equations to calculate ambient vapor pressure ($e$), true dew point ($T_{\text{dew}}$), and reconstructed relative humidity ($RH_{\text{amb}}$) based on dynamic ambient floor tracking.

---

## 🔌 Hardware Pinout & Power Rail Map

| Signal Name | Physical Pin | Mode / Direction | Function & Hardware Invariant |
|---|---|---|---|
| **`BAT_CTRL`** | `GPIO 17` | Digital Output | Master battery LDO power latch (**Active HIGH: latched via RTC pad hold in sleep**) |
| **`EPD_3V3_EN`** | `GPIO 6` | Digital Output | Peripheral & display rail gate (**Active LOW: held LOW in sleep to keep display RAM energized**) |
| **`STATUS_LED`** | `GPIO 3` | Open-Drain Output | User LED & Flow A oscilloscope benchmark test point (Active LOW) |
| **`BAT_ADC`** | `GPIO 4` | Analog Input | Battery voltage sense (ADC1 CH3, 1:2 divider, 0-3.1V sensing) |
| **`RTC_INT`** | `GPIO 5` | Digital Input | PCF85063A hardware countdown timer interrupt (**Active LOW, internal pull-up required**) |
| **`BOOT`** | `GPIO 0` | Digital Input | Tactile BOOT key (`LV_KEY_NEXT`, wakes into Flow B, screen toggles) |
| **`BAT_KEY`** | `GPIO 18` | Digital Input | Tactile BAT_KEY (`LV_KEY_ENTER`, wakes into Flow B) |
| **`I2C_SDA`** | `GPIO 47` | I2C Open-Drain | Shared I2C0 Serial Data (SHTC3, PCF85063, ES8311; external 4.7kΩ pull-up) |
| **`I2C_SCL`** | `GPIO 48` | I2C Open-Drain | Shared I2C0 Serial Clock (400 kHz) |
| **`EPD_BUSY`** | `GPIO 8` | Digital Input | SSD1681 busy indicator (Active HIGH; monitored for falling edge) |
| **`EPD_RST`** | `GPIO 9` | Digital Output | SSD1681 hardware reset (Active LOW) |
| **`EPD_DC`** | `GPIO 10` | Digital Output | SSD1681 Data/Command select |
| **`EPD_CS`** | `GPIO 11` | Digital Output | SSD1681 SPI Chip Select (Active LOW) |
| **`EPD_SCK`** | `GPIO 12` | SPI Output | Display SPI Serial Clock (up to 20 MHz) |
| **`EPD_MOSI`** | `GPIO 13` | SPI Output | Display SPI MOSI line |
| **`PA_EN`** | `GPIO 42` | Digital Output | NS4168 Amp power gate (**Active LOW: 1 = Power Cut in sleep**) |
| **`PA_CTRL`** | `GPIO 46` | Digital Output | NS4168 Amp control (**Active HIGH: 0 = Muted/Standby**) |

---

## 🔄 Declarative Application Lifecycle Engine

Applications define declarative lifecycle hooks:

```c
#include "h1os/h1os.h"
#include "h1os/h1os_lvgl.h"

static void app_on_boot(void *user_data) {
    ESP_LOGI("APP", "Cold boot initialized");
}

static void app_on_wake(const h1os_wake_context_t *ctx, void *user_data) {
    ESP_LOGI("APP", "Woke from sleep (Causes: 0x%08lX)", (unsigned long)ctx->wakeup_causes);
}

static void app_on_pre_sleep(uint32_t sleep_sec, void *user_data) {
    ESP_LOGI("APP", "Standing down for %lu seconds", (unsigned long)sleep_sec);
}

void app_main(void) {
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

## ⏱️ Interactive Flow B & 30-Second Inactivity Sleep

- **Button Wake:** Waking the system by tapping `BOOT` or `POWER` launches an interactive 30-second session. Any button click resets the timer.
- **RTC Periodic Wake:** When woken by the PCF85063A countdown timer for a scheduled telemetry update, H1OS renders the new frame, flushes the display, and **immediately returns to deep sleep** to preserve battery.
- **Sleep Transition Sequence:** Drains LVGL $\to$ waits `EPD_BUSY` falling edge $\to$ waits 250 ms particle settling delay $\to$ saves frame to flash if dirty $\to$ enters Deep Sleep Mode 1 (1.0 µA).

---

## 🛡️ ULP-RISC-V Coprocessor Monitor

Runs autonomously in RTC Slow SRAM while the main dual-core CPU is asleep:
- **Brownout Threshold Detection:** Autonomous ADC sampling on GPIO 4 with emergency wake if $V_{\text{bat}} < 3.25\text{V}$.
- **Zero-Volt Cable Guard:** Ignores brownout when $V_{\text{bat}} < 100\text{mV}$ (USB cable powered without battery).
- **Wake-on-Release:** Wakes Xtensa strictly when the button transitions back HIGH.
- **Hold Classification:** Holds $> 2.5\text{s}$ prime ROM bootloader or power cut.

---

## 🛠️ Build Instructions

Build and flash using ESP-IDF v6.1 and Ninja:

```powershell
cd examples/H1OS

# Build
idf.py -B build_dev build

# Flash and Monitor
idf.py -B build_dev -p COMx flash monitor
```

---

## 📄 License

This operating system is open-source software licensed under the [MIT License](LICENSE).  
Copyright (c) 2026 Humidyne Labs / Humiditron.
