/**
 * @file main.c
 * @brief Unified Environmental Monitor & Deep Sleep Loop Demonstration Application
 *
 * Demonstrates the Rev 1.2.0 BSP features:
 *  - Tri-Node Sensing & Psychrometric Engine (SHTC3 + TSENS Die + SSD1681 Glass).
 *  - Native US/Imperial Environmental Telemetry (°F, %RH, Dew Point, Abs Humidity).
 *  - Dynamic Sliding Ambient Floor & Thermal Multi-Node Tracking.
 *  - PCF85063A Hardware RTC Alarm Wake Mechanism.
 *  - Pure Physical Telemetry: Directly measured Vbat (V/%), POSIX uptime, active wake duration (ms), cycle counter #.
 *  - Dual Tactile Button Support (BOOT: Sleep/Wake, POWER: Power Off / Hold).
 *  - Dev Continuous Mode support to bypass deep sleep and keep USB COM port connected for development.
 *
 * @attribution
 * - Architecture & Development: HUMIDYNE LABS / Humiditron (2026)
 * - AI Systems Co-Developer: Gemini (Google DeepMind)
 * - Hardware Target: Waveshare ESP32-S3 ePaper 1.54 V2
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "bsp/bsp.h"
#include "lvgl.h"

static const char *TAG = "unified_demo";

/* --- Configuration Constants --- */
#define SENSOR_SAMPLE_INTERVAL_SEC      60       /* 60-second headless sub execution period       */
#define DEFAULT_DEEP_SLEEP_SEC          120      /* 120-second (2-minute) PCF85063A Alarm UI wake */
#define CRITICAL_BATTERY_SHUTDOWN_PCT   10       /* Auto-shutdown at <= 10% SoC                   */

/**
 * Development Mode Switch:
 * Set to 'true' to keep USB COM / serial port alive for continuous logging by using FreeRTOS delays instead of deep sleep.
 * Set to 'false' for full production deep sleep power-optimized cycling (PCF85063A alarm wake).
 */
#define CONFIG_ENABLE_DEV_CONTINUOUS_MODE false

/* --- Persistent App State in RTC Slow RAM --- */
typedef struct {
    time_t   boot_epoch_sec;      /* POSIX time at cold boot */
    uint32_t total_uptime_sec;
    uint32_t sleep_interval_sec;
    uint32_t cycle_counter;
    float    last_temp_f;
    float    last_rh_pct;
    uint32_t initial_vbat_mv;     /* Boot initial battery voltage (mV)      */
    uint8_t  active_page;         /* 0 = Page 1 (ENV), 1 = Page 2 (SYS/BAT) */
} app_rtc_persisted_state_t;

RTC_DATA_ATTR static app_rtc_persisted_state_t s_app_state = {
    .boot_epoch_sec     = 0,
    .total_uptime_sec   = 0,
    .sleep_interval_sec = DEFAULT_DEEP_SLEEP_SEC,
    .cycle_counter      = 0,
    .last_temp_f        = 0.0f,
    .last_rh_pct        = 0.0f,
    .initial_vbat_mv    = 0,
    .active_page        = 0,
};

static inline void _EPD_HELPER(uint32_t delay_time) {
    sub_display_wait_busy(delay_time); // Wait for physical E-Paper controller to release BUSY line
    bsp_delay_ms(delay_time);          // Manual settling delay once display is free to guarantee complete electrophoretic particle latching on glass
    return;
}

/* --- Forward Declarations --- */
static void render_page_environmental(const bsp_app_telemetry_t *telem);
static void render_page_system_health(const bsp_app_telemetry_t *telem);
static void render_active_dashboard(const bsp_app_telemetry_t *telem);
static void render_shutdown_ui(const char *title_str, const char *sub_str);
static void on_boot_button_click(bsp_button_t btn, bsp_button_event_t event, void *user_data);
static void on_power_button_click(bsp_button_t btn, bsp_button_event_t event, void *user_data);

/* =========================================================================
 * UI Rendering (200x200 Monochrome E-Paper with LVGL v9)
 * ========================================================================= */
