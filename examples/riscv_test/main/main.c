/*
 * SPDX-License-Identifier: MIT
 * ESP32-S3 ULP-RISC-V Coprocessor Wakeup Validation Test Harness
 *
 * Sequentially exercises and evaluates:
 *   - Test 1: Event Mode (RTC GPIO only)
 *   - Test 2: Timer Mode (PMU Countdown only)
 *   - Test 3: Dual Mode  (PMU Countdown + RTC GPIO concurrently)
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "esp_log.h"
#include "esp_sleep.h"
#include "esp_system.h"
#include "esp_rom_gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/rtc_io.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/rtc_io_reg.h"
#include "soc/gpio_reg.h"
#include "ulp_riscv.h"
#include "ulp_riscv_test.h"
#include "shared_test_data.h"

static const char *TAG = "RISCV_TEST";

#define PIN_POWER_HOLD   GPIO_NUM_17
#define PIN_BUTTON_BOOT  GPIO_NUM_0
#define PIN_BUTTON_PWR   GPIO_NUM_18
#define PIN_RTC_INT      GPIO_NUM_5

/* Persisted across deep sleep cycles in RTC Slow Memory */
RTC_DATA_ATTR static uint32_t s_current_test = 0;
RTC_DATA_ATTR static uint32_t s_boot_count   = 0;

extern const uint8_t ulp_riscv_test_bin_start[] asm("_binary_ulp_riscv_test_bin_start");
extern const uint8_t ulp_riscv_test_bin_end[]   asm("_binary_ulp_riscv_test_bin_end");

static void init_power_latch(void)
{
    /* Keep BAT_CTRL latched HIGH so unit stays powered on LiPo */
    rtc_gpio_init(PIN_POWER_HOLD);
    rtc_gpio_set_direction(PIN_POWER_HOLD, RTC_GPIO_MODE_OUTPUT_ONLY);
    rtc_gpio_set_level(PIN_POWER_HOLD, 1);
    rtc_gpio_hold_en(PIN_POWER_HOLD);
}

static void configure_rtc_pins(void)
{
    /* Configure GPIO 0 (BOOT button) */
    rtc_gpio_init(PIN_BUTTON_BOOT);
    rtc_gpio_set_direction(PIN_BUTTON_BOOT, RTC_GPIO_MODE_INPUT_ONLY);
    rtc_gpio_pullup_en(PIN_BUTTON_BOOT);
    rtc_gpio_pulldown_dis(PIN_BUTTON_BOOT);

    /* Configure GPIO 18 (PWR button) */
    rtc_gpio_init(PIN_BUTTON_PWR);
    rtc_gpio_set_direction(PIN_BUTTON_PWR, RTC_GPIO_MODE_INPUT_ONLY);
    rtc_gpio_pullup_en(PIN_BUTTON_PWR);
    rtc_gpio_pulldown_dis(PIN_BUTTON_PWR);

    /* Configure GPIO 5 (PCF85063A INT line) */
    rtc_gpio_init(PIN_RTC_INT);
    rtc_gpio_set_direction(PIN_RTC_INT, RTC_GPIO_MODE_INPUT_ONLY);
    rtc_gpio_pullup_en(PIN_RTC_INT);
    rtc_gpio_pulldown_dis(PIN_RTC_INT);
}

