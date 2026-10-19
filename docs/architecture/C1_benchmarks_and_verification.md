# Optional / Future Hardware Verification & Benchmarking Plan

> [!NOTE]
> **Document Scope:** This document outlines an optional, future physical bench verification plan for evaluating hardware timing and power tolerances using laboratory instrumentation (oscilloscope, inline current profiler, reference psychrometer). The figures below represent design targets and test procedures rather than active runtime assertions.

## 1. Overview & Verification Targets

This document defines the physical measurement procedures, test fixtures, expected design targets, and diagnostic hooks for **Stage 4.2: E-Class Hardware Benchmarking**.

| Benchmark Metric | Design Target | Measured Channel / Hook | Architectural Significance |
| :--- | :--- | :--- | :--- |
| **Flow A Sub-Execution Timing** | Minimal wake window | GPIO 3 (`HAL_PIN_STATUS_LED`) pulse width | Minimizes MCU self-heating in the sensor cavity. |
| **Deep Sleep Standby Current** | Low-leakage standby floor | Nordic PPK2 / inline µA meter on battery input | Extends multi-month battery operation on 500mAh LiPo. |
| **Partial Refresh Latency** | Fast partial update | SSD1681 `EPD_BUSY` (GPIO 8) low-to-high-to-low duration | Clean electrophoretic particle migration with zero flicker. |
| **Zero-Hour Conflict Suppression** | $0$ rapid double-wakes when sub-sample meets RTC alarm | Internal timer suppression logic in `orch_flow.c` & `orch_wake_stub.c` | Eliminates race condition between internal timer & PCF85063A. |
| **Flash Endurance Audit** | $\le 1$ erase/write per sleep cycle (0 if clean) | `epd_frame` partition sector write counter | Extends SPI NOR flash lifespan beyond 100,000 cycles. |
| **Tri-Node Thermal Equilibrium** | $T_{\text{SHTC3}} \le T_{\text{Glass}} < T_{\text{MCU}}$ in steady state | Tri-Node telemetry query (`SHTC3`, `TSENS`, `SSD1681 0x1B`) | Validates thermodynamic invariant engine model. |

---

## 2. Test Procedures & Test Fixtures

### 2.1 Benchmark 1: Flow A Sub-Execution Timing
- **Objective:** Measure the RTC Fast Memory wake stub duration while capturing SHTC3 normal-power telemetry before returning directly to deep sleep.
- **Fixture:** Connect an oscilloscope channel to **GPIO 3** (`STATUS_LED`) with active-low trigger.
- **Instrumented Code:** In `orch_wake_stub.c`, GPIO 3 is pulled LOW upon wake entry (`REG_WRITE(GPIO_OUT_W1TC_REG, (1UL << HAL_PIN_STATUS_LED))`) and set HIGH (`GPIO_OUT_W1TS_REG`) immediately before `esp_wake_stub_sleep()`.
- **Expected Sequence:**
  1. Wake stub asserts GPIO 3 LOW.
  2. SHTC3 Wake Command (`0x3517`) and Normal-Power measurement command (`0x7866`).
  3. SHTC3 Normal-Power conversion wait ($13\text{ ms}$).
  4. Read 6 bytes of SHTC3 data and send Sleep Command (`0xB098`).
  5. Integer math conversion and RTC Slow SRAM ring push.
  6. Deassert GPIO 3 HIGH and trigger `esp_wake_stub_sleep()`.
- **Pass Criterion:** Clean single pulse width on oscilloscope cursor matching the normal-mode conversion sequence.

---

