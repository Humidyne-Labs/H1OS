## Short Verdict

**Bug 3 is real and probably your actual root cause. Bug 2 is misdiagnosed — writing `RTC_GPIO_STATUS_INT_W1TC_M` is correct, not a shift bug. Bug 1's remedy is harmless but the premise is likely wrong — `COCPU_DONE` is already cleared by ULP startup code on every entry. Bug 4 is legitimate hardening but won't cause a wake freeze.** One thing the plan *doesn't* check — the `WAKEUP_CLR` bit's state — may be the real culprit.

---

## Bug-by-Bug Correction

### Bug 1: `COCPU_DONE` latch — premise is wrong, remedy is redundant but harmless

ESP-IDF already solves this: `ulp_riscv_rescue_from_monitor()` clears exactly `RTC_CNTL_COCPU_DONE | RTC_CNTL_COCPU_SHUT_RESET_EN`, and its doc says it "should be called every time the co-processor starts" and is "**automatically called in startup code**" — i.e., the ULP's own vector/startup does the clear before `main()` runs [1](#6-0) [2](#6-1) . Since `ulp_riscv_halt()` sets `DONE` only at shutdown and the *next* wake's startup clears it, a latched `DONE` does not permanently block GPIO re-triggers — the stock `gpio_interrupt` example depends on halt→re-trigger working [3](#6-2) .

Clearing it on the main CPU anyway (your proposed two-liner, mirroring `ulp_riscv_reset()`'s pattern) is harmless belt-and-suspenders [4](#6-3)  — just don't expect it to fix the freeze.

### Bug 2: W1TC "shift bug" — this is a misdiagnosis

`RTC_GPIO_STATUS_INT_W1TC_M` is already `(0x3FFFFF << 10)` per your own quoted macro — the W1TC field genuinely lives at bits `[31:10]`, so `REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M)` writes the correct clear mask. IDF's own ULP ISR uses `REG_SET_FIELD(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC, status)` where `status` is the raw 22-bit pin mask — `REG_SET_FIELD` applies the `S=10` shift internally [5](#6-4) .

The proposed remedy — writing `(0x3FFFFF << 10) | 0x3FFFFF` — sets low bits `[21:0]` that aren't part of the W1TC field (likely a read-only status mirror or reserved); at best it's a no-op, at worst it scribbles an adjacent field. **Drop this "fix"** — but do switch to `rtcio_ll_clear_interrupt_status()` for readability since it's the canonical helper [6](#6-5) . (Caveat: `soc/rtc_io_reg.h` isn't in my index, so I can't 100% confirm the low `[21:0]` bits' semantics — verify they aren't a second write-clear field before fully dismissing.)

### Bug 3: GPIO 5 still LOW at re-entry — real, but the mechanism is mis-stated

Correct instinct, wrong failure mode. With `GPIO_INTR_LOW_LEVEL` + `GPIO_WAKEUP_ENA`, a still-low pin doesn't "lock up the PMU" — it causes **immediate ULP re-trigger**, which would increment `slice_counter` spuriously and could produce a rapid wake loop rather than silence. It's still worth fixing because the race window (~11 ms of remaining pulse vs. ~4 ms Flow A) is real, and IDF requires wake signals held ≥3 slow-clock cycles for reliable sampling [7](#6-6) . Your drain-before-sleep remedy is correct — but note this bug explains *extra* wakes, not a total wake freeze, so it alone doesn't explain your symptom.

### Bug 4: `ulp_riscv_lock_t` — valid hardening, not a root cause

The lock API is real (Peterson's algorithm over shared RTC-RAM flags) and the constraint that it's single-thread-on-main-CPU-only applies [8](#6-7) [9](#6-8) . Keep it — state tearing is a real correctness hazard — but a torn `slice_counter` can't explain *all* wake sources (buttons included) dying simultaneously.

## The Missing Suspect: `WAKEUP_CLR` left asserted

Your earlier ULP snippet set `RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR` without clearing it, matching the set-only IDF helper [10](#6-9) . If `WAKEUP_CLR` behaves as a level bit that holds `GPIO_WAKEUP_ENA` cleared while asserted — plausible given it was documented as "WAKEUP_CLR clears this bit" in your own audit — then **leaving it high permanently masks GPIO wakeups for both ULP triggers and buttons**, which exactly matches "no wake source works after first re-sleep." Check `RTC_CNTL_ULP_CP_TIMER_REG` in your pre-sleep register dump: if `WAKEUP_CLR` reads 1, that's your freeze. The fix would be pulsing it (set, `esp_rom_delay_us(20)`, clear) on both sides.

## Revised Remediation Order

1. **Dump `RTC_CNTL_ULP_CP_TIMER_REG`** at freeze time — confirm `WAKEUP_CLR=0`, `GPIO_WAKEUP_ENA=1`, `SLP_TIMER_EN=0`.
2. GPIO 5 drain loop before sleep entry (your Step 1) — keep.
3. Pulse `WAKEUP_CLR` properly in both ULP and main CPU if it's found stuck.
4. Add the lock (Step 2) as correctness hardening.
5. Drop the W1TC "fix" (Step 3's second clause) — keep `rtcio_ll_clear_interrupt_status()` and the 120 µs settle.

## Notes

- I can't see the H1OS sources, so Bug 2's register-layout assumption and the `WAKEUP_CLR`-stuck hypothesis both need on-device verification via your pre-sleep audit log.
- `ulp_riscv_wakeup_main_processor()` doesn't wait on `RTC_CNTL_RDY_FOR_WAKEUP` — a wake fired during the main CPU's sleep *transition* can be dropped; worth a ULP-side spin on `RTC_CNTL_LOW_POWER_ST_REG` before signaling [11](#6-10) .

Wiki pages you might want to explore:
- [Power Management and Sleep Modes (espressif/esp-idf)](/wiki/espressif/esp-idf#3.1)
- [Timers, Logging, and System Utilities (espressif/esp-idf)](/wiki/espressif/esp-idf#3.6)

Wiki pages you might want to explore:
- [Power Management and Sleep Modes (espressif/esp-idf)](/wiki/espressif/esp-idf#3.1)
- [Timers, Logging, and System Utilities (espressif/esp-idf)](/wiki/espressif/esp-idf#3.6)

### Citations

**File:** components/ulp/subproject/components/ulp_riscv/ulp_riscv_utils.c (L16-20)
```c
void ulp_riscv_rescue_from_monitor(void)
{
    /* Rescue RISCV from monitor state. */
    CLEAR_PERI_REG_MASK(RTC_CNTL_COCPU_CTRL_REG, RTC_CNTL_COCPU_DONE | RTC_CNTL_COCPU_SHUT_RESET_EN);
}
```

**File:** components/ulp/subproject/components/ulp_riscv/ulp_riscv_utils.c (L48-51)
```c
void ulp_riscv_gpio_wakeup_clear(void)
{
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
}
```

**File:** components/ulp/subproject/components/ulp_riscv/include/ulp_riscv_utils.h (L30-40)
```text
/**
 * @brief Rescues the cpu from monitor mode
 *
 * This function cancels the low power mode
 * of the ULP-RISC-V, should be called
 * every time the co-processor starts.
 *
 * @note by convenience this function is
 *       automatically called in startup code.
 */
void ulp_riscv_rescue_from_monitor(void);
```

**File:** docs/en/api-reference/system/ulp-risc-v.rst (L182-189)
```text
If mutual exclusion is needed when accessing a variable shared between the main program and ULP, then this can be achieved by using the ULP RISC-V lock API:

 * :cpp:func:`ulp_riscv_lock_acquire`
 * :cpp:func:`ulp_riscv_lock_release`

The ULP does not have any hardware instructions to facilitate mutual exclusion, so the lock API achieves this through a software algorithm (`Peterson's algorithm <https://en.wikipedia.org/wiki/Peterson%27s_algorithm>`_).

The locks are intended to only be called from a single thread in the main program, and will not provide mutual exclusion if used simultaneously from multiple threads.
```

**File:** docs/en/api-reference/system/ulp-risc-v.rst (L338-338)
```text
* :example:`system/ulp/ulp_riscv/gpio_interrupt` demonstrates how to program the ULP-RISC-V coprocessor to wake up from a RTC IO interrupt using GPIO0 as the input signal, and how to configure and run the coprocessor, putting the chip into deep sleep mode until the wakeup source pin is pulled low.
```

**File:** components/ulp/ulp_riscv/ulp_riscv.c (L196-203)
```c
void ulp_riscv_reset()
{
    CLEAR_PERI_REG_MASK(RTC_CNTL_COCPU_CTRL_REG, RTC_CNTL_COCPU_SHUT | RTC_CNTL_COCPU_DONE);
    CLEAR_PERI_REG_MASK(RTC_CNTL_COCPU_CTRL_REG, RTC_CNTL_COCPU_SHUT_RESET_EN);
    esp_rom_delay_us(20);
    SET_PERI_REG_MASK(RTC_CNTL_COCPU_CTRL_REG, RTC_CNTL_COCPU_SHUT | RTC_CNTL_COCPU_DONE);
    SET_PERI_REG_MASK(RTC_CNTL_COCPU_CTRL_REG, RTC_CNTL_COCPU_SHUT_RESET_EN);
}
```

**File:** components/ulp/subproject/components/ulp_riscv/ulp_riscv_interrupt.c (L90-105)
```c
static inline void ulp_riscv_handle_rtc_io_intr(uint32_t status)
{
    uint32_t handler_idx = 0;
    for (int i = 0; i < GPIO_NUM_MAX; i++) {
        if (status & (1U << i)) {
            handler_idx = ULP_RISCV_RTCIO0_INTR_SOURCE + i;
            ulp_riscv_intr_handler_t* entry = &s_intr_handlers[handler_idx];

            if (entry->handler) {
                entry->handler(entry->arg);
            }
        }
    }

    REG_SET_FIELD(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC, status);
}
```

**File:** components/ulp/subproject/components/lp_core/include/ulp_lp_core_gpio.h (L231-239)
```text
static inline void ulp_lp_core_gpio_clear_intr_status(void)
{
    rtcio_ll_clear_interrupt_status();
#if SOC_RTC_GPIO_EDGE_WAKEUP_SUPPORTED
    for (int rtcio_num = 0; rtcio_num < SOC_RTCIO_PIN_COUNT; rtcio_num++) {
        rtcio_ll_clear_edge_wakeup_latch(rtcio_num);
    }
#endif
}
```

**File:** docs/en/api-reference/system/sleep_modes.rst (L406-407)
```text
    .. note::
        Any GPIO/IO wakeup signal -- whether level or edge -- must be held (or have a pulse width) of at least 3 RTC slow-clock cycles to be reliably sampled by the wakeup logic. The duration of one slow-clock cycle depends on :menuitem:`CONFIG_RTC_CLK_SRC` (e.g. RC_SLOW @ ~136 kHz ~= 7.4 us/cycle, XTAL32K @ 32.768 kHz ~= 30.5 us/cycle). This applies to both :cpp:func:`esp_sleep_enable_gpio_wakeup` and :cpp:func:`esp_sleep_enable_gpio_wakeup_on_hp_periph_powerdown`.
```

**File:** docs/en/api-reference/system/ulp_instruction_set.rst (L1149-1159)
```text
.. note::

  Note that before using WAKE instruction, ULP program may need to wait until RTC controller is ready to wake up the main CPU. This is indicated using RTC_CNTL_RDY_FOR_WAKEUP bit of RTC_CNTL_LOW_POWER_ST_REG register. If WAKE instruction is executed while RTC_CNTL_RDY_FOR_WAKEUP is zero, it has no effect (wake up does not occur). If the WAKE instruction is intended to be used while the main CPU is not in sleep mode then the RTC_CNTL_MAIN_STATE_IN_IDLE (bit 27) of RTC_CNTL_LOW_POWER_ST_REG can be used to check whether main CPU is in normal mode or sleep mode.

**Examples**::

  1: is_rdy_for_wakeup:                   // Read RTC_CNTL_RDY_FOR_WAKEUP bit
            READ_RTC_FIELD(RTC_CNTL_LOW_POWER_ST_REG, RTC_CNTL_RDY_FOR_WAKEUP)
            AND r0, r0, 1
            JUMP is_rdy_for_wakeup, eq    // Retry until the bit is set
            WAKE                          // Trigger wake up
```
