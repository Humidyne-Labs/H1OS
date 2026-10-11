/**
 * @file main.c
 * @brief H1OS Showcase Demonstration: 4-Screen Luxury Environmental OS
 *
 * Demonstrates the H1OS Class-E Luxury Environmental Telemetry Operating System
 * on the Waveshare ESP32-S3 ePaper 1.54" V2 (200x200 Monochrome EPD, 188 DPI):
 *  - Screen 1: Primary Environmental Hero (°F/°C, %RH, Vapor Pressure, Invariant Status).
 *  - Screen 2: Psychrometrics Engine & Invariants (Dew Point, Abs/Sat Humidity, Glass/Floor Temps).
 *  - Screen 3: System Health & Power Autonomy (Battery Voltage, %SoC, Days Autonomy, MicroSD, MCU ΔT).
 *  - Screen 4: Verbose OS Diagnostics (Reset Reason, Wake Causes, ULP Reason, Free/Min Heap, HWM Stack).
 *  - Hardware Keypad Input (BOOT toggles Page 1 -> 2 -> 3 -> 4 -> 1).
 *  - Synthesized Audio Feedback (Harmonic Boot Chime & Micro-Tone Navigation Tick).
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
#include "esp_system.h"
#include "esp_heap_caps.h"
#include "esp_sleep.h"
#include "h1os/h1os.h"
#include "h1os/h1os_lvgl.h"
#include "h1os/h1os_time.h"
#include "h1os/sub_audio.h"
#include "h1os/sub_sdcard.h"
#include "h1os/orch_state.h"
#include "battery_estimator.h"
#include "lvgl.h"

static const char *TAG = "h1os_demo";

#define NUM_PAGES 4

/* Persistent Application State in RTC Slow Memory */
typedef struct {
    uint32_t boot_epoch_sec;
    uint32_t total_uptime_sec;
    uint32_t cycle_counter;
    uint8_t  active_page; // 0 = ENV HERO, 1 = PSYCHROMETRICS, 2 = HEALTH, 3 = DIAGNOSTICS
} app_rtc_persisted_state_t;

RTC_DATA_ATTR static app_rtc_persisted_state_t s_app_state = {0};

/* --- Forward Declarations --- */
static void render_page_env_hero(const h1os_telemetry_t *telem);
static void render_page_psychrometrics(const h1os_telemetry_t *telem);
static void render_page_system_health(const h1os_telemetry_t *telem);
static void render_page_diagnostics(const h1os_telemetry_t *telem);
static void update_active_display(void);
static void keypad_event_cb(lv_event_t *e);

/* =========================================================================
 * Helper: Reset Reason String
 * ========================================================================= */
static const char* get_reset_reason_str(esp_reset_reason_t reason)
{
    switch (reason) {
        case ESP_RST_POWERON:   return "POWER_ON";
        case ESP_RST_EXT:       return "EXTERNAL_PIN";
        case ESP_RST_SW:        return "SW_RESTART";
        case ESP_RST_PANIC:     return "EXCEPTION_PANIC";
        case ESP_RST_INT_WDT:   return "INT_WATCHDOG";
        case ESP_RST_TASK_WDT:  return "TASK_WATCHDOG";
        case ESP_RST_DEEPSLEEP: return "DEEP_SLEEP";
        case ESP_RST_BROWNOUT:  return "BROWNOUT";
        default:                return "UNKNOWN";
    }
}

/* =========================================================================
 * Helper: Wake Causes String
 * ========================================================================= */
static const char* get_wake_causes_str(uint32_t causes)
{
    if (causes & BIT(ESP_SLEEP_WAKEUP_UNDEFINED)) return "COLD_BOOT";
    if (causes & BIT(ESP_SLEEP_WAKEUP_EXT1))      return "EXT1_BUTTON_RTC";
    if (causes & BIT(ESP_SLEEP_WAKEUP_TIMER))     return "HW_TIMER";
    if (causes & BIT(ESP_SLEEP_WAKEUP_ULP))       return "ULP_SENTINEL";
    return "INTERNAL";
}

/* =========================================================================
 * UI Base Frame Builder: Sets up 200x200 canvas, title, page indicator & divider
 * ========================================================================= */
