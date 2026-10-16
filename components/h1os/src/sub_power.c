/**
 * @file sub_power.c
 * @brief Layer 2: Battery ADC Monitoring & Deep Sleep Hardware Driver Implementation
 *
 * SPDX-License-Identifier: MIT
 */

#include "h1os/sub_power.h"
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
#include <stdlib.h>

#if CONFIG_ULP_COPROC_ENABLED
#include "ulp_riscv.h"
#include "ulp_h1os.h"

extern const uint8_t ulp_h1os_bin_start[] asm("_binary_ulp_h1os_bin_start");
extern const uint8_t ulp_h1os_bin_end[]   asm("_binary_ulp_h1os_bin_end");
#endif

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

    /* 1. Initialize ADC1 Oneshot Unit */
    adc_oneshot_unit_init_cfg_t unit_cfg = {
        .unit_id  = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_DISABLE,
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

static int compare_int(const void *a, const void *b) {
    return (*(const int *)a - *(const int *)b);
}

esp_err_t sub_power_read_battery(uint16_t *out_mv, uint8_t *out_pct)
{
    if (out_mv == NULL) return ESP_ERR_INVALID_ARG;
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

    qsort(samples, 16, sizeof(int), compare_int);

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
#if CONFIG_ULP_COPROC_ENABLED
    /* Load binary on cold boot or if ULP memory was reset */
    uint32_t causes = esp_sleep_get_wakeup_causes();
    if (!(causes & BIT(ESP_SLEEP_WAKEUP_ULP))) {
        ESP_LOGI(TAG, "Loading ULP-RISC-V Coprocessor binary...");
        esp_err_t err = ulp_riscv_load_binary(ulp_h1os_bin_start, (size_t)(ulp_h1os_bin_end - ulp_h1os_bin_start));
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "ulp_riscv_load_binary failed: %s", esp_err_to_name(err));
            return err;
        }

        /* Pass battery calibration parameters into ULP exported symbols */
        uint32_t scale = 3100;
        int32_t offset = 0;
        sub_power_get_ulp_cal_params(&scale, &offset);
        ulp_cal_scale        = scale;
        ulp_cal_offset       = offset;
        ulp_vbat_critical_mv = 3250;
        ulp_last_vbat_mv     = 4000;
        ulp_dispatch_reason  = 0;
        ulp_last_wake_btn    = 0;

        /* Set periodic timer wakeup period (Flow A sample interval, e.g. 60s) */
        uint32_t period_sec = (flow_a_period_sec > 0) ? flow_a_period_sec : 60;
        ulp_set_wakeup_period(0, (uint64_t)period_sec * 1000000ULL);

        /* Configure ULP to wake on periodic timer */
        ulp_riscv_cfg_t cfg = {
            .wakeup_source = ULP_RISCV_WAKEUP_SOURCE_TIMER,
        };
        err = ulp_riscv_config_and_run(&cfg);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "ulp_riscv_config_and_run failed: %s", esp_err_to_name(err));
            return err;
        }

        /* Enable GPIO wakeups in RTC_CNTL_ULP_CP_TIMER_REG alongside the sleep timer */
        SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);

        ESP_LOGI(TAG, "ULP-RISC-V Coprocessor initialized and running (Period: %lu s)", (unsigned long)period_sec);
    }
    return ESP_OK;
#else
    return ESP_ERR_NOT_SUPPORTED;
#endif
}

esp_err_t sub_power_enter_deep_sleep(uint32_t sleep_seconds, uint64_t ext1_pins_mask)
{
    /* Latch critical rails and freeze pad states with RTC pad holds */
    hal_io_isolate_sleep_pads();

#if CONFIG_ULP_COPROC_ENABLED
    /* ULP coprocessor wakeup is enabled via ULP runtime */
    esp_sleep_enable_ulp_wakeup();

    /* Enable GPIO wakeups in the RTC domain strictly for the ULP Coprocessor:
     * On ESP32-S3, gpio_wakeup_enable() configures the RTC IO controller.
     * When coupled with RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA and esp_sleep_enable_ulp_wakeup(),
     * IO transitions wake the ULP-RISC-V coprocessor, NOT the Xtensa CPU directly.
     * The ULP coprocessor evaluates pin states, debounces transitions, and only wakes
     * the main application (Xtensa) via ulp_riscv_wakeup_main_processor() if valid. */
    gpio_wakeup_enable(HAL_PIN_BUTTON_BOOT, GPIO_INTR_LOW_LEVEL);
    gpio_wakeup_enable(HAL_PIN_BUTTON_POWER, GPIO_INTR_LOW_LEVEL);
    gpio_wakeup_enable(HAL_PIN_RTC_INT, GPIO_INTR_LOW_LEVEL);
#else
    /* Non-ULP build: Fallback to direct EXT1 wakeup for Xtensa CPU */
    if (ext1_pins_mask != 0) {
        esp_sleep_enable_ext1_wakeup(ext1_pins_mask, ESP_EXT1_WAKEUP_ANY_LOW);
    }
#endif

    (void)sleep_seconds;

    /* Keep RTC domain powered so ULP and RTC pad holds remain active */
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);

    ESP_LOGI(TAG, "Entering deep sleep with ULP Coprocessor reactive monitor...");
    esp_deep_sleep_start();
    return ESP_OK;
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