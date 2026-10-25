/**
 * @file screen_env_hero.c
 * @brief Screen 1: Primary environmental hero display page
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "h1os/h1os_lvgl.h"
#include "h1os/h1os_time.h"
#include "screens.h"

/**
 * @brief Renders Screen 1: Primary environmental hero telemetry page.
 *
 * @param[in]    telem           Pointer to validated environmental telemetry snapshot.
 * @param[in]    cycle_count     Monotonic update cycle count.
 * @param[in]    event_cb        Keypad navigation callback.
 */
void screen_env_hero_render(const h1os_telemetry_t *telem, uint32_t cycle_count, lv_event_cb_t event_cb)
{
    h1os_lvgl_lock(100);
    lv_obj_t *scr = screen_base_create("HUMIDYNE LABS", "1/4", event_cb);

    lv_obj_t *lbl_temp = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_temp, "%.1f°F", (double)telem->ambient_temp_f);
    lv_obj_set_style_text_font(lbl_temp, H1OS_FONT_20, 0);
    lv_obj_align(lbl_temp, LV_ALIGN_TOP_LEFT, 6, 32);

    lv_obj_t *lbl_rh = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_rh, "%.1f%%", (double)telem->ambient_rh_pct);
    lv_obj_set_style_text_font(lbl_rh, H1OS_FONT_20, 0);
    lv_obj_align(lbl_rh, LV_ALIGN_TOP_RIGHT, -6, 32);

    lv_obj_t *lbl_sub = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_sub, "(%.1f°C ambient)", (double)telem->ambient_temp_c);
    lv_obj_set_style_text_font(lbl_sub, H1OS_FONT_14, 0);
    lv_obj_align(lbl_sub, LV_ALIGN_TOP_LEFT, 6, 62);

    static lv_point_precise_t mid_pts[] = {{4, 88}, {196, 88}};
    lv_obj_t *mid_line = lv_line_create(scr);
    lv_line_set_points(mid_line, mid_pts, 2);
    lv_obj_set_style_line_width(mid_line, 1, 0);
    lv_obj_set_style_line_color(mid_line, lv_color_black(), 0);

    lv_obj_t *lbl_stat = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_stat, "Status:  %s (%u%%)",
                          telem->is_thermally_settled ? "SETTLED" : "SETTLING",
                          telem->trinode_confidence_pct);
    lv_obj_set_style_text_font(lbl_stat, H1OS_FONT_14, 0);
    lv_obj_align(lbl_stat, LV_ALIGN_TOP_LEFT, 6, 100);

    lv_obj_t *lbl_vp = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_vp, "Vapor P:  %.1f hPa", (double)telem->vapor_pressure_hpa);
    lv_obj_set_style_text_font(lbl_vp, H1OS_FONT_14, 0);
    lv_obj_align(lbl_vp, LV_ALIGN_TOP_LEFT, 6, 126);

    char time_str[16] = "--:--";
    h1os_time_get_formatted(H1OS_TIME_FMT_12H_MIN, time_str, sizeof(time_str));

    lv_obj_t *lbl_foot_l = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_foot_l, "Cycle #%lu", (unsigned long)cycle_count);
    lv_obj_set_style_text_font(lbl_foot_l, H1OS_FONT_14, 0);
    lv_obj_align(lbl_foot_l, LV_ALIGN_BOTTOM_LEFT, 6, -6);

    lv_obj_t *lbl_foot_r = lv_label_create(scr);
    lv_label_set_text(lbl_foot_r, time_str);
    lv_obj_set_style_text_font(lbl_foot_r, H1OS_FONT_14, 0);
    lv_obj_align(lbl_foot_r, LV_ALIGN_BOTTOM_RIGHT, -6, -6);

    h1os_lvgl_unlock();
}
