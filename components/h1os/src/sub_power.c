/**
 * @file sub_power.c
 * @brief Layer 2: Battery ADC Monitoring & Deep Sleep Hardware Driver Implementation
 *
 * SPDX-License-Identifier: MIT
 */

#include "h1os/sub_power.h"
#include "h1os/sub_rtc.h"
#include "h1os/orch_state.h"
#include "h1os/orch_wake_stub.h"
#include "h1os/hal_io.h"


#include "h1os/hal_types.h"
#include "esp_log.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "esp_sleep.h"
#include "driver/gpio.h"
#include "driver/rtc_io.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/rtc_io_reg.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdlib.h>

#include "ulp_riscv.h"
#include "ulp_h1os.h"

extern const uint8_t ulp_h1os_bin_start[] asm("_binary_ulp_h1os_bin_start");
extern const uint8_t ulp_h1os_bin_end[]   asm("_binary_ulp_h1os_bin_end");

static const char *TAG = "sub_power";

static adc_oneshot_unit_handle_t s_adc_handle  = NULL;
static adc_cali_handle_t         s_cali_handle = NULL;
static bool                      s_cali_valid  = false;


/* 13-point LiPo OCV Discharge Curve (matching legacy hardware calibration) */
static const struct {
    uint16_t mv;
    uint8_t  pct;
} s_lipo_table[] = {
    { 4200, 100 },
    { 4060,  92 },
    { 3980,  85 },
    { 3920,  75 },
    { 3870,  65 },
    { 3820,  55 },
    { 3780,  45 },
    { 3750,  35 },
    { 3720,  25 },
    { 3680,  15 },
    { 3600,   8 },
    { 3450,   3 },
    { 3300,   0 }
};

#define LIPO_TABLE_SIZE (sizeof(s_lipo_table) / sizeof(s_lipo_table[0]))

static uint8_t mv_to_percent(uint16_t mv)
{
    if (mv >= s_lipo_table[0].mv) return 100;
    if (mv <= s_lipo_table[LIPO_TABLE_SIZE - 1].mv) return 0;

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

esp_err_t sub_power_init(void)
{
    if (s_adc_handle != NULL) return ESP_OK;

    /* 1. Initialize ADC1 Oneshot Unit in shared ULP RISC-V mode */
    adc_oneshot_unit_init_cfg_t unit_cfg = {
        .unit_id  = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_RISCV,
    };
    esp_err_t err = adc_oneshot_new_unit(&unit_cfg, &s_adc_handle);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize ADC1 unit: %s", esp_err_to_name(err));
        return err;
    }

    /* 2. Configure Channel 3 (GPIO 4) with 12 dB Attenuation (0 - 3.1V input) */
    adc_oneshot_chan_cfg_t chan_cfg = {
        .atten    = ADC_ATTEN_DB_12,
        .bitwidth = ADC_BITWIDTH_DEFAULT,
    };
    err = adc_oneshot_config_channel(s_adc_handle, ADC_CHANNEL_3, &chan_cfg);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure ADC1 CH3: %s", esp_err_to_name(err));
        return err;
    }

    /* 3. Initialize Calibration Scheme (Curve Fitting on ESP32-S3) */
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
        ESP_LOGW(TAG, "ADC calibration creation failed: %s, falling back to raw math", esp_err_to_name(err));
    }
#endif

    return ESP_OK;
}

esp_err_t sub_power_deinit(void)
{
    if (s_cali_valid && s_cali_handle != NULL) {
#if ADC_CALI_SCHEME_CURVE_FITTING_SUPPORTED
        adc_cali_delete_scheme_curve_fitting(s_cali_handle);
#endif
        s_cali_handle = NULL;
        s_cali_valid  = false;
    }

    if (s_adc_handle != NULL) {
        adc_oneshot_del_unit(s_adc_handle);
        s_adc_handle = NULL;
    }
    return ESP_OK;
}

