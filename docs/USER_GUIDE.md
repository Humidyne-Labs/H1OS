# 📖 ESP32-S3 ePaper BSP Reference Manual & Developer Guide

**Target Hardware:** Waveshare ESP32-S3 ePaper 1.54" V2 (ESP32-S3-PICO-1-N8R8)  
**Firmware Version:** `v1.3.1`  
**Supported Frameworks:** ESP-IDF `v5.1+`, `v5.3+`, `v6.1` | LVGL `v9.6.0`  
**License:** MIT

---

## 📑 Table of Contents

1. [Architectural Overview](#1-architectural-overview)
2. [Lifecycle Engine & Application Entry](#2-lifecycle-engine--application-entry)
3. [Dynamic Initialization Profiles](#3-dynamic-initialization-profiles)
4. [Low-Power Sleep Subsystem & Scheduling](#4-low-power-sleep-subsystem--scheduling)
5. [Autonomous Background Sub-Execution (<10ms Cadence)](#5-autonomous-background-sub-execution-10ms-cadence)
6. [Environmental Sensing & Psychrometric Engine](#6-environmental-sensing--psychrometric-engine)
7. [Display Driver & LVGL v9 Integration](#7-display-driver--lvgl-v9-integration)
8. [Power Domain Full (PD_FULL) Performance Scaling](#8-power-domain-full-pd_full-performance-scaling)
9. [Power Management, Battery ADC & Power-Off](#9-power-management-battery-adc--power-off)
10. [Complete Production Application Template](#10-complete-production-application-template)

---

## 1. Architectural Overview

The Waveshare ESP32-S3 ePaper 1.54" V2 development platform is a reference implementation for Class-E environmental telemetry:
- **Compute Module:** Espressif Systems ESP32-S3-PICO-1-N8R8 (Xtensa dual-core LX7 @ up to 240 MHz, 8 MB SPI Flash, 8 MB Octal PSRAM).
- **Display Subsystem:** 200×200 pixel monochrome Solomon Systech SSD1681 bi-stable e-Paper display with dual-plane RAM persistence (`0x24` & `0x26`) via dedicated flash partition (`epd_frame`).
- **Environmental Sensing:** Sensirion SHTC3 (I2C `0x70`), SSD1681 On-Glass thermal sensor (SPI `0x1B`), and ESP32-S3 internal silicon die TSENS.
- **Precision Timing:** NXP PCF85063A calendar RTC with 32.768 kHz quartz oscillator, hardware countdown timer, and alarms.
- **Power Architecture:** Discrete LDO power-hold latch (`GPIO 17`), battery voltage ADC divider (`GPIO 4`, ADC1 CH3), and user status LED (`GPIO 3`).

```
┌─────────────────────────────────────────────────────────────────────────────────┐
│                                ESP32-S3 DUAL-CORE LX7                           │
├────────────────────────────────────────┬────────────────────────────────────────┤
│          CORE 0: NETWORKING & CLOUD    │           CORE 1: UI & SENSORS         │
├────────────────────────────────────────┼────────────────────────────────────────┤
│ • Wi-Fi Station (Fast Reconnect <400ms)│ • LVGL v9 Display Port Task (Pri 5)    │
│ • BLE GATT Provisioning (wifi_prov)    │ • SSD1681 1-bit Mono EPD Bit-Blit SPI  │
│ • SNTP Network Time Synchronization    │ • Tactile Button State Handlers        │
│ • ThingsBoard Secure MQTTS (Port 8883) │ • SHTC3 Sensor I2C Acquisition         │
│ • Remote Firmware HTTPS OTA Worker     │ • ES8311 Codec & NS4168 Audio Synth    │
│ • Low-Power Sleep Transitions          │ • Zero-Copy Flash Asset Rendering      │
└────────────────────────────────────────┴────────────────────────────────────────┘
```

---

## 2. Lifecycle Engine & Application Entry

The BSP employs an event-driven lifecycle engine with hardware-level pre-execution interception. Instead of custom boot branching in `app_main()`, applications declare a [`bsp_app_lifecycle_t`](components/esp32-s3_bsp/include/bsp/bsp.h) struct and call [`bsp_app_start()`](components/esp32-s3_bsp/src/bsp_common.c):

```c
#include "bsp/bsp.h"

static void app_on_pxe(bsp_button_mask_t btn_mask, void *user_data)
{
    ESP_LOGI("APP", "Pre-Execution Hook (PXE): btn_mask=0x%02X", btn_mask);
    if (btn_mask & BSP_BUTTON_MASK_BOOT) {
        ESP_LOGI("APP", "BOOT button held during power-on / wake!");
    }
}

static void app_on_boot(void *user_data)
{
    ESP_LOGI("APP", "Boot initialized - initial system startup");
    // Run initial setup & first UI draw
}

static void app_on_wake(const bsp_wake_context_t *ctx, void *user_data)
{
    ESP_LOGI("APP", "Wake initialized: cause=%d, from_button=%s", 
             ctx->wake_cause, ctx->woke_from_button ? "YES" : "NO");
    // Run scheduled UI refresh cycle (EPD partial update)
}

static void app_on_sleep(bsp_sleep_mode_t mode, uint32_t duration_sec, void *user_data)
{
    ESP_LOGI("APP", "Entering sleep (%s, %lu s)...", (mode == BSP_SLEEP_MODE_DEEP) ? "DEEP" : "LIGHT", (unsigned long)duration_sec);
}

static void app_on_power_off(void *user_data)
{
    ESP_LOGI("APP", "System powering off - draw final persistent screen");
}

void app_main(void)
{
    bsp_app_lifecycle_t lifecycle = {
        .on_pxe              = app_on_pxe,
        .on_boot             = app_on_boot,
        .on_wake             = app_on_wake,
        .on_sleep            = app_on_sleep,
        .on_power_off        = app_on_power_off,
        .default_chime_mask  = BSP_CHIME_MASK_BOOT | BSP_CHIME_MASK_POWER_OFF,
        .user_data           = NULL,
    };
    bsp_app_start(&lifecycle);
}
```

### Two-Phase IO Bring-Up & Bootloader Hardware Latch
1. **BSP Bootloader Power Hook ([`bootloader_components/bsp_boot_hook`](components/esp32-s3_bsp/bootloader_components/bsp_boot_hook))**: Automatically registered via `BOOTLOADER_EXTRA_COMPONENT_DIRS`. Drives `GPIO 17` (`BSP_PIN_POWER_HOLD`) HIGH and engages the hardware RTC pad hold latch (`gpio_ll_hold_en`) in `bootloader_before_init()` within $\approx 25\,\text{ms}$ of power-on. The pin remains hardware-latched HIGH across all resets, CPU frequency shifts, and deep sleep cycles.
2. **Phase 1: Early IO (`bsp_io_early_init()`)**: Unlatches pad holds exclusively on the tactile buttons (`GPIO 0`, `GPIO 18`) and `GPIO 5` (`RTC_INT`), enables internal pull-ups, and executes `.on_pxe(btn_mask)` with zero delay.
3. **Phase 2: Master IO (`bsp_init_io()`)**: Configures all remaining peripheral pins (EPD, I2C, I2S, PA, SD) and settles power rails.
4. **Power Off (`bsp_power_off()`)**: Releases the pad hold and drives `GPIO 17` LOW to cut battery LDO power.

---

## 3. Dynamic Initialization Profiles

The initialization profile configures the minimal set of hardware resources required for each operating phase:

- **`BSP_INIT_MODE_BOOT`**: Full hardware bringup (Power, I2C, SHTC3, RTC, Buttons, Audio, EPD display OTP clear, and LVGL task).
- **`BSP_INIT_MODE_WAKE`**: Fast hardware bringup (Power, I2C, SHTC3, RTC, Buttons, Audio, EPD display fast partial update, and LVGL task). Retains persistent display buffers.
- **`BSP_INIT_MODE_SUB_EXEC`**: Minimal headless profile ($<10\text{ ms}$ on-time at 80 MHz). Powers shared I2C bus and SHTC3 only. Display, LVGL, buttons, and audio are completely bypassed.

---

## 4. Low-Power Sleep Subsystem & Scheduling

The BSP establishes a strict domain separation between internal and external timers:
1. **Internal RTC Sleep Timer:** Used for background sub-execution sensor sampling while the user UI sleeps.
2. **External PCF85063A Hardware RTC:** Driven by the 32.768 kHz quartz crystal, reserved for scheduled UI display wakeups.

### Hardware Sleep Bounds
- **`BSP_SLEEP_MIN_DURATION_SEC`:** `1` second (Hardware 1Hz prescaler limit)
- **`BSP_SLEEP_MAX_DURATION_SEC`:** `15300` seconds (255 minutes / 4.25 hours)

### Entering Sleep
```c
bsp_sleep_config_t sleep_cfg = {
    .mode                   = BSP_SLEEP_MODE_DEEP,
    .duration_sec           = 60,                        // Internal 60s sub-execution cadence
    .rtc_alarm_duration_sec = 300,                       // 300s (5-minute) PCF85063A Countdown Timer
    .wake_sources           = BSP_WAKE_SRC_TIMER | BSP_WAKE_SRC_EXTERNAL_RTC | BSP_WAKE_SRC_BUTTONS,
    .next_init_mode         = BSP_INIT_MODE_SUB_EXEC,
};
bsp_sleep(&sleep_cfg);
```

---

## 5. Autonomous Background Sub-Execution (<10ms Cadence)

### The Self-Heating Challenge
The SHTC3 sensor is situated on the shared ground copper plane directly adjacent to the ESP32-S3 SoC, onboard 3.3V LDO, and display boost circuit. Active CPU run time (+1.5°C to +3.0°C) depresses the raw relative humidity reading.

### Sub-Execution Operation
When armed via `bsp_sensors_arm_sub_execution(60)`:
1. The MCU wakes from deep sleep at 80 MHz baseline frequency.
2. `bsp_app_start()` detects the timer wake and runs `bsp_sub_execution_init()`.
3. Samples raw temperature and RH words from SHTC3 in $<10\text{ ms}$.
4. Evaluates the integer raw differential gate and logs to the 64-slot ring buffer in RTC Slow Memory.
5. Immediately returns to deep sleep. The application `.on_wake()` hook is **never** invoked for headless sub-executions.

---

## 6. Environmental Sensing & Psychrometric Engine

The psychrometric engine calculates invariant thermodynamic quantities without runtime I2C polling:

```c
#include "bsp/bsp_sensors.h"

bsp_shtc3_data_t data = {0};
esp_err_t ret = bsp_sensors_read(&data, false);

if (ret == ESP_OK && data.valid) {
    float temp_c   = data.temperature_c;        // Reconstructed Ambient Temp (°C)
    float temp_f   = data.temperature_f;        // Reconstructed Ambient Temp (°F)
    float rh_pct   = data.humidity_percent;     // True Ambient Relative Humidity (% RH)
    float dew_pt_c = data.dew_point_c;          // Physical Invariant Dew Point (°C)
    float abs_hum  = data.absolute_humidity_g;  // Absolute Humidity (g/m³)
    uint8_t conf   = data.confidence_pct;       // Dynamic Confidence Score (0-100%)
}

// Access 64-entry RTC Slow Memory History:
const bsp_env_telemetry_history_t *history = bsp_sensors_get_telemetry_history();
```

---

## 7. Display Driver & LVGL v9 Integration

The display port drives the 200×200 monochrome SSD1681 panel with thread-safe LVGL v9 integration:

```c
#include "bsp/bsp_lvgl.h"
#include "lvgl.h"

bsp_lvgl_lock();
lv_obj_t *scr = lv_screen_active();
lv_obj_clean(scr);

lv_obj_t *lbl = lv_label_create(scr);
lv_label_set_text_fmt(lbl, "%.1f°F | %.1f%%", temp_f, rh_pct);
lv_obj_align(lbl, LV_ALIGN_CENTER, 0, 0);

bsp_lvgl_unlock();
```

---

## 8. Power Domain Full (PD_FULL) Performance Scaling

For compute-intensive operations (LVGL rendering, font blitting, and SPI transfers), assert the `PD_FULL` performance lock:

```c
bsp_pm_pd_full_acquire();
// High-speed rendering & SPI transfers at 240 MHz
bsp_delay_ms(1200);
bsp_pm_pd_full_release(); // Drops back to 80 MHz baseline
```

> **Note:** The BSP strictly blocks physical I2C sensor acquisitions while `bsp_pm_is_pd_full_active()` is true to protect sensor data integrity.

---

## 9. Power Management, Battery ADC & Power-Off

### Battery Voltage & SoC Monitoring
```c
#include "bsp/bsp_power.h"

uint32_t vbat_mv = 0;
bsp_battery_get_voltage(&vbat_mv, NULL);
uint8_t batt_pct = bsp_battery_get_percentage(); // 0-100% based on LiPo OCV LUT

if (batt_pct <= 10 || vbat_mv < 3400) {
    ESP_LOGW("PWR", "Battery depleted: executing safe power off");
    bsp_power_off();
}
```

### Tactile Buttons
```c
#include "bsp/bsp_button.h"

static void on_boot_button(bsp_button_t btn, bsp_button_event_t event, void *user_data)
{
    if (event == BSP_BUTTON_EVENT_SINGLE_CLICK) {
        bsp_sleep_deep(300);
    }
}

static void on_power_button(bsp_button_t btn, bsp_button_event_t event, void *user_data)
{
    if (event == BSP_BUTTON_EVENT_LONG_PRESS) {
        bsp_power_off();
    }
}

// In on_boot / on_wake:
bsp_button_register_cb(BSP_BUTTON_BOOT,  BSP_BUTTON_EVENT_SINGLE_CLICK, on_boot_button,  NULL);
bsp_button_register_cb(BSP_BUTTON_POWER, BSP_BUTTON_EVENT_LONG_PRESS,   on_power_button, NULL);
```

---

## 10. Complete Production Application Template

```c
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "bsp/bsp.h"
#include "lvgl.h"

static const char *TAG = "app_main";

#define DEFAULT_SLEEP_SEC 300 // 5 minutes

typedef struct {
    uint32_t cycle_counter;
    time_t   boot_epoch;
} app_state_t;

RTC_DATA_ATTR static app_state_t s_app_state = {0};

static void render_ui(const bsp_shtc3_data_t *sens, uint32_t vbat_mv, uint8_t batt_pct)
{
    bsp_lvgl_lock();
    lv_obj_t *scr = lv_screen_active();
    lv_obj_clean(scr);

    lv_obj_t *title = lv_label_create(scr);
    lv_label_set_text_fmt(title, "HUMIDITRON #%lu", (unsigned long)s_app_state.cycle_counter);
    lv_obj_align(title, LV_ALIGN_TOP_LEFT, 6, 6);

    lv_obj_t *temp = lv_label_create(scr);
    lv_label_set_text_fmt(temp, "%.1f°F  %.1f%%", sens->temperature_f, sens->humidity_percent);
    lv_obj_set_style_text_font(temp, &lv_font_montserrat_20, 0);
    lv_obj_align(temp, LV_ALIGN_CENTER, 0, -10);

    lv_obj_t *footer = lv_label_create(scr);
    lv_label_set_text_fmt(footer, "BAT: %.2fV (%u%%) | SMP: %lu", 
                          (float)vbat_mv / 1000.0f, batt_pct, 
                          (unsigned long)bsp_sensors_get_sample_count());
    lv_obj_align(footer, LV_ALIGN_BOTTOM_MID, 0, -6);

    bsp_lvgl_unlock();
}

static void run_cycle(void)
{
    s_app_state.cycle_counter++;

    // 1. Read Battery
    uint32_t vbat_mv = 0;
    bsp_battery_get_voltage(&vbat_mv, NULL);
    uint8_t batt_pct = bsp_battery_get_percentage();

    // 2. Read Environmental Telemetry
    bsp_shtc3_data_t sens = {0};
    bsp_sensors_read(&sens, false);

    // 3. Render UI under PD_FULL Performance Lock
    bsp_pm_pd_full_acquire();
    render_ui(&sens, vbat_mv, batt_pct);
    bsp_delay_ms(1200);
    bsp_pm_pd_full_release();

    // 4. Enter Deep Sleep (Background 60s sub-execution + External 300s Countdown Timer)
    bsp_sleep_config_t sleep_cfg = {
        .mode                   = BSP_SLEEP_MODE_DEEP,
        .duration_sec           = 60,
        .rtc_alarm_duration_sec = DEFAULT_SLEEP_SEC,
        .wake_sources           = BSP_WAKE_SRC_TIMER | BSP_WAKE_SRC_EXTERNAL_RTC | BSP_WAKE_SRC_BUTTONS,
        .next_init_mode         = BSP_INIT_MODE_SUB_EXEC,
    };
    bsp_sleep(&sleep_cfg);
}

static void app_on_pxe(bsp_button_mask_t btn_mask, void *user_data)
{
    ESP_LOGI(TAG, "PXE hook: btn_mask=0x%02X", btn_mask);
}

static void app_on_boot(void *user_data)
{
    ESP_LOGI(TAG, "Boot started");
    s_app_state.boot_epoch = time(NULL);
    run_cycle();
}

static void app_on_wake(const bsp_wake_context_t *ctx, void *user_data)
{
    ESP_LOGI(TAG, "Wake triggered (cause: %d)", ctx->wake_cause);
    run_cycle();
}

static void app_on_sleep(bsp_sleep_mode_t mode, uint32_t duration_sec, void *user_data)
{
    ESP_LOGI(TAG, "Sleep hook triggered (mode: %d, sec: %lu)", (int)mode, (unsigned long)duration_sec);
}

static void app_on_power_off(void *user_data)
{
    ESP_LOGI(TAG, "Power-off hook triggered");
}

void app_main(void)
{
    bsp_app_lifecycle_t lifecycle = {
        .on_pxe              = app_on_pxe,
        .on_boot             = app_on_boot,
        .on_wake             = app_on_wake,
        .on_sleep            = app_on_sleep,
        .on_power_off        = app_on_power_off,
        .default_chime_mask  = BSP_CHIME_MASK_BOOT | BSP_CHIME_MASK_POWER_OFF,
        .user_data           = NULL,
    };
    bsp_app_start(&lifecycle);
}
```
