/**
 * @file sub_sdcard.c
 * @brief Layer 2: MicroSD Card Subsystem Manager Implementation (1-Bit SDMMC FATFS)
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>
#include <string.h>
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "driver/sdmmc_host.h"
#include "esp_log.h"
#include "hal_types.h"
#include "sub_sdcard.h"

static const char *TAG = "sub_sdcard";

static sdmmc_card_t *s_sd_card = NULL;

esp_err_t sub_sdcard_mount(void)
{
    if (s_sd_card != NULL) {
        ESP_LOGW(TAG, "SD Card already mounted");
        return ESP_OK;
    }

    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files              = 5,
        .allocation_unit_size   = 16 * 1024,
    };

    sdmmc_host_t host = SDMMC_HOST_DEFAULT();
    host.max_freq_khz = SDMMC_FREQ_DEFAULT;
    host.flags        = SDMMC_HOST_FLAG_1BIT;

    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
    slot_config.width = 1;
    slot_config.clk   = HAL_PIN_SD_CLK;
    slot_config.cmd   = HAL_PIN_SD_MOSI;
    slot_config.d0    = HAL_PIN_SD_MISO;
    slot_config.cd    = SDMMC_SLOT_NO_CD;
    slot_config.wp    = SDMMC_SLOT_NO_WP;

    esp_log_level_t prev_sdmmc_log = esp_log_level_get("sdmmc_common");
    esp_log_level_t prev_vfs_log   = esp_log_level_get("vfs_fat_sdmmc");
    esp_log_level_set("sdmmc_common",  ESP_LOG_WARN);
    esp_log_level_set("vfs_fat_sdmmc", ESP_LOG_WARN);

    esp_err_t ret = esp_vfs_fat_sdmmc_mount(SUB_SDCARD_MOUNT_POINT, &host, &slot_config, &mount_config, &s_sd_card);

    esp_log_level_set("sdmmc_common",  prev_sdmmc_log);
    esp_log_level_set("vfs_fat_sdmmc", prev_vfs_log);

    if (ret != ESP_OK) {
        s_sd_card = NULL;
        return ret;
    }

    ESP_LOGI(TAG, "MicroSD card mounted successfully at %s", SUB_SDCARD_MOUNT_POINT);
    return ESP_OK;
}

esp_err_t sub_sdcard_unmount(void)
{
    if (s_sd_card == NULL) {
        return ESP_OK;
    }

    esp_err_t ret = esp_vfs_fat_sdcard_unmount(SUB_SDCARD_MOUNT_POINT, s_sd_card);
    s_sd_card = NULL;
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "MicroSD card unmounted");
    }
    return ret;
}

bool sub_sdcard_is_mounted(void)
{
    return (s_sd_card != NULL);
}

esp_err_t sub_sdcard_get_capacity_mb(uint32_t *out_capacity_mb)
{
    if (!out_capacity_mb)  return ESP_ERR_INVALID_ARG;
    if (s_sd_card == NULL) return ESP_ERR_INVALID_STATE;

    uint64_t bytes = ((uint64_t)s_sd_card->csd.capacity) * s_sd_card->csd.sector_size;
    *out_capacity_mb = (uint32_t)(bytes / (1024 * 1024));
    return ESP_OK;
}

esp_err_t sub_sdcard_format(void)
{
    if (s_sd_card == NULL) return ESP_ERR_INVALID_STATE;
    return esp_vfs_fat_sdcard_format(SUB_SDCARD_MOUNT_POINT, s_sd_card);
}
