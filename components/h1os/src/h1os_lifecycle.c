/**
 * @file h1os_lifecycle.c
 * @brief Layer 4: Declarative application lifecycle engine implementation
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "driver/gpio.h"
#include "driver/rtc_io.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "h1os.h"
#include "h1os_lvgl.h"
#include "h1os_time.h"
#include "hal_i2c.h"
#include "hal_io.h"
#include "orch_display_sync.h"
#include "orch_flow.h"
#include "orch_math.h"
#include "orch_state.h"
#include "sdkconfig.h"
#include "soc/rtc_cntl_reg.h"
#include "sub_audio.h"
#include "sub_display.h"
#include "sub_nvs.h"
#include "sub_power.h"
#include "sub_rtc.h"
#include "ulp_h1os.h"

#include <stdio.h>
#include <string.h>

static const char *TAG = "h1os_lifecycle";

static h1os_lifecycle_t s_app_lifecycle = {0};
static int64_t s_session_expiry_us = 0;
static TaskHandle_t s_session_task_handle = NULL;
static bool s_session_running = false;
static bool s_audio_initialized = false;

/* Retain previous battery state across deep-sleep cycles in RTC Slow SRAM for accurate charger unplug detection */
RTC_DATA_ATTR static h1os_battery_state_t s_prev_bat_state = H1OS_BATTERY_DISCHARGING;

/**
 * @brief Reset the interactive session inactivity timer (extends session by timeout_sec).
 */
void h1os_reset_session_timer(void)
{
    uint32_t timeout_sec = s_app_lifecycle.session.inactivity_timeout_sec;
    if (timeout_sec == 0) {
        ESP_LOGE(TAG, "Lifecycle configuration error: inactivity_timeout_sec is 0. Aborting session timer reset.");
        return;
    }
    s_session_expiry_us = esp_timer_get_time() + ((int64_t)timeout_sec * 1000000LL);
    ESP_LOGD(TAG, "Interactive session timer reset (+%lu s)", (unsigned long)timeout_sec);
}

/**
 * @brief Check whether an interactive inactivity countdown session is active.
 *
 * @return true if running in an interactive user session, false during unattended wakes.
 */
bool h1os_is_session_active(void)
{
    return s_session_running;
}

/**
 * @brief H1os trigger chime.
 *
 * @param[in]    type            Parameter type.
 *
 * @return Return value of type static void.
 */
static void h1os_trigger_chime(h1os_chime_type_t type)
{
    if (!s_audio_initialized) {
        return;
    }
    if (s_app_lifecycle.presentation.on_chime != NULL) {
        s_app_lifecycle.presentation.on_chime(type, s_app_lifecycle.user_data);
    } else if (s_app_lifecycle.presentation.chime_mask & (1U << type)) {
        uint8_t chime = (uint8_t)type;
        sub_audio_play(SUB_AUDIO_CHIME, &chime, sizeof(chime));
    }
}

/**
 * @brief H1os trigger splash.
 *
 * @param[in]    type            Parameter type.
 *
 * @return Return value of type static void.
 */
static void h1os_trigger_splash(h1os_splash_type_t type)
{
    if (s_app_lifecycle.presentation.on_splash != NULL) {
        s_app_lifecycle.presentation.on_splash(type, s_app_lifecycle.user_data);
    }
}

/**
 * @brief Drain pending LVGL render/flush tasks and stop the Core 1 LVGL worker task.
 */
static void h1os_quiesce_lvgl_pipeline(void)
{
    if (h1os_lvgl_has_pending_tasks()) {
        ESP_LOGI(TAG, "Waiting for LVGL pipeline to drain...");
        uint32_t wait_ms = 0;
        while (h1os_lvgl_has_pending_tasks() && wait_ms < 6000U) {
            vTaskDelay(pdMS_TO_TICKS(20));
            wait_ms += 20U;
        }
    }
    h1os_lvgl_stop();
}

