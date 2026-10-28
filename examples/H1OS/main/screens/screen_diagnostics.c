/**
 * @file screen_diagnostics.c
 * @brief Screen 5: Verbose system diagnostics and silicon telemetry page
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "esp_private/esp_clk.h"
#include "esp_sleep.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "h1os/h1os_lvgl.h"
#include "h1os/h1os_version.h"
#include "screens.h"

#include <inttypes.h>

static const char *get_reset_reason_str(esp_reset_reason_t reason)
{
    switch (reason) {
    case ESP_RST_POWERON:
        return "POWER_ON";
    case ESP_RST_EXT:
        return "EXTERNAL_PIN";
    case ESP_RST_SW:
        return "SW_RESTART";
    case ESP_RST_PANIC:
        return "PANIC";
    case ESP_RST_INT_WDT:
        return "INT_WDT";
    case ESP_RST_TASK_WDT:
        return "TASK_WDT";
    case ESP_RST_DEEPSLEEP:
        return "DEEP_SLEEP";
    case ESP_RST_BROWNOUT:
        return "BROWNOUT";
    default:
        return "UNKNOWN";
    }
}

static const char *get_wake_causes_str(uint32_t causes)
{
    if (causes & BIT(ESP_SLEEP_WAKEUP_UNDEFINED))
        return "BOOT";
    if (causes & BIT(ESP_SLEEP_WAKEUP_EXT1))
        return "EXT1_BUTTON";
    if (causes & BIT(ESP_SLEEP_WAKEUP_TIMER))
        return "HW_TIMER";
    if (causes & BIT(ESP_SLEEP_WAKEUP_ULP))
        return "ULP_MONITOR";
    return "INTERNAL";
}

/**
 * @brief Renders Screen 5: Verbose hardware register and memory diagnostics page.
 *
 * @param[in]    telem           Pointer to validated environmental telemetry snapshot.
 * @param[in]    event_cb        Keypad navigation callback.
 */
