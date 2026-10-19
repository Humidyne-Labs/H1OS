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

#define SUB_NVS_NAMESPACE "h1os" /**< Default NVS partition namespace for H1OS settings. */

/**
 * @brief Initialize the NVS flash storage subsystem.
 *
 * @return ESP_OK on success, or flash partition error.
 */
esp_err_t sub_nvs_init(void);

/**
 * @brief Store a null-terminated string value in NVS.
 *
 * @param[in] key   Unique key identifier string.
 * @param[in] value String payload to persist.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_nvs_set_str(const char *key, const char *value);

/**
 * @brief Retrieve a string value from NVS.
 *
 * @param[in]  key     Unique key identifier string.
 * @param[out] out_val Destination character buffer.
 * @param[in]  max_len Capacity of destination buffer.
 *
 * @return ESP_OK on success, or ESP_ERR_NVS_NOT_FOUND if key not present.
 */
esp_err_t sub_nvs_get_str(const char *key, char *out_val, size_t max_len);

/**
 * @brief Store an unsigned 32-bit integer in NVS.
 *
 * @param[in] key   Unique key identifier string.
 * @param[in] value Integer value to persist.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_nvs_set_u32(const char *key, uint32_t value);

/**
 * @brief Retrieve an unsigned 32-bit integer from NVS.
 *
 * @param[in]  key     Unique key identifier string.
 * @param[out] out_val Destination pointer for integer.
 *
 * @return ESP_OK on success, or ESP_ERR_NVS_NOT_FOUND.
 */
esp_err_t sub_nvs_get_u32(const char *key, uint32_t *out_val);

/**
 * @brief Store a binary blob in NVS.
 *
 * @param[in] key  Unique key identifier string.
 * @param[in] data Pointer to binary data buffer.
 * @param[in] len  Length of data in bytes.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_nvs_set_blob(const char *key, const void *data, size_t len);

/**
 * @brief Retrieve a binary blob from NVS.
 *
 * @param[in]     key       Unique key identifier string.
 * @param[out]    out_data  Destination buffer for binary data.
 * @param[in,out] inout_len On entry: capacity of buffer; on exit: actual read bytes.
 *
 * @return ESP_OK on success, or ESP_ERR_NVS_NOT_FOUND.
 */
esp_err_t sub_nvs_get_blob(const char *key, void *out_data, size_t *inout_len);

/**
 * @brief Erase a specific key from NVS.
 *
 * @param[in] key Key identifier string to erase.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_nvs_erase_key(const char *key);

/**
 * @brief Perform a factory reset wiping the entire H1OS NVS namespace.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_nvs_erase_all(void);

#ifdef __cplusplus
}
#endif
