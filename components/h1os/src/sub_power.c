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
#include "soc/rtc_io_reg.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
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
        ulp_cycles_per_ms    = 17500;

        /* Set periodic timer wakeup period (Flow A sample interval, e.g. 60s) */
        uint32_t period_sec = (flow_a_period_sec > 0) ? flow_a_period_sec : 60;
        ulp_set_wakeup_period(0, (uint64_t)period_sec * 1000000ULL);

        /* Configure ULP to wake on GPIO wakeup source per reference architecture */
        ulp_riscv_cfg_t cfg = {
            .wakeup_source = ULP_RISCV_WAKEUP_SOURCE_GPIO,
        };
        err = ulp_riscv_config_and_run(&cfg);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "ulp_riscv_config_and_run failed: %s", esp_err_to_name(err));
            return err;
        }

        /* Arm periodic sleep timer alongside GPIO wakeup in RTC_CNTL_ULP_CP_TIMER_REG */
        SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN);

        /* Release RTC domain GPIO control back to HP digital matrix so HP application can read buttons during active boot session */
        rtc_gpio_deinit(HAL_PIN_BUTTON_BOOT);
        rtc_gpio_deinit(HAL_PIN_BUTTON_POWER);
        rtc_gpio_deinit(HAL_PIN_RTC_INT);

        ESP_LOGI(TAG, "ULP-RISC-V Coprocessor initialized and running (Period: %lu s, Timing: %lu cycles/ms)",
                 (unsigned long)period_sec, (unsigned long)ulp_cycles_per_ms);
    }
    return ESP_OK;
#else
    return ESP_ERR_NOT_SUPPORTED;
#endif
}

esp_err_t sub_power_enter_deep_sleep(uint32_t sleep_seconds, uint64_t ext1_pins_mask)
{
    (void)sleep_seconds;
    (void)ext1_pins_mask;

    /* Latch critical rails, isolate sleep pads, and configure RTC IO wakeups strictly in RTC domain */
    hal_io_isolate_sleep_pads();

#if CONFIG_ULP_COPROC_ENABLED
    /* Reset exported ULP dispatch and button variables before entering sleep */
    ulp_dispatch_reason  = 0;
    ulp_last_wake_btn    = 0;
    ulp_cycles_per_ms    = 17500;
    ulp_last_wake_cause  = 0;
    ulp_hold_duration_ms = 0;

    /* Arm per-pin RTC GPIO wakeup comparator & low-level trigger on Main CPU before sleep */
    const gpio_num_t wake_pins[] = {HAL_PIN_BUTTON_BOOT, HAL_PIN_BUTTON_POWER, HAL_PIN_RTC_INT};
    for (size_t i = 0; i < sizeof(wake_pins) / sizeof(wake_pins[0]); i++) {
        gpio_num_t pin = wake_pins[i];
        rtc_gpio_init(pin);                                    /* sets MUX_SEL, routes pad to RTC domain */
        rtc_gpio_set_direction(pin, RTC_GPIO_MODE_INPUT_ONLY); /* enables FUN_IE in RTC domain */
        if (pin == HAL_PIN_RTC_INT) {
            rtc_gpio_pullup_en(pin);                           /* open-drain PCF85063A INT line requires pull-up */
            rtc_gpio_pulldown_dis(pin);
        } else {
            rtc_gpio_pullup_dis(pin);                          /* buttons have external 10k pull-ups on PCB */
            rtc_gpio_pulldown_dis(pin);
        }
        rtc_gpio_hold_en(pin);                                 /* preserve pad configuration across sleep */
        SET_PERI_REG_MASK(RTC_GPIO_PIN0_REG + 4 * pin, RTC_GPIO_PIN0_WAKEUP_ENABLE);
        REG_SET_FIELD    (RTC_GPIO_PIN0_REG + 4 * pin, RTC_GPIO_PIN0_INT_TYPE, 4 /* ULP_RISCV_GPIO_INTR_LOW_LEVEL */);
    }

    /* Strict Architectural Invariant: ONLY the ULP coprocessor wakes the main application */
    esp_sleep_enable_ulp_wakeup();

    /* Clear any lingering GPIO wakeup latch and arm both ULP periodic sleep timer AND RTC GPIO wakeup */
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG,
                      RTC_CNTL_ULP_CP_SLP_TIMER_EN | RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);
