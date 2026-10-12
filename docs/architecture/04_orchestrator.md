# Layer 3: System Pipeline & Orchestrator Specification

## 1. Overview
Layer 3 is the central orchestration brain of H1OS. It maintains persistent state across deep sleep cycles, coordinates all Layer 2 subsystems, executes psychrometric algorithms, and arbitrates between **Flow A (Headless Sensor Sample Burst)** and **Flow B (Interactive User Session with Configurable Inactivity Sleep)**.

---

## 2. File Manifest

| File | Component | Key Responsibilities |
| :--- | :--- | :--- |
| `orch_state.h/.c` | Persistent RTC Storage | Retains counters, system flags, ULP dispatch commands, and 32-slot sensor ring buffer (<512 bytes) in RTC Slow Memory. |
| `orch_math.c/.h` | Psychrometric Math Engine | Magnus equations, vapor pressure invariant, dew point reconstruction, continuous EWMA, integer slope gates. |
| `orch_flow.c/.h` | Execution Flow Arbiter | Single Unified Binary Arbiter: routes Flow A sample vs Flow B interactive session; coordinates 8-step sleep transition sequence. |
| `orch_display_sync.c/.h` | Frame Sync Engine | Coordinates display framebuffer persistence to `epd_frame` flash partition during sleep transition events. |
| `orch_wake_stub.c/.h` | Fast RTC Wake Stub | Executes Flow A sensor sample burst directly from RTC Fast Memory on Core 0. |

---

## 3. Component Details & Data Structures

### 3.1 `orch_state.h/.c` (Persistent State Architecture)
ESP32-S3 has 8KB of RTC Slow SRAM. Layer 3 uses **less than 512 bytes**, leaving the rest free for the ULP coprocessor.

```c
#pragma once
#include <stdint.h>
#include <stdbool.h>

#define ORCH_RTC_MAGIC       0x534C4154 // "SLAT" (Clean Slate)
#define ORCH_RING_CAPACITY    32

typedef enum {
    ULP_DISPATCH_NONE = 0,
    ULP_DISPATCH_SENSOR_SAMPLE,     // Flow A (Headless sensor sample burst)
    ULP_DISPATCH_MAIN_WAKE,         // Flow B (Interactive LVGL session)
    ULP_DISPATCH_BOOTLOADER_JUMP,   // Primed by BOOT hold > 2.5s
    ULP_DISPATCH_POWER_OFF,         // Primed by POWER hold > 2.5s
    ULP_DISPATCH_CRITICAL_SHUTDOWN  // Battery threshold (< 3.25V)
} ulp_dispatch_reason_t;

typedef struct {
    int16_t  shtc3_temp_centi_c;    // SHTC3 package temp (centi-°C)
    uint16_t shtc3_rh_centi_pct;    // SHTC3 package RH (centi-%)
    int16_t  mcu_tsens_centi_c;     // MCU internal die TSENS
    int16_t  epd_glass_centi_c;     // SSD1681 surface glass thermistor
    uint32_t timestamp_epoch;
    uint8_t  quality_flags;         // Bit 0: Cold reading, Bit 1: Settled
} orch_tri_node_sample_t;

typedef struct {
    uint32_t                magic;
    uint32_t                boot_count;
    uint32_t                wake_count;
    uint8_t                 flags;
    
    // ULP Reactive Monitor Dispatch State
    ulp_dispatch_reason_t   ulp_dispatch_reason;
    uint16_t                last_vbat_mv;
    uint32_t                sample_interval_sec;     // Nominal 60s
    uint32_t                wake_timestamp_epoch;    // Time of last active wake
    
    // Dynamic Sliding Ambient Floor & EWMA State
    int16_t                 amb_floor_temp_centi_c;
    float                   reconstructed_amb_temp_c;
    float                   reconstructed_amb_rh_pct;
    float                   reconstructed_dew_point_c;
    float                   vapor_pressure_hpa;
    bool                    ewma_inited;
    
    // 32-Slot Ring Buffer
    orch_tri_node_sample_t  ring[ORCH_RING_CAPACITY];
    uint8_t                 ring_head;
    uint32_t                total_samples;
} orch_persisted_state_t;

#define ORCH_FLAG_NONE             0
#define ORCH_FLAG_EPD_FRAME_VALID  (1 << 0)
#define ORCH_FLAG_CRITICAL_BATTERY (1 << 1)
#define ORCH_FLAG_THERMAL_LOCKOUT  (1 << 2)

orch_persisted_state_t* orch_state_get(void);
void                    orch_state_reset(void);
```

