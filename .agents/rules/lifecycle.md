# Master Rule: H1OS Application Lifecycle & Dual-Core Concurrency Architecture (`v2.4.5-dev`)

## 1. Primary Directive
`h1os_start()` (or `h1os_init()`) is the **MANDATORY single entry point** and lifecycle orchestrator for all application firmware on H1OS.

Direct low-level peripheral initialization, manual reset reason checking (`esp_reset_reason()`), raw GPIO wake mask configuration, manual NVS scratchpad management, or bypassing the 4-layer boundary hierarchy in `app_main()` is **PROHIBITED**. All application initialization, state transitions, parallel synchronization, hardware profiling, flow arbitration, and sleep transitions MUST be driven through the declarative `h1os_lifecycle_t` event framework.

---

## 2. Four-Layer Unidirectional Hierarchy

```
+-------------------------------------------------------------------------------+
| LAYER 4: APPLICATION & UI ENGINE (h1os.h, h1os_lvgl.h, h1os_time.h)           |
| - Declarative lifecycle hooks: on_boot, on_wake, on_sync, on_pre_sleep,       |
|   on_shutdown, on_error                                                       |
| - Static FreeRTOS EventGroup sleep barrier (BARRIER_SYNC_DONE | DISPLAY_DONE) |
| - Decoupled LVGL v9 presentation task pinned to Core 1 + h1os_ui_post queue   |
+-------------------------------------------------------------------------------+
                                       |
                                       v
+-------------------------------------------------------------------------------+
| LAYER 3: SYSTEM ORCHESTRATION PIPELINE (orch_flow, orch_state, orch_math)     |
| - Flow Arbiter: Flow A (Headless Telemetry) vs Flow B (Parallel App/UI Wake)  |
| - Persistent RTC Slow Memory (648B total, 512B 32-slot Tri-Node ring buffer)  |
| - Headless RTC_IRAM_ATTR sensor wake stub (orch_wake_stub.c)                  |
| - Thermodynamic math invariants (Magnus vapor pressure, dew point, EWMA)      |
| - ULP-RISC-V Pure Event Mode Coprocessor Monitor (sleep-gated)                |
+-------------------------------------------------------------------------------+
                                       |
                                       v
+-------------------------------------------------------------------------------+
| LAYER 2: HARDWARE SUBSYSTEM MANAGERS (sub_display, sub_rtc, sub_power, ...)   |
| - Encapsulated drivers: sub_display, sub_rtc, sub_power, sub_audio,           |
|   sub_sdcard, sub_nvs (Note: sub_sensor retired in favor of orch_wake_stub)   |
| - Invariant: Zero inter-subsystem cross-talk; zero upward Layer 3/4 includes  |
+-------------------------------------------------------------------------------+
                                       |
                                       v
+-------------------------------------------------------------------------------+
| LAYER 1: HARDWARE ABSTRACTION LAYER (hal_io, hal_spi, hal_i2c, hal_adc, ...)  |
| - Pure C hardware primitives: Pad holds, latch release, DMA SPI, I2C master   |
| - hal_types.h: Shared fixed-width types, error codes, and pinout constants    |
+-------------------------------------------------------------------------------+
```

### Invariants of Layer Separation:
1. **Unidirectional Control:** Upper layers call lower layers; lower layers **NEVER** call up or signal higher layers.
2. **Zero Cross-Talk in Layer 2:** Subsystems never communicate directly. Layer 3 Orchestrator coordinates all multi-subsystem tasks.
3. **Bootloader Power Latching & Fatal Error Recovery (`MANDATE-06`):** Power latch (`GPIO 17 BAT_CTRL = 1`) is asserted in `h1os_boot_hook` within 25 ms. Runtime HAL preserves RTC sleep pad holds and exposes `hal_io_release_power_latch()` for orderly power-down. If any cold-boot hardware initialization fails (`orch_flow_init()`, `sub_display_init()`, or `h1os_lvgl_init()`), `h1os_handle_fatal_startup_error()` invokes `on_error(err, stage)` and immediately releases `GPIO 17` on battery power (or enters `EXT0` deep sleep on `GPIO 18` when USB power is attached).
4. **ULP Sleep-Gating Rule:** The ULP-RISC-V Coprocessor is active in Pure Event Mode (`ULP_RISCV_WAKEUP_SOURCE_GPIO`) **only** while the dual-core Xtensa CPU is in deep sleep. Once Flow B wakes, ULP execution is suspended.

