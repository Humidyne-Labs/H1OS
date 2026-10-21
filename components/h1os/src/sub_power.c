/**
 * @file sub_power.c
 * @brief Layer 2: Battery ADC monitoring, DFS, and sleep engine implementation
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "h1os/sub_power.h"

#include "driver/gpio.h"
#include "driver/rtc_io.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"
#include "esp_pm.h"
#include "esp_rom_sys.h"
#include "esp_sleep.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "h1os/hal_io.h"
#include "h1os/hal_types.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/rtc_io_reg.h"
#include "ulp_h1os.h"
#include "ulp_riscv.h"

#include <stdlib.h>

extern const uint8_t ulp_h1os_bin_start[] asm("_binary_ulp_h1os_bin_start");
extern const uint8_t ulp_h1os_bin_end[] asm("_binary_ulp_h1os_bin_end");

static const char *TAG = "sub_power";

static adc_oneshot_unit_handle_t s_adc_handle = NULL;
static adc_cali_handle_t s_cali_handle = NULL;
static bool s_cali_valid = false;

static uint32_t s_flow_a_sec     = 60;
static uint32_t s_flow_b_sec     = 300;
static uint32_t s_overflow_limit = 5;
static uint32_t s_remainder_sec  = 0;

static const struct {
    uint16_t mv;
    uint8_t pct;
} s_lipo_table[] =
{
    {4200, 100},
    {4060, 92},
    {3980, 85},
    {3920, 75},
    {3870, 65},
    {3820, 55},
    {3780, 45},
    {3750, 35},
    {3720, 25},
    {3680, 15},
    {3600, 8},
    {3450, 3},
    {3300, 0}
};

#define LIPO_TABLE_SIZE (sizeof(s_lipo_table) / sizeof(s_lipo_table[0]))

/**
 * @brief Mv to percent.
 *
 * @param[in]    mv              Parameter mv.
 *
 * @return Return value of type static uint8_t.
 */
static uint8_t mv_to_percent(uint16_t mv)
{
    if (mv >= s_lipo_table[0].mv)
        return 100;
    if (mv <= s_lipo_table[LIPO_TABLE_SIZE - 1].mv)
        return 0;

    for (size_t i = 0; i < LIPO_TABLE_SIZE - 1; i++) {
        if (mv <= s_lipo_table[i].mv && mv >= s_lipo_table[i + 1].mv) {
            uint16_t span_mv = s_lipo_table[i].mv - s_lipo_table[i + 1].mv;
            uint8_t span_pct = s_lipo_table[i].pct - s_lipo_table[i + 1].pct;
            uint16_t diff_mv = mv - s_lipo_table[i + 1].mv;
            return s_lipo_table[i + 1].pct + (uint8_t)((diff_mv * span_pct) / span_mv);
        }
    }
    return 0;
}

