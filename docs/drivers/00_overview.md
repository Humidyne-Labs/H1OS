# Peripheral & Driver Verification: Hardware Matrix & Bus Architecture

## 1. System Overview & Bus Topology
The Waveshare ESP32-S3 e-Paper 1.54" V2 development board incorporates multiple ICs spanning high-speed SPI, standard I2C, I2S digital audio, 1-bit SDMMC, and analog sensing.

The table below defines the exact hardware assignment, physical pins, electrical characteristics, operating modes, and bus speeds.

| Subsystem / IC | Bus / Interface | Physical Pins (ESP32-S3) | Operating Parameters | Standby / Sleep State | Verified Hardware Reference |
|---|---|---|---|---|---|
| **Sensirion SHTC3** | Shared I2C (0x70) | SDA: `GPIO 47`<br>SCL: `GPIO 48` | 400 kHz Fast-Mode<br>External 4.7 kΩ Pull-ups to 3.3V<br>Normal Mode (`0x7866`): Full ADC Precision | Sleep cmd: `0xB098` | `components/h1os/src/sub_sensor.c` |
| **NXP PCF85063A** | Shared I2C (0x51)<br>INT: Open-Drain | SDA: `GPIO 47`<br>SCL: `GPIO 48`<br>INT: `GPIO 5` | 400 kHz Fast-Mode<br>External 4.7 kΩ Pull-ups to 3.3V<br>32.768 kHz Quartz (12.5pF)<br>CLKOUT Disabled (`COF=0x07`) | Countdown Timer active | `components/h1os/src/sub_rtc.c` |
| **Everest Semi ES8311** | Shared I2C (0x18)<br>I2S Master | SDA: `GPIO 47`, SCL: `GPIO 48`<br>MCLK: Internal/Unused<br>BCLK: `GPIO 21`, WS: `GPIO 45`<br>DOUT: `GPIO 40` (I2S DSDIN) | 16 kHz 16-bit Standard Philips Mono<br>Root Clock: `PLL_160M` with DFS Lock<br>22-Register clock tree<br>PA Rail: `GPIO 42` (Active LOW) | Standby cmd: `0x0D=0xFC`<br>Rail kept ON (0) to avoid I2C clamping | `components/h1os/src/sub_audio.c` |
| **NS4168 Class-D Amp** | Audio Power Amp | Enable/Mute: `GPIO 46`<br>Power Rail: `GPIO 42` | Analog differential drive from ES8311<br>CTRL: 1 = Active, 0 = Muted | Muted: `GPIO 46 = 0` | `components/h1os/src/sub_audio.c` |
| **Solomon Systech SSD1681** | SPI2 Master<br>(Mode 0, 4-Wire) | MOSI: `GPIO 13`, SCK: `GPIO 12`<br>CS: `GPIO 11`, DC: `GPIO 10`<br>RST: `GPIO 9`, BUSY: `GPIO 8`<br>3V3 Rail: `GPIO 6` (Active LOW) | Write: 20 MHz SPI DMA<br>Read (Temp): 2 MHz 3-Wire Half-Duplex<br>Ping-Pong RAM `0x24` / `0x26`<br>Partial LUT: 159 Bytes (Non-Touch) | Deep Sleep Mode 1 (`0x10=0x01`)<br>RAM Retained | `components/h1os/src/sub_display.cpp` |
| **Battery Sensing & Latch** | ADC1_CH3<br>RTC GPIO 17 | ADC: `GPIO 4`<br>BAT_CTRL: `GPIO 17` | ADC 12 dB attenuation (0–3.1V)<br>1:2 Resistive Divider ($200\,\text{k}\Omega / 200\,\text{k}\Omega$)<br>BAT_CTRL: 1 = LDO Enabled | Deep Sleep Pad Hold: `GPIO 17 = 1`<br>Shutdown: `GPIO 17 = 0` | `components/h1os/src/sub_power.c` |
| **MicroSD Card** | SDMMC 1-Bit Slot | CLK: `GPIO 39`<br>CMD: `GPIO 41`<br>D0: `GPIO 40` | SDMMC Default Speed (20 MHz)<br>FATFS 16KB allocation unit | VFS unmount<br>Pins tristate | `components/h1os/src/sub_sdcard.c` |
| **Tactile Buttons & LED** | GPIO Digital I/O | BOOT: `GPIO 0`<br>POWER: `GPIO 18`<br>LED: `GPIO 3` (Open-Drain) | External $10\,\text{k}\Omega$ Pull-ups to 3.3V<br>Internal Pull-ups in parallel ($45\,\text{k}\Omega$)<br>LED: 0 = ON, 1 = OFF<br>Debounce: 30ms, Hold: 2500ms | EXT1 Wakeup: ANY_LOW on 0 & 18 | `components/h1os/src/hal_io.c` |

---

## 2. Power Rails & Critical Sequencing Rules

