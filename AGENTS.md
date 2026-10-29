# H1OS Master Engineering Specification & Agent Invariants

This file constitutes the authoritative, always-active engineering and behavioral specification for autonomous agents and firmware developers working on **H1OS** (`v2.4.5-dev`) on ESP32-S3.

---

## 1. Core Directives & Architectural Invariants

1. **Zero Guesswork Policy (Code & Silicon):** NEVER guess or extrapolate function signatures, struct members, enums, peripheral pins, or configuration options. Use compiler-backed semantic code intelligence (`get_definition`, `find_references`, `get_type_info`, `get_callers`, `get_callees`) and authoritative headers (`h1os.h`, `hal_types.h`, `sub_*.h`, `orch_*.h`).
2. **Empirical Ground Truth & No Made-Up Numbers ("Sherlock Ohming vs. Fact"):**
   - **Never Fabricate Metrics:** Ballpark, baseline, or operational figures (e.g., deep sleep current, wake latency, quiescent power draw, thermal conduction rates) MUST be explicitly cited from an authoritative manufacturer datasheet or verified on physical test instruments (oscilloscope, DMM, power profiler). If a figure was neither measured on physical hardware nor read directly in official documentation, it is **NOT a valid engineering metric**. Presenting unmeasured estimates as factual quantities is strictly prohibited.
   - **Hypothesis vs. Fact Boundary ("Sherlock Ohming"):** Observed circuit behavior may strongly support an electrical deduction (e.g., parasitic reverse-powering via unpowered ESD clamping diodes, open-drain bus leakage), but without instrumented oscilloscope verification or explicit schematic evidence, it remains a **hypothesis**, NOT established fact. Deducing physical mechanisms is valuable engineering, but it MUST be explicitly labeled as an *unverified hypothesis / speculative deduction*, never asserted as empirical ground truth.
3. **Four-Layer Unidirectional Boundary Hierarchy:**
   - **Layer 1: HAL (`hal_*`)**: Stateless primitives directly manipulating registers and ESP-IDF peripheral drivers (`hal_io`, `hal_i2c`, `hal_spi`, `hal_adc`, `hal_i2s`, `hal_types`). Zero application state, zero psychrometric math.
   - **Layer 2: Peripheral Subsystems (`sub_*`)**: Encapsulated device drivers (`sub_display`, `sub_rtc`, `sub_power`, `sub_audio`, `sub_nvs`, `sub_sdcard`). Layer 2 subsystems **NEVER** communicate directly with one another and **NEVER** include Layer 3 (`orch_*`) or Layer 4 (`h1os_*`) headers. *(Note: `sub_sensor` is retired; SHTC3 and MCU die TSENS acquisition execute exclusively in Layer 3 `orch_wake_stub.c` to enforce zero-heat isolation.)*
   - **Layer 3: Orchestrator & ULP (`orch_*`)**: Flow arbiter (`orch_flow`), persistent `648-byte` RTC Slow Memory state (`orch_state`), headless `RTC_IRAM_ATTR` sensor wake stub (`orch_wake_stub`), thermodynamic invariant math (`orch_math`), and the Pure Event Mode ULP-RISC-V coprocessor monitor (`ulp/main.c`).
   - **Layer 4: Application Lifecycle (`h1os_*`)**: Declarative lifecycle & dual-core sleep barrier (`h1os_start`, `h1os_sleep`, `h1os_sync_hold`, `h1os_sync_notify_complete`), Core 1 LVGL v9 UI engine & actor queue (`h1os_lvgl.h`, `h1os_ui_post`), and time sync (`h1os_time.h`).
   - *Hierarchy Rule:* Upper layers call lower layers; lower layers **NEVER** call upper layers or cross-talk.
4. **Hardware-First Mandate ("Use the Hardware"):**
   - **Dual-Core Affinity & Parallel Execution (`v2.4.5-dev`):** Core 0 handles system orchestration, `on_sync()` Wi-Fi/BLE/ESP-NOW telemetry synchronization, async I/O (`sub_sdcard`, `sub_audio`), and headless Flow A bursts; Core 1 is dedicated strictly to the LVGL v9 presentation and SSD1681 e-Paper refresh task (`h1os_lvgl`, priority `5`).
   - **Power Latching & Fatal Startup Recovery (`MANDATE-06`):** `BAT_CTRL` (`GPIO 17`) is asserted in `h1os_boot_hook` within 25 ms and held across deep sleep via RTC pad hold. If any cold-boot hardware initialization fails (`orch_flow_init()`, `sub_display_init()`, or `h1os_lvgl_init()`), `h1os_handle_fatal_startup_error()` invokes `on_error(err, stage)` and immediately releases `GPIO 17` (`hal_io_release_power_latch()`) on battery power (or enters `EXT0` deep sleep on `GPIO 18` when USB power is attached) so a faulted board never drains the LiPo cell.
   - **Zero-Heat Sensing:** Never poll the SHTC3 during active CPU operation. SHTC3 sampling is restricted to headless Flow A sample bursts (`~18.5 ms` at 80 MHz in `orch_wake_stub.c`) so internal silicon heat cannot conduct across the PCB trace neck before the reading completes.
   - **Never Busy-Wait (Two-Domain Synchronization Law):**
     - **Awake FreeRTOS Domain (`hal_*`, `sub_*`, `orch_flow.c`, `h1os_*`):** Never spawn dedicated polling tasks or `vTaskDelay()` spin-wait loops to monitor timeouts, task exits, or hardware `BUSY`/button pins. Always use `esp_timer` (`esp_timer_start_once` / `esp_timer_start_periodic` / `esp_timer_restart`) for asynchronous timeouts and periodic state machines, GPIO edge interrupts (`gpio_isr_handler_add`) + hardware glitch filters (`gpio_new_pin_glitch_filter`) + `xSemaphoreTake` / `ulTaskNotifyTake` for hardware ready/busy/button lines, static `EventGroup` barriers (`xEventGroupCreateStatic`) for multi-subsystem sleep synchronization, and static binary semaphores (`xSemaphoreCreateBinaryStatic`) for cross-task teardown synchronization.
     - **Bare-Metal Sleep Domain (`orch_wake_stub.c` & `ulp/main.c`):** FreeRTOS, `esp_timer`, and `gptimer` interrupt vectors reside in Flash/IRAM and are unmapped or powered down during deep sleep. Inside `RTC_IRAM_ATTR` and ULP code, straight-line bounded `ccount`/register polling with `rtc_reg_barrier()` (`memw` / `fence`) and `__attribute__((noinline))` loop barriers is mandatory.
