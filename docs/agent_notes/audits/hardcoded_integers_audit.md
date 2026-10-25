# Codebase Hardcoded Integer Scanner Audit Report

- **Files Inspected with Findings:** 21
- **Total Integer Tokens Found:** 555
- **Filter Trivial (0, 1, -1):** Yes

## 1. Summary by File

| File | Non-Trivial Magic Constants | Hex / Bitmasks | Total |
| :--- | :---: | :---: | :---: |
| `components\h1os\bootloader_components\h1os_boot_hook\h1os_boot_hook.c` | 5 | 0 | 5 |
| `components\h1os\include\h1os\h1os_version.h` | 2 | 0 | 2 |
| `components\h1os\include\h1os\hal_types.h` | 1 | 0 | 1 |
| `components\h1os\include\h1os\sub_display.h` | 1 | 0 | 1 |
| `components\h1os\src\h1os_lifecycle.c` | 19 | 0 | 19 |
| `components\h1os\src\h1os_lvgl.cpp` | 19 | 7 | 26 |
| `components\h1os\src\h1os_time.c` | 3 | 0 | 3 |
| `components\h1os\src\hal_flash.c` | 2 | 0 | 2 |
| `components\h1os\src\hal_i2c.c` | 2 | 0 | 2 |
| `components\h1os\src\hal_io.c` | 18 | 2 | 20 |
| `components\h1os\src\hal_spi.c` | 15 | 0 | 15 |
| `components\h1os\src\orch_display_sync.c` | 1 | 0 | 1 |
| `components\h1os\src\orch_flow.c` | 7 | 1 | 8 |
| `components\h1os\src\orch_state.c` | 1 | 0 | 1 |
| `components\h1os\src\orch_wake_stub.c` | 37 | 10 | 47 |
| `components\h1os\src\sub_audio.c` | 34 | 114 | 148 |
| `components\h1os\src\sub_display.cpp` | 10 | 76 | 86 |
| `components\h1os\src\sub_power.c` | 66 | 0 | 66 |
| `components\h1os\src\sub_rtc.c` | 28 | 31 | 59 |
| `components\h1os\src\sub_sdcard.c` | 5 | 0 | 5 |
| `components\h1os\ulp\main.c` | 38 | 0 | 38 |

## 2. Detailed Findings by File

### `components\h1os\bootloader_components\h1os_boot_hook\h1os_boot_hook.c` (5 matches)

| Line | Token | Value | Context |
| :---: | :---: | :---: | :--- |
| 19 | `17` | `17` | `#define H1OS_PIN_POWER_HOLD 17` |
| 20 | `6` | `6` | `#define H1OS_PIN_EPD_3V3_EN 6` |
| 21 | `42` | `42` | `#define H1OS_PIN_PA_EN      42` |
| 22 | `46` | `46` | `#define H1OS_PIN_PA_CTRL    46` |
| 84 | `17)` | `17` | `ESP_LOGE(TAG, "[FATAL] BAT_CTRL (GPIO 17) power latch failed! [out=%lu, hold=%lu]",` |

### `components\h1os\include\h1os\h1os_version.h` (2 matches)

| Line | Token | Value | Context |
| :---: | :---: | :---: | :--- |
| 29 | `16)` | `16` | `#define H1OS_VERSION_VAL(major, minor, patch) (((uint32_t)(major) << 16) \| ((uint32_t)(minor) << 8) \| (uint32_t)(patch))` |
| 29 | `8)` | `8` | `#define H1OS_VERSION_VAL(major, minor, patch) (((uint32_t)(major) << 16) \| ((uint32_t)(minor) << 8) \| (uint32_t)(patch))` |

### `components\h1os\include\h1os\hal_types.h` (1 matches)

| Line | Token | Value | Context |
| :---: | :---: | :---: | :--- |
| 73 | `8)` | `8` | `#define HAL_EPD_FRAME_SIZE_BYTES ((HAL_EPD_WIDTH_PX * HAL_EPD_HEIGHT_PX) / 8)` |

### `components\h1os\include\h1os\sub_display.h` (1 matches)

| Line | Token | Value | Context |
| :---: | :---: | :---: | :--- |
| 25 | `8)` | `8` | `#define EPD_BUFFER_SIZE ((EPD_WIDTH * EPD_HEIGHT) / 8)` |

### `components\h1os\src\h1os_lifecycle.c` (19 matches)

| Line | Token | Value | Context |
| :---: | :---: | :---: | :--- |
| 59 | `1000000LL);` | `1000000` | `int64_t new_expiry = esp_timer_get_time() + ((int64_t)timeout_sec * 1000000LL);` |
| 118 | `6000U)` | `6000` | `while (h1os_lvgl_has_pending_tasks() && wait_ms < 6000U) {` |
| 120 | `20U;` | `20` | `wait_ms += 20U;` |
| 176 | `2)` | `2` | `: (ulp_last_wake_cause == 2) ? "PWR_BTN"` |
| 177 | `3)` | `3` | `: (ulp_last_wake_cause == 3) ? "LONG_OVERFLOW"` |
| 178 | `4)` | `4` | `: (ulp_last_wake_cause == 4) ? "SENSOR_TICK"` |
| 179 | `5)` | `5` | `: (ulp_last_wake_cause == 5) ? "RTC_INT_STUCK_FAULT"` |
| 180 | `6)` | `6` | `: (ulp_last_wake_cause == 6) ? "CRITICAL_BATTERY"` |
| 190 | `5)` | `5` | `ESP_LOGE(TAG, "[ULP FAULT] External PCF85063A /INT pin (GPIO 5) remained stuck LOW >50ms! Re-arm suppressed.");` |
| 192 | `6)` | `6` | `if (ulp_last_wake_cause == 6) {` |
| 193 | `3250` | `3250` | `ESP_LOGE(TAG, "[ULP FAULT] Battery critically low: %lu mV (< 3250 mV threshold)!", (unsigned long)ulp_last_vbat_mv);` |
| 224 | `2)` | `2` | `} else if (ulp_last_wake_btn == 2) {` |
| 225 | `18)";` | `18` | `trigger_desc = "ULP Tactile Press (POWER / GPIO 18)";` |
| 448 | `4096,` | `4096` | `BaseType_t res = xTaskCreatePinnedToCore(h1os_session_monitor_task, "h1os_sess", 4096, NULL, 3, (TaskHandle_t *)&s_session_task_handle, 0);` |
| 448 | `3,` | `3` | `BaseType_t res = xTaskCreatePinnedToCore(h1os_session_monitor_task, "h1os_sess", 4096, NULL, 3, (TaskHandle_t *)&s_session_task_handle, 0);` |
| 561 | `30)` | `30` | `current_soc_x10 >= st->initial_soc_x10 + 30) {` |
| 641 | `1000ULL);` | `1000` | `st->total_app_run_ms += (uint32_t)(esp_timer_get_time() / 1000ULL);` |
| 645 | `200` | `200` | `for (int32_t i = 0; i < 200 && stable_high < 4; i++) {` |
| 645 | `4;` | `4` | `for (int32_t i = 0; i < 200 && stable_high < 4; i++) {` |

### `components\h1os\src\h1os_lvgl.cpp` (26 matches)

| Line | Token | Value | Context |
| :---: | :---: | :---: | :--- |
| 41 | `8` | `8` | `#define LVGL_I1_PALETTE_SIZE 8` |
| 89 | `1000ULL);` | `1000` | `return (uint32_t)(esp_timer_get_time() / 1000ULL);` |
| 180 | `8;` | `8` | `const uint32_t epd_stride = EPD_WIDTH / 8;` |
| 182 | `7)` | `7` | `if ((area->x1 & 7) == 0 && (area_w & 7) == 0) {` |
| 182 | `7)` | `7` | `if ((area->x1 & 7) == 0 && (area_w & 7) == 0) {` |
| 183 | `3;` | `3` | `uint16_t bytes_per_line = area_w >> 3;` |
| 184 | `3;` | `3` | `uint16_t start_byte_x = area->x1 >> 3;` |
| 202 | `3;` | `3` | `uint32_t first_byte = x1 >> 3;` |
| 203 | `3;` | `3` | `uint32_t last_byte = x2 >> 3;` |
| 204 | `7;` | `7` | `uint8_t shift = x1 & 7;` |
| 206 | `0xFF` | `255` | `uint8_t left_mask = 0xFF >> shift;` |
| 207 | `0xFF` | `255` | `uint8_t right_mask = 0xFF << (7 - (x2 & 7));` |
| 207 | `(7` | `7` | `uint8_t right_mask = 0xFF << (7 - (x2 & 7));` |
| 207 | `7));` | `7` | `uint8_t right_mask = 0xFF << (7 - (x2 & 7));` |
| 232 | `(8` | `8` | `uint8_t val = (carry << (8 - shift)) \| (*s >> shift);` |
| 288 | `40;` | `40` | `uint32_t buffer_lines = 40;` |
| 298 | `0xFF);` | `255` | `palette[0] = lv_color32_make(0x00, 0x00, 0x00, 0xFF);` |
| 299 | `0xFF,` | `255` | `palette[1] = lv_color32_make(0xFF, 0xFF, 0xFF, 0xFF);` |
| 299 | `0xFF,` | `255` | `palette[1] = lv_color32_make(0xFF, 0xFF, 0xFF, 0xFF);` |
| 299 | `0xFF);` | `255` | `palette[1] = lv_color32_make(0xFF, 0xFF, 0xFF, 0xFF);` |
| 302 | `0xFF,` | `255` | `memset(buf1 + LVGL_I1_PALETTE_SIZE, 0xFF, buf_size - LVGL_I1_PALETTE_SIZE);` |
| 312 | `2000);` | `2000` | `lv_indev_set_long_press_time(s_lv_keypad_indev, 2000);` |
| 358 | `5;` | `5` | `task_priority = (task_priority > 0) ? task_priority : 5;` |
| 365 | `8192,` | `8192` | `8192,` |
| 395 | `6000)` | `6000` | `while (s_lvgl_task_handle != NULL && wait_ms < 6000) {` |
| 397 | `20;` | `20` | `wait_ms += 20;` |

