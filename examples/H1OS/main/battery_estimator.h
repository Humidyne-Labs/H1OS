/**
 * @file battery_estimator.h
 * @brief H1OS showcase application: modular 4-screen environmental telemetry
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#ifndef BATTERY_ESTIMATOR_H
#define BATTERY_ESTIMATOR_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint32_t battery_get_soc_basis_pts(uint32_t vbat_mv);

float battery_estimate_avg_current_ma(uint32_t nominal_mah, uint32_t v1_mv, uint32_t v2_mv, uint32_t delta_t_sec);

static inline int32_t battery_estimate_avg_current_ua(uint32_t nominal_mah, uint32_t v1_mv, uint32_t v2_mv,
                                                      uint32_t delta_t_sec)
{
    float i_ma = battery_estimate_avg_current_ma(nominal_mah, v1_mv, v2_mv, delta_t_sec);
    if (i_ma < 0.0f) {
        return (int32_t)i_ma;
    }
    return (int32_t)(i_ma * 1000.0f);
}

float battery_estimate_remaining_days(uint32_t nominal_mah, uint32_t current_vbat_mv, float avg_current_ma);

#ifdef __cplusplus
}
#endif

#endif
