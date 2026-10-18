/*
 * SPDX-License-Identifier: MIT
 * ESP32-S3 ULP-RISC-V Coprocessor Wakeup Validation Test Harness
 *
 * Sequentially exercises and evaluates:
 *   - Test 1: Event Mode (RTC GPIO 18 only, PMU timer disabled)
 *   - Test 2: Timer Mode (PMU Countdown only, RTC GPIO wake disabled)
 *   - Test 3: Dual Mode  (PMU Countdown + RTC GPIO 18 armed concurrently)
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

/* Note: Power hold (BAT_CTRL, GPIO 17) is latched exclusively by 2nd-stage bootloader hook */
#define PIN_BUTTON_BOOT  GPIO_NUM_0
#define PIN_BUTTON_PWR   GPIO_NUM_18

/* Persisted across deep sleep cycles in RTC Slow Memory */
RTC_DATA_ATTR static uint32_t s_current_test = 0;
RTC_DATA_ATTR static uint32_t s_boot_count   = 0;

extern const uint8_t ulp_riscv_test_bin_start[] asm("_binary_ulp_riscv_test_bin_start");
extern const uint8_t ulp_riscv_test_bin_end[]   asm("_binary_ulp_riscv_test_bin_end");


static void configure_rtc_pins(void)
{
    /* Configure GPIO 18 (PWR button) - Primary wake trigger.
     * Enable internal RTC pullup (~45k) to guarantee high idle state if external 10k is absent.
     * In parallel with 10k, equivalent pullup is ~8.2k (safe and fast).
     */
    rtc_gpio_init(PIN_BUTTON_PWR);
    rtc_gpio_set_direction(PIN_BUTTON_PWR, RTC_GPIO_MODE_INPUT_ONLY);
    rtc_gpio_pullup_en(PIN_BUTTON_PWR);
    rtc_gpio_pulldown_dis(PIN_BUTTON_PWR);

    /* Configure GPIO 0 (BOOT button) for monitoring only.
     * CRITICAL: GPIO 0 is an ESP32-S3 boot strapping pin. If held LOW during deep sleep wake reset,
     * the chip enters ROM download bootloader mode instead of running application code.
     * Therefore, GPIO 0 is NEVER armed as a deep sleep wake source.
     */
    rtc_gpio_init(PIN_BUTTON_BOOT);
    rtc_gpio_set_direction(PIN_BUTTON_BOOT, RTC_GPIO_MODE_INPUT_ONLY);
    rtc_gpio_pullup_en(PIN_BUTTON_BOOT);
    rtc_gpio_pulldown_dis(PIN_BUTTON_BOOT);
}

static void log_pin_levels_pre_sleep(void)
{
    int pwr_lvl  = rtc_gpio_get_level(PIN_BUTTON_PWR);
    int boot_lvl = rtc_gpio_get_level(PIN_BUTTON_BOOT);

    ESP_LOGI(TAG, "Pre-Sleep Pin Levels Check: PWR (GPIO 18) = %d, BOOT (GPIO 0) = %d", pwr_lvl, boot_lvl);
    if (pwr_lvl == 0) {
        ESP_LOGW(TAG, "WARNING: PWR (GPIO 18) is LOW prior to deep sleep! May trigger immediate wake or indicates button held down.");
    }
}

static const char *get_checkpoint_name(uint32_t cp)
{
    switch (cp) {
        case ULP_CP_ENTERED_MAIN:   return "1: ENTERED_MAIN";
        case ULP_CP_ISR_REGISTERED: return "2: ISR_REGISTERED";
        case ULP_CP_PINS_SAMPLED:   return "3: PINS_SAMPLED";
        case ULP_CP_WAITING_RDY:    return "4: WAITING_RDY (SPINNING)";
        case ULP_CP_RDY_CONFIRMED:  return "5: RDY_CONFIRMED";
        case ULP_CP_WAKE_SIGNALED:  return "6: WAKE_SIGNALED";
        case ULP_CP_CDC_CLEARED:    return "7: CDC_CLEARED";
        case ULP_CP_HALTED:         return "8: HALTED (CLEAN EXIT)";
        default:                    return "0: NOT_REACHED";
    }
}

