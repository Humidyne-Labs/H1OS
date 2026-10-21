# H1OS Full Repository Technical Audit Report

**Target Platform:** Waveshare ESP32-S3 ePaper 1.54" V2 (`ESP32-S3-PICO-1-N8R8`)  
**SDK & Middleware:** ESP-IDF v6.1 / LVGL v9.5  
**Scope:** Full-tree audit covering logical bugs, thermal & mathematical models, hardware register usage, ESP-IDF deprecations, architectural layer invariants (`A0`–`C4`), unused code/prototypes, and proposed fixes.

---

## 1. Investigation of Reported Hardware Quirks

### 1.1 Quirk #1: Why MCU Die Temperature (`mcu_tsens_centi_c`) Runs Consistently Lower Than SHTC3 & EPD Glass
You noted that the ESP32-S3 internal die temperature sensor consistently reads lower than both the SHTC3 and the SSD1681 e-Paper glass sensor—even though the MCU is not actively cooled. **There are two concrete hardware/mathematical bugs in `orch_wake_stub.c` and `orch_flow.c` causing this:**

#### A. Unconfigured `SENS_TSENS_DAC` & Clock Divider in `orch_wake_stub.c` (`lines 194–223`)
In `wake_stub_read_die_temp_centi_c()`, the wake stub powers up the SAR temperature sensor and triggers a raw conversion, then applies:
```c
int32_t t_centi = (((4386 * (int32_t)raw) - 205200) / 100) - (int32_t)cal_centi_c;
```
The constant `-205200` corresponds to `0.4386 * raw - 20.52°C`, which is the ESP32-S3 transfer equation **specifically when `DAC_offset = 0` (`SENS_TSENS_DAC = 15`, measurement range `-10°C to +80°C`) and `SENS_TSENS_CLK_DIV = 6`**.
- However, `wake_stub_read_die_temp_centi_c()` **never writes `SENS_TSENS_DAC` or `SENS_TSENS_CLK_DIV`** in `SENS_SAR_TSENS_CTRL2_REG` / `SENS_SAR_TSENS_CTRL_REG` before asserting `SENS_TSENS_POWER_UP`.
- Furthermore, in `sub_sensor_read_mcu_die_temp()` (`sub_sensor.c:160`), the ESP-IDF driver is configured with `TEMPERATURE_SENSOR_CONFIG_DEFAULT(-10, 50)`—which is a **completely different call-site configuration** that is never even invoked on cold boot!
- If `SENS_TSENS_DAC` is not explicitly set to `15` (`0x0F`) and `SENS_TSENS_CLK_DIV` to `6` in the wake stub, or if `SENS_TSENS_RESET` is not pulsed after enabling the clock gate (`SENS_TSENS_CLK_EN`), the SAR temperature oscillator runs unreset with default divider timings.

#### B. Sign Convention & Calibration Offset Application (`orch_flow.c:55–61` & `orch_wake_stub.c:218`)
In `orch_flow.c`:
```c
if (EFUSE.rd_sys_part1_data4.blk_version_major != 0) {
    uint32_t cal_temp = EFUSE.rd_sys_part1_data4.temp_calib;
    int32_t cal_deci_c = ((cal_temp & BIT(8)) != 0) ? -(int32_t)((uint8_t)cal_temp) : (int32_t)((uint8_t)cal_temp);
    st->tsens_cal_centi_c = (int16_t)(cal_deci_c * 10);
}
```
1. **Direct bitfield access vs. eFuse Calibration Scheme:** On ESP32-S3, `EFUSE.rd_sys_part1_data4.temp_calib` is a 9-bit signed magnitude value in `0.1°C` units, valid when `EFUSE.rd_repeat_data2.rpt4_reserved0` / calibration version is populated (`esp_efuse_rtc_calib_get_tsens_val()`).
2. **Downstream Cascade into Ambient Reconstruction (`orch_flow.c:180–204`):**
   Because `t_die` reads `1.5°C–4.0°C` lower than true ambient on many chips, look at what happens in `orch_flow_evaluate_ambient_selection()`:
   - **In Case A (`valid_trend < 2`):**
     ```c
     float min_ref = (t_glass < t_die) ? t_glass : t_die;
     t_amb = (min_ref < t_valid) ? min_ref : t_valid;
     ```
     Because `t_die` is biased **below** true ambient, `min_ref` always picks `t_die` instead of `t_valid` or `t_glass` during startup/unsettled wakes!
   - **In Case B (`window_avg_shtc3_c > window_avg_die_c + ORCH_LEAKAGE_MARGIN_C`):**
     Because `window_avg_die_c` runs perpetually lower than `window_avg_shtc3_c` even in complete thermal equilibrium, `window_avg_shtc3_c > window_avg_die_c + 0.30f` was **always true**! That explains why `orch_flow.c:38` had to be hacked from `0.30f` to `6.00f` (`#define ORCH_LEAKAGE_MARGIN_C 6.00f //0.30f`).
   - **Psychrometric RH Distortion (`orch_math_calc_psychrometrics`):**
     Whenever Case A or Case B selects the artificially low `t_die` as `t_amb`, `orch_math_calc_psychrometrics(t_valid, rh_valid, t_amb, ...)` computes actual vapor pressure $e$ using `t_valid` (SHTC3), and then divides by saturation vapor pressure $e_s(T_{\text{amb}})$ at the lower `t_die`. Because $e_s(T)$ drops by ~6.5% per `1°C`, a `2°C` low bias on `t_die` **artificially inflates reconstructed relative humidity (`RH_amb`) by +12% to +14% RH**!

