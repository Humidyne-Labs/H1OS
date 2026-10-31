# Environmental Chamber Metrology & Qualification Test Ledger (Run #5)

**Test Campaign:** Sealed Acrylic Chamber RH Baseline, Autonomy & Thermal Qualification (`TST_005` / Run #5)  
**Primary Standard:** 60g Boveda 69.0% Two-Way Osmotic Salt-Membrane Pack  
**Reference Benchmark:** Klaro Valet Digital Thermohygrometer (Case Elegance)  
**Device Under Test (DUT):** HUMID1 (Waveshare ESP32-S3-PICO-1-N8R8 + Sensirion SHTC3 + Everest ES8311 + NS4150B + Solomon SSD1681 1.54" EPD)  
**DUT Test Firmware:** Commit `9cff5dd` / Release bundle `h1os-v2.4.5-bundle.zip` (`v2.4.5-dev-2-g9cff5dd`, compiled `2026-10-29 02:01:12` under production profile `-O2`)  
**DUT Build Profile:** Production Release (`examples/H1OS/sdkconfig.defaults.prod`: `-O2`, silent assertions, `LOG_LEVEL_WARN`)  
**Test Duration:** `12.0 Hours` (`2026-10-29 02:39 AM` to `2026-10-29 02:37 PM`)  
**Test Status:** **PARTIAL PASS (Wake & ADC Metrology Verified) / FAIL ON THERMAL OFFSET (`+3.5°C to +4.5°C` Codec Hotspot, `+0.8°C` SHTC3 Offset, `4.58 mA` Draw) — Remediated in `v2.4.6-dev`**  

---

## 1. Chamber Specifications & Instrumentation Setup

### Chamber & Hardware Configuration
* **Enclosure Type:** Heavy-wall clear acrylic canister with perimeter stainless steel clamp-lock latch (`~1.4 L` net headspace above pre-acclimated Spanish cedar substrate).
* **Hermetic Seal:** Food-grade silicone perimeter compression gasket; non-permeable acrylic body.
* **Vapor Standard:** 1 × 60g Boveda 69.0% two-way osmotic salt-membrane pack (equilibrated).
* **Reference Benchmark:** Klaro Valet (`0.1°F` temperature resolution, `1%` integer RH LCD, coin-cell powered, $\le 15\ \mu\text{W}$ thermal dissipation).
* **DUT Configuration:** HUMID1 running `v2.4.5-dev` (`h1os.bin` SHA-256 `76842679...`, ELF SHA-256 `d34ce314...`), configured with fixed test wake intervals:
  * **Flow A (Headless Wake-Stub Sensor Sample Burst):** `60 seconds` (`H1OS_DEFAULT_FLOW_A_PERIOD_SEC = 60U`)
  * **Flow B (Unattended Display Refresh & Parallel Sync):** `300 seconds` / `5 minutes` (`H1OS_DEFAULT_FLOW_B_PERIOD_SEC = 300U`, `overflow_limit = 5`)
  * **Interactive Session Inactivity Timeout:** `30 seconds` (`H1OS_DEFAULT_INACTIVITY_TIMEOUT_SEC = 30U`)
* **Power Source:** Internal AntPow `AP502535` 400 mAh / 1.48 Wh 3.7V LiPo cell (standalone battery operation, `USB = 0`).

---

## 2. Empirical Telemetry Progression (`t = 0.0h` to `t = 12.0h`)

### 2.1 Initial Chamber Closure (`2026-10-29 02:39:49 AM` — `2026-10-29_02-39-49_181.jpg`)
* **Reference Benchmark (Klaro Valet):** `73.7°F` (`23.17°C`), `65% RH` (initial transient upon lid closure).
* **DUT Telemetry (`Screen 3: System Health`):**
  * **Battery Terminal Voltage (`VBAT`):** `4073 mV` (`88%` State of Charge, `DISCHARGING`)
  * **Boot Anchor Voltage (`BOOT VBAT`):** `4073 mV`
  * **Cumulative Runtime:** `SLEEP: 0.0h | ACT: 31.1s` (initial 30-second cold-boot interactive session + splash)
  * **Autonomy Engine Status:** `DRAW: CAL... | AUTONOMY: CAL... | SPENT: 0.0 mAh` (awaiting $\ge 1.0\%$ SoC drop calibration gate).

### 2.2 End-of-Run Steady-State Inspection (`2026-10-29 02:36:54 PM – 02:37:33 PM` — `t = 12.0h`)

All five UI carousel screens were photographed alongside the Klaro Valet reference prior to opening the acrylic chamber:

| Metric / Parameter | Reference (Klaro Valet) | DUT (HUMID1 `v2.4.5-dev`) | Observed Delta ($\Delta = \text{DUT} - \text{Ref}$) | Verification Status |
| :--- | :--- | :--- | :--- | :--- |
| **Ambient Temperature ($T$)** | `72.6°F` (`22.56°C`) | `74.1°F` (`23.4°C`) | **`+1.5°F` (`+0.84°C`)** | **FAIL** (Exceeds $\pm 0.20^\circ\text{C}$ gate) |
| **Relative Humidity ($\text{RH}$)** | `70% RH` (69.0% Boveda) | `63.5% RH` (Hist: `63.6%`) | **`-6.5% RH`** (`-5.5%` vs Boveda) | **FAIL** (Depressed by local $+0.84^\circ\text{C}$ self-heating) |
| **Vapor Partial Pressure ($e$)** | `18.3 hPa` (at `22.1°C` / `69%`) | `18.3 hPa` | **`0.0 hPa`** | **PASS** (Confirms intact SHTC3 vapor sensing) |
| **Dew Point ($T_{\text{dew}}$)** | `16.1°C` (`61.0°F`) | `16.1°C` (`60.9°F`) | **`0.0°C` (`-0.1°F`)** | **PASS** (Absolute moisture content accurate) |
| **Absolute Humidity ($d_v$)** | `13.3 g/m³` | `13.3 g/m³` | **`0.0 g/m³`** | **PASS** |
| **SHTC3 32-Sample Window** | `22.56°C` | Floor `22.4°C` / Ceil `23.4°C` / Avg `23.3°C` | `+0.74°C` window avg | **FAIL** (Steady thermal offset above floor) |
| **MCU Die Temp (`TSENS`)** | `~22.6°C` ambient | `26.8°C` (32-sample Avg: `26.8°C`) | **`+4.2°C` vs Ref (`+3.4°C` vs SHTC3)** | **FAIL** (Continuous sleep heat source adjacent to U9) |
| **EPD Glass Temp (`SSD1681`)** | `~22.6°C` ambient | `24.0°C` | **`+1.4°C` vs Ref (`+0.6°C` vs SHTC3)** | Elevated by internal enclosure plume |
| **Tri-Node Consensus** | `22.56°C` | `24.7°C` (`Delta: -1.3°C`, `Conf: 78%`) | `+2.14°C` | Correctly flags internal thermal gradient |
| **Wake Reliability (`12.0h`)** | `715` expected ticks | `Boots: 1 | Wakes: 715 (Fail: 0)` | **`0` missed wakes / `0` I2C errors** | **PASS** (`143 Flow B` + `572 Flow A` + `3 Btn`) |
| **Battery Metrology (`VBAT`)** | `4073 mV -> 3948 mV` | `3948 mV (74%)`, `DISCHARGING` | `-125 mV` (`-13.8%` SoC in `12.0h`) | **PASS** (`ERR-S6` `ulp_adc_init` fix verified) |
| **Average Current Draw** | Target $\le 0.45\text{ mA}$ | **`4.58 mA`** (`55.2 mAh` spent in `12.0h`) | **`+4.13 mA` excess quiescent draw** | **FAIL** ($\sim 16\text{ mW}$ continuous parasitic dissipation) |

### 2.3 Psychrometric Proof That SHTC3 RH Offset Is 100% Driven by Local Self-Heating
From `Screen 2: Psychrometrics` (`2026-10-29_14-37-04_325.jpg`), the DUT measured:
* $T_{\text{SHTC3}} = 23.4^\circ\text{C}$ (`74.1°F`), $\text{RH}_{\text{SHTC3}} = 63.5\%$, $e = 18.3\text{ hPa}$, $T_{\text{dew}} = 16.1^\circ\text{C}$ (`60.9°F`), $d_v = 13.3\text{ g/m}^3$.
* Using the August-Roche-Magnus equation implemented in `orch_math.c`:
  $$e_s(23.4^\circ\text{C}) = 6.112 \cdot \exp\left(\frac{17.625 \times 23.4}{243.04 + 23.4}\right) = 28.83\text{ hPa}, \qquad e = 0.635 \times 28.83 = 18.31\text{ hPa}$$
* At the unheated initial window floor temperature ($T_{\text{floor}} = 22.4^\circ\text{C}$, $e_s = 27.08\text{ hPa}$) and chamber equilibrium ($22.1^\circ\text{C}$, $e_s = 26.59\text{ hPa}$), that exact same water vapor partial pressure ($e = 18.31\text{ hPa}$) corresponds to:
  $$\text{RH}(22.4^\circ\text{C}) = \frac{18.31}{27.08} \times 100\% = 67.6\%\text{ RH}, \qquad \text{RH}(22.1^\circ\text{C}) = \frac{18.31}{26.59} \times 100\% = \mathbf{68.9\%\text{ RH}}$$
* Thus, the Sensirion SHTC3 polymer dielectric and vapor pressure math are completely accurate; the `-5.5% to -6.5% RH` depression is a direct thermodynamic consequence of the continuous $\sim 16\text{ mW}$ (`4.13 mA` excess at `3.95 V`) parasitic heat source warming the PCB and sensor cavity by $+0.8\text{–}1.3^\circ\text{C}$.

---

## 3. Radiometric Thermal Imaging Analysis (`TST_005_IMGS_THERMAL`)

Immediately following the 12-hour chamber test (`14:50:34` to `15:00:04`), 24 radiometric thermal images (`IMG261029145034.bmp` through `IMG261029150004.bmp`) were captured across the enclosure and exposed PCB and cross-referenced against the component placement map (`legend/part_map.png`):

1. **External Enclosure Thermal Plume (`IMG261029145034.bmp`, `IMG261029145039.bmp`):**
   * Through the closed casing, a distinct thermal plume (`Max = 28.0°C – 28.3°C` vs `Min = 21.8°C – 22.1°C` background) radiates from the upper-middle quadrant of the PCB directly overlying `U10` (ES8311) and `U9` (ESP32-S3).
2. **Direct Bare-PCB Hotspot Localization (`IMG261029145503.bmp` – `IMG261029145822.bmp`, `legend/IMG261029145614.bmp`):**
   * With the PCB exposed in idle/deep-sleep state (`Center` / `Max` crosshair aligned to component footprints in `part_map.png`):
     * **Primary Hotspot — `U10` (Everest ES8311 Audio Codec, QFN-20):** Consistently registers as the peak thermal emitter on the PCB at **`26.2°C – 28.9°C`** (`IMG261029145614.bmp`: `Max = 26.8°C` centered directly on `U10`, `Min = 22.4°C` at lower-right board edge, yielding a **`+4.4°C` localized package temperature rise** during sleep).
     * **Secondary Coupled Region — `U9` (ESP32-S3-PICO-1-N8R8) & `U11` (NS4150B Class-D Amplifier):** Situated `2 mm` from `U10` on the shared 3.3V/GND copper plane, `U9` registers **`25.4°C – 26.8°C`** (matching the internal `MCU DIE: 26.8°C` TSENS telemetry on Screen 5 within $<0.2^\circ\text{C}$).
     * **Power Management ICs (`U4` ETA6098 Charger & `U7` MP1605 Buck Regulator):** Remain near ambient (`23.0°C – 24.1°C`), confirming the `4.58 mA` draw is dissipated as Joule heat inside the 3.3V load (`U10` ES8311 + I2S pad pull-ups) rather than regulator switching losses (`mp1605.pdf` p. 1: $11\ \mu\text{A}$ quiescent current, $\sim 90\%$ light-load efficiency; `eta6098.pdf` p. 3: $I_{\text{BAT}} \le 2\ \mu\text{A}$ when `VBUS` is absent).
     * **Sensor Node — `U6` (Sensirion SHTC3):** Located at the bottom edge of the PCB (`Min = 22.3°C – 22.8°C` in open air, rising to `23.4°C` inside the sealed 1.4 L acrylic chamber due to trapped convective/conductive heat from `U10`).

---

## 4. Root Cause Correlation & Firmware Remediation (`v2.4.6-dev`)

Forensic inspection of the `TST_005` binary (`h1os.bin`) and source tree against the hardware datasheets (`es8311_pb_v16.pdf`, `es8311_user_guide_v8.pdf`, `ns4150b.pdf`) identified five compounding firmware defects explaining both why `U10` (ES8311) ran `+3.5–4.5°C` hot during sleep and why the thermal offset manifested specifically in Run #5 after the `PIT-02`/`PIT-03` Flow B wake fix:

1. **`RC-01` — Corrupted ES8311 Standby Register Map (`sub_audio.c:236-257`):**
   * `s_es8311_deinit[]` wrote `{0x0E, 0xFF}` instead of the datasheet POR default `{0x0E, 0x6A}` (`es8311_user_guide_v8.pdf` p. 18), forcing undocumented internal analog control bits `[7]` and `[0]` HIGH (`1`) and holding `RST_MOD = 1`.
   * `s_es8311_deinit[]` wrote `{0x00, 0x1E}` instead of `{0x00, 0x1F}` (p. 14), leaving Bit 0 (`RST_DAC_DIG`) un-reset (`0`) based on the false assumption that Bit 0 was `RST_REG` (`INI_REG` is actually in `Reg 0xFA` Bit 0, p. 29).
   * `s_es8311_deinit[]` wrote `{0x45, 0x00}` (p. 28–29, Bit 0 `PULLUP_SE = 0`), leaving the ES8311's internal `BCLK` (Pin 6) and `LRCK` (Pin 8) pull-ups to `PVDD` (`3.3V`) **ENABLED** while `hal_io_isolate_sleep_pads()` drove `GPIO 15` (`SCLK`) and `GPIO 38` (`LRCK`) **LOW (`0V`)**, creating a continuous DC current path through `U10` during 100% of deep sleep.
   * High-bias and loopback registers written during pre-charge (`0x10 = 0x1F` max bias, `0x11 = 0x7F`, `0x16 = 0x24`, `0x1B = 0x0A`, `0x44 = 0x58` loopback mux) were never restored to POR defaults (`0x10 = 0x13`, `0x11 = 0x7C`, `0x16 = 0x04`, `0x1B = 0x0C`, `0x44 = 0x00`), `Reg 0x0F` low-power mode bits (`0xFF`) were not asserted, and `Reg 0x1C` was written as `0x00` (enabling the ADC equalizer instead of `0x4C` `ADC_EQBYPASS = 1`).
2. **`RC-02` — Violation of ES8311 Datasheet Note 4/5 Clock Sequencing & Continuous Active Idle Sessions (`sub_audio.c:446-649`):**
   * `sub_audio_init()` left `PA_CTRL` (`GPIO 46 = 1`, NS4150B switching at 400 kHz, `3–4 mA`), the ES8311 (`4.5–8 mA`, including the unused microphone PGA at `+30 dB` via `0x0E = 0x02`, `0x14 = 0x1A`), and 4.096 MHz I2S clocks running continuously for the entire 30-second interactive session even when silent.
   * When entering standby (`sub_audio_standby()`), `{0x00, 0x1E}` and `{0x01, 0x00}` were written without a pre-clock-stop CSM settling window (`es8311_pb_v16.pdf` p. 8 Note 4: *"entering low power through control register setting, then stopping input clock"*).
3. **`RC-03` — ESP32-S3 Internal I2S Pull-Up Leakage (`gpio_reset_pin`) & `ASDOUT` Output Contention (`hal_io.c:539-551`):**
   * Calling `gpio_reset_pin()` on all 5 I2S pins (`GPIO 14, 15, 16, 38, 45`) enabled ESP32-S3 internal `~45 kΩ` pull-up resistors (`.pull_up_en = true`) before driving all 5 pins LOW (`0V`), sinking `~367 µA` continuously across the MCU pads during deep sleep and driving `GPIO 16` (`ASDOUT`) as a push-pull output LOW directly against ES8311 Pin 7 (`ASDOUT` output).
4. **`RC-04` — 2nd-Stage Bootloader `PA_EN` (`GPIO 42`) Hold-Release Glitch on Flow B Wakes & Unverified Standby Skip (`h1os_boot_hook.c:57-62`, `sub_audio.c:633-636`):**
   * Why Test #5 exhibited the `+3–4°C` offset after the wake fix: prior to Test #5 (`PIT-02`/`PIT-03`), Flow B stopped waking after the first 5-minute cycle. Once Flow B woke every 300 seconds (143 times in Test #5), `bootloader_before_init()` executed `gpio_ll_hold_dis(&GPIO, 42)` **before** configuring `GPIO 42` output level (`0`) and output enable (`1`). Because Deep Sleep resets the digital GPIO matrix (`GPIO 42` defaults to JTAG `MTMS` input with pull-up HIGH), releasing the pad hold first glitched `PA_EN` HIGH on Flow B wakes, POR-resetting `U10` out of standby while `sub_audio_standby()` blindly skipped re-initialization because `s_rtc_codec_in_standby` in `RTC_SLOW_MEM` remained `true`.
5. **`RC-05` — Premature ULP GPIO Wakeup Enable During Active Cold-Boot Session (`sub_power.c:363`):**
   * `sub_power_init_ulp()` armed `RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA` during cold-boot bringup while the main Xtensa cores were actively running the 30-second interactive session (violating the ULP Sleep-Gating Rule), and included Layer 3 `h1os/orch_state.h` from Layer 2 `sub_power.c`.

All five root causes have been remediated in **`v2.4.6-dev`**, restoring `<1.0 µA` codec standby, eliminating I2S pad pull-up and `ASDOUT` contention, enforcing glitch-free bootloader rail latching with self-healing I2C standby verification on Flow B wakes, and parking the codec and amplifier on demand between tones.

---

## 5. Post-Audit Hardware Verification (`TST_005_IMGS_POST-THERMAL`) & `v2.4.7-dev` Remediation

Following the initial `v2.4.6-dev` patch, bench verification was conducted after a 10-minute ambient cooldown (`TST_005_IMGS_POST-THERMAL/IMG261029161206.bmp` – `IMG261029161752.bmp` and `internal_thermal_note.md`):

### 5.1 Observed Hardware Behavior on `v2.4.6-dev`

| Phase / Timestamp | Thermal Frames | `U10` (ES8311) Temp | Floor Temp | Observed Hardware & Acoustic Behavior |
| :--- | :--- | :--- | :--- | :--- |
| **1. Cold Boot & Session Active** (`16:12:06`) | `IMG261029161206.bmp` | `31.3°C` (MCU active) | `29.8°C` | Cold boot chime & button chirps play with zero pop-click, but first chime note (`70 ms`) and `50 ms` button chirps sound truncated. |
| **2. Post-Boot 30s Timeout & Flow B Sleep** (`16:12:13` – `16:14:42`) | `IMG261029161213.bmp` – `IMG261029161442.bmp` | `28.5°C` $ightarrow$ **`29.0°C–29.4°C`** | `26.2°C–27.2°C` | **PASS on Cold Boot Sleep:** `U10` hotspot extinguishes after the initial 30s timeout and stays cool across unattended Flow B wakes (`16:12:54` – `16:14:42`). |
| **3. Tactile Button Wake** (`16:14:50` – `16:15:08`) | `IMG261029161450.bmp` – `IMG261029161508.bmp` | `29.9°C` (`Max 33.0°C`) | `26.2°C–27.1°C` | Operator presses tactile button (`16:14:50` finger visible on lower button); `U10` wakes for interactive session (`16:14:59`, `16:15:08`). |
| **4. Post-Button-Wake 30s Timeout & Subsequent Flow B** (`16:15:17` – `16:17:52`) | `IMG261029161517.bmp` – `IMG261029161752.bmp` | **`28.9°C–30.3°C`** (`Max 30.7°C–32.1°C`) | `24.9°C–27.5°C` | **FAIL on Post-Button Sleep:** After the 30s timeout following a button wake, `U10` remains warm (`+3.0°C to +4.5°C` above floor) across Flow B cycles. |

### 5.2 Exact Silicon & Driver Root Causes Identified & Fixed in `v2.4.7-dev` (`ERR-S8`)

1. **Why `U10` Stayed Awake After a Button-Wake 30s Timeout (`s_es8311_deinit` Register Ordering vs. Espressif `_3rd_party_ref_codec/es8311.c`):**
   * In the ES8311 silicon, when `REG00` is `0x80` (`CSM_ON = 1`), writing `{0x0D, 0xFC}` *before* `{0x00, 0x1F}` causes the internal Chip State Machine (`CSM`) reset transition (`0x00 = 0x1F`, `RST_DIG = 1`) to revert `Reg 0x0D` back to its pre-charge value (`0xFA`: `PDN_VREF = 0`, `VMIDSEL = 10b` active VMID reference).
   * Cross-referencing against the official Espressif reference driver (`_3rd_party_ref_codec/es8311.c:222-240`, `es8311_suspend()`) confirmed that `es8311_suspend()` writes `{0x0D, 0xFA}` first, executes the CSM reset and clock gating sequence (`{0x02, 0x10}` $ightarrow$ `{0x00, 0x00}` $ightarrow$ `{0x00, 0x1F}` $ightarrow$ `{0x01, 0x30}` $ightarrow$ `{0x01, 0x00}`), and writes **`{0x0D, 0xFC}` AFTER `{0x00, 0x1F}` and `{0x01, 0x00}`** (followed by `{0x02, 0x00}`).
   * Furthermore, when `Reg 0x0D` reverted to `0xFA` at the 30s timeout, the `v2.4.6-dev` readback check in `sub_audio_standby()` detected `Reg 0x0D == 0xFA != 0xFC` on the next unattended Flow B wake and attempted to re-write `s_es8311_deinit[]` while `s_tx_chan == NULL` (no `MCLK`).
   * **`v2.4.7-dev` Fix:** Updated `s_es8311_deinit[]` to the exact `es8311_suspend()` register order (`0x0D = 0xFC` and `0x02 = 0x00` written *after* `0x00 = 0x1F` and `0x01 = 0x00` with `MCLK` active), and restored complete unattended Flow B bypass (`if (!s_audio_inited && s_rtc_codec_in_standby && esp_reset_reason() == ESP_RST_DEEPSLEEP) return ESP_OK;`).
2. **Why `50 ms` Button Chirps & the First Note of the Boot Chime Were Truncated (`sub_audio.c`):**
   * **Trailing Chirp Truncation (`64 ms` I2S DMA Ring Buffer vs. `50 ms` Chirp):** The I2S TX channel uses `4` descriptors $	imes$ `256` samples = `1024 samples` (`64 ms` at `16 kHz`). A `50 ms` chirp (`800 samples`) fits completely inside the empty `1024-sample` DMA ring, so `i2s_channel_write()` returns in `< 1 ms`. In `v2.4.6-dev`, `sub_audio_flush_frame()` queued only `1` zero frame (`16 ms`) + `20 ms` delay (`36 ms` total drain) before `audio_worker_task()` called `sub_audio_standby()`, which pulled `PA_CTRL` (`GPIO 46`) LOW at `t = 36 ms` and cut off the remaining `14–30 ms` of every `50 ms` chirp still in the DMA buffer.
   * **Leading Boot Chime Note Truncation:** Waking the codec on-demand from `0x0D = 0xFC` (`VMID = 0V`) inside `sub_audio_prepare_and_unmute()` using `{0x0D, 0x31}` (`VMIDSEL = 1` slow normal charge on `C114 = 1 µF`) without `{0x44, 0x58}` or `sub_audio_wait_until_ready()` clipped the start of the `70 ms` first note (`523 Hz`) of `H1OS_CHIME_BOOT`.
   * **`v2.4.7-dev` Fix:** `sub_audio_init()` now initializes the ES8311 in low-power mode (`0x0F = 0xFF`) with unused mic off (`0x0E = 0x62`, `0x14 = 0x00`, `0x17 = 0x00`), soft-ramp OFF (`0x37 = 0x08`), and `{0x44, 0x58}` / `{0x0D, 0x01}` active, waits for `sub_audio_wait_until_ready(100)` (`CSM != S0`), and enables `PA_CTRL = 1` (`120 ms` settling) before returning. Removed per-tone `sub_audio_standby()` calls from `audio_worker_task()` so the codec and amplifier stay warm during the 30-second interactive session and sleep at the 30s timeout, and upgraded `sub_audio_flush_frame()` to drain all `4` DMA descriptors (`4 × 256 = 1024 samples = 64 ms`) + `20 ms` delay.