/**
 * @brief Initialize Battery ADC subsystem (ADC1 Channel 3 on GPIO 4 with 12 dB atten and eFuse cal).
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_power_init(void)
{
    if (s_adc_handle != NULL)
        return ESP_OK;

    adc_oneshot_unit_init_cfg_t unit_cfg = {
        .unit_id = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_RISCV,
    };
    esp_err_t err = adc_oneshot_new_unit(&unit_cfg, &s_adc_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize ADC1 unit: %s", esp_err_to_name(err));
        return err;
    }

    adc_oneshot_chan_cfg_t chan_cfg = {
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };
    err = adc_oneshot_config_channel(s_adc_handle, ADC_CHANNEL_3, &chan_cfg);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure ADC1 CH3: %s", esp_err_to_name(err));
        return err;
    }

#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
    adc_cali_curve_fitting_config_t cali_cfg = {
        .unit_id = ADC_UNIT_1,
        .chan = ADC_CHANNEL_3,
        .atten = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };
    err = adc_cali_create_scheme_curve_fitting(&cali_cfg, &s_cali_handle);
    if (err == ESP_OK) {
        s_cali_valid = true;
    } else {
        ESP_LOGW(TAG, "ADC calibration creation failed: %s, falling back to raw math", esp_err_to_name(err));
    }
#endif

    return ESP_OK;
}

/**
 * @brief Deinitialize ADC handles.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_power_deinit(void)
{
    if (s_cali_valid && s_cali_handle != NULL) {
#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
        adc_cali_delete_scheme_curve_fitting(s_cali_handle);
#endif
        s_cali_handle = NULL;
        s_cali_valid = false;
    }

    if (s_adc_handle != NULL) {
        adc_oneshot_del_unit(s_adc_handle);
        s_adc_handle = NULL;
    }
    return ESP_OK;
}

/**
 * @brief Sample calibrated battery voltage with 16-sample trimmed outlier filtering.
 *
 * @param[out]   out_mv          Battery voltage in millivolts (e.g. 3850 mV).
 * @param[out]   out_pct         Estimated state of charge (0 to 100%).
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_power_read_battery(uint16_t *out_mv, uint8_t *out_pct)
{
    if (out_mv == NULL)
        return ESP_ERR_INVALID_ARG;

    if (sub_power_connected_usb()) {
        *out_mv = 4200;
        if (out_pct != NULL) {
            *out_pct = 100;
        }
        return ESP_OK;
    }

    if (s_adc_handle == NULL) {
        esp_err_t err = sub_power_init();
        if (err != ESP_OK)
            return err;
    }

    int samples[16];
    for (int i = 0; i < 16; i++) {
        int raw = 0;
        adc_oneshot_read(s_adc_handle, ADC_CHANNEL_3, &raw);
        samples[i] = raw;
    }

    for (int i = 1; i < 16; i++) {
        int key = samples[i];
        int j = i - 1;
        while (j >= 0 && samples[j] > key) {
            samples[j + 1] = samples[j];
            j--;
        }
        samples[j + 1] = key;
    }

    int sum = 0;
    for (int i = 4; i < 12; i++) {
        sum += samples[i];
    }
    int avg_raw = sum / 8;

    int voltage_mv = 0;
    if (s_cali_valid && s_cali_handle != NULL) {
        adc_cali_raw_to_voltage(s_cali_handle, avg_raw, &voltage_mv);
    } else {
        voltage_mv = (avg_raw * 3100) / 4095;
    }

    uint16_t vbat_mv = (uint16_t)(voltage_mv * 2);

    *out_mv = vbat_mv;
    if (out_pct != NULL) {
        *out_pct = mv_to_percent(vbat_mv);
    }

    return ESP_OK;
}

/**
 * @brief Extract linear calibration coefficients (scale and offset) for ULP coprocessor hand-off.
 *
 * @param[out]   out_scale       Multiplier scaled by 4096.
 * @param[out]   out_offset_mv   Voltage offset in millivolts.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_power_get_ulp_cal_params(uint32_t *out_scale, int32_t *out_offset_mv)
{
    if (out_scale == NULL || out_offset_mv == NULL)
        return ESP_ERR_INVALID_ARG;

    if (s_cali_valid && s_cali_handle != NULL) {
        int v_low = 0;
        int v_high = 0;
        adc_cali_raw_to_voltage(s_cali_handle, 1000, &v_low);
        adc_cali_raw_to_voltage(s_cali_handle, 3000, &v_high);

        int32_t m_scale = (int32_t)(((int64_t)(v_high - v_low) * 4096) / 2000);
        int32_t b_offset = (int32_t)(v_low - ((m_scale * 1000LL) / 4096));

        *out_scale = (uint32_t)m_scale;
        *out_offset_mv = b_offset * 2;
    } else {
        *out_scale = 3100;
        *out_offset_mv = 0;
    }
    return ESP_OK;
}

/**
 * @brief Initialize and start the ULP-RISC-V Coprocessor Reactive Monitor.
 *
 * @details Loads the binary into RTC Slow SRAM on cold boot, passes ADC eFuse calibration, configures the periodic wake timer (Flow A period), and arms the coprocessor.
 *
 * @param[in]    flow_a_period_sec Periodic wake interval for Flow A telemetry in seconds.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_power_init_ulp(uint32_t flow_a_period_sec)
{
    uint32_t causes = esp_sleep_get_wakeup_causes();
    if (!(causes & BIT(ESP_SLEEP_WAKEUP_ULP))) {
        ESP_LOGI(TAG, "Loading ULP-RISC-V Coprocessor binary...");
        esp_err_t err = ulp_riscv_load_binary(ulp_h1os_bin_start, (size_t)(ulp_h1os_bin_end - ulp_h1os_bin_start));
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "ulp_riscv_load_binary failed: %s", esp_err_to_name(err));
            return err;
        }

        sub_power_init();

        sub_power_get_ulp_cal_params((uint32_t *)&ulp_cal_scale, (int32_t *)&ulp_cal_offset);
        ESP_LOGI(TAG, "ULP battery linear calibration primed: scale=%lu, offset=%ld mV",
                 (unsigned long)ulp_cal_scale, (long)ulp_cal_offset);
        ulp_dispatch_reason = 0;
        ulp_last_wake_btn = 0;
        ulp_last_vbat_mv = 4000;

        uint32_t period_sec = (flow_a_period_sec > 0) ? flow_a_period_sec : 60;
        ulp_set_wakeup_period(0, (uint64_t)period_sec * 1000000ULL);

        ulp_riscv_cfg_t cfg = {
            .wakeup_source = ULP_RISCV_WAKEUP_SOURCE_GPIO,
        };
        err = ulp_riscv_config_and_run(&cfg);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "ulp_riscv_config_and_run failed: %s", esp_err_to_name(err));
            return err;
        }

        CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN);
        SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);

        rtc_gpio_deinit(HAL_PIN_BUTTON_BOOT);
        rtc_gpio_deinit(HAL_PIN_BUTTON_POWER);
        rtc_gpio_deinit(HAL_PIN_RTC_INT);

        ESP_LOGI(TAG, "ULP-RISC-V Coprocessor initialized in Pure Event Mode (ERR-001 Mitigated)");
    }
    return ESP_OK;
}

/**
 * @brief Configure ULP slice parameters prior to entering deep sleep.
 *
 * @param[in]    flow_a_sec      Flow A sample interval in seconds.
 * @param[in]    flow_b_sec      Flow B display refresh interval in seconds.
 * @param[in]    overflow        Total slice overflow threshold.
 * @param[in]    remainder_sec   Final remainder slice duration in seconds.
 */
