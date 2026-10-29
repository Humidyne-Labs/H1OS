# H1OS Formal Concurrency Architecture & Codebase Review Report (`v2.4.5-dev`)

* **Document ID:** `H1OS-AUDIT-2026-10-28-R1`
* **Audit Standard:** `H1OS-STD-001` (`docs/architecture/D0_std_audit_framework.md`), NASA JPL *Power of Ten* (`PIT-01` – `PIT-11`), & `AGENTS.md` Architectural Governance
* **Target Hardware:** Waveshare ESP32-S3 ePaper 1.54" V2 (`ESP32-S3-PICO-1-N8R8`, Dual-Core Xtensa LX7 @ 80/240 MHz + ULP-RISC-V Coprocessor)
* **Evaluated Baseline:** `v2.4.4-dev` $\rightarrow$ **Remediated & Certified Release:** `v2.4.5-dev`
* **Scope:** `docs/mandates/concurrency_review_package/*`, `docs/mandates/mandate_02_dynamic_flow_periods_rfc.md`, `docs/mandates/mandate_04_lifecycle_concurrency_rfc.md`, `docs/mandates/mandate_06_error_handling_and_safe_shutdown_rfc.md`, `components/h1os/**` (34 source/header files), `examples/H1OS/**` (8 source/header files), and `docs/architecture/**`

---

## 1. Executive Summary & Forward Architectural Direction

An exhaustive review of the H1OS mandate package (`concurrency_review_package/01_h1os_lifecycle_concurrency_rfc.md`, `02_h1os_concurrency_solutions_plan.md`, `03_source_code_reference.md`, `MANDATE-02`, `MANDATE-04`, and `MANDATE-06`) and a line-by-line formal audit of the entire `components/h1os/` and `examples/H1OS/` source tree were conducted.

### 1.1 Selected Concurrency Architecture (`MANDATE-04` Forward Direction)
To resolve the dual-core concurrency standstill without breaking existing single-threaded applications or inducing double e-Paper refreshes, **H1OS `v2.4.5-dev` implements the Complementary Hybrid Dual-Core Architecture**:

1. **Overlapped Dual-Core Parallel Execution (`on_sync` on Core 0 $\parallel$ LVGL/SSD1681 on Core 1):**
   * On boot and wake cycles, `on_boot()` or `on_wake()` populates the initial RAM widget tree on Core 0 from `RTC_SLOW_MEM` telemetry.
   * `h1os_lvgl_start(5, 1)` immediately launches `h1os_lvgl_port_task` on **Core 1**, which renders the 1-bit frame buffer (`~8 ms` at 240 MHz), transfers 5,000 bytes over SPI2 DMA (`~2 ms`), and sleeps at **0% CPU** on the hardware falling-edge interrupt (`GPIO_INTR_NEGEDGE` on `GPIO 8` `EPD_BUSY`) while the SSD1681 state machine drives the physical microcapsules (`~300 ms` partial refresh or `~1413–1800 ms` full OTP refresh).
   * Concurrently on **Core 0**, `h1os_launch_interactive_session()` invokes the new `on_sync(&ctx, user_data)` hook so Wi-Fi/MQTT/HTTPS/BLE or SD card transactions execute in parallel with the physical e-Paper refresh, reducing total awake time from $T_{\text{net}} + T_{\text{disp}}$ to $\max(T_{\text{net}}, T_{\text{disp}})$.
2. **Statically Allocated FreeRTOS `EventGroup` Sleep Barrier (`BARRIER_SYNC_DONE | BARRIER_DISPLAY_DONE`):**
   * Unattended RTC Flow B wakes (`H1OS_WAKE_STATE_RTC_FLOW_B`) synchronize on a statically allocated FreeRTOS `EventGroup` (`xEventGroupCreateStatic(&s_sleep_barrier_buf)`) requiring both `BARRIER_SYNC_DONE` (signaled by `h1os_sync_notify_complete()`) and `BARRIER_DISPLAY_DONE` (signaled by `h1os_display_notify_quiescent()`) before entering `h1os_sleep()`.
   * Synchronous `on_sync()` callbacks automatically signal `h1os_sync_notify_complete()` upon return; asynchronous callbacks (such as ESP-IDF MQTT event handlers or background tasks) call `h1os_sync_hold()` inside `on_sync()` and invoke `h1os_sync_notify_complete()` when their transaction finishes (bounded by `session.sync_timeout_ms`, default `5000 ms`).