#### C. Proposed Resolution for Quirk #1
1. **Explicitly configure and reset TSENS in `orch_wake_stub.c`:** Pulse `SENS_TSENS_RESET` in `SENS_SAR_TSENS_CTRL2_REG`, explicitly write `SENS_TSENS_DAC = 15` (`0x0F`, `-20.52°C` offset range) and `SENS_TSENS_CLK_DIV = 6` in `SENS_SAR_TSENS_CTRL_REG`, and increase the stabilization delay from `300 us` to `400 us`.
2. **Dynamic Self-Zeroing Baseline (`die_to_shtc3_tare_centi_c`):** In a closed-loop slow-moving telemetry system, after 3+ consecutive cold sleep wakes (`valid_trend >= 3` in Flow A, where the board has been asleep at `< 28 µA` for several minutes), the SHTC3 (`±0.2°C` factory accuracy) is at true ambient temperature, whereas the ESP32-S3 internal SAR TSENS only has `±1.5°C` to `±3.0°C` absolute accuracy even with eFuse calibration. By recording the settled offset $\Delta_{\text{tare}} = T_{\text{SHTC3,cold}} - T_{\text{die,cold}}$ during deep-sleep equilibrium, `t_die` becomes a **precision differential heat-rise sensor** ($\Delta T_{\text{die}}$) rather than an uncalibrated absolute thermometer.

---

### 1.2 Quirk #2: Why the Audio Codec (ES8311) & Class-D Amp (NS4168) Heat the Board
You noted that `< 1°C` of board temperature change dramatically impacts SHTC3 readings and that the codec and Class-D amplifier are the primary heat offenders. **The audit uncovered a major power/thermal bug in `sub_audio.c` and `h1os_boot_hook.c`:**

1. **`sub_audio_init()` Unmutes the Class-D Amplifier and Leaves I2S Clocks Running for the Entire 30-Second Session (`sub_audio.c:366`):**
   Look at the end of `sub_audio_init()` (`sub_audio.c:331–368`):
   ```c
   err = sub_audio_park_warm(false); // <-- DRIVES PA_CTRL (GPIO 46) HIGH AND ENABLES I2S MCLK/BCLK!
   ```
   - `sub_audio_park_warm(false)` enables the I2S TX channel (generating continuous 4.096 MHz `MCLK` and 512 kHz `BCLK`) **and drives `HAL_PIN_PA_CTRL` (`GPIO 46`) HIGH (`1`)**!
   - Meanwhile, in `audio_worker_task()` (`sub_audio.c:150–179`), after a 150 ms boot/button chime finishes playing, the worker writes 4 zero-buffers and goes back to `xQueueReceive(..., portMAX_DELAY)` **without ever calling `sub_audio_park_warm(true)`**!
   - **Result:** For the entire 30-second interactive session, the NS4168 Class-D amplifier's H-bridge is actively switching at ~300 kHz into the speaker coil with a 0-volt signal, and the ES8311 DAC + charge pumps + I2S clocks stay 100% powered on. A Class-D amplifier switching continuously at idle draws **4–8 mA at 3.7V (~15–30 mW)**, which conducts directly through the ground plane to the SHTC3!
2. **Cold Boot / Unattended Wake Codec State (`h1os_boot_hook.c:52–57` & `h1os_lifecycle.c:295`):**
   - Because of Hardware Errata E4 (driving `PA_EN` GPIO 42 HIGH unpowers the ES8311 and clamps `I2C_SDA`/`I2C_SCL` to 0.7V via ES8311 ESD diodes), `h1os_boot_hook.c` must hold `PA_EN` (`GPIO 42`) LOW (`0 = rail ON`).
   - However, on an **unattended RTC wake** (`is_user_wake == false`), `h1os_lifecycle.c` skips `sub_audio_init()`. While `sub_audio_standby()` is called at the *end* of the wake in `orch_flow_quiesce_peripherals()`, if the ES8311 ever reset or powered up in default state, its internal VMID/CSM references stay warm until `sub_audio_standby()` runs.
