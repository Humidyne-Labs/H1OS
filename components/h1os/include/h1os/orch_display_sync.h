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

void orch_display_sync_mark_dirty(void);

esp_err_t orch_display_sync_save_if_dirty(void);

esp_err_t orch_display_sync_restore_to_framebuffer(void);

bool orch_display_sync_should_full_refresh(void);

void orch_display_sync_record_partial_refresh(void);

void orch_display_sync_record_full_refresh(void);

uint16_t orch_display_sync_get_partial_count(void);

#ifdef __cplusplus
}
#endif
