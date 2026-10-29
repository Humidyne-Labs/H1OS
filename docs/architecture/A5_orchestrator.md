# Layer 3: System Pipeline & Orchestrator Specification

## 1. Overview
Layer 3 is the central orchestration brain of H1OS. It maintains persistent state across deep sleep cycles, coordinates all Layer 2 subsystems, executes psychrometric algorithms, and arbitrates between **Flow A (Headless Sensor Sample Burst in RTC Wake Stub)** and **Flow B (Interactive User Session or Unattended UI Refresh)**.

---

## 2. File Manifest

| File | Component | Key Responsibilities |
| :--- | :--- | :--- |
| `orch_state.h/.c` | Persistent RTC Storage | Retains counters, system flags, ULP dispatch commands, 32-slot Tri-Node sensor ring buffer, and cumulative battery autonomy runtimes in RTC Slow Memory (mirrored to NVS). |
| `orch_math.c/.h` | Psychrometric Math Engine | August-Roche-Magnus equations, saturation & actual vapor pressure, dew point, absolute humidity, continuous EWMA, and integer plateau stability gate. |
| `orch_flow.c/.h` | Execution Flow Arbiter | Single Unified Binary Arbiter: routes cold boot, Flow B wakes, bootloader jumps, and critical shutdowns; evaluates steady-state SHTC3 telemetry and Tri-Node verification; coordinates sleep transition sequence. |
| `orch_display_sync.c/.h` | Frame Sync Engine | Coordinates display framebuffer persistence to `epd_frame` flash partition during sleep/shutdown and tracks the 6-cycle partial refresh anti-ghosting quota. |
| `orch_wake_stub.c/.h` | Fast RTC Wake Stub | Executes headless Flow A sensor sample burst (`bsp_wake_stub`) directly from RTC Fast Memory on Core 0 without booting FreeRTOS. |

---

## 3. Component Details & Data Structures

### 3.1 `orch_state.h/.c` (Persistent State Architecture)
Allocated in RTC Slow SRAM (`RTC_NOINIT_ATTR static volatile orch_persisted_state_t s_persisted_state`) and retained across all deep sleep cycles and wake stub executions:

```c
#pragma once
#include <stdbool.h>
#include <stdint.h>

#define ORCH_RTC_MAGIC              0x534C4154 // "SLAT"
#define ORCH_RING_CAPACITY          32

typedef enum {
    ULP_DISPATCH_NONE = 0,
    ULP_DISPATCH_SENSOR_SAMPLE,     // Headless Flow A sensor sample burst dispatch
    ULP_DISPATCH_MAIN_WAKE,         // Interactive Flow B UI presentation wake dispatch
    ULP_DISPATCH_CRITICAL_SHUTDOWN, // Low-battery brownout threshold cut dispatch (< 3.25V)
    ULP_DISPATCH_BOOTLOADER_JUMP,   // BOOT0 held down >= 2.5s during sleep: jump to download mode
    ULP_DISPATCH_POWER_OFF          // BAT_KEY held down >= 2.5s during sleep: power off
} orch_ulp_dispatch_t;

#define SAMPLE_FLAG_VALID_COLD      0x01
#define SAMPLE_FLAG_THERMAL_SETTLED 0x02
#define SAMPLE_DELTA_GATE_CENTI_C   20   // Maximum allowable drift for steady state (0.20°C)

typedef struct {
    int16_t  shtc3_temp_centi_c;  // SHTC3 temperature in centi-degrees Celsius (1°C = 100)
    uint16_t shtc3_rh_centi_pct;  // SHTC3 relative humidity in centi-percent (1% = 100)
    int16_t  mcu_tsens_centi_c;   // ESP32-S3 internal TSENS die temperature in centi-°C
    int16_t  epd_glass_centi_c;   // SSD1681 on-glass thermal sensor in centi-°C
    uint32_t timestamp_sec;       // Sample cumulative sleep timestamp in seconds
    uint8_t  quality_flags;       // Sample qualification bitmask (SAMPLE_FLAG_*)
    uint8_t  _pad[3];             // Alignment padding to 32-bit boundary
} orch_tri_node_sample_t;

typedef struct {
    uint32_t magic;
    uint32_t boot_count;
    uint32_t wake_count;
    uint32_t flow_b_counter;
    uint32_t button_wake_count;
    uint8_t  flags;
    uint8_t  ulp_dispatch_reason;
    uint16_t last_vbat_mv;
    uint16_t boot_vbat_mv;

    uint32_t sample_interval_sec;
    uint32_t flow_b_period_sec;
    uint32_t last_ewma_sample_seq;

    uint16_t epd_partial_refresh_count;
    uint16_t valid_trend;

    int16_t  window_low_temp_centi_c;
    int16_t  window_high_temp_centi_c;
    int16_t  last_glass_temp_centi_c;

    float    window_avg_shtc3_c;
    float    window_avg_die_c;
    float    temp_historical_c;
    float    rh_historical_pct;

    float    ambient_temp_c;
    float    ambient_rh_pct;
    float    dew_point_c;
    float    vapor_pressure_hpa;

    float    trinode_temp_c;
    float    trinode_delta_c;
    uint8_t  trinode_confidence_pct;
    bool     ewma_inited;
    int16_t  tsens_cal_centi_c;
    int16_t  tsens_offset_centi_c;

    orch_tri_node_sample_t ring[ORCH_RING_CAPACITY];
    uint8_t  ring_head;
    uint32_t total_samples;

    uint32_t total_sleep_sec;
    uint32_t total_app_run_ms;
    uint32_t last_nvs_commit_sec;
    uint16_t initial_soc_x10;
    uint8_t  _pad_soc[2];
    uint32_t sensor_fail_count;
    uint8_t  last_sensor_error;
    uint8_t  _pad_sensor[3];
    uint16_t rh_alert_low_centi_pct;
    uint16_t rh_alert_high_centi_pct;
} orch_persisted_state_t;

volatile orch_persisted_state_t *orch_state_get(void);
void orch_state_reset(void);
void orch_state_push_sample(const orch_tri_node_sample_t *sample);
bool orch_state_get_latest_sample(orch_tri_node_sample_t *out_sample);
bool orch_state_get_latest_valid_sample(orch_tri_node_sample_t *out_sample);
void orch_state_save_runtimes_to_nvs(void);
void orch_state_load_runtimes_from_nvs(void);
void orch_state_reset_discharge_lap(uint16_t current_soc_x10);
```

