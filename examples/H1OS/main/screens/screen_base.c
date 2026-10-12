/**
 * @file screen_base.c
 * @brief Common base layout builder for 200x200 monochrome e-Paper screens.
 *
 * SPDX-License-Identifier: MIT
 */

#include "screens.h"
#include "h1os/h1os_lvgl.h"

lv_obj_t* screen_base_create(const char *title, const char *page_str, lv_event_cb_t event_cb)
{
    h1os_lvgl_lock(100);
    lv_obj_t *scr = lv_screen_active();
    lv_obj_clean(scr);
    lv_obj_set_style_bg_color(scr, lv_color_white(), 0);

    // Bind hardware keypad listener to active screen cleanly
    lv_group_t *def_grp = lv_group_get_default();
    if (def_grp == NULL) {
        def_grp = lv_group_create();
        lv_group_set_default(def_grp);
        lv_indev_t *indev = h1os_lvgl_get_indev();
        if (indev != NULL) {
            lv_indev_set_group(indev, def_grp);
        }
    }
    if (event_cb != NULL) {
        lv_obj_remove_event_cb(scr, event_cb);
        lv_obj_add_event_cb(scr, event_cb, LV_EVENT_ALL, NULL);
    }
    lv_group_remove_obj(scr);
    lv_group_add_obj(def_grp, scr);
    lv_group_focus_obj(scr);
    lv_obj_set_clickable(scr, true);

    // 1. Header Title: Left-aligned at (X: 6, Y: 4)
    lv_obj_t *lbl_title = lv_label_create(scr);
    lv_label_set_text(lbl_title, title);
    lv_obj_set_style_text_font(lbl_title, H1OS_FONT_14, 0);
    lv_obj_align(lbl_title, LV_ALIGN_TOP_LEFT, 6, 4);

    // 2. Invertible Sleep/Wake Status Badge (Page Indicator at Top-Right)
    //    - Active interactive session (AWAKE): Inverted badge (Black background, White text)
    //    - Sleeping / Unattended wake (SLEEP): Standard badge (White background, Black text)
    bool is_awake = h1os_is_session_active();
    lv_obj_t *badge = lv_obj_create(scr);
    lv_obj_remove_style_all(badge);
    lv_obj_set_size(badge, 36, 17);
    lv_obj_align(badge, LV_ALIGN_TOP_RIGHT, -4, 2);
    lv_obj_set_style_bg_opa(badge, LV_OPA_COVER, 0);
    lv_obj_set_style_bg_color(badge, is_awake ? lv_color_black() : lv_color_white(), 0);
    lv_obj_set_style_border_width(badge, 1, 0);
    lv_obj_set_style_border_color(badge, lv_color_black(), 0);

    lv_obj_t *lbl_pg = lv_label_create(badge);
    lv_label_set_text(lbl_pg, page_str);
    lv_obj_set_style_text_font(lbl_pg, H1OS_FONT_14, 0);
    lv_obj_set_style_text_color(lbl_pg, is_awake ? lv_color_white() : lv_color_black(), 0);
    lv_obj_center(lbl_pg);

    // Divider Line (Y = 22, X: 4 to 196)
    static lv_point_precise_t line_pts[] = {{4, 22}, {196, 22}};
    lv_obj_t *line = lv_line_create(scr);
    lv_line_set_points(line, line_pts, 2);
    lv_obj_set_style_line_width(line, 1, 0);
    lv_obj_set_style_line_color(line, lv_color_black(), 0);

    return scr;
}