3. **Proposed Fix (`sub_audio.c`):**
   - Change the end of `sub_audio_init()` to call `sub_audio_park_warm(true);` so the codec and Class-D amplifier remain muted (`PA_CTRL = 0`) and I2S clocks stay gated off after initialization until the exact millisecond an audio command arrives.
   - In `audio_worker_task()`, call `sub_audio_park_warm(true);` immediately after draining the playback queue (`uxQueueMessagesWaiting(s_audio_queue) == 0`). This limits Class-D amp switching to the ~120 ms duration of a chime, cutting audio thermal dissipation during interactive sessions by **> 95%**.

---

## 2. Logical Bugs, Code Mistakes & Memory Safety Issues

| ID | Severity | Location | Issue Description | Proposed Fix |
| :--- | :--- | :--- | :--- | :--- |
| **BUG-01** | **CRITICAL** | `orch_flow.c:221–228` | **EWMA Historical State Corrupted on Every UI Query:** `orch_flow_query_telemetry()` updates `st->temp_historical_c` and `st->rh_historical_pct` (and dumps the 32-entry ring buffer to UART) **every time `h1os_get_telemetry()` is called**. During an interactive session, every button press (`KEY_RIGHT`) calls `update_active_display()` $\rightarrow$ `h1os_get_telemetry()`, repeatedly feeding the *same* sample into the EWMA filter and decaying historical history toward the current reading. | Track `st->last_processed_sample_count` in `orch_persisted_state_t` and only advance the EWMA filter and ring-buffer UART dump when `st->total_samples != st->last_processed_sample_count`. |
| **BUG-02** | **CRITICAL** | `examples/H1OS/main/main.c:73–82` & `screens/*.c` | **Recursive `lv_refr_now(NULL)` Inside `lv_timer_handler()` Input Callback:** `keypad_event_cb()` runs *inside* LVGL's input device read timer (`lv_timer_handler()`). Calling `update_active_display()` $\rightarrow$ `screen_*_render()` calls `lv_refr_now(NULL)` synchronously from inside an active LVGL timer execution, and acquires nested `h1os_lvgl_lock()` locks. | Remove `lv_refr_now(NULL)` from `screen_*_render()` (LVGL's own refresh timer automatically renders dirty objects on the very next tick) or only call `lv_refr_now(NULL)` when not inside `lv_timer_handler()`. |
| **BUG-03** | **HIGH** | `examples/H1OS/main/screens/screen_base.c:18` | **Asymmetric Mutex Lock in `screen_base_create()`:** `screen_base_create()` calls `h1os_lvgl_lock(100)` on entry and **never unlocks it**, relying on the caller (`screen_*_render()`) to call `h1os_lvgl_unlock()`. If any caller invokes `screen_base_create()` without knowing this hidden side effect, both `lv_lock()` and the 240 MHz PM lock (`s_cpu_max_lock`) leak permanently. | Move `h1os_lvgl_lock(100)` explicitly to the top of each `screen_*_render()` function (matching its `h1os_lvgl_unlock()` at the bottom) and keep `screen_base_create()` lock-neutral. |
| **BUG-04** | **HIGH** | `sub_audio.c:482` | **Buffer Over-Read in `SUB_AUDIO_PCM` Playback:** `sub_audio.h:76` specifies `len` in `sub_audio_play(mode, data, len)` is in **bytes** (and `SUB_AUDIO_TONE` checks `len < 2 * sizeof(uint32_t)`). However, `SUB_AUDIO_PCM` assigns `cmd.params.pcm.sample_count = len;` instead of `len / sizeof(int16_t)`, causing `sub_audio_render_pcm_samples()` to read **2x past the end of the PCM buffer**. | Change `sub_audio.c:482` to `cmd.params.pcm.sample_count = len / sizeof(int16_t);`. |
| **BUG-05** | **HIGH** | `sub_audio.c:195` | **`sub_audio_read_chip_id()` Fails Whenever Audio is Parked or in Standby:** Line 195 checks `if (s_tx_chan != NULL && !s_i2s_chan_enabled) return ESP_ERR_INVALID_STATE;`. Because `sub_audio_standby()` and `sub_audio_park_warm(true)` set `s_i2s_chan_enabled = false`, calling `sub_audio_is_ready()` after standby always fails even though the ES8311 I2C slave is powered (`PA_EN = 0`) and responds on I2C! | Remove the `!s_i2s_chan_enabled` rejection in `sub_audio_read_chip_id()` (ES8311 I2C register `0xFD/0xFE` reads only require `PA_EN = 0` and I2C bus init, not active I2S MCLK). |
| **BUG-06** | **MEDIUM** | `sub_sensor.c:139–140` | **SHTC3 Conversion Divisor Off-by-One (`65536.0f` vs `65535.0f`):** `sub_sensor_convert_shtc3_units()` divides by `65536.0f` ($2^{16}$), whereas Sensirion's SHTC3 datasheet (and `orch_wake_stub.c:366` + `sub_sensor.h:57` Doxygen) specifies $2^{16} - 1 = 65535$. | Change `65536.0f` to `65535.0f` in `sub_sensor.c:139–140`. |
| **BUG-07** | **MEDIUM** | `h1os_lifecycle.c:316–317` | **Incorrect `wake_context_t` Fields Passed to `on_wake`:**<br>1. `ctx.sleep_duration_sec` is set to `sample_interval_sec` (60s) instead of `flow_b_period_sec` (300s) on full-cycle RTC wakes.<br>2. `h1os.h:35` documents `wake_button` as *"GPIO pin number of waking button"*, whereas `h1os_lifecycle.c` passes `ulp_last_wake_btn` (`1` = BOOT, `2` = POWER). Since `GPIO_NUM_0` is `0` (indistinguishable from "no button" if `0` means none), update the `h1os.h` Doxygen and add `H1OS_WAKE_BTN_NONE=0`, `H1OS_WAKE_BTN_BOOT=1`, `H1OS_WAKE_BTN_POWER=2`. | Pass `(button_woke ? st->sample_interval_sec : st->flow_b_period_sec)` for `sleep_duration_sec` and clarify `wake_button` enum in `h1os.h`. |
| **BUG-08** | **MEDIUM** | `h1os_lvgl.cpp:47` | **`h1os_lvgl_lock(uint32_t timeout_ms)` Ignores `timeout_ms`:** The function signature accepts `timeout_ms`, fails to cast `(void)timeout_ms;`, and calls unconditional blocking `lv_lock()`. | Cast `(void)timeout_ms;` or document blocking semantics clearly to avoid misleading callers. |
| **BUG-09** | **LOW** | `sub_sdcard.c:55` | **`HAL_PIN_SD_DET` Configured as Input Without Pull-Up:** `sub_sdcard_is_inserted()` configures `GPIO 16` (`HAL_PIN_SD_DET`) with `GPIO_PULLUP_DISABLE`. If the board has no external pull-up populated on `SD_DET`, the pin floats when no card is inserted. | Enable internal pull-up (`GPIO_PULLUP_ENABLE`) on `HAL_PIN_SD_DET` as defensive hardware practice. |