---

### 3.2 `orch_math.c/.h` (Class-E Psychrometric Math Engine)
Implements thermodynamic psychrometrics directly from factory-calibrated SHTC3 steady-state readings with zero synthetic offsets:
- **Saturation & Actual Vapor Pressure ($e_s, e$):**

$$
e_s(T) = 6.112 \cdot \exp\left(\frac{17.625 \cdot T}{243.04 + T}\right) \quad [\text{hPa}], \qquad e = \frac{RH}{100.0} \cdot e_s(T) \quad [\text{hPa}]
$$

- **Dew Point ($T_{\text{dew}}$) & Absolute Humidity ($d_v$):**

$$
\gamma = \ln\left(\frac{RH}{100.0}\right) + \frac{17.625 \cdot T}{243.04 + T}, \qquad T_{\text{dew}} = \frac{243.04 \cdot \gamma}{17.625 - \gamma} \quad [^\circ\text{C}], \qquad d_v = 216.7 \cdot \frac{e}{273.15 + T} \quad [\text{g/m}^3]
$$

```c
float orch_math_calc_sat_vapor_pressure(float temp_c);
float orch_math_calc_vapor_pressure(float temp_c, float rh_pct);
float orch_math_calc_dew_point(float temp_c, float rh_pct);
void  orch_math_calc_psychrometrics(float temp_c, float rh_pct, float *out_vp_hpa, float *out_dew_c);
float orch_math_calc_absolute_humidity(float vapor_pressure_hpa, float amb_temp_c);
float orch_math_update_ewma(float current_sample, float previous_ewma, float alpha);
bool  orch_math_is_plateau_settled(int16_t initial_temp_centi_c, int16_t current_temp_centi_c, int16_t gate_threshold_centi_c);
```

---

### 3.3 `orch_flow.c/.h` (Lifecycle Flow Arbiter & Sleep Sequencer)

#### Pure Event Mode Slicing & Zero-Hour Conflict Elimination
- **ULP Sleep Gating:** The ULP Coprocessor is enabled **only** while the system is actively sleeping (`RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA = 1`). In Flow B, the dual-core Xtensa and LVGL have full ownership of all hardware; ULP GPIO wakeup is immediately disarmed upon wake.
- **Hardware Countdown Timer Slicing (Midnight-Agnostic):**
  H1OS uses the PCF85063A **hardware countdown timer** (`Timer_val` Reg `0x10`, `Timer_mode` Reg `0x11`) in Pure Event Mode rather than competing internal/external timers.
  - **Timing Law & Parameter Bounds:**
    - **Flow A ($T_A$):** `H1OS_FLOW_A_MIN_SEC` ($60\text{s}$) to `H1OS_FLOW_A_MAX_SEC` ($14,400\text{s}$ / $4\text{ hours}$). Durations $> 255\text{s}$ must be exact multiples of 60 seconds to align with the hardware prescaler (`TIMER_CLK_1_60_HZ`).
    - **Flow B ($T_B$):** `H1OS_FLOW_B_MIN_SEC` ($300\text{s}$ / $5\text{ min}$) to `H1OS_FLOW_B_MAX_SEC` ($86,400\text{s}$ / $24\text{ hours}$). Must be strictly greater than $T_A$.
    - **Remainder Floor:** `H1OS_FLOW_REMAINDER_MIN_SEC` ($60\text{s}$). If $\text{remainder} = T_B \bmod T_A > 0$, it must be $\ge 60\text{s}$ to justify the re-arm cycle.
  - **Slicing Equation & Silicon Auto-Reload:**
    - $\text{full\_slices} = \lfloor T_B / T_A \rfloor$, $\text{remainder} = T_B \bmod T_A$, $\text{overflow} = \text{full\_slices} + (\text{remainder} > 0 \mathbin{?} 1 : 0)$.
    - The PCF85063A countdown timer is armed for $T_A$ in periodic pulse mode (`TIMER_PULSE_MODE_BIT`).
    - When $\text{remainder} == 0$, the timer **auto-reloads continuously in silicon** without software re-arming, accumulating $0.00\text{ ms}$ of compounding execution drift.
    - If $\text{remainder} > 0$, on slice $\text{overflow} - 1$, `bsp_wake_stub()` re-arms the hardware timer for $\text{remainder}$ seconds via `rtc_rearm_countdown_stub()`.
  - **Single Variable Authority:** All time logic across the orchestrator, lifecycle, and power subsystems derives strictly from `st->sample_interval_sec` ($T_A$) and `st->flow_b_period_sec` ($T_B$) in RTC Slow Memory. No duplicate file-static variables or fallback constants are permitted.