### Rule 1: BAT_CTRL (GPIO 17) Power Latch
- **Hardware Circuit:** The battery power gate requires `GPIO 17` held HIGH to keep the main system LDO regulator enabled.
- **Boot Requirement:** Asserted HIGH strictly in the 2nd-stage bootloader (`h1os_boot_hook`) and locked via RTC IO domain pad hold (`rtc_gpio_hold_en(GPIO_NUM_17)`).
- **Deep Sleep:** Persists across deep sleep and warm resets via the hardware RTC IO pad hold and `esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON)`.
- **System Off:** `hal_io_release_power_latch()` disables the RTC pad hold and drives `GPIO 17 = 0` to drop the regulator gate.

### Rule 2: EPD_3V3_EN (GPIO 6) Peripheral & E-Paper Rail
- **Active Level:** Active LOW (`0 = Power ON`, `1 = Power OFF`).
- **Deep Sleep:** Held LOW (`0`) in RTC IO domain to keep the SSD1681 and SHTC3 powered in deep sleep so they maintain RAM and calibration.

### Rule 3: PA_EN (GPIO 42) & ESD Diode Clamping Hazard
- **Active Level:** Active LOW (`0 = Power ON`, `1 = Power OFF`).
- **Critical Hardware Quirk:** Cutting `PA_EN` HIGH (`1`) while the shared I2C bus (GPIO 47/48) is pulled up to 3.3V forward-biases the ES8311 internal ESD diodes, clamping SDA/SCL to ~0.7V (see [`ERRATA.md` Errata E4](../../ERRATA.md#e4-es8311-esd-diode-i2c-bus-clamping)).
- **Mandate:** `PA_EN` **MUST REMAIN ENERGIZED (LOW / 0)** during all normal and sleep operations. Audio power saving is achieved strictly via ES8311 software standby and NS4168 mute (`PA_CTRL GPIO 46 = 0`).

### Rule 4: I2S Clock Stability & Dynamic Frequency Scaling (DFS)
- **Clock Tree Source:** ESP32-S3 I2S generates BCLK and WS via fractional division ($N + b/a$) from `PLL_160M` (`I2S_CLK_SRC_DEFAULT`).
- **Frequency Scaling Risk:** If Dynamic Frequency Scaling (DFS) or CPU throttling occurs during audio playback without holding an `ESP_PM_APB_FREQ_MAX` lock, the root PLL frequency drops, causing audio playback speed and pitch to drop proportionally.
- **Mandate:** The I2S channel holds the APB/PLL max frequency lock during playback and releases it upon entering standby.

---

## 3. Four-Layer Clean-Slate Mapping

```mermaid
graph TD
    App[Layer 4: Application / Orchestrator] --> Sub[Layer 2: Subsystem Drivers]
    Sub --> HAL[Layer 1: Hardware Abstraction Layer]
    HAL --> HW[Layer 0: Physical Silicon & GPIOs]

    subgraph Layer2_Subsystems ["Layer 2 Subsystem Drivers"]
        sub_sensor["sub_sensor.c: SHTC3 & TSENS"]
        sub_rtc["sub_rtc.c: PCF85063A RTC"]
        sub_audio["sub_audio.c: ES8311 & NS4168"]
        sub_display["sub_display.cpp: SSD1681 E-Paper"]
        sub_power["sub_power.c: Battery ADC & Sleep Engine"]
    end

    subgraph Layer1_HAL ["Layer 1 HAL Drivers"]
        hal_i2c["hal_i2c.c: Shared Master I2C 400kHz"]
        hal_spi["hal_spi.c: EPD SPI Master 20MHz/2MHz"]
        hal_io["hal_io.c: Pinout, Latch & Sleep Isolation"]
    end
```

Every peripheral has a single Layer 1 HAL gateway and an isolated Layer 2 Subsystem controller. Higher layers NEVER talk to GPIO or bus handles directly.

---

## 4. Documentation Directory & Reference Index

| Spec # | Document | Scope & Physical Subsystem |
|---|---|---|
| `00` | [`00_overview.md`](00_overview.md) | Master pinout, bus topology, power sequencing, and architecture map. |
| `01` | [`01_shtc3.md`](01_shtc3.md) | Sensirion SHTC3 Relative Humidity & Temperature Sensor. |
| `02` | [`02_rtc.md`](02_rtc.md) | NXP PCF85063A Ultra-Low Power Calendar RTC & Countdown Timer. |
| `03` | [`03_audio.md`](03_audio.md) | Everest Semi ES8311 Codec & NS4168 Class-D Mono Power Amplifier. |
| `04` | [`04_epaper.md`](04_epaper.md) | Solomon Systech SSD1681 1.54" 200×200 E-Paper Display Controller. |
| `05` | [`05_power.md`](05_power.md) | Power Latch (`BAT_CTRL`), 12 dB Battery ADC & LiPo OCV Curve. |
| `06` | [`06_sdcard.md`](06_sdcard.md) | MicroSD Storage Slot & 1-Bit SDMMC Mode FATFS File System. |
| `07` | [`07_io.md`](07_io.md) | Tactile Pushbuttons (`BOOT`, `POWER`), 10k Pull-ups & Status LED. |
| `Root` | [`ERRATA.md`](../../ERRATA.md) | Hardware Errata, Silicon Nuances & PCB Rev B Redesign Guidelines. |
