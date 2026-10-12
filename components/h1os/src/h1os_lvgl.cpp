/**
 * @file h1os_lvgl.cpp
 * @brief Layer 4: LVGL v9 FreeRTOS Integration Port & Keypad Input Implementation
 *
 * SPDX-License-Identifier: MIT
 */

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "esp_heap_caps.h"
#include "sub_display.h"
#include "hal_io.h"
#include "hal_types.h"
#include "h1os_lvgl.h"
#include "h1os.h"
#include "orch_display_sync.h"
#include "display/lv_display_private.h"
#include "sdkconfig.h"

static const char *TAG = "h1os_lvgl";

static lv_display_t *s_lv_display       = NULL;
static lv_indev_t   *s_lv_keypad_indev  = NULL;
static TaskHandle_t  s_lvgl_task_handle = NULL;
static bool          s_lvgl_task_running = false;
static bool          s_first_boot_flush  = true;

#define LVGL_I1_PALETTE_SIZE  8

static void h1os_lvgl_port_task(void *pvParameters);

bool h1os_lvgl_lock(uint32_t timeout_ms) {
    lv_lock();
    return true;
}

void h1os_lvgl_unlock(void) {
    lv_unlock();
}

static uint32_t lvgl_tick_get_cb(void) {
    return (uint32_t)(esp_timer_get_time() / 1000ULL);
}

static void lvgl_keypad_read_cb(lv_indev_t *indev, lv_indev_data_t *data) {
    data->state = LV_INDEV_STATE_RELEASED;
    data->key   = 0;

    uint32_t btns = (uint32_t)hal_io_read_buttons();

    if (btns & HAL_BTN_BOOT) {
        data->state = LV_INDEV_STATE_PRESSED;
        data->key   = LV_KEY_RIGHT;
        h1os_reset_session_timer();
    } else if (btns & HAL_BTN_POWER) {
        data->state = LV_INDEV_STATE_PRESSED;
        data->key   = LV_KEY_ENTER;
        h1os_reset_session_timer();
    }
}

static void lvgl_display_flush_cb(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
    lv_color_format_t cf = lv_display_get_color_format(disp);
    if (cf != LV_COLOR_FORMAT_I1) {
        lv_display_flush_ready(disp);
        return;
    }

    lv_obj_t *act_scr = lv_display_get_screen_active(disp);
    if (act_scr != NULL && lv_obj_get_child_count(act_scr) == 0) {
        lv_display_flush_ready(disp);
        return;
    }

    const uint8_t *src_buf  = px_map + LVGL_I1_PALETTE_SIZE;
    uint8_t       *dest_buf = sub_display_get_framebuffer();

    uint16_t area_w     = (area->x2 - area->x1 + 1);
    uint16_t area_h     = (area->y2 - area->y1 + 1);
    uint32_t src_stride = lv_draw_buf_width_to_stride(area_w, LV_COLOR_FORMAT_I1);

    if ((area->x1 % 8 == 0) && (area_w % 8 == 0) && (dest_buf != NULL)) {
        uint16_t bytes_per_line = area_w   / 8;
        uint16_t start_byte_x   = area->x1 / 8;

        for (uint16_t y = 0; y < area_h; y++) {
            uint16_t      dst_y      = area->y1 + y;
            uint32_t      dst_offset = (dst_y * (EPD_WIDTH / 8)) + start_byte_x;
            const uint8_t *src       = src_buf + (y * src_stride);
            uint8_t       *dst       = dest_buf + dst_offset;

            if (((uintptr_t)src % 4 == 0) && ((uintptr_t)dst % 4 == 0) && (bytes_per_line % 4 == 0)) {
                const uint32_t *src32 = (const uint32_t *)src;
                uint32_t       *dst32 = (uint32_t *)dst;
                uint16_t        words = bytes_per_line / 4;
                for (uint16_t i = 0; i < words; i++) dst32[i] = src32[i];
            } else {
                memcpy(dst, src, bytes_per_line);
            }
        }
    } else if (dest_buf != NULL) {
        for (uint16_t y = 0; y < area_h; y++) {
            const uint8_t *src_line = src_buf + (y * src_stride);
            uint16_t       dst_y    = area->y1 + y;

            for (uint16_t x = 0; x < area_w; x++) {
                uint8_t bit_val = (src_line[x >> 3] >> (7 - (x & 0x07))) & 0x01;
                uint16_t px = area->x1 + x;
                if (px < EPD_WIDTH && dst_y < EPD_HEIGHT) {
                    uint32_t byte_idx = (dst_y * (EPD_WIDTH / 8)) + (px / 8);
                    uint8_t bit_mask = 1 << (7 - (px % 8));
                    if (bit_val) {
                        dest_buf[byte_idx] |= bit_mask;
                    } else {
                        dest_buf[byte_idx] &= ~bit_mask;
                    }
                }
            }
        }
    }

    if (lv_display_flush_is_last(disp)) {
        orch_display_sync_mark_dirty();
        if (s_first_boot_flush) {
            sub_display_refresh_full();
            s_first_boot_flush = false;
        } else {
            sub_display_refresh_partial();
        }
    }

    lv_display_flush_ready(disp);
}

