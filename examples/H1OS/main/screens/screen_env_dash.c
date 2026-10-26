/**
 * @file screen_env_dash.c
 * @brief Screen 1: Primary environmental dashboard display page
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "h1os/h1os_lvgl.h"
#include "h1os/h1os_time.h"
#include "screens.h"

/**
 * @brief Renders Screen 1: Primary environmental dashboard telemetry page.
 *
 * @param[in]    telem           Pointer to validated environmental telemetry snapshot.
 * @param[in]    cycle_count     Monotonic update cycle count.
 * @param[in]    event_cb        Keypad navigation callback.
 */
void screen_env_dash_render(const h1os_telemetry_t *telem, uint32_t cycle_count, lv_event_cb_t event_cb)
{
    h1os_lvgl_lock(100);
    lv_obj_t *scr = screen_base_create("HUMIDYNE LABS", "1/5", event_cb);

    /* Primary Dashboard Reading: Ambient Temperature */
    lv_obj_t *lbl_temp = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_temp, "%.1f°F", (double)telem->ambient_temp_f);
    lv_obj_set_style_text_font(lbl_temp, H1OS_FONT_20, 0);
    lv_obj_align(lbl_temp, LV_ALIGN_TOP_LEFT, 6, 32);

    /* Primary Dashboard Reading: Ambient Relative Humidity with Tint Icon */
    lv_obj_t *lbl_rh = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_rh, LV_SYMBOL_TINT " %.1f%%", (double)telem->ambient_rh_pct);
    lv_obj_set_style_text_font(lbl_rh, H1OS_FONT_20, 0);
    lv_obj_align(lbl_rh, LV_ALIGN_TOP_RIGHT, -6, 32);

    /* Secondary Metric: Ambient Celsius Reference */
    lv_obj_t *lbl_sub = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_sub, "(%.1f°C ambient)", (double)telem->ambient_temp_c);
    lv_obj_set_style_text_font(lbl_sub, H1OS_FONT_14, 0);
    lv_obj_align(lbl_sub, LV_ALIGN_TOP_LEFT, 6, 62);

    /* Horizontal Mid-Screen Hairline Divider */
    static lv_point_precise_t mid_pts[] = {{4, 88}, {196, 88}};
    lv_obj_t *mid_line = lv_line_create(scr);
    lv_line_set_points(mid_line, mid_pts, 2);
    lv_obj_set_style_line_width(mid_line, 1, 0);
    lv_obj_set_style_line_color(mid_line, lv_color_black(), 0);

    /* Row 1: Thermal Plateau Settling Status (Dual Column) */
    lv_obj_t *lbl_stat_k = lv_label_create(scr);
    lv_label_set_text(lbl_stat_k, "Status");
    lv_obj_set_style_text_font(lbl_stat_k, H1OS_FONT_14, 0);
    lv_obj_align(lbl_stat_k, LV_ALIGN_TOP_LEFT, 6, 100);

    lv_obj_t *lbl_stat_v = lv_label_create(scr);
    if (telem->is_thermally_settled) {
        lv_label_set_text_fmt(lbl_stat_v, "SETTLED (%u%%)", telem->trinode_confidence_pct);
    } else {
        lv_label_set_text_fmt(lbl_stat_v, LV_SYMBOL_REFRESH " %u%%", telem->trinode_confidence_pct);
    }
    lv_obj_set_style_text_font(lbl_stat_v, H1OS_FONT_14, 0);
    lv_obj_align(lbl_stat_v, LV_ALIGN_TOP_RIGHT, -6, 100);

    /* Row 2: Thermodynamic Water Vapor Pressure (Dual Column) */
    lv_obj_t *lbl_vp_k = lv_label_create(scr);
    lv_label_set_text(lbl_vp_k, "Vapor Pressure");
    lv_obj_set_style_text_font(lbl_vp_k, H1OS_FONT_14, 0);
    lv_obj_align(lbl_vp_k, LV_ALIGN_TOP_LEFT, 6, 126);

    lv_obj_t *lbl_vp_v = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_vp_v, "%.1f hPa", (double)telem->vapor_pressure_hpa);
    lv_obj_set_style_text_font(lbl_vp_v, H1OS_FONT_14, 0);
    lv_obj_align(lbl_vp_v, LV_ALIGN_TOP_RIGHT, -6, 126);

    /* Footer: Cycle Counter & POSIX Wall Clock */
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
