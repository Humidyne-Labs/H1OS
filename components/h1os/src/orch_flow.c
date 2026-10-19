/**
 * @file orch_flow.c
 * @brief Layer 3: Execution flow arbiter and thermal lockout MUX implementation
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "h1os/orch_flow.h"

#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_rom_sys.h"
#include "esp_sleep.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "h1os/h1os_lvgl.h"
#include "h1os/hal_io.h"
#include "h1os/orch_display_sync.h"
#include "h1os/orch_math.h"
#include "h1os/orch_state.h"
#include "h1os/sub_audio.h"
#include "h1os/sub_display.h"
#include "h1os/sub_power.h"
#include "h1os/sub_rtc.h"
#include "h1os/sub_sensor.h"

#include <time.h>

static const char *TAG = "orch_flow";

#include "soc/efuse_struct.h"
#include "soc/gpio_reg.h"
#include "soc/rtc_cntl_reg.h"

#include <limits.h>
#include <math.h>

#define ORCH_HISTORICAL_EWMA_ALPHA 0.25f
#define ORCH_LEAKAGE_MARGIN_C 0.30f
#define ORCH_TRINODE_SPAN_C 15.0f

#include "ulp_h1os.h"

/**
 * @brief Inspect system wake source and arbitrate target flow.
 *
 * @return Detected flow type.
 */
orch_flow_type_t orch_flow_determine_wakeup(void)
{
    uint32_t causes = esp_sleep_get_wakeup_causes();
    orch_persisted_state_t *st = orch_state_get();

    if (causes & BIT(ESP_SLEEP_WAKEUP_UNDEFINED)) {
        st->boot_count++;
        if (EFUSE.rd_sys_part1_data4.blk_version_major != 0) {
            uint32_t cal_temp = EFUSE.rd_sys_part1_data4.temp_calib;

            int32_t cal_deci_c = ((cal_temp & BIT(8)) != 0) ? -(int32_t)((uint8_t)cal_temp) : (int32_t)((uint8_t)cal_temp);
            st->tsens_cal_centi_c = (int16_t)(cal_deci_c * 10);
        } else {
            st->tsens_cal_centi_c = 0;
        }
        uint32_t g17_out = (REG_READ(GPIO_OUT_REG) >> 17) & 1U;
        uint32_t g17_oe = (REG_READ(GPIO_ENABLE_REG) >> 17) & 1U;
        uint32_t g17_hold = (REG_READ(RTC_CNTL_PAD_HOLD_REG) >> 17) & 1U;
        ESP_LOGI(TAG, "System boot detected. Boot count: %lu (eFuse TSENS cal: %.2f C) | BL Hook GPIO17[out=%lu, oe=%lu, rtc_hold=%lu]",
						(unsigned long)st->boot_count, 
						(double)st->tsens_cal_centi_c / 100.0, 
						(unsigned long)g17_out,
						(unsigned long)g17_oe, 
						(unsigned long)g17_hold);
        return ORCH_FLOW_BOOT;
    }

    st->wake_count++;

    if (causes & BIT(ESP_SLEEP_WAKEUP_COCPU_TRAP_TRIG)) {
        ESP_LOGE(TAG, "[ULP FAULT] Coprocessor trapped/crashed! Causes bitmask: 0x%08lx", (unsigned long)causes);
        return ORCH_FLOW_B_MAIN_WAKE;
    }

    if (causes & BIT(ESP_SLEEP_WAKEUP_ULP)) {
        st->ulp_dispatch_reason = (uint8_t)(ulp_dispatch_reason & 0xFF);
        if (st->ulp_dispatch_reason == ULP_DISPATCH_CRITICAL_SHUTDOWN || st->ulp_dispatch_reason == ULP_DISPATCH_POWER_OFF) {
            return ORCH_FLOW_CRITICAL_OFF;
        }
        if (st->ulp_dispatch_reason == ULP_DISPATCH_BOOTLOADER_JUMP) {
            return ORCH_FLOW_BOOTLOADER_JUMP;
        }

        return ORCH_FLOW_B_MAIN_WAKE;
    }

    return ORCH_FLOW_B_MAIN_WAKE;
}

/**
 * @brief Check whether system is in Thermal Lockout state.
 *
 * @details If true, active dissipation from CPU/Display/Wi-Fi has perturbed board equilibrium.
 *
 * @return True if in lockout, False if in thermal equilibrium.
 */