### 2.2 Benchmark 2: Deep Sleep Standby Quiescent Current (< 15 µA)
- **Objective:** Measure total quiescent current during deep sleep when all hardware rails are isolated.
- **Fixture:** Connect Nordic Semiconductor Power Profiler Kit II (PPK2) or Keysight µA meter in series with LiPo battery terminal ($3.7\text{--}4.2\text{V}$). Disconnect USB cable to test pure battery draw.
- **Critical Rail Invariants Verified:**
  1. `BAT_CTRL` (GPIO 17) latched HIGH via RTC pad hold (LDO enabled).
  2. `EPD_3V3_EN` (GPIO 6) held LOW via RTC pad hold (display rail active, SSD1681 in Deep Sleep Mode 1 @ $1.0\text{ }\mu\text{A}$).
  3. `PA_EN` (GPIO 42) held HIGH and `PA_CTRL` (GPIO 46) held LOW (audio power cut & muted).
  4. ES8311 Codec in software standby (Reg 0x0D = 0x00 @ $<1.0\text{ }\mu\text{A}$), keeping I2C bus un-clamped.
  5. PCF85063A `COF[2:0] = 111` (CLKOUT pin permanently disabled to prevent parasitic square-wave leakage).
- **Pass Criterion:** Average standby floor $\le 15.0\text{ }\mu\text{A}$ RMS over a 60-second sleep interval.

---

### 2.3 Benchmark 3: Partial Refresh Latency (~300 ms)
- **Objective:** Measure electrophoretic particle update time using the custom 159-byte waveform LUT.
- **Fixture:** Oscilloscope logic analyzer channel on **GPIO 8** (`EPD_BUSY`).
- **Telemetry Log:** In `sub_display.cpp`, `sub_display_refresh_partial()` prints:
  ```text
  I (xxxx) sub_display: Partial Refresh completed in 312 ms (Target: ~300 ms)
  ```
- **Pass Criterion:** Hardware BUSY line pulse width between $280\text{ ms}$ and $350\text{ ms}$.

---

### 2.4 Benchmark 4: Zero-Hour Conflict Elimination Stress Test
- **Objective:** Verify that when a Flow A headless sensor sample burst coincides with or straddles an external PCF85063A countdown timer expiration, no rapid double-wake occurs.
- **Validation Logic:**
  1. In Flow A Fast Wake Stub (`orch_wake_stub_run()`):
     - Check `sub_rtc_get_and_clear_interrupts(&alarm, &timer)`: if either fired, abort sleep and promote directly to Flow B.
     - Check `sub_rtc_get_remaining_seconds(&rem_sec)`: if $T_{\text{rem}} \le T_{\text{sleep}}$, clamp internal sleep time to $T_{\text{rem}}$.
  2. In `orch_flow_transition_to_sleep()` / `sub_power_enter_deep_sleep()`:
     - Lookahead evaluation: if $T_{\text{rem}} \le T_{\text{sleep}}$, suppress internal timer ($T_{\text{internal}} = 0$) and sleep exclusively on external GPIO 5 `RTC_INT`.
- **Pass Criterion:** Zero back-to-back wakes $< 100\text{ ms}$ observed over 1,000 continuous sleep cycles.

---

### 2.5 Benchmark 5: Flash Endurance Audit
- **Objective:** Ensure SPI NOR flash partition `epd_frame` is only written when the framebuffer has actually changed, preventing flash exhaustion.
- **Validation Logic:**
  - `orch_display_sync_mark_dirty()` is called strictly when LVGL flushes a new frame.
  - `orch_display_sync_save_if_dirty()` writes and clears the dirty flag.
  - Subsequent sleep sequences without frame changes skip flash sector erase and write operations.
- **Pass Criterion:** Flash sector erase/write calls strictly equal the number of dirty screen refreshes, and 0 writes occur during periodic headless sensor sample bursts.

---

### 2.6 Benchmark 6: Tri-Node Thermal Equilibrium Validation
- **Objective:** Verify that ambient temperature reconstruction correctly captures the cavity gradient without synthetic curve fitting.
- **Gradient Rule:**

$$
T_{\text{SHTC3}} \le T_{\text{Glass}} < T_{\text{MCU}}
$$

  - $T_{\text{MCU}}$ (die junction) is warmest due to silicon dissipation.
  - $T_{\text{Glass}}$ reflects frontal case surface temperature.
  - $T_{\text{SHTC3}}$ reflects cavity thermodynamic floor.
- **Pass Criterion:** Reconstructed ambient $T_{\text{amb}}$ tracks reference dry-bulb thermometer to within $\pm 0.3^\circ\text{C}$ and reconstructed $RH_{\text{amb}}$ tracks reference to within $\pm 2.0\%$.
