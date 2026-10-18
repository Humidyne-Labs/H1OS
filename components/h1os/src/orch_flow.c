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
#include "esp_rom_sys.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <time.h>

static const char *TAG = "orch_flow";

#include <math.h>
#include <limits.h>
#include "soc/efuse_struct.h"
#include "soc/gpio_reg.h"
#include "soc/rtc_cntl_reg.h"

#define ORCH_HISTORICAL_EWMA_ALPHA   0.25f   /* Light EWMA alpha for long-term temp_historical */
#define ORCH_LEAKAGE_MARGIN_C        0.30f   /* SHTC3_avg > Die_avg + 0.30 C board heat leakage margin */
#define ORCH_TRINODE_SPAN_C          15.0f   /* Linear confidence 0-100% span (15.0 C delta = 0%) */

#include "ulp_h1os.h"

orch_flow_type_t orch_flow_determine_wakeup(void)
{
    uint32_t causes = esp_sleep_get_wakeup_causes();
    orch_persisted_state_t *st = orch_state_get();

    if (causes & BIT(ESP_SLEEP_WAKEUP_UNDEFINED)) {
        /* System boot / Power On Reset */
        st->boot_count++;
        if (EFUSE.rd_sys_part1_data4.blk_version_major != 0) {
            uint32_t cal_temp = EFUSE.rd_sys_part1_data4.temp_calib;
            /* BIT(8) is sign (1: negative, 0: positive); magnitude in 0.1 C (10 centi-C) */
            int32_t cal_deci_c = ((cal_temp & BIT(8)) != 0) ? -(int32_t)((uint8_t)cal_temp) : (int32_t)((uint8_t)cal_temp);
            st->tsens_cal_centi_c = (int16_t)(cal_deci_c * 10);
        } else {
            st->tsens_cal_centi_c = 0;
        }
        uint32_t g17_out  = (REG_READ(GPIO_OUT_REG) >> 17) & 1U;
        uint32_t g17_oe   = (REG_READ(GPIO_ENABLE_REG) >> 17) & 1U;
        uint32_t g17_hold = (REG_READ(RTC_CNTL_PAD_HOLD_REG) >> 17) & 1U;
        ESP_LOGI(TAG, "System boot detected. Boot count: %lu (eFuse TSENS cal: %.2f C) | BL Hook GPIO17[out=%lu, oe=%lu, rtc_hold=%lu]",
                 (unsigned long)st->boot_count, (float)st->tsens_cal_centi_c / 100.0f,
                 (unsigned long)g17_out, (unsigned long)g17_oe, (unsigned long)g17_hold);
        return ORCH_FLOW_BOOT;
    }

    st->wake_count++;

    /* Check for ULP Coprocessor crash / trap */
    if (causes & BIT(ESP_SLEEP_WAKEUP_COCPU_TRAP_TRIG)) {
        ESP_LOGE(TAG, "[ULP FAULT] Coprocessor trapped/crashed! Causes bitmask: 0x%08lx", (unsigned long)causes);
        return ORCH_FLOW_B_MAIN_WAKE;
    }

    /* Check ULP Coprocessor dispatch reason */
    if (causes & BIT(ESP_SLEEP_WAKEUP_ULP)) {
        st->ulp_dispatch_reason = (uint8_t)(ulp_dispatch_reason & 0xFF);
        if (st->ulp_dispatch_reason == ULP_DISPATCH_CRITICAL_SHUTDOWN ||
            st->ulp_dispatch_reason == ULP_DISPATCH_POWER_OFF) {
            return ORCH_FLOW_CRITICAL_OFF;
        }
        if (st->ulp_dispatch_reason == ULP_DISPATCH_BOOTLOADER_JUMP) {
            return ORCH_FLOW_BOOTLOADER_JUMP;
        }
        if (st->ulp_dispatch_reason == ULP_DISPATCH_SENSOR_SAMPLE) {
            return ORCH_FLOW_A_SAMPLE;
        }
        return ORCH_FLOW_B_MAIN_WAKE;
    }

    if (causes & BIT(ESP_SLEEP_WAKEUP_TIMER)) {
        st->ulp_dispatch_reason = ULP_DISPATCH_SENSOR_SAMPLE;
        return ORCH_FLOW_A_SAMPLE;
    }

    /* All non-boot wakeups reaching the OS are Flow B Main Wakes */
    return ORCH_FLOW_B_MAIN_WAKE;
}

