/**
 * @file h1os.h
 * @brief H1OS E-Class Environmental Telemetry OS master public API
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "esp_err.h"
#include "esp_sleep.h"
#include "esp_system.h"
#include "hal_types.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "h1os_version.h"

typedef struct {
    esp_reset_reason_t reset_reason;
    uint32_t wakeup_causes;
    uint32_t boot_count;
    uint32_t deep_sleep_count;
    bool woke_from_button;
    uint8_t wake_button;
    uint32_t sleep_duration_sec;
    void *user_data;
} h1os_wake_context_t;

typedef enum { H1OS_SPLASH_BOOT = 0, H1OS_SPLASH_SLEEP, H1OS_SPLASH_SHUTDOWN, H1OS_SPLASH_MAX } h1os_splash_type_t;

typedef enum {
    H1OS_CHIME_BOOT = 0,
    H1OS_CHIME_SLEEP,
    H1OS_CHIME_SHUTDOWN,
    H1OS_CHIME_ALARM,
    H1OS_CHIME_MAX
} h1os_chime_type_t;

typedef void (*h1os_boot_cb_t)(void *user_data);
typedef void (*h1os_wake_cb_t)(const h1os_wake_context_t *ctx, void *user_data);
typedef void (*h1os_pre_sleep_cb_t)(uint32_t sleep_sec, void *user_data);
typedef void (*h1os_shutdown_cb_t)(void *user_data);
typedef void (*h1os_splash_cb_t)(h1os_splash_type_t type, void *user_data);
typedef void (*h1os_chime_cb_t)(h1os_chime_type_t type, void *user_data);

typedef struct {
    h1os_boot_cb_t on_boot;
    h1os_wake_cb_t on_wake;
    h1os_pre_sleep_cb_t on_pre_sleep;
    h1os_shutdown_cb_t on_shutdown;

    struct {
        h1os_splash_cb_t on_splash;
        h1os_chime_cb_t on_chime;
        uint8_t chime_mask;
        uint8_t volume_pct;
    } presentation;

    struct {
        uint32_t inactivity_timeout_sec;
        bool enable_dfs_80mhz;
        uint32_t flow_a_period_sec;
        uint32_t flow_b_period_sec;
    } session;

    void *user_data;
} h1os_lifecycle_t;

typedef struct {
    float ambient_temp_c;
    float ambient_temp_f;
    float ambient_rh_pct;
    float dew_point_c;
    float dew_point_f;
    float absolute_humidity_g;

    float window_low_c;
    float window_high_c;
    float window_avg_shtc3_c;
    float window_avg_die_c;
    float temp_historical_c;
    float rh_historical_pct;

    float raw_shtc3_temp_c;
    float mcu_die_temp_c;
    float epd_glass_temp_c;
    float trinode_temp_c;
    float trinode_delta_c;
    uint8_t trinode_confidence_pct;

    bool is_thermally_settled;
    uint16_t valid_trend;
    uint32_t sample_count;
    uint16_t battery_mv;
    uint8_t battery_percent;
    bool is_usb_powered;
} h1os_telemetry_t;

static inline const char *h1os_get_version(void)
{
    return h1os_version_get_string();
}

esp_err_t h1os_start(const h1os_lifecycle_t *config);

esp_err_t h1os_set_volume(uint8_t volume_pct);

esp_err_t h1os_get_telemetry(h1os_telemetry_t *out_telemetry);

esp_err_t h1os_sleep(uint32_t sleep_sec);

void h1os_reset_session_timer(void);

bool h1os_is_session_active(void);

void h1os_shutdown(void);

void h1os_shutdown_for_storage(void);

#ifdef __cplusplus
}
#endif
