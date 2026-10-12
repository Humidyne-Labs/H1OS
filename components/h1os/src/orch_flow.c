/**
 * @file orch_flow.c
 * @brief Layer 3: Execution Flow Arbiter & Thermal Lockout MUX Implementation
 *
 * SPDX-License-Identifier: MIT
 */

#include "h1os/orch_flow.h"
#include "h1os/orch_state.h"
#include "h1os/orch_math.h"
#include "h1os/orch_display_sync.h"
#include "h1os/sub_sensor.h"
#include "h1os/sub_rtc.h"
#include "h1os/sub_power.h"
#include "h1os/sub_display.h"
#include "h1os/sub_audio.h"
#include "h1os/h1os_lvgl.h"
#include "h1os/hal_io.h"
#include "esp_sleep.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <time.h>

static const char *TAG = "orch_flow";

static int64_t s_lockout_until_us = 0;

#if CONFIG_ULP_COPROC_ENABLED
#include "ulp_h1os.h"
#endif

orch_flow_type_t orch_flow_determine_wakeup(void)
{
    uint32_t causes = esp_sleep_get_wakeup_causes();
    orch_persisted_state_t *st = orch_state_get();

    if (causes & BIT(ESP_SLEEP_WAKEUP_UNDEFINED)) {
        /* Cold boot / Power On Reset */
        st->boot_count++;
        ESP_LOGI(TAG, "Cold boot detected. Boot count: %lu", (unsigned long)st->boot_count);
        return ORCH_FLOW_COLD_BOOT;
    }

    st->wake_count++;

    /* Check ULP Coprocessor dispatch reason */
    if (causes & BIT(ESP_SLEEP_WAKEUP_ULP)) {
#if CONFIG_ULP_COPROC_ENABLED
        st->ulp_dispatch_reason = (uint8_t)(ulp_dispatch_reason & 0xFF);
#endif
        if (st->ulp_dispatch_reason == ULP_DISPATCH_CRITICAL_SHUTDOWN ||
            st->ulp_dispatch_reason == ULP_DISPATCH_POWER_OFF) {
            return ORCH_FLOW_CRITICAL_OFF;
        }
        if (st->ulp_dispatch_reason == ULP_DISPATCH_BOOTLOADER_JUMP) {
            return ORCH_FLOW_BOOTLOADER_JUMP;
        }
        if (st->ulp_dispatch_reason == ULP_DISPATCH_SENSOR_SPRINT) {
            return ORCH_FLOW_A_SPRINT;
        }
        return ORCH_FLOW_B_MAIN_WAKE;
    }

    /* Internal timer wake -> Flow A Headless Sensor Sprint */
    if (causes & BIT(ESP_SLEEP_WAKEUP_TIMER)) {
        return ORCH_FLOW_A_SPRINT;
    }

    /* Button or External RTC (EXT1) wake -> Flow B Main Wake */
    if (causes & BIT(ESP_SLEEP_WAKEUP_EXT1)) {
        return ORCH_FLOW_B_MAIN_WAKE;
    }

    /* Fallback default to Flow B */
    return ORCH_FLOW_B_MAIN_WAKE;
}

