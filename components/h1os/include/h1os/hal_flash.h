/**
 * @file hal_flash.h
 * @brief Layer 1 HAL Raw Flash Partition Storage Driver for EPD Framebuffer
 * 
 * Target Partition: "epd_frame" (16 KB / 0x4000)
 * Invariant Rule: Performs sector-aligned erase and raw byte reads/writes.
 * 
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "h1os/hal_types.h"
#include "esp_partition.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Finds and verifies the dedicated "epd_frame" partition.
 * 
 * @return ESP_OK on success, or ESP_ERR_NOT_FOUND if partition is missing.
 */
esp_err_t hal_flash_init(void);

/**
 * @brief Reads the persisted 5000-byte EPD frame from flash.
 * 
 * @param out_buffer Destination buffer (must be at least 5000 bytes).
 * @param len Number of bytes to read (typically 5000).
 * @return ESP_OK on success, or flash read error.
 */
esp_err_t hal_flash_read_frame(uint8_t *out_buffer, size_t len);

/**
 * @brief Erases the partition sector and writes the 5000-byte frame.
 * 
 * @param frame_data Pointer to 5000-byte frame to commit.
 * @param len Length in bytes (must be <= partition size).
 * @return ESP_OK on success, or flash write error.
 */
esp_err_t hal_flash_write_frame(const uint8_t *frame_data, size_t len);

#ifdef __cplusplus
}
#endif
