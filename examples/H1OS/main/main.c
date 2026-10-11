/**
 * @file main.c
 * @brief H1OS Application Demonstration
 *
 * Demonstrates the H1OS Class-E Luxury Environmental Telemetry Operating System:
 *  - Tri-Node Sensing & Psychrometric Invariant Engine.
 *  - Native US/Imperial & Metric Environmental Telemetry (°F/°C, %RH, Dew Point, Abs Humidity).
 *  - Pure Single-Owner Hardware Lifecycle (Flow A <4ms vs Flow B Interactive UI).
 *  - LVGL v9 Keypad Input (BOOT toggles Screen 1 <-> Screen 2).
 *  - 30-Second Inactivity Stand-Down with 80 MHz DFS Power Droop.
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "h1os/h1os.h"
#include "h1os/h1os_lvgl.h"
#include "lvgl.h"

static const char *TAG = "h1os_main";

#define DEFAULT_DEEP_SLEEP_SEC 120

/* Persistent App State in RTC Slow Memory */
typedef struct {
    uint32_t boot_epoch_sec;
    uint32_t total_uptime_sec;
    uint32_t cycle_counter;
    uint8_t  active_page; // 0 = Screen 1 (ENV), 1 = Screen 2 (HEALTH)
} app_rtc_persisted_state_t;

RTC_DATA_ATTR static app_rtc_persisted_state_t s_app_state = {0};

/* --- Forward Declarations --- */
static void render_page_environmental(const h1os_telemetry_t *telem);
static void render_page_system_health(const h1os_telemetry_t *telem);
static void update_active_display(void);
static void keypad_event_cb(lv_event_t *e);

/* =========================================================================
 * UI Rendering (200x200 Monochrome E-Paper with LVGL v9 & Montserrat Typography)
 * ========================================================================= */
static void keypad_event_cb(lv_event_t *e)
{
    uint32_t key = lv_event_get_key(e);
    if (key == LV_KEY_NEXT || key == LV_KEY_ENTER) {
        /* Toggle active page */
        s_app_state.active_page = (s_app_state.active_page == 0) ? 1 : 0;
        ESP_LOGI(TAG, "Keypad event: switched to screen %u", s_app_state.active_page + 1);
        update_active_display();
    }
}

