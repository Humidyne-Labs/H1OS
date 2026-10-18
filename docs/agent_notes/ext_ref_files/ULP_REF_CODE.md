Yes — below is a complete skeleton split into the main-app part and the ULP part, modeled on the `system/ulp/ulp_riscv/gpio_interrupt` example [1](#1-0) .

---

## Main app (`main.c`)

The two wake sources are armed separately: `ULP_RISCV_WAKEUP_SOURCE_GPIO` sets `RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA`, and you must add `RTC_CNTL_ULP_CP_SLP_TIMER_EN` yourself since `ulp_riscv_config_wakeup_source` only sets one bit [2](#1-1) .

```c
#include "ulp_riscv.h"
#include "ulp_riscv_gpio.h"          /* actually used inside ULP; here for types */
#include "driver/rtc_io.h"
#include "ulp/ulp_riscv/include/ulp_riscv_utils.h"
#include "soc/rtc_cntl_reg.h"

extern const uint8_t ulp_bin_start[] asm("_binary_ulp_main_bin_start");
extern const uint8_t ulp_bin_end[]   asm("_binary_ulp_main_bin_end");

/* shared with ULP program (both sides see these) */
volatile uint32_t ulp_gpio_wake_count;
volatile uint32_t ulp_timer_wake_count;
volatile uint32_t ulp_last_gpio_status;

#define TIMER_PERIOD_S   60
#define RTC_SLOW_CLK_HZ  136000   /* ~136 kHz on S3, ~90 kHz on S2; use RTC_SLOW_CLK_FREQ_xxx or measure */

static void init_ulp_gpio_wakeup(gpio_num_t io)
{
    /* io here must be the RTCIO number (see Notes) */
    rtc_gpio_init(io);
    rtc_gpio_set_direction(io, RTC_GPIO_MODE_INPUT_ONLY);
    rtc_gpio_pulldown_dis(io);
    rtc_gpio_pullup_dis(io);
    rtc_gpio_hold_en(io);                  /* keep config during sleep */

    /* wake type: e.g. low-level keeps GPIO0 (boot pin) happy */
    esp_sleep_enable_ulp_gpio_wakeup();
}

void app_main(void)
{
    ulp_gpio_wake_count = ulp_timer_wake_count = ulp_last_gpio_status = 0;

    init_ulp_gpio_wakeup(GPIO_NUM_0);
    init_ulp_gpio_wakeup(GPIO_NUM_18);     /* RTCIO index, see Notes */
    init_ulp_gpio_wakeup(GPIO_NUM_5);

    ulp_riscv_load_binary(ulp_bin_start, (ulp_bin_end - ulp_bin_start));

    /* 60 s periodic wake */
    ulp_set_wakeup_period(0, TIMER_PERIOD_S * RTC_SLOW_CLK_HZ);   /* RTC_CNTL_ULP_CP_TIMER_1_REG */

    ulp_riscv_cfg_t cfg = { .wakeup_source = ULP_RISCV_WAKEUP_SOURCE_GPIO };
    ulp_riscv_config_and_run(&cfg);          /* sets GPIO_WAKEUP_ENA */

    /* additionally arm the sleep timer for periodic wakes */
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN);

    esp_deep_sleep_start();
}
```

Timer mechanics: `ulp_set_wakeup_period` programs `RTC_CNTL_ULP_CP_TIMER_1_REG`; when the count elapses the core powers up at the entry point, and after the program writes `RTC_CNTL_COCPU_DONE` it powers down and the timer restarts — giving you the periodic behavior for free [3](#1-2) .

## ULP app (`ulp/ulp_main.c`)

GPIO wakes arrive as RTC peripheral IRQ 31; `ulp_riscv_gpio_isr_register` sets the pin's `RTC_GPIO_PIN0_INT_TYPE` and binds a handler per RTCIO index [4](#1-3) .

```c
#include "ulp_riscv.h"
#include "ulp_riscv_utils.h"
#include "ulp_riscv_gpio.h"
#include "ulp_riscv_interrupt.h"
#include "soc/rtc_io_reg.h"

extern volatile uint32_t ulp_gpio_wake_count;
extern volatile uint32_t ulp_timer_wake_count;
extern volatile uint32_t ulp_last_gpio_status;

#define RTCIO0   0
#define RTCIO5   5
#define RTCIO18  18        /* verify mapping for your chip! */

static volatile bool gpio_fired[3];

/* ISR context: just flag it, respond in main() */
static void gpio0_isr(void *arg)  { gpio_fired[0] = true; }
static void gpio5_isr(void *arg)  { gpio_fired[1] = true; }
static void gpio18_isr(void *arg) { gpio_fired[2] = true; }

int main(void)
{
    /* snapshot which pins caused the wake (0 => timer wake) */
    uint32_t st = REG_GET_FIELD(RTC_GPIO_STATUS_REG, RTC_GPIO_STATUS_INT);
    ulp_last_gpio_status = st;

    if (st) {
        ulp_gpio_wake_count++;
        /* drain any edge events via registered handlers while running */
        ulp_riscv_gpio_isr_register(RTCIO0,  ULP_RISCV_GPIO_INTR_ANYEDGE, gpio0_isr,  NULL);
        ulp_riscv_gpio_isr_register(RTCIO5,  ULP_RISCV_GPIO_INTR_ANYEDGE, gpio5_isr,  NULL);
        ulp_riscv_gpio_isr_register(RTCIO18, ULP_RISCV_GPIO_INTR_ANYEDGE, gpio18_isr, NULL);

        for (int i = 0; i < 3; i++) {
            if (gpio_fired[i]) {
                gpio_fired[i] = false;
                /* respond: e.g. set flag / wake main CPU */
            }
        }
        ulp_riscv_gpio_wakeup_clear();   /* clear RTC GPIO wake latch */
    } else {
        ulp_timer_wake_count++;          /* 60 s periodic tick response */
    }

    /* halt: writes RTC_CNTL_COCPU_DONE -> core powers down, timer re-arms */
    ulp_riscv_halt();
    return 0;
}
```

The dispatcher reads `RTC_GPIO_STATUS_REG`, calls the per-RTCIO handler, then clears via `RTC_GPIO_STATUS_W1TC` [5](#1-4) .

## Build (`CMakeLists.txt`)

```cmake
set(ulp_app_name ulp_${COMPONENT_NAME})
set(ulp_sources  "ulp/ulp_main.c")
set(ulp_exp_dep_srcs "main.c")
ulp_embed_binary(${ulp_app_name} "${ulp_sources}" "${ulp_exp_dep_srcs}" TYPE riscv)
```

In menuconfig enable `CONFIG_ULP_COPROC_ENABLED`, `CONFIG_ULP_COPROC_TYPE_RISCV`, `CONFIG_ULP_RISCV_INTERRUPT_ENABLE` (needed for `ulp_riscv_gpio_isr_register`/`ulp_riscv_intr_alloc`) [6](#1-5) , and reserve enough RTC slow memory.

## Notes

- **RTCIO vs GPIO numbering**: `ulp_riscv_gpio_isr_register` writes `RTC_GPIO_PIN0_REG + 4*gpio_num` and `ULP_RISCV_RTCIO0_INTR_SOURCE + gpio_num` — i.e., the argument is the RTCIO index, not the GPIO number. On ESP32-S3, GPIO18 is not RTCIO18; use `rtc_io_number_get()` or `soc/rtc_io_periph.h` to map. GPIO0 maps to RTCIO0 on S2; verify per target. This only exists on S2/S3 [7](#1-6) .
- **Interrupt types**: use `ULP_RISCV_GPIO_INTR_LOW_LEVEL`/`HIGH_LEVEL` for wake-from-halt; edges work once the core is already running [8](#1-7) . GPIO0 is the boot strap pin — avoid `HIGH_LEVEL` wake if it must stay low at boot.
- `ulp_riscv_halt()` name is illustrative — the actual mechanism is setting `RTC_CNTL_COCPU_DONE` [9](#1-8) ; check `ulp_riscv_utils.h` for the helper your IDF version exposes.

Wiki pages you might want to explore:
- [Timers, Logging, and System Utilities (espressif/esp-idf)](/wiki/espressif/esp-idf#3.6)

### Citations

**File:** docs/en/api-reference/system/ulp-risc-v.rst (L221-229)
```text
The ULP RISC-V coprocessor is started by a timer. The timer is started once :cpp:func:`ulp_riscv_run` is called. The timer counts the number of RTC_SLOW_CLK ticks (by default, produced by an internal {IDF_TARGET_RTC_CLK_FRE} RC oscillator). The number of ticks is set using ``RTC_CNTL_ULP_CP_TIMER_1_REG`` register. When starting the ULP, ``RTC_CNTL_ULP_CP_TIMER_1_REG`` will be used to set the number of timer ticks.

The application can set ULP timer period values (RTC_CNTL_ULP_CP_TIMER_1_REG) using the :cpp:func:`ulp_set_wakeup_period` function.

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

**File:** components/ulp/subproject/components/ulp_riscv/include/ulp_riscv_interrupt.h (L17-45)
```text
#if CONFIG_ULP_RISCV_INTERRUPT_ENABLE

/* ULP RISC-V Interrupt sources */
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