esp_err_t h1os_lvgl_init(void)
{
    if (s_lv_display != NULL) return ESP_OK;

    esp_err_t ret = sub_display_init(false);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize display hardware: %s", esp_err_to_name(ret));
        return ret;
    }

    lv_init();
    lv_tick_set_cb(lvgl_tick_get_cb);

    s_lv_display = lv_display_create(EPD_WIDTH, EPD_HEIGHT);
    if (s_lv_display == NULL) {
        ESP_LOGE(TAG, "Failed to create LVGL display");
        return ESP_FAIL;
    }

    lv_display_set_color_format(s_lv_display, LV_COLOR_FORMAT_I1);

    uint32_t buffer_lines = 40;
    uint32_t stride       = lv_draw_buf_width_to_stride(EPD_WIDTH, LV_COLOR_FORMAT_I1);
    size_t   buf_size     = (stride * buffer_lines) + LVGL_I1_PALETTE_SIZE;
    uint8_t  *buf1        = (uint8_t *)heap_caps_aligned_calloc(64, 1, buf_size, MALLOC_CAP_DMA | MALLOC_CAP_8BIT);
    if (buf1 == NULL) {
        buf1 = (uint8_t *)heap_caps_aligned_calloc(64, 1, buf_size, MALLOC_CAP_8BIT);
    }
    assert(buf1 != NULL);

    lv_color32_t palette[2];
    palette[0] = lv_color32_make(0x00, 0x00, 0x00, 0xFF);
    palette[1] = lv_color32_make(0xFF, 0xFF, 0xFF, 0xFF);
    memcpy(buf1, palette, LVGL_I1_PALETTE_SIZE);

    memset(buf1 + LVGL_I1_PALETTE_SIZE, 0xFF, buf_size - LVGL_I1_PALETTE_SIZE);

    lv_display_set_buffers(s_lv_display, buf1, NULL, buf_size, LV_DISPLAY_RENDER_MODE_PARTIAL);
    lv_display_set_flush_cb(s_lv_display, lvgl_display_flush_cb);

    s_lv_keypad_indev = lv_indev_create();
    if (s_lv_keypad_indev != NULL) {
        lv_indev_set_type(s_lv_keypad_indev, LV_INDEV_TYPE_KEYPAD);
        lv_indev_set_read_cb(s_lv_keypad_indev, lvgl_keypad_read_cb);
        lv_indev_set_long_press_time(s_lv_keypad_indev, 2000); /* 2.0s hold for shutdown */
        lv_indev_set_long_press_repeat_time(s_lv_keypad_indev, 0);
        ESP_LOGI(TAG, "Registered LVGL keypad indev handler (Long-press: 2000ms)");
    }

    ESP_LOGI(TAG, "LVGL v9 port initialized in 1-bit monochrome mode");
    return ESP_OK;
}

esp_err_t h1os_lvgl_start(int task_priority, int core_id)
{
    if (s_lvgl_task_handle != NULL) return ESP_OK;

    esp_err_t ret = h1os_lvgl_init();
    if (ret != ESP_OK) return ret;

    task_priority = (task_priority > 0) ? task_priority : 5;
    core_id       = ((core_id >= 0) && (core_id < (int)configNUM_CORES)) ? core_id : -1;

    BaseType_t res = xTaskCreatePinnedToCore(
        h1os_lvgl_port_task,
        "h1os_lvgl",
        8192,
        NULL,
        task_priority,
        &s_lvgl_task_handle,
        core_id
    );

    s_lvgl_task_running = (res == pdPASS);
    return s_lvgl_task_running ? ESP_OK : ESP_FAIL;
}

esp_err_t h1os_lvgl_stop(void)
{
    if (s_lvgl_task_handle != NULL) {
        s_lvgl_task_running = false;
        vTaskDelay(pdMS_TO_TICKS(50));
        if (s_lvgl_task_handle != NULL) {
            vTaskDelete(s_lvgl_task_handle);
            s_lvgl_task_handle = NULL;
        }
    }
    return ESP_OK;
}

bool h1os_lvgl_has_pending_tasks(void)
{
    if (s_lv_display == NULL) return false;
    /* Check if display refresh timer is actively scheduled / running */
    lv_timer_t *refr_timer = lv_display_get_refr_timer(s_lv_display);
    if (refr_timer != NULL && !lv_timer_get_paused(refr_timer)) {
        /* Timer is active; check if any screen layer or area is dirty */
        if (s_lv_display->inv_p > 0 || s_lv_display->rendering_in_progress) {
            return true;
        }
    }
    return false;
}

lv_indev_t* h1os_lvgl_get_indev(void)
{
    return s_lv_keypad_indev;
}

static void h1os_lvgl_port_task(void *pvParameters)
{
    ESP_LOGI(TAG, "LVGL port task active on Core %d", xPortGetCoreID());
    while (s_lvgl_task_running) {
        uint32_t delay_ms = LV_DEF_REFR_PERIOD;
        if (h1os_lvgl_lock(100)) {
            delay_ms = lv_timer_handler();
            h1os_lvgl_unlock();
        }
        delay_ms = (delay_ms == LV_NO_TIMER_READY) ? LV_DEF_REFR_PERIOD : delay_ms;
        vTaskDelay(pdMS_TO_TICKS(delay_ms));
    }
    s_lvgl_task_handle = NULL;
    vTaskDelete(NULL);
}
