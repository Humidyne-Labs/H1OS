# Everest Semiconductor ES8311 & NS4168 Audio Subsystem

## 1. Physical Specifications & Hardware Architecture

- **Codec IC:** Everest Semiconductor ES8311 Low-Power Audio Codec
- **Amplifier IC:** Nuvoton / National NS4168 3W Mono Class-D Audio Power Amplifier
- **Control Interface:** Shared Master I2C (`I2C_NUM_0`, 7-Bit Address: `0x18`)
- **Digital Audio Interface:** I2S0 Master Mode (Standard Philips Format)
  - Master Clock (MCLK): `GPIO 14` (`HAL_PIN_I2S_MCLK`, $256 \times F_s$)
  - Bit / Serial Clock (BCLK / SCLK): `GPIO 15` (`HAL_PIN_I2S_SCLK`)
  - Word Select / LR Clock (LRCK / WS): `GPIO 38` (`HAL_PIN_I2S_LRCK`)
  - Serial Audio Data Out to Codec (DSDIN / DOUT): `GPIO 45` (`HAL_PIN_I2S_DSDIN`)
  - Serial Audio Data In from Codec (ASDOUT / DIN): `GPIO 16` (`HAL_PIN_I2S_ASDOUT`)
- **Power & Control Pins:**
  - `PA_EN` (`GPIO 42`): Audio Subsystem Power Rail (Active LOW: `0 = Power ON`, `1 = Power OFF`)
  - `PA_CTRL` (`GPIO 46`): NS4168 Amplifier Enable / Mute (Active HIGH: `1 = Amp Enabled`, `0 = Muted / Shutdown`)

---

## 2. Electrical Invariant: Shared I2C Bus Disruption on Power-Gating

### Physical Circuit Behavior & Link to Errata E4

Driving `PA_EN` (`GPIO 42`) HIGH to cut power to the audio subsystem causes the shared I2C bus (`GPIO 47/48`) to completely fail, taking down communication with the Sensirion SHTC3 and NXP PCF85063A. The Everest Semiconductor ES8311 documentation lacks ESD protection specifications, contains no I2C pull-up recommendations, and leaves the Chip/Clock State Machine (CSM `S0`–`S7`) undefined. Furthermore, voltage levels during power gating were never measured on hardware (claims of ~0.7V or GND clamping are unverified). 

