/**
 * @file hal_i2c.h
 * @brief Layer 1 HAL Thread-Safe Shared I2C Master Bus Driver
 *
 * Target Bus: GPIO 47 (SDA) & GPIO 48 (SCL) @ 400 kHz Fast-Mode
 * Invariant Rule: Protects physical I2C transactions with a recursive mutex.
 * Exposes atomic write, read, and write-read transactions.
 *
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
 * @brief Initializes the shared I2C master bus hardware.
 *
 * Installs ESP-IDF I2C driver on GPIO 47 / GPIO 48 and creates recursive mutex.
 *
 * @return ESP_OK on success, or driver error code.
 */
esp_err_t hal_i2c_init(void);

/**
 * @brief Deinitializes the shared I2C master bus and releases mutex.
 *
 * @return ESP_OK on success.
 */
esp_err_t hal_i2c_deinit(void);

/**
 * @brief Executes an atomic register write transaction over I2C.
 *
 * @param dev_addr 7-bit I2C device address.
 * @param write_data Pointer to data buffer to transmit.
 * @param write_len Length of write buffer in bytes.
 * @param timeout_ms Timeout budget in milliseconds.
 * @return ESP_OK on success, ESP_ERR_TIMEOUT, or NACK error.
 */
esp_err_t hal_i2c_write(uint8_t dev_addr, const uint8_t *write_data, size_t write_len, uint32_t timeout_ms);

/**
 * @brief Executes an atomic register read transaction over I2C.
 *
 * @param dev_addr 7-bit I2C device address.
 * @param read_data Pointer to buffer to receive data.
 * @param read_len Number of bytes to read.
 * @param timeout_ms Timeout budget in milliseconds.
 * @return ESP_OK on success, ESP_ERR_TIMEOUT, or NACK error.
 */
esp_err_t hal_i2c_read(uint8_t dev_addr, uint8_t *read_data, size_t read_len, uint32_t timeout_ms);

/**
 * @brief Executes an atomic write-then-read combined transaction (Repeated START).
 *
 * @param dev_addr 7-bit I2C device address.
 * @param write_data Register address or command bytes to write.
 * @param write_len Number of bytes to write.
 * @param read_data Destination buffer for read bytes.
 * @param read_len Number of bytes to read.
 * @param timeout_ms Timeout budget in milliseconds.
 * @return ESP_OK on success, ESP_ERR_TIMEOUT, or NACK error.
 */
esp_err_t hal_i2c_write_read(uint8_t dev_addr, const uint8_t *write_data, size_t write_len, uint8_t *read_data,
                             size_t read_len, uint32_t timeout_ms);

/**
 * @brief Probes if an I2C device with given 7-bit address responds on the bus.
 *
 * @param dev_addr 7-bit device address.
 * @return ESP_OK if device ACKed, ESP_ERR_NOT_FOUND or other error on NACK/timeout.
 */
esp_err_t hal_i2c_probe(uint8_t dev_addr);

#ifdef __cplusplus
}
#endif