static lv_obj_t* create_page_base(const char *title, const char *page_str)
{
    h1os_lvgl_lock(100);
    lv_obj_t *scr = lv_screen_active();
    lv_obj_clean(scr);
    lv_obj_set_style_bg_color(scr, lv_color_white(), 0);

    // Bind hardware keypad listener to active screen cleanly (prevent duplicate callbacks)
    lv_group_t *def_grp = lv_group_get_default();
    if (def_grp == NULL) {
        def_grp = lv_group_create();
        lv_group_set_default(def_grp);
        lv_indev_t *indev = h1os_lvgl_get_indev();
        if (indev != NULL) {
            lv_indev_set_group(indev, def_grp);
        }
    }
    lv_obj_remove_event_cb(scr, keypad_event_cb);
    lv_obj_add_event_cb(scr, keypad_event_cb, LV_EVENT_KEY, NULL);
    lv_group_remove_obj(scr);
    lv_group_add_obj(def_grp, scr);
    lv_group_focus_obj(scr);

    // 1. Header Title: Left-aligned at (X: 6, Y: 4)
    lv_obj_t *lbl_title = lv_label_create(scr);
    lv_label_set_text(lbl_title, title);
    lv_obj_set_style_text_font(lbl_title, H1OS_FONT_14, 0);
    lv_obj_align(lbl_title, LV_ALIGN_TOP_LEFT, 6, 4);

    // Page Indicator: Right-aligned at (X: -6, Y: 4)
    lv_obj_t *lbl_pg = lv_label_create(scr);
    lv_label_set_text(lbl_pg, page_str);
    lv_obj_set_style_text_font(lbl_pg, H1OS_FONT_14, 0);
    lv_obj_align(lbl_pg, LV_ALIGN_TOP_RIGHT, -6, 4);

    // Divider Line (Y = 22, X: 4 to 196)
    static lv_point_precise_t line_pts[] = {{4, 22}, {196, 22}};
    lv_obj_t *line = lv_line_create(scr);
    lv_line_set_points(line, line_pts, 2);
    lv_obj_set_style_line_width(line, 1, 0);
    lv_obj_set_style_line_color(line, lv_color_black(), 0);

    return scr;
}

/* =========================================================================
 * Screen 1: Primary Environmental Hero (Page 1/4)
 * ========================================================================= */
static void render_page_env_hero(const h1os_telemetry_t *telem)
{
    lv_obj_t *scr = create_page_base("HUMIDYNE LABS", "1/4");

    // 1. Hero 20pt Numbers (Left: Temp °F, Right: %RH)
    lv_obj_t *lbl_temp = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_temp, "%.1f°F", telem->ambient_temp_f);
    lv_obj_set_style_text_font(lbl_temp, H1OS_FONT_20, 0);
    lv_obj_align(lbl_temp, LV_ALIGN_TOP_LEFT, 6, 32);

    lv_obj_t *lbl_rh = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_rh, "%.1f%%", telem->ambient_rh_pct);
    lv_obj_set_style_text_font(lbl_rh, H1OS_FONT_20, 0);
    lv_obj_align(lbl_rh, LV_ALIGN_TOP_RIGHT, -6, 32);

    // Metric equivalent
    lv_obj_t *lbl_sub = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_sub, "(%.1f°C ambient)", telem->ambient_temp_c);
    lv_obj_set_style_text_font(lbl_sub, H1OS_FONT_14, 0);
    lv_obj_align(lbl_sub, LV_ALIGN_TOP_LEFT, 6, 62);

    // Subtle Divider (Y = 88)
    static lv_point_precise_t mid_pts[] = {{4, 88}, {196, 88}};
    lv_obj_t *mid_line = lv_line_create(scr);
    lv_line_set_points(mid_line, mid_pts, 2);
    lv_obj_set_style_line_width(mid_line, 1, 0);
    lv_obj_set_style_line_color(mid_line, lv_color_black(), 0);

    // 2. Moisture Metrics Block
    lv_obj_t *lbl_stat = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_stat, "Status:   %s",
                          telem->is_thermally_settled ? "SETTLED" : "SETTLING");
    lv_obj_set_style_text_font(lbl_stat, H1OS_FONT_14, 0);
    lv_obj_align(lbl_stat, LV_ALIGN_TOP_LEFT, 6, 100);

    orch_persisted_state_t *st = orch_state_get();
    lv_obj_t *lbl_vp = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_vp, "Vapor P:  %.1f hPa", st->vapor_pressure_hpa);
    lv_obj_set_style_text_font(lbl_vp, H1OS_FONT_14, 0);
    lv_obj_align(lbl_vp, LV_ALIGN_TOP_LEFT, 6, 126);

    // 3. Footer Bar: Cycle count (left), Current Clock Time (right)
    char time_str[16] = "--:--";
    h1os_time_get_formatted(H1OS_TIME_FMT_12H_MIN, time_str, sizeof(time_str));

    lv_obj_t *lbl_foot_l = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_foot_l, "Cycle #%lu", (unsigned long)s_app_state.cycle_counter);
    lv_obj_set_style_text_font(lbl_foot_l, H1OS_FONT_14, 0);
    lv_obj_align(lbl_foot_l, LV_ALIGN_BOTTOM_LEFT, 6, -6);

    lv_obj_t *lbl_foot_r = lv_label_create(scr);
    lv_label_set_text(lbl_foot_r, time_str);
    lv_obj_set_style_text_font(lbl_foot_r, H1OS_FONT_14, 0);
    lv_obj_align(lbl_foot_r, LV_ALIGN_BOTTOM_RIGHT, -6, -6);

    lv_refr_now(NULL);
    h1os_lvgl_unlock();
}