void orch_flow_execute_sensor_sample(void)
{
    orch_persisted_state_t *st = orch_state_get();

    uint16_t raw_t  = 0;
    uint16_t raw_rh = 0;

    esp_err_t err = sub_sensor_read_shtc3_raw(&raw_t, &raw_rh, false);
    if (err == ESP_OK) {
        int16_t temp_centi_c  = (int16_t)(-4500 + (int32_t)((17500LL * raw_t) / 65535LL));
        uint16_t rh_centi_pct = (uint16_t)((10000LL * raw_rh) / 65535LL);

        float die_c = 0.0f;
        sub_sensor_init();
        sub_sensor_read_mcu_die_temp(&die_c);
        sub_sensor_deinit();
        int16_t die_centi_c = (int16_t)(die_c * 100.0f);

        /* Evaluate successive-sample delta gate */
        uint8_t q_flags = 0;
        if (st->total_samples == 0) {
            q_flags = 0;
            st->valid_trend = 0;
        } else {
            uint8_t prev_idx = (st->ring_head == 0) ? (ORCH_RING_CAPACITY - 1) : (st->ring_head - 1);
            int16_t prev_t = st->ring[prev_idx].shtc3_temp_centi_c;
            int16_t diff = temp_centi_c - prev_t;
            if (diff < 0) diff = -diff;

            if (diff <= SAMPLE_DELTA_GATE_CENTI_C) {
                st->ring[prev_idx].quality_flags |= (SAMPLE_FLAG_VALID_COLD | SAMPLE_FLAG_THERMAL_SETTLED);
                q_flags = SAMPLE_FLAG_VALID_COLD | SAMPLE_FLAG_THERMAL_SETTLED;
                if (st->valid_trend < 2) {
                    st->valid_trend = 2;
                } else {
                    st->valid_trend++;
                }
            } else {
                q_flags = 0;
                st->valid_trend = 0;
            }
        }

        orch_tri_node_sample_t sample = {
            .shtc3_temp_centi_c = temp_centi_c,
            .shtc3_rh_centi_pct = rh_centi_pct,
            .mcu_tsens_centi_c  = die_centi_c,
            .epd_glass_centi_c  = st->last_glass_temp_centi_c,
            .timestamp_sec      = (uint32_t)time(NULL),
            .quality_flags      = q_flags,
        };
        orch_state_push_sample(&sample);
        ESP_LOGI(TAG, "Flow A Sensor Sample committed: T=%.2f C, RH=%.2f %%, Die=%.2f C (Ring: %u/32, Trend: %u)",
                 (float)temp_centi_c / 100.0f, (float)rh_centi_pct / 100.0f,
                 (float)die_centi_c / 100.0f, st->ring_head, st->valid_trend);
    } else {
        ESP_LOGW(TAG, "Flow A SHTC3 read failed: %s", esp_err_to_name(err));
    }
}

bool orch_flow_is_thermal_lockout(void)
{
    /* Thermally settled once >= 2 successive Flow A samples pass the <= 0.20 C gate */
    return (orch_state_get()->valid_trend < 2);
}

void orch_flow_set_thermal_lockout(bool enable, uint32_t duration_sec)
{
    (void)duration_sec;
    orch_persisted_state_t *st = orch_state_get();
    if (enable) {
        st->flags |= ORCH_FLAG_THERMAL_LOCKOUT;
    } else {
        st->flags &= ~ORCH_FLAG_THERMAL_LOCKOUT;
    }
}

