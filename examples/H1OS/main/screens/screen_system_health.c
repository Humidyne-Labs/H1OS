/**
 * @file screen_system_health.c
 * @brief Screen 3: System health, autonomy, and power page
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "battery_estimator.h"
#include "h1os/h1os_lvgl.h"
#include "h1os/h1os_time.h"
#include "h1os/sub_sdcard.h"
#include "screens.h"

/**
 * @brief Renders Screen 3: System health, autonomy, and power page.
 *
 * @param[in]    telem           Pointer to validated environmental telemetry snapshot.
 * @param[in]    event_cb        Keypad navigation callback.
 */
void screen_system_health_render(const h1os_telemetry_t *telem, lv_event_cb_t event_cb)
{
    h1os_lvgl_lock(100);
    lv_obj_t *scr = screen_base_create("SYSTEM HEALTH", "3/4", event_cb);

    lv_obj_t *lbl_bat = lv_label_create(scr);
    if (telem->is_usb_powered) {
        lv_label_set_text(lbl_bat, "Power:       USB CABLE");
    } else {
        lv_label_set_text_fmt(lbl_bat, "Battery:     %.2fV (%u%%)",
                                            (double)((float)telem->battery_mv / 1000.0f),
                                            telem->battery_percent);
    }
    lv_obj_set_style_text_font(lbl_bat, H1OS_FONT_14, 0);
    lv_obj_align(lbl_bat, LV_ALIGN_TOP_LEFT, 6, 30);

    lv_obj_t *lbl_autonomy = lv_label_create(scr);
    if (telem->is_usb_powered) {
        lv_label_set_text(lbl_autonomy, "Autonomy:    CHARGING");
    } else {
        float sched_ma = battery_estimate_schedule_current_ma(telem->flow_a_period_sec, telem->flow_b_period_sec);
        float avg_ma   = sched_ma;
        uint32_t elapsed_sec = telem->sample_count * ((telem->flow_a_period_sec > 0) ? telem->flow_a_period_sec : 60);
        if (elapsed_sec >= 3600 && telem->boot_vbat_mv > (telem->battery_mv + 15)) {
            float emp_ma = battery_estimate_avg_current_ma(500, telem->boot_vbat_mv, telem->battery_mv, elapsed_sec);
            if (emp_ma > 0.02f && emp_ma < 50.0f) {
                avg_ma = (0.60f * emp_ma) + (0.40f * sched_ma);
            }
        }
        float days = battery_estimate_remaining_days(500, telem->battery_mv, avg_ma);
        lv_label_set_text_fmt(lbl_autonomy, "Autonomy:    ~%.0f Days", (double)days);
    }
    lv_obj_set_style_text_font(lbl_autonomy, H1OS_FONT_14, 0);
    lv_obj_align(lbl_autonomy, LV_ALIGN_TOP_LEFT, 6, 52);

    lv_obj_t *lbl_sd = lv_label_create(scr);
    uint32_t sd_mb = 0;
    if (sub_sdcard_is_mounted() && sub_sdcard_get_capacity_mb(&sd_mb) == ESP_OK) {
        lv_label_set_text_fmt(lbl_sd, "MicroSD:     %.1f GB OK", (double)((float)sd_mb / 1024.0f));
    } else {
        lv_label_set_text(lbl_sd, "MicroSD:     NO CARD");
    }
    lv_obj_set_style_text_font(lbl_sd, H1OS_FONT_14, 0);
    lv_obj_align(lbl_sd, LV_ALIGN_TOP_LEFT, 6, 80);

    lv_obj_t *lbl_nvs = lv_label_create(scr);
    lv_label_set_text(lbl_nvs, "Flash NVS:   SLAT ACTIVE");
    lv_obj_set_style_text_font(lbl_nvs, H1OS_FONT_14, 0);
    lv_obj_align(lbl_nvs, LV_ALIGN_TOP_LEFT, 6, 102);

    lv_obj_t *lbl_mcu = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_mcu, "MCU Die:     %.1f°C", (double)telem->mcu_die_temp_c);
    lv_obj_set_style_text_font(lbl_mcu, H1OS_FONT_14, 0);
    lv_obj_align(lbl_mcu, LV_ALIGN_TOP_LEFT, 6, 130);

    lv_obj_t *lbl_delta = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_delta, "TriNode ΔT:  %+.1f°C (%u%%)",
                                        (double)telem->trinode_delta_c,
                                        telem->trinode_confidence_pct);
    lv_obj_set_style_text_font(lbl_delta, H1OS_FONT_14, 0);
    lv_obj_align(lbl_delta, LV_ALIGN_TOP_LEFT, 6, 150);

    char date_str[16] = "2026-10-20";
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