static void render_page_environmental(const h1os_telemetry_t *telem)
{
    h1os_lvgl_lock(100);
    lv_obj_t *scr = lv_screen_active();
    lv_obj_clean(scr);
    lv_obj_set_style_bg_color(scr, lv_color_white(), 0);

    // Bind keypad event listener to screen
    lv_obj_add_event_cb(scr, keypad_event_cb, LV_EVENT_KEY, NULL);
    lv_group_t *def_grp = lv_group_get_default();
    if (def_grp == NULL) {
        def_grp = lv_group_create();
        lv_group_set_default(def_grp);
        lv_indev_t *indev = h1os_lvgl_get_indev();
        if (indev != NULL) {
            lv_indev_set_group(indev, def_grp);
        }
    }
    lv_group_add_obj(def_grp, scr);

    // 1. Header Bar: HUMIDYNE LABS (left), 1/2 (right)
    lv_obj_t *header = lv_label_create(scr);
    lv_label_set_text(header, "HUMIDYNE LABS");
    lv_obj_set_style_text_font(header, H1OS_FONT_14, 0);
    lv_obj_align(header, LV_ALIGN_TOP_LEFT, 6, 4);

    lv_obj_t *lbl_page = lv_label_create(scr);
    lv_label_set_text(lbl_page, "1/2");
    lv_obj_set_style_text_font(lbl_page, H1OS_FONT_14, 0);
    lv_obj_align(lbl_page, LV_ALIGN_TOP_RIGHT, -6, 4);

    // Divider Line 1
    static lv_point_precise_t line1_pts[] = {{4, 22}, {196, 22}};
    lv_obj_t *line1 = lv_line_create(scr);
    lv_line_set_points(line1, line1_pts, 2);
    lv_obj_set_style_line_width(line1, 1, 0);
    lv_obj_set_style_line_color(line1, lv_color_black(), 0);

    // 2. Primary Telemetry Display (Large 20pt Numbers)
    lv_obj_t *lbl_temp = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_temp, "%.1f°F", telem->ambient_temp_f);
    lv_obj_set_style_text_font(lbl_temp, H1OS_FONT_20, 0);
    lv_obj_align(lbl_temp, LV_ALIGN_TOP_LEFT, 6, 28);

    lv_obj_t *lbl_rh = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_rh, "%.1f%%", telem->ambient_rh_pct);
    lv_obj_set_style_text_font(lbl_rh, H1OS_FONT_20, 0);
    lv_obj_align(lbl_rh, LV_ALIGN_TOP_RIGHT, -6, 28);

    lv_obj_t *lbl_sub = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_sub, "(%.1f°C ambient)", telem->ambient_temp_c);
    lv_obj_set_style_text_font(lbl_sub, H1OS_FONT_14, 0);
    lv_obj_align(lbl_sub, LV_ALIGN_TOP_LEFT, 6, 54);

    // Divider Line 2
    static lv_point_precise_t line2_pts[] = {{4, 74}, {196, 74}};
    lv_obj_t *line2 = lv_line_create(scr);
    lv_line_set_points(line2, line2_pts, 2);
    lv_obj_set_style_line_width(line2, 1, 0);
    lv_obj_set_style_line_color(line2, lv_color_black(), 0);

    // 3. Psychrometrics Block
    lv_obj_t *lbl_dew = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_dew, "Dew Point:  %.1f°F", telem->dew_point_f);
    lv_obj_set_style_text_font(lbl_dew, H1OS_FONT_14, 0);
    lv_obj_align(lbl_dew, LV_ALIGN_TOP_LEFT, 6, 80);

    lv_obj_t *lbl_abs = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_abs, "Abs Humid:  %.1f g/m³", telem->absolute_humidity_g);
    lv_obj_set_style_text_font(lbl_abs, H1OS_FONT_14, 0);
    lv_obj_align(lbl_abs, LV_ALIGN_TOP_LEFT, 6, 102);

    // Footer
    lv_obj_t *lbl_foot = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_foot, "Cycle #%lu | %s",
                          (unsigned long)s_app_state.cycle_counter,
                          telem->is_thermally_settled ? "SETTLED" : "SETTLING");
    lv_obj_set_style_text_font(lbl_foot, H1OS_FONT_14, 0);
    lv_obj_align(lbl_foot, LV_ALIGN_BOTTOM_LEFT, 6, -6);

    lv_refr_now(NULL);
    h1os_lvgl_unlock();
}

static void render_page_system_health(const h1os_telemetry_t *telem)
{
    h1os_lvgl_lock(100);
    lv_obj_t *scr = lv_screen_active();
    lv_obj_clean(scr);
    lv_obj_set_style_bg_color(scr, lv_color_white(), 0);

    // Bind keypad event listener to screen
    lv_obj_add_event_cb(scr, keypad_event_cb, LV_EVENT_KEY, NULL);
    lv_group_t *def_grp = lv_group_get_default();
    if (def_grp != NULL) {
        lv_group_add_obj(def_grp, scr);
    }

    // 1. Header Bar: HUMIDYNE LABS (left), 2/2 (right)
    lv_obj_t *header = lv_label_create(scr);
    lv_label_set_text(header, "SYSTEM HEALTH");
    lv_obj_set_style_text_font(header, H1OS_FONT_14, 0);
    lv_obj_align(header, LV_ALIGN_TOP_LEFT, 6, 4);

    lv_obj_t *lbl_page = lv_label_create(scr);
    lv_label_set_text(lbl_page, "2/2");
    lv_obj_set_style_text_font(lbl_page, H1OS_FONT_14, 0);
    lv_obj_align(lbl_page, LV_ALIGN_TOP_RIGHT, -6, 4);

    // Divider Line 1
    static lv_point_precise_t line1_pts[] = {{4, 22}, {196, 22}};
    lv_obj_t *line1 = lv_line_create(scr);
    lv_line_set_points(line1, line1_pts, 2);
    lv_obj_set_style_line_width(line1, 1, 0);
    lv_obj_set_style_line_color(line1, lv_color_black(), 0);

    // 2. Battery & Power
    lv_obj_t *lbl_vbat = lv_label_create(scr);
    if (telem->is_usb_powered) {
        lv_label_set_text(lbl_vbat, "PWR: USB CABLE");
    } else {
        lv_label_set_text_fmt(lbl_vbat, "BAT: %.2fV (%u%%)", (float)telem->battery_mv / 1000.0f, telem->battery_percent);
    }
    lv_obj_set_style_text_font(lbl_vbat, H1OS_FONT_14, 0);
    lv_obj_align(lbl_vbat, LV_ALIGN_TOP_LEFT, 6, 28);

    // Tri-Node Temperatures
    lv_obj_t *lbl_nodes = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_nodes, "SHTC3: %.1f°C\nMCU:   %.1f°C\nGlass: %.1f°C",
                          telem->raw_shtc3_temp_c, telem->mcu_die_temp_c, telem->epd_glass_temp_c);
    lv_obj_set_style_text_font(lbl_nodes, H1OS_FONT_14, 0);
    lv_obj_align(lbl_nodes, LV_ALIGN_TOP_LEFT, 6, 56);

    // Footer
    lv_obj_t *lbl_foot = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_foot, "Uptime: %lu s", (unsigned long)s_app_state.total_uptime_sec);
    lv_obj_set_style_text_font(lbl_foot, H1OS_FONT_14, 0);
    lv_obj_align(lbl_foot, LV_ALIGN_BOTTOM_LEFT, 6, -6);

    lv_refr_now(NULL);
    h1os_lvgl_unlock();
}