5. **Compiler Diagnostics & Two-Strike Resolution Protocol:**
   - Always verify compilation with the canonical ESP-IDF profile (`C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1`).
   - Keep header (`.h`) declarations and source (`.c`/`.cpp`) definitions atomically synchronized so the project compiles cleanly after every logical change.
   - If a build fails, isolate the exact diagnostic line and propose one targeted fix. If it fails a second time, **STOP IMMEDIATELY**, state the diagnostic verbatim, and request confirmation.

---

## 2. Engineering Nomenclature & Technical Lexicon Policy

Strictly adhere to professional **Embedded Systems Hardware and Software Engineering** standards. Informal jargon, military slang, pop-culture metaphors, and ideological commentary are strictly prohibited.

### Enforcement Scope & Zero-Judgment Boundary
1. **Mandatory Repository Scope:** This policy applies unconditionally to all content stored, persisted, or committed to the repository—including source code (`.c`, `.cpp`, `.h`), inline comments, git commit messages, git tags, pull request descriptions, documentation (`docs/`, `*.md`), and test ledgers.
2. **Interactive Chat Exemption:** Conversational brainstorming, rapid hypothesis exploration, casual dialog, and informal banter in interactive user chat are exempt from strict lexicon gating (zero-judgment zone). However, any text written to disk, committed to Git, or added as a project artifact MUST strictly conform to the engineering lexicon.

### Required Engineering Vocabulary Mapping
| Prohibited Jargon / Slang | Required Engineering Term | Technical Context |
| :--- | :--- | :--- |
| **stand-down / stand down** | **sleep transition / power down / suspend** | Transitioning the SoC or peripherals into deep sleep or low-power state. |
| **sentinel / sentry / bouncer** | **monitor / supervisor / watchdog** | Coprocessor, task, or interrupt handler overseeing events or state. |
| **tripwire** | **threshold / limit trigger / brownout detector** | Voltage, thermal, or timer boundary triggering a state transition. |
| **sprint / sortie / mission** | **sample / sample burst / measurement pass** | Ultra-fast sensor acquisition pulse before thermal conduction. |
| **recon / reconnaissance** | **probing / polling / scanning / telemetry query** | Checking bus lines, I2C discovery, or sensor interrogation. |
| **payload** | **data buffer / telemetry frame / sample packet** | Sensor reading struct, ring buffer element, or network transmission. |
| **scaffold purge / purge** | **removal / erase / clear / refactoring / pruning** | Deleting obsolete code, wiping configuration, or clearing caches. |
| **neutralize** | **clear / discharge / de-energize / reset** | Clearing display RAM, resetting DC bias, or de-asserting GPIO rails. |
| **kill / terminate (non-POSIX)**| **halt / disable / abort / power cut** | Graceful shutdown or gate de-assertion. |
| **fallback / fall back** | **default / recovery mode / safe state** | Fault handling logic. |
| **doctrine / dogma** | **standard / architecture / principle / specification**| Non-technical, cultish, or ideological framing. |
| **bones / muscle / vanity** | **contracts / subsystems / presentation layer** | Anatomical slang / informal construction metaphors. |

### The Tone & Professionalism Clause
1. **Eliminate Hostile / Adversarial Phrasing:** Prohibit violent idioms (*"nuke"*, *"blow away"*, *"destroy"*, *"wipe out"*, *"strangle"*). Use standard engineering terms (*"reset"*, *"erase"*, *"clear"*, *"abort"*).
2. **No Manifesto-Style Prose:** Maintain a neutral, matter-of-fact, dispassionate tone focused purely on empirical measurement, circuit schematics, system architecture, and API contracts.
3. **No Pop-Culture or Whimsical Lore:** Prohibit superheroes, movie quotes, religious/theological terms, and fantasy metaphors (*"magic"*, *"pixie dust"*, *"dragons"*). Note: *daemon* is permitted strictly in POSIX service context.
4. **No Ordnance or Ordnance Disposal Terminology:** Strictly prohibit all terms and analogies related to military ordnance, demolition, or ordnance disposal.
5. **No Pharmacological References:** Strictly prohibit all pharmacological, medicinal, and toxicological references.