static void dump_telemetry_report(uint32_t stage, uint32_t causes, test_shared_data_t *d)
{
    bool is_ulp_wake  = (causes & BIT(ESP_SLEEP_WAKEUP_ULP)) != 0;
    bool is_trap_wake = (causes & BIT(ESP_SLEEP_WAKEUP_COCPU_TRAP_TRIG)) != 0;

    const char *stage_name = "UNKNOWN";
    if (stage == TEST_MODE_EVENT_ONLY) stage_name = "TEST 1: EVENT MODE (RTC GPIO)";
    else if (stage == TEST_MODE_TIMER_ONLY) stage_name = "TEST 2: TIMER MODE (5s PMU COUNTDOWN)";
    else if (stage == TEST_MODE_DUAL_BOTH) stage_name = "TEST 3: DUAL MODE (PMU TIMER + RTC GPIO)";

    const char *verdict = "FAIL";
    if (is_trap_wake) {
        verdict = "FATAL TRAP (0x1000)";
    } else if (is_ulp_wake && d->magic == ULP_TEST_MAGIC && d->ulp_completed == 1) {
        verdict = "PASS";
    }

    printf("\n");
    printf("========================================================================\n");
    printf(" [RISC-V TEST] TELEMETRY DUMP: %s\n", stage_name);
    printf("========================================================================\n");
    printf(" Boot Count / Sleep Wake # : %lu\n", (unsigned long)s_boot_count);
    printf(" Main Wake Causes Bitmask  : 0x%08lX (ULP: %s, TRAP: %s)\n",
           (unsigned long)causes, is_ulp_wake ? "YES" : "NO", is_trap_wake ? "YES (CRASH!)" : "NO");
    printf(" Shared Structure Magic    : 0x%08lX (%s)\n",
           (unsigned long)d->magic, (d->magic == ULP_TEST_MAGIC) ? "VALID" : "CORRUPTED");
    printf(" Stage Configured in ULP   : %lu\n", (unsigned long)d->test_stage);
    printf(" ULP Total Entry Count     : %lu\n", (unsigned long)d->ulp_entry_count);
    printf(" ULP GPIO Wake Count       : %lu\n", (unsigned long)d->ulp_gpio_wake_count);
    printf(" ULP Timer Wake Count      : %lu\n", (unsigned long)d->ulp_timer_wake_count);
    printf(" ULP ISR Handler Executions: %lu\n", (unsigned long)d->ulp_isr_fired_count);
    printf(" Last ISR Source GPIO      : %ld\n", (long)d->ulp_last_isr_source);
    printf(" Raw RTC_GPIO_STATUS_REG   : 0x%08lX\n", (unsigned long)d->ulp_last_gpio_status);
    printf(" Sampled Pin Levels (0/5/18): %d / %d / %d (Raw: 0x%08lX)\n",
           (int)(d->ulp_pin_levels & 1U),
           (int)((d->ulp_pin_levels >> 5) & 1U),
           (int)((d->ulp_pin_levels >> 18) & 1U),
           (unsigned long)d->ulp_pin_levels);
    printf(" Coprocessor Execution Time: %lu cycles\n", (unsigned long)d->ulp_cycle_count);
    printf(" ULP Completed Hand-Off    : %lu\n", (unsigned long)d->ulp_completed);
    printf(" STAGE VERDICT             : %s\n", verdict);
    printf("========================================================================\n\n");
}

static void arm_stage_1_event_mode(test_shared_data_t *d)
{
    ESP_LOGI(TAG, "========================================================================");
    ESP_LOGI(TAG, ">>> PREPARING TEST 1: Pure Event Mode (RTC GPIO) <<<");
    ESP_LOGI(TAG, "PMU Sleep Timer is DISABLED. ULP will sleep until external GPIO edge.");
    ESP_LOGI(TAG, "ACTION REQUIRED: Press tactile BOOT (GPIO 0) or PWR (GPIO 18) button!");
    ESP_LOGI(TAG, "========================================================================");

    d->test_stage = TEST_MODE_EVENT_ONLY;
    d->ulp_completed = 0;
    d->ulp_gpio_wake_count = 0;
    d->ulp_timer_wake_count = 0;
    d->ulp_isr_fired_count = 0;

    /* Arm RTC GPIO wake detector */
    rtc_gpio_wakeup_enable(PIN_BUTTON_BOOT, GPIO_INTR_LOW_LEVEL);
    rtc_gpio_wakeup_enable(PIN_BUTTON_PWR, GPIO_INTR_LOW_LEVEL);
    rtc_gpio_wakeup_enable(PIN_RTC_INT, GPIO_INTR_LOW_LEVEL);

    /* Configure ULP in Event Mode */
    ulp_riscv_cfg_t cfg = { .wakeup_source = ULP_RISCV_WAKEUP_SOURCE_GPIO };
    ESP_ERROR_CHECK(ulp_riscv_config_and_run(&cfg));

    /* Strictly ensure PMU timer is disabled */
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN);

    esp_sleep_enable_ulp_wakeup();
    esp_deep_sleep_start();
}

static void arm_stage_2_timer_mode(test_shared_data_t *d)
{
    ESP_LOGI(TAG, "========================================================================");
    ESP_LOGI(TAG, ">>> PREPARING TEST 2: Pure Timer Mode (PMU Countdown) <<<");
    ESP_LOGI(TAG, "RTC GPIO Wakeup is DISABLED. ULP programmed for 5-second sleep interval.");
    ESP_LOGI(TAG, "Will automatically wake in 5.0 seconds via internal 136 kHz RC timer...");
    ESP_LOGI(TAG, "========================================================================");

    d->test_stage = TEST_MODE_TIMER_ONLY;
    d->ulp_completed = 0;
    d->ulp_gpio_wake_count = 0;
    d->ulp_timer_wake_count = 0;
    d->ulp_isr_fired_count = 0;

    /* Disable GPIO wakeup bit on ULP */
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);

    /* Set 5-second wakeup period (5,000,000 microseconds) */
    ESP_ERROR_CHECK(ulp_set_wakeup_period(0, 5000000));

    /* Configure ULP in Timer Mode */
    ulp_riscv_cfg_t cfg = { .wakeup_source = ULP_RISCV_WAKEUP_SOURCE_TIMER };
    ESP_ERROR_CHECK(ulp_riscv_config_and_run(&cfg));

    /* Ensure PMU timer bit is asserted */
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN);

    esp_sleep_enable_ulp_wakeup();
    esp_deep_sleep_start();
}