static void orch_flow_dump_ring_debug(const orch_persisted_state_t *st)
{
    if (st == NULL) return;

    /* Build internal debug arrays */
    float shtc3T_ring[ORCH_RING_CAPACITY];
    float shtc3RH_ring[ORCH_RING_CAPACITY];
    float mcuT_ring[ORCH_RING_CAPACITY];
    float epdT_ring[ORCH_RING_CAPACITY];

    /* Set to known state */
    memset(shtc3T_ring,  0, sizeof(shtc3T_ring));
    memset(shtc3RH_ring, 0, sizeof(shtc3RH_ring));
    memset(mcuT_ring,    0, sizeof(mcuT_ring));
    memset(epdT_ring,    0, sizeof(epdT_ring));

    ESP_LOGI(TAG, "Ring Buffer Dump [TMP, RHP, DIE, EPD]:");
    for (int i = 0; i < ORCH_RING_CAPACITY; i++) {
        shtc3T_ring[i]  = (float)st->ring[i].shtc3_temp_centi_c / 100.0f;
        shtc3RH_ring[i] = (float)st->ring[i].shtc3_rh_centi_pct / 100.0f;
        mcuT_ring[i]    = (float)st->ring[i].mcu_tsens_centi_c  / 100.0f;
        epdT_ring[i]    = (float)st->ring[i].epd_glass_centi_c  / 100.0f;
        ESP_LOGI(TAG, "  [%02d] %.2f, %.2f, %.2f, %.2f", i,
                 shtc3T_ring[i], 
                 shtc3RH_ring[i],
                 mcuT_ring[i],
                 epdT_ring[i]);
    }
}

