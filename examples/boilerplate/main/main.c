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
 * @brief Render starter presentation screen on SSD1681 e-Paper panel.
 *
 * @param[in] telem Pointer to latest telemetry snapshot.
 */
static void render_starter_screen(const h1os_telemetry_t *telem)
{
    lv_obj_t *scr = lv_screen_active();
    lv_obj_clean(scr);
    lv_obj_set_style_bg_color(scr, lv_color_white(), 0);

    /* Header Bar: Project title and monotonic cycle counter */
    lv_obj_t *header = lv_label_create(scr);
    lv_label_set_text(header, "H1OS STARTER");
    lv_obj_set_style_text_font(header, HUMID1_FONT_UI_BODY, 0);
    lv_obj_align(header, LV_ALIGN_TOP_LEFT, 6, 4);

    lv_obj_t *lbl_cycle = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_cycle, "#%lu", (unsigned long)s_app_state.cycle_counter);
    lv_obj_set_style_text_font(lbl_cycle, HUMID1_FONT_UI_BODY, 0);
    lv_obj_align(lbl_cycle, LV_ALIGN_TOP_RIGHT, -6, 4);

    /* 1-Pixel Bilevel Header Separator (Y = 22) */
    static lv_point_precise_t div_pts[] = {{4, 22}, {196, 22}};
    lv_obj_t *div = lv_line_create(scr);
    lv_line_set_points(div, div_pts, 2);
    lv_obj_set_style_line_width(div, 1, 0);
    lv_obj_set_style_line_color(div, lv_color_black(), 0);

    /* Primary Thermodynamic Telemetry (Fahrenheit and Relative Humidity) */
    lv_obj_t *lbl_temp = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_temp, "%.1f°F", (double)telem->ambient_temp_f);
    lv_obj_set_style_text_font(lbl_temp, HUMID1_FONT_UI_HEADER, 0);
    lv_obj_align(lbl_temp, LV_ALIGN_TOP_LEFT, 6, 32);

    lv_obj_t *lbl_rh = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_rh, "%.1f%%", (double)telem->ambient_rh_pct);
    lv_obj_set_style_text_font(lbl_rh, HUMID1_FONT_UI_HEADER, 0);
    lv_obj_align(lbl_rh, LV_ALIGN_TOP_RIGHT, -6, 32);

    /* Celsius Secondary Metric */
    lv_obj_t *lbl_metric = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_metric, "(%.1f°C ambient)", (double)telem->ambient_temp_c);
    lv_obj_set_style_text_font(lbl_metric, HUMID1_FONT_UI_BODY, 0);
    lv_obj_align(lbl_metric, LV_ALIGN_TOP_LEFT, 6, 58);

    /* August-Roche-Magnus Dew Point Invariant */
    lv_obj_t *lbl_dew = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_dew, "Dew Point:  %.1f°F", (double)telem->dew_point_f);
    lv_obj_set_style_text_font(lbl_dew, HUMID1_FONT_UI_BODY, 0);
    lv_obj_align(lbl_dew, LV_ALIGN_TOP_LEFT, 6, 84);

    /* Power Topology: VBUS Detection vs. LiPo State of Charge */
    lv_obj_t *lbl_pwr = lv_label_create(scr);
    if (telem->is_usb_powered) {
        lv_label_set_text(lbl_pwr, "Power:      USB CABLE");
    } else {
        lv_label_set_text_fmt(lbl_pwr, "Battery:    %.2fV (%u%%)", (double)((float)telem->battery_mv / 1000.0f),
                              telem->battery_percent);
    }
    lv_obj_set_style_text_font(lbl_pwr, HUMID1_FONT_UI_BODY, 0);
    lv_obj_align(lbl_pwr, LV_ALIGN_TOP_LEFT, 6, 108);

    /* Sensor Thermal Equilibrium Status */
    lv_obj_t *lbl_status = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_status, "Status:     %s", telem->is_thermally_settled ? "SETTLED" : "SETTLING");
    lv_obj_set_style_text_font(lbl_status, HUMID1_FONT_UI_BODY, 0);
    lv_obj_align(lbl_status, LV_ALIGN_TOP_LEFT, 6, 132);

    /* Footer: Firmware Version Identification */
    lv_obj_t *lbl_foot = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_foot, "%s v%" PRIu32 ".%" PRIu32 " READY", H1OS_NAME, h1os_version_get_major(),
                          h1os_version_get_minor());
    lv_obj_set_style_text_font(lbl_foot, HUMID1_FONT_UI_BODY, 0);
    lv_obj_align(lbl_foot, LV_ALIGN_BOTTOM_LEFT, 6, -6);
}

