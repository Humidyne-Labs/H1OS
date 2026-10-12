# H1OS: Future Roadmap & Peripheral Driver Verification Guide

> **Document Status:** Active Reference & Roadmap  
> **Target Hardware:** Waveshare ESP32-S3 ePaper 1.54" V2 (`ESP32-S3-PICO-1-N8R8`)  
> **Platform Identity:** **H1OS** — Class-E Environmental Operating System for Luxury Telemetry  
> **Reference Specs:** [`docs/perf_and_drivers/`](docs/perf_and_drivers/)

---

## 1. Executive Summary & Brand Charter

### 1.1 The H1OS Philosophy
**H1OS** transforms off-the-shelf development hardware into an **instrument-grade Class-E hygrometer and luxury environmental telemetry appliance**. 

Unlike typical hobbyist IoT firmware that polls continuously and suffers from electronics-induced self-heating, H1OS is built on three core pillars:
1. **Absolute Metrological Invariance:**
   - **Zero-Heat Sensor Sprints:** Xtensa main core wakes for $<10\,\text{ms}$ (or executes via the $<3\,\text{ms}$ RTC Fast Wake Stub / autonomous ULP-RISC-V coprocessor monitor), ensuring ambient thermal readings are completely untainted by MCU power dissipation.
   - **Tri-Node Psychrometrics:** Real-time cross-correlation between the Sensirion SHTC3 ambient sensor, the ESP32-S3 internal silicon TSENS, and the SSD1681 on-glass electrophoretic thermistor.
   - **Thermodynamic Invariants:** Calculation of invariant actual vapor pressure ($e$), true dew point ($T_{\text{dew}}$) using August-Roche-Magnus formulations, and psychrometric enthalpy.
2. **Visual Serenity & Bi-Stable Permanence:**
   - 200×200 electrophoretic e-Paper display driven by ping-pong differential partial refreshes.
   - Custom high-contrast 1-bit bold Montserrat typography engineered specifically for electrophoretic particle migration dynamics.
   - Zero-glare, zero static power consumption.
3. **Tactile & Acoustic Elegance:**
   - High-fidelity Class-D audio via the Everest Semi ES8311 codec and NS4168 amplifier, generating warm harmonic chime arpeggios (boot, wake, alert) rather than harsh square-wave piezo beeps.
   - 100 kΩ pull-up hardware-debounced tactile buttons with non-blocking long-press bootloader jumps.

---

## 2. Platform Architecture Alignment (H1OS Adopted)

The platform has formally transitioned to **H1OS**:

| Architecture Domain | Established Standard | Implementation Details |
|---|---|---|
| **Component Directory Structure** | **Hybrid / Registry-Aligned** | Retains `components/esp32-s3_bsp` for seamless upstream Espressif Component Registry compatibility, while exposing `#include "h1os/h1os.h"` as the primary master executive API. |
| **Flagship Instrument Demo** | **`examples/H1OS`** | Located at [`examples/H1OS`](../examples/H1OS) (`project(h1os)`), showcasing the Class-E luxury hygrometer dashboard. |
| **Master Header** | **`h1os/h1os.h`** | High-level declarative umbrella header ([`include/h1os/h1os.h`](../components/esp32-s3_bsp/include/h1os/h1os.h)) providing `h1os_start()`, `h1os_get_telemetry()`, `h1os_sleep()`, and `h1os_shutdown()`. |
| **Version Alignment** | **v1.0.0-alpha** | SemVer `1.0.0-alpha` representing the clean-slate 4-layer architecture. |

---

## 3. Peripheral Driver Verification Matrix & Audit

Every driver in the H1OS repository has been verified against the physical IC register truth documented in [`docs/perf_and_drivers/`](docs/perf_and_drivers/).

### 3.1 Driver-to-Document Verification Map

