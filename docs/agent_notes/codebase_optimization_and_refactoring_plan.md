# Architectural Optimization & Refactoring Analysis

**Document:** `codebase_optimization_and_refactoring_plan.md`  
**Target Scope:** Entire `components/h1os` tree (`src/`, `include/h1os/`, `ulp/`, `bootloader_components/`)  
**Focus Areas:**
1. Logic & State Machine Optimizations
2. Mathematical & Register Operation Streamlining
3. Function Consolidation (Eliminating fragmentation and redundancy)
4. Separation of Concerns for Overly "Busy" Functions (Readable, high-cohesion design)  
**Git Working Branch:** `prune`

---

## 1. Executive Overview

A detailed walkthrough of the physical implementation across the 41 source and header files in `components/h1os` highlights an advanced hardware-grounded architecture. However, several modules carry evolutionary technical debt from rapid iteration:
- **Busy monolithic functions** mixing device hardware control, math calculations, RTOS task management, and UI logic in a single body.
- **Redundant functions and scattered register pokes** performing nearly identical actions across different layers.
- **Repeated floating-point operations** that can be converted to integer fixed-point arithmetic or consolidated into unified math pipelines.
- **Duplicated state tracking** where flags are asserted in multiple locations without a single authoritative state transition.

This document identifies specific functions and algorithms across the codebase, categorizes them into concrete optimization patterns, and provides architectural refactorings.

---

## 2. Logic & State Machine Optimizations

### 2.1 The Two-Headed Flow A Dual Pipeline (`h1os_lifecycle.c` vs `orch_wake_stub.c`)
- **Current State:**
  - `orch_wake_stub.c` implements low-power bit-bang I2C sensor acquisition, die TSENS conversion, thermal delta gating, and ring buffer commit in $<3\text{ ms}$ inside RTC Fast Memory.
  - `orch_flow_execute_sensor_sample()` in `orch_flow.c` implements the exact same sequence using high-level I2C drivers in the OS runtime (~25 ms).
  - `h1os_lifecycle.c` (lines 238–263) contains a full conditional branch to run `orch_flow_execute_sensor_sample()` inside FreeRTOS.
- **Optimization / Remedy:**
  - **Excise the OS-side Flow A runtime:** Flow A belongs exclusively in the bare-metal wake stub (`orch_wake_stub.c`).
  - Delete `orch_flow_execute_sensor_sample()` from `orch_flow.c`.
  - Delete lines 238–263 from `h1os_lifecycle.c`.
  - Install the wake stub once in `sub_power_enter_deep_sleep_mode()` via `orch_wake_stub_install()`.
  - **Result:** Saves >150 lines of duplicate C code, eliminates dual-path logic divergence, and prevents FreeRTOS from ever booting on sensor pulses.

### 2.2 ULP Button State Tracking & Dispatch Logic (`ulp/main.c`)
- **Current State:**
  - `ulp_dispatch_and_wake()` evaluates triggers via a cascade of `if-else` branches: brownout check $\rightarrow$ GPIO 0 check $\rightarrow$ GPIO 18 check $\rightarrow$ GPIO 5 tick check $\rightarrow$ timeout loop.
  - Button state is read instantaneously without debouncing or tracking hold duration.
- **Optimization / Remedy:**
  - Replace the ad-hoc `if-else` chain with a deterministic state machine:
    - `EVENT_CLASSIFY`: Evaluates wake status mask.
    - `GLITCH_DEBOUNCE`: Runs a 30 ms delay loop to verify switch contact stability.
    - `HOLD_TIMING`: Loops with a 50 ms tick while pin is LOW. If $T_{\text{hold}} > 2500\text{ms}$, transitions to `DISPATCH_LONG_HOLD`. If released ($50\text{ms} \le T_{\text{hold}} \le 800\text{ms}$), transitions to `DISPATCH_TAP_RELEASE`.
    - `EXEC_WAKE`: Performs CDC-compliant register clearing and signals the main CPU.
  - **Result:** Solves the missing Wake-on-Release rule, eliminates false wakes from switch chatter, and structures coprocessor execution into clean, verifiable states.

