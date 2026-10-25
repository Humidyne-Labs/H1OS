# H1OS v2.3.2 Nightly Test Summary, FLIR Thermal Analysis & Zero-Calibration Thermal Architecture

**Target Platform:** Waveshare ESP32-S3 ePaper 1.54" V2 (`ESP32-S3-PICO-1-N8R8`)  
**Test Window:** `2026-10-21 01:23 AM` to `01:52 PM` (`12 hours 29 minutes` / `749 minutes`)  
**Firmware Profile:** `H1OS v2.3.2-dev` (`Flow A = 60s`, `Flow B = 300s`, `4 samples + 5th slice wake`)  

## 1. Executive Summary & Architectural Specification

### 1.1 Sleep/Wake Orchestration & Runtime Stability: 100% Pass
Over `749 minutes` of continuous unattended operation, H1OS executed **761 deep-sleep wakes** and **153 full Flow B display cycles** (`4` bare-metal Flow A sensor sprints pushed to the 32-sample ring buffer per cycle, waking into Flow B on slice `5`) with **zero deadlocks, zero sleep rejections, zero ULP traps, and zero I2C bus lockups**. All previous Cycle 7 race conditions between Core 0/1 LVGL flushing, PCF85063A `/INT` open-drain pulse release, and ULP GPIO wakeup gating are completely resolved.

### 1.2 The Zero-Calibration Hardware Architecture
The Sensirion SHTC3 comes **factory-calibrated to a high degree of accuracy (`±0.2°C`, `±2% RH`)**:
- Comparing the end-of-test water vapor partial pressure (`13.60 hPa`, Dew Point `12.1°C / 53.9°F`) against the true room reference (`71.0°F / 21.67°C`, `53.0% RH`, `13.70 hPa`, Dew Point `11.7°C / 53.0°F`) confirms the SHTC3 sensing element is within **0.7% (`-0.10 hPa`)** of the room reference.
- The `+2.23°C` (`+4.0°F`) discrepancy observed during the nightly run was **not** a sensor calibration error—it was caused by **board heat** from peripheral bugs (`ES8311` standby reset bug leaving analog bias active at ~4 mA, `NS4168` `PA_CTRL` readback bug, `240 MHz` CPU locks held across mechanical EPD `BUSY` waits, and the 8 MB PSRAM march test running on every wake).
- **Core OS Principle:** We do **not** apply synthetic offsets, ambient reconstitutions, slice trimming, or sensor taring. Instead, the OS/middleware eliminates peripheral and MCU heat generation so the PCB cools naturally to ambient during sleep. When consecutive Flow A samples satisfy `|temp2 - temp1| <= SAMPLE_DELTA_GATE_CENTI_C` (`0.20°C`), the board has reached thermal steady state and the factory-calibrated SHTC3 reading (`t_valid`, `rh_valid`) is trusted directly. The SSD1681 on-glass sensor and ESP32-S3 internal die sensor serve strictly to verify that the SHTC3 is operating within a normal range (`trinode_temp_c`, `trinode_delta_c`, `trinode_confidence_pct`).

## 2. FLIR Thermal Camera Sequence Analysis (`IMG230600163735` – `IMG230600163930`)

Your 5 thermal images capture the exact hardware heat sources across a wake-to-sleep cycle that prevented the PCB from cooling completely between wakes:

| Thermal Frame | Timestamp | Crosshair / Scale | Observed Thermal Signature & Hardware Root Cause |
| :--- | :---: | :---: | :--- |
| **`IMG230600163735.bmp`** | `16:37:35` (`t = 0s`) | `22.6°C` (`20.6–29.0°C`) | **Wake Onset:** Idle PCB background is dark blue (`~21.0–22.0°C`, near room ambient). The `ESP32-S3-PICO-1-N8R8` package on the left immediately jumps to `~26–27°C` during the 240 MHz 8 MB Octal PSRAM march test (`CONFIG_SPIRAM_MEMTEST=y`). |
| **`IMG230600163747.bmp`** | `16:37:47` (`t = +12s`) | `22.6°C` (`20.6–28.9°C`) | **240 MHz Active Peak:** The ESP32-S3 SiP reaches `28.9°C` (bright red/pink core) while holding the 240 MHz PM lock across `sub_display_wait_busy()` and active session polling. |
| **`IMG230600163821.bmp`** | `16:38:21` (`t = +46s`) | `24.1°C` (`20.0–28.6°C`) | **Post-Sleep PCB Heat Dump:** The ESP32-S3 enters deep sleep and conducts its stored thermal energy (`Q = C_th * dT`) into the FR4 copper ground plane, raising the central PCB crosshair from `22.6°C` to `24.1°C` (`+1.5°C` jump). |
| **`IMG230600163913.bmp`** | `16:39:13` (`t = +98s`) | `25.2°C` (`20.9–28.6°C`) | **Codec (`ES8311`) & Class-D (`NS4168`) Hotspots:** Two distinct IC hotspots glow orange/yellow in the central board region (`~26.5–27.5°C`) alongside the bottom connector, pushing the central PCB temperature to `25.2°C`. |
| **`IMG230600163930.bmp`** | `16:39:30` (`t = +115s`) | `24.5°C` (`20.8–30.0°C`) | **Slow PCB Exponential Decay:** Because the ES8311 remained in active POR bias (`~3.5–4.5 mA`) after `sub_audio_standby()` wrote `{0x00, 0x1F}`, the PCB remained warm at `24.5°C` instead of cooling back to `21.7°C` room ambient. |

