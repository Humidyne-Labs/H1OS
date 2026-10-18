Yes — but you don't need an ISR. `ulp_riscv_wakeup_main_processor()` is just a fire-and-forget signal (`SET RTC_CNTL_SW_CPU_INT`); the ULP keeps executing afterward, so the fix is simply **ordering**: read the ADC, publish the result to RTC-RAM shared vars, *then* wake, then halt. [1](#3-0) 

```c
/* Do all work BEFORE signaling wake */
int32_t raw = ulp_riscv_adc_read_channel(ADC_UNIT_1, ADC_CHANNEL_x);

/* Publish to shared vars (exported via ulp_h1os.h) */
ulp_sensor_raw       = raw;
ulp_sensor_seq++;                        /* seq counter = poor man's atomic flag */
ulp_sensor_valid     = 1;

/* NOW wake the main CPU */
if (wake_main) {
    ulp_riscv_wakeup_main_processor();
}
ulp_riscv_halt();
```

---

## Why this works

- `ulp_riscv_adc_read_channel()` is a **blocking polled read** — it spins on `adc_oneshot_ll_get_event()` internally, so there's no interrupt to wait for anyway. [2](#3-1) 
- Deep-sleep wake isn't instantaneous: the main CPU goes through ROM boot → `esp_sleep_wakeup` → app restore, taking ~ms. By the time your app reads `ulp_sensor_raw`, the ULP has already halted. Ordering alone is sufficient.
- An actual ULP-side ISR is overkill: ULP interrupt support is limited (no nested interrupts; only SW and RTC-IO external sources are supported, internal sources aren't), and there's no ADC-done interrupt routed to the ULP anyway. [3](#3-2) 

## Hardening the handshake (optional)

If the main CPU might race the ULP (e.g., woken by a button while ULP is mid-conversion), use the provided Peterson's-lock API rather than a hand-rolled flag: [4](#3-3) 

```c
/* shared: volatile ulp_riscv_lock_t ulp_sensor_lock; */
ulp_riscv_lock_acquire(&ulp_sensor_lock);
ulp_sensor_raw = raw;
ulp_sensor_seq++;
ulp_riscv_lock_release(&ulp_sensor_lock);
```

The main CPU uses the symmetric `ulp_riscv_lock_acquire/release` and checks `ulp_sensor_seq` changed before trusting the data. [5](#3-4) 

## Watch out

- Shared vars live in `.bss`/`.data` of the ULP binary in RTC Slow RAM — they persist across deep sleep, which is exactly why this pattern works. Don't read them on the main CPU before the ULP binary is first loaded/run. [6](#3-5) 
- If the main CPU is woken by a *button* while the ULP is still running its sensor-tick path, the ULP continues to completion — the wake signal doesn't preempt it. `ulp_riscv_halt()` in the ULP then finishes normally. [7](#3-6) 

## Notes

- LP-Core test code shows the same read-then-bump-seq pattern (`adc_raw[i]` + `adc_scan_seq++` in a loop) if you want a reference shape for a multi-channel scan. [8](#3-7) 
- Keep the ADC read *before* your GPIO-5 pulse drain loop too — the 15.6 ms wait dominates the ULP's on-time, so doing the conversion first doesn't cost you anything extra in energy terms.

Wiki pages you might want to explore:
- [Timers, Logging, and System Utilities (espressif/esp-idf)](/wiki/espressif/esp-idf#3.6)
- [CI/CD Pipeline Architecture (espressif/esp-idf)](/wiki/espressif/esp-idf#5.1)

### Citations

**File:** components/ulp/subproject/components/ulp_riscv/ulp_riscv_utils.c (L22-25)
```c
void ulp_riscv_wakeup_main_processor(void)
{
    SET_PERI_REG_MASK(RTC_CNTL_STATE0_REG, RTC_CNTL_SW_CPU_INT);
}
```

**File:** components/ulp/subproject/components/ulp_riscv/ulp_riscv_utils.c (L27-35)
```c
void ulp_riscv_halt(void)
{
    /* Setting the delay time after RISCV recv `DONE` signal, Ensure that action `RESET` can be executed in time. */
    REG_SET_FIELD(RTC_CNTL_COCPU_CTRL_REG, RTC_CNTL_COCPU_SHUT_2_CLK_DIS, 0x3F);

    /* Suspends the ulp operation and reset the ULP core. Must be the final operation before going to halt. */
    SET_PERI_REG_MASK(RTC_CNTL_COCPU_CTRL_REG, RTC_CNTL_COCPU_DONE | RTC_CNTL_COCPU_SHUT_RESET_EN);

    while (1);
```

**File:** components/ulp/subproject/components/ulp_riscv/ulp_riscv_adc.c (L20-24)
```c
    adc_oneshot_ll_start(adc_n);
    while (adc_oneshot_ll_get_event(event) != true) {
        ;
    }
    int32_t out_raw = adc_oneshot_ll_get_raw_result(adc_n);
```

**File:** docs/en/api-reference/system/ulp-risc-v.rst (L173-177)
```text
.. note::

    - Variables declared in the global scope of the ULP RISC-V program reside in either the ``.bss`` or ``.data`` section of the binary. These sections are initialized when the ULP RISC-V binary is loaded and executed. Accessing these variables from the main program on the main CPU before the first ULP RISC-V run may result in undefined behavior.

    - The ``ulp_`` prefix is the default value. You can specify the prefix to use with ``ulp_embed_binary`` to avoid name collisions for multiple ULP programs.
```

**File:** docs/en/api-reference/system/ulp-risc-v.rst (L179-189)
```text
Mutual Exclusion
^^^^^^^^^^^^^^^^

If mutual exclusion is needed when accessing a variable shared between the main program and ULP, then this can be achieved by using the ULP RISC-V lock API:

 * :cpp:func:`ulp_riscv_lock_acquire`
 * :cpp:func:`ulp_riscv_lock_release`

The ULP does not have any hardware instructions to facilitate mutual exclusion, so the lock API achieves this through a software algorithm (`Peterson's algorithm <https://en.wikipedia.org/wiki/Peterson%27s_algorithm>`_).

The locks are intended to only be called from a single thread in the main program, and will not provide mutual exclusion if used simultaneously from multiple threads.
```

**File:** docs/en/api-reference/system/ulp-risc-v.rst (L301-306)
```text

Interrupt handling is enabled via special 32-bit registers Q0-Q3 and custom R-type instructions. For more information, see *{IDF_TARGET_NAME} Technical Reference Manual* > *ULP Coprocessor* > *ULP-RISC-V* > *ULP-RISC-V Interrupts* [`PDF <{IDF_TARGET_TRM_EN_URL}>`__].

All interrupts are enabled globally during start-up. When an interrupt occurs, the processor jumps to the IRQ vector. The IRQ vector performs the task of saving the register context and then calling the global interrupt dispatcher. The ULP RISC-V driver implements a *weak* interrupt dispatcher :cpp:func:`_ulp_riscv_interrupt_handler` which serves as the central point for handling all interrupts. This global dispatcher calls respective interrupt handlers which have been allocated via the :cpp:func:`ulp_riscv_intr_alloc`.

Interrupt handling on the ULP RISC-V is not fully featured yet. At present, interrupt handling for internal interrupt sources is not supported. Support is provided for two RTC peripheral sources, viz., software-triggered interrupts and RTC IO-triggered interrupts. ULP RISC-V does not support nested interrupts. If users need custom interrupt handling then they may override the default global interrupt dispatcher by defining their own :cpp:func:`_ulp_riscv_interrupt_handler`.
```

**File:** components/ulp/subproject/components/ulp_riscv/ulp_riscv_lock.c (L9-21)
```c
void ulp_riscv_lock_acquire(ulp_riscv_lock_t *lock)
{
    lock->critical_section_flag_ulp = true;
    lock->turn = ULP_RISCV_LOCK_TURN_MAIN_CPU;

    while (lock->critical_section_flag_main_cpu && (lock->turn == ULP_RISCV_LOCK_TURN_MAIN_CPU)) {
    }
}

void ulp_riscv_lock_release(ulp_riscv_lock_t *lock)
{
    lock->critical_section_flag_ulp = false;
}
```

**File:** components/ulp/test_apps/lp_core/lp_core_basic_tests/main/lp_core/test_main_adc.c (L9-19)
```c
volatile int adc_raw[8];
volatile uint32_t adc_scan_seq;

int main(void)
{
    while (1) {
        for (int i = 0; i < 8; i++) {
            lp_core_lp_adc_read_channel_raw(ADC_UNIT_1, i, (int *)&adc_raw[i]);
        }
        adc_scan_seq++;
    }
```
