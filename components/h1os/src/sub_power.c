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
#include <stdlib.h>

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

esp_err_t sub_power_enter_deep_sleep(uint32_t sleep_seconds, uint64_t ext1_pins_mask)
{
    /* Latch critical rails and freeze pad states with RTC pad holds */
    hal_io_isolate_sleep_pads();

    if (ext1_pins_mask != 0) {
        esp_sleep_enable_ext1_wakeup(ext1_pins_mask, ESP_EXT1_WAKEUP_ANY_LOW);
    }

    if (sleep_seconds > 0) {
        esp_sleep_enable_timer_wakeup((uint64_t)sleep_seconds * 1000000ULL);
    }

    /* ULP coprocessor wakeup is enabled via ULP runtime */
    esp_sleep_enable_ulp_wakeup();

    /* Install RTC Wake Stub for <3ms Flow A autonomous sensor sampling */
    orch_wake_stub_install();

    ESP_LOGI(TAG, "Entering deep sleep (%lu sec)...", (unsigned long)sleep_seconds);
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