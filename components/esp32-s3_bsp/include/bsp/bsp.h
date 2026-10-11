/**
 * @file bsp.h
 * @brief Master Include Header for Waveshare ESP32-S3-ePaper-1.54 V2 BSP
 *
 * Umbrella header providing a consolidated, single-include point for all peripheral
 * drivers, hardware abstractions, error handling, versioning, and power management routines.
 *
 * Hardware Target:
 *  - Microcontroller: Espressif Systems ESP32-S3-PICO-1-N8R8
 *  - Target Board: Waveshare ESP32-S3 ePaper 1.54 V2
 *
 * @version 1.0.0
 * @attribution
 * - Architecture & Development: HUMIDYNE LABS / Humiditron
 * - AI Systems Co-Developer: Gemini (Google DeepMind)
 * - Hardware Target: Waveshare Electronics ESP32-S3 ePaper 1.54 V2
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BSP_H
#define BSP_H

#include "bsp/bsp_version.h"
#include "bsp/bsp_err.h"
#include "bsp/bsp_power.h"
#include "bsp/bsp_button.h"
#include "bsp/bsp_splash.h"
#include "bsp/bsp_sdcard.h"
#include "bsp/bsp_lvgl.h"
#include "bsp/bsp_nvs.h"
#include "bsp/bsp_wifi.h"
#include "bsp/bsp_time.h"
#include "bsp/bsp_prov.h"
#include "bsp/bsp_ota.h"
#if CONFIG_BSP_ENABLE_THINGSBOARD
#include "bsp/bsp_tb.h"
#endif

/* --- Clean-Slate 4-Layer Modular Architecture Headers --- */
#include "bsp/hal_types.h"
#include "bsp/hal_io.h"
#include "bsp/hal_i2c.h"
#include "bsp/hal_spi.h"
#include "bsp/hal_flash.h"
#include "bsp/sub_sensor.h"
#include "bsp/sub_rtc.h"
#include "bsp/sub_power.h"
#include "bsp/sub_audio.h"
#include "bsp/sub_display.h"
#include "bsp/orch_state.h"
#include "bsp/orch_math.h"
#include "bsp/orch_flow.h"
#include "bsp/orch_display_sync.h"
#include "bsp/orch_wake_stub.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Converted BSP EPD Font Macro
 */
#define MONTSERRAT_14 &bsp_font_montserrat_14_1bpp
#define MONTSERRAT_20 &bsp_font_montserrat_20_1bpp

/**
 * @brief Modular Hardware Initialization Configuration
 */
typedef struct {
    bool  init_power;    ///< Hold LDO power rail HIGH and calibrate ADC battery monitor (Default: true)
    bool  init_i2c;      ///< Initialize shared I2C bus at 400kHz with mutex protection (Default: true)
    bool  init_sensors;  ///< Initialize Sensirion SHTC3 environmental sensor (Default: true)
    bool  init_rtc;      ///< Initialize PCF85063A hardware real-time clock (Default: true)
    bool  init_buttons;  ///< Initialize debounced interrupt handlers for BOOT and POWER keys (Default: true)
    bool  init_audio;    ///< Initialize ES8311 I2S audio codec & NS4168 amp (Default: true)
    float audio_volume;  ///< Initial audio volume 0-100 (Default: 80.0)
    bool  init_sdcard;   ///< Mount MicroSD card over SDMMC FATFS (Default: false)
    bool  init_display;  ///< Initialize SSD1681 1.54" SPI e-Paper display (Default: true)
    bool  init_nvs;      ///< Initialize non-volatile flash storage (Default: true)
    bool  start_lvgl;    ///< Spawn LVGL v9 FreeRTOS render task pinned to Core 1 (Default: true)
} bsp_config_t;

/**
 * @brief Default Hardware Initialization Configuration Macro
 */
#define BSP_CONFIG_DEFAULT() { \
    .init_power   = true,      \
    .init_i2c     = true,      \
    .init_sensors = true,      \
    .init_rtc     = true,      \
    .init_buttons = true,      \
    .init_audio   = true,      \
    .audio_volume = 60.0f,     \
    .init_sdcard  = false,     \
    .init_display = true,      \
    .init_nvs     = true,      \
    .start_lvgl   = true       \
}

