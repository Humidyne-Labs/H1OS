# Layer 2: Hardware Subsystem Managers Specification

## 1. Overview
Layer 2 comprises dedicated peripheral subsystem managers ("Does the thing"). Each subsystem controls one hardware domain using Layer 1 HAL primitives.
> **Invariant Rule:** Subsystems in Layer 2 are completely isolated from each other. The display driver does NOT talk to the power manager. The audio driver manages its own dedicated PM lock rather than calling `sub_power`. All cross-subsystem coordination is handled by Layer 3 Orchestrator.

---

## 2. File Manifest

| File | Subsystem | Key Responsibilities |
| :--- | :--- | :--- |
| `sub_display.cpp/.h` | E-Paper Display | SSD1681 200x200 controller, dual-RAM Ping-Pong buffer, partial LUT, Busy wait, pre-display on-glass temperature read (`0x1B`). |
| `sub_rtc.c/.h` | External RTC Chip | PCF85063A POSIX timekeeping, hardware countdown timer, interrupt clearing, 32.768 kHz `CLKOUT` disable (`COF=0x07`). |
| `sub_power.c/.h` | Power & Sleep Driver | ULP quiet-state battery voltage retrieval, 13-point LiPo OCV lookup, Elapsed Runtime Empirical Autonomy Engine, DFS, Pure Event Mode deep sleep execution. |
| `sub_audio.c/.h` | Audio Chimes & PCM | ES8311 software standby (`<1.0 µA`), NS4168 amp mute, background FreeRTOS worker, synthesized tones/chimes, and PCM playback. |
| `sub_nvs.c/.h` | Persistent Storage | NVS flash key-value wrapper for cumulative battery runtimes and user settings. |
| `sub_sdcard.c/.h` | Removable Storage | Asynchronous and synchronous 1-bit SDMMC FATFS manager: mount, unmount, format, capacity check. |

*(Note: Physical SHTC3 and internal ESP32-S3 SAR TSENS acquisition execute exclusively inside the bare-metal Layer 3 RTC Wake Stub [`orch_wake_stub.c`] during deep-sleep Flow A bursts to prevent main-CPU self-heating.)*

---

## 3. Subsystem Specifications

### 3.1 `sub_display.cpp/.h` (SSD1681 1.54" E-Paper Display Manager)
Manages the electrophoretic particle state on the 200x200 non-touch panel.
- **Dual-RAM Architecture (Ping-Pong)**:
  - RAM `0x24` = New Frame Data.
  - RAM `0x26` = Old / Previous Frame Data.
  - Partial refreshes use differential hardware waveforms between `0x24` and `0x26`.
- **Pre-Display Glass Thermistor Capture (`0x1B`)**:
  - Reads the internal SSD1681 temperature sensor during `sub_display_init()` prior to any frame transfer or charge-pump activation and caches the reading in centi-°C (`sub_display_get_glass_temp_centi_c()`).
- **Power Isolation**:
  - Puts panel into Deep Sleep Mode 1 (`0x10, 0x01`) while keeping 3.3V rail latched.

```cpp
esp_err_t sub_display_init(bool is_wake_cycle);
esp_err_t sub_display_deinit(void);

uint8_t  *sub_display_get_framebuffer(void);
void      sub_display_clear(uint8_t color);
esp_err_t sub_display_sync_previous_frame(const uint8_t *prev_frame);

esp_err_t sub_display_wait_busy(TickType_t timeout_ticks);
esp_err_t sub_display_refresh_full(void);
esp_err_t sub_display_clear_to_white_full(void);
esp_err_t sub_display_refresh_partial(void);
esp_err_t sub_display_read_glass_temp(float *out_temp_c);
int16_t   sub_display_get_glass_temp_centi_c(void);
esp_err_t sub_display_enter_deep_sleep(void);
```

---

### 3.2 `sub_rtc.c/.h` (PCF85063A Real-Time Clock Manager)
Drives the ultra-low-power quartz RTC chip (`I2C Address 0x51`).
- **CLKOUT Parasitic Drain Elimination**: Writes `COF[2:0] = 111` (`0x07`) to Reg `0x01` (`Control_2`) to permanently disable 32.768 kHz square wave output.
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

### 3.3 `sub_power.c/.h` (Battery Monitor & Sleep Execution Driver)
- **Exclusive ULP Quiet-State Sensing**: Retired main CPU ADC reads during active run; reads resting battery terminal voltage from the 8-entry ULP-RISC-V Slow SRAM ring buffer (`ulp_vbat_ring[8]`), eliminating active $I \cdot R$ load sag. See [A8 Battery Metrology & Autonomy Engine](A8_battery_and_power_management.md).
- **Single 13-Point LiPo OCV Lookup Curve**: Piecewise linear interpolation mapping resting terminal millivolts to tenths of a percent (`0..1000 = 0.0%..100.0%` via `sub_power_mv_to_soc_tenths()`) and rounded integer percent (`0..100%`).
- **Battery State Machine & Zero-Volt Cable Guard**: Evaluates USB host status and $\Delta V$ over 2 sleep cycles to classify `H1OS_BATTERY_DISCHARGING`, `H1OS_BATTERY_CHARGING`, and `H1OS_BATTERY_CHARGED`. Forces `4200 mV` (`100% CHARGED`) when running on USB bench power without a LiPo cell attached.
- **Elapsed Runtime Empirical Autonomy Engine**: Computes average current draw over total elapsed runtime (`avg_draw_ma`), consumed capacity (`mah_spent_lap`), and remaining operating days (`autonomy_days`) with zero hardcoded currents.
- **Hardware Sleep Entry**: Isolates static pads, drains `/INT` and button lines HIGH, arms ULP GPIO wakeup in Pure Event Mode, and enters deep sleep.
- **Dynamic Frequency Scaling (DFS)**: Configures CPU clock scaling (`SYS_CLK_MODE_DYNAMIC`, `FIXED_MAX`, `FIXED_MIN`) and provides `sub_power_cpu_max_acquire()` / `sub_power_cpu_max_release()` for 240 MHz compute bursts.