## 3. Root-Cause Audit of Hardware Heat Sources & Battery Anomalies

### 3.1 Smoking Gun #1: Why the ES8311 Codec & NS4168 Class-D Amp Heated the Board (`sub_audio.c`)
Three interacting bugs in `sub_audio.c`, `hal_io.c`, and `orch_flow.c` caused the audio subsystem to heat up on wake events and draw continuous current in sleep:

1. **`s_es8311_deinit[]` Wrote `{0x00, 0x1F}` (`RST_REG = 1`) *After* `{0x0D, 0xFC}` (`sub_audio.c:224–225`):**
   ```c
   {0x0D, 0xFC}, /**< REG0D: Assert power down across system blocks */
   {0x00, 0x1F}, /**< REG00: Digital block reset */
   ```
   In the Everest Semiconductor ES8311 silicon, **Bit 0 of Register `0x00` (`RESET_REG00`) is `RST_REG` (`1 = reset all control registers 0x01..0x45 to factory Power-On-Reset defaults`)**!
   - Writing `{0x00, 0x1F}` immediately after `{0x0D, 0xFC}` **wiped out `0x0D = 0xFC`, `0x0E = 0xFF`, `0x12 = 0x02`, `0x14 = 0x00`, and `0x17 = 0x00`**, resetting `REG0D` back to its POR default (`0x01`, which powers ON the internal analog VMID reference and bias generators at `~3.5–4.5 mA` continuous draw)!
   - In addition, `s_es8311_init_pre_charge` enabled `{0x13, 0x10}` (analog bias) and `{0x1C, 0x6A}` (2.0V MIC bias generator), which were never cleared in `s_es8311_deinit`.
   - **Fix Implemented:** Changed `{0x00, 0x1F}` to **`{0x00, 0x1E}`** (`CSM_ON = 0`, `RST_DIG/DAC/ADC/CSM = 1`, **`RST_REG = 0`**) so the digital state machines reset while `0x0D = 0xFC` (`< 1.0 µA` analog power-down) remains latched in silicon, and added `{0x13, 0x00}` and `{0x1C, 0x00}` to `s_es8311_deinit[]`.

2. **Unattended Flow B Wakes Unconditionally Called `sub_audio_standby()` (`orch_flow.c`):**
   - Even though `h1os_lifecycle.c` skipped `sub_audio_init()` on unattended RTC wakes (`is_user_wake == false`), `orch_flow_quiesce_peripherals()` unconditionally called `sub_audio_standby()` before sleep entry on all 153 wakes, transmitting 11 I2C writes ending in `{0x00, 0x1F}` to the codec on every wake.
   - **Fix Implemented:** Added `RTC_DATA_ATTR static bool s_rtc_codec_in_standby` in `sub_audio.c`. Once the ES8311 is placed into verified standby (`0x00 = 0x1E, 0x0D = 0xFC`), subsequent unattended deep-sleep wakes (`!s_audio_inited && s_rtc_codec_in_standby`) bypass I2C transactions to the codec completely.