/**
 * @brief Comprehensive Board Initialization
 *
 * Applies default configuration, enables power rails, configures I2C, RTC, sensors,
 * buttons, display driver, and starts the LVGL v9 rendering task pinned to Core 1.
 *
 * @return esp_err_t ESP_OK on success
 * @details Memory ownership: none. Behavior: Blocking. Thread safety: no thread safety guarantees.
 */
esp_err_t bsp_board_init(void);

/**
 * @brief Dynamic Hardware Initialization by Mode (FULL, FAST)
 *
 * - BSP_INIT_MODE_FULL: Cold boot, full peripheral startup, display + LVGL.
 * - BSP_INIT_MODE_FAST: Wake boot, fast display ready without clear.
 *
 * @param[in] mode Target bsp_init_mode_t
 * @return esp_err_t ESP_OK on success
 * @details Memory ownership: none. Behavior: Blocking. Thread safety: no thread safety guarantees.
 */
esp_err_t bsp_init_mode(bsp_init_mode_t mode);

/**
 * @brief Custom Board Initialization
 *
 * @param[in] config Pointer to custom bsp_config_t struct
 * @return esp_err_t ESP_OK on success
 * @details Memory ownership: none. Behavior: Blocking. Thread safety: no thread safety guarantees.
 */
esp_err_t bsp_board_init_with_config(const bsp_config_t *config);

/**
 * @brief Initialize all GPIO output pins (power latch, audio PA, display power rail, LED)
 *
 * @return esp_err_t ESP_OK on success
 * @details Memory ownership: none. Behavior: Blocking. Thread safety: no thread safety guarantees.
 */
esp_err_t bsp_init_io(void);

/**
 * @brief Retrieve Unique Hardware Device ID string from MAC address (e.g. "ESP32S3-70041D3B")
 *
 * @param[out] buf Destination buffer
 * @param[in] max_len Buffer length
 * @return esp_err_t ESP_OK on success
 * @details Memory ownership: none. Behavior: Blocking. Thread safety: no thread safety guarantees.
 */
esp_err_t bsp_get_device_id(char *buf, size_t max_len);

/**
 * @brief Retrieve Human-Readable Device Name string (e.g. "HumidOS-1D3B")
 *
 * @param[out] buf Destination buffer
 * @param[in] max_len Buffer length
 * @return esp_err_t ESP_OK on success
 * @details Memory ownership: none. Behavior: Blocking. Thread safety: no thread safety guarantees.
 */
esp_err_t bsp_get_device_name(char *buf, size_t max_len);

/**
 * @brief Base57 character set excluding visually ambiguous characters (0, O, o, 1, l, I)
 */
#define BSP_CHARSET_UNAMBIGUOUS "abcdefghijkmnopqrstuvwxyzABCDEFGHJKLMNPQRSTUVWXYZ23456789"

/**
 * @brief Generate a cryptographically random, unambiguous key string (excluding 0, O, o, 1, l, I)
 *
 * @param[out] buf Destination buffer
 * @param[in] len Key length (excluding null terminator)
 * @param[in] charset Custom character set (or NULL for BSP_CHARSET_UNAMBIGUOUS)
 * @return esp_err_t ESP_OK on success
 * @details Memory ownership: none. Behavior: Blocking. Thread safety: no thread safety guarantees.
 */
esp_err_t bsp_generate_unambiguous_key(char *buf, size_t len, const char *charset);

/**
 * @brief Structured Wake Context passed to application on_wake callback
 */
typedef struct {
    esp_reset_reason_t       reset_reason;       ///< Reset reason (e.g. ESP_RST_DEEPSLEEP, ESP_RST_POWERON)
    esp_sleep_wakeup_cause_t wake_cause;         ///< Wakeup cause (e.g. EXT1, TIMER, GPIO)
    uint64_t                 ext1_wakeup_pins;   ///< GPIO mask of pins that triggered EXT1 wakeup
    bool                     woke_from_button;   ///< True if wake was triggered by BOOT or POWER button
    bsp_button_t             wake_button;        ///< Which button triggered wakeup (if button wake)
    bsp_init_mode_t          init_mode;          ///< Initialization profile executed (FULL, FAST, MIN)
    uint32_t                 sleep_duration_sec; ///< Configured sleep duration from previous cycle
    uint32_t                 boot_count;         ///< Monotonic system boot count
    uint32_t                 deep_sleep_count;   ///< Total deep sleep cycles
    uint32_t                 light_sleep_count;  ///< Total light sleep cycles
    uint8_t                  app_stage;          ///< Persistent application stage code (from RTC memory)
    void                     *user_data;         ///< User data pointer passed during lifecycle start
} bsp_wake_context_t;

