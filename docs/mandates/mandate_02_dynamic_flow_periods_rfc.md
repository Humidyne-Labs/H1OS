# RFC: MANDATE-02 — Dynamic Flow Periods API, Silicon Limits & Slicing Guards

## 1. Overview & Context

This dedicated discussion artifact isolates **`MANDATE-02`** from `docs/audits/_docs/` for separate engineering evaluation.

The mandate specifies a public API allowing downstream applications to dynamically alter Flow A (headless SHTC3 sensor acquisition) and Flow B (unattended display refresh and cloud transmission) intervals at runtime, updating the active RTC Slow Memory state and re-arming the hardware countdown timer accordingly.

---

## 2. Hardware & Firmware Ground Truth

### 1. PCF85063A Countdown Register & Prescaler Constraints
The PCF85063A external RTC countdown timer register (`Timer_value`, address `0x10`) is an 8-bit down-counter (range 0..255). It is driven by four selectable clock sources derived from the 32.768 kHz quartz crystal:
- **`TIMER_CLK_4096_HZ` (0x00):** $4096\text{ Hz}$ ($244.14\ \mu\text{s}$ tick).
- **`TIMER_CLK_64_HZ` (0x01):** $64\text{ Hz}$ ($15.625\text{ ms}$ tick).
- **`TIMER_CLK_1_HZ` (0x02):** $1\text{ Hz}$ ($1.000\text{ s}$ tick).
- **`TIMER_CLK_1_60_HZ` (0x03):** $1/60\text{ Hz}$ ($60.000\text{ s}$ / 1-minute tick).

#### Hardware Limits:
1. **Absolute Maximum Countdown Ceiling:**
   $$\text{Max Period} = 255 \times 60\text{ s} = 15,300\text{ s} = 255\text{ minutes} = \mathbf{4.25\text{ hours}}\ (4\text{h }15\text{m})$$
   Any single countdown duration exceeding $15,300\text{ seconds}$ is physically unrepresentable in the PCF85063A silicon and cannot be armed directly.
2. **Prescaler Resolution Shift Boundary ($255\text{ seconds}$):**
   - For durations $\le 255\text{s}$, the driver selects `TIMER_CLK_1_HZ`, providing exact $1\text{-second}$ resolution.
   - For durations $> 255\text{s}$, the driver must switch to `TIMER_CLK_1_60_HZ`, providing only $60\text{-second}$ (1-minute) resolution. The register value is computed as:
     $$\text{timer\_val} = \left\lfloor \frac{\text{seconds} + 59}{60} \right\rfloor$$
   - **Resolution Invariant:** Durations $> 255\text{s}$ that are not whole multiples of 60 seconds are rounded up by the hardware to the nearest minute, introducing a deterministic drift of up to $+59\text{ seconds}$.

### 2. Firmware Slicing Engine Architecture
In `orch_flow.c:396-403`:
```c
uint32_t full_slices = flow_b_sec / flow_a_sec;
uint32_t remainder   = flow_b_sec % flow_a_sec;
uint32_t overflow    = full_slices + (remainder > 0 ? 1 : 0);
uint32_t initial_arm_sec = (full_slices > 0) ? flow_a_sec : remainder;
```

In `orch_wake_stub.c:619`:
```c
if (ulp_slice_counter == (ulp_overflow_limit - 1) && ulp_remainder_sec > 0) {
    rtc_rearm_countdown_stub(ulp_remainder_sec);
}
```

In `components/h1os/ulp/main.c:221-237`:
```c
slice_counter++;
if (slice_counter < overflow_limit) {
    last_wake_cause = ULP_WAKE_CAUSE_SENSOR_TICK;
    dispatch_reason = ULP_DISPATCH_SENSOR_SAMPLE;
    wake_main       = true;  /* Wakes to fast RTC wake stub (Flow A) */
} else {
    slice_counter   = 0;
    remainder_sec   = 0;
    last_wake_cause = ULP_WAKE_CAUSE_LONG_OVERFLOW;
    dispatch_reason = ULP_DISPATCH_MAIN_WAKE;
    wake_main       = true;  /* Wakes full FreeRTOS CPU (Flow B) */
}
```

---

## 3. Complete Silicon Timing & Fringe Case Analysis