static void render_page_environmental(const bsp_app_telemetry_t *telem)
{
    bsp_lvgl_lock();
    lv_obj_t *scr = lv_screen_active();
    lv_obj_clean(scr);
    lv_obj_set_style_bg_color(scr, lv_color_white(), 0);
    lv_obj_invalidate(scr);

    // 1. Header Bar: HUMIDYNE LABS (left), 1/2 (right)
    lv_obj_t *header = lv_label_create(scr);
    lv_label_set_text(header, "HUMIDYNE LABS");
    lv_obj_set_style_text_font(header, MONTSERRAT_14, 0);
    lv_obj_align(header, LV_ALIGN_TOP_LEFT, 6, 4);

    lv_obj_t *lbl_page = lv_label_create(scr);
    lv_label_set_text(lbl_page, "1/2");
    lv_obj_set_style_text_font(lbl_page, MONTSERRAT_14, 0);
    lv_obj_align(lbl_page, LV_ALIGN_TOP_RIGHT, -6, 4);

    // Header Divider Line (y=20)
    static lv_point_precise_t line1_pts[] = {{4, 20}, {196, 20}};
    lv_obj_t *line1 = lv_line_create(scr);
    lv_line_set_points(line1, line1_pts, 2);
    lv_obj_set_style_line_width(line1, 1, 0);
    lv_obj_set_style_line_color(line1, lv_color_black(), 0);

    // 2. Primary Telemetry Display (Large Temperature & RH)
    lv_obj_t *lbl_temp = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_temp, "%.1f°F", telem->ambient_temp_f);
    lv_obj_set_style_text_font(lbl_temp, MONTSERRAT_20, 0);
    lv_obj_align(lbl_temp, LV_ALIGN_TOP_LEFT, 6, 26);

    lv_obj_t *lbl_rh = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_rh, "%.1f%%", telem->ambient_rh_pct);
    lv_obj_set_style_text_font(lbl_rh, MONTSERRAT_20, 0);
    lv_obj_align(lbl_rh, LV_ALIGN_TOP_RIGHT, -6, 26);

    // Sub-title ambient °C
    lv_obj_t *lbl_sub = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_sub, "(%.1f°C ambient)", telem->ambient_temp_c);
    lv_obj_set_style_text_font(lbl_sub, MONTSERRAT_14, 0);
    lv_obj_align(lbl_sub, LV_ALIGN_TOP_LEFT, 6, 50);

    // Divider Line 2 (y=68)
    static lv_point_precise_t line2_pts[] = {{4, 68}, {196, 68}};
    lv_obj_t *line2 = lv_line_create(scr);
    lv_line_set_points(line2, line2_pts, 2);
    lv_obj_set_style_line_width(line2, 1, 0);
    lv_obj_set_style_line_color(line2, lv_color_black(), 0);

    // 3. Psychrometric & Multi-Node Temperature Block
    lv_obj_t *lbl_dew = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_dew, "Dew Point:  %.1f°F", telem->dew_point_f);
    lv_obj_set_style_text_font(lbl_dew, MONTSERRAT_14, 0);
    lv_obj_align(lbl_dew, LV_ALIGN_TOP_LEFT, 6, 72);

    lv_obj_t *lbl_abs = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_abs, "Abs Humid:  %.1f g/m^3", telem->absolute_humidity_g);
    lv_obj_set_style_text_font(lbl_abs, MONTSERRAT_14, 0);
    lv_obj_align(lbl_abs, LV_ALIGN_TOP_LEFT, 6, 90);

    // Multi-Node °C
    lv_obj_t *lbl_node_c = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_node_c, "Glass: %.1f°C  Die: %.1f°C", telem->epd_glass_temp_c, telem->mcu_die_temp_c);
    lv_obj_set_style_text_font(lbl_node_c, MONTSERRAT_14, 0);
    lv_obj_align(lbl_node_c, LV_ALIGN_TOP_LEFT, 6, 108);

    // Multi-Node °F
    float glass_f = (telem->epd_glass_temp_c * 1.8f) + 32.0f;
    float die_f   = (telem->mcu_die_temp_c * 1.8f) + 32.0f;
    lv_obj_t *lbl_node_f = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_node_f, "Glass: %.1f°F  Die: %.1f°F", glass_f, die_f);
    lv_obj_set_style_text_font(lbl_node_f, MONTSERRAT_14, 0);
    lv_obj_align(lbl_node_f, LV_ALIGN_TOP_LEFT, 6, 126);

    // Divider Line 3 (y=146)
    static lv_point_precise_t line3_pts[] = {{4, 146}, {196, 146}};
    lv_obj_t *line3 = lv_line_create(scr);
    lv_line_set_points(line3, line3_pts, 2);
    lv_obj_set_style_line_width(line3, 1, 0);
    lv_obj_set_style_line_color(line3, lv_color_black(), 0);

    // Row 3 (y=178): Sleep Interval Alarm, Boot/Cycle Counter & Elapsed Uptime
    lv_obj_t *lbl_foot_l = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_foot_l, "Alarm: %lus", (unsigned long)s_app_state.sleep_interval_sec);
    lv_obj_set_style_text_font(lbl_foot_l, MONTSERRAT_14, 0);
    lv_obj_align(lbl_foot_l, LV_ALIGN_TOP_LEFT, 6, 178);

    lv_obj_t *lbl_foot_mid = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_foot_mid, "#%lu", (unsigned long)s_app_state.cycle_counter);
    lv_obj_set_style_text_font(lbl_foot_mid, MONTSERRAT_14, 0);
    lv_obj_align(lbl_foot_mid, LV_ALIGN_TOP_MID, 0, 178);

    lv_obj_t *lbl_foot_r = lv_label_create(scr);
    if (s_app_state.total_uptime_sec < 60) {
        lv_label_set_text_fmt(lbl_foot_r, "Up: %lus", (unsigned long)s_app_state.total_uptime_sec);
    } else if (s_app_state.total_uptime_sec < 3600) {
        lv_label_set_text_fmt(lbl_foot_r, "Up: %lum", (unsigned long)(s_app_state.total_uptime_sec / 60));
    } else {
        lv_label_set_text_fmt(lbl_foot_r, "Up: %.1fh", (float)s_app_state.total_uptime_sec / 3600.0f);
    }
    lv_obj_set_style_text_font(lbl_foot_r, MONTSERRAT_14, 0);
    lv_obj_align(lbl_foot_r, LV_ALIGN_TOP_RIGHT, -6, 178);

    // Force LVGL to render all widgets synchronously into the display buffer
    lv_refr_now(NULL);
    bsp_lvgl_unlock();
}

