/**
 * @file screen_system_health.c
 * @brief Screen 4: System power, autonomy, and storage health page
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "h1os/h1os_lvgl.h"
#include "h1os/h1os_time.h"
#include "h1os/sub_power.h"
#include "h1os/sub_sdcard.h"
#include "screens.h"

static const char *get_battery_icon(uint8_t pct)
{
    if (pct >= 80) return LV_SYMBOL_BATTERY_FULL;
    if (pct >= 55) return LV_SYMBOL_BATTERY_3;
    if (pct >= 30) return LV_SYMBOL_BATTERY_2;
    if (pct >= 10) return LV_SYMBOL_BATTERY_1;
    return LV_SYMBOL_BATTERY_EMPTY;
}

/**
 * @brief Renders Screen 4: System health, autonomy, and power page.
 *
 * @param[in]    telem           Pointer to validated environmental telemetry snapshot.
 * @param[in]    event_cb        Keypad navigation callback.
 */
void screen_system_health_render(const h1os_telemetry_t *telem, lv_event_cb_t event_cb)
{
    h1os_lvgl_lock(100);
    lv_obj_t *scr = screen_base_create("SYSTEM HEALTH", "4/5", event_cb);

    /* Row 1: Battery Rail Voltage & State of Charge */
    lv_obj_t *lbl_k1 = lv_label_create(scr);
    lv_label_set_text(lbl_k1, "Battery");
    lv_obj_set_style_text_font(lbl_k1, H1OS_FONT_14, 0);
    lv_obj_align(lbl_k1, LV_ALIGN_TOP_LEFT, 6, 32);

    lv_obj_t *lbl_v1 = lv_label_create(scr);
    const char *bat_sym = get_battery_icon(telem->battery_percent);
    lv_label_set_text_fmt(lbl_v1, "%s %.2fV (%u%%)",
                          bat_sym,
                          (double)((float)telem->battery_mv / 1000.0f),
                          telem->battery_percent);
    lv_obj_set_style_text_font(lbl_v1, H1OS_FONT_14, 0);
    lv_obj_align(lbl_v1, LV_ALIGN_TOP_RIGHT, -6, 32);

    /* Row 2: Active Power Source / Charger Telemetry */
    lv_obj_t *lbl_k2 = lv_label_create(scr);
    lv_label_set_text(lbl_k2, "Source");
    lv_obj_set_style_text_font(lbl_k2, H1OS_FONT_14, 0);
    lv_obj_align(lbl_k2, LV_ALIGN_TOP_LEFT, 6, 56);

    lv_obj_t *lbl_v2 = lv_label_create(scr);
    if (telem->battery_state == H1OS_BATTERY_CHARGED) {
        lv_label_set_text(lbl_v2, LV_SYMBOL_USB " EXT USB");
    } else if (telem->battery_state == H1OS_BATTERY_CHARGING) {
        lv_label_set_text(lbl_v2, LV_SYMBOL_CHARGE " CHARGE");
    } else {
        lv_label_set_text(lbl_v2, "BATTERY");
    }
    lv_obj_set_style_text_font(lbl_v2, H1OS_FONT_14, 0);
    lv_obj_align(lbl_v2, LV_ALIGN_TOP_RIGHT, -6, 56);

    /* Row 3: Operational Autonomy Projection */
    lv_obj_t *lbl_k3 = lv_label_create(scr);
    lv_label_set_text(lbl_k3, "Autonomy");
    lv_obj_set_style_text_font(lbl_k3, H1OS_FONT_14, 0);
    lv_obj_align(lbl_k3, LV_ALIGN_TOP_LEFT, 6, 80);

    lv_obj_t *lbl_v3 = lv_label_create(scr);
    if (telem->battery_state == H1OS_BATTERY_CHARGED) {
        lv_label_set_text(lbl_v3, "EXT USB");
    } else if (telem->battery_state == H1OS_BATTERY_CHARGING) {
        lv_label_set_text(lbl_v3, "CHARGE");
    } else if (telem->autonomy.autonomy_days < 0.0f) {
        lv_label_set_text(lbl_v3, "CALIBRATE");
    } else {
        lv_label_set_text_fmt(lbl_v3, "~%.0f Days", (double)telem->autonomy.autonomy_days);
    }
    lv_obj_set_style_text_font(lbl_v3, H1OS_FONT_14, 0);
    lv_obj_align(lbl_v3, LV_ALIGN_TOP_RIGHT, -6, 80);

    /* Row 4: Removable MicroSD Card Storage */
    lv_obj_t *lbl_k4 = lv_label_create(scr);
    lv_label_set_text(lbl_k4, "MicroSD");
    lv_obj_set_style_text_font(lbl_k4, H1OS_FONT_14, 0);
    lv_obj_align(lbl_k4, LV_ALIGN_TOP_LEFT, 6, 104);

    lv_obj_t *lbl_v4 = lv_label_create(scr);
    uint32_t sd_mb = 0;
    if (sub_sdcard_is_mounted() && sub_sdcard_get_capacity_mb(&sd_mb) == ESP_OK) {
        lv_label_set_text_fmt(lbl_v4, "%.1f GB OK", (double)((float)sd_mb / 1024.0f));
    } else {
        lv_label_set_text(lbl_v4, "NO CARD");
    }
    lv_obj_set_style_text_font(lbl_v4, H1OS_FONT_14, 0);
    lv_obj_align(lbl_v4, LV_ALIGN_TOP_RIGHT, -6, 104);

    /* Row 5: On-Board SPI Flash NVS Storage */
    lv_obj_t *lbl_k5 = lv_label_create(scr);
    lv_label_set_text(lbl_k5, "Flash NVS");
    lv_obj_set_style_text_font(lbl_k5, H1OS_FONT_14, 0);
    lv_obj_align(lbl_k5, LV_ALIGN_TOP_LEFT, 6, 128);

    lv_obj_t *lbl_v5 = lv_label_create(scr);
    lv_label_set_text(lbl_v5, "ACTIVE");
    lv_obj_set_style_text_font(lbl_v5, H1OS_FONT_14, 0);
    lv_obj_align(lbl_v5, LV_ALIGN_TOP_RIGHT, -6, 128);

    /* Footer: Calendar Date & Posix Wall Clock */
    char date_str[16] = "2026-10-25";
    char time_str[16] = "--:--";
    h1os_time_get_date_formatted(H1OS_DATE_FMT_MM_DD_YY, date_str, sizeof(date_str));
    h1os_time_get_formatted(H1OS_TIME_FMT_12H_MIN, time_str, sizeof(time_str));

    lv_obj_t *lbl_foot_l = lv_label_create(scr);
    lv_label_set_text(lbl_foot_l, date_str);
    lv_obj_set_style_text_font(lbl_foot_l, H1OS_FONT_14, 0);
    lv_obj_align(lbl_foot_l, LV_ALIGN_BOTTOM_LEFT, 6, -6);

    lv_obj_t *lbl_foot_r = lv_label_create(scr);
    lv_label_set_text(lbl_foot_r, time_str);
    lv_obj_set_style_text_font(lbl_foot_r, H1OS_FONT_14, 0);
    lv_obj_align(lbl_foot_r, LV_ALIGN_BOTTOM_RIGHT, -6, -6);

    h1os_lvgl_unlock();
}