### `components\h1os\src\h1os_time.c` (3 matches)

| Line | Token | Value | Context |
| :---: | :---: | :---: | :--- |
| 34 | `64)` | `64` | `if (tz_str == NULL \|\| strlen(tz_str) == 0 \|\| strlen(tz_str) > 64) {` |
| 73 | `1900,` | `1900` | `timeinfo.tm_year + 1900,` |
| 108 | `1900,` | `1900` | `tm_target.tm_year + 1900,` |

### `components\h1os\src\hal_flash.c` (2 matches)

| Line | Token | Value | Context |
| :---: | :---: | :---: | :--- |
| 89 | `4095)` | `4095` | `size_t erase_size = (len + 4095) & ~4095;` |
| 89 | `~4095;` | `4095` | `size_t erase_size = (len + 4095) & ~4095;` |

### `components\h1os\src\hal_i2c.c` (2 matches)

| Line | Token | Value | Context |
| :---: | :---: | :---: | :--- |
| 92 | `7,` | `7` | `.glitch_ignore_cnt = 7,` |
| 298 | `50);` | `50` | `esp_err_t ret = i2c_master_probe(s_bus_handle, dev_addr, 50);` |

### `components\h1os\src\hal_io.c` (20 matches)

| Line | Token | Value | Context |
| :---: | :---: | :---: | :--- |
| 112 | `5000` | `5000` | `#define HAL_LEDC_FREQUENCY 5000` |
| 166 | `3` | `3` | `ESP_LOGD(TAG, "LEDC PWM initialized on GPIO 3 (Active LOW).");` |
| 186 | `100)` | `100` | `if (brightness_pct > 100) {` |
| 187 | `100;` | `100` | `brightness_pct = 100;` |
| 189 | `1023U)` | `1023` | `uint32_t duty = ((uint32_t)brightness_pct * 1023U) / 100U;` |
| 189 | `100U;` | `100` | `uint32_t duty = ((uint32_t)brightness_pct * 1023U) / 100U;` |
| 213 | `100)` | `100` | `if (target_pct > 100) {` |
| 214 | `100;` | `100` | `target_pct = 100;` |
| 216 | `1023U)` | `1023` | `uint32_t target_duty = ((uint32_t)target_pct * 1023U) / 100U;` |
| 216 | `100U;` | `100` | `uint32_t target_duty = ((uint32_t)target_pct * 1023U) / 100U;` |
| 223 | `2000;` | `2000` | `static volatile uint32_t s_breath_period_ms = 2000;` |
| 236 | `2U;` | `2` | `uint32_t half = s_breath_period_ms / 2U;` |
| 237 | `100U)` | `100` | `if (half < 100U) {` |
| 238 | `100U;` | `100` | `half = 100U;` |
| 284 | `2000;` | `2000` | `cycle_period_ms = 2000;` |
| 293 | `2048,` | `2048` | `BaseType_t res = xTaskCreate(led_breath_task, "led_breath", 2048, NULL, 1, (TaskHandle_t *)&s_breath_task);` |
| 313 | `15;` | `15` | `int32_t wait_cycles = 15;` |
| 381 | `100` | `100` | `return hal_led_set_brightness(on ? 100 : 0);` |
| 497 | `0x7FF;` | `2047` | `uint32_t f1 = REG_READ(USB_SERIAL_JTAG_FRAM_NUM_REG) & 0x7FF;` |
| 503 | `0x7FF;` | `2047` | `uint32_t f2 = REG_READ(USB_SERIAL_JTAG_FRAM_NUM_REG) & 0x7FF;` |

### `components\h1os\src\hal_spi.c` (15 matches)

| Line | Token | Value | Context |
| :---: | :---: | :---: | :--- |
| 85 | `8,` | `8` | `.max_transfer_sz = HAL_EPD_FRAME_SIZE_BYTES + 8,` |
| 95 | `20` | `20` | `.clock_speed_hz = 20 * 1000 * 1000,` |
| 95 | `1000` | `1000` | `.clock_speed_hz = 20 * 1000 * 1000,` |
| 95 | `1000,` | `1000` | `.clock_speed_hz = 20 * 1000 * 1000,` |
| 98 | `7,` | `7` | `.queue_size = 7,` |
| 109 | `2` | `2` | `.clock_speed_hz = 2 * 1000 * 1000,` |
| 109 | `1000` | `1000` | `.clock_speed_hz = 2 * 1000 * 1000,` |
| 109 | `1000,` | `1000` | `.clock_speed_hz = 2 * 1000 * 1000,` |
| 123 | `(20` | `20` | `"SPI2 bus initialized with DMA (20 MHz write, 2 MHz half-duplex read) on CS=%d, "` |
| 123 | `2` | `2` | `"SPI2 bus initialized with DMA (20 MHz write, 2 MHz half-duplex read) on CS=%d, "` |
| 174 | `8;` | `8` | `t.length = 8;` |
| 201 | `8;` | `8` | `t.length = len * 8;` |
| 227 | `8;` | `8` | `t.length = HAL_EPD_FRAME_SIZE_BYTES * 8;` |
| 259 | `8;` | `8` | `t_cmd.length = 8;` |
| 274 | `8;` | `8` | `t_read.rxlength = len * 8;` |

### `components\h1os\src\orch_display_sync.c` (1 matches)

| Line | Token | Value | Context |
| :---: | :---: | :---: | :--- |
| 20 | `6` | `6` | `#define CONFIG_H1OS_EPD_PARTIAL_REFRESH_LIMIT 6` |

### `components\h1os\src\orch_flow.c` (8 matches)

| Line | Token | Value | Context |
| :---: | :---: | :---: | :--- |
| 64 | `10);` | `10` | `st->tsens_cal_centi_c = (int16_t)(cal_deci_c * 10);` |
| 70 | `17)` | `17` | `uint32_t g17_out  = (REG_READ(GPIO_OUT_REG) >> 17) & 1U;` |
| 71 | `17)` | `17` | `uint32_t g17_oe   = (REG_READ(GPIO_ENABLE_REG) >> 17) & 1U;` |
| 72 | `17)` | `17` | `uint32_t g17_hold = (REG_READ(RTC_CNTL_PAD_HOLD_REG) >> 17) & 1U;` |
| 91 | `0xFF);` | `255` | `st->ulp_dispatch_reason = (uint8_t)(ulp_dispatch_reason & 0xFF);` |
| 115 | `2);` | `2` | `return (orch_state_get()->valid_trend < 2);` |
| 394 | `3;` | `3` | `for (int32_t attempt = 0; attempt < 3; attempt++) {` |
| 402 | `3` | `3` | `ESP_LOGE(TAG, "Failed to arm PCF85063A countdown after 3 attempts: %s", esp_err_to_name(rtc_err));` |

### `components\h1os\src\orch_state.c` (1 matches)

| Line | Token | Value | Context |
| :---: | :---: | :---: | :--- |
| 84 | `1000;` | `1000` | `st->initial_soc_x10      = (current_soc_x10 > 0) ? current_soc_x10 : 1000;` |

### `components\h1os\src\orch_wake_stub.c` (47 matches)