---

### 3.2 `orch_math.c/.h` (Class-E Psychrometric Invariant Engine)
Implements thermodynamic reconstruction with zero artificial curve fitting:
- **Vapor Pressure Invariant ($e$):** Ambient vapor pressure in the cavity is invariant across temperature shifts.

$$
e_s(T) = 6.112 \cdot \exp\left(\frac{17.625 \cdot T}{243.04 + T}\right) \quad [\text{hPa}]
$$

$$
e = \frac{RH_{\text{meas}}}{100} \cdot e_s(T_{\text{meas}}) \quad [\text{hPa}]
$$

- **Dew Point Invariant ($T_{\text{dew}}$):**

$$
T_{\text{dew}} = \frac{243.04 \cdot \ln(e / 6.112)}{17.625 - \ln(e / 6.112)} \quad [^\circ\text{C}]
$$

- **Ambient RH Reconstruction:**

$$
RH_{\text{ambient}} = 100 \cdot \frac{e}{e_s(T_{\text{floor}})}
$$

```c
float     orch_math_calc_vapor_pressure(float temp_c, float rh_pct);
float     orch_math_calc_dew_point(float temp_c, float rh_pct);
float     orch_math_calc_absolute_humidity(float vp_hpa, float temp_c);
float     orch_math_reconstruct_ambient_rh(float vp_hpa, float amb_temp_c);
float     orch_math_update_ewma(float sample, float current_ewma, float alpha);
```

---

### 3.3 `orch_flow.c/.h` (Lifecycle Flow Arbiter & Sleep Sequencer)

#### Flow Routing & Simplified ULP Sleep-Gating
- **ULP Sleep Gating:** The ULP Coprocessor is enabled **only** while the system is actively sleeping. In Flow B, the dual-core Xtensa and LVGL have full ownership of all hardware; the ULP is completely idle.
- **Hardware Countdown Timer (Midnight-Agnostic):**
  We strictly use the PCF85063A **hardware countdown timer** (`Timer_val` Reg 0x10, `Timer_mode` Reg 0x11) rather than the calendar alarm registers (0x0B..0x0F). Calendar alarms do not account for midnight rollover—a 5-minute sleep interval crossing the 23:59:59 $\to$ 00:00:00 day boundary would produce undefined behavior and missed wakes. The hardware countdown timer decrements ticks (1 Hz or 1/60 Hz) directly down to zero and asserts `GPIO 5` `RTC_INT` completely agnostic to calendar boundaries or rollover.
- **Deterministic Zero-Hour Collision Math (Next-Sleep Lookahead):**
  Before going to sleep, the Orchestrator evaluates whether the *next* accumulated sleep duration would overshoot or collide with the external RTC timer timeout:

$$
\text{if } \Big(T_{\text{rtc}} < (N_{\text{ulp}} \times T_{\text{sleep}}) + T_{\text{sleep}}\Big) \implies \textbf{DO NOT ARM INTERNAL RTC / ULP TIMER}
$$

  - **Rule:** If the projected sleep accumulator $\big((N_{\text{ulp}} + 1) \times T_{\text{sleep}}\big)$ exceeds $T_{\text{rtc}}$, scheduling another Flow A wake would collide with or straddle the external RTC timer interrupt. Therefore, the internal periodic timer is **not armed**.
  - **Result:** The ULP sleeps purely on the external hardware interrupt line (`GPIO 5` `RTC_INT`). When the external PCF85063A countdown timer expires, the ULP catches the interrupt cleanly and wakes the system into Flow B.
  - If $(N_{\text{ulp}} + 1) \times T_{\text{sleep}} \le T_{\text{rtc}}$, the internal periodic timer is safely armed for another headless Flow A sensor pulse.

