# DeepWiki Q&A with Code Context for Repository: espressif/esp-idf
## Q1
i need a master example + checklist of things to do/not do, when running both the ulps rsicv and main application. riscv is running as event mode, taking interrupt inputs from io and waking.
### Answer
You want the ULP RISC-V running in **event mode** — i.e. started by a GPIO interrupt rather than the periodic timer — sharing work with the main CPU. Below is a canonical pattern assembled from the driver and test code, followed by the checklist.

## Master example — event (GPIO) mode

### 1. CMake — embed the ULP binary

```cmake
idf_component_register()

set(ulp_app_name ulp_${COMPONENT_NAME})
set(ulp_sources "ulp/ulp_main.c")
set(ulp_exp_dep_srcs "ulp_main.c")

ulp_embed_binary(${ulp_app_name} "${ulp_sources}" "${ulp_exp_dep_srcs}" TYPE riscv)
```

`TYPE riscv` is required when both FSM and RISC-V coprocessor types are enabled esp-idf:39-41 . Enable `CONFIG_ULP_COPROC_ENABLED`, select `CONFIG_ULP_COPROC_TYPE_RISCV`, and size `CONFIG_ULP_COPROC_RESERVE_MEM` for your largest ULP program esp-idf:109-113 .

### 2. Main application

```c
#include "ulp_riscv.h"
#include "ulp_main.h"          /* generated: ulp_* symbols */

extern const uint8_t bin_start[] asm("_binary_ulp_main_bin_start");
extern const uint8_t bin_end[]   asm("_binary_ulp_main_bin_end");

void app_main(void)
{
    /* Load firmware into RTC memory */
    ESP_ERROR_CHECK(ulp_riscv_load_binary(bin_start, bin_end - bin_start));

    /* Event mode: ULP is woken by RTC IO interrupts, not the timer */
    ulp_riscv_cfg_t cfg = {
        .wakeup_source = ULP_RISCV_WAKEUP_SOURCE_GPIO,
    };
    ESP_ERROR_CHECK(ulp_riscv_config_and_run(&cfg));

    /* Init any shared variables now */
    ulp_event_count = 0;

    /* Sleep / go do work — let ULP IRQs wake you via esp_sleep_enable_ulp_wakeup() */
}
```

`ULP_RISCV_WAKEUP_SOURCE_GPIO` sets `RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA` instead of the sleep timer esp-idf:87-107 . The config enum and `ULP_RISCV_DEFAULT_CONFIG` (which defaults to TIMER — you must override it) are in esp-idf:19-35 . Load/run ordering is documented at esp-idf:194-214 .

### 3. ULP side — register GPIO ISR and halt

```c
#include "ulp_riscv_gpio.h"
#include "ulp_riscv_interrupt.h"
#include "ulp_riscv_utils.h"

volatile uint32_t event_count;

static void gpio0_isr(void *arg)
{
    event_count++;
    /* Note: dispatcher already clears the RTC IO status bits */
}

int main(void)
{
    ulp_riscv_gpio_init(GPIO_NUM_0);
    ulp_riscv_input_enable(GPIO_NUM_0);
    ulp_riscv_gpio_isr_register(GPIO_NUM_0,
                                ULP_RISCV_GPIO_INT_TYPE_HIGH_LEVEL,
                                gpio0_isr, NULL);

    /* Optionally wake main CPU on every Nth event:
     * if (event_count >= THRESHOLD) ulp_riscv_wakeup_main_processor();
     */
    while (1) { /* stay in low-power wait / wfi loop per your design */ }
}
```

`ulp_riscv_gpio_isr_register` validates the args, writes `RTC_GPIO_PIN0_INT_TYPE`, and forwards to `ulp_riscv_intr_alloc` with source `ULP_RISCV_RTCIO0_INTR_SOURCE + gpio_num` esp-idf:11-30 . The global (weak) dispatcher `_ulp_riscv_interrupt_handler` reads `RTC_GPIO_STATUS_REG`, calls your per-pin handler, and clears all set status bits for you esp-idf:90-105 esp-idf:120-131 .

Reference the in-tree example `system/ulp/ulp_riscv/gpio_interrupt` (GPIO0 wake) and `system/ulp/ulp_riscv/interrupts` (SW + RTC IO interrupts) esp-idf:334-338 .

## Checklist — do / don't

