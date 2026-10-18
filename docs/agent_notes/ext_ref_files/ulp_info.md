#define PIN_POWER_HOLD   GPIO_NUM_17
#define PIN_BUTTON_BOOT  GPIO_NUM_0
#define PIN_BUTTON_PWR   GPIO_NUM_18

/* Persisted across deep sleep cycles in RTC Slow Memory */
RTC_DATA_ATTR static uint32_t s_current_test = 0;
RTC_DATA_ATTR static uint32_t s_boot_count   = 0;

extern const uint8_t ulp_riscv_test_bin_start[] asm("_binary_ulp_riscv_test_bin_start");
extern const uint8_t ulp_riscv_test_bin_end[]   asm("_binary_ulp_riscv_test_bin_end");

static void configure_rtc_pins(void)
{
    /* Configure GPIO 0 (BOOT button) */
    rtc_gpio_init(PIN_BUTTON_BOOT);
    rtc_gpio_set_direction(PIN_BUTTON_BOOT, RTC_GPIO_MODE_INPUT_ONLY);
    rtc_gpio_pullup_dis(PIN_BUTTON_BOOT); //10k external pullup on board
    rtc_gpio_pulldown_dis(PIN_BUTTON_BOOT);

    /* Configure GPIO 18 (PWR button) */
    rtc_gpio_init(PIN_BUTTON_PWR);
    rtc_gpio_set_direction(PIN_BUTTON_PWR, RTC_GPIO_MODE_INPUT_ONLY);
    rtc_gpio_pullup_dis(PIN_BUTTON_PWR); //10k external pullup on board
    rtc_gpio_pulldown_dis(PIN_BUTTON_PWR);
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
}

static void arm_stage_1_event_mode(test_shared_data_t *d)
{
    d->test_stage = TEST_MODE_EVENT_ONLY;
    d->ulp_completed = 0;
    d->ulp_gpio_wake_count = 0;
    d->ulp_timer_wake_count = 0;
    d->ulp_isr_fired_count = 0;

    /* Arm RTC GPIO wake detector */
    rtc_gpio_wakeup_enable(PIN_BUTTON_BOOT, GPIO_INTR_LOW_LEVEL);
    rtc_gpio_wakeup_enable(PIN_BUTTON_PWR, GPIO_INTR_LOW_LEVEL);

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
    d->test_stage = TEST_MODE_DUAL_BOTH;
    d->ulp_completed = 0;
    d->ulp_gpio_wake_count = 0;
    d->ulp_timer_wake_count = 0;
    d->ulp_isr_fired_count = 0;

    /* Arm RTC GPIO wake detector */
    rtc_gpio_wakeup_enable(PIN_BUTTON_BOOT, GPIO_INTR_LOW_LEVEL);
    rtc_gpio_wakeup_enable(PIN_BUTTON_PWR, GPIO_INTR_LOW_LEVEL);

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

    configure_rtc_pins();

    if (reset_reason != ESP_RST_DEEPSLEEP || s_current_test == 0) {
        /* Cold Boot / Power-On Reset */
        s_boot_count = 0;
        s_current_test = TEST_MODE_EVENT_ONLY;
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
            while (1) {
                vTaskDelay(pdMS_TO_TICKS(1000));
            }
        }
    }
}

---

#if CONFIG_ULP_RISCV_INTERRUPT_ENABLE
static void gpio0_isr(void *arg)
{
    test_data.ulp_isr_fired_count++;
    test_data.ulp_last_isr_source = 0;
}

static void gpio18_isr(void *arg)
{
    test_data.ulp_isr_fired_count++;
    test_data.ulp_last_isr_source = 18;
}
#endif

int main(void)
{
    test_data.ulp_entry_count++;
    uint32_t start_c = ULP_RISCV_GET_CCOUNT();

#if CONFIG_ULP_RISCV_INTERRUPT_ENABLE
    /* Register RTC GPIO ISR handlers for tactile keys and RTC INT */
    ulp_riscv_gpio_isr_register(GPIO_NUM_0, ULP_RISCV_GPIO_INTR_LOW_LEVEL, gpio0_isr, NULL);
    ulp_riscv_gpio_isr_register(GPIO_NUM_18, ULP_RISCV_GPIO_INTR_LOW_LEVEL, gpio18_isr, NULL);
#endif

    /* 1. Snapshot raw RTC IO interrupt status register */
    uint32_t rtcio_int_st = REG_GET_FIELD(RTC_GPIO_STATUS_REG, RTC_GPIO_STATUS_INT);
    test_data.ulp_last_gpio_status = rtcio_int_st;

    /* 2. Sample live levels of tested RTC GPIO lines */
    int b0  = ulp_riscv_gpio_get_level(GPIO_NUM_0);
    int b18 = ulp_riscv_gpio_get_level(GPIO_NUM_18);
    test_data.ulp_pin_levels = ((b0 ? 1U : 0U) | ((b18 ? 1U : 0U) << 18));

    /* 3. Classify wakeup cause */
    if (rtcio_int_st != 0 || b0 == 0 || b18 == 0) {
        test_data.ulp_gpio_wake_count++;
    } else {
        test_data.ulp_timer_wake_count++;
    }

    test_data.ulp_cycle_count = ULP_RISCV_GET_CCOUNT() - start_c;
    test_data.ulp_completed = 1;

    asm volatile("fence" ::: "memory");

    /* 4. Hand off execution: Wake Main CPU from deep sleep */
    while (!REG_GET_FIELD(RTC_CNTL_LOW_POWER_ST_REG, RTC_CNTL_RDY_FOR_WAKEUP));
    ulp_riscv_wakeup_main_processor();

    /* 5. Clear RTC GPIO wake latch with conservative 120us CDC pulse (>16 cycles on 136kHz RC) */
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
    ulp_riscv_delay_us(120);
    CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
    REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);

    /* 6. Halt coprocessor and enter sleep */
    ulp_riscv_halt();
    return 0;
}
