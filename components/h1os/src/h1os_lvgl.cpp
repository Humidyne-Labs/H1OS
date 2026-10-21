/**
 * @file h1os_lvgl.cpp
 * @brief Layer 4: LVGL v9 FreeRTOS integration port and keypad input driver
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "h1os_lvgl.h"

#include "display/lv_display_private.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "h1os.h"
#include "hal_io.h"
#include "hal_types.h"
#include "orch_display_sync.h"
#include "sdkconfig.h"
#include "sub_display.h"
#include "sub_power.h"

#include <algorithm>
#include <assert.h>
#include <stdio.h>
#include <string.h>

static const char *TAG = "h1os_lvgl";

static lv_display_t *s_lv_display       = NULL;
static lv_indev_t   *s_lv_keypad_indev  = NULL;
static TaskHandle_t  s_lvgl_task_handle = NULL;

static volatile bool s_lvgl_task_running = false;
static volatile bool s_flush_in_progress = false;
static bool s_first_boot_flush           = true;

#define LVGL_I1_PALETTE_SIZE 8

struct CpuMaxTurboScope {
    CpuMaxTurboScope()
    {
        sub_power_cpu_max_acquire();
    }
    ~CpuMaxTurboScope()
    {
        sub_power_cpu_max_release();
    }
};

static void h1os_lvgl_port_task(void *pvParameters);

/**
 * @brief Acquire LVGL reentrant mutex lock.
 *
 * @param[in]    timeout_ms      Parameter timeout_ms.
 *
 * @return True on success, false otherwise.
 */
bool h1os_lvgl_lock(uint32_t timeout_ms)
{
    (void)timeout_ms;
    sub_power_cpu_max_acquire();
    if (s_lv_display != NULL) {
        lv_lock();
    }
    return true;
}

/**
 * @brief Release LVGL reentrant mutex lock.
 */
void h1os_lvgl_unlock(void)
{
    if (s_lv_display != NULL) {
        lv_unlock();
    }
    sub_power_cpu_max_release();
}

/**
 * @brief Lvgl tick get cb.
 *
 * @return Return value of type static uint32_t.
 */
static uint32_t lvgl_tick_get_cb(void)
{
    return (uint32_t)(esp_timer_get_time() / 1000ULL);
}

/**
 * @brief Lvgl keypad read cb.
 *
 * @param[in]    indev           Parameter indev.
 * @param[in]    data            Parameter data.
 *
 * @return Return value of type static void.
 */
static void lvgl_keypad_read_cb(lv_indev_t *indev, lv_indev_data_t *data)
{
    (void)indev;
    data->state = LV_INDEV_STATE_RELEASED;
    data->key = 0;

    uint32_t btns = (uint32_t)hal_io_read_buttons();

    static uint32_t s_prev_logged_btns = 0;
    if (btns != s_prev_logged_btns) {
        ESP_LOGI(TAG, "Hardware button event: btns=0x%02lx (BOOT=%d, PWR=%d)",
                      (unsigned long)btns,
                      (btns & HAL_BTN_BOOT)  ? 1 : 0,
                      (btns & HAL_BTN_POWER) ? 1 : 0);
        s_prev_logged_btns = btns;
    }

    if (btns & HAL_BTN_BOOT) {
        data->state = LV_INDEV_STATE_PRESSED;
        data->key = LV_KEY_RIGHT;
        h1os_reset_session_timer();
    } else if (btns & HAL_BTN_POWER) {
        data->state = LV_INDEV_STATE_PRESSED;
        data->key = LV_KEY_ENTER;
        h1os_reset_session_timer();
    }
}

/**
 * @brief Lvgl display flush cb.
 *
 * @param[in]    disp            Parameter disp.
 * @param[in]    area            Parameter area.
 * @param[in]    px_map          Parameter px_map.
 *
 * @return Return value of type static void.
 */
