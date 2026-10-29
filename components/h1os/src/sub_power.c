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
#include "esp_attr.h"
#include "esp_sleep.h"
#include "h1os/orch_state.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "h1os/hal_io.h"
#include "h1os/hal_types.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/rtc_io_reg.h"
#include "ulp_adc.h"
#include "ulp_h1os.h"
#include "ulp_riscv.h"

#include <stdlib.h>

extern const uint8_t ulp_h1os_bin_start[] asm("_binary_ulp_h1os_bin_start");
extern const uint8_t ulp_h1os_bin_end[]   asm("_binary_ulp_h1os_bin_end");

static const char *TAG = "sub_power";

#define SUB_POWER_RTC_INT_DRAIN_TIMEOUT_US      50000U /**< Timeout awaiting PCF85063A INT release (50 ms).  */
#define SUB_POWER_RTC_INT_DRAIN_STEP_US         500U   /**< Step delay polling PCF85063A INT pin (500 µs).   */
#define SUB_POWER_VBAT_ZERO_VOLT_GUARD_MV       3300U  /**< Lower floor below which USB assumes charged.     */
#define SUB_POWER_VBAT_ASSUMED_CHARGED_MV       4200U  /**< Assumed full cell potential on bench power.      */
#define SUB_POWER_VBAT_NOMINAL_FALLBACK_MV      4000U  /**< Default nominal potential when out of range.     */
#define SUB_POWER_VBAT_FULL_CHARGE_THRESHOLD_MV 4180U  /**< Full charge detection voltage (4.18V).           */
#define SUB_POWER_CHARGING_RAMP_DELTA_MV        15U    /**< Voltage rise confirming active charging (15 mV). */
#define SUB_POWER_CHARGING_FLOAT_DELTA_MV       5U     /**< Maximum float delta at CV confirming charged.    */

static bool              s_ulp_adc_inited = false;
static adc_cali_handle_t s_cali_handle    = NULL;
static bool              s_cali_valid     = false;

static const struct {
    uint16_t mv;
    uint16_t soc_x10;
} s_lipo_table[] = {
    {4200, 1000},
    {4120, 950},
    {4040, 880},
    {3960, 800},
    {3890, 730},
    {3820, 600},
    {3780, 480},
    {3750, 360},
    {3720, 250},
    {3680, 150},
    {3600, 80},
    {3450, 30},
    {3300, 0}
};

#define LIPO_TABLE_SIZE (sizeof(s_lipo_table) / sizeof(s_lipo_table[0]))

uint16_t sub_power_mv_to_soc_tenths(uint16_t mv)
{
    if (mv >= s_lipo_table[0].mv) {
        return 1000;
    }
    if (mv <= s_lipo_table[LIPO_TABLE_SIZE - 1].mv) {
        return 0;
    }

    for (size_t i = 0; i < LIPO_TABLE_SIZE - 1; i++) {
        if (mv <= s_lipo_table[i].mv && mv >= s_lipo_table[i + 1].mv) {
            uint32_t span_mv  = s_lipo_table[i].mv - s_lipo_table[i + 1].mv;
            uint32_t span_soc = s_lipo_table[i].soc_x10 - s_lipo_table[i + 1].soc_x10;
            uint32_t diff_mv  = mv - s_lipo_table[i + 1].mv;
            return (uint16_t)(s_lipo_table[i + 1].soc_x10 + ((diff_mv * span_soc) / span_mv));
        }
    }
    return 0;
}

static uint8_t mv_to_percent(uint16_t mv)
{
    return (uint8_t)((sub_power_mv_to_soc_tenths(mv) + 5U) / 10U);
}