bool orch_flow_is_thermal_lockout(void)
{
    return (orch_state_get()->valid_trend < 2);
}

/**
 * @brief Orch flow dump ring debug.
 *
 * @param[in]    st              Parameter st.
 *
 * @return Return value of type static void.
 */
static void orch_flow_dump_ring_debug(const orch_persisted_state_t *st)
{
    if (st == NULL)
        return;

    float shtc3T_ring[ORCH_RING_CAPACITY];
    float shtc3RH_ring[ORCH_RING_CAPACITY];
    float mcuT_ring[ORCH_RING_CAPACITY];
    float epdT_ring[ORCH_RING_CAPACITY];

    memset(shtc3T_ring, 0, sizeof(shtc3T_ring));
    memset(shtc3RH_ring, 0, sizeof(shtc3RH_ring));
    memset(mcuT_ring, 0, sizeof(mcuT_ring));
    memset(epdT_ring, 0, sizeof(epdT_ring));

    ESP_LOGI(TAG, "Ring Buffer Dump [TMP, RHP, DIE, EPD]:");
    for (int i = 0; i < ORCH_RING_CAPACITY; i++) {
        shtc3T_ring[i] = (float)st->ring[i].shtc3_temp_centi_c / 100.0f;
        shtc3RH_ring[i] = (float)st->ring[i].shtc3_rh_centi_pct / 100.0f;
        mcuT_ring[i] = (float)st->ring[i].mcu_tsens_centi_c / 100.0f;
        epdT_ring[i] = (float)st->ring[i].epd_glass_centi_c / 100.0f;
        ESP_LOGI(TAG, "  [%02d] %.2f, %.2f, %.2f, %.2f", 
						i, 
						(double)shtc3T_ring[i], 
						(double)shtc3RH_ring[i],
						(double)mcuT_ring[i], 
						(double)epdT_ring[i]);
    }
}

/**
 * @brief Orch flow scan ring metrics.
 *
 * @param[in]    st              Parameter st.
 *
 * @return Return value of type static void.
 */
static void orch_flow_scan_ring_metrics(orch_persisted_state_t *st)
{
    uint32_t count = (st->total_samples < ORCH_RING_CAPACITY) ? st->total_samples : ORCH_RING_CAPACITY;
    int16_t current_low = INT16_MAX;
    int16_t current_high = INT16_MIN;
    int32_t sum_shtc3 = 0;
    int32_t sum_die = 0;
    uint32_t valid_cnt = 0;

    for (uint32_t i = 0; i < count; i++) {
        if (st->ring[i].quality_flags & SAMPLE_FLAG_VALID_COLD) {
            int16_t s_t = st->ring[i].shtc3_temp_centi_c;
            if (s_t < current_low)
                current_low = s_t;
            if (s_t > current_high)
                current_high = s_t;
            sum_shtc3 += s_t;
            sum_die += st->ring[i].mcu_tsens_centi_c;
            valid_cnt++;
        }
    }

    if (valid_cnt == 0) {
        for (uint32_t i = 0; i < count; i++) {
            int16_t s_t = st->ring[i].shtc3_temp_centi_c;
            if (s_t < current_low)
                current_low = s_t;
            if (s_t > current_high)
                current_high = s_t;
            sum_shtc3 += s_t;
            sum_die += st->ring[i].mcu_tsens_centi_c;
            valid_cnt++;
        }
    }

    st->window_low_temp_centi_c = current_low;
    st->window_high_temp_centi_c = current_high;
    st->amb_floor_temp_centi_c = current_low;
    st->window_avg_shtc3_c = ((float)sum_shtc3 / (float)valid_cnt) / 100.0f;
    st->window_avg_die_c = ((float)sum_die / (float)valid_cnt) / 100.0f;
}

/**
 * @brief Orch flow evaluate ambient selection.
 *
 * @param[in]    st              Parameter st.
 * @param[in]    t_valid         Parameter t_valid.
 * @param[in]    t_die           Parameter t_die.
 * @param[in]    t_glass         Parameter t_glass.
 * @param[in]    out_mode        Parameter out_mode.
 *
 * @return Return value of type static float.
 */