```
┌────────────────────────────────────────────────────────────────────────────────────────┐
│                                 H1OS DRIVER MATRIX                                    │
├─────────────────────┬──────────────────┬──────────────────────────┬────────────────────┤
│ Driver Module       │ Source Files     │ Reference Document       │ Verification Status│
├─────────────────────┼──────────────────┼──────────────────────────┼────────────────────┤
│ Sensirion SHTC3     │ sub_sensor.c     │ 01_shtc3_temp_humidity   │ PASS (CRC-8, Sleep)│
│ NXP PCF85063A       │ sub_rtc.c        │ 02_pcf85063a_rtc         │ PASS (TCF [4:3], C)│
│ ES8311 & NS4168     │ sub_audio.c      │ 03_es8311_ns4168_audio   │ PASS (Clock tree)  │
│ Solomon SSD1681     │ sub_display.cpp  │ 04_ssd1681_epaper        │ PASS (159B LUT, CS)│
│ Power Latch & ADC   │ sub_power.c      │ 05_power_latch_and_adc   │ PASS (13-pt LiPo)  │
│ MicroSD FATFS       │ bsp_sdcard.c     │ 06_microsd_fatfs         │ PASS (1-bit SDMMC) │
│ Tactile Buttons/LED │ bsp_button.c     │ 07_tactile_buttons_led   │ PASS (100k pullup) │
│ Bus HAL (I2C/SPI)   │ hal_i2c, hal_spi │ 00_overview_matrix       │ PASS (4.7k, 20MHz) │
│ Hardware Errata/PCB │ (Hardware Rev B) │ 08_hardware_errata_guide │ DOCUMENTED (E1-E8) │
└─────────────────────┴──────────────────┴──────────────────────────┴────────────────────┘
```

---

### 3.2 Deep-Dive Audit Checklist by IC

#### 1. Sensirion SHTC3 Relative Humidity & Temperature Sensor
- [x] **I2C Address:** Confirmed `0x70`.
- [x] **Wake-Up Sequence:** Sends command `0x3517`, waits mandatory $\ge 240\,\mu\text{s}$ (driver implements $1000\,\mu\text{s}$ safe margin).
- [x] **Measurement Command:** High-precision clock-stretching command `0x7CA2` ($T$ first, then $RH$).
- [x] **Conversion Delay:** $12.1\,\text{ms}$ maximum conversion time strictly enforced before reading 6 bytes.
- [x] **CRC-8 Polynomial:** Implements polynomial $P(x) = x^8 + x^5 + x^4 + 1$ (`0x31`) with initialization `0xFF`. Both $T$ and $RH$ words verified against CRC bytes.
- [x] **Deep Sleep Entry:** Sends command `0xB098` immediately after readout to reduce quiescent draw to $<0.6\,\mu\text{A}$ and eliminate self-heating.

#### 2. NXP PCF85063A Real-Time Clock & Calendar
- [x] **I2C Address:** Confirmed `0x51`.
- [x] **Crystal Load Capacitance:** Bit 0 of register `Control_1` (`0x00`) sets `0` for 7.0 pF or `1` for 12.5 pF. Driver explicitly sets `CTRL1_CAP_SEL_12_5PF` (`0x01`) to match the onboard 12.5 pF 32.768 kHz tuning-fork crystal.
- [x] **CLKOUT Pin Suppression:** Bits `[2:0]` of `Control_2` (`0x01`) set `COF = 0x07` (CLKOUT disabled/high-Z) to eliminate unnecessary pin oscillation and save power.
- [x] **Countdown Timer Frequency Prescaler (`TCF`):** Bits `[4:3]` in `Timer_mode_register` (`0x11`) correctly shifted:
  - `0b10 << 3` (`0x10`) for 1 Hz clock.
  - `0b11 << 3` (`0x18`) for 1/60 Hz (1 minute) clock.
- [x] **Pulsed Interrupt Mode:** Bit 6 (`TI_TP`) set to `1` in `Timer_mode_register` to emit a $3.9\,\text{ms}$ active-low pulse on `GPIO 5` (`RTC_INT`), eliminating interrupt latch-ups.
- [x] **8-Byte NVRAM Byte:** Register `0x03` (`RAM_byte`) used for sleep phase persistence across deep sleep cycles.

