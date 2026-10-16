# Everest Semiconductor ES8311 & NS4168 Audio Subsystem

## 1. Physical Specifications & Hardware Architecture

- **Codec IC:** Everest Semiconductor ES8311 Low-Power Audio Codec
- **Amplifier IC:** Nuvoton / National NS4168 3W Mono Class-D Audio Power Amplifier
- **Control Interface:** Shared Master I2C (`I2C_NUM_0`, 7-Bit Address: `0x18`)
- **Digital Audio Interface:** I2S0 Master Mode (Standard Philips Format)
  - Bit Clock (BCLK): `GPIO 21`
  - Word Select / LR Clock (LRCK): `GPIO 45`
  - Serial Data Out / DSDIN: `GPIO 40`
  - Master Clock (MCLK): Unused (Codec derives clock internally from BCLK)
- **Power & Control Pins:**
  - `PA_EN` (`GPIO 42`): Audio Subsystem Power Rail (Active LOW: `0 = Power ON`, `1 = Power OFF`)
  - `PA_CTRL` (`GPIO 46`): NS4168 Amplifier Enable / Mute (Active HIGH: `1 = Amp Enabled`, `0 = Muted / Shutdown`)

---

## 2. Electrical Invariant: The ESD Diode Clamping Hazard

### Physical Circuit Behavior & Link to Errata E4

The ES8311 has internal ESD clamping diodes connected between its digital input pins (SDA, SCL) and its internal VDD supply rail. Driving `PA_EN` (`GPIO 42`) HIGH to cut power to the audio subsystem causes current to flow from the 3.3V I2C pull-ups through the forward-biased ESD protection diodes into the dead VDD rail, clamping the shared I2C bus down to **~0.7V** and freezing the entire bus.

For detailed schematic analysis and PCB Rev B redesign guidelines, see [`ERRATA.md` Errata E4](../../ERRATA.md#e4-es8311-esd-diode-i2c-bus-clamping).

### Immutable Software Requirement

`PA_EN` (`GPIO 42`) **MUST REMAIN ENERGIZED (LOW = 0)** during all normal and deep sleep operations. Audio power saving must be achieved strictly through software register suspension in the ES8311 (`0x0D=0xFC`) and hardware mute on `PA_CTRL` (`GPIO 46 = 0`), without disturbing the shared I2C bus.

---

## 6. Audit & Bug Identification Matrix

| Parameter / Feature             | Legacy Reference (`bsp_audio.c`)                                    | Original `sub_audio.c` (Clean-Slate)                     | Bug Diagnosis & Required Fix                                                                                       |
| ------------------------------- | ------------------------------------------------------------------- | -------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------ |
| **PA Power Rail (GPIO 42)**     | `bsp_audio_power_enable(true)` sets `GPIO 42 = 0` (Active LOW)      | **Never configured or initialized!**                     | **FIXED:** Added `HAL_PIN_PA_EN` output configuration and set LOW in `sub_audio_init()` and `hal_io_early_init()`. |
| **ES8311 Clock Tree**           | Complete 22-register table with OSR, dividers, and reference biases | Wrote only 4 registers (`0x00`, `0x0D`, `0x12`, `0x32`)! | **FIXED:** Ported complete reference register table to guarantee valid clocking and decoding.                      |
| **Zero-Heat Deep Standby**      | Complete 15-register suspend sequence per `es8311_suspend()`        | Wrote only 2 registers (`0x12=0x03`, `0x0D=0x00`)        | **FIXED:** Implemented reference shutdown sequence to eliminate standby draw and thermal drift.                    |
| **I2S Clock & DFS Lock**        | Default PLL_160M clock with PM lock                                 | Default PLL_160M                                         | **PASS:** Driver enforces APB max lock during transmission.                                                        |
| **I2S Channel Format**          | 16-bit 16kHz Philips Standard Mono                                  | 16-bit 16kHz Philips Standard Mono                       | **PASS**                                                                                                           |
| **I2C Bus Clamping Protection** | Rail kept ON (`0`) during sleep                                     | Rail kept ON (`0`) in `hal_io`                           | **PASS**                                                                                                           |

## Register Map:

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
| **`0x0F`**      | `SYS_LP_MOD`      | `0x80`             | Subsystem low-power override: Bit 7 (`LPDAC = 1`) enables low-power DAC mode; other sub-blocks default.                                                 |
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
| **`0x37`**      | `DAC_RAMP`        | `0x08`             | Disables DAC EQ and/or fade in/out ramp rate. Datasheet/User Guide in repo has error, EQ Default = Disabled, Ramp Default = Disabled                                                           |
| **`0x44`**      | `GPIO_CFG`        | `0x08` then `0x58` | Silicon errata noise filter lock (written `0x08` twice), then internal routing set to `0x58`.                                                           |
| **`0x45`**      | `GPIO_PULL`       | `0x00`             | Internal I2S clock line pull-up/pull-downs disabled.                                                                                                    |

---

## 7. Power Management & Sleep Gating Policy

### 7.1 Unattended Wake Isolation (<1 µA Invariant)
To prevent quiescent current dissipation and thermal contamination of the enclosure:
- **Unattended Periodic Wakes (RTC Countdown Timer):**
  - The ES8311 codec and NS4168 amplifier are **never initialized or taken out of standby**.
  - `sub_audio_init()` is strictly bypassed during Flow A and unattended Flow B display refreshes.
  - The entire audio subsystem remains in low-leakage hardware standby (<1.0 µA).
- **Interactive User Wakes (Cold Boot or Physical Button Tap):**
  - When the user presses `BOOT` or `POWER` to interact with the device, `is_user_wake` is asserted.
  - `sub_audio_init()` executes to configure clock dividers and prepare the FreeRTOS audio worker task.

### 7.2 Volume Initialization Contract
- The internal volume variable `s_volume_pct` is initialized to `0` (muted / unconfigured).
- Upon user wake, volume is configured strictly from `lifecycle.presentation.volume_pct`.
- Hardcoded fallback defaults (e.g. `50%` or `60%`) have been removed; audio levels are contractual and developer-defined.