*(Note: The 7 critical ULP/RTC/LVGL deep-sleep race conditions that caused the overnight Cycle 7 freeze were already identified and patched in the earlier diff).*

---

## 3. Mathematical & Psychrometric Verification

### 3.1 SHTC3 Raw-to-Metric Conversion (`orch_wake_stub.c:366–367`)
- **Formula Used:**
  $$T_{\text{centi-C}} = -4500 + \left\lfloor \frac{17500 \times S_T}{65535} \right\rfloor, \quad \text{RH}_{\text{centi-\%}} = \left\lfloor \frac{10000 \times S_{\text{RH}}}{65535} \right\rfloor$$
- **Verdict:** **Mathematically sound** in `orch_wake_stub.c` (uses `65535LL` and 64-bit integer promotion, preventing 32-bit overflow since $17500 \times 65535 = 1.146 \times 10^9 < 2^{31}-1$). Fix `sub_sensor.c:139–140` from `65536.0f` to `65535.0f` for consistency.

### 3.2 Magnus-Tetens Saturation Vapor Pressure & Dew Point (`orch_math.c:73–153`)
- **Constants Used:** $A = 6.112\text{ hPa}$, $B = 17.62$, $C = 243.12^\circ\text{C}$ (Sonntag / Sensirion application note standard for $-45^\circ\text{C}$ to $+60^\circ\text{C}$).
- **Equations:**
  $$e_s(T) = 6.112 \cdot \exp\left(\frac{17.62 \cdot T}{243.12 + T}\right)$$
  $$e = \frac{\text{RH}}{100} \cdot e_s(T_{\text{sensor}})$$
  $$\gamma = \ln\left(\frac{e}{6.112}\right), \quad T_{\text{dew}} = \frac{243.12 \cdot \gamma}{17.62 - \gamma}$$
  $$\text{RH}_{\text{amb}} = \text{clamp}_{[0,100]}\left(100 \cdot \frac{e}{e_s(T_{\text{amb}})}\right)$$
- **Verdict:** **Mathematically and physically exact.** Under strict `-Wdouble-promotion` (`CMakeLists.txt:46`), all literals have `f` suffixes and use `expf()` / `logf()` / `fabsf()`.

### 3.3 Absolute Humidity (`orch_math.c:167–174`)
- **Formula Used:**
  $$\text{AH}\ (\text{g/m}^3) = \frac{216.7 \cdot e_{\text{hPa}}}{T_{^\circ\text{C}} + 273.15}$$
- **Derivation Check:** From the Ideal Gas Law for water vapor ($\rho_v = \frac{e \cdot M_w}{R \cdot T_K}$):
  - $e$ in Pascals $= 100 \times e_{\text{hPa}}$
  - $M_w = 18.01528\text{ g/mol}$, $R = 8.31446\text{ J/(mol}\cdot\text{K)}$
  - $\frac{100 \times 18.01528}{8.31446} = \mathbf{216.674\text{ g}\cdot\text{K/(J}\cdot\text{hPa)}}$