static void update_active_display(void)
{
    h1os_telemetry_t telem = {0};
    h1os_get_telemetry(&telem);

    if (s_app_state.active_page == 0) {
        render_page_environmental(&telem);
    } else {
        render_page_system_health(&telem);
    }
}

/* =========================================================================
 * Application Lifecycle Handlers
 * ========================================================================= */
static void app_on_boot(void *user_data)
{
    ESP_LOGI(TAG, "Lifecycle: COLD BOOT initialized");
    s_app_state.cycle_counter = 1;
    s_app_state.boot_epoch_sec = (uint32_t)time(NULL);
    update_active_display();
}

static void app_on_wake(const h1os_wake_context_t *ctx, void *user_data)
{
    s_app_state.cycle_counter++;
    time_t now = time(NULL);
    if (s_app_state.boot_epoch_sec > 0 && now >= (time_t)s_app_state.boot_epoch_sec) {
        s_app_state.total_uptime_sec = (uint32_t)(now - s_app_state.boot_epoch_sec);
    }
    ESP_LOGI(TAG, "Lifecycle: WAKE #%lu (Causes bitmask: 0x%08lx)",
             (unsigned long)s_app_state.cycle_counter, (unsigned long)ctx->wakeup_causes);
    update_active_display();
}

static void app_on_pre_sleep(uint32_t sleep_sec, void *user_data)
{
    ESP_LOGI(TAG, "Lifecycle: PRE-SLEEP hook (Duration: %lu s)", (unsigned long)sleep_sec);
}

static void app_on_shutdown(void *user_data)
{
    ESP_LOGI(TAG, "Lifecycle: SHUTDOWN hook executing");
}

/* =========================================================================
 * Application Entry Point
 * ========================================================================= */
void app_main(void)
{
    ESP_LOGI(TAG, "Starting %s (%s v%s)", H1OS_NAME, H1OS_SUBTITLE, H1OS_VERSION_STRING);

    h1os_lifecycle_t lifecycle = {
        .on_boot                    = app_on_boot,
        .on_wake                    = app_on_wake,
        .on_pre_sleep               = app_on_pre_sleep,
        .on_shutdown                = app_on_shutdown,
        .presentation = {
            .on_splash              = NULL,
            .on_chime               = NULL,
            .chime_mask             = 0,
        },
        .session = {
            .inactivity_timeout_sec = 30,
            .enable_dfs_80mhz       = true,
        },
        .user_data                  = NULL,
    };

    esp_err_t ret = h1os_start(&lifecycle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "H1OS Startup Failed: %s", esp_err_to_name(ret));
    }
}
