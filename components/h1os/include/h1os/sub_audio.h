/**
 * @file sub_audio.h
 * @brief Layer 2: ES8311 Codec & NS4168 Power/Standby Audio Driver
 *
 * Provides tone playback and software standby power-down (Reg 0x0D @ <1.0 µA).
 * Crucially keeps ES8311 in low-power standby rather than cutting 3.3V power,
 * preventing ESD diode forward-bias from clamping the shared I2C bus to ~0.7V.
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "esp_err.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize ES8311 codec and NS4168 amplifier.
 * Configures I2S audio bus and sets codec to active run mode.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_audio_init(void);

/**
 * @brief Put ES8311 codec into ultra-low-power software standby (Reg 0x0D = 0x00 @ <1.0 µA)
 * and pull NS4168 PA_CTRL LOW.
 * Keeps power rails on so I2C bus is NOT clamped by unpowered chip protection diodes.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_audio_standby(void);

/**
 * @brief Teardown audio subsystem, stop background worker task, and delete I2S channel.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_audio_deinit(void);

/**
 * @brief Poll ES8311 over I2C to confirm Chip ID (0xFD=0x83, 0xFE=0x11)
 * and wait for Chip State Machine (Reg 0xFC bits 6:4) to exit power-down state S0.
 *
 * @param timeout_ms Maximum wait time in milliseconds.
 * @return ESP_OK if codec is verified and in active CSM state, or error.
 */
esp_err_t sub_audio_wait_until_ready(uint32_t timeout_ms);

/**
 * @brief Quick status check of whether ES8311 codec is ready.
 *
 * @return true if communication and active CSM state verified.
 */
bool sub_audio_is_ready(void);

/**
 * @brief Acoustic payload type for consolidated sub_audio_play dispatch.
 */
typedef enum {
    SUB_AUDIO_TONE = 0, /**< Synthesized square/sine tone (params: uint32_t frequency_hz, uint32_t
                           duration_ms) */
    SUB_AUDIO_CHIME,    /**< Standard acoustic presentation chime (params: uint8_t chime_type) */
    SUB_AUDIO_PCM, /**< Raw 16-bit Mono PCM buffer (params: const int16_t *samples, count = len) */
} sub_audio_type_t;

/**
 * @brief Unified asynchronous audio playback dispatcher.
 *
 * Enqueues the requested audio command into the background audio worker task.
 *
 * @param[in] type Type of playback: SUB_AUDIO_TONE, SUB_AUDIO_CHIME, or SUB_AUDIO_PCM.
 * @param[in] data Pointer to payload data:
 *                 - SUB_AUDIO_TONE: const uint32_t params[2] = { frequency_hz, duration_ms }
 *                 - SUB_AUDIO_CHIME: const uint8_t *chime_type
 *                 - SUB_AUDIO_PCM: const int16_t *samples
 * @param[in] len  Length / sample count:
 *                 - SUB_AUDIO_TONE: 2 (parameter count) or sizeof(params)
 *                 - SUB_AUDIO_CHIME: 1 (byte count)
 *                 - SUB_AUDIO_PCM: sample count (number of int16_t samples)
 * @return ESP_OK on success, ESP_ERR_TIMEOUT if queue is full, or ESP_ERR_INVALID_ARG.
 */
esp_err_t sub_audio_play(sub_audio_type_t type, const void *data, size_t len);

/**
 * @brief Check if audio playback is currently active or queue has pending items.
 *
 * @return true if playing or queued, false if idle in standby.
 */
bool sub_audio_is_busy(void);

/**
 * @brief Wait until background audio worker completes all playback and enters standby.
 *
 * @param timeout_ms Maximum time to wait in milliseconds.
 * @return ESP_OK if idle, ESP_ERR_TIMEOUT if still active.
 */
esp_err_t sub_audio_wait_idle(uint32_t timeout_ms);

/**
 * @brief Set ES8311 DAC output volume percentage (0% = Mute, 100% = 0 dB full-scale).
 * Persists across standby/wake cycles.
 *
 * @param[in] volume_pct Volume percentage (0 - 100).
 * @return ESP_OK on success.
 */
esp_err_t sub_audio_set_volume(uint8_t volume_pct);

/**
 * @brief Get currently configured output volume percentage (0 - 100).
 *
 * @return Current volume percentage.
 */
uint8_t sub_audio_get_volume(void);

/**
 * @brief Configure ES8311 DAC power mode (Low-Power vs Normal).
 *
 * In low-power mode (default upon init), ES8311 operates with LPDAC enabled (Reg 0x0F bit 7 = 1),
 * significantly reducing active DAC bias current. Normal mode provides standard bias.
 *
 * @param[in] enable true for Low-Power Mode (default), false for Normal Power Mode.
 * @return ESP_OK on success.
 */
esp_err_t sub_audio_set_low_power_mode(bool enable);

/**
 * @brief Query whether audio subsystem is in Low-Power Mode.
 *
 * @return true if Low-Power Mode is active, false if Normal Power Mode.
 */
bool sub_audio_get_low_power_mode(void);

#ifdef __cplusplus
}
#endif