3. **Deterministic Single-Refresh Guarantee Across Both Outbound and Inbound Flows (`session.sync_wait_ms`):**
   * **Outbound Telemetry Mode (`session.sync_wait_ms == 0`, Default):** Local SHTC3, MCU Die TSENS, and ULP battery readings are already settled in `RTC_SLOW_MEM` at $T=0$. Core 1 flushes the display immediately while Core 0 transmits outbound telemetry in parallel.
   * **Inbound Cloud-Gated Mode (`session.sync_wait_ms > 0`):** When an application requires inbound remote data on-screen before flushing the e-Paper panel, `h1os_lvgl_set_sync_gate(sync_wait_ms)` holds Core 1's `lv_timer_handler()` up to `sync_wait_ms` (or until `h1os_sync_notify_complete()` releases the gate), coalescing initial `on_wake()` widgets and `h1os_ui_post()` mutations into **one single physical SSD1681 refresh**.
4. **Thread-Safe Static UI Actor Queue (`h1os_ui_post`) + Scoped Recursive Mutex (`h1os_lvgl_lock`):**
   * Added `h1os_ui_post(h1os_ui_fn_t fn, void *arg, uint32_t timeout_ms)` backed by a 16-slot statically allocated FreeRTOS queue (`xQueueCreateStatic`) that wakes Core 1 via `xTaskNotifyGive()` and drains inside Core 1's `h1os_lvgl_lock(100)` critical section prior to `lv_timer_handler()`.
   * Removed the coarse-grained outer `h1os_lvgl_lock(1000)` wrapper around `on_boot()`, `on_wake()`, `on_pre_sleep()`, and `on_shutdown()` in `h1os_lifecycle.c` (while retaining scoped `h1os_lvgl_lock(1000)` inside `h1os_trigger_splash()`), ensuring non-UI I/O inside lifecycle hooks never blocks Core 1.

---

## 2. Authoritative Answers to the 4 Concurrency Review Questions

| Question (`concurrency_review_package/README.md`) | Authoritative Engineering Resolution | Implementation Location |
| :--- | :--- | :--- |
| **Q1. Serialized vs. Overlapped Execution (Battery Impact)** | **Overlapped Parallel Execution ($\max(T_{\text{net}}, T_{\text{disp}})$) with Static `EventGroup` Sleep Barrier.** Core 0 runs `on_sync()` while Core 1 drives the SSD1681 refresh and sleeps on `GPIO_INTR_NEGEDGE` (`GPIO 8`). *Empirical Grounding Note (`AGENTS.md` Invariant 1.2):* SSD1681 partial (`~300 ms`) and full OTP (`~1413–1800 ms`) timings are hardware-measured baselines; the $T_{\text{net}} \approx 2.5\text{ s}$ and $\sim 42\%$ energy savings in `02_h1os_concurrency_solutions_plan.md` are analytical timing-model projections pending physical current-probe verification on connected Wi-Fi firmware. | `h1os_lifecycle.c:55-97`, `525-568` |
| **Q2. Double-Refresh Prevention (Outbound vs. Inbound)** | **Configurable Pre-Flush Gate (`session.sync_wait_ms`).** Default `sync_wait_ms = 0` starts the physical e-Paper refresh at $T=0$ in parallel with outbound `on_sync()`. Setting `sync_wait_ms > 0` holds Core 1's flush until `h1os_sync_notify_complete()` (or timeout), coalescing `on_wake()` and inbound `h1os_ui_post()` updates into a single physical refresh. | `h1os.h:198`, `h1os_lvgl.cpp:150-170`, `598-610` |
| **Q3. Inter-Core UI Mutation Mechanism** | **Complementary Hybrid (`h1os_ui_post` Static Queue + `h1os_lvgl_lock` Recursive Mutex).** Fixed a critical `S0` thread-safety defect in the draft plan (`02_h1os_concurrency_solutions_plan.md` §5.2) where `s_ui_queue` was drained *outside* `h1os_lvgl_lock()` and without waking `ulTaskNotifyTake()`. In `v2.4.5-dev`, `h1os_ui_post()` wakes Core 1 via `xTaskNotifyGive()` and `h1os_lvgl_port_task()` drains `s_ui_queue` *inside* `h1os_lvgl_lock(100)`. | `h1os_lvgl.h:26-37`, `95-115`, `h1os_lvgl.cpp:55-58`, `121-145`, `590-597` |
| **Q4. Lifecycle API Contract & Wake State Disambiguation** | **Additive, Non-Breaking Contract (`on_wake` + `on_sync` + `on_error` + `h1os_wake_state_t` + Monotonic Counters).** Implemented both Option 1 (`h1os_wake_state_t`: `BOOT`, `INTERACTIVE_SESSION`, `RTC_FLOW_B`) and Option 2 (`flow_b_counter`, `button_wake_count` in `RTC_SLOW_MEM`) across `orch_persisted_state_t`, `h1os_wake_context_t`, and `h1os_telemetry_t`. | `orch_state.h:110-111`, `h1os.h:68-96`, `orch_flow.c:86-116` |

---

## 3. Formal Codebase Audit Findings & Remediation Ledger (`v2.4.4-dev` $\rightarrow$ `v2.4.5-dev`)

