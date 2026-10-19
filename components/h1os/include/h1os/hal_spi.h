/**
 * @file hal_spi.h
 * @brief Layer 1: DMA-backed SPI master bus driver for SSD1681 display
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "driver/spi_master.h"
#include "h1os/hal_types.h"

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t hal_spi_init(void);

esp_err_t hal_spi_deinit(void);

esp_err_t hal_spi_write_cmd(uint8_t cmd);

esp_err_t hal_spi_write_data(const uint8_t *data, size_t len);

esp_err_t hal_spi_write_frame_dma(const uint8_t *frame_buffer);

esp_err_t hal_spi_read_data(uint8_t cmd, uint8_t *out_data, size_t len);

#ifdef __cplusplus
}
#endif
