/**
 * @file orch_display_sync.h
 * @brief Layer 3: Deferred flash frame sync engine
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "esp_err.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Mark current display frame as dirty, scheduling a deferred SPI flash backup.
 */
void orch_display_sync_mark_dirty(void);

/**
 * @brief Commit active display framebuffer to SPI flash if marked dirty.
 *
 * @return
 *   - ESP_OK: Flash partition written or buffer not dirty.
 *   - ESP_FAIL: Flash write failed.
 */
esp_err_t orch_display_sync_save_if_dirty(void);

/**
 * @brief Restore preserved display framebuffer from SPI flash into RAM buffer.
 *
 * @return
 *   - ESP_OK: Previous frame restored successfully.
 *   - ESP_FAIL: Flash read error.
 */
esp_err_t orch_display_sync_restore_to_framebuffer(void);

/**
 * @brief Determine whether the next display update requires a full OTP flash refresh.
 *
 * Evaluates monotonic partial refresh counter against panel DC bias clearance quota (typically 6).
 *
 * @return True if full refresh is mandated to prevent panel ghosting/burn-in.
 */
bool orch_display_sync_should_full_refresh(void);

/**
 * @brief Increment the consecutive partial refresh counter.
 */
void orch_display_sync_record_partial_refresh(void);

/**
 * @brief Reset the partial refresh counter following a full OTP refresh.
 */
void orch_display_sync_record_full_refresh(void);

/**
 * @brief Retrieve current monotonic partial refresh counter value.
 *
 * @return Number of partial refreshes executed since last full refresh.
 */
uint16_t orch_display_sync_get_partial_count(void);

#ifdef __cplusplus
}
#endif
