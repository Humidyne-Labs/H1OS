/**
 * @file main.c
 * @brief ULP-RISC-V verification harness application main
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "driver/gpio.h"
#include "driver/rtc_io.h"
#include "esp_log.h"
#include "esp_rom_gpio.h"
#include "esp_rom_sys.h"
#include "esp_sleep.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "shared_test_data.h"
#include "soc/gpio_reg.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/rtc_io_reg.h"
#include "ulp_common.h"
#include "ulp_riscv.h"
#include "ulp_riscv_test.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static const char *TAG = "RISCV_TEST";

#define PIN_BUTTON_BOOT GPIO_NUM_0
#define PIN_BUTTON_PWR GPIO_NUM_18

RTC_DATA_ATTR static uint32_t s_current_test = 0;
RTC_DATA_ATTR static uint32_t s_boot_count = 0;
RTC_DATA_ATTR static bool s_stage1_pass = false;
RTC_DATA_ATTR static bool s_stage2_pass = false;
RTC_DATA_ATTR static bool s_stage3_pass = false;

extern const uint8_t ulp_riscv_test_bin_start[] asm("_binary_ulp_riscv_test_bin_start");
extern const uint8_t ulp_riscv_test_bin_end[] asm("_binary_ulp_riscv_test_bin_end");

/**
 * @brief Clear stale rtc gpio wake latch.
 *
 * @return Return value of type static void.
 */
static void clear_stale_rtc_gpio_wake_latch(void)
{
    REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
    esp_rom_delay_us(120);
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
}

/**
 * @brief Configure rtc pins.
 *
 * @return Return value of type static void.
 */
static void configure_rtc_pins(void)
{
    rtc_gpio_hold_dis(PIN_BUTTON_PWR);
    rtc_gpio_hold_dis(PIN_BUTTON_BOOT);

    rtc_gpio_init(PIN_BUTTON_PWR);
    rtc_gpio_set_direction(PIN_BUTTON_PWR, RTC_GPIO_MODE_INPUT_ONLY);
    rtc_gpio_pullup_en(PIN_BUTTON_PWR);
    rtc_gpio_pulldown_dis(PIN_BUTTON_PWR);

    gpio_sleep_sel_dis(PIN_BUTTON_PWR);

    rtc_gpio_init(PIN_BUTTON_BOOT);
    rtc_gpio_set_direction(PIN_BUTTON_BOOT, RTC_GPIO_MODE_INPUT_ONLY);
    rtc_gpio_pullup_en(PIN_BUTTON_BOOT);
    rtc_gpio_pulldown_dis(PIN_BUTTON_BOOT);
}

/**
 * @brief Log pin levels pre sleep.
 *
 * @return Return value of type static void.
 */
static void log_pin_levels_pre_sleep(void)
{
    int pwr_lvl = rtc_gpio_get_level(PIN_BUTTON_PWR);
    int boot_lvl = rtc_gpio_get_level(PIN_BUTTON_BOOT);

    ESP_LOGI(TAG, "Pre-Sleep Pin Levels Check: PWR (GPIO 18) = %d, BOOT (GPIO 0) = %d", pwr_lvl, boot_lvl);
    if (pwr_lvl == 0) {
        ESP_LOGW(TAG, "WARNING: PWR (GPIO 18) is LOW prior to deep sleep! May trigger immediate "
                      "wake or indicates button held down.");
    }
}

static const char *get_checkpoint_name(uint32_t cp)
{
    switch (cp) {
    case ULP_CP_ENTERED_MAIN:
        return "1: ENTERED_MAIN";
    case ULP_CP_ISR_REGISTERED:
        return "2: ISR_REGISTERED";
    case ULP_CP_PINS_SAMPLED:
        return "3: PINS_SAMPLED";
    case ULP_CP_WAITING_RDY:
        return "4: WAITING_RDY (SPINNING)";
    case ULP_CP_RDY_CONFIRMED:
        return "5: RDY_CONFIRMED";
    case ULP_CP_WAKE_SIGNALED:
        return "6: WAKE_SIGNALED";
    case ULP_CP_CDC_CLEARED:
        return "7: CDC_CLEARED";
    case ULP_CP_HALTED:
        return "8: HALTED (CLEAN EXIT)";
    default:
        return "0: NOT_REACHED";
    }
}