### 2.3 Thermal Lockout State MUX (`orch_flow.c`)
- **Current State:**
  - `orch_flow.c` maintains a manual setter `orch_flow_set_thermal_lockout(bool enable, uint32_t duration_sec)` that modifies `st->flags |= ORCH_FLAG_THERMAL_LOCKOUT`.
  - Meanwhile, `orch_flow_query_telemetry()` computes `amb_mode` autonomously based on `valid_trend < 2` and `window_avg_shtc3 > window_avg_die`.
  - The manual setter is dead scaffolding that conflicts with the autonomous state evaluator.
- **Optimization / Remedy:**
  - Delete `orch_flow_set_thermal_lockout()`.
  - Consolidate thermal lockout into an authoritative inline state query:
    ```c
    static inline bool orch_flow_is_thermal_lockout(const orch_persisted_state_t *st) {
        return (st->valid_trend < 2) || 
               (st->window_avg_shtc3_c > (st->window_avg_die_c + ORCH_LEAKAGE_MARGIN_C));
    }
    ```
  - **Result:** Single source of truth; prevents conflicting state flags between manual calls and algorithmic telemetry evaluations.

---

## 3. Mathematical & Register Operation Optimizations

### 3.1 Piecewise LUT vs. eFuse Linear Fixed-Point Arithmetic in ULP
- **Current State:**
  - `ulp/main.c` lines 36–58 store a 17-element `vbat_lut[17]` in RTC Slow RAM and execute runtime integer division and linear interpolation in `ulp_raw_to_mv()`.
  - Meanwhile, `sub_power.c` derives calibration slope `m` and offset `b` from ESP32 factory eFuses.
- **Optimization / Remedy:**
  - Eliminate the 17-point table (saves 68 bytes of RTC Slow RAM).
  - Implement direct fixed-point linear scaling on the RV32IMC core:
    ```c
    /* Factory eFuse linear calibration on RV32IMC */
    static inline uint32_t ulp_raw_to_mv(int32_t raw) {
        if (raw <= 0) return 0;
        /* V = ((raw * cal_scale) >> 11) + cal_offset */
        int32_t mv = (int32_t)(((int64_t)raw * (int64_t)cal_scale) >> 11) + cal_offset;
        return (mv < 0) ? 0 : (uint32_t)mv;
    }
    ```
  - **Result:** Hardware-calibrated accuracy matching `sub_power.c`, zero LUT memory overhead, and single-cycle multiply execution.

### 3.2 Battery Reading 16-Sample Trimmed Mean (`sub_power.c`)
- **Current State:**
  - `sub_power_read_battery()` calls `qsort()` with a generic function pointer `compare_int` over a 16-element stack array on every battery read, followed by integer averaging.
- **Optimization / Remedy:**
  - Replace the heavy standard C library `qsort()` overhead with an unrolled 16-element insertion sort or min/max tracking:
    ```c
    /* Fast in-place insertion sort for small fixed N=16 */
    for (int i = 1; i < 16; i++) {
        int key = samples[i];
        int j = i - 1;
        while (j >= 0 && samples[j] > key) {
            samples[j + 1] = samples[j];
            j--;
        }
        samples[j + 1] = key;
    }
    ```
  - **Result:** Eliminates function pointer call overhead and code bloat from `qsort()`, reducing stack and execution cycles.

### 3.3 Psychrometric Math Redundant Exponentials (`orch_math.c`)
- **Current State:**
  - `orch_math_calc_sat_vapor_pressure()` computes $e_s(T) = 6.112 \cdot \exp((17.625 \cdot T) / (243.04 + T))$.
  - `orch_math_calc_dew_point()` calls `logf()` and recomputes the polynomial ratio $(17.625 \cdot T) / (243.04 + T)$.
  - In `orch_flow_query_telemetry()`, `orch_math_calc_vapor_pressure()`, `orch_math_calc_dew_point()`, and `orch_math_reconstruct_ambient_rh()` are called back-to-back, computing saturation pressure multiple times.