/**
 * @brief UI Splash Screen Callback Signature
 * @param[in] type Splash event type
 * @param[in] user_data Custom application context pointer
 */
typedef void (*bsp_splash_cb_t)(bsp_splash_type_t type, void *user_data);

/**
 * @brief Audio Chime Callback Signature
 * @param[in] type Chime event type
 * @param[in] user_data Custom application context pointer
 */
typedef void (*bsp_chime_cb_t)(bsp_chime_type_t type, void *user_data);

/**
 * @brief Pre-execution callback executed at earliest boot phase before peripheral subsystem init
 * @param[in] btn_mask Bitmask of depressed buttons at boot time
 * @param[in] user_data Custom application context pointer
 */
typedef void (*bsp_pxe_cb_t)(bsp_button_mask_t btn_mask, void *user_data);

/**
 * @brief Callback executed on boot (POR, hardware reset, software restart)
 */
typedef void (*bsp_boot_cb_t)(void *user_data);
#define bsp_cold_boot_cb_t bsp_boot_cb_t

/**
 * @brief Callback executed on resume from sleep (Deep Sleep or Light Sleep)
 */
typedef void (*bsp_wake_cb_t)(const bsp_wake_context_t *ctx, void *user_data);

/**
 * @brief Callback executed right before entering sleep (for app cleanup / display badge)
 */
typedef void (*bsp_sleep_cb_t)(bsp_sleep_mode_t mode, uint32_t duration_sec, void *user_data);
#define bsp_before_sleep_cb_t bsp_sleep_cb_t

/**
 * @brief Callback executed immediately prior to system power off
 */
typedef void (*bsp_power_off_cb_t)(void *user_data);
#define bsp_shutdown_cb_t bsp_power_off_cb_t

/**
 * @brief Comprehensive Application Lifecycle Configuration
 */
typedef struct {
    /* Core Lifecycle Execution */
    bsp_pxe_cb_t          on_pxe;              ///< Handler for pre-execution boot checks (button holding)
    bsp_boot_cb_t         on_boot;             ///< Handler for initial boot
    bsp_wake_cb_t         on_wake;             ///< Handler for sleep wake events
    bsp_sleep_cb_t        on_sleep;            ///< Hook called immediately prior to sleep entry
    bsp_power_off_cb_t    on_power_off;        ///< Hook called immediately prior to power off

    /* Visual Splash Screen Callbacks */
    bsp_splash_cb_t       on_boot_splash;      ///< Render boot splash UI
    bsp_splash_cb_t       on_wake_splash;      ///< Render wake splash UI
    bsp_splash_cb_t       on_sleep_splash;     ///< Render sleep badge / UI
    bsp_splash_cb_t       on_power_off_splash; ///< Render power-off screen

    /* Audio Chime Configuration */
    bsp_chime_cb_t        on_chime;            ///< Custom chime callback (overrides hardware synthesizer if set)
    uint8_t               default_chime_mask;  ///< Bitmask of default hardware chimes to play if on_chime == NULL

    /* Background Sub-Execution Configuration */
    //bool                  enable_sub_execution;      ///< Enable autonomous background sensor sampling while main app sleeps
    uint32_t              sub_execution_interval_sec;  ///< Sub-execution cadence in seconds (default: 0s | OFF)

    void                  *user_data;                  ///< Custom application context pointer passed to all callbacks
} bsp_app_lifecycle_t;

/**
 * @brief Early Base IO and Power Latch Initialization (Phase 1)
 *
 * Releases RTC pad holds, drives BAT_CTRL (GPIO 17) HIGH immediately to secure board power,
 * and pre-configures input pull-ups on BOOT and POWER buttons for early PXE detection.
 *
 * @return esp_err_t ESP_OK on success
 */