| ✅ Do | ❌ Don't |
|---|---|
| Set `wakeup_source = ULP_RISCV_WAKEUP_SOURCE_GPIO` when you want event-mode; TIMER is the default and will periodically wake the ULP even if you don't want it esp-idf:32-35  | Don't leave `RTC_CNTL_ULP_CP_SLP_TIMER_EN` set — the ULP will keep powering up on the timer esp-idf:227-229  |
| Enable `CONFIG_ULP_RISCV_INTERRUPT_ENABLE` — `ulp_riscv_gpio_isr_register`/`ulp_riscv_intr_alloc` are compiled out without it esp-idf:17-17  | Don't call `ulp_riscv_gpio_isr_register` with a NULL handler or out-of-range pin/type — it returns `ESP_ERR_INVALID_ARG` esp-idf:13-23  |
| Mark every shared variable `volatile` and use the generated `ulp_*.h` header to access them from the main CPU esp-idf:153-171  | Don't read ULP `.bss`/`.data` variables before the first ULP run — sections aren't initialized until the binary loads esp-idf:173-177  |
| Use `ulp_riscv_lock_acquire`/`ulp_riscv_lock_release` (Peterson's algorithm) for mutual exclusion on shared state — but only from a single main-CPU thread esp-idf:182-189  | Don't access RTC peripherals (e.g., RTC I2C) from both cores simultaneously — there's no hardware atomicity protection esp-idf:257-259  |
| Keep ULP ISRs short; know there is **no nested interrupt support**, and only SW + RTC IO sources are implemented esp-idf:304-306  | Don't assume internal interrupts (timer/ebreak/unaligned) dispatch — `ULP_RISCV_INTERNAL_INTERRUPT` handling is a TODO in the driver esp-idf:114-117  |
| Call `ulp_set_wakeup_period()` only if you also want timer wakeups; call `esp_sleep_enable_ulp_wakeup()` before sleeping so ULP wakes the main CPU esp-idf:47-49 esp-idf:64-65  | Don't expect the main-CPU `ulp_riscv_isr_register` ISR to fire during deep sleep — it's only active while the main CPU is awake esp-idf:45-48  |
| Remember ULP symbols are exported as `uint32_t` (arrays `uint32_t[N]`); cast function symbols when needed esp-idf:159-161  | Don't forget `RTC_CNTL_COCPU_DONE` halts the ULP and re-arms the timer; in event mode decide explicitly whether your `main()` returns or loops esp-idf:225-229  |
| Debug via shared variables or the bit-banged UART TX driver; a ULP trap wakes the main CPU with `ESP_SLEEP_WAKEUP_COCPU_TRAP_TRIG` esp-idf:315-319  | Don't mask bugs by keeping the main CPU awake — some issues only appear when power domains are off esp-idf:315-315  |

## Notes

- The ULP interrupt API is still partial: only `ULP_RISCV_SW_INTR_SOURCE` + `ULP_RISCV_RTCIO0..21` sources exist in `ulp_riscv_interrupt_source_t` esp-idf:20-45 .
- `ulp_riscv_config_and_run` is target-gated to ESP32-S2/S3 in this codebase; the `ULP_RISCV_SW_INT`/`ULP_RISCV_TRAP_INT` masks are defined only for those targets esp-idf:113-164 esp-idf:38-43 .
- If you need custom dispatch, you can override the weak `_ulp_riscv_interrupt_handler` esp-idf:110-112 .

Wiki pages you might want to explore:
- [Timers, Logging, and System Utilities (espressif/esp-idf)](/wiki/espressif/esp-idf#3.6)
### Citations
**File:** docs/en/api-reference/system/ulp-risc-v.rst (L39-41)
```text
    ulp_embed_binary(${ulp_app_name} "${ulp_sources}" "${ulp_exp_dep_srcs}" TYPE riscv)

The first argument to ``ulp_embed_binary`` specifies the ULP binary name. The name specified here is also used by other generated artifacts such as the ELF file, map file, header file, and linker export file. The second argument specifies the ULP source files. The third argument specifies the list of component source files which include the header file to be generated. This list is needed to build the dependencies correctly and ensure that the generated header file is created before any of these files are compiled. Finally, The fourth argument ``TYPE`` is optional, but it must be provided as ``TYPE riscv`` to compile using risc-v toolchain, if both :ref:`CONFIG_ULP_COPROC_TYPE_FSM` and :ref:`CONFIG_ULP_COPROC_TYPE_RISCV` are selected in menu option ``ULP Coprocessor types``. See the sectio ... (truncated)
```
**File:** docs/en/api-reference/system/ulp-risc-v.rst (L109-113)
```text
To compile and build your project:

1. Enable :menuitem:`CONFIG_ULP_COPROC_ENABLED` and select :menuitem:`CONFIG_ULP_COPROC_TYPE_RISCV`. The :menuitem:`CONFIG_ULP_COPROC_RESERVE_MEM` option reserves RTC memory for the ULP, and must be set to a value big enough to store both the ULP RISC-V code and data. If the application components contain multiple ULP programs, then the size of the RTC memory must be sufficient to hold the largest one.

2. Build the application as usual (e.g., ``idf.py app``).
```
**File:** docs/en/api-reference/system/ulp-risc-v.rst (L153-171)
```text
The main program can access the global ULP RISC-V program variables as the build system makes this possible by generating the ``${ULP_APP_NAME}.h`` and ``${ULP_APP_NAME}.ld`` files which define the global symbols present in the ULP RISC-V program. Each global symbol defined in the ULP RISC-V program is included in these files and are prefixed with ``ulp_``.

The header file contains the declaration of the symbol:

.. code-block:: c

    extern uint32_t ulp_measurement_count;

Note that all symbols (variables, functions) are declared as ``uint32_t``. Arrays are declared as ``uint32_t [SIZE]``. For functions, take the address of the symbol and cast it to the appropriate type.

To access the ULP RISC-V program variables from the main program, the generated header file should be included using an ``include`` statement. This will allow the ULP RISC-V program variables to be accessed as regular variables.

.. code-block:: c

    #include "ulp_app_name.h"

    void init_ulp_vars() {
        ulp_measurement_count = 64;
    }
```
**File:** docs/en/api-reference/system/ulp-risc-v.rst (L173-177)
```text
.. note::

    - Variables declared in the global scope of the ULP RISC-V program reside in either the ``.bss`` or ``.data`` section of the binary. These sections are initialized when the ULP RISC-V binary is loaded and executed. Accessing these variables from the main program on the main CPU before the first ULP RISC-V run may result in undefined behavior.

    - The ``ulp_`` prefix is the default value. You can specify the prefix to use with ``ulp_embed_binary`` to avoid name collisions for multiple ULP programs.
```
**File:** docs/en/api-reference/system/ulp-risc-v.rst (L182-189)
```text
If mutual exclusion is needed when accessing a variable shared between the main program and ULP, then this can be achieved by using the ULP RISC-V lock API:

 * :cpp:func:`ulp_riscv_lock_acquire`
 * :cpp:func:`ulp_riscv_lock_release`

The ULP does not have any hardware instructions to facilitate mutual exclusion, so the lock API achieves this through a software algorithm (`Peterson's algorithm <https://en.wikipedia.org/wiki/Peterson%27s_algorithm>`_).

The locks are intended to only be called from a single thread in the main program, and will not provide mutual exclusion if used simultaneously from multiple threads.
```
**File:** docs/en/api-reference/system/ulp-risc-v.rst (L194-214)
```text
To run a ULP RISC-V program, the main application needs to load the ULP program into RTC memory using the :cpp:func:`ulp_riscv_load_binary` function, and then start it using the :cpp:func:`ulp_riscv_run` function.

Note that the :menuitem:`CONFIG_ULP_COPROC_ENABLED` and :menuitem:`CONFIG_ULP_COPROC_TYPE_RISCV` options must be enabled in menuconfig to work with ULP RISC-V. To reserve memory for the ULP, the ``RTC slow memory reserved for coprocessor`` option must be set to a value big enough to store ULP RISC-V code and data. If the application components contain multiple ULP programs, then the size of the RTC memory must be sufficient to hold the largest one.

Each ULP RISC-V program is embedded into the ESP-IDF application as a binary blob. The application can reference this blob and load it in the following way (suppose ULP_APP_NAME was defined to ``ulp_app_name``):

.. code-block:: c

    extern const uint8_t bin_start[] asm("_binary_ulp_app_name_bin_start");
    extern const uint8_t bin_end[]   asm("_binary_ulp_app_name_bin_end");

    void start_ulp_program() {
        ESP_ERROR_CHECK( ulp_riscv_load_binary( bin_start,
            (bin_end - bin_start)) );
    }

Once the program is loaded into RTC memory, the application can start it by calling the :cpp:func:`ulp_riscv_run` function:

.. code-block:: c

    ESP_ERROR_CHECK( ulp_riscv_run() );
```
**File:** docs/en/api-reference/system/ulp-risc-v.rst (L225-229)
```text
Once the timer counts the number of ticks set in the ``RTC_CNTL_ULP_CP_TIMER_1_REG`` register, the ULP RISC-V coprocessor will power up and start running the program from the entry point set in the call to :cpp:func:`ulp_riscv_run`.

The program runs until the field ``RTC_CNTL_COCPU_DONE`` in register ``RTC_CNTL_COCPU_CTRL_REG`` gets written or when a trap occurs due to illegal processor state. Once the program halts, the ULP RISC-V coprocessor will power down, and the timer will be started again.

To disable the timer (effectively preventing the ULP program from running again), please clear the ``RTC_CNTL_ULP_CP_SLP_TIMER_EN`` bit in the ``RTC_CNTL_ULP_CP_TIMER_REG`` register. This can be done both from the ULP code and from the main program.
```
**File:** docs/en/api-reference/system/ulp-risc-v.rst (L257-259)
```text
.. note::

    There is no hardware atomicity protection in accessing the RTC I2C peripheral between the main CPU and the ULP RISC-V core. Therefore, care must be taken that both cores are not accessing the peripheral simultaneously.
```
**File:** docs/en/api-reference/system/ulp-risc-v.rst (L304-306)
```text
All interrupts are enabled globally during start-up. When an interrupt occurs, the processor jumps to the IRQ vector. The IRQ vector performs the task of saving the register context and then calling the global interrupt dispatcher. The ULP RISC-V driver implements a *weak* interrupt dispatcher :cpp:func:`_ulp_riscv_interrupt_handler` which serves as the central point for handling all interrupts. This global dispatcher calls respective interrupt handlers which have been allocated via the :cpp:func:`ulp_riscv_intr_alloc`.

Interrupt handling on the ULP RISC-V is not fully featured yet. At present, interrupt handling for internal interrupt sources is not supported. Support is provided for two RTC peripheral sources, viz., software-triggered interrupts and RTC IO-triggered interrupts. ULP RISC-V does not support nested interrupts. If users need custom interrupt handling then they may override the default global interrupt dispatcher by defining their own :cpp:func:`_ulp_riscv_interrupt_handler`.
```
**File:** docs/en/api-reference/system/ulp-risc-v.rst (L315-319)
```text
 * Share program state through shared variables: as described in :ref:`ulp-riscv-access-variables`, both the main CPU and the ULP core can easily access global variables in RTC memory. Writing state information to such a variable from the ULP and reading it from the main CPU can help you discern what is happening on the ULP core. The downside of this approach is that it requires the main CPU to be awake, which will not always be the case. Keeping the main CPU awake might even, in some cases, mask problems, as some issues may only occur when certain power domains are powered down.

 * Use the bit-banged UART driver to print: the ULP RISC-V component comes with a low-speed bit-banged UART TX driver that can be used for printing information independently of the main CPU state. See :example:`system/ulp/ulp_riscv/uart_print` for an example of how to use this driver.

 * Trap signal: the ULP RISC-V has a hardware trap that will trigger under certain conditions, e.g., illegal instruction. This will cause the main CPU to be woken up with the wake-up cause :cpp:enumerator:`ESP_SLEEP_WAKEUP_COCPU_TRAP_TRIG`.
```
**File:** docs/en/api-reference/system/ulp-risc-v.rst (L334-338)
```text
* :example:`system/ulp/ulp_riscv/interrupts` demonstrates how the ULP-RISC-V coprocessor can register and handle software and RTC IO triggered interrupts, keeping a count of the software interrupts and waking up the main processor from deep sleep after a certain threshold or when a button is pressed.

* :example:`system/ulp/ulp_riscv/adc` demonstrates how to use the ULP-RISC-V coprocessor to periodically measure input voltage and wake up the system from deep sleep if the voltage exceeds a set threshold.

* :example:`system/ulp/ulp_riscv/gpio_interrupt` demonstrates how to program the ULP-RISC-V coprocessor to wake up from a RTC IO interrupt using GPIO0 as the input signal, and how to configure and run the coprocessor, putting the chip into deep sleep mode until the wakeup source pin is pulled low.
```
**File:** components/ulp/ulp_riscv/ulp_riscv.c (L87-107)
```c
static esp_err_t ulp_riscv_config_wakeup_source(ulp_riscv_wakeup_source_t wakeup_source)
{
    esp_err_t ret = ESP_OK;

    switch (wakeup_source) {
    case ULP_RISCV_WAKEUP_SOURCE_TIMER:
        /* start ULP_TIMER */
        CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_CTRL_REG, RTC_CNTL_ULP_CP_FORCE_START_TOP);
        SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN);
        break;

    case ULP_RISCV_WAKEUP_SOURCE_GPIO:
        SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);
        break;

    default:
        ret = ESP_ERR_INVALID_ARG;
    }

    return ret;
}
```
**File:** components/ulp/ulp_riscv/ulp_riscv.c (L113-164)
```c
#if CONFIG_IDF_TARGET_ESP32S2
    /* Reset COCPU when power on. */
    SET_PERI_REG_MASK(RTC_CNTL_COCPU_CTRL_REG, RTC_CNTL_COCPU_SHUT_RESET_EN);

    /* The coprocessor cpu trap signal doesn't have a stable reset value,
      force ULP-RISC-V clock on to stop RTC_COCPU_TRAP_TRIG_EN from waking the CPU*/
    SET_PERI_REG_MASK(RTC_CNTL_COCPU_CTRL_REG, RTC_CNTL_COCPU_CLK_FO);

    /* Disable ULP timer */
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN);
    /* wait for at least 1 RTC_SLOW_CLK cycle */
    esp_rom_delay_us(20);
    /* Select RISC-V as the ULP_TIMER trigger target. */
    CLEAR_PERI_REG_MASK(RTC_CNTL_COCPU_CTRL_REG, RTC_CNTL_COCPU_SEL);

    /* Select ULP-RISC-V to send the DONE signal. */
    SET_PERI_REG_MASK(RTC_CNTL_COCPU_CTRL_REG, RTC_CNTL_COCPU_DONE_FORCE);

    ret = ulp_riscv_config_wakeup_source(cfg->wakeup_source);