static void render_page_system_health(const bsp_app_telemetry_t *telem)
{
    bsp_lvgl_lock();
    lv_obj_t *scr = lv_screen_active();
    lv_obj_clean(scr);
    lv_obj_set_style_bg_color(scr, lv_color_white(), 0);
    lv_obj_invalidate(scr);

    // 1. Header Bar: HUMIDYNE LABS (left), 2/2 (right)
    lv_obj_t *header = lv_label_create(scr);
    lv_label_set_text(header, "HUMIDYNE LABS");
    lv_obj_set_style_text_font(header, MONTSERRAT_14, 0);
    lv_obj_align(header, LV_ALIGN_TOP_LEFT, 6, 4);

    lv_obj_t *lbl_page = lv_label_create(scr);
    lv_label_set_text(lbl_page, "2/2");
    lv_obj_set_style_text_font(lbl_page, MONTSERRAT_14, 0);
    lv_obj_align(lbl_page, LV_ALIGN_TOP_RIGHT, -6, 4);

    // Header Divider Line (y=20)
    static lv_point_precise_t line1_pts[] = {{4, 20}, {196, 20}};
    lv_obj_t *line1 = lv_line_create(scr);
    lv_line_set_points(line1, line1_pts, 2);
    lv_obj_set_style_line_width(line1, 1, 0);
    lv_obj_set_style_line_color(line1, lv_color_black(), 0);

    // 2. Primary Battery Display (Large Voltage & SoC %)
    lv_obj_t *lbl_vbat = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_vbat, "%.2f V", (float)telem->battery_mv / 1000.0f);
    lv_obj_set_style_text_font(lbl_vbat, MONTSERRAT_20, 0);
    lv_obj_align(lbl_vbat, LV_ALIGN_TOP_LEFT, 6, 26);

    lv_obj_t *lbl_pct = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_pct, "%u %%", telem->battery_percent);
    lv_obj_set_style_text_font(lbl_pct, MONTSERRAT_20, 0);
    lv_obj_align(lbl_pct, LV_ALIGN_TOP_RIGHT, -6, 26);

    // Sub-title
    lv_obj_t *lbl_sub = lv_label_create(scr);
    lv_label_set_text(lbl_sub, "(LiPo 3.7V Nominal, R_DIV)");
    lv_obj_set_style_text_font(lbl_sub, MONTSERRAT_14, 0);
    lv_obj_align(lbl_sub, LV_ALIGN_TOP_LEFT, 6, 50);

    // Divider Line 2 (y=68)
    static lv_point_precise_t line2_pts[] = {{4, 68}, {196, 68}};
    lv_obj_t *line2 = lv_line_create(scr);
    lv_line_set_points(line2, line2_pts, 2);
    lv_obj_set_style_line_width(line2, 1, 0);
    lv_obj_set_style_line_color(line2, lv_color_black(), 0);

    // 3. Power & Sensor Analytics
    float elapsed_hours = (s_app_state.total_uptime_sec >= 120) ? ((float)s_app_state.total_uptime_sec / 3600.0f) : 0.0f;
    float delta_v_mv    = (s_app_state.initial_vbat_mv > 0) ? ((float)s_app_state.initial_vbat_mv - (float)telem->battery_mv) : 0.0f;
    float mv_per_hr     = (elapsed_hours > 0.0f) ? (delta_v_mv / elapsed_hours) : 0.0f;
    float avg_current_ua = mv_per_hr * 500.0f; // 400 mAh LiPo: 500 uAh/mV

    lv_obj_t *lbl_rate = lv_label_create(scr);
    if (elapsed_hours > 0.0f && delta_v_mv > 0.0f) {
        lv_label_set_text_fmt(lbl_rate, "Discharge:  -%.1f mV/h", mv_per_hr);
    } else {
        lv_label_set_text(lbl_rate, "Discharge:  0.0 mV/h");
    }
    lv_obj_set_style_text_font(lbl_rate, MONTSERRAT_14, 0);
    lv_obj_align(lbl_rate, LV_ALIGN_TOP_LEFT, 6, 72);

    lv_obj_t *lbl_draw = lv_label_create(scr);
    if (elapsed_hours > 0.0f && avg_current_ua > 0.0f) {
        if (avg_current_ua < 1000.0f) {
            lv_label_set_text_fmt(lbl_draw, "Est Curr:   ~%.0f uA", avg_current_ua);
        } else {
            lv_label_set_text_fmt(lbl_draw, "Est Curr:   ~%.2f mA", avg_current_ua / 1000.0f);
        }
    } else {
        lv_label_set_text(lbl_draw, "Est Curr:   <25 uA (Sleep)");
    }
    lv_obj_set_style_text_font(lbl_draw, MONTSERRAT_14, 0);
    lv_obj_align(lbl_draw, LV_ALIGN_TOP_LEFT, 6, 90);

    lv_obj_t *lbl_smp = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_smp, "Samples:    %lu (Total)", (unsigned long)telem->sample_count);
    lv_obj_set_style_text_font(lbl_smp, MONTSERRAT_14, 0);
    lv_obj_align(lbl_smp, LV_ALIGN_TOP_LEFT, 6, 108);

    lv_obj_t *lbl_status = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_status, "Thermal:    %s", telem->is_thermally_settled ? "SETTLED (PASS)" : "SETTLING");
    lv_obj_set_style_text_font(lbl_status, MONTSERRAT_14, 0);
    lv_obj_align(lbl_status, LV_ALIGN_TOP_LEFT, 6, 126);

    // Divider Line 3 (y=146)
    static lv_point_precise_t line3_pts[] = {{4, 146}, {196, 146}};
    lv_obj_t *line3 = lv_line_create(scr);
    lv_line_set_points(line3, line3_pts, 2);
    lv_obj_set_style_line_width(line3, 1, 0);
    lv_obj_set_style_line_color(line3, lv_color_black(), 0);

    // Row 3 (y=178): Sleep Interval Alarm, Boot/Cycle Counter & Elapsed Uptime
    lv_obj_t *lbl_foot_l = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_foot_l, "Alarm: %lus", (unsigned long)s_app_state.sleep_interval_sec);
    lv_obj_set_style_text_font(lbl_foot_l, MONTSERRAT_14, 0);
    lv_obj_align(lbl_foot_l, LV_ALIGN_TOP_LEFT, 6, 178);

    lv_obj_t *lbl_foot_mid = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_foot_mid, "#%lu", (unsigned long)s_app_state.cycle_counter);
    lv_obj_set_style_text_font(lbl_foot_mid, MONTSERRAT_14, 0);
    lv_obj_align(lbl_foot_mid, LV_ALIGN_TOP_MID, 0, 178);

    lv_obj_t *lbl_foot_r = lv_label_create(scr);
    if (s_app_state.total_uptime_sec < 60) {
        lv_label_set_text_fmt(lbl_foot_r, "Up: %lus", (unsigned long)s_app_state.total_uptime_sec);
    } else if (s_app_state.total_uptime_sec < 3600) {
        lv_label_set_text_fmt(lbl_foot_r, "Up: %lum", (unsigned long)(s_app_state.total_uptime_sec / 60));
    } else {
        lv_label_set_text_fmt(lbl_foot_r, "Up: %.1fh", (float)s_app_state.total_uptime_sec / 3600.0f);
    }
    lv_obj_set_style_text_font(lbl_foot_r, MONTSERRAT_14, 0);
    lv_obj_align(lbl_foot_r, LV_ALIGN_TOP_RIGHT, -6, 178);

    // Force LVGL to render all widgets synchronously into the display buffer
    lv_refr_now(NULL);
    bsp_lvgl_unlock();
}