void sub_power_set_sleep_slices(uint32_t flow_a_sec, uint32_t flow_b_sec, uint32_t overflow, uint32_t remainder_sec)
{
    s_flow_a_sec     = (flow_a_sec > 0) ? flow_a_sec : 60;
    s_flow_b_sec     = (flow_b_sec > 0) ? flow_b_sec : 300;
    s_overflow_limit = (overflow > 0) ? overflow : 1;
    s_remainder_sec  = remainder_sec;
}

/**
 * @brief Configure EXT1 wake sources and enter deep sleep with operational mode arbitration.
 *
 * @details Maintains RTC pad holds on power latch (GPIO 17) and EPD rail (GPIO 6) to keep rails active.
 *
 * @param[in]    sleep_seconds   Timer duration in seconds (0 = timer disabled).
 * @param[in]    ext1_pins_mask  Bitmask of RTC GPIO pins for wakeup (e.g. GPIO 0, 18, 5).
 * @param[in]    mode            Full cycle or Flow A burst mode.
 *
 * @return Does not return on success (enters deep sleep).
 */
esp_err_t sub_power_enter_deep_sleep_mode(uint32_t sleep_seconds, uint64_t ext1_pins_mask, sub_power_sleep_mode_t mode)
{
    (void)sleep_seconds;
    (void)ext1_pins_mask;

    hal_io_isolate_sleep_pads();

    /* Ensure ADC1 is initialized in ULP RISC-V mode before sleep handoff */
    if (s_adc_handle == NULL) {
        sub_power_init();
    }

    uint32_t full_slices = s_flow_b_sec / s_flow_a_sec;

    ulp_overflow_limit = s_overflow_limit;
    ulp_remainder_sec  = s_remainder_sec;
    if (mode == SUB_POWER_SLEEP_FULL_CYCLE) {
        ulp_slice_counter = 0;
    }
    ulp_dispatch_reason = 0;
    ulp_last_wake_btn   = 0;
    ulp_rtc_int_stuck   = 0;
    ulp_usb_connected   = sub_power_connected_usb() ? 1 : 0;
    asm volatile("memw" ::: "memory");

    ESP_LOGI(TAG,
             "Event Mode Slicing [%s]: Tick=%lus, Target=%lus -> FullSlices=%lu, Remainder=%lus -> "
             "TotalOverflowLimit=%lu (SliceAcc=%lu, USB=%lu)",
             (mode == SUB_POWER_SLEEP_FULL_CYCLE) ? "FULL_CYCLE" : "FLOW_A_BURST",
             (unsigned long)s_flow_a_sec,
             (unsigned long)s_flow_b_sec,
             (unsigned long)full_slices,
             (unsigned long)s_remainder_sec,
             (unsigned long)s_overflow_limit,
             (unsigned long)ulp_slice_counter,
             (unsigned long)ulp_usb_connected);

    /* Keep ULP GPIO wakeup disarmed while configuring RTC IO pads and printing logs */
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN | RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);

    const gpio_num_t wake_pins[] = {HAL_PIN_BUTTON_BOOT, HAL_PIN_BUTTON_POWER, HAL_PIN_RTC_INT};
    for (size_t i = 0; i < sizeof(wake_pins) / sizeof(wake_pins[0]); i++) {
        gpio_num_t pin = wake_pins[i];

        rtc_gpio_init(pin);
        rtc_gpio_set_direction(pin, RTC_GPIO_MODE_INPUT_ONLY);

        rtc_gpio_hold_dis(pin);

        rtc_gpio_pullup_en(pin);
        rtc_gpio_pulldown_dis(pin);

        rtc_gpio_wakeup_enable(pin, GPIO_INTR_LOW_LEVEL);
    }

    rtc_gpio_init(HAL_PIN_BATTERY_ADC);
    rtc_gpio_set_direction(HAL_PIN_BATTERY_ADC, RTC_GPIO_MODE_DISABLED);
    rtc_gpio_pullup_dis(HAL_PIN_BATTERY_ADC);
    rtc_gpio_pulldown_dis(HAL_PIN_BATTERY_ADC);
    rtc_gpio_hold_dis(HAL_PIN_BATTERY_ADC);

    esp_sleep_enable_ulp_wakeup();

    uint32_t drain_wait_us = 0;
    while (rtc_gpio_get_level(HAL_PIN_RTC_INT) == 0 && drain_wait_us < 50000) {
        esp_rom_delay_us(500);
        drain_wait_us += 500;
    }

    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);

    ESP_LOGI(TAG, "Pre-Sleep Audit: ULP_CP_TIMER=0x%08lx, GPIO_STATUS=0x%08lx",
                    (unsigned long)REG_READ(RTC_CNTL_ULP_CP_TIMER_REG),
                    (unsigned long)REG_READ(RTC_GPIO_STATUS_REG));
    ESP_LOGI(TAG, "RTC Wake Audit: PIN0(BOOT)=0x%08lx, PIN5(RTC)=0x%08lx, PIN18(PWR)=0x%08lx",
                    (unsigned long)REG_READ(RTC_GPIO_PIN0_REG + (4 * 0)),
                    (unsigned long)REG_READ(RTC_GPIO_PIN0_REG + (4 * 5)),
                    (unsigned long)REG_READ(RTC_GPIO_PIN0_REG + (4 * 18)));
    ESP_LOGI(TAG, "Entering deep sleep in Pure Event Mode (Timer: PCF85063A %lus pulse, Slices: %lu, Wake: ULP)...",
                    (unsigned long)s_flow_a_sec,
                    (unsigned long)s_overflow_limit);

    /* Clear latched status and arm ULP GPIO wakeup immediately prior to sleep entry */
    REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);
    REG_WRITE(RTC_CNTL_INT_CLR_REG, RTC_CNTL_COCPU_INT_CLR | RTC_CNTL_COCPU_TRAP_INT_CLR | RTC_CNTL_ULP_CP_INT_CLR);
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
    esp_rom_delay_us(120);
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);
    esp_rom_delay_us(120);

    esp_deep_sleep_start();
    return ESP_OK;
}

