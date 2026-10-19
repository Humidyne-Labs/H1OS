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

esp_err_t hal_flash_init(void);

esp_err_t hal_flash_read_frame(uint8_t *out_buffer, size_t len);

esp_err_t hal_flash_write_frame(const uint8_t *frame_data, size_t len);

#ifdef __cplusplus
}
#endif
