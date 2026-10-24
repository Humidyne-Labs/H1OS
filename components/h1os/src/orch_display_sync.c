/**
 * @file orch_display_sync.c
 * @brief Layer 3: Deferred flash frame sync engine implementation
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "h1os/orch_display_sync.h"

#include "esp_log.h"
#include "h1os/hal_flash.h"
#include "h1os/orch_state.h"
#include "h1os/sub_display.h"
#include "sdkconfig.h"

#include <string.h>

#ifndef CONFIG_H1OS_EPD_PARTIAL_REFRESH_LIMIT
#define CONFIG_H1OS_EPD_PARTIAL_REFRESH_LIMIT 6
#endif

static const char *TAG = "orch_display_sync";

static bool s_frame_dirty = false;

/**
 * @brief Synchronize latest SSD1681 on-glass temperature into persisted RTC state.
 */
static inline void orch_display_sync_latch_glass_temp(void)
{
    int16_t glass_cc = sub_display_get_glass_temp_centi_c();
    if (glass_cc != 0) {
        orch_state_get()->last_glass_temp_centi_c = glass_cc;
    }
}

/**
 * @brief Mark the current display framebuffer as dirty (needs flash persistence on sleep).
 */
void orch_display_sync_mark_dirty(void)
{
    orch_display_sync_latch_glass_temp();
    s_frame_dirty = true;
}

/**
 * @brief Save working display framebuffer to "epd_frame" flash partition if dirty.
 *
 * @return ESP_OK on success or if clean (no write needed).
 */
esp_err_t orch_display_sync_save_if_dirty(void)
{
    orch_display_sync_latch_glass_temp();
    if (!s_frame_dirty) {
        return ESP_OK;
    }

    uint8_t *fb = sub_display_get_framebuffer();
    if (fb == NULL)
        return ESP_ERR_INVALID_STATE;

    esp_err_t err = hal_flash_write_frame(fb, EPD_BUFFER_SIZE);
    if (err == ESP_OK) {
        s_frame_dirty = false;
        orch_state_get()->flags |= ORCH_FLAG_EPD_FRAME_VALID;
        ESP_LOGI(TAG, "Persisted 5000-byte EPD frame to flash partition");
    } else {
        ESP_LOGW(TAG, "Failed to persist EPD frame to flash: %s", esp_err_to_name(err));
    }
    return err;
}

/**
 * @brief Restore framebuffer from "epd_frame" flash partition into display working buffer.
 *
 * @return ESP_OK on success, ESP_ERR_NOT_FOUND if partition empty/invalid.
 */
esp_err_t orch_display_sync_restore_to_framebuffer(void)
{
    orch_display_sync_latch_glass_temp();
    volatile orch_persisted_state_t *st = orch_state_get();
    if (!(st->flags & ORCH_FLAG_EPD_FRAME_VALID)) {
        return ESP_ERR_NOT_FOUND;
    }

    uint8_t *fb = sub_display_get_framebuffer();
    if (fb == NULL)
        return ESP_ERR_INVALID_STATE;

    esp_err_t err = hal_flash_read_frame(fb, EPD_BUFFER_SIZE);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "Restored 5000-byte EPD frame from flash partition");

        sub_display_sync_previous_frame(fb);
    } else {
        ESP_LOGW(TAG, "Failed to read EPD frame from flash: %s", esp_err_to_name(err));
    }
    return err;
}

/**
 * @brief Determine if a full OTP display refresh is required.
 *
 * @details Evaluates whether the anti-ghosting partial refresh limit has been reached.
 *
 * @return true if full refresh required, false if differential partial refresh is permitted.
 */
bool orch_display_sync_should_full_refresh(void)
{
    volatile orch_persisted_state_t *st = orch_state_get();

    if (st->epd_partial_refresh_count >= CONFIG_H1OS_EPD_PARTIAL_REFRESH_LIMIT) {
        ESP_LOGI(TAG, "Anti-ghosting quota reached (%u partial refreshes >= limit %d) -> Full refresh required",
                        (unsigned)st->epd_partial_refresh_count,
                        CONFIG_H1OS_EPD_PARTIAL_REFRESH_LIMIT);
        return true;
    }

    return false;
}

/**
 * @brief Record execution of a differential partial refresh.
 *
 * @details Increments the accumulated partial refresh counter in persistent RTC memory.
 */
void orch_display_sync_record_partial_refresh(void)
{
    volatile orch_persisted_state_t *st = orch_state_get();
    st->epd_partial_refresh_count++;
    ESP_LOGD(TAG, "Recorded differential partial refresh #%u / %d",
                    (unsigned)st->epd_partial_refresh_count,
                    CONFIG_H1OS_EPD_PARTIAL_REFRESH_LIMIT);
}

/**
 * @brief Record execution of a full OTP display refresh.
 *
 * @details Resets the accumulated partial refresh counter back to 0.
 */
void orch_display_sync_record_full_refresh(void)
{
    volatile orch_persisted_state_t *st = orch_state_get();
    st->epd_partial_refresh_count = 0;
    ESP_LOGI(TAG, "Full OTP refresh recorded: anti-ghosting counter reset to 0");
}

/**
 * @brief Get the accumulated count of partial refreshes since the last full refresh.
 *
 * @return Return value of type uint16_t.
 */
uint16_t orch_display_sync_get_partial_count(void)
{
    return orch_state_get()->epd_partial_refresh_count;
}