#elif CONFIG_IDF_TARGET_ESP32S3
    /* Reset COCPU when power on. */
    SET_PERI_REG_MASK(RTC_CNTL_COCPU_CTRL_REG, RTC_CNTL_COCPU_SHUT_RESET_EN);

    /* The coprocessor cpu trap signal doesn't have a stable reset value,
      force ULP-RISC-V clock on to stop RTC_COCPU_TRAP_TRIG_EN from waking the CPU*/
    SET_PERI_REG_MASK(RTC_CNTL_COCPU_CTRL_REG, RTC_CNTL_COCPU_CLK_FO);

    /* Disable ULP timer */
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN);
    /* wait for at least 1 RTC_SLOW_CLK cycle */
    esp_rom_delay_us(20);

    /* Select ULP-RISC-V to send the DONE signal */
    SET_PERI_REG_MASK(RTC_CNTL_COCPU_CTRL_REG, RTC_CNTL_COCPU_DONE_FORCE);

    /* Set the CLKGATE_EN signal */
    SET_PERI_REG_MASK(RTC_CNTL_COCPU_CTRL_REG, RTC_CNTL_COCPU_CLKGATE_EN);

    ret = ulp_riscv_config_wakeup_source(cfg->wakeup_source);

    /* Select RISC-V as the ULP_TIMER trigger target
     * Selecting the RISC-V as the Coprocessor at the end is a workaround
     * for the hang issue recorded in IDF-4510.
     */
    CLEAR_PERI_REG_MASK(RTC_CNTL_COCPU_CTRL_REG, RTC_CNTL_COCPU_SEL);

    /* Clear any spurious wakeup trigger interrupts upon ULP startup */
    esp_rom_delay_us(20);
    REG_WRITE(RTC_CNTL_INT_CLR_REG, RTC_CNTL_COCPU_INT_CLR | RTC_CNTL_COCPU_TRAP_INT_CLR | RTC_CNTL_ULP_CP_INT_CLR);