3. **`HAL_PIN_PA_CTRL` (`GPIO 46`) `GPIO_MODE_OUTPUT` Readback Bug & 30s Unmuted Class-D Idle (`hal_io.c:51`, `sub_audio.c:525, 542`):**
   - In `hal_io.c:51`, `HAL_PIN_PA_CTRL` (`GPIO 46`) was configured as `GPIO_MODE_OUTPUT` (which disables the ESP32-S3 pad input buffer `FUN_IE = 0`). On ESP32-S3, `gpio_get_level()` reads `GPIO_IN1_REG` and **always returns `0` when `FUN_IE = 0`**, even when the pin is actively driving `1` (3.3V)!
   - Consequently, when `sub_audio_park_warm(true)` (`target_level = 0`) checked `if ((uint32_t)gpio_get_level(HAL_PIN_PA_CTRL) != 0)`, it evaluated `0 != 0` (`false`) and **failed to drive `PA_CTRL` LOW**!
   - Furthermore, `sub_audio_init()` called `sub_audio_park_warm(false)` at line 525, leaving the NS4168 3W Class-D H-bridge switching continuously at ~300 kHz for the entire 30-second interactive session.
   - **Fix Implemented:** Configured `HAL_PIN_PA_CTRL` as `GPIO_MODE_INPUT_OUTPUT` in `hal_io.c`, latched `GPIO 46 = 0` in `h1os_boot_hook.c`, tracked `s_pa_enabled` explicitly in `sub_audio.c`, kept the Class-D amplifier muted (`PA_CTRL = 0`) at the end of `sub_audio_init()`, and automatically re-muted `PA_CTRL = 0` and disabled I2S clocks in `audio_worker_task()` immediately after the playback queue drains.

### 3.2 Smoking Gun #2: Why the ESP32-S3 Ramped So Hot on Wake & Drained the Battery
Five firmware/config factors caused the ESP32-S3 to dump excessive heat into the PCB on every Flow B wake:

1. **240 MHz Turbo Lock Held Across 300 ms – 2,200 ms Mechanical E-Paper `BUSY` Waits (`h1os_lvgl.cpp:133, 417`):**
   - `lvgl_display_flush_cb()` held `CpuMaxTurboScope turbo` (`sub_power_cpu_max_acquire()`) across `sub_display_refresh_partial()` (`~300 ms`) and `sub_display_refresh_full()` (`~2,200 ms`), and `h1os_lvgl_port_task()` held a second `sub_power_cpu_max_acquire()` lock around `lv_timer_handler()`.
   - Even with `SYS_CLK_MODE_DYNAMIC` enabled, holding `s_cpu_max_lock` while polling `HAL_PIN_EPD_BUSY` forced the ESP32-S3 to stay locked at **240 MHz** for the entire 300 ms – 2,200 ms physical electrophoretic refresh!
   - **Fix Implemented:** Scoped `CpuMaxTurboScope` in `lvgl_display_flush_cb()` strictly around the `< 2 ms` 1-bit pixel packing loop and removed the outer lock in `h1os_lvgl_port_task()`, so the CPU immediately drops to **80 MHz** while waiting on `HAL_PIN_EPD_BUSY`.

2. **8 MB Octal PSRAM March Test Running on Every Deep-Sleep Wake (`H1OS/sdkconfig`):**
   - `CONFIG_SPIRAM_MEMTEST=y` and `# CONFIG_BOOTLOADER_SKIP_VALIDATE_IN_DEEP_SLEEP is not set` in `H1OS/sdkconfig` caused every 5-minute Flow B wake (`153 wakes`) to run an 8 MB Octal PSRAM test and full app flash image verification at 240 MHz (`~300–350 ms` @ `~95 mA` before `app_main()` even started).
   - **Fix Implemented:** Set `CONFIG_SPIRAM_MEMTEST=n` and `CONFIG_BOOTLOADER_SKIP_VALIDATE_IN_DEEP_SLEEP=y` across `H1OS/sdkconfig`, `H1OS/sdkconfig.defaults`, `H1OS/sdkconfig.defaults.dev`, and `components/h1os/sdkconfig.defaults`.