/**
 * @brief H1os session monitor task.
 *
 * @param[in]    arg             Parameter arg.
 *
 * @return Return value of type static void.
 */
static void h1os_session_monitor_task(void *arg)
{
    (void)arg;
    while (s_session_running) {
        vTaskDelay(pdMS_TO_TICKS(500));

        if (s_session_expiry_us > 0 && esp_timer_get_time() >= s_session_expiry_us) {
            ESP_LOGI(TAG, "Interactive session timeout reached (%lu s inactivity). Entering deep sleep...",
                (unsigned long)s_app_lifecycle.session.inactivity_timeout_sec);
            s_session_running = false;
            uint32_t sleep_sec = orch_state_get()->flow_b_period_sec;
            if (sleep_sec == 0) {
                ESP_LOGE(TAG, "Lifecycle configuration error: flow_b_period_sec is 0. Aborting to safe shutdown.");
                h1os_shutdown();
                break;
            }
            h1os_sleep(sleep_sec);
            break;
        }
    }
    s_session_task_handle = NULL;
    vTaskDelete(NULL);
}

/**
 * @brief Diagnostic dump of ULP wake telemetry.
 *
 * @details Isolated helper function for development; comment out the call in h1os_start() for release builds.
 *
 * @return Return value of type static void.
 */
static void debug_dump_ulp_telemetry(void)
{
    ESP_LOGI(TAG, "--------------------------------------------------------------------------------");
    ESP_LOGI(TAG, "[ULP TELEMETRY] Wake #%lu: cause=%lu (%s), slice=%lu/%lu, vbat=%lu mV (raw=%lu), btn=%lu, stuck=%lu",
             (unsigned long)ulp_wake_counter,
             (unsigned long)ulp_last_wake_cause,
               (ulp_last_wake_cause == 1) ? "BOOT_BTN"
             : (ulp_last_wake_cause == 2) ? "PWR_BTN"
             : (ulp_last_wake_cause == 3) ? "LONG_OVERFLOW"
             : (ulp_last_wake_cause == 4) ? "SENSOR_TICK"
             : (ulp_last_wake_cause == 5) ? "RTC_INT_STUCK_FAULT"
             : (ulp_last_wake_cause == 6) ? "CRITICAL_BATTERY"
                                          : "UNKNOWN",
             (unsigned long)ulp_slice_counter,
             (unsigned long)ulp_overflow_limit,
             (unsigned long)ulp_last_vbat_mv,
             (unsigned long)ulp_vbat_raw_adc,
             (unsigned long)ulp_last_wake_btn,
             (unsigned long)ulp_rtc_int_stuck);

    if (ulp_rtc_int_stuck) {
        ESP_LOGE(TAG, "[ULP FAULT] External PCF85063A /INT pin (GPIO 5) remained stuck LOW >50ms! Re-arm suppressed.");
    }
    if (ulp_last_wake_cause == 6) {
        ESP_LOGE(TAG, "[ULP FAULT] Battery critically low: %lu mV (< 3250 mV threshold)!", (unsigned long)ulp_last_vbat_mv);
    }
    ESP_LOGI(TAG, "--------------------------------------------------------------------------------");
}

/**
 * @brief Logs a prominent, framed ASCII console banner identifying the active lifecycle flow.
 *
 * @param[in]    flow            Parameter flow.
 *
 * @return Return value of type static void.
 */