#endif
```
**File:** components/ulp/ulp_riscv/include/ulp_riscv.h (L19-35)
```text
typedef enum {
    ULP_RISCV_WAKEUP_SOURCE_TIMER,
    ULP_RISCV_WAKEUP_SOURCE_GPIO,
} ulp_riscv_wakeup_source_t;

/**
 * @brief ULP riscv init parameters
 *
 */
typedef struct {
    ulp_riscv_wakeup_source_t wakeup_source; /*!< ULP wakeup source */
} ulp_riscv_cfg_t;

#define ULP_RISCV_DEFAULT_CONFIG()                      \
    {                                                   \
        .wakeup_source = ULP_RISCV_WAKEUP_SOURCE_TIMER, \
    }
```
**File:** components/ulp/ulp_riscv/include/ulp_riscv.h (L38-43)
```text
#if (CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32S3)
#define ULP_RISCV_SW_INT    (BIT(13))   // Corresponds to RTC_CNTL_COCPU_INT_ST_M interrupt status bit
#define ULP_RISCV_TRAP_INT  (BIT(17))   // Corresponds to RTC_CNTL_COCPU_TRAP_INT_ST_M interrupt status bit
#else
#error "ULP_RISCV_SW_INT and ULP_RISCV_TRAP_INT are undefined. Please check soc/rtc_cntl_reg.h for the correct bitmap on your target SoC."
#endif /* (CONFIG_IDF_TARGET_ESP32S2 || CONFIG_IDF_TARGET_ESP32S3) */
```
**File:** components/ulp/ulp_riscv/include/ulp_riscv.h (L45-48)
```text
/**
 * @brief Register ULP signal ISR
 *
 * @note The ISR routine will only be active if the main CPU is not in deepsleep
```
**File:** components/ulp/subproject/components/ulp_riscv/ulp_riscv_gpio.c (L11-30)
```c
esp_err_t ulp_riscv_gpio_isr_register(gpio_num_t gpio_num, ulp_riscv_gpio_int_type_t intr_type, intr_handler_t handler, void *arg)
{
    if (gpio_num < 0 || gpio_num >= GPIO_NUM_MAX) {
        return ESP_ERR_INVALID_ARG;
    }

    if (intr_type < 0 || intr_type >= ULP_RISCV_GPIO_INTR_MAX) {
        return ESP_ERR_INVALID_ARG;
    }

    if (!handler) {
        return ESP_ERR_INVALID_ARG;
    }

    /* Set the interrupt type */
    REG_SET_FIELD(RTC_GPIO_PIN0_REG + 4 * gpio_num, RTC_GPIO_PIN0_INT_TYPE, intr_type);

    /* Set the interrupt handler */
    return ulp_riscv_intr_alloc(ULP_RISCV_RTCIO0_INTR_SOURCE + gpio_num, handler, arg);
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
**File:** components/ulp/subproject/components/ulp_riscv/ulp_riscv_interrupt.c (L110-112)
```c
void __attribute__((weak)) _ulp_riscv_interrupt_handler(uint32_t q1)
{
    /* Call respective interrupt handlers based on the interrupt status in q1 */
```
**File:** components/ulp/subproject/components/ulp_riscv/ulp_riscv_interrupt.c (L114-117)
```c
    /* Internal Interrupts */
    if (q1 & ULP_RISCV_INTERNAL_INTERRUPT) {
        // TODO
    }
```
**File:** components/ulp/subproject/components/ulp_riscv/ulp_riscv_interrupt.c (L120-131)
```c
    if (q1 & ULP_RISCV_PERIPHERAL_INTERRUPT) {
        /* RTC Peripheral interrupts */
        uint32_t cocpu_int_st = READ_PERI_REG(SENS_SAR_COCPU_INT_ST_REG);
        if (cocpu_int_st) {
            ulp_riscv_handle_rtc_periph_intr(cocpu_int_st);
        }

        /* RTC IO interrupts */
        uint32_t rtcio_int_st = REG_GET_FIELD(RTC_GPIO_STATUS_REG, RTC_GPIO_STATUS_INT);
        if (rtcio_int_st) {
            ulp_riscv_handle_rtc_io_intr(rtcio_int_st);
        }
```
**File:** components/ulp/subproject/components/ulp_riscv/include/ulp_riscv_interrupt.h (L17-17)
```text
#if CONFIG_ULP_RISCV_INTERRUPT_ENABLE
```
**File:** components/ulp/subproject/components/ulp_riscv/include/ulp_riscv_interrupt.h (L20-45)
```text
typedef enum {
    ULP_RISCV_SW_INTR_SOURCE = 0,           /**< Interrupt triggered by SW */
    ULP_RISCV_RTCIO0_INTR_SOURCE,           /**< Interrupt triggered by RTCIO 0 */
    ULP_RISCV_RTCIO1_INTR_SOURCE,           /**< Interrupt triggered by RTCIO 1 */
    ULP_RISCV_RTCIO2_INTR_SOURCE,           /**< Interrupt triggered by RTCIO 2 */
    ULP_RISCV_RTCIO3_INTR_SOURCE,           /**< Interrupt triggered by RTCIO 3 */
    ULP_RISCV_RTCIO4_INTR_SOURCE,           /**< Interrupt triggered by RTCIO 4 */
    ULP_RISCV_RTCIO5_INTR_SOURCE,           /**< Interrupt triggered by RTCIO 5 */
    ULP_RISCV_RTCIO6_INTR_SOURCE,           /**< Interrupt triggered by RTCIO 6 */
    ULP_RISCV_RTCIO7_INTR_SOURCE,           /**< Interrupt triggered by RTCIO 7 */
    ULP_RISCV_RTCIO8_INTR_SOURCE,           /**< Interrupt triggered by RTCIO 8 */
    ULP_RISCV_RTCIO9_INTR_SOURCE,           /**< Interrupt triggered by RTCIO 9 */
    ULP_RISCV_RTCIO10_INTR_SOURCE,          /**< Interrupt triggered by RTCIO 10 */
    ULP_RISCV_RTCIO11_INTR_SOURCE,          /**< Interrupt triggered by RTCIO 11 */
    ULP_RISCV_RTCIO12_INTR_SOURCE,          /**< Interrupt triggered by RTCIO 12 */
    ULP_RISCV_RTCIO13_INTR_SOURCE,          /**< Interrupt triggered by RTCIO 13 */
    ULP_RISCV_RTCIO14_INTR_SOURCE,          /**< Interrupt triggered by RTCIO 14 */
    ULP_RISCV_RTCIO15_INTR_SOURCE,          /**< Interrupt triggered by RTCIO 15 */
    ULP_RISCV_RTCIO16_INTR_SOURCE,          /**< Interrupt triggered by RTCIO 16 */
    ULP_RISCV_RTCIO17_INTR_SOURCE,          /**< Interrupt triggered by RTCIO 17 */
    ULP_RISCV_RTCIO18_INTR_SOURCE,          /**< Interrupt triggered by RTCIO 18 */
    ULP_RISCV_RTCIO19_INTR_SOURCE,          /**< Interrupt triggered by RTCIO 19 */
    ULP_RISCV_RTCIO20_INTR_SOURCE,          /**< Interrupt triggered by RTCIO 20 */
    ULP_RISCV_RTCIO21_INTR_SOURCE,          /**< Interrupt triggered by RTCIO 21 */
    ULP_RISCV_MAX_INTR_SOURCE,              /**< Total number of ULP RISC-V interrupt sources */
} ulp_riscv_interrupt_source_t;
```
**File:** components/ulp/test_apps/ulp_riscv/main/test_ulp_riscv.c (L47-49)
```c
        TEST_ASSERT(ulp_riscv_load_binary(ulp_bin, ulp_bin_len) == ESP_OK);
        TEST_ASSERT(ulp_set_wakeup_period(0, ULP_WAKEUP_PERIOD) == ESP_OK);
        TEST_ASSERT(ulp_riscv_run() == ESP_OK);
```
**File:** components/ulp/test_apps/ulp_riscv/main/test_ulp_riscv.c (L64-65)
```c
    /* Setup wakeup triggers */
    TEST_ASSERT(esp_sleep_enable_ulp_wakeup() == ESP_OK);
```
## Q2
i cant wake the riscv from sleep on gpio edge transition?
### Answer
Yes — edge wake is supported, but it only works if several pieces line up: the pin must be an RTC IO configured with an RTC interrupt type, `ULP_RISCV_WAKEUP_SOURCE_GPIO` must be set, and critically **the ULP must have actually powered down** — a GPIO event restarts the ULP from its entry point; it does not "interrupt" a still-running or still-powered core.

