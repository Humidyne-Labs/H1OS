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
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Acoustic payload type for consolidated sub_audio_play dispatch.
 */
typedef enum {
    SUB_AUDIO_TONE = 0, /**< Synthesized tone pattern (freq_hz, duration_ms). */
    SUB_AUDIO_CHIME,    /**< Standard acoustic presentation chime pattern.    */
    SUB_AUDIO_PCM       /**< Raw 16-bit signed Mono PCM buffer stream.        */
} sub_audio_type_t;

/**
 * @brief Initialize ES8311 audio codec and NS4168 amplifier hardware.
 *
 * @param[in] volume_pct Output volume (0 = Mute, 100 = 0 dB Max).
 * 
 * Configures I2S master bus (16-bit 16kHz mono), performs codec register initialization
 * over shared I2C, and sets up the asynchronous FreeRTOS audio worker task.
 *
 * @return ESP_OK on success, or driver error code.
 */
esp_err_t sub_audio_init(uint8_t volume_pct);

/**
 * @brief Put audio subsystem into low-power hardware standby.
 *
 * Mutes amplifier (GPIO 46 LOW), disables class-D power gate (GPIO 42 HIGH),
 * and enters software power-down on ES8311.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_audio_standby(void);

/**
 * @brief Deinitialize audio subsystem and release I2S and FreeRTOS resources.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_audio_deinit(void);

/**
 * @brief Block until audio subsystem initialization completes.
 *
 * @param[in] timeout_ms Maximum time to wait in milliseconds.
 *
 * @return ESP_OK if audio worker is ready, ESP_ERR_TIMEOUT otherwise.
 */
esp_err_t sub_audio_wait_until_ready(uint32_t timeout_ms);

/**
 * @brief Check if audio subsystem is initialized and ready to accept commands.
 *
 * @return True if audio worker is operational, false otherwise.
 */
bool sub_audio_is_ready(void);

/**
 * @brief Dispatch audio playback command to background worker task.
 *
 * @param[in] type Acoustic payload type (SUB_AUDIO_TONE, SUB_AUDIO_CHIME, SUB_AUDIO_PCM).
 * @param[in] data Pointer to payload data buffer or parameters struct.
 * @param[in] len  Length of data payload in bytes.
 *
 * @return ESP_OK if command was queued to worker, or error code.
 */
esp_err_t sub_audio_play(sub_audio_type_t type, const void *data, size_t len);

/**
 * @brief Check if audio playback is actively streaming.
 *
 * @return True if amplifier is active and audio samples are playing.
 */
bool sub_audio_is_busy(void);

/**
 * @brief Block until all pending audio commands finish playback and amplifier enters standby.
 *
 * @param[in] timeout_ms Maximum wait time in milliseconds.
 *
 * @return ESP_OK when playback is idle, ESP_ERR_TIMEOUT on expiration.
 */
esp_err_t sub_audio_wait_idle(uint32_t timeout_ms);

/**
 * @brief Set master audio volume percentage (0..100%).
 *
 * @param[in] volume_pct Output volume (0 = Mute, 100 = 0 dB Max).
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_audio_set_volume(uint8_t volume_pct);

/**
 * @brief Retrieve current audio volume percentage.
 *
 * @return Current volume level (0..100%).
 */
uint8_t sub_audio_get_volume(void);

/**
 * @brief Enable or disable aggressive codec low-power mode.
 *
 * @param[in] enable True to enable analog power-down when idle.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_audio_set_low_power_mode(bool enable);

/**
 * @brief Query whether codec low-power mode is enabled.
 *
 * @return True if low-power mode is active.
 */
bool sub_audio_get_low_power_mode(void);

#ifdef __cplusplus
}
#endif