static void h1os_log_flow_banner(orch_flow_type_t flow)
{
    volatile orch_persisted_state_t *st = orch_state_get();
    const char *flow_title = "UNKNOWN FLOW";
    const char *trigger_desc = "None";

    switch (flow) {
    case ORCH_FLOW_BOOT:
        flow_title = "[COLD BOOT INITIALIZATION]";
        trigger_desc = "Power-On Reset / Hard Reset";
        break;
    case ORCH_FLOW_A_SAMPLE:
        flow_title = "[FLOW A - QUIESCENT SENSOR SAMPLE BURST]";
        trigger_desc = "ULP Periodic Sleep Timer (60s tick)";
        break;
    case ORCH_FLOW_B_MAIN_WAKE:
        flow_title = "[FLOW B - INTERACTIVE UI SESSION]";
        if (ulp_last_wake_btn == 1) {
            trigger_desc = "ULP Tactile Press (BOOT / GPIO 0)";
        } else if (ulp_last_wake_btn == 2) {
            trigger_desc = "ULP Tactile Press (POWER / GPIO 18)";
        } else {
            trigger_desc = "External RTC Alarm / Timer Tick";
        }
        break;
    case ORCH_FLOW_CRITICAL_OFF:
        flow_title = "[CRITICAL LOW POWER SHUTDOWN]";
        trigger_desc = "Battery Brownout Guard (< 3.25V) / Power Key Hold";
        break;
    case ORCH_FLOW_BOOTLOADER_JUMP:
        flow_title = "[ROM BOOTLOADER JUMP MODE]";
        trigger_desc = "BOOT Button Long-Press (>= 2.5s)";
        break;
    default:
        flow_title = "[UNKNOWN / CORRUPTED FLOW STATE]";
        trigger_desc = "Invalid Flow Enum Trapped";
        ESP_LOGE(TAG, "Unhandled or corrupted lifecycle flow detected: %d", (int)flow);
        break;
    }

    ESP_LOGI(TAG, "================================================================================");
    ESP_LOGI(TAG, ">>> H1OS ACTIVE FLOW: %s <<<", flow_title);
    ESP_LOGI(TAG, ">>> Trigger Source  : %s", trigger_desc);
    ESP_LOGI(TAG, ">>> Boot Count      : %lu | Wake Count: %lu | Session Inactivity: %lu s",
             (unsigned long)st->boot_count,
             (unsigned long)st->wake_count,
             (unsigned long)s_app_lifecycle.session.inactivity_timeout_sec);
    ESP_LOGI(TAG, "================================================================================");
}

/**
 * @brief H1os early system bringup.
 *
 * @param[in]    config          Parameter config.
 *
 * @return Return value of type static orch_flow_type_t.
 */
static orch_flow_type_t h1os_early_system_bringup(const h1os_lifecycle_t *config)
{
    if (config != NULL) {
        s_app_lifecycle = *config;
    }

    sub_power_init_dfs(s_app_lifecycle.session.clk_mode);

    hal_io_early_init();

    hal_i2c_init();

    /* Initialize PCF85063A RTC (12.5pF load cap, disable 32.768 kHz CLKOUT) and sync POSIX clock */
    if (sub_rtc_init() == ESP_OK) {
        (void)h1os_time_sync_rtc_to_system();
    }

    sub_nvs_init();

    /* Ensure ULP GPIO wakeup is gated off while Xtensa CPU owns the system */
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);

    orch_flow_type_t flow = orch_flow_determine_wakeup();

    /* Load persisted autonomy runtimes from NVS after cold-boot orch_state_reset() so NVS values are preserved */
    if (flow == ORCH_FLOW_BOOT) {
        orch_state_load_runtimes_from_nvs();
    }

    volatile orch_persisted_state_t *st = orch_state_get();
    if (s_app_lifecycle.session.flow_a_period_sec > 0) {
        st->sample_interval_sec = s_app_lifecycle.session.flow_a_period_sec;
    }
    if (s_app_lifecycle.session.flow_b_period_sec > 0) {
        st->flow_b_period_sec = s_app_lifecycle.session.flow_b_period_sec;
    }

    ESP_LOGI(TAG, "Booting %s (%s) Version %s [Flow A: %lus, Flow B: %lus]",
                    H1OS_NAME,
                    H1OS_SUBTITLE,
                    h1os_version_get_string(),
                    (unsigned long)st->sample_interval_sec,
                    (unsigned long)st->flow_b_period_sec);

    h1os_log_flow_banner(flow);

    if (flow != ORCH_FLOW_BOOT) {
        debug_dump_ulp_telemetry();
    }

    /* Call sub_power_init_ulp on all flows: loads ULP on cold boot, or accounts for final Flow B sleep slice on RTC overflow wake */
    sub_power_init_ulp(st->sample_interval_sec);

    return flow;
}

