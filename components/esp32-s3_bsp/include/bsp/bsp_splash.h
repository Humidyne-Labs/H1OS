/**
 * @file bsp_splash.h
 * @brief System UI Splash Screens & Audio Chime Definitions (Compatibility Wrapper)
 *
 * @note Splash and chime lifecycle management has been unified into bsp_app_lifecycle_t in bsp.h.
 *       This header is maintained for backward compatibility.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef BSP_SPLASH_H
#define BSP_SPLASH_H

#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Early Boot Depressed Button Bitmask Flags (PXE Detection)
 */
typedef enum {
    BSP_BUTTON_MASK_NONE  = 0,         ///< No buttons depressed on boot
    BSP_BUTTON_MASK_BOOT  = (1 << 0),  ///< BOOT button (GPIO 0) held on boot
    BSP_BUTTON_MASK_POWER = (1 << 1),  ///< POWER button (GPIO 18) held on boot
    BSP_BUTTON_MASK_BOTH  = (BSP_BUTTON_MASK_BOOT | BSP_BUTTON_MASK_POWER), ///< Both buttons held
} bsp_button_mask_t;

/**
 * @brief UI Splash Screen Types
 */
typedef enum {
    BSP_SPLASH_BOOT      = 0, ///< Rendered upon system boot
    BSP_SPLASH_WAKE      = 1, ///< Rendered upon resuming from sleep
    BSP_SPLASH_SLEEP     = 2, ///< Rendered prior to entering sleep
    BSP_SPLASH_POWER_OFF = 3, ///< Rendered prior to system power off
    BSP_SPLASH_MAX       = 4
} bsp_splash_type_t;

#define BSP_SPLASH_SHUTDOWN BSP_SPLASH_POWER_OFF

/**
 * @brief Audio Chime / Notification Event Types
 */
typedef enum {
    BSP_CHIME_BOOT      = 0, ///< Melodic boot chime
    BSP_CHIME_WAKE      = 1, ///< Wake from sleep acoustic cue
    BSP_CHIME_SLEEP     = 2, ///< Sleep stand-down descending tone
    BSP_CHIME_POWER_OFF = 3, ///< Power off tone
    BSP_CHIME_ALARM     = 4, ///< Critical telemetry / threshold alarm
    BSP_CHIME_NOTIFY    = 5, ///< General notification chirp
    BSP_CHIME_EVENT     = 6, ///< User action / UI event click tone
    BSP_CHIME_MAX       = 7
} bsp_chime_type_t;

#define BSP_CHIME_SHUTDOWN BSP_CHIME_POWER_OFF

/**
 * @brief Default Chime Bitmask Flags for selective enablement
 */
#define BSP_CHIME_MASK_NONE       (0x00)
#define BSP_CHIME_MASK_BOOT       (1 << BSP_CHIME_BOOT)
#define BSP_CHIME_MASK_WAKE       (1 << BSP_CHIME_WAKE)
#define BSP_CHIME_MASK_SLEEP      (1 << BSP_CHIME_SLEEP)
#define BSP_CHIME_MASK_POWER_OFF  (1 << BSP_CHIME_POWER_OFF)
#define BSP_CHIME_MASK_SHUTDOWN   BSP_CHIME_MASK_POWER_OFF
#define BSP_CHIME_MASK_ALARM      (1 << BSP_CHIME_ALARM)
#define BSP_CHIME_MASK_NOTIFY     (1 << BSP_CHIME_NOTIFY)
#define BSP_CHIME_MASK_EVENT      (1 << BSP_CHIME_EVENT)
#define BSP_CHIME_MASK_ALL        (0x7F)

#ifdef __cplusplus
}
#endif

#endif /* BSP_SPLASH_H */
