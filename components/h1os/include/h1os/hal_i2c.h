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

/**
 * @brief Initialize shared I2C master bus hardware.
 *
 * Installs ESP-IDF I2C driver on GPIO 47 / GPIO 48 and creates recursive mutex.
 *
 * @return
 *   - ESP_OK: Bus initialized and mutex created successfully.
 *   - ESP_ERR_INVALID_STATE: Driver already installed.
 *   - ESP_FAIL: Hardware initialization failed.
 */
esp_err_t hal_i2c_init(void);

/**
 * @brief Deinitialize shared I2C master bus and release mutex.
 *
 * @return ESP_OK on success.
 */
esp_err_t hal_i2c_deinit(void);

/**
 * @brief Execute an atomic register write transaction over I2C.
 *
 * @param[in] dev_addr   7-bit I2C device address.
 * @param[in] write_data Pointer to data buffer to transmit. Must not be NULL.
 * @param[in] write_len  Length of write buffer in bytes.
 * @param[in] timeout_ms Timeout budget in milliseconds.
 *
 * @return
 *   - ESP_OK: Write transaction acknowledged.
 *   - ESP_ERR_TIMEOUT: Bus transaction timed out.
 *   - ESP_ERR_INVALID_ARG: Null pointer.
 */
esp_err_t hal_i2c_write(uint8_t dev_addr, const uint8_t *write_data, size_t write_len, uint32_t timeout_ms);

/**
 * @brief Execute an atomic register read transaction over I2C.
 *
 * @param[in]  dev_addr   7-bit I2C device address.
 * @param[out] read_data  Pointer to buffer to receive data. Must not be NULL.
 * @param[in]  read_len   Number of bytes to read.
 * @param[in]  timeout_ms Timeout budget in milliseconds.
 *
 * @return
 *   - ESP_OK: Read transaction completed successfully.
 *   - ESP_ERR_TIMEOUT: Bus transaction timed out.
 *   - ESP_ERR_INVALID_ARG: Null pointer.
 */
esp_err_t hal_i2c_read(uint8_t dev_addr, uint8_t *read_data, size_t read_len, uint32_t timeout_ms);

/**
 * @brief Execute an atomic write-then-read combined transaction (Repeated START).
 *
 * @param[in]  dev_addr   7-bit I2C device address.
 * @param[in]  write_data Register address or command bytes to write. Must not be NULL.
 * @param[in]  write_len  Number of bytes to write.
 * @param[out] read_data  Destination buffer for read bytes. Must not be NULL.
 * @param[in]  read_len   Number of bytes to read.
 * @param[in]  timeout_ms Timeout budget in milliseconds.
 *
 * @return
 *   - ESP_OK: Combined transaction completed successfully.
 *   - ESP_ERR_TIMEOUT: Bus transaction timed out.
 *   - ESP_ERR_INVALID_ARG: Null pointer.
 */
esp_err_t hal_i2c_write_read(uint8_t dev_addr, const uint8_t *write_data, size_t write_len, uint8_t *read_data,
                             size_t read_len, uint32_t timeout_ms);

/**
 * @brief Probe if an I2C device responds with ACK at given 7-bit address.
 *
 * @param[in] dev_addr 7-bit device address to probe.
 *
 * @return
 *   - ESP_OK: Device responded with ACK.
 *   - ESP_ERR_NOT_FOUND: Device NACKed address byte.
 *   - ESP_ERR_TIMEOUT: Transaction timed out.
 */
esp_err_t hal_i2c_probe(uint8_t dev_addr);

#ifdef __cplusplus
}
#endif
