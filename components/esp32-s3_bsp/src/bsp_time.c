/**
 * @file bsp_time.c
 * @brief SNTP Synchronization, Timezone Management & RTC Bridge Implementation
 *
 * @version 1.0.0
 * @attribution
 * - Architecture & Development: HUMIDYNE LABS / Humiditron
 * - AI Systems Co-Developer: Gemini (Google DeepMind)
 * - Hardware Target: Waveshare Electronics ESP32-S3 ePaper 1.54 V2
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "bsp/sub_rtc.h"
#include "bsp/bsp_time.h"

static const char *TAG = "bsp_time";

static bsp_time_sync_cb_t s_sync_cb        = NULL;
static void              *s_sync_user_data = NULL;
static esp_timer_handle_t s_periodic_sync_timer = NULL;

esp_err_t bsp_time_set_timezone(const char *tz_str) {
    if (tz_str == NULL || strlen(tz_str) == 0) 
		tz_str = "UTC";
	
    setenv("TZ", tz_str, 1);
    tzset();
    ESP_LOGI(TAG, "System timezone set to: %s", tz_str);
    return ESP_OK;
}

esp_err_t bsp_time_sync_system_to_rtc(void)
{
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);

    esp_err_t ret = sub_rtc_set_time(&timeinfo);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "Synchronized PCF85063A RTC from POSIX clock: %04d-%02d-%02d %02d:%02d:%02d",
                 timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday,
                 timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
    } else {
        ESP_LOGE(TAG, "Failed to write PCF85063A RTC: %s", esp_err_to_name(ret));
    }
    return ret;
}

esp_err_t bsp_time_sync_rtc_to_system(void)
{
    struct tm tm_target;
    esp_err_t ret = sub_rtc_get_time(&tm_target);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read PCF85063A RTC: %s", esp_err_to_name(ret));
        return ret;
    }

    time_t t = mktime(&tm_target);
    if (t == (time_t)-1) {
        ESP_LOGE(TAG, "Failed to convert RTC date to time_t");
        return ESP_FAIL;
    }

    struct timeval tv = { .tv_sec = t, .tv_usec = 0 };
    settimeofday(&tv, NULL);
    ESP_LOGI(TAG, "Synchronized ESP32 system clock from PCF85063A RTC: %04d-%02d-%02d %02d:%02d:%02d",
             tm_target.tm_year + 1900, tm_target.tm_mon + 1, tm_target.tm_mday,
             tm_target.tm_hour, tm_target.tm_min, tm_target.tm_sec);
    return ESP_OK;
}

esp_err_t bsp_time_register_sync_cb(bsp_time_sync_cb_t cb, void *user_data)
{
    s_sync_cb        = cb;
    s_sync_user_data = user_data;
    ESP_LOGI(TAG, "External time synchronization callback registered");
    return ESP_OK;
}

esp_err_t bsp_time_sntp_sync(uint32_t timeout_ms)
{
    if (s_sync_cb == NULL) {
        ESP_LOGD(TAG, "No external time sync callback registered; running on PCF85063A RTC");
        return ESP_ERR_NOT_SUPPORTED;
    }

    ESP_LOGI(TAG, "Invoking external time sync callback (timeout: %lu ms)...", (unsigned long)timeout_ms);
    esp_err_t err = s_sync_cb(timeout_ms, s_sync_user_data);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "External time sync successful; writing to PCF85063A RTC hardware");
        bsp_time_sync_system_to_rtc();
    } else {
        ESP_LOGW(TAG, "External time sync callback failed: %s", esp_err_to_name(err));
    }
    return err;
}

esp_err_t bsp_time_get_formatted(bsp_time_format_t fmt, char *dest, size_t max_len)
{
    if (dest == NULL || max_len < 16) return ESP_ERR_INVALID_ARG;

    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);

    switch (fmt) {
        case BSP_TIME_FMT_24H_SEC:
            strftime(dest, max_len, "%H:%M:%S", &timeinfo);
            break;
        case BSP_TIME_FMT_24H_MIN:
            strftime(dest, max_len, "%H:%M", &timeinfo);
            break;
        case BSP_TIME_FMT_12H_SEC:
            strftime(dest, max_len, "%I:%M:%S %p", &timeinfo);
            break;
        case BSP_TIME_FMT_12H_MIN:
            strftime(dest, max_len, "%I:%M %p", &timeinfo);
            break;
        default:
            strftime(dest, max_len, "%H:%M:%S", &timeinfo);
            break;
    }
    return ESP_OK;
}

esp_err_t bsp_time_get_date_formatted(bsp_date_format_t fmt, char *dest, size_t max_len)
{
    if (dest == NULL || max_len < 16) return ESP_ERR_INVALID_ARG;

    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);

    switch (fmt) {
        case BSP_DATE_FMT_MM_DD_YY:
            strftime(dest, max_len, "%m/%d/%y", &timeinfo);
            break;
        case BSP_DATE_FMT_DOW:
            strftime(dest, max_len, "%A", &timeinfo);
            break;
        case BSP_DATE_FMT_MM_DD_YY_DOW:
            strftime(dest, max_len, "%m/%d/%y %A", &timeinfo);
            break;
        default:
            strftime(dest, max_len, "%m/%d/%y", &timeinfo);
            break;
    }
    return ESP_OK;
}

esp_err_t bsp_time_get_date_str(char *dest, size_t max_len) {
    return bsp_time_get_date_formatted(BSP_DATE_FMT_MM_DD_YY, dest, max_len);
}

esp_err_t bsp_time_get_dow_str(char *dest, size_t max_len) {
    return bsp_time_get_date_formatted(BSP_DATE_FMT_DOW, dest, max_len);
}

esp_err_t bsp_time_get_date_dow_str(char *dest, size_t max_len) {
    return bsp_time_get_date_formatted(BSP_DATE_FMT_MM_DD_YY_DOW, dest, max_len);
}

static void periodic_sync_timer_cb(void *arg) {
    ESP_LOGI(TAG, "Periodic time sync timer triggered");
    bsp_time_sntp_sync(8000);
}

esp_err_t bsp_time_start_periodic_sync(uint32_t interval_sec) {
    if (interval_sec == 0) interval_sec = 86400; // Default: 24 Hours

    if (s_periodic_sync_timer != NULL) {
        esp_timer_stop(s_periodic_sync_timer);
        esp_timer_delete(s_periodic_sync_timer);
        s_periodic_sync_timer = NULL;
    }

    esp_timer_create_args_t timer_args = {
        .callback = periodic_sync_timer_cb,
        .name     = "bsp_sntp_sync_timer",
    };
    esp_err_t ret = esp_timer_create(&timer_args, &s_periodic_sync_timer);
    if (ret != ESP_OK) return ret;

    return esp_timer_start_periodic(s_periodic_sync_timer, (uint64_t)interval_sec * 1000000ULL);
}

void bsp_time_stop_periodic_sync(void) {
    if (s_periodic_sync_timer != NULL) {
        esp_timer_stop(s_periodic_sync_timer);
        esp_timer_delete(s_periodic_sync_timer);
        s_periodic_sync_timer = NULL;
    }
}
