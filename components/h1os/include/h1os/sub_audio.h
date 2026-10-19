/**
 * @file sub_audio.h
 * @brief Layer 2: ES8311 codec and NS4168 audio power/standby driver
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "esp_err.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t sub_audio_init(void);

esp_err_t sub_audio_standby(void);

esp_err_t sub_audio_deinit(void);

esp_err_t sub_audio_wait_until_ready(uint32_t timeout_ms);

bool sub_audio_is_ready(void);

typedef enum {
    SUB_AUDIO_TONE = 0,
    SUB_AUDIO_CHIME,
    SUB_AUDIO_PCM,
} sub_audio_type_t;

esp_err_t sub_audio_play(sub_audio_type_t type, const void *data, size_t len);

bool sub_audio_is_busy(void);

esp_err_t sub_audio_wait_idle(uint32_t timeout_ms);

esp_err_t sub_audio_set_volume(uint8_t volume_pct);

uint8_t sub_audio_get_volume(void);

esp_err_t sub_audio_set_low_power_mode(bool enable);

bool sub_audio_get_low_power_mode(void);

#ifdef __cplusplus
}
#endif
