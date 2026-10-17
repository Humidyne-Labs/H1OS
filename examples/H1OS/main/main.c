/**
 * @file main.c
 * @brief H1OS Showcase Demonstration: Modular 4-Screen Luxury Environmental OS
 *
 * Demonstrates the H1OS Class-E Luxury Environmental Telemetry Operating System
 * on the Waveshare ESP32-S3 ePaper 1.54" V2 (200x200 Monochrome EPD, 188 DPI):
 *  - Modular Screens (screen_env_hero, screen_psychrometrics, screen_system_health, screen_diagnostics).
 *  - Tactile Keypad Navigation:
 *      * Short-press BOOT (GPIO 0): Step forward (1 -> 2 -> 3 -> 4 -> 1) with 15ms audio tick.
 *      * Short-press POWER (GPIO 18): Step backward (4 -> 3 -> 2 -> 1 -> 4) with 15ms audio tick.
 *      * Long-press POWER (GPIO 18 >= 2s): Power-down chime & orderly hardware shutdown (h1os_shutdown).
 *  - Synthesized Audio Feedback (ES8311 I2S Codec & NS4168 Amp).
 *  - 30-Second Inactivity Sleep with 80 MHz DFS Power Droop.
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "h1os/h1os.h"
#include "h1os/hal_io.h"
#include "h1os/h1os_lvgl.h"
#include "h1os/sub_audio.h"
#include "h1os/sub_power.h"
#include "h1os/sub_sdcard.h"
#include "screens.h"
#include "humid1_cyber_wave.h"

static const char *TAG = "h1os_demo";

/* Persistent Application State in RTC Slow Memory */
typedef struct {
    uint32_t boot_epoch_sec;
    uint32_t total_uptime_sec;
    uint32_t cycle_counter;
    /**********************
     *   0 = ENV HERO, 
     *   1 = PSYCHROMETRICS, 
     *   2 = HEALTH, 
     *   3 = DIAGNOSTICS 
     **********************/
    uint8_t  active_page;
} app_rtc_persisted_state_t;

RTC_DATA_ATTR static app_rtc_persisted_state_t s_app_state = {0};

/* --- Forward Declarations --- */
static void update_active_display(void);
static void keypad_event_cb(lv_event_t *e);

/* =========================================================================
 * Screen Switcher Dispatcher
 * ========================================================================= */
static void update_active_display(void)
{
    static h1os_telemetry_t telem;
    h1os_get_telemetry(&telem);

    switch (s_app_state.active_page) {
        case H1OS_SCREEN_ENV_HERO:
            screen_env_hero_render(&telem, s_app_state.cycle_counter, keypad_event_cb);
            break;
        case H1OS_SCREEN_PSYCHROMETRICS:
            screen_psychrometrics_render(&telem, keypad_event_cb);
            break;
        case H1OS_SCREEN_SYSTEM_HEALTH:
            screen_system_health_render(&telem, keypad_event_cb);
            break;
        case H1OS_SCREEN_DIAGNOSTICS:
            screen_diagnostics_render(&telem, keypad_event_cb);
            break;
        default:
            s_app_state.active_page = H1OS_SCREEN_ENV_HERO;
            screen_env_hero_render(&telem, s_app_state.cycle_counter, keypad_event_cb);
            break;
    }
}

static bool s_is_shutting_down = false;

/* =========================================================================
 * Hardware Keypad Event Callback
 * ========================================================================= */
static void keypad_event_cb(lv_event_t *e)
{
    if (s_is_shutting_down) return;

    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_LONG_PRESSED) {
        // Native LVGL Long-Press Detection (>= 2.0s hold on POWER / LV_KEY_ENTER)
        ESP_LOGI(TAG, "Keypad: Native LVGL long-press (>=2.0s) detected! Executing shutdown...");
        s_is_shutting_down = true;
        h1os_shutdown();
        return;
    }

    if (code == LV_EVENT_KEY) {
        uint32_t key = lv_event_get_key(e);
        if (key == 0 && lv_event_get_param(e) != NULL) {
            key = *(const uint32_t *)lv_event_get_param(e);
        }
        ESP_LOGI(TAG, "Keypad event received: LV_EVENT_KEY (key=0x%lx)", (unsigned long)key);

        if (key == LV_KEY_NEXT || key == LV_KEY_RIGHT) {
            // BOOT Button: Forward Cycle (Non-blocking acoustic feedback)
            sub_audio_play_tone_async(1046, 50);
            s_app_state.active_page = (s_app_state.active_page + 1) % H1OS_NUM_SCREENS;
            ESP_LOGI(TAG, "Keypad forward (BOOT): Navigating to page %u/%u",
                     s_app_state.active_page + 1, H1OS_NUM_SCREENS);
            update_active_display();
            return;
        } else if (key == LV_KEY_PREV || key == LV_KEY_LEFT || key == LV_KEY_ENTER) {
            // POWER Button: Reverse Cycle (Non-blocking acoustic feedback)
            sub_audio_play_tone_async(880, 50);
            s_app_state.active_page = (s_app_state.active_page + H1OS_NUM_SCREENS - 1) % H1OS_NUM_SCREENS;
            ESP_LOGI(TAG, "Keypad reverse (POWER): Navigating to page %u/%u",
                     s_app_state.active_page + 1, H1OS_NUM_SCREENS);
            update_active_display();
        }
    }
}