void orch_flow_execute_sub_sprint(void)
{
    /* Flow A: Execute rapid <4ms sensor read */
    sub_sensor_init();

    uint16_t raw_temp = 0;
    uint16_t raw_rh = 0;
    esp_err_t err = sub_sensor_read_shtc3_raw(&raw_temp, &raw_rh, true /* Low-Power 1ms */);

    float temp_c = 25.0f;
    float rh_pct = 50.0f;
    if (err == ESP_OK) {
        sub_sensor_convert_shtc3_units(raw_temp, raw_rh, &temp_c, &rh_pct);
    }

    float die_temp_c = 25.0f;
    sub_sensor_read_mcu_die_temp(&die_temp_c);

    /* Formulate Tri-Node sample */
    orch_tri_node_sample_t sample = {
        .shtc3_temp_centi_c = (int16_t)(temp_c * 100.0f),
        .shtc3_rh_centi_pct = (uint16_t)(rh_pct * 100.0f),
        .mcu_tsens_centi_c  = (int16_t)(die_temp_c * 100.0f),
        .epd_glass_centi_c  = (int16_t)(temp_c * 100.0f),
        .timestamp_sec      = (uint32_t)time(NULL),
        .quality_flags      = 0x01, /* Cold sample */
    };
    orch_state_push_sample(&sample);

    /* Update Math Engine Invariants */
    orch_persisted_state_t *st = orch_state_get();
    float vp = orch_math_calc_vapor_pressure(temp_c, rh_pct);
    float dew = orch_math_calc_dew_point(temp_c, rh_pct);

    /* Track ambient floor */
    if (sample.shtc3_temp_centi_c < st->amb_floor_temp_centi_c || !st->ewma_inited) {
        st->amb_floor_temp_centi_c = sample.shtc3_temp_centi_c;
    }
    float amb_floor_c = (float)st->amb_floor_temp_centi_c / 100.0f;
    float rh_amb = orch_math_reconstruct_ambient_rh(vp, amb_floor_c);

    if (!st->ewma_inited) {
        st->reconstructed_amb_temp_c  = amb_floor_c;
        st->reconstructed_amb_rh_pct  = rh_amb;
        st->reconstructed_dew_point_c = dew;
        st->vapor_pressure_hpa        = vp;
        st->ewma_inited               = true;
    } else {
        st->reconstructed_amb_temp_c  = orch_math_update_ewma(amb_floor_c, st->reconstructed_amb_temp_c, 0.30f);
        st->reconstructed_amb_rh_pct  = orch_math_update_ewma(rh_amb, st->reconstructed_amb_rh_pct, 0.30f);
        st->reconstructed_dew_point_c = orch_math_update_ewma(dew, st->reconstructed_dew_point_c, 0.30f);
        st->vapor_pressure_hpa        = vp;
    }

    /* Zero-Hour Conflict Elimination: Check if external RTC countdown or alarm expired */
    bool alarm_fired = false, timer_fired = false;
    sub_rtc_get_and_clear_interrupts(&alarm_fired, &timer_fired);
    if (alarm_fired || timer_fired) {
        ESP_LOGI(TAG, "Zero-Hour Collision: External RTC timer expired! Promoting to Flow B (Main App Wake)");
        sub_sensor_deinit();
        return;
    }

    uint32_t rem_sec = 0;
    esp_err_t rtc_err = sub_rtc_get_remaining_seconds(&rem_sec);
    if (rtc_err == ESP_OK && rem_sec == 0) {
        ESP_LOGI(TAG, "Zero-Hour Collision: External RTC remaining is 0s! Promoting to Flow B (Main App Wake)");
        sub_sensor_deinit();
        return;
    }

    /* Cadence Decision: Discard runt rearm if next sample lands at or after external RTC expiry */
    uint32_t next_sample_sec = st->sample_interval_sec;
    uint32_t internal_sleep_sec = 0;

    if (rtc_err == ESP_OK && next_sample_sec < rem_sec) {
        /* Next sensor sample will complete BEFORE external RTC expires -> Rearm */
        internal_sleep_sec = next_sample_sec;
        ESP_LOGD(TAG, "Rearming internal timer for next sprint (%lus, RTC due in %lus)",
                 (unsigned long)internal_sleep_sec, (unsigned long)rem_sec);
    } else {
        /* Next sample lands at or after external RTC expiry -> Discard rearm!
         * Sleep purely until external PCF85063A INT triggers Flow B (internal_sleep_sec = 0) */
        ESP_LOGI(TAG, "Discarding runt sprint rearm (RTC due in %lus <= %lus). Sleeping until external RTC INT.",
                 (unsigned long)rem_sec, (unsigned long)next_sample_sec);
        internal_sleep_sec = 0;
    }

    /* Return to deep sleep immediately */
    sub_sensor_deinit();
    sub_power_enter_deep_sleep(internal_sleep_sec, (1ULL << HAL_PIN_BUTTON_BOOT) |
                                                   (1ULL << HAL_PIN_BUTTON_POWER) |
                                                   (1ULL << HAL_PIN_RTC_INT));
}

bool orch_flow_is_thermal_lockout(void)
{
    return (esp_timer_get_time() < s_lockout_until_us);
}

void orch_flow_set_thermal_lockout(bool enable, uint32_t duration_sec)
{
    if (enable) {
        s_lockout_until_us = esp_timer_get_time() + ((int64_t)duration_sec * 1000000LL);
        orch_state_get()->flags |= ORCH_FLAG_THERMAL_LOCKOUT;
    } else {
        s_lockout_until_us = 0;
        orch_state_get()->flags &= ~ORCH_FLAG_THERMAL_LOCKOUT;
    }
}