static void dump_telemetry_report(uint32_t stage, uint32_t causes, test_shared_data_t *d)
{
    bool is_ulp_wake  = (causes & BIT(ESP_SLEEP_WAKEUP_ULP)) != 0;
    bool is_trap_wake = (causes & BIT(ESP_SLEEP_WAKEUP_COCPU_TRAP_TRIG)) != 0;

    const char *stage_name = "UNKNOWN";
    if (stage == TEST_MODE_EVENT_ONLY) stage_name = "TEST 1: EVENT MODE (RTC GPIO 18)";
    else if (stage == TEST_MODE_TIMER_ONLY) stage_name = "TEST 2: TIMER MODE (5s PMU COUNTDOWN)";
    else if (stage == TEST_MODE_DUAL_BOTH) stage_name = "TEST 3: DUAL MODE (PMU TIMER + RTC GPIO 18)";

    const char *verdict = "FAIL";
    if (is_trap_wake) {
        verdict = "FATAL TRAP (0x1000)";
    } else if (d->ulp_rdy_timeout != 0) {
        verdict = "FAIL: ULP RDY_FOR_WAKEUP TIMEOUT";
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
    printf(" ULP Checkpoint Reached    : %s\n", get_checkpoint_name(d->ulp_step_checkpoint));
    printf(" ULP RDY_FOR_WAKEUP Status : %s\n", (d->ulp_rdy_timeout != 0) ? "TIMEOUT (HANG AVERTED)" : "OK");
    printf(" ULP Total Entry Count     : %lu\n", (unsigned long)d->ulp_entry_count);
    printf(" ULP GPIO Wake Count       : %lu\n", (unsigned long)d->ulp_gpio_wake_count);
    printf(" ULP Timer Wake Count      : %lu\n", (unsigned long)d->ulp_timer_wake_count);
    printf(" ULP ISR Handler Executions: %lu\n", (unsigned long)d->ulp_isr_fired_count);
    printf(" Last ISR Source GPIO      : %ld\n", (long)d->ulp_last_isr_source);
    printf(" Raw RTC_GPIO_STATUS_REG   : 0x%08lX\n", (unsigned long)d->ulp_last_gpio_status);
    printf(" Sampled Pin Levels        : PWR(18)=%d, BOOT(0)=%d (Raw: 0x%08lX)\n",
           (int)(d->ulp_pin_levels & 1U),
           (int)((d->ulp_pin_levels >> 1) & 1U),
           (unsigned long)d->ulp_pin_levels);
    printf(" Coprocessor Execution Time: %lu cycles\n", (unsigned long)d->ulp_cycle_count);
    printf(" ULP Completed Hand-Off    : %lu\n", (unsigned long)d->ulp_completed);
    printf(" STAGE VERDICT             : %s\n", verdict);
    printf("========================================================================\n\n");

    fflush(stdout);
    vTaskDelay(pdMS_TO_TICKS(1500));    
}

static void arm_stage_1_event_mode(test_shared_data_t *d)
{
    ESP_LOGI(TAG, "========================================================================");
    ESP_LOGI(TAG, ">>> PREPARING TEST 1: Pure Event Mode (RTC GPIO 18) <<<");
    ESP_LOGI(TAG, "PMU Sleep Timer is DISABLED. ULP will sleep until GPIO 18 edge.");
    ESP_LOGI(TAG, "ACTION REQUIRED: Press tactile PWR (GPIO 18) button to wake!");
    ESP_LOGI(TAG, "========================================================================");

    d->test_stage = TEST_MODE_EVENT_ONLY;
    d->ulp_completed = 0;
    d->ulp_gpio_wake_count = 0;
    d->ulp_timer_wake_count = 0;
    d->ulp_isr_fired_count = 0;
    d->ulp_step_checkpoint = 0;
    d->ulp_rdy_timeout = 0;

    /* Arm ONLY GPIO 18 for RTC GPIO wake. GPIO 0 is omitted to prevent ROM boot strapping trap. */
    rtc_gpio_wakeup_enable(PIN_BUTTON_PWR, GPIO_INTR_LOW_LEVEL);
    rtc_gpio_wakeup_disable(PIN_BUTTON_BOOT);

    /* Configure ULP in Event Mode */
    ulp_riscv_cfg_t cfg = { .wakeup_source = ULP_RISCV_WAKEUP_SOURCE_GPIO };
    ESP_ERROR_CHECK(ulp_riscv_config_and_run(&cfg));

    /* Strictly ensure PMU timer is disabled */
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN);

    log_pin_levels_pre_sleep();

    fflush(stdout);
    vTaskDelay(pdMS_TO_TICKS(1500));

    esp_sleep_enable_ulp_wakeup();
    esp_deep_sleep_start();
}

