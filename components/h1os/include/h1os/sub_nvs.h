/**
 * @file sub_nvs.h
 * @brief Layer 2: Non-Volatile Storage (NVS) Subsystem Manager
 *
 * Provides structured key-value persistence in flash for system parameters,
 * calibration offsets, and user settings.
 *
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

/**
 * @brief Initialize the NVS flash storage subsystem.
 */
esp_err_t sub_nvs_init(void);

/**
 * @brief Store a string value in NVS.
 */
esp_err_t sub_nvs_set_str(const char *key, const char *value);

/**
 * @brief Retrieve a string value from NVS.
 */
esp_err_t sub_nvs_get_str(const char *key, char *out_val, size_t max_len);

/**
 * @brief Store an unsigned 32-bit integer in NVS.
 */
esp_err_t sub_nvs_set_u32(const char *key, uint32_t value);

/**
 * @brief Retrieve an unsigned 32-bit integer from NVS.
 */
esp_err_t sub_nvs_get_u32(const char *key, uint32_t *out_val);

/**
 * @brief Store a binary blob in NVS.
 */
esp_err_t sub_nvs_set_blob(const char *key, const void *data, size_t len);

/**
 * @brief Retrieve a binary blob from NVS.
 */
esp_err_t sub_nvs_get_blob(const char *key, void *out_data, size_t *inout_len);

/**
 * @brief Erase a specific key from NVS.
 */
esp_err_t sub_nvs_erase_key(const char *key);

/**
 * @brief Perform a factory reset wiping the entire H1OS NVS namespace.
 */
esp_err_t sub_nvs_erase_all(void);

#ifdef __cplusplus
}
#endif