static void render_active_dashboard(const bsp_app_telemetry_t *telem)
{
    if (s_app_state.active_page == 1) {
        render_page_system_health(telem);
    } else {
        render_page_environmental(telem);
    }
}

static void render_shutdown_ui(const char *title_str, const char *sub_str)
{
    uint32_t vbat_mv = 0;
    bsp_battery_get_voltage(&vbat_mv, NULL);
    uint8_t batt_pct = bsp_battery_get_percentage();

    bsp_lvgl_lock();
    bsp_lvgl_set_first_flush_mode(true); // Force full OTP refresh for shutdown screen
    lv_obj_t *scr = lv_screen_active();
    lv_obj_clean(scr);
    lv_obj_set_style_bg_color(scr, lv_color_white(), 0);
    lv_obj_invalidate(scr);

    lv_obj_t *title = lv_label_create(scr);
    lv_label_set_text(title, title_str ? title_str : "HUMIDYNE\nLABS");
    lv_obj_set_style_text_font(title, MONTSERRAT_20, 0);
    lv_obj_set_style_text_align(title, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(title, LV_ALIGN_CENTER, 0, -35);

    lv_obj_t *sub = lv_label_create(scr);
    if (sub_str) {
        lv_label_set_text(sub, sub_str);
    } else {
        lv_label_set_text_fmt(sub, "SoC: %u%% (%.2fV)\nPress POWER to Turn On", batt_pct, (float)vbat_mv / 1000.0f);
    }
    lv_obj_set_style_text_font(sub, MONTSERRAT_14, 0);
    lv_obj_set_style_text_align(sub, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(sub, LV_ALIGN_CENTER, 0, 25);

    // Force LVGL to render all widgets synchronously into the display buffer
    lv_refr_now(NULL);
    bsp_lvgl_unlock();
}

/* =========================================================================
 * Button Callbacks
 * ========================================================================= */
static void on_boot_button_click(bsp_button_t btn, bsp_button_event_t event, void *user_data)
{
    if (event == BSP_BUTTON_EVENT_SINGLE_CLICK) {
        // Toggle active screen between 0 (Screen 1: ENV) and 1 (Screen 2: SYS)
        s_app_state.active_page = (s_app_state.active_page == 0) ? 1 : 0;
        ESP_LOGI(TAG, "BOOT button clicked: Switched to Screen %u (%s)",
                 s_app_state.active_page + 1, (s_app_state.active_page == 0) ? "ENV" : "SYS");

        // Acquire fresh telemetry via Layer 4 and re-render active dashboard
        bsp_app_telemetry_t telem = {0};
        bsp_app_get_telemetry(&telem);
        render_active_dashboard(&telem);
    }
}

static void on_power_button_click(bsp_button_t btn, bsp_button_event_t event, void *user_data)
{
    if (event == BSP_BUTTON_EVENT_LONG_PRESS) {
        ESP_LOGI(TAG, "POWER button long press: Triggering clean system power off");
        bsp_app_shutdown();
    }
}

/* =========================================================================
 * Master Execution Cycle
 * ========================================================================= */
static void execute_environmental_monitor_cycle(void)
{
    while (1) {
        int64_t cycle_start_us = esp_timer_get_time();
        s_app_state.cycle_counter++;

        if (s_app_state.sleep_interval_sec == 0) {
            s_app_state.sleep_interval_sec = DEFAULT_DEEP_SLEEP_SEC;
        }

        // 1. Ingest unified telemetry via Layer 4 API
        bsp_app_telemetry_t telem = {0};
        bsp_app_get_telemetry(&telem);

        // Derive precise elapsed uptime and baseline battery voltage from PCF85063A RTC POSIX clock
        time_t now_epoch = time(NULL);
        if (s_app_state.boot_epoch_sec == 0 || s_app_state.cycle_counter == 1 || s_app_state.initial_vbat_mv == 0) {
            s_app_state.boot_epoch_sec   = now_epoch;
            s_app_state.total_uptime_sec = 0;
            s_app_state.initial_vbat_mv  = telem.battery_mv;
        } else {
            s_app_state.total_uptime_sec = (uint32_t)(now_epoch >= s_app_state.boot_epoch_sec
                                                      ? (now_epoch - s_app_state.boot_epoch_sec) : 0);
        }

        ESP_LOGI(TAG, "Battery Status: %lu mV (%u%%)", (unsigned long)telem.battery_mv, telem.battery_percent);

        // 2. Critical Battery Guard: Auto power off if <= 10%
        if (telem.battery_percent <= CRITICAL_BATTERY_SHUTDOWN_PCT || telem.battery_mv < 3400) {
            ESP_LOGW(TAG, "Battery depleted (<= %d%%). Executing graceful shutdown...", CRITICAL_BATTERY_SHUTDOWN_PCT);
            bsp_app_shutdown();
            return;
        }

        s_app_state.last_temp_f = telem.ambient_temp_f;
        s_app_state.last_rh_pct = telem.ambient_rh_pct;

        uint32_t active_ms = (uint32_t)((esp_timer_get_time() - cycle_start_us) / 1000);

        ESP_LOGI(TAG, "==========================================================================");
        ESP_LOGI(TAG, "  CLASS-E HYGROMETER CYCLE #%lu TELEMETRY REPORT (FULL UI REFRESH)", (unsigned long)s_app_state.cycle_counter);
        ESP_LOGI(TAG, "==========================================================================");
        ESP_LOGI(TAG, "  Ambient Temp:    %5.1f °F (%5.1f °C)",                           telem.ambient_temp_f, telem.ambient_temp_c);
        ESP_LOGI(TAG, "  Ambient RH:      %5.1f %%",                                       telem.ambient_rh_pct);
        ESP_LOGI(TAG, "  Dew Point:       %5.1f °F (%5.1f °C)",                           telem.dew_point_f, telem.dew_point_c);
        ESP_LOGI(TAG, "  Absolute Humid:  %5.1f g/m³",                                     telem.absolute_humidity_g);
        ESP_LOGI(TAG, "  Thermal Status:  %s",                                             telem.is_thermally_settled ? "SETTLED" : "SETTLING");
        ESP_LOGI(TAG, "  Nodes:           SHTC3 Raw=%.1f°C, Die=%.1f°C, Glass=%.1f°C",     telem.raw_shtc3_temp_c, telem.mcu_die_temp_c, telem.epd_glass_temp_c);
        ESP_LOGI(TAG, "  Battery Health:  %lu mV (%u%%, Initial=%lu mV)",                  (unsigned long)telem.battery_mv, telem.battery_percent, (unsigned long)s_app_state.initial_vbat_mv);
        ESP_LOGI(TAG, "  Sample Count:    %lu",                                            (unsigned long)telem.sample_count);
        ESP_LOGI(TAG, "  Fast Sprint:     %lu ms",                                         (unsigned long)active_ms);
        ESP_LOGI(TAG, "  System Uptime:   %lu s",                                          (unsigned long)s_app_state.total_uptime_sec);
        ESP_LOGI(TAG, "==========================================================================");

        // 3. Assert PD_FULL lock (240 MHz) for LVGL Rendering and E-Paper SPI Blit
        bsp_pm_pd_full_acquire();
        render_active_dashboard(&telem);
        bsp_pm_pd_full_release();

        // 5. Power Button Hold Guard: If user is holding the power button, allow time for long-press shutdown
        TickType_t hold_start = xTaskGetTickCount();
        while (gpio_get_level((gpio_num_t)HAL_PIN_BUTTON_POWER) == 0) {
            vTaskDelay(pdMS_TO_TICKS(50));
            if ((xTaskGetTickCount() - hold_start) > pdMS_TO_TICKS(1800)) {
                ESP_LOGW(TAG, "POWER button held during active wake cycle: triggering system power off");
                bsp_app_shutdown();
                return;
            }
        }

#if CONFIG_ENABLE_DEV_CONTINUOUS_MODE
        ESP_LOGI(TAG, "DEV CONTINUOUS MODE: Delaying %lu seconds (COM port remains connected)...", (unsigned long)s_app_state.sleep_interval_sec);
        vTaskDelay(pdMS_TO_TICKS(s_app_state.sleep_interval_sec * 1000));
#else
        // 6. Enter Deep Sleep with Dual Wake Triggers: Internal 60s Timer + External PCF85063A Alarm
        ESP_LOGI(TAG, "Entering Deep Sleep (Internal Timer: %ds, PCF85063A Alarm: %ds)...", SENSOR_SAMPLE_INTERVAL_SEC, (int)s_app_state.sleep_interval_sec);

        bsp_sleep_config_t sleep_cfg = {
            .mode                   = BSP_SLEEP_MODE_DEEP,
            .duration_sec           = SENSOR_SAMPLE_INTERVAL_SEC,
            .rtc_alarm_duration_sec = s_app_state.sleep_interval_sec,
            .wake_sources           = BSP_WAKE_SRC_TIMER | BSP_WAKE_SRC_EXTERNAL_RTC | BSP_WAKE_SRC_BUTTONS,
            .next_init_mode         = BSP_INIT_MODE_MINIMAL,
        };
        bsp_app_sleep(&sleep_cfg);
        break;
#endif
    }
}

/* =========================================================================
 * Application Lifecycle Handlers
 * ========================================================================= */
static void app_on_pxe(bsp_button_mask_t btn_mask, void *user_data)
{
    // Fast non-blocking check: only clock pins if actively held LOW
    if (btn_mask & BSP_BUTTON_MASK_BOOT) {
        int held_ms = 0;
        while (gpio_get_level((gpio_num_t)HAL_PIN_BUTTON_BOOT) == 0) {
            bsp_delay_ms(25);
            held_ms += 25;
            if (held_ms >= 1200) {
                ESP_LOGW(TAG, "Lifecycle PXE: BOOT0 held for %d ms -> Entering ROM Download Bootloader...", held_ms);
                bsp_system_reboot_to_bootloader();
            }
        }
        if (held_ms < 400 && held_ms > 0) {
            s_app_state.active_page = (s_app_state.active_page == 0) ? 1 : 0;
            ESP_LOGI(TAG, "Lifecycle PXE: BOOT0 tap detected (%d ms) -> Toggled to Screen %u", held_ms, s_app_state.active_page + 1);
        }
    }
/*
    if (btn_mask & BSP_BUTTON_MASK_POWER) {
        int held_ms = 0;
        while (gpio_get_level((gpio_num_t)BSP_PIN_BUTTON_POWER) == 0) {
            bsp_delay_ms(25);
            held_ms += 25;
            if (held_ms >= 1200) {
                ESP_LOGW(TAG, "Lifecycle PXE: POWER held for %d ms -> Triggering clean system power off", held_ms);
                bsp_app_shutdown();
                return;
            }
        }
    }
*/        
}

static void app_on_boot(void *user_data)
{
    ESP_LOGI(TAG, "Lifecycle: BOOT initialized");
    bsp_button_register_cb(BSP_BUTTON_BOOT,  BSP_BUTTON_EVENT_SINGLE_CLICK, on_boot_button_click,  NULL);
    bsp_button_register_cb(BSP_BUTTON_POWER, BSP_BUTTON_EVENT_LONG_PRESS,   on_power_button_click, NULL);

    execute_environmental_monitor_cycle();
}

static void app_on_wake(const bsp_wake_context_t *ctx, void *user_data)
{
    ESP_LOGI(TAG, "Lifecycle: WAKE (Cause: %d, Woke from Button: %s, Mode: %d)", (int)ctx->wake_cause, ctx->woke_from_button ? "YES" : "NO", (int)ctx->init_mode);

    bsp_button_register_cb(BSP_BUTTON_BOOT,  BSP_BUTTON_EVENT_SINGLE_CLICK, on_boot_button_click,  NULL);
    bsp_button_register_cb(BSP_BUTTON_POWER, BSP_BUTTON_EVENT_LONG_PRESS,   on_power_button_click, NULL);

    // Full UI Refresh Cycle (Triggered by PCF85063A Alarm or Button Press)
    execute_environmental_monitor_cycle();
}

static void app_on_sleep(bsp_sleep_mode_t mode, uint32_t duration_sec, void *user_data)
{
    ESP_LOGI(TAG, "Lifecycle: on_sleep hook executed (Duration: %lu s)", (unsigned long)duration_sec);
}

static void app_on_power_off_splash(bsp_splash_type_t type, void *user_data)
{
    ESP_LOGI(TAG, "Lifecycle: on_power_off_splash rendering power-off UI");
    render_shutdown_ui("HUMIDYNE\nLABS", "Press POWER button\nto turn back on");
}

static void app_on_power_off(void *user_data)
{
    ESP_LOGI(TAG, "Lifecycle: on_power_off hook executed - wiping state");

    // Cleanly wipe application and BSP RTC Slow memory state so next power-up starts fresh as boot
    memset(&s_app_state, 0, sizeof(s_app_state));
    s_app_state.sleep_interval_sec = DEFAULT_DEEP_SLEEP_SEC;
}

/* =========================================================================
 * Application Entry Point
 * ========================================================================= */
void app_main(void)
{
    bsp_app_lifecycle_t lifecycle = {
        .on_pxe                     = app_on_pxe,
        .on_boot                    = app_on_boot,
        .on_wake                    = app_on_wake,
        .on_sleep                   = app_on_sleep,
        .on_power_off               = app_on_power_off,
        .on_power_off_splash        = app_on_power_off_splash,
        .default_chime_mask         = BSP_CHIME_MASK_BOOT | BSP_CHIME_MASK_POWER_OFF | BSP_CHIME_MASK_ALARM,
        .sub_execution_interval_sec = SENSOR_SAMPLE_INTERVAL_SEC,
        .user_data                  = NULL,
    };

    esp_err_t ret = bsp_app_start(&lifecycle);
	
    if (ret != ESP_OK) ESP_LOGE(TAG, "BSP Application Engine startup failed: %s", bsp_err_to_name(ret));
}
