/**
 * @file bsp_equ_math.c
 * @brief Consolidated Mathematical & Psychrometric Equations Implementation
 *
 * @version 1.0.0
 * @attribution
 * - Architecture & Development: HUMIDYNE LABS / Humiditron
 * - AI Systems Co-Developer: Gemini (Google DeepMind)
 *
 * SPDX-License-Identifier: MIT
 */

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "bsp/bsp_equ_math.h"

// Magnus Formula Constants for -45°C to +60°C range
static const float SHTC3_MAGNUS_M  = 17.625f;
static const float SHTC3_MAGNUS_TN = 243.04f;
static const float SHTC3_MAGNUS_A  = 6.112f; // hPa

float bsp_math_calc_vapor_pressure_hpa(float temp_c, float rh_pct) {
    float rh_clamped = BSP_MATH_CLAMP(rh_pct, 0.01f, 100.0f);
    float sat_vapor  = SHTC3_MAGNUS_A * expf((SHTC3_MAGNUS_M * temp_c) / (SHTC3_MAGNUS_TN + temp_c));
    return (rh_clamped / 100.0f) * sat_vapor;
}

float bsp_math_calc_dew_point_c(float temp_c, float rh_pct) {
    float rh_clamped = BSP_MATH_CLAMP(rh_pct, 0.01f, 100.0f);
    float gamma      = logf(rh_clamped / 100.0f) + ((SHTC3_MAGNUS_M * temp_c) / (SHTC3_MAGNUS_TN + temp_c));
    return (SHTC3_MAGNUS_TN * gamma) / (SHTC3_MAGNUS_M - gamma);
}

float bsp_math_reconstruct_ambient_rh(float temp_sens_c, float rh_sens_pct, float temp_amb_c) {
    float rh_clamped = BSP_MATH_CLAMP(rh_sens_pct, 0.01f, 100.0f);
    float exponent   = ((SHTC3_MAGNUS_M * temp_sens_c) / (SHTC3_MAGNUS_TN + temp_sens_c)) -
                       ((SHTC3_MAGNUS_M * temp_amb_c)  / (SHTC3_MAGNUS_TN + temp_amb_c));
    float rh_amb     = rh_clamped * expf(exponent);
    return BSP_MATH_CLAMP(rh_amb, 0.0f, 100.0f);
}

float bsp_math_calc_absolute_humidity_g(float vapor_pressure_hpa, float temp_amb_c) {
    return 216.7f * (vapor_pressure_hpa / (273.15f + temp_amb_c));
}

uint8_t bsp_math_calc_confidence_score(float temp_sens_c, float temp_amb_c) {
    float delta_t = fabsf(temp_sens_c - temp_amb_c);
    float score   = 100.0f - (delta_t * 10.0f);
    return (uint8_t)BSP_MATH_CLAMP(score, 10.0f, 100.0f);
}

float bsp_math_apply_ewma(float current_sample, float *state_val, float alpha) {
    if (state_val == NULL) return current_sample;
    alpha      = BSP_MATH_CLAMP(alpha, 0.01f, 1.0f);
    *state_val = (alpha * current_sample) + ((1.0f - alpha) * (*state_val));
    return *state_val;
}

esp_err_t bsp_math_calc_sliding_window_metrics(const bsp_env_telemetry_history_t *history, bsp_sliding_window_metrics_t *out)
{
    if (history == NULL || out == NULL) return ESP_ERR_INVALID_ARG;
    memset(out, 0, sizeof(*out));

    uint32_t total = history->total_samples;
    if (total == 0) {
        return ESP_ERR_NOT_FOUND;
    }

    uint32_t count       = (total < BSP_ENV_SAMPLE_RING_CAPACITY) ? total : BSP_ENV_SAMPLE_RING_CAPACITY;
    uint32_t poll_sec    = (history->poll_interval_sec > 0) ? history->poll_interval_sec : 60;
    uint32_t clean_count = 0;
    float sum_temp       = 0.0f;
    float floor_temp     = 999.0f;
    float ceiling_temp   = -999.0f;
    float min_rh         = 100.0f;
    float max_rh         = 0.0f;

    float newest_clean_rh = 0.0f, oldest_clean_rh = 0.0f;
    bool found_newest = false;

    // Scan from newest to oldest sample in ring buffer
    for (uint32_t i = 0; i < count; i++) {
        uint32_t idx = (history->head_index + BSP_ENV_SAMPLE_RING_CAPACITY - 1 - i) % BSP_ENV_SAMPLE_RING_CAPACITY;
        bool is_clean = (history->window_clean_mask & (1ULL << idx)) != 0;

        float t_c = SHTC3_RAW_TO_TEMP_C(history->samples[idx].raw_temp_u16);
        float rh  = SHTC3_RAW_TO_RH_PCT(history->samples[idx].raw_rh_u16);

        if (is_clean || i == 0) {
            if (is_clean) clean_count++;
            sum_temp += t_c;
            if (t_c < floor_temp)   floor_temp = t_c;
            if (t_c > ceiling_temp) ceiling_temp = t_c;
            if (rh < min_rh)        min_rh = rh;
            if (rh > max_rh)        max_rh = rh;

            if (!found_newest) {
                newest_clean_rh = rh;
                found_newest = true;
            }
            oldest_clean_rh = rh;
        }
    }

    uint32_t denom = (clean_count > 0) ? clean_count : 1;
    out->clean_sample_count = clean_count;
    out->temp_avg_c         = sum_temp / (float)denom;
    out->temp_floor_c       = (floor_temp <= 200.0f) ? floor_temp : 25.0f;
    out->temp_ceiling_c     = (ceiling_temp >= -100.0f) ? ceiling_temp : 25.0f;
    out->rh_min_pct         = (min_rh <= 100.0f) ? min_rh : 50.0f;
    out->rh_max_pct         = (max_rh >= 0.0f) ? max_rh : 50.0f;

    // Trend rate (% RH / hr)
    if (count > 1) {
        float span_hours = (float)(count * poll_sec) / 3600.0f;
        if (span_hours > 0.001f) {
            out->trend_rate_rh_per_hr = (newest_clean_rh - oldest_clean_rh) / span_hours;
        }
    }

    // Settled sample rate per hour (0 - 60 smp/h)
    out->settled_sample_rate_per_hr = (float)clean_count * (3600.0f / (float)(count * poll_sec));
    if (out->settled_sample_rate_per_hr > 60.0f) out->settled_sample_rate_per_hr = 60.0f;

    // Clean window flag: window is clean if >= 75% of slots are cold & settled
    out->is_clean_window = (clean_count >= (count * 3 / 4)) && (clean_count > 0);

    return ESP_OK;
}