/**
 * @brief Configure EXT1 wake sources and enter deep sleep (defaults to SUB_POWER_SLEEP_FULL_CYCLE).
 *
 * @details Maintains RTC pad holds on power latch (GPIO 17) and EPD rail (GPIO 6) to keep rails active.
 *
 * @param[in]    sleep_seconds   Timer duration in seconds (0 = timer disabled).
 * @param[in]    ext1_pins_mask  Bitmask of RTC GPIO pins for wakeup (e.g. GPIO 0, 18, 5).
 *
 * @return Does not return on success (enters deep sleep).
 */
esp_err_t sub_power_enter_deep_sleep(uint32_t sleep_seconds, uint64_t ext1_pins_mask)
{
    return sub_power_enter_deep_sleep_mode(sleep_seconds, ext1_pins_mask, SUB_POWER_SLEEP_FULL_CYCLE);
}

/**
 * @brief Power off system completely by releasing battery power latch (GPIO 17).
 *
 * @details Used for critical low-battery shutdown or explicit user power-off.
 */
void sub_power_cut_power_latch(void)
{
    ESP_LOGW(TAG, "Releasing battery power latch (GPIO 17) - SYSTEM SHUTDOWN");
    hal_io_release_power_latch();
}

/**
 * @brief Check to see if USB is connected.
 *
 * @details Used for charger detection.
 *
 * @return true if usb is connected, or false if disconnected.
 */