/**
 * @brief Initialize Battery ADC subsystem (ADC1 Channel 3 on GPIO 4 with 12 dB atten and eFuse cal).
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_power_init(void)
{
    if (s_ulp_adc_inited) {
        return ESP_OK;
    }

    rtc_gpio_hold_dis(HAL_PIN_BATTERY_ADC);

    /* Use ulp_adc_init() rather than raw adc_oneshot_new_unit() so ESP-IDF loads
     * the eFuse hardware reference calibration code (adc_set_hw_calibration_code)
     * into the SAR ADC1 internal analog reg_i2c registers for 12 dB attenuation and
     * enables the deep-sleep SAR ADC monitor domain (esp_sleep_enable_adc_tsens_monitor). */
    const ulp_adc_cfg_t ulp_adc_cfg = {
        .adc_n    = ADC_UNIT_1,
        .channel  = ADC_CHANNEL_3,
        .atten    = ADC_ATTEN_DB_12,
        .width    = ADC_BITWIDTH_DEFAULT,
        .ulp_mode = ADC_ULP_MODE_RISCV,
    };
    esp_err_t err = ulp_adc_init(&ulp_adc_cfg);
    if (err != ESP_OK && err != ESP_ERR_INVALID_STATE) {
        ESP_LOGE(TAG, "Failed to initialize ULP ADC1 CH3: %s", esp_err_to_name(err));
        return err;
    }
    s_ulp_adc_inited = true;

#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
    adc_cali_curve_fitting_config_t cali_cfg = {
        .unit_id  = ADC_UNIT_1,
        .chan     = ADC_CHANNEL_3,
        .atten    = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };
    err = adc_cali_create_scheme_curve_fitting(&cali_cfg, &s_cali_handle);
    if (err == ESP_OK) {
        s_cali_valid = true;
    } else {
        ESP_LOGW(TAG, "ADC calibration creation failed: %s, using default linear coefficients", esp_err_to_name(err));
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
        s_cali_valid  = false;
    }

    if (s_ulp_adc_inited) {
        (void)ulp_adc_deinit();
        s_ulp_adc_inited = false;
    }
    return ESP_OK;
}

/**
 * @brief Retrieve calibrated resting battery voltage, SoC %, and charge state from ULP ring buffer.
 *
 * @param[out]   out_mv          Battery voltage in millivolts (e.g. 3850 mV).
 * @param[out]   out_pct         Estimated state of charge (0 to 100%).
 * @param[out]   out_state       Evaluated battery state (DISCHARGING, CHARGING, CHARGED).
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_power_get_battery_status(uint16_t *out_mv,
                                       uint8_t *out_pct,
                                       h1os_battery_state_t *out_state)
{
    if (out_mv == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    const volatile uint32_t *ring = (const volatile uint32_t *)&ulp_vbat_ring;
    uint32_t head  = ulp_vbat_ring_head % 8U;
    uint32_t count = ulp_vbat_ring_count;
    uint32_t vbat  = ulp_last_vbat_mv;
    bool usb_conn  = sub_power_connected_usb();

    /* Zero-Volt Cable Guard: When running on USB bench power without a LiPo cell attached,
     * the 200k/200k divider floats or reads <100 mV. Force 4200 mV (100% CHARGED). */
    if (usb_conn && vbat < SUB_POWER_VBAT_ZERO_VOLT_GUARD_MV) {
        vbat = SUB_POWER_VBAT_ASSUMED_CHARGED_MV;
    } else if (vbat == 0U || vbat > 4500U) {
        vbat = SUB_POWER_VBAT_NOMINAL_FALLBACK_MV;
    }

    uint16_t vbat_mv = (uint16_t)vbat;
    uint8_t pct      = mv_to_percent(vbat_mv);

    *out_mv = vbat_mv;
    if (out_pct != NULL) {
        *out_pct = pct;
    }

    h1os_battery_state_t state = H1OS_BATTERY_DISCHARGING;
    if (usb_conn) {
        state = (vbat_mv >= SUB_POWER_VBAT_FULL_CHARGE_THRESHOLD_MV) ? H1OS_BATTERY_CHARGED : H1OS_BATTERY_CHARGING;
    } else if (count >= 2U) {
        uint32_t newest_idx = (head == 0U) ? 7U : (head - 1U);
        /* Compare newest sample against sample from 2 cycles prior (or 1 cycle prior if count == 2) */
        uint32_t lookback   = (count >= 3U) ? 2U : 1U;
        uint32_t prev_idx   = (newest_idx + 8U - lookback) % 8U;
        uint32_t v_new      = ring[newest_idx];
        uint32_t v_prev     = ring[prev_idx];

        if (v_new >= v_prev + SUB_POWER_CHARGING_RAMP_DELTA_MV) {
            state = H1OS_BATTERY_CHARGING;
        } else if (v_new >= SUB_POWER_VBAT_FULL_CHARGE_THRESHOLD_MV && (v_new > v_prev ? (v_new - v_prev) : (v_prev - v_new)) <= SUB_POWER_CHARGING_FLOAT_DELTA_MV) {
            state = H1OS_BATTERY_CHARGED;
        } else {
            state = H1OS_BATTERY_DISCHARGING;
        }
    }

    if (out_state != NULL) {
        *out_state = state;
    }

    return ESP_OK;
}