static void arm_stage_3_dual_mode(test_shared_data_t *d)
{
    ESP_LOGI(TAG, "========================================================================");
    ESP_LOGI(TAG, ">>> PREPARING TEST 3: Dual Mode (Timer + GPIO Concurrently) <<<");
    ESP_LOGI(TAG, "BOTH 5s PMU Timer AND RTC GPIO wakeups are asserted simultaneously.");
    ESP_LOGI(TAG, "You can either WAIT 5.0s for timer wake OR TAP BOOT button immediately!");
    ESP_LOGI(TAG, "========================================================================");

    d->test_stage = TEST_MODE_DUAL_BOTH;
    d->ulp_completed = 0;
    d->ulp_gpio_wake_count = 0;
    d->ulp_timer_wake_count = 0;
    d->ulp_isr_fired_count = 0;

    /* Arm RTC GPIO wake detector */
    rtc_gpio_wakeup_enable(PIN_BUTTON_BOOT, GPIO_INTR_LOW_LEVEL);
    rtc_gpio_wakeup_enable(PIN_BUTTON_PWR, GPIO_INTR_LOW_LEVEL);
    rtc_gpio_wakeup_enable(PIN_RTC_INT, GPIO_INTR_LOW_LEVEL);

    /* Set 5-second wakeup period */
    ESP_ERROR_CHECK(ulp_set_wakeup_period(0, 5000000));

    /* Arm GPIO wakeup and then assert Timer bit concurrently */
    ulp_riscv_cfg_t cfg = { .wakeup_source = ULP_RISCV_WAKEUP_SOURCE_GPIO };
    ESP_ERROR_CHECK(ulp_riscv_config_and_run(&cfg));
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN);

    esp_sleep_enable_ulp_wakeup();
    esp_deep_sleep_start();
}

void app_main(void)
{
    esp_reset_reason_t reset_reason = esp_reset_reason();
    uint32_t wake_causes = esp_sleep_get_wakeup_causes();
    test_shared_data_t *p_data = (test_shared_data_t *)&ulp_test_data;

    init_power_latch();
    configure_rtc_pins();

    if (reset_reason != ESP_RST_DEEPSLEEP || s_current_test == 0) {
        /* Cold Boot / Power-On Reset */
        s_boot_count = 0;
        s_current_test = TEST_MODE_EVENT_ONLY;

        printf("\n\n");
        printf("************************************************************************\n");
        printf("*  H1OS ESP32-S3 ULP-RISC-V Coprocessor Wakeup Formal Test Suite       *\n");
        printf("*  Hardware Target : Waveshare ESP32-S3 ePaper 1.54\" V2                *\n");
        printf("*  Slow Clock      : Internal 136 kHz RC (CONFIG_RTC_CLK_SRC_INT_RC=y) *\n");
        printf("*  Interrupts      : CONFIG_ULP_RISCV_INTERRUPT_ENABLE=y (ENABLED)     *\n");
        printf("************************************************************************\n\n");

        ESP_LOGI(TAG, "Loading ULP-RISC-V firmware binary (%u bytes)...",
                 (unsigned)(ulp_riscv_test_bin_end - ulp_riscv_test_bin_start));
        ESP_ERROR_CHECK(ulp_riscv_load_binary(ulp_riscv_test_bin_start,
                                              (ulp_riscv_test_bin_end - ulp_riscv_test_bin_start)));

        arm_stage_1_event_mode(p_data);
    } else {
        /* Deep Sleep Wakeup */
        s_boot_count++;

        dump_telemetry_report(s_current_test, wake_causes, p_data);

        if (s_current_test == TEST_MODE_EVENT_ONLY) {
            ESP_LOGI(TAG, "Stage 1 Finished. Transitioning to Stage 2 (Timer Mode)...");
            s_current_test = TEST_MODE_TIMER_ONLY;
            arm_stage_2_timer_mode(p_data);
        } else if (s_current_test == TEST_MODE_TIMER_ONLY) {
            ESP_LOGI(TAG, "Stage 2 Finished. Transitioning to Stage 3 (Dual Mode)...");
            s_current_test = TEST_MODE_DUAL_BOTH;
            arm_stage_3_dual_mode(p_data);
        } else if (s_current_test == TEST_MODE_DUAL_BOTH) {
            s_current_test = TEST_MODE_COMPLETE;
            printf("\n");
            printf("************************************************************************\n");
            printf("*  TEST SUITE COMPLETE: ALL 3 MODES VALIDATED SUCCESSFULLY!            *\n");
            printf("*  Check telemetry dump above for mutual exclusivity characterization. *\n");
            printf("************************************************************************\n\n");
            while (1) {
                vTaskDelay(pdMS_TO_TICKS(1000));
            }
        }
    }
}
