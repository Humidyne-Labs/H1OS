/**
 * @file sub_display.h
 * @brief Layer 2: SSD1681 1.54" E-Paper Display Manager
 *
 * Provides Ping-Pong dual-RAM framebuffer management (0x24/0x26), partial waveform LUT,
 * BUSY synchronization via GPIO ISR, on-glass surface thermistor read (SPI Cmd 0x1B),
 * and Deep Sleep Mode 1 (1.0 µA) retention.
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"
#include "freertos/FreeRTOS.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EPD_WIDTH       200
#define EPD_HEIGHT      200
#define EPD_BUFFER_SIZE ((EPD_WIDTH * EPD_HEIGHT) / 8) /* 5000 bytes */

/**
 * @brief Initialize SSD1681 display controller.
 * Wakes panel, initializes SPI interface, configures scanning geometry,
 * and sets up BUSY synchronization semaphore.
 *
 * @param[in] is_wake_cycle True if resuming from deep sleep with persistent framebuffer.
 * @return ESP_OK on success.
 */
esp_err_t sub_display_init(bool is_wake_cycle);

/**
 * @brief Get pointer to the active working framebuffer (5000 bytes, 1-bit per pixel).
 * Bit 1 = White, Bit 0 = Black.
 */
uint8_t* sub_display_get_framebuffer(void);

/**
 * @brief Clear active working framebuffer.
 *
 * @param[in] color 0xFF for White, 0x00 for Black.
 */
void sub_display_clear(uint8_t color);

/**
 * @brief Synchronize previous frame into shadow buffer and hardware RAM 0x26.
 * Essential on deep sleep wake to enable differential partial scanning against the glass.
 *
 * @param[in] prev_frame Pointer to 5000-byte pre-sleep image buffer.
 * @return ESP_OK on success.
 */
esp_err_t sub_display_sync_previous_frame(const uint8_t *prev_frame);

/**
 * @brief Synchronously wait for EPD panel to finish driving electrophoretic particles.
 * Blocks on binary semaphore driven by GPIO 8 (BUSY) falling edge.
 *
 * @param[in] timeout_ticks Max FreeRTOS ticks to wait.
 * @return ESP_OK on panel ready, ESP_ERR_TIMEOUT on expiration.
 */
esp_err_t sub_display_wait_busy(TickType_t timeout_ticks);

/**
 * @brief Execute full display refresh (OTP factory waveform LUT).
 * Synchronizes old frame RAM (0x26) with new frame RAM (0x24).
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_refresh_full(void);

/**
 * @brief Clear display to pure white and trigger full OTP refresh.
 * Chemically neutralizes electrophoretic microcapsules to protect against permanent burn-in.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_clear_to_white_full(void);

/**
 * @brief Execute fast partial refresh (~300ms) with software LUT.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_refresh_partial(void);

/**
 * @brief Read SSD1681 on-glass integrated temperature sensor (SPI Cmd 0x1B).
 *
 * @param[out] out_temp_c Surface glass temperature in Celsius.
 * @return ESP_OK on success.
 */
esp_err_t sub_display_read_glass_temp(float *out_temp_c);

/**
 * @brief Put SSD1681 into Deep Sleep Mode 1 (Command 0x10, Data 0x01 @ 1.0 µA).
 * Crucially retains RAM contents while the 3.3V rail remains held.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_enter_deep_sleep(void);

#ifdef __cplusplus
}
#endif
