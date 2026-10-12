/**
 * @file h1os_lifecycle.c
 * @brief Layer 4: Declarative Application Lifecycle Engine Implementation
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "esp_sleep.h"
#include "hal_io.h"
#include "hal_i2c.h"
#include "sub_nvs.h"
#include "sub_sensor.h"
#include "sub_display.h"
#include "sub_power.h"
#include "orch_state.h"
#include "orch_math.h"
#include "orch_flow.h"
#include "h1os_lvgl.h"
#include "h1os.h"

#include "sub_rtc.h"
#include "sub_audio.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#if CONFIG_ULP_COPROC_ENABLED
#include "ulp_h1os.h"
#endif

static const char *TAG = "h1os_lifecycle";
static h1os_lifecycle_t s_app_lifecycle = {0};
static int64_t s_session_expiry_us = 0;
static TaskHandle_t s_session_task_handle = NULL;
static bool s_session_running = false;

void h1os_reset_session_timer(void)
{
    uint32_t timeout_sec = s_app_lifecycle.session.inactivity_timeout_sec;
    if (timeout_sec == 0) timeout_sec = 30;
    s_session_expiry_us = esp_timer_get_time() + ((int64_t)timeout_sec * 1000000LL);
    ESP_LOGD(TAG, "Interactive session timer reset (+%lu s)", (unsigned long)timeout_sec);
}

static void h1os_session_monitor_task(void *arg)
{
    uint32_t pwr_held_ms = 0;

    while (s_session_running) {
        vTaskDelay(pdMS_TO_TICKS(100));

        /* Long-press detection on Hardware Power Key (GPIO 18 / BAT_KEY) */
        if (hal_io_button_is_pressed(HAL_PIN_BUTTON_POWER)) {
            pwr_held_ms += 100;
            if (pwr_held_ms >= 2000) {
                ESP_LOGI(TAG, "Power button long-press detected (>= 2.0s). Initiating system shutdown...");
                s_session_running = false;

                /* Synthesize descending shutdown tone (1046 Hz -> 784 Hz -> 523 Hz) */
                sub_audio_play_tone(1046, 50);
                vTaskDelay(pdMS_TO_TICKS(15));
                sub_audio_play_tone(784, 50);
                vTaskDelay(pdMS_TO_TICKS(15));
                sub_audio_play_tone(523, 100);

                h1os_shutdown();
                break;
            }
        } else {
            pwr_held_ms = 0;
        }

        /* Inactivity session timeout */
        if (s_session_expiry_us > 0 && esp_timer_get_time() >= s_session_expiry_us) {
            ESP_LOGI(TAG, "Interactive session timeout reached (%lu s inactivity). Entering deep sleep...",
                     (unsigned long)s_app_lifecycle.session.inactivity_timeout_sec);
            s_session_running = false;
            h1os_sleep(120); /* Enter deep sleep */
            break;
        }
    }
    s_session_task_handle = NULL;
    vTaskDelete(NULL);
}

esp_err_t h1os_start(const h1os_lifecycle_t *config)
{
    if (config != NULL) {
        s_app_lifecycle = *config;
    }

    ESP_LOGI(TAG, "Booting %s (%s) Version %s", H1OS_NAME, H1OS_SUBTITLE, H1OS_VERSION_STRING);

    // 1. Initialize Base Hardware I/O & Release Boot Pad Holds
    hal_io_early_init();

    // 2. Initialize Shared I2C Master Bus (Sensors, RTC, Audio Codec)
    hal_i2c_init();

    // 3. Initialize Persistent Storage Subsystem
    sub_nvs_init();

    // 3. Inspect Flow Arbiter (Flow A Wake Stub vs Flow B Interactive UI)
    orch_flow_type_t flow = orch_flow_determine_wakeup();

    if (flow == ORCH_FLOW_A_SPRINT) {
        ESP_LOGI(TAG, "Executing Flow A Sensor Sprint...");
        orch_flow_execute_sub_sprint();
        // Returns immediately to sleep inside stub
        return ESP_OK;
    }

    if (flow == ORCH_FLOW_CRITICAL_OFF) {
        ESP_LOGW(TAG, "Critical shutdown requested! Powering down.");
        h1os_shutdown();
        return ESP_OK;
    }

    if (flow == ORCH_FLOW_BOOTLOADER_JUMP) {
        ESP_LOGW(TAG, "Entering ROM bootloader jump mode...");
        esp_restart();
        return ESP_OK;
    }

    // 4. Flow B Interactive UI Boot
    ESP_LOGI(TAG, "Launching Flow B Main Session...");
    h1os_lvgl_init();
    sub_audio_init();

    bool is_rtc_wake = false;
    uint32_t causes = esp_sleep_get_wakeup_causes();
    if (causes & BIT(ESP_SLEEP_WAKEUP_ULP)) {
#if CONFIG_ULP_COPROC_ENABLED
        if (ulp_last_wake_btn == 0) {
            is_rtc_wake = true;
        }
#endif
    } else if (causes & BIT(ESP_SLEEP_WAKEUP_EXT1)) {
        /* Check if PCF85063A INT was the wake source */
        bool alarm_f = false, timer_f = false;
        sub_rtc_get_and_clear_interrupts(&alarm_f, &timer_f);
        if (alarm_f || timer_f) {
            is_rtc_wake = true;
        }
    }

    if (s_app_lifecycle.on_boot && flow == ORCH_FLOW_COLD_BOOT) {
        s_app_lifecycle.on_boot(s_app_lifecycle.user_data);
    } else if (s_app_lifecycle.on_wake) {
        h1os_wake_context_t ctx = {
            .reset_reason = esp_reset_reason(),
            .wakeup_causes = causes,
            .boot_count = orch_state_get()->boot_count,
            .deep_sleep_count = orch_state_get()->wake_count,
            .woke_from_button = !is_rtc_wake,
            .wake_button = 0,
            .sleep_duration_sec = orch_state_get()->sample_interval_sec,
            .user_data = s_app_lifecycle.user_data
        };
        s_app_lifecycle.on_wake(&ctx, s_app_lifecycle.user_data);
    }

    // 5. Start LVGL interactive render loop
    h1os_lvgl_start(5, 1);

    // 6. Invariant Governance:
    //    - If RTC Wake: screen update rendered, go right back to sleep immediately!
    //    - If Cold Boot or User Button Wake: wait 30s session timeout for user interaction.
    if (is_rtc_wake) {
        ESP_LOGI(TAG, "RTC Countdown wake completed screen refresh. Entering deep sleep immediately.");
        return h1os_sleep(120);
    } else {
        ESP_LOGI(TAG, "Starting 30-second interactive session monitor...");
        h1os_reset_session_timer();
        s_session_running = true;
        xTaskCreatePinnedToCore(h1os_session_monitor_task, "h1os_sess", 3072, NULL, 3, &s_session_task_handle, 0);
    }

    return ESP_OK;
}