For detailed physical analysis, datasheet gap evaluation, and PCB Rev B redesign guidelines, see [`ERRATA.md` Errata E4](../../ERRATA.md#errata-e4-audio-codec-power-gating-disrupts-shared-i2c-bus).

### Immutable Software Requirement

`PA_EN` (`GPIO 42`) **MUST REMAIN ENERGIZED (LOW = 0)** during all normal and deep sleep operations. Audio power saving must be achieved strictly through software register suspension in the ES8311 (`0x0D=0xFC`) and hardware mute on `PA_CTRL` (`GPIO 46 = 0`), without disturbing the shared I2C bus.

---

## 3. Register Configuration Map

| **Reg Address** | **Register Name** | **Config Value**   | **Functional Description**                                                                                                                              |
| --------------- | ----------------- | ------------------ | ------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **`0x00`**      | `RESET`           | `0x80`             | CSM (Clock State Machine) powered on; slave mode (`MSC = 0`, `CSM_ON = 1`).                                                                             |
| **`0x01`**      | `CLK_MGR1`        | `0x3F`             | Selects MCLK pin as clock source (Bit 7 = 0); powers on internal digital clocks.                                                                        |
| **`0x02`**      | `CLK_MGR2`        | `0x00`             | Pre-divider = 1, pre-multiplier = 1.                                                                                                                    |
| **`0x03`**      | `CLK_MGR3`        | `0x10`             | Single-speed clock mode; ADC oversampling ratio config.                                                                                                 |
| **`0x04`**      | `CLK_MGR4`        | `0x20`             | DAC oversampling ratio ($OSR = 32$) matched for 16 kHz sample rate.                                                                                     |
| **`0x05`**      | `CLK_MGR5`        | `0x00`             | DAC and ADC digital clock dividers set to 1.                                                                                                            |
| **`0x06`**      | `CLK_MGR6`        | `0x03`             | BCLK divider = 4 (value 3); normal SCLK polarity.                                                                                                       |
| **`0x07`**      | `CLK_MGR7`        | `0x00`             | Master LRCK divider high byte.                                                                                                                          |
| **`0x08`**      | `CLK_GATE`        | `0xFF`             | Master LRCK divider low byte (`0xFF`) / digital clock gating active.                                                                                    |
| **`0x09`**      | `SDP_IN`          | `0x0C`             | DAC serial port: Left-channel data (`SEL=0`), unmuted (`MUTE=0`), 16-bit word length (`WL=3`), Philips $I^2S$ format (`FMT=0`).                         |
| **`0x0A`**      | `SDP_OUT`         | `0x0C`             | ADC serial port unmuted and configured for 16-bit $I^2S$ matching SDP_IN.                                                                               |
| **`0x0B`**      | `PWR_UP_A`        | `0x00`             | Power-up stage A timing set to immediate.                                                                                                               |
| **`0x0C`**      | `SYSTEM_0C`       | `0x00`             | DAC input routing default (SDP In Left to DAC).                                                                                                         |
| **`0x0D`**      | `SYS_PWR_ANA`     | `0xFA` then `0x01` | **Critical fix.** `0xFA` during open pre-charges $C_{VMID}$; `0x01` powers on analog reference and enables low-impedance mid-rail ($V_{DDA}/2$) buffer. |
| **`0x0E`**      | `SYS_PGA_MOD`     | `0x02`             | Analog bias and VROI reference active (`0x02`); microphone PGA and ADC modulator powered down.                                                          |
| **`0x0F`**      | `SYS_LP_MOD`      | `0x80`             | Subsystem low-power default: Bit 7 (`LPDAC = 1`) enables low-power DAC mode; noise floor difference through NS4168 is negligible while saving power. |
| **`0x10`**      | `SYS_BIAS`        | `0x1F`             | Analog bias current generator adjustment; delivers nominal internal reference current.                                                                  |
| **`0x11`**      | `SYS_VMID`        | `0x7F`             | VMID buffer impedance and filter settings; filters mid-rail reference through external $C_{VMID}$.                                                      |
| **`0x12`**      | `DAC_PWR`         | `0x00`             | DAC analog power stage ON (`PDN_DAC = 0`).                                                                                                              |
| **`0x13`**      | `SYS_PWR3`        | `0x10`             | Internal analog reference bias generator configuration.                                                                                                 |
| **`0x14`**      | `ADC_PWR`         | `0x1A`             | Internal bias termination for ADC input network (keeps microphone input silent without bus hum).                                                        |
| **`0x15`**      | `ADC_GAIN`        | `0x40`             | ADC PGA gain / ramp reference baseline.                                                                                                                 |
| **`0x16`**      | `ADC_VOL`         | `0x24`             | ADC volume scale baseline.                                                                                                                              |
| **`0x17`**      | `ADC_ALC`         | `0xBF`             | Internal analog ALC calibration register (prevents bias drift).                                                                                         |
| **`0x1B`**      | `ADC_HPF1`        | `0x0A`             | ADC HPF stage 1 coefficient.                                                                                                                            |
| **`0x1C`**      | `ADC_HPF2`        | `0x6A`             | ADC HPF stage 2 and equalizer coefficient.                                                                                                              |
| **`0x31`**      | `DAC_MUTE`        | `0x00` / `0x60`    | DAC DSM/DEM unmute (`0x00`) during playback; soft mute (`0x60`) during idle.                                                                            |
| **`0x32`**      | `DAC_VOL`         | `0xBF`             | DAC digital volume attenuation (nominal unity gain $0\text{ dB} = \text{0xBF}$; perceptual table maps to this register).                                |
| **`0x37`**      | `DAC_RAMP`        | `0x08`             | **Silicon Errata:** Mandatory `0x08` write. Bypasses uncalibrated digital EQ block and disables volume fade ramp. Datasheet erroneously claims EQ defaults to disabled. |
| **`0x44`**      | `GPIO_CFG`        | `0x08` then `0x58` | Silicon errata noise filter lock (written `0x08` twice), then internal routing set to `0x58`.                                                           |
| **`0x45`**      | `GPIO_PULL`       | `0x00`             | Internal I2S clock line pull-up/pull-downs disabled.                                                                                                    |

---

## 4. Power Management & Sleep Gating Policy

### 4.1 Unattended Wake Isolation (<1 µA Invariant)
To prevent quiescent current dissipation and thermal contamination of the enclosure:
- **Unattended Periodic Wakes (RTC Countdown Timer):**
  - The ES8311 codec and NS4168 amplifier are **never initialized or taken out of standby**.
  - `sub_audio_init()` is strictly bypassed during Flow A and unattended Flow B display refreshes.
  - The entire audio subsystem remains in low-leakage hardware standby (<1.0 µA).
- **Interactive User Wakes (Cold Boot or Physical Button Tap):**
  - When the user presses `BOOT` or `POWER` to interact with the device, `is_user_wake` is asserted.
  - `sub_audio_init()` executes to configure clock dividers and prepare the FreeRTOS audio worker task.

### 4.2 Volume Initialization Contract
- The internal volume variable `s_volume_pct` is initialized to `0` (muted / unconfigured).
- Upon user wake, volume is configured strictly from `lifecycle.presentation.volume_pct`.
- Hardcoded fallback defaults (e.g. `50%` or `60%`) have been removed; audio levels are contractual and developer-defined.

### 4.3 Hardware & Silicon Errata References
- **Register 0x37 Digital Equalizer Bypass:** Writing `0x08` to Register `0x37` is required to disable the volume fade ramp and bypass the uncalibrated hardware EQ filter. For detailed silicon defect analysis, see [`ERRATA.md` ERR-S2](../../ERRATA.md#err-s2-es8311-register-0x37-digital-equalizer-bypass--low-power-default).
- **Shared I2C Bus Power-Gating Hazard:** For physical defect analysis on keeping `PA_EN` energized, see [`ERRATA.md` Errata E4](../../ERRATA.md#errata-e4-audio-codec-power-gating-disrupts-shared-i2c-bus).
