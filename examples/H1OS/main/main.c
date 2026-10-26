/**
 * @file main.c
 * @brief H1OS showcase application entry point and lifecycle orchestration
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "h1os/h1os.h"
#include "h1os/h1os_lvgl.h"
#include "h1os/h1os_version.h"
#include "h1os/hal_io.h"
#include "h1os/sub_audio.h"
#include "h1os/sub_power.h"
#include "h1os/sub_sdcard.h"
#include "humid1_cyber_wave.h"
#include "screens.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

static const char *TAG = "h1os_demo";

typedef struct {
    uint32_t boot_epoch_sec;
    uint32_t total_uptime_sec;
    uint32_t cycle_counter;
    uint8_t  active_page;
} app_rtc_persisted_state_t;

RTC_DATA_ATTR static app_rtc_persisted_state_t s_app_state = {0};

static void update_active_display(void);
static void keypad_event_cb(lv_event_t *e);

/**
 * @brief Updates active screen layout in the carousel based on current application state.
 *
 * @return Return value of type static void.
 */
static void update_active_display(void)
{
    static h1os_telemetry_t telem;
    h1os_get_telemetry(&telem);

    switch (s_app_state.active_page) {
    case H1OS_SCREEN_ENV_DASH:
        screen_env_dash_render(&telem, s_app_state.cycle_counter, keypad_event_cb);
        break;
    case H1OS_SCREEN_PSYCHROMETRICS:
        screen_psychrometrics_render(&telem, keypad_event_cb);
        break;
    case H1OS_SCREEN_THERMAL_NODES:
        screen_thermal_nodes_render(&telem, keypad_event_cb);
        break;
    case H1OS_SCREEN_SYSTEM_HEALTH:
        screen_system_health_render(&telem, keypad_event_cb);
        break;
    case H1OS_SCREEN_DIAGNOSTICS:
        screen_diagnostics_render(&telem, keypad_event_cb);
        break;
    default:
        s_app_state.active_page = H1OS_SCREEN_ENV_DASH;
        screen_env_dash_render(&telem, s_app_state.cycle_counter, keypad_event_cb);
        break;
    }
}

static bool s_is_shutting_down = false;

/**
 * @brief Handles keypad navigation input events for switching carousel screens.
 *
 * @param[in]    e               LVGL event descriptor.
 *
 * @return Return value of type static void.
 */
