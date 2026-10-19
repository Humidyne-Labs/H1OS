/**
 * @file sub_sensor.h
 * @brief Layer 2: Sensirion SHTC3 and ESP32-S3 internal TSENS driver
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "esp_err.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t sub_sensor_init(void);

esp_err_t sub_sensor_deinit(void);

esp_err_t sub_sensor_read_shtc3_raw(uint16_t *out_raw_temp, uint16_t *out_raw_rh, bool low_power);

void sub_sensor_convert_shtc3_units(uint16_t raw_temp, uint16_t raw_rh, float *out_temp_c, float *out_rh_pct);

esp_err_t sub_sensor_read_mcu_die_temp(float *out_die_temp_c);

#ifdef __cplusplus
}
#endif