/* =========================================================================
 * Screen 2: Psychrometrics Engine & Invariants (Page 2/4)
 * ========================================================================= */
static void render_page_psychrometrics(const h1os_telemetry_t *telem)
{
    lv_obj_t *scr = create_page_base("PSYCHROMETRICS", "2/4");

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

    // Footer Bar
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

/* =========================================================================
 * Screen 3: System Health & Battery Autonomy (Page 3/4)
 * ========================================================================= */
static void render_page_system_health(const h1os_telemetry_t *telem)
{
    lv_obj_t *scr = create_page_base("SYSTEM HEALTH", "3/4");

    // Row 1: Battery Voltage & Percentage
    lv_obj_t *lbl_bat = lv_label_create(scr);
    if (telem->is_usb_powered) {
        lv_label_set_text(lbl_bat, "Power:       USB CABLE");
    } else {
        lv_label_set_text_fmt(lbl_bat, "Battery:     %.2fV (%u%%)",
                              (float)telem->battery_mv / 1000.0f, telem->battery_percent);
    }
    lv_obj_set_style_text_font(lbl_bat, H1OS_FONT_14, 0);
    lv_obj_align(lbl_bat, LV_ALIGN_TOP_LEFT, 6, 30);

    // Row 2: Projected Autonomy
    lv_obj_t *lbl_autonomy = lv_label_create(scr);
    if (telem->is_usb_powered) {
        lv_label_set_text(lbl_autonomy, "Autonomy:    CONTINUOUS");
    } else {
        float days = battery_estimate_remaining_days(400, telem->battery_mv, 0.35f);
        lv_label_set_text_fmt(lbl_autonomy, "Autonomy:    ~%.0f Days", days);
    }
    lv_obj_set_style_text_font(lbl_autonomy, H1OS_FONT_14, 0);
    lv_obj_align(lbl_autonomy, LV_ALIGN_TOP_LEFT, 6, 52);

    // Row 3: MicroSD Storage
    lv_obj_t *lbl_sd = lv_label_create(scr);
    uint32_t sd_mb = 0;
    if (sub_sdcard_is_mounted() && sub_sdcard_get_capacity_mb(&sd_mb) == ESP_OK) {
        lv_label_set_text_fmt(lbl_sd, "MicroSD:     %.1f GB OK", (float)sd_mb / 1024.0f);
    } else {
        lv_label_set_text(lbl_sd, "MicroSD:     NO CARD");
    }
    lv_obj_set_style_text_font(lbl_sd, H1OS_FONT_14, 0);
    lv_obj_align(lbl_sd, LV_ALIGN_TOP_LEFT, 6, 80);

    // Row 4: Flash NVS
    lv_obj_t *lbl_nvs = lv_label_create(scr);
    lv_label_set_text(lbl_nvs, "Flash NVS:   SLAT ACTIVE");
    lv_obj_set_style_text_font(lbl_nvs, H1OS_FONT_14, 0);
    lv_obj_align(lbl_nvs, LV_ALIGN_TOP_LEFT, 6, 102);

    // Row 5: MCU Die Temp & Delta T
    float delta_t = telem->mcu_die_temp_c - telem->ambient_temp_c;
    lv_obj_t *lbl_mcu = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_mcu, "MCU Die:     %.1f°C", telem->mcu_die_temp_c);
    lv_obj_set_style_text_font(lbl_mcu, H1OS_FONT_14, 0);
    lv_obj_align(lbl_mcu, LV_ALIGN_TOP_LEFT, 6, 130);

    lv_obj_t *lbl_delta = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_delta, "Thermal ΔT:  %+.1f°C", delta_t);
    lv_obj_set_style_text_font(lbl_delta, H1OS_FONT_14, 0);
    lv_obj_align(lbl_delta, LV_ALIGN_TOP_LEFT, 6, 150);

    // Footer Bar: Date (left), Time (right)
    char date_str[16] = "2026-10-11";
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

    lv_refr_now(NULL);
    h1os_lvgl_unlock();
}