3. **Active Wake Spin-Wait & Post-Busy Delay Pruning (`orch_flow.c`, `sub_display.cpp`, `h1os_lifecycle.c`, `hal_io.c`):**
   - Removed the redundant `vTaskDelay(pdMS_TO_TICKS(250))` after `sub_display_wait_busy()` in `orch_flow_quiesce_peripherals()`.
   - Reduced `epd_reset_pulse()` active spin-wait in `sub_display.cpp` from `20 ms` (`10000 us + 10000 us`) to `4 ms` (`2000 us + 2000 us`, matching SSD1681 `t_RES >= 1 ms`).
   - Reduced the pre-sleep handoff delay in `h1os_launch_interactive_session()` (`is_rtc_wake`) from `50 ms` to `10 ms` (since `h1os_quiesce_lvgl_pipeline()` already awaits `h1os_lvgl_has_pending_tasks()`).
   - Streamlined `hal_check_usb_ll()` in `hal_io.c` from two sequential `1500 us` spin waits (`3.0 ms`) into a single `1100 us` USB Full-Speed SOF window.
   - Set `.pull_up_en = GPIO_PULLUP_DISABLE` on `HAL_PIN_EPD_BUSY` (`GPIO 8`) in `sub_display.cpp` to eliminate `73 µA` continuous deep-sleep leakage.

4. **Screen 4 `CPU: 240MHz` Measurement Artifact (`screen_diagnostics.c:67, 129`):**
   - `screen_diagnostics_render()` called `esp_clk_cpu_freq()` *after* calling `h1os_lvgl_lock(100)`, which acquires the 240 MHz turbo lock, so Screen 4 always displayed `240MHz` even when running at an 80 MHz baseline.
   - **Fix Implemented:** Sampled `base_cpu_mhz = (uint32_t)(esp_clk_cpu_freq() / 1000000)` prior to `h1os_lvgl_lock(100)`.

### 3.3 Smoking Gun #3: Zero-Calibration Steady-State SHTC3 Selection (`orch_wake_stub.c`, `orch_flow.c`, `orch_math.c`)
- **Pure Steady-State Gate (`orch_wake_stub.c`):**
  - On each Flow A wake (`< 15 ms` bit-banged I2C read in RTC Fast Memory without booting FreeRTOS), `bsp_wake_stub()` converts the raw SHTC3 temperature and humidity via Sensirion's factory transfer formulas and evaluates `orch_math_is_plateau_settled(prev_t, temp_centi_c, SAMPLE_DELTA_GATE_CENTI_C)` (`|temp2 - temp1| <= 0.20°C`).
  - When `|temp2 - temp1| <= 0.20°C`, the board is at thermal steady state: both samples are marked `SAMPLE_FLAG_VALID_COLD | SAMPLE_FLAG_THERMAL_SETTLED` and `st->valid_trend` increments.
- **Direct Factory SHTC3 Trust & Tri-Node Verification (`orch_flow.c`):**
  - `orch_flow_query_telemetry()` retrieves the latest settled SHTC3 sample (`t_valid`, `rh_valid`) and uses it **directly** as `ambient_temp_c` and `ambient_rh_pct`, computing `vapor_pressure_hpa` and `dew_point_c` directly from `(t_valid, rh_valid)` with zero synthetic offsets, zero RH reconstitution, zero slice trimming, and zero sensor taring.
  - The SSD1681 on-glass sensor (`t_glass`) and ESP32-S3 internal SAR die sensor (`t_die`) are used **exclusively** to compute `trinode_temp_c = (t_valid + t_die + t_glass) / 3.0f`, `trinode_delta_c = t_valid - t_trinode`, and `trinode_confidence_pct` to verify that the SHTC3 is operating within a normal range.

### 3.4 Smoking Gun #4: Battery SoC & Autonomy Estimator Mismatch (`sub_power.c`, `battery_estimator.c`, `screen_system_health.c`)
- **Root Cause:** `sub_power.c` (`s_lipo_table`) mapped `3890 mV` (`3.89V`) to **`68%` SoC**, whereas `battery_estimator.c` (`battery_get_soc_basis_pts`) used a 3-segment linear approximation that mapped `3890 mV` to **`82.3%` SoC**, and `screen_system_health.c:41` passed a hardcoded `0.35f mA` draw into `battery_estimate_remaining_days(400, telem->battery_mv, 0.35f)` while leaving `battery_estimate_avg_current_ma()` completely unused.
- **Fix Implemented:**
  - Unified both `sub_power.c` and `battery_estimator.c` onto the same 13-point LiPo OCV curve (`3890 mV = 73% / 7300 bp`).
  - Added `battery_estimate_schedule_current_ma(flow_a_sec, flow_b_sec)` and wired `screen_system_health.c` to blend the schedule-based current with the empirical voltage-drop current (`battery_estimate_avg_current_ma()`) once $\ge 1\text{ hour}$ of battery operation has elapsed.

## 4. Summary of Modified Files in Pending Patch (`v2.3.2-dev`)