| Line | Token | Value | Context |
| :---: | :---: | :---: | :--- |
| 28 | `0x104)` | `260` | `#define SENS_SAR_PERI_CLK_GATE_CONF_REG (DR_REG_SENS_BASE + 0x104)` |
| 31 | `29)` | `29` | `#define SENS_TSENS_CLK_EN (1UL << 29)` |
| 35 | `32))` | `32` | `#define SDA_BIT_MASK (1UL << (HAL_PIN_I2C_SDA - 32))` |
| 36 | `32))` | `32` | `#define SCL_BIT_MASK (1UL << (HAL_PIN_I2C_SCL - 32))` |
| 38 | `0x70` | `112` | `#define I2C_ADDR_SHTC3     0x70` |
| 39 | `0x51` | `81` | `#define I2C_ADDR_PCF85063  0x51` |
| 41 | `0x10` | `16` | `#define RTC_REG_TIMER_VAL  0x10` |
| 42 | `0x11` | `17` | `#define RTC_REG_TIMER_MODE 0x11` |
| 44 | `(2` | `2` | `#define RTC_TIMER_CLK_1_HZ    (2 << 3)` |
| 44 | `3)` | `3` | `#define RTC_TIMER_CLK_1_HZ    (2 << 3)` |
| 45 | `(3` | `3` | `#define RTC_TIMER_CLK_1_60_HZ (3 << 3)` |
| 45 | `3)` | `3` | `#define RTC_TIMER_CLK_1_60_HZ (3 << 3)` |
| 49 | `2)` | `2` | `#define RTC_TIMER_TE_BIT      (1 << 2)` |
| 50 | `(3` | `3` | `#define RTC_TIMER_TCF_MASK    (3 << 3)` |
| 50 | `3)` | `3` | `#define RTC_TIMER_TCF_MASK    (3 << 3)` |
| 51 | `(3` | `3` | `#define RTC_TIMER_TCF_MIN     (3 << 3)` |
| 51 | `3)` | `3` | `#define RTC_TIMER_TCF_MIN     (3 << 3)` |
| 52 | `0x07` | `7` | `#define RTC_CTRL2_COF_OFF     0x07` |
| 110 | `7;` | `7` | `for (int32_t i = 7; i >= 0; i--) {` |
| 138 | `7;` | `7` | `for (int32_t i = 7; i >= 0; i--) {` |
| 165 | `0xFF;` | `255` | `uint8_t crc = 0xFF;` |
| 168 | `8;` | `8` | `for (uint8_t bit = 8; bit > 0; --bit) {` |
| 169 | `0x80)` | `128` | `if (crc & 0x80) {` |
| 170 | `0x31);` | `49` | `crc = (uint8_t)((crc << 1) ^ 0x31);` |
| 192 | `6);` | `6` | `REG_SET_FIELD(SENS_SAR_TSENS_CTRL_REG, SENS_TSENS_CLK_DIV, 6);` |
| 193 | `3);` | `3` | `REG_SET_FIELD(SENS_SAR_TSENS_CTRL2_REG, SENS_TSENS_XPD_FORCE, 3);` |
| 210 | `0xFF)` | `255` | `if (timeout <= 0 \|\| raw == 0 \|\| raw == 0xFF) {` |
| 215 | `179651)` | `179651` | `int32_t t_centi = (((int32_t)raw * 179651) >> 12) - (int32_t)offset_centi_c;` |
| 215 | `12)` | `12` | `int32_t t_centi = (((int32_t)raw * 179651) >> 12) - (int32_t)offset_centi_c;` |
| 216 | `-4000` | `4000` | `if (t_centi < -4000 \|\| t_centi > 12500) {` |
| 216 | `12500)` | `12500` | `if (t_centi < -4000 \|\| t_centi > 12500) {` |
| 227 | `3;` | `3` | `for (int32_t attempt = 0; attempt < 3; attempt++) {` |
| 258 | `255)` | `255` | `if (seconds <= 255) {` |
| 263 | `59)` | `59` | `timer_val = (uint8_t)((seconds + 59) / 60);` |
| 263 | `60);` | `60` | `timer_val = (uint8_t)((seconds + 59) / 60);` |
| 290 | `3;` | `3` | `for (int32_t attempt = 0; attempt < 3; attempt++) {` |
| 383 | `2)` | `2` | `if (sample_ok && shtc3_crc8(&rx[0], 2) == rx[2] && shtc3_crc8(&rx[3], 2) == rx[5]) {` |
| 383 | `2)` | `2` | `if (sample_ok && shtc3_crc8(&rx[0], 2) == rx[2] && shtc3_crc8(&rx[3], 2) == rx[5]) {` |
| 384 | `8)` | `8` | `uint16_t raw_t  = ((uint16_t)rx[0] << 8) \| rx[1];` |
| 385 | `8)` | `8` | `uint16_t raw_rh = ((uint16_t)rx[3] << 8) \| rx[4];` |
| 388 | `65535U));` | `65535` | `int16_t  temp_centi_c = (int16_t)(-4500 + (int32_t)((17500U * (uint32_t)raw_t) / 65535U));` |
| 389 | `65535U);` | `65535` | `uint16_t rh_centi_pct = (uint16_t)((10000U * (uint32_t)raw_rh) / 65535U);` |
| 406 | `2)` | `2` | `if (st->valid_trend < 2) {` |
| 407 | `2;` | `2` | `st->valid_trend = 2;` |
| 441 | `20000;` | `20000` | `uint32_t timeout_us = 20000;` |
| 444 | `500)` | `500` | `if (timeout_us <= 500) {` |
| 447 | `500;` | `500` | `timeout_us -= 500;` |

### `components\h1os\src\sub_audio.c` (148 matches)

