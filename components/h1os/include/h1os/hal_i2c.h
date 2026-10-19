/**
 * @file hal_i2c.h
 * @brief Layer 1: Thread-safe shared I2C master bus driver
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "h1os/hal_types.h"

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t hal_i2c_init(void);

esp_err_t hal_i2c_deinit(void);

esp_err_t hal_i2c_write(uint8_t dev_addr, const uint8_t *write_data, size_t write_len, uint32_t timeout_ms);

esp_err_t hal_i2c_read(uint8_t dev_addr, uint8_t *read_data, size_t read_len, uint32_t timeout_ms);

esp_err_t hal_i2c_write_read(uint8_t dev_addr, const uint8_t *write_data, size_t write_len, uint8_t *read_data,
                             size_t read_len, uint32_t timeout_ms);

esp_err_t hal_i2c_probe(uint8_t dev_addr);

#ifdef __cplusplus
}
#endif
