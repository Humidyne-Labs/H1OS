/**
 * @file hal_spi.h
 * @brief Layer 1 HAL DMA-Backed SPI Master Bus Driver for SSD1681 Display
 * 
 * Target Bus: SPI2 (FSPI)
 * Pins: SCK (GPIO 12), MOSI (GPIO 13), CS (GPIO 11), DC (GPIO 10), RST (GPIO 9), BUSY (GPIO 8)
 * 
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "bsp/hal_types.h"
#include "driver/spi_master.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes SPI2 Master host with DMA channel enabled for display communication.
 * 
 * @return ESP_OK on success, or driver error code.
 */
esp_err_t hal_spi_init(void);

/**
 * @brief Deinitializes SPI2 Master host and releases bus resources.
 * 
 * @return ESP_OK on success.
 */
esp_err_t hal_spi_deinit(void);

/**
 * @brief Transmits a single command byte to the SSD1681 controller (DC = 0).
 * 
 * @param cmd Command byte.
 * @return ESP_OK on success.
 */
esp_err_t hal_spi_write_cmd(uint8_t cmd);

/**
 * @brief Transmits data bytes to the SSD1681 controller (DC = 1).
 * 
 * @param data Pointer to buffer containing payload.
 * @param len Length of data in bytes.
 * @return ESP_OK on success.
 */
esp_err_t hal_spi_write_data(const uint8_t *data, size_t len);

/**
 * @brief Transmits a full 5000-byte frame buffer via DMA transfer.
 * 
 * @param frame_buffer Pointer to 5000-byte buffer.
 * @return ESP_OK on success.
 */
esp_err_t hal_spi_write_frame_dma(const uint8_t *frame_buffer);

/**
 * @brief Reads data from SSD1681 (e.g. on-glass thermal sensor Cmd 0x1B).
 * 
 * @param cmd Command to write before reading.
 * @param out_data Buffer to receive read bytes.
 * @param len Number of bytes to read.
 * @return ESP_OK on success.
 */
esp_err_t hal_spi_read_data(uint8_t cmd, uint8_t *out_data, size_t len);

#ifdef __cplusplus
}
#endif