| Finding ID | Severity | Taxonomy / Rule | File & Lines (`v2.4.4-dev`) | Root Cause Description | Remediation Applied in `v2.4.5-dev` | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **`REV-01`** | **`S0` (Blocker)** | `PIT-01-D` / `MANDATE-02` Init Order | `h1os_lifecycle.c:628-638`, `orch_flow.c:57-58`, `sub_power.c:347` | `h1os_start()` called `h1os_set_flow_periods_internal()` at line 628 *before* `h1os_early_system_bringup()` (line 638). Inside `h1os_early_system_bringup()`, `orch_flow_determine_wakeup()` detected cold boot and called `orch_state_reset()`, zeroing out `st->sample_interval_sec = 0` and `st->flow_b_period_sec = 0`. Line 363 then called `sub_power_init_ulp(0)`, which failed fast with `ESP_ERR_INVALID_ARG` on 100% of cold boots. On deep-sleep wakes, line 628 overwrote runtime `h1os_set_flow_periods()` intervals and zeroed `ulp_slice_counter` before `debug_dump_ulp_telemetry()`. | Split validation (`h1os_validate_flow_periods()`) from `RTC_SLOW_MEM` commit (`h1os_apply_flow_periods()`). `h1os_start()` validates `config->session` up front, and `h1os_early_system_bringup()` commits flow periods *after* `orch_flow_determine_wakeup()` and `debug_dump_ulp_telemetry()`, preserving runtime periods across deep sleep and passing non-zero `sample_interval_sec` to `sub_power_init_ulp()`. | **FIXED** |
| **`REV-02`** | **`S0` (Blocker)** | `PIT-01-A`, `PIT-01-C`, `PIT-07-B`, `MANDATE-04` | `h1os_lifecycle.c:468-507`, `h1os_lvgl.cpp:546-578` | Coarse-grained `h1os_lvgl_lock(1000)` wrapped `on_boot()`, `on_wake()`, `on_pre_sleep()`, and `on_shutdown()`; no parallel `on_sync()` phase or `EventGroup` sleep barrier existed; `h1os_wake_context_t` lacked explicit `wake_state` and monotonic `flow_b_count` / `button_wake_count`. | Removed outer 1000 ms lock on lifecycle hooks (moving scoped lock into `h1os_trigger_splash()`), added static 16-slot `h1os_ui_post()` queue drained inside `h1os_lvgl_lock(100)`, added `on_sync()` + static `EventGroup` sleep barrier (`BARRIER_SYNC_DONE \| BARRIER_DISPLAY_DONE`), and added `h1os_wake_state_t` + monotonic counters. | **FIXED** |
| **`REV-03`** | **`S0` (Blocker)** | `PIT-08-A`, `MANDATE-06` Battery Safety | `h1os_lifecycle.c:621-649`, `examples/H1OS/main/main.c:281-284` | If `h1os_start()` failed on battery power, `app_main()` returned while `GPIO 17` (`BAT_CTRL`) remained latched HIGH at 80–240 MHz (`~35 mA`), stranding the MCU until LiPo brownout (`< 3.25V`). | Added `h1os_error_cb_t on_error` to `h1os_lifecycle_t` and implemented `h1os_handle_fatal_startup_error()` to invoke `on_error`, place audio/display in standby, release `GPIO 17` (`BAT_CTRL`), and enter `EXT0` deep sleep on `GPIO 18` if USB power is attached. | **FIXED** |
| **`REV-04`** | **`S0` (Blocker)** | `PIT-02-E`, `AGENTS.md` §3 Step 4 | `sub_display.cpp:559,648,724-737`, `orch_flow.c:369-375` | `AGENTS.md` Section 3 Step 4 mandates a **250 ms physical settling delay** after `EPD_BUSY` (`GPIO 8`) falls LOW before issuing SSD1681 Deep Sleep Mode 1 (`0x10 = 0x01`). After `sub_display_wait_busy()` was converted to a microsecond-immediate `GPIO_INTR_NEGEDGE` ISR, `sub_display_enter_deep_sleep()` sent `0x10 = 0x01` within `< 15 ms` of `BUSY` falling LOW. | Recorded `s_last_refresh_done_us = esp_timer_get_time()` at the end of `sub_display_refresh_full()` and `sub_display_refresh_partial()`, and enforced the remaining `250 ms` post-refresh settling wait in `sub_display_enter_deep_sleep()` before sending `0x10 = 0x01`. | **FIXED** |
| **`REV-05`** | **`S2` (Major)** | JPL Rule 3 / `PIT-04-C` Static Allocation | `hal_i2c.c:80`, `sub_audio.c:538` | `hal_i2c_init()` used dynamic heap allocation `xSemaphoreCreateRecursiveMutex()` and `sub_audio_init()` used dynamic `xQueueCreate(8, sizeof(audio_cmd_t))` instead of static FreeRTOS buffers. | Replaced both with `xSemaphoreCreateRecursiveMutexStatic(&s_i2c_mutex_buf)` in `hal_i2c.c` and `xQueueCreateStatic(...)` in `sub_audio.c`. Zero dynamic FreeRTOS queue/semaphore/event-group allocations remain in H1OS. | **FIXED** |
| **`REV-06`** | **`S1` (Critical)** | `PIT-01-E`, `PIT-08-C` Task Teardown Race | `sub_audio.c:1082-1114` | `sub_audio_deinit()` deleted `s_tx_chan` and called `vTaskDelete(s_audio_task_handle)` without waiting for `sub_audio_wait_idle()` or signaling `audio_worker_task` to exit, risking mid-transfer I2S use-after-free or leaked `s_i2c_mutex` / `s_audio_pm_lock`. | Updated `sub_audio_deinit()` to call `sub_audio_wait_idle(1000)` and dispatch a cooperative `AUDIO_CMD_STOP` command synchronized on static `s_audio_stop_sem` before disabling and deleting `s_tx_chan`. | **FIXED** |
| **`REV-07`** | **`S1` (Critical)** | `AGENTS.md` §1.3 Four-Layer Hierarchy | `hal_types.h:13`, `sub_power.c:10,26,416`, `sub_audio.c:10,1186`, `sub_sdcard.c:10,248`, `examples/H1OS/**` | Layer 1 `hal_types.h` included Layer 3 `orch_state.h`; Layer 2 `sub_power.c`, `sub_audio.c`, and `sub_sdcard.c` included Layer 4 `h1os.h`; `examples/H1OS/` directly included Layer 1–3 headers (`hal_io.h`, `sub_audio.h`, `sub_power.h`, `sub_sdcard.h`) and called `orch_state_get()`. | Removed upward includes from `hal_types.h`, `sub_power.c`, `sub_audio.c`, and `sub_sdcard.c`; moved Layer 4 wrappers (`h1os_audio_play_*`, `h1os_sdcard_*`, `h1os_led_*`) to `h1os_lifecycle.c`; exposed diagnostic fields in `h1os_telemetry_t`; updated `examples/H1OS/` to use Layer 4 headers/APIs exclusively. | **FIXED** |
| **`REV-08`** | **`S2` (Minor)** | `B3_firmware_standards.md` & `AGENTS.md` §2 | `h1os_time.c:232,240`, `sub_power.c:299`, `Kconfig:24`, `sdkconfig.defaults:3`, `examples/H1OS/main/idf_component.yml:2`, `README.md:186` | Naked `int` local variables in `h1os_time.c` and `sub_power.c`; prohibited lexicon word `"neutralize"` in `Kconfig:24`; `"Touch"` in `sdkconfig.defaults:3`; `>=5.1` in `examples/H1OS/main/idf_component.yml`; `cd examples/H1OS` in `README.md`. | Replaced naked `int` with `int32_t`, replaced `"neutralize"` with `"clear and discharge"` in `Kconfig`, updated `sdkconfig.defaults` to `"Non-Touch"`, synchronized `idf: ">=6.1.0"`, and updated `README.md` to `cd examples/H1OS`. | **FIXED** |