/**
 * @brief H1os handle non ui flows.
 *
 * @param[in]    flow            Parameter flow.
 *
 * @return True on success, false otherwise.
 */
static bool h1os_handle_non_ui_flows(orch_flow_type_t flow)
{
    if (flow == ORCH_FLOW_CRITICAL_OFF) {
        ESP_LOGW(TAG, "Critical shutdown requested! Powering down.");
        h1os_shutdown();
        return true;
    }

    if (flow == ORCH_FLOW_BOOTLOADER_JUMP) {
        ESP_LOGW(TAG, "Entering ROM bootloader jump mode via RTC_CNTL_FORCE_DOWNLOAD_BOOT...");
        sub_display_wait_busy(pdMS_TO_TICKS(5000));
        sub_audio_standby();
        REG_WRITE(RTC_CNTL_OPTION1_REG, RTC_CNTL_FORCE_DOWNLOAD_BOOT);
        esp_restart();
        return true;
    }

    return false;
}

/**
 * @brief H1os launch interactive session.
 *
 * @param[in]    flow            Parameter flow.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t h1os_launch_interactive_session(orch_flow_type_t flow)
{
    ESP_LOGI(TAG, "Launching Flow B Main Session...");
    bool is_wake = (flow != ORCH_FLOW_BOOT);
    bool is_rtc_wake = false;
    bool button_woke = false;
    uint32_t causes = 0;

    if (is_wake) {
        causes = esp_sleep_get_wakeup_causes();
        if (causes & BIT(ESP_SLEEP_WAKEUP_COCPU_TRAP_TRIG)) {
            ESP_LOGE(TAG, "[ULP FAULT] Coprocessor trapped/crashed! Causes bitmask: 0x%08lx", (unsigned long)causes);

            is_rtc_wake = false;
        } else if (causes & BIT(ESP_SLEEP_WAKEUP_ULP)) {
            button_woke = (ulp_last_wake_btn != 0);
            if (!button_woke) {
                is_rtc_wake = true;
            }
        } else {
            is_rtc_wake = true;
        }
    }

    h1os_lvgl_init(is_wake);
    if (is_wake) {
        esp_err_t r_err = orch_display_sync_restore_to_framebuffer();
        if (r_err != ESP_OK) {
            ESP_LOGW(TAG, "Display frame restore failed (%s), forcing full OTP refresh", esp_err_to_name(r_err));
            h1os_lvgl_set_first_flush_mode(true);
        }
    }

    bool is_user_wake = (!is_wake) || button_woke;
    if (is_user_wake) {
        s_audio_initialized = (sub_audio_init(s_app_lifecycle.presentation.volume_pct) == ESP_OK);
    } else {
        s_audio_initialized = false;
        ESP_LOGI(TAG, "Unattended wake event: Codec initialization skipped (audio sleep preserved)");
    }

    /* Always clear any latched PCF85063A interrupt flags on Flow B entry */
    bool alarm_f = false, timer_f = false;
    sub_rtc_get_and_clear_interrupts(&alarm_f, &timer_f);

    s_session_running = !is_rtc_wake;
    if (s_session_running) {
        h1os_reset_session_timer();
    }

    volatile orch_persisted_state_t *st = orch_state_get();

    if (flow == ORCH_FLOW_BOOT) {
        h1os_trigger_chime(H1OS_CHIME_BOOT);
        h1os_lvgl_lock(1000);
        h1os_trigger_splash(H1OS_SPLASH_BOOT);
        if (s_app_lifecycle.on_boot) {
            s_app_lifecycle.on_boot(s_app_lifecycle.user_data);
        }
        h1os_lvgl_unlock();
    } else if (s_app_lifecycle.on_wake) {
        h1os_wake_context_t ctx = {.reset_reason       = esp_reset_reason(),
                                   .wakeup_causes      = causes,
                                   .boot_count         = st->boot_count,
                                   .deep_sleep_count   = st->wake_count,
                                   .woke_from_button   = button_woke,
                                   .wake_button        = button_woke ? (uint8_t)ulp_last_wake_btn : (uint8_t)H1OS_WAKE_BTN_NONE,
                                   .sleep_duration_sec = button_woke ? st->sample_interval_sec : st->flow_b_period_sec,
                                   .user_data          = s_app_lifecycle.user_data};
        h1os_lvgl_lock(1000);
        s_app_lifecycle.on_wake(&ctx, s_app_lifecycle.user_data);
        h1os_lvgl_unlock();
    }

    h1os_lvgl_start(5, 1);

    if (is_rtc_wake) {
        /* Allow Core 1 LVGL task to pick up and begin flushing the updated frame */
        vTaskDelay(pdMS_TO_TICKS(10));
        ESP_LOGI(TAG, "RTC Countdown wake completed screen refresh. Entering deep sleep immediately.");
        uint32_t sleep_sec = st->flow_b_period_sec;
        if (sleep_sec == 0) {
            ESP_LOGE(TAG, "Lifecycle configuration error: flow_b_period_sec is 0 on RTC wake. Aborting to safe shutdown.");
            h1os_shutdown();
            return ESP_ERR_INVALID_STATE;
        }
        return h1os_sleep(sleep_sec);
    } else {
        uint32_t timeout_sec = s_app_lifecycle.session.inactivity_timeout_sec;
        if (timeout_sec == 0) {
            ESP_LOGE(TAG, "Lifecycle configuration error: inactivity_timeout_sec is 0 for interactive session. Aborting to safe shutdown.");
            h1os_shutdown();
            return ESP_ERR_INVALID_ARG;
        }
        ESP_LOGI(TAG, "Starting %lu-second interactive session monitor...", (unsigned long)timeout_sec);
        h1os_reset_session_timer();
        xTaskCreatePinnedToCore(h1os_session_monitor_task, "h1os_sess", 3072, NULL, 3, &s_session_task_handle, 0);
    }

    return ESP_OK;
}

