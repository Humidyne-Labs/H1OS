/**
 * @file sub_display.h
 * @brief Layer 2: SSD1681 1.54" 200x200 monochrome e-Paper display manager
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "esp_err.h"
#include "freertos/FreeRTOS.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define EPD_WIDTH  200 /**< Panel width in pixels.  */
#define EPD_HEIGHT 200 /**< Panel height in pixels. */

/**< 5000-byte 1-bit packed frame buffer size. */
#define EPD_BUFFER_SIZE ((EPD_WIDTH * EPD_HEIGHT) / 8)

/**
 * @brief Initialize SSD1681 electrophoretic display controller.
 *
 * Enables 3.3V power rail (GPIO 6), performs hardware reset pulse, and initializes
 * display RAM registers via SPI DMA.
 *
 * @param[in] is_wake_cycle True if resuming from sleep (bypasses full OTP clear).
 *
 * @return ESP_OK on success, or SPI communication error.
 */
esp_err_t sub_display_init(bool is_wake_cycle);

/**
 * @brief Deinitialize SSD1681 display subsystem and release SPI bus resources.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_deinit(void);

/**
 * @brief Retrieve direct pointer to the active 5000-byte internal RAM framebuffer.
 *
 * @return Pointer to packed 1-bit monochrome pixel array.
 */
uint8_t *sub_display_get_framebuffer(void);

/**
 * @brief Clear internal RAM framebuffer to pure color.
 *
 * @param[in] color 0x00 for solid black, 0xFF for solid white.
 */
void sub_display_clear(uint8_t color);

/**
 * @brief Synchronize SSD1681 previous-frame RAM with historical frame for differential refresh.
 *
 * @param[in] prev_frame Pointer to 5000-byte preserved previous framebuffer.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_sync_previous_frame(const uint8_t *prev_frame);

/**
 * @brief Block until SSD1681 BUSY line deasserts (panel update complete).
 *
 * @param[in] timeout_ticks FreeRTOS tick timeout.
 *
 * @return ESP_OK when panel idle, ESP_ERR_TIMEOUT on timeout.
 */
esp_err_t sub_display_wait_busy(TickType_t timeout_ticks);

/**
 * @brief Execute full OTP flashing refresh on electrophoretic panel.
 *
 * Completely clears DC bias and ghosting artifacts. Takes ~2.4 seconds.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_refresh_full(void);

/**
 * @brief Clear panel to solid white and trigger full OTP refresh.
 *
 * Mandatory prior to long-term storage or battery disconnection.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_clear_to_white_full(void);

/**
 * @brief Execute fast differential partial refresh on panel without screen flash.
 *
 * Updates only changed pixels. Takes ~300ms.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_refresh_partial(void);

/**
 * @brief Read temperature from SSD1681 embedded on-glass thermal sensor.
 *
 * @param[out] out_temp_c Pointer to store glass temperature in degrees Celsius.
 *
 * @return ESP_OK on success, or SPI read error.
 */
esp_err_t sub_display_read_glass_temp(float *out_temp_c);

/**
 * @brief Retrieve the latest cached SSD1681 on-glass temperature in centi-degrees Celsius.
 *
 * @return Cached glass temperature in centi-°C (0 if not yet sampled).
 */
int16_t sub_display_get_glass_temp_centi_c(void);

/**
 * @brief Put SSD1681 into Deep Sleep Mode 1 (<1uA quiescent drain).
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_enter_deep_sleep(void);

#ifdef __cplusplus
}
#endif
