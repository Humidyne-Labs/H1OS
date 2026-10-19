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

float orch_math_calc_sat_vapor_pressure(float temp_c);

float orch_math_calc_vapor_pressure(float temp_c, float rh_pct);

float orch_math_calc_dew_point(float temp_c, float rh_pct);

float orch_math_reconstruct_ambient_rh(float vapor_pressure_hpa, float amb_floor_temp_c);

void orch_math_calc_psychrometrics(float temp_c, float rh_pct, float amb_floor_c, float *out_vp_hpa, float *out_dew_c,
                                   float *out_rh_amb);

float orch_math_calc_absolute_humidity(float vapor_pressure_hpa, float amb_temp_c);

float orch_math_update_ewma(float current_sample, float previous_ewma, float alpha);

bool orch_math_is_plateau_settled(int16_t initial_temp_centi_c, int16_t current_temp_centi_c,
                                  int16_t gate_threshold_centi_c);

#ifdef __cplusplus
}
#endif
