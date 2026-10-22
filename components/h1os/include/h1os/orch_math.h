/**
 * @file orch_math.h
 * @brief Layer 3: Class-E psychrometric math and EWMA filters
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Calculate saturation vapor pressure using August-Roche-Magnus approximation.
 *
 * @param[in] temp_c Temperature in degrees Celsius.
 *
 * @return Saturation vapor pressure in hectopascals (hPa).
 */
float orch_math_calc_sat_vapor_pressure(float temp_c);

/**
 * @brief Calculate actual water vapor partial pressure from temperature and relative humidity.
 *
 * @param[in] temp_c Temperature in degrees Celsius.
 * @param[in] rh_pct Relative humidity percentage (0..100%).
 *
 * @return Actual vapor pressure in hectopascals (hPa).
 */
float orch_math_calc_vapor_pressure(float temp_c, float rh_pct);

/**
 * @brief Calculate dew point temperature from temperature and relative humidity.
 *
 * @param[in] temp_c Temperature in degrees Celsius.
 * @param[in] rh_pct Relative humidity percentage (0..100%).
 *
 * @return Dew point in degrees Celsius.
 */
float orch_math_calc_dew_point(float temp_c, float rh_pct);

/**
 * @brief Calculate vapor pressure and dew point directly from factory-calibrated SHTC3 readings.
 *
 * @param[in]  temp_c     Settled SHTC3 temperature in Celsius.
 * @param[in]  rh_pct     Settled SHTC3 relative humidity %.
 * @param[out] out_vp_hpa Pointer to store vapor pressure in hPa.
 * @param[out] out_dew_c  Pointer to store dew point in Celsius.
 */
void orch_math_calc_psychrometrics(float temp_c, float rh_pct, float *out_vp_hpa, float *out_dew_c);

/**
 * @brief Calculate absolute humidity in grams per cubic meter (g/m³).
 *
 * @param[in] vapor_pressure_hpa Water vapor pressure in hPa.
 * @param[in] amb_temp_c         Ambient temperature in Celsius.
 *
 * @return Absolute humidity in g/m³.
 */
float orch_math_calc_absolute_humidity(float vapor_pressure_hpa, float amb_temp_c);

/**
 * @brief Update an Exponentially Weighted Moving Average (EWMA) filter.
 *
 * @param[in] current_sample New sample value.
 * @param[in] previous_ewma  Previous EWMA value.
 * @param[in] alpha          Smoothing factor (0.0 to 1.0).
 *
 * @return Updated EWMA value.
 */
float orch_math_update_ewma(float current_sample, float previous_ewma, float alpha);

/**
 * @brief Check if temperature trend has settled onto a stable thermal plateau.
 *
 * @param[in] initial_temp_centi_c   Initial reference temperature in centi-degrees Celsius.
 * @param[in] current_temp_centi_c   Current sampled temperature in centi-degrees Celsius.
 * @param[in] gate_threshold_centi_c Maximum allowable absolute delta in centi-degrees Celsius.
 *
 * @return True if |initial - current| <= gate_threshold.
 */
bool orch_math_is_plateau_settled(int16_t initial_temp_centi_c, int16_t current_temp_centi_c, int16_t gate_threshold_centi_c);

#ifdef __cplusplus
}
#endif
