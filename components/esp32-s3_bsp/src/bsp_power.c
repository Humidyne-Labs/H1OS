/**
 * @file bsp_power.c
 * @brief Power Control Latch, Status LED, Battery ADC, Shutdown Sequence & Dual Sleep Modes Implementation
 *
 * Circuit Architecture:
 *  - Power Latch: GPIO 17 (BAT_CTRL) is driven HIGH to turn on the onboard LDO gate and hold power.
 *  - Battery Voltage Divider:
 *      VBAT ────[ R1: 100kΩ ]────┬────[ R2: 100kΩ ]──── GND
 *                                │
 *                           GPIO 4 (ADC1_CH3)
 *      V_ADC = VBAT * (R2 / (R1 + R2)) = VBAT / 2
 *      VBAT  = V_ADC * 2.0
 *
 * @version 1.0.0
 * @attribution
 * - Architecture & Development: HUMIDYNE LABS / Humiditron
 * - AI Systems Co-Developer: Gemini (Google DeepMind)
 * - Hardware Target: Waveshare Electronics ESP32-S3 ePaper 1.54 V2
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "esp_sleep.h"
#include "driver/gpio.h"
#include "driver/rtc_io.h"
#include "bsp/pinout.h"
#include "bsp/bsp_display.h"
#include "bsp/bsp_audio.h"
#include "bsp/bsp_wifi.h"
#include "bsp/bsp_rtc.h"
#include "bsp/bsp_sensors.h"
#include "bsp/bsp_power.h"
#include "bsp/bsp_rtc_mem.h"
#include "bsp/bsp_splash.h"
#include "bsp/bsp_lvgl.h"
#include "bsp/bsp_button.h"
#include "bsp/bsp.h"
#include "esp_pm.h"
#include "soc/rtc_cntl_reg.h"
#include "sdkconfig.h"

static const char *TAG = "bsp_power";

#if CONFIG_PM_ENABLE
static esp_pm_lock_handle_t s_pm_pd_full_lock = NULL;
#endif

// ADC Subsystem Handles (ESP32-S3 GPIO 4 = ADC1_CHANNEL_3)
#define BSP_ADC_BATTERY_CHANNEL ADC_CHANNEL_3
#ifndef CONFIG_BSP_BATTERY_CORRECTION_FACTOR_MV
#define CONFIG_BSP_BATTERY_CORRECTION_FACTOR_MV 50
#endif
#define BATTERY_LUT_SIZE (sizeof(s_battery_ocv_lut) / sizeof(s_battery_ocv_lut[0]))

typedef struct {
    uint16_t voltage_mv; ///< voltage_mv value
    uint8_t  percentage; ///< percentage value
} battery_lut_point_t;

static adc_oneshot_unit_handle_t s_adc_handle          = NULL;
static adc_cali_handle_t         s_cali_handle         = NULL;
static bool                      s_calibrated          = false;
static bool                      s_led_state           = false;
static bool                      s_power_inited        = false;
static bsp_power_off_cb_t        s_shutdown_cb         = NULL;
static void                      *s_shutdown_user_data = NULL;
static bsp_power_sleep_cb_t      s_sleep_cb            = NULL;
static void                      *s_sleep_user_data    = NULL;

// Standard 3.7V Li-ion/LiPo discharge curve (rested OCV) sorted ascending
static const battery_lut_point_t s_battery_ocv_lut[] = {
    { 3300,   0 },
    { 3450,   3 },
    { 3600,   8 },
    { 3680,  15 },
    { 3720,  25 },
    { 3750,  35 },
    { 3780,  45 },
    { 3820,  55 },
    { 3870,  65 },
    { 3920,  75 },
    { 3980,  85 },
    { 4060,  92 },
    { 4200, 100 }
};

/* =========================================================================
 * Internal Calibration Helper
 * ========================================================================= */