/**
 * @brief Dump and clear ulp ring buffer.
 *
 * @param[in]    d               Parameter d.
 *
 * @return Return value of type static void.
 */
static void dump_and_clear_ulp_ring_buffer(test_shared_data_t *d)
{
    printf("\n************************************************************************\n");
    printf("*  ULP RISC-V INTERNAL RTC SLOW MEMORY RING BUFFER LOG                  *\n");
    printf("************************************************************************\n");

    if (d->log_buf.head == d->log_buf.tail) {
        printf(" [RING BUFFER EMPTY - NO NEW ULP LOG MESSAGES]\n");
    } else {
        if (d->log_buf.head - d->log_buf.tail > ULP_LOG_BUF_SIZE) {
            printf(" [WARNING: Ring buffer wrapped! Dropping %lu overflow bytes]\n",
                   (unsigned long)(d->log_buf.head - d->log_buf.tail - ULP_LOG_BUF_SIZE));
            d->log_buf.tail = d->log_buf.head - ULP_LOG_BUF_SIZE;
        }

        while (d->log_buf.tail < d->log_buf.head) {
            char c = d->log_buf.buffer[d->log_buf.tail & ULP_LOG_BUF_MASK];
            putchar(c);
            d->log_buf.tail++;
        }
    }
    printf("************************************************************************\n");
    fflush(stdout);
}

/**
 * @brief Dump telemetry report.
 *
 * @param[in]    stage           Parameter stage.
 * @param[in]    causes          Parameter causes.
 * @param[in]    d               Parameter d.
 *
 * @return Return value of type static void.
 */