esp_err_t orch_flow_query_telemetry(float *out_temp_c, float *out_rh_pct, float *out_dew_c)
{
    orch_persisted_state_t *st = orch_state_get();

    if (orch_flow_is_thermal_lockout()) {
        /* Transparently return pristine cold baseline values */
        if (out_temp_c) *out_temp_c = st->reconstructed_amb_temp_c;
        if (out_rh_pct) *out_rh_pct = st->reconstructed_amb_rh_pct;
        if (out_dew_c)  *out_dew_c  = st->reconstructed_dew_point_c;
        return ESP_OK;
    }

    /* System in equilibrium: perform live read */
    uint16_t raw_temp = 0;
    uint16_t raw_rh = 0;
    esp_err_t err = sub_sensor_read_shtc3_raw(&raw_temp, &raw_rh, false);
    if (err == ESP_OK) {
        float live_t = 25.0f, live_rh = 50.0f;
        sub_sensor_convert_shtc3_units(raw_temp, raw_rh, &live_t, &live_rh);
        float vp = orch_math_calc_vapor_pressure(live_t, live_rh);
        float dew = orch_math_calc_dew_point(live_t, live_rh);
        float amb_floor_c = (float)st->amb_floor_temp_centi_c / 100.0f;
        float recon_rh = orch_math_reconstruct_ambient_rh(vp, amb_floor_c);

        if (out_temp_c) *out_temp_c = amb_floor_c;
        if (out_rh_pct) *out_rh_pct = recon_rh;
        if (out_dew_c)  *out_dew_c  = dew;
        return ESP_OK;
    }

    /* Fallback on error to cached values */
    if (out_temp_c) *out_temp_c = st->reconstructed_amb_temp_c;
    if (out_rh_pct) *out_rh_pct = st->reconstructed_amb_rh_pct;
    if (out_dew_c)  *out_dew_c  = st->reconstructed_dew_point_c;
    return err;
}

esp_err_t orch_flow_transition_to_sleep(uint32_t sleep_sec)
{
    ESP_LOGI(TAG, "Sleep transition sequence starting (%lu sec)", (unsigned long)sleep_sec);

    /* 1. Wait for LVGL render and flush pipeline to drain completely */
    if (h1os_lvgl_has_pending_tasks()) {
        ESP_LOGI(TAG, "Waiting for LVGL pipeline to drain...");
        uint32_t wait_ms = 0;
        while (h1os_lvgl_has_pending_tasks() && wait_ms < 500) {
            vTaskDelay(pdMS_TO_TICKS(20));
            wait_ms += 20;
        }
    }

    /* 1b. Wait for any background audio playback and soft-ramp teardown to complete */
    if (sub_audio_is_busy()) {
        ESP_LOGI(TAG, "Waiting for audio playback to finish...");
        sub_audio_wait_idle(1000);
    }

    /* 2. Wait for physical EPD panel to finish driving electrophoretic particles (GPIO 8 BUSY falling edge) */
    ESP_LOGI(TAG, "Waiting for EPD panel BUSY line...");
    sub_display_wait_busy(pdMS_TO_TICKS(5000));

    /* 3. Post-Busy Particle Settling Guard: 250ms delay for micro-capsule voltages to discharge */
    vTaskDelay(pdMS_TO_TICKS(250));

    /* 4. Persist 5000-byte EPD frame to raw flash partition if modified */
    orch_display_sync_save_if_dirty();

    /* 5. Put SSD1681 display controller into Deep Sleep Mode 1 (1.0 µA) */
    sub_display_enter_deep_sleep();

    /* 6. Arm external PCF85063A countdown timer if sleep duration > 0 */
    if (sleep_sec > 0) {
        sub_rtc_arm_countdown(sleep_sec);
    }

    /* 7. Sub-Interval Sensor Cadence:
     * Arm internal timer for Flow A sample cadence (e.g. 30s) if sample_interval_sec < sleep_sec.
     * If sample interval is disabled or >= sleep_sec, sleep purely until external RTC expires. */
    uint32_t sample_sec = orch_state_get()->sample_interval_sec;
    uint32_t internal_sleep_sec = 0;
    if (sample_sec > 0 && sample_sec < sleep_sec) {
        internal_sleep_sec = sample_sec;
    }

    /* 8. Enter hardware deep sleep with buttons and RTC INT wake sources */
    uint64_t wake_mask = (1ULL << HAL_PIN_BUTTON_BOOT) |
                         (1ULL << HAL_PIN_BUTTON_POWER) |
                         (1ULL << HAL_PIN_RTC_INT);
    return sub_power_enter_deep_sleep(internal_sleep_sec, wake_mask);
}

