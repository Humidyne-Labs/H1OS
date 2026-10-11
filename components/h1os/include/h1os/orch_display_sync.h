/**
 * @file orch_display_sync.h
 * @brief Layer 3: Deferred Flash Frame Sync Engine
 *
 * Persists SSD1681 1.54" 200x200 framebuffer (5000 bytes) to the raw "epd_frame"
 * flash partition during sleep or shutdown, and restores it on wake for instant
 * differential partial updates. Prevents flash wear by writing only when dirty.
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Mark the current display framebuffer as dirty (needs flash persistence on sleep).
 */
void orch_display_sync_mark_dirty(void);

/**
 * @brief Save working display framebuffer to "epd_frame" flash partition if dirty.
 *
 * @return ESP_OK on success or if clean (no write needed).
 */
esp_err_t orch_display_sync_save_if_dirty(void);

/**
 * @brief Restore framebuffer from "epd_frame" flash partition into display working buffer.
 *
 * @return ESP_OK on success, ESP_ERR_NOT_FOUND if partition empty/invalid.
 */
esp_err_t orch_display_sync_restore_to_framebuffer(void);

#ifdef __cplusplus
}
#endif
