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
 * @brief Play synthesized audio chime/tone.
 *
 * @param[in] frequency_hz Frequency in Hertz (e.g. 1000 for 1 kHz).
 * @param[in] duration_ms  Duration in milliseconds.
 * @return ESP_OK on success.
 */
esp_err_t sub_audio_play_tone(uint32_t frequency_hz, uint32_t duration_ms);

/**
 * @brief Play standard H1OS acoustic presentation chime.
 *
 * @param[in] type Chime type (BOOT, WAKE, SLEEP, SHUTDOWN, ALARM).
 * @return ESP_OK on success.
 */
esp_err_t sub_audio_play_chime(uint8_t type);

#ifdef __cplusplus
}
#endif
