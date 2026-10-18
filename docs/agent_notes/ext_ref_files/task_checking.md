The most reliable way to ensure a task has actually started executing before returning is an **explicit handshake (synchronization)** using a task notification or binary semaphore.

Querying FreeRTOS state APIs directly (such as `eTaskGetState()`) is unreliable:

* If the task is waiting on `s_audio_queue`, its state is `eBlocked`, not `eRunning`.
* Polling for `eRunning` creates a race condition on dual-core ESP32 chips, where a task can transition between `eRunning`, `eReady`, and `eBlocked` in microseconds.

---

### Method 1: Direct-to-Task Notification (Recommended — Zero Heap Overhead)

Pass the creator task's handle into the new task (or use `xTaskGetCurrentTaskHandle()`), then block until the worker signals it is up and ready.

#### 1. In `audio_worker_task`

Signal the parent task right before entering the main loop:

```c
void audio_worker_task(void *pvParameters)
{
    TaskHandle_t creator_task = (TaskHandle_t)pvParameters;

    /* Perform task-local hardware/driver init if needed */

    /* Signal the creator task that initialization is complete and loop is starting */
    if (creator_task != NULL) {
        xTaskNotifyGive(creator_task);
    }

    audio_cmd_t cmd;
    while (1) {
        if (xQueueReceive(s_audio_queue, &cmd, portMAX_DELAY) == pdTRUE) {
            // Process audio command...
        }
    }
}

```

#### 2. In your initialization code

Capture the creator task handle, pass it to `pvParameters`, and wait with a timeout:

```c
/* 6. Spawn audio background worker task at priority 6 */
if (s_audio_queue == NULL) {
    s_audio_queue = xQueueCreate(8, sizeof(audio_cmd_t));
    if (s_audio_queue != NULL) {
        TaskHandle_t current_task = xTaskGetCurrentTaskHandle();

        BaseType_t res = xTaskCreatePinnedToCore(
            audio_worker_task,
            "h1os_audio_worker",
            4096,
            (void *)current_task,      /* Pass creator handle */
            6,
            &s_audio_task_handle,
            tskNO_AFFINITY
        );

        if (res == pdPASS) {
            /* Block until worker signals, or timeout after 500ms */
            if (ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(500)) == 0) {
                // Task creation succeeded, but worker failed to start in time
            }
        } else {
            // Memory allocation failure (insufficient heap for stack/TCB)
        }
    }
}

```

---

### Method 2: Binary Semaphore Handshake

If you don't want to pass task handles around:

```c
SemaphoreHandle_t s_init_sem = xSemaphoreCreateBinary();

// Inside audio_worker_task:
// ...after initialization...
xSemaphoreGive(s_init_sem);

// Inside init function after xTaskCreatePinnedToCore:
if (xSemaphoreTake(s_init_sem, pdMS_TO_TICKS(500)) == pdTRUE) {
    // Confirmed running
}
vSemaphoreDelete(s_init_sem);

```

---

### Key Checks to Include

* **Return code validation:** Always verify `xTaskCreatePinnedToCore(...) == pdPASS`. If internal heap is exhausted, `s_audio_task_handle` remains undefined or unchanged.
* **Core yielding:** Because the worker task priority (6) is higher than LVGL (5), if the calling task has a priority lower than 6, FreeRTOS will preempt immediately on the same core. On a secondary core, however, execution timing depends on the other core's current load, making the notification wait essential.