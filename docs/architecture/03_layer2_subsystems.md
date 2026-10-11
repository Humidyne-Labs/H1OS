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
Manages the electrophoretic particle state on the 200x200 panel.
- **Dual-RAM Architecture (Ping-Pong)**:
  - RAM 0x24 = New Frame Data.
  - RAM 0x26 = Old / Previous Frame Data.
  - Partial refreshes (~300ms) use differential hardware waveforms between 0x24 and 0x26.
- **Power Isolation**:
  - Puts panel into Deep Sleep Mode 1 (`0x10, 0x01` @ 1.0 µA) while keeping 3.3V rail latched.

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
  1. `0x3517` (Wakeup). Wait 250 µs.
  2. `0x609C` (Low-Power T-first, 1 ms measurement) or `0x7866` (Normal T-first).
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
- **12 dB ADC Curve Fitting**: Reads `GPIO 4` (ADC1_CH3) with 16-sample trimmed mean.
- **Zero-Volt Cable Guard**: If latch is asserted and $V_{\text{bat}} \approx 0\text{mV}$, detects instrument is running from USB VBUS without a battery; bypasses low-battery shutdown.
- **Hardware Sleep Entry**: Configures EXT1 wakeup and puts CPU into deep sleep.

```c
esp_err_t sub_power_init(void);
esp_err_t sub_power_deinit(void);
esp_err_t sub_power_read_battery(uint16_t *out_mv, uint8_t *out_pct);
bool      sub_power_is_usb_powered(void);
esp_err_t sub_power_enter_deep_sleep(uint32_t sleep_seconds, uint64_t ext1_pins_mask);
void      sub_power_cut_power_latch(void);
```

---

### 3.5 `sub_audio.c/.h` (Audio Codec & Amplifier Subsystem)
- **Zero-Heat Software Standby**: Keeps `PA_EN` (GPIO 42) low/energized while awake and writes Reg `0x0D = 0x01` to put ES8311 into software standby (<1.0 µA), preventing ESD diode I2C clamping.
- **Tone Synthesizer**: Generates hardware beeps and chimes via I2S.

```c
esp_err_t sub_audio_init(void);
esp_err_t sub_audio_deinit(void);
esp_err_t sub_audio_standby(void);
esp_err_t sub_audio_play_tone(uint32_t freq_hz, uint32_t duration_ms);
```

---

### 3.6 `sub_nvs.c/.h` (Persistent Configuration Subsystem)
Lightweight wrapper around ESP-IDF NVS flash for calibration offsets, baseline elevation, and user settings.

```c
esp_err_t sub_nvs_init(void);
esp_err_t sub_nvs_get_i32(const char *key, int32_t *out_val);
esp_err_t sub_nvs_set_i32(const char *key, int32_t val);
esp_err_t sub_nvs_get_str(const char *key, char *out_str, size_t max_len);
esp_err_t sub_nvs_set_str(const char *key, const char *str);
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
