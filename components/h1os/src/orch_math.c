/**
 * @file orch_math.c
 * @brief Layer 3: Class-E psychrometric and signal math implementation
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "h1os/orch_math.h"

#include "esp_attr.h"

#include <math.h>

#define MAGNUS_A 17.625f
#define MAGNUS_B 243.04f

/**
 * @brief Calculate saturation vapor pressure e_s(T) in hPa.
 *
 * @details Formula: e_s(T) = 6.112 * exp((17.625 * T) / (243.04 + T))
 *
 * @param[in]    temp_c          Temperature in Celsius.
 *
 * @return Saturation vapor pressure in hPa.
 */
float orch_math_calc_sat_vapor_pressure(float temp_c)
{
    return 6.112f * expf((MAGNUS_A * temp_c) / (MAGNUS_B + temp_c));
}

/**
 * @brief Calculate actual water vapor pressure (e) in hPa.
 *
 * @details Formula: e = (rh_pct / 100.0) * e_s(temp_c)
 *
 * @param[in]    temp_c          Temperature in Celsius.
 * @param[in]    rh_pct          Relative humidity in percent (0 - 100).
 *
 * @return Actual water vapor pressure in hPa.
 */
float orch_math_calc_vapor_pressure(float temp_c, float rh_pct)
{
    float es = orch_math_calc_sat_vapor_pressure(temp_c);
    float rh_norm = rh_pct / 100.0f;
    
    if (rh_norm < 0.0f) {
        rh_norm = 0.0f;
    }

    if (rh_norm > 1.0f) {
        rh_norm = 1.0f;
    }

    return rh_norm * es;
}

/**
 * @brief Calculate true dew point (T_dew) in Celsius from temperature and relative humidity.
 *
 * @param[in]    temp_c          Measured temperature in Celsius.
 * @param[in]    rh_pct          Measured relative humidity in percent.
 *
 * @return Dew point in Celsius.
 */
float orch_math_calc_dew_point(float temp_c, float rh_pct)
{
    float rh_norm = rh_pct / 100.0f;
    if (rh_norm <= 0.0001f) {
        rh_norm = 0.0001f;
    }

    if (rh_norm > 1.0f) {
        rh_norm = 1.0f;
    }

    float gamma = logf(rh_norm) + (MAGNUS_A * temp_c) / (MAGNUS_B + temp_c);

    return (MAGNUS_B * gamma) / (MAGNUS_A - gamma);
}

/**
 * @brief Calculate vapor pressure (e) and dew point (T_dew) directly from factory-calibrated SHTC3 readings.
 *
 * @param[in]    temp_c          Settled SHTC3 temperature in Celsius.
 * @param[in]    rh_pct          Settled SHTC3 relative humidity in percent.
 * @param[out]   out_vp_hpa      Output vapor pressure in hPa (optional, can be NULL).
 * @param[out]   out_dew_c       Output dew point in Celsius (optional, can be NULL).
 */
void orch_math_calc_psychrometrics(float temp_c, float rh_pct, float *out_vp_hpa, float *out_dew_c)
{
    if (out_vp_hpa) {
        *out_vp_hpa = orch_math_calc_vapor_pressure(temp_c, rh_pct);
    }

    if (out_dew_c) {
        *out_dew_c = orch_math_calc_dew_point(temp_c, rh_pct);
    }
}

/**
 * @brief Calculate absolute humidity (vapor density) in grams per cubic meter (g/m³).
 *
 * @details Formula: d_v = 216.7 * (e / (273.15 + T_ambient))
 *
 * @param[in]    vapor_pressure_hpa Vapor pressure in hPa.
 * @param[in]    amb_temp_c      Ambient temperature in Celsius.
 *
 * @return Vapor density in g/m³.
 */
float orch_math_calc_absolute_humidity(float vapor_pressure_hpa, float amb_temp_c)
{
    float temp_k = 273.15f + amb_temp_c;
    if (temp_k <= 0.1f) {
        return 0.0f;
    }

    return 216.7f * (vapor_pressure_hpa / temp_k);
}

/**
 * @brief Update continuous recursive EWMA filter.
 *
 * @details S_t = alpha * X_t + (1 - alpha) * S_{t-1}
 *
 * @param[in]    current_sample  New sample value.
 * @param[in]    previous_ewma   Previous filtered value.
 * @param[in]    alpha           Weight coefficient (typically 0.25 to 0.35).
 *
 * @return Filtered result.
 */
float orch_math_update_ewma(float current_sample, float previous_ewma, float alpha)
{
    if (alpha <= 0.0f) {
        return previous_ewma;
    }

    if (alpha >= 1.0f) {
        return current_sample;
    }

    return (alpha * current_sample) + ((1.0f - alpha) * previous_ewma);
}

/**
 * @brief Evaluates whether sensor package has settled to thermal plateau (|initial - current| <= gate_threshold).
 *
 * @details Marked RTC_IRAM_ATTR so it can be safely called from the RTC Fast Memory deep sleep wake stub.
 *
 * @param[in]    initial_temp_centi_c   Previous/reference sample temp (centi-°C).
 * @param[in]    current_temp_centi_c   Current sample temp (centi-°C).
 * @param[in]    gate_threshold_centi_c Maximum allowable absolute drift (typically 20 centi-°C = 0.20 °C).
 *
 * @return True if |initial - current| <= gate_threshold.
 */
bool RTC_IRAM_ATTR orch_math_is_plateau_settled(int16_t initial_temp_centi_c, int16_t current_temp_centi_c,
                                                                              int16_t gate_threshold_centi_c)
{
    int32_t diff = (int32_t)current_temp_centi_c - (int32_t)initial_temp_centi_c;
    if (diff < 0) {
        diff = -diff;
    }

    return (diff <= (int32_t)gate_threshold_centi_c);
}
