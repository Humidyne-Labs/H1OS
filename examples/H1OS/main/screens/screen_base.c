/**
 * @file screen_base.c
 * @brief Common base layout builder for 200x200 monochrome e-Paper screens
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "h1os/h1os_lvgl.h"
#include "screens.h"

static lv_obj_t *s_active_badge     = NULL;
static lv_obj_t *s_active_badge_lbl = NULL;

static bool s_badge_is_awake = false;

lv_obj_t *screen_base_create(const char *title, const char *page_str, lv_event_cb_t event_cb)
{
    lv_obj_t *scr = lv_screen_active();
    lv_obj_clean(scr);
    lv_obj_set_style_bg_color(scr, lv_color_white(), 0);

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

    lv_obj_t *lbl_title = lv_label_create(scr);
    lv_label_set_text(lbl_title, title);
    lv_obj_set_style_text_font(lbl_title, H1OS_FONT_14, 0);
    lv_obj_align(lbl_title, LV_ALIGN_TOP_LEFT, 6, 4);

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

    s_active_badge     = badge;
    s_active_badge_lbl = lbl_pg;
    s_badge_is_awake   = is_awake;

    static lv_point_precise_t line_pts[] = {{4, 22}, {196, 22}};
    lv_obj_t *line = lv_line_create(scr);
    lv_line_set_points(line, line_pts, 2);
    lv_obj_set_style_line_width(line, 1, 0);
    lv_obj_set_style_line_color(line, lv_color_black(), 0);

    return scr;
}

/**
 * @brief Sets awake session pill badge in top-right header.
 *
 * @param[in]    is_awake        True if interactive session active, false for unattended sleep.
 */
void screen_base_set_awake_badge(bool is_awake)
{
    if (s_active_badge == NULL || s_active_badge_lbl == NULL)
        return;

    if (s_badge_is_awake == is_awake)
        return;

    if (h1os_lvgl_lock(100)) {
        if (lv_obj_is_valid(s_active_badge) && lv_obj_is_valid(s_active_badge_lbl)) {
            lv_obj_set_style_bg_color(s_active_badge, is_awake ? lv_color_black() : lv_color_white(), 0);
            lv_obj_set_style_text_color(s_active_badge_lbl, is_awake ? lv_color_white() : lv_color_black(), 0);
            lv_obj_invalidate(s_active_badge);
            s_badge_is_awake = is_awake;
        }
        h1os_lvgl_unlock();
    }
}