esp_err_t bsp_io_early_init(void);

/**
 * @brief Start Unified BSP Application Engine with Lifecycle Hooks
 *
 * Automatically initializes RTC memory, inspects reset reason, selects optimal hardware init mode
 * (FULL on cold boot, FAST on wake), populates wake context, clears RTC flags, and dispatches on_cold_boot / on_wake.
 *
 * @param[in] lifecycle Pointer to bsp_app_lifecycle_t configuration
 * @return esp_err_t ESP_OK on success
 * @details Memory ownership: none. Behavior: Blocking. Thread safety: no thread safety guarantees.
 */
esp_err_t bsp_app_start(const bsp_app_lifecycle_t *lifecycle);

/**
 * @brief Manually trigger a UI Splash screen event defined in the active lifecycle
 *
 * @param[in] type Splash event type to trigger (BOOT, WAKE, SLEEP, SHUTDOWN)
 * @return esp_err_t ESP_OK if handler executed, ESP_ERR_NOT_FOUND if no handler configured
 */
esp_err_t bsp_trigger_splash(bsp_splash_type_t type);

/**
 * @brief Manually trigger an Audio Chime event defined in the active lifecycle
 *
 * Executes custom on_chime callback if configured, or plays default synthesized tone if enabled in default_chime_mask.
 *
 * @param[in] type Chime event type to trigger (BOOT, WAKE, SLEEP, SHUTDOWN, ALARM, NOTIFY, EVENT)
 * @return esp_err_t ESP_OK if chime played/dispatched, ESP_ERR_NOT_FOUND if disabled
 */
esp_err_t bsp_trigger_chime(bsp_chime_type_t type);

/**
 * @brief Single Unified Application Sleep Entry Point (Matches bsp_app_start)
 *
 * Dispatches before_sleep hook, triggers optional sleep splash/chime, powers down peripherals,
 * syncs dirty frame to 'epd_frame' flash partition, arms wake sources, and enters hardware light or deep sleep.
 *
 * @param[in] config Sleep configuration (mode, duration, wake sources, next init mode)
 * @return esp_err_t ESP_OK on success
 * @details Memory ownership: none. Behavior: Blocking. Thread safety: no thread safety guarantees.
 */
esp_err_t bsp_app_sleep(const bsp_sleep_config_t *config);

/**
 * @brief Helper Macro for Deep Sleep Entry
 */
#define bsp_sleep_deep(sec) bsp_app_sleep(&(bsp_sleep_config_t){ \
    .mode           = BSP_SLEEP_MODE_DEEP,                   \
    .duration_sec   = (sec),                                 \
    .wake_sources   = BSP_WAKE_SRC_ALL,                      \
    .next_init_mode = BSP_INIT_MODE_WAKE                     \
})

/**
 * @brief Helper Macro for Light Sleep Entry
 */
#define bsp_sleep_light(sec) bsp_app_sleep(&(bsp_sleep_config_t){ \
    .mode           = BSP_SLEEP_MODE_LIGHT,                   \
    .duration_sec   = (sec),                                  \
    .wake_sources   = BSP_WAKE_SRC_ALL,                       \
    .next_init_mode = BSP_INIT_MODE_WAKE                      \
})

/**
 * @brief Retrieve current wake context
 *
 * @param[out] ctx Pointer to bsp_wake_context_t destination
 * @return esp_err_t ESP_OK on success, ESP_ERR_INVALID_STATE if context is not available
 * @details Memory ownership: none. Behavior: Blocking. Thread safety: no thread safety guarantees.
 */
esp_err_t bsp_lifecycle_get_context(bsp_wake_context_t *ctx);

/**
 * @brief Set application stage index in RTC Slow Memory
 *
 * @param[in] stage Stage identifier (0..255)
 * @return esp_err_t ESP_OK on success
 * @details Memory ownership: none. Behavior: Blocking. Thread safety: no thread safety guarantees.
 */
esp_err_t bsp_lifecycle_set_stage(uint8_t stage);