#### 3. Everest Semi ES8311 Codec & NS4168 Class-D Mono Power Amplifier
- [x] **I2C Address:** Confirmed `0x18`.
- [x] **Power Gating Architecture:**
  - `PA_EN` (`GPIO 42` = 0) kept LOW across deep sleep to prevent ESD protection diodes from forward-biasing and clamping the shared I2C bus (`GPIO 47/48`) to $\sim 0.7\,\text{V}$.
  - `PA_CTRL` (`GPIO 46`) muted LOW during idle to prevent pop-and-click transients.
- [x] **Clock Tree Alignment:**
  - BCLK derived from ESP32-S3 `PLL_160M` via fractional division.
  - Register `0x02` through `0x08` programmed with the 22-register Philips mono 16 kHz audio clock tree.
- [x] **DFS & Playback Frequency Stability:** Verified that ESP-IDF's `i2s_channel_enable()` automatically acquires an `ESP_PM_APB_FREQ_MAX` power management lock, guaranteeing that Dynamic Frequency Scaling (DFS) will not drop the APB clock and alter audio pitch during active chime playback.
- [x] **Zero-Heat Standby Sequence:** 15-register suspend sequence brings ES8311 current down to $<1.0\,\mu\text{A}$ without cutting power rail.

#### 4. Solomon Systech SSD1681 1.54" 200×200 E-Paper Display
- [x] **SPI Bus & Pinout:** `GPIO 11` (SCK), `GPIO 13` (MOSI/SDA), `GPIO 12` (CS), `GPIO 10` (DC), `GPIO 9` (RST), `GPIO 8` (BUSY).
- [x] **159-Byte Partial Waveform LUT Multi-Register Partition:**
  - Register `0x32`: 153 bytes of phase/voltage waveforms.
  - Register `0x3F`: 1 byte EOP (End-of-Pulse) option.
  - Register `0x03`: 1 byte gate driving voltage (`0x00`).
  - Register `0x04`: 3 bytes source driving voltage (`0x41, 0xA8, 0x32`).
  - Register `0x2C`: 1 byte VCOM voltage (`0x28`).
- [x] **Ping-Pong Differential Buffer:** Alternates `0x24` (RAM_BW, new frame) and `0x26` (RAM_RED, previous frame) with display update sequence `0xCF` (differential update) and `0x3C = 0x80` (border float).
- [x] **On-Glass Thermistor Readout (`0x1B`):** Dedicated 2 MHz 3-wire half-duplex SPI device handle with continuous CS low assertion allows direct temperature readout from the electrophoretic panel glass.

#### 5. Power Latch (`BAT_CTRL`) & Battery Voltage ADC
- [x] **Power Latch (`GPIO 17`):** Driven HIGH early in bootloader; pad held across sleep with `gpio_hold_en(GPIO_NUM_17)`. RTC peripheral power domain kept powered (`ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON`) to prevent latch drop.
- [x] **ADC Calibration:** ADC1 Channel 3 (`GPIO 4`) configured with 12 dB attenuation ($0\dots 3100\,\text{mV}$ range) and curve-fitting calibration.
- [x] **16-Sample Trimmed Outlier Filter:** 16 successive samples taken, minimum 2 and maximum 2 discarded, remaining 12 averaged.
- [x] **Calibrated 13-Point LiPo OCV Lookup:** 13-point piecewise linear interpolation table accurately converting open-circuit cell voltage ($3.27\,\text{V} \dots 4.20\,\text{V}$) into State-of-Charge (0%–100%).

#### 6. MicroSD Storage & 1-Bit SDMMC
- [x] **Bus Mode:** 1-bit SDMMC host (`GPIO 2` CLK, `GPIO 1` CMD, `GPIO 41` D0).
- [x] **Non-Blocking Mount:** Returns `BSP_ERR_SD_MOUNT_FAILED` gracefully without hanging or spamming errors when no card is inserted.
- [x] **Cluster Size:** Optimized for 16 KB cluster allocation for fast telemetry logging.

