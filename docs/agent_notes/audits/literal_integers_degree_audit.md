# H1OS Firmware Literal Integer & Magic Constant Audit Report

> **Audit Target:** `components/` (ESP-IDF Firmware Core & Drivers)  
> **Analysis Methodology:** Space-delimited string tokenization, delimiter stripping, and 3-Tier Risk Degree Classification.

---

## 1. Executive Summary & Degree Taxonomy

| Tier | Classification | Criteria | Risk Level | Total Count | Percentage |
| :---: | :--- | :--- | :---: | :---: | :---: |
| **1st Degree** | Structural / Protocol & Enums | Bitmasks (`& 0xFF`), shifts (`<< 8`), pin mappings (`GPIO 17`), register addresses, state machine cases, state variables (`ulp_last_wake_cause`), and enum definitions | **Acceptable** | 335 | 65.2% |
| **2nd Degree** | Mathematical & Metrology | Sensor transfer functions (`65535`, `17500`), unit scaling (`1000ULL`), battery SoC curve tables (`s_soc_lut`), audio attenuation curves | **Contextual** | 57 | 11.1% |
| **3rd Degree** | Operational Magic Numbers | Timeouts, delays, electrical cutoff thresholds (`3250` mV), task stack floors, RTOS priorities, loop retry bounds | **Actionable** | 122 | 23.7% |
| **TOTAL** | — | Non-trivial integers across `components/` | — | **514** | **100.0%** |

---

## 2. Inventory by Component & Degree

| Component File | 1st Degree (Structural & Enums) | 2nd Degree (Math & Curve Tables) | 3rd Degree (Operational Magic Numbers) | Total Literals |
| :--- | :---: | :---: | :---: | :---: |
| `components\h1os\bootloader_components\h1os_boot_hook\h1os_boot_hook.c` | 5 | 0 | **0** | 5 |
| `components\h1os\include\h1os\h1os_version.h` | 2 | 0 | **0** | 2 |
| `components\h1os\include\h1os\hal_types.h` | 1 | 0 | **0** | 1 |
| `components\h1os\include\h1os\sub_display.h` | 1 | 0 | **0** | 1 |
| `components\h1os\src\h1os_lifecycle.c` | 9 | 2 | **0** | 11 |
| `components\h1os\src\h1os_lvgl.cpp` | 17 | 2 | **1** | 20 |
| `components\h1os\src\h1os_time.c` | 0 | 0 | **3** | 3 |
| `components\h1os\src\hal_flash.c` | 0 | 0 | **2** | 2 |
| `components\h1os\src\hal_i2c.c` | 0 | 0 | **2** | 2 |
| `components\h1os\src\hal_io.c` | 4 | 0 | **13** | 17 |
| `components\h1os\src\hal_spi.c` | 0 | 8 | **7** | 15 |
| `components\h1os\src\orch_display_sync.c` | 1 | 0 | **0** | 1 |
| `components\h1os\src\orch_flow.c` | 5 | 0 | **1** | 6 |
| `components\h1os\src\orch_state.c` | 0 | 1 | **0** | 1 |
| `components\h1os\src\orch_wake_stub.c` | 28 | 4 | **12** | 44 |
| `components\h1os\src\sub_audio.c` | 116 | 4 | **23** | 143 |
| `components\h1os\src\sub_display.cpp` | 77 | 3 | **5** | 85 |
| `components\h1os\src\sub_power.c` | 4 | 32 | **21** | 57 |
| `components\h1os\src\sub_rtc.c` | 48 | 0 | **11** | 59 |
| `components\h1os\src\sub_sdcard.c` | 0 | 0 | **1** | 1 |
| `components\h1os\ulp\main.c` | 17 | 1 | **20** | 38 |

---

## 3. High-Priority 3rd Degree Magic Literals (Actionable Review)

The following table isolates true 3rd degree operational magic numbers (timeouts, stack floors, retry limits, debounce delays, electrical thresholds):