/**
 * @brief Get application stage index from RTC Slow Memory
 *
 * @return uint8_t Current stage identifier
 * @details Memory ownership: none. Behavior: Blocking. Thread safety: no thread safety guarantees.
 */
uint8_t bsp_lifecycle_get_stage(void);

/**
 * @brief Save custom application state struct to RTC Slow Memory scratchpad (max 31 bytes)
 *
 * @param[in] data Source buffer
 * @param[in] len Byte count (max 31)
 * @return esp_err_t ESP_OK on success
 * @details Memory ownership: none. Behavior: Blocking. Thread safety: no thread safety guarantees.
 */
esp_err_t bsp_lifecycle_save_state(const void *data, size_t len);

/**
 * @brief Load custom application state struct from RTC Slow Memory scratchpad
 *
 * @param[out] out_data Destination buffer
 * @param[in] len Byte count (max 31)
 * @return esp_err_t ESP_OK on success
 * @details Memory ownership: none. Behavior: Blocking. Thread safety: no thread safety guarantees.
 */
esp_err_t bsp_lifecycle_load_state(void *out_data, size_t len);

/**
 * @brief Unified Class-E Environmental Telemetry & Multi-Node Diagnostic Structure
 */
typedef struct {
    /* 1. Smoothed Ambient Readings (EWMA) */
    float    ambient_temp_c;          ///< Ambient Temperature in Celsius (°C)
    float    ambient_temp_f;          ///< Ambient Temperature in Fahrenheit (°F)
    float    ambient_rh_pct;          ///< Ambient Relative Humidity (% RH)
    float    dew_point_c;             ///< Invariant Dew Point in Celsius (°C)
    float    dew_point_f;             ///< Invariant Dew Point in Fahrenheit (°F)
    float    absolute_humidity_g;     ///< Invariant Absolute Humidity (g/m³)

    /* 2. Multi-Node Diagnostics */
    float    raw_shtc3_temp_c;        ///< Raw uncompensated PCB SHTC3 reading (°C)
    float    mcu_die_temp_c;          ///< ESP32-S3 internal TSENS die temperature (°C)
    float    epd_glass_temp_c;        ///< SSD1681 glass thermistor readout (°C)

    /* 3. Quality & Stability Metrics */
    bool     is_thermally_settled;    ///< True if system is in thermal equilibrium
    uint32_t sample_count;            ///< Monotonic count of committed telemetry samples
    uint32_t battery_mv;              ///< Calibrated battery voltage (mV)
    uint8_t  battery_percent;         ///< Battery charge level (0 - 100%)
} bsp_app_telemetry_t;

/**
 * @brief Unified Application Telemetry Ingestion API
 *
 * Transparently retrieves psychrometrically reconstructed ambient readings,
 * shielded against self-heating by the Layer 3 Thermal Lockout MUX.
 *
 * @param[out] out_telemetry Destination pointer populated with telemetry metrics.
 * @return esp_err_t ESP_OK on success.
 */
esp_err_t bsp_app_get_telemetry(bsp_app_telemetry_t *out_telemetry);

/**
 * @brief Perform Clean System Shutdown
 * @details Memory ownership: none. Behavior: Blocking. Thread safety: no thread safety guarantees.
 */
esp_err_t bsp_app_shutdown(void);

/**
 * @brief Generic Millisecond Delay Helper
 *
 * Suspends execution for the specified duration in milliseconds.
 * Uses FreeRTOS task delay if the scheduler is running, or hardware ROM delay on early boot.
 * Allows delaying execution without including FreeRTOS header files in application code.
 *
 * @param[in] ms Delay duration in milliseconds
 * @details Memory ownership: none. Behavior: Blocking / Task Yield. Thread safety: Thread-safe.
 */
void bsp_delay_ms(uint32_t ms);

/**
 * @brief Generic Microsecond Delay Helper
 *
 * Pauses execution for the specified duration in microseconds using high-resolution timer.
 * Does not require including FreeRTOS headers.
 *
 * @param[in] us Delay duration in microseconds
 * @details Memory ownership: none. Behavior: Busy-wait delay. Thread safety: Thread-safe.
 */
void bsp_delay_us(uint32_t us);

#ifdef __cplusplus
}
#endif

#endif /* BSP_H */
