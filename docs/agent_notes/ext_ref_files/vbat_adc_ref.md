Use `ulp_adc_init()` from `ulp_adc.h` — it wraps the oneshot driver with `ulp_mode = ADC_ULP_MODE_RISCV`, which is what makes the channel config persist for ULP use. In the ULP, you then read with `ulp_riscv_adc_read_channel()`.

---

## Main app init (call once at boot)

```c
#include "ulp_adc.h"

ulp_adc_cfg_t adc_cfg = {
    .adc_n      = ADC_UNIT_1,
    .channel    = ADC_CHANNEL_x,   /* matches your analog GPIO */
    .atten      = ADC_ATTEN_DB_12, /* full ~3.1 V range */
    .width      = ADC_BITWIDTH_DEFAULT,
    .ulp_mode   = ADC_ULP_MODE_RISCV,
};
ESP_ERROR_CHECK(ulp_adc_init(&adc_cfg));
```

`ulp_adc_init()` builds an `adc_oneshot_unit_init_cfg_t` with your `ulp_mode` (defaulting to RISCV if you leave it `ADC_ULP_MODE_DISABLE`) and calls `adc_oneshot_new_unit()`, then `adc_oneshot_config_channel()` for the single channel [1](#2-0) . If you need more channels later, use `ulp_adc_config_channel()` on additional channels after init [2](#2-1) .

## Why `ulp_mode` matters

Two things inside `adc_oneshot_new_unit()` / `adc_oneshot_config_channel()` only happen in ULP mode:

- Instead of the normal power acquire, it calls `esp_sleep_sub_mode_config(ESP_SLEEP_USE_ADC_TSEN_MONITOR_MODE, true)`, which keeps the RTC voltage domain ≥0.9 V in deep sleep so the SAR ADC stays usable [3](#2-2) [4](#2-3) .
- `adc_oneshot_config_channel()` calls `adc_oneshot_hal_setup()` immediately when `handle->ulp_mode` is set, pre-loading the channel into the RTC-controlled registers the ULP path uses [5](#2-4) .

## ULP-side read

```c
int32_t raw = ulp_riscv_adc_read_channel(ADC_UNIT_1, ADC_CHANNEL_x); /* -1 on invalid */
```

This forces `ADC_LL_CTRL_RTC` control, starts the conversion, polls the done event, and returns the raw value — including a fix where deep-sleep entry can clear the channel bitmap [6](#2-5) .

## Ordering constraints

- Init the ADC **before** `ulp_riscv_config_and_run()` / entering deep sleep, so the calibration code (`adc_set_hw_calibration_code`) and channel setup are already in hardware [7](#2-6) .
- **ADC1 only.** ADC2 on S3 needs `sar2_rtc_force` switching for sleep mode; avoid it for ULP use [8](#2-7) .
- The ADC GPIO must stay routed to RTC/analog in sleep — same `rtc_gpio_init` treatment as your wake pins, minus the wakeup bits.
- Raw values only on ULP — voltage calibration runs on the main CPU side; on the ULP you compare against a threshold raw count (see `system/ulp/ulp_riscv/adc` example) [9](#2-8) .

## Notes

- `lp_core_lp_adc_init()` is the LP-Core variant (`ADC_ULP_MODE_LP_CORE`) on chips with `SOC_LP_ADC_SUPPORTED` — not the right API for ULP-RISC-V on S3 [10](#2-9) .
- Your earlier wake-pin fixes are orthogonal: the ADC pin doesn't need `RTC_GPIO_WAKEUP_ENABLE`, just the RTC pad routing.
- There's a working end-to-end test app at `components/ulp/test_apps/ulp_riscv/main/test_ulp_riscv.c` using `ulp_adc_init` + ULP reads [11](#2-10) .

Wiki pages you might want to explore:
- [Power Management and Sleep Modes (espressif/esp-idf)](/wiki/espressif/esp-idf#3.1)
- [Timers, Logging, and System Utilities (espressif/esp-idf)](/wiki/espressif/esp-idf#3.6)
- [Display, Camera, and Analog Peripherals (espressif/esp-idf)](/wiki/espressif/esp-idf#6.2)

### Citations

**File:** components/ulp/ulp_common/ulp_adc.c (L20-28)
```c
esp_err_t ulp_adc_config_channel(adc_unit_t adc_n, adc_channel_t channel, const ulp_adc_chan_cfg_t *chan_cfg)
{
    esp_err_t ret = ESP_OK;

    ESP_RETURN_ON_FALSE(chan_cfg, ESP_ERR_INVALID_ARG, TAG, "chan_cfg == NULL");
    ESP_RETURN_ON_FALSE(s_adc_handle, ESP_ERR_INVALID_STATE, TAG, "ADC unit not initialized");

    //-------------ADC Config---------------//
    ret = adc_oneshot_config_channel(s_adc_handle, channel, chan_cfg);
```

**File:** components/ulp/ulp_common/ulp_adc.c (L41-74)
```c
esp_err_t ulp_adc_init(const ulp_adc_cfg_t *cfg)
{
    esp_err_t ret = ESP_OK;

    ESP_RETURN_ON_FALSE(cfg, ESP_ERR_INVALID_ARG, TAG, "cfg == NULL");

    //-------------ADC1 Init---------------//
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = cfg->adc_n,
        .ulp_mode = cfg->ulp_mode,
    };

    if (init_config.ulp_mode == ADC_ULP_MODE_DISABLE) {
        /* Default to RISCV for backward compatibility */
        ESP_LOGI(TAG, "No ulp mode specified in cfg struct, default to riscv");
        init_config.ulp_mode = ADC_ULP_MODE_RISCV;
    }

    ret = adc_oneshot_new_unit(&init_config, &s_adc_handle);
    if (ret != ESP_OK) {
        return ret;
    }

    //-------------ADC Config---------------//
    adc_oneshot_chan_cfg_t config = {
        .bitwidth = cfg->width,
        .atten = cfg->atten,
    };
    ret = adc_oneshot_config_channel(s_adc_handle, cfg->channel, &config);
    if (ret != ESP_OK) {
        adc_oneshot_del_unit(s_adc_handle);
        s_adc_handle = NULL;
        return ret;
    }
```

**File:** components/ulp/ulp_common/ulp_adc.c (L77-79)
```c
#if SOC_ADC_CALIBRATION_V1_SUPPORTED
    adc_set_hw_calibration_code(cfg->adc_n, cfg->atten);
#endif
```

**File:** components/esp_adc/adc_oneshot.c (L160-169)
```c
    if (init_config->ulp_mode == ADC_ULP_MODE_DISABLE) {
        sar_periph_ctrl_adc_oneshot_power_acquire();
    } else {
#if SOC_ADC_DIG_CTRL_SUPPORTED && !SOC_ADC_RTC_CTRL_SUPPORTED
        ESP_GOTO_ON_ERROR(esp_clk_tree_acquire_src((soc_module_clk_t)(unit->hal.clk_src)), err, TAG, "clock source enable failed");
#endif
#if SOC_LIGHT_SLEEP_SUPPORTED || SOC_DEEP_SLEEP_SUPPORTED
        esp_sleep_sub_mode_config(ESP_SLEEP_USE_ADC_TSEN_MONITOR_MODE, true);
#endif
    }
```

**File:** components/esp_adc/adc_oneshot.c (L210-214)
```c
    portENTER_CRITICAL(&rtc_spinlock);
    adc_oneshot_hal_channel_config(hal, &cfg, channel);
    if (handle->ulp_mode) {
        adc_oneshot_hal_setup(hal, channel);
    }
```

**File:** components/esp_hw_support/port/esp32s2/rtc_sleep.c (L68-82)
```c
        if ((sleep_flags & RTC_SLEEP_USE_ADC_TESEN_MONITOR) || !(sleep_flags & RTC_SLEEP_PD_INT_8M)) {
            /*
             * rtc voltage in sleep mode >= 0.9v
             * if 8MD256 select as RTC slow clock src, only need dbg_atten_slp set to 0
             * Support all features:
             * - ADC/Temperature sensor in monitor mode (ULP) (also need pd_cur_monitor = 0)
             * - 8MD256 as RTC slow clock src
             * - RTC IO as input
             * - RTC Memory at high temperature
             * - ULP
             * - Touch sensor
             */
            out_config->rtc_regulator_fpu = 1;
            out_config->dbg_atten_slp = RTC_CNTL_DBG_ATTEN_DEEPSLEEP_NODROP;
            out_config->rtc_dbias_slp = RTC_CNTL_DBIAS_0V90;
```

**File:** components/ulp/subproject/components/ulp_riscv/ulp_riscv_adc.c (L9-32)
```c
int32_t ulp_riscv_adc_read_channel(adc_unit_t adc_n, int channel)
{
    uint32_t event = (adc_n == ADC_UNIT_1) ? ADC_LL_EVENT_ADC1_ONESHOT_DONE : ADC_LL_EVENT_ADC2_ONESHOT_DONE;
    adc_oneshot_ll_clear_event(event);
    adc_oneshot_ll_disable_all_unit();
    adc_oneshot_ll_enable(adc_n);
    /* Force SW control of the channel bitmap; deep-sleep entry can clear it, which would
     * otherwise make the channel selection below take no effect. */
    adc_ll_set_controller(adc_n, ADC_LL_CTRL_RTC);
    adc_oneshot_ll_set_channel(adc_n, channel);

    adc_oneshot_ll_start(adc_n);
    while (adc_oneshot_ll_get_event(event) != true) {
        ;
    }
    int32_t out_raw = adc_oneshot_ll_get_raw_result(adc_n);
    if (adc_oneshot_ll_raw_check_valid(adc_n, out_raw) == false) {
        return -1;
    }

    //HW workaround: when enabling periph clock, this should be false
    adc_oneshot_ll_disable_all_unit();

    return out_raw;
```

**File:** components/esp_hal_ana_conv/esp32s3/include/hal/adc_ll.h (L812-838)
```text
/**
 * Force switch ADC2 to RTC controller in sleep mode. Shield arbiter.
 * In sleep mode, the arbiter is in power-down mode.
 * Need to switch the controller to RTC to shield the control of the arbiter.
 * After waking up, it needs to switch to arbiter control.
 *
 * @note The hardware will do this automatically. In normal use, there is no need to call this interface to manually switch the controller.
 * @note Only support ADC2.
 */
static inline void adc_ll_enable_sleep_controller(void)
{
    SENS.sar_meas2_mux.sar2_rtc_force = 1;
}

/**
 * Force switch ADC2 to arbiter in wakeup mode.
 * In sleep mode, the arbiter is in power-down mode.
 * Need to switch the controller to RTC to shield the control of the arbiter.
 * After waking up, it needs to switch to arbiter control.
 *
 * @note The hardware will do this automatically. In normal use, there is no need to call this interface to manually switch the controller.
 * @note Only support ADC2.
 */
static inline void adc_ll_disable_sleep_controller(void)
{
    SENS.sar_meas2_mux.sar2_rtc_force = 0;
}
```

**File:** docs/en/api-reference/system/ulp-risc-v.rst (L336-336)
```text
* :example:`system/ulp/ulp_riscv/adc` demonstrates how to use the ULP-RISC-V coprocessor to periodically measure input voltage and wake up the system from deep sleep if the voltage exceeds a set threshold.
```

**File:** components/ulp/lp_core/shared/ulp_lp_core_lp_adc_shared.c (L55-77)
```c
esp_err_t lp_core_lp_adc_init(adc_unit_t unit_id)
{
    esp_err_t ret = lp_adc_validate_unit(unit_id);
    if (ret != ESP_OK) {
        return ret;
    }

#if IS_ULP_COCPU
    // Not supported from LP core
    return ESP_ERR_NOT_SUPPORTED;
#else
    /* LP ADC is being initialized from the HP core.
     * Hence, we use the standard ADC driver APIs here.
     */

    /* Initialize ADC */
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = unit_id,
        .ulp_mode = ADC_ULP_MODE_LP_CORE, // LP Core will use the ADC
    };

    return (adc_oneshot_new_unit(&init_config, &s_adc_unit_handles[unit_id]));
#endif /* IS_ULP_COCPU */
```

**File:** components/ulp/test_apps/ulp_riscv/main/test_ulp_riscv.c (L14-26)
```c
#include "ulp_riscv.h"
#include "ulp_riscv_lock.h"
#include "ulp_adc.h"
#include "ulp_test_app.h"
#include "ulp_test_app2.h"
#include "ulp_test_shared.h"
#include "unity.h"
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_adc/adc_oneshot.h"
#include "ulp_riscv_cpu_freq_shared.h"
```