#### Flow B Wake Profiles & Lifecycle Governance
The Orchestrator determines sleep timing based on the origin of the wake event:
1. **User Interactive Wake (`ULP_DISPATCH_MAIN_WAKE` from Button Tap):**
   - The device was sleeping and the user tapped `BOOT` or `POWER`.
   - Starts the **configurable inactivity session** (`session.inactivity_timeout_sec`, default 30s) and renders the inverted awake indicator badge. LVGL keypad indev processes button events.
   - Any button click resets the inactivity timer back to `inactivity_timeout_sec`.
   - Dynamic Frequency Scaling (DFS) droops CPU from 240 MHz turbo to 80 MHz baseline between clicks.
   - When the configured inactivity duration elapses without interaction, triggers the coordinated 8-step sleep sequence below.
2. **External RTC Timer Wake (`ULP_DISPATCH_MAIN_WAKE` from PCF85063A Countdown Timer):**
   - Woken purely to execute the periodic environmental screen update.
   - Renders telemetry to the E-Paper panel (with standard non-inverted sleep badge), flushes the framebuffer, waits for panel BUSY line release, and **goes right back to sleep immediately** without idling or waiting for user interaction.
3. **Boot (`ORCH_FLOW_BOOT`):**
   - Fresh power application or battery insertion.
   - System runs hardware bring-up, renders initial UI, and **waits the configured inactivity timeout** (`session.inactivity_timeout_sec`, default 30s) for potential user interaction or debug before entering initial deep sleep.

#### Deterministic 8-Step Sleep Transition Sequence
When Flow B enters sleep (either immediately after an RTC screen update, upon expiration of the user/boot inactivity timer, or on an explicit `h1os_sleep()` call), `orch_flow` executes the deterministic 8-step sleep transition sequence:
1. **LVGL Frame Pipeline Drain:** Wait for LVGL render and flush pipeline to drain completely (`h1os_lvgl_has_pending_tasks()`).
2. **Audio Subsystem Teardown:** Wait for any background audio playback and hardware soft-ramp teardown to complete (`sub_audio_wait_idle()`).
3. **Hardware Panel Busy Wait:** Wait for SSD1681 `EPD_BUSY` (`GPIO 8`) to release LOW (`sub_display_wait_busy()`).
4. **Post-Busy Particle Settling Guard:** 250 ms delay for micro-capsule voltages to discharge before cutting clocks.
5. **Flash Commit:** Commit 5000-byte framebuffer to `epd_frame` SPI flash partition if modified (`orch_display_sync_save_if_dirty()`).
6. **Controller Deep Sleep:** Put SSD1681 into Deep Sleep Mode 1 (`sub_display_enter_deep_sleep()`).
7. **External RTC Arming:** Arm external PCF85063A countdown timer (`sub_rtc_arm_countdown()`).
8. **Hardware Sleep Entry:** Evaluate Zero-Hour conflict gate, arm wake sources, and enter deep sleep (`sub_power_enter_deep_sleep()`).

```c
typedef enum {
    ORCH_FLOW_BOOT = 0,
    ORCH_FLOW_A_SAMPLE,
    ORCH_FLOW_B_MAIN_WAKE,
    ORCH_FLOW_BOOTLOADER_JUMP,
    ORCH_FLOW_CRITICAL_OFF
} orch_flow_type_t;

orch_flow_type_t orch_flow_determine_wakeup(void);
void             orch_flow_execute_sensor_sample(void);
bool             orch_flow_is_thermal_lockout(void);
void             orch_flow_set_thermal_lockout(bool enable, uint32_t duration_sec);
esp_err_t        orch_flow_query_telemetry(float *out_t, float *out_rh, float *out_dew);
esp_err_t        orch_flow_transition_to_sleep(uint32_t sleep_seconds);
```