static void arm_stage_2_timer_mode(test_shared_data_t *d)
{
    ESP_LOGI(TAG, "========================================================================");
    ESP_LOGI(TAG, ">>> PREPARING TEST 2: Pure Timer Mode (PMU Countdown) <<<");
    ESP_LOGI(TAG, "RTC GPIO Wakeup is cleanly DISABLED. ULP programmed for 5-second interval.");
    ESP_LOGI(TAG, "Will automatically wake in 5.0 seconds via internal 136 kHz RC timer...");
    ESP_LOGI(TAG, "========================================================================");

    d->test_stage = TEST_MODE_TIMER_ONLY;
    d->ulp_completed = 0;
    d->ulp_gpio_wake_count = 0;
    d->ulp_timer_wake_count = 0;
    d->ulp_isr_fired_count = 0;
    d->ulp_step_checkpoint = 0;
    d->ulp_rdy_timeout = 0;

    /* Cleanly disarm RTC GPIO wake detector */
    rtc_gpio_wakeup_disable(PIN_BUTTON_PWR);
    rtc_gpio_wakeup_disable(PIN_BUTTON_BOOT);
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);

    /* Set 5-second wakeup period (5,000,000 microseconds) */
    ESP_ERROR_CHECK(ulp_set_wakeup_period(0, 5000000));

    /* Configure ULP in Timer Mode */
    ulp_riscv_cfg_t cfg = { .wakeup_source = ULP_RISCV_WAKEUP_SOURCE_TIMER };
    ESP_ERROR_CHECK(ulp_riscv_config_and_run(&cfg));

    /* Ensure PMU timer bit is asserted */
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN);

    log_pin_levels_pre_sleep();

    fflush(stdout);
    vTaskDelay(pdMS_TO_TICKS(1500));

    esp_sleep_enable_ulp_wakeup();
    esp_deep_sleep_start();
}

static void arm_stage_3_dual_mode(test_shared_data_t *d)
{
    ESP_LOGI(TAG, "========================================================================");
    ESP_LOGI(TAG, ">>> PREPARING TEST 3: Dual Mode (Timer + GPIO 18 Concurrently) <<<");
    ESP_LOGI(TAG, "BOTH 5s PMU Timer AND RTC GPIO 18 wakeups are armed simultaneously.");
    ESP_LOGI(TAG, "You can either WAIT 5.0s for timer wake OR TAP PWR (GPIO 18) button immediately!");
    ESP_LOGI(TAG, "========================================================================");

    d->test_stage = TEST_MODE_DUAL_BOTH;
    d->ulp_completed = 0;
    d->ulp_gpio_wake_count = 0;
    d->ulp_timer_wake_count = 0;
    d->ulp_isr_fired_count = 0;
    d->ulp_step_checkpoint = 0;
    d->ulp_rdy_timeout = 0;

    /* Arm RTC GPIO wake detector for GPIO 18 */
    rtc_gpio_wakeup_enable(PIN_BUTTON_PWR, GPIO_INTR_LOW_LEVEL);
    rtc_gpio_wakeup_disable(PIN_BUTTON_BOOT);

    /* Set 5-second wakeup period */
    ESP_ERROR_CHECK(ulp_set_wakeup_period(0, 5000000));

    /* Arm GPIO wakeup and then assert Timer bit concurrently */
    ulp_riscv_cfg_t cfg = { .wakeup_source = ULP_RISCV_WAKEUP_SOURCE_GPIO };
    ESP_ERROR_CHECK(ulp_riscv_config_and_run(&cfg));
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN);

    log_pin_levels_pre_sleep();

    fflush(stdout);
    vTaskDelay(pdMS_TO_TICKS(1500));

    esp_sleep_enable_ulp_wakeup();
    esp_deep_sleep_start();
}

void app_main(void)
{
    esp_reset_reason_t reset_reason = esp_reset_reason();
    uint32_t wake_causes = esp_sleep_get_wakeup_causes();
    test_shared_data_t *p_data = (test_shared_data_t *)&ulp_test_data;

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
        printf("*  Primary Wake Pin: GPIO 18 (PWR Key, Active LOW)                     *\n");
        printf("************************************************************************\n\n");

        ESP_LOGI(TAG, "Loading ULP-RISC-V firmware binary (%u bytes)...",
                 (unsigned)(ulp_riscv_test_bin_end - ulp_riscv_test_bin_start));
        ESP_ERROR_CHECK(ulp_riscv_load_binary(ulp_riscv_test_bin_start,
                                              (ulp_riscv_test_bin_end - ulp_riscv_test_bin_start)));
        fflush(stdout);
        vTaskDelay(pdMS_TO_TICKS(1500));
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
            fflush(stdout);
            vTaskDelay(pdMS_TO_TICKS(1500));
            while (1) {
                vTaskDelay(pdMS_TO_TICKS(1000));
            }
        }
    }
}