static bool init_adc_calibration(adc_unit_t unit, adc_channel_t channel, adc_atten_t atten, adc_cali_handle_t *out_handle)
{
    esp_err_t ret   = ESP_FAIL;
    bool calibrated = false;

#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
    if (!calibrated) {
        ESP_LOGD(TAG, "Attempting Curve Fitting ADC calibration");
        adc_cali_curve_fitting_config_t cali_config = {
            .unit_id = unit,
            .chan = channel,
            .atten = atten,
            .bitwidth = ADC_BITWIDTH_DEFAULT, // 12-bits
        };
        ret = adc_cali_create_scheme_curve_fitting(&cali_config, out_handle);
        if (ret == ESP_OK) calibrated = true;
    }
#endif

#if ADC_CALI_SCHEME_LINE_FITTING_SUPPORTED
    if (!calibrated) {
        ESP_LOGD(TAG, "Attempting Line Fitting ADC calibration");
        adc_cali_line_fitting_config_t cali_config = {
            .unit_id = unit,
            .atten = atten,
            .bitwidth = ADC_BITWIDTH_DEFAULT, // 12-bits
        };
        ret = adc_cali_create_scheme_line_fitting(&cali_config, out_handle);
        if (ret == ESP_OK) calibrated = true;
    }
#endif

    if (calibrated) { ESP_LOGI(TAG, "ADC Calibration curve successfully registered");                           } 
	else            { ESP_LOGW(TAG, "ADC Calibration scheme not supported; using raw uncalibrated estimation"); }

    return calibrated;
}

/* =========================================================================
 * Public Power & Battery APIs
 * ========================================================================= */

esp_err_t bsp_power_register_shutdown_cb(bsp_power_off_cb_t cb, void *user_data) {
    s_shutdown_cb        = cb;
    s_shutdown_user_data = user_data;
    return ESP_OK;
}

esp_err_t bsp_power_unregister_shutdown_cb(void) {
    s_shutdown_cb        = NULL;
    s_shutdown_user_data = NULL;
    return ESP_OK;
}

esp_err_t bsp_power_register_sleep_cb(bsp_power_sleep_cb_t cb, void *user_data) {
    s_sleep_cb        = cb;
    s_sleep_user_data = user_data;
    return ESP_OK;
}

esp_err_t bsp_power_unregister_sleep_cb(void) {
    s_sleep_cb        = NULL;
    s_sleep_user_data = NULL;
    return ESP_OK;
}

void bsp_power_off(void)
{
    ESP_LOGI(TAG, "Executing complete system power-off sequence...");

    // 1. Run user power-off lifecycle hook if registered
    if (s_shutdown_cb != NULL) {
        ESP_LOGI(TAG, "Invoking registered power-off callback...");
        s_shutdown_cb(s_shutdown_user_data);
    }

    // 2. Trigger power-off visual splash screen and acoustic chime if registered
    bsp_trigger_splash(BSP_SPLASH_POWER_OFF);
    bsp_trigger_chime (BSP_CHIME_POWER_OFF);

    // 3. Wait for physical E-Paper refresh to complete latching on the glass (if splash was drawn)
    bsp_display_wait_busy(EPD_FULL_REFRESH_TIMEOUT_MS);
    bsp_delay_ms(3500);

    // 4. Commit final displayed frame to 'epd_frame' flash partition before power cut
    bsp_display_sync_partition_frame();

    // 5. Stop button timers/polling immediately so no further button events fire
    bsp_button_stop();

    // 6. Stop LVGL rendering background task
    bsp_lvgl_stop();

    // 7. Put display into deep sleep and disable display power rail
    bsp_display_deep_sleep();

    // 8. Mute and power off audio subsystem
    bsp_audio_deinit();

    // 9. Turn off status LED
    bsp_led_set(false);

    // 10. Disconnect Wi-Fi
    bsp_wifi_disconnect();

    // 11. Clear any active RTC alarms and timers so external RTC does not wake the device while powered down
    bsp_rtc_clear_countdown_timer();
    bsp_rtc_clear_alarm();
    bsp_rtc_get_and_clear_interrupts(NULL, NULL);

    // 12. Reset RTC slow memory state to guarantee a pristine cold boot profile on subsequent power up
    bsp_rtc_mem_reset();

    // 11. Wait until user has completely released the power button with stable debounce
    int stable_high_count = 0;
    while (stable_high_count < 4) {
        if (gpio_get_level((gpio_num_t)BSP_PIN_BUTTON_POWER) == 1) {
            stable_high_count++;
        } else {
            stable_high_count = 0;
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }

    // 12. Drop power latch (GPIO 17 = 0) to cut battery LDO gate
    ESP_LOGI(TAG, "De-asserting BAT_CTRL power latch (GPIO %d)...", BSP_PIN_POWER_HOLD);
    gpio_deep_sleep_hold_dis();
    rtc_gpio_hold_dis(BSP_PIN_POWER_HOLD);
    rtc_gpio_deinit(BSP_PIN_POWER_HOLD);
    gpio_hold_dis((gpio_num_t)BSP_PIN_POWER_HOLD);
    gpio_set_level((gpio_num_t)BSP_PIN_POWER_HOLD, 0);
    vTaskDelay(pdMS_TO_TICKS(100));

    // If external power (USB / VBUS) is present, the board stays powered -> enter standby deep sleep
    ESP_LOGI(TAG, "Entering quiescent standby deep sleep (Wake via POWER button only)...");
    esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
    rtc_gpio_pullup_en((gpio_num_t)BSP_PIN_BUTTON_POWER);
    rtc_gpio_pulldown_dis((gpio_num_t)BSP_PIN_BUTTON_POWER);
    esp_sleep_enable_ext0_wakeup((gpio_num_t)BSP_PIN_BUTTON_POWER, 0);
    esp_deep_sleep_start();
}

esp_err_t bsp_power_init(void)
{
    if (s_power_inited) return ESP_OK;

    ESP_LOGI(TAG, "Initializing Battery ADC Monitor (GPIO %d / ADC1_CH3)", BSP_PIN_BATTERY_ADC);

    // 2. Configure ADC1 Channel 3 (GPIO 4) for Battery Sensing
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id  = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
    };
    esp_err_t err = adc_oneshot_new_unit(&init_config, &s_adc_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to create ADC oneshot unit: %s", esp_err_to_name(err));
        return err;
    }

    adc_oneshot_chan_cfg_t chan_config = {
        .atten    = ADC_ATTEN_DB_12,       // 0 - 3.1V sensing range
        .bitwidth = ADC_BITWIDTH_DEFAULT,  // 12-bits
    };
    err = adc_oneshot_config_channel(s_adc_handle, BSP_ADC_BATTERY_CHANNEL, &chan_config);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure ADC channel: %s", esp_err_to_name(err));
        return err;
    }

    // 3. Initialize Factory Calibration Scheme
    s_calibrated   = init_adc_calibration(ADC_UNIT_1, BSP_ADC_BATTERY_CHANNEL, ADC_ATTEN_DB_12, &s_cali_handle);
    s_power_inited = true;

    return ESP_OK;
}