static void dump_telemetry_report(uint32_t stage, uint32_t causes, test_shared_data_t *d)
{
    bool is_ulp_wake = (causes & BIT(ESP_SLEEP_WAKEUP_ULP)) != 0;
    bool is_timer_wake = (causes & BIT(ESP_SLEEP_WAKEUP_TIMER)) != 0;
    bool is_trap_wake = (causes & BIT(ESP_SLEEP_WAKEUP_COCPU_TRAP_TRIG)) != 0;

    const char *stage_name = "UNKNOWN";
    if (stage == TEST_MODE_TIMER_ONLY)
        stage_name = "STAGE 1: TIMER MODE (5s PMU COUNTDOWN)";
    else if (stage == TEST_MODE_EVENT_ONLY)
        stage_name = "STAGE 2: EVENT MODE (RTC GPIO 18)";
    else if (stage == TEST_MODE_DUAL_BOTH)
        stage_name = "STAGE 3: DUAL MODE (PMU TIMER + RTC GPIO 18)";

    const char *verdict = "FAIL";
    if (is_trap_wake) {
        verdict = "FATAL TRAP (0x1000)";
    } else if (d->ulp_completed == 2) {
        verdict = "FAIL: ULP WOKE TOO EARLY (MAIN CPU WAS AWAKE)";
    } else if (d->ulp_rdy_timeout != 0) {
        verdict = "FAIL: ULP RDY_FOR_WAKEUP TIMEOUT";
    } else if (is_timer_wake && d->ulp_completed == 0) {
        verdict = "FALLBACK WAKE: 30s TIMER (ULP trigger missed or coprocessor hung)";
    } else if (is_ulp_wake && d->magic == ULP_TEST_MAGIC && d->ulp_completed == 1) {
        if (stage == TEST_MODE_TIMER_ONLY) {
            verdict = (d->ulp_timer_wake_count > 0) ? "PASS" : "FAIL: TIMER WAKE NOT COUNTED";
            if (strcmp(verdict, "PASS") == 0)
                s_stage1_pass = true;
        } else if (stage == TEST_MODE_EVENT_ONLY) {
            verdict = (d->ulp_gpio_wake_count > 0) ? "PASS" : "FAIL: GPIO WAKE NOT COUNTED";
            if (strcmp(verdict, "PASS") == 0)
                s_stage2_pass = true;
        } else if (stage == TEST_MODE_DUAL_BOTH) {
            if (d->ulp_gpio_wake_count > 0) {
                verdict = "PASS: CONCURRENT GPIO WAKE PREEMPTED TIMER";
                s_stage3_pass = true;
            } else {
                verdict = "CONFIRMED SILICON INVARIANT (ERR-001): TIMER SUPPRESSED GPIO WAKE";
                s_stage3_pass = false;
            }
        }
    }

    printf("\n");
    printf("========================================================================\n");
    printf(" [RISC-V TEST] TELEMETRY DUMP: %s\n", stage_name);
    printf("========================================================================\n");
    printf(" Boot Count / Sleep Wake # : %lu\n", (unsigned long)s_boot_count);
    printf(" Main Wake Causes Bitmask  : 0x%08lX (ULP: %s, TIMER: %s, TRAP: %s)\n", (unsigned long)causes,
           is_ulp_wake ? "YES" : "NO", is_timer_wake ? "YES (30s FALLBACK)" : "NO",
           is_trap_wake ? "YES (CRASH!)" : "NO");
    printf(" Shared Structure Magic    : 0x%08lX (%s)\n", (unsigned long)d->magic,
           (d->magic == ULP_TEST_MAGIC) ? "VALID" : "CORRUPTED");
    printf(" Stage Configured in ULP   : %lu\n", (unsigned long)d->test_stage);
    printf(" ULP Checkpoint Reached    : %s\n", get_checkpoint_name(d->ulp_step_checkpoint));
    printf(" ULP Hand-Off Status       : %lu (0=Init, 1=Success, 2=Early Wake)\n", (unsigned long)d->ulp_completed);
    printf(" ULP RDY_FOR_WAKEUP Status : %s\n", (d->ulp_rdy_timeout != 0) ? "TIMEOUT / AWAKE CHECK" : "OK");
    printf(" ULP Total Entry Count     : %lu\n", (unsigned long)d->ulp_entry_count);
    printf(" ULP GPIO Wake Count       : %lu\n", (unsigned long)d->ulp_gpio_wake_count);
    printf(" ULP Timer Wake Count      : %lu\n", (unsigned long)d->ulp_timer_wake_count);
    printf(" ULP ISR Handler Executions: %lu\n", (unsigned long)d->ulp_isr_fired_count);
    printf(" Last ISR Source GPIO      : %ld\n", (long)d->ulp_last_isr_source);
    printf(" Raw RTC_GPIO_STATUS_REG   : 0x%08lX\n", (unsigned long)d->ulp_last_gpio_status);
    printf(" Raw RTC_CNTL_ULP_CP_TIMER : 0x%08lX (TIMER_EN=%d, GPIO_ENA=%d, CLR=%d)\n",
           (unsigned long)d->ulp_reg_timer_val, (int)((d->ulp_reg_timer_val & RTC_CNTL_ULP_CP_SLP_TIMER_EN) ? 1 : 0),
           (int)((d->ulp_reg_timer_val & RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA) ? 1 : 0),
           (int)((d->ulp_reg_timer_val & RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR) ? 1 : 0));
    printf(" Sampled Pin Levels        : PWR(18)=%d, BOOT(0)=%d (Raw: 0x%08lX)\n", (int)(d->ulp_pin_levels & 1U),
           (int)((d->ulp_pin_levels >> 1) & 1U), (unsigned long)d->ulp_pin_levels);
    const char *trigger_desc = "UNKNOWN / NONE";
    if (d->ulp_timer_wake_count > 0 && d->ulp_gpio_wake_count == 0) {
        trigger_desc = "INTERNAL PMU TIMER (Countdown Expired)";
    } else if (d->ulp_gpio_wake_count > 0 && d->ulp_timer_wake_count == 0) {
        trigger_desc = "PHYSICAL RTC GPIO 18 TAP (Tactile Key Pressed)";
    } else if (d->ulp_gpio_wake_count > 0 && d->ulp_timer_wake_count > 0) {
        trigger_desc = "DUAL CONCURRENT (Both GPIO & Timer Registered)";
    }

    printf(" Coprocessor Execution Time: %lu cycles\n", (unsigned long)d->ulp_cycle_count);
    printf(" ULP Elapsed Slow Ticks    : %lu (~%lu ms)\n", (unsigned long)d->ulp_elapsed_rtc_ticks,
           (unsigned long)(d->ulp_elapsed_rtc_ticks / 136));
    printf(" Verified Wake Trigger     : %s\n", trigger_desc);
    printf(" STAGE VERDICT             : %s\n", verdict);
    printf("========================================================================\n\n");

    fflush(stdout);
    vTaskDelay(pdMS_TO_TICKS(1500));
}