```c
esp_err_t sub_power_init(void);
esp_err_t sub_power_deinit(void);
esp_err_t sub_power_get_battery_status(uint16_t *out_mv, uint8_t *out_pct, h1os_battery_state_t *out_state);
uint16_t  sub_power_mv_to_soc_tenths(uint16_t mv);
void      sub_power_calc_autonomy(uint16_t initial_soc_x10, uint16_t current_soc_x10, uint32_t total_sleep_sec, uint32_t total_app_ms, h1os_autonomy_metrics_t *out_metrics);
esp_err_t sub_power_read_battery(uint16_t *out_mv, uint8_t *out_pct);
esp_err_t sub_power_get_ulp_cal_params(uint32_t *out_scale, int32_t *out_offset_mv);
esp_err_t sub_power_init_ulp(uint32_t flow_a_period_sec);
void      sub_power_set_sleep_slices(uint32_t flow_a_sec, uint32_t flow_b_sec, uint32_t overflow, uint32_t remainder_sec);
esp_err_t sub_power_enter_deep_sleep_mode(uint32_t sleep_seconds, uint64_t ext1_pins_mask, sub_power_sleep_mode_t mode);
esp_err_t sub_power_enter_deep_sleep(uint32_t sleep_seconds, uint64_t ext1_pins_mask);
void      sub_power_cut_power_latch(void);
bool      sub_power_connected_usb(void);
esp_err_t sub_power_init_dfs(sys_clk_mode_t mode);
esp_err_t sub_power_cpu_max_acquire(void);
esp_err_t sub_power_cpu_max_release(void);
```

---

### 3.4 `sub_audio.c/.h` (Audio Codec & Amplifier Subsystem)
- **Software Standby**: Keeps `PA_EN` (`GPIO 42`) held LOW and writes the ES8311 software standby register sequence (`0x0D = 0xFC`, `0x00 = 0x1E` with `RST_REG = 0`) to avoid ESD diode I2C clamping while keeping standby draw $<1.0\ \mu\text{A}$ (see [Errata E4](../../ERRATA.md#errata-e4-audio-codec-power-gating-clamps-shared-i2c-bus-to-07v)).
- **Unified Asynchronous Dispatcher**: Dispatches synthesized tones (`SUB_AUDIO_TONE`), chimes (`SUB_AUDIO_CHIME`), and raw 16-bit PCM streams (`SUB_AUDIO_PCM`) to `h1os_audio_worker` via `sub_audio_play()`, flushing a silent DMA frame upon queue completion so trailing notes never clip.
- **I2S Playback Clock Lock Invariant**: Holds a dedicated `ESP_PM_CPU_FREQ_MAX` lock during I2S initialization and playback to prevent APB frequency droop from shifting sample pitch or underrunning DMA buffers.

```c
esp_err_t sub_audio_init(uint8_t volume_pct);
esp_err_t sub_audio_standby(void);
esp_err_t sub_audio_deinit(void);
esp_err_t sub_audio_wait_until_ready(uint32_t timeout_ms);
bool      sub_audio_is_ready(void);
esp_err_t sub_audio_play(sub_audio_type_t type, const void *data, size_t len);
bool      sub_audio_is_busy(void);
esp_err_t sub_audio_wait_idle(uint32_t timeout_ms);
esp_err_t sub_audio_set_volume(uint8_t volume_pct);
uint8_t   sub_audio_get_volume(void);
esp_err_t sub_audio_set_low_power_mode(bool enable);
bool      sub_audio_get_low_power_mode(void);
```

---

### 3.5 `sub_nvs.c/.h` (Persistent Configuration Subsystem)
Lightweight wrapper around ESP-IDF NVS flash (`SUB_NVS_NAMESPACE = "h1os"`) for cumulative battery runtimes and user settings.

```c
esp_err_t sub_nvs_init(void);
esp_err_t sub_nvs_set_str(const char *key, const char *value);
esp_err_t sub_nvs_get_str(const char *key, char *out_val, size_t max_len);
esp_err_t sub_nvs_set_u32(const char *key, uint32_t value);
esp_err_t sub_nvs_get_u32(const char *key, uint32_t *out_val);
esp_err_t sub_nvs_set_blob(const char *key, const void *data, size_t len);
esp_err_t sub_nvs_get_blob(const char *key, void *out_data, size_t *inout_len);
esp_err_t sub_nvs_erase_key(const char *key);
esp_err_t sub_nvs_erase_all(void);
```

---

### 3.6 `sub_sdcard.c/.h` (Removable Storage Subsystem)
1-bit SDMMC FATFS manager for offline telemetry logging. Supports non-blocking background mounting (`sub_sdcard_mount_async()`) with absent-card latching and safe unmount synchronization.

```c
esp_err_t sub_sdcard_mount(void);
esp_err_t sub_sdcard_mount_async(void);
esp_err_t sub_sdcard_unmount(void);
bool      sub_sdcard_is_mounted(void);
esp_err_t sub_sdcard_get_capacity_mb(uint32_t *out_capacity_mb);
esp_err_t sub_sdcard_format(void);
```