---

## 3. Application Lifecycle, Dual Execution Flows & Dual-Core Concurrency (`v2.4.5-dev`)

`h1os_start()` (or `h1os_init()`) is the **MANDATORY single entry point** and lifecycle orchestrator. All state transitions, flow arbitration, parallel synchronization, and sleep transitions must be driven through `h1os_lifecycle_t`.

### Dual Execution Flows
1. **Flow A (Headless Telemetry Burst):**
   - Execution: Core 0 fast RTC wake stub (`orch_wake_stub.c` / `bsp_wake_stub()`) at 80 MHz (`~18.5 ms` total active duration, dominated by the `14.05 ms` SHTC3 normal-power measurement wait). Core 1 gated off, SPI Flash unpowered.
   - Execution Sequence: Wake on periodic PCF85063A RTC timer pulse (`GPIO 5`) forwarded by ULP Pure Event Mode $\rightarrow$ sample SHTC3 (`0x7866`) and MCU die TSENS $\rightarrow$ compute fixed-point psychrometric invariants (August-Roche-Magnus $e$, $T_{\text{dew}}$, absolute humidity $d_v$, EWMA) $\rightarrow$ commit to `648-byte` `orch_persisted_state_t` in `RTC_SLOW_MEM` $\rightarrow$ if `flow_a_counter < ratio_b_per_a`, re-arm RTC countdown and return directly to deep sleep; otherwise set `pending_flow_b = 1` and return to ROM bootloader to launch Flow B.
   - Thermal Invariant: Zero PCB self-heating bias. High-power rails and Flash remain unpowered during headless Flow A bursts.
2. **Flow B (Parallel Dual-Core Application / UI Wake):**
   - Execution: Dual-core FreeRTOS SMP with 240 MHz Turbo lock during SPI DMA transfers, dropping via DFS to 80 MHz during `GPIO 8` (`EPD_BUSY`) interrupt waits and idle interaction.
   - Trigger & Wake State (`h1os_wake_state_t`):
     - `H1OS_WAKE_STATE_BOOT`: Cold power-on reset (`boot_count` incremented; flow periods validated via `h1os_validate_flow_periods()` before `orch_flow_init()` and applied via `h1os_apply_flow_periods()` after `orch_state_reset()`).
     - `H1OS_WAKE_STATE_RTC_FLOW_B`: Headless periodic RTC Flow B wake (`flow_b_counter` incremented; executes `on_wake` + `on_sync` + parallel Core 1 e-Paper refresh, then enters deep sleep immediately upon barrier completion without starting the 30s inactivity timer).
     - `H1OS_WAKE_STATE_INTERACTIVE_SESSION`: User tactile button wake on `GPIO 0` or `GPIO 18` (`button_wake_count` incremented; runs interactive session bounded by the one-shot `esp_timer` inactivity timer `s_session_timer`).
   - Parallel Dual-Core Sequence (`v2.4.5-dev` / `MANDATE-04`):
     1. Core 0 validates `h1os_lifecycle_t`, runs `orch_flow_init()`, `sub_display_init()`, and `h1os_lvgl_init()` (routing any failure to `h1os_handle_fatal_startup_error()` / `on_error`).
     2. Core 0 invokes `on_boot()` (on cold boot) or `on_wake(&wake_ctx)` (while Core 1 LVGL task is not yet running, requiring no outer `h1os_lvgl_lock` wrapper; `h1os_trigger_splash()` acquires a scoped lock internally).
     3. If `session.sync_wait_ms > 0` and `on_sync` is registered, Core 0 arms the inbound pre-flush coalescing gate (`h1os_lvgl_set_sync_gate(sync_wait_ms)`).
     4. Core 0 spawns the Core 1 LVGL task via `h1os_lvgl_start(5, 1)` (`LVGL_TASK_PRIO_PORT = 5`, pinned to Core 1).
     5. Core 0 immediately invokes `on_sync(&wake_ctx)` **in parallel** with Core 1's LVGL layout and SSD1681 display refresh. Synchronous `on_sync` handlers auto-complete on return; asynchronous network handlers call `h1os_sync_hold()` before returning and `h1os_sync_notify_complete()` from their worker/callback when finished.