void bsp_led_set(bool state) {
    s_led_state = state;
    // 'Open-Drain' Active LOW: 0 = LED ON, 1 = LED OFF
    gpio_set_level(BSP_PIN_LED_STATUS, state ? 0 : 1);
}

void bsp_led_toggle(void) {
    bsp_led_set(!s_led_state);
}

esp_err_t bsp_battery_get_voltage(uint32_t *out_mv, uint32_t *out_raw)
{
    if (out_mv == NULL) return ESP_ERR_INVALID_ARG;

    if (!s_power_inited) {
        esp_err_t err = bsp_power_init();
        if (err != ESP_OK) return err;
    }

	int raw_val = 0;
	esp_err_t err = adc_oneshot_read(s_adc_handle, BSP_ADC_BATTERY_CHANNEL, &raw_val);
	if (err != ESP_OK) {
		ESP_LOGE(TAG, "ADC read failed: %s", esp_err_to_name(err));
		return err;
	}

    if (out_raw != NULL) *out_raw = (uint32_t)raw_val;

    int voltage_mv = 0;
    if (s_calibrated && s_cali_handle != NULL) {
        adc_cali_raw_to_voltage(s_cali_handle, raw_val, &voltage_mv);
		// Display Calibrated Voltage in mV
		ESP_LOGI(TAG, "ADC Cali Voltage: %" PRIu32 " mV", voltage_mv);
    } else {
		// Fallback: 12-bit ADC with 12 dB attenuation (Vref = 1100 mV, k = 0.25 -> 4200 mV full scale)
        // Add 2047 before division for half-LSB integer rounding
        voltage_mv = (((uint32_t)raw_val * 4200) + 2047) / 4095;
		// Display Non Calibrated Voltage in mV
		ESP_LOGW(TAG, "[FALLBACK] Uncalibrated ADC Pin Voltage: %" PRIu32 " mV", voltage_mv);
    }

    // Compensate for 1:2 'external' resistor divider (R1=200k 1%, R2=200k 1% -> 2.0x factor)
    *out_mv = (uint32_t)(voltage_mv * 2) + CONFIG_BSP_BATTERY_CORRECTION_FACTOR_MV; // R_DIV has a 1% Tolerance.

    return ESP_OK;
}

