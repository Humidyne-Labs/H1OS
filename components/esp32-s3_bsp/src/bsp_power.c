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
#include "bsp/hal_types.h"
#include "bsp/sub_rtc.h"
#include "bsp/bsp_wifi.h"
#include "bsp/bsp_power.h"
#include "bsp/bsp_splash.h"
#include "bsp/bsp_lvgl.h"
#include "bsp/bsp_button.h"
#include "bsp/bsp.h"
#include "bsp/sub_power.h"
#include "bsp/sub_display.h"
#include "bsp/sub_audio.h"
#include "bsp/orch_state.h"
#include "bsp/orch_display_sync.h"
#include "bsp/orch_flow.h"
#include "bsp/orch_display_sync.h"
#include "bsp/orch_wake_stub.h"
#include "esp_pm.h"
#include "soc/rtc_cntl_reg.h"
#include "sdkconfig.h"

static const char *TAG = "bsp_power";

#if CONFIG_PM_ENABLE
static esp_pm_lock_handle_t s_pm_pd_full_lock = NULL;
#endif

static bool                 s_led_state           = false;
static bsp_power_off_cb_t   s_shutdown_cb         = NULL;
static void                 *s_shutdown_user_data = NULL;
static bsp_power_sleep_cb_t s_sleep_cb            = NULL;
static void                 *s_sleep_user_data    = NULL;

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
    sub_display_wait_busy(4000);
    bsp_delay_ms(3500);

    // 4. Commit final displayed frame to 'epd_frame' flash partition before power cut
    orch_display_sync_save_if_dirty();

    // 5. Stop button timers/polling immediately so no further button events fire
    bsp_button_stop();

    // 6. Stop LVGL rendering background task
    bsp_lvgl_stop();

    // 7. Put display into deep sleep and disable display power rail
    sub_display_enter_deep_sleep();

    // 8. Mute and power off audio subsystem
    sub_audio_standby();

    // 9. Turn off status LED
    bsp_led_set(false);

    // 10. Disconnect Wi-Fi
    bsp_wifi_disconnect();

    // 11. Clear any active RTC alarms and timers so external RTC does not wake the device while powered down
    sub_rtc_cancel_countdown();
    sub_rtc_get_and_clear_interrupts(NULL, NULL);

    // 12. Reset RTC slow memory state to guarantee a pristine cold boot profile on subsequent power up
    orch_state_reset();

    // 11. Wait until user has completely released the power button with stable debounce
    int stable_high_count = 0;
    while (stable_high_count < 4) {
        if (gpio_get_level((gpio_num_t)HAL_PIN_BUTTON_POWER) == 1) {
            stable_high_count++;
        } else {
            stable_high_count = 0;
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }

    // 12. Drop power latch (GPIO 17 = 0) to cut battery LDO gate
    ESP_LOGI(TAG, "De-asserting BAT_CTRL power latch (GPIO %d)...", HAL_PIN_POWER_HOLD);
    gpio_deep_sleep_hold_dis();
    rtc_gpio_hold_dis(HAL_PIN_POWER_HOLD);
    rtc_gpio_deinit(HAL_PIN_POWER_HOLD);
    gpio_hold_dis((gpio_num_t)HAL_PIN_POWER_HOLD);
    gpio_set_level((gpio_num_t)HAL_PIN_POWER_HOLD, 0);
    vTaskDelay(pdMS_TO_TICKS(100));

    // If external power (USB / VBUS) is present, the board stays powered -> enter standby deep sleep
    ESP_LOGI(TAG, "Entering quiescent standby deep sleep (Wake via POWER button only)...");
    esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
    rtc_gpio_pullup_en((gpio_num_t)HAL_PIN_BUTTON_POWER);
    rtc_gpio_pulldown_dis((gpio_num_t)HAL_PIN_BUTTON_POWER);
    esp_sleep_enable_ext0_wakeup((gpio_num_t)HAL_PIN_BUTTON_POWER, 0);
    esp_deep_sleep_start();
}

esp_err_t bsp_power_init(void)
{
    ESP_LOGI(TAG, "Initializing Battery ADC Monitor via Subsystem (GPIO %d / ADC1_CH3)", HAL_PIN_BATTERY_ADC);
    return sub_power_init();
}

void bsp_led_set(bool state) {
    s_led_state = state;
    // 'Open-Drain' Active LOW: 0 = LED ON, 1 = LED OFF
    gpio_set_level(HAL_PIN_STATUS_LED, state ? 0 : 1);
}

void bsp_led_toggle(void) {
    bsp_led_set(!s_led_state);
}