/**
 * @brief Prepare serial and pins before sleep.
 *
 * @return Return value of type static void.
 */
static void prepare_serial_and_pins_before_sleep(void)
{
    log_pin_levels_pre_sleep();
    fflush(stdout);
    vTaskDelay(pdMS_TO_TICKS(1500));
}

/**
 * @brief Enter deep sleep guarded.
 *
 * @param[in]    d               Parameter d.
 *
 * @return Return value of type static void.
 */
static void enter_deep_sleep_guarded(test_shared_data_t *d)
{
    SET_PERI_REG_MASK(RTC_CNTL_TIME_UPDATE_REG, RTC_CNTL_TIME_UPDATE);
    d->sleep_start_rtc_ticks = READ_PERI_REG(RTC_CNTL_TIME0_REG);

    esp_sleep_enable_timer_wakeup(30000000ULL);
    esp_sleep_enable_ulp_wakeup();
    esp_deep_sleep_start();

    ESP_LOGE(TAG, "FATAL: Deep sleep was REJECTED by hardware! Wakeup trigger was already pending "
                  "at sleep entry.");
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/**
 * @brief Arm stage 1 timer mode.
 *
 * @param[in]    d               Parameter d.
 *
 * @return Return value of type static void.
 */
static void arm_stage_1_timer_mode(test_shared_data_t *d)
{
    ESP_LOGI(TAG, "========================================================================");
    ESP_LOGI(TAG, ">>> PREPARING STAGE 1: Pure Timer Mode (PMU Countdown) <<<");
    ESP_LOGI(TAG, "Proves binary loading, slow clock domain, and ULP wake pipeline first.");
    ESP_LOGI(TAG, "Will automatically wake in 5.0 seconds via internal 136 kHz RC timer...");
    ESP_LOGI(TAG, "========================================================================");

    d->test_stage = TEST_MODE_TIMER_ONLY;
    d->ulp_completed = 0;
    d->ulp_gpio_wake_count = 0;
    d->ulp_timer_wake_count = 0;
    d->ulp_isr_fired_count = 0;
    d->ulp_last_isr_source = 0xFF;
    d->ulp_step_checkpoint = 0;
    d->ulp_rdy_timeout = 0;

    rtc_gpio_wakeup_disable(PIN_BUTTON_PWR);
    rtc_gpio_wakeup_disable(PIN_BUTTON_BOOT);
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);
    clear_stale_rtc_gpio_wake_latch();

    prepare_serial_and_pins_before_sleep();

    ESP_ERROR_CHECK(ulp_set_wakeup_period(0, 5000000));

    ulp_riscv_cfg_t cfg = {.wakeup_source = ULP_RISCV_WAKEUP_SOURCE_TIMER};
    ESP_ERROR_CHECK(ulp_riscv_config_and_run(&cfg));
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN);

    uint32_t t_reg1 = READ_PERI_REG(RTC_CNTL_ULP_CP_TIMER_REG);
    ESP_LOGI(TAG,
             "Hardware Reg Check: RTC_CNTL_ULP_CP_TIMER_REG = 0x%08lX (TIMER_EN=%d, GPIO_ENA=%d, "
             "CLR=%d)",
             (unsigned long)t_reg1, (int)((t_reg1 & RTC_CNTL_ULP_CP_SLP_TIMER_EN) ? 1 : 0),
             (int)((t_reg1 & RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA) ? 1 : 0),
             (int)((t_reg1 & RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR) ? 1 : 0));

    enter_deep_sleep_guarded(d);
}

