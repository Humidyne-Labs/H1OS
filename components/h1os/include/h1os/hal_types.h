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

// clang-format off
/* Power & Sensing Rails */
#define HAL_PIN_POWER_HOLD     GPIO_NUM_17 /**< Master LDO Power Latch (BAT_CTRL): Active HIGH.               */
#define HAL_PIN_BATTERY_ADC    GPIO_NUM_4  /**< Battery Voltage Sensing: ADC1_CHANNEL_3 (1:2 divider).        */
#define HAL_PIN_STATUS_LED     GPIO_NUM_3  /**< User LED: Open-Drain, Active LOW (0 = ON, 1 = OFF).           */

/* Input Buttons */
#define HAL_PIN_BUTTON_BOOT    GPIO_NUM_0  /**< Hardware BOOT0 Key: Active LOW (external 10k pullup on PCB).  */
#define HAL_PIN_BUTTON_POWER   GPIO_NUM_18 /**< Hardware BAT_KEY: Active LOW (external 10k pullup on PCB).    */

/* Shared I2C Master Bus */
#define HAL_PIN_I2C_SDA        GPIO_NUM_47 /**< Shared I2C Serial Data (SHTC3, PCF85063, ES8311).             */
#define HAL_PIN_I2C_SCL        GPIO_NUM_48 /**< Shared I2C Serial Clock.                                      */
#define HAL_PIN_RTC_INT        GPIO_NUM_5  /**< PCF85063A INT: Open-Drain (internal pullup mandatory).        */

/* Monochrome E-Paper Display (SSD1681) */
#define HAL_PIN_EPD_3V3_EN     GPIO_NUM_6  /**< EPD 3.3V Rail Gate: Active LOW (0 = Rail ON).                 */
#define HAL_PIN_EPD_BUSY       GPIO_NUM_8  /**< Display Busy Line: Active HIGH (1 = Busy, 0 = Idle).          */
#define HAL_PIN_EPD_RST        GPIO_NUM_9  /**< Display Hardware Reset: Active LOW.                           */
#define HAL_PIN_EPD_DC         GPIO_NUM_10 /**< Display Data / Command: 0 = Cmd, 1 = Data.                    */
#define HAL_PIN_EPD_CS         GPIO_NUM_11 /**< Display SPI Chip Select: Active LOW.                          */
#define HAL_PIN_EPD_SCK        GPIO_NUM_12 /**< Display SPI Serial Clock (up to 20MHz).                       */
#define HAL_PIN_EPD_MOSI       GPIO_NUM_13 /**< Display SPI Master Out Slave In.                              */

/* Audio Subsystem (ES8311 + NS4168) */
#define HAL_PIN_PA_EN          GPIO_NUM_42 /**< Amp Power Gate: Active LOW (1 = Power Cut, 0 = ON).           */
#define HAL_PIN_PA_CTRL        GPIO_NUM_46 /**< Amp Standby/Mute: Active HIGH (0 = Mute, 1 = Enable).         */
#define HAL_PIN_I2S_MCLK       GPIO_NUM_14 /**< Master Clock (256 * Fs).                                      */
#define HAL_PIN_I2S_SCLK       GPIO_NUM_15 /**< Bit / Serial Clock.                                           */
#define HAL_PIN_I2S_ASDOUT     GPIO_NUM_16 /**< Codec Audio Out to ESP32 (DIN).                               */
#define HAL_PIN_I2S_LRCK       GPIO_NUM_38 /**< Word Select / Frame Sync (WS).                                */
#define HAL_PIN_I2S_DSDIN      GPIO_NUM_45 /**< ESP32 Audio Out to Codec (DOUT).                              */

/* MicroSD Card (SDMMC 1-Bit Mode, external pullups, no CD pin wired) */
#define HAL_PIN_SD_CLK         GPIO_NUM_39 /**< MicroSD Clock.                                                */
#define HAL_PIN_SD_MISO        GPIO_NUM_40 /**< MicroSD MISO / D0.                                            */
#define HAL_PIN_SD_MOSI        GPIO_NUM_41 /**< MicroSD MOSI / CMD.                                           */

/* I2C Peripheral Addresses */
#define HAL_I2C_ADDR_ES8311    0x18        /**< Everest Semi Audio Codec 7-bit address.                       */
#define HAL_I2C_ADDR_PCF85063  0x51        /**< NXP Calendar RTC 7-bit address.                               */
#define HAL_I2C_ADDR_SHTC3     0x70        /**< Sensirion Temp / Humidity Sensor 7-bit address.               */

#define HAL_I2C_FREQ_HZ        400000      /**< Shared I2C bus fast-mode operating clock frequency (400 kHz). */

/* Display Geometry */
#define HAL_EPD_WIDTH_PX       200         /**< Display panel width in physical pixels.                       */
#define HAL_EPD_HEIGHT_PX      200         /**< Display panel height in physical pixels.                      */
#define HAL_EPD_DPI            188         /**< Display panel resolution in dots per inch.                    */

/**< Packed 1-bit frame buffer size (5000 bytes). */
#define HAL_EPD_FRAME_SIZE_BYTES ((HAL_EPD_WIDTH_PX * HAL_EPD_HEIGHT_PX) / 8)

/* Flash Partitions */
#define HAL_PARTITION_EPD_FRAME "epd_frame" /**< 16KB dedicated SPI flash partition for raw EPD frame.        */
#define HAL_PARTITION_STORAGE   "storage"   /**< SPIFFS / LittleFS non-volatile file storage partition.       */
// clang-format on

/**
 * @brief Pushbutton actuation bitmask identifiers.
 */
typedef enum {
    HAL_BTN_NONE  = 0,        /**< No buttons depressed.             */
    HAL_BTN_BOOT  = (1 << 0), /**< BOOT0 button depressed (GPIO 0).  */
    HAL_BTN_POWER = (1 << 1)  /**< POWER button depressed (GPIO 18). */
} hal_btn_mask_t;

/**
 * @brief Acoustic chime sound pattern types.
 */
typedef enum {
    H1OS_CHIME_BOOT = 0, /**< Ascending multi-tone power-on chime.   */
    H1OS_CHIME_SLEEP,    /**< Descending sleep preparation chime.    */
    H1OS_CHIME_SHUTDOWN, /**< Dual-tone shutdown confirmation chime. */
    H1OS_CHIME_ALARM,    /**< Repetitive alert chime pattern.        */
    H1OS_CHIME_MAX       /**< Maximum chime enum value.              */
} h1os_chime_type_t;

/**
 * @brief System CPU clock frequency scaling and power profile modes.
 */
typedef enum {
    SYS_CLK_MODE_DYNAMIC   = 0, /**< Dynamic Frequency Scaling: 80 MHz baseline, 240 MHz turbo bursts (Default). */
    SYS_CLK_MODE_FIXED_MAX = 1, /**< Fixed Maximum Clock: Locked to max frequency (240 MHz), DFS disabled.       */
    SYS_CLK_MODE_FIXED_MIN = 2  /**< Fixed Minimum Clock: Locked to base frequency (80 MHz), turbo disabled.     */
} sys_clk_mode_t;

#ifdef __cplusplus
}
#endif