static void lvgl_display_flush_cb(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
    s_flush_in_progress = true;
    lv_color_format_t cf = lv_display_get_color_format(disp);
    if (cf != LV_COLOR_FORMAT_I1) {
        lv_display_flush_ready(disp);
        s_flush_in_progress = false;
        return;
    }

    lv_obj_t *act_scr = lv_display_get_screen_active(disp);
    if (act_scr != NULL && lv_obj_get_child_count(act_scr) == 0) {
        lv_display_flush_ready(disp);
        s_flush_in_progress = false;
        return;
    }

    const uint8_t *src_buf = px_map + LVGL_I1_PALETTE_SIZE;
    uint8_t *dest_buf = sub_display_get_framebuffer();

    uint16_t area_w = (area->x2 - area->x1 + 1);
    uint16_t area_h = (area->y2 - area->y1 + 1);
    uint32_t src_stride = lv_draw_buf_width_to_stride(area_w, LV_COLOR_FORMAT_I1);

    if (dest_buf == NULL || src_buf == NULL || area_w == 0 || area_h == 0) {
        lv_display_flush_ready(disp);
        s_flush_in_progress = false;
        return;
    }

    uint16_t y_start = area->y1;
    if (y_start >= EPD_HEIGHT) {
        lv_display_flush_ready(disp);
        s_flush_in_progress = false;
        return;
    }
    if (y_start + area_h > EPD_HEIGHT) {
        area_h = EPD_HEIGHT - y_start;
    }

    {
        CpuMaxTurboScope turbo;
        const uint32_t epd_stride = EPD_WIDTH / 8;

        if ((area->x1 & 7) == 0 && (area_w & 7) == 0) {
            uint16_t bytes_per_line = area_w >> 3;
            uint16_t start_byte_x = area->x1 >> 3;

            const uint8_t *src = src_buf;
            uint8_t *dst = dest_buf + (y_start * epd_stride) + start_byte_x;

            for (uint16_t y = 0; y < area_h; y++) {
                memcpy(dst, src, bytes_per_line);
                src += src_stride;
                dst += epd_stride;
            }
        } else {
            uint16_t x1 = area->x1;
            uint16_t x2 = x1 + area_w - 1;
            if (x1 < EPD_WIDTH) {
                if (x2 >= EPD_WIDTH)
                    x2 = EPD_WIDTH - 1;

                uint32_t first_byte = x1 >> 3;
                uint32_t last_byte = x2 >> 3;
                uint8_t shift = x1 & 7;

                uint8_t left_mask = 0xFF >> shift;
                uint8_t right_mask = 0xFF << (7 - (x2 & 7));

                for (uint16_t y = 0; y < area_h; y++) {
                    const uint8_t *s = src_buf + (y * src_stride);
                    uint8_t *d = dest_buf + ((y_start + y) * epd_stride) + first_byte;

                    if (first_byte == last_byte) {
                        uint8_t mask = left_mask & right_mask;
                        uint8_t val = (*s >> shift) & mask;
                        *d = (*d & ~mask) | val;
                        continue;
                    }

                    uint8_t carry = *s;
                    *d = (*d & ~left_mask) | ((carry >> shift) & left_mask);
                    d++;

                    for (uint32_t bx = first_byte + 1; bx < last_byte; bx++) {
                        s++;
                        uint8_t next = *s;
                        *d++ = (carry << (8 - shift)) | (next >> shift);
                        carry = next;
                    }

                    s++;
                    uint8_t val = (carry << (8 - shift)) | (*s >> shift);
                    *d = (*d & ~right_mask) | (val & right_mask);
                }
            }
        }
    }

    if (lv_display_flush_is_last(disp)) {
        orch_display_sync_mark_dirty();
        bool do_full = s_first_boot_flush || orch_display_sync_should_full_refresh();
        if (do_full) {
            sub_display_refresh_full();
            s_first_boot_flush = false;
            orch_display_sync_record_full_refresh();
        } else {
            sub_display_refresh_partial();
            orch_display_sync_record_partial_refresh();
        }
    }

    lv_display_flush_ready(disp);
    s_flush_in_progress = false;
}

/**
 * @brief Initialize LVGL v9 graphics subsystem, 1-bit display buffer, and keypad input driver.
 *
 * @param[in]    is_wake_cycle   True if resuming from sleep (enables differential partial flush).
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t h1os_lvgl_init(bool is_wake_cycle)
{
    if (s_lv_display != NULL)
        return ESP_OK;

    esp_err_t ret = sub_display_init(is_wake_cycle);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize display hardware: %s", esp_err_to_name(ret));
        return ret;
    }

    s_first_boot_flush = !is_wake_cycle;

    lv_init();
    lv_tick_set_cb(lvgl_tick_get_cb);

    s_lv_display = lv_display_create(EPD_WIDTH, EPD_HEIGHT);
    if (s_lv_display == NULL) {
        ESP_LOGE(TAG, "Failed to create LVGL display");
        return ESP_FAIL;
    }

    lv_display_set_color_format(s_lv_display, LV_COLOR_FORMAT_I1);

    uint32_t buffer_lines = 40;
    uint32_t stride = lv_draw_buf_width_to_stride(EPD_WIDTH, LV_COLOR_FORMAT_I1);
    size_t buf_size = (stride * buffer_lines) + LVGL_I1_PALETTE_SIZE;
    uint8_t *buf1 = (uint8_t *)heap_caps_aligned_calloc(64, 1, buf_size, MALLOC_CAP_DMA | MALLOC_CAP_8BIT);
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
        lv_indev_set_display(s_lv_keypad_indev, s_lv_display);
        lv_indev_set_read_cb(s_lv_keypad_indev, lvgl_keypad_read_cb);
        lv_indev_set_long_press_time(s_lv_keypad_indev, 2000);
        lv_indev_set_long_press_repeat_time(s_lv_keypad_indev, 0);

        lv_group_t *def_grp = lv_group_get_default();
        if (def_grp == NULL) {
            def_grp = lv_group_create();
            lv_group_set_default(def_grp);
        }
        lv_indev_set_group(s_lv_keypad_indev, def_grp);
        ESP_LOGI(TAG, "Registered LVGL keypad indev handler with default group (Long-press: 2000ms)");
    }

    ESP_LOGI(TAG, "LVGL v9 port initialized in 1-bit monochrome mode (first flush: %s)",
             s_first_boot_flush ? "FULL" : "PARTIAL");
    return ESP_OK;
}

/**
 * @brief Explicitly override whether the first flush executes a full or partial refresh.
 *
 * @param[in]    full_refresh    True for full OTP flashing refresh, False for differential partial.
 */