uint8_t bsp_battery_get_percentage(void)
{
    uint32_t vbat_mv = 0;
    esp_err_t err = bsp_battery_get_voltage(&vbat_mv, NULL);
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "Unable to read battery voltage; returning 100%%");
        return 100;
    }

    // 1. Boundary Clamping
    if (vbat_mv <= s_battery_ocv_lut[0].voltage_mv) {
        return s_battery_ocv_lut[0].percentage;
    }
    if (vbat_mv >= s_battery_ocv_lut[BATTERY_LUT_SIZE - 1].voltage_mv) {
        return s_battery_ocv_lut[BATTERY_LUT_SIZE - 1].percentage;
    }

    // 2. Linear Interpolation between adjacent points
    for (size_t i = 1; i < BATTERY_LUT_SIZE; i++) {
        if (vbat_mv < s_battery_ocv_lut[i].voltage_mv) {
            uint16_t v_low   = s_battery_ocv_lut[i - 1].voltage_mv;
            uint16_t v_high  = s_battery_ocv_lut[i].voltage_mv;
            uint8_t  p_low   = s_battery_ocv_lut[i - 1].percentage;
            uint8_t  p_high  = s_battery_ocv_lut[i].percentage;

            uint32_t delta_v = v_high - v_low;
            uint32_t delta_p = p_high - p_low;

            // Integer interpolation with half-step rounding (+ delta_v / 2)
            uint32_t interpolated = p_low + (((vbat_mv - v_low) * delta_p + (delta_v / 2)) / delta_v);
            return (uint8_t)interpolated;
        }
    }

    return 100;
}

bool bsp_battery_is_low(uint8_t threshold_pct) {
    return (bsp_battery_get_percentage() <= threshold_pct);
}

esp_reset_reason_t bsp_get_reset_reason(void) {
    return esp_reset_reason();
}

esp_sleep_wakeup_cause_t bsp_get_wakeup_cause(void) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    return esp_sleep_get_wakeup_cause();
#pragma GCC diagnostic pop
}

/* =========================================================================
 * Dynamic Frequency Scaling (DFS) & PM Turbo Locks
 * ========================================================================= */
esp_err_t bsp_pm_init(void)
{
#if CONFIG_PM_ENABLE
    esp_pm_config_t pm_config = {
        .max_freq_mhz         = 240,
        .min_freq_mhz         = 80,
        .light_sleep_enable   = false,
    };
    esp_err_t err = esp_pm_configure(&pm_config);
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "esp_pm_configure returned: %s", esp_err_to_name(err));
        return err;
    }

    if (s_pm_pd_full_lock == NULL) {
        err = esp_pm_lock_create(ESP_PM_CPU_FREQ_MAX, 0, "bsp_pd_full", &s_pm_pd_full_lock);
        if (err != ESP_OK) {
            ESP_LOGW(TAG, "esp_pm_lock_create returned: %s", esp_err_to_name(err));
            return err;
        }
    }
    ESP_LOGI(TAG, "Dynamic Frequency Scaling initialized (80 MHz quiet baseline <-> 240 MHz max performance)");
    return ESP_OK;
#else
    return ESP_OK;
#endif
}

static uint32_t s_pd_full_lock_count = 0;

void bsp_pm_pd_full_acquire(void) {
#if CONFIG_PM_ENABLE
    if (s_pm_pd_full_lock != NULL) {
        esp_pm_lock_acquire(s_pm_pd_full_lock);
    }
#endif
    s_pd_full_lock_count++;
}

void bsp_pm_pd_full_release(void) {
#if CONFIG_PM_ENABLE
    if (s_pm_pd_full_lock != NULL) {
        esp_pm_lock_release(s_pm_pd_full_lock);
    }
#endif
    if (s_pd_full_lock_count > 0) {
        s_pd_full_lock_count--;
    }
}

bool bsp_pm_is_pd_full_active(void) {
    return (s_pd_full_lock_count > 0);
}