/* =========================================================================
 * Application Lifecycle Handlers
 * ========================================================================= */
static void app_on_boot(void *user_data)
{
    ESP_LOGI(TAG, "Lifecycle: BOOT initialized");
    s_app_state.cycle_counter = 1;
    s_app_state.boot_epoch_sec = (uint32_t)time(NULL);

    screen_base_set_awake_badge(true);
    // Probe MicroSD card asynchronously on initial cold boot
    sub_sdcard_mount_async();
    // Gentle status LED heartbeat breathing during active interactive session
    hal_led_start_breathing(2000);
    update_active_display();
}

static void app_on_wake(const h1os_wake_context_t *ctx, void *user_data)
{
    s_app_state.cycle_counter++;
    time_t now = time(NULL);
    if (s_app_state.boot_epoch_sec > 0 && now >= (time_t)s_app_state.boot_epoch_sec) {
        s_app_state.total_uptime_sec = (uint32_t)(now - s_app_state.boot_epoch_sec);
    }
    ESP_LOGI(TAG, "Lifecycle: WAKE #%lu (Causes bitmask: 0x%08lx, ButtonWake: %d)",
             (unsigned long)s_app_state.cycle_counter, (unsigned long)ctx->wakeup_causes, ctx->woke_from_button);

    if (ctx->woke_from_button) {
        /* First Click: Intercepted by ULP to wake Flow B; Flow B toggles awake badge */
        ESP_LOGI(TAG, "First click intercepted by ULP: Inverting awake status badge.");
        screen_base_set_awake_badge(true);
        sub_sdcard_mount_async();
        hal_led_start_breathing(2000);
    } else {
        /* Unattended external RTC countdown wake: Keep sleep badge */
        screen_base_set_awake_badge(false);
    }

    update_active_display();
}

static void app_on_pre_sleep(uint32_t sleep_sec, void *user_data)
{
    ESP_LOGI(TAG, "Lifecycle: PRE-SLEEP hook (Duration: %lu s)", (unsigned long)sleep_sec);
    screen_base_set_awake_badge(false);
    hal_led_stop_breathing();
    sub_sdcard_unmount();
}

static void app_on_shutdown(void *user_data)
{
    ESP_LOGI(TAG, "Lifecycle: SHUTDOWN hook executing");
    hal_led_stop_breathing();
    sub_sdcard_unmount();
}

static void app_on_splash(h1os_splash_type_t type, void *user_data)
{
    ESP_LOGI(TAG, "Lifecycle: SPLASH hook executing (Type %d)", (int)type);
    if (type == H1OS_SPLASH_BOOT) {
        h1os_lvgl_lock(100);
        lv_obj_t *scr = lv_screen_active();
        lv_obj_clean(scr);
        lv_obj_set_style_bg_color(scr, lv_color_white(), 0);

        lv_obj_t *img = lv_image_create(scr);
        lv_image_set_src(img, &humid1_cyber_wave);
        lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);

        lv_refr_now(NULL);
        h1os_lvgl_unlock();

        /* Hold splash graphic briefly so it is visible before primary UI transition */
        vTaskDelay(pdMS_TO_TICKS(2*1000));
    }
}

/* =========================================================================
 * Application Entry Point
 * ========================================================================= */
void app_main(void)
{
    h1os_lifecycle_t lifecycle = {
        .session = {
            .inactivity_timeout_sec = 30,
            .flow_a_period_sec      = 60,
            .flow_b_period_sec      = 300,
        },
        .presentation = {
            .chime_mask = (1 << H1OS_CHIME_BOOT) |
                          (1 << H1OS_CHIME_SHUTDOWN),

            .on_chime   = NULL,
            .on_splash  = app_on_splash,
            .volume_pct = 40,
        },
        .on_boot      = app_on_boot,
        .on_wake      = app_on_wake,
        .on_pre_sleep = app_on_pre_sleep,
        .on_shutdown  = app_on_shutdown,
        .user_data    = NULL,
    };

    h1os_start(&lifecycle);
}

