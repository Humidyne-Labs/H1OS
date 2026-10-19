/**
 * @file sub_nvs.h
 * @brief Layer 2: Non-volatile configuration storage (NVS) manager
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "esp_err.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SUB_NVS_NAMESPACE "h1os"

esp_err_t sub_nvs_init(void);

esp_err_t sub_nvs_set_str(const char *key, const char *value);

esp_err_t sub_nvs_get_str(const char *key, char *out_val, size_t max_len);

esp_err_t sub_nvs_set_u32(const char *key, uint32_t value);

esp_err_t sub_nvs_get_u32(const char *key, uint32_t *out_val);

esp_err_t sub_nvs_set_blob(const char *key, const void *data, size_t len);

esp_err_t sub_nvs_get_blob(const char *key, void *out_data, size_t *inout_len);

esp_err_t sub_nvs_erase_key(const char *key);

esp_err_t sub_nvs_erase_all(void);

#ifdef __cplusplus
}
#endif