esp_err_t orch_flow_query_telemetry(float *out_temp_c, float *out_rh_pct, float *out_dew_c)
{
    orch_persisted_state_t *st = orch_state_get();

    /* Flow B Invariant: Never query SHTC3 (0x70) in Flow B!
     * All calculations operate on the 32-sample RTC ring buffer populated by Flow A,
     * the pre-display SSD1681 Glass Thermistor (st->last_glass_temp_centi_c), and MCU Die TSENS. */

    /* 1. Cold-Boot / Empty Ring Buffer Guard (total_samples == 0):
     *    Do not fabricate or compute any temperatures on cold boot before Flow A has sampled. */
    if (st->total_samples == 0) {
        ESP_LOGI(TAG, "Flow A Telemetry: [COLD BOOT / NO SAMPLES YET] total_samples=0, glass=%.2f C",
                 (float)st->last_glass_temp_centi_c / 100.0f);
        if (out_temp_c) *out_temp_c = 0.0f;
        if (out_rh_pct) *out_rh_pct = 0.0f;
        if (out_dew_c)  *out_dew_c  = 0.0f;
        return ESP_OK;
    }

    /* 2. Read current Glass Temp (cached pre-display in sub_display_init) and Die Temp (from Flow A ring) */
    float t_glass = (float)st->last_glass_temp_centi_c / 100.0f;
    orch_tri_node_sample_t latest_raw = {0};
    orch_state_get_latest_sample(&latest_raw);
    float t_die = (float)latest_raw.mcu_tsens_centi_c / 100.0f;

    /* 3. Scan 32-Sample Ring Buffer: Compute Valid Window Floor, Ceiling, & Short-Term Averages */
    uint32_t count = (st->total_samples < ORCH_RING_CAPACITY) ? st->total_samples : ORCH_RING_CAPACITY;
    int16_t current_low  = INT16_MAX;
    int16_t current_high = INT16_MIN;
    int32_t sum_shtc3    = 0;
    int32_t sum_die      = 0;
    uint32_t valid_cnt   = 0;

    for (uint32_t i = 0; i < count; i++) {
        if (st->ring[i].quality_flags & SAMPLE_FLAG_VALID_COLD) {
            int16_t s_t = st->ring[i].shtc3_temp_centi_c;
            if (s_t < current_low)  current_low  = s_t;
            if (s_t > current_high) current_high = s_t;
            sum_shtc3 += s_t;
            sum_die   += st->ring[i].mcu_tsens_centi_c;
            valid_cnt++;
        }
    }

    /* If no sample in the window is marked VALID_COLD yet, scan all available samples */
    if (valid_cnt == 0) {
        for (uint32_t i = 0; i < count; i++) {
            int16_t s_t = st->ring[i].shtc3_temp_centi_c;
            if (s_t < current_low)  current_low  = s_t;
            if (s_t > current_high) current_high = s_t;
            sum_shtc3 += s_t;
            sum_die   += st->ring[i].mcu_tsens_centi_c;
            valid_cnt++;
        }
    }

    st->window_low_temp_centi_c  = current_low;
    st->window_high_temp_centi_c = current_high;
    st->amb_floor_temp_centi_c   = current_low;
    st->window_avg_shtc3_c       = ((float)sum_shtc3 / (float)valid_cnt) / 100.0f;
    st->window_avg_die_c         = ((float)sum_die   / (float)valid_cnt) / 100.0f;

    /* 4. Tier 1 (Current Valid Sample) & Tier 3 (Long-Term temp_historical Light EWMA) */
    orch_tri_node_sample_t valid_samp = {0};
    orch_state_get_latest_valid_sample(&valid_samp);

    float t_valid  = (float)valid_samp.shtc3_temp_centi_c / 100.0f;
    float rh_valid = (float)valid_samp.shtc3_rh_centi_pct / 100.0f;

    if (!st->ewma_inited) {
        st->temp_historical_c = t_valid;
        st->rh_historical_pct = rh_valid;
        st->ewma_inited       = true;
    } else {
        st->temp_historical_c = orch_math_update_ewma(t_valid, st->temp_historical_c, ORCH_HISTORICAL_EWMA_ALPHA);
        st->rh_historical_pct = orch_math_update_ewma(rh_valid, st->rh_historical_pct, ORCH_HISTORICAL_EWMA_ALPHA);
    }

    /* 5. Tri-Node Composite Mean & 0-100% Linear Confidence Score */
    float t_trinode = (t_valid + t_die + t_glass) / 3.0f;
    float delta_trinode = t_valid - t_trinode;
    float conf = 100.0f - ((fabsf(delta_trinode) / ORCH_TRINODE_SPAN_C) * 100.0f);
    if (conf < 0.0f) conf = 0.0f;
    if (conf > 100.0f) conf = 100.0f;

    st->trinode_temp_c         = t_trinode;
    st->trinode_delta_c        = delta_trinode;
    st->trinode_confidence_pct = (uint8_t)(conf + 0.5f);

    /* 6. Dynamic Ambient Selection (T_amb):
     *    - Case A (valid_trend < 2): Promote min(T_glass, T_die, T_valid)
     *    - Case B (window_avg_shtc3 > window_avg_die + margin): Promote min(T_die, T_glass)
     *    - Typical Settled: Use unsmoothed T_valid directly */
    float t_amb = t_valid;
    const char *amb_mode = "SETTLED(T_valid)";
    if (st->valid_trend < 2) {
        float min_ref = (t_glass < t_die) ? t_glass : t_die;
        t_amb = (min_ref < t_valid) ? min_ref : t_valid;
        st->flags |= ORCH_FLAG_THERMAL_LOCKOUT;
        amb_mode = "CASE_A_UNSETTLED";
    } else if (st->window_avg_shtc3_c > (st->window_avg_die_c + ORCH_LEAKAGE_MARGIN_C)) {
        t_amb = (t_die < t_glass) ? t_die : t_glass;
        st->flags |= ORCH_FLAG_THERMAL_LOCKOUT;
        amb_mode = "CASE_B_LEAKAGE";
    } else {
        t_amb = t_valid;
        st->flags &= ~ORCH_FLAG_THERMAL_LOCKOUT;
    }

    /* 7. Psychrometric Math (Magnus Equations from T_valid, RH_valid, and T_amb) */
    float vp     = orch_math_calc_vapor_pressure(t_valid, rh_valid);
    float dew    = orch_math_calc_dew_point(t_valid, rh_valid);
    float rh_amb = orch_math_reconstruct_ambient_rh(vp, t_amb);

    st->reconstructed_amb_temp_c  = t_amb;
    st->reconstructed_amb_rh_pct  = rh_amb;
    st->reconstructed_dew_point_c = dew;
    st->vapor_pressure_hpa        = vp;

    ESP_LOGI(TAG, "Flow A Ring: samples=%lu head=%u trend=%u | Latest[SHTC3=%.2fC/%.1f%% Die=%.2fC flags=0x%02X]",
             (unsigned long)st->total_samples, st->ring_head, st->valid_trend,
             (float)latest_raw.shtc3_temp_centi_c / 100.0f,
             (float)latest_raw.shtc3_rh_centi_pct / 100.0f,
             t_die, latest_raw.quality_flags);
    ESP_LOGI(TAG, "Tri-Node & Tiers: mode=%s T_amb=%.2fC RH_amb=%.1f%% | T_valid=%.2fC WinAvg[SHTC3=%.2fC Die=%.2fC] Hist=%.2fC | Glass=%.2fC Tri=%.2fC(d=%+.2fC, conf=%u%%)",
             amb_mode, t_amb, rh_amb, t_valid,
             st->window_avg_shtc3_c, st->window_avg_die_c, st->temp_historical_c,
             t_glass, t_trinode, delta_trinode, st->trinode_confidence_pct);

    /* Dump internal debug arrays modularly */
    orch_flow_dump_ring_debug(st);

    if (out_temp_c) *out_temp_c = t_amb;
    if (out_rh_pct) *out_rh_pct = rh_amb;
    if (out_dew_c)  *out_dew_c  = dew;
    return ESP_OK;
}

