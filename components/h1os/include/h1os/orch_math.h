/**
 * @file orch_math.h
 * @brief Layer 3: Class-E psychrometric invariant engine and EWMA filters
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
 * @brief Psychrometrically reconstruct ambient relative humidity at the true ambient floor temperature.
 *
 * Leverages the thermodynamic principle that water vapor partial pressure remains constant
 * across PCB microclimates and self-heating boundaries.
 *
 * @param[in] vapor_pressure_hpa Conserved vapor pressure in hPa.
 * @param[in] amb_floor_temp_c   True ambient floor temperature in degrees Celsius.
 *
 * @return Reconstructed ambient relative humidity percentage (0..100%).
 */
float orch_math_reconstruct_ambient_rh(float vapor_pressure_hpa, float amb_floor_temp_c);

/**
 * @brief Calculate full psychrometric suite from raw sensor readings and ambient floor temperature.
 *
 * @param[in]  temp_c       Raw sensor temperature in Celsius.
 * @param[in]  rh_pct       Raw sensor relative humidity %.
 * @param[in]  amb_floor_c  Estimated true ambient floor temperature in Celsius.
 * @param[out] out_vp_hpa   Pointer to store vapor pressure in hPa.
 * @param[out] out_dew_c    Pointer to store dew point in Celsius.
 * @param[out] out_rh_amb   Pointer to store reconstructed ambient relative humidity %.
 */
void orch_math_calc_psychrometrics(float temp_c, float rh_pct, float amb_floor_c, float *out_vp_hpa, float *out_dew_c, float *out_rh_amb);

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
