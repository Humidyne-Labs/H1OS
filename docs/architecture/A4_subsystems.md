# Layer 2: Hardware Subsystem Managers Specification

## 1. Overview
Layer 2 comprises dedicated peripheral subsystem managers ("Does the thing"). Each subsystem controls one hardware domain using Layer 1 HAL primitives.
> **Invariant Rule:** Subsystems in Layer 2 are completely isolated from each other. The display driver does NOT talk to the power manager. The sensor driver does NOT inspect CPU frequency locks. All cross-subsystem coordination is handled by Layer 3 Orchestrator.

---

## 2. File Manifest

| File | Subsystem | Key Responsibilities |
| :--- | :--- | :--- |
| `sub_display.cpp/.h` | E-Paper Display | SSD1681 200x200 controller, dual-RAM Ping-Pong buffer, partial LUT, Busy wait. |
| `sub_sensor.c/.h` | Environmental Sensors | SHTC3 raw I2C polling (`Wake` -> `Read` -> `Sleep`), MCU internal TSENS readout. |
| `sub_rtc.c/.h` | External RTC Chip | PCF85063A POSIX timekeeping, hardware alarms, countdown timer, interrupt clearing. |
| `sub_power.c/.h` | Power & Sleep Driver | Battery voltage ADC, Zero-Volt Cable Guard, deep sleep hardware execution. |
| `sub_audio.c/.h` | Audio Chimes | ES8311 software standby, NS4168 amp mute, synthesized tone generator. |
| `sub_nvs.c/.h` | Persistent Storage | NVS flash key-value wrapper for calibration offsets and user preferences. |
| `sub_sdcard.c/.h` | Removable Storage | Basic 1-bit SDMMC FATFS manager: file I/O, format, capacity check. |

---

## 3. Subsystem Specifications

### 3.1 `sub_display.cpp/.h` (SSD1681 1.54" E-Paper Display Manager)
Manages the electrophoretic particle state on the 200x200 non-touch panel.
- **Dual-RAM Architecture (Ping-Pong)**:
  - RAM `0x24` = New Frame Data.
  - RAM `0x26` = Old / Previous Frame Data.
  - Partial refreshes use differential hardware waveforms between `0x24` and `0x26`.
- **Power Isolation**:
  - Puts panel into Deep Sleep Mode 1 (`0x10, 0x01`) while keeping 3.3V rail latched.

```cpp
esp_err_t sub_display_init(bool is_wake_cycle);
esp_err_t sub_display_deinit(void);

uint8_t*  sub_display_get_framebuffer(void);
void      sub_display_clear(uint8_t color);

esp_err_t sub_display_refresh_full(void);
esp_err_t sub_display_refresh_partial(void);
esp_err_t sub_display_wait_busy(TickType_t timeout_ticks);
esp_err_t sub_display_enter_deep_sleep(void);
esp_err_t sub_display_read_glass_temp(float *out_temp_c);
```

---

### 3.2 `sub_sensor.c/.h` (SHTC3 & Internal TSENS Manager)
Provides physical sensor readings without algorithmic post-processing.
- **SHTC3 Pure Read Lifecycle**:
  1. `0x3517` (Wakeup).
  2. `0x7866` (Normal Power Mode T-first for full ADC resolution) or `0x609C` (Low-Power Mode T-first).
  3. Read 6 bytes (`[Temp MSB, LSB, CRC]`, `[RH MSB, LSB, CRC]`).
  4. `0xB098` (Sleep).

```c
esp_err_t sub_sensor_init(void);
esp_err_t sub_sensor_deinit(void);
esp_err_t sub_sensor_read_shtc3_raw(uint16_t *out_raw_temp, uint16_t *out_raw_rh, bool low_power);
void      sub_sensor_convert_shtc3_units(uint16_t raw_temp, uint16_t raw_rh, float *out_temp_c, float *out_rh_pct);
esp_err_t sub_sensor_read_mcu_die_temp(float *out_die_temp_c);
```

---

### 3.3 `sub_rtc.c/.h` (PCF85063A Real-Time Clock Manager)
Drives the ultra-low-power quartz RTC chip (`I2C Address 0x51`).
- **CLKOUT Parasitic Drain Elimination**: Writes `COF[2:0] = 111` to Reg `0x01` (`Control_2`) to permanently disable 32.768 kHz square wave output.
- **Hardware Countdown & Alarm**: Drives open-drain interrupt line `GPIO 5` LOW on expiration.

```c
esp_err_t sub_rtc_init(void);
esp_err_t sub_rtc_get_time(struct tm *out_time);
esp_err_t sub_rtc_set_time(const struct tm *time);
esp_err_t sub_rtc_arm_countdown(uint32_t seconds);
esp_err_t sub_rtc_cancel_countdown(void);
esp_err_t sub_rtc_get_remaining_seconds(uint32_t *out_sec);
esp_err_t sub_rtc_get_and_clear_interrupts(bool *out_alarm, bool *out_timer);
```

---