/**
 * @brief Arm stage 2 event mode.
 *
 * @param[in]    d               Parameter d.
 *
 * @return Return value of type static void.
 */
static void arm_stage_2_event_mode(test_shared_data_t *d)
{
    ESP_LOGI(TAG, "========================================================================");
    ESP_LOGI(TAG, ">>> PREPARING STAGE 2: Pure Event Mode (RTC GPIO 18) <<<");
    ESP_LOGI(TAG, "PMU Sleep Timer is DISABLED. 30-second fallback timer armed.");
    ESP_LOGI(TAG, "ACTION REQUIRED: Press tactile PWR (GPIO 18) button to wake!");
    ESP_LOGI(TAG, "========================================================================");

    d->test_stage = TEST_MODE_EVENT_ONLY;
    d->ulp_completed = 0;
    d->ulp_gpio_wake_count = 0;
    d->ulp_timer_wake_count = 0;
    d->ulp_isr_fired_count = 0;
    d->ulp_last_isr_source = 0xFF;
    d->ulp_step_checkpoint = 0;
    d->ulp_rdy_timeout = 0;

    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN);

    clear_stale_rtc_gpio_wake_latch();

    rtc_gpio_wakeup_enable(PIN_BUTTON_PWR, GPIO_INTR_LOW_LEVEL);
    rtc_gpio_wakeup_disable(PIN_BUTTON_BOOT);

    esp_sleep_enable_timer_wakeup(30000000ULL);

    prepare_serial_and_pins_before_sleep();

    ulp_riscv_cfg_t cfg = {.wakeup_source = ULP_RISCV_WAKEUP_SOURCE_GPIO};
    ESP_ERROR_CHECK(ulp_riscv_config_and_run(&cfg));

    uint32_t t_reg2 = READ_PERI_REG(RTC_CNTL_ULP_CP_TIMER_REG);
    ESP_LOGI(TAG,
             "Hardware Reg Check: RTC_CNTL_ULP_CP_TIMER_REG = 0x%08lX (TIMER_EN=%d, GPIO_ENA=%d, "
             "CLR=%d)",
             (unsigned long)t_reg2, (int)((t_reg2 & RTC_CNTL_ULP_CP_SLP_TIMER_EN) ? 1 : 0),
             (int)((t_reg2 & RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA) ? 1 : 0),
             (int)((t_reg2 & RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR) ? 1 : 0));

    enter_deep_sleep_guarded(d);
}

/**
 * @brief Arm stage 3 dual mode.
 *
 * @param[in]    d               Parameter d.
 *
 * @return Return value of type static void.
 */