/**
 * @brief Fetch latest platform telemetry and update presentation layout.
 */
static void update_display(void)
{
    h1os_telemetry_t telem = {0};
    h1os_get_telemetry(&telem);
    render_starter_screen(&telem);
}

/**
 * @brief Cross-Core UI Mutation Actor Callback (Core 0 -> Core 1).
 *
 * @param[in] arg Optional user argument.
 */
static void ui_update_actor(void *arg)
{
    (void)arg;
    update_display();
}

/**
 * @brief Post an asynchronous display refresh request to Core 1 LVGL actor queue.
 */
void app_request_display_update(void)
{
    esp_err_t err = h1os_ui_post(ui_update_actor, NULL, 100);
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "Failed to enqueue UI update: %s", esp_err_to_name(err));
    }
}

/**
 * @brief Application cold boot hook.
 *
 * Invoked on Core 0 before Core 1 LVGL task startup.
 *
 * @param[in] user_data Opaque user data configured in h1os_lifecycle_t.
 */
static void app_on_boot(void *user_data)
{
    (void)user_data;
    ESP_LOGI(TAG, "Application booted cleanly (H1OS %s, built %s %s, code 0x%08" PRIx32 ")",
             h1os_version_get_string(), h1os_version_get_build_date(), h1os_version_get_build_time(),
             h1os_version_get_code());
    s_app_state.cycle_counter = 1;
    s_app_state.boot_epoch_sec = (uint32_t)time(NULL);
    update_display();
}

/**
 * @brief Application sleep wake hook.
 *
 * Invoked on Core 0 before Core 1 LVGL task startup on interactive or periodic wake.
 *
 * @param[in] ctx       Platform wakeup context descriptor.
 * @param[in] user_data Opaque user data configured in h1os_lifecycle_t.
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
 * @brief Hook executed immediately prior to entering deep sleep.
 *
 * @param[in] sleep_sec Planned sleep interval in seconds.
 * @param[in] user_data Opaque user data configured in h1os_lifecycle_t.
 */
static void app_on_pre_sleep(uint32_t sleep_sec, void *user_data)
{
    (void)user_data;
    ESP_LOGI(TAG, "System entering deep sleep for %lu seconds", (unsigned long)sleep_sec);
}

/**
 * @brief Hook executed immediately prior to battery power cut.
 *
 * @param[in] user_data Opaque user data configured in h1os_lifecycle_t.
 */
static void app_on_shutdown(void *user_data)
{
    (void)user_data;
    ESP_LOGI(TAG, "System shutting down");
}

/**
 * @brief Fatal startup or lifecycle error hook (MANDATE-06).
 *
 * @param[in] err       Error code triggering the condition.
 * @param[in] context   Diagnostic label of failing stage.
 * @param[in] user_data Opaque user data configured in h1os_lifecycle_t.
 */
static void app_on_error(esp_err_t err, const char *context, void *user_data)
{
    (void)user_data;
    ESP_LOGE(TAG, "Fatal startup error at stage '%s': %s (0x%x)", context ? context : "unknown",
             esp_err_to_name(err), (unsigned int)err);
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
        .on_sync = NULL,
        .on_pre_sleep = app_on_pre_sleep,
        .on_shutdown = app_on_shutdown,
        .on_error = app_on_error,
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
                .sync_wait_ms = 0,
                .sync_timeout_ms = 5000,
            },
        .user_data = NULL,
    };

    esp_err_t ret = h1os_start(&lifecycle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to start H1OS: %s", esp_err_to_name(ret));
    }
}