bsp_init_mode_t bsp_get_recommended_init_mode(void)
{
    esp_reset_reason_t rst = esp_reset_reason();
    if (rst != ESP_RST_DEEPSLEEP) {
        return BSP_INIT_MODE_BOOT;
    }

    esp_sleep_wakeup_cause_t cause = bsp_get_wakeup_cause();
    if (cause == ESP_SLEEP_WAKEUP_TIMER) {
        return BSP_INIT_MODE_SUB_EXEC;
    }

    if (cause == ESP_SLEEP_WAKEUP_EXT1 || cause == ESP_SLEEP_WAKEUP_EXT0) {
        return BSP_INIT_MODE_WAKE;
    }

    bsp_rtc_state_t *rtc_st = bsp_rtc_mem_get_state();
    if (rtc_st && rtc_st->magic == BSP_RTC_MEM_MAGIC) {
        return (bsp_init_mode_t)rtc_st->next_init_mode;
    }

    return BSP_INIT_MODE_WAKE;
}

esp_err_t bsp_enter_sleep(const bsp_sleep_config_t *config)
{
    bsp_sleep_config_t cfg = (config != NULL) ? *config : (bsp_sleep_config_t)BSP_SLEEP_CONFIG_DEFAULT();

    // Store sleep state in RTC Slow Memory
    bsp_rtc_state_t *rtc_st = bsp_rtc_mem_get_state();
    if (rtc_st && rtc_st->magic == BSP_RTC_MEM_MAGIC) {
        rtc_st->last_sleep_mode         = (uint8_t)cfg.mode;
        rtc_st->next_init_mode          = (uint8_t)cfg.next_init_mode;
        rtc_st->last_sleep_duration_sec = cfg.duration_sec;
        if (cfg.mode == BSP_SLEEP_MODE_DEEP) {
            rtc_st->deep_sleep_count++;
        } else {
            rtc_st->light_sleep_count++;
        }
    }

    // Headless sub-execution bypasses UI, splashes, and flash sync (<10ms budget)
    if (cfg.next_init_mode != BSP_INIT_MODE_SUB_EXEC) {
        // 1. Invoke registered user pre-sleep lifecycle hook
        if (s_sleep_cb != NULL) {
            s_sleep_cb(cfg.mode, cfg.duration_sec, s_sleep_user_data);
        }

        // 2. Trigger visual sleep splash screen and acoustic chime if registered
        bsp_trigger_splash(BSP_SPLASH_SLEEP);
        bsp_trigger_chime (BSP_CHIME_SLEEP);

        // 3. Wait for physical E-Paper refresh to complete latching on the glass (if splash was drawn)
        bsp_display_wait_busy(EPD_PARTIAL_REFRESH_TIMEOUT_MS);

        // 4. Synchronize dirty display framebuffer to 'epd_frame' flash partition before sleeping
        bsp_display_sync_partition_frame();
    }

    // 5. Turn off Status LED
    bsp_led_set(false);

    // 6. Disconnect Wi-Fi
    bsp_wifi_disconnect();

    // 7. Put SSD1681 e-Paper into ultra-low power deep sleep mode (<1 uA)
    bsp_display_deep_sleep();

    // 8. Mute Audio Power Amp without cutting codec power rail (prevents I2C bus clamping!)
    bsp_audio_standby();

    // 6. Configure Wakeup Triggers
    uint64_t ext1_pin_mask = 0;
    if (cfg.wake_sources & BSP_WAKE_SRC_BUTTONS) {
        ext1_pin_mask |= (1ULL << BSP_PIN_BUTTON_BOOT) | (1ULL << BSP_PIN_BUTTON_POWER);
    }

    if (cfg.wake_sources & BSP_WAKE_SRC_EXTERNAL_RTC) {
        if (cfg.rtc_alarm_duration_sec > 0) {
            // Enforce PCF85063A hardware timer sleep bounds [1s, 15300s] (1 sec to 255 min)
            if (cfg.rtc_alarm_duration_sec < BSP_SLEEP_MIN_DURATION_SEC) {
                ESP_LOGW(TAG, "Requested sleep duration %lu s below minimum; clamping to %d s",
                         (unsigned long)cfg.rtc_alarm_duration_sec, BSP_SLEEP_MIN_DURATION_SEC);
                cfg.rtc_alarm_duration_sec = BSP_SLEEP_MIN_DURATION_SEC;
            } else if (cfg.rtc_alarm_duration_sec > BSP_SLEEP_MAX_DURATION_SEC) {
                ESP_LOGW(TAG, "Requested sleep duration %lu s above maximum; clamping to %d s",
                         (unsigned long)cfg.rtc_alarm_duration_sec, BSP_SLEEP_MAX_DURATION_SEC);
                cfg.rtc_alarm_duration_sec = BSP_SLEEP_MAX_DURATION_SEC;
            }

            // Arm PCF85063A Hardware Countdown Timer directly (1/60Hz crystal prescaler)
            bsp_rtc_set_countdown_timer(cfg.rtc_alarm_duration_sec);
        }
        
        // Ensure RTC IO pull-up is enabled for open-drain INT line
        rtc_gpio_init(BSP_PIN_RTC_INT);
        rtc_gpio_set_direction(BSP_PIN_RTC_INT, RTC_GPIO_MODE_INPUT_ONLY);
        rtc_gpio_pullup_en(BSP_PIN_RTC_INT);
        rtc_gpio_pulldown_dis(BSP_PIN_RTC_INT);
        
        ext1_pin_mask |= (1ULL << BSP_PIN_RTC_INT);
    }

    // Wait for user to release buttons before entering sleep so the current press doesn't instantly wake the MCU.
    // Sub-execution bypasses this completely because it does not use buttons.
    if ((cfg.wake_sources & BSP_WAKE_SRC_BUTTONS) && (cfg.next_init_mode != BSP_INIT_MODE_SUB_EXEC)) {
        gpio_pullup_en   ((gpio_num_t)BSP_PIN_BUTTON_BOOT);
        gpio_pulldown_dis((gpio_num_t)BSP_PIN_BUTTON_BOOT);
        gpio_hold_dis    ((gpio_num_t)BSP_PIN_BUTTON_BOOT);

        gpio_pullup_en   ((gpio_num_t)BSP_PIN_BUTTON_POWER);
        gpio_pulldown_dis((gpio_num_t)BSP_PIN_BUTTON_POWER);
        gpio_hold_dis    ((gpio_num_t)BSP_PIN_BUTTON_POWER);

        int release_timeout = 0;
        while ((gpio_get_level((gpio_num_t)BSP_PIN_BUTTON_BOOT)  == 0  ||
                gpio_get_level((gpio_num_t)BSP_PIN_BUTTON_POWER) == 0) && release_timeout++ < 4) {
            vTaskDelay(pdMS_TO_TICKS(50));
        }
        vTaskDelay(pdMS_TO_TICKS(25));
    }

    if (cfg.wake_sources & BSP_WAKE_SRC_TIMER || cfg.duration_sec > 0) {
        if (cfg.duration_sec > 0) {
            esp_sleep_enable_timer_wakeup((uint64_t)cfg.duration_sec * 1000000ULL);
        }
    }

    if (cfg.mode == BSP_SLEEP_MODE_LIGHT) {
        if (cfg.wake_sources & BSP_WAKE_SRC_BUTTONS) {
            gpio_wakeup_enable((gpio_num_t)BSP_PIN_BUTTON_BOOT,  GPIO_INTR_LOW_LEVEL);
            gpio_wakeup_enable((gpio_num_t)BSP_PIN_BUTTON_POWER, GPIO_INTR_LOW_LEVEL);
        }
		
        if (cfg.wake_sources & BSP_WAKE_SRC_EXTERNAL_RTC) {
            gpio_wakeup_enable((gpio_num_t)BSP_PIN_RTC_INT, GPIO_INTR_LOW_LEVEL);
        }
		
        if (ext1_pin_mask != 0) {
            esp_sleep_enable_gpio_wakeup();
        }

        if (cfg.duration_sec > 0) {
            ESP_LOGI(TAG, "Entering Light Sleep for %lu seconds...", (unsigned long)cfg.duration_sec);
        } else {
            ESP_LOGI(TAG, "Entering Light Sleep (Indefinite / External Wakeup Triggers)...");
        }
        fflush(stdout);
        vTaskDelay(pdMS_TO_TICKS(50));

        esp_err_t ret = esp_light_sleep_start();

        if (cfg.wake_sources & BSP_WAKE_SRC_BUTTONS) {
            gpio_wakeup_disable((gpio_num_t)BSP_PIN_BUTTON_BOOT);
            gpio_wakeup_disable((gpio_num_t)BSP_PIN_BUTTON_POWER);
        }
		
        if (cfg.wake_sources & BSP_WAKE_SRC_EXTERNAL_RTC) {
            gpio_wakeup_disable((gpio_num_t)BSP_PIN_RTC_INT);
            bsp_rtc_clear_countdown_timer();
            bsp_rtc_get_and_clear_interrupts(NULL, NULL);
        }

        ESP_LOGI(TAG, "Resumed from Light Sleep");
        return ret;
    }

    // DEEP SLEEP
    if (ext1_pin_mask != 0) {
        if (cfg.wake_sources & BSP_WAKE_SRC_BUTTONS) {         
            rtc_gpio_init(BSP_PIN_BUTTON_BOOT);
            rtc_gpio_set_direction(BSP_PIN_BUTTON_BOOT, RTC_GPIO_MODE_INPUT_ONLY);
            rtc_gpio_pullup_en(BSP_PIN_BUTTON_BOOT);
            rtc_gpio_pulldown_dis(BSP_PIN_BUTTON_BOOT);            
        
            rtc_gpio_init(BSP_PIN_BUTTON_POWER);
            rtc_gpio_set_direction(BSP_PIN_BUTTON_POWER, RTC_GPIO_MODE_INPUT_ONLY);
            rtc_gpio_pullup_en(BSP_PIN_BUTTON_POWER);
            rtc_gpio_pulldown_dis(BSP_PIN_BUTTON_POWER);
        }
		
        if (cfg.wake_sources & BSP_WAKE_SRC_EXTERNAL_RTC) {
            rtc_gpio_init(BSP_PIN_RTC_INT);
            rtc_gpio_set_direction(BSP_PIN_RTC_INT, RTC_GPIO_MODE_INPUT_ONLY);
            rtc_gpio_pullup_en(BSP_PIN_RTC_INT);
            rtc_gpio_pulldown_dis(BSP_PIN_RTC_INT);
        }
        esp_sleep_enable_ext1_wakeup_io(ext1_pin_mask, ESP_EXT1_WAKEUP_ANY_LOW);
    }
	
    if (cfg.duration_sec > 0) {
        ESP_LOGI(TAG, "Entering Deep Sleep for %lu seconds...", (unsigned long)cfg.duration_sec);
    } else {
        ESP_LOGI(TAG, "Entering Deep Sleep (Indefinite / External Wakeup Triggers: Buttons & RTC INT)...");
    }

    // Maintain EPD & Sensor 3.3V Power Rail (Active LOW: 0=ON) in RTC IO domain
    rtc_gpio_init(BSP_PIN_EPD_3V3_EN);
    rtc_gpio_set_direction(BSP_PIN_EPD_3V3_EN, RTC_GPIO_MODE_OUTPUT_ONLY);
    rtc_gpio_set_level(BSP_PIN_EPD_3V3_EN, 0);
    rtc_gpio_hold_en(BSP_PIN_EPD_3V3_EN);

    // Maintain EPD Control Lines (CS=HIGH, RST=HIGH, DC=HIGH) in RTC IO domain so SSD1681 does not see floating / reset state
    rtc_gpio_init(BSP_PIN_EPD_RST);
    rtc_gpio_set_direction(BSP_PIN_EPD_RST, RTC_GPIO_MODE_OUTPUT_ONLY);
    rtc_gpio_set_level(BSP_PIN_EPD_RST, 1);
    rtc_gpio_hold_en(BSP_PIN_EPD_RST);

    rtc_gpio_init(BSP_PIN_EPD_CS);
    rtc_gpio_set_direction(BSP_PIN_EPD_CS, RTC_GPIO_MODE_OUTPUT_ONLY);
    rtc_gpio_set_level(BSP_PIN_EPD_CS, 1);
    rtc_gpio_hold_en(BSP_PIN_EPD_CS);

    rtc_gpio_init(BSP_PIN_EPD_DC);
    rtc_gpio_set_direction(BSP_PIN_EPD_DC, RTC_GPIO_MODE_OUTPUT_ONLY);
    rtc_gpio_set_level(BSP_PIN_EPD_DC, 1);
    rtc_gpio_hold_en(BSP_PIN_EPD_DC);

    gpio_set_level((gpio_num_t)BSP_PIN_PA_EN, 0);
    gpio_hold_en((gpio_num_t)BSP_PIN_PA_EN);    

    // Latch Audio Class-D Amp Control (BSP_PIN_PA_CTRL GPIO 46 Active-HIGH: 0=OFF/Muted)
    gpio_set_level((gpio_num_t)BSP_PIN_PA_CTRL, 0);
    gpio_hold_en((gpio_num_t)BSP_PIN_PA_CTRL);

    // Enable Global Deep Sleep Pad Hold
    gpio_deep_sleep_hold_en();

    // Force RTC Peripherals domain to remain powered ON during deep sleep so RTC GPIO 17 (BAT_CTRL) keeps LDO latch held HIGH!
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);

    // Note: To view raw ESP32-S3 ROM bootloader output on UART during deep sleep wakeups, comment out the line below.
    esp_deep_sleep_disable_rom_logging();

    fflush(stdout); // flush UART
    vTaskDelay(pdMS_TO_TICKS(50));
    esp_deep_sleep_start();
	
    return ESP_OK;
}