esp_err_t sub_power_read_battery(uint16_t *out_mv, uint8_t *out_pct)
{
    if (out_mv == NULL) return ESP_ERR_INVALID_ARG;

    /* Architectural Invariant: If USB is plugged in, VBAT is always 4200 mV (100%) */
    if (sub_power_connected_usb()) {
        *out_mv = 4200;
        if (out_pct != NULL) {
            *out_pct = 100;
        }
        return ESP_OK;
    }

    if (s_adc_handle == NULL) {
        esp_err_t err = sub_power_init();
        if (err != ESP_OK) return err;
    }

    /* 16-sample trimmed mean (drop lowest 4 and highest 4) */
    int samples[16];
    for (int i = 0; i < 16; i++) {
        int raw = 0;
        adc_oneshot_read(s_adc_handle, ADC_CHANNEL_3, &raw);
        samples[i] = raw;
    }

    /* Fast in-place insertion sort for fixed N=16 */
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
        /* Fallback linear calculation: 12 dB full scale ~3100 mV */
        voltage_mv = (avg_raw * 3100) / 4095;
    }

    /* Resistor divider is 1:2 (200k / 200k), so VBAT = V_ADC * 2 */
    uint16_t vbat_mv = (uint16_t)(voltage_mv * 2);

    *out_mv = vbat_mv;
    if (out_pct != NULL) {
        *out_pct = mv_to_percent(vbat_mv);
    }

    return ESP_OK;
}

esp_err_t sub_power_get_ulp_cal_params(uint32_t *out_scale, int32_t *out_offset_mv)
{
    if (out_scale == NULL || out_offset_mv == NULL) return ESP_ERR_INVALID_ARG;

    if (s_cali_valid && s_cali_handle != NULL) {
        int v_low  = 0;
        int v_high = 0;
        adc_cali_raw_to_voltage(s_cali_handle, 1000, &v_low);
        adc_cali_raw_to_voltage(s_cali_handle, 3000, &v_high);

        /* Slope m = (v_high - v_low) / (3000 - 1000) */
        int32_t m_scale  = (int32_t)(((int64_t)(v_high - v_low) * 4096) / 2000);
        int32_t b_offset = (int32_t)(v_low - ((m_scale * 1000LL) / 4096));

        *out_scale     = (uint32_t)m_scale;
        *out_offset_mv = b_offset * 2; /* account for 1:2 divider */
    } else {
        /* Default ideal 12 dB full-scale 3100 mV */
        *out_scale     = 3100;
        *out_offset_mv = 0;
    }
    return ESP_OK;
}

esp_err_t sub_power_init_ulp(uint32_t flow_a_period_sec)
{
    /* Load binary on cold boot or if ULP memory was reset */
    uint32_t causes = esp_sleep_get_wakeup_causes();
    if (!(causes & BIT(ESP_SLEEP_WAKEUP_ULP))) {
        ESP_LOGI(TAG, "Loading ULP-RISC-V Coprocessor binary...");
        esp_err_t err = ulp_riscv_load_binary(ulp_h1os_bin_start, (size_t)(ulp_h1os_bin_end - ulp_h1os_bin_start));
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "ulp_riscv_load_binary failed: %s", esp_err_to_name(err));
            return err;
        }

        /* 1. Initialize ADC1 Oneshot and calibration handles prior to calibration extraction */
        sub_power_init();

        /* 2. Pass eFuse linear battery calibration parameters into ULP exported symbols */
        sub_power_get_ulp_cal_params((uint32_t *)&ulp_cal_scale, (int32_t *)&ulp_cal_offset);
        ESP_LOGI(TAG, "ULP battery linear calibration primed: scale=%lu, offset=%ld mV",
                 (unsigned long)ulp_cal_scale, (long)ulp_cal_offset);
        ulp_dispatch_reason  = 0;
        ulp_last_wake_btn    = 0;
        ulp_last_vbat_mv     = 4000;

        /* Set periodic timer wakeup period (Flow A sample interval, e.g. 60s) */
        uint32_t period_sec = (flow_a_period_sec > 0) ? flow_a_period_sec : 60;
        ulp_set_wakeup_period(0, (uint64_t)period_sec * 1000000ULL);

        /* Configure ULP to wake on GPIO wakeup source per reference architecture (Pure Event Mode) */
        ulp_riscv_cfg_t cfg = {
            .wakeup_source = ULP_RISCV_WAKEUP_SOURCE_GPIO,
        };
        err = ulp_riscv_config_and_run(&cfg);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "ulp_riscv_config_and_run failed: %s", esp_err_to_name(err));
            return err;
        }

        /* Ensure periodic hardware sleep timer is strictly disabled to prevent PMU arbitration lockup (ERR-001) */
        CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN);
        SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);

        /* Release RTC domain GPIO control back to HP digital matrix so HP application can read buttons during active boot session */
        rtc_gpio_deinit(HAL_PIN_BUTTON_BOOT);
        rtc_gpio_deinit(HAL_PIN_BUTTON_POWER);
        rtc_gpio_deinit(HAL_PIN_RTC_INT);

        ESP_LOGI(TAG, "ULP-RISC-V Coprocessor initialized in Pure Event Mode (ERR-001 Mitigated)");
    }
    return ESP_OK;
}