### 3.4 `sub_power.c/.h` (Battery Monitor & Sleep Execution Driver)
- **Exclusive ULP Quiet-State Sensing**: Retired main CPU ADC reads during active run; reads resting battery terminal voltage from the 8-entry ULP-RISC-V Slow SRAM ring buffer (`ulp_vbat_ring[8]`), eliminating active $I \cdot R$ load sag. See [A8 Battery Metrology & Autonomy Engine](A8_battery_and_power_management.md).
- **Single 13-Point LiPo OCV Lookup Curve**: Piecewise linear interpolation mapping resting terminal millivolts to 0..100% SoC.
- **Battery State Machine**: Evaluates $\Delta V$ over sleep cycles to classify `H1OS_BATTERY_DISCHARGING`, `H1OS_BATTERY_CHARGING`, and `H1OS_BATTERY_CHARGED`.
- **Two-Level Empirical Autonomy Engine**: Computes Level 1 macro flight current ($I_{\text{wall}}$), remaining operating days ($\text{Days}_{\text{rem}}$), and Level 2 active execution task fractions with zero hardcoded currents.
- **Hardware Sleep Entry**: Configures EXT1 wakeup, RTC IO pad holds, and enters deep sleep.
- **Dynamic Frequency Scaling (DFS)**: Gates CPU cores to an 80 MHz baseline during quiescent wait/polling periods, while providing `sub_power_cpu_max_acquire()` and `sub_power_cpu_max_release()` to burst the clock to 240 MHz turbo during compute-heavy operations (LVGL rendering blitz and I2S audio synthesis).

```c
esp_err_t sub_power_init(void);
esp_err_t sub_power_deinit(void);
esp_err_t sub_power_get_battery_status(uint16_t *out_mv, uint8_t *out_pct, h1os_battery_state_t *out_state);
esp_err_t sub_power_read_battery(uint16_t *out_mv, uint8_t *out_pct);
void      sub_power_calc_autonomy(uint16_t initial_soc_x10, uint16_t current_soc_x10, uint32_t total_sleep_sec, uint32_t total_ulp_ms, uint32_t total_stub_ms, uint32_t total_app_ms, h1os_autonomy_metrics_t *out_metrics);
bool      sub_power_connected_usb(void);
esp_err_t sub_power_enter_deep_sleep_mode(uint32_t sleep_seconds, uint64_t ext1_pins_mask, sub_power_sleep_mode_t mode);
esp_err_t sub_power_enter_deep_sleep(uint32_t sleep_seconds, uint64_t ext1_pins_mask);
void      sub_power_cut_power_latch(void);
esp_err_t sub_power_init_dfs(sys_clk_mode_t mode);
esp_err_t sub_power_cpu_max_acquire(void);
esp_err_t sub_power_cpu_max_release(void);
```

---

### 3.5 `sub_audio.c/.h` (Audio Codec & Amplifier Subsystem)
- **Software Standby**: Keeps `PA_EN` (`GPIO 42`) held LOW and writes the ES8311 software standby register sequence to avoid ESD diode I2C clamping (see [Errata E4](../../ERRATA.md#errata-e4-audio-codec-power-gating-clamps-shared-i2c-bus-to-07v)).
- **Tone Synthesizer**: Generates hardware beeps and chimes via I2S.
- **I2S Playback Clock Lock Invariant**: During I2S audio initialization and tone/chime playback, `sub_power_cpu_max_acquire()` is held to guarantee the system PLL runs at full 240 MHz clock speed. Without this clock lock, APB frequency droop during DFS drops the I2S MCLK/BCLK dividers, causing playback pitch to shift octaves lower and introducing DMA buffer underruns.

```c
esp_err_t sub_audio_init(void);
esp_err_t sub_audio_deinit(void);
esp_err_t sub_audio_standby(void);
esp_err_t sub_audio_play(sub_audio_type_t type, const void *data, size_t len);
bool      sub_audio_is_busy(void);
esp_err_t sub_audio_wait_idle(uint32_t timeout_ms);
esp_err_t sub_audio_set_volume(uint8_t volume_pct);
uint8_t   sub_audio_get_volume(void);
```

---

### 3.6 `sub_nvs.c/.h` (Persistent Configuration Subsystem)
Lightweight wrapper around ESP-IDF NVS flash for calibration offsets, baseline elevation, and user settings.

```c
esp_err_t sub_nvs_init(void);
esp_err_t sub_nvs_get_u32(const char *key, uint32_t *out_val);
esp_err_t sub_nvs_set_u32(const char *key, uint32_t val);
esp_err_t sub_nvs_get_str(const char *key, char *out_str, size_t max_len);
esp_err_t sub_nvs_set_str(const char *key, const char *str);
esp_err_t sub_nvs_get_blob(const char *key, void *out_data, size_t *inout_len);
esp_err_t sub_nvs_set_blob(const char *key, const void *data, size_t len);
```

---

### 3.7 `sub_sdcard.c/.h` (Removable Storage Subsystem)
Basic 1-bit SDMMC FATFS manager for offline flight telemetry logging.
- Only implements basic essentials: file I/O, format, and capacity checking.

```c
esp_err_t sub_sdcard_mount(void);
esp_err_t sub_sdcard_unmount(void);
bool      sub_sdcard_is_mounted(void);
esp_err_t sub_sdcard_get_capacity(uint64_t *out_total_bytes, uint64_t *out_free_bytes);
esp_err_t sub_sdcard_format(void);
```
