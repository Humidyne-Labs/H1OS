# Layer 3: System Pipeline & Orchestrator Specification

## 1. Overview
Layer 3 is the core "brain" of the Clean-Slate BSP. It maintains the persistent state across deep sleep cycles, coordinates all Layer 2 subsystems, executes psychrometric algorithms, and orchestrates the two execution modes: **Flow A (Headless Sub-Execution, <10ms)** and **Flow B (Main Application Wake)**.

---

## 2. File Manifest

| File | Component | Key Responsibilities |
| :--- | :--- | :--- |
| `orch_state.h/.c` | Persistent RTC Storage | Retains counters, system flags, ULP dispatch commands, and 32-slot sensor ring buffer (<512 bytes) in RTC Slow Memory. |
| `orch_ulp.c/.h` | ULP Sentinel Firmware | RISC-V coprocessor firmware: battery tripwire, button debounce, die TSENS slope, and deep-sleep real-time arbiter. |
| `orch_math.c/.h` | Psychrometric Math Engine | Magnus equations, vapor pressure, absolute humidity, running EWMA, integer slope stability gates. |
| `orch_flow.c/.h` | Lifecycle Flow Orchestrator | Execution branch arbiter: handles ULP wake interrupts (Flow A sub-sprint vs Flow B main UI); executes zero-hour conflict resolution. |
| `orch_display_sync.c/.h` | Frame Sync Engine | Coordinates display framebuffer persistence to flash partition during stand-down events. |

---

## 3. Component Details & Data Structures

### 3.1 `orch_state.h/.c` (Persistent State Architecture)
ESP32-S3 has 8KB of RTC Slow SRAM. Layer 3 uses **less than 512 bytes**, leaving the rest completely free for ULP-RISCV firmware and execution stack.

```c
#pragma once
#include <stdint.h>
#include <stdbool.h>

#define ORCH_RTC_MAGIC      0x534C4154 // "SLAT" (Clean Slate)
#define ORCH_RING_CAPACITY   32

typedef enum {
    ULP_DISPATCH_NONE = 0,
    ULP_DISPATCH_SENSOR_SPRINT,   // Prompt Core 0 into Flow A (<5ms)
    ULP_DISPATCH_MAIN_WAKE,       // Prompt Core 0/1 into Flow B (Display/App)
    ULP_DISPATCH_CRITICAL_SHUTDOWN// Low battery tripwire triggered (<3.25V)
} ulp_dispatch_reason_t;

typedef struct {
    int16_t  shtc3_temp_centi_c;    // SHTC3 package temp (centi-°C, e.g. 2350 = 23.50 °C)
    uint16_t shtc3_rh_centi_pct;    // SHTC3 package RH (centi-%, e.g. 5520 = 55.20 %)
    int16_t  mcu_tsens_centi_c;     // MCU internal die TSENS
    int16_t  epd_glass_centi_c;     // SSD1681 surface glass thermistor (SPI Cmd 0x1B)
    uint32_t timestamp_epoch;
    uint8_t  quality_flags;         // Bit 0: Cold reading, Bit 1: Thermally settled
} orch_tri_node_sample_t;

typedef struct {
    uint32_t                magic;
    uint32_t                boot_count;
    uint32_t                wake_count;
    uint8_t                 flags;
    
    // ULP Real-Time Sentinel Dispatch State
    ulp_dispatch_reason_t   ulp_dispatch_reason;
    uint16_t                last_vbat_mv;            // Sampled autonomously by ULP ADC
    int16_t                 ulp_die_temp_centi_c;    // Die temp tracked by ULP
    uint32_t                sample_interval_sec;     // Nominal 60s
    uint32_t                wake_timestamp_epoch;    // Time of last active wake
    
    // Dynamic Sliding Ambient Floor (Minima over last M samples)
    int16_t                 amb_floor_temp_centi_c;
    
    // Continuous IIR / EWMA running state (Class-E Reconstructed Ambient)
    float                   reconstructed_amb_temp_c;
    float                   reconstructed_amb_rh_pct;
    float                   reconstructed_dew_point_c;
    float                   vapor_pressure_hpa;
    bool                    ewma_inited;
    
    // Tri-Node Telemetry Ring Buffer (32 slots * 16 bytes = 512 bytes)
    orch_tri_node_sample_t  ring[ORCH_RING_CAPACITY];
    uint8_t                 ring_head;
    uint32_t                total_samples;
} orch_persisted_state_t;

// Flags Bitmask
#define ORCH_FLAG_NONE             0
#define ORCH_FLAG_EPD_FRAME_VALID  (1 << 0)
#define ORCH_FLAG_CRITICAL_BATTERY (1 << 1)
#define ORCH_FLAG_THERMAL_LOCKOUT  (1 << 2)

orch_persisted_state_t* orch_state_get(void);
void                    orch_state_reset(void);
```

---

### 3.2 `orch_math.c/.h` (Class-E Psychrometric & Signal Engine)
A pure physical reconstruction library with zero synthetic curve dividers:
- **Integer Plateau Gate (ULP / Flow A)**:
  Evaluates raw temperature drop from hot sleep entry baseline ($z$) and slope flattening:
  $$\Delta T_{\text{drop}} = T_{\text{initial}} - T_{\text{current}} \ge \delta_{\text{gate}} \quad (0.05^\circ\text{C} - 0.20^\circ\text{C}) \implies \text{Thermally Settled}$$