static float orch_flow_evaluate_ambient_selection(orch_persisted_state_t *st, float t_valid, float t_die, float t_glass, const char **out_mode)
{
    float t_amb = t_valid;
    const char *mode = "SETTLED(T_valid)";

    if (st->valid_trend < 2) {
        float min_ref = (t_glass < t_die) ? t_glass : t_die;
        t_amb = (min_ref < t_valid) ? min_ref : t_valid;
        st->flags |= ORCH_FLAG_THERMAL_LOCKOUT;
        mode = "CASE_A_UNSETTLED";
    } else if (st->window_avg_shtc3_c > (st->window_avg_die_c + ORCH_LEAKAGE_MARGIN_C)) {
        t_amb = (t_die < t_glass) ? t_die : t_glass;
        st->flags |= ORCH_FLAG_THERMAL_LOCKOUT;
        mode = "CASE_B_LEAKAGE";
    } else {
        t_amb = t_valid;
        st->flags &= ~ORCH_FLAG_THERMAL_LOCKOUT;
    }

    if (out_mode) {
        *out_mode = mode;
    }
    return t_amb;
}

/**
 * @brief Query current environmental telemetry through the Thermal Lockout MUX.
 *
 * @details If in thermal equilibrium, takes fresh sensor reading. If in thermal lockout, transparently returns pristine cold reading from RTC ring buffer.
 *
 * @param[out]   out_temp_c      Reconstructed ambient temperature in Celsius.
 * @param[out]   out_rh_pct      Reconstructed ambient relative humidity in percent.
 * @param[out]   out_dew_c       True dew point in Celsius.
 *
 * @return ESP_OK on success.
 */
esp_err_t orch_flow_query_telemetry(float *out_temp_c, float *out_rh_pct, float *out_dew_c)
{
    orch_persisted_state_t *st = orch_state_get();

    if (st->total_samples == 0) {
        ESP_LOGI(TAG, "Flow A Telemetry: [COLD BOOT / NO SAMPLES YET] total_samples=0, glass=%.2f C",
						(double)st->last_glass_temp_centi_c / 100.0);
        if (out_temp_c)
            *out_temp_c = 0.0f;
        if (out_rh_pct)
            *out_rh_pct = 0.0f;
        if (out_dew_c)
            *out_dew_c = 0.0f;
        return ESP_OK;
    }

    float t_glass = (float)st->last_glass_temp_centi_c / 100.0f;
    orch_tri_node_sample_t latest_raw = {0};
    orch_state_get_latest_sample(&latest_raw);
    float t_die = (float)latest_raw.mcu_tsens_centi_c / 100.0f;

    orch_flow_scan_ring_metrics(st);

    orch_tri_node_sample_t valid_samp = {0};
    orch_state_get_latest_valid_sample(&valid_samp);

    float t_valid = (float)valid_samp.shtc3_temp_centi_c / 100.0f;
    float rh_valid = (float)valid_samp.shtc3_rh_centi_pct / 100.0f;

    if (!st->ewma_inited) {
        st->temp_historical_c = t_valid;
        st->rh_historical_pct = rh_valid;
        st->ewma_inited = true;
    } else {
        st->temp_historical_c = orch_math_update_ewma(t_valid, st->temp_historical_c, ORCH_HISTORICAL_EWMA_ALPHA);
        st->rh_historical_pct = orch_math_update_ewma(rh_valid, st->rh_historical_pct, ORCH_HISTORICAL_EWMA_ALPHA);
    }

    float t_trinode = (t_valid + t_die + t_glass) / 3.0f;
    float delta_trinode = t_valid - t_trinode;
    float conf = 100.0f - ((fabsf(delta_trinode) / ORCH_TRINODE_SPAN_C) * 100.0f);
    if (conf < 0.0f)
        conf = 0.0f;
    if (conf > 100.0f)
        conf = 100.0f;

    st->trinode_temp_c = t_trinode;
    st->trinode_delta_c = delta_trinode;
    st->trinode_confidence_pct = (uint8_t)(conf + 0.5f);

    const char *amb_mode = NULL;
    float t_amb = orch_flow_evaluate_ambient_selection(st, t_valid, t_die, t_glass, &amb_mode);

    float vp = 0.0f;
    float dew = 0.0f;
    float rh_amb = 0.0f;
    orch_math_calc_psychrometrics(t_valid, rh_valid, t_amb, &vp, &dew, &rh_amb);

    st->reconstructed_amb_temp_c = t_amb;
    st->reconstructed_amb_rh_pct = rh_amb;
    st->reconstructed_dew_point_c = dew;
    st->vapor_pressure_hpa = vp;

    ESP_LOGI(TAG,
             "Flow A Ring: samples=%lu head=%u trend=%u | Latest[SHTC3=%.2fC/%.1f%% Die=%.2fC flags=0x%02X]",
				(unsigned long)st->total_samples, 
				st->ring_head, st->valid_trend,
				(double)latest_raw.shtc3_temp_centi_c / 100.0, 
				(double)latest_raw.shtc3_rh_centi_pct / 100.0,
				(double)t_die, 
				latest_raw.quality_flags);
				
    ESP_LOGI(TAG, "Tri-Node & Tiers: mode=%s T_amb=%.2fC RH_amb=%.1f%% | "
				  "T_valid=%.2fC WinAvg[SHTC3=%.2fC Die=%.2fC] Hist=%.2fC | "
				  "Glass=%.2fC Tri=%.2fC(d=%+.2fC, conf=%u%%)",
					amb_mode, 
					(double)t_amb, 
					(double)rh_amb, 
					(double)t_valid, 
					(double)st->window_avg_shtc3_c,
					(double)st->window_avg_die_c, 
					(double)st->temp_historical_c, 
					(double)t_glass, 
					(double)t_trinode,
					(double)delta_trinode, 
					st->trinode_confidence_pct);

    orch_flow_dump_ring_debug(st);

    if (out_temp_c)
        *out_temp_c = t_amb;
    if (out_rh_pct)
        *out_rh_pct = rh_amb;
    if (out_dew_c)
        *out_dew_c = dew;
    return ESP_OK;
}