| # | Fringe Case Scenario | Physical / Silicon Mechanism | System Failure if Unguarded | Guard Specification |
| :- | :--- | :--- | :--- | :--- |
| **1** | **Degenerate Slicing ($B \le A$)** | In `ulp/main.c`, `slice_counter` starts at 0. If $B \le A$, `overflow_limit = 1`. On tick 1, `slice_counter` becomes 1. Since `1 < 1` is false, ULP dispatches `MAIN_WAKE` directly. | **Flow A is completely bypassed.** The system never takes a single sensor reading; boots Flow B on tick 1. | **`flow_b_sec > flow_a_sec` must be strictly enforced.** ($overflow\_limit \ge 2$). |
| **2** | **Unsigned Integer Underflow** | In C (`uint32_t`), if $B < A$ (e.g. $B = 300\text{s}, A = 600\text{s}$), evaluating `(flow_b_sec - flow_a_sec)` wraps around to $4,294,966,996$. | A naive `(B - A) >= 30` check evaluates to **true**, allowing invalid $B < A$ pairs to pass. | Prerequisite check: `if (flow_b_sec <= flow_a_sec) return ESP_ERR_INVALID_ARG;`. |
| **3** | **Separation Headroom ($B - A < 30\text{s}$)** | When $B / A = 1$ ($A < B < 2A$), the time remaining after Flow A is $r = B - A$. | Deep sleep power rail isolation, pad holding, and 32.768 kHz crystal oscillation fail to stabilize if sleep slice is $< 30\text{s}$. | `if ((flow_b_sec - flow_a_sec) < 30) return ESP_ERR_INVALID_ARG;`. |
| **4** | **Micro-Remainder Slices ($r = B \pmod A < 30\text{s}$)** | When $B / A \ge 2$, on slice $k$, `orch_wake_stub.c:619` rearms the timer for $r$ seconds (e.g. $B = 305\text{s}, A = 60\text{s} \implies r = 5\text{s}$). | Timer expires after 5 seconds, triggering an immediate re-wake loop while the chip is still sequencing sleep entry. | `if (remainder > 0 && remainder < 30) return ESP_ERR_INVALID_ARG;`. |
| **5** | **Prescaler Drift ($> 255\text{s}$ not divisible by 60)** | PCF85063A registers above 255s count 1-minute ticks (`TIMER_CLK_1_60_HZ`). Durations like 280s round up to 300s (`(280 + 59)/60 = 5`). | Hardware drifts by $+20\text{s}$ on every slice. Remainder slices $> 255\text{s}$ distort the presentation wake time. | `if (flow_a_sec > 255 && (flow_a_sec % 60 != 0)) return ESP_ERR_INVALID_ARG;`<br>`if (remainder > 255 && (remainder % 60 != 0)) return ESP_ERR_INVALID_ARG;`. |
| **6** | **Timer Register Overflow ($> 15,300\text{s}$)** | $255 \times 60\text{s} = 15,300\text{s} = 4.25\text{ hours}$. | Values $> 15,300\text{s}$ overflow the 8-bit `Timer_value` register, wrapping modulo 256. | `if (flow_b_sec > 15300) return ESP_ERR_INVALID_ARG;`. |

---

## 4. Architectural Proposals for Discussion

### Proposal 1: Unified Function with Strict Bounds & Rejection
Provide a single public API with unit conversion helper macros:

```c
#define H1OS_FLOW_A_MIN_SEC    60U     /**< 1 minute.      */
#define H1OS_FLOW_A_MAX_SEC    3600U   /**< 1 hour.        */
#define H1OS_FLOW_B_MIN_SEC    300U    /**< 5 minutes.     */
#define H1OS_FLOW_B_MAX_SEC    15300U  /**< 4.25 hours.    */
#define H1OS_FLOW_HEADROOM_SEC 30U     /**< 30 seconds.    */

#define H1OS_MIN_TO_SEC(m)     ((uint32_t)(m) * 60U)
#define H1OS_HOURS_TO_SEC(h)   ((uint32_t)(h) * 3600U)
#define H1OS_SEC_TO_MIN(s)     ((uint32_t)(s) / 60U)
#define H1OS_SEC_TO_HOURS(s)   ((uint32_t)(s) / 3600U)

/**
 * @brief Dynamically update Flow A and Flow B sleep intervals at runtime.
 *
 * @param flow_a_sec Headless sensor sampling interval in seconds (60..3600).
 * @param flow_b_sec Display/cloud wake interval in seconds (300..15300).
 * @return ESP_OK on success, ESP_ERR_INVALID_ARG if any bounds or slicing invariants fail.
 */
esp_err_t h1os_set_flow_periods(uint32_t flow_a_sec, uint32_t flow_b_sec);
```

### Proposal 2: Automatic Slicing Harmonizer (Auto-Rounding)
Instead of returning `ESP_ERR_INVALID_ARG` when a remainder is invalid or micro-duration ($r < 30\text{s}$ or $> 255\text{s}$ unaligned), the function could automatically round `flow_b_sec` up to the nearest clean multiple of `flow_a_sec` or enforce exact multiples:
- **Pros:** Application never crashes on valid high-level intent (e.g. "update every 17 minutes").
- **Cons:** Violates explicit contractual determinism; the system wakes at an interval different from what the caller passed.

### Proposal 3: Pure Multiples Invariant (`flow_b_sec % flow_a_sec == 0`)
Mandate that Flow B must **always be an exact integer multiple of Flow A** ($B = k \cdot A, k \ge 2$):
- **Pros:** Completely eliminates remainder slices, eliminates wake stub rearming logic in `orch_wake_stub.c`, and guarantees perfect clock prescaler alignment.
- **Cons:** Slightly restricts application flexibility (e.g., cannot do 60s Flow A with a 350s Flow B; must do 300s or 360s).

---

## 5. Open Questions for Engineering Decision
1. Should `h1os_set_flow_periods()` strictly reject unaligned/micro-remainder values (`ESP_ERR_INVALID_ARG`), or should it auto-harmonize Flow B?
2. Is the 4.25-hour hardware ceiling ($15,300\text{s}$) sufficient for all intended downstream use cases, or is a multi-stage software epoch counter required for multi-day unattended deployments?
3. Would restricting Flow B to exact integer multiples of Flow A ($B = k \cdot A, k \ge 2$) simplify downstream fleet orchestration?