bool sub_power_connected_usb(void)
{
    bool usb_state = hal_check_usb_ll();
    ESP_LOGI(TAG, "USB is %s", usb_state ? "Connected" : "NOT Connected");
    return usb_state;
}

#if CONFIG_PM_ENABLE
static esp_pm_lock_handle_t s_cpu_max_lock = NULL;
#endif

/**
 * @brief Initialize Dynamic Frequency Scaling (DFS) power management.
 *
 * @details Configures CPU frequency scaling based on the selected clock mode.
 *          SYS_CLK_MODE_DYNAMIC gates CPU cores to 80 MHz baseline during quiescent periods,
 *          allowing transient turbo scaling (CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ) during heavy UI/compute bursts.
 *          SYS_CLK_MODE_FIXED_MAX locks CPU cores permanently to maximum clock (CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ).
 *          SYS_CLK_MODE_FIXED_MIN locks CPU cores permanently to 80 MHz baseline.
 *
 * @param[in]    mode            Clock scaling mode (SYS_CLK_MODE_DYNAMIC, FIXED_MAX, FIXED_MIN).
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_power_init_dfs(sys_clk_mode_t mode)
{
#if CONFIG_PM_ENABLE
    int max_freq = (mode == SYS_CLK_MODE_FIXED_MIN) ? 80 : CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ;
    int min_freq = (mode == SYS_CLK_MODE_FIXED_MAX) ? CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ : 80;

    esp_pm_config_t pm_config = {
        .max_freq_mhz = max_freq,
        .min_freq_mhz = min_freq,
        .light_sleep_enable = false,
    };
    esp_err_t err = esp_pm_configure(&pm_config);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure DFS: %s", esp_err_to_name(err));
        return err;
    }

    if (mode == SYS_CLK_MODE_DYNAMIC && s_cpu_max_lock == NULL) {
        err = esp_pm_lock_create(ESP_PM_CPU_FREQ_MAX, 0, "h1os_turbo", &s_cpu_max_lock);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Failed to create CPU MAX PM lock: %s", esp_err_to_name(err));
            return err;
        }
    }

    const char *mode_str = (mode == SYS_CLK_MODE_DYNAMIC)   ? "DYNAMIC" :
                           (mode == SYS_CLK_MODE_FIXED_MAX) ? "FIXED_MAX" :
                                                              "FIXED_MIN";

    ESP_LOGI(TAG, "Dynamic Frequency Scaling initialized: %s (Base: %d MHz, Max: %d MHz)",
             mode_str,
             pm_config.min_freq_mhz,
             pm_config.max_freq_mhz);
    return ESP_OK;
#else
    (void)mode;
    ESP_LOGW(TAG, "CONFIG_PM_ENABLE disabled; DFS unavailable");
    return ESP_ERR_NOT_SUPPORTED;
#endif
}

/**
 * @brief Acquire 240 MHz CPU performance lock (e.g. during LVGL rendering blitz).
 *
 * @details Boosts CPU cores from 80 MHz baseline to 240 MHz turbo clock.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_power_cpu_max_acquire(void)
{
#if CONFIG_PM_ENABLE
    if (s_cpu_max_lock != NULL) {
        return esp_pm_lock_acquire(s_cpu_max_lock);
    }
#endif
    return ESP_OK;
}

/**
 * @brief Release 240 MHz CPU performance lock.
 *
 * @details Allows CPU cores to gate back down to 80 MHz baseline.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_power_cpu_max_release(void)
{
#if CONFIG_PM_ENABLE
    if (s_cpu_max_lock != NULL) {
        return esp_pm_lock_release(s_cpu_max_lock);
    }
#endif
    return ESP_OK;
}