- **Verdict:** **Mathematically sound** (`216.7f` is accurate to within `0.012%`).

### 3.4 Battery ADC Calibration & ULP Fixed-Point Math (`sub_power.c:219–243` & `ulp/main.c:66–74`)
- **Host Extraction (`sub_power.c`):**
  $$m_{\text{scale}} = \left\lfloor \frac{(V_{3000} - V_{1000}) \times 4096}{2000} \right\rfloor, \quad b_{\text{offset}} = V_{1000} - \left\lfloor \frac{m_{\text{scale}} \times 1000}{4096} \right\rfloor$$
  $$\text{out\_offset\_mv} = 2 \cdot b_{\text{offset}}$$
- **ULP Evaluation (`ulp/main.c`):**
  $$V_{\text{adc}} = \frac{\text{raw} \times m_{\text{scale}}}{4096}, \quad V_{\text{bat}} = 2 \cdot V_{\text{adc}} + \text{out\_offset\_mv}$$
- **Fallback Check:** When `s_cali_valid == false`, `sub_power.c:239` sets `*out_scale = 3100; *out_offset_mv = 0;`. Since the ULP divides by `4096` (`>> 12`), $\frac{\text{raw} \times 3100}{4096}$ matches the host fallback $\frac{\text{raw} \times 3100}{4095}$ to within `0.024%` (`< 1 mV`).
- **Max Overflow Check:** $\text{raw}_{\max} \times m_{\text{scale}} \approx 4095 \times 3500 = 14,332,500 \ll 2^{32}-1$. No `uint32_t` overflow is possible.
- **Verdict:** **Mathematically sound.**

### 3.5 Tri-Node Confidence & Thermal Lockout Model (`orch_flow.c:229–238`)
- **Critique of Current Tri-Node Formula:**
  ```c
  float t_trinode = (t_valid + t_die + t_glass) / 3.0f;
  float delta_trinode = t_valid - t_trinode;
  ```
  Mathematically, $T_{\text{valid}} - \frac{T_{\text{valid}} + T_{\text{die}} + T_{\text{glass}}}{3} = \frac{2 T_{\text{valid}} - T_{\text{die}} - T_{\text{glass}}}{3}$.
  - On cold boot or before the first EPD refresh on wake, `st->last_glass_temp_centi_c` is initialized to `2500` (`25.00°C`), and `t_die` had the uncalibrated offset described in Section 1.1.
  - Even more importantly, in `orch_flow_evaluate_ambient_selection()` (`orch_flow.c:185–194`), when the system enters `CASE_A_UNSETTLED` or `CASE_B_LEAKAGE`, setting `t_amb = min(t_die, t_glass)` directly substitutes a **low-resolution/uncalibrated auxiliary sensor** (`±1.5°C` SSD1681 glass integer sensor or `±2°C` MCU TSENS) in place of the `±0.2°C` SHTC3 sensor!
  - **Recommended Improvement:** In `CASE_A_UNSETTLED` (when `valid_trend < 2` and `st->total_samples > 0`), `st->amb_floor_temp_centi_c` (or `t_valid` from `orch_state_get_latest_valid_sample()`) is **already** the coldest/settled SHTC3 reading from the RTC ring buffer! Clamping `t_amb` to `t_valid` (or subtracting the measured die self-heating rise $\Delta T_{\text{die}} = \max(0, T_{\text{die,now}} - T_{\text{die,floor}})$ from `t_valid`) preserves the SHTC3's `0.01°C` precision instead of jumping to the coarse `1°C`-stepped EPD glass sensor or biased MCU die sensor.

---

## 4. Architectural Compliance & Documentation Audit

### 4.1 4-Layer Dependency Invariants (`A1_master_blueprint.md` Section 2)
The architecture blueprint states:
- **Rule 1 (Strict Downward Dependency):** Layer $N$ may only `#include` headers from Layer $N-1$ (or `hal_types.h`).
- **Rule 2 (No Horizontal Subsystem Coupling):** Layer 2 modules (`sub_*`) must never call or `#include` another Layer 2 module directly.

**Violations Found in Source Tree:**
1. **`sub_audio.c` (Layer 2) includes Layer 4 (`h1os/h1os.h`) and Layer 2 peer (`h1os/sub_power.h`):**
   - `sub_audio.c:16` includes `"h1os/h1os.h"` solely to use `H1OS_CHIME_BOOT`, `H1OS_CHIME_SLEEP`, `H1OS_CHIME_SHUTDOWN`, `H1OS_CHIME_CLICK`, `H1OS_CHIME_ALERT`. Moving or mirroring those chime IDs in `sub_audio.h` (or `hal_types.h`) eliminates the upward Layer 2 $\rightarrow$ Layer 4 dependency.
   - `sub_audio.c:19` includes `"h1os/sub_power.h"` to call `sub_power_cpu_max_acquire()` / `release()`.
