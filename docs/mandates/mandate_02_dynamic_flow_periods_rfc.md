# RFC: MANDATE-02 — Dynamic Flow Periods API, Silicon Limits & Slicing Guards

## 1. Overview & Context

This dedicated specification isolates **`MANDATE-02`** from `docs/audits/_docs/` for authoritative engineering documentation.

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
1. **Single-Countdown Register Ceiling:**
   $$\text{Max Single Countdown} = 255 \times 60\text{ s} = 15,300\text{ s} = 255\text{ minutes} = \mathbf{4.25\text{ hours}}\ (4\text{h }15\text{m})$$
   Flow A is capped at $14,400\text{ seconds}$ ($4\text{ hours}$ = $240\text{ minutes}$), fitting cleanly within this register limit.
2. **Prescaler Resolution Shift Boundary ($255\text{ seconds}$):**
   - For durations $\le 255\text{s}$, the driver selects `TIMER_CLK_1_HZ`, providing exact $1\text{-second}$ resolution.
   - For durations $> 255\text{s}$, the driver selects `TIMER_CLK_1_60_HZ`, providing $60\text{-second}$ (1-minute) resolution.
   - **Prescaler Alignment Invariant:** Any duration $> 255\text{s}$ must be an exact multiple of 60 seconds ($\text{sec} \pmod{60} == 0$), preventing prescaler rounding drift.
3. **Hardware Auto-Reload:**
   When configured with `TIMER_PULSE_MODE_BIT` (`TI_TP = 1`), the PCF85063A down-counter automatically reloads `Timer_value` upon reaching `0` and continues counting down from the 32.768 kHz quartz oscillator without stopping. Software execution does not introduce cumulative drift across identical slices.

---

## 3. Finalized Slicing & Overlap Remainder Architecture

To provide full developer ergonomics without requiring strict integer multiples, H1OS supports arbitrary period pairs $(A, B)$ using the **overlap remainder engine**:
* $\text{full\_slices} = \lfloor B / A \rfloor$
* $\text{remainder} = B \pmod A$
* $\text{overflow\_limit} = \text{full\_slices} + (\text{remainder} > 0 \mathbin{?} 1 : 0)$

### The 60-Second Remainder Floor
* If $\text{remainder} == 0$: The system runs on 100% continuous hardware auto-reload.
* If $\text{remainder} > 0$: The final slice before Flow B requires re-arming the RTC timer via `rtc_rearm_countdown_stub(ulp_remainder_sec)`. To prevent energy-wasting micro-wakes, any non-zero remainder must be **$\ge 60\text{ seconds}$**.

---

## 4. Authoritative API Contract (`include/h1os/h1os.h`)

```c
#define H1OS_FLOW_A_MIN_SEC         60U        /**< 1 minute minimum Flow A period.         */
#define H1OS_FLOW_A_MAX_SEC         14400U     /**< 4 hours maximum Flow A period.          */
#define H1OS_FLOW_B_MIN_SEC         300U       /**< 5 minutes minimum Flow B period.        */
#define H1OS_FLOW_B_MAX_SEC         86400U     /**< 24 hours maximum Flow B period.         */
#define H1OS_FLOW_REMAINDER_MIN_SEC 60U        /**< 60 seconds minimum remainder slice.     */

#define H1OS_MIN_TO_SEC(m)          ((uint32_t)(m) * 60U)
#define H1OS_HOURS_TO_SEC(h)        ((uint32_t)(h) * 3600U)
#define H1OS_SEC_TO_MIN(s)          ((uint32_t)(s) / 60U)
#define H1OS_SEC_TO_HOURS(s)        ((uint32_t)(s) / 3600U)

/**
 * @brief Dynamically configure Flow A and Flow B sleep intervals at runtime.
 *
 * Enforces all silicon constraints, ordering invariants, and remainder slice floors.
 * Updates active RTC Slow Memory state and immediately arms the hardware RTC countdown
 * timer with the new Flow A cadence.
 *
 * @param[in] flow_a_sec Headless sensor acquisition interval (60s .. 14400s / 4h).
 *                       Must be an exact multiple of 60 seconds if > 255s.
 * @param[in] flow_b_sec Display refresh and network wake interval (300s .. 86400s / 24h).
 *                       Must be strictly greater than flow_a_sec.
 *                       Any remainder (flow_b_sec % flow_a_sec) must be >= 60 seconds.
 *
 * @return
 *   - ESP_OK: Flow periods validated, committed to RTC Slow Memory, and hardware timer armed.
 *   - ESP_ERR_INVALID_ARG: Any boundary, prescaler, ordering, or remainder invariant violated.
 */
esp_err_t h1os_set_flow_periods(uint32_t flow_a_sec, uint32_t flow_b_sec);
```

---

## 5. Architectural Invariants Enforced

1. **Single Variable Authority:** All time logic across `sub_power.c`, `orch_flow.c`, `orch_wake_stub.c`, and `h1os_lifecycle.c` derives strictly from `st->sample_interval_sec` and `st->flow_b_period_sec` in RTC Slow Memory.
2. **Unified Setter Path:** All assignments to flow periods funnel strictly through `h1os_set_flow_periods_internal()`. Both `h1os_start()` and `h1os_set_flow_periods()` invoke this exact validator.
3. **Deterministic Returns:** Callers must always check the return value of `h1os_start()` and `h1os_set_flow_periods()`. Invalid arguments fail immediately without silent fallbacks.
