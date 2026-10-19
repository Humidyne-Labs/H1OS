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

#define SUB_SDCARD_MOUNT_POINT "/sdcard"

esp_err_t sub_sdcard_mount(void);

esp_err_t sub_sdcard_mount_async(void);

esp_err_t sub_sdcard_unmount(void);

bool sub_sdcard_is_mounted(void);

esp_err_t sub_sdcard_get_capacity_mb(uint32_t *out_capacity_mb);

esp_err_t sub_sdcard_format(void);

#ifdef __cplusplus
}
#endif