esp_err_t bsp_battery_get_voltage(uint32_t *out_mv, uint32_t *out_raw)
{
    if (out_mv == NULL) return ESP_ERR_INVALID_ARG;

    uint16_t mv = 0;
    esp_err_t err = sub_power_read_battery(&mv, NULL);
    if (err == ESP_OK) {
        *out_mv = mv;
        if (out_raw != NULL) *out_raw = (mv * 4095) / (3100 * 2);
    }
    return err;
}

uint8_t bsp_battery_get_percentage(void)
{
    uint16_t mv = 0;
    uint8_t pct = 0;
    if (sub_power_read_battery(&mv, &pct) == ESP_OK) {
        return pct;
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

    return BSP_INIT_MODE_WAKE;
}

esp_err_t bsp_enter_sleep(const bsp_sleep_config_t *config)
{
    bsp_sleep_config_t cfg = (config != NULL) ? *config : (bsp_sleep_config_t)BSP_SLEEP_CONFIG_DEFAULT();

    // Store sleep state in Layer 3 RTC Slow Memory
    orch_persisted_state_t *st = orch_state_get();
    st->sample_interval_sec = cfg.duration_sec;
    if (cfg.mode == BSP_SLEEP_MODE_DEEP) {
        st->wake_count++;
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
        sub_display_wait_busy(pdMS_TO_TICKS(5000));

        // 4. Synchronize dirty display framebuffer to 'epd_frame' flash partition before sleeping
        orch_display_sync_save_if_dirty();
        orch_flow_set_thermal_lockout(true, 60);

        uint32_t scale = 0; int32_t offset = 0;
        if (sub_power_get_ulp_cal_params(&scale, &offset) == ESP_OK) {
            st->ulp_vbat_scale = scale;
            st->ulp_vbat_offset_mv = offset;
        }
    }

    // 5. Turn off Status LED
    bsp_led_set(false);

    // 6. Disconnect Wi-Fi
    bsp_wifi_disconnect();

    // 7. Put SSD1681 e-Paper into ultra-low power deep sleep mode (<1 uA)
    sub_display_enter_deep_sleep();

    // 8. Mute Audio Power Amp without cutting codec power rail (prevents I2C bus clamping!)
    sub_audio_standby();

    // 6. Configure Wakeup Triggers
    uint64_t ext1_pin_mask = 0;
    if (cfg.wake_sources & BSP_WAKE_SRC_BUTTONS) {
        ext1_pin_mask |= (1ULL << HAL_PIN_BUTTON_BOOT) | (1ULL << HAL_PIN_BUTTON_POWER);
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
            sub_rtc_arm_countdown(cfg.rtc_alarm_duration_sec);
        }
        
        // Ensure RTC IO pull-up is enabled for open-drain INT line
        rtc_gpio_init(HAL_PIN_RTC_INT);
        rtc_gpio_set_direction(HAL_PIN_RTC_INT, RTC_GPIO_MODE_INPUT_ONLY);
        rtc_gpio_pullup_en(HAL_PIN_RTC_INT);
        rtc_gpio_pulldown_dis(HAL_PIN_RTC_INT);
        
        ext1_pin_mask |= (1ULL << HAL_PIN_RTC_INT);
    }

    // Wait for user to release buttons before entering sleep so the current press doesn't instantly wake the MCU.
    // Sub-execution bypasses this completely because it does not use buttons.
    if ((cfg.wake_sources & BSP_WAKE_SRC_BUTTONS) && (cfg.next_init_mode != BSP_INIT_MODE_SUB_EXEC)) {
        gpio_pullup_en   ((gpio_num_t)HAL_PIN_BUTTON_BOOT);
        gpio_pulldown_dis((gpio_num_t)HAL_PIN_BUTTON_BOOT);
        gpio_hold_dis    ((gpio_num_t)HAL_PIN_BUTTON_BOOT);

        gpio_pullup_en   ((gpio_num_t)HAL_PIN_BUTTON_POWER);
        gpio_pulldown_dis((gpio_num_t)HAL_PIN_BUTTON_POWER);
        gpio_hold_dis    ((gpio_num_t)HAL_PIN_BUTTON_POWER);

        int release_timeout = 0;
        while ((gpio_get_level((gpio_num_t)HAL_PIN_BUTTON_BOOT)  == 0  ||
                gpio_get_level((gpio_num_t)HAL_PIN_BUTTON_POWER) == 0) && release_timeout++ < 4) {
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
            gpio_wakeup_enable((gpio_num_t)HAL_PIN_BUTTON_BOOT,  GPIO_INTR_LOW_LEVEL);
            gpio_wakeup_enable((gpio_num_t)HAL_PIN_BUTTON_POWER, GPIO_INTR_LOW_LEVEL);
        }
		
        if (cfg.wake_sources & BSP_WAKE_SRC_EXTERNAL_RTC) {
            gpio_wakeup_enable((gpio_num_t)HAL_PIN_RTC_INT, GPIO_INTR_LOW_LEVEL);
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
            gpio_wakeup_disable((gpio_num_t)HAL_PIN_BUTTON_BOOT);
            gpio_wakeup_disable((gpio_num_t)HAL_PIN_BUTTON_POWER);
        }
		
        if (cfg.wake_sources & BSP_WAKE_SRC_EXTERNAL_RTC) {
            gpio_wakeup_disable((gpio_num_t)HAL_PIN_RTC_INT);
            sub_rtc_cancel_countdown();
            sub_rtc_get_and_clear_interrupts(NULL, NULL);
        }

        ESP_LOGI(TAG, "Resumed from Light Sleep");
        return ret;
    }

    // DEEP SLEEP
    if (ext1_pin_mask != 0) {
        if (cfg.wake_sources & BSP_WAKE_SRC_BUTTONS) {         
            rtc_gpio_init(HAL_PIN_BUTTON_BOOT);
            rtc_gpio_set_direction(HAL_PIN_BUTTON_BOOT, RTC_GPIO_MODE_INPUT_ONLY);
            rtc_gpio_pullup_en(HAL_PIN_BUTTON_BOOT);
            rtc_gpio_pulldown_dis(HAL_PIN_BUTTON_BOOT);            
        
            rtc_gpio_init(HAL_PIN_BUTTON_POWER);
            rtc_gpio_set_direction(HAL_PIN_BUTTON_POWER, RTC_GPIO_MODE_INPUT_ONLY);
            rtc_gpio_pullup_en(HAL_PIN_BUTTON_POWER);
            rtc_gpio_pulldown_dis(HAL_PIN_BUTTON_POWER);
        }
		
        if (cfg.wake_sources & BSP_WAKE_SRC_EXTERNAL_RTC) {
            rtc_gpio_init(HAL_PIN_RTC_INT);
            rtc_gpio_set_direction(HAL_PIN_RTC_INT, RTC_GPIO_MODE_INPUT_ONLY);
            rtc_gpio_pullup_en(HAL_PIN_RTC_INT);
            rtc_gpio_pulldown_dis(HAL_PIN_RTC_INT);
        }
        esp_sleep_enable_ext1_wakeup_io(ext1_pin_mask, ESP_EXT1_WAKEUP_ANY_LOW);
    }
	
    if (cfg.duration_sec > 0) {
        ESP_LOGI(TAG, "Entering Deep Sleep for %lu seconds...", (unsigned long)cfg.duration_sec);
    } else {
        ESP_LOGI(TAG, "Entering Deep Sleep (Indefinite / External Wakeup Triggers: Buttons & RTC INT)...");
    }

    // Maintain EPD & Sensor 3.3V Power Rail (Active LOW: 0=ON) in RTC IO domain
    rtc_gpio_init(HAL_PIN_EPD_3V3_EN);
    rtc_gpio_set_direction(HAL_PIN_EPD_3V3_EN, RTC_GPIO_MODE_OUTPUT_ONLY);
    rtc_gpio_set_level(HAL_PIN_EPD_3V3_EN, 0);
    rtc_gpio_hold_en(HAL_PIN_EPD_3V3_EN);

    // Maintain EPD Control Lines (CS=HIGH, RST=HIGH, DC=HIGH) in RTC IO domain so SSD1681 does not see floating / reset state
    rtc_gpio_init(HAL_PIN_EPD_RST);
    rtc_gpio_set_direction(HAL_PIN_EPD_RST, RTC_GPIO_MODE_OUTPUT_ONLY);
    rtc_gpio_set_level(HAL_PIN_EPD_RST, 1);
    rtc_gpio_hold_en(HAL_PIN_EPD_RST);

    rtc_gpio_init(HAL_PIN_EPD_CS);
    rtc_gpio_set_direction(HAL_PIN_EPD_CS, RTC_GPIO_MODE_OUTPUT_ONLY);
    rtc_gpio_set_level(HAL_PIN_EPD_CS, 1);
    rtc_gpio_hold_en(HAL_PIN_EPD_CS);

    rtc_gpio_init(HAL_PIN_EPD_DC);
    rtc_gpio_set_direction(HAL_PIN_EPD_DC, RTC_GPIO_MODE_OUTPUT_ONLY);
    rtc_gpio_set_level(HAL_PIN_EPD_DC, 1);
    rtc_gpio_hold_en(HAL_PIN_EPD_DC);

    gpio_set_level((gpio_num_t)HAL_PIN_PA_EN, 0);
    gpio_hold_en((gpio_num_t)HAL_PIN_PA_EN);    

    // Latch Audio Class-D Amp Control (HAL_PIN_PA_CTRL GPIO 46 Active-HIGH: 0=OFF/Muted)
    gpio_set_level((gpio_num_t)HAL_PIN_PA_CTRL, 0);
    gpio_hold_en((gpio_num_t)HAL_PIN_PA_CTRL);

    // Enable Global Deep Sleep Pad Hold
    gpio_deep_sleep_hold_en();

    // Force RTC Peripherals domain to remain powered ON during deep sleep so RTC GPIO 17 (BAT_CTRL) keeps LDO latch held HIGH!
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);