esp_err_t sub_power_read_battery(uint16_t *out_mv, uint8_t *out_pct)
{
    h1os_battery_state_t state;
    return sub_power_get_battery_status(out_mv, out_pct, &state);
}

/**
 * @brief Compute empirical battery autonomy metrics over total elapsed runtime.
 */
void sub_power_calc_autonomy(uint16_t initial_soc_x10, uint16_t current_soc_x10,
                             uint32_t total_sleep_sec, uint32_t total_app_ms,
                             h1os_autonomy_metrics_t *out_metrics)
{
    if (out_metrics == NULL) {
        return;
    }

    out_metrics->avg_draw_ma   = -1.0f;
    out_metrics->autonomy_days = -1.0f;
    out_metrics->mah_spent_lap = 0.0f;

    float elapsed_sec   = (float)total_sleep_sec + ((float)total_app_ms / 1000.0f);
    float elapsed_hours = elapsed_sec / 3600.0f;

    /* Calibration guard: require >= 1.0% (10 tenths) SoC drop and >= 60s elapsed runtime */
    if (initial_soc_x10 <= current_soc_x10 || elapsed_sec < 60.0f) {
        return;
    }

    int32_t delta_x10 = (int32_t)initial_soc_x10 - (int32_t)current_soc_x10;
    if (delta_x10 < 10) {
        return;
    }

    const float nominal_mah = 400.0f;
    float delta_soc_pct = (float)delta_x10 / 10.0f;
    float delta_c_lap   = nominal_mah * (delta_soc_pct / 100.0f);
    out_metrics->mah_spent_lap = delta_c_lap;

    float avg_draw_ma = delta_c_lap / elapsed_hours;
    out_metrics->avg_draw_ma = avg_draw_ma;

    float current_soc_pct = (float)current_soc_x10 / 10.0f;
    float c_rem = nominal_mah * (current_soc_pct / 100.0f);
    float h_rem = c_rem / avg_draw_ma;
    out_metrics->autonomy_days = h_rem / 24.0f;
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
    if (out_scale == NULL || out_offset_mv == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if (s_cali_valid && s_cali_handle != NULL) {
        int32_t v_2000 = 0;
        int32_t v_3000 = 0;
        adc_cali_raw_to_voltage(s_cali_handle, 2000, (int *)&v_2000);
        adc_cali_raw_to_voltage(s_cali_handle, 3000, (int *)&v_3000);

        /* Fold the 2x divider directly into slope and offset:
         * m_vbat = (2 * (V_3000 - V_2000) * 4096) / 1000
         * b_vbat = (2 * V_2000) - ((m_vbat * 2000) / 4096)
         */
        int32_t m_scale  = (int32_t)(((int64_t)2 * (v_3000 - v_2000) * 4096LL) / 1000LL);
        int32_t b_offset = (int32_t)((int64_t)2 * v_2000 - (((int64_t)m_scale * 2000LL) / 4096LL)) + SUB_POWER_VBAT_TRIM_OFFSET_MV;

        *out_scale     = (uint32_t)m_scale;
        *out_offset_mv = b_offset;
    } else {
        *out_scale     = 8601;
        *out_offset_mv = SUB_POWER_VBAT_TRIM_OFFSET_MV;
    }
    return ESP_OK;
}

/**
 * @brief Initialize and start the ULP-RISC-V Coprocessor Reactive Monitor.
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
        ulp_last_wake_btn   = 0;
        ulp_last_vbat_mv    = 4000;

        if (flow_a_period_sec == 0) {
            ESP_LOGE(TAG, "Cannot initialize ULP: flow_a_period_sec is 0");
            return ESP_ERR_INVALID_ARG;
        }
        ulp_set_wakeup_period(0, (uint64_t)flow_a_period_sec * 1000000ULL);

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

RTC_DATA_ATTR static uint32_t s_cached_flow_a_sec = 0;
RTC_DATA_ATTR static uint32_t s_cached_flow_b_sec = 0;

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
    s_cached_flow_a_sec = flow_a_sec;
    s_cached_flow_b_sec = flow_b_sec;
    ulp_overflow_limit  = overflow;
    ulp_remainder_sec   = remainder_sec;
}

/**
 * @brief Configure EXT1 wake sources and enter deep sleep with operational mode arbitration.
 *
 * @param[in]    sleep_seconds   Timer duration in seconds (Flow A slice duration).
 * @param[in]    ext1_pins_mask  Bitmask of RTC GPIO pins for wakeup (e.g. GPIO 0, 18, 5).
 * @param[in]    mode            Full cycle or Flow A burst mode.
 *
 * @return Does not return on success (enters deep sleep).
 */
esp_err_t sub_power_enter_deep_sleep_mode(uint32_t sleep_seconds, uint64_t ext1_pins_mask, sub_power_sleep_mode_t mode)
{
    (void)ext1_pins_mask;

    hal_io_isolate_sleep_pads();

    /* Ensure ADC1 CH3 is initialized via ulp_adc_init() (loading SAR1 reg_i2c hw cal code) before sleep handoff */
    if (!s_ulp_adc_inited) {
        (void)sub_power_init();
    }

    if (s_cached_flow_a_sec == 0U) {
        s_cached_flow_a_sec = orch_state_get()->sample_interval_sec;
    }
    if (s_cached_flow_b_sec == 0U) {
        s_cached_flow_b_sec = orch_state_get()->flow_b_period_sec;
    }
    uint32_t flow_a_sec  = (sleep_seconds > 0U) ? sleep_seconds : s_cached_flow_a_sec;
    uint32_t flow_b_sec  = s_cached_flow_b_sec;
    uint32_t full_slices = (flow_a_sec > 0U) ? (flow_b_sec / flow_a_sec) : 0U;

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
             (unsigned long)flow_a_sec,
             (unsigned long)flow_b_sec,
             (unsigned long)full_slices,
             (unsigned long)ulp_remainder_sec,
             (unsigned long)ulp_overflow_limit,
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

    /* Keep GPIO 4 (ADC1_CH3) analog pad configuration from ulp_adc_init() intact; only ensure pad hold is off */
    rtc_gpio_hold_dis(HAL_PIN_BATTERY_ADC);

    esp_sleep_enable_ulp_wakeup();

    uint32_t drain_wait_us = 0;
    while (rtc_gpio_get_level(HAL_PIN_RTC_INT) == 0 && drain_wait_us < SUB_POWER_RTC_INT_DRAIN_TIMEOUT_US) {
        esp_rom_delay_us(SUB_POWER_RTC_INT_DRAIN_STEP_US);
        drain_wait_us += SUB_POWER_RTC_INT_DRAIN_STEP_US;
    }

    /* Wait up to 100 ms for any lingering button press on BOOT or POWER to release HIGH */
    uint32_t btn_drain_us = 0;
    while ((rtc_gpio_get_level(HAL_PIN_BUTTON_BOOT) == 0 || rtc_gpio_get_level(HAL_PIN_BUTTON_POWER) == 0) &&
           btn_drain_us < SUB_POWER_RTC_INT_DRAIN_TIMEOUT_US * 2U) {
        esp_rom_delay_us(1000);
        btn_drain_us += 1000U;
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
                    (unsigned long)flow_a_sec,
                    (unsigned long)ulp_overflow_limit);

    /* Clean up ULP and RTC controller interrupt flags to prevent sleep rejection (PIT-02 / PIT-03) */
    CLEAR_PERI_REG_MASK(RTC_CNTL_STATE0_REG, RTC_CNTL_SW_CPU_INT);
    asm volatile("memw" ::: "memory");

    SET_PERI_REG_MASK(RTC_CNTL_INT_CLR_REG,
                      RTC_CNTL_SLP_REJECT_INT_CLR |
                          RTC_CNTL_SLP_WAKEUP_INT_CLR |
                          RTC_CNTL_COCPU_INT_CLR |
                          RTC_CNTL_COCPU_TRAP_INT_CLR |
                          RTC_CNTL_ULP_CP_INT_CLR);
    asm volatile("memw" ::: "memory");

    REG_SET_BIT(RTC_CNTL_STATE0_REG, RTC_CNTL_SLP_REJECT_CAUSE_CLR);
    asm volatile("memw" ::: "memory");

    /* Clear latched status and arm ULP GPIO wakeup immediately prior to sleep entry */
    REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);
    asm volatile("memw" ::: "memory");

    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
    asm volatile("memw" ::: "memory");
    esp_rom_delay_us(120);
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
    asm volatile("memw" ::: "memory");
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);
    asm volatile("memw" ::: "memory");
    esp_rom_delay_us(120);

    esp_deep_sleep_start();
    return ESP_OK;
}

