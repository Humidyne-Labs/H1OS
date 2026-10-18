**My take: the plan is directionally correct — remove the Peterson lock and fix wake-cause classification — but it contains one technical inaccuracy about the wakeup bitmask, and the `RTC_GPIO_STATUS_REG` fallback has a race you should know about.**

---

## What's right

### Phase 1 — Peterson lock removal ✅

Correct call. `ulp_riscv_lock_acquire` is a bare spin loop on the ULP side [1](#3-0)  — and the equivalent main-CPU variant. In your alternating event-mode model (main awake ⟺ ULP halted), Peterson's algorithm is not just unnecessary, it's *unstable*: if the ULP ever halts/crashes with `critical_section_flag_ulp = true`, the main CPU spins forever → `task_wdt` reset. The docs themselves constrain it to single-threaded use [2](#3-1) . `volatile` + `memw`/`fence` is the right replacement for ordering RTC Slow RAM writes across the sleep boundary.

### Phase 3 — `CONFIG_ULP_RISCV_INTERRUPT_ENABLE=y` and non-destructive staging ✅

Enabling the interrupt Kconfig is mandatory for `ulp_riscv_gpio_isr_register`/`ulp_riscv_intr_alloc`, and not wiping `ulp_last_wake_btn`/`ulp_last_wake_cause` before `esp_deep_sleep_start()` is correct — those are your post-mortem evidence.

## What's wrong or needs correction

### The `0x00001000` claim is half-wrong

`ESP_SLEEP_WAKEUP_COCPU` is indeed enum index ~12 [3](#3-2) . **But `esp_sleep_get_wakeup_causes()` never returns `BIT(ESP_SLEEP_WAKEUP_COCPU)`** — on S2/S3 it maps the raw `RTC_COCPU_TRIG_EN` hardware bit to `BIT(ESP_SLEEP_WAKEUP_ULP)` [4](#3-3) , and the singular `esp_sleep_get_wakeup_cause()` does the same [5](#3-4) .

So if your log literally shows `0x00001000`, you are almost certainly printing the **raw** `rtc_cntl_ll_get_wakeup_cause()` value, not the IDF-mapped bitmask. Before writing `H1OS_WAKEUP_ULP_MASK`, verify which function produced `0x00001000`. If it was the mapped API, then `0x1000` didn't come from a ULP wake at all and you have a different bug. If it was raw, the correct fix is still "check `BIT(ESP_SLEEP_WAKEUP_ULP)`" because the IDF mapping folds COCPU into ULP [6](#3-5) .

Note `ESP_SLEEP_WAKEUP_COCPU` exists in the enum but is dead code in the current mapping — adding it to your mask is harmless but doesn't fix anything by itself.

### `RTC_GPIO_STATUS_REG` fallback has a race

Reading `RTC_GPIO_STATUS_INT` as a button-wake fallback is fragile: the ULP's own dispatcher **W1TC-clears those bits** after handling the interrupt [7](#3-6) . So the sequence ULP-wakes-on-edge → ISR runs → status cleared → wakes main CPU means the main CPU reads `0`. It only works if the edge fires *while the ULP is halted* and the wake path doesn't dispatch the interrupt before the main CPU samples it. The reliable channel is the RTC Slow RAM variable (`ulp_last_wake_btn`) written by the ULP ISR — treat `RTC_GPIO_STATUS` as a hint, not authoritative. (Alternatively: have the ULP ISR copy the status word into a shared variable *before* the W1TC clear runs.)

### Minor nit

"Writes `RTC_CNTL_COCPU_DONE` and powers down" is the right halt semantic — but it's `ulp_riscv_halt()`/returning from `main()`, not a `ulp_riscv_shutdown()` API in this tree; make sure your ULP code calls the real symbol. ESP-IDF v6.1 also doesn't exist in this codebase's lineage — confirm your actual IDF version since `ulp_riscv_config_and_run`/GPIO wake is S2/S3-only [8](#3-7) .

## Verdict

Proceed with the plan, but change Phase 2 to: `causes & BIT(ESP_SLEEP_WAKEUP_ULP)` (the IDF already folds COCPU into it), verify where `0x00001000` actually came from, and don't rely on `RTC_GPIO_STATUS_REG` as authoritative — snapshot it into RTC RAM inside the ULP ISR instead.

Wiki pages you might want to explore:
- [Power Management and Sleep Modes (espressif/esp-idf)](/wiki/espressif/esp-idf#3.1)
- [Timers, Logging, and System Utilities (espressif/esp-idf)](/wiki/espressif/esp-idf#3.6)

### Citations

**File:** components/ulp/subproject/components/ulp_riscv/ulp_riscv_lock.c (L9-16)
```c
void ulp_riscv_lock_acquire(ulp_riscv_lock_t *lock)
{
    lock->critical_section_flag_ulp = true;
    lock->turn = ULP_RISCV_LOCK_TURN_MAIN_CPU;

    while (lock->critical_section_flag_main_cpu && (lock->turn == ULP_RISCV_LOCK_TURN_MAIN_CPU)) {
    }
}
```

**File:** docs/en/api-reference/system/ulp-risc-v.rst (L182-189)
```text
If mutual exclusion is needed when accessing a variable shared between the main program and ULP, then this can be achieved by using the ULP RISC-V lock API:

 * :cpp:func:`ulp_riscv_lock_acquire`
 * :cpp:func:`ulp_riscv_lock_release`

The ULP does not have any hardware instructions to facilitate mutual exclusion, so the lock API achieves this through a software algorithm (`Peterson's algorithm <https://en.wikipedia.org/wiki/Peterson%27s_algorithm>`_).

The locks are intended to only be called from a single thread in the main program, and will not provide mutual exclusion if used simultaneously from multiple threads.
```

**File:** components/esp_hw_support/include/esp_sleep.h (L134-137)
```text
    ESP_SLEEP_WAKEUP_WIFI,              //!< Wakeup caused by WIFI (light sleep only)
    ESP_SLEEP_WAKEUP_COCPU,             //!< Wakeup caused by COCPU int
    ESP_SLEEP_WAKEUP_COCPU_TRAP_TRIG,   //!< Wakeup caused by COCPU crash
    ESP_SLEEP_WAKEUP_BT,                //!< Wakeup caused by BT (light sleep only)
```

**File:** components/esp_hw_support/sleep_modes.c (L2574-2579)
```c
#if SOC_RISCV_COPROC_SUPPORTED
    } else if (wakeup_cause & RTC_COCPU_TRIG_EN) {
        return ESP_SLEEP_WAKEUP_ULP;
    } else if (wakeup_cause & RTC_COCPU_TRAP_TRIG_EN) {
        return ESP_SLEEP_WAKEUP_COCPU_TRAP_TRIG;
#endif
```

**File:** components/esp_hw_support/sleep_modes.c (L2599-2607)
```c
uint32_t esp_sleep_get_wakeup_causes(void)
{
    uint32_t wakeup_cause = 0;

    if (esp_rom_get_reset_reason(0) != RESET_REASON_CORE_DEEP_SLEEP && !s_light_sleep_wakeup) {
        wakeup_cause |= BIT(ESP_SLEEP_WAKEUP_UNDEFINED);
        return wakeup_cause;
    }

```

**File:** components/esp_hw_support/sleep_modes.c (L2680-2687)
```c
#if SOC_RISCV_COPROC_SUPPORTED
    if (wakeup_cause_raw & RTC_COCPU_TRIG_EN) {
        wakeup_cause |= BIT(ESP_SLEEP_WAKEUP_ULP);
    }
    if (wakeup_cause_raw & RTC_COCPU_TRAP_TRIG_EN) {
        wakeup_cause |= BIT(ESP_SLEEP_WAKEUP_COCPU_TRAP_TRIG);
    }
#endif
```