- **Optimization / Remedy:**
  - Consolidate psychrometric calculations into a unified vector transform:
    ```c
    void orch_math_calc_psychrometrics(float temp_c, float rh_pct, float amb_floor_c,
                                       float *out_vp_hpa, float *out_dew_c, float *out_rh_amb)
    ```
  - Compute the saturation exponent once and reuse it across vapor pressure, dew point, and ambient RH reconstruction.
  - **Result:** Cuts floating-point `expf()` and `logf()` operations by 50%, improving execution speed and reducing math library footprint.

---

## 4. Functions Requiring Consolidation

### 4.1 Consolidating Redundant Synchronous & Asynchronous Audio Dispatchers (`sub_audio.c`)
- **Current State:**
  - `sub_audio.c` defines 6 separate public wrappers:
    - `sub_audio_play_tone()` & `sub_audio_play_tone_async()`
    - `sub_audio_play_chime()` & `sub_audio_play_chime_async()`
    - `sub_audio_play_pcm()` & `sub_audio_play_pcm_async()`
  - Every synchronous version creates a local binary semaphore, packages an `audio_cmd_t`, enqueues it, blocks on `xSemaphoreTake`, and deletes the semaphore.
  - In actual practice, synchronous blocking of audio in UI and presentation code causes frame drops on the e-Paper and delays FreeRTOS tasks.
- **Consolidation Alternative:**
  - Consolidate into 3 clean, unified entry points with a `bool sync` flag, or standardize on asynchronous execution with an optional completion callback:
    ```c
    esp_err_t sub_audio_tone(uint32_t freq_hz, uint32_t duration_ms, bool wait_done);
    esp_err_t sub_audio_chime(h1os_chime_type_t chime, bool wait_done);
    esp_err_t sub_audio_pcm(const int16_t *samples, size_t count, bool wait_done);
    ```
  - **Result:** Eliminates over 80 lines of duplicate wrapper boilerplate in `sub_audio.c` and simplifies the public API in `sub_audio.h`.

### 4.2 Consolidating Framebuffer Transfer & Memory Clearing (`sub_display.cpp`)
- **Current State:**
  - `sub_display_clear()` calls `memset(s_current_frame, color, 5000)`.
  - `sub_display_clear_to_white_full()` sets both buffers and triggers a full refresh.
  - `sub_display_sync_previous_frame()` copies buffers and writes to RAM `0x26`.
  - RAM counter setup (`0x4E`, `0x4F`) is duplicated in `set_ram_counters()`, `refresh_full()`, and `refresh_partial()`.
- **Consolidation Alternative:**
  - Consolidate RAM counter programming and DMA streaming into a single low-level primitive:
    ```c
    static void epd_commit_ram_dma(uint8_t ram_cmd, const uint8_t *frame_data);
    ```
  - Both `refresh_full()` and `refresh_partial()` call this single primitive for RAM `0x24` and `0x26`.
  - **Result:** Centralizes SPI DMA command sequences, preventing register offsets and reducing display driver binary size.

### 4.3 Consolidating Sleep Preparation Routines (`orch_flow.c` & `sub_power.c`)
- **Current State:**
  - Both `orch_flow.c` (lines 399–403) and `h1os_lifecycle.c` (lines 249–253) contain identical while-loops to drain the PCF85063A open-drain pulse:
    ```c
    uint32_t drain_wait_us = 0;
    while (gpio_get_level(HAL_PIN_RTC_INT) == 0 && drain_wait_us < 25000) {
        esp_rom_delay_us(500);
        drain_wait_us += 500;
    }
    ```
  - Meanwhile, `sub_power_enter_deep_sleep_mode()` configures pad holds and sleep parameters separately.
- **Consolidation Alternative:**
  - Move the pulse-drain check directly into `sub_power_enter_deep_sleep_mode()` as an atomic pre-sleep hardware barrier.
  - Remove the duplicated while-loops from `orch_flow.c` and `h1os_lifecycle.c`.
  - **Result:** Single, robust pre-sleep drain barrier that guarantees the chip never enters deep sleep with `GPIO 5` low.