| Line | Token | Value | Context |
| :---: | :---: | :---: | :--- |
| 34 | `0x0D` | `13` | `#define ES8311_REG_SYS_PWR_ANA 0x0D` |
| 35 | `0x0F` | `15` | `#define ES8311_REG_SYS_LP_MOD  0x0F` |
| 36 | `0x12` | `18` | `#define ES8311_REG_DAC_PWR     0x12` |
| 37 | `0x32` | `50` | `#define ES8311_REG_DAC_VOL     0x32` |
| 38 | `0xFC` | `252` | `#define ES8311_REG_FLAG        0xFC` |
| 39 | `0xFD` | `253` | `#define ES8311_REG_CHIP_ID1    0xFD` |
| 40 | `0xFE` | `254` | `#define ES8311_REG_CHIP_ID2    0xFE` |
| 42 | `0x100` | `256` | `#define FRAME_SIZE 0x100` |
| 128 | `0x3A,` | `58` | `0x00, 0x3A, 0x48, 0x51, 0x57, 0x5D,` |
| 128 | `0x48,` | `72` | `0x00, 0x3A, 0x48, 0x51, 0x57, 0x5D,` |
| 128 | `0x51,` | `81` | `0x00, 0x3A, 0x48, 0x51, 0x57, 0x5D,` |
| 128 | `0x57,` | `87` | `0x00, 0x3A, 0x48, 0x51, 0x57, 0x5D,` |
| 128 | `0x5D,` | `93` | `0x00, 0x3A, 0x48, 0x51, 0x57, 0x5D,` |
| 129 | `0x61,` | `97` | `0x61, 0x65, 0x68, 0x6B, 0x6E, 0x71,` |
| 129 | `0x65,` | `101` | `0x61, 0x65, 0x68, 0x6B, 0x6E, 0x71,` |
| 129 | `0x68,` | `104` | `0x61, 0x65, 0x68, 0x6B, 0x6E, 0x71,` |
| 129 | `0x6B,` | `107` | `0x61, 0x65, 0x68, 0x6B, 0x6E, 0x71,` |
| 129 | `0x6E,` | `110` | `0x61, 0x65, 0x68, 0x6B, 0x6E, 0x71,` |
| 129 | `0x71,` | `113` | `0x61, 0x65, 0x68, 0x6B, 0x6E, 0x71,` |
| 130 | `0x73,` | `115` | `0x73, 0x75, 0x77, 0x79, 0x7B, 0x7D,` |
| 130 | `0x75,` | `117` | `0x73, 0x75, 0x77, 0x79, 0x7B, 0x7D,` |
| 130 | `0x77,` | `119` | `0x73, 0x75, 0x77, 0x79, 0x7B, 0x7D,` |
| 130 | `0x79,` | `121` | `0x73, 0x75, 0x77, 0x79, 0x7B, 0x7D,` |
| 130 | `0x7B,` | `123` | `0x73, 0x75, 0x77, 0x79, 0x7B, 0x7D,` |
| 130 | `0x7D,` | `125` | `0x73, 0x75, 0x77, 0x79, 0x7B, 0x7D,` |
| 131 | `0x7E,` | `126` | `0x7E, 0x80, 0x81, 0x83, 0x84, 0x85,` |
| 131 | `0x80,` | `128` | `0x7E, 0x80, 0x81, 0x83, 0x84, 0x85,` |
| 131 | `0x81,` | `129` | `0x7E, 0x80, 0x81, 0x83, 0x84, 0x85,` |
| 131 | `0x83,` | `131` | `0x7E, 0x80, 0x81, 0x83, 0x84, 0x85,` |
| 131 | `0x84,` | `132` | `0x7E, 0x80, 0x81, 0x83, 0x84, 0x85,` |
| 131 | `0x85,` | `133` | `0x7E, 0x80, 0x81, 0x83, 0x84, 0x85,` |
| 132 | `0x87,` | `135` | `0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C,` |
| 132 | `0x88,` | `136` | `0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C,` |
| 132 | `0x89,` | `137` | `0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C,` |
| 132 | `0x8A,` | `138` | `0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C,` |
| 132 | `0x8B,` | `139` | `0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C,` |
| 132 | `0x8C,` | `140` | `0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C,` |
| 133 | `0x8D,` | `141` | `0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92,` |
| 133 | `0x8E,` | `142` | `0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92,` |
| 133 | `0x8F,` | `143` | `0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92,` |
| 133 | `0x90,` | `144` | `0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92,` |
| 133 | `0x91,` | `145` | `0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92,` |
| 133 | `0x92,` | `146` | `0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92,` |
| 134 | `0x93,` | `147` | `0x93, 0x94, 0x95, 0x96, 0x97, 0x98,` |
| 134 | `0x94,` | `148` | `0x93, 0x94, 0x95, 0x96, 0x97, 0x98,` |
| 134 | `0x95,` | `149` | `0x93, 0x94, 0x95, 0x96, 0x97, 0x98,` |
| 134 | `0x96,` | `150` | `0x93, 0x94, 0x95, 0x96, 0x97, 0x98,` |
| 134 | `0x97,` | `151` | `0x93, 0x94, 0x95, 0x96, 0x97, 0x98,` |
| 134 | `0x98,` | `152` | `0x93, 0x94, 0x95, 0x96, 0x97, 0x98,` |
| 135 | `0x99,` | `153` | `0x99, 0x99, 0x9A, 0x9B, 0x9C, 0x9D,` |
| 135 | `0x99,` | `153` | `0x99, 0x99, 0x9A, 0x9B, 0x9C, 0x9D,` |
| 135 | `0x9A,` | `154` | `0x99, 0x99, 0x9A, 0x9B, 0x9C, 0x9D,` |
| 135 | `0x9B,` | `155` | `0x99, 0x99, 0x9A, 0x9B, 0x9C, 0x9D,` |
| 135 | `0x9C,` | `156` | `0x99, 0x99, 0x9A, 0x9B, 0x9C, 0x9D,` |
| 135 | `0x9D,` | `157` | `0x99, 0x99, 0x9A, 0x9B, 0x9C, 0x9D,` |
| 136 | `0x9E,` | `158` | `0x9E, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2,` |
| 136 | `0x9E,` | `158` | `0x9E, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2,` |
| 136 | `0x9F,` | `159` | `0x9E, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2,` |
| 136 | `0xA0,` | `160` | `0x9E, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2,` |
| 136 | `0xA1,` | `161` | `0x9E, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2,` |
| 136 | `0xA2,` | `162` | `0x9E, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2,` |
| 137 | `0xA2,` | `162` | `0xA2, 0xA3, 0xA4, 0xA5, 0xA5, 0xA6,` |
| 137 | `0xA3,` | `163` | `0xA2, 0xA3, 0xA4, 0xA5, 0xA5, 0xA6,` |
| 137 | `0xA4,` | `164` | `0xA2, 0xA3, 0xA4, 0xA5, 0xA5, 0xA6,` |
| 137 | `0xA5,` | `165` | `0xA2, 0xA3, 0xA4, 0xA5, 0xA5, 0xA6,` |
| 137 | `0xA5,` | `165` | `0xA2, 0xA3, 0xA4, 0xA5, 0xA5, 0xA6,` |
| 137 | `0xA6,` | `166` | `0xA2, 0xA3, 0xA4, 0xA5, 0xA5, 0xA6,` |
| 138 | `0xA7,` | `167` | `0xA7, 0xA8, 0xA8, 0xA9, 0xAA, 0xAA,` |
| 138 | `0xA8,` | `168` | `0xA7, 0xA8, 0xA8, 0xA9, 0xAA, 0xAA,` |
| 138 | `0xA8,` | `168` | `0xA7, 0xA8, 0xA8, 0xA9, 0xAA, 0xAA,` |
| 138 | `0xA9,` | `169` | `0xA7, 0xA8, 0xA8, 0xA9, 0xAA, 0xAA,` |
| 138 | `0xAA,` | `170` | `0xA7, 0xA8, 0xA8, 0xA9, 0xAA, 0xAA,` |
| 138 | `0xAA,` | `170` | `0xA7, 0xA8, 0xA8, 0xA9, 0xAA, 0xAA,` |
| 139 | `0xAB,` | `171` | `0xAB, 0xAC, 0xAC, 0xAD, 0xAE, 0xAE,` |
| 139 | `0xAC,` | `172` | `0xAB, 0xAC, 0xAC, 0xAD, 0xAE, 0xAE,` |
| 139 | `0xAC,` | `172` | `0xAB, 0xAC, 0xAC, 0xAD, 0xAE, 0xAE,` |
| 139 | `0xAD,` | `173` | `0xAB, 0xAC, 0xAC, 0xAD, 0xAE, 0xAE,` |
| 139 | `0xAE,` | `174` | `0xAB, 0xAC, 0xAC, 0xAD, 0xAE, 0xAE,` |
| 139 | `0xAE,` | `174` | `0xAB, 0xAC, 0xAC, 0xAD, 0xAE, 0xAE,` |
| 140 | `0xAF,` | `175` | `0xAF, 0xB0, 0xB0, 0xB1, 0xB2, 0xB2,` |
| 140 | `0xB0,` | `176` | `0xAF, 0xB0, 0xB0, 0xB1, 0xB2, 0xB2,` |
| 140 | `0xB0,` | `176` | `0xAF, 0xB0, 0xB0, 0xB1, 0xB2, 0xB2,` |
| 140 | `0xB1,` | `177` | `0xAF, 0xB0, 0xB0, 0xB1, 0xB2, 0xB2,` |
| 140 | `0xB2,` | `178` | `0xAF, 0xB0, 0xB0, 0xB1, 0xB2, 0xB2,` |
| 140 | `0xB2,` | `178` | `0xAF, 0xB0, 0xB0, 0xB1, 0xB2, 0xB2,` |
| 141 | `0xB3,` | `179` | `0xB3, 0xB3, 0xB4, 0xB5, 0xB5, 0xB6,` |
| 141 | `0xB3,` | `179` | `0xB3, 0xB3, 0xB4, 0xB5, 0xB5, 0xB6,` |
| 141 | `0xB4,` | `180` | `0xB3, 0xB3, 0xB4, 0xB5, 0xB5, 0xB6,` |
| 141 | `0xB5,` | `181` | `0xB3, 0xB3, 0xB4, 0xB5, 0xB5, 0xB6,` |
| 141 | `0xB5,` | `181` | `0xB3, 0xB3, 0xB4, 0xB5, 0xB5, 0xB6,` |
| 141 | `0xB6,` | `182` | `0xB3, 0xB3, 0xB4, 0xB5, 0xB5, 0xB6,` |
| 142 | `0xB6,` | `182` | `0xB6, 0xB7, 0xB7, 0xB8, 0xB9, 0xB9,` |
| 142 | `0xB7,` | `183` | `0xB6, 0xB7, 0xB7, 0xB8, 0xB9, 0xB9,` |
| 142 | `0xB7,` | `183` | `0xB6, 0xB7, 0xB7, 0xB8, 0xB9, 0xB9,` |
| 142 | `0xB8,` | `184` | `0xB6, 0xB7, 0xB7, 0xB8, 0xB9, 0xB9,` |
| 142 | `0xB9,` | `185` | `0xB6, 0xB7, 0xB7, 0xB8, 0xB9, 0xB9,` |
| 142 | `0xB9,` | `185` | `0xB6, 0xB7, 0xB7, 0xB8, 0xB9, 0xB9,` |
| 143 | `0xBA,` | `186` | `0xBA, 0xBA, 0xBB, 0xBC, 0xBC, 0xBD,` |
| 143 | `0xBA,` | `186` | `0xBA, 0xBA, 0xBB, 0xBC, 0xBC, 0xBD,` |
| 143 | `0xBB,` | `187` | `0xBA, 0xBA, 0xBB, 0xBC, 0xBC, 0xBD,` |
| 143 | `0xBC,` | `188` | `0xBA, 0xBA, 0xBB, 0xBC, 0xBC, 0xBD,` |
| 143 | `0xBC,` | `188` | `0xBA, 0xBA, 0xBB, 0xBC, 0xBC, 0xBD,` |
| 143 | `0xBD,` | `189` | `0xBA, 0xBA, 0xBB, 0xBC, 0xBC, 0xBD,` |
| 144 | `0xBD,` | `189` | `0xBD, 0xBE, 0xBE, 0xBF, 0xBF` |
| 144 | `0xBE,` | `190` | `0xBD, 0xBE, 0xBE, 0xBF, 0xBF` |
| 144 | `0xBE,` | `190` | `0xBD, 0xBE, 0xBE, 0xBF, 0xBF` |
| 144 | `0xBF,` | `191` | `0xBD, 0xBE, 0xBE, 0xBF, 0xBF` |
| 144 | `0xBF` | `191` | `0xBD, 0xBE, 0xBE, 0xBF, 0xBF` |
| 254 | `100)` | `100` | `if (pct > 100) {` |
| 255 | `100;` | `100` | `pct = 100;` |
| 310 | `0x8311)` | `33553` | `if (err1 != ESP_OK \|\| err2 != ESP_OK \|\| *chip_id != 0x8311) {` |
| 354 | `5;` | `5` | `const uint32_t step_ms = 5;` |
| 358 | `4)` | `4` | `uint8_t csm_state = (flag >> 4) & 0x07;` |
| 358 | `0x07;` | `7` | `uint8_t csm_state = (flag >> 4) & 0x07;` |
| 416 | `0x80` | `128` | `ret \|= es8311_write_reg(ES8311_REG_SYS_LP_MOD, s_low_power_mode ? 0x80 : 0x00);` |
| 458 | `0x8311)` | `33553` | `if (chip_id != 0x8311) {` |
| 459 | `0x8311)",` | `33553` | `ESP_LOGE(TAG, "Chip ID invalid (0x%04X, expected 0x8311)", chip_id);` |
| 469 | `4;` | `4` | `chan_cfg.dma_desc_num      = 4;` |
| 530 | `4096,` | `4096` | `4096,` |
| 532 | `6,` | `6` | `6,` |
| 590 | `120` | `120` | `vTaskDelay(pdMS_TO_TICKS(target_enabled ? 120 : 80));` |
| 590 | `80));` | `80` | `vTaskDelay(pdMS_TO_TICKS(target_enabled ? 120 : 80));` |
| 638 | `16000;` | `16000` | `const uint32_t sample_rate   = 16000;` |
| 639 | `1000;` | `1000` | `const uint32_t total_samples = (sample_rate * duration_ms) / 1000;` |
| 640 | `64)` | `64` | `const uint32_t ramp_samples  = (total_samples > 64) ? 32 : (total_samples / 4);` |
| 640 | `32` | `32` | `const uint32_t ramp_samples  = (total_samples > 64) ? 32 : (total_samples / 4);` |
| 640 | `4);` | `4` | `const uint32_t ramp_samples  = (total_samples > 64) ? 32 : (total_samples / 4);` |
| 810 | `70);` | `70` | `sub_audio_render_tone_samples(523, 70);` |
| 812 | `70);` | `70` | `sub_audio_render_tone_samples(659, 70);` |
| 814 | `70);` | `70` | `sub_audio_render_tone_samples(784, 70);` |
| 816 | `150);` | `150` | `sub_audio_render_tone_samples(1046, 150);` |
| 820 | `80);` | `80` | `sub_audio_render_tone_samples(1046, 80);` |
| 822 | `80);` | `80` | `sub_audio_render_tone_samples(784, 80);` |
| 824 | `140);` | `140` | `sub_audio_render_tone_samples(659, 140);` |
| 828 | `90);` | `90` | `sub_audio_render_tone_samples(784, 90);` |
| 830 | `90);` | `90` | `sub_audio_render_tone_samples(659, 90);` |
| 832 | `180);` | `180` | `sub_audio_render_tone_samples(523, 180);` |
| 836 | `2;` | `2` | `for (int32_t i = 0; i < 2; i++) {` |
| 837 | `80);` | `80` | `sub_audio_render_tone_samples(1760, 80);` |
| 839 | `80);` | `80` | `sub_audio_render_tone_samples(880, 80);` |
| 948 | `500;` | `500` | `const uint32_t timeout_ms = (wait_ms > 0) ? wait_ms : 500;` |
| 981 | `(2` | `2` | `if (len < (2 * sizeof(uint32_t))) {` |
| 1004 | `16000;` | `16000` | `cmd.params.pcm.sample_rate_hz = 16000;` |
| 1011 | `50);` | `50` | `return sub_audio_send_command(&cmd, false, 50);` |
| 1044 | `10;` | `10` | `elapsed += 10;` |
| 1099 | `100)` | `100` | `if (volume_pct > 100) {` |
| 1100 | `100;` | `100` | `volume_pct = 100;` |
| 1139 | `0x80` | `128` | `return es8311_write_reg(ES8311_REG_SYS_LP_MOD, enable ? 0x80 : 0x00);` |

