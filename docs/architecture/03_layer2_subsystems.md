# Layer 2: Hardware Subsystem Managers Specification

## 1. Overview
Layer 2 comprises dedicated peripheral subsystem managers. Each subsystem driver controls one hardware domain using Layer 1 HAL primitives.
> **Invariant Rule:** Subsystems in Layer 2 are completely isolated from each other. The display driver does NOT talk to the power manager. The sensor driver does NOT inspect CPU frequency locks. All cross-subsystem coordination is handled by Layer 3.

---

## 2. File Manifest

| File | Subsystem | Key Responsibilities |
| :--- | :--- | :--- |
| `sub_display.cpp/.h` | E-Paper Display | SSD1681 200x200 controller, dual-RAM Ping-Pong buffer, partial LUT, Busy wait. |
| `sub_sensor.c/.h` | Environmental Sensors | SHTC3 raw I2C polling (`Wake` -> `Read` -> `Sleep`), MCU internal TSENS readout. |
| `sub_rtc.c/.h` | External RTC Chip | PCF85063A POSIX timekeeping, hardware alarms, countdown timer, interrupt clearing. |
| `sub_power.c/.h` | Power & Sleep Driver | Battery voltage ADC & LUT, EXT1 wake configuration, deep sleep hardware execution. |
| `sub_audio.c/.h` | Audio Chimes | Hardware buzzer synthesizer, standby mute control. |

---

## 3. Subsystem Specifications

### 3.1 `sub_display.cpp/.h` (SSD1681 1.54" E-Paper Display Manager)
Manages the electrophoretic particle state on the 200x200 panel.

- **Dual-RAM Architecture (Ping-Pong)**:
  - RAM 0x24 = New Frame Data.
  - RAM 0x26 = Old / Previous Frame Data.
  - Partial refreshes (~300ms) require SSD1681 to compute hardware differential waveforms between 0x24 and 0x26.
- **Framebuffer Ownership**:
  - Allocates two 5000-byte buffers in DMA-capable SRAM (`s_current_frame`, `s_previous_frame`).
  - Tracks dirty status internally (`s_dirty`).
- **FreeRTOS Synchronization**:
  - Employs a binary semaphore (`s_busy_sem`) signaled by a GPIO ISR on `GPIO 7` (`EPD_BUSY`) falling edge, eliminating CPU polling loops during OTP panel updates.

```cpp
esp_err_t sub_display_init(bool is_wake_cycle);
esp_err_t sub_display_deinit(void);

// Buffer manipulation
uint8_t*  sub_display_get_framebuffer(void);
void      sub_display_clear(uint8_t color);

// Physical refresh triggers
esp_err_t sub_display_refresh_full(void);
esp_err_t sub_display_refresh_partial(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
esp_err_t sub_display_wait_ready(TickType_t timeout_ticks);

// Power isolation
esp_err_t sub_display_enter_deep_sleep(void);

// On-glass temperature readout (Hardware SPI half-duplex)
esp_err_t sub_display_read_glass_temp(float *out_temp_c);
```

---

### 3.2 `sub_sensor.c/.h` (SHTC3 & Internal TSENS Manager)
Provides physical sensor readings without any algorithmic post-processing.

- **SHTC3 Pure Read Lifecycle**:
  1. I2C command `0x3517` (Wakeup SHTC3).
  2. Wait 250 µs.
  3. I2C command `0x5C24` (Precision T-first) or `0x609C` (Low-power T-first).
  4. Wait measurement duration (12 ms normal, 1 ms low-power).
  5. Read 6 bytes (`[Temp MSB, LSB, CRC]`, `[RH MSB, LSB, CRC]`).
  6. I2C command `0xB098` (Sleep SHTC3).
- **MCU Die Temperature**:
  - Reads ESP32-S3 internal analog TSENS via `esp_driver_tsens`.

```c
esp_err_t sub_sensor_init(void);
esp_err_t sub_sensor_read_shtc3_raw(uint16_t *out_raw_temp, uint16_t *out_raw_rh, bool low_power);
esp_err_t sub_sensor_read_mcu_die_temp(float *out_die_temp_c);
```

