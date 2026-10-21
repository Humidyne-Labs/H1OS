/**
 * @file main.c
 * @brief H1OS turnkey starter application boilerplate
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "esp_log.h"
#include "h1os/h1os.h"
#include "h1os/h1os_lvgl.h"
#include "h1os/h1os_version.h"
#include "lvgl.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

static const char *TAG = "boilerplate_app";

typedef struct {
    uint32_t boot_epoch_sec;
    uint32_t cycle_counter;
} app_state_t;

RTC_DATA_ATTR static app_state_t s_app_state = {0};

/**
 * @brief Start render_starter_screen background operations.
 *
 * @param[in]    telem           Parameter telem.
 *
 * @return Return value of type static void.
 */
static void render_starter_screen(const h1os_telemetry_t *telem)
{
    h1os_lvgl_lock(100);
    lv_obj_t *scr = lv_screen_active();
    lv_obj_clean(scr);
    lv_obj_set_style_bg_color(scr, lv_color_white(), 0);

    lv_obj_t *header = lv_label_create(scr);
    lv_label_set_text(header, "H1OS STARTER");
    lv_obj_set_style_text_font(header, H1OS_FONT_14, 0);
    lv_obj_align(header, LV_ALIGN_TOP_LEFT, 6, 4);

    lv_obj_t *lbl_cycle = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_cycle, "#%lu", (unsigned long)s_app_state.cycle_counter);
    lv_obj_set_style_text_font(lbl_cycle, H1OS_FONT_14, 0);
    lv_obj_align(lbl_cycle, LV_ALIGN_TOP_RIGHT, -6, 4);

    static lv_point_precise_t div_pts[] = {{4, 22}, {196, 22}};
    lv_obj_t *div = lv_line_create(scr);
    lv_line_set_points(div, div_pts, 2);
    lv_obj_set_style_line_width(div, 1, 0);
    lv_obj_set_style_line_color(div, lv_color_black(), 0);

    lv_obj_t *lbl_temp = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_temp, "%.1f°F", (double)telem->ambient_temp_f);
    lv_obj_set_style_text_font(lbl_temp, H1OS_FONT_20, 0);
    lv_obj_align(lbl_temp, LV_ALIGN_TOP_LEFT, 6, 32);

    lv_obj_t *lbl_rh = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_rh, "%.1f%%", (double)telem->ambient_rh_pct);
    lv_obj_set_style_text_font(lbl_rh, H1OS_FONT_20, 0);
    lv_obj_align(lbl_rh, LV_ALIGN_TOP_RIGHT, -6, 32);

    lv_obj_t *lbl_metric = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_metric, "(%.1f°C ambient)", (double)telem->ambient_temp_c);
    lv_obj_set_style_text_font(lbl_metric, H1OS_FONT_14, 0);
    lv_obj_align(lbl_metric, LV_ALIGN_TOP_LEFT, 6, 58);

    lv_obj_t *lbl_dew = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_dew, "Dew Point:  %.1f°F", (double)telem->dew_point_f);
    lv_obj_set_style_text_font(lbl_dew, H1OS_FONT_14, 0);
    lv_obj_align(lbl_dew, LV_ALIGN_TOP_LEFT, 6, 84);

    lv_obj_t *lbl_pwr = lv_label_create(scr);
    if (telem->is_usb_powered) {
        lv_label_set_text(lbl_pwr, "Power:      USB CABLE");
    } else {
        lv_label_set_text_fmt(lbl_pwr, "Battery:    %.2fV (%u%%)", (double)((float)telem->battery_mv / 1000.0f),
                              telem->battery_percent);
    }
    lv_obj_set_style_text_font(lbl_pwr, H1OS_FONT_14, 0);
    lv_obj_align(lbl_pwr, LV_ALIGN_TOP_LEFT, 6, 108);

    lv_obj_t *lbl_status = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_status, "Status:     %s", telem->is_thermally_settled ? "SETTLED" : "SETTLING");
    lv_obj_set_style_text_font(lbl_status, H1OS_FONT_14, 0);
    lv_obj_align(lbl_status, LV_ALIGN_TOP_LEFT, 6, 132);

    lv_obj_t *lbl_foot = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_foot, "%s v%" PRIu32 ".%" PRIu32 " READY", H1OS_NAME, h1os_version_get_major(),
                          h1os_version_get_minor());
    lv_obj_set_style_text_font(lbl_foot, H1OS_FONT_14, 0);
    lv_obj_align(lbl_foot, LV_ALIGN_BOTTOM_LEFT, 6, -6);

    h1os_lvgl_unlock();
}

/**
 * @brief Update display.
 *
 * @return Return value of type static void.
 */
static void update_display(void)
{
    h1os_telemetry_t telem = {0};
    h1os_get_telemetry(&telem);
    render_starter_screen(&telem);
}

/**
 * @brief App on boot.
 *
 * @param[in]    user_data       Parameter user_data.
 *
 * @return Return value of type static void.
 */
static void app_on_boot(void *user_data)
{
    (void)user_data;
    ESP_LOGI(TAG, "Application booted cleanly (H1OS %s, built %s %s, code 0x%08" PRIx32 ")", h1os_version_get_string(),
             h1os_version_get_build_date(), h1os_version_get_build_time(), h1os_version_get_code());
    s_app_state.cycle_counter = 1;
    s_app_state.boot_epoch_sec = (uint32_t)time(NULL);
    update_display();
}

/**
 * @brief App on wake.
 *
 * @param[in]    ctx             Parameter ctx.
 * @param[in]    user_data       Parameter user_data.
 *
 * @return Return value of type static void.
 */
static void app_on_wake(const h1os_wake_context_t *ctx, void *user_data)
{
    (void)ctx;
    (void)user_data;
    s_app_state.cycle_counter++;
    ESP_LOGI(TAG, "Application resumed from sleep (Cycle #%lu)", (unsigned long)s_app_state.cycle_counter);
    update_display();
}

/**
 * @brief App on pre sleep.
 *
 * @param[in]    sleep_sec       Parameter sleep_sec.
 * @param[in]    user_data       Parameter user_data.
 *
 * @return Return value of type static void.
 */
static void app_on_pre_sleep(uint32_t sleep_sec, void *user_data)
{
    (void)user_data;
    ESP_LOGI(TAG, "System entering deep sleep for %lu seconds", (unsigned long)sleep_sec);
}

/**
 * @brief App on shutdown.
 *
 * @param[in]    user_data       Parameter user_data.
 *
 * @return Return value of type static void.
 */
static void app_on_shutdown(void *user_data)
{
    (void)user_data;
    ESP_LOGI(TAG, "System shutting down");
}

/**
 * @brief Application entry point.
 */
void app_main(void)
{
    ESP_LOGI(TAG, "Starting H1OS Application Boilerplate");

    h1os_lifecycle_t lifecycle = {
        .on_boot = app_on_boot,
        .on_wake = app_on_wake,
        .on_pre_sleep = app_on_pre_sleep,
        .on_shutdown = app_on_shutdown,
        .presentation =
            {
                .on_splash = NULL,
                .on_chime = NULL,
                .chime_mask = 0,
                .volume_pct = 50,
            },
        .session =
            {
                .inactivity_timeout_sec = 30,
                .clk_mode = SYS_CLK_MODE_DYNAMIC,
                .flow_a_period_sec = 60,
                .flow_b_period_sec = 300,
            },
        .user_data = NULL,
    };

    esp_err_t ret = h1os_start(&lifecycle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to start H1OS: %s", esp_err_to_name(ret));
    }
}