2. **`sub_display.cpp` (Layer 2) includes Layer 3 (`h1os/orch_state.h`):**
   - `sub_display.cpp:17` includes `"h1os/orch_state.h"` to write `orch_state_get()->last_glass_temp_centi_c = (int16_t)t_c * 100;` inside `epd_read_glass_temp()`. Instead, `orch_display_sync` or `orch_flow` (Layer 3) should query `sub_display_get_glass_temp_c()` and store it into `orch_state`.
3. **`sub_power.c` (Layer 2) includes Layer 3 (`orch_state.h`, `orch_wake_stub.h`) and Layer 2 peer (`sub_rtc.h`):**
   - `sub_power_enter_deep_sleep_mode()` computes Flow A / Flow B slicing (`orch_state_get()->sample_interval_sec`), arms the external RTC (`sub_rtc_arm_countdown()`), and installs the Layer 3 wake stub (`orch_wake_stub_install()`). Architecturally, this orchestration belongs in `orch_flow_execute_sleep()` (Layer 3), passing the computed parameters down to `sub_power` (Layer 2).

### 4.2 RTC Slow Memory Budget (`A1` & `A5`: `< 512 bytes` vs Actual `632 bytes`)
- `A1_master_blueprint.md` and `A5_rtc_memory_and_state.md` state that `orch_persisted_state_t` must be `< 512 bytes`.
- In `orch_state.h`, `ORCH_RING_CAPACITY` is `32` and `sizeof(orch_tri_node_sample_t)` is `16 bytes` ($32 \times 16 = 512\text{ bytes}$ for the ring buffer alone), making `sizeof(orch_persisted_state_t)` = **`632 bytes`**.
- While `632 bytes` is completely safe in hardware (ESP32-S3 has 8 KB of RTC Slow SRAM and `sdkconfig.defaults` reserves `4096 bytes` for ULP coprocessor code+data, leaving `> 3.3 KB` for `RTC_DATA_ATTR`), `A1` and `A5` should be updated to state `< 768 bytes` (or `ORCH_RING_CAPACITY` reduced to `24` if `< 512 bytes` is a hard requirement).

### 4.3 Contradictions Between Architecture Docs (`A6`, `A7`) and `ERRATA.md`
1. **`A6_ulp_coprocessor.md` (Section 5, lines 173–175) vs `A3_gpio_hold_and_sleep.md` (Section 3.2):**
   - `A6` shows calling `gpio_hold_en()` on `HAL_PIN_BUTTON_BOOT`, `HAL_PIN_BUTTON_POWER`, and `HAL_PIN_RTC_INT`.
   - `A3` (and `ERRATA.md` Section 2) rightly states that calling `gpio_hold_en()` on RTC wake pins freezes the pad mux before `rtc_gpio_init()`, permanently deafening ULP GPIO wakeups! `A6` should be updated to match `sub_power.c` and `A3`.
2. **`A6_ulp_coprocessor.md` (Section 1 Note) vs `ERRATA.md` (Section 1 `ERR-S1`):**
   - `A6` claims `RTC_CNTL_ULP_CP_SLP_TIMER_EN` and `RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA` can be armed concurrently. `ERRATA.md` documents that on ESP32-S3 silicon, arming `SLP_TIMER_EN` completely masks RTC GPIO wakeups (Pure Event Mode via PCF85063A `/INT` is required).
3. **`A7_sensor_psychrometrics.md` (Section 5) vs Actual Code:**
   - `A7` still describes an older `k = 0.25` linear thermal divider and `TIMER_EXPIRE` wakeup path, whereas the code implements the 32-sample cold ring buffer + 3-tier `orch_flow_evaluate_ambient_selection()` model.

---

## 5. Unused Functions, Dead Prototypes & Orphaned Kconfig Symbols

### 5.1 Entirely Unused Source Module: `sub_sensor.c` / `sub_sensor.h`
None of the 5 functions in `sub_sensor.c` are called anywhere in the repository (`components/h1os` or `examples/H1OS`):
- `sub_sensor_init()` — **0 callers**
- `sub_sensor_deinit()` — **0 callers**
- `sub_sensor_read_shtc3_raw()` — **0 callers** (SHTC3 is only read via bit-banged I2C inside `orch_wake_stub.c`)
- `sub_sensor_convert_shtc3_units()` — **0 callers**
- `sub_sensor_read_mcu_die_temp()` — **0 callers**

**Recommendation:** Either integrate `sub_sensor_read_shtc3_raw()` into `orch_flow_query_telemetry()` when `st->total_samples == 0` (so Cold Boot has a real initial SHTC3 & MCU die temperature reading instead of returning `0.00°C / 0.0% RH` on the initial boot screen!), or mark `sub_sensor.c` as an optional diagnostic driver. **Using `sub_sensor` on Cold Boot when `total_samples == 0` solves the `0.0°C` cold-boot telemetry problem!**

