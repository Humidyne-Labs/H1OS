# H1OS Firmware Literal Integer & Magic Constant Audit Report

> **Audit Target:** `components/` (ESP-IDF Firmware Core & Drivers)  
> **Analysis Methodology:** Space-delimited string tokenization, delimiter stripping, and 3-Tier Risk Degree Classification.

---

## 1. Executive Summary & Degree Taxonomy

| Tier | Classification | Criteria | Risk Level | Total Count | Percentage |
| :---: | :--- | :--- | :---: | :---: | :---: |
| **1st Degree** | Structural / Protocol & Enums | Bitmasks (`& 0xFF`), shifts (`<< 8`), pin mappings (`GPIO 17`), register addresses, state machine cases, state variables (`ulp_last_wake_cause`), and enum definitions | **Acceptable** | 315 | 56.8% |
| **2nd Degree** | Mathematical & Metrology | Sensor transfer functions (`65535`, `17500`), unit scaling (`1000ULL`), battery SoC curve tables (`s_soc_lut`), audio attenuation curves | **Contextual** | 49 | 8.8% |
| **3rd Degree** | Operational Magic Numbers | Timeouts, delays, electrical cutoff thresholds (`3250` mV), task stack floors, RTOS priorities, loop retry bounds | **Actionable** | 191 | 34.4% |
| **TOTAL** | — | Non-trivial integers across `components/` | — | **555** | **100.0%** |

---

## 2. Inventory by Component & Degree

| Component File | 1st Degree (Structural & Enums) | 2nd Degree (Math & Curve Tables) | 3rd Degree (Operational Magic Numbers) | Total Literals |
| :--- | :---: | :---: | :---: | :---: |
| `components\h1os\bootloader_components\h1os_boot_hook\h1os_boot_hook.c` | 5 | 0 | **0** | 5 |
| `components\h1os\include\h1os\h1os_version.h` | 2 | 0 | **0** | 2 |
| `components\h1os\include\h1os\hal_types.h` | 0 | 1 | **0** | 1 |
| `components\h1os\include\h1os\sub_display.h` | 0 | 0 | **1** | 1 |
| `components\h1os\src\h1os_lifecycle.c` | 10 | 2 | **7** | 19 |
| `components\h1os\src\h1os_lvgl.cpp` | 16 | 3 | **7** | 26 |
| `components\h1os\src\h1os_time.c` | 0 | 0 | **3** | 3 |
| `components\h1os\src\hal_flash.c` | 0 | 0 | **2** | 2 |
| `components\h1os\src\hal_i2c.c` | 0 | 0 | **2** | 2 |
| `components\h1os\src\hal_io.c` | 3 | 0 | **17** | 20 |
| `components\h1os\src\hal_spi.c` | 0 | 8 | **7** | 15 |
| `components\h1os\src\orch_display_sync.c` | 0 | 0 | **1** | 1 |
| `components\h1os\src\orch_flow.c` | 5 | 0 | **3** | 8 |
| `components\h1os\src\orch_state.c` | 0 | 1 | **0** | 1 |
| `components\h1os\src\orch_wake_stub.c` | 26 | 4 | **17** | 47 |
| `components\h1os\src\sub_audio.c` | 116 | 4 | **28** | 148 |
| `components\h1os\src\sub_display.cpp` | 77 | 3 | **6** | 86 |
| `components\h1os\src\sub_power.c` | 5 | 13 | **48** | 66 |
| `components\h1os\src\sub_rtc.c` | 48 | 0 | **11** | 59 |
| `components\h1os\src\sub_sdcard.c` | 0 | 0 | **5** | 5 |
| `components\h1os\ulp\main.c` | 2 | 10 | **26** | 38 |

---

## 3. High-Priority 3rd Degree Magic Literals (Actionable Review)

The following table isolates true 3rd degree operational magic numbers (timeouts, stack floors, retry limits, debounce delays, electrical thresholds):

