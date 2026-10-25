/**
 * @file orch_flow.c
 * @brief Layer 3: Execution flow arbiter and steady-state SHTC3 telemetry selector
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "h1os/orch_flow.h"

#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_rom_sys.h"
#include "esp_sleep.h"
#include "esp_system.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "h1os/hal_io.h"
#include "h1os/orch_display_sync.h"
#include "h1os/orch_math.h"
#include "h1os/orch_state.h"
#include "h1os/orch_wake_stub.h"
#include "h1os/sub_audio.h"
#include "h1os/sub_display.h"
#include "h1os/sub_power.h"
#include "h1os/sub_rtc.h"

#include <time.h>

static const char *TAG = "orch_flow";

#include "soc/efuse_struct.h"
#include "soc/gpio_reg.h"
#include "soc/rtc_cntl_reg.h"

#include <limits.h>
#include <math.h>
#include <string.h>

#define ORCH_HISTORICAL_EWMA_ALPHA 0.25f
#define ORCH_TRINODE_SPAN_C        15.0f
#define ORCH_RTC_ARM_RETRY_LIMIT   3U /**< Maximum retries attempting PCF85063A countdown timer arming. */

#include "ulp_h1os.h"

/**
 * @brief Inspect system wake source and arbitrate target flow.
 *
 * @return Detected flow type.
 */