### Deterministic Sleep Transition & `EventGroup` Barrier Sequence
1. **Dual-Core Sleep Barrier (`s_lifecycle_event_group`):** Before powering down in `h1os_sleep()` (or after a headless `H1OS_WAKE_STATE_RTC_FLOW_B` wake), Core 0 blocks on `xEventGroupWaitBits(..., BARRIER_SYNC_DONE | BARRIER_DISPLAY_DONE, ...)` bounded by `session.sync_timeout_ms` (`5000 ms` default, plus `3500 ms` display refresh grace margin).
2. **Pre-Sleep Hook:** Core 0 invokes `on_pre_sleep()` (which may enqueue final UI mutations via `h1os_ui_post()`).
3. **Core 1 Drain & Teardown:** Core 0 calls `h1os_lvgl_wait_idle(3000)` and `h1os_lvgl_stop()`, draining any remaining queued `h1os_ui_post()` work items and halting the Core 1 task cleanly via static binary semaphore `s_stop_done_sem`.
4. **SSD1681 Deep Sleep & 250 ms Physical Settling Window (`REV-04`):** `sub_display_enter_deep_sleep()` waits on the `GPIO 8` (`EPD_BUSY`) falling-edge interrupt semaphore (`sub_display_wait_busy()`), then enforces the mandatory **250 ms post-`BUSY` electrophoretic settling delay** (`SUB_DISPLAY_SETTLING_WINDOW_MS`) before sending SSD1681 command `0x10` (`0x01`) so microcapsules never freeze mid-transition.
5. **Frame Persistence & NVS Commit Arbitration (`REV-07`):** If the framebuffer is dirty, `sub_display` commits the 5,000-byte 1-bit buffer to SPI Flash partition `epd_frame`. Layer 3 `orch_flow_execute_sleep()` (and Layer 4 `h1os_sleep()`) arbitrates hourly (`3600 s`) or immediate `sub_nvs_commit_runtime_stats()` updates.
6. **Peripheral Standby & Deep Sleep Entry:** `sub_power_enter_deep_sleep_mode()` places ES8311 in `<1 µA` software standby (`PA_EN` held LOW `0`), waits for open-drain interrupt lines (`GPIO 5`, `GPIO 0`, `GPIO 18`) to release HIGH, starts the ULP-RISC-V monitor in Pure Event Mode, holds `BAT_CTRL` (`GPIO 17`), and enters hardware deep sleep (`esp_deep_sleep_start()`).

---

## 4. LVGL v9 Bilevel UI, E-Paper Constraints & Cross-Core Actor Queue

All UI code targets the Waveshare ESP32-S3 ePaper 1.54" V2 panel (SSD1681 driver):
* **Geometry:** 200 x 200 pixels (1:1 square aspect ratio), 188 DPI.
* **Usable Margins & Maximum Width:** $X = 6\text{ px}$ to $194\text{ px}$. Maximum string width is strictly **$\le 188.0\text{ px}$**.
* **Color Depth:** 1-bit Monochrome (`LV_COLOR_FORMAT_I1`), pure black and pure white. Draw buffer: exactly 5,000 bytes (plus 8-byte LVGL v9 palette header in the draw buffer).
* **100% Opacity Mandate:** Opacity must always be `LV_OPA_COVER` (100%). Alpha blending, partial opacity (`LV_OPA_50`), and pseudo-random dithering are strictly prohibited.
* **Typography:** Minimum font height is **14 pixels** (e.g. `H1OS_FONT_14`). Fonts <14 px blur into illegibility during differential updates.
* **Proportional Font Rules:** Montserrat font metrics are proportional with 4-bit fractional advance widths and class kerning. Never use multiple spaces for alignment; use dual column labels or single-space padding.
* **Layout Grid (200 px Total):** Header ($Y = 0..20\text{ px}$ with 1 px bottom border), Body ($Y = 22..148\text{ px}$), Footer ($Y = 150..200\text{ px}$).
* **Cross-Core UI Mutation & Thread Safety (`MANDATE-04` / `REV-02`):**
  - **Preferred Non-Blocking Actor Pattern (Core 0 $\rightarrow$ Core 1):** Background tasks, `on_sync` handlers, and network callbacks on Core 0 should enqueue UI updates via `h1os_ui_post(h1os_ui_fn_t fn, void *arg, uint32_t timeout_ms)` (16-slot static FreeRTOS queue). Core 1 wakes immediately via `xTaskNotifyGive()` and executes every queued callback **inside `h1os_lvgl_lock(100)`** immediately before `lv_timer_handler()`.
  - **Direct Recursive Mutex Pattern:** When synchronous locking is required outside `on_wake`/`on_boot` or `h1os_ui_post`, wrap LVGL calls in `if (h1os_lvgl_lock(timeout_ms)) { ... h1os_lvgl_unlock(); }` (always passing an explicit `uint32_t timeout_ms` parameter).
  - **Single-Refresh Inbound Coalescing:** When `on_sync` fetches remote data to display on the current wake's screen, set `lifecycle.session.sync_wait_ms` (e.g. `250 ms`). Core 1 delays its first `lv_timer_handler()` flush until `h1os_sync_notify_complete()` releases the gate (or `sync_wait_ms` expires), coalescing `on_wake` + `on_sync` UI updates into a **single physical SSD1681 refresh**.
* **Font Validation Tools:** Verify all strings against layout boundaries using `python tools/agent/check_string_width.py --audit-screens` and CSV metrics in `tools/fonts/`.

---

## 5. Embedded C/C++ Coding Standards, Concurrency & Safety

1. **Memory Safety & Pointer Hygiene:**
   - Initialize all pointers to `NULL`. Set pointers to `NULL` immediately after `free()`.
   - Validate pointers at all subsystem boundaries (`if (ptr == NULL) return ESP_ERR_INVALID_ARG;`).
   - Check return values on all ESP-IDF and FreeRTOS calls (`ESP_ERROR_CHECK()` or deterministic propagation).
2. **100% Static RTOS Primitive Allocation (JPL Rule 3 / `PIT-04-C`):**
   - Never use dynamic heap allocation for RTOS synchronization primitives (`xSemaphoreCreateMutex`, `xQueueCreate`, `xEventGroupCreate`).
   - Exclusively use static storage (`StaticSemaphore_t`, `StaticQueue_t`, `StaticEventGroup_t`) with `xSemaphoreCreateMutexStatic()`, `xSemaphoreCreateRecursiveMutexStatic()`, `xSemaphoreCreateBinaryStatic()`, `xQueueCreateStatic()`, and `xEventGroupCreateStatic()`.