esp_err_t sub_power_enter_deep_sleep(uint32_t sleep_seconds, uint64_t ext1_pins_mask)
{
    return sub_power_enter_deep_sleep_mode(sleep_seconds, ext1_pins_mask, SUB_POWER_SLEEP_FULL_CYCLE);
}

void sub_power_cut_power_latch(void)
{
    ESP_LOGW(TAG, "Releasing battery power latch (GPIO 17) - SYSTEM SHUTDOWN");
    hal_io_release_power_latch();
}

bool sub_power_connected_usb(void)
{
    bool usb_state = hal_check_usb_ll();
    ESP_LOGD(TAG, "USB is %s", usb_state ? "Connected" : "NOT Connected");
    return usb_state;
}

#if CONFIG_PM_ENABLE
static esp_pm_lock_handle_t s_cpu_max_lock = NULL;
#endif

esp_err_t sub_power_init_dfs(sys_clk_mode_t mode)
{
#if CONFIG_PM_ENABLE
    int32_t max_freq = (mode == SYS_CLK_MODE_FIXED_MIN) ? 80 : CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ;
    int32_t min_freq = (mode == SYS_CLK_MODE_FIXED_MAX) ? CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ : 80;

    esp_pm_config_t pm_config = {
        .max_freq_mhz       = (int)max_freq,
        .min_freq_mhz       = (int)min_freq,
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

esp_err_t sub_power_cpu_max_acquire(void)
{
#if CONFIG_PM_ENABLE
    if (s_cpu_max_lock != NULL) {
        return esp_pm_lock_acquire(s_cpu_max_lock);
    }
#endif
    return ESP_OK;
}

esp_err_t sub_power_cpu_max_release(void)
{
#if CONFIG_PM_ENABLE
    if (s_cpu_max_lock != NULL) {
        return esp_pm_lock_release(s_cpu_max_lock);
    }
#endif
    return ESP_OK;
}