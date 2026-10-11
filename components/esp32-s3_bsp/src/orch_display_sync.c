/**
 * @file orch_display_sync.c
 * @brief Layer 3: Deferred Flash Frame Sync Engine Implementation
 *
 * SPDX-License-Identifier: MIT
 */

#include "bsp/orch_display_sync.h"
#include "bsp/orch_state.h"
#include "bsp/sub_display.h"
#include "bsp/hal_flash.h"
#include "esp_log.h"
#include <string.h>

static const char *TAG = "orch_display_sync";

static bool s_frame_dirty = false;

void orch_display_sync_mark_dirty(void)
{
    s_frame_dirty = true;
}

esp_err_t orch_display_sync_save_if_dirty(void)
{
    if (!s_frame_dirty) {
        return ESP_OK;
    }

    uint8_t *fb = sub_display_get_framebuffer();
    if (fb == NULL) return ESP_ERR_INVALID_STATE;

    /* Write to epd_frame raw flash partition */
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

esp_err_t orch_display_sync_restore_to_framebuffer(void)
{
    orch_persisted_state_t *st = orch_state_get();
    if (!(st->flags & ORCH_FLAG_EPD_FRAME_VALID)) {
        return ESP_ERR_NOT_FOUND;
    }

    uint8_t *fb = sub_display_get_framebuffer();
    if (fb == NULL) return ESP_ERR_INVALID_STATE;

    esp_err_t err = hal_flash_read_frame(fb, EPD_BUFFER_SIZE);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "Restored 5000-byte EPD frame from flash partition");
    }
    return err;
}