3. **Cooperative Worker Teardown (`PIT-01-E`):**
   - Never call `vTaskDelete()` externally on an active peripheral worker task or tear down hardware channels (`i2s_del_channel`, `spi_bus_remove_device`) while a worker task may be mid-transfer. Signal the worker via a stop command or atomic flag, wait on a static completion binary semaphore (`s_exit_sem` / `s_stop_done_sem`), and let the worker exit cleanly before releasing bus resources.
4. **Single-Responsibility Functions:** If a function performs more than one distinct task, split it into 2 or 3 smaller helper functions. Modularity and testability strictly supersede negligible call overhead.
5. **The Gump Naming Rule:** Name identifiers literally by what they physically do:
   `[Layer/Module Prefix] _ [Physical Target/Peripheral] _ [Literal Action]`
   *(e.g., `orch_flow_sample_sensors()`, `hal_io_release_power_latch()`, `sub_display_clear_to_white()`)*.
6. **Visual Block Alignment ("Pretty Code"):** Format struct definitions, constants, and function argument lists into clean, columnar blocks for rapid vertical scanning.

---

### 5.b Safety Invariants & Pitfall Catalog (`H1OS-STD-001`)
When generating, modifying, or reviewing firmware, enforce H1OS safety pitfalls. 
If an ID is cited or if auditing a domain, read `docs/architecture/D0_std_audit_framework.md`:

- **PIT-01 (Concurrency/RTOS):** No unbarriered cross-core shared state, no unbounded waits (`portMAX_DELAY`), atomic RMW, static priority inheritance mutexes, cooperative task deletion.
- **PIT-02 (Power/Sleep):** Pin pad isolation, pad hold (`BAT_CTRL`, active-low enables), button release debounce, PMU wake stabilization checks.
- **PIT-03 (Coprocessor/CDC):** Bitmask vs. shift macro typing (`_S` vs `_M`), RTC slow-clock CDC hold delays (≥120 µs), write-only strobe handling, pure event mode.
- **PIT-04 (Buses/Topology):** Shared-rail electrical isolation (no unpowered bus clamping), zero runtime heap allocations (`PIT-04-C`), bounded bus timeouts.
- **PIT-05 (Memory/Persistence):** `RTC_DATA_ATTR` for cross-sleep survival, cold-boot NVS ordering, static stack bounds (`.su`), explicit `nvs_commit()` before sleep.
- **PIT-06 (Metrology/Math):** Zero synthetic tare offsets/fudge factors, explicit single-precision `f` literals (`PIT-06-B`), `int64_t` promotion for fixed-point math, thermal settling verification.
- **PIT-07 (Display Pipeline):** No sleep during active charge pump/EPD refresh, cross-core `lv_lock` protection, partial refresh scrubbing.
- **PIT-08 (Driver Robustness):** Checked `esp_err_t` returns, bounded hardware polling loops, structured `goto cleanup;` resource release.

---

## 6. Empirical Science & Mathematical Grounding

* **Math Precedes Code:** Never implement heuristic curve-fitting or synthetic sensor scaling when physical governing equations exist.
* **August-Roche-Magnus Psychrometrics:** True water vapor pressure ($e$) and dew point ($T_{\text{dew}}$) are thermodynamic invariants unaffected by PCB self-heating. Compute using August-Roche-Magnus formulations (`orch_math.c`).
* **LiPo State of Charge (SoC):** Compute battery percentage using the empirical 13-point Open-Circuit Voltage (OCV) lookup curve rather than linear voltage approximations (`sub_power.c`).
* **Integer Fixed-Point Math:** Because the ULP-RISC-V coprocessor and RTC wake stub avoid floating-point library calls in sleep context, compute in centi-degrees ($1^\circ\text{C} = 100$), centi-percent RH, and centi-Kelvin ($0^\circ\text{C} = 27315$).

---

## 7. Release Governance & Pre-Merge Checklist

Direct commits to `main` are strictly prohibited. Before merging any branch into `main`:
1. **Identity & Name Sanitization Audit:** Run `python tools/agent/sanitize.py --check` (or `--fix`) to verify zero personal identities, workstation usernames, or local filesystem paths leak into committed repository files or release archives.
2. **Asset Optimization & Metadata Invariant (`/shrink` or `/quant`):** Execute the repository asset shrink pipeline (`tools/agent/optimize_images.py` and `tools/agent/optimize_pdf.py`) prior to staging or committing changes. All photographic evidence must be stamped with all-caps EXIF attribution (`HUMIDITRON/HUMADYNE_LABS`) and progressive JPEG quantization. PDFs are strictly preserved in their original compressed format with lossless metadata harmonization.
3. **Zero-Warning Build:** Verify compilation passes with 0 warnings/errors via `idf.py -B build_dev build`. You must build the examples inside `examples/H1OS` (the showcase project directory) to avoid polluting the repository root.
4. **Mandatory `sdkconfig` Removal Invariant:** Always remove `examples/H1OS/sdkconfig` and `sdkconfig.old` before reconfiguring or switching presets (`--preset dev` vs `--preset prod`).
5. **Synchronize 4 Version Strings:** Update `h1os_version.h`, `idf_component.yml`, `README.md`, and `CHANGELOG.md`.
6. **Regenerate API Documentation:** Run `doxygen Doxyfile; moxygen --flavor github -a -o docs/api.md docs/doxygen/xml`.
7. **Touch Changelog:** Record changes in `CHANGELOG.md` under Keep a Changelog categories (`Added`, `Changed`, `Fixed & Hardened`, `Removed`).
8. **Tag Release:** Push annotated tag `vX.Y.Z-tag` to remote.