---

## 4. `RTC_SLOW_MEM` & Internal SRAM Budget Verification

### 4.1 `orch_persisted_state_t` (`RTC_SLOW_MEM`) Footprint
* **Previous Size (`v2.4.4-dev`):** `640 bytes` (`160` 32-bit words)
* **Added Fields (`v2.4.5-dev`):**
  * `uint32_t flow_b_counter` (`4 bytes`, offset `12`)
  * `uint32_t button_wake_count` (`4 bytes`, offset `16`)
* **Updated Size (`v2.4.5-dev`):** `648 bytes` (`162` 32-bit words, `0` unaligned holes, `7.91%` of `8,192 B` `RTC_SLOW_MEM`).

### 4.2 Static FreeRTOS Synchronization Primitives Added in Internal SRAM
* `s_sleep_barrier_buf` (`StaticEventGroup_t` in `h1os_lifecycle.c`): `~32 B` static BSS
* `s_ui_queue_struct` + `s_ui_queue_storage[16 * 8]` (`StaticQueue_t` + `128 B` buffer in `h1os_lvgl.cpp`): `~216 B` static BSS
* `s_i2c_mutex_buf` (`StaticSemaphore_t` in `hal_i2c.c`): `~88 B` static BSS (converted from heap)
* `s_audio_queue_struct` + `s_audio_queue_storage[8 * 28]` + `s_audio_stop_sem_buffer` (`sub_audio.c`): `~392 B` static BSS (converted from heap)
* **Total Dynamic Heap Allocations for Synchronization Primitives:** **`0` (`100%` static allocation)**
