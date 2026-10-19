/**
 * @file sub_sdcard.h
 * @brief Layer 2: MicroSD card subsystem manager (1-bit SDMMC FATFS)
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "esp_err.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SUB_SDCARD_MOUNT_POINT "/sdcard" /**< VFS mount point prefix for MicroSD filesystem. */

/**
 * @brief Mount MicroSD card into FATFS VFS in 1-bit SDMMC mode.
 *
 * @return ESP_OK on success, or mount failure error.
 */
esp_err_t sub_sdcard_mount(void);

/**
 * @brief Mount MicroSD card asynchronously in background task.
 *
 * @return ESP_OK if mount task dispatched successfully.
 */
esp_err_t sub_sdcard_mount_async(void);

/**
 * @brief Unmount MicroSD card and release SDMMC host peripheral.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_sdcard_unmount(void);

/**
 * @brief Check if MicroSD card is actively mounted in VFS.
 *
 * @return True if filesystem is mounted and accessible.
 */
bool sub_sdcard_is_mounted(void);

/**
 * @brief Query total storage capacity of mounted MicroSD card in megabytes.
 *
 * @param[out] out_capacity_mb Pointer to store total capacity in MB. Must not be NULL.
 *
 * @return ESP_OK on success, or ESP_ERR_INVALID_STATE if not mounted.
 */
esp_err_t sub_sdcard_get_capacity_mb(uint32_t *out_capacity_mb);

/**
 * @brief Format mounted MicroSD card with clean FAT32 filesystem.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_sdcard_format(void);

#ifdef __cplusplus
}
#endif