- **Vapor Pressure Invariant ($e$)**:
  The mass of moisture in ambient air entering the sensor cavity is invariant regardless of package heating. Saturation vapor pressure at sensor die temperature:
  $$e_s(T_{\text{die}}) = 6.112 \cdot \exp\left(\frac{17.625 \cdot T_{\text{die}}}{243.04 + T_{\text{die}}}\right) \quad [\text{hPa}]$$
  Invariant ambient vapor pressure:
  $$e = \frac{RH_{\text{meas}}}{100} \cdot e_s(T_{\text{die}}) \quad [\text{hPa}]$$
- **Dew Point Invariant ($T_{\text{dew}}$)**:
  $$\gamma(T_{\text{die}}, RH_{\text{meas}}) = \ln\left(\frac{RH_{\text{meas}}}{100}\right) + \frac{17.625 \cdot T_{\text{die}}}{243.04 + T_{\text{die}}}$$
  $$T_{\text{dew}} = \frac{243.04 \cdot \gamma}{17.625 - \gamma} \quad [^\circ\text{C}]$$
- **Ambient Relative Humidity Reconstruction ($RH_{\text{amb}}$)**:
  Using the dynamic ambient baseline floor $T_{\text{amb\_floor}} = \min(T_{\text{die}}[n-M \dots n])$:
  $$RH_{\text{amb}} = \frac{e}{e_s(T_{\text{amb\_floor}})} \times 100\% = RH_{\text{meas}} \cdot \exp\left(\frac{17.625 \cdot T_{\text{die}}}{243.04 + T_{\text{die}}} - \frac{17.625 \cdot T_{\text{amb\_floor}}}{243.04 + T_{\text{amb\_floor}}}\right)$$
- **Absolute Humidity (Vapor Density)**:
  $$d_v = 216.7 \cdot \frac{e}{273.15 + T_{\text{amb\_floor}}} \quad [\text{g/m}^3]$$
- **Continuous Recursive EWMA**:
  $$S_t = \alpha \cdot X_t + (1 - \alpha) \cdot S_{t-1} \quad (\alpha = 0.25\dots 0.35)$$

---

### 3.3 `orch_flow.c/.h` (Flow Arbiter & Thermal Lockout MUX)

#### Thermal Lockout MUX Gatekeeper
Protects high-precision sensors from being read while the PCB is thermally perturbed by active CPU (240MHz), e-Paper HV driving, or Wi-Fi bursts:
- **Lockout Condition**: Active if $(t_{\text{now}} - t_{\text{wake}}) < \tau_{\text{lockout}}$ where $\tau_{\text{lockout}} \ge 0.5 \times T_{\text{sleep\_interval}}$ (minimum 30–60s).
- **Behavior**:
  - When locked out: Any telemetry query transparently returns the pristine cold reading from the RTC Slow Memory ring buffer.
  - When in thermal equilibrium: Allows direct hardware acquisition.

#### Flow A: Zero-Heat Acquisition Pipeline (<10ms Budget)
Executes periodically in deep sleep (every 60s/120s):
- **Why Xtensa Sprint is the Engine (Hardware Pinout Reality)**:
  The hardware board routes the SHTC3 sensor I2C bus to **GPIO 15 (SDA) and GPIO 16 (SCL)**, powered by switched rail `GPIO 6`. Because these pins cannot be driven by the RTC coprocessor in deep sleep without keeping the full digital domain awake, **Flow A Xtensa Sub-Execution Sprint** is the architecture of record.
- **Execution Lifecycle**:
  1. Clock Setup: 80MHz crystal clock (no 240MHz PLL boost).
  2. Rail & I2C Bring-Up: Asserts `hal_io_set_sensor_rail(true)` and initializes `hal_i2c`.
  3. Sensor Read: SHTC3 Low-Power read (~1ms), reads internal MCU TSENS die.
  4. State Commit: Commits `orch_tri_node_sample_t` into RTC Slow Memory ring buffer.
  5. Zero-Hour Conflict Check: If remaining RTC alarm time $t_{\text{rem}} \le T_{\text{sub}}$, suppress timer rearm and sleep until RTC alarm.
  6. Return to Sleep: Total on-time **6 to 8 ms** (< 0.0001°C thermal impact). Active current during this 8ms window produces no measurable heating on the sensor package.

#### Flow B: Full Application Wake & Boot Pipeline
Triggered by cold power-on, reset button, external RTC countdown timer expiration, or tactile button wake:
1. **Power Latch Guard**: Locks `BAT_CTRL` HIGH immediately.
2. **PXE Handler**: Inspects depressed buttons; boots ROM bootloader if BOOT0 held >1.2s.
3. **Tri-Node Surface Reference**: Reads SSD1681 glass surface temperature via SPI Cmd 0x1B during display power-up.
4. **Sliding-Window Math**: Recalculates $T_{\text{amb\_floor}}$, updates EWMA, Dew Point, and $RH_{\text{amb}}$.
5. **Restore Display State**: If `ORCH_FLAG_EPD_FRAME_VALID` is set, loads 5000 bytes from `epd_frame` partition into display driver old-RAM buffer (0x26).
6. **Dispatch Lifecycle**: Dispatches `on_boot` or `on_wake` to Layer 4 application code.

---

### 3.4 `orch_display_sync.c/.h` (Deferred Flash Frame Sync Engine)
Eliminates flash write spam during active UI interactions:
- When LVGL flushes frames, `sub_display` marks `s_dirty = true` in memory.
- During stand-down (`bsp_app_sleep` or `bsp_app_shutdown`), Layer 3 queries `sub_display`:
  - If `s_dirty == true`:
    1. Erases 8KB range in `epd_frame` partition via `hal_flash_erase()`.
    2. Writes 5000 bytes via `hal_flash_write()`.
    3. Sets `ORCH_FLAG_EPD_FRAME_VALID` in RTC memory.
    4. Clears `s_dirty`.
  - If `s_dirty == false`: Skips flash write entirely.