#### 7. Tactile Buttons (`BOOT` & `POWER`) & Status LED
- [x] **External 100 kΩ Pull-Ups:** Documented on `GPIO 0` (BOOT) and `GPIO 18` (POWER); internal weak pull-ups left enabled in parallel.
- [x] **10 ms Non-Blocking Debounce:** Tick-driven state machine avoiding busy-wait delays.
- [x] **2000 ms Long-Press Actions:**
  - Long-press `BOOT` (GPIO 0): Reboots directly into ROM USB Download Bootloader via `esp_restart()` with RTC flags.
  - Long-press `POWER` (GPIO 18): Executes orderly shutdown, de-asserting `GPIO 17` latch to cut battery power.

---

## 4. Hardware Benchmarking & Test Protocols (Next Session)

When hardware bench testing begins, execute these 5 standardized test protocols:

### Protocol 1: Flow A Sensor Sprint On-Time (< 10 ms Target)
1. Connect oscilloscope Channel 1 to `GPIO 3` (Status LED) and Channel 2 to `GPIO 48` (I2C SCL).
2. Configure `orch_flow_execute_a()` to toggle `GPIO 3` HIGH at entry and LOW at sleep entry.
3. **Pass Criteria:** Total pulse duration $\le 10.0\,\text{ms}$.

### Protocol 2: Deep Sleep Standby Quiescent Current (< 15 µA Target)
1. Power device from a Nordic Power Profiler Kit II (PPK2) at $3.70\,\text{V}$ across battery terminals.
2. Allow device to complete initial boot, display refresh, and enter deep sleep.
3. Measure continuous floor current over a 120-second window.
4. **Pass Criteria:** Average quiescent current $\le 15.0\,\mu\text{A}$ (incorporating SHTC3 sleep, ES8311 suspend, SSD1681 sleep, and ESP32-S3 RTC domain).

### Protocol 3: Differential Partial Refresh Latency (~300 ms Target)
1. Connect logic analyzer to `GPIO 12` (CS), `GPIO 10` (DC), and `GPIO 8` (BUSY).
2. Trigger `sub_display_update_partial()` with the custom 159-byte LUT.
3. Measure elapsed time from CS assertion to BUSY line rising HIGH and falling back LOW.
4. **Pass Criteria:** BUSY assert time $\le 350\,\text{ms}$ with zero perceptible ghosting.

### Protocol 4: Zero-Hour Collision Arbitration Test
1. Set PCF85063A hardware countdown timer to wake in 60 seconds (`GPIO 5` low pulse).
2. Set ESP32-S3 internal sleep timer to wake in 60 seconds.
3. Observe wake sequence over serial monitor.
4. **Pass Criteria:** Flow A executes first, samples SHTC3, queries PCF85063A countdown register, detects zero-hour condition, and hands off seamlessly to Flow B without double-waking or hanging.

### Protocol 5: Tri-Node Thermal Validation Test
1. Place device inside a controlled climate chamber alongside an external calibrated reference hygrometer (e.g., Rotronic or Vaisala).
2. Run continuous 3-hour logging cycle (60-second sensor sprints, 10-minute EPD flushes).
3. Record Tri-Node temperature array: $T_{\text{SHTC3}}$, $T_{\text{TSENS}}$, $T_{\text{EPD\_GLASS}}$.
4. **Pass Criteria:** Calculated ambient plateau temperature deviates by $\le \pm 0.2^\circ\text{C}$ from chamber reference.

---

## 5. Quick-Resume Checklist for Next Session

To immediately pick up progress next session:

```powershell
# 1. Verify git branch and status
git status

# 2. Build and verify OSDemo / H1OS binary
idf.py --preset dev build

# 3. Flash to hardware (COM3 or current port)
idf.py -B build_dev -p COM3 flash monitor

# 4. Execute Driver / Peripheral Verification Test Suite
cd examples/Peripherals_Test_Suite
idf.py --preset dev build
```