void screen_diagnostics_render(const h1os_telemetry_t *telem, lv_event_cb_t event_cb)
{

    uint32_t base_cpu_mhz = (uint32_t)(esp_clk_cpu_freq() / 1000000);
    h1os_lvgl_lock(100);
    lv_obj_t *scr = screen_base_create("OS DIAGNOSTICS", "5/5", event_cb);

    volatile orch_persisted_state_t *st = orch_state_get();

    /* Row 1: System Reset Reason */
    lv_obj_t *lbl_k1 = lv_label_create(scr);
    lv_label_set_text(lbl_k1, "Reset");
    lv_obj_set_style_text_font(lbl_k1, H1OS_FONT_14, 0);
    lv_obj_align(lbl_k1, LV_ALIGN_TOP_LEFT, 6, 28);

    lv_obj_t *lbl_v1 = lv_label_create(scr);
    lv_label_set_text(lbl_v1, get_reset_reason_str(esp_reset_reason()));
    lv_obj_set_style_text_font(lbl_v1, H1OS_FONT_14, 0);
    lv_obj_align(lbl_v1, LV_ALIGN_TOP_RIGHT, -6, 28);

    /* Row 2: Deep Sleep Wake Event Cause */
    uint32_t causes = esp_sleep_get_wakeup_causes();
    lv_obj_t *lbl_k2 = lv_label_create(scr);
    lv_label_set_text(lbl_k2, "Wake");
    lv_obj_set_style_text_font(lbl_k2, H1OS_FONT_14, 0);
    lv_obj_align(lbl_k2, LV_ALIGN_TOP_LEFT, 6, 48);

    lv_obj_t *lbl_v2 = lv_label_create(scr);
    lv_label_set_text(lbl_v2, get_wake_causes_str(causes));
    lv_obj_set_style_text_font(lbl_v2, H1OS_FONT_14, 0);
    lv_obj_align(lbl_v2, LV_ALIGN_TOP_RIGHT, -6, 48);

    /* Row 3: ULP Coprocessor Dispatch Mode */
    const char *ulp_str = "NONE";
    switch (st->ulp_dispatch_reason) {
    case ULP_DISPATCH_SENSOR_SAMPLE:
        ulp_str = "SENSOR_SAMPLE";
        break;
    case ULP_DISPATCH_MAIN_WAKE:
        ulp_str = "MAIN_WAKE";
        break;
    case ULP_DISPATCH_CRITICAL_SHUTDOWN:
        ulp_str = "CRIT_SHUTDOWN";
        break;
    case ULP_DISPATCH_BOOTLOADER_JUMP:
        ulp_str = "BOOTLOADER";
        break;
    case ULP_DISPATCH_POWER_OFF:
        ulp_str = "POWER_OFF";
        break;
    default:
        ulp_str = "NONE";
        break;
    }

    lv_obj_t *lbl_k3 = lv_label_create(scr);
    lv_label_set_text(lbl_k3, "RISC-V");
    lv_obj_set_style_text_font(lbl_k3, H1OS_FONT_14, 0);
    lv_obj_align(lbl_k3, LV_ALIGN_TOP_LEFT, 6, 68);

    lv_obj_t *lbl_v3 = lv_label_create(scr);
    lv_label_set_text(lbl_v3, ulp_str);
    lv_obj_set_style_text_font(lbl_v3, H1OS_FONT_14, 0);
    lv_obj_align(lbl_v3, LV_ALIGN_TOP_RIGHT, -6, 68);

    /* Row 4: Heap Memory (Current Free & Minimum Watermark) */
    lv_obj_t *lbl_k4 = lv_label_create(scr);
    lv_label_set_text(lbl_k4, "Heap");
    lv_obj_set_style_text_font(lbl_k4, H1OS_FONT_14, 0);
    lv_obj_align(lbl_k4, LV_ALIGN_TOP_LEFT, 6, 88);

    lv_obj_t *lbl_v4 = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_v4, "%luK (Min %luK)",
                          (unsigned long)(esp_get_free_heap_size() / 1024),
                          (unsigned long)(esp_get_minimum_free_heap_size() / 1024));
    lv_obj_set_style_text_font(lbl_v4, H1OS_FONT_14, 0);
    lv_obj_align(lbl_v4, LV_ALIGN_TOP_RIGHT, -6, 88);

    /* Row 5: FreeRTOS Presentation Task Stack High-Water Mark */
    UBaseType_t hwm = uxTaskGetStackHighWaterMark(NULL);
    lv_obj_t *lbl_k5 = lv_label_create(scr);
    lv_label_set_text(lbl_k5, "Stack");
    lv_obj_set_style_text_font(lbl_k5, H1OS_FONT_14, 0);
    lv_obj_align(lbl_k5, LV_ALIGN_TOP_LEFT, 6, 108);

    lv_obj_t *lbl_v5 = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_v5, "%u B HWM", (unsigned int)(hwm * sizeof(StackType_t)));
    lv_obj_set_style_text_font(lbl_v5, H1OS_FONT_14, 0);
    lv_obj_align(lbl_v5, LV_ALIGN_TOP_RIGHT, -6, 108);

    /* Row 6: Total Wake Cycles & Sensor Ingestion Failures */
    lv_obj_t *lbl_k6 = lv_label_create(scr);
    lv_label_set_text(lbl_k6, "Wakes");
    lv_obj_set_style_text_font(lbl_k6, H1OS_FONT_14, 0);
    lv_obj_align(lbl_k6, LV_ALIGN_TOP_LEFT, 6, 128);

    lv_obj_t *lbl_v6 = lv_label_create(scr);
    uint32_t fails = telem ? telem->sensor_fail_count : st->sensor_fail_count;
    if (fails > 0) {
        lv_label_set_text_fmt(lbl_v6, "%lu (Fail %lu)",
                              (unsigned long)st->wake_count,
                              (unsigned long)fails);
    } else {
        uint8_t ring_count = (st->total_samples >= ORCH_RING_CAPACITY) ?
                              (uint8_t)ORCH_RING_CAPACITY :
                              (uint8_t)st->total_samples;
        lv_label_set_text_fmt(lbl_v6, "%lu (Ring %u/32)",
                              (unsigned long)st->wake_count,
                              ring_count);
    }
    lv_obj_set_style_text_font(lbl_v6, H1OS_FONT_14, 0);
    lv_obj_align(lbl_v6, LV_ALIGN_TOP_RIGHT, -6, 128);

    /* Row 7: Core Clock & SHTC3 Silicon Telemetry State */
    lv_obj_t *lbl_k7 = lv_label_create(scr);
    lv_label_set_text(lbl_k7, "CPU");
    lv_obj_set_style_text_font(lbl_k7, H1OS_FONT_14, 0);
    lv_obj_align(lbl_k7, LV_ALIGN_TOP_LEFT, 6, 148);

    lv_obj_t *lbl_v7 = lv_label_create(scr);
    uint8_t last_err = telem ? telem->last_sensor_error : st->last_sensor_error;
    if (last_err == ORCH_SENSOR_ERR_NONE) {
        lv_label_set_text_fmt(lbl_v7, "%luMHz • SHT:OK", (unsigned long)base_cpu_mhz);
    } else {
        lv_label_set_text_fmt(lbl_v7, "%luMHz • ERR_%u",
                              (unsigned long)base_cpu_mhz,
                              (unsigned int)last_err);
    }
    lv_obj_set_style_text_font(lbl_v7, H1OS_FONT_14, 0);
    lv_obj_align(lbl_v7, LV_ALIGN_TOP_RIGHT, -6, 148);

    /* Footer: H1OS Architecture Release & ESP-IDF Runtime */
    lv_obj_t *lbl_foot_l = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_foot_l, "H1OS v%" PRIu32 ".%" PRIu32 ".%" PRIu32,
                          h1os_version_get_major(),
                          h1os_version_get_minor(),
                          h1os_version_get_patch());
    lv_obj_set_style_text_font(lbl_foot_l, H1OS_FONT_14, 0);
    lv_obj_align(lbl_foot_l, LV_ALIGN_BOTTOM_LEFT, 6, -6);

    lv_obj_t *lbl_foot_r = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_foot_r, "IDF %s", esp_get_idf_version());
    lv_obj_set_style_text_font(lbl_foot_r, H1OS_FONT_14, 0);
    lv_obj_align(lbl_foot_r, LV_ALIGN_BOTTOM_RIGHT, -6, -6);

    h1os_lvgl_unlock();
}
