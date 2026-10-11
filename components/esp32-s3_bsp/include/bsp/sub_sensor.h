/**
 * @file sub_sensor.h
 * @brief Layer 2: Sensirion SHTC3 & ESP32-S3 Internal TSENS Driver
 *
 * Isolated physical sensor driver. Provides pristine physical readings without
 * algorithmic psychrometric compensation or power gating dependencies.
 * Cross-subsystem math and scheduling are handled strictly by Layer 3.
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize sensor hardware interfaces (internal TSENS handle).
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_sensor_init(void);

/**
 * @brief Deinitialize internal sensor drivers to free resources.
 * @return ESP_OK on success.
 */
esp_err_t sub_sensor_deinit(void);

/**
 * @brief Direct physical SHTC3 sensor readout (Wake -> Measure -> Read -> Sleep).
 *
 * @param[out] out_raw_temp Raw 16-bit Sensirion temperature register word.
 * @param[out] out_raw_rh   Raw 16-bit Sensirion relative humidity register word.
 * @param[in]  low_power    True for 1ms fast low-power conversion, False for 15ms high-precision.
 * @return ESP_OK on success, ESP_ERR_INVALID_CRC on CRC mismatch, or I2C bus error.
 */
esp_err_t sub_sensor_read_shtc3_raw(uint16_t *out_raw_temp, uint16_t *out_raw_rh, bool low_power);

/**
 * @brief Convert raw SHTC3 16-bit words into standard SI units.
 *
 * @param[in]  raw_temp Raw temperature word.
 * @param[in]  raw_rh   Raw relative humidity word.
 * @param[out] out_temp_c Temperature in Celsius.
 * @param[out] out_rh_pct Relative humidity in percent (0.0 to 100.0).
 */
void sub_sensor_convert_shtc3_units(uint16_t raw_temp, uint16_t raw_rh, float *out_temp_c, float *out_rh_pct);

/**
 * @brief Read ESP32-S3 internal silicon junction temperature via internal TSENS macro.
 *
 * @param[out] out_die_temp_c MCU die temperature in Celsius.
 * @return ESP_OK on success, or driver error.
 */
esp_err_t sub_sensor_read_mcu_die_temp(float *out_die_temp_c);

#ifdef __cplusplus
}
#endif
