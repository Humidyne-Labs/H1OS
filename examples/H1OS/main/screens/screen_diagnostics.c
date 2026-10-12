/**
 * @file screen_diagnostics.c
 * @brief Screen 4: Verbose OS Diagnostics (Page 4/4)
 *
 * SPDX-License-Identifier: MIT
 */

#include "screens.h"
#include "h1os/h1os_lvgl.h"
#include "h1os/orch_state.h"
#include "esp_system.h"
#include "esp_sleep.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char* get_reset_reason_str(esp_reset_reason_t reason)
{
    switch (reason) {
        case ESP_RST_POWERON:   return "POWER_ON";
        case ESP_RST_EXT:       return "EXTERNAL_PIN";
        case ESP_RST_SW:        return "SW_RESTART";
        case ESP_RST_PANIC:     return "EXCEPTION_PANIC";
        case ESP_RST_INT_WDT:   return "INT_WATCHDOG";
        case ESP_RST_TASK_WDT:  return "TASK_WATCHDOG";
        case ESP_RST_DEEPSLEEP: return "DEEP_SLEEP";
        case ESP_RST_BROWNOUT:  return "BROWNOUT";
        default:                return "UNKNOWN";
    }
}

static const char* get_wake_causes_str(uint32_t causes)
{
    if (causes & BIT(ESP_SLEEP_WAKEUP_UNDEFINED)) return "COLD_BOOT";
    if (causes & BIT(ESP_SLEEP_WAKEUP_EXT1))      return "EXT1_BUTTON_RTC";
    if (causes & BIT(ESP_SLEEP_WAKEUP_TIMER))     return "HW_TIMER";
    if (causes & BIT(ESP_SLEEP_WAKEUP_ULP))       return "ULP_MONITOR";
    return "INTERNAL";
}

void screen_diagnostics_render(const h1os_telemetry_t *telem, lv_event_cb_t event_cb)
{
    lv_obj_t *scr = screen_base_create("OS DIAGNOSTICS", "4/4", event_cb);

    orch_persisted_state_t *st = orch_state_get();

    // Row 1: Reset Reason
    lv_obj_t *lbl_rst = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_rst, "Reset:  %s", get_reset_reason_str(esp_reset_reason()));
    lv_obj_set_style_text_font(lbl_rst, H1OS_FONT_DEJAVU_14, 0);
    lv_obj_align(lbl_rst, LV_ALIGN_TOP_LEFT, 6, 28);

    // Row 2: Wake Causes
    uint32_t causes = esp_sleep_get_wakeup_causes();
    lv_obj_t *lbl_wake = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_wake, "Wake:   %s", get_wake_causes_str(causes));
    lv_obj_set_style_text_font(lbl_wake, H1OS_FONT_DEJAVU_14, 0);
    lv_obj_align(lbl_wake, LV_ALIGN_TOP_LEFT, 6, 48);

    // Row 3: ULP Monitor Dispatch
    const char *ulp_str = "NONE";
    if (st->ulp_dispatch_reason == ULP_DISPATCH_SENSOR_SPRINT) ulp_str = "SENSOR_SPRINT";
    else if (st->ulp_dispatch_reason == ULP_DISPATCH_MAIN_WAKE) ulp_str = "MAIN_WAKE";
    else if (st->ulp_dispatch_reason == ULP_DISPATCH_CRITICAL_SHUTDOWN) ulp_str = "CRIT_SHUTDOWN";

    lv_obj_t *lbl_ulp = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_ulp, "ULP:    %s", ulp_str);
    lv_obj_set_style_text_font(lbl_ulp, H1OS_FONT_DEJAVU_14, 0);
    lv_obj_align(lbl_ulp, LV_ALIGN_TOP_LEFT, 6, 68);

    // Row 4: Heap Memory (Free / Minimum Ever Free)
    uint32_t free_heap = esp_get_free_heap_size() / 1024;
    uint32_t min_heap  = esp_get_minimum_free_heap_size() / 1024;
    lv_obj_t *lbl_heap = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_heap, "Heap:   %luK / %luK Min",
                          (unsigned long)free_heap, (unsigned long)min_heap);
    lv_obj_set_style_text_font(lbl_heap, H1OS_FONT_DEJAVU_14, 0);
    lv_obj_align(lbl_heap, LV_ALIGN_TOP_LEFT, 6, 94);

    // Row 5: FreeRTOS Task High Watermark
    UBaseType_t hwm = uxTaskGetStackHighWaterMark(NULL);
    lv_obj_t *lbl_stack = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_stack, "Stack:  %u B HWM", (unsigned int)(hwm * sizeof(StackType_t)));
    lv_obj_set_style_text_font(lbl_stack, H1OS_FONT_DEJAVU_14, 0);
    lv_obj_align(lbl_stack, LV_ALIGN_TOP_LEFT, 6, 114);

    // Row 6: Wakes & Ring Buffer Head
    lv_obj_t *lbl_wakes = lv_label_create(scr);
    lv_label_set_text_fmt(lbl_wakes, "Wakes:  %lu (Ring: %u/32)",
                          (unsigned long)st->wake_count, st->ring_head);
    lv_obj_set_style_text_font(lbl_wakes, H1OS_FONT_DEJAVU_14, 0);
    lv_obj_align(lbl_wakes, LV_ALIGN_TOP_LEFT, 6, 134);

    // Row 7: Dynamic Frequency Scaling
    lv_obj_t *lbl_dfs = lv_label_create(scr);
    lv_label_set_text(lbl_dfs, "CPU:    80MHz (DFS ON)");
    lv_obj_set_style_text_font(lbl_dfs, H1OS_FONT_DEJAVU_14, 0);
    lv_obj_align(lbl_dfs, LV_ALIGN_TOP_LEFT, 6, 154);

    // Footer Bar: Version (left), Target (right) - shortened to fit 200px display
    lv_obj_t *lbl_foot_l = lv_label_create(scr);
    lv_label_set_text(lbl_foot_l, "H1OS v2.0");
    lv_obj_set_style_text_font(lbl_foot_l, H1OS_FONT_14, 0);
    lv_obj_align(lbl_foot_l, LV_ALIGN_BOTTOM_LEFT, 6, -6);

    lv_obj_t *lbl_foot_r = lv_label_create(scr);
    lv_label_set_text(lbl_foot_r, "IDF v6.1");
    lv_obj_set_style_text_font(lbl_foot_r, H1OS_FONT_14, 0);
    lv_obj_align(lbl_foot_r, LV_ALIGN_BOTTOM_RIGHT, -6, -6);

    lv_refr_now(NULL);
    h1os_lvgl_unlock();
}