#endif

    /* Keep RTC domain powered so ULP and RTC pad holds remain active */
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);

    ESP_LOGI(TAG, "RTC Wake Armed: PIN0=0x%08" PRIx32 ", PIN18=0x%08" PRIx32 ", PIN5=0x%08" PRIx32 ", TIMER_REG=0x%08" PRIx32 ", STATUS=0x%08" PRIx32,
             (uint32_t)REG_READ(RTC_GPIO_PIN0_REG),
             (uint32_t)REG_READ(RTC_GPIO_PIN0_REG + 4 * HAL_PIN_BUTTON_POWER),
             (uint32_t)REG_READ(RTC_GPIO_PIN0_REG + 4 * HAL_PIN_RTC_INT),
             (uint32_t)REG_READ(RTC_CNTL_ULP_CP_TIMER_REG),
             (uint32_t)REG_READ(RTC_GPIO_STATUS_REG));

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

#if CONFIG_ULP_COPROC_ENABLED
esp_err_t sub_power_proof_of_life_test(void)
{
    esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();
    uint32_t causes_mask = esp_sleep_get_wakeup_causes();

    ESP_LOGI("PROOF_OF_LIFE", "================================================================================");
    ESP_LOGI("PROOF_OF_LIFE", "                     H1OS HARDWARE PROOF-OF-LIFE CHECK                          ");
    ESP_LOGI("PROOF_OF_LIFE", "================================================================================");
    ESP_LOGI("PROOF_OF_LIFE", "Boot / Wakeup Cause from SoC: %d (mask=0x%08" PRIx32 ")", (int)cause, causes_mask);

    if (cause == ESP_SLEEP_WAKEUP_ULP || (causes_mask & BIT(ESP_SLEEP_WAKEUP_ULP))) {
        const char *cause_str = "UNKNOWN";
        if (ulp_last_wake_cause == 1) cause_str = "BOOT BUTTON (GPIO 0)";
        else if (ulp_last_wake_cause == 2) cause_str = "POWER BUTTON (GPIO 18)";
        else if (ulp_last_wake_cause == 3) cause_str = "PERIODIC TIMER TICK (10s)";
        else if (ulp_last_wake_cause == 4) cause_str = "RTC ALARM (GPIO 5)";

        ESP_LOGI("PROOF_OF_LIFE", ">>> MAIN CPU WOKEN BY ULP COPICROPROCESSOR! <<<");
        ESP_LOGI("PROOF_OF_LIFE", "ULP Wake Counter:   %" PRIu32, (uint32_t)ulp_wake_counter);
        ESP_LOGI("PROOF_OF_LIFE", "ULP Detected Cause: %s (%" PRIu32 ")", cause_str, (uint32_t)ulp_last_wake_cause);
        ESP_LOGI("PROOF_OF_LIFE", "ULP Latched Status: 0x%08" PRIx32, (uint32_t)ulp_gpio_status_raw);
        ESP_LOGI("PROOF_OF_LIFE", "ULP Button ID:      %" PRIu32, (uint32_t)ulp_last_wake_btn);
        ESP_LOGI("PROOF_OF_LIFE", "================================================================================");
        vTaskDelay(pdMS_TO_TICKS(2500));
    } else {
        ESP_LOGI("PROOF_OF_LIFE", "Cold boot detected. Loading ULP binary into RTC Slow SRAM...");
        esp_err_t err = ulp_riscv_load_binary(ulp_h1os_bin_start, (size_t)(ulp_h1os_bin_end - ulp_h1os_bin_start));
        if (err != ESP_OK) {
            ESP_LOGE("PROOF_OF_LIFE", "Failed to load ULP binary: %s", esp_err_to_name(err));
            return err;
        }
    }

    /* 1. Configure RTC wake pins:
     * Strict Rule: DO NOT call rtc_gpio_hold_en() on input pins! */
    const gpio_num_t wake_pins[] = {HAL_PIN_BUTTON_BOOT, HAL_PIN_BUTTON_POWER, HAL_PIN_RTC_INT};
    for (size_t i = 0; i < sizeof(wake_pins) / sizeof(wake_pins[0]); i++) {
        gpio_num_t pin = wake_pins[i];
        rtc_gpio_init(pin);                                    /* MUX_SEL = 1, LP clock enabled */
        rtc_gpio_set_direction(pin, RTC_GPIO_MODE_INPUT_ONLY); /* FUN_IE = 1 */
        if (pin == HAL_PIN_RTC_INT) {
            rtc_gpio_pullup_en(pin);                           /* Open-drain PCF85063A INT */
            rtc_gpio_pulldown_dis(pin);
        } else {
            rtc_gpio_pullup_dis(pin);                          /* Hardware 10k pull-up on PCB */
            rtc_gpio_pulldown_dis(pin);
        }

        /* Arm comparator: WAKEUP_ENABLE = 1, INT_TYPE = 4 (LOW_LEVEL) */
        SET_PERI_REG_MASK(RTC_GPIO_PIN0_REG + 4 * pin, RTC_GPIO_PIN0_WAKEUP_ENABLE);
        REG_SET_FIELD(RTC_GPIO_PIN0_REG + 4 * pin, RTC_GPIO_PIN0_INT_TYPE, 4);
    }

    /* 2. Program 10-second periodic timer */
    ulp_set_wakeup_period(0, 10000000ULL); // 10 seconds in microseconds

    /* 3. Arm dual wakeup: GPIO wakeup + Sleep timer */
    ulp_riscv_cfg_t cfg = {
        .wakeup_source = ULP_RISCV_WAKEUP_SOURCE_GPIO,
    };
    ulp_riscv_config_and_run(&cfg);
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG,
                      RTC_CNTL_ULP_CP_SLP_TIMER_EN | RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);

    /* 4. Allow ULP to wake the main CPU */
    esp_sleep_enable_ulp_wakeup();
    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);

    ESP_LOGI("PROOF_OF_LIFE", "--------------------------------------------------------------------------------");
    ESP_LOGI("PROOF_OF_LIFE", "Armed dual-wake: PIN0=0x%08" PRIx32 ", PIN18=0x%08" PRIx32 ", PIN5=0x%08" PRIx32 ", TIMER_REG=0x%08" PRIx32,
             (uint32_t)REG_READ(RTC_GPIO_PIN0_REG),
             (uint32_t)REG_READ(RTC_GPIO_PIN0_REG + 4 * HAL_PIN_BUTTON_POWER),
             (uint32_t)REG_READ(RTC_GPIO_PIN0_REG + 4 * HAL_PIN_RTC_INT),
             (uint32_t)REG_READ(RTC_CNTL_ULP_CP_TIMER_REG));
    ESP_LOGI("PROOF_OF_LIFE", "Entering deep sleep NOW. Tap BOOT/POWER to test GPIO wake, or wait 10s for TIMER wake!");
    ESP_LOGI("PROOF_OF_LIFE", "--------------------------------------------------------------------------------");

    esp_deep_sleep_start();
    return ESP_OK;
}
#else
esp_err_t sub_power_proof_of_life_test(void)
{
    ESP_LOGE("PROOF_OF_LIFE", "ULP Coprocessor not enabled in sdkconfig!");
    return ESP_ERR_NOT_SUPPORTED;
}
#endif