### `components\h1os\src\sub_display.cpp` (86 matches)

| Line | Token | Value | Context |
| :---: | :---: | :---: | :--- |
| 35 | `0x40,` | `64` | `0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,` |
| 35 | `0x80,` | `128` | `0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,` |
| 35 | `0x80,` | `128` | `0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,` |
| 36 | `0x40,` | `64` | `0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,` |
| 36 | `0x40,` | `64` | `0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,` |
| 37 | `0x80,` | `128` | `0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,` |
| 38 | `0x0F,` | `15` | `0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00,` |
| 43 | `0x22,` | `34` | `0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x02, 0x17, 0x41, 0xB0, 0x32, 0x28};` |
| 43 | `0x22,` | `34` | `0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x02, 0x17, 0x41, 0xB0, 0x32, 0x28};` |
| 43 | `0x22,` | `34` | `0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x02, 0x17, 0x41, 0xB0, 0x32, 0x28};` |
| 43 | `0x22,` | `34` | `0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x02, 0x17, 0x41, 0xB0, 0x32, 0x28};` |
| 43 | `0x22,` | `34` | `0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x02, 0x17, 0x41, 0xB0, 0x32, 0x28};` |
| 43 | `0x22,` | `34` | `0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x02, 0x17, 0x41, 0xB0, 0x32, 0x28};` |
| 43 | `0x02,` | `2` | `0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x02, 0x17, 0x41, 0xB0, 0x32, 0x28};` |
| 43 | `0x17,` | `23` | `0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x02, 0x17, 0x41, 0xB0, 0x32, 0x28};` |
| 43 | `0x41,` | `65` | `0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x02, 0x17, 0x41, 0xB0, 0x32, 0x28};` |
| 43 | `0xB0,` | `176` | `0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x02, 0x17, 0x41, 0xB0, 0x32, 0x28};` |
| 43 | `0x32,` | `50` | `0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x02, 0x17, 0x41, 0xB0, 0x32, 0x28};` |
| 43 | `0x28};` | `40` | `0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x02, 0x17, 0x41, 0xB0, 0x32, 0x28};` |
| 75 | `60;` | `60` | `for (int32_t i = 0; i < 60; i++) {` |
| 102 | `{0xC7,` | `199` | `uint8_t d_drv[] = {0xC7, 0x00, 0x00};` |
| 106 | `{0x03};` | `3` | `uint8_t d_entry[] = {0x03};` |
| 107 | `0x11` | `17` | `ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x11), TAG, "SPI cmd 0x11 failed");` |
| 108 | `0x11` | `17` | `ESP_RETURN_ON_ERROR(hal_spi_write_data(d_entry, sizeof(d_entry)), TAG, "SPI data 0x11 failed");` |
| 110 | `0x18};` | `24` | `uint8_t d_xwin[] = {0x00, 0x18};` |
| 111 | `0x44` | `68` | `ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x44), TAG, "SPI cmd 0x44 failed");` |
| 112 | `0x44` | `68` | `ESP_RETURN_ON_ERROR(hal_spi_write_data(d_xwin, sizeof(d_xwin)), TAG, "SPI data 0x44 failed");` |
| 114 | `0xC7,` | `199` | `uint8_t d_ywin[] = {0x00, 0x00, 0xC7, 0x00};` |
| 115 | `0x45` | `69` | `ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x45), TAG, "SPI cmd 0x45 failed");` |
| 116 | `0x45` | `69` | `ESP_RETURN_ON_ERROR(hal_spi_write_data(d_ywin, sizeof(d_ywin)), TAG, "SPI data 0x45 failed");` |
| 118 | `{0x05};` | `5` | `uint8_t d_border[] = {0x05};` |
| 119 | `0x3C` | `60` | `ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x3C), TAG, "SPI cmd 0x3C failed");` |
| 120 | `0x3C` | `60` | `ESP_RETURN_ON_ERROR(hal_spi_write_data(d_border, sizeof(d_border)), TAG, "SPI data 0x3C failed");` |
| 164 | `50;` | `50` | `static constexpr int16_t SSD1681_TEMP_HALF_DEG_CENTI_C = 50;` |
| 168 | `{0x80};` | `128` | `uint8_t t_sel[] = {0x80};` |
| 172 | `{0xB1};` | `177` | `uint8_t t_load[] = {0xB1};` |
| 179 | `0xFF)` | `255` | `if (temp_raw[0] != 0x00 && temp_raw[0] != 0xFF) {` |
| 181 | `0x80)` | `128` | `int16_t frac_c = (temp_raw[1] & 0x80) ? SSD1681_TEMP_HALF_DEG_CENTI_C : 0;` |
| 182 | `100` | `100` | `int16_t glass_cc = (int16_t)temp_int * 100 + ((temp_int >= 0) ? frac_c : -frac_c);` |
| 183 | `-4000` | `4000` | `if (glass_cc >= -4000 && glass_cc <= 8500) {` |
| 183 | `8500)` | `8500` | `if (glass_cc >= -4000 && glass_cc <= 8500) {` |
| 193 | `0xFF,` | `255` | `memset(s_current_frame, 0xFF, EPD_BUFFER_SIZE);` |
| 194 | `0xFF,` | `255` | `memset(s_previous_frame, 0xFF, EPD_BUFFER_SIZE);` |
| 245 | `0x4E` | `78` | `ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x4E), TAG, "SPI cmd 0x4E failed");` |
| 246 | `0x4E` | `78` | `ESP_RETURN_ON_ERROR(hal_spi_write_data(d_x, sizeof(d_x)), TAG, "SPI data 0x4E failed");` |
| 247 | `0x4F` | `79` | `ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x4F), TAG, "SPI cmd 0x4F failed");` |
| 248 | `0x4F` | `79` | `ESP_RETURN_ON_ERROR(hal_spi_write_data(d_y, sizeof(d_y)), TAG, "SPI data 0x4F failed");` |
| 274 | `0x26` | `38` | `ESP_LOGI(TAG, "SSD1681 RAM 0x26 synchronized with prior frame for differential scan");` |
| 293 | `0x12` | `18` | `ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x12), TAG, "SPI cmd 0x12 failed");` |
| 297 | `0x24` | `36` | `ESP_RETURN_ON_ERROR(epd_commit_ram_dma(0x24, s_current_frame), TAG, "Commit RAM 0x24 failed");` |
| 298 | `0x26` | `38` | `ESP_RETURN_ON_ERROR(epd_commit_ram_dma(0x26, s_current_frame), TAG, "Commit RAM 0x26 failed");` |
| 300 | `{0xF7};` | `247` | `uint8_t d_upd[] = {0xF7};` |
| 301 | `0x22` | `34` | `ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x22), TAG, "SPI cmd 0x22 failed");` |
| 302 | `0x22` | `34` | `ESP_RETURN_ON_ERROR(hal_spi_write_data(d_upd, sizeof(d_upd)), TAG, "SPI data 0x22 failed");` |
| 304 | `0x20` | `32` | `ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x20), TAG, "SPI cmd 0x20 failed");` |
| 309 | `1000LL;` | `1000` | `int64_t t_elapsed_ms = (esp_timer_get_time() - t_start) / 1000LL;` |
| 329 | `0xFF,` | `255` | `memset(s_current_frame, 0xFF, EPD_BUFFER_SIZE);` |
| 330 | `0xFF,` | `255` | `memset(s_previous_frame, 0xFF, EPD_BUFFER_SIZE);` |
| 348 | `0x32` | `50` | `ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x32), TAG, "SPI cmd 0x32 failed");` |
| 349 | `153),` | `153` | `ESP_RETURN_ON_ERROR(hal_spi_write_data(&lut_buffer[0], 153), TAG, "SPI data 0x32 failed");` |
| 349 | `0x32` | `50` | `ESP_RETURN_ON_ERROR(hal_spi_write_data(&lut_buffer[0], 153), TAG, "SPI data 0x32 failed");` |
| 351 | `0x3F` | `63` | `ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x3F), TAG, "SPI cmd 0x3F failed");` |
| 352 | `0x3F` | `63` | `ESP_RETURN_ON_ERROR(hal_spi_write_data(&lut_buffer[153], 1), TAG, "SPI data 0x3F failed");` |
| 354 | `0x03` | `3` | `ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x03), TAG, "SPI cmd 0x03 failed");` |
| 355 | `0x03` | `3` | `ESP_RETURN_ON_ERROR(hal_spi_write_data(&lut_buffer[154], 1), TAG, "SPI data 0x03 failed");` |
| 357 | `0x04` | `4` | `ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x04), TAG, "SPI cmd 0x04 failed");` |
| 358 | `3),` | `3` | `ESP_RETURN_ON_ERROR(hal_spi_write_data(&lut_buffer[155], 3), TAG, "SPI data 0x04 failed");` |
| 358 | `0x04` | `4` | `ESP_RETURN_ON_ERROR(hal_spi_write_data(&lut_buffer[155], 3), TAG, "SPI data 0x04 failed");` |
| 360 | `0x2C` | `44` | `ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x2C), TAG, "SPI cmd 0x2C failed");` |
| 377 | `0x24` | `36` | `ESP_RETURN_ON_ERROR(epd_commit_ram_dma(0x24, s_current_frame), TAG, "Commit RAM 0x24 failed");` |
| 381 | `0x40,` | `64` | `static const uint8_t disp_option[10] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00};` |
| 382 | `0x37` | `55` | `ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x37), TAG, "SPI cmd 0x37 failed");` |
| 383 | `0x37` | `55` | `ESP_RETURN_ON_ERROR(hal_spi_write_data(disp_option, sizeof(disp_option)), TAG, "SPI data 0x37 failed");` |
| 385 | `{0x80};` | `128` | `uint8_t d_border[] = {0x80};` |
| 386 | `0x3C` | `60` | `ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x3C), TAG, "SPI cmd 0x3C failed");` |
| 387 | `0x3C` | `60` | `ESP_RETURN_ON_ERROR(hal_spi_write_data(d_border, sizeof(d_border)), TAG, "SPI data 0x3C failed");` |
| 389 | `{0xCF};` | `207` | `uint8_t d_upd[] = {0xCF};` |
| 390 | `0x22` | `34` | `ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x22), TAG, "SPI cmd 0x22 failed");` |
| 391 | `0x22` | `34` | `ESP_RETURN_ON_ERROR(hal_spi_write_data(d_upd, sizeof(d_upd)), TAG, "SPI data 0x22 failed");` |
| 393 | `0x20` | `32` | `ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x20), TAG, "SPI cmd 0x20 failed");` |
| 398 | `1000LL;` | `1000` | `int64_t t_elapsed_ms = (esp_timer_get_time() - t_start) / 1000LL;` |
| 399 | `~300` | `300` | `ESP_LOGI(TAG, "Partial Refresh completed in %lld ms (Target: ~300 ms)", (long long)t_elapsed_ms);` |
| 435 | `{0x80};` | `128` | `uint8_t t_sel[] = {0x80};` |
| 439 | `{0xB1};` | `177` | `uint8_t t_load[] = {0xB1};` |
| 448 | `0x80)` | `128` | `float temp_frac = (temp_raw[1] & 0x80) ? 0.5f : 0.0f;` |
| 451 | `0xFF` | `255` | `if (glass_temp < -40.0f \|\| glass_temp > 85.0f \|\| temp_raw[0] == 0xFF \|\| temp_raw[0] == 0x00) {` |