| File | Line | Token | Category | Code Context | Rationale / Recommended Abstraction |
| :--- | :---: | :---: | :--- | :--- | :--- |
| `sub_display.h` | 25 | `8)` | **Magic Integer Constant** | `#define EPD_BUFFER_SIZE ((EPD_WIDTH * EPD_HEIGHT) / 8)` | Literal integer without named macro abstraction. |
| `h1os_lifecycle.c` | 118 | `6000U)` | **Timeout / Delay Duration** | `while (h1os_lvgl_has_pending_tasks() && wait_ms < 6000U) {` | Hardcoded time duration in milliseconds or microseconds. |
| `h1os_lifecycle.c` | 120 | `20U;` | **Timeout / Delay Duration** | `wait_ms += 20U;` | Hardcoded time duration in milliseconds or microseconds. |
| `h1os_lifecycle.c` | 193 | `3250` | **Battery / Voltage Threshold** | `ESP_LOGE(TAG, "[ULP FAULT] Battery critically low: %lu mV (< 3250 mV threshold)!", (unsigned long)ulp_last_vbat_mv);` | Critical electrical or state-of-charge threshold limit. |
| `h1os_lifecycle.c` | 448 | `4096,` | **Stack Size / RTOS Priority** | `BaseType_t res = xTaskCreatePinnedToCore(h1os_session_monitor_task, "h1os_sess", 4096, NULL, 3, (TaskHandle_t *)&s_session_task_handle, 0);` | FreeRTOS task stack size or scheduler priority literal. |
| `h1os_lifecycle.c` | 448 | `3,` | **Stack Size / RTOS Priority** | `BaseType_t res = xTaskCreatePinnedToCore(h1os_session_monitor_task, "h1os_sess", 4096, NULL, 3, (TaskHandle_t *)&s_session_task_handle, 0);` | FreeRTOS task stack size or scheduler priority literal. |
| `h1os_lifecycle.c` | 561 | `30)` | **Battery / Voltage Threshold** | `current_soc_x10 >= st->initial_soc_x10 + 30) {` | Critical electrical or state-of-charge threshold limit. |
| `h1os_lifecycle.c` | 645 | `4;` | **Loop Bound / Retry Limit** | `for (int32_t i = 0; i < 200 && stable_high < 4; i++) {` | Arbitrary loop retry limit or debounce counter. |
| `h1os_lvgl.cpp` | 232 | `(8` | **Magic Integer Constant** | `uint8_t val = (carry << (8 - shift)) \| (*s >> shift);` | Literal integer without named macro abstraction. |
| `h1os_lvgl.cpp` | 288 | `40;` | **Magic Integer Constant** | `uint32_t buffer_lines = 40;` | Literal integer without named macro abstraction. |
| `h1os_lvgl.cpp` | 312 | `2000);` | **Timeout / Delay Duration** | `lv_indev_set_long_press_time(s_lv_keypad_indev, 2000);` | Hardcoded time duration in milliseconds or microseconds. |
| `h1os_lvgl.cpp` | 358 | `5;` | **Magic Integer Constant** | `task_priority = (task_priority > 0) ? task_priority : 5;` | Literal integer without named macro abstraction. |
| `h1os_lvgl.cpp` | 365 | `8192,` | **Magic Integer Constant** | `8192,` | Literal integer without named macro abstraction. |
| `h1os_lvgl.cpp` | 395 | `6000)` | **Timeout / Delay Duration** | `while (s_lvgl_task_handle != NULL && wait_ms < 6000) {` | Hardcoded time duration in milliseconds or microseconds. |
| `h1os_lvgl.cpp` | 397 | `20;` | **Timeout / Delay Duration** | `wait_ms += 20;` | Hardcoded time duration in milliseconds or microseconds. |
| `h1os_time.c` | 34 | `64)` | **Magic Integer Constant** | `if (tz_str == NULL \|\| strlen(tz_str) == 0 \|\| strlen(tz_str) > 64) {` | Literal integer without named macro abstraction. |
| `h1os_time.c` | 73 | `1900,` | **Magic Integer Constant** | `timeinfo.tm_year + 1900,` | Literal integer without named macro abstraction. |
| `h1os_time.c` | 108 | `1900,` | **Magic Integer Constant** | `tm_target.tm_year + 1900,` | Literal integer without named macro abstraction. |
| `hal_flash.c` | 89 | `4095)` | **Magic Integer Constant** | `size_t erase_size = (len + 4095) & ~4095;` | Literal integer without named macro abstraction. |
| `hal_flash.c` | 89 | `~4095;` | **Magic Integer Constant** | `size_t erase_size = (len + 4095) & ~4095;` | Literal integer without named macro abstraction. |
| `hal_i2c.c` | 92 | `7,` | **Magic Integer Constant** | `.glitch_ignore_cnt = 7,` | Literal integer without named macro abstraction. |
| `hal_i2c.c` | 298 | `50);` | **Magic Integer Constant** | `esp_err_t ret = i2c_master_probe(s_bus_handle, dev_addr, 50);` | Literal integer without named macro abstraction. |
| `hal_io.c` | 112 | `5000` | **Magic Integer Constant** | `#define HAL_LEDC_FREQUENCY 5000` | Literal integer without named macro abstraction. |
| `hal_io.c` | 186 | `100)` | **Magic Integer Constant** | `if (brightness_pct > 100) {` | Literal integer without named macro abstraction. |
| `hal_io.c` | 187 | `100;` | **Magic Integer Constant** | `brightness_pct = 100;` | Literal integer without named macro abstraction. |
| `hal_io.c` | 189 | `1023U)` | **Magic Integer Constant** | `uint32_t duty = ((uint32_t)brightness_pct * 1023U) / 100U;` | Literal integer without named macro abstraction. |
| `hal_io.c` | 189 | `100U;` | **Magic Integer Constant** | `uint32_t duty = ((uint32_t)brightness_pct * 1023U) / 100U;` | Literal integer without named macro abstraction. |
| `hal_io.c` | 213 | `100)` | **Magic Integer Constant** | `if (target_pct > 100) {` | Literal integer without named macro abstraction. |
| `hal_io.c` | 214 | `100;` | **Magic Integer Constant** | `target_pct = 100;` | Literal integer without named macro abstraction. |
| `hal_io.c` | 216 | `1023U)` | **Magic Integer Constant** | `uint32_t target_duty = ((uint32_t)target_pct * 1023U) / 100U;` | Literal integer without named macro abstraction. |
| `hal_io.c` | 216 | `100U;` | **Magic Integer Constant** | `uint32_t target_duty = ((uint32_t)target_pct * 1023U) / 100U;` | Literal integer without named macro abstraction. |
| `hal_io.c` | 223 | `2000;` | **Magic Integer Constant** | `static volatile uint32_t s_breath_period_ms = 2000;` | Literal integer without named macro abstraction. |
| `hal_io.c` | 236 | `2U;` | **Magic Integer Constant** | `uint32_t half = s_breath_period_ms / 2U;` | Literal integer without named macro abstraction. |
| `hal_io.c` | 237 | `100U)` | **Magic Integer Constant** | `if (half < 100U) {` | Literal integer without named macro abstraction. |
| `hal_io.c` | 238 | `100U;` | **Magic Integer Constant** | `half = 100U;` | Literal integer without named macro abstraction. |
| `hal_io.c` | 284 | `2000;` | **Magic Integer Constant** | `cycle_period_ms = 2000;` | Literal integer without named macro abstraction. |
| `hal_io.c` | 293 | `2048,` | **Stack Size / RTOS Priority** | `BaseType_t res = xTaskCreate(led_breath_task, "led_breath", 2048, NULL, 1, (TaskHandle_t *)&s_breath_task);` | FreeRTOS task stack size or scheduler priority literal. |
| `hal_io.c` | 313 | `15;` | **Magic Integer Constant** | `int32_t wait_cycles = 15;` | Literal integer without named macro abstraction. |
| `hal_io.c` | 381 | `100` | **Magic Integer Constant** | `return hal_led_set_brightness(on ? 100 : 0);` | Literal integer without named macro abstraction. |
| `hal_spi.c` | 98 | `7,` | **Magic Integer Constant** | `.queue_size = 7,` | Literal integer without named macro abstraction. |
| `hal_spi.c` | 123 | `(20` | **Magic Integer Constant** | `"SPI2 bus initialized with DMA (20 MHz write, 2 MHz half-duplex read) on CS=%d, "` | Literal integer without named macro abstraction. |
| `hal_spi.c` | 123 | `2` | **Magic Integer Constant** | `"SPI2 bus initialized with DMA (20 MHz write, 2 MHz half-duplex read) on CS=%d, "` | Literal integer without named macro abstraction. |
| `hal_spi.c` | 174 | `8;` | **Magic Integer Constant** | `t.length = 8;` | Literal integer without named macro abstraction. |
| `hal_spi.c` | 201 | `8;` | **Magic Integer Constant** | `t.length = len * 8;` | Literal integer without named macro abstraction. |
| `hal_spi.c` | 259 | `8;` | **Magic Integer Constant** | `t_cmd.length = 8;` | Literal integer without named macro abstraction. |
| `hal_spi.c` | 274 | `8;` | **Magic Integer Constant** | `t_read.rxlength = len * 8;` | Literal integer without named macro abstraction. |
| `orch_display_sync.c` | 20 | `6` | **Magic Integer Constant** | `#define CONFIG_H1OS_EPD_PARTIAL_REFRESH_LIMIT 6` | Literal integer without named macro abstraction. |
| `orch_flow.c` | 64 | `10);` | **Magic Integer Constant** | `st->tsens_cal_centi_c = (int16_t)(cal_deci_c * 10);` | Literal integer without named macro abstraction. |
| `orch_flow.c` | 394 | `3;` | **Loop Bound / Retry Limit** | `for (int32_t attempt = 0; attempt < 3; attempt++) {` | Arbitrary loop retry limit or debounce counter. |
| `orch_flow.c` | 402 | `3` | **Loop Bound / Retry Limit** | `ESP_LOGE(TAG, "Failed to arm PCF85063A countdown after 3 attempts: %s", esp_err_to_name(rtc_err));` | Arbitrary loop retry limit or debounce counter. |
| `orch_wake_stub.c` | 35 | `32))` | **Magic Integer Constant** | `#define SDA_BIT_MASK (1UL << (HAL_PIN_I2C_SDA - 32))` | Literal integer without named macro abstraction. |
| `orch_wake_stub.c` | 36 | `32))` | **Magic Integer Constant** | `#define SCL_BIT_MASK (1UL << (HAL_PIN_I2C_SCL - 32))` | Literal integer without named macro abstraction. |
| `orch_wake_stub.c` | 110 | `7;` | **Magic Integer Constant** | `for (int32_t i = 7; i >= 0; i--) {` | Literal integer without named macro abstraction. |
| `orch_wake_stub.c` | 138 | `7;` | **Magic Integer Constant** | `for (int32_t i = 7; i >= 0; i--) {` | Literal integer without named macro abstraction. |
| `orch_wake_stub.c` | 168 | `8;` | **Magic Integer Constant** | `for (uint8_t bit = 8; bit > 0; --bit) {` | Literal integer without named macro abstraction. |
| `orch_wake_stub.c` | 192 | `6);` | **Magic Integer Constant** | `REG_SET_FIELD(SENS_SAR_TSENS_CTRL_REG, SENS_TSENS_CLK_DIV, 6);` | Literal integer without named macro abstraction. |
| `orch_wake_stub.c` | 193 | `3);` | **Magic Integer Constant** | `REG_SET_FIELD(SENS_SAR_TSENS_CTRL2_REG, SENS_TSENS_XPD_FORCE, 3);` | Literal integer without named macro abstraction. |
| `orch_wake_stub.c` | 227 | `3;` | **Loop Bound / Retry Limit** | `for (int32_t attempt = 0; attempt < 3; attempt++) {` | Arbitrary loop retry limit or debounce counter. |
| `orch_wake_stub.c` | 258 | `255)` | **Magic Integer Constant** | `if (seconds <= 255) {` | Literal integer without named macro abstraction. |
| `orch_wake_stub.c` | 263 | `59)` | **Magic Integer Constant** | `timer_val = (uint8_t)((seconds + 59) / 60);` | Literal integer without named macro abstraction. |
| `orch_wake_stub.c` | 263 | `60);` | **Magic Integer Constant** | `timer_val = (uint8_t)((seconds + 59) / 60);` | Literal integer without named macro abstraction. |
| `orch_wake_stub.c` | 290 | `3;` | **Loop Bound / Retry Limit** | `for (int32_t attempt = 0; attempt < 3; attempt++) {` | Arbitrary loop retry limit or debounce counter. |
| `orch_wake_stub.c` | 383 | `2)` | **Magic Integer Constant** | `if (sample_ok && shtc3_crc8(&rx[0], 2) == rx[2] && shtc3_crc8(&rx[3], 2) == rx[5]) {` | Literal integer without named macro abstraction. |
| `orch_wake_stub.c` | 383 | `2)` | **Magic Integer Constant** | `if (sample_ok && shtc3_crc8(&rx[0], 2) == rx[2] && shtc3_crc8(&rx[3], 2) == rx[5]) {` | Literal integer without named macro abstraction. |
| `orch_wake_stub.c` | 441 | `20000;` | **Timeout / Delay Duration** | `uint32_t timeout_us = 20000;` | Hardcoded time duration in milliseconds or microseconds. |
| `orch_wake_stub.c` | 444 | `500)` | **Timeout / Delay Duration** | `if (timeout_us <= 500) {` | Hardcoded time duration in milliseconds or microseconds. |
| `orch_wake_stub.c` | 447 | `500;` | **Timeout / Delay Duration** | `timeout_us -= 500;` | Hardcoded time duration in milliseconds or microseconds. |
| `sub_audio.c` | 255 | `100;` | **Magic Integer Constant** | `pct = 100;` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 354 | `5;` | **Magic Integer Constant** | `const uint32_t step_ms = 5;` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 469 | `4;` | **Magic Integer Constant** | `chan_cfg.dma_desc_num      = 4;` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 530 | `4096,` | **Magic Integer Constant** | `4096,` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 532 | `6,` | **Magic Integer Constant** | `6,` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 590 | `120` | **Timeout / Delay Duration** | `vTaskDelay(pdMS_TO_TICKS(target_enabled ? 120 : 80));` | Hardcoded time duration in milliseconds or microseconds. |
| `sub_audio.c` | 590 | `80));` | **Timeout / Delay Duration** | `vTaskDelay(pdMS_TO_TICKS(target_enabled ? 120 : 80));` | Hardcoded time duration in milliseconds or microseconds. |
| `sub_audio.c` | 638 | `16000;` | **Magic Integer Constant** | `const uint32_t sample_rate   = 16000;` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 640 | `64)` | **Magic Integer Constant** | `const uint32_t ramp_samples  = (total_samples > 64) ? 32 : (total_samples / 4);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 640 | `32` | **Magic Integer Constant** | `const uint32_t ramp_samples  = (total_samples > 64) ? 32 : (total_samples / 4);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 640 | `4);` | **Magic Integer Constant** | `const uint32_t ramp_samples  = (total_samples > 64) ? 32 : (total_samples / 4);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 810 | `70);` | **Magic Integer Constant** | `sub_audio_render_tone_samples(523, 70);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 812 | `70);` | **Magic Integer Constant** | `sub_audio_render_tone_samples(659, 70);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 814 | `70);` | **Magic Integer Constant** | `sub_audio_render_tone_samples(784, 70);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 816 | `150);` | **Magic Integer Constant** | `sub_audio_render_tone_samples(1046, 150);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 820 | `80);` | **Magic Integer Constant** | `sub_audio_render_tone_samples(1046, 80);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 822 | `80);` | **Magic Integer Constant** | `sub_audio_render_tone_samples(784, 80);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 824 | `140);` | **Magic Integer Constant** | `sub_audio_render_tone_samples(659, 140);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 828 | `90);` | **Magic Integer Constant** | `sub_audio_render_tone_samples(784, 90);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 830 | `90);` | **Magic Integer Constant** | `sub_audio_render_tone_samples(659, 90);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 832 | `180);` | **Magic Integer Constant** | `sub_audio_render_tone_samples(523, 180);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 837 | `80);` | **Magic Integer Constant** | `sub_audio_render_tone_samples(1760, 80);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 839 | `80);` | **Magic Integer Constant** | `sub_audio_render_tone_samples(880, 80);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 948 | `500;` | **Timeout / Delay Duration** | `const uint32_t timeout_ms = (wait_ms > 0) ? wait_ms : 500;` | Hardcoded time duration in milliseconds or microseconds. |
| `sub_audio.c` | 1004 | `16000;` | **Magic Integer Constant** | `cmd.params.pcm.sample_rate_hz = 16000;` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 1011 | `50);` | **Magic Integer Constant** | `return sub_audio_send_command(&cmd, false, 50);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 1044 | `10;` | **Magic Integer Constant** | `elapsed += 10;` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 1100 | `100;` | **Magic Integer Constant** | `volume_pct = 100;` | Literal integer without named macro abstraction. |
| `sub_display.cpp` | 75 | `60;` | **Loop Bound / Retry Limit** | `for (int32_t i = 0; i < 60; i++) {` | Arbitrary loop retry limit or debounce counter. |
| `sub_display.cpp` | 164 | `50;` | **Magic Integer Constant** | `static constexpr int16_t SSD1681_TEMP_HALF_DEG_CENTI_C = 50;` | Literal integer without named macro abstraction. |
| `sub_display.cpp` | 182 | `100` | **Magic Integer Constant** | `int16_t glass_cc = (int16_t)temp_int * 100 + ((temp_int >= 0) ? frac_c : -frac_c);` | Literal integer without named macro abstraction. |
| `sub_display.cpp` | 349 | `153),` | **Magic Integer Constant** | `ESP_RETURN_ON_ERROR(hal_spi_write_data(&lut_buffer[0], 153), TAG, "SPI data 0x32 failed");` | Literal integer without named macro abstraction. |
| `sub_display.cpp` | 358 | `3),` | **Magic Integer Constant** | `ESP_RETURN_ON_ERROR(hal_spi_write_data(&lut_buffer[155], 3), TAG, "SPI data 0x04 failed");` | Literal integer without named macro abstraction. |
| `sub_display.cpp` | 399 | `~300` | **Magic Integer Constant** | `ESP_LOGI(TAG, "Partial Refresh completed in %lld ms (Target: ~300 ms)", (long long)t_elapsed_ms);` | Literal integer without named macro abstraction. |
| `sub_power.c` | 54 | `{4120,` | **Magic Integer Constant** | `{4120, 950},` | Literal integer without named macro abstraction. |
| `sub_power.c` | 54 | `950},` | **Magic Integer Constant** | `{4120, 950},` | Literal integer without named macro abstraction. |
| `sub_power.c` | 55 | `{4040,` | **Magic Integer Constant** | `{4040, 880},` | Literal integer without named macro abstraction. |
| `sub_power.c` | 55 | `880},` | **Magic Integer Constant** | `{4040, 880},` | Literal integer without named macro abstraction. |
| `sub_power.c` | 56 | `{3960,` | **Magic Integer Constant** | `{3960, 800},` | Literal integer without named macro abstraction. |
| `sub_power.c` | 56 | `800},` | **Magic Integer Constant** | `{3960, 800},` | Literal integer without named macro abstraction. |
| `sub_power.c` | 57 | `{3890,` | **Magic Integer Constant** | `{3890, 730},` | Literal integer without named macro abstraction. |
| `sub_power.c` | 57 | `730},` | **Magic Integer Constant** | `{3890, 730},` | Literal integer without named macro abstraction. |
| `sub_power.c` | 58 | `{3820,` | **Magic Integer Constant** | `{3820, 600},` | Literal integer without named macro abstraction. |
| `sub_power.c` | 58 | `600},` | **Magic Integer Constant** | `{3820, 600},` | Literal integer without named macro abstraction. |
| `sub_power.c` | 59 | `{3780,` | **Magic Integer Constant** | `{3780, 480},` | Literal integer without named macro abstraction. |
| `sub_power.c` | 59 | `480},` | **Magic Integer Constant** | `{3780, 480},` | Literal integer without named macro abstraction. |
| `sub_power.c` | 60 | `{3750,` | **Magic Integer Constant** | `{3750, 360},` | Literal integer without named macro abstraction. |
| `sub_power.c` | 60 | `360},` | **Magic Integer Constant** | `{3750, 360},` | Literal integer without named macro abstraction. |
| `sub_power.c` | 61 | `{3720,` | **Magic Integer Constant** | `{3720, 250},` | Literal integer without named macro abstraction. |
| `sub_power.c` | 61 | `250},` | **Magic Integer Constant** | `{3720, 250},` | Literal integer without named macro abstraction. |
| `sub_power.c` | 62 | `{3680,` | **Magic Integer Constant** | `{3680, 150},` | Literal integer without named macro abstraction. |
| `sub_power.c` | 62 | `150},` | **Magic Integer Constant** | `{3680, 150},` | Literal integer without named macro abstraction. |
| `sub_power.c` | 64 | `{3450,` | **Magic Integer Constant** | `{3450, 30},` | Literal integer without named macro abstraction. |
| `sub_power.c` | 64 | `30},` | **Magic Integer Constant** | `{3450, 30},` | Literal integer without named macro abstraction. |
| `sub_power.c` | 92 | `5U)` | **Battery / Voltage Threshold** | `return (uint8_t)((sub_power_mv_to_soc_tenths(mv) + 5U) / 10U);` | Critical electrical or state-of-charge threshold limit. |
| `sub_power.c` | 92 | `10U);` | **Battery / Voltage Threshold** | `return (uint8_t)((sub_power_mv_to_soc_tenths(mv) + 5U) / 10U);` | Critical electrical or state-of-charge threshold limit. |
| `sub_power.c` | 184 | `8U;` | **Battery / Voltage Threshold** | `uint32_t head  = ulp_vbat_ring_head % 8U;` | Critical electrical or state-of-charge threshold limit. |
| `sub_power.c` | 191 | `3300U)` | **Battery / Voltage Threshold** | `if (usb_conn && vbat < 3300U) {` | Critical electrical or state-of-charge threshold limit. |
| `sub_power.c` | 192 | `4200U;` | **Battery / Voltage Threshold** | `vbat = 4200U;` | Critical electrical or state-of-charge threshold limit. |
| `sub_power.c` | 194 | `4000U;` | **Battery / Voltage Threshold** | `vbat = 4000U;` | Critical electrical or state-of-charge threshold limit. |
| `sub_power.c` | 207 | `4180U)` | **Battery / Voltage Threshold** | `state = (vbat_mv >= 4180U) ? H1OS_BATTERY_CHARGED : H1OS_BATTERY_CHARGING;` | Critical electrical or state-of-charge threshold limit. |
| `sub_power.c` | 208 | `2U)` | **Magic Integer Constant** | `} else if (count >= 2U) {` | Literal integer without named macro abstraction. |
| `sub_power.c` | 209 | `7U` | **Magic Integer Constant** | `uint32_t newest_idx = (head == 0U) ? 7U : (head - 1U);` | Literal integer without named macro abstraction. |
| `sub_power.c` | 211 | `3U)` | **Magic Integer Constant** | `uint32_t lookback   = (count >= 3U) ? 2U : 1U;` | Literal integer without named macro abstraction. |
| `sub_power.c` | 211 | `2U` | **Magic Integer Constant** | `uint32_t lookback   = (count >= 3U) ? 2U : 1U;` | Literal integer without named macro abstraction. |
| `sub_power.c` | 212 | `8U` | **Magic Integer Constant** | `uint32_t prev_idx   = (newest_idx + 8U - lookback) % 8U;` | Literal integer without named macro abstraction. |
| `sub_power.c` | 212 | `8U;` | **Magic Integer Constant** | `uint32_t prev_idx   = (newest_idx + 8U - lookback) % 8U;` | Literal integer without named macro abstraction. |
| `sub_power.c` | 216 | `15U)` | **Magic Integer Constant** | `if (v_new >= v_prev + 15U) {` | Literal integer without named macro abstraction. |
| `sub_power.c` | 218 | `5U)` | **Magic Integer Constant** | `} else if (v_new >= 4180U && (v_new > v_prev ? (v_new - v_prev) : (v_prev - v_new)) <= 5U) {` | Literal integer without named macro abstraction. |
| `sub_power.c` | 264 | `10)` | **Magic Integer Constant** | `if (delta_x10 < 10) {` | Literal integer without named macro abstraction. |
| `sub_power.c` | 299 | `2000,` | **Magic Integer Constant** | `adc_cali_raw_to_voltage(s_cali_handle, 2000, &v_2000);` | Literal integer without named macro abstraction. |
| `sub_power.c` | 300 | `3000,` | **Magic Integer Constant** | `adc_cali_raw_to_voltage(s_cali_handle, 3000, &v_3000);` | Literal integer without named macro abstraction. |
| `sub_power.c` | 307 | `2000LL)` | **Magic Integer Constant** | `int32_t b_offset = (int32_t)((int64_t)2 * v_2000 - (((int64_t)m_scale * 2000LL) / 4096LL));` | Literal integer without named macro abstraction. |
| `sub_power.c` | 307 | `4096LL));` | **Magic Integer Constant** | `int32_t b_offset = (int32_t)((int64_t)2 * v_2000 - (((int64_t)m_scale * 2000LL) / 4096LL));` | Literal integer without named macro abstraction. |
| `sub_power.c` | 343 | `4000;` | **Battery / Voltage Threshold** | `ulp_last_vbat_mv    = 4000;` | Critical electrical or state-of-charge threshold limit. |
| `sub_power.c` | 479 | `50000U)` | **Magic Integer Constant** | `while (rtc_gpio_get_level(HAL_PIN_RTC_INT) == 0 && drain_wait_us < 50000U) {` | Literal integer without named macro abstraction. |
| `sub_power.c` | 481 | `500U;` | **Magic Integer Constant** | `drain_wait_us += 500U;` | Literal integer without named macro abstraction. |
| `sub_power.c` | 498 | `(4` | **Magic Integer Constant** | `(unsigned long)REG_READ(RTC_GPIO_PIN0_REG + (4 * 0)),` | Literal integer without named macro abstraction. |
| `sub_power.c` | 499 | `(4` | **Magic Integer Constant** | `(unsigned long)REG_READ(RTC_GPIO_PIN0_REG + (4 * 5)),` | Literal integer without named macro abstraction. |
| `sub_power.c` | 499 | `5)),` | **Magic Integer Constant** | `(unsigned long)REG_READ(RTC_GPIO_PIN0_REG + (4 * 5)),` | Literal integer without named macro abstraction. |
| `sub_power.c` | 500 | `(4` | **Magic Integer Constant** | `(unsigned long)REG_READ(RTC_GPIO_PIN0_REG + (4 * 18)));` | Literal integer without named macro abstraction. |
| `sub_power.c` | 500 | `18)));` | **Magic Integer Constant** | `(unsigned long)REG_READ(RTC_GPIO_PIN0_REG + (4 * 18)));` | Literal integer without named macro abstraction. |
| `sub_rtc.c` | 64 | `10)` | **Magic Integer Constant** | `return (uint8_t)(((val >> 4) * 10) + (val & 0x0F));` | Literal integer without named macro abstraction. |
| `sub_rtc.c` | 76 | `10)` | **Magic Integer Constant** | `return (uint8_t)(((val / 10) << 4) \| (val % 10));` | Literal integer without named macro abstraction. |
| `sub_rtc.c` | 76 | `10));` | **Magic Integer Constant** | `return (uint8_t)(((val / 10) << 4) \| (val % 10));` | Literal integer without named macro abstraction. |
| `sub_rtc.c` | 202 | `100;` | **Magic Integer Constant** | `out_time->tm_year = bcd2dec(data[6]) + 100;` | Literal integer without named macro abstraction. |
| `sub_rtc.c` | 233 | `100` | **Magic Integer Constant** | `data[6] = dec2bcd((uint8_t)(time->tm_year >= 100 ? time->tm_year - 100 : time->tm_year));` | Literal integer without named macro abstraction. |
| `sub_rtc.c` | 233 | `100` | **Magic Integer Constant** | `data[6] = dec2bcd((uint8_t)(time->tm_year >= 100 ? time->tm_year - 100 : time->tm_year));` | Literal integer without named macro abstraction. |
| `sub_rtc.c` | 254 | `15300)` | **Magic Integer Constant** | `if (seconds == 0 \|\| seconds > 15300) {` | Literal integer without named macro abstraction. |
| `sub_rtc.c` | 261 | `255)` | **Magic Integer Constant** | `if (seconds <= 255) {` | Literal integer without named macro abstraction. |
| `sub_rtc.c` | 266 | `59)` | **Magic Integer Constant** | `timer_value = (uint8_t)((seconds + 59) / 60);` | Literal integer without named macro abstraction. |
| `sub_rtc.c` | 266 | `60);` | **Magic Integer Constant** | `timer_value = (uint8_t)((seconds + 59) / 60);` | Literal integer without named macro abstraction. |
| `sub_rtc.c` | 293 | `3;` | **Loop Bound / Retry Limit** | `for (int32_t retry = 0; retry < 3; retry++) {` | Arbitrary loop retry limit or debounce counter. |
| `sub_sdcard.c` | 76 | `4096,` | **Stack Size / RTOS Priority** | `BaseType_t res = xTaskCreate(sdcard_mount_worker_task, "sd_mount", 4096, NULL, 2, &handle);` | FreeRTOS task stack size or scheduler priority literal. |
| `sub_sdcard.c` | 76 | `2,` | **Stack Size / RTOS Priority** | `BaseType_t res = xTaskCreate(sdcard_mount_worker_task, "sd_mount", 4096, NULL, 2, &handle);` | FreeRTOS task stack size or scheduler priority literal. |
| `sub_sdcard.c` | 101 | `5,` | **Magic Integer Constant** | `.max_files = 5,` | Literal integer without named macro abstraction. |
| `sub_sdcard.c` | 108 | `100;` | **Timeout / Delay Duration** | `host.command_timeout_ms = 100;` | Hardcoded time duration in milliseconds or microseconds. |
| `sub_sdcard.c` | 158 | `25;` | **Magic Integer Constant** | `int32_t wait_cycles = 25;` | Literal integer without named macro abstraction. |
| `main.c` | 26 | `5;` | **Magic Integer Constant** | `volatile uint32_t overflow_limit  = 5;` | Literal integer without named macro abstraction. |
| `main.c` | 32 | `8601;` | **Magic Integer Constant** | `volatile uint32_t cal_scale       = 8601;` | Literal integer without named macro abstraction. |
| `main.c` | 34 | `4000;` | **Battery / Voltage Threshold** | `volatile uint32_t last_vbat_mv    = 4000;` | Critical electrical or state-of-charge threshold limit. |
| `main.c` | 38 | `8` | **Magic Integer Constant** | `#define ULP_VBAT_RING_SIZE 8` | Literal integer without named macro abstraction. |
| `main.c` | 44 | `50000` | **Magic Integer Constant** | `#define RTC_INT_TIMEOUT_US         50000` | Literal integer without named macro abstraction. |
| `main.c` | 45 | `100` | **Magic Integer Constant** | `#define RTC_INT_POLL_US            100` | Literal integer without named macro abstraction. |
| `main.c` | 47 | `30000` | **Magic Integer Constant** | `#define BUTTON_DEBOUNCE_US         30000` | Literal integer without named macro abstraction. |
| `main.c` | 48 | `2500000` | **Magic Integer Constant** | `#define BUTTON_HOLD_US             2500000` | Literal integer without named macro abstraction. |
| `main.c` | 49 | `30` | **Magic Integer Constant** | `#define BUTTON_TAP_MIN_MS          30` | Literal integer without named macro abstraction. |
| `main.c` | 50 | `2500` | **Magic Integer Constant** | `#define BUTTON_TAP_MAX_MS          2500` | Literal integer without named macro abstraction. |
| `main.c` | 51 | `5000` | **Magic Integer Constant** | `#define BUTTON_POLL_US             5000` | Literal integer without named macro abstraction. |
| `main.c` | 52 | `50000` | **Magic Integer Constant** | `#define BUTTON_RELEASE_TIMEOUT_US  50000` | Literal integer without named macro abstraction. |
| `main.c` | 54 | `50000` | **Magic Integer Constant** | `#define PMU_RDY_SPIN_MAX           50000` | Literal integer without named macro abstraction. |
| `main.c` | 59 | `2` | **Magic Integer Constant** | `#define ULP_DISPATCH_MAIN_WAKE         2` | Literal integer without named macro abstraction. |
| `main.c` | 60 | `3` | **Magic Integer Constant** | `#define ULP_DISPATCH_CRITICAL_SHUTDOWN 3` | Literal integer without named macro abstraction. |
| `main.c` | 61 | `4` | **Magic Integer Constant** | `#define ULP_DISPATCH_BOOTLOADER_JUMP   4` | Literal integer without named macro abstraction. |
| `main.c` | 62 | `5` | **Magic Integer Constant** | `#define ULP_DISPATCH_POWER_OFF         5` | Literal integer without named macro abstraction. |
| `main.c` | 163 | `3250))` | **Battery / Voltage Threshold** | `if (!usb_connected && (vbat_mv >= 100 && vbat_mv < 3250)) {` | Critical electrical or state-of-charge threshold limit. |
| `main.c` | 164 | `6;` | **Magic Integer Constant** | `last_wake_cause = 6;` | Literal integer without named macro abstraction. |
| `main.c` | 200 | `2;` | **Magic Integer Constant** | `last_wake_cause = 2;` | Literal integer without named macro abstraction. |
| `main.c` | 201 | `2;` | **Magic Integer Constant** | `last_wake_btn   = 2;` | Literal integer without named macro abstraction. |
| `main.c` | 211 | `2;` | **Magic Integer Constant** | `last_wake_cause = is_boot ? 1 : 2;` | Literal integer without named macro abstraction. |
| `main.c` | 212 | `2;` | **Magic Integer Constant** | `last_wake_btn   = is_boot ? 1 : 2;` | Literal integer without named macro abstraction. |
| `main.c` | 228 | `4;` | **Magic Integer Constant** | `last_wake_cause = 4;` | Literal integer without named macro abstraction. |
| `main.c` | 235 | `3;` | **Magic Integer Constant** | `last_wake_cause = 3;` | Literal integer without named macro abstraction. |
| `main.c` | 264 | `5;` | **Magic Integer Constant** | `last_wake_cause = 5;` | Literal integer without named macro abstraction. |
