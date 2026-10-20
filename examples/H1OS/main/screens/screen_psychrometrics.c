/**
 * @file screen_psychrometrics.c
 * @brief Screen 2: Psychrometric engine and invariant metrics page
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "h1os/h1os_lvgl.h"
#include "h1os/h1os_time.h"
#include "h1os/orch_state.h"
#include "screens.h"

/**
 * @brief Renders Screen 2: Psychrometric engine and invariant metrics page.
 *
 * @param[in]    telem           Pointer to validated environmental telemetry snapshot.
 * @param[in]    event_cb        Keypad navigation callback.
 */
void screen_psychrometrics_render(const h1os_telemetry_t *telem, lv_event_cb_t event_cb)
{
    lv_obj_t *scr = screen_base_create("PSYCHROMETRICS", "2/4", event_cb);

    lv_obj_t *lbl_dew = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_dew, "Dew Point: %.1f°F (%.1f°C)", 
                                        telem->dew_point_f, 
                                        telem->dew_point_c);
    lv_obj_set_style_text_font(lbl_dew, H1OS_FONT_14, 0);
    lv_obj_align(lbl_dew, LV_ALIGN_TOP_LEFT, 6, 32);

    lv_obj_t *lbl_abs = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_abs, "Abs Humid:   %.1f g/m³", telem->absolute_humidity_g);
    lv_obj_set_style_text_font(lbl_abs, H1OS_FONT_14, 0);
    lv_obj_align(lbl_abs, LV_ALIGN_TOP_LEFT, 6, 80);

    lv_obj_t *lbl_glass = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_glass, "EPD Glass:   %.1f°C", telem->epd_glass_temp_c);
    lv_obj_set_style_text_font(lbl_glass, H1OS_FONT_14, 0);
    lv_obj_align(lbl_glass, LV_ALIGN_TOP_LEFT, 6, 108);

    lv_obj_t *lbl_floor = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_floor, "Win L/H:     %.1f/%.1f°C", 
                                        telem->window_low_c, 
                                        telem->window_high_c);
    lv_obj_set_style_text_font(lbl_floor, H1OS_FONT_14, 0);
    lv_obj_align(lbl_floor, LV_ALIGN_TOP_LEFT, 6, 134);

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

    lv_refr_now(NULL);
    h1os_lvgl_unlock();
}