### `components\h1os\src\sub_power.c` (66 matches)

| Line | Token | Value | Context |
| :---: | :---: | :---: | :--- |
| 53 | `{4200,` | `4200` | `{4200, 1000},` |
| 53 | `1000},` | `1000` | `{4200, 1000},` |
| 54 | `{4120,` | `4120` | `{4120, 950},` |
| 54 | `950},` | `950` | `{4120, 950},` |
| 55 | `{4040,` | `4040` | `{4040, 880},` |
| 55 | `880},` | `880` | `{4040, 880},` |
| 56 | `{3960,` | `3960` | `{3960, 800},` |
| 56 | `800},` | `800` | `{3960, 800},` |
| 57 | `{3890,` | `3890` | `{3890, 730},` |
| 57 | `730},` | `730` | `{3890, 730},` |
| 58 | `{3820,` | `3820` | `{3820, 600},` |
| 58 | `600},` | `600` | `{3820, 600},` |
| 59 | `{3780,` | `3780` | `{3780, 480},` |
| 59 | `480},` | `480` | `{3780, 480},` |
| 60 | `{3750,` | `3750` | `{3750, 360},` |
| 60 | `360},` | `360` | `{3750, 360},` |
| 61 | `{3720,` | `3720` | `{3720, 250},` |
| 61 | `250},` | `250` | `{3720, 250},` |
| 62 | `{3680,` | `3680` | `{3680, 150},` |
| 62 | `150},` | `150` | `{3680, 150},` |
| 63 | `{3600,` | `3600` | `{3600, 80},` |
| 63 | `80},` | `80` | `{3600, 80},` |
| 64 | `{3450,` | `3450` | `{3450, 30},` |
| 64 | `30},` | `30` | `{3450, 30},` |
| 65 | `{3300,` | `3300` | `{3300, 0}` |
| 73 | `1000;` | `1000` | `return 1000;` |
| 92 | `5U)` | `5` | `return (uint8_t)((sub_power_mv_to_soc_tenths(mv) + 5U) / 10U);` |
| 92 | `10U);` | `10` | `return (uint8_t)((sub_power_mv_to_soc_tenths(mv) + 5U) / 10U);` |
| 184 | `8U;` | `8` | `uint32_t head  = ulp_vbat_ring_head % 8U;` |
| 191 | `3300U)` | `3300` | `if (usb_conn && vbat < 3300U) {` |
| 192 | `4200U;` | `4200` | `vbat = 4200U;` |
| 193 | `4500U)` | `4500` | `} else if (vbat == 0U \|\| vbat > 4500U) {` |
| 194 | `4000U;` | `4000` | `vbat = 4000U;` |
| 207 | `4180U)` | `4180` | `state = (vbat_mv >= 4180U) ? H1OS_BATTERY_CHARGED : H1OS_BATTERY_CHARGING;` |
| 208 | `2U)` | `2` | `} else if (count >= 2U) {` |
| 209 | `7U` | `7` | `uint32_t newest_idx = (head == 0U) ? 7U : (head - 1U);` |
| 211 | `3U)` | `3` | `uint32_t lookback   = (count >= 3U) ? 2U : 1U;` |
| 211 | `2U` | `2` | `uint32_t lookback   = (count >= 3U) ? 2U : 1U;` |
| 212 | `8U` | `8` | `uint32_t prev_idx   = (newest_idx + 8U - lookback) % 8U;` |
| 212 | `8U;` | `8` | `uint32_t prev_idx   = (newest_idx + 8U - lookback) % 8U;` |
| 216 | `15U)` | `15` | `if (v_new >= v_prev + 15U) {` |
| 218 | `4180U` | `4180` | `} else if (v_new >= 4180U && (v_new > v_prev ? (v_new - v_prev) : (v_prev - v_new)) <= 5U) {` |
| 218 | `5U)` | `5` | `} else if (v_new >= 4180U && (v_new > v_prev ? (v_new - v_prev) : (v_prev - v_new)) <= 5U) {` |
| 264 | `10)` | `10` | `if (delta_x10 < 10) {` |
| 299 | `2000,` | `2000` | `adc_cali_raw_to_voltage(s_cali_handle, 2000, &v_2000);` |
| 300 | `3000,` | `3000` | `adc_cali_raw_to_voltage(s_cali_handle, 3000, &v_3000);` |
| 306 | `4096LL)` | `4096` | `int32_t m_scale  = (int32_t)(((int64_t)2 * (v_3000 - v_2000) * 4096LL) / 1000LL);` |
| 306 | `1000LL);` | `1000` | `int32_t m_scale  = (int32_t)(((int64_t)2 * (v_3000 - v_2000) * 4096LL) / 1000LL);` |
| 307 | `2000LL)` | `2000` | `int32_t b_offset = (int32_t)((int64_t)2 * v_2000 - (((int64_t)m_scale * 2000LL) / 4096LL));` |
| 307 | `4096LL));` | `4096` | `int32_t b_offset = (int32_t)((int64_t)2 * v_2000 - (((int64_t)m_scale * 2000LL) / 4096LL));` |
| 343 | `4000;` | `4000` | `ulp_last_vbat_mv    = 4000;` |
| 349 | `1000000ULL);` | `1000000` | `ulp_set_wakeup_period(0, (uint64_t)flow_a_period_sec * 1000000ULL);` |
| 368 | `3)` | `3` | `} else if (ulp_last_wake_cause == 3) {` |
| 413 | `1000ULL);` | `1000` | `st->total_app_run_ms += (uint32_t)(esp_timer_get_time() / 1000ULL);` |
| 479 | `50000U)` | `50000` | `while (rtc_gpio_get_level(HAL_PIN_RTC_INT) == 0 && drain_wait_us < 50000U) {` |
| 481 | `500U;` | `500` | `drain_wait_us += 500U;` |
| 487 | `100000U)` | `100000` | `btn_drain_us < 100000U) {` |
| 489 | `1000U;` | `1000` | `btn_drain_us += 1000U;` |
| 498 | `(4` | `4` | `(unsigned long)REG_READ(RTC_GPIO_PIN0_REG + (4 * 0)),` |
| 499 | `(4` | `4` | `(unsigned long)REG_READ(RTC_GPIO_PIN0_REG + (4 * 5)),` |
| 499 | `5)),` | `5` | `(unsigned long)REG_READ(RTC_GPIO_PIN0_REG + (4 * 5)),` |
| 500 | `(4` | `4` | `(unsigned long)REG_READ(RTC_GPIO_PIN0_REG + (4 * 18)));` |
| 500 | `18)));` | `18` | `(unsigned long)REG_READ(RTC_GPIO_PIN0_REG + (4 * 18)));` |
| 525 | `17)` | `17` | `ESP_LOGW(TAG, "Releasing battery power latch (GPIO 17) - SYSTEM SHUTDOWN");` |
| 543 | `80` | `80` | `int32_t max_freq = (mode == SYS_CLK_MODE_FIXED_MIN) ? 80 : CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ;` |
| 544 | `80;` | `80` | `int32_t min_freq = (mode == SYS_CLK_MODE_FIXED_MAX) ? CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ : 80;` |