/**
 * @brief Initialize H1OS and dispatch application lifecycle.
 *
 * @param[in]    config          Parameter config.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t h1os_start(const h1os_lifecycle_t *config)
{
    if (config == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    orch_flow_type_t flow = h1os_early_system_bringup(config);

    if (h1os_handle_non_ui_flows(flow)) {
        return ESP_OK;
    }

    return h1os_launch_interactive_session(flow);
}

/**
 * @brief Retrieve current Tri-Node environmental telemetry.
 *
 * @param[out]   out_telemetry   Parameter out_telemetry.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t h1os_get_telemetry(h1os_telemetry_t *out_telemetry)
{
    if (!out_telemetry) {
        return ESP_ERR_INVALID_ARG;
    }
    memset(out_telemetry, 0, sizeof(h1os_telemetry_t));

    float t = 0.0f, rh = 0.0f, dew = 0.0f;
    esp_err_t ret = orch_flow_query_telemetry(&t, &rh, &dew);
    volatile orch_persisted_state_t *st = orch_state_get();

    if (ret == ESP_OK) {
        out_telemetry->ambient_temp_c       = t;
        out_telemetry->ambient_temp_f       = (t * 9.0f / 5.0f) + 32.0f;
        out_telemetry->ambient_rh_pct       = rh;
        out_telemetry->dew_point_c          = dew;
        out_telemetry->dew_point_f          = (dew * 9.0f / 5.0f) + 32.0f;
        out_telemetry->vapor_pressure_hpa   = st->vapor_pressure_hpa;
        out_telemetry->is_thermally_settled = !orch_flow_is_thermal_lockout();
        out_telemetry->absolute_humidity_g  = orch_math_calc_absolute_humidity(st->vapor_pressure_hpa, t);
    }

    out_telemetry->window_low_c           = (float)st->window_low_temp_centi_c / 100.0f;
    out_telemetry->window_high_c          = (float)st->window_high_temp_centi_c / 100.0f;
    out_telemetry->window_avg_shtc3_c     = st->window_avg_shtc3_c;
    out_telemetry->window_avg_die_c       = st->window_avg_die_c;
    out_telemetry->temp_historical_c      = st->temp_historical_c;
    out_telemetry->rh_historical_pct      = st->rh_historical_pct;
    out_telemetry->trinode_temp_c         = st->trinode_temp_c;
    out_telemetry->trinode_delta_c        = st->trinode_delta_c;
    out_telemetry->trinode_confidence_pct = st->trinode_confidence_pct;
    out_telemetry->valid_trend            = st->valid_trend;
    out_telemetry->epd_glass_temp_c       = (float)st->last_glass_temp_centi_c / 100.0f;

    orch_tri_node_sample_t latest_samp = {0};
    if (orch_state_get_latest_sample(&latest_samp)) {
        out_telemetry->raw_shtc3_temp_c = (float)latest_samp.shtc3_temp_centi_c / 100.0f;
        out_telemetry->mcu_die_temp_c   = (float)latest_samp.mcu_tsens_centi_c / 100.0f;
    } else {
        out_telemetry->raw_shtc3_temp_c = t;
        out_telemetry->mcu_die_temp_c   = st->window_avg_die_c;
    }
    out_telemetry->sample_count      = st->total_samples;
    out_telemetry->flow_a_period_sec = (st->sample_interval_sec > 0) ? st->sample_interval_sec : 60;
    out_telemetry->flow_b_period_sec = (st->flow_b_period_sec > 0) ? st->flow_b_period_sec : 300;

    uint16_t vbat_mv = 0;
    uint8_t vbat_pct = 0;
    h1os_battery_state_t bat_state = H1OS_BATTERY_DISCHARGING;
    if (sub_power_get_battery_status(&vbat_mv, &vbat_pct, &bat_state) == ESP_OK) {
        out_telemetry->battery_mv      = vbat_mv;
        out_telemetry->battery_percent = vbat_pct;
        out_telemetry->is_usb_powered  = (bat_state == H1OS_BATTERY_CHARGED || sub_power_connected_usb());
        out_telemetry->battery_state   = bat_state;
        st->last_vbat_mv               = vbat_mv;
        if (!out_telemetry->is_usb_powered && (st->boot_vbat_mv == 0 || vbat_mv > st->boot_vbat_mv)) {
            st->boot_vbat_mv = vbat_mv;
        }
        out_telemetry->boot_vbat_mv = st->boot_vbat_mv;

        uint16_t current_soc_x10 = sub_power_mv_to_soc_tenths(vbat_mv);

        if (bat_state == H1OS_BATTERY_DISCHARGING) {
            bool state_transition_from_charge = (s_prev_bat_state == H1OS_BATTERY_CHARGING ||
                                                 s_prev_bat_state == H1OS_BATTERY_CHARGED);
            if (st->initial_soc_x10 == 0 ||
                state_transition_from_charge ||
                current_soc_x10 >= st->initial_soc_x10 + 30) {
                orch_state_reset_discharge_lap(current_soc_x10);
            }
        }
        s_prev_bat_state = bat_state;

        sub_power_calc_autonomy(st->initial_soc_x10,
                                current_soc_x10,
                                st->total_sleep_sec,
                                st->total_app_run_ms,
                                &out_telemetry->autonomy);
    }

    return ret;
}

/**
 * @brief Put the platform into ultra-low-power deep sleep.
 *
 * @param[in]    sleep_sec       Parameter sleep_sec.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t h1os_sleep(uint32_t sleep_sec)
{
    if (sleep_sec == 0) {
        ESP_LOGE(TAG, "Lifecycle error: h1os_sleep received sleep_sec = 0. Aborting sleep transition.");
        return ESP_ERR_INVALID_ARG;
    }
    ESP_LOGI(TAG, "Entering coordinated sleep sequence (%lu sec)...", (unsigned long)sleep_sec);
    h1os_trigger_chime(H1OS_CHIME_SLEEP);
    h1os_lvgl_lock(1000);
    h1os_trigger_splash(H1OS_SPLASH_SLEEP);
    if (s_app_lifecycle.on_pre_sleep) {
        s_app_lifecycle.on_pre_sleep(sleep_sec, s_app_lifecycle.user_data);
    }
    h1os_lvgl_unlock();

    h1os_quiesce_lvgl_pipeline();
    return orch_flow_transition_to_sleep(sleep_sec);
}

/**
 * @brief Execute system shutdown.
 *
 * @param[in]    force_clean_white Parameter force_clean_white.
 *
 * @return Return value of type static void.
 */
