/**
 * @file h1os_lifecycle.c
 * @brief Layer 4: Declarative Application Lifecycle Engine Implementation
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>
#include <string.h>
#include "sdkconfig.h"
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
#include "driver/gpio.h"
#include "driver/rtc_io.h"
#include "orch_display_sync.h"

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

bool h1os_is_session_active(void)
{
    return s_session_running;
}

static void h1os_trigger_chime(h1os_chime_type_t type)
{
    if (s_app_lifecycle.presentation.on_chime != NULL) {
        s_app_lifecycle.presentation.on_chime(type, s_app_lifecycle.user_data);
    } else if (s_app_lifecycle.presentation.chime_mask & (1 << type)) {
        sub_audio_play_chime_async((uint8_t)type);
    }
}

static void h1os_session_monitor_task(void *arg)
{
    while (s_session_running) {
        vTaskDelay(pdMS_TO_TICKS(500));

        /* Inactivity session timeout */
        if (s_session_expiry_us > 0 && esp_timer_get_time() >= s_session_expiry_us) {
            ESP_LOGI(TAG, "Interactive session timeout reached (%lu s inactivity). Entering deep sleep...",
                     (unsigned long)s_app_lifecycle.session.inactivity_timeout_sec);
            s_session_running = false;
            uint32_t sleep_sec = orch_state_get()->flow_b_period_sec;
            if (sleep_sec == 0) sleep_sec = 120;
            h1os_sleep(sleep_sec); /* Enter deep sleep */
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

    /* Apply configurable Flow A and Flow B timings to persistent state */
    orch_persisted_state_t *st = orch_state_get();
    if (s_app_lifecycle.session.flow_a_period_sec > 0) {
        st->sample_interval_sec = s_app_lifecycle.session.flow_a_period_sec;
    }
    if (s_app_lifecycle.session.flow_b_period_sec > 0) {
        st->flow_b_period_sec = s_app_lifecycle.session.flow_b_period_sec;
    }

    ESP_LOGI(TAG, "Booting %s (%s) Version %s [Flow A: %lus, Flow B: %lus]",
             H1OS_NAME, H1OS_SUBTITLE, H1OS_VERSION_STRING,
             (unsigned long)st->sample_interval_sec,
             (unsigned long)st->flow_b_period_sec);

    // 1. Initialize Base Hardware I/O & Release Boot Pad Holds
    hal_io_early_init();

    // 2. Initialize Shared I2C Master Bus (Sensors, RTC, Audio Codec)
    hal_i2c_init();

    // 3. Initialize Persistent Storage Subsystem
    sub_nvs_init();

    // 3. Inspect Flow Arbiter (Flow A Wake Stub vs Flow B Interactive UI)
    orch_flow_type_t flow = orch_flow_determine_wakeup();

    if (flow == ORCH_FLOW_A_SAMPLE) {
        ESP_LOGI(TAG, "Executing Flow A Sensor Sample Burst...");
        orch_flow_execute_sensor_sample();
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
    bool is_wake = (flow != ORCH_FLOW_BOOT);
    h1os_lvgl_init(is_wake);
    if (is_wake) {
        esp_err_t r_err = orch_display_sync_restore_to_framebuffer();
        if (r_err != ESP_OK) {
            ESP_LOGW(TAG, "Display frame restore failed (%s), forcing full OTP refresh", esp_err_to_name(r_err));
            h1os_lvgl_set_first_flush_mode(true);
        }
    }
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

    s_session_running = !is_rtc_wake;
    if (s_session_running) {
        h1os_reset_session_timer();
    }

    if (flow == ORCH_FLOW_BOOT) {
        h1os_trigger_chime(H1OS_CHIME_BOOT);
        if (s_app_lifecycle.on_boot) {
            s_app_lifecycle.on_boot(s_app_lifecycle.user_data);
        }
    } else if (s_app_lifecycle.on_wake) {
        h1os_trigger_chime(H1OS_CHIME_WAKE);
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
    //    - If Boot or User Button Wake: wait configured inactivity session timeout for user interaction.
    if (is_rtc_wake) {
        ESP_LOGI(TAG, "RTC Countdown wake completed screen refresh. Entering deep sleep immediately.");
        uint32_t sleep_sec = orch_state_get()->flow_b_period_sec;
        if (sleep_sec == 0) sleep_sec = 120;
        return h1os_sleep(sleep_sec);
    } else {
        uint32_t timeout_sec = s_app_lifecycle.session.inactivity_timeout_sec;
        if (timeout_sec == 0) timeout_sec = 30;
        ESP_LOGI(TAG, "Starting %lu-second interactive session monitor...", (unsigned long)timeout_sec);
        h1os_reset_session_timer();
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
        /* External power detection:
         *  - < 100 mV: Zero-Volt Cable Guard (no cell, charger not floating)
         *  - Active USB host connection via hardware SOF detection */
        out_telemetry->is_usb_powered = (vbat_mv < 100) || sub_power_connected_usb();
    }

    return ret;
}

esp_err_t h1os_sleep(uint32_t sleep_sec)
{
    ESP_LOGI(TAG, "Entering coordinated sleep sequence (%lu sec)...", (unsigned long)sleep_sec);
    h1os_trigger_chime(H1OS_CHIME_SLEEP);
    if (s_app_lifecycle.on_pre_sleep) {
        s_app_lifecycle.on_pre_sleep(sleep_sec, s_app_lifecycle.user_data);
    }
    return orch_flow_transition_to_sleep(sleep_sec);
}

static void execute_system_shutdown(bool force_clean_white)
{
    ESP_LOGI(TAG, "Executing system shutdown (%s)...",
             force_clean_white ? "storage mode: clean white" : "standard mode");
    s_session_running = false; /* Stop inactivity monitor from racing into h1os_sleep() */

    h1os_trigger_chime(H1OS_CHIME_SHUTDOWN);
    if (s_app_lifecycle.on_shutdown) {
        s_app_lifecycle.on_shutdown(s_app_lifecycle.user_data);
    }
    // Wait for shutdown chime to finish playing cleanly before cutting power
    sub_audio_wait_idle(1500);

    /* Display shutdown / storage handling */
    sub_display_wait_busy(pdMS_TO_TICKS(5000));
    if (force_clean_white) {
        sub_display_clear_to_white_full();
        orch_state_get()->flags &= ~ORCH_FLAG_EPD_FRAME_VALID;
    } else {
        orch_display_sync_save_if_dirty();
    }
    sub_display_enter_deep_sleep();

    /* The POWER button physically bridges the LDO gate while held, and an
     * EXT1 ANY_LOW wake would fire instantly if it is still down. Wait for a
     * stable release (4 x 50 ms HIGH), bounded to 10 s. */
    int stable_high = 0;
    for (int i = 0; i < 200 && stable_high < 4; i++) {
        stable_high = (gpio_get_level(HAL_PIN_BUTTON_POWER) == 1) ? stable_high + 1 : 0;
        vTaskDelay(pdMS_TO_TICKS(50));
    }

    /* Release battery LDO power latch (GPIO 17 LOW). On battery, power dies here. */
    ESP_LOGW(TAG, "Releasing battery power latch (GPIO 17)");
    hal_io_lock_power_latch(false);
    vTaskDelay(pdMS_TO_TICKS(200));

    /* Still running => powered from USB VBUS. Do NOT use sub_power_enter_deep_sleep():
     * it re-asserts and holds GPIO 17 HIGH. Enter a POWER-button-only deep sleep. */
    ESP_LOGW(TAG, "External power detected; entering standby (wake: POWER button only)");
    esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
    rtc_gpio_pullup_en(HAL_PIN_BUTTON_POWER);
    rtc_gpio_pulldown_dis(HAL_PIN_BUTTON_POWER);
    esp_sleep_enable_ext1_wakeup(1ULL << HAL_PIN_BUTTON_POWER, ESP_EXT1_WAKEUP_ANY_LOW);
    esp_deep_sleep_start();
}

void h1os_shutdown(void)
{
#if CONFIG_H1OS_EPD_CLEAN_WHITE_ON_SHUTDOWN
    execute_system_shutdown(true);
#else
    execute_system_shutdown(false);
#endif
}

void h1os_shutdown_for_storage(void)
{
    execute_system_shutdown(true);
}