### 5.2 Unused Functions in Active Modules
| File | Symbol | Status / Recommendation |
| :--- | :--- | :--- |
| `orch_math.c` / `.h` | `orch_math_is_plateau_settled()` | **Unused.** Superseded by inline delta gate in `orch_wake_stub.c`. Keep `static inline` or remove from public header. |
| `orch_math.c` / `.h` | `orch_math_calc_vapor_pressure()` | **Unused externally.** Duplicate of math inside `orch_math_calc_psychrometrics()`. Have `orch_math_calc_psychrometrics()` call them internally to eliminate code duplication! |
| `orch_math.c` / `.h` | `orch_math_calc_dew_point()` | **Unused externally.** Call inside `orch_math_calc_psychrometrics()` to eliminate duplicate Magnus-Tetens code. |
| `orch_math.c` / `.h` | `orch_math_reconstruct_ambient_rh()` | **Unused externally.** Call inside `orch_math_calc_psychrometrics()` to eliminate duplicate code. |
| `orch_state.h` | `ulp_vbat_scale`, `ulp_vbat_offset_mv`, `wake_timestamp_epoch`, `app_stage`, `scratchpad_len`, `scratchpad[32]` | **Unused struct fields** in `orch_persisted_state_t` (wastes 48 bytes of RTC Slow SRAM). Remove to shrink `orch_persisted_state_t`. |
| `hal_types.h` | `h1os_init_mode_t`, `h1os_sleep_mode_t` | **Unused enums.** Legacy remnants; safe to remove. |

### 5.3 Orphaned Legacy Symbols in `components/h1os/Kconfig`
The following `Kconfig` options are defined in `components/h1os/Kconfig` (and `sdkconfig.defaults`) under a legacy `BSP_*` prefix, but **are never referenced anywhere in C/C++ code**:
- `CONFIG_BSP_THERMAL_COMPENSATION_DEFAULT`
- `CONFIG_BSP_THERMAL_DIVIDER_K_X1000`
- `CONFIG_BSP_THERMAL_EMA_ALPHA_X1000`
- `CONFIG_BSP_BATTERY_CORRECTION_FACTOR_MV`
- `CONFIG_BSP_AUDIO_DEFAULT_VOLUME`
- `CONFIG_BSP_AUDIO_LOW_POWER_DEFAULT`
- `CONFIG_BSP_RTC_WAKEUP_SOURCE`

Only `CONFIG_H1OS_EPD_CLEAN_WHITE_ON_SHUTDOWN` is actually used by the codebase (`h1os_lifecycle.c:559`). Cleaning up or wiring these Kconfig symbols will prevent developer confusion when tuning menuconfig parameters.

---

## 6. Deprecations & ESP-IDF v6.1 Compatibility Check

1. **`driver/rtc_io.h` / `esp_sleep_enable_ext1_wakeup()` (`h1os_lifecycle.c:548`):**
   - In ESP-IDF v5.3+ / v6.x, `esp_sleep_enable_ext1_wakeup(mask, mode)` is deprecated in favor of `esp_sleep_enable_ext1_wakeup_io(mask, level_mode)` (which no longer uses `ESP_EXT1_WAKEUP_ANY_LOW`, a mode that was removed on later chips and replaced by per-pin or `ESP_EXT1_WAKEUP_ALL_LOW` / `esp_sleep_enable_ext1_wakeup_io`). On ESP32-S3, `ESP_EXT1_WAKEUP_ANY_LOW` still compiles via legacy compatibility headers, or you can use `esp_sleep_enable_ext0_wakeup(HAL_PIN_BUTTON_POWER, 0)` since standby wake only monitors the single `HAL_PIN_BUTTON_POWER` pin (`GPIO 18`)!
2. **Legacy I2C Driver (`driver/i2c.h` in `hal_i2c.c`):**
   - `hal_i2c.c` uses the legacy `i2c_param_config` / `i2c_driver_install` API (`driver/i2c.h`) and relies on `CONFIG_I2C_SKIP_LEGACY_CONFLICT_CHECK=y` in `sdkconfig.defaults`. This is intentional and well-justified in your codebase because ESP-IDF's new `driver/i2c_master.h` logs errors or asserts during raw register bit-banging transitions, whereas `hal_i2c.c` cleanly manages bus recovery.
3. **Strict Compiler Flags (`CMakeLists.txt:43–49`):**
   - The component compiles with `-Wall -Wextra -Werror -Wdouble-promotion -Wfloat-conversion`. All proposed fixes strictly preserve `f` suffixes on floating-point constants and explicit casts to ensure zero warnings under `-Werror`.


---

## 7. Post-Fix Verification Audit Results (`v2.3.2-dev`)

All approved architectural, mathematical, and hardware improvements have been implemented and verified across the entire repository (`components/h1os`, `examples/H1OS`, `examples/boilerplate`, and `CHANGELOG.md`):