esp_err_t orch_flow_transition_to_sleep(uint32_t sleep_sec)
{
    if (sleep_sec == 0) {
        ESP_LOGE(TAG, "Lifecycle error: sleep_sec is 0. Aborting sleep transition.");
        return ESP_ERR_INVALID_ARG;
    }

    ESP_LOGI(TAG, "Sleep transition sequence starting (%lu sec)", (unsigned long)sleep_sec);

    /* 1. Wait for LVGL render and flush pipeline to drain completely (including badge update) */
    if (h1os_lvgl_has_pending_tasks()) {
        ESP_LOGI(TAG, "Waiting for LVGL pipeline to drain...");
        uint32_t wait_ms = 0;
        while (h1os_lvgl_has_pending_tasks() && wait_ms < 2500) {
            vTaskDelay(pdMS_TO_TICKS(20));
            wait_ms += 20;
        }
    }

    /* 1b. Wait for any background audio playback and soft-ramp teardown to complete */
    if (sub_audio_is_busy()) {
        ESP_LOGI(TAG, "Waiting for audio playback to finish...");
        sub_audio_wait_idle(1000);
    }
    sub_audio_standby();

    /* 2. Wait for physical EPD panel to finish driving electrophoretic particles (GPIO 8 BUSY falling edge) */
    ESP_LOGI(TAG, "Waiting for EPD panel BUSY line...");
    sub_display_wait_busy(pdMS_TO_TICKS(5000));

    /* 3. Post-Busy Particle Settling Guard: 250ms delay for micro-capsule voltages to discharge */
    vTaskDelay(pdMS_TO_TICKS(250));

    /* 4. Persist 5000-byte EPD frame to raw flash partition if modified */
    orch_display_sync_save_if_dirty();

    /* 5. Put SSD1681 display controller into Deep Sleep Mode 1 (1.0 µA) */
    sub_display_enter_deep_sleep();

    /* 6. Sub-Interval Sensor Timing & Centralized RTC Countdown Arming:
     * Note: Countdown timer arming is handled exclusively inside sub_power_enter_deep_sleep_mode()
     * to eliminate back-to-back I2C STOP/START/RELOAD cycles and avoid asynchronous clock-domain collisions! */
    uint32_t sample_sec = orch_state_get()->sample_interval_sec;
    uint32_t internal_sleep_sec = 0;
    if (sample_sec > 0 && sample_sec < sleep_sec) {
        internal_sleep_sec = sample_sec;
    }

    ESP_LOGI(TAG, "Entering coordinated deep sleep: External RTC UI timer = %lus, Internal Sample timer = %lus",
             (unsigned long)sleep_sec, (unsigned long)internal_sleep_sec);

    /* 7. Drain GPIO 5 pulse: Wait for external PCF85063A ~15.6ms open-drain pulse to release HIGH.
     * Bounded to 25ms timeout. Entering deep sleep while the line is held LOW causes immediate
     * false triggers, missed edge transitions, and PMU arbitration aborts! */
    uint32_t drain_wait_us = 0;
    while (gpio_get_level(HAL_PIN_RTC_INT) == 0 && drain_wait_us < 25000) {
        esp_rom_delay_us(500);
        drain_wait_us += 500;
    }

    /* 8. Enter hardware deep sleep with buttons and RTC INT wake sources */
    uint64_t wake_mask = (1ULL << HAL_PIN_BUTTON_BOOT) |
                         (1ULL << HAL_PIN_BUTTON_POWER) |
                         (1ULL << HAL_PIN_RTC_INT);
    return sub_power_enter_deep_sleep(internal_sleep_sec, wake_mask);
}

