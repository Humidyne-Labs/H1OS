/**
 * @file screen_psychrometrics.c
 * @brief Screen 2: Psychrometric engine and invariant metrics page
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "h1os/h1os_lvgl.h"
#include "h1os/h1os_time.h"
#include "screens.h"

/**
 * @brief Renders Screen 2: Psychrometric engine and invariant metrics page.
 *
 * @param[in]    telem           Pointer to validated environmental telemetry snapshot.
 * @param[in]    event_cb        Keypad navigation callback.
 */
void screen_psychrometrics_render(const h1os_telemetry_t *telem, lv_event_cb_t event_cb)
{
    h1os_lvgl_lock(100);
    lv_obj_t *scr = screen_base_create("PSYCHROMETRICS", "2/5", event_cb);

    /* Row 1: August-Roche-Magnus Condensation Dew Point */
    lv_obj_t *lbl_k1 = lv_label_create(scr);
    lv_label_set_text(lbl_k1, "Dew Point");
    lv_obj_set_style_text_font(lbl_k1, H1OS_FONT_14, 0);
    lv_obj_align(lbl_k1, LV_ALIGN_TOP_LEFT, 6, 32);

    lv_obj_t *lbl_v1 = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_v1, "%.1f°F (%.1f°C)",
                          (double)telem->dew_point_f,
                          (double)telem->dew_point_c);
    lv_obj_set_style_text_font(lbl_v1, H1OS_FONT_14, 0);
    lv_obj_align(lbl_v1, LV_ALIGN_TOP_RIGHT, -6, 32);

    /* Row 2: Absolute Volumetric Water Vapor Mass */
    lv_obj_t *lbl_k2 = lv_label_create(scr);
    lv_label_set_text(lbl_k2, "Abs Humidity");
    lv_obj_set_style_text_font(lbl_k2, H1OS_FONT_14, 0);
    lv_obj_align(lbl_k2, LV_ALIGN_TOP_LEFT, 6, 56);

    lv_obj_t *lbl_v2 = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_v2, "%.1f g/m³", (double)telem->absolute_humidity_g);
    lv_obj_set_style_text_font(lbl_v2, H1OS_FONT_14, 0);
    lv_obj_align(lbl_v2, LV_ALIGN_TOP_RIGHT, -6, 56);

    /* Row 3: Thermodynamic Water Vapor Pressure */
    lv_obj_t *lbl_k3 = lv_label_create(scr);
    lv_label_set_text(lbl_k3, "Vapor Pressure");
    lv_obj_set_style_text_font(lbl_k3, H1OS_FONT_14, 0);
    lv_obj_align(lbl_k3, LV_ALIGN_TOP_LEFT, 6, 80);

    lv_obj_t *lbl_v3 = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_v3, "%.1f hPa", (double)telem->vapor_pressure_hpa);
    lv_obj_set_style_text_font(lbl_v3, H1OS_FONT_14, 0);
    lv_obj_align(lbl_v3, LV_ALIGN_TOP_RIGHT, -6, 80);

    /* Row 4: Historical Sliding Window Floor */
    lv_obj_t *lbl_k4 = lv_label_create(scr);
    lv_label_set_text(lbl_k4, "Window Low");
    lv_obj_set_style_text_font(lbl_k4, H1OS_FONT_14, 0);
    lv_obj_align(lbl_k4, LV_ALIGN_TOP_LEFT, 6, 104);

    lv_obj_t *lbl_v4 = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_v4, "%.1f°C", (double)telem->window_low_c);
    lv_obj_set_style_text_font(lbl_v4, H1OS_FONT_14, 0);
    lv_obj_align(lbl_v4, LV_ALIGN_TOP_RIGHT, -6, 104);

    /* Row 5: Historical Sliding Window Ceiling */
    lv_obj_t *lbl_k5 = lv_label_create(scr);
    lv_label_set_text(lbl_k5, "Window High");
    lv_obj_set_style_text_font(lbl_k5, H1OS_FONT_14, 0);
    lv_obj_align(lbl_k5, LV_ALIGN_TOP_LEFT, 6, 128);

    lv_obj_t *lbl_v5 = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_v5, "%.1f°C", (double)telem->window_high_c);
    lv_obj_set_style_text_font(lbl_v5, H1OS_FONT_14, 0);
    lv_obj_align(lbl_v5, LV_ALIGN_TOP_RIGHT, -6, 128);

    /* Footer: TriNode Confidence & Posix Wall Clock */
    char time_str[16] = "--:--";
    h1os_time_get_formatted(H1OS_TIME_FMT_12H_MIN, time_str, sizeof(time_str));

    lv_obj_t *lbl_foot_l = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_foot_l, "Conf: %u%% (T:%u)",
                          telem->trinode_confidence_pct,
                          telem->valid_trend);
    lv_obj_set_style_text_font(lbl_foot_l, H1OS_FONT_14, 0);
    lv_obj_align(lbl_foot_l, LV_ALIGN_BOTTOM_LEFT, 6, -6);

    lv_obj_t *lbl_foot_r = lv_label_create(scr);
    lv_label_set_text(lbl_foot_r, time_str);
    lv_obj_set_style_text_font(lbl_foot_r, H1OS_FONT_14, 0);
    lv_obj_align(lbl_foot_r, LV_ALIGN_BOTTOM_RIGHT, -6, -6);

    h1os_lvgl_unlock();
}
