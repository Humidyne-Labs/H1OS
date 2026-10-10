/**
 * @file main.c
 * @brief Standalone Reference Example for Declarative Splash Screens & Audio Chimes
 *
 * Demonstrates declarative UI splash screens and audio chime configuration
 * passed directly through bsp_app_lifecycle_t to bsp_app_start().
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_err.h"
#include "bsp/bsp.h"

static const char *TAG = "splash_example";

static void on_boot_splash_cb(bsp_splash_type_t type, void *user_data)
{
    ESP_LOGI(TAG, "[UI] >>> Boot Splash Handler Executed! (Type: %d, Context: %s)",
             (int)type, (const char *)user_data);
}

static void on_sleep_splash_cb(bsp_splash_type_t type, void *user_data)
{
    ESP_LOGI(TAG, "[UI] >>> Pre-Sleep Splash Handler Executed! (Type: %d, Context: %s)",
             (int)type, (const char *)user_data);
}

static void on_custom_chime_cb(bsp_chime_type_t type, void *user_data)
{
    ESP_LOGI(TAG, "[AUDIO] >>> Custom Chime Dispatcher: Event %d", (int)type);
}

static void on_boot_cb(void *user_data)
{
    ESP_LOGI(TAG, "Lifecycle: on_boot reached. Boot splash has already fired!");

    // Test manual trigger of a notification chime
    ESP_LOGI(TAG, "Triggering notification chime via bsp_trigger_chime()...");
    bsp_trigger_chime(BSP_CHIME_NOTIFY);

    // Test manual trigger of sleep splash
    ESP_LOGI(TAG, "Triggering sleep splash via bsp_trigger_splash()...");
    bsp_trigger_splash(BSP_SPLASH_SLEEP);
}

void app_main(void)
{
    ESP_LOGI(TAG, "Starting Declarative Splash & Chime Lifecycle Example...");

    bsp_app_lifecycle_t lifecycle = {
        .on_boot            = on_boot_cb,
        .on_boot_splash     = on_boot_splash_cb,
        .on_sleep_splash    = on_sleep_splash_cb,
        .on_chime           = on_custom_chime_cb,
        .default_chime_mask = BSP_CHIME_MASK_BOOT | BSP_CHIME_MASK_SLEEP | BSP_CHIME_MASK_NOTIFY,
        .user_data          = (void *)"AppContext",
    };

    ESP_ERROR_CHECK(bsp_app_start(&lifecycle));

    ESP_LOGI(TAG, "Declarative Splash & Chime Lifecycle Example Complete.");
}