| File | Line | Token | Category | Code Context | Rationale / Recommended Abstraction |
| :--- | :---: | :---: | :--- | :--- | :--- |
| `h1os_lvgl.cpp` | 239 | `(8` | **Magic Integer Constant** | `uint8_t val = (carry << (8 - shift)) \| (*s >> shift);` | Literal integer without named macro abstraction. |
| `h1os_time.c` | 34 | `64)` | **Magic Integer Constant** | `if (tz_str == NULL \|\| strlen(tz_str) == 0 \|\| strlen(tz_str) > 64) {` | Literal integer without named macro abstraction. |
| `h1os_time.c` | 73 | `1900,` | **Magic Integer Constant** | `timeinfo.tm_year + 1900,` | Literal integer without named macro abstraction. |
| `h1os_time.c` | 108 | `1900,` | **Magic Integer Constant** | `tm_target.tm_year + 1900,` | Literal integer without named macro abstraction. |
| `hal_flash.c` | 89 | `4095)` | **Magic Integer Constant** | `size_t erase_size = (len + 4095) & ~4095;` | Literal integer without named macro abstraction. |
| `hal_flash.c` | 89 | `~4095;` | **Magic Integer Constant** | `size_t erase_size = (len + 4095) & ~4095;` | Literal integer without named macro abstraction. |
| `hal_i2c.c` | 92 | `7,` | **Magic Integer Constant** | `.glitch_ignore_cnt = 7,` | Literal integer without named macro abstraction. |
| `hal_i2c.c` | 298 | `50);` | **Magic Integer Constant** | `esp_err_t ret = i2c_master_probe(s_bus_handle, dev_addr, 50);` | Literal integer without named macro abstraction. |
| `hal_io.c` | 190 | `100)` | **Magic Integer Constant** | `if (brightness_pct > 100) {` | Literal integer without named macro abstraction. |
| `hal_io.c` | 191 | `100;` | **Magic Integer Constant** | `brightness_pct = 100;` | Literal integer without named macro abstraction. |
| `hal_io.c` | 193 | `1023U)` | **Magic Integer Constant** | `uint32_t duty = ((uint32_t)brightness_pct * 1023U) / 100U;` | Literal integer without named macro abstraction. |
| `hal_io.c` | 193 | `100U;` | **Magic Integer Constant** | `uint32_t duty = ((uint32_t)brightness_pct * 1023U) / 100U;` | Literal integer without named macro abstraction. |
| `hal_io.c` | 217 | `100)` | **Magic Integer Constant** | `if (target_pct > 100) {` | Literal integer without named macro abstraction. |
| `hal_io.c` | 218 | `100;` | **Magic Integer Constant** | `target_pct = 100;` | Literal integer without named macro abstraction. |
| `hal_io.c` | 220 | `1023U)` | **Magic Integer Constant** | `uint32_t target_duty = ((uint32_t)target_pct * 1023U) / 100U;` | Literal integer without named macro abstraction. |
| `hal_io.c` | 220 | `100U;` | **Magic Integer Constant** | `uint32_t target_duty = ((uint32_t)target_pct * 1023U) / 100U;` | Literal integer without named macro abstraction. |
| `hal_io.c` | 240 | `2U;` | **Magic Integer Constant** | `uint32_t half = s_breath_period_ms / 2U;` | Literal integer without named macro abstraction. |
| `hal_io.c` | 241 | `100U)` | **Magic Integer Constant** | `if (half < 100U) {` | Literal integer without named macro abstraction. |
| `hal_io.c` | 242 | `100U;` | **Magic Integer Constant** | `half = 100U;` | Literal integer without named macro abstraction. |
| `hal_io.c` | 317 | `15;` | **Magic Integer Constant** | `int32_t wait_cycles = 15;` | Literal integer without named macro abstraction. |
| `hal_io.c` | 385 | `100` | **Magic Integer Constant** | `return hal_led_set_brightness(on ? 100 : 0);` | Literal integer without named macro abstraction. |
| `hal_spi.c` | 98 | `7,` | **Magic Integer Constant** | `.queue_size = 7,` | Literal integer without named macro abstraction. |
| `hal_spi.c` | 123 | `(20` | **Magic Integer Constant** | `"SPI2 bus initialized with DMA (20 MHz write, 2 MHz half-duplex read) on CS=%d, "` | Literal integer without named macro abstraction. |
| `hal_spi.c` | 123 | `2` | **Magic Integer Constant** | `"SPI2 bus initialized with DMA (20 MHz write, 2 MHz half-duplex read) on CS=%d, "` | Literal integer without named macro abstraction. |
| `hal_spi.c` | 174 | `8;` | **Magic Integer Constant** | `t.length = 8;` | Literal integer without named macro abstraction. |
| `hal_spi.c` | 201 | `8;` | **Magic Integer Constant** | `t.length = len * 8;` | Literal integer without named macro abstraction. |
| `hal_spi.c` | 259 | `8;` | **Magic Integer Constant** | `t_cmd.length = 8;` | Literal integer without named macro abstraction. |
| `hal_spi.c` | 274 | `8;` | **Magic Integer Constant** | `t_read.rxlength = len * 8;` | Literal integer without named macro abstraction. |
| `orch_flow.c` | 65 | `10);` | **Magic Integer Constant** | `st->tsens_cal_centi_c = (int16_t)(cal_deci_c * 10);` | Literal integer without named macro abstraction. |
| `orch_wake_stub.c` | 112 | `7;` | **Magic Integer Constant** | `for (int32_t i = 7; i >= 0; i--) {` | Literal integer without named macro abstraction. |
| `orch_wake_stub.c` | 140 | `7;` | **Magic Integer Constant** | `for (int32_t i = 7; i >= 0; i--) {` | Literal integer without named macro abstraction. |
| `orch_wake_stub.c` | 170 | `8;` | **Magic Integer Constant** | `for (uint8_t bit = 8; bit > 0; --bit) {` | Literal integer without named macro abstraction. |
| `orch_wake_stub.c` | 194 | `6);` | **Magic Integer Constant** | `REG_SET_FIELD(SENS_SAR_TSENS_CTRL_REG, SENS_TSENS_CLK_DIV, 6);` | Literal integer without named macro abstraction. |
| `orch_wake_stub.c` | 195 | `3);` | **Magic Integer Constant** | `REG_SET_FIELD(SENS_SAR_TSENS_CTRL2_REG, SENS_TSENS_XPD_FORCE, 3);` | Literal integer without named macro abstraction. |
| `orch_wake_stub.c` | 229 | `3;` | **Loop Bound / Retry Limit** | `for (int32_t attempt = 0; attempt < 3; attempt++) {` | Arbitrary loop retry limit or debounce counter. |
| `orch_wake_stub.c` | 260 | `255)` | **Magic Integer Constant** | `if (seconds <= 255) {` | Literal integer without named macro abstraction. |
| `orch_wake_stub.c` | 265 | `59)` | **Magic Integer Constant** | `timer_val = (uint8_t)((seconds + 59) / 60);` | Literal integer without named macro abstraction. |
| `orch_wake_stub.c` | 265 | `60);` | **Magic Integer Constant** | `timer_val = (uint8_t)((seconds + 59) / 60);` | Literal integer without named macro abstraction. |
| `orch_wake_stub.c` | 292 | `3;` | **Loop Bound / Retry Limit** | `for (int32_t attempt = 0; attempt < 3; attempt++) {` | Arbitrary loop retry limit or debounce counter. |
| `orch_wake_stub.c` | 385 | `2)` | **Magic Integer Constant** | `if (sample_ok && shtc3_crc8(&rx[0], 2) == rx[2] && shtc3_crc8(&rx[3], 2) == rx[5]) {` | Literal integer without named macro abstraction. |
| `orch_wake_stub.c` | 385 | `2)` | **Magic Integer Constant** | `if (sample_ok && shtc3_crc8(&rx[0], 2) == rx[2] && shtc3_crc8(&rx[3], 2) == rx[5]) {` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 261 | `100;` | **Magic Integer Constant** | `pct = 100;` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 360 | `5;` | **Magic Integer Constant** | `const uint32_t step_ms = 5;` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 475 | `4;` | **Magic Integer Constant** | `chan_cfg.dma_desc_num      = 4;` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 644 | `16000;` | **Magic Integer Constant** | `const uint32_t sample_rate   = 16000;` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 646 | `64)` | **Magic Integer Constant** | `const uint32_t ramp_samples  = (total_samples > 64) ? 32 : (total_samples / 4);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 646 | `32` | **Magic Integer Constant** | `const uint32_t ramp_samples  = (total_samples > 64) ? 32 : (total_samples / 4);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 646 | `4);` | **Magic Integer Constant** | `const uint32_t ramp_samples  = (total_samples > 64) ? 32 : (total_samples / 4);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 816 | `70);` | **Magic Integer Constant** | `sub_audio_render_tone_samples(523, 70);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 818 | `70);` | **Magic Integer Constant** | `sub_audio_render_tone_samples(659, 70);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 820 | `70);` | **Magic Integer Constant** | `sub_audio_render_tone_samples(784, 70);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 822 | `150);` | **Magic Integer Constant** | `sub_audio_render_tone_samples(1046, 150);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 826 | `80);` | **Magic Integer Constant** | `sub_audio_render_tone_samples(1046, 80);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 828 | `80);` | **Magic Integer Constant** | `sub_audio_render_tone_samples(784, 80);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 830 | `140);` | **Magic Integer Constant** | `sub_audio_render_tone_samples(659, 140);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 834 | `90);` | **Magic Integer Constant** | `sub_audio_render_tone_samples(784, 90);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 836 | `90);` | **Magic Integer Constant** | `sub_audio_render_tone_samples(659, 90);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 838 | `180);` | **Magic Integer Constant** | `sub_audio_render_tone_samples(523, 180);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 843 | `80);` | **Magic Integer Constant** | `sub_audio_render_tone_samples(1760, 80);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 845 | `80);` | **Magic Integer Constant** | `sub_audio_render_tone_samples(880, 80);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 1010 | `16000;` | **Magic Integer Constant** | `cmd.params.pcm.sample_rate_hz = 16000;` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 1017 | `50);` | **Magic Integer Constant** | `return sub_audio_send_command(&cmd, false, 50);` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 1050 | `10;` | **Magic Integer Constant** | `elapsed += 10;` | Literal integer without named macro abstraction. |
| `sub_audio.c` | 1106 | `100;` | **Magic Integer Constant** | `volume_pct = 100;` | Literal integer without named macro abstraction. |
| `sub_display.cpp` | 166 | `50;` | **Magic Integer Constant** | `static constexpr int16_t SSD1681_TEMP_HALF_DEG_CENTI_C = 50;` | Literal integer without named macro abstraction. |
| `sub_display.cpp` | 184 | `100` | **Magic Integer Constant** | `int16_t glass_cc = (int16_t)temp_int * 100 + ((temp_int >= 0) ? frac_c : -frac_c);` | Literal integer without named macro abstraction. |
| `sub_display.cpp` | 351 | `153),` | **Magic Integer Constant** | `ESP_RETURN_ON_ERROR(hal_spi_write_data(&lut_buffer[0], 153), TAG, "SPI data 0x32 failed");` | Literal integer without named macro abstraction. |
| `sub_display.cpp` | 360 | `3),` | **Magic Integer Constant** | `ESP_RETURN_ON_ERROR(hal_spi_write_data(&lut_buffer[155], 3), TAG, "SPI data 0x04 failed");` | Literal integer without named macro abstraction. |
| `sub_display.cpp` | 401 | `~300` | **Magic Integer Constant** | `ESP_LOGI(TAG, "Partial Refresh completed in %lld ms (Target: ~300 ms)", (long long)t_elapsed_ms);` | Literal integer without named macro abstraction. |
| `sub_power.c` | 101 | `5U)` | **Battery / Voltage Threshold** | `return (uint8_t)((sub_power_mv_to_soc_tenths(mv) + 5U) / 10U);` | Critical electrical or state-of-charge threshold limit. |
| `sub_power.c` | 101 | `10U);` | **Battery / Voltage Threshold** | `return (uint8_t)((sub_power_mv_to_soc_tenths(mv) + 5U) / 10U);` | Critical electrical or state-of-charge threshold limit. |
| `sub_power.c` | 193 | `8U;` | **Battery / Voltage Threshold** | `uint32_t head  = ulp_vbat_ring_head % 8U;` | Critical electrical or state-of-charge threshold limit. |
| `sub_power.c` | 217 | `2U)` | **Magic Integer Constant** | `} else if (count >= 2U) {` | Literal integer without named macro abstraction. |
| `sub_power.c` | 218 | `7U` | **Magic Integer Constant** | `uint32_t newest_idx = (head == 0U) ? 7U : (head - 1U);` | Literal integer without named macro abstraction. |
| `sub_power.c` | 220 | `3U)` | **Magic Integer Constant** | `uint32_t lookback   = (count >= 3U) ? 2U : 1U;` | Literal integer without named macro abstraction. |
| `sub_power.c` | 220 | `2U` | **Magic Integer Constant** | `uint32_t lookback   = (count >= 3U) ? 2U : 1U;` | Literal integer without named macro abstraction. |
| `sub_power.c` | 221 | `8U` | **Magic Integer Constant** | `uint32_t prev_idx   = (newest_idx + 8U - lookback) % 8U;` | Literal integer without named macro abstraction. |
| `sub_power.c` | 221 | `8U;` | **Magic Integer Constant** | `uint32_t prev_idx   = (newest_idx + 8U - lookback) % 8U;` | Literal integer without named macro abstraction. |
| `sub_power.c` | 273 | `10)` | **Magic Integer Constant** | `if (delta_x10 < 10) {` | Literal integer without named macro abstraction. |
| `sub_power.c` | 308 | `2000,` | **Magic Integer Constant** | `adc_cali_raw_to_voltage(s_cali_handle, 2000, &v_2000);` | Literal integer without named macro abstraction. |
| `sub_power.c` | 309 | `3000,` | **Magic Integer Constant** | `adc_cali_raw_to_voltage(s_cali_handle, 3000, &v_3000);` | Literal integer without named macro abstraction. |
| `sub_power.c` | 316 | `2000LL)` | **Magic Integer Constant** | `int32_t b_offset = (int32_t)((int64_t)2 * v_2000 - (((int64_t)m_scale * 2000LL) / 4096LL));` | Literal integer without named macro abstraction. |
| `sub_power.c` | 316 | `4096LL));` | **Magic Integer Constant** | `int32_t b_offset = (int32_t)((int64_t)2 * v_2000 - (((int64_t)m_scale * 2000LL) / 4096LL));` | Literal integer without named macro abstraction. |
| `sub_power.c` | 352 | `4000;` | **Battery / Voltage Threshold** | `ulp_last_vbat_mv    = 4000;` | Critical electrical or state-of-charge threshold limit. |
| `sub_power.c` | 496 | `2U)` | **Magic Integer Constant** | `btn_drain_us < SUB_POWER_RTC_INT_DRAIN_TIMEOUT_US * 2U) {` | Literal integer without named macro abstraction. |
| `sub_power.c` | 507 | `(4` | **Magic Integer Constant** | `(unsigned long)REG_READ(RTC_GPIO_PIN0_REG + (4 * 0)),` | Literal integer without named macro abstraction. |
| `sub_power.c` | 508 | `(4` | **Magic Integer Constant** | `(unsigned long)REG_READ(RTC_GPIO_PIN0_REG + (4 * 5)),` | Literal integer without named macro abstraction. |
| `sub_power.c` | 508 | `5)),` | **Magic Integer Constant** | `(unsigned long)REG_READ(RTC_GPIO_PIN0_REG + (4 * 5)),` | Literal integer without named macro abstraction. |
| `sub_power.c` | 509 | `(4` | **Magic Integer Constant** | `(unsigned long)REG_READ(RTC_GPIO_PIN0_REG + (4 * 18)));` | Literal integer without named macro abstraction. |
| `sub_power.c` | 509 | `18)));` | **Magic Integer Constant** | `(unsigned long)REG_READ(RTC_GPIO_PIN0_REG + (4 * 18)));` | Literal integer without named macro abstraction. |
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
| `sub_sdcard.c` | 106 | `5,` | **Magic Integer Constant** | `.max_files = 5,` | Literal integer without named macro abstraction. |
| `main.c` | 26 | `5;` | **Magic Integer Constant** | `volatile uint32_t overflow_limit  = 5;` | Literal integer without named macro abstraction. |
| `main.c` | 32 | `8601;` | **Magic Integer Constant** | `volatile uint32_t cal_scale       = 8601;` | Literal integer without named macro abstraction. |
| `main.c` | 34 | `4000;` | **Battery / Voltage Threshold** | `volatile uint32_t last_vbat_mv    = 4000;` | Critical electrical or state-of-charge threshold limit. |
| `main.c` | 39 | `{4000,` | **Battery / Voltage Threshold** | `volatile uint32_t vbat_ring[ULP_VBAT_RING_SIZE] = {4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000};` | Critical electrical or state-of-charge threshold limit. |
| `main.c` | 39 | `4000,` | **Battery / Voltage Threshold** | `volatile uint32_t vbat_ring[ULP_VBAT_RING_SIZE] = {4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000};` | Critical electrical or state-of-charge threshold limit. |
| `main.c` | 39 | `4000,` | **Battery / Voltage Threshold** | `volatile uint32_t vbat_ring[ULP_VBAT_RING_SIZE] = {4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000};` | Critical electrical or state-of-charge threshold limit. |
| `main.c` | 39 | `4000,` | **Battery / Voltage Threshold** | `volatile uint32_t vbat_ring[ULP_VBAT_RING_SIZE] = {4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000};` | Critical electrical or state-of-charge threshold limit. |
| `main.c` | 39 | `4000,` | **Battery / Voltage Threshold** | `volatile uint32_t vbat_ring[ULP_VBAT_RING_SIZE] = {4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000};` | Critical electrical or state-of-charge threshold limit. |
| `main.c` | 39 | `4000,` | **Battery / Voltage Threshold** | `volatile uint32_t vbat_ring[ULP_VBAT_RING_SIZE] = {4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000};` | Critical electrical or state-of-charge threshold limit. |
| `main.c` | 39 | `4000,` | **Battery / Voltage Threshold** | `volatile uint32_t vbat_ring[ULP_VBAT_RING_SIZE] = {4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000};` | Critical electrical or state-of-charge threshold limit. |
| `main.c` | 39 | `4000};` | **Battery / Voltage Threshold** | `volatile uint32_t vbat_ring[ULP_VBAT_RING_SIZE] = {4000, 4000, 4000, 4000, 4000, 4000, 4000, 4000};` | Critical electrical or state-of-charge threshold limit. |
| `main.c` | 163 | `3250))` | **Battery / Voltage Threshold** | `if (!usb_connected && (vbat_mv >= 100 && vbat_mv < 3250)) {` | Critical electrical or state-of-charge threshold limit. |
| `main.c` | 164 | `6;` | **Magic Integer Constant** | `last_wake_cause = 6;` | Literal integer without named macro abstraction. |
| `main.c` | 200 | `2;` | **Magic Integer Constant** | `last_wake_cause = 2;` | Literal integer without named macro abstraction. |
| `main.c` | 201 | `2;` | **Magic Integer Constant** | `last_wake_btn   = 2;` | Literal integer without named macro abstraction. |
| `main.c` | 211 | `2;` | **Magic Integer Constant** | `last_wake_cause = is_boot ? 1 : 2;` | Literal integer without named macro abstraction. |
| `main.c` | 212 | `2;` | **Magic Integer Constant** | `last_wake_btn   = is_boot ? 1 : 2;` | Literal integer without named macro abstraction. |
| `main.c` | 228 | `4;` | **Magic Integer Constant** | `last_wake_cause = 4;` | Literal integer without named macro abstraction. |
| `main.c` | 235 | `3;` | **Magic Integer Constant** | `last_wake_cause = 3;` | Literal integer without named macro abstraction. |
| `main.c` | 264 | `5;` | **Magic Integer Constant** | `last_wake_cause = 5;` | Literal integer without named macro abstraction. |