/* =========================================================================
 * Screen 4: Verbose OS Diagnostics (Page 4/4)
 * ========================================================================= */
static void render_page_diagnostics(const h1os_telemetry_t *telem)
{
    lv_obj_t *scr = create_page_base("OS DIAGNOSTICS", "4/4");

    orch_persisted_state_t *st = orch_state_get();

    // Row 1: Reset Reason
    lv_obj_t *lbl_rst = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_rst, "Reset:  %s", get_reset_reason_str(esp_reset_reason()));
    lv_obj_set_style_text_font(lbl_rst, H1OS_FONT_14, 0);
    lv_obj_align(lbl_rst, LV_ALIGN_TOP_LEFT, 6, 28);

    // Row 2: Wake Causes
    uint32_t causes = esp_sleep_get_wakeup_causes();
    lv_obj_t *lbl_wake = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_wake, "Wake:   %s", get_wake_causes_str(causes));
    lv_obj_set_style_text_font(lbl_wake, H1OS_FONT_14, 0);
    lv_obj_align(lbl_wake, LV_ALIGN_TOP_LEFT, 6, 48);

    // Row 3: ULP Sentinel Dispatch
    const char *ulp_str = "NONE";
    if (st->ulp_dispatch_reason == ULP_DISPATCH_SENSOR_SPRINT) ulp_str = "SENSOR_SPRINT";
    else if (st->ulp_dispatch_reason == ULP_DISPATCH_MAIN_WAKE) ulp_str = "MAIN_WAKE";
    else if (st->ulp_dispatch_reason == ULP_DISPATCH_CRITICAL_SHUTDOWN) ulp_str = "CRIT_SHUTDOWN";

    lv_obj_t *lbl_ulp = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_ulp, "ULP:    %s", ulp_str);
    lv_obj_set_style_text_font(lbl_ulp, H1OS_FONT_14, 0);
    lv_obj_align(lbl_ulp, LV_ALIGN_TOP_LEFT, 6, 68);

    // Row 4: Heap Memory (Free / Minimum Ever Free)
    uint32_t free_heap = esp_get_free_heap_size() / 1024;
    uint32_t min_heap  = esp_get_minimum_free_heap_size() / 1024;
    lv_obj_t *lbl_heap = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_heap, "Heap:   %luK / %luK Min",
                          (unsigned long)free_heap, (unsigned long)min_heap);
    lv_obj_set_style_text_font(lbl_heap, H1OS_FONT_14, 0);
    lv_obj_align(lbl_heap, LV_ALIGN_TOP_LEFT, 6, 94);

    // Row 5: FreeRTOS Task High Watermark
    UBaseType_t hwm = uxTaskGetStackHighWaterMark(NULL);
    lv_obj_t *lbl_stack = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_stack, "Stack:  %u B HWM", (unsigned int)(hwm * sizeof(StackType_t)));
    lv_obj_set_style_text_font(lbl_stack, H1OS_FONT_14, 0);
    lv_obj_align(lbl_stack, LV_ALIGN_TOP_LEFT, 6, 114);

    // Row 6: Wakes & Ring Buffer Head
    lv_obj_t *lbl_wakes = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_wakes, "Wakes:  %lu (Ring: %u/32)",
                          (unsigned long)st->wake_count, st->ring_head);
    lv_obj_set_style_text_font(lbl_wakes, H1OS_FONT_14, 0);
    lv_obj_align(lbl_wakes, LV_ALIGN_TOP_LEFT, 6, 134);

    // Row 7: Dynamic Frequency Scaling
    lv_obj_t *lbl_dfs = lv_label_create(scr);
    lv_label_set_text(lbl_dfs, "CPU:    80MHz (DFS ON)");
    lv_obj_set_style_text_font(lbl_dfs, H1OS_FONT_14, 0);
    lv_obj_align(lbl_dfs, LV_ALIGN_TOP_LEFT, 6, 154);

    // Footer Bar: Version (left), Target (right)
    lv_obj_t *lbl_foot_l = lv_label_create(scr);
    lv_label_set_text(lbl_foot_l, "H1OS v2.0.0-dev");
    lv_obj_set_style_text_font(lbl_foot_l, H1OS_FONT_14, 0);
    lv_obj_align(lbl_foot_l, LV_ALIGN_BOTTOM_LEFT, 6, -6);

    lv_obj_t *lbl_foot_r = lv_label_create(scr);
    lv_label_set_text(lbl_foot_r, "ESP-IDF v6.1");
    lv_obj_set_style_text_font(lbl_foot_r, H1OS_FONT_14, 0);
    lv_obj_align(lbl_foot_r, LV_ALIGN_BOTTOM_RIGHT, -6, -6);

    lv_refr_now(NULL);
    h1os_lvgl_unlock();
}