---

## How the GPIO wake path works

`ULP_RISCV_WAKEUP_SOURCE_GPIO` only sets `RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA` esp-idf:87-107 . The RTC IO hardware then watches `RTC_GPIO_PINx_INT_TYPE` — which `ulp_riscv_gpio_isr_register` writes — and a matching event powers up the ULP, which re-runs from the entry point and then dispatches the pending interrupt via `_ulp_riscv_interrupt_handler` esp-idf:11-30 esp-idf:120-131 .

## Likely reasons it isn't firing

1. **The ULP never went to sleep.** The core only powers down when `RTC_CNTL_COCPU_DONE` is written (i.e., your ULP `main()` returns/halt path runs); if your previous run is still looping or never ran, the GPIO edge can't "wake" anything esp-idf:225-229 . So your ULP `main()` should register the ISR and return — not `while(1)` — so the next edge starts a fresh run.

2. **Pin not set up as RTC input.** You need `ulp_riscv_gpio_init()` (sets `RTC_IO_TOUCH_PAD0_MUX_SEL`/`FUN_SEL`) plus `ulp_riscv_gpio_input_enable()` (`FUN_IE`) before registering the ISR esp-idf:37-64 .

3. **Interrupt support not compiled in.** `ulp_riscv_gpio_isr_register` is entirely gated behind `CONFIG_ULP_RISCV_INTERRUPT_ENABLE` esp-idf:10-30 .