/**
 * @brief Orch flow quiesce peripherals.
 *
 * @return Return value of type static void.
 */
static void orch_flow_quiesce_peripherals(void)
{
    if (h1os_lvgl_has_pending_tasks()) {
        ESP_LOGI(TAG, "Waiting for LVGL pipeline to drain...");
        uint32_t wait_ms = 0;
        while (h1os_lvgl_has_pending_tasks() && wait_ms < 2500) {
            vTaskDelay(pdMS_TO_TICKS(20));
            wait_ms += 20;
        }
    }

    if (sub_audio_is_busy()) {
        ESP_LOGI(TAG, "Waiting for audio playback to finish...");
        sub_audio_wait_idle(1000);
    }
    sub_audio_standby();

    ESP_LOGI(TAG, "Waiting for EPD panel BUSY line...");
    sub_display_wait_busy(pdMS_TO_TICKS(5000));

    vTaskDelay(pdMS_TO_TICKS(250));

    orch_display_sync_save_if_dirty();

    sub_display_enter_deep_sleep();
}

/**
 * @brief Orch flow execute sleep.
 *
 * @param[in]    sleep_sec       Parameter sleep_sec.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t orch_flow_execute_sleep(uint32_t sleep_sec)
{
    uint32_t sample_sec = orch_state_get()->sample_interval_sec;
    uint32_t internal_sleep_sec = 0;
    if (sample_sec > 0 && sample_sec < sleep_sec) {
        internal_sleep_sec = sample_sec;
    }

    ESP_LOGI(TAG, "Entering coordinated deep sleep: External RTC UI timer = %lus, Internal Sample timer = %lus",
					(unsigned long)sleep_sec, 
					(unsigned long)internal_sleep_sec);

    uint64_t wake_mask = (1ULL << HAL_PIN_BUTTON_BOOT) | (1ULL << HAL_PIN_BUTTON_POWER) | (1ULL << HAL_PIN_RTC_INT);
    return sub_power_enter_deep_sleep(internal_sleep_sec, wake_mask);
}

/**
 * @brief Execute coordinated 8-step sleep transition sequence to deep sleep.
 *
 * @param[in]    sleep_sec       Sleep duration in seconds.
 *
 * @return ESP_OK on success.
 */
esp_err_t orch_flow_transition_to_sleep(uint32_t sleep_sec)
{
    if (sleep_sec == 0) {
        ESP_LOGE(TAG, "Lifecycle error: sleep_sec is 0. Aborting sleep transition.");
        return ESP_ERR_INVALID_ARG;
    }

    ESP_LOGI(TAG, "Sleep transition sequence starting (%lu sec)", (unsigned long)sleep_sec);
    orch_flow_quiesce_peripherals();
    return orch_flow_execute_sleep(sleep_sec);
}