#### Flow B Wake Profiles & Dual-Core Lifecycle Governance (`v2.4.5-dev`)
1. **User Interactive Wake (`H1OS_WAKE_STATE_INTERACTIVE_SESSION` — `ULP_DISPATCH_MAIN_WAKE` from Button Tap):**
   - Woken by user tap on `BOOT` or `POWER` (`ulp_last_wake_btn != 0`, incrementing `st->button_wake_count`).
   - Initializes audio subsystem (`sub_audio_init`), activates the configurable inactivity session (`session.inactivity_timeout_sec`, default 30s) via the one-shot `esp_timer` (`s_session_timer`), invokes `on_wake()`, starts Core 1 LVGL (`h1os_lvgl_start(5, 1)`), and dispatches `on_sync()` on Core 0 in parallel.
2. **External RTC Timer Wake (`H1OS_WAKE_STATE_RTC_FLOW_B` — `ULP_DISPATCH_MAIN_WAKE` from PCF85063A Overflow):**
   - Woken to execute the periodic environmental screen update and telemetry sync (`is_rtc_wake == true`, incrementing `st->flow_b_counter`).
   - Skips audio initialization (preserving `<1 µA` codec standby), invokes `on_wake()`, starts Core 1 LVGL (`h1os_lvgl_start(5, 1)`), and executes `on_sync()` on Core 0 in parallel with Core 1's e-Paper refresh. Once the static `EventGroup` sleep barrier (`BARRIER_SYNC_DONE | BARRIER_DISPLAY_DONE`) completes, the system **immediately returns to deep sleep**.
3. **Cold Boot (`H1OS_WAKE_STATE_BOOT` — `ORCH_FLOW_BOOT`):**
   - Validates flow periods (`h1os_validate_flow_periods()`), initializes hardware (`orch_flow_init()`), applies configured flow periods after `orch_state_reset()` (`h1os_apply_flow_periods()`), loads persisted battery autonomy runtimes from NVS, starts the ULP binary in Pure Event Mode, plays boot chime/splash, invokes `on_boot()`, starts Core 1 LVGL + parallel Core 0 `on_sync()`, and runs the interactive session.

```c
typedef enum {
    ORCH_FLOW_BOOT = 0,
    ORCH_FLOW_A_SAMPLE,
    ORCH_FLOW_B_MAIN_WAKE,
    ORCH_FLOW_BOOTLOADER_JUMP,
    ORCH_FLOW_CRITICAL_OFF
} orch_flow_type_t;

orch_flow_type_t orch_flow_determine_wakeup(void);
bool             orch_flow_is_thermal_lockout(void);
esp_err_t        orch_flow_query_telemetry(float *out_temp_c, float *out_rh_pct, float *out_dew_c);
esp_err_t        orch_flow_transition_to_sleep(uint32_t sleep_sec);
```

---

## 4. Telemetry Standards & Diagnostic Modularity

### 4.1 Telemetry NA Convention (0.0°C / 0% Standard)
- Synthetic seed values (e.g. `2500` centi-°C / `25.0°C`) on cold boot have been completely eradicated.
- `orch_state_reset()` initializes all temperature and humidity metrics (`window_low_temp_centi_c`, `window_high_temp_centi_c`, `last_glass_temp_centi_c`) to `0`.
- When `total_samples == 0` on cold boot, `orch_flow_query_telemetry()` returns `0.0f` for temperature, RH, and dew point until the first Flow A sample is captured in deep sleep.

### 4.2 Modular Diagnostic Ring Hexdump
Ring buffer diagnostics in `orch_flow_query_telemetry()` are encapsulated in `orch_flow_dump_ring_debug(const volatile orch_persisted_state_t *st)` using static `.bss` arrays (`shtc3T_ring`, `shtc3RH_ring`, `mcuT_ring`, `epdT_ring`) to keep stack usage minimal and only execute when `st->total_samples != st->last_ewma_sample_seq`.