---

## 8. Documentation Governance, Living Memory & Architecture Index ("Documentation is Law")

> *"Documentation is memory and history reflective of progress and hard lessons learned. We document the weeds so we can find flowers next time."*

### The Documentation Laws
1. **Synchronous Updates:** Documentation is never an afterthought. When APIs, state machines, hardware pinouts, or peripheral configurations change, corresponding documentation in [`docs/`](docs/) MUST be updated in the exact same commit.
2. **Failure Analysis & Living Errata:** Document design dead-ends, silicon hardware limitations, and discarded workarounds in [`docs/architecture/C2_lessons_learned.md`](docs/architecture/C2_lessons_learned.md) and [`ERRATA.md`](ERRATA.md). Never erase historical technical rationale—distill it so future engineers avoid repeating discarded experiments.
3. **Open-Source Hardware (OSHW) & Attribution:** Maintain clear board schematics, pinout tables ([`docs/pinout.md`](docs/pinout.md)), and appropriate SPDX license identifiers (`SPDX-License-Identifier: MIT` or `CC-BY-4.0`) across all code and documentation files. Always credit upstream algorithms, font authors, and drivers.

### Authoritative Architecture Index ([`docs/architecture/`](docs/architecture/))
Cross-reference the canonical system blueprint documents before modifying architecture:

| Category | Authoritative Architecture Document | Core Scope |
| :--- | :--- | :--- |
| **System Governance** | [`A0_system_governance.md`](docs/architecture/A0_system_governance.md) | Architectural standards, module ownership, and layer compliance. |
| **Master Blueprint** | [`A1_master_blueprint.md`](docs/architecture/A1_master_blueprint.md) | High-level system topology, dual-core concurrency, and hardware block diagrams. |
| **HAL Layer** | [`A2_hal.md`](docs/architecture/A2_hal.md) | Stateless Layer 1 drivers, register maps, and peripheral abstractions. |
| **Power & Sleep** | [`A3_gpio_hold_and_sleep.md`](docs/architecture/A3_gpio_hold_and_sleep.md) | RTC pad hold states, latching circuit, and power rail sequencing. |
| **Subsystems** | [`A4_subsystems.md`](docs/architecture/A4_subsystems.md) | Layer 2 encapsulated drivers (display, audio, RTC, power, NVS, SD). |
| **Orchestrator** | [`A5_orchestrator.md`](docs/architecture/A5_orchestrator.md) | Layer 3 flow arbiter (Flow A vs Flow B) and `648-byte` RTC Slow Memory state. |
| **ULP Coprocessor** | [`A6_ulp_coprocessor.md`](docs/architecture/A6_ulp_coprocessor.md) | ULP-RISC-V Pure Event Mode monitor, memory layout, and sleep gating. |
| **Psychrometrics** | [`A7_sensor_psychrometrics.md`](docs/architecture/A7_sensor_psychrometrics.md) | Thermodynamic invariants, August-Roche-Magnus math, and TSENS. |
| **Battery & Power** | [`A8_battery_and_power_management.md`](docs/architecture/A8_battery_and_power_management.md) | 13-point LiPo OCV lookup curve and dynamic power management. |
| **Application API** | [`B1_api_and_services.md`](docs/architecture/B1_api_and_services.md) | Layer 4 declarative lifecycle, `on_sync` / `on_error` hooks, `h1os_ui_post`, and services. |
| **State Machine** | [`B2_state_machine.md`](docs/architecture/B2_state_machine.md) | Deterministic state transitions, `EventGroup` sleep barrier, and wake handling. |
| **Firmware Standards** | [`B3_firmware_standards.md`](docs/architecture/B3_firmware_standards.md) | Coding style, safety hierarchy, pointer hygiene, and formatting. |
| **Verification** | [`C1_benchmarks_and_verification.md`](docs/architecture/C1_benchmarks_and_verification.md) | Timing benchmarks, memory budgets, and power profile metrics. |
| **Lessons Learned** | [`C2_lessons_learned.md`](docs/architecture/C2_lessons_learned.md) | Historical errata, failed trials, and discarded hardware workarounds. |
| **Roadmap** | [`C3_roadmap.md`](docs/architecture/C3_roadmap.md) | Phased subsystem milestones, concurrency evolution, and Rev B hardware targets. |
| **Changelog Policy** | [`C4_changelog_policy.md`](docs/architecture/C4_changelog_policy.md) | Keep a Changelog formatting rules and release procedures. |
| **Audit Framework** | [`D0_std_audit_framework.md`](docs/architecture/D0_std_audit_framework.md) | 5-tier safety and architectural audit rubric (JPL, BARR-C, MISRA, CERT-C, Espressif). |

---

## 9. MCP Tool Harness: Scope, Architecture & Strategic Planning