orch_flow_type_t orch_flow_determine_wakeup(void)
{
    uint32_t causes = esp_sleep_get_wakeup_causes();
    volatile orch_persisted_state_t *st = orch_state_get();

    if ((causes & BIT(ESP_SLEEP_WAKEUP_UNDEFINED)) || esp_reset_reason() != ESP_RST_DEEPSLEEP) {
        orch_state_reset();
        st = orch_state_get();
        st->boot_count = 1;
        if (EFUSE.rd_sys_part1_data4.blk_version_major != 0) {
            uint32_t cal_temp = EFUSE.rd_sys_part1_data4.temp_calib;

            int32_t cal_deci_c = ((cal_temp & BIT(8)) != 0) ? -(int32_t)((uint8_t)cal_temp) : (int32_t)((uint8_t)cal_temp);
            st->tsens_cal_centi_c = (int16_t)(cal_deci_c * 10);
        } else {
            st->tsens_cal_centi_c = 0;
        }
        st->tsens_offset_centi_c = (int16_t)(ORCH_TSENS_DEFAULT_INTERCEPT_CENTI_C + st->tsens_cal_centi_c);

        uint32_t g17_out  = (REG_READ(GPIO_OUT_REG) >> 17) & 1U;
        uint32_t g17_oe   = (REG_READ(GPIO_ENABLE_REG) >> 17) & 1U;
        uint32_t g17_hold = (REG_READ(RTC_CNTL_PAD_HOLD_REG) >> 17) & 1U;
        ESP_LOGI(TAG, "System boot detected. Boot count: %lu (eFuse TSENS cal: %.2f C, intercept: %d cC) | BL Hook GPIO17[out=%lu, oe=%lu, rtc_hold=%lu]",
                        (unsigned long)st->boot_count,
                        (double)((float)st->tsens_cal_centi_c / 100.0f),
                        (int)st->tsens_offset_centi_c,
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
 * @details Returns true until at least two consecutive Flow A samples have settled
 *          within SAMPLE_DELTA_GATE_CENTI_C (|temp2 - temp1| <= 0.20 C).
 *
 * @return True if settling (lockout), False if board is in thermal steady state.
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
static void orch_flow_dump_ring_debug(const volatile orch_persisted_state_t *st)
{
    if (st == NULL) {
        return;
    }

    static float shtc3T_ring[ORCH_RING_CAPACITY];
    static float shtc3RH_ring[ORCH_RING_CAPACITY];
    static float mcuT_ring[ORCH_RING_CAPACITY];
    static float epdT_ring[ORCH_RING_CAPACITY];

    memset(shtc3T_ring, 0, sizeof(shtc3T_ring));
    memset(shtc3RH_ring, 0, sizeof(shtc3RH_ring));
    memset(mcuT_ring, 0, sizeof(mcuT_ring));
    memset(epdT_ring, 0, sizeof(epdT_ring));

    ESP_LOGI(TAG, "Ring Buffer Dump [TMP, RHP, DIE, EPD]:");
    for (uint32_t i = 0; i < ORCH_RING_CAPACITY; i++) {
        shtc3T_ring[i]  = (float)st->ring[i].shtc3_temp_centi_c / 100.0f;
        shtc3RH_ring[i] = (float)st->ring[i].shtc3_rh_centi_pct / 100.0f;
        mcuT_ring[i]    = (float)st->ring[i].mcu_tsens_centi_c / 100.0f;
        epdT_ring[i]    = (float)st->ring[i].epd_glass_centi_c / 100.0f;
        ESP_LOGI(TAG, " [%02lu] %.2f, %.2f, %.2f, %.2f", (unsigned long)i,
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
static void orch_flow_scan_ring_metrics(volatile orch_persisted_state_t *st)
{
    uint32_t count        = (st->total_samples < ORCH_RING_CAPACITY) ? st->total_samples : ORCH_RING_CAPACITY;
    int16_t  current_low  = INT16_MAX;
    int16_t  current_high = INT16_MIN;
    int32_t  sum_shtc3    = 0;
    int32_t  sum_die      = 0;
    uint32_t valid_cnt    = 0;

    for (uint32_t i = 0; i < count; i++) {
        if (st->ring[i].quality_flags & SAMPLE_FLAG_VALID_COLD) {
            int16_t s_t = st->ring[i].shtc3_temp_centi_c;
            if (s_t < current_low) {
                current_low = s_t;
            }
            if (s_t > current_high) {
                current_high = s_t;
            }
            sum_shtc3 += s_t;
            sum_die += st->ring[i].mcu_tsens_centi_c;
            valid_cnt++;
        }
    }

    if (valid_cnt == 0) {
        for (uint32_t i = 0; i < count; i++) {
            int16_t s_t = st->ring[i].shtc3_temp_centi_c;
            if (s_t < current_low) {
                current_low = s_t;
            }
            if (s_t > current_high) {
                current_high = s_t;
            }
            sum_shtc3 += s_t;
            sum_die += st->ring[i].mcu_tsens_centi_c;
            valid_cnt++;
        }
    }

    st->window_low_temp_centi_c  = current_low;
    st->window_high_temp_centi_c = current_high;
    st->window_avg_shtc3_c       = ((float)sum_shtc3 / (float)valid_cnt) / 100.0f;
    st->window_avg_die_c         = ((float)sum_die / (float)valid_cnt) / 100.0f;
}

/**
 * @brief Query current environmental telemetry directly from factory-calibrated SHTC3 steady-state samples.
 *
 * @details The SHTC3 is factory-calibrated and requires no synthetic offsets, reconstitutions, or taring.
 *          When consecutive Flow A samples satisfy |temp2 - temp1| <= SAMPLE_DELTA_GATE_CENTI_C, the board
 *          is at thermal steady state and the SHTC3 reading is trusted directly. The EPD glass and MCU die
 *          sensors serve strictly to verify that the SHTC3 is operating within a normal range.
 *
 * @param[out]   out_temp_c      Trusted SHTC3 ambient temperature in Celsius.
 * @param[out]   out_rh_pct      Trusted SHTC3 ambient relative humidity in percent.
 * @param[out]   out_dew_c       Calculated dew point in Celsius.
 *
 * @return ESP_OK on success.
 */
esp_err_t orch_flow_query_telemetry(float *out_temp_c, float *out_rh_pct, float *out_dew_c)
{
    volatile orch_persisted_state_t *st = orch_state_get();

    int16_t disp_glass = sub_display_get_glass_temp_centi_c();
    if (disp_glass != 0) {
        st->last_glass_temp_centi_c = disp_glass;
    }

    if (st->total_samples == 0) {
        ESP_LOGI(TAG, "Flow A Telemetry: [COLD BOOT / NO SAMPLES YET] total_samples=0, glass=%.2f C",
                        (double)((float)st->last_glass_temp_centi_c / 100.0f));
        if (out_temp_c) {
            *out_temp_c = 0.0f;
        }
        if (out_rh_pct) {
            *out_rh_pct = 0.0f;
        }
        if (out_dew_c) {
            *out_dew_c = 0.0f;
        }
        return ESP_OK;
    }

    float t_glass = (float)st->last_glass_temp_centi_c / 100.0f;
    orch_tri_node_sample_t latest_raw = {0};
    orch_state_get_latest_sample(&latest_raw);
    float t_die = (float)latest_raw.mcu_tsens_centi_c / 100.0f;

    orch_flow_scan_ring_metrics(st);

    orch_tri_node_sample_t valid_samp = {0};
    orch_state_get_latest_valid_sample(&valid_samp);

    /* Trust the factory-calibrated SHTC3 steady-state sample directly (zero offsets, zero reconstitution) */
    float t_valid  = (float)valid_samp.shtc3_temp_centi_c / 100.0f;
    float rh_valid = (float)valid_samp.shtc3_rh_centi_pct / 100.0f;

    bool is_new_sample = (st->total_samples != st->last_ewma_sample_seq);
    if (is_new_sample) {
        if (!st->ewma_inited) {
            st->temp_historical_c = t_valid;
            st->rh_historical_pct = rh_valid;
            st->ewma_inited = true;
        } else {
            st->temp_historical_c = orch_math_update_ewma(t_valid, st->temp_historical_c, ORCH_HISTORICAL_EWMA_ALPHA);
            st->rh_historical_pct = orch_math_update_ewma(rh_valid, st->rh_historical_pct, ORCH_HISTORICAL_EWMA_ALPHA);
        }
        st->last_ewma_sample_seq = st->total_samples;
    }

    /* Glass and MCU die sensors are used strictly to verify the SHTC3 is operating within a normal range */
    float t_trinode = (t_valid + t_die + t_glass) / 3.0f;
    float delta_trinode = t_valid - t_trinode;
    float conf = 100.0f - ((fabsf(delta_trinode) / ORCH_TRINODE_SPAN_C) * 100.0f);
    if (conf < 0.0f) {
        conf = 0.0f;
    }
    if (conf > 100.0f) {
        conf = 100.0f;
    }

    st->trinode_temp_c         = t_trinode;
    st->trinode_delta_c        = delta_trinode;
    st->trinode_confidence_pct = (uint8_t)(conf + 0.5f);

    if (orch_flow_is_thermal_lockout()) {
        st->flags |= ORCH_FLAG_THERMAL_LOCKOUT;
    } else {
        st->flags &= ~ORCH_FLAG_THERMAL_LOCKOUT;
    }

    float vp  = 0.0f;
    float dew = 0.0f;
    orch_math_calc_psychrometrics(t_valid, rh_valid, &vp, &dew);

    st->ambient_temp_c     = t_valid;
    st->ambient_rh_pct     = rh_valid;
    st->dew_point_c        = dew;
    st->vapor_pressure_hpa = vp;

    if (is_new_sample) {
        const char *state_str = (st->flags & ORCH_FLAG_THERMAL_LOCKOUT) ? "SETTLING" : "SETTLED(SHTC3_DIRECT)";
        ESP_LOGI(TAG,
                 "Flow A Ring: samples=%lu head=%u trend=%u | "
                 "Latest[SHTC3=%.2fC/%.1f%% Die=%.2fC flags=0x%02X]",
                    (unsigned long)st->total_samples,
                    st->ring_head,
                    st->valid_trend,
                    (double)((float)latest_raw.shtc3_temp_centi_c / 100.0f),
                    (double)((float)latest_raw.shtc3_rh_centi_pct / 100.0f),
                    (double)t_die,
                    latest_raw.quality_flags);

        ESP_LOGI(TAG, "SHTC3 & Verification Nodes: state=%s T_shtc3=%.2fC RH_shtc3=%.1f%% | "
                      "WinAvg[SHTC3=%.2fC Die=%.2fC] Hist=%.2fC | "
                      "Verify[Glass=%.2fC Die=%.2fC Tri=%.2fC d=%+.2fC conf=%u%%]",
                        state_str,
                        (double)t_valid,
                        (double)rh_valid,
                        (double)st->window_avg_shtc3_c,
                        (double)st->window_avg_die_c,
                        (double)st->temp_historical_c,
                        (double)t_glass,
                        (double)t_die,
                        (double)t_trinode,
                        (double)delta_trinode,
                        st->trinode_confidence_pct);

        orch_flow_dump_ring_debug(st);
    }

    if (out_temp_c) {
        *out_temp_c = t_valid;
    }
    if (out_rh_pct) {
        *out_rh_pct = rh_valid;
    }
    if (out_dew_c) {
        *out_dew_c = dew;
    }
    return ESP_OK;
}

/**
 * @brief Orch flow quiesce peripherals.
 *
 * @return Return value of type static void.
 */
static void orch_flow_quiesce_peripherals(void)
{
    if (sub_audio_is_busy()) {
        ESP_LOGI(TAG, "Waiting for audio playback to finish...");
        sub_audio_wait_idle(1000);
    }
    sub_audio_standby();

    ESP_LOGI(TAG, "Waiting for EPD panel BUSY line...");
    sub_display_wait_busy(pdMS_TO_TICKS(5000));

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
    volatile orch_persisted_state_t *st = orch_state_get();
    uint32_t flow_a_sec = st->sample_interval_sec;
    uint32_t flow_b_sec = (sleep_sec > 0) ? sleep_sec : st->flow_b_period_sec;

    if (flow_a_sec == 0 || flow_b_sec == 0) {
        ESP_LOGE(TAG, "Cannot execute sleep: unconfigured flow periods (flow_a=%lu, flow_b=%lu)",
                 (unsigned long)flow_a_sec, (unsigned long)flow_b_sec);
        return ESP_ERR_INVALID_STATE;
    }

    uint32_t full_slices = flow_b_sec / flow_a_sec;
    uint32_t remainder   = flow_b_sec % flow_a_sec;
    uint32_t overflow    = full_slices + (remainder > 0 ? 1 : 0);
    if (overflow == 0) {
        overflow = 1;
    }

    uint32_t initial_arm_sec = (full_slices > 0) ? flow_a_sec : remainder;
    esp_err_t rtc_err = ESP_FAIL;
    for (int32_t attempt = 0; attempt < (int32_t)ORCH_RTC_ARM_RETRY_LIMIT; attempt++) {
        rtc_err = sub_rtc_arm_countdown(initial_arm_sec);
        if (rtc_err == ESP_OK) {
            break;
        }
        vTaskDelay(pdMS_TO_TICKS(5));
    }
    if (rtc_err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to arm PCF85063A countdown after %u attempts: %s", (unsigned)ORCH_RTC_ARM_RETRY_LIMIT, esp_err_to_name(rtc_err));
    }

    orch_wake_stub_install();
    sub_power_set_sleep_slices(flow_a_sec, flow_b_sec, overflow, remainder);

    uint32_t internal_sleep_sec = 0;
    if (flow_a_sec < flow_b_sec) {
        internal_sleep_sec = flow_a_sec;
    }

    ESP_LOGI(TAG, "Entering coordinated deep sleep: External RTC UI timer = %lus (Pure Event Mode: %lu slices x %lus)",
                    (unsigned long)flow_b_sec,
                    (unsigned long)overflow,
                    (unsigned long)flow_a_sec);

    uint64_t wake_mask = (1ULL << HAL_PIN_BUTTON_BOOT) | (1ULL << HAL_PIN_BUTTON_POWER) | (1ULL << HAL_PIN_RTC_INT);
    return sub_power_enter_deep_sleep(internal_sleep_sec, wake_mask);
}

/**
 * @brief Execute coordinated sleep transition sequence to deep sleep.
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