#if CONFIG_ULP_COPROC_ENABLED
    esp_sleep_enable_ulp_wakeup();
#endif

    // Install RTC Wake Stub for <3ms Flow A autonomous sensor sampling
    orch_wake_stub_install();

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
        gpio_set_direction((gpio_num_t)HAL_PIN_POWER_HOLD, GPIO_MODE_OUTPUT);
        gpio_set_level((gpio_num_t)HAL_PIN_POWER_HOLD, 1);
        gpio_sleep_sel_dis((gpio_num_t)HAL_PIN_POWER_HOLD);
        rtc_gpio_init(HAL_PIN_POWER_HOLD);
        rtc_gpio_set_direction(HAL_PIN_POWER_HOLD, RTC_GPIO_MODE_OUTPUT_ONLY);
        rtc_gpio_set_level(HAL_PIN_POWER_HOLD, 1);
        rtc_gpio_hold_en(HAL_PIN_POWER_HOLD);
        gpio_hold_en((gpio_num_t)HAL_PIN_POWER_HOLD);
    } else {
        gpio_deep_sleep_hold_dis();
        rtc_gpio_hold_dis(HAL_PIN_POWER_HOLD);
        gpio_hold_dis((gpio_num_t)HAL_PIN_POWER_HOLD);
        rtc_gpio_deinit(HAL_PIN_POWER_HOLD);
        gpio_set_level((gpio_num_t)HAL_PIN_POWER_HOLD, 0);
    }
    return ESP_OK;
}

