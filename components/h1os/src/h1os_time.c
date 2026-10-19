/**
 * @file h1os_time.c
 * @brief Layer 4: System Time Services, Timezone Management & RTC Bridge Implementation
 *
 * SPDX-License-Identifier: MIT
 */

#include "h1os_time.h"

#include "esp_log.h"
#include "esp_timer.h"
#include "sub_rtc.h"

#include <stdio.h>
#include <string.h>
#include <sys/time.h>

static const char *TAG = "h1os_time";

static h1os_time_sync_cb_t s_sync_cb        = NULL;
static void               *s_sync_user_data = NULL;

esp_err_t h1os_time_set_timezone(const char *tz_str)
{
    if (tz_str == NULL || strlen(tz_str) == 0 || strlen(tz_str) > 64) {
        tz_str = "UTC";
    }
    setenv("TZ", tz_str, 1);
    tzset();
    ESP_LOGI(TAG, "System timezone set to: %s", tz_str);
    return ESP_OK;
}

esp_err_t h1os_time_register_sync_cb(h1os_time_sync_cb_t cb, void *user_data)
{
    s_sync_cb        = cb;
    s_sync_user_data = user_data;
    return ESP_OK;
}

esp_err_t h1os_time_sync_system_to_rtc(void)
{
    time_t    now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);

    esp_err_t ret = sub_rtc_set_time(&timeinfo);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "Synchronized PCF85063A RTC from POSIX clock: %04d-%02d-%02d %02d:%02d:%02d",
                 timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday, timeinfo.tm_hour,
                 timeinfo.tm_min, timeinfo.tm_sec);
    } else {
        ESP_LOGE(TAG, "Failed to write PCF85063A RTC: %s", esp_err_to_name(ret));
    }
    return ret;
}

esp_err_t h1os_time_sync_rtc_to_system(void)
{
    struct tm tm_target;
    esp_err_t ret = sub_rtc_get_time(&tm_target);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read PCF85063A RTC: %s", esp_err_to_name(ret));
        return ret;
    }

    time_t t = mktime(&tm_target);
    if (t == (time_t)-1) {
        ESP_LOGE(TAG, "mktime() failed to convert PCF85063A time structure");
        return ESP_FAIL;
    }

    struct timeval tv = {.tv_sec = t, .tv_usec = 0};
    settimeofday(&tv, NULL);
    ESP_LOGI(TAG, "Synchronized POSIX clock from PCF85063A: %04d-%02d-%02d %02d:%02d:%02d",
             tm_target.tm_year + 1900, tm_target.tm_mon + 1, tm_target.tm_mday, tm_target.tm_hour,
             tm_target.tm_min, tm_target.tm_sec);
    return ESP_OK;
}

esp_err_t h1os_time_sync_now(uint32_t timeout_ms)
{
    if (s_sync_cb == NULL) {
        ESP_LOGW(TAG, "No time sync callback registered");
        return ESP_ERR_NOT_SUPPORTED;
    }

    ESP_LOGI(TAG, "Invoking external time sync callback (timeout: %lu ms)...",
             (unsigned long)timeout_ms);
    esp_err_t ret = s_sync_cb(timeout_ms, s_sync_user_data);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "Time acquisition successful; committing to hardware RTC");
        h1os_time_sync_system_to_rtc();
    } else {
        ESP_LOGW(TAG, "Time sync callback failed: %s", esp_err_to_name(ret));
    }
    return ret;
}

esp_err_t h1os_time_get_formatted(h1os_time_format_t fmt, char *dest, size_t max_len)
{
    if (dest == NULL || max_len == 0)
        return ESP_ERR_INVALID_ARG;

    time_t    now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);

    const char *format_str;
    switch (fmt) {
    case H1OS_TIME_FMT_24H_SEC:
        format_str = "%H:%M:%S";
        break;
    case H1OS_TIME_FMT_24H_MIN:
        format_str = "%H:%M";
        break;
    case H1OS_TIME_FMT_12H_SEC:
        format_str = "%I:%M:%S %p";
        break;
    case H1OS_TIME_FMT_12H_MIN:
        format_str = "%I:%M %p";
        break;
    default:
        return ESP_ERR_INVALID_ARG;
    }

    size_t written = strftime(dest, max_len, format_str, &timeinfo);
    return (written > 0) ? ESP_OK : ESP_FAIL;
}

esp_err_t h1os_time_get_date_formatted(h1os_date_format_t fmt, char *dest, size_t max_len)
{
    if (dest == NULL || max_len == 0)
        return ESP_ERR_INVALID_ARG;

    time_t    now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);

    const char *format_str;
    switch (fmt) {
    case H1OS_DATE_FMT_MM_DD_YY:
        format_str = "%m/%d/%y";
        break;
    case H1OS_DATE_FMT_DOW:
        format_str = "%A";
        break;
    case H1OS_DATE_FMT_MM_DD_YY_DOW:
        format_str = "%m/%d/%y %A";
        break;
    default:
        return ESP_ERR_INVALID_ARG;
    }

    size_t written = strftime(dest, max_len, format_str, &timeinfo);
    return (written > 0) ? ESP_OK : ESP_FAIL;
}
