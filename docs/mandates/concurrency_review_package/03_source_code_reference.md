# H1OS Source Code Reference for Concurrency Review

This document contains verbatim source code extracts showing the exact call sites and peripheral drivers relevant to the dual-core lifecycle review.

---

## 1. Lifecycle Session Launch & Pre-Spawn Mutex Acquisition

**Source File:** `components/h1os/src/h1os_lifecycle.c` (Lines 415–435)

```c
    if (flow == ORCH_FLOW_BOOT) {
        h1os_trigger_chime(H1OS_CHIME_BOOT);
        h1os_lvgl_lock(1000);
        h1os_trigger_splash(H1OS_SPLASH_BOOT);
        if (s_app_lifecycle.on_boot) {
            s_app_lifecycle.on_boot(s_app_lifecycle.user_data);
        }
        h1os_lvgl_unlock();
    } else if (s_app_lifecycle.on_wake) {
        h1os_wake_context_t ctx = {.reset_reason = esp_reset_reason(),
                                   .wakeup_causes = causes,
                                   .boot_count = st->boot_count,
                                   .deep_sleep_count = st->wake_count,
                                   .woke_from_button = button_woke,
                                   .wake_button = button_woke ? (uint8_t)ulp_last_wake_btn : (uint8_t)H1OS_WAKE_BTN_NONE,
                                   .sleep_duration_sec = button_woke ? st->sample_interval_sec : st->flow_b_period_sec,
                                   .user_data = s_app_lifecycle.user_data};
        h1os_lvgl_lock(1000);
        s_app_lifecycle.on_wake(&ctx, s_app_lifecycle.user_data);
        h1os_lvgl_unlock();
    }

    err = h1os_lvgl_start(5, 1);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "h1os_lvgl_start failed: %s", esp_err_to_name(err));
        return err;
    }
```

* **Observation:** Notice that `h1os_lvgl_lock(1000)` wraps `s_app_lifecycle.on_wake(...)`, but `h1os_lvgl_start(5, 1)` is not invoked until **after** `on_wake` returns!

---

## 2. Core 1 Task Spawning & Affinity

**Source File:** `components/h1os/src/h1os_lvgl.cpp` (Lines 414–434)

```c
esp_err_t h1os_lvgl_start(int32_t task_priority, int32_t core_id)
{
    if (s_lvgl_task_running) {
        return ESP_OK;
    }

    task_priority = (task_priority > 0) ? task_priority : LVGL_TASK_PRIO_PORT;
    core_id = ((core_id >= 0) && (core_id < (int32_t)configNUM_CORES)) ? core_id : -1;

    s_lvgl_task_running = true;

    BaseType_t res = xTaskCreatePinnedToCore(h1os_lvgl_port_task,
                                             "h1os_lvgl",
                                             LVGL_TASK_STACK_PORT,
                                             NULL,
                                             task_priority,
                                             (TaskHandle_t *)&s_lvgl_task_handle,
                                             core_id);

    if (res != pdPASS) {
        s_lvgl_task_running = false;
        ESP_LOGE(TAG, "Failed to spawn LVGL port task on Core %ld", (long)core_id);
        return ESP_FAIL;
    }
    return ESP_OK;
}
```

* **Observation:** `core_id` passed from lifecycle is strictly `1`. The task is permanently pinned to Core 1.

---

## 3. Core 0 Main Task & Wi-Fi Pinning

**Source File:** `components/h1os/sdkconfig.defaults` (Lines 60–63)

```ini
CONFIG_FREERTOS_UNICORE=n
CONFIG_ESP_MAIN_TASK_AFFINITY_CPU0=y
```

* **Observation:** Core 0 (`CPU0`) executes `app_main`, the FreeRTOS timer daemon, and all Wi-Fi/LwIP threads.

---

## 4. SSD1681 Electrophoretic Refresh & Hardware BUSY Hold

**Source File:** `components/h1os/src/sub_display.cpp` (Lines 640–655)

```c
    uint8_t d_upd[] = {0xCF};
    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x22), TAG, "SPI cmd 0x22 failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(d_upd, sizeof(d_upd)), TAG, "SPI data 0x22 failed");

    /* 0x20: Master Activation - triggers physical high-voltage electrophoretic waveform */
    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x20), TAG, "SPI cmd 0x20 failed");
    
    /* Blocks on GPIO 8 falling-edge interrupt semaphore */
    sub_display_wait_busy(pdMS_TO_TICKS(2000));

    memcpy(s_previous_frame, s_current_frame, EPD_BUFFER_SIZE);

    int64_t t_elapsed_ms = (esp_timer_get_time() - t_start) / 1000LL;
    ESP_LOGI(TAG, "Partial Refresh completed in %lld ms (Target: ~300 ms)", (long long)t_elapsed_ms);
```

* **Observation:** `hal_spi_write_cmd(0x20)` fires the physical display waveform. The caller (Core 1) blocks on `sub_display_wait_busy()` for 300 ms (partial) or 1800 ms (full refresh).

---

## 5. Architectural Rule: Hardware-First Dual Core Affinity

**Source File:** `AGENTS.md` (Section 1.4)

> **Dual-Core Affinity:** Core 0 handles system, radio, and headless Flow A bursts; Core 1 is dedicated strictly to the LVGL v9 presentation task.

---

**Prepared by Humidyne Labs / Humiditron Systems Engineering**  
SPDX-License-Identifier: MIT