The 3-Finger MCP tool suite equips the agent with compiler-grade AST intelligence, binary memory profiling, hardware telemetry SQL, and formal mathematical solvers. Using the right tool eliminates guesswork, prevents token burn, and guarantees physical correctness.

### 1. Semantic Code Intelligence (`clangd`)
* **Available Tools:** `find_symbol`, `get_definition`, `find_references`, `get_type_info`, `get_callers`, `get_callees`, `list_file_symbols`.
* **Purpose & Application:** AST-accurate C/C++ semantic navigation backed by LLVM 18 and `compile_commands.json`. Resolves active `#ifdef` configurations, struct layouts, type hierarchies, and full incoming/outgoing call graphs.
* **Why Preferred Over `grep`:**
  - `grep` is syntactic and blind: it returns false positives in comments, string literals, inactive `#if 0` blocks, and similarly named variables across unrelated files.
  - `clangd` is semantic and exact: `get_definition` jumps straight to the true compiler definition; `find_references` lists exact call sites; `get_type_info` provides precise struct packing and byte offsets.
* **Workflow Example:**
  - ❌ *Bad:* Running `grep -r "sensor_fail_count"` across all files, reading 50 lines of context per match.
  - ✅ *Good:* Calling `get_definition` on `orch_sensor_err_t` to verify enum values, then `find_references` on `sensor_fail_count` to map every assignment in `orch_wake_stub.c`.

### 2. Embedded Diagnostics & Memory Budgets (`embedded-ops`)
* **Available Tools:** `murdock_memory_budget`, `ba_serial_capture_and_decode`, `clangd_touch_reload`.
* **Purpose & Application:** Binary inspection and runtime verification.
  - `murdock_memory_budget`: Evaluates compiled `h1os.elf` using `xtensa-esp32s3-elf-size` and `nm` to return structured JSON byte counts for DRAM, DIRAM, RTC Slow, and Flash partition headroom.
  - `ba_serial_capture_and_decode`: Captures serial boot sequences and automatically runs `xtensa-esp32s3-elf-addr2line` to decode panic backtraces to `file:line (function)`.
  - `clangd_touch_reload`: Busts clangd AST cache after CMake reconfigures without restarting sessions.
* **Why Preferred Over Host Text Dumps:** Eliminates manual calculation of linker map addresses; immediately catches RTC Slow SRAM overflow (>4 KB) before hardware deployment.

### 3. Telemetry & Tabular Analytics (`duckdb`)
* **Available Tools:** `query`.
* **Purpose & Application:** High-performance in-memory SQL analytics directly against disk CSV and Parquet files without database imports or file-locking conflicts.
* **Why Preferred Over Ad-Hoc Scripts:**
  - Allows instant multi-file aggregation (e.g., font metric audits, temperature delta queries over 10-hour chamber tests) in a single turn without writing throwaway Python parsing scripts.
* **Workflow Example:**
  - ❌ *Bad:* Writing a 40-line Python script to load `char_widths_montserrat_14.csv`, sort by width, and print the top 5 widest characters.
  - ✅ *Good:* Executing `SELECT char, width_px FROM 'tools/fonts/char_widths_montserrat_14.csv' ORDER BY width_px DESC LIMIT 5;` via DuckDB.

### 4. Mathematical Grounding & Formal Verification (`science`)
* **Available Tools:** `derive_fixed_point_polynomial`, `solve_z3_assertions`, `fit_thermal_rc`, `eval_symbolic_math`.
* **Purpose & Application:**
  - `derive_fixed_point_polynomial`: Derives Chebyshev/Padé minimax polynomial approximations for FPU-less ULP RISC-V in Q16.16/Q8.24 with Horner evaluation C code and error bounds.
  - `solve_z3_assertions`: Formal SMT verification proving freedom from race conditions and GPIO latch deadlocks.
  - `fit_thermal_rc`: Empirical curve-fitting of sensor thermal step responses ($\tau$).
* **Why Preferred Over Heuristic Guessing:** Produces mathematically optimal, cycle-efficient fixed-point approximations rather than trial-and-error lookup tables.

### 5. Documentation & Technical Reference (`local-index` & `espressif-documentation`)
* **Available Tools:** `search_code_advanced`, `find_files`, `get_file_summary`, `search_espressif_sources`.
* **Purpose & Application:** Precision search across repository architecture docs, IC datasheets (SHTC3, PCF85063A, ES8311, SSD1681), and Espressif Technical Reference Manuals.
* **Tool Quirk:** `local-index/search_code_advanced` strictly requires argument `pattern: str` (do not pass `query`).

---

## 10. Senior Architect's Field Guide for Future Junior Agents & Maintainers

Welcome to the H1OS source tree. Every line in this repository exists because physical hardware—a dual-core ESP32-S3-PICO-1-N8R8, a 200x200 SSD1681 e-Paper panel, a Sensirion SHTC3 sensor, a PCF85063A quartz RTC, and an ES8311/NS4168 audio pipeline—demanded it on the bench. Before modifying any file, internalize these seven engineering principles:

1. **Respect the Two Execution Worlds (FreeRTOS Awake vs. Bare-Metal RTC Sleep):**
   - When the system is **awake in Flow B**, let hardware interrupts, `esp_timer`, and static FreeRTOS `EventGroup` / `Queue` / `Semaphore` primitives do the waiting. Never write a `while (busy) { vTaskDelay(10); }` loop or spawn a `4 KB` FreeRTOS task just to poll a timestamp or a GPIO pin. Use `esp_timer` one-shot/periodic alarms, `GPIO_INTR_NEGEDGE`/`GPIO_INTR_ANYEDGE` ISRs, and static binary semaphores (`xSemaphoreCreateBinaryStatic`) so both Xtensa cores can enter low-power idle states cleanly—especially when upper-layer applications run Wi-Fi and BLE stacks on Core 0.
   - When the system is **asleep in Flow A (`orch_wake_stub.c`) or the ULP (`ulp/main.c`)**, SPI NOR Flash is powered off and the MMU cache is disabled. Never call standard library functions (`memset`, `memcpy`), `esp_timer`, or FreeRTOS primitives from `orch_wake_stub.c`. Always guard fixed-trip-count bit-bang loops with `__attribute__((noinline))` and inline assembly loop clobbers (`asm volatile("" : "+r"(i))`), guard local array zeroing with `asm volatile("" : "+m"(buf[i]))` so GCC `-O2` `-ftree-loop-distribute-patterns` never synthesizes a fatal call to Flash-resident `memset`, and place `rtc_reg_barrier()` (`memw` on Xtensa, `fence` on RISC-V) between sequential peripheral register writes.
2. **Coordinate Core 0 I/O & Core 1 e-Paper Refresh Without Blocking (`v2.4.5-dev`):**
   - Core 1 owns the LVGL v9 context and SSD1681 SPI bus; Core 0 owns `on_sync()` telemetry and background peripheral I/O. Never hold `h1os_lvgl_lock()` across slow network, SD card, or I2C operations. Enqueue cross-core UI updates via `h1os_ui_post(fn, arg, timeout_ms)`, use `h1os_sync_hold()` / `h1os_sync_notify_complete()` for asynchronous radio transfers, and configure `session.sync_wait_ms` when inbound data must coalesce into a single physical e-Paper refresh before deep sleep.
3. **Never Fight Physics with Software Fudge Factors:**
   - The SHTC3 is factory-calibrated. When the PCB is thermally settled (`|T2 - T1| <= 0.20 C` across consecutive quiescent Flow A wakes), trust the SHTC3 directly and compute true water vapor pressure ($e$), dew point ($T_{\text{dew}}$), and absolute humidity ($d_v$) using pure August-Roche-Magnus equations. Never add synthetic temperature offsets or linear tares.
4. **Protect the Shared Open-Drain I2C Bus (`GPIO 47` SDA / `GPIO 48` SCL):**
   - Three peripherals share `I2C_NUM_0`: SHTC3 (`0x70`), PCF85063A (`0x51`), and ES8311 (`0x18`). Never cut `PA_EN` (`GPIO 42`) power (keep ES8311 in `<1 uA` software standby instead per Errata E4), always verify `SCL` high rise (`scl_high_wait()`) to honor slave clock stretching, and always send `NACK` (`false`) on the final byte of any master I2C read frame so the slave releases `SDA` high before `STOP`.
5. **Guard Flash Endurance, Static SRAM Headroom & Cold-Boot Ordering:**
   - Keep `RTC_SLOW_MEM` structures compact (`orch_persisted_state_t` is `648 bytes`) and allocate synchronization primitives statically (`StaticSemaphore_t`, `StaticQueue_t`, `StaticEventGroup_t`) with zero runtime heap churn (`PIT-04-C`). On cold boot, validate flow periods before `orch_flow_init()` and apply them via `h1os_apply_flow_periods()` *after* `orch_state_reset()` so configured intervals are never overwritten by defaults (`REV-01`). Throttle periodic NVS Flash commits in Layer 3/4 to hourly Flow B piggyback intervals (`ORCH_NVS_AUTONOMY_COMMIT_INTERVAL_SEC = 3600`) paired with immediate commits on clean shutdown or state transitions.
6. **Measure Twice, Cut Once (Craftsmanship & Humility):**
   - Read the target header, trace every caller, check the hardware errata (`ERRATA.md`), and verify numeric bounds in 64-bit arithmetic before writing code. Leave every module cleaner, leaner, and more deterministic than you found it.
7. **Never Bloat Git History (Asset Hygiene & The `/shrink` Directive):**
   - Git is an immutable distributed ledger; checking in 15 MB uncompressed Chinese font files, multi-megabyte digital camera photos, or redundant GIMP archives penalizes every developer who clones the repo forever. Always run `/shrink` (or `python tools/agent/optimize_images.py` and `python tools/agent/optimize_pdf.py`) before commits. Guarantee that all EXIF and PDF metadata is stamped `HUMIDITRON/HUMADYNE_LABS`, and PDF streams/vector schematics are never degraded.

---

## 11. Engineering Attribution & Contributors

* **Lead Hardware & Systems Architect:** Humiditron (Humidyne Labs)
* **Principal Firmware Audit, Dual-Core Concurrency (`MANDATE-04` / `MANDATE-06`), `-O2` Wake Stub Hardening & Event-Driven Architecture Refactor (`v2.4.4-dev` – `v2.4.5-dev`):** Gemini (Autonomous Embedded Systems Architect & Principal Auditor)
* **Core Firmware Development, Metrology & Simulation Engineering (`v2.0` – `v2.4.3-dev`):** Antigravity Gemini 3.8 (Junior Embedded Systems Agent)