4. **Stale status bits.** The dispatcher clears `RTC_GPIO_STATUS` via W1TC *after* handlers run esp-idf:90-105 . If a level-triggered source is still asserted (e.g., line still low/high), the status re-latches and you can get a spurious immediate re-wake — or with edge type, a stale edge latched before sleep can cause issues on targets with an edge-wakeup latch (see `rtcio_ll_clear_edge_wakeup_latch`) esp-idf:358-366 .

5. **Edge type vs. level type.** For waking the *ULP*, edge types are fine — `ULP_RISCV_GPIO_INTR_POSEDGE`/`NEGEDGE`/`ANYEDGE` exist in `ulp_riscv_gpio_int_type_t` esp-idf:22-30 . But note: on-chip main-CPU `gpio_wakeup_enable` rejects edge types ("only supports level mode") — don't confuse the two paths esp-idf:684-713 . Also the wakeup pulse must persist ≥3 RTC_SLOW_CLK cycles to be reliably sampled esp-idf:406-407 .

6. **Non-RTC pin.** The wake comes through the RTC IO subsystem — the pin must be an RTC GPIO, not a regular digital GPIO.

## Minimal working ULP pattern

```c
volatile uint32_t edge_count;

static void gpio_isr(void *arg) { edge_count++; }

int main(void)
{
    ulp_riscv_gpio_init(GPIO_NUM_0);          /* if first boot, else re-arm */
    ulp_riscv_gpio_input_enable(GPIO_NUM_0);
    ulp_riscv_gpio_isr_register(GPIO_NUM_0,
                                ULP_RISCV_GPIO_INTR_NEGEDGE,
                                gpio_isr, NULL);
    return 0;   /* COCPU_DONE → power down → next edge restarts us */
}
```

Note a subtlety: since the GPIO wake restarts from `main()`, your ISR registration runs each wake — that's expected in this model.

## Notes

