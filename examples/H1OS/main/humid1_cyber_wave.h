/**
 * @file humid1_cyber_wave.h
 * @brief HUMID1 cyber-wave EPD boot graphic descriptor
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HUMID1_CYBER_WAVE_WIDTH  200  /**< Asset width in physical pixels. */
#define HUMID1_CYBER_WAVE_HEIGHT 200  /**< Asset height in physical pixels. */
#define HUMID1_CYBER_WAVE_BYTES  5000 /**< Packed 1-bit binary asset size in bytes. */

/**
 * @brief LVGL 1-bit image descriptor for the HUMID1 cyber-wave boot animation.
 */
LV_IMAGE_DECLARE(humid1_cyber_wave);

#ifdef __cplusplus
}
#endif
