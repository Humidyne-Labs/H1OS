/**
 * @file sub_nvs.c
 * @brief Layer 2: Non-volatile storage (NVS) manager implementation
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "sub_nvs.h"

#include "esp_log.h"
#include "nvs.h"
#include "nvs_flash.h"

#include <stdio.h>
#include <string.h>

static const char *TAG = "sub_nvs";
static bool s_nvs_initialized = false;

/**
 * @brief Initialize the NVS flash storage subsystem.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_nvs_init(void)
{
    if (s_nvs_initialized)
        return ESP_OK;

    ESP_LOGI(TAG, "Initializing NVS Flash Subsystem");

    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_LOGW(TAG, "NVS partition truncated or version mismatch; erasing and re-initializing...");
        err = nvs_flash_erase();
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Failed to erase NVS partition: %s", esp_err_to_name(err));
            return err;
        }
        err = nvs_flash_init();
    }

    s_nvs_initialized = (err == ESP_OK);
    if (s_nvs_initialized) {
        ESP_LOGI(TAG, "NVS Initialized Successfully");
    } else {
        ESP_LOGE(TAG, "Failed to initialize NVS: %s", esp_err_to_name(err));
    }

    return err;
}

/**
 * @brief Store a string value in NVS.
 *
 * @param[in]    key             Parameter key.
 * @param[in]    value           Parameter value.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_nvs_set_str(const char *key, const char *value)
{
    if (key == NULL || value == NULL)
        return ESP_ERR_INVALID_ARG;
    if (!s_nvs_initialized)
        sub_nvs_init();

    nvs_handle_t handle;
    esp_err_t err = nvs_open(SUB_NVS_NAMESPACE, NVS_READWRITE, &handle);
    if (err != ESP_OK)
        return err;

    err = nvs_set_str(handle, key, value);
    if (err == ESP_OK) {
        err = nvs_commit(handle);
    }
    nvs_close(handle);
    return err;
}

/**
 * @brief Retrieve a string value from NVS.
 *
 * @param[in]    key             Parameter key.
 * @param[out]   out_val         Parameter out_val.
 * @param[in]    max_len         Parameter max_len.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_nvs_get_str(const char *key, char *out_val, size_t max_len)
{
    if (key == NULL || out_val == NULL || max_len == 0)
        return ESP_ERR_INVALID_ARG;
    if (!s_nvs_initialized)
        sub_nvs_init();

    nvs_handle_t handle;
    esp_err_t err = nvs_open(SUB_NVS_NAMESPACE, NVS_READONLY, &handle);
    if (err != ESP_OK)
        return err;

    size_t required_len = max_len;
    err = nvs_get_str(handle, key, out_val, &required_len);
    nvs_close(handle);
    return err;
}

/**
 * @brief Store an unsigned 32-bit integer in NVS.
 *
 * @param[in]    key             Parameter key.
 * @param[in]    value           Parameter value.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_nvs_set_u32(const char *key, uint32_t value)
{
    if (key == NULL)
        return ESP_ERR_INVALID_ARG;
    if (!s_nvs_initialized)
        sub_nvs_init();

    nvs_handle_t handle;
    esp_err_t err = nvs_open(SUB_NVS_NAMESPACE, NVS_READWRITE, &handle);
    if (err != ESP_OK)
        return err;

    err = nvs_set_u32(handle, key, value);
    if (err == ESP_OK) {
        err = nvs_commit(handle);
    }
    nvs_close(handle);
    return err;
}

/**
 * @brief Retrieve an unsigned 32-bit integer from NVS.
 *
 * @param[in]    key             Parameter key.
 * @param[out]   out_val         Parameter out_val.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_nvs_get_u32(const char *key, uint32_t *out_val)
{
    if (key == NULL || out_val == NULL)
        return ESP_ERR_INVALID_ARG;
    if (!s_nvs_initialized)
        sub_nvs_init();

    nvs_handle_t handle;
    esp_err_t err = nvs_open(SUB_NVS_NAMESPACE, NVS_READONLY, &handle);
    if (err != ESP_OK)
        return err;

    err = nvs_get_u32(handle, key, out_val);
    nvs_close(handle);
    return err;
}

/**
 * @brief Store a binary blob in NVS.
 *
 * @param[in]    key             Parameter key.
 * @param[in]    data            Parameter data.
 * @param[in]    len             Parameter len.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_nvs_set_blob(const char *key, const void *data, size_t len)
{
    if (key == NULL || data == NULL || len == 0)
        return ESP_ERR_INVALID_ARG;
    if (!s_nvs_initialized)
        sub_nvs_init();

    nvs_handle_t handle;
    esp_err_t err = nvs_open(SUB_NVS_NAMESPACE, NVS_READWRITE, &handle);
    if (err != ESP_OK)
        return err;

    err = nvs_set_blob(handle, key, data, len);
    if (err == ESP_OK) {
        err = nvs_commit(handle);
    }
    nvs_close(handle);
    return err;
}

/**
 * @brief Retrieve a binary blob from NVS.
 *
 * @param[in]    key             Parameter key.
 * @param[out]   out_data        Parameter out_data.
 * @param[out]   inout_len       Parameter inout_len.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_nvs_get_blob(const char *key, void *out_data, size_t *inout_len)
{
    if (key == NULL || out_data == NULL || inout_len == NULL || *inout_len == 0)
        return ESP_ERR_INVALID_ARG;
    if (!s_nvs_initialized)
        sub_nvs_init();

    nvs_handle_t handle;
    esp_err_t err = nvs_open(SUB_NVS_NAMESPACE, NVS_READONLY, &handle);
    if (err != ESP_OK)
        return err;

    err = nvs_get_blob(handle, key, out_data, inout_len);
    nvs_close(handle);
    return err;
}

/**
 * @brief Erase a specific key from NVS.
 *
 * @param[in]    key             Parameter key.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_nvs_erase_key(const char *key)
{
    if (key == NULL)
        return ESP_ERR_INVALID_ARG;
    if (!s_nvs_initialized)
        sub_nvs_init();

    nvs_handle_t handle;
    esp_err_t err = nvs_open(SUB_NVS_NAMESPACE, NVS_READWRITE, &handle);
    if (err != ESP_OK)
        return err;

    err = nvs_erase_key(handle, key);
    if (err == ESP_OK) {
        err = nvs_commit(handle);
    }
    nvs_close(handle);
    return err;
}

/**
 * @brief Perform a factory reset wiping the entire H1OS NVS namespace.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_nvs_erase_all(void)
{
    if (!s_nvs_initialized)
        sub_nvs_init();

    nvs_handle_t handle;
    esp_err_t err = nvs_open(SUB_NVS_NAMESPACE, NVS_READWRITE, &handle);
    if (err != ESP_OK)
        return err;

    err = nvs_erase_all(handle);
    if (err == ESP_OK) {
        err = nvs_commit(handle);
    }
    nvs_close(handle);
    return err;
}
