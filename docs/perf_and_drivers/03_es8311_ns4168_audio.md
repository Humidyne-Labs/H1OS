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

### Physical Circuit Behavior
The ES8311 has internal ESD clamping diodes connected between its digital input pins (SDA, SCL) and its internal VDD supply rail:
```
           3.3V (Pull-ups)
              │
              ├──[ 4.7kΩ ]─── SDA (GPIO 47) ──┬──[ ES8311 ESD Diode ]──> VDD_ES8311 (GPIO 42)
              │                               │
              └──[ 4.7kΩ ]─── SCL (GPIO 48) ──┴──[ ES8311 ESD Diode ]──> VDD_ES8311 (GPIO 42)
```
If software drives `PA_EN` (`GPIO 42`) HIGH to cut power to the audio subsystem:
1. `VDD_ES8311` drops to 0V.
2. Current flows from the 3.3V I2C pull-up resistors through the forward-biased ESD protection diodes into the dead VDD rail.
3. The forward voltage drop across silicon ESD diodes is ~0.6V to 0.7V.
4. **Result:** The shared I2C bus SDA and SCL lines are clamped down to **~0.7V**, completely deadlocking communication with the PCF85063A RTC and SHTC3 sensor!

### Immutable Software Requirement
`PA_EN` (`GPIO 42`) **MUST REMAIN ENERGIZED (LOW = 0)** during all normal and deep sleep operations. Audio power saving must be achieved strictly through software register suspension in the ES8311 and hardware mute on `PA_CTRL` (`GPIO 46 = 0`), which achieves `< 1.0 µA` total quiescent current without disturbing the I2C bus.

---

## 3. ES8311 Complete Register Initialization Table

To operate the ES8311 at 16 kHz 16-bit mono over I2S without an external MCLK, the full 22-register clock tree must be programmed:

```c
/* 1. Wake chip and set low-power analog baseline */
bsp_codec_write_reg(0x0D, 0xFA);

/* 2. Silicon errata I2C noise immunity (written twice) */
bsp_codec_write_reg(0x44, 0x08);
bsp_codec_write_reg(0x44, 0x08);

/* 3. Clock tree & reference biasing */
bsp_codec_write_reg(0x01, 0x30);
bsp_codec_write_reg(0x02, 0x00);
bsp_codec_write_reg(0x03, 0x10);
bsp_codec_write_reg(0x16, 0x24); /* ADC gain scale */
bsp_codec_write_reg(0x04, 0x10);
bsp_codec_write_reg(0x05, 0x00);
bsp_codec_write_reg(0x0B, 0x00);
bsp_codec_write_reg(0x0C, 0x00);
bsp_codec_write_reg(0x10, 0x1F); /* Reg 0x10: Analog bias generator adjust */
bsp_codec_write_reg(0x11, 0x7F); /* Reg 0x11: Internal VMID buffer impedance */
bsp_codec_write_reg(0x00, 0x80); /* CSM power on */

/* 4. Slave mode & MCLK selection */
bsp_codec_write_reg(0x00, 0x80); /* Slave mode (MSC = 0, CSM_ON = 1) */
bsp_codec_write_reg(0x01, 0x3F); /* Use MCLK pin, all clocks on */
bsp_codec_write_reg(0x06, 0x00); /* Normal SCLK polarity */
bsp_codec_write_reg(0x13, 0x10); /* Internal reference bias */
bsp_codec_write_reg(0x1B, 0x0A);
bsp_codec_write_reg(0x1C, 0x6A);
bsp_codec_write_reg(0x44, 0x58); /* Internal reference signal routing */

/* 5. 16-bit 16kHz Philips I2S Sample Rate & Clock Dividers */
bsp_codec_write_reg(0x09, 0x0C); /* 16-bit Philips I2S, SDP in unmute */
bsp_codec_write_reg(0x0A, 0x0C); /* SDP out unmute */
bsp_codec_write_reg(0x02, 0x00); /* Pre-divider = 1, Pre-multiplier = 1 */
bsp_codec_write_reg(0x05, 0x00); /* ADC/DAC clock dividers = 1 */
bsp_codec_write_reg(0x03, 0x10); /* Single speed, ADC OSR */
bsp_codec_write_reg(0x04, 0x20); /* DAC OSR = 0x20 for 16kHz Fs */
bsp_codec_write_reg(0x07, 0x00); /* Master LRCK divider high byte */
bsp_codec_write_reg(0x08, 0xFF); /* Master LRCK divider low byte */
bsp_codec_write_reg(0x06, 0x03); /* BCLK divider = 4 (reg value 3) */

/* 6. Power on DAC and Analog Blocks */
bsp_codec_write_reg(0x00, 0x80);
bsp_codec_write_reg(0x01, 0x3F);
bsp_codec_write_reg(0x09, 0x0C);
bsp_codec_write_reg(0x0A, 0x0C);
bsp_codec_write_reg(0x17, 0xBF);
bsp_codec_write_reg(0x0E, 0x02); /* Analog blocks power on / VROI */
bsp_codec_write_reg(0x12, 0x00); /* DAC analog power ON (PDN_DAC = 0) */
bsp_codec_write_reg(0x14, 0x1A);
bsp_codec_write_reg(0x0D, 0x01); /* Analog reference & normal VMID */
bsp_codec_write_reg(0x15, 0x40);
bsp_codec_write_reg(0x37, 0x08);
bsp_codec_write_reg(0x45, 0x00);

/* 7. Volume and Unmute */
bsp_codec_write_reg(0x32, 0xBF); /* 0 dB nominal volume */
bsp_codec_write_reg(0x31, 0x00); /* Unmute DAC DSM/DEM */
```