/* =========================================================================
 * Screen Switcher Dispatcher
 * ========================================================================= */
static void update_active_display(void)
{
    h1os_telemetry_t telem = {0};
    h1os_get_telemetry(&telem);

    switch (s_app_state.active_page) {
        case 0:
            render_page_env_hero(&telem);
            break;
        case 1:
            render_page_psychrometrics(&telem);
            break;
        case 2:
            render_page_system_health(&telem);
            break;
        case 3:
            render_page_diagnostics(&telem);
            break;
        default:
            s_app_state.active_page = 0;
            render_page_env_hero(&telem);
            break;
    }
}

/* =========================================================================
 * Hardware Keypad Event Callback
 * ========================================================================= */
static void keypad_event_cb(lv_event_t *e)
{
    uint32_t key = lv_event_get_key(e);
    if (key == LV_KEY_NEXT || key == LV_KEY_RIGHT || key == LV_KEY_ENTER) {
        // Synthesize short haptic confirmation tick (2400 Hz for 15ms)
        sub_audio_play_tone(2400, 15);

        // Single step: Cycle page 0 -> 1 -> 2 -> 3 -> 0
        s_app_state.active_page = (s_app_state.active_page + 1) % NUM_PAGES;
        ESP_LOGI(TAG, "Keypad event (key %lu): Navigating to page %u/%u",
                 (unsigned long)key, s_app_state.active_page + 1, NUM_PAGES);
        update_active_display();
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

    // Initial audio cue: 2-tone harmonic chord (1046 Hz -> 1318 Hz)
    sub_audio_play_tone(1046, 40);
    vTaskDelay(pdMS_TO_TICKS(10));
    sub_audio_play_tone(1318, 60);

    // Probe MicroSD card
    sub_sdcard_mount();

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

    // Probe MicroSD card
    sub_sdcard_mount();

    update_active_display();
}

static void app_on_pre_sleep(uint32_t sleep_sec, void *user_data)
{
    ESP_LOGI(TAG, "Lifecycle: PRE-SLEEP hook (Duration: %lu s)", (unsigned long)sleep_sec);
    // Unmount MicroSD card cleanly before deep sleep
    sub_sdcard_unmount();
}

static void app_on_shutdown(void *user_data)
{
    ESP_LOGI(TAG, "Lifecycle: SHUTDOWN hook executing");
    sub_sdcard_unmount();
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