---

## 5. Overly "Busy" Functions: Identification & Separation of Concerns

### 5.1 `orch_flow_query_telemetry()` in `orch_flow.c` (Lines 207–343, ~137 lines)
- **Why It Is "Busy":**
  - This single function does **six completely distinct jobs**:
    1. Inspects cold-boot status and returns default structures.
    2. Reads and parses glass and die temperatures.
    3. Scans the 32-sample ring buffer, calculating min, max, and sums for SHTC3 and MCU die.
    4. Computes Tri-Node mean, delta, and 0–100% confidence scores.
    5. Implements multi-case conditional promotion logic (`CASE_A_UNSETTLED`, `CASE_B_LEAKAGE`, `SETTLED`).
    6. Calls Magnus psychrometric equations and formats debug telemetry logs.
  - Reading or modifying this function is error-prone because math, data extraction, and logging are tightly coupled.
- **Proposed Separation of Concerns:**
  Split `orch_flow_query_telemetry()` into 3 focused, readable sub-functions:
  1. `orch_flow_scan_ring_metrics(const orch_persisted_state_t *st, ring_window_metrics_t *out_metrics)`
     - *Sole Responsibility:* Pure data scan across `ring[0..31]`. Computes floor, ceiling, and valid window averages.
  2. `orch_flow_evaluate_ambient_selection(const ring_window_metrics_t *m, float t_glass, float *out_amb, const char **out_mode)`
     - *Sole Responsibility:* Pure logic selection for $T_{\text{amb}}$ (Case A vs Case B vs Normal).
  3. `orch_flow_query_telemetry()` (Coordinator)
     - Calls the scanner, calls the evaluator, runs psychrometric math, and returns the output struct.
  - **Benefit:** High cohesion, easy unit testability, and clean readability.

---

### 5.2 `orch_flow_transition_to_sleep()` in `orch_flow.c` (Lines 345–411, ~66 lines)
- **Why It Is "Busy":**
  - Mixes UI pipeline draining, audio waiting, e-Paper panel BUSY polling, flash synchronization, display controller sleep mode, timing calculation, GPIO pulse draining, and deep sleep entry into one continuous sequence.
- **Proposed Separation of Concerns:**
  Split into two distinct architectural phases:
  1. `orch_flow_quiesce_peripherals()`:
     - Drains LVGL rendering.
     - Waits for audio idle and parks codec.
     - Waits for SSD1681 BUSY and commits flash if dirty.
     - Places SSD1681 into Deep Sleep Mode 1.
  2. `orch_flow_execute_sleep()`:
     - Calculates sub-interval timers.
     - Hands execution to `sub_power_enter_deep_sleep()`.
  - **Benefit:** Allows the quiescing sequence to be invoked independently (e.g. before shutdown or low-battery cutoff) without duplicating hardware teardown code.

---

### 5.3 `es8311_init_dac_registers()` in `sub_audio.c` (Lines 198–267, ~70 lines)
- **Why It Is "Busy":**
  - Sends 32 discrete register write commands over I2C with hardcoded magic hex numbers (`0x01 = 0x30`, `0x16 = 0x24`, `0x17 = 0xBF`, `0x44 = 0x58`), interleaved with delays and errata workarounds.
- **Proposed Separation of Concerns:**
  - Replace the imperative chain of `es8311_write_reg()` calls with a clean static register table structure:
    ```c
    typedef struct {
        uint8_t reg;
        uint8_t val;
    } es8311_reg_init_t;

    static const es8311_reg_init_t s_es8311_init_seq[] = {
        { 0x44, 0x08 }, { 0x44, 0x08 }, /* Noise immunity */
        { 0x0D, 0xFA },                 /* Analog baseline */
        { 0x01, 0x30 }, { 0x02, 0x00 }, /* Clock tree */
        ...
    };
    ```
  - Implement a simple table-driven loader:
    ```c
    for (size_t i = 0; i < sizeof(s_es8311_init_seq)/sizeof(s_es8311_init_seq[0]); i++) {
        es8311_write_reg(s_es8311_init_seq[i].reg, s_es8311_init_seq[i].val);
    }
    ```
  - **Benefit:** Reduces function size by >50 lines, makes register sequences visually readable, and simplifies tuning and maintenance.

