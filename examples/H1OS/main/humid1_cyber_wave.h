/**
 * @file humid1_cyber_wave.h
 * @brief HUMID1 Cyber-Wave EPD Boot Graphic LVGL Image Descriptor
 *
 * Dimensions: 200 x 200 pixels
 * Format: 1-bit monochrome (LV_COLOR_FORMAT_I1)
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HUMID1_CYBER_WAVE_WIDTH 200
#define HUMID1_CYBER_WAVE_HEIGHT 200
#define HUMID1_CYBER_WAVE_BYTES 5000

LV_IMAGE_DECLARE(humid1_cyber_wave);

#ifdef __cplusplus
}
#endif