static void arm_stage_3_dual_mode(test_shared_data_t *d)
{
    ESP_LOGI(TAG, "========================================================================");
    ESP_LOGI(TAG, ">>> PREPARING STAGE 3: Dual Mode (15s PMU Timer + GPIO 18 Concurrently) <<<");
    ESP_LOGI(TAG, "PMU Timer is set to 15.0 seconds. RTC GPIO 18 is armed concurrently.");
    ESP_LOGI(TAG, "ACTION REQUIRED: Tap tactile PWR (GPIO 18) button within 15 seconds!");
    ESP_LOGI(TAG, "Host USB CDC reconnect takes ~3s. Waking before 15s proves GPIO wake.");
    ESP_LOGI(TAG, "========================================================================");

    d->test_stage = TEST_MODE_DUAL_BOTH;
    d->ulp_completed = 0;
    d->ulp_gpio_wake_count = 0;
    d->ulp_timer_wake_count = 0;
    d->ulp_isr_fired_count = 0;
    d->ulp_last_isr_source = 0xFF;
    d->ulp_step_checkpoint = 0;
    d->ulp_rdy_timeout = 0;

    clear_stale_rtc_gpio_wake_latch();

    rtc_gpio_wakeup_enable(PIN_BUTTON_PWR, GPIO_INTR_LOW_LEVEL);
    rtc_gpio_wakeup_disable(PIN_BUTTON_BOOT);

    ESP_ERROR_CHECK(ulp_set_wakeup_period(0, 15000000));

    prepare_serial_and_pins_before_sleep();

    ulp_riscv_cfg_t cfg = {.wakeup_source = ULP_RISCV_WAKEUP_SOURCE_GPIO};
    ESP_ERROR_CHECK(ulp_riscv_config_and_run(&cfg));
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN);

    uint32_t t_reg3 = READ_PERI_REG(RTC_CNTL_ULP_CP_TIMER_REG);
    ESP_LOGI(TAG,
             "Hardware Reg Check: RTC_CNTL_ULP_CP_TIMER_REG = 0x%08lX (TIMER_EN=%d, GPIO_ENA=%d, "
             "CLR=%d)",
             (unsigned long)t_reg3, (int)((t_reg3 & RTC_CNTL_ULP_CP_SLP_TIMER_EN) ? 1 : 0),
             (int)((t_reg3 & RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA) ? 1 : 0),
             (int)((t_reg3 & RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR) ? 1 : 0));

    enter_deep_sleep_guarded(d);
}

/**
 * @brief Application entry point.
 */
