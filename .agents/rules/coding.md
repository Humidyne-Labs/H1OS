# Embedded C/C++ Coding Standards, Hardware Utilization & Code Aesthetics

This rule governs the implementation quality, hardware-first design principles, concurrency safety, memory safety, and visual aesthetics of C/C++ firmware in **H1OS** (`v2.4.5-dev`).

---

## 1. Hardware-First Mandate ("Use the Hardware")

This is embedded silicon code. Actively exploit all on-chip hardware accelerators, coprocessors, and peripheral engines:

1. **Leverage FreeRTOS SMP & Static Primitives:**
   - Use dual-core affinity: Core 0 for system orchestration, `on_sync()` wireless stacks, and headless Flow A bursts; Core 1 dedicated to the LVGL v9 presentation and SSD1681 refresh task (`h1os_lvgl`, priority `5`).
   - Allocate all RTOS synchronization primitives statically (`StaticSemaphore_t`, `StaticQueue_t`, `StaticEventGroup_t` via `xSemaphoreCreateMutexStatic`, `xSemaphoreCreateRecursiveMutexStatic`, `xSemaphoreCreateBinaryStatic`, `xQueueCreateStatic`, and `xEventGroupCreateStatic`) to guarantee zero runtime heap fragmentation (`PIT-04-C` / JPL Rule 3).
2. **Never Busy-Wait (Event-Driven Awake vs. Bare-Metal Sleep Split):**
   - **Awake FreeRTOS Layers (`hal_*`, `sub_*`, `orch_flow.c`, `h1os_*`):** Polling with `vTaskDelay()` spin loops for hardware `BUSY` pins, button states, inactivity timeouts, or worker task exits is prohibited. Use `esp_timer` (`esp_timer_start_once` / `esp_timer_start_periodic` / `esp_timer_restart`) for timeouts and periodic state machines, GPIO edge interrupts (`gpio_isr_handler_add`) + hardware glitch filters (`gpio_new_pin_glitch_filter`) + `xSemaphoreTake` / `ulTaskNotifyTake` for hardware lines, static `EventGroup` barriers (`xEventGroupCreateStatic`) for multi-subsystem sleep coordination, and static binary semaphores (`xSemaphoreCreateBinaryStatic`) for cooperative worker teardown joins (`PIT-01-E`).
   - **Bare-Metal Wake Stub (`orch_wake_stub.c`) & ULP (`ulp/main.c`):** Never call FreeRTOS, `esp_timer`, or standard library `memset`/`memcpy` while SPI Flash is powered down. Use bounded `ccount`/register loops guarded with `__attribute__((noinline))`, loop register clobbers (`asm volatile("" : "+r"(i))`), local array memory clobbers (`asm volatile("" : "+m"(buf[i]))`), and `rtc_reg_barrier()` (`memw` / `fence`).
3. **Coprocessor & DMA Utilization:** Delegate ultra-low-power GPIO interrupt evaluation to the ULP-RISC-V coprocessor in Pure Event Mode (`ULP_RISCV_WAKEUP_SOURCE_GPIO`) and bulk display transfers to SPI DMA channels.
4. **Platform & Hardware Reality Checks:** Always cross-reference proposed features against actual board schematics (`ERRATA.md`) and Espressif documentation. If an operation is physically impossible (e.g. attempting RTC I2C transactions on digital-only `GPIO 47/48`, or cutting `PA_EN` on the shared I2C bus), state it as an unalterable hardware fact.

---

## 2. Memory Safety, Concurrency & Pointer Hygiene

1. **Zero Dangling Pointers:**
   - Always initialize pointers to `NULL`.
   - Immediately set pointers to `NULL` after calling `free()` or releasing memory.
2. **Parameter Validation:** Validate pointer arguments at all public and subsystem boundaries (`if (ptr == NULL) return ESP_ERR_INVALID_ARG;`).
3. **Explicit Error Handling & Battery-Safe Recovery:** Check return codes on all ESP-IDF and FreeRTOS calls. Propagate or log errors deterministically, and ensure fatal cold-boot initialization failures release the battery power latch (`GPIO 17`) via `h1os_handle_fatal_startup_error()` (`MANDATE-06`).
4. **Atomic Header-Implementation Coherency:** When modifying function signatures or struct definitions, update both the `.h` declaration and `.c`/`.cpp` implementation atomically so the tree remains compilable at every step.

---

## 3. Single-Responsibility Functions

- If a function performs more than one distinct task, **split it into 2 or 3 smaller, well-named helper functions**.
- Modularity, testability, and code readability strictly take priority over negligible function-call overhead.
- Keep function scope focused and self-documenting.

---

## 4. Visual Block Alignment ("Pretty Code")

Code must be formatted into clean, columnar visual blocks that allow rapid vertical scanning:

### Example: Columnar Struct Definitions
```c
typedef struct {
    uint32_t          inactivity_timeout_sec; /**< Interactive session idle sleep timeout (default 30s). */
    h1os_clk_mode_t   clk_mode;               /**< Active session CPU clock scaling strategy. */
    uint32_t          flow_a_period_sec;      /**< Period between headless Flow A sensor bursts. */
    uint32_t          flow_b_period_sec;      /**< Period between parallel Flow B sync/UI wakes. */
    uint32_t          sync_wait_ms;           /**< Max pre-flush wait (ms) to coalesce inbound sync data. */
    uint32_t          sync_timeout_ms;        /**< Max sleep barrier wait (ms) for async on_sync completion. */
} h1os_session_cfg_t;
```

### Example: Columnar Assignments & Macros
```c
#define HAL_PIN_BAT_CTRL      17
#define HAL_PIN_EPD_3V3_EN     6
#define HAL_PIN_STATUS_LED     3
#define HAL_PIN_BAT_ADC        4
#define HAL_PIN_RTC_INT        5

static esp_err_t s_init_peripherals(void)
{
    esp_err_t ret      = ESP_OK;
    uint32_t  attempts = 0;
    bool      bus_busy = false;
    /* ... */
}
```

---

## 5. LVGL Presentation Layer Discipline & OSHW Reuse

1. **Presentation Isolation & Cross-Core Queueing:** LVGL v9 belongs strictly to Layer 4 on Core 1. Never embed raw physical bus transactions (I2C/SPI writes) inside LVGL widget event callbacks, and never mutate LVGL objects directly from Core 0 background tasks without either enqueuing work via `h1os_ui_post(fn, arg, timeout_ms)` or acquiring `h1os_lvgl_lock(timeout_ms)`.
2. **Minimal Footprint:** Favor 1-bit packed binary assets, static buffers where practical, and minimal RAM overhead.
3. **Open Source Reusability:** Design reusable, cleanly decoupled widgets and drivers to benefit the wider Open Source Hardware (OSHW) and embedded community.