esp_err_t bsp_power_set_epd_rail(bool enable)
{
    // EPD_3V3_EN (GPIO 6) is Active-LOW: 0=ON, 1=OFF
    if (enable) {
        rtc_gpio_init(HAL_PIN_EPD_3V3_EN);
        rtc_gpio_set_direction(HAL_PIN_EPD_3V3_EN, RTC_GPIO_MODE_OUTPUT_ONLY);
        rtc_gpio_set_level(HAL_PIN_EPD_3V3_EN, 0);
        gpio_set_level((gpio_num_t)HAL_PIN_EPD_3V3_EN, 0);
        rtc_gpio_hold_en(HAL_PIN_EPD_3V3_EN);
        gpio_hold_en((gpio_num_t)HAL_PIN_EPD_3V3_EN);
    } else {
        rtc_gpio_hold_dis(HAL_PIN_EPD_3V3_EN);
        gpio_hold_dis((gpio_num_t)HAL_PIN_EPD_3V3_EN);
        rtc_gpio_deinit(HAL_PIN_EPD_3V3_EN);
        gpio_set_level((gpio_num_t)HAL_PIN_EPD_3V3_EN, 1);
    }
    return ESP_OK;
}

esp_err_t bsp_power_set_pa_rail(bool enable)
{
    // PA_EN (GPIO 42) is Active-LOW: 0=ON, 1=OFF
    if (enable) {
        gpio_set_direction((gpio_num_t)HAL_PIN_PA_EN, GPIO_MODE_OUTPUT);
        gpio_set_level((gpio_num_t)HAL_PIN_PA_EN, 0);
        gpio_hold_en((gpio_num_t)HAL_PIN_PA_EN);
    } else {
        gpio_hold_dis((gpio_num_t)HAL_PIN_PA_EN);
        gpio_set_level((gpio_num_t)HAL_PIN_PA_EN, 1);
    }
    return ESP_OK;
}

void bsp_system_reboot_to_bootloader(void)
{
    ESP_LOGW(TAG, "Rebooting directly into ROM Download Bootloader Mode...");
    REG_SET_BIT(RTC_CNTL_OPTION1_REG, RTC_CNTL_FORCE_DOWNLOAD_BOOT);
    esp_restart();
}
