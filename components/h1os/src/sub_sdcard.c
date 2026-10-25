/**
 * @file sub_sdcard.c
 * @brief Layer 2: MicroSD card subsystem manager implementation
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "sub_sdcard.h"

#include "driver/gpio.h"
#include "driver/sdmmc_host.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hal_types.h"
#include "sdmmc_cmd.h"

#include <stdio.h>
#include <string.h>

static const char *TAG = "sub_sdcard";

#define SUB_SDCARD_TASK_STACK_MOUNT     4096U /**< SD mount worker task stack depth.     */
#define SUB_SDCARD_TASK_PRIO_MOUNT      2     /**< SD mount worker task priority.        */
#define SUB_SDCARD_COMMAND_TIMEOUT_MS   500U  /**< SD card command timeout (500 ms).     */
#define SUB_SDCARD_UNMOUNT_DRAIN_CYCLES 50U   /**< Max 10 ms drain cycles awaiting mount.*/

static sdmmc_card_t *s_sd_card = NULL;
static volatile TaskHandle_t s_mount_task = NULL;
static bool s_card_absent_latched = false;

/**
 * @brief Sdcard mount worker task.
 *
 * @param[in]    pvParameters    Parameter pvParameters.
 *
 * @return Return value of type static void.
 */
static void sdcard_mount_worker_task(void *pvParameters)
{
    (void)pvParameters;
    if (s_card_absent_latched) {
        ESP_LOGD(TAG, "MicroSD slot known empty (latched). Bypassing async mount.");
        s_mount_task = NULL;
        vTaskDelete(NULL);
        return;
    }

    esp_err_t err = sub_sdcard_mount();
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "Asynchronous MicroSD mount successful.");
    } else {
        ESP_LOGD(TAG, "Asynchronous MicroSD mount result: %s (slot empty or unformatted)", esp_err_to_name(err));
    }
    s_mount_task = NULL;
    vTaskDelete(NULL);
}

/**
 * @brief Asynchronously mount MicroSD card in a background FreeRTOS task.
 *
 * @details Does not block caller or freeze UI refresh if card is missing.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_sdcard_mount_async(void)
{
    if (s_sd_card != NULL) {
        return ESP_OK;
    }
    if (s_card_absent_latched) {
        return ESP_ERR_NOT_FOUND;
    }
    if (s_mount_task != NULL) {
        return ESP_OK;
    }

    TaskHandle_t handle = NULL;
    BaseType_t res = xTaskCreate(sdcard_mount_worker_task, "sd_mount", SUB_SDCARD_TASK_STACK_MOUNT, NULL, SUB_SDCARD_TASK_PRIO_MOUNT, &handle);
    if (res == pdPASS) {
        s_mount_task = handle;
        return ESP_OK;
    }
    return ESP_FAIL;
}

/**
 * @brief Mount MicroSD card using 1-bit SDMMC driver (synchronous).
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_sdcard_mount(void)
{
    if (s_sd_card != NULL) {
        ESP_LOGW(TAG, "SD Card already mounted");
        return ESP_OK;
    }
    if (s_card_absent_latched) {
        return ESP_ERR_NOT_FOUND;
    }

    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 0,
    };

    sdmmc_host_t host = SDMMC_HOST_DEFAULT();
    host.max_freq_khz = SDMMC_FREQ_DEFAULT;
    host.flags = SDMMC_HOST_FLAG_1BIT;
    host.command_timeout_ms = SUB_SDCARD_COMMAND_TIMEOUT_MS;

    sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
    slot_config.width = 1;
    slot_config.clk = HAL_PIN_SD_CLK;
    slot_config.cmd = HAL_PIN_SD_MOSI;
    slot_config.d0 = HAL_PIN_SD_MISO;
    slot_config.cd = SDMMC_SLOT_NO_CD;
    slot_config.wp = SDMMC_SLOT_NO_WP;

    esp_log_level_set("sdmmc_common", ESP_LOG_NONE);
    esp_log_level_set("vfs_fat_sdmmc", ESP_LOG_NONE);
    esp_log_level_set("sdmmc_cmd", ESP_LOG_NONE);
    esp_log_level_set("sdmmc_sd", ESP_LOG_NONE);
    esp_log_level_set("sdmmc_io", ESP_LOG_NONE);
    esp_log_level_set("SD_HOST", ESP_LOG_NONE);
    esp_log_level_set("SD_TRANS", ESP_LOG_NONE);

    esp_err_t ret = esp_vfs_fat_sdmmc_mount(SUB_SDCARD_MOUNT_POINT, &host, &slot_config, &mount_config, &s_sd_card);

    esp_log_level_set("sdmmc_common", ESP_LOG_WARN);
    esp_log_level_set("vfs_fat_sdmmc", ESP_LOG_WARN);
    esp_log_level_set("sdmmc_cmd", ESP_LOG_WARN);
    esp_log_level_set("sdmmc_sd", ESP_LOG_WARN);
    esp_log_level_set("sdmmc_io", ESP_LOG_WARN);
    esp_log_level_set("SD_HOST", ESP_LOG_WARN);
    esp_log_level_set("SD_TRANS", ESP_LOG_WARN);

    if (ret != ESP_OK) {
        s_sd_card = NULL;
        s_card_absent_latched = true;
        gpio_reset_pin(HAL_PIN_SD_CLK);
        gpio_reset_pin(HAL_PIN_SD_MOSI);
        gpio_reset_pin(HAL_PIN_SD_MISO);
        ESP_LOGD(TAG, "MicroSD card not detected in slot (%s). Absent state latched.", esp_err_to_name(ret));
        return ret;
    }

    ESP_LOGI(TAG, "MicroSD card mounted successfully at %s", SUB_SDCARD_MOUNT_POINT);
    return ESP_OK;
}

/**
 * @brief Unmount MicroSD card and release hardware bus resources.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_sdcard_unmount(void)
{
    /* Wait briefly if an asynchronous mount worker is still in flight */
    int32_t wait_cycles = (int32_t)SUB_SDCARD_UNMOUNT_DRAIN_CYCLES;
    while (s_mount_task != NULL && wait_cycles-- > 0) {
        vTaskDelay(pdMS_TO_TICKS(10));
    }

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

/**
 * @brief Check if MicroSD card is mounted and ready for I/O.
 *
 * @return True on success, false otherwise.
 */
bool sub_sdcard_is_mounted(void)
{
    return (s_sd_card != NULL);
}

/**
 * @brief Get total capacity of mounted card in megabytes.
 *
 * @param[out]   out_capacity_mb Parameter out_capacity_mb.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_sdcard_get_capacity_mb(uint32_t *out_capacity_mb)
{
    if (!out_capacity_mb) {
        return ESP_ERR_INVALID_ARG;
    }
    if (s_sd_card == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    uint64_t bytes = ((uint64_t)s_sd_card->csd.capacity) * s_sd_card->csd.sector_size;
    *out_capacity_mb = (uint32_t)(bytes / (1024ULL * 1024ULL));
    return ESP_OK;
}

/**
 * @brief Format mounted card as FAT32 filesystem.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_sdcard_format(void)
{
    if (s_sd_card == NULL) {
        return ESP_ERR_INVALID_STATE;
    }
    return esp_vfs_fat_sdcard_format(SUB_SDCARD_MOUNT_POINT, s_sd_card);
}
