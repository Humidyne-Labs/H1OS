/**
 * @file hal_types.h
 * @brief Layer 1: Base hardware constants, pinout mappings, and primitive types
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "driver/gpio.h"
#include "esp_err.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define HAL_PIN_POWER_HOLD GPIO_NUM_17
#define HAL_PIN_BATTERY_ADC GPIO_NUM_4
#define HAL_PIN_STATUS_LED GPIO_NUM_3

#define HAL_PIN_BUTTON_BOOT GPIO_NUM_0
#define HAL_PIN_BUTTON_POWER GPIO_NUM_18

#define HAL_PIN_I2C_SDA GPIO_NUM_47
#define HAL_PIN_I2C_SCL GPIO_NUM_48
#define HAL_PIN_RTC_INT GPIO_NUM_5

#define HAL_PIN_EPD_3V3_EN GPIO_NUM_6
#define HAL_PIN_EPD_BUSY GPIO_NUM_8
#define HAL_PIN_EPD_RST GPIO_NUM_9
#define HAL_PIN_EPD_DC GPIO_NUM_10
#define HAL_PIN_EPD_CS GPIO_NUM_11
#define HAL_PIN_EPD_SCK GPIO_NUM_12
#define HAL_PIN_EPD_MOSI GPIO_NUM_13

#define HAL_PIN_PA_EN GPIO_NUM_42
#define HAL_PIN_PA_CTRL GPIO_NUM_46
#define HAL_PIN_I2S_MCLK GPIO_NUM_14
#define HAL_PIN_I2S_SCLK GPIO_NUM_15
#define HAL_PIN_I2S_ASDOUT GPIO_NUM_16
#define HAL_PIN_I2S_LRCK GPIO_NUM_38
#define HAL_PIN_I2S_DSDIN GPIO_NUM_45

#define HAL_PIN_SD_CLK GPIO_NUM_39
#define HAL_PIN_SD_MISO GPIO_NUM_40
#define HAL_PIN_SD_MOSI GPIO_NUM_41

#define HAL_I2C_ADDR_ES8311 0x18
#define HAL_I2C_ADDR_PCF85063 0x51
#define HAL_I2C_ADDR_SHTC3 0x70

#define HAL_I2C_FREQ_HZ 400000

#define HAL_EPD_WIDTH_PX 200
#define HAL_EPD_HEIGHT_PX 200
#define HAL_EPD_DPI 188
#define HAL_EPD_FRAME_SIZE_BYTES ((HAL_EPD_WIDTH_PX * HAL_EPD_HEIGHT_PX) / 8)

#define HAL_PARTITION_EPD_FRAME "epd_frame"
#define HAL_PARTITION_STORAGE "storage"

typedef enum {
    HAL_BTN_NONE = 0,
    HAL_BTN_BOOT = (1 << 0),
    HAL_BTN_POWER = (1 << 1),
} hal_btn_mask_t;

typedef enum {
    H1OS_INIT_MODE_BOOT = 0,
    H1OS_INIT_MODE_WAKE = 1,
    H1OS_INIT_MODE_SUB_EXEC = 2,
} h1os_init_mode_t;

typedef enum {
    H1OS_SLEEP_MODE_LIGHT = 0,
    H1OS_SLEEP_MODE_DEEP = 1,
} h1os_sleep_mode_t;

#ifdef __cplusplus
}
#endif
