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
#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hal_types.h"
#include "sub_sdcard.h"

static const char *TAG = "sub_sdcard";

static sdmmc_card_t *s_sd_card = NULL;
static TaskHandle_t  s_mount_task = NULL;

static void sdcard_mount_worker_task(void *pvParameters)
{
    (void)pvParameters;
    if (!sub_sdcard_probe()) {
        ESP_LOGD(TAG, "MicroSD pre-flight check: No card detected in slot. Skipping mount.");
        s_mount_task = NULL;
        vTaskDelete(NULL);
        return;
    }

    esp_err_t err = sub_sdcard_mount();
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "Asynchronous MicroSD mount successful.");
    } else {
        ESP_LOGD(TAG, "Asynchronous MicroSD mount failed: %s (no card inserted or unformatted)", esp_err_to_name(err));
    }
    s_mount_task = NULL;
    vTaskDelete(NULL);
}

bool sub_sdcard_probe(void)
{
    if (s_sd_card != NULL) {
        return true;
    }

    /* Fast electrical check on DAT0 (GPIO 40) and CMD (GPIO 41):
     * Pull down briefly. SD cards actively pull DAT0/CMD high on power-up.
     * If floating or pulled down, no card is physically attached. */
    gpio_config_t probe_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_SD_MISO) | (1ULL << HAL_PIN_SD_MOSI),
        .mode         = GPIO_MODE_INPUT,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_ENABLE,
        .intr_type    = GPIO_INTR_DISABLE,
    };
    gpio_config(&probe_cfg);
    esp_rom_delay_us(100);

    int miso_lvl = gpio_get_level(HAL_PIN_SD_MISO);
    int mosi_lvl = gpio_get_level(HAL_PIN_SD_MOSI);

    /* Release pull-downs and de-init pins back to default reset state so SDMMC host receives pristine pads */
    gpio_pulldown_dis(HAL_PIN_SD_MISO);
    gpio_pulldown_dis(HAL_PIN_SD_MOSI);
    gpio_reset_pin(HAL_PIN_SD_MISO);
    gpio_reset_pin(HAL_PIN_SD_MOSI);

    /* If either pin was pulled high against the internal pulldown, card is detected */
    return (miso_lvl != 0 || mosi_lvl != 0);
}

esp_err_t sub_sdcard_mount_async(void)
{
    if (s_sd_card != NULL) {
        return ESP_OK;
    }
    if (s_mount_task != NULL) {
        /* Mount already in progress */
        return ESP_OK;
    }

    BaseType_t res = xTaskCreate(sdcard_mount_worker_task, "sd_mount", 3584, NULL, 2, &s_mount_task);
    return (res == pdPASS) ? ESP_OK : ESP_FAIL;
}

esp_err_t sub_sdcard_mount(void)
{
    if (s_sd_card != NULL) {
        ESP_LOGW(TAG, "SD Card already mounted");
        return ESP_OK;
    }

    /* Fast pre-flight check: don't touch SDMMC peripheral if slot is empty */
    if (!sub_sdcard_probe()) {
        ESP_LOGD(TAG, "MicroSD pre-flight check: No card detected. Skipping SDMMC bus init.");
        return ESP_ERR_NOT_FOUND;
    }

    /* FatFS Mount Configuration:
     * .allocation_unit_size specifies cluster size in bytes ONLY if the card is formatted
     * by FatFS (i.e. format_if_mount_failed == true). Setting to 0 enables FatFS auto-allocation
     * based on SD card volume geometry and sector count. */
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files              = 5,
        .allocation_unit_size   = 0, /* 0 = Auto-determine cluster allocation unit */
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
        gpio_reset_pin(HAL_PIN_SD_CLK);
        gpio_reset_pin(HAL_PIN_SD_MOSI);
        gpio_reset_pin(HAL_PIN_SD_MISO);
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
    gpio_reset_pin(HAL_PIN_SD_CLK);
    gpio_reset_pin(HAL_PIN_SD_MOSI);
    gpio_reset_pin(HAL_PIN_SD_MISO);
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