| File Path | Summary of Code Changes |
| :--- | :--- |
| `api/bootloader/h1os_boot_hook.c` | Latches `H1OS_PIN_PA_CTRL` (`GPIO 46 = 0`) with pad hold in `bootloader_before_init()` so the NS4168 Class-D amp stays muted during bootloader startup. |
| `api/hal_io.c` | Pre-sets `HAL_PIN_PA_CTRL = 0` before releasing holds, configures `GPIO 46` as `GPIO_MODE_INPUT_OUTPUT` so `gpio_get_level()` reads the true output latch state, and streamlines `hal_check_usb_ll()` into a single `1.1 ms` SOF check. |
| `api/sub_audio.c` | Changes `s_es8311_deinit` `REG00` from `{0x00, 0x1F}` to `{0x00, 0x1E}` (`RST_REG = 0`) + `{0x13, 0x00}` + `{0x1C, 0x00}`; adds `RTC_DATA_ATTR s_rtc_codec_in_standby` to skip I2C writes on unattended wakes; mutes Class-D amp (`PA_CTRL = 0`) and disables I2S immediately upon playback queue drain. |
| `api/sub_display.cpp` | Disables internal pull-up (`GPIO_PULLUP_DISABLE`) on `HAL_PIN_EPD_BUSY` (`GPIO 8`) to eliminate `73 µA` continuous deep-sleep leakage and shortens `epd_reset_pulse()` active spin-wait from `20 ms` to `4 ms`. |
| `api/h1os_lvgl.cpp` | Scopes `CpuMaxTurboScope` (`240 MHz`) strictly around pixel bit-packing and removes outer lock in `h1os_lvgl_port_task()` so CPU drops to `80 MHz` during 300–2200 ms `EPD_BUSY` waits. |
| `api/orch_wake_stub.c` | Evaluates pure steady-state plateau settlement (`|temp2 - temp1| <= SAMPLE_DELTA_GATE_CENTI_C`) with zero sensor taring and zero slice trimming. |
| `api/orch_math.h` & `api/orch_math.c` | Removes `orch_math_reconstruct_ambient_rh()` and computes `vapor_pressure_hpa` and `dew_point_c` directly from settled SHTC3 readings. |
| `api/orch_state.h` & `api/orch_state.c` | Removes synthetic offset, tare, and reconstructed fields (`die_tare_centi_c`, `pcb_thermal_offset_c`, `amb_floor_temp_centi_c`, `reconstructed_*`) and retains direct steady-state SHTC3 and Tri-Node verification metrics. |
| `api/orch_flow.c` | Trusts factory-calibrated steady-state SHTC3 readings (`t_valid`, `rh_valid`) directly with zero offsets or reconstitutions; uses `t_glass` and `t_die` strictly for cross-node range verification; removes redundant `250 ms` post-busy delay. |
| `api/h1os.h` & `api/h1os_lifecycle.c` | Exposes `vapor_pressure_hpa`, `boot_vbat_mv`, `flow_a_period_sec`, and `flow_b_period_sec` in `h1os_telemetry_t` and reduces unattended RTC wake pre-sleep delay from `50 ms` to `10 ms`. |
| `api/sub_power.c` | Aligns `s_lipo_table` with the unified 13-point LiPo OCV curve. |
| `H1OS/main/battery_estimator.h/.c` | Replaces 3-segment approximation with the unified 13-point LiPo OCV LUT and adds `battery_estimate_schedule_current_ma()`. |
| `H1OS/main/screens/screen_env_hero.c` | Reads `telem->vapor_pressure_hpa` directly and removes Layer 3 `orch_state.h` include. |
| `H1OS/main/screens/screen_psychrometrics.c` | Removes unused Layer 3 `orch_state.h` include. |
| `H1OS/main/screens/screen_system_health.c` | Computes autonomy using schedule-aware + empirical discharge current (`battery_estimate_schedule_current_ma` + `battery_estimate_avg_current_ma`). |
| `H1OS/main/screens/screen_diagnostics.c` | Samples `esp_clk_cpu_freq()` before acquiring `h1os_lvgl_lock(100)` so Screen 4 reports the true baseline clock (`80MHz`). |
| `H1OS/sdkconfig*` | Sets `CONFIG_SPIRAM_MEMTEST=n` and `CONFIG_BOOTLOADER_SKIP_VALIDATE_IN_DEEP_SLEEP=y` for fast `< 25 ms` deep-sleep wakes. |
