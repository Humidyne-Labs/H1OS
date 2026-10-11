/**
 * @file h1os_lifecycle.c
 * @brief Layer 4: Declarative Application Lifecycle Engine Implementation
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "esp_sleep.h"
#include "hal_io.h"
#include "sub_nvs.h"
#include "orch_flow.h"
#include "h1os_lvgl.h"
#include "h1os.h"

static const char *TAG = "h1os_lifecycle";
static h1os_lifecycle_t s_app_lifecycle = {0};

esp_err_t h1os_start(const h1os_lifecycle_t *config)
{
    if (config != NULL) {
        s_app_lifecycle = *config;
    }

    ESP_LOGI(TAG, "Booting %s (%s) Version %s", H1OS_NAME, H1OS_SUBTITLE, H1OS_VERSION_STRING);

    // 1. Initialize Base Hardware I/O & Release Boot Pad Holds
    hal_io_early_init();

    // 2. Initialize Persistent Storage Subsystem
    sub_nvs_init();

    // 3. Inspect Flow Arbiter (Flow A Wake Stub vs Flow B Interactive UI)
    orch_flow_type_t flow = orch_flow_determine_wakeup();

    if (flow == ORCH_FLOW_A_SPRINT) {
        ESP_LOGI(TAG, "Executing Flow A Sensor Sprint...");
        orch_flow_execute_sub_sprint();
        // Returns immediately to sleep inside stub
        return ESP_OK;
    }

    // 4. Flow B Interactive UI Boot
    ESP_LOGI(TAG, "Launching Flow B Main Session...");
    h1os_lvgl_init();

    if (s_app_lifecycle.on_boot && flow == ORCH_FLOW_COLD_BOOT) {
        s_app_lifecycle.on_boot(s_app_lifecycle.user_data);
    } else if (s_app_lifecycle.on_wake) {
        h1os_wake_context_t ctx = {
            .reset_reason = esp_reset_reason(),
            .wake_cause = esp_sleep_get_wakeup_cause(),
            .user_data = s_app_lifecycle.user_data
        };
        s_app_lifecycle.on_wake(&ctx, s_app_lifecycle.user_data);
    }

    // 5. Start LVGL interactive render loop
    h1os_lvgl_start(5, 1);

    return ESP_OK;
}

esp_err_t h1os_get_telemetry(h1os_telemetry_t *out_telemetry)
{
    if (!out_telemetry) return ESP_ERR_INVALID_ARG;
    memset(out_telemetry, 0, sizeof(h1os_telemetry_t));

    float t = 0.0f, rh = 0.0f, dew = 0.0f;
    esp_err_t ret = orch_flow_query_telemetry(&t, &rh, &dew);
    if (ret == ESP_OK) {
        out_telemetry->ambient_temp_c = t;
        out_telemetry->ambient_temp_f = (t * 9.0f / 5.0f) + 32.0f;
        out_telemetry->ambient_rh_pct = rh;
        out_telemetry->dew_point_c    = dew;
        out_telemetry->dew_point_f    = (dew * 9.0f / 5.0f) + 32.0f;
        out_telemetry->is_thermally_settled = !orch_flow_is_thermal_lockout();
    }
    return ret;
}

esp_err_t h1os_sleep(uint32_t sleep_sec)
{
    ESP_LOGI(TAG, "Entering coordinated stand-down sequence (%lu sec)...", (unsigned long)sleep_sec);
    if (s_app_lifecycle.on_pre_sleep) {
        s_app_lifecycle.on_pre_sleep(sleep_sec, s_app_lifecycle.user_data);
    }
    return orch_flow_stand_down_and_sleep(sleep_sec);
}

void h1os_shutdown(void)
{
    ESP_LOGI(TAG, "Executing system shutdown and battery power cut...");
    if (s_app_lifecycle.on_shutdown) {
        s_app_lifecycle.on_shutdown(s_app_lifecycle.user_data);
    }
    // Release battery LDO power latch (GPIO 17 driven LOW, hold disabled)
    hal_io_lock_power_latch(false);
}
