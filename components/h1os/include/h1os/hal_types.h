/**
 * @file hal_types.h
 * @brief Layer 1 HAL Base Types, Physical Pin Mappings, and Constants
 *
 * Hardware Target: Waveshare ESP32-S3 ePaper 1.54" V2 (ESP32-S3-PICO-1-N8R8)
 *
 * Invariant Rule: Contains ZERO application state, ZERO math logic, and ZERO power policy.
 * All layers include down to hal_types.h for primitive types.
 *
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

/* =========================================================================
 * 1. Physical Hardware Pin Mappings (Waveshare V2 Truth)
 * ========================================================================= */

// Power Latch & Battery
#define HAL_PIN_POWER_HOLD GPIO_NUM_17  ///< Master LDO Power Latch (BAT_CTRL): Active HIGH
#define HAL_PIN_BATTERY_ADC GPIO_NUM_4  ///< Battery Voltage Sensing: ADC1_CHANNEL_3 (1:2 divider)
#define HAL_PIN_STATUS_LED GPIO_NUM_3  ///< User LED: Open-Drain, Active LOW (0 = ON, 1 = OFF)

// Tactile Buttons
#define HAL_PIN_BUTTON_BOOT GPIO_NUM_0  ///< Hardware BOOT0 Key: Active LOW (external 10k pullup on PCB)
#define HAL_PIN_BUTTON_POWER GPIO_NUM_18  ///< Hardware BAT_KEY: Active LOW (external 10k pullup on PCB)

// Shared I2C0 Bus (External 4.7kΩ pull-ups on PCB)
#define HAL_PIN_I2C_SDA GPIO_NUM_47  ///< Shared I2C Serial Data (SHTC3, PCF85063, ES8311)
#define HAL_PIN_I2C_SCL GPIO_NUM_48  ///< Shared I2C Serial Clock
#define HAL_PIN_RTC_INT GPIO_NUM_5  ///< PCF85063A INT: Open-Drain (internal pullup mandatory)

// SSD1681 1.54" 200x200 Mono E-Paper Display (SPI2 Bus & Rail Gate)
#define HAL_PIN_EPD_3V3_EN GPIO_NUM_6  ///< EPD 3.3V Rail Gate: Active LOW (0 = Rail ON)
#define HAL_PIN_EPD_BUSY GPIO_NUM_8  ///< Display Busy Line: Active HIGH (1 = Busy, 0 = Idle)
#define HAL_PIN_EPD_RST GPIO_NUM_9  ///< Display Hardware Reset: Active LOW
#define HAL_PIN_EPD_DC GPIO_NUM_10  ///< Display Data / Command: 0 = Cmd, 1 = Data
#define HAL_PIN_EPD_CS GPIO_NUM_11  ///< Display SPI Chip Select: Active LOW
#define HAL_PIN_EPD_SCK GPIO_NUM_12  ///< Display SPI Serial Clock (up to 20MHz)
#define HAL_PIN_EPD_MOSI GPIO_NUM_13  ///< Display SPI Master Out Slave In

// ES8311 I2S Audio Codec & NS4168 Class-D Amp
#define HAL_PIN_PA_EN GPIO_NUM_42  ///< Amp Power Gate: Active LOW (1 = Power Cut, 0 = ON)
#define HAL_PIN_PA_CTRL GPIO_NUM_46  ///< Amp Standby/Mute: Active HIGH (0 = Mute, 1 = Enable)
#define HAL_PIN_I2S_MCLK GPIO_NUM_14  ///< Master Clock (256 * Fs)
#define HAL_PIN_I2S_SCLK GPIO_NUM_15  ///< Bit / Serial Clock
#define HAL_PIN_I2S_ASDOUT GPIO_NUM_16  ///< Codec Audio Out to ESP32 (DIN)
#define HAL_PIN_I2S_LRCK GPIO_NUM_38  ///< Word Select / Frame Sync (WS)
#define HAL_PIN_I2S_DSDIN GPIO_NUM_45  ///< ESP32 Audio Out to Codec (DOUT)

// MicroSD Card Slot (SPI / SDMMC 1-Bit)
#define HAL_PIN_SD_CLK GPIO_NUM_39  ///< MicroSD Clock
#define HAL_PIN_SD_MISO GPIO_NUM_40  ///< MicroSD MISO / D0
#define HAL_PIN_SD_MOSI GPIO_NUM_41  ///< MicroSD MOSI / CMD

/* =========================================================================
 * 2. I2C Bus Addresses & Target Speeds
 * ========================================================================= */
#define HAL_I2C_ADDR_ES8311 0x18  ///< Everest Semi Audio Codec
#define HAL_I2C_ADDR_PCF85063 0x51  ///< NXP Calendar RTC
#define HAL_I2C_ADDR_SHTC3 0x70  ///< Sensirion Temp / Humidity Sensor

#define HAL_I2C_FREQ_HZ 400000  ///< Fast-mode 400 kHz

/* =========================================================================
 * 3. Display Geometry & Partition Constants
 * ========================================================================= */
#define HAL_EPD_WIDTH_PX 200
#define HAL_EPD_HEIGHT_PX 200
#define HAL_EPD_DPI 188
#define HAL_EPD_FRAME_SIZE_BYTES ((HAL_EPD_WIDTH_PX * HAL_EPD_HEIGHT_PX) / 8)  // 5000 Bytes

#define HAL_PARTITION_EPD_FRAME "epd_frame"  ///< 16KB dedicated SPI flash partition
#define HAL_PARTITION_STORAGE "storage"  ///< SPIFFS / LittleFS partition

/* =========================================================================
 * 4. Common Return Codes & Bitmasks
 * ========================================================================= */
typedef enum {
    HAL_BTN_NONE = 0,
    HAL_BTN_BOOT = (1 << 0),
    HAL_BTN_POWER = (1 << 1),
} hal_btn_mask_t;

/**
 * @brief Initialization Modes for Dynamic Hardware Configuration
 */
typedef enum {
    H1OS_INIT_MODE_BOOT = 0,  ///< Boot initialization: all hardware subsystems & LVGL initialized
    H1OS_INIT_MODE_WAKE = 1,  ///< Wake initialization: fast display refresh retaining existing framebuffers
    H1OS_INIT_MODE_SUB_EXEC = 2,  ///< Sub-execution initialization: scaled-back runtime (I2C + sensor only)
} h1os_init_mode_t;

/**
 * @brief Sleep Execution Modes
 */
typedef enum {
    H1OS_SLEEP_MODE_LIGHT = 0,  ///< Light sleep (RAM preserved, clock gated)
    H1OS_SLEEP_MODE_DEEP = 1,  ///< Deep sleep (Power down, RTC slow memory preserved)
} h1os_sleep_mode_t;

#ifdef __cplusplus
}
#endif