esp_err_t bsp_power_set_latch(bool enable)
{
    if (enable) {
        gpio_set_direction((gpio_num_t)BSP_PIN_POWER_HOLD, GPIO_MODE_OUTPUT);
        gpio_set_level((gpio_num_t)BSP_PIN_POWER_HOLD, 1);
        gpio_sleep_sel_dis((gpio_num_t)BSP_PIN_POWER_HOLD);
        rtc_gpio_init(BSP_PIN_POWER_HOLD);
        rtc_gpio_set_direction(BSP_PIN_POWER_HOLD, RTC_GPIO_MODE_OUTPUT_ONLY);
        rtc_gpio_set_level(BSP_PIN_POWER_HOLD, 1);
        rtc_gpio_hold_en(BSP_PIN_POWER_HOLD);
        gpio_hold_en((gpio_num_t)BSP_PIN_POWER_HOLD);
    } else {
        gpio_deep_sleep_hold_dis();
        rtc_gpio_hold_dis(BSP_PIN_POWER_HOLD);
        gpio_hold_dis((gpio_num_t)BSP_PIN_POWER_HOLD);
        rtc_gpio_deinit(BSP_PIN_POWER_HOLD);
        gpio_set_level((gpio_num_t)BSP_PIN_POWER_HOLD, 0);
    }
    return ESP_OK;
}