- This GPIO-wake path is only wired up for ESP32-S2/S3 (`ulp_riscv_config_and_run` and the `ULP_RISCV_SW_INT`/`TRAP_INT` masks are `#if`'d to those targets) esp-idf:113-164 esp-idf:38-43 . On newer chips (C6/H4/C5/P4) use the LP-Core (`ulp_lp_core_gpio_wakeup_enable`, `ULP_LP_CORE_WAKEUP_SOURCE_LP_IO`) instead esp-idf:247-250 .
- The canonical reference is `system/ulp/ulp_riscv/gpio_interrupt` — it uses GPIO0 pulled **low** to trigger wake esp-idf:334-338 .
- If you tell me your target chip and which of the above steps you've done, I can narrow it down further.

Wiki pages you might want to explore:
- [Timers, Logging, and System Utilities (espressif/esp-idf)](/wiki/espressif/esp-idf#3.6)
- [Peripheral Drivers (espressif/esp-idf)](/wiki/espressif/esp-idf#6)
### Citations
**File:** components/ulp/subproject/components/ulp_riscv/ulp_riscv_gpio.c (L10-30)
```c
#if CONFIG_ULP_RISCV_INTERRUPT_ENABLE
esp_err_t ulp_riscv_gpio_isr_register(gpio_num_t gpio_num, ulp_riscv_gpio_int_type_t intr_type, intr_handler_t handler, void *arg)
{
    if (gpio_num < 0 || gpio_num >= GPIO_NUM_MAX) {
        return ESP_ERR_INVALID_ARG;
    }

    if (intr_type < 0 || intr_type >= ULP_RISCV_GPIO_INTR_MAX) {
        return ESP_ERR_INVALID_ARG;
    }

    if (!handler) {
        return ESP_ERR_INVALID_ARG;
    }

    /* Set the interrupt type */
    REG_SET_FIELD(RTC_GPIO_PIN0_REG + 4 * gpio_num, RTC_GPIO_PIN0_INT_TYPE, intr_type);

    /* Set the interrupt handler */
    return ulp_riscv_intr_alloc(ULP_RISCV_RTCIO0_INTR_SOURCE + gpio_num, handler, arg);
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
**File:** components/ulp/subproject/components/ulp_riscv/ulp_riscv_interrupt.c (L120-131)
```c
    if (q1 & ULP_RISCV_PERIPHERAL_INTERRUPT) {
        /* RTC Peripheral interrupts */
        uint32_t cocpu_int_st = READ_PERI_REG(SENS_SAR_COCPU_INT_ST_REG);
        if (cocpu_int_st) {
            ulp_riscv_handle_rtc_periph_intr(cocpu_int_st);
        }

        /* RTC IO interrupts */
        uint32_t rtcio_int_st = REG_GET_FIELD(RTC_GPIO_STATUS_REG, RTC_GPIO_STATUS_INT);
        if (rtcio_int_st) {
            ulp_riscv_handle_rtc_io_intr(rtcio_int_st);
        }
```
**File:** docs/en/api-reference/system/ulp-risc-v.rst (L225-229)
```text
Once the timer counts the number of ticks set in the ``RTC_CNTL_ULP_CP_TIMER_1_REG`` register, the ULP RISC-V coprocessor will power up and start running the program from the entry point set in the call to :cpp:func:`ulp_riscv_run`.

The program runs until the field ``RTC_CNTL_COCPU_DONE`` in register ``RTC_CNTL_COCPU_CTRL_REG`` gets written or when a trap occurs due to illegal processor state. Once the program halts, the ULP RISC-V coprocessor will power down, and the timer will be started again.

To disable the timer (effectively preventing the ULP program from running again), please clear the ``RTC_CNTL_ULP_CP_SLP_TIMER_EN`` bit in the ``RTC_CNTL_ULP_CP_TIMER_REG`` register. This can be done both from the ULP code and from the main program.
```
**File:** docs/en/api-reference/system/ulp-risc-v.rst (L334-338)
```text
* :example:`system/ulp/ulp_riscv/interrupts` demonstrates how the ULP-RISC-V coprocessor can register and handle software and RTC IO triggered interrupts, keeping a count of the software interrupts and waking up the main processor from deep sleep after a certain threshold or when a button is pressed.

* :example:`system/ulp/ulp_riscv/adc` demonstrates how to use the ULP-RISC-V coprocessor to periodically measure input voltage and wake up the system from deep sleep if the voltage exceeds a set threshold.

* :example:`system/ulp/ulp_riscv/gpio_interrupt` demonstrates how to program the ULP-RISC-V coprocessor to wake up from a RTC IO interrupt using GPIO0 as the input signal, and how to configure and run the coprocessor, putting the chip into deep sleep mode until the wakeup source pin is pulled low.
```
**File:** components/ulp/subproject/components/ulp_riscv/include/ulp_riscv_gpio.h (L22-30)
```text
typedef enum {
    ULP_RISCV_GPIO_INTR_DISABLE = 0,    /*!< Disable RTC GPIO interrupt                             */
    ULP_RISCV_GPIO_INTR_POSEDGE = 1,    /*!< RTC GPIO interrupt type : rising edge                  */
    ULP_RISCV_GPIO_INTR_NEGEDGE = 2,    /*!< RTC GPIO interrupt type : falling edge                 */
    ULP_RISCV_GPIO_INTR_ANYEDGE = 3,    /*!< RTC GPIO interrupt type : both rising and falling edge */
    ULP_RISCV_GPIO_INTR_LOW_LEVEL = 4,  /*!< RTC GPIO interrupt type : input low level trigger      */
    ULP_RISCV_GPIO_INTR_HIGH_LEVEL = 5, /*!< RTC GPIO interrupt type : input high level trigger     */
    ULP_RISCV_GPIO_INTR_MAX
} ulp_riscv_gpio_int_type_t;
```
**File:** components/ulp/subproject/components/ulp_riscv/include/ulp_riscv_gpio.h (L37-64)
```text
static inline void ulp_riscv_gpio_init(gpio_num_t gpio_num)
{
#if SOC_LP_IO_CLOCK_IS_INDEPENDENT
    rtcio_ll_enable_io_clock(true);
#endif
    SET_PERI_REG_MASK(RTC_IO_TOUCH_PAD0_REG + gpio_num * 4, RTC_IO_TOUCH_PAD0_MUX_SEL);
    REG_SET_FIELD(RTC_IO_TOUCH_PAD0_REG + gpio_num * 4, RTC_IO_TOUCH_PAD0_FUN_SEL, 0);
}

static inline void ulp_riscv_gpio_deinit(gpio_num_t gpio_num)
{
    CLEAR_PERI_REG_MASK(RTC_IO_TOUCH_PAD0_REG + gpio_num * 4, RTC_IO_TOUCH_PAD0_MUX_SEL);
}

static inline void ulp_riscv_gpio_output_enable(gpio_num_t gpio_num)
{
    REG_SET_FIELD(RTC_GPIO_ENABLE_W1TS_REG, RTC_GPIO_ENABLE_W1TS, BIT(gpio_num));
}

static inline void ulp_riscv_gpio_output_disable(gpio_num_t gpio_num)
{
    REG_SET_FIELD(RTC_GPIO_ENABLE_W1TC_REG, RTC_GPIO_ENABLE_W1TC, BIT(gpio_num));
}

static inline void ulp_riscv_gpio_input_enable(gpio_num_t gpio_num)
{
    SET_PERI_REG_MASK(RTC_IO_TOUCH_PAD0_REG + gpio_num * 4, RTC_IO_TOUCH_PAD0_FUN_IE);
}
```
**File:** components/esp_hal_gpio/esp32s31/include/hal/rtc_io_ll.h (L358-366)
```text
/**
 * Clear edge-wakeup latch.
 *
 * @param rtcio_num The index of rtcio. 0 ~ MAX(rtcio).
 */
static inline void rtcio_ll_clear_edge_wakeup_latch(int rtcio_num)
{
    LP_GPIO.pinn[rtcio_num].pinn_edge_wakeup_clr = 1;
}
```
**File:** components/esp_driver_gpio/src/gpio.c (L684-713)
```c
esp_err_t gpio_wakeup_enable(gpio_num_t gpio_num, gpio_int_type_t intr_type)
{
    GPIO_CHECK(GPIO_IS_VALID_GPIO(gpio_num), "GPIO number error", ESP_ERR_INVALID_ARG);
    esp_err_t ret = ESP_OK;

    if ((intr_type == GPIO_INTR_LOW_LEVEL) || (intr_type == GPIO_INTR_HIGH_LEVEL)) {
#if SOC_RTCIO_WAKE_SUPPORTED
        if (rtc_gpio_is_valid_gpio(gpio_num)) {
#if SOC_LP_IO_CLOCK_IS_INDEPENDENT
            // LP_IO Wake-up function does not depend on LP_IO Matrix, but uses its clock to
            // sample the wake-up signal, we need to enable the LP_IO clock here.
            io_mux_enable_lp_io_clock(gpio_num, true);
#endif
            ret = rtc_gpio_wakeup_enable(gpio_num, intr_type);
        }
#endif
        portENTER_CRITICAL(&gpio_context.gpio_spinlock);
        gpio_hal_set_intr_type(gpio_context.gpio_hal, gpio_num, intr_type);
        gpio_hal_wakeup_enable(gpio_context.gpio_hal, gpio_num);
#if CONFIG_ESP_SLEEP_GPIO_RESET_WORKAROUND || CONFIG_PM_SLP_DISABLE_GPIO
        gpio_hal_sleep_sel_dis(gpio_context.gpio_hal, gpio_num);
#endif
        portEXIT_CRITICAL(&gpio_context.gpio_spinlock);
    } else {
        ESP_LOGE(GPIO_TAG, "GPIO wakeup only supports level mode, but edge mode set. gpio_num:%u", gpio_num);
        ret = ESP_ERR_INVALID_ARG;
    }

    return ret;
}
```
**File:** docs/zh_CN/api-reference/system/sleep_modes.rst (L406-407)
```text
    .. note::
        使用 IO 唤醒源（无论是电平模式还是边沿模式）将芯片从睡眠中唤醒时，唤醒信号必须保持（电平模式）或脉冲宽度（边沿模式）至少 3 个 RTC 慢时钟周期，唤醒逻辑才能可靠采样。一个慢时钟周期的时长取决于 :menuitem:`CONFIG_RTC_CLK_SRC` 的配置（例如 RC_SLOW @ ~136 kHz ≈ 7.4 µs/周期，XTAL32K @ 32.768 kHz ≈ 30.5 µs/周期）。该约束同样适用于 :cpp:func:`esp_sleep_enable_gpio_wakeup` 和 :cpp:func:`esp_sleep_enable_gpio_wakeup_on_hp_periph_powerdown`。
```
**File:** components/ulp/subproject/components/lp_core/include/ulp_lp_core_gpio.h (L247-250)
```text
static inline void ulp_lp_core_gpio_wakeup_enable(lp_io_num_t lp_io_num, gpio_int_type_t intr_type)
{
    rtcio_ll_wakeup_enable(lp_io_num, intr_type);
}
```
## Q3
i cant wake the riscv from sleep on gpio edge transition?
*Codemap generation in progress or failed to parse*