---

### 3.3 `sub_rtc.c/.h` (PCF85063A Real-Time Clock Manager)
Drives the ultra-low-power quartz RTC chip (`I2C Address 0x51`).

- **CLKOUT Parasitic Drain Elimination**:
  - Writes bits `COF[2:0] = 111` into register `0x01` (`Control_2`) to permanently disable the 32.768 kHz push-pull clock output, preventing continuous capacitive charge-discharge trace leakage.
- **Hardware Countdown Timer**:
  - Supports 1Hz resolution (1 to 255 seconds) and 1/60Hz resolution (1 to 255 minutes).
  - Drives open-drain interrupt line `GPIO 5` LOW on expiration.
- **Interrupt Servicing**:
  - `sub_rtc_get_and_clear_interrupts()` reads `Control_2` and clears `TF` (Timer Flag) and `AF` (Alarm Flag).
- **Time Remaining Query**:
  - `sub_rtc_get_remaining_seconds()` reads `Timer_value` and prescaler mode to return exact remaining sleep seconds for zero-hour collision prevention.

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
Governs battery monitoring, clock frequencies, sleep triggers, and ULP Sentinel configuration.

- **Battery ADC Sensing Architecture (Calibration, Gain, & Filtering)**:
  - **Hardware Hardware Attenuation (Gain)**: Configured for **`ADC_ATTEN_DB_12`** (0 to 3.1V input range). With the 1:2 external divider (100kΩ/100kΩ), this directly measures battery voltages up to 4.3V without saturation.
  - **Factory Calibration (eFuse Curve Fitting)**: Uses ESP32-S3 factory eFuse calibration curves (`esp_adc_cal_characteristics_t` or `adc_oneshot_get_calibrated_result`). Converts raw 12-bit ADC readings directly into calibrated millivolts, eliminating silicon process offset and gain errors.
  - **Pre-Sleep Calibration Hand-Off to ULP**: Prior to sleep, the main CPU calculates the linear calibration coefficients:
    $$V_{\text{bat\_mV}} = \text{raw} \times m_{\text{scale}} + b_{\text{offset}}$$
    and writes them into `orch_persisted_state_t` in RTC Slow Memory.
  - **Filtering**:
    - *Main CPU:* 16-sample multisampling with trimmed outlier rejection.
    - *ULP Sentinel:* 4-sample boxcar average + running EWMA filter in RTC Slow Memory to reject load step transients from RF bursts.
  - **LiPo OCV Lookup Table**: Maps calibrated voltage across a 10-point Li-Po discharge curve (3.27V = 0% critical shutdown, 3.70V = 50% nominal, 4.20V = 100% full).
- **Sleep Execution**:
  - Configures EXT1 wakeup bitmask (`GPIO 0` BOOT, `GPIO 18` BAT_KEY, `GPIO 5` RTC INT).
  - Configures ULP Sentinel wake trigger.
  - Sets RTC pad holds on `GPIO 17` (`BAT_CTRL`), `GPIO 11` (`EPD_CS`), and `GPIO 9` (`EPD_RST`).
  - Calls `esp_deep_sleep_start()`.

```c
esp_err_t sub_power_init(void);
esp_err_t sub_power_read_battery(uint16_t *out_mv, uint8_t *out_pct);
esp_err_t sub_power_configure_ulp_sentinel(void);
esp_err_t sub_power_enter_deep_sleep(void);
esp_err_t sub_power_power_off(void);
```
esp_err_t sub_power_get_battery_mv(uint32_t *out_mv);
uint8_t   sub_power_get_battery_percent(void);

// Hardware Sleep Entry
esp_err_t sub_power_enter_deep_sleep(uint32_t timer_seconds, uint64_t ext1_pins_mask);
esp_err_t sub_power_enter_light_sleep(uint32_t timer_seconds, uint64_t gpio_pins_mask);

// Physical Power Cut
void      sub_power_drop_power_latch(void);
```
