/**
 * @file sub_sdcard.h
 * @brief Layer 2: MicroSD Card Subsystem Manager (1-Bit SDMMC FATFS)
 *
 * Provides basic file I/O, formatting, and capacity checks.
 *
 * Hardware Target:
 *  - CLK: GPIO 39
 *  - D0:  GPIO 40
 *  - CMD: GPIO 41
 *  - Mount Point: "/sdcard"
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

#define SUB_SDCARD_MOUNT_POINT "/sdcard"

/**
 * @brief Mount MicroSD card using 1-bit SDMMC driver (synchronous).
 */
esp_err_t sub_sdcard_mount(void);

/**
 * @brief Asynchronously mount MicroSD card in a background FreeRTOS task.
 * Does not block caller or freeze UI refresh if card is missing.
 */
esp_err_t sub_sdcard_mount_async(void);

/**
 * @brief Unmount MicroSD card and release hardware bus resources.
 */
esp_err_t sub_sdcard_unmount(void);

/**
 * @brief Fast pre-flight probe to detect if MicroSD card is physically present in the slot.
 * Returns in < 5ms without running full 1-second SDMMC retry timeout loops.
 * 
 * @return true if card appears present, false otherwise.
 */
bool sub_sdcard_probe(void);

/**
 * @brief Check if MicroSD card is mounted and ready for I/O.
 */
bool sub_sdcard_is_mounted(void);

/**
 * @brief Get total capacity of mounted card in megabytes.
 */
esp_err_t sub_sdcard_get_capacity_mb(uint32_t *out_capacity_mb);

/**
 * @brief Format mounted card as FAT32 filesystem.
 */
esp_err_t sub_sdcard_format(void);

#ifdef __cplusplus
}
#endif
