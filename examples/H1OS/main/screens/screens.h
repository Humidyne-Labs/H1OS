/**
 * @file screens.h
 * @brief H1OS showcase application: modular 4-screen environmental telemetry
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "h1os/h1os.h"
#include "lvgl.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define H1OS_NUM_SCREENS 4

typedef enum {
    H1OS_SCREEN_ENV_HERO = 0,
    H1OS_SCREEN_PSYCHROMETRICS,
    H1OS_SCREEN_SYSTEM_HEALTH,
    H1OS_SCREEN_DIAGNOSTICS,
} h1os_screen_id_t;

lv_obj_t *screen_base_create(const char *title, const char *page_str, lv_event_cb_t event_cb);

void screen_base_set_awake_badge(bool is_awake);

void screen_env_hero_render(const h1os_telemetry_t *telem, uint32_t cycle_count, lv_event_cb_t event_cb);

void screen_psychrometrics_render(const h1os_telemetry_t *telem, lv_event_cb_t event_cb);

void screen_system_health_render(const h1os_telemetry_t *telem, lv_event_cb_t event_cb);

void screen_diagnostics_render(const h1os_telemetry_t *telem, lv_event_cb_t event_cb);

#ifdef __cplusplus
}
#endif