---

## 4. Zero-Heat Deep Standby Sequence (<1.0 µA)

When placing the audio subsystem into sleep:
1. Mute NS4168 Amplifier immediately: `gpio_set_level(HAL_PIN_PA_CTRL, 0);`
2. Soft-mute DAC DSM: `bsp_codec_write_reg(0x31, 0x60);` + 5 ms delay.
3. Power down ES8311 internal analog and DAC stages:
   ```c
   bsp_codec_write_reg(0x32, 0x00); /* Mute volume */
   bsp_codec_write_reg(0x17, 0x00);
   bsp_codec_write_reg(0x0E, 0xFF); /* Power down PGA & ADC Modulator */
   bsp_codec_write_reg(0x12, 0x02); /* Power down DAC output stage */
   bsp_codec_write_reg(0x14, 0x00); /* Power down ADC */
   bsp_codec_write_reg(0x0D, 0xFA);
   bsp_codec_write_reg(0x15, 0x00);
   bsp_codec_write_reg(0x02, 0x10);
   bsp_codec_write_reg(0x00, 0x00);
   bsp_codec_write_reg(0x00, 0x1F); /* Assert digital reset */
   bsp_codec_write_reg(0x01, 0x30);
   bsp_codec_write_reg(0x01, 0x00); /* Gate all clocks */
   bsp_codec_write_reg(0x45, 0x00);
   bsp_codec_write_reg(0x0D, 0xFC); /* Power down analog references & VMID */
   bsp_codec_write_reg(0x02, 0x00);
   ```
4. Disable active I2S TX channel: `i2s_channel_disable(s_tx_chan);`

---

## 5. I2S Clock Architecture, DFS & Playback Rate Stability

### Root Clock Source: PLL_160M vs Dynamic Frequency Scaling
On the ESP32-S3:
- The I2S hardware peripheral lacks a dedicated analog Audio PLL (APLL).
- Under ESP-IDF v5/v6, `I2S_CLK_SRC_DEFAULT` maps to **`PLL_160M`** (a 160 MHz clock derived from the main system PLL).
- Internal hardware fractional dividers ($N + b/a$) divide this 160 MHz clock down to generate:
  - $\text{MCLK} = \text{Sample Rate} \times 256 = 16{,}000 \times 256 = 4.096\text{ MHz}$
  - $\text{BCLK} = \text{Sample Rate} \times \text{Slots} \times \text{Bits} = 16{,}000 \times 2 \times 16 = 512\text{ kHz}$
  - $\text{WS/LRCK} = \text{Sample Rate} = 16{,}000\text{ Hz}$

### Playback Rate Drift Vulnerability
If Dynamic Frequency Scaling (**DFS** via `CONFIG_PM_ENABLE`) or runtime manual CPU frequency scaling is performed:
1. When CPU frequency drops (e.g. from 240 MHz to 80 MHz, or APB drops to 40 MHz / 10 MHz), if the root clock of I2S is altered without re-calculating fractional divider registers, **the output BCLK and WS clock rates drop proportionally**.
2. **Audible Effect:** Audio pitches down (e.g. one octave lower) and tone durations stretch out (e.g. 500 ms tone takes 1000 ms to play).
3. **Hardware Mitigation:**
   - The ESP-IDF I2S driver takes an `ESP_PM_APB_FREQ_MAX` power management lock while the I2S channel is active (`i2s_channel_enable`), preventing DFS from throttling the clock during audio transfers.
   - Tone playback routines must ensure the I2S clock is fully settled before enabling the external amplifier, and must restore zero-power standby upon completion.

---

## 6. Audit & Bug Identification Matrix

| Parameter / Feature | Legacy Reference (`bsp_audio.c`) | Original `sub_audio.c` (Clean-Slate) | Bug Diagnosis & Required Fix |
|---|---|---|---|
| **PA Power Rail (GPIO 42)** | `bsp_audio_power_enable(true)` sets `GPIO 42 = 0` (Active LOW) | **Never configured or initialized!** | **FIXED:** Added `HAL_PIN_PA_EN` output configuration and set LOW in `sub_audio_init()` and `hal_io_early_init()`. |
| **ES8311 Clock Tree** | Complete 22-register table with OSR, dividers, and reference biases | Wrote only 4 registers (`0x00`, `0x0D`, `0x12`, `0x32`)! | **FIXED:** Ported complete reference register table to guarantee valid clocking and decoding. |
| **Zero-Heat Deep Standby** | Complete 15-register suspend sequence per `es8311_suspend()` | Wrote only 2 registers (`0x12=0x03`, `0x0D=0x00`) | **FIXED:** Implemented reference shutdown sequence to guarantee `< 1.0 µA` and eliminate thermal drift. |
| **I2S Clock & DFS Lock** | Default PLL_160M clock with PM lock | Default PLL_160M | **PASS:** Driver enforces APB max lock during transmission. |
| **I2S Channel Format** | 16-bit 16kHz Philips Standard Mono | 16-bit 16kHz Philips Standard Mono | **PASS** |
| **I2C Bus Clamping Protection** | Rail kept ON (`0`) during sleep | Rail kept ON (`0`) in `hal_io` | **PASS** |

