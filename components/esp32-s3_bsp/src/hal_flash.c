/**
 * @file hal_flash.c
 * @brief Layer 1 HAL Raw Flash Partition Storage Implementation
 * 
 * SPDX-License-Identifier: MIT
 */

#include "bsp/hal_flash.h"
#include "esp_log.h"
#include "esp_partition.h"

static const char *TAG = "HAL_FLASH";
static const esp_partition_t *s_part = NULL;

esp_err_t hal_flash_init(void)
{
    if (s_part != NULL) {
        return ESP_OK;
    }

    s_part = esp_partition_find_first(ESP_PARTITION_TYPE_DATA,
                                      ESP_PARTITION_SUBTYPE_ANY,
                                      HAL_PARTITION_EPD_FRAME);
    if (!s_part) {
        ESP_LOGE(TAG, "Partition '%s' not found in partition table!", HAL_PARTITION_EPD_FRAME);
        return ESP_ERR_NOT_FOUND;
    }

    ESP_LOGD(TAG, "Found partition '%s' at offset 0x%08" PRIx32 ", size 0x%08" PRIx32,
             s_part->label, s_part->address, s_part->size);
    return ESP_OK;
}

esp_err_t hal_flash_read_frame(uint8_t *out_buffer, size_t len)
{
    if (!s_part) {
        esp_err_t ret = hal_flash_init();
        if (ret != ESP_OK) {
            return ret;
        }
    }

    if (!out_buffer || len == 0 || len > s_part->size) {
        return ESP_ERR_INVALID_ARG;
    }

    return esp_partition_read(s_part, 0, out_buffer, len);
}

esp_err_t hal_flash_write_frame(const uint8_t *frame_data, size_t len)
{
    if (!s_part) {
        esp_err_t ret = hal_flash_init();
        if (ret != ESP_OK) {
            return ret;
        }
    }

    if (!frame_data || len == 0 || len > s_part->size) {
        return ESP_ERR_INVALID_ARG;
    }

    // Erase the 16KB partition sector (must be 4KB sector aligned)
    size_t erase_size = (len + 4095) & ~4095;
    if (erase_size > s_part->size) {
        erase_size = s_part->size;
    }

    esp_err_t ret = esp_partition_erase_range(s_part, 0, erase_size);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to erase partition '%s': %d", s_part->label, ret);
        return ret;
    }

    // Write the raw frame data
    ret = esp_partition_write(s_part, 0, frame_data, len);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to write frame to '%s': %d", s_part->label, ret);
        return ret;
    }

    ESP_LOGD(TAG, "Successfully committed %zu bytes to flash partition '%s'", len, s_part->label);
    return ESP_OK;
}
