/**
 * @file hal_flash.h
 * @brief Layer 1: Raw flash partition storage driver for EPD framebuffer
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "esp_partition.h"
#include "h1os/hal_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize raw flash partition driver for display framebuffer persistence.
 *
 * Locates the dedicated 16KB "epd_frame" partition in SPI flash.
 *
 * @return
 *   - ESP_OK: Partition located and validated.
 *   - ESP_ERR_NOT_FOUND: "epd_frame" partition not present in partition table.
 */
esp_err_t hal_flash_init(void);

/**
 * @brief Read preserved 1-bit frame data from SPI flash partition.
 *
 * @param[out] out_buffer Destination buffer (capacity >= len). Must not be NULL.
 * @param[in]  len        Number of bytes to read (typically HAL_EPD_FRAME_SIZE_BYTES).
 *
 * @return
 *   - ESP_OK: Frame read successfully.
 *   - ESP_ERR_INVALID_ARG: Null pointer or buffer overflow.
 *   - ESP_FAIL: Flash read error.
 */
esp_err_t hal_flash_read_frame(uint8_t *out_buffer, size_t len);

/**
 * @brief Erase and write 1-bit frame data into SPI flash partition.
 *
 * Performs sector erase prior to flashing to guarantee bit integrity.
 *
 * @param[in] frame_data Pointer to 1-bit monochrome packed pixel buffer.
 * @param[in] len        Number of bytes to write (typically HAL_EPD_FRAME_SIZE_BYTES).
 *
 * @return
 *   - ESP_OK: Frame written successfully.
 *   - ESP_ERR_INVALID_ARG: Null pointer or invalid length.
 *   - ESP_FAIL: Flash erase or write error.
 */
esp_err_t hal_flash_write_frame(const uint8_t *frame_data, size_t len);

#ifdef __cplusplus
}
#endif
