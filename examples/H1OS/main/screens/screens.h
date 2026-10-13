/**
 * @file screens.h
 * @brief H1OS Demo Modular Screen Layouts & Base Frame Builder
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "h1os/h1os.h"
#include "lvgl.h"

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

/**
 * @brief Creates standard 200x200 canvas with top header and divider line.
 * Locks LVGL internally. Must call h1os_lvgl_unlock() when screen assembly completes.
 *
 * @param[in] title    Header title text (e.g., "HUMIDYNE LABS").
 * @param[in] page_str Page indicator string (e.g., "1/4").
 * @param[in] event_cb Keypad input callback to register on the screen canvas.
 * @return Active screen lv_obj_t pointer.
 */
lv_obj_t* screen_base_create(const char *title, const char *page_str, lv_event_cb_t event_cb);

/**
 * @brief Update the active top-right page indicator badge to reflect awake (inverted) or sleep (normal) state.
 */
void screen_base_set_awake_badge(bool is_awake);

/**
 * @brief Render Screen 1: Primary Environmental Hero (Page 1/4)
 */
void screen_env_hero_render(const h1os_telemetry_t *telem, uint32_t cycle_count, lv_event_cb_t event_cb);

/**
 * @brief Render Screen 2: Psychrometrics Engine & Invariants (Page 2/4)
 */
void screen_psychrometrics_render(const h1os_telemetry_t *telem, lv_event_cb_t event_cb);

/**
 * @brief Render Screen 3: System Health & Battery Autonomy (Page 3/4)
 */
void screen_system_health_render(const h1os_telemetry_t *telem, lv_event_cb_t event_cb);

/**
 * @brief Render Screen 4: Verbose OS Diagnostics (Page 4/4)
 */
void screen_diagnostics_render(const h1os_telemetry_t *telem, lv_event_cb_t event_cb);

#ifdef __cplusplus
}
#endif