static void keypad_event_cb(lv_event_t *e)
{
    if (s_is_shutting_down) {
        return;
    }

    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_LONG_PRESSED) {
        ESP_LOGI(TAG, "Keypad: Native LVGL long-press (>=2.0s) detected! Executing shutdown...");
        s_is_shutting_down = true;
        h1os_shutdown();
        return;
    }

    if (code == LV_EVENT_SHORT_CLICKED) {
        const uint32_t tone_rev[] = {880, 50};
        sub_audio_play(SUB_AUDIO_TONE, tone_rev, sizeof(tone_rev));
        s_app_state.active_page = (s_app_state.active_page + H1OS_NUM_SCREENS - 1) % H1OS_NUM_SCREENS;
        ESP_LOGI(TAG, "Keypad reverse (POWER): Navigating to page %u/%u",
                        s_app_state.active_page + 1,
                        H1OS_NUM_SCREENS);
        update_active_display();
        return;
    }

    if (code == LV_EVENT_KEY) {
        uint32_t key = lv_event_get_key(e);
        if (key == 0 && lv_event_get_param(e) != NULL) {
            key = *(const uint32_t *)lv_event_get_param(e);
        }
        ESP_LOGI(TAG, "Keypad event received: LV_EVENT_KEY (key=0x%lx)", (unsigned long)key);

        if (key == LV_KEY_NEXT || key == LV_KEY_RIGHT) {
            const uint32_t tone_fwd[] = {1046, 50};
            sub_audio_play(SUB_AUDIO_TONE, tone_fwd, sizeof(tone_fwd));
            s_app_state.active_page = (s_app_state.active_page + 1) % H1OS_NUM_SCREENS;
            ESP_LOGI(TAG, "Keypad forward (BOOT): Navigating to page %u/%u",
                            s_app_state.active_page + 1,
                            H1OS_NUM_SCREENS);
            update_active_display();
            return;
        }
    }
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
    ESP_LOGI(TAG, "Lifecycle: BOOT initialized (H1OS %s, built %s %s, code 0x%08" PRIx32 ")",
                    h1os_version_get_string(),
                    h1os_version_get_build_date(),
                    h1os_version_get_build_time(),
                    h1os_version_get_code());

    s_app_state.cycle_counter  = 1;
    s_app_state.boot_epoch_sec = (uint32_t)time(NULL);

    screen_base_set_awake_badge(true);

    sub_sdcard_mount_async();

    hal_led_start_breathing(2000);
    update_active_display();
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
    (void)user_data;
    s_app_state.cycle_counter++;
    time_t now = time(NULL);
    if (s_app_state.boot_epoch_sec > 0 && now >= (time_t)s_app_state.boot_epoch_sec) {
        s_app_state.total_uptime_sec = (uint32_t)(now - s_app_state.boot_epoch_sec);
    }
    ESP_LOGI(TAG, "Lifecycle: WAKE #%lu (Causes bitmask: 0x%08lx, ButtonWake: %d)",
                    (unsigned long)s_app_state.cycle_counter,
                    (unsigned long)ctx->wakeup_causes,
                    ctx->woke_from_button);

    if (ctx->woke_from_button) {
        ESP_LOGI(TAG, "First click intercepted by ULP: Inverting awake status badge.");
        screen_base_set_awake_badge(true);
        sub_sdcard_mount_async();
        hal_led_start_breathing(2000);
    } else {
        screen_base_set_awake_badge(false);
    }

    update_active_display();
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
    ESP_LOGI(TAG, "Lifecycle: PRE-SLEEP hook (Duration: %lu s)", (unsigned long)sleep_sec);
    screen_base_set_awake_badge(false);
    hal_led_stop_breathing();
    sub_sdcard_unmount();
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
    ESP_LOGI(TAG, "Lifecycle: SHUTDOWN hook executing");
    hal_led_stop_breathing();
    sub_sdcard_unmount();
}

/**
 * @brief App on splash.
 *
 * @param[in]    type            Parameter type.
 * @param[in]    user_data       Parameter user_data.
 *
 * @return Return value of type static void.
 */
static void app_on_splash(h1os_splash_type_t type, void *user_data)
{
    (void)user_data;
    ESP_LOGI(TAG, "Lifecycle: SPLASH hook executing (Type %d)", (int)type);
    if (type == H1OS_SPLASH_BOOT) {
        lv_obj_t *scr = lv_screen_active();
        lv_obj_clean(scr);
        lv_obj_set_style_bg_color(scr, lv_color_white(), 0);

        lv_obj_t *img = lv_image_create(scr);
        lv_image_set_src(img, &humid1_cyber_wave);
        lv_obj_align(img, LV_ALIGN_CENTER, 0, 0);

        lv_refr_now(NULL);

        /* Release CPU 240 MHz lock during 2s splash viewing delay so CPU drops to 80 MHz */
        h1os_lvgl_unlock();
        vTaskDelay(pdMS_TO_TICKS(2 * 1000));
        h1os_lvgl_lock(1000);
    }
}

/**
 * @brief Application entry point.
 */
void app_main(void)
{
    h1os_lifecycle_t lifecycle = {
        .session =
            {
                .inactivity_timeout_sec = H1OS_DEFAULT_INACTIVITY_TIMEOUT_SEC,
                .clk_mode               = SYS_CLK_MODE_DYNAMIC,
                .flow_a_period_sec      = H1OS_DEFAULT_FLOW_A_PERIOD_SEC,
                .flow_b_period_sec      = H1OS_DEFAULT_FLOW_B_PERIOD_SEC,
            },

        .presentation =
            {
                .chime_mask = (1 << H1OS_CHIME_BOOT) | (1 << H1OS_CHIME_SHUTDOWN),

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

    esp_err_t err = h1os_start(&lifecycle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "h1os_start failed: %s", esp_err_to_name(err));
    }
}