### `components\h1os\src\sub_rtc.c` (59 matches)

| Line | Token | Value | Context |
| :---: | :---: | :---: | :--- |
| 24 | `0x02` | `2` | `#define RTC_REG_OFFSET      0x02` |
| 25 | `0x03` | `3` | `#define RTC_REG_RAM_BYTE    0x03` |
| 26 | `0x04` | `4` | `#define RTC_REG_SECONDS     0x04` |
| 27 | `0x05` | `5` | `#define RTC_REG_MINUTES     0x05` |
| 28 | `0x06` | `6` | `#define RTC_REG_HOURS       0x06` |
| 29 | `0x07` | `7` | `#define RTC_REG_DAYS        0x07` |
| 30 | `0x08` | `8` | `#define RTC_REG_WEEKDAYS    0x08` |
| 31 | `0x09` | `9` | `#define RTC_REG_MONTHS      0x09` |
| 32 | `0x0A` | `10` | `#define RTC_REG_YEARS       0x0A` |
| 33 | `0x0B` | `11` | `#define RTC_REG_ALARM_SEC   0x0B` |
| 34 | `0x10` | `16` | `#define RTC_REG_TIMER_VALUE 0x10` |
| 35 | `0x11` | `17` | `#define RTC_REG_TIMER_MODE  0x11` |
| 37 | `5)` | `5` | `#define CTRL1_STOP_MASK      (1 << 5)` |
| 40 | `0x58` | `88` | `#define CTRL1_SW_RESET_CMD    0x58` |
| 42 | `6)` | `6` | `#define CTRL2_AF_MASK  (1 << 6)` |
| 43 | `3)` | `3` | `#define CTRL2_TF_MASK  (1 << 3)` |
| 44 | `7)` | `7` | `#define CTRL2_AIE_MASK (1 << 7)` |
| 45 | `0x07` | `7` | `#define CTRL2_COF_OFF   0x07` |
| 47 | `3)` | `3` | `#define TIMER_CLK_4096_HZ    (0 << 3)` |
| 48 | `3)` | `3` | `#define TIMER_CLK_64_HZ      (1 << 3)` |
| 49 | `(2` | `2` | `#define TIMER_CLK_1_HZ       (2 << 3)` |
| 49 | `3)` | `3` | `#define TIMER_CLK_1_HZ       (2 << 3)` |
| 50 | `(3` | `3` | `#define TIMER_CLK_1_60_HZ    (3 << 3)` |
| 50 | `3)` | `3` | `#define TIMER_CLK_1_60_HZ    (3 << 3)` |
| 51 | `2)` | `2` | `#define TIMER_ENABLE_BIT     (1 << 2)` |
| 64 | `4)` | `4` | `return (uint8_t)(((val >> 4) * 10) + (val & 0x0F));` |
| 64 | `10)` | `10` | `return (uint8_t)(((val >> 4) * 10) + (val & 0x0F));` |
| 64 | `0x0F));` | `15` | `return (uint8_t)(((val >> 4) * 10) + (val & 0x0F));` |
| 76 | `10)` | `10` | `return (uint8_t)(((val / 10) << 4) \| (val % 10));` |
| 76 | `4)` | `4` | `return (uint8_t)(((val / 10) << 4) \| (val % 10));` |
| 76 | `10));` | `10` | `return (uint8_t)(((val / 10) << 4) \| (val % 10));` |
| 170 | `0x80))` | `128` | `if (err == ESP_OK && (sec_reg & 0x80)) {` |
| 196 | `0x7F);` | `127` | `out_time->tm_sec = bcd2dec(data[0] & 0x7F);` |
| 197 | `0x7F);` | `127` | `out_time->tm_min = bcd2dec(data[1] & 0x7F);` |
| 198 | `0x3F);` | `63` | `out_time->tm_hour = bcd2dec(data[2] & 0x3F);` |
| 199 | `0x3F);` | `63` | `out_time->tm_mday = bcd2dec(data[3] & 0x3F);` |
| 200 | `0x07;` | `7` | `out_time->tm_wday = data[4] & 0x07;` |
| 201 | `0x1F)` | `31` | `out_time->tm_mon = bcd2dec(data[5] & 0x1F) - 1;` |
| 202 | `100;` | `100` | `out_time->tm_year = bcd2dec(data[6]) + 100;` |
| 223 | `5);` | `5` | `ctrl1 \|= (1 << 5);` |
| 227 | `0x7F;` | `127` | `data[0] = dec2bcd((uint8_t)time->tm_sec) & 0x7F;` |
| 228 | `0x7F;` | `127` | `data[1] = dec2bcd((uint8_t)time->tm_min) & 0x7F;` |
| 229 | `0x3F;` | `63` | `data[2] = dec2bcd((uint8_t)time->tm_hour) & 0x3F;` |
| 230 | `0x3F;` | `63` | `data[3] = dec2bcd((uint8_t)time->tm_mday) & 0x3F;` |
| 231 | `0x07;` | `7` | `data[4] = (uint8_t)time->tm_wday & 0x07;` |
| 232 | `0x1F;` | `31` | `data[5] = dec2bcd((uint8_t)(time->tm_mon + 1)) & 0x1F;` |
| 233 | `100` | `100` | `data[6] = dec2bcd((uint8_t)(time->tm_year >= 100 ? time->tm_year - 100 : time->tm_year));` |
| 233 | `100` | `100` | `data[6] = dec2bcd((uint8_t)(time->tm_year >= 100 ? time->tm_year - 100 : time->tm_year));` |
| 237 | `5);` | `5` | `ctrl1 &= ~(1 << 5);` |
| 254 | `15300)` | `15300` | `if (seconds == 0 \|\| seconds > 15300) {` |
| 261 | `255)` | `255` | `if (seconds <= 255) {` |
| 266 | `59)` | `59` | `timer_value = (uint8_t)((seconds + 59) / 60);` |
| 266 | `60);` | `60` | `timer_value = (uint8_t)((seconds + 59) / 60);` |
| 292 | `0xFF;` | `255` | `uint8_t check_ctrl2 = 0xFF;` |
| 293 | `3;` | `3` | `for (int32_t retry = 0; retry < 3; retry++) {` |
| 313 | `0x07)` | `7` | `if ((check_mode & 0x07) != 0x07) {` |
| 313 | `0x07)` | `7` | `if ((check_mode & 0x07) != 0x07) {` |
| 370 | `(3` | `3` | `uint8_t clk_src = timer_mode & (3 << 3);` |
| 370 | `3);` | `3` | `uint8_t clk_src = timer_mode & (3 << 3);` |