void app_main(void)
{
    esp_reset_reason_t reset_reason = esp_reset_reason();
    uint32_t wake_causes = esp_sleep_get_wakeup_causes();
    test_shared_data_t *p_data = (test_shared_data_t *)&ulp_test_data;

    esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);

    configure_rtc_pins();

    if (reset_reason != ESP_RST_DEEPSLEEP || s_current_test == 0) {
        s_boot_count = 0;
        s_current_test = TEST_MODE_TIMER_ONLY;
        s_stage1_pass = false;
        s_stage2_pass = false;
        s_stage3_pass = false;

        printf("\n\n");
        printf("************************************************************************\n");
        printf("*  H1OS ESP32-S3 ULP-RISC-V Coprocessor Wakeup Formal Test Suite       *\n");
        printf("*  Hardware Target : Waveshare ESP32-S3 ePaper 1.54\" V2                *\n");
        printf("*  Slow Clock      : Internal 136 kHz RC (CONFIG_RTC_CLK_SRC_INT_RC=y) *\n");
        printf("*  Interrupts      : CONFIG_ULP_RISCV_INTERRUPT_ENABLE=y (ENABLED)     *\n");
        printf("*  Strategy        : Timer Mode FIRST -> Event Mode -> Dual Mode       *\n");
        printf("*  Primary Wake Pin: GPIO 18 (PWR Key, Active LOW)                     *\n");
        printf("************************************************************************\n\n");

        ESP_LOGI(TAG, "Loading ULP-RISC-V firmware binary (%u bytes)...",
                 (unsigned)(ulp_riscv_test_bin_end - ulp_riscv_test_bin_start));
        ESP_ERROR_CHECK(
            ulp_riscv_load_binary(ulp_riscv_test_bin_start, (ulp_riscv_test_bin_end - ulp_riscv_test_bin_start)));
        fflush(stdout);
        vTaskDelay(pdMS_TO_TICKS(1500));
        p_data->log_buf.head = 0;
        p_data->log_buf.tail = 0;
        arm_stage_1_timer_mode(p_data);
    } else {
        s_boot_count++;

        ulp_timer_stop();

        vTaskDelay(pdMS_TO_TICKS(2000));

        dump_and_clear_ulp_ring_buffer(p_data);

        dump_telemetry_report(s_current_test, wake_causes, p_data);

        if (s_current_test == TEST_MODE_TIMER_ONLY) {
            ESP_LOGI(TAG, "Stage 1 (Timer) Finished. Transitioning to Stage 2 (Event Mode)...");
            s_current_test = TEST_MODE_EVENT_ONLY;
            arm_stage_2_event_mode(p_data);
        } else if (s_current_test == TEST_MODE_EVENT_ONLY) {
            ESP_LOGI(TAG, "Stage 2 (Event) Finished. Transitioning to Stage 3 (Dual Mode)...");
            s_current_test = TEST_MODE_DUAL_BOTH;
            arm_stage_3_dual_mode(p_data);
        } else if (s_current_test == TEST_MODE_DUAL_BOTH) {
            s_current_test = TEST_MODE_COMPLETE;
            printf("\n");
            printf("************************************************************************\n");
            if (s_stage1_pass && s_stage2_pass && !s_stage3_pass) {
                printf("*  TEST SUITE COMPLETE: SILICON ERRATA ERR-001 DEFINITIVELY VERIFIED!  *\n");
                printf("*  Stage 1 (Pure Timer Mode) : PASS (ULP woke on PMU countdown)        *\n");
                printf("*  Stage 2 (Pure Event Mode) : PASS (ULP woke on physical GPIO 18 tap) *\n");
                printf("*  Stage 3 (Dual Arm Mode)   : TIMER_EN MASKS GPIO_WAKEUP_ENA (PROVEN) *\n");
                printf("*  Architecture Mandate      : Pure Event Mode + External PCF85063A    *\n");
            } else if (s_stage1_pass && s_stage2_pass && s_stage3_pass) {
                printf("*  TEST SUITE COMPLETE: ALL 3 MODES VALIDATED SUCCESSFULLY! (PASS)     *\n");
                printf("*  Concurrent Wakeup Observed: GPIO preempted timer!                   *\n");
            } else {
                printf("*  TEST SUITE FINISHED: ONE OR MORE STAGES FAILED                      *\n");
                printf("*  Stage 1: %-4s | Stage 2: %-4s | Stage 3: %-4s                       *\n",
                       s_stage1_pass ? "PASS" : "FAIL", s_stage2_pass ? "PASS" : "FAIL",
                       s_stage3_pass ? "PASS" : "FAIL");
            }
            printf("========================================================================\n");
            printf(">>> INTERACTIVE LOOP MODE ACTIVATED:                                 <<<\n");
            printf(">>> Press & RELEASE the BOOT (GPIO 0) button to re-run test suite!   <<<\n");
            printf("========================================================================\n\n");
            fflush(stdout);

            while (gpio_get_level(PIN_BUTTON_BOOT) != 0) {
                vTaskDelay(pdMS_TO_TICKS(50));
            }

            while (gpio_get_level(PIN_BUTTON_BOOT) == 0) {
                vTaskDelay(pdMS_TO_TICKS(50));
            }

            printf("\n[LOOP TRIGGER] BOOT (GPIO 0) button released! Restarting test suite from "
                   "Stage 1...\n\n");
            fflush(stdout);
            vTaskDelay(pdMS_TO_TICKS(500));

            s_boot_count = 0;
            s_stage1_pass = false;
            s_stage2_pass = false;
            s_stage3_pass = false;
            s_current_test = TEST_MODE_TIMER_ONLY;
            p_data->log_buf.head = 0;
            p_data->log_buf.tail = 0;

            arm_stage_1_timer_mode(p_data);
        }
    }
}
