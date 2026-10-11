/**
 * @file h1os.h
 * @brief H1OS: Class-E Environmental Operating System Master API
 *
 * Platform: H1OS (Humid-1 Operating System)
 * Hardware Target: Waveshare ESP32-S3 ePaper 1.54" V2 (ESP32-S3-PICO-1-N8R8)
 * Role: Luxury Hygrometer & Environmental Telemetry Executive Engine
 *
 * @version 1.0.0-alpha
 * @attribution
 * - Architecture & System Design: HUMIDYNE LABS / Humiditron
 * - AI Systems Co-Developer: Gemini (Google DeepMind)
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef H1OS_H
#define H1OS_H

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

/* Consolidated platform dependencies */
#include "bsp/bsp.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================= */
/*  Platform Identity & Versioning                                           */
/* ========================================================================= */

#define H1OS_NAME               "H1OS"
#define H1OS_SUBTITLE           "Class-E Environmental Operating System"
#define H1OS_VERSION_MAJOR      1
#define H1OS_VERSION_MINOR      0
#define H1OS_VERSION_PATCH      0
#define H1OS_VERSION_TAG        "alpha"
#define H1OS_VERSION_STRING     "1.0.0-alpha"

#define H1OS_VERSION_VAL(maj, min, pat) (((maj) << 16) | ((min) << 8) | (pat))
#define H1OS_CURRENT_VERSION    H1OS_VERSION_VAL(H1OS_VERSION_MAJOR, H1OS_VERSION_MINOR, H1OS_VERSION_PATCH)

/* ========================================================================= */
/*  Type Definitions & Platform Contracts                                    */
/* ========================================================================= */

/**
 * @brief H1OS Tri-Node Psychrometric Telemetry Snapshot
 */
typedef bsp_app_telemetry_t       h1os_telemetry_t;

/**
 * @brief H1OS Application Lifecycle Callbacks & Configuration
 */
typedef bsp_app_lifecycle_t       h1os_app_lifecycle_t;

/**
 * @brief Hardware Sleep Configuration
 */
typedef bsp_sleep_config_t        h1os_sleep_config_t;

/**
 * @brief Hardware Initialization Configuration Profile
 */
typedef bsp_config_t              h1os_config_t;

/* ========================================================================= */
/*  Public API Entry Points                                                  */
/* ========================================================================= */

/**
 * @brief Get the H1OS platform semantic version string.
 *
 * @return const char* Formatted as "1.0.0-alpha".
 */
static inline const char *h1os_get_version(void)
{
    return H1OS_VERSION_STRING;
}

/**
 * @brief Initialize H1OS and dispatch the application lifecycle dispatcher.
 *
 * Enforces boot mode validation, restores persistent state from RTC Slow SRAM,
 * handles fast wake stubs, and launches the registered user lifecycle hooks.
 *
 * @param lifecycle Pointer to application lifecycle struct.
 * @return esp_err_t ESP_OK on clean hand-off or orderly sleep entry.
 */
static inline esp_err_t h1os_start(const h1os_app_lifecycle_t *lifecycle)
{
    return bsp_app_start(lifecycle);
}

/**
 * @brief Retrieve current Tri-Node environmental telemetry.
 *
 * Transparently gated by the H1OS Thermal Lockout MUX: if an active display
 * refresh or CPU-intensive task has recently occurred, the reading reflects
 * the pure invariant ambient baseline.
 *
 * @param out_sample Destination pointer for telemetry struct.
 * @return esp_err_t ESP_OK if valid sample returned.
 */
static inline esp_err_t h1os_get_telemetry(h1os_telemetry_t *out_sample)
{
    return bsp_app_get_telemetry(out_sample);
}

/**
 * @brief Put the platform into ultra-low-power deep sleep.
 *
 * Commits any pending dirty e-Paper frame to flash, arms the hardware countdown
 * timer (PCF85063A) and ULP-RISC-V sentinel, locks RTC pad holds, and enters sleep.
 *
 * @param config Optional sleep configuration (NULL for default deep sleep).
 * @return esp_err_t ESP_OK (or device powers down).
 */
static inline esp_err_t h1os_sleep(const h1os_sleep_config_t *config)
{
    return bsp_app_sleep(config);
}

/**
 * @brief Convenience helper for timed deep sleep.
 *
 * @param duration_sec Sleep duration in seconds.
 * @return esp_err_t ESP_OK.
 */
static inline esp_err_t h1os_sleep_deep(uint32_t duration_sec)
{
    bsp_sleep_config_t cfg = {
        .mode           = BSP_SLEEP_MODE_DEEP,
        .duration_sec   = duration_sec,
        .wake_sources   = BSP_WAKE_SRC_ALL,
        .next_init_mode = BSP_INIT_MODE_WAKE,
    };
    return bsp_app_sleep(&cfg);
}

/**
 * @brief Orderly system shutdown and physical battery power cut.
 *
 * Emits the descending power-off acoustic chime, renders the shutdown splash,
 * commits final flash state, and de-asserts BAT_CTRL (GPIO 17) to drop LDO gate.
 *
 * @return esp_err_t ESP_OK.
 */
static inline esp_err_t h1os_shutdown(void)
{
    return bsp_app_shutdown();
}

#ifdef __cplusplus
}
#endif

#endif /* H1OS_H */