### `components\h1os\src\sub_sdcard.c` (5 matches)

| Line | Token | Value | Context |
| :---: | :---: | :---: | :--- |
| 76 | `4096,` | `4096` | `BaseType_t res = xTaskCreate(sdcard_mount_worker_task, "sd_mount", 4096, NULL, 2, &handle);` |
| 76 | `2,` | `2` | `BaseType_t res = xTaskCreate(sdcard_mount_worker_task, "sd_mount", 4096, NULL, 2, &handle);` |
| 101 | `5,` | `5` | `.max_files = 5,` |
| 108 | `100;` | `100` | `host.command_timeout_ms = 100;` |
| 158 | `25;` | `25` | `int32_t wait_cycles = 25;` |

### `components\h1os\ulp\main.c` (38 matches)

| Line | Token | Value | Context |
| :---: | :---: | :---: | :--- |
| 26 | `5;` | `5` | `volatile uint32_t overflow_limit  = 5;` |
| 32 | `8601;` | `8601` | `volatile uint32_t cal_scale       = 8601;` |
| 34 | `4000;` | `4000` | `volatile uint32_t last_vbat_mv    = 4000;` |
| 38 | `8` | `8` | `#define ULP_VBAT_RING_SIZE 8` |
| 39 | `{4000,` | `4000` | `volatile uint32_t vbat_ring[ULP_VBAT_RING_SIZE] = {4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000};` |
| 39 | `4000,` | `4000` | `volatile uint32_t vbat_ring[ULP_VBAT_RING_SIZE] = {4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000};` |
| 39 | `4000,` | `4000` | `volatile uint32_t vbat_ring[ULP_VBAT_RING_SIZE] = {4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000};` |
| 39 | `4000,` | `4000` | `volatile uint32_t vbat_ring[ULP_VBAT_RING_SIZE] = {4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000};` |
| 39 | `4000,` | `4000` | `volatile uint32_t vbat_ring[ULP_VBAT_RING_SIZE] = {4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000};` |
| 39 | `4000,` | `4000` | `volatile uint32_t vbat_ring[ULP_VBAT_RING_SIZE] = {4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000};` |
| 39 | `4000,` | `4000` | `volatile uint32_t vbat_ring[ULP_VBAT_RING_SIZE] = {4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000};` |
| 39 | `4000};` | `4000` | `volatile uint32_t vbat_ring[ULP_VBAT_RING_SIZE] = {4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000};` |
| 44 | `50000` | `50000` | `#define RTC_INT_TIMEOUT_US         50000` |
| 45 | `100` | `100` | `#define RTC_INT_POLL_US            100` |
| 47 | `30000` | `30000` | `#define BUTTON_DEBOUNCE_US         30000` |
| 48 | `2500000` | `2500000` | `#define BUTTON_HOLD_US             2500000` |
| 49 | `30` | `30` | `#define BUTTON_TAP_MIN_MS          30` |
| 50 | `2500` | `2500` | `#define BUTTON_TAP_MAX_MS          2500` |
| 51 | `5000` | `5000` | `#define BUTTON_POLL_US             5000` |
| 52 | `50000` | `50000` | `#define BUTTON_RELEASE_TIMEOUT_US  50000` |
| 54 | `50000` | `50000` | `#define PMU_RDY_SPIN_MAX           50000` |
| 55 | `10000` | `10000` | `#define ADC_CONV_SPIN_MAX          10000` |
| 59 | `2` | `2` | `#define ULP_DISPATCH_MAIN_WAKE         2` |
| 60 | `3` | `3` | `#define ULP_DISPATCH_CRITICAL_SHUTDOWN 3` |
| 61 | `4` | `4` | `#define ULP_DISPATCH_BOOTLOADER_JUMP   4` |
| 62 | `5` | `5` | `#define ULP_DISPATCH_POWER_OFF         5` |
| 78 | `12)` | `12` | `int32_t vbat = (int32_t)(((uint32_t)raw * cal_scale) >> 12) + cal_offset;` |
| 163 | `100` | `100` | `if (!usb_connected && (vbat_mv >= 100 && vbat_mv < 3250)) {` |
| 163 | `3250))` | `3250` | `if (!usb_connected && (vbat_mv >= 100 && vbat_mv < 3250)) {` |
| 164 | `6;` | `6` | `last_wake_cause = 6;` |
| 200 | `2;` | `2` | `last_wake_cause = 2;` |
| 201 | `2;` | `2` | `last_wake_btn   = 2;` |
| 209 | `1000U;` | `1000` | `uint32_t hold_ms = elapsed_us / 1000U;` |
| 211 | `2;` | `2` | `last_wake_cause = is_boot ? 1 : 2;` |
| 212 | `2;` | `2` | `last_wake_btn   = is_boot ? 1 : 2;` |
| 228 | `4;` | `4` | `last_wake_cause = 4;` |
| 235 | `3;` | `3` | `last_wake_cause = 3;` |
| 264 | `5;` | `5` | `last_wake_cause = 5;` |