esp_err_t h1os_get_telemetry(h1os_telemetry_t *out_telemetry)
{
    if (!out_telemetry) return ESP_ERR_INVALID_ARG;
    memset(out_telemetry, 0, sizeof(h1os_telemetry_t));

    float t = 0.0f, rh = 0.0f, dew = 0.0f;
    esp_err_t ret = orch_flow_query_telemetry(&t, &rh, &dew);
    if (ret == ESP_OK) {
        out_telemetry->ambient_temp_c = t;
        out_telemetry->ambient_temp_f = (t * 9.0f / 5.0f) + 32.0f;
        out_telemetry->ambient_rh_pct = rh;
        out_telemetry->dew_point_c    = dew;
        out_telemetry->dew_point_f    = (dew * 9.0f / 5.0f) + 32.0f;
        out_telemetry->is_thermally_settled = !orch_flow_is_thermal_lockout();

        /* Reconstructed absolute humidity */
        float vp = orch_math_calc_vapor_pressure(t, rh);
        out_telemetry->absolute_humidity_g = orch_math_calc_absolute_humidity(vp, t);
    }

    /* Multi-Node Diagnostics */
    orch_persisted_state_t *st = orch_state_get();
    orch_tri_node_sample_t latest_samp = {0};
    if (orch_state_get_latest_sample(&latest_samp)) {
        out_telemetry->raw_shtc3_temp_c = (float)latest_samp.shtc3_temp_centi_c / 100.0f;
        out_telemetry->mcu_die_temp_c   = (float)latest_samp.mcu_tsens_centi_c / 100.0f;
        out_telemetry->epd_glass_temp_c = (float)latest_samp.epd_glass_centi_c / 100.0f;
    } else {
        out_telemetry->raw_shtc3_temp_c = t;
        sub_sensor_read_mcu_die_temp(&out_telemetry->mcu_die_temp_c);
        sub_display_read_glass_temp(&out_telemetry->epd_glass_temp_c);
    }
    out_telemetry->sample_count = st->total_samples;

    /* Battery & Power Acquisition */
    uint16_t vbat_mv = 0;
    uint8_t  vbat_pct = 0;
    if (sub_power_read_battery(&vbat_mv, &vbat_pct) == ESP_OK) {
        out_telemetry->battery_mv = vbat_mv;
        out_telemetry->battery_percent = vbat_pct;
        /* Zero-Volt Cable Guard: < 100mV means powered exclusively by USB VBUS without battery */
        out_telemetry->is_usb_powered = (vbat_mv < 100);
    }

    return ret;
}

esp_err_t h1os_sleep(uint32_t sleep_sec)
{
    ESP_LOGI(TAG, "Entering coordinated sleep sequence (%lu sec)...", (unsigned long)sleep_sec);
    if (s_app_lifecycle.on_pre_sleep) {
        s_app_lifecycle.on_pre_sleep(sleep_sec, s_app_lifecycle.user_data);
    }
    return orch_flow_transition_to_sleep(sleep_sec);
}

void h1os_shutdown(void)
{
    ESP_LOGI(TAG, "Executing system shutdown and battery power cut...");
    if (s_app_lifecycle.on_shutdown) {
        s_app_lifecycle.on_shutdown(s_app_lifecycle.user_data);
    }
    // Release battery LDO power latch (GPIO 17 driven LOW, hold disabled)
    hal_io_lock_power_latch(false);
}