esp_err_t bsp_power_set_epd_rail(bool enable)
{
    // EPD_3V3_EN (GPIO 6) is Active-LOW: 0=ON, 1=OFF
    if (enable) {
        rtc_gpio_init(BSP_PIN_EPD_3V3_EN);
        rtc_gpio_set_direction(BSP_PIN_EPD_3V3_EN, RTC_GPIO_MODE_OUTPUT_ONLY);
        rtc_gpio_set_level(BSP_PIN_EPD_3V3_EN, 0);
        gpio_set_level((gpio_num_t)BSP_PIN_EPD_3V3_EN, 0);
        rtc_gpio_hold_en(BSP_PIN_EPD_3V3_EN);
        gpio_hold_en((gpio_num_t)BSP_PIN_EPD_3V3_EN);
    } else {
        rtc_gpio_hold_dis(BSP_PIN_EPD_3V3_EN);
        gpio_hold_dis((gpio_num_t)BSP_PIN_EPD_3V3_EN);
        rtc_gpio_deinit(BSP_PIN_EPD_3V3_EN);
        gpio_set_level((gpio_num_t)BSP_PIN_EPD_3V3_EN, 1);
    }
    return ESP_OK;
}

esp_err_t bsp_power_set_pa_rail(bool enable)
{
    // PA_EN (GPIO 42) is Active-LOW: 0=ON, 1=OFF
    if (enable) {
        gpio_set_direction((gpio_num_t)BSP_PIN_PA_EN, GPIO_MODE_OUTPUT);
        gpio_set_level((gpio_num_t)BSP_PIN_PA_EN, 0);
        gpio_hold_en((gpio_num_t)BSP_PIN_PA_EN);
    } else {
        gpio_hold_dis((gpio_num_t)BSP_PIN_PA_EN);
        gpio_set_level((gpio_num_t)BSP_PIN_PA_EN, 1);
    }
    return ESP_OK;
}

void bsp_system_reboot_to_bootloader(void)
{
    ESP_LOGW(TAG, "Rebooting directly into ROM Download Bootloader Mode...");
    REG_SET_BIT(RTC_CNTL_OPTION1_REG, RTC_CNTL_FORCE_DOWNLOAD_BOOT);
    esp_restart();
}