---

## 3. Dual Execution Flows: Flow A vs. Flow B

### Flow A: Headless Sensor Telemetry Burst (`~18.5 ms` at 80 MHz)
* **Execution Domain:** Fast RTC wake stub (`orch_wake_stub.c` / `bsp_wake_stub()`) on Core 0 running at 80 MHz. Core 1 is gated off, SPI Flash is unpowered.
* **Operation:**
  1. Wakes when the ULP forwards the N-th PCF85063A RTC countdown pulse (`GPIO 5`).
  2. Samples SHTC3 environmental sensor in normal mode (`0x7866`, `14.05 ms` conversion) and MCU die TSENS.
  3. Executes integer fixed-point Magnus psychrometric invariant calculation (`orch_math`): computes true water vapor pressure ($e$), dew point ($T_{\text{dew}}$), absolute humidity ($d_v$), and EWMA slope.
  4. Appends telemetry record to the 32-slot ring buffer in `648-byte` `orch_persisted_state_t` (`RTC_SLOW_MEM`).
  5. If `flow_a_counter < ratio_b_per_a`, re-arms the PCF85063A countdown timer and returns immediately to deep sleep (`esp_wake_stub_sleep(&bsp_wake_stub)`); otherwise sets `pending_flow_b = 1` and boots into Flow B.
* **Thermal Invariant:** Zero self-heating bias. CPU Flash and high-power rails remain unpowered during headless Flow A bursts.

### Flow B: Parallel Dual-Core Synchronization & UI Presentation (`MANDATE-04`)
* **Execution Domain:** Dual-core Xtensa LX7 FreeRTOS SMP with 240 MHz Turbo lock during SPI DMA transfers, dropping via DFS to 80 MHz during `GPIO 8` (`EPD_BUSY`) interrupt waits and idle interaction.
* **Wake States (`h1os_wake_state_t`):**
  - `H1OS_WAKE_STATE_BOOT`: Cold power-on reset (`boot_count` incremented).
  - `H1OS_WAKE_STATE_RTC_FLOW_B`: Headless periodic RTC Flow B wake (`flow_b_counter` incremented; executes `on_wake` + `on_sync` + Core 1 e-Paper refresh, then enters deep sleep immediately upon barrier completion without starting the 30s inactivity timer).
  - `H1OS_WAKE_STATE_INTERACTIVE_SESSION`: Tactile button wake on `GPIO 0` or `GPIO 18` (`button_wake_count` incremented; runs interactive session bounded by the one-shot `esp_timer` inactivity timer `s_session_timer`).
* **Parallel Dual-Core Execution Sequence:**
  1. Core 0 validates flow periods (`h1os_validate_flow_periods()`), runs `orch_flow_init()`, applies configured flow periods after `orch_state_reset()` (`h1os_apply_flow_periods()`), and initializes `sub_display` and `h1os_lvgl`.
  2. Core 0 invokes `on_boot()` (on cold boot) or `on_wake(&wake_ctx)` while Core 1 is still stopped (no outer `h1os_lvgl_lock` required).
  3. If `session.sync_wait_ms > 0` and `on_sync` is registered, Core 0 arms the inbound pre-flush coalescing gate (`h1os_lvgl_set_sync_gate()`).
  4. Core 0 starts the Core 1 LVGL v9 presentation task via `h1os_lvgl_start(5, 1)` (priority `5`, Core 1).
  5. Core 0 immediately executes `on_sync(&wake_ctx)` **in parallel** with Core 1's LVGL layout and SSD1681 display refresh.

---

## 4. Coordinated Sleep Transition & `EventGroup` Barrier Sequence

