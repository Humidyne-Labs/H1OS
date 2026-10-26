/**
 * @file screen_thermal_nodes.c
 * @brief Screen 3: TriNode sensor cross-correlation and thermal settling page
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "h1os/h1os_lvgl.h"
#include "h1os/h1os_time.h"
#include "screens.h"

/**
 * @brief Renders Screen 3: TriNode sensor cross-correlation and delta page.
 *
 * @param[in]    telem           Pointer to validated environmental telemetry snapshot.
 * @param[in]    event_cb        Keypad navigation callback.
 */
void screen_thermal_nodes_render(const h1os_telemetry_t *telem, lv_event_cb_t event_cb)
{
    h1os_lvgl_lock(100);
    lv_obj_t *scr = screen_base_create("THERMAL NODES", "3/5", event_cb);

    /* Row 1: SHTC3 Ambient Sensor */
    lv_obj_t *lbl_k1 = lv_label_create(scr);
    lv_label_set_text(lbl_k1, "SHTC3 Ambient");
    lv_obj_set_style_text_font(lbl_k1, H1OS_FONT_14, 0);
    lv_obj_align(lbl_k1, LV_ALIGN_TOP_LEFT, 6, 32);

    lv_obj_t *lbl_v1 = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_v1, "%.1f°C", (double)telem->ambient_temp_c);
    lv_obj_set_style_text_font(lbl_v1, H1OS_FONT_14, 0);
    lv_obj_align(lbl_v1, LV_ALIGN_TOP_RIGHT, -6, 32);

    /* Row 2: SSD1681 EPD On-Glass Thermistor */
    lv_obj_t *lbl_k2 = lv_label_create(scr);
    lv_label_set_text(lbl_k2, "EPD Glass");
    lv_obj_set_style_text_font(lbl_k2, H1OS_FONT_14, 0);
    lv_obj_align(lbl_k2, LV_ALIGN_TOP_LEFT, 6, 56);

    lv_obj_t *lbl_v2 = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_v2, "%.1f°C", (double)telem->epd_glass_temp_c);
    lv_obj_set_style_text_font(lbl_v2, H1OS_FONT_14, 0);
    lv_obj_align(lbl_v2, LV_ALIGN_TOP_RIGHT, -6, 56);

    /* Row 3: ESP32-S3 Internal MCU Silicon TSENS */
    lv_obj_t *lbl_k3 = lv_label_create(scr);
    lv_label_set_text(lbl_k3, "MCU Silicon");
    lv_obj_set_style_text_font(lbl_k3, H1OS_FONT_14, 0);
    lv_obj_align(lbl_k3, LV_ALIGN_TOP_LEFT, 6, 80);

    lv_obj_t *lbl_v3 = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_v3, "%.1f°C", (double)telem->mcu_die_temp_c);
    lv_obj_set_style_text_font(lbl_v3, H1OS_FONT_14, 0);
    lv_obj_align(lbl_v3, LV_ALIGN_TOP_RIGHT, -6, 80);

    /* Row 4: TriNode Inter-Node Delta T */
    lv_obj_t *lbl_k4 = lv_label_create(scr);
    lv_label_set_text(lbl_k4, "TriNode ΔT");
    lv_obj_set_style_text_font(lbl_k4, H1OS_FONT_14, 0);
    lv_obj_align(lbl_k4, LV_ALIGN_TOP_LEFT, 6, 104);

    lv_obj_t *lbl_v4 = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_v4, "%+.1f°C", (double)telem->trinode_delta_c);
    lv_obj_set_style_text_font(lbl_v4, H1OS_FONT_14, 0);
    lv_obj_align(lbl_v4, LV_ALIGN_TOP_RIGHT, -6, 104);

    /* Row 5: Thermal Settling Equilibrium */
    lv_obj_t *lbl_k5 = lv_label_create(scr);
    lv_label_set_text(lbl_k5, "Stability");
    lv_obj_set_style_text_font(lbl_k5, H1OS_FONT_14, 0);
    lv_obj_align(lbl_k5, LV_ALIGN_TOP_LEFT, 6, 128);

    lv_obj_t *lbl_v5 = lv_label_create(scr);
    if (telem->is_thermally_settled) {
        lv_label_set_text_fmt(lbl_v5, "SETTLED (%u%%)", telem->trinode_confidence_pct);
    } else {
        lv_label_set_text_fmt(lbl_v5, LV_SYMBOL_REFRESH " %u%%", telem->trinode_confidence_pct);
    }
    lv_obj_set_style_text_font(lbl_v5, H1OS_FONT_14, 0);
    lv_obj_align(lbl_v5, LV_ALIGN_TOP_RIGHT, -6, 128);

    /* Footer: 3-Node Architecture Tag & Time */
    char time_str[16] = "--:--";
    h1os_time_get_formatted(H1OS_TIME_FMT_12H_MIN, time_str, sizeof(time_str));

    lv_obj_t *lbl_foot_l = lv_label_create(scr);
    lv_label_set_text(lbl_foot_l, "3-Node Mesh");
    lv_obj_set_style_text_font(lbl_foot_l, H1OS_FONT_14, 0);
    lv_obj_align(lbl_foot_l, LV_ALIGN_BOTTOM_LEFT, 6, -6);

    lv_obj_t *lbl_foot_r = lv_label_create(scr);
    lv_label_set_text(lbl_foot_r, time_str);
    lv_obj_set_style_text_font(lbl_foot_r, H1OS_FONT_14, 0);
    lv_obj_align(lbl_foot_r, LV_ALIGN_BOTTOM_RIGHT, -6, -6);

    h1os_lvgl_unlock();
}