| Audit Check | Scope | Result | Verification Details |
| :--- | :--- | :--- | :--- |
| **1. Strict 4-Layer Dependency Hierarchy (`A1`)** | All 56 `.c`/`.cpp`/`.h` files | **PASS (0 Violations)** | Removed all upward and horizontal `#include` dependencies across Layer 2 (`sub_audio.c`, `sub_display.cpp`, `sub_power.c`) and Layer 3 (`orch_flow.c`). Every file now strictly obeys `Layer 4 -> Layer 3 -> Layer 2 -> Layer 1`. |
| **2. Dead Code & Redundant Driver Purge** | `sub_sensor.c/.h`, `HAL_PIN_SD_DET`, `Kconfig` | **PASS (0 Orphans)** | Removed `sub_sensor.c` and `sub_sensor.h` (and `esp_driver_tsens` from `CMakeLists.txt`), removed `HAL_PIN_SD_DET` (`GPIO 16`), pruned 48 bytes of unused fields from `orch_persisted_state_t` (`632 B -> 592 B`), and removed 7 orphaned `BSP_*` options from `Kconfig`. |
| **3. Wake Stub RTC IRAM Residency** | `orch_wake_stub.c`, `orch_math.c`, `orch_state.c` | **PASS (100% IRAM)** | Every function invoked by `bsp_wake_stub()` while SPI flash cache is disabled (`wake_stub_read_die_temp_centi_c`, `rtc_write_reg_retry`, `rtc_rearm_countdown_stub`, `orch_math_is_plateau_settled`, `orch_state_get`, `orch_state_push_sample`) is marked `RTC_IRAM_ATTR`. |
| **4. Fixed-Point TSENS & 32-Bit SHTC3 Math** | `orch_wake_stub.c`, `orch_flow.c` | **PASS (0 Divisions in TSENS)** | Pre-computed `tsens_offset_centi_c = 2052 + tsens_cal_centi_c` on Cold Boot; configured `SENS_TSENS_CLK_DIV = 6` and `SENS_TSENS_DAC = 15` (`0x0F`) with `SENS_TSENS_RESET` pulse; replaced TSENS division with `((int32_t)raw * 179651) >> 12`; replaced 64-bit `65535LL` SHTC3 division with 32-bit `65535U`; added deep-sleep `die_tare_centi_c` self-zeroing (`valid_trend >= 3`) and restored `ORCH_LEAKAGE_MARGIN_C` to `0.50f`. |
| **5. Single-Responsibility Psychrometric Engine** | `orch_math.c`, `orch_math.h` | **PASS (0 Duplication)** | `orch_math_calc_psychrometrics()` now composes `orch_math_calc_vapor_pressure()`, `orch_math_calc_dew_point()`, and `orch_math_reconstruct_ambient_rh()`; fixed `orch_math_is_plateau_settled()` to evaluate `|initial - current| <= gate_threshold`. |
| **6. Audio PCM Safety, Standby Recovery & I2S Flush** | `sub_audio.c`, `sub_audio.h` | **PASS** | Fixed `SUB_AUDIO_PCM` `sample_count = len / sizeof(int16_t)`, removed `!s_i2s_chan_enabled` rejection in `sub_audio_read_chip_id()`, added DAC register re-initialization on standby wake, kept NS4168 Class-D amp unmuted during interactive sessions, and executed a single zero-frame flush (`sub_audio_flush_frame()`) after draining the playback queue. |
| **7. Multi-Core LVGL Lock Symmetry & Non-Recursive Refresh** | `h1os_lifecycle.c`, `examples/H1OS/main/screens/*.c` | **PASS** | Made `screen_base_create()` lock-neutral, placed symmetric `h1os_lvgl_lock(100)` / `h1os_lvgl_unlock()` at the top/bottom of each `screen_*_render()` function, removed recursive `lv_refr_now(NULL)` inside keypad callbacks, and gated EWMA updates in `orch_flow_query_telemetry()` behind `st->total_samples != st->last_ewma_sample_seq`. |
| **8. Real GCC/G++ Compiler Audit (`-Wall -Wextra -Werror -Wdouble-promotion -Wstrict-prototypes`)** | All 27 `.c`/`.cpp` translation units | **PASS (27/27, 0 Warnings)** | Verified all 27 translation units across `components/h1os/src/`, `examples/H1OS/main/`, and `examples/boilerplate/main/` compile with 0 warnings and 0 errors, and added missing self-contained standard/FreeRTOS includes (`<stddef.h>` in `sub_audio.h`, `<inttypes.h>` in `hal_flash.c`, `"esp_rom_sys.h"` in `hal_spi.c`, `"freertos/task.h"` and `<string.h>` in `sub_rtc.c`, `"freertos/task.h"` in `sub_display.cpp`, `<stdlib.h>` in `h1os_time.c`, and `<assert.h>` in `h1os_lvgl.cpp`). |
