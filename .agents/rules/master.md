# Master Agent Execution Rules: H1OS & ESP32-S3 Firmware Development (`v2.4.5-dev`)

## 1. Core Directives & Mandates

1. **Zero Guesswork Policy:** NEVER guess or extrapolate function prototypes, struct members, enums, peripheral pins, or configuration flags.
   - Use compiler-backed semantic code intelligence (`get_definition`, `find_references`, `get_type_info`, `get_callers`, `get_callees`) for exact symbol inspection.
   - Cross-reference authoritative headers (`h1os.h`, `hal_types.h`, `sub_*.h`, `orch_*.h`) before authoring calls.
2. **Four-Layer Unidirectional Boundary Hierarchy:**
   - **Layer 1: HAL (`hal_*`)**: Stateless primitives manipulating registers and buses (`hal_io`, `hal_i2c`, `hal_spi`, `hal_adc`, `hal_i2s`, `hal_types`). Zero application state, zero math.
   - **Layer 2: Peripheral Subsystems (`sub_*`)**: Encapsulated device drivers (`sub_display`, `sub_rtc`, `sub_power`, `sub_audio`, `sub_nvs`, `sub_sdcard`). *(Note: `sub_sensor` is retired; SHTC3 and MCU die TSENS run exclusively in Layer 3 `orch_wake_stub.c`.)*
   - **Layer 3: Orchestrator & ULP (`orch_*`)**: Flow arbiter (Flow A vs. Flow B), persistent `648-byte` RTC state (`orch_state`), headless `RTC_IRAM_ATTR` sensor wake stub (`orch_wake_stub`), thermodynamic invariant math (`orch_math`), and the Pure Event Mode ULP-RISC-V coprocessor monitor (`ulp/main.c`).
   - **Layer 4: Application Lifecycle (`h1os_*`)**: Declarative lifecycle & dual-core sleep barrier (`h1os_start`, `h1os_sleep`, `h1os_sync_hold`, `h1os_sync_notify_complete`), Core 1 LVGL v9 UI engine & actor queue (`h1os_lvgl.h`, `h1os_ui_post`), and time sync (`h1os_time.h`).
   - *Invariants:* Upper layers call lower layers; lower layers **NEVER** call up or cross-talk.
3. **Strict Error Checking & Fatal Startup Recovery (`MANDATE-06`):** Every ESP-IDF, FreeRTOS, and H1OS API call returning `esp_err_t` MUST be checked via `ESP_ERROR_CHECK()` or handled deterministically. Any fatal cold-boot failure in `h1os_start()` must route through `h1os_handle_fatal_startup_error()` (`on_error`) to release `BAT_CTRL` (`GPIO 17`) on battery power.
4. **Hardware-First Mandate ("Use the Hardware"):**
   - **Dual-Core Affinity & Parallel Execution (`MANDATE-04`):** Core 0 handles system orchestration, parallel `on_sync()` telemetry, and headless Flow A bursts; Core 1 is dedicated to the LVGL v9 presentation task (`h1os_lvgl`, priority `5`).
   - **Power Latching:** `BAT_CTRL` (`GPIO 17`) is asserted in `h1os_boot_hook` within 25 ms and held via RTC pad hold across deep sleep.
   - **Zero-Heat Sensing:** Never poll the SHTC3 during active CPU operation. SHTC3 sampling is restricted to headless Flow A sample bursts (`~18.5 ms` at 80 MHz in `orch_wake_stub.c`).
   - **Never Busy-Wait & 100% Static RTOS Primitives:** Never spin in `vTaskDelay()` loops during awake states; block on `esp_timer`, GPIO interrupts, or static FreeRTOS notifications/semaphores/event groups (`xSemaphoreCreate*Static`, `xQueueCreateStatic`, `xEventGroupCreateStatic`).

---

## 2. Constraint-Driven UI Development (LVGL 9 Bilevel Specification)

All graphics code MUST comply with `.agents/rules/lvgl.md`:
* **Geometry & Usable Boundary:** 200 x 200 pixels, 1:1 aspect ratio, 188 DPI. Maximum text width is $\le 188.0\text{ px}$ ($X = 6..194\text{ px}$).
* **Color Depth & Buffer:** 1-bit Monochrome (`LV_COLOR_FORMAT_I1`), pure black/white, 5,000-byte pixel draw buffer (plus 8-byte palette header).
* **100% Opacity Mandate:** Opacity must strictly be `LV_OPA_COVER`. Alpha blending, dithering, and partial opacity are prohibited.
* **Spatial Budget:** Header ($Y = 0..20\text{ px}$ with 1 px bottom border), Body ($Y = 22..148\text{ px}$), Footer ($Y = 150..200\text{ px}$).
* **Typography:** Minimum font height is **14 pixels**. Small fonts (<14 px) bleed and are forbidden.
* **Thread Safety & Cross-Core Queueing:** From Core 0 background/sync contexts, post UI mutations via `h1os_ui_post(fn, arg, timeout_ms)` (drained on Core 1 inside `h1os_lvgl_lock(100)`), or wrap synchronous mutations in `if (h1os_lvgl_lock(timeout_ms)) { ... h1os_lvgl_unlock(); }`.

---

## 3. Subagent Spawning & Parallel Delegation

Proactively spawn subagents using `invoke_subagent` whenever:
* **Research & Deep Lookups:** Multi-file codebase sweeps, register maps, or datasheet conversions (delegate to `research` subagent).
* **Parallel Build & Analysis:** Independent tasks running concurrently (e.g. build verification running alongside documentation synthesis).
* **Autonomous Continuation:** Do NOT poll subagents in loops; wait for reactive background system messages.

---

## 4. Compiler Diagnostics & Two-Strike Resolution Protocol

* **Verification Mandate:** Never declare success without compilation verification via the canonical profile command (`C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1`) inside `examples/public`. Keep `.h` declarations and `.c`/`.cpp` definitions atomically synchronized.
* **Two-Strike Protocol:**
  1. If compilation fails, isolate the exact diagnostic line from compiler output.
  2. Propose exactly one targeted syntactic or signature fix.
  3. If compilation fails a second time, **STOP IMMEDIATELY**. Do not guess alternative signatures or cast types to force compilation. State the diagnostic verbatim and ask the user for confirmation.

---

## 5. Naming & Code Aesthetics

* **The Gump Naming Rule:** Name identifiers literally by what they physically do:
  `[Layer/Module Prefix] _ [Physical Target/Peripheral] _ [Literal Action]`
  *(e.g., `orch_flow_sample_sensors()`, `hal_io_release_power_latch()`, `sub_display_clear_to_white()`)*.
* **Visual Block Alignment ("Pretty Code"):** Format struct definitions, constants, and function arguments into clean columnar blocks for rapid vertical scanning.