void h1os_lvgl_set_first_flush_mode(bool full_refresh)
{
    s_first_boot_flush = full_refresh;
}

/**
 * @brief Start the LVGL background FreeRTOS task.
 *
 * @param[in]    task_priority   Parameter task_priority.
 * @param[in]    core_id         Parameter core_id.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t h1os_lvgl_start(int task_priority, int core_id)
{
    if (s_lvgl_task_handle != NULL)
        return ESP_OK;

    esp_err_t ret = h1os_lvgl_init(false);
    if (ret != ESP_OK)
        return ret;

    task_priority = (task_priority > 0) ? task_priority : 5;
    core_id = ((core_id >= 0) && (core_id < (int)configNUM_CORES)) ? core_id : -1;

    s_lvgl_task_running = true;

    BaseType_t res = xTaskCreatePinnedToCore(h1os_lvgl_port_task,
                                             "h1os_lvgl",
                                             8192,
                                             NULL,
                                             task_priority,
                                             &s_lvgl_task_handle,
                                             core_id);

    if (res != pdPASS) {
        s_lvgl_task_running = false;
        ESP_LOGE(TAG, "Failed to spawn LVGL port task on Core %d", core_id);
        return ESP_FAIL;
    }
    return ESP_OK;
}

/**
 * @brief Stop the LVGL background task.
 *
 * @details Safely handles being called from within an LVGL input callback on the
 *          LVGL task thread itself (e.g. long-press shutdown) without self-deletion.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t h1os_lvgl_stop(void)
{
    if (s_lvgl_task_handle != NULL) {
        s_lvgl_task_running = false;
        if (xTaskGetCurrentTaskHandle() == s_lvgl_task_handle) {
            return ESP_OK;
        }
        uint32_t wait_ms = 0;
        while (s_lvgl_task_handle != NULL && wait_ms < 6000) {
            vTaskDelay(pdMS_TO_TICKS(20));
            wait_ms += 20;
        }
        if (s_lvgl_task_handle != NULL) {
            vTaskDelete(s_lvgl_task_handle);
            s_lvgl_task_handle = NULL;
        }
    }
    return ESP_OK;
}

/**
 * @brief Check if the LVGL display pipeline has pending render/flush tasks.
 *
 * @return True on success, false otherwise.
 */
bool h1os_lvgl_has_pending_tasks(void)
{
    if (s_lv_display == NULL)
        return false;

    if (s_flush_in_progress)
        return true;

    if (s_lvgl_task_handle != NULL && xTaskGetCurrentTaskHandle() == s_lvgl_task_handle)
        return false;

    lv_timer_t *refr_timer = lv_display_get_refr_timer(s_lv_display);
    if (refr_timer != NULL && !lv_timer_get_paused(refr_timer)) {
        if (s_lv_display->inv_p > 0 || s_lv_display->rendering_in_progress) {
            return true;
        }
    }
    return false;
}

lv_indev_t *h1os_lvgl_get_indev(void)
{
    return s_lv_keypad_indev;
}

/**
 * @brief H1os lvgl port task.
 *
 * @param[in]    pvParameters    Parameter pvParameters.
 *
 * @return Return value of type static void.
 */
static void h1os_lvgl_port_task(void *pvParameters)
{
    (void)pvParameters;
    ESP_LOGI(TAG, "LVGL port task active on Core %d", xPortGetCoreID());
    while (s_lvgl_task_running) {
        lv_lock();
        uint32_t delay_ms = lv_timer_handler();
        lv_unlock();
        delay_ms = (delay_ms == LV_NO_TIMER_READY || delay_ms > LV_DEF_REFR_PERIOD) ? LV_DEF_REFR_PERIOD : delay_ms;
        vTaskDelay(pdMS_TO_TICKS(delay_ms));
    }
    s_lvgl_task_handle = NULL;
    vTaskDelete(NULL);
}