static void execute_system_shutdown(bool force_clean_white)
{
    ESP_LOGI(TAG, "Executing system shutdown (%s)...", force_clean_white ? "storage mode: clean white" : "standard mode");
    s_session_running = false;

    sub_rtc_cancel_countdown();

    h1os_trigger_chime(H1OS_CHIME_SHUTDOWN);
    h1os_lvgl_lock(1000);
    h1os_trigger_splash(H1OS_SPLASH_SHUTDOWN);
    if (s_app_lifecycle.on_shutdown) {
        s_app_lifecycle.on_shutdown(s_app_lifecycle.user_data);
    }
    h1os_lvgl_unlock();

    h1os_quiesce_lvgl_pipeline();

    sub_audio_wait_idle(1500);
    sub_audio_standby();

    sub_display_wait_busy(pdMS_TO_TICKS(5000));
    if (force_clean_white) {
        sub_display_clear_to_white_full();
        orch_state_get()->flags &= ~ORCH_FLAG_EPD_FRAME_VALID;
    } else {
        orch_display_sync_save_if_dirty();
    }
    sub_display_enter_deep_sleep();

    /* Persist cumulative autonomy runtimes to NVS prior to releasing power latch */
    volatile orch_persisted_state_t *st = orch_state_get();
    st->total_app_run_ms += (uint32_t)(esp_timer_get_time() / 1000ULL);
    orch_state_save_runtimes_to_nvs();

    int32_t stable_high = 0;
    for (int32_t i = 0; i < 200 && stable_high < 4; i++) {
        stable_high = (gpio_get_level(HAL_PIN_BUTTON_POWER) == 1) ? stable_high + 1 : 0;
        vTaskDelay(pdMS_TO_TICKS(50));
    }

    sub_power_cut_power_latch();
    vTaskDelay(pdMS_TO_TICKS(200));

    ESP_LOGW(TAG, "External power detected; entering standby (wake: POWER button only)");
    esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
    rtc_gpio_pullup_en(HAL_PIN_BUTTON_POWER);
    rtc_gpio_pulldown_dis(HAL_PIN_BUTTON_POWER);
    esp_sleep_enable_ext0_wakeup(HAL_PIN_BUTTON_POWER, 0);
    esp_deep_sleep_start();
}

/**
 * @brief Orderly system shutdown and physical battery power cut.
 */
void h1os_shutdown(void)
{
#if CONFIG_H1OS_EPD_CLEAN_WHITE_ON_SHUTDOWN
    execute_system_shutdown(true);
#else
    execute_system_shutdown(false);
#endif
}

/**
 * @brief Shutdown for long-term storage: clears display to pure white before cutting power.
 *
 * @details Protects e-Paper electrophoretic microcapsules against permanent dye migration and burn-in.
 */
void h1os_shutdown_for_storage(void)
{
    execute_system_shutdown(true);
}

/**
 * @brief Set audio subsystem output volume percentage (0% = Mute, 100% = 0 dB Max).
 *
 * @param[in]    volume_pct      Parameter volume_pct.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t h1os_set_volume(uint8_t volume_pct)
{
    return sub_audio_set_volume(volume_pct);
}