esp_err_t sub_power_enter_deep_sleep_mode(uint32_t sleep_seconds, uint64_t ext1_pins_mask, sub_power_sleep_mode_t mode)
{
    (void)sleep_seconds;
    (void)ext1_pins_mask;

    hal_io_isolate_sleep_pads();

    /* 1. Calculate dynamic slicing ratio and remainder for Two-Stage RTC Arming */
    uint32_t flow_a_sec = orch_state_get()->sample_interval_sec;
    uint32_t flow_b_sec = orch_state_get()->flow_b_period_sec;
    if (flow_a_sec == 0) flow_a_sec = 60;
    if (flow_b_sec == 0) flow_b_sec = 300;

    uint32_t full_slices = flow_b_sec / flow_a_sec;
    uint32_t remainder   = flow_b_sec % flow_a_sec;
    /* Total ticks to reach Flow B: full slices + 1 remainder tick (if remainder > 0) */
    uint32_t overflow = full_slices + (remainder > 0 ? 1 : 0);
    if (overflow == 0) overflow = 1;

    if (mode == SUB_POWER_SLEEP_FULL_CYCLE) {
        /* Arm external PCF85063A countdown timer in repetitive pulsed mode for base Flow A period */
        sub_rtc_arm_countdown(flow_a_sec);
    }

    ulp_overflow_limit = overflow;
    if (mode == SUB_POWER_SLEEP_FULL_CYCLE) {
        ulp_slice_counter = 0;
    }
    ulp_dispatch_reason  = 0;
    ulp_rtc_int_stuck    = 0;
    ulp_usb_connected    = sub_power_connected_usb() ? 1 : 0;
    asm volatile("memw" ::: "memory");

    ESP_LOGI(TAG, "Event Mode Slicing [%s]: Tick=%lus, Target=%lus -> FullSlices=%lu, Remainder=%lus -> TotalOverflowLimit=%lu (SliceAcc=%lu, USB=%lu)",
             (mode == SUB_POWER_SLEEP_FULL_CYCLE) ? "FULL_CYCLE" : "FLOW_A_BURST",
             (unsigned long)flow_a_sec, (unsigned long)flow_b_sec,
             (unsigned long)full_slices, (unsigned long)remainder,
             (unsigned long)overflow, (unsigned long)ulp_slice_counter,
             (unsigned long)ulp_usb_connected);

    const gpio_num_t wake_pins[] = {HAL_PIN_BUTTON_BOOT, HAL_PIN_BUTTON_POWER, HAL_PIN_RTC_INT};
    for (size_t i = 0; i < sizeof(wake_pins) / sizeof(wake_pins[0]); i++) {
        gpio_num_t pin = wake_pins[i];
        
        /* 1. Route pad to RTC subsystem */
        rtc_gpio_init(pin);
        rtc_gpio_set_direction(pin, RTC_GPIO_MODE_INPUT_ONLY);
        
        /* 2. Disarm any lingering pad hold on wake inputs */
        rtc_gpio_hold_dis(pin);

        /* 3. Configure pull-ups/pull-downs */
        if (pin == HAL_PIN_RTC_INT) {
            rtc_gpio_pullup_en(pin);
            rtc_gpio_pulldown_dis(pin);
        } else {
            rtc_gpio_pullup_dis(pin); // External 10k pull-ups on PCB
            rtc_gpio_pulldown_dis(pin);
        }

        /* 4. Enable level-low wake (sets int_type and wakeup_enable in RTCIO) */
        rtc_gpio_wakeup_enable(pin, GPIO_INTR_LOW_LEVEL);
    }

    /* Route Battery ADC (GPIO 4) to RTC analog subsystem for ULP sampling (no wakeup bits) */
    rtc_gpio_init(HAL_PIN_BATTERY_ADC);
    rtc_gpio_set_direction(HAL_PIN_BATTERY_ADC, RTC_GPIO_MODE_INPUT_ONLY);
    rtc_gpio_pullup_dis(HAL_PIN_BATTERY_ADC);
    rtc_gpio_pulldown_dis(HAL_PIN_BATTERY_ADC);
    rtc_gpio_hold_dis(HAL_PIN_BATTERY_ADC);

    /* ULP coprocessor wake source for the main application */
    esp_sleep_enable_ulp_wakeup();

    /* Install RTC Fast Memory deep sleep wake stub (<3ms Flow A sensor burst) */
    orch_wake_stub_install();

    /* Centralized PCF85063A open-drain pulse drain barrier:
     * Wait for external PCF85063A ~15.6ms pulse on GPIO 5 to release HIGH before clearing latches.
     * Bounded to 50ms timeout. Entering sleep or clearing latches while line is LOW causes
     * immediate false wake loops, missed edge transitions, and PMU lockups (ERR-S4)! */
    uint32_t drain_wait_us = 0;
    while (gpio_get_level(HAL_PIN_RTC_INT) == 0 && drain_wait_us < 50000) {
        esp_rom_delay_us(500);
        drain_wait_us += 500;
    }

    /* 5. Clear lingering latches & enforce Pure Event Mode: TIMER_EN = 0, GPIO_WAKEUP_ENA = 1 */
    REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);
    REG_WRITE(RTC_CNTL_INT_CLR_REG, RTC_CNTL_COCPU_INT_CLR | RTC_CNTL_COCPU_TRAP_INT_CLR | RTC_CNTL_ULP_CP_INT_CLR);
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
    esp_rom_delay_us(120); /* Guaranteed >= 3.9 RTC_SLOW_CLK cycles on XTAL32K */
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN);
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);

    /* 6. Allow slow clock domain synchronization delay (>= 4 RTC_SLOW_CLK cycles) */
    esp_rom_delay_us(120);

    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);

    ESP_LOGI(TAG, "Pre-Sleep Audit: ULP_CP_TIMER=0x%08lx, GPIO_STATUS=0x%08lx",
             (unsigned long)REG_READ(RTC_CNTL_ULP_CP_TIMER_REG),
             (unsigned long)REG_READ(RTC_GPIO_STATUS_REG));
    ESP_LOGI(TAG, "RTC Wake Audit: PIN0(BOOT)=0x%08lx, PIN5(RTC)=0x%08lx, PIN18(PWR)=0x%08lx",
             (unsigned long)REG_READ(RTC_GPIO_PIN0_REG + (4 * 0)),
             (unsigned long)REG_READ(RTC_GPIO_PIN0_REG + (4 * 5)),
             (unsigned long)REG_READ(RTC_GPIO_PIN0_REG + (4 * 18)));
    /* Two-Domain Architecture Invariant (Doc 13):
     * Digital pad auto-hold (GPIO 42 PA_EN, GPIO 46 PA_CTRL) was already cleanly armed
     * in hal_io_isolate_sleep_pads(). RTC IO pads (GPIO 0..21) are governed exclusively
     * by RTC_CNTL_PAD_HOLD_REG and are strictly unheld for wake inputs (IO0, IO18, IO5, IO4). */

    ESP_LOGI(TAG, "Entering deep sleep in Pure Event Mode (Timer: PCF85063A %lus pulse, Slices: %lu, Wake: ULP)...",
             (unsigned long)flow_a_sec, (unsigned long)overflow);
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
    ESP_LOGI(TAG, "USB is %s", usb_state ? "Connected" : "NOT Connected");
    return usb_state;
}
