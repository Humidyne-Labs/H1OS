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
#include "h1os/h1os_lvgl.h"
#include "h1os/sub_audio.h"
#include "h1os/sub_sdcard.h"
#include "screens.h"

static const char *TAG = "h1os_demo";

/* Persistent Application State in RTC Slow Memory */
typedef struct {
    uint32_t boot_epoch_sec;
    uint32_t total_uptime_sec;
    uint32_t cycle_counter;
    uint8_t  active_page; // 0 = ENV HERO, 1 = PSYCHROMETRICS, 2 = HEALTH, 3 = DIAGNOSTICS
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
    h1os_telemetry_t telem = {0};
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

/* =========================================================================
 * Hardware Keypad Event Callback
 * ========================================================================= */
static void keypad_event_cb(lv_event_t *e)
{
    uint32_t key = lv_event_get_key(e);

    if (key == LV_KEY_RIGHT || key == LV_KEY_NEXT || key == LV_KEY_ENTER) {
        // BOOT Button (Forward Cycle)
        sub_audio_play_tone(2400, 15);
        s_app_state.active_page = (s_app_state.active_page + 1) % H1OS_NUM_SCREENS;
        ESP_LOGI(TAG, "Keypad forward: Navigating to page %u/%u",
                 s_app_state.active_page + 1, H1OS_NUM_SCREENS);
        update_active_display();
    } else if (key == LV_KEY_LEFT || key == LV_KEY_PREV) {
        // POWER Button Short-Click (Backward Cycle)
        sub_audio_play_tone(1800, 15);
        s_app_state.active_page = (s_app_state.active_page + H1OS_NUM_SCREENS - 1) % H1OS_NUM_SCREENS;
        ESP_LOGI(TAG, "Keypad reverse: Navigating to page %u/%u",
                 s_app_state.active_page + 1, H1OS_NUM_SCREENS);
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
