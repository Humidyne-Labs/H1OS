/**
 * @file bsp_rtc_mem.c
 * @brief Internal ESP32-S3 RTC Slow Memory Persistent Storage Implementation
 *
 * @version 1.0.0
 * @attribution
 * - Architecture & Development: HUMIDYNE LABS / Humiditron
 * - AI Systems Co-Developer: Gemini (Google DeepMind)
 * - Hardware Target: Waveshare Electronics ESP32-S3 ePaper 1.54 V2
 *
 * SPDX-License-Identifier: MIT
 */

#include <string.h>
#include "esp_log.h"
#include "esp_attr.h"
#include "esp_sleep.h"
#include "bsp/bsp_rtc_mem.h"

static const char *TAG = "bsp_rtc_mem";

RTC_DATA_ATTR static bsp_rtc_state_t s_rtc_state;
//RTC_DATA_ATTR static uint8_t         s_rtc_frame_buffer[5000];
//RTC_DATA_ATTR static bool            s_rtc_frame_valid = false;
static bool                          s_boot_counted    = false;

esp_err_t bsp_rtc_mem_init(void) {
    if (s_rtc_state.magic != BSP_RTC_MEM_MAGIC) {
        ESP_LOGI(TAG, "RTC Slow Memory uninitialized or invalid (magic 0x%08lX); re-initializing",
                 (unsigned long)s_rtc_state.magic);
        bsp_rtc_mem_reset();
        s_boot_counted = true;
    } else if (!s_boot_counted) {
        s_rtc_state.boot_count++;
        s_boot_counted = true;
        ESP_LOGI(TAG, "RTC Slow Memory valid (Boot count: %lu, Deep sleep count: %lu)",
                 (unsigned long)s_rtc_state.boot_count, (unsigned long)s_rtc_state.deep_sleep_count);
    }
    return ESP_OK;
}

bsp_rtc_state_t *bsp_rtc_mem_get_state(void) {
    return &s_rtc_state;
}

uint32_t bsp_rtc_mem_get_boot_count(void) {
    return s_rtc_state.boot_count;
}

void bsp_rtc_mem_set_next_init_mode(bsp_init_mode_t mode) {
    s_rtc_state.next_init_mode = (uint8_t)mode;
}

bsp_init_mode_t bsp_rtc_mem_get_next_init_mode(void) {
    return (bsp_init_mode_t)s_rtc_state.next_init_mode;
}

esp_err_t bsp_rtc_mem_read_scratchpad(uint8_t *dest, size_t len) {
    if (dest == NULL || len == 0 || len > sizeof(s_rtc_state.scratchpad)) {
        return ESP_ERR_INVALID_ARG;
    }
    memcpy(dest, s_rtc_state.scratchpad, len);
    return ESP_OK;
}

esp_err_t bsp_rtc_mem_write_scratchpad(const uint8_t *src, size_t len) {
    if (src == NULL || len == 0 || len > sizeof(s_rtc_state.scratchpad)) {
        return ESP_ERR_INVALID_ARG;
    } memcpy(s_rtc_state.scratchpad, src, len);
    return ESP_OK;
}

#include "esp_partition.h"

esp_err_t bsp_rtc_mem_save_display_frame(const uint8_t *frame, size_t len)
{
    if (frame == NULL || len == 0 || len > 5000) {
        return ESP_ERR_INVALID_ARG;
    }

    const esp_partition_t *part = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_ANY, "epd_frame");
    if (part == NULL) {
        ESP_LOGE(TAG, "Partition 'epd_frame' not found in partition table");
        return ESP_ERR_NOT_FOUND;
    }

    // Erase 2 flash sectors (8192 bytes) to accommodate 5000 bytes
    esp_err_t err = esp_partition_erase_range(part, 0, 8192);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to erase 'epd_frame' partition: %s", esp_err_to_name(err));
        return err;
    }

    err = esp_partition_write(part, 0, frame, len);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to write 'epd_frame' partition: %s", esp_err_to_name(err));
        return err;
    }

    s_rtc_state.flags |= BSP_RTC_FLAG_EPD_FRAME_VALID;
    ESP_LOGI(TAG, "Persisted 1-bit EPD frame (%u bytes) to 'epd_frame' flash partition", (unsigned)len);
    return ESP_OK;
}

esp_err_t bsp_rtc_mem_load_display_frame(uint8_t *dest, size_t len)
{
    if (dest == NULL || len == 0 || len > 5000) {
        return ESP_ERR_INVALID_ARG;
    }

    if (!bsp_rtc_mem_has_display_frame()) {
        return ESP_ERR_NOT_FOUND;
    }

    const esp_partition_t *part = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_ANY, "epd_frame");
    if (part == NULL) {
        ESP_LOGE(TAG, "Partition 'epd_frame' not found in partition table");
        return ESP_ERR_NOT_FOUND;
    }

    esp_err_t err = esp_partition_read(part, 0, dest, len);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read 'epd_frame' partition: %s", esp_err_to_name(err));
        return err;
    }

    ESP_LOGI(TAG, "Loaded 1-bit EPD frame (%u bytes) from 'epd_frame' flash partition", (unsigned)len);
    return ESP_OK;
}

bool bsp_rtc_mem_has_display_frame(void)
{
    return (s_rtc_state.flags & BSP_RTC_FLAG_EPD_FRAME_VALID) != 0;
}

void bsp_rtc_mem_set_display_frame_valid(bool valid)
{
    if (valid) {
        s_rtc_state.flags |= BSP_RTC_FLAG_EPD_FRAME_VALID;
    } else {
        s_rtc_state.flags &= ~BSP_RTC_FLAG_EPD_FRAME_VALID;
    }
}

void bsp_rtc_mem_reset(void) {
    memset(&s_rtc_state, 0, sizeof(bsp_rtc_state_t));
    s_rtc_state.magic          = BSP_RTC_MEM_MAGIC;
    s_rtc_state.boot_count     = 1;
    s_rtc_state.last_init_mode = (uint8_t)BSP_INIT_MODE_FULL;
    s_rtc_state.next_init_mode = (uint8_t)BSP_INIT_MODE_FULL;
    s_rtc_state.flags          = BSP_RTC_FLAG_NONE;
}
