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

/**
 * @brief Initialize Sensirion SHTC3 sensor and MCU internal TSENS hardware.
 *
 * @return ESP_OK on success, or sensor communication failure.
 */
esp_err_t sub_sensor_init(void);

/**
 * @brief Deinitialize sensors and put SHTC3 into sleep mode.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_sensor_deinit(void);

/**
 * @brief Read raw 16-bit ADC ticks from Sensirion SHTC3 sensor over I2C.
 *
 * Wakes SHTC3, triggers measurement, reads 6-byte response with CRC validation,
 * and commands SHTC3 back to sleep.
 *
 * @param[out] out_raw_temp Pointer to store raw 16-bit temperature ticks. Must not be NULL.
 * @param[out] out_raw_rh   Pointer to store raw 16-bit relative humidity ticks. Must not be NULL.
 * @param[in]  low_power    True to use low-power measurement mode (0.8ms vs 12ms).
 *
 * @return ESP_OK on success, ESP_ERR_INVALID_CRC on CRC mismatch, or I2C timeout.
 */
esp_err_t sub_sensor_read_shtc3_raw(uint16_t *out_raw_temp, uint16_t *out_raw_rh, bool low_power);

/**
 * @brief Convert raw SHTC3 ticks into engineering units (°C and %RH).
 *
 * Formula: T = -45 + 175 * (raw_temp / 65535), RH = 100 * (raw_rh / 65535).
 *
 * @param[in]  raw_temp   Raw 16-bit temperature ticks.
 * @param[in]  raw_rh     Raw 16-bit relative humidity ticks.
 * @param[out] out_temp_c Pointer to store temperature in degrees Celsius.
 * @param[out] out_rh_pct Pointer to store relative humidity percentage.
 */
void sub_sensor_convert_shtc3_units(uint16_t raw_temp, uint16_t raw_rh, float *out_temp_c, float *out_rh_pct);

/**
 * @brief Read temperature from ESP32-S3 internal on-die temperature sensor (TSENS).
 *
 * @param[out] out_die_temp_c Pointer to store die temperature in degrees Celsius. Must not be NULL.
 *
 * @return ESP_OK on success, or driver error code.
 */
esp_err_t sub_sensor_read_mcu_die_temp(float *out_die_temp_c);

#ifdef __cplusplus
}
#endif
