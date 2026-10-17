# Revised Implementation Plan: ULP-RISC-V Pure Event Mode Silicon Remediation (v3)

Following the 4th-party audit review of [`ulp_event_mode_logic_audit.md`](file:///c:/Users/Matt/Documents/GitHub/H1OS/docs/architecture/ulp_event_mode_logic_audit.md), the architecture and implementation plan have been revised to eliminate build-breaking calls and correctly address the level-trigger wake storm.

---

## 1. 4th-Party Audit Reconciliation & Verified Realities

| Audit Finding | Silicon Reality on ESP32-S3 | Action Taken |
| :--- | :--- | :--- |
| **Defect 1 (Edge vs Level)** | **Accurate.** ESP32-S3 RTC comparators only sample logic levels (`LOW_LEVEL`). `INT_TYPE = 2` drops wake transitions. | Configured `rtc_gpio_wakeup_enable(pin, GPIO_INTR_LOW_LEVEL)`. |
| **Defect 2 (Bit 10 Role)** | **Misattributed.** TRM Reg 6.50 defines Bit 10 as Light-sleep wake for HP CPU. ULP deep sleep wake is gated by `RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA` & comparator status. | Use standard `rtc_gpio_wakeup_enable()` without manual Bit 10 overrides. |
| **Defect 3 (LP IO Clock)** | **Invalid (Breaks Build).** `io_mux_enable_lp_io_clock()` only exists on LP_IO matrix chips (C6/H2/P4). ESP32-S3 has no LP_IO clock. | **Removed completely.** Calling this causes undefined reference linker error. |
| **Defect 4 (Pad Buffers)** | **Accurate.** Pads require input buffers enabled and must not be frozen by pad holds. | Explicit `rtc_gpio_hold_dis(pin)` ensures pads are not frozen. |
| **Defect 5 (CDC Latency)** | **Accurate.** Slow clock domain crossing requires $\ge 50\ \mu\text{s}$ delay before entering deep sleep. | Retained `esp_rom_delay_us(50)`. |
| **Defect 6 (Wake Storm)** | **Accurate.** Level mode causes runaway wake loops if `GPIO_WAKEUP_ENA` is re-armed while lines are still LOW. | **Addressed via asymmetric ULP re-arming protocol in firmware.** |
| **Defect 7 / 8 (RDY Gate)** | **Accurate.** ULP must spin on `RTC_CNTL_RDY_FOR_WAKEUP` before waking Main CPU. | Added spin loop on `RTC_CNTL_RDY_FOR_WAKEUP` in `ulp/main.c`. |

---

## 2. Proposed Code Changes

### Component 1: `components/h1os/src/sub_power.c` (`sub_power_enter_deep_sleep`)
```c
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
    
    /* Note: Do NOT call io_mux_enable_lp_io_clock() - non-existent on ESP32-S3 */
}

/* 5. Clear peripheral status and wake latch */
REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);
SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);

/* 6. Pure Event Mode: timer disabled, GPIO wakeup enabled */
CLEAR_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_SLP_TIMER_EN);
SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);

/* 7. CDC sync delay (min 3 RTC_SLOW_CLK cycles) */
esp_rom_delay_us(50);
```

### Component 2: `components/h1os/ulp/main.c` (Level Wake Storm Mitigation)
```c
/* Conditionally wake Main CPU and cleanly shut down ULP */
if (wake_main) {
    /* 1. Spin until RTC controller is ready for wakeup (TRM requirement) */
    while (!REG_GET_FIELD(RTC_CNTL_LOW_POWER_ST_REG, RTC_CNTL_RDY_FOR_WAKEUP));

    /* 2. Wake Main CPU */
    ulp_riscv_wakeup_main_processor();

    /* 3. Clear trigger latch & peripheral flag */
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);
    REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);

    /* 4. DO NOT re-arm GPIO_WAKEUP_ENA here: line is still LOW.
     * Main CPU will handle debounce and re-arm it before entering next sleep. */
} else {
    /* Sensor Poll Tick: wait for PCF85063A ~15.6ms pulse to release before re-arming */
    uint32_t wait_timeout = 500000;
    while ((ulp_riscv_gpio_get_level(GPIO_NUM_5) == 0) && (--wait_timeout > 0));

    /* Clear peripheral interrupt flag & controller latch */
    REG_WRITE(RTC_GPIO_STATUS_W1TC_REG, RTC_GPIO_STATUS_INT_W1TC_M);
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_CLR);

    /* Re-arm GPIO wakeup for subsequent events */
    SET_PERI_REG_MASK(RTC_CNTL_ULP_CP_TIMER_REG, RTC_CNTL_ULP_CP_GPIO_WAKEUP_ENA);
}
```

---

## 3. Verification & Execution Steps

1. Apply changes to `components/h1os/src/sub_power.c` and `components/h1os/ulp/main.c`.
2. Compile development build:
   ```powershell
   & "C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1"; idf.py -B build_dev build
   ```
3. Compile production build:
   ```powershell
   & "C:\Espressif\tools\Microsoft.v6.1.PowerShell_profile.ps1"; idf.py -B build_prod build
   ```
4. Verify build artifacts and clean compilation without missing symbols.