Applications transition to sleep via `h1os_sleep()` or `h1os_shutdown()` (or automatically at the end of `H1OS_WAKE_STATE_RTC_FLOW_B` / inactivity timeout) to trigger the deterministic sequence:
1. **Await Dual-Core Sleep Barrier (`s_lifecycle_event_group`):** Block on `xEventGroupWaitBits(..., BARRIER_SYNC_DONE | BARRIER_DISPLAY_DONE, ...)` bounded by `session.sync_timeout_ms` (`5000 ms` default, plus `3500 ms` display refresh grace margin).
2. **Invoke Pre-Sleep Hook:** Execute registered `on_pre_sleep` callback (which may enqueue final UI changes via `h1os_ui_post()`).
3. **Drain & Stop Core 1 UI Engine:** Drain LVGL work items and buffers via `h1os_lvgl_wait_idle(3000)` and halt the Core 1 task cleanly via `h1os_lvgl_stop()` (`s_stop_done_sem`).
4. **SSD1681 Deep Sleep & 250 ms Settling Delay (`REV-04`):** `sub_display_enter_deep_sleep()` waits on the `GPIO 8` (`EPD_BUSY`) falling-edge interrupt semaphore (`sub_display_wait_busy()`), then enforces the mandatory **250 ms post-`BUSY` electrophoretic settling delay** (`SUB_DISPLAY_SETTLING_WINDOW_MS`) before issuing SSD1681 deep sleep command `0x10` (`0x01`).
5. **Flash Frame & NVS Sync (`REV-07`):** If the active frame is dirty, commit the 5,000-byte 1-bit buffer to SPI Flash partition `epd_frame`. Arbitrate hourly (`3600 s`) or immediate `sub_nvs_commit_runtime_stats()` updates in Layer 3/4.
6. **Peripheral Standby & Deep Sleep Entry:** Place ES8311 in `<1 µA` software standby (`PA_EN` held LOW `0`), wait for open-drain interrupt lines (`GPIO 5`, `GPIO 0`, `GPIO 18`) to release HIGH, start the ULP-RISC-V monitor in Pure Event Mode, hold `BAT_CTRL` (`GPIO 17`), and enter hardware deep sleep (`esp_deep_sleep_start()`).

---

## 5. Declarative C Implementation Pattern (`v2.4.5-dev`)

```c
#include "esp_log.h"
#include "h1os/h1os.h"
#include "h1os/h1os_lvgl.h"

static const char *TAG = "app_main";

static void app_on_boot(void *user_data)
{
    (void)user_data;
    ESP_LOGI(TAG, "Cold boot initialized. Building initial LVGL screen...");
}

static void app_on_wake(const h1os_wake_context_t *ctx, void *user_data)
{
    (void)user_data;
    ESP_LOGI(TAG, "Flow B wake (state=%d): boot=%lu, flow_b=%lu, btn=%lu",
             (int)ctx->wake_state,
             (unsigned long)ctx->boot_count,
             (unsigned long)ctx->flow_b_count,
             (unsigned long)ctx->button_wake_count);
}

static void app_on_sync(const h1os_wake_context_t *ctx, void *user_data)
{
    (void)user_data;
    ESP_LOGI(TAG, "Core 0 parallel sync executing alongside Core 1 EPD refresh (wake=%lu)",
             (unsigned long)ctx->wake_count);
    /* For async Wi-Fi/ESP-NOW: call h1os_sync_hold() here, and call
     * h1os_sync_notify_complete() from the radio callback when done.
     * Use h1os_ui_post(fn, arg, 50) to push inbound updates to Core 1. */
}

static void app_on_pre_sleep(uint32_t sleep_sec, void *user_data)
{
    (void)user_data;
    ESP_LOGI(TAG, "Entering unattended sleep for %lu s.", (unsigned long)sleep_sec);
}

static void app_on_error(esp_err_t err, const char *stage, void *user_data)
{
    (void)user_data;
    ESP_LOGE(TAG, "Fatal startup error at %s: %s", stage, esp_err_to_name(err));
}

void app_main(void)
{
    const h1os_lifecycle_t lifecycle = {
        .on_boot      = app_on_boot,
        .on_wake      = app_on_wake,
        .on_sync      = app_on_sync,
        .on_pre_sleep = app_on_pre_sleep,
        .on_shutdown  = NULL,
        .on_error     = app_on_error,
        .session = {
            .inactivity_timeout_sec = 30,
            .clk_mode               = SYS_CLK_MODE_DYNAMIC,
            .flow_a_period_sec      = 60,
            .flow_b_period_sec      = 300,
            .sync_wait_ms           = 0,
            .sync_timeout_ms        = 5000,
        },
        .user_data    = NULL,
    };

    ESP_ERROR_CHECK(h1os_start(&lifecycle));
}
```
