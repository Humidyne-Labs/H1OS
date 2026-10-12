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

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

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
 * @brief Play raw 16-bit signed PCM audio samples synchronously.
 *
 * @param[in] samples Pointer to 16-bit signed Mono PCM samples.
 * @param[in] sample_count Number of int16_t samples.
 * @param[in] sample_rate_hz Sample rate in Hz (default: 16000).
 * @return ESP_OK on success.
 */
esp_err_t sub_audio_play_pcm(const int16_t *samples, size_t sample_count, uint32_t sample_rate_hz);

/**
 * @brief Play raw 16-bit signed PCM audio samples asynchronously in background worker task.
 * Note: Caller must ensure the buffer remains valid until playback finishes (e.g., const/static buffer).
 *
 * @param[in] samples Pointer to 16-bit signed Mono PCM samples.
 * @param[in] sample_count Number of int16_t samples.
 * @param[in] sample_rate_hz Sample rate in Hz (default: 16000).
 * @return ESP_OK on success, ESP_ERR_NO_MEM / ESP_ERR_TIMEOUT if queue full.
 */
esp_err_t sub_audio_play_pcm_async(const int16_t *samples, size_t sample_count, uint32_t sample_rate_hz);

/**
 * @brief Play synthesized audio chime/tone synchronously.
 *
 * @param[in] frequency_hz Frequency in Hertz (e.g. 1000 for 1 kHz).
 * @param[in] duration_ms  Duration in milliseconds.
 * @return ESP_OK on success.
 */
esp_err_t sub_audio_play_tone(uint32_t frequency_hz, uint32_t duration_ms);

/**
 * @brief Play synthesized audio chime/tone asynchronously via worker task.
 *
 * @param[in] frequency_hz Frequency in Hertz (e.g. 1000 for 1 kHz).
 * @param[in] duration_ms  Duration in milliseconds.
 * @return ESP_OK on success.
 */
esp_err_t sub_audio_play_tone_async(uint32_t frequency_hz, uint32_t duration_ms);

/**
 * @brief Play standard H1OS acoustic presentation chime synchronously.
 *
 * @param[in] type Chime type (BOOT, WAKE, SLEEP, SHUTDOWN, ALARM).
 * @return ESP_OK on success.
 */
esp_err_t sub_audio_play_chime(uint8_t type);

/**
 * @brief Play standard H1OS acoustic presentation chime asynchronously.
 *
 * @param[in] type Chime type (BOOT, WAKE, SLEEP, SHUTDOWN, ALARM).
 * @return ESP_OK on success.
 */
esp_err_t sub_audio_play_chime_async(uint8_t type);

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

#ifdef __cplusplus
}
#endif
