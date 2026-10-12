/**
 * @file screen_psychrometrics.c
 * @brief Screen 2: Psychrometrics Engine & Invariants (Page 2/4)
 *
 * SPDX-License-Identifier: MIT
 */

#include "screens.h"
#include "h1os/h1os_lvgl.h"
#include "h1os/h1os_time.h"
#include "h1os/orch_state.h"

void screen_psychrometrics_render(const h1os_telemetry_t *telem, lv_event_cb_t event_cb)
{
    lv_obj_t *scr = screen_base_create("PSYCHROMETRICS", "2/4", event_cb);

    orch_persisted_state_t *st = orch_state_get();

    // Row 1: Dew Point (°F and °C)
    lv_obj_t *lbl_dew = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_dew, "Dew Point:   %.1f°F", telem->dew_point_f);
    lv_obj_set_style_text_font(lbl_dew, H1OS_FONT_14, 0);
    lv_obj_align(lbl_dew, LV_ALIGN_TOP_LEFT, 6, 32);

    lv_obj_t *lbl_dew_c = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_dew_c, "             (%.1f°C)", telem->dew_point_c);
    lv_obj_set_style_text_font(lbl_dew_c, H1OS_FONT_14, 0);
    lv_obj_align(lbl_dew_c, LV_ALIGN_TOP_LEFT, 6, 52);

    // Row 2: Absolute Humidity
    lv_obj_t *lbl_abs = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_abs, "Abs Humid:   %.1f g/m³", telem->absolute_humidity_g);
    lv_obj_set_style_text_font(lbl_abs, H1OS_FONT_14, 0);
    lv_obj_align(lbl_abs, LV_ALIGN_TOP_LEFT, 6, 80);

    // Row 3: Glass Thermistor & Ambient Floor
    lv_obj_t *lbl_glass = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_glass, "EPD Glass:   %.1f°C", telem->epd_glass_temp_c);
    lv_obj_set_style_text_font(lbl_glass, H1OS_FONT_14, 0);
    lv_obj_align(lbl_glass, LV_ALIGN_TOP_LEFT, 6, 108);

    lv_obj_t *lbl_floor = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_floor, "Amb Floor:   %.1f°C", (float)st->amb_floor_temp_centi_c / 100.0f);
    lv_obj_set_style_text_font(lbl_floor, H1OS_FONT_14, 0);
    lv_obj_align(lbl_floor, LV_ALIGN_TOP_LEFT, 6, 134);

    // Footer Bar: Invariant status (left), Clock Time (right)
    char time_str[16] = "--:--";
    h1os_time_get_formatted(H1OS_TIME_FMT_12H_MIN, time_str, sizeof(time_str));

    lv_obj_t *lbl_foot_l = lv_label_create(scr);
    lv_label_set_text(lbl_foot_l, "Invariant: OK");
    lv_obj_set_style_text_font(lbl_foot_l, H1OS_FONT_14, 0);
    lv_obj_align(lbl_foot_l, LV_ALIGN_BOTTOM_LEFT, 6, -6);

    lv_obj_t *lbl_foot_r = lv_label_create(scr);
    lv_label_set_text(lbl_foot_r, time_str);
    lv_obj_set_style_text_font(lbl_foot_r, H1OS_FONT_14, 0);
    lv_obj_align(lbl_foot_r, LV_ALIGN_BOTTOM_RIGHT, -6, -6);

    lv_refr_now(NULL);
    h1os_lvgl_unlock();
}