---

### 5.4 `h1os_start()` in `h1os_lifecycle.c` (Lines 184–360, ~176 lines)
- **Why It Is "Busy":**
  - Acts as an enormous catch-all entrypoint: hardware init, ULP telemetry printing, flow arbitration, Flow A execution, ULP binary loading, LVGL init, bootloader jumps, shutdown, and UI launch.
- **Proposed Separation of Concerns:**
  - Decompose `h1os_start()` by extracting discrete lifecycle phase handlers:
    1. `h1os_early_system_bringup()`: IO early init, I2C init, NVS init, eFuse cal.
    2. `h1os_handle_non_ui_flows(orch_flow_type_t flow)`: Dispatches critical off, ROM bootloader jump, or wake stub.
    3. `h1os_launch_interactive_session()`: LVGL init, frame restore, presentation chimes/splashes, session task creation.
  - `h1os_start()` becomes a clean 25-line coordinator that reads top-to-bottom like an architectural roadmap.

---

## 6. Summary: Refactoring Impact Matrix

| Area / Component | Action | Lines of Code Impact | Architectural & Performance Gain |
| :--- | :--- | :--- | :--- |
| **Flow A Dual Path** (`orch_flow.c`, `h1os_lifecycle.c`) | Delete runtime Flow A duplicate; hook up `orch_wake_stub.c` | -120 lines pruned | Eliminates ~25 ms OS boot and cavity self-heating on 60s sample pulses. |
| **ULP State Machine** (`ulp/main.c`) | Replace `if-else` cascade with debounced hold/release state machine | ~60 lines refactored | Fixes missing Wake-on-Release rule; eliminates button contact bounce and race conditions. |
| **Thermal Lockout MUX** (`orch_flow.c`) | Remove manual setter; make query inline from telemetry metrics | -20 lines pruned | Single source of truth; eliminates dead scaffolding. |
| **ULP Battery Math** (`ulp/main.c`) | Replace 17-point LUT with calibrated eFuse linear math | -40 lines pruned, -68B RAM | Hardware-calibrated accuracy; saves scarce RTC Slow RAM. |
| **Battery Trimmed Mean** (`sub_power.c`) | Replace `qsort()` with fast in-place insertion sort | ~25 lines refactored | Eliminates CRT function pointer call overhead and saves code space. |
| **Psychrometric Equations** (`orch_math.c`) | Consolidate into unified vector pipeline | -25 lines refactored | 50% fewer `expf()` and `logf()` calls on Flow B telemetry queries. |
| **Audio API Consolidation** (`sub_audio.c`) | Consolidate sync/async duplicate entry points | -80 lines pruned | Cleaner API surface; eliminates redundant semaphore allocations. |
| **Display RAM Primitives** (`sub_display.cpp`) | Consolidate RAM counter and DMA write sequences | -35 lines pruned | Centralizes low-level SPI DMA transfers. |
| **Pre-Sleep Pulse Barrier** (`sub_power.c`) | Centralize PCF85063A pulse drain into `sub_power` | -15 lines duplicated | Guarantees atomic pre-sleep hardware protection. |
| **Telemetry Query Decomposition** (`orch_flow.c`) | Separate ring scanner, ambient selector, and math coordinator | ~140 lines structured | Modular, highly readable, independently testable functions. |
| **ES8311 Register Init** (`sub_audio.c`) | Replace 32 imperative function calls with static register table | -50 lines pruned | Table-driven, maintainable, easily tunable codec register configuration. |
| **Lifecycle Entry Decomposition** (`h1os_lifecycle.c`) | Extract bringup, non-UI flow handling, and session launch | ~180 lines structured | Clean 25-line top-level orchestration flow. |
