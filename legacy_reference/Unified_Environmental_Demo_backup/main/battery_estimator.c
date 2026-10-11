/**
 * @file battery_estimator.c
 * @brief Empirical Battery State-of-Charge & Average Current Estimation Implementation
 *
 * @version 1.0.0
 * @attribution
 * - Architecture & Development: HUMIDYNE LABS / Humiditron (2026)
 *
 * SPDX-License-Identifier: MIT
 */

#include "battery_estimator.h"

uint32_t battery_get_soc_basis_pts(uint32_t vbat_mv)
{
    if (vbat_mv >= 4200) return 10000;
    if (vbat_mv >= 3850) {
        return 8000 + ((vbat_mv - 3850) * 2000) / (4200 - 3850);
    }
    if (vbat_mv >= 3650) {
        return 2000 + ((vbat_mv - 3650) * 6000) / (3850 - 3650);
    }
    if (vbat_mv >= 3300) {
        return 0 + ((vbat_mv - 3300) * 2000) / (3650 - 3300);
    }
    return 0;
}

float battery_estimate_avg_current_ma(uint32_t nominal_mah,
                                      uint32_t v1_mv,
                                      uint32_t v2_mv,
                                      uint32_t delta_t_sec)
{
    if (delta_t_sec == 0) {
        return -1.0f; // Division by zero
    }

    uint32_t soc1_bp = battery_get_soc_basis_pts(v1_mv);
    uint32_t soc2_bp = battery_get_soc_basis_pts(v2_mv);

    if (soc1_bp <= soc2_bp) {
        return -2.0f; // Voltage rise or zero change (charging/settling)
    }

    // Delta SoC as a float ratio [0.0 - 1.0]
    float delta_soc = (float)(soc1_bp - soc2_bp) / 10000.0f;
    float consumed_mah = (float)nominal_mah * delta_soc;
    float delta_hours = (float)delta_t_sec / 3600.0f;

    return consumed_mah / delta_hours;
}

float battery_estimate_remaining_days(uint32_t nominal_mah, uint32_t current_vbat_mv, float avg_current_ma)
{
    if (avg_current_ma <= 0.001f) {
        avg_current_ma = 0.35f; // Fallback to 5-min duty cycle model (~350 µA)
    }
    uint32_t soc_bp = battery_get_soc_basis_pts(current_vbat_mv);
    float remaining_mah = (float)nominal_mah * ((float)soc_bp / 10000.0f);
    float hours = remaining_mah / avg_current_ma;
    return hours / 24.0f;
}
