/**
 * @file sub_display.cpp
 * @brief Layer 2: SSD1681 e-Paper display manager implementation
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "h1os/sub_display.h"

#include "driver/gpio.h"
#include "esp_attr.h"
#include "esp_check.h"
#include "esp_log.h"
#include "esp_rom_sys.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "h1os/hal_io.h"
#include "h1os/hal_spi.h"
#include "h1os/hal_types.h"

#include <string.h>

static const char *TAG = "sub_display";

#define SUB_DISPLAY_IDLE_POLL_BOUND 60U /**< Maximum poll loops awaiting EPD BUSY assertion (approx 15 ms). */

static uint8_t s_current_frame[EPD_BUFFER_SIZE];
static uint8_t s_previous_frame[EPD_BUFFER_SIZE];

static bool              s_inited                     = false;
static bool              s_in_deep_sleep              = false;
static bool              s_busy_isr_installed         = false;
static int16_t           s_last_glass_temp_centi_c    = 0;
static StaticSemaphore_t s_busy_idle_sem_buf;
static SemaphoreHandle_t s_busy_idle_sem              = NULL;

/**
 * @brief Solomon Systech SSD1681 1.54" E-Paper Partial Refresh Waveform Table (WF_PARTIAL_1IN54).
 *
 * @details Authoritative decomposition and register mapping for the 159-byte factory partial
 *          refresh waveform lookup table used on the Waveshare ESP32-S3 ePaper 1.54" V2 panel.
 *
 *          References:
 *          - Solomon Systech SSD1681 Advance Information                            (Rev 0.13, Jun 2019)
 *            - Section 6.6: Programmable Waveform for Gate, Source and VCOM         (pp. 13-14)
 *            - Section 6.7: Waveform Setting & Figure 6-6: Waveform Setting Mapping (pp. 14-16)
 *            - Section 7:   Command Table                                           (pp. 20-33)
 *
 *          Multi-Register Dispatch Architecture:
 *          The 159-byte payload is partitioned across five distinct SSD1681 hardware registers:
 *          +-------------------+---------+-----------+------------------------------------------------+
 *          | Register Command  | Offset  | Length    | Hardware Subsystem / Purpose                   |
 *          +-------------------+---------+-----------+------------------------------------------------+
 *          | 0x32 (WRITE_LUT)  | 0..152  | 153 Bytes | Core Voltage LUTs (0-4), Timing (0-11), FR, XON|
 *          | 0x3F (EOPT)       | 153     | 1 Byte    | End of Frame Option (LUT termination behavior) |
 *          | 0x03 (GATE_VOLT)  | 154     | 1 Byte    | Gate Driving Voltages (VGH / VGL)              |
 *          | 0x04 (SRCE_VOLT)  | 155..157| 3 Bytes   | Source Driving Voltages (VSH1, VSH2, VSL)      |
 *          | 0x2C (WRITE_VCOM) | 158     | 1 Byte    | VCOM Modulation Voltage (DCVCOM)               |
 *          +-------------------+---------+-----------+------------------------------------------------+
 *
 *          Phase Voltage Bitfield Encoding (Table 6-6):
 *          Each LUT byte controls 4 phases (A, B, C, D) for that group:
 *          - Bits [7:6]: Phase A Voltage Selection (VS[nA])
 *          - Bits [5:4]: Phase B Voltage Selection (VS[nB])
 *          - Bits [3:2]: Phase C Voltage Selection (VS[nC])
 *          - Bits [1:0]: Phase D Voltage Selection (VS[nD])
 *
 *          Source Voltage Levels (LUT0 - LUT3):
 *          - 00b = VSS  (0.0V / Ground / Floating)
 *          - 01b = VSH1 (+15.0V, set by register 0x04 byte 1)
 *          - 10b = VSL  (-15.0V, set by register 0x04 byte 3)
 *          - 11b = VSH2 (+5.8V,  set by register 0x04 byte 2)
 *
 *          VCOM Voltage Levels (LUT4):
 *          - 00b = DCVCOM (-1.0V, set by register 0x2C)
 *          - 01b = VSH1 + DCVCOM (+14.0V)
 *          - 10b = VSL  + DCVCOM (-16.0V)
 *          - 11b = N/A
 *
 *          Differential Ping-Pong LUT Semantics (Display Mode 2, Command 0x37 = 0x40):
 *          - LUT0: Black-to-Black (B -> B) transition (Hold black, no change)
 *          - LUT1: White-to-White (W -> W) transition (Hold white, no change)
 *          - LUT2: Black-to-White (B -> W) transition (Drive white pigment to surface)
 *          - LUT3: White-to-Black (W -> B) transition (Drive black pigment to surface)
 *          - LUT4: VCOM backplane electrode modulation
 */
static const uint8_t WF_PARTIAL_1IN54[159] = {

    /* =========================================================================================
     * 1. COMMAND 0x32: WRITE LUT REGISTER (Bytes 0 .. 152 = 153 Bytes)
     * ========================================================================================= */

    /* -----------------------------------------------------------------------------------------
     * 1.1 Voltage Selection LUTs (Bytes 0 .. 59 = 60 Bytes, 12 Groups x 5 Tables)
     *     Format per byte: [Phase A (D7:D6) | Phase B (D5:D4) | Phase C (D3:D2) | Phase D (D1:D0)]
     * ----------------------------------------------------------------------------------------- */

    /* --- LUT0: Black -> Black Transition (Bytes 0 .. 11, Groups 0 .. 11) ---
     * Group 0: 0x00 -> Phase A..D = VSS (0V, particle holding)
     * Group 1: 0x40 -> Phase A = VSH1 (+15V), Phase B..D = VSS
     * Groups 2..11: 0x00 -> Inactive / skipped */
    /* [  0..  3] Grp 0..3   */ 0x00, 0x40, 0x00, 0x00,
    /* [  4..  7] Grp 4..7   */ 0x00, 0x00, 0x00, 0x00,
    /* [  8.. 11] Grp 8..11  */ 0x00, 0x00, 0x00, 0x00,

    /* --- LUT1: White -> White Transition (Bytes 12 .. 23, Groups 0 .. 11) ---
     * Group 0: 0x80 -> Phase A = VSL (-15V), Phase B..D = VSS
     * Group 1: 0x80 -> Phase A = VSL (-15V), Phase B..D = VSS
     * Groups 2..11: 0x00 -> Inactive / skipped */
    /* [ 12.. 15] Grp 0..3   */ 0x80, 0x80, 0x00, 0x00,
    /* [ 16.. 19] Grp 4..7   */ 0x00, 0x00, 0x00, 0x00,
    /* [ 20.. 23] Grp 8..11  */ 0x00, 0x00, 0x00, 0x00,

    /* --- LUT2: Black -> White Transition (Bytes 24 .. 35, Groups 0 .. 11) ---
     * Group 0: 0x40 -> Phase A = VSH1 (+15V, pull white pigment), Phase B..D = VSS
     * Group 1: 0x40 -> Phase A = VSH1 (+15V, pull white pigment), Phase B..D = VSS
     * Groups 2..11: 0x00 -> Inactive / skipped */
    /* [ 24.. 27] Grp 0..3   */ 0x40, 0x40, 0x00, 0x00,
    /* [ 28.. 31] Grp 4..7   */ 0x00, 0x00, 0x00, 0x00,
    /* [ 32.. 35] Grp 8..11  */ 0x00, 0x00, 0x00, 0x00,

    /* --- LUT3: White -> Black Transition (Bytes 36 .. 47, Groups 0 .. 11) ---
     * Group 0: 0x00 -> Phase A..D = VSS (0V)
     * Group 1: 0x80 -> Phase A = VSL (-15V, pull black pigment), Phase B..D = VSS
     * Groups 2..11: 0x00 -> Inactive / skipped */
    /* [ 36.. 39] Grp 0..3   */ 0x00, 0x80, 0x00, 0x00,
    /* [ 40.. 43] Grp 4..7   */ 0x00, 0x00, 0x00, 0x00,
    /* [ 44.. 47] Grp 8..11  */ 0x00, 0x00, 0x00, 0x00,

    /* --- LUT4: VCOM Modulation Waveform (Bytes 48 .. 59, Groups 0 .. 11) ---
     * All Groups: 0x00 -> DCVCOM (-1.0V constant common backplane bias) */
    /* [ 48.. 51] Grp 0..3   */ 0x00, 0x00, 0x00, 0x00,
    /* [ 52.. 55] Grp 4..7   */ 0x00, 0x00, 0x00, 0x00,
    /* [ 56.. 59] Grp 8..11  */ 0x00, 0x00, 0x00, 0x00,

    /* -----------------------------------------------------------------------------------------
     * 1.2 Timing, Phase Length & Repeat Counts (Bytes 60 .. 143 = 84 Bytes, 12 Groups x 7 Bytes)
     *     Structure per group:
     *     - TP[nA]  : Phase A duration in frames           (0..255; 0 = skipped            )
     *     - TP[nB]  : Phase B duration in frames           (0..255; 0 = skipped            )
     *     - SR[nAB] : State repeat count for Sub-Group A&B (0 = 1x, 1 = 2x, ..., 255 = 256x)
     *     - TP[nC]  : Phase C duration in frames           (0..255; 0 = skipped            )
     *     - TP[nD]  : Phase D duration in frames           (0..255; 0 = skipped            )
     *     - SR[nCD] : State repeat count for Sub-Group C&D (0 = 1x, 1 = 2x, ..., 255 = 256x)
     *     - RP[n]   : Group repeat count                   (0 = 1x, 1 = 2x, ..., 255 = 256x)
     * ----------------------------------------------------------------------------------------- */
    /* TP[A]  TP[B]  SR[AB] TP[C]  TP[D]  SR[CD] RP     */
    /* [ 60.. 66] Group  0: Phase A = 15 frames, Repeat = 1x */
       0x0F,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
    /* [ 67.. 73] Group  1: Phase A = 1 frame, Phase B = 1 frame, Repeat = 1x */
       0x01,  0x01,  0x00,  0x00,  0x00,  0x00,  0x00,
    /* [ 74.. 80] Group  2: Inactive (all phases skipped) */
       0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
    /* [ 81.. 87] Group  3: Inactive (all phases skipped) */
       0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
    /* [ 88.. 94] Group  4: Inactive (all phases skipped) */
       0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
    /* [ 95..101] Group  5: Inactive (all phases skipped) */
       0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
    /* [102..108] Group  6: Inactive (all phases skipped) */
       0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
    /* [109..115] Group  7: Inactive (all phases skipped) */
       0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
    /* [116..122] Group  8: Inactive (all phases skipped) */
       0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
    /* [123..129] Group  9: Inactive (all phases skipped) */
       0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
    /* [130..136] Group 10: Inactive (all phases skipped) */
       0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,
    /* [137..143] Group 11: Inactive (all phases skipped) */
       0x00,  0x00,  0x00,  0x00,  0x00,  0x00,  0x00,

    /* -----------------------------------------------------------------------------------------
     * 1.3 Frame Rate Control: FR[0 .. 11] (Bytes 144 .. 149 = 6 Bytes, 2 Groups per Byte)
     *     Bits [7:4] = Even Group Frame Rate, Bits [3:0] = Odd Group Frame Rate
     *     Value 0x22 -> FR[n] = 2 (standard ~50 Hz frame frequency setting)
     * ----------------------------------------------------------------------------------------- */
    /* [144] FR[0]  & FR[1]   */ 0x22,
    /* [145] FR[2]  & FR[3]   */ 0x22,
    /* [146] FR[4]  & FR[5]   */ 0x22,
    /* [147] FR[6]  & FR[7]   */ 0x22,
    /* [148] FR[8]  & FR[9]   */ 0x22,
    /* [149] FR[10] & FR[11]  */ 0x22,

    /* -----------------------------------------------------------------------------------------
     * 1.4 All-Gate-On (XON) Gate Line Selection (Bytes 150 .. 152 = 3 Bytes)
     *     Bitfield enabling concurrent gate assertion during sub-group phases.
     *     Value 0x00 -> Normal gate-by-gate interlaced scanning (no All-Gate-On override).
     * ----------------------------------------------------------------------------------------- */
    /* [150] XON[0AB..3CD]   */ 0x00,
    /* [151] XON[4AB..7CD]   */ 0x00,
    /* [152] XON[8AB..11CD]  */ 0x00,

    /* =========================================================================================
     * 2. COMMAND 0x3F: END OF FRAME OPTION (EOPT) (Byte 153 = 1 Byte)
     * ========================================================================================= */
    /* [153] EOPT: 0x02 = Normal termination (POR default; source output floating on finish) */
    0x02,

    /* =========================================================================================
     * 3. COMMAND 0x03: GATE DRIVING VOLTAGE CONTROL (Byte 154 = 1 Byte)
     * ========================================================================================= */
    /* [154] VGH / VGL: 0x17 -> VGH = +20.0V, VGL = -20.0V (Max Gate overdrive swing = 40Vp-p) */
    0x17,

    /* =========================================================================================
     * 4. COMMAND 0x04: SOURCE DRIVING VOLTAGE CONTROL (Bytes 155 .. 157 = 3 Bytes)
     * ========================================================================================= */
    /* [155] VSH1: 0x41 -> Source High Level 1 = +15.0V (Bit 7 = 0; range 9.0V to 17.0V)      */
    0x41,
    /* [156] VSH2: 0xB0 -> Source High Level 2 = +5.8V  (Bit 7 = 1; range 2.4V to 8.8V)       */
    0xB0,
    /* [157] VSL : 0x32 -> Source Low Level   = -15.0V (Bit 7 = 0; range -5.0V to -17.0V)     */
    0x32,

    /* =========================================================================================
     * 5. COMMAND 0x2C: WRITE VCOM REGISTER (Byte 158 = 1 Byte)
     * ========================================================================================= */
    /* [158] DCVCOM: 0x28 -> Common Electrode Voltage = -1.0V (Table 7-1: 28h = -1.0V)         */
    0x28
};

/**
 * @brief IRAM GPIO falling-edge interrupt handler for HAL_PIN_EPD_BUSY (GPIO 8).
 *
 * @details Signals s_busy_idle_sem the microsecond the SSD1681 state machine deasserts
 *          BUSY from HIGH (1) to LOW (0).
 */
static void IRAM_ATTR epd_busy_falling_isr_handler(void *arg)
{
    (void)arg;
    if (s_busy_idle_sem != NULL) {
        BaseType_t high_task_woken = pdFALSE;
        (void)xSemaphoreGiveFromISR(s_busy_idle_sem, &high_task_woken);
        if (high_task_woken == pdTRUE) {
            portYIELD_FROM_ISR();
        }
    }
}

/**
 * @brief Ensure HAL_PIN_EPD_BUSY falling-edge interrupt and static binary semaphore are initialized.
 */
static void epd_ensure_busy_sync_ready(void)
{
    if (s_busy_idle_sem == NULL) {
        s_busy_idle_sem = xSemaphoreCreateBinaryStatic(&s_busy_idle_sem_buf);
    }
    if (!s_busy_isr_installed) {
        esp_err_t isr_err = gpio_install_isr_service(0);
        if (isr_err == ESP_OK || isr_err == ESP_ERR_INVALID_STATE) {
            gpio_set_intr_type(HAL_PIN_EPD_BUSY, GPIO_INTR_NEGEDGE);
            if (gpio_isr_handler_add(HAL_PIN_EPD_BUSY, epd_busy_falling_isr_handler, NULL) == ESP_OK) {
                gpio_intr_enable(HAL_PIN_EPD_BUSY);
                s_busy_isr_installed = true;
            }
        }
    }
}

/**
 * @brief Epd reset pulse.
 *
 * @details Wakes SSD1681 out of Deep Sleep Mode 1 (0x10 = 0x01) and resets state machine.
 *
 * @return Return value of type static void.
 */
static void epd_reset_pulse(void)
{
    gpio_set_level(HAL_PIN_EPD_RST, 0);
    esp_rom_delay_us(2000);
    gpio_set_level(HAL_PIN_EPD_RST, 1);
    esp_rom_delay_us(2000);
    s_in_deep_sleep = false;
}

/**
 * @brief Synchronously wait for EPD panel to finish driving electrophoretic particles.
 *
 * @details Waits up to 15 ms for the SSD1681 state machine to assert BUSY HIGH (1) after
 *          a command (e.g. 0x20 Master Activation or 0x12 SW Reset), then blocks on the
 *          hardware falling-edge GPIO interrupt semaphore (`s_busy_idle_sem`) until BUSY
 *          drops back LOW (0) with zero 10 ms polling context switches.
 *
 * @param[in]    timeout_ticks   Max FreeRTOS ticks to wait.
 *
 * @return ESP_OK on panel ready, ESP_ERR_TIMEOUT on expiration.
 */
esp_err_t sub_display_wait_busy(TickType_t timeout_ticks)
{
    epd_ensure_busy_sync_ready();

    /* Clear any stale semaphore token from prior transactions */
    if (s_busy_idle_sem != NULL) {
        (void)xSemaphoreTake(s_busy_idle_sem, 0);
    }

    /* Wait up to 15 ms for BUSY (GPIO 8) to assert HIGH after command issue */
    for (int32_t i = 0; i < (int32_t)SUB_DISPLAY_IDLE_POLL_BOUND; i++) {
        if (gpio_get_level(HAL_PIN_EPD_BUSY) == 1) {
            break;
        }
        esp_rom_delay_us(250);
    }

    if (gpio_get_level(HAL_PIN_EPD_BUSY) == 0) {
        return ESP_OK;
    }

    if (s_busy_idle_sem != NULL && s_busy_isr_installed) {
        /* Clear token again in case a transient edge occurred during assertion check, then re-verify pin level */
        (void)xSemaphoreTake(s_busy_idle_sem, 0);
        if (gpio_get_level(HAL_PIN_EPD_BUSY) == 0) {
            return ESP_OK;
        }

        if (xSemaphoreTake(s_busy_idle_sem, timeout_ticks) == pdTRUE) {
            return ESP_OK;
        }
        if (gpio_get_level(HAL_PIN_EPD_BUSY) == 0) {
            return ESP_OK;
        }
        ESP_LOGW(TAG, "SSD1681 BUSY interrupt wait timed out");
        return ESP_ERR_TIMEOUT;
    }

    /* Defensive fallback if GPIO ISR service is unavailable */
    TickType_t start_ticks = xTaskGetTickCount();
    while (gpio_get_level(HAL_PIN_EPD_BUSY) == 1) {
        TickType_t elapsed = xTaskGetTickCount() - start_ticks;
        if (elapsed >= timeout_ticks) {
            ESP_LOGW(TAG, "SSD1681 BUSY wait timed out");
            return ESP_ERR_TIMEOUT;
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }

    return ESP_OK;
}

/**
 * @brief Epd configure base registers.
 *
 * @return Return value of type static void.
 */
static esp_err_t epd_configure_base_registers(void)
{
    uint8_t d_drv[] = {0xC7, 0x00, 0x00};
    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x01), TAG, "SPI cmd 0x01 failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(d_drv, sizeof(d_drv)), TAG, "SPI data 0x01 failed");

    uint8_t d_entry[] = {0x03};
    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x11), TAG, "SPI cmd 0x11 failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(d_entry, sizeof(d_entry)), TAG, "SPI data 0x11 failed");

    uint8_t d_xwin[] = {0x00, 0x18};
    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x44), TAG, "SPI cmd 0x44 failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(d_xwin, sizeof(d_xwin)), TAG, "SPI data 0x44 failed");

    uint8_t d_ywin[] = {0x00, 0x00, 0xC7, 0x00};
    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x45), TAG, "SPI cmd 0x45 failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(d_ywin, sizeof(d_ywin)), TAG, "SPI data 0x45 failed");

    uint8_t d_border[] = {0x05};
    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x3C), TAG, "SPI cmd 0x3C failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(d_border, sizeof(d_border)), TAG, "SPI data 0x3C failed");
    return ESP_OK;
}

/**
 * @brief Initialize SSD1681 display controller.
 *
 * @details Wakes panel, initializes SPI interface, configures scanning geometry, and sets up BUSY falling-edge interrupt synchronization.
 *
 * @param[in]    is_wake_cycle   True if resuming from deep sleep with persistent framebuffer.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_init(bool is_wake_cycle)
{
    (void)is_wake_cycle;
    if (s_inited) {
        if (s_in_deep_sleep) {
            epd_reset_pulse();
            sub_display_wait_busy(pdMS_TO_TICKS(1000));
            hal_spi_write_cmd(0x12);
            sub_display_wait_busy(pdMS_TO_TICKS(1000));
            epd_configure_base_registers();
        }
        return ESP_OK;
    }

    hal_spi_init();

    gpio_config_t busy_conf = {
        .pin_bit_mask = (1ULL << HAL_PIN_EPD_BUSY),
        .mode         = GPIO_MODE_INPUT,
        .pull_up_en   = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type    = GPIO_INTR_NEGEDGE,
    };
    gpio_config(&busy_conf);
    epd_ensure_busy_sync_ready();

    epd_reset_pulse();
    sub_display_wait_busy(pdMS_TO_TICKS(1000));

    hal_spi_write_cmd(0x12);
    sub_display_wait_busy(pdMS_TO_TICKS(1000));

    static constexpr int16_t SSD1681_TEMP_HALF_DEG_CENTI_C = 50;
    uint8_t temp_raw[2] = {0};

    hal_spi_write_cmd(0x18);
    uint8_t t_sel[] = {0x80};
    hal_spi_write_data(t_sel, sizeof(t_sel));

    hal_spi_write_cmd(0x22);
    uint8_t t_load[] = {0xB1};
    hal_spi_write_data(t_load, sizeof(t_load));

    hal_spi_write_cmd(0x20);
    sub_display_wait_busy(pdMS_TO_TICKS(100));

    if (hal_spi_read_data(0x1B, temp_raw, sizeof(temp_raw)) == ESP_OK) {
        if (temp_raw[0] != 0x00 && temp_raw[0] != 0xFF) {
            int8_t  temp_int = (int8_t)temp_raw[0];
            int16_t frac_c   = (temp_raw[1] & 0x80) ? SSD1681_TEMP_HALF_DEG_CENTI_C : 0;
            int16_t glass_cc = (int16_t)temp_int * 100 + ((temp_int >= 0) ? frac_c : -frac_c);
            if (glass_cc >= -4000 && glass_cc <= 8500) {
                s_last_glass_temp_centi_c = glass_cc;
                ESP_LOGI(TAG, "SSD1681 Pre-display Glass Temp acquired: %.2f C (Raw: 0x%02X 0x%02X)",
                         (double)((float)glass_cc / 100.0f), temp_raw[0], temp_raw[1]);
            }
        }
    }

    epd_configure_base_registers();

    memset(s_current_frame, 0xFF, EPD_BUFFER_SIZE);
    memset(s_previous_frame, 0xFF, EPD_BUFFER_SIZE);

    s_inited = true;
    return ESP_OK;
}

/**
 * @brief Deinitialize SSD1681 display subsystem and release SPI bus resources.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_deinit(void)
{
    if (!s_inited) {
        return ESP_OK;
    }

    sub_display_enter_deep_sleep();
    if (s_busy_isr_installed) {
        (void)gpio_isr_handler_remove(HAL_PIN_EPD_BUSY);
        s_busy_isr_installed = false;
    }
    hal_spi_deinit();
    s_inited = false;
    return ESP_OK;
}

uint8_t *sub_display_get_framebuffer(void)
{
    return s_current_frame;
}

/**
 * @brief Clear active working framebuffer.
 *
 * @param[in]    color           0xFF for White, 0x00 for Black.
 */
void sub_display_clear(uint8_t color)
{
    memset(s_current_frame, color, EPD_BUFFER_SIZE);
}

/**
 * @brief Epd commit ram dma.
 *
 * @param[in]    ram_cmd         Parameter ram_cmd.
 * @param[in]    frame_data      Parameter frame_data.
 *
 * @return Return value of type static void.
 */
static esp_err_t epd_commit_ram_dma(uint8_t ram_cmd, const uint8_t *frame_data)
{
    static const uint8_t d_x[] = {0x00};
    static const uint8_t d_y[] = {0x00, 0x00};

    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x4E), TAG, "SPI cmd 0x4E failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(d_x, sizeof(d_x)), TAG, "SPI data 0x4E failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x4F), TAG, "SPI cmd 0x4F failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(d_y, sizeof(d_y)), TAG, "SPI data 0x4F failed");

    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(ram_cmd), TAG, "SPI ram_cmd failed");
    return hal_spi_write_frame_dma(frame_data);
}

/**
 * @brief Synchronize previous frame into shadow buffer and hardware RAM 0x26.
 *
 * @details Essential on deep sleep wake to enable differential partial scanning against the glass.
 *
 * @param[in]    prev_frame      Pointer to 5000-byte pre-sleep image buffer.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_sync_previous_frame(const uint8_t *prev_frame)
{
    if (prev_frame == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    memcpy(s_previous_frame, prev_frame, EPD_BUFFER_SIZE);
    memcpy(s_current_frame, prev_frame, EPD_BUFFER_SIZE);

    epd_commit_ram_dma(0x26, s_previous_frame);

    ESP_LOGI(TAG, "SSD1681 RAM 0x26 synchronized with prior frame for differential scan");
    return ESP_OK;
}

/**
 * @brief Execute full display refresh (OTP factory waveform LUT).
 *
 * @details Synchronizes old frame RAM (0x26) with new frame RAM (0x24).
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_refresh_full(void)
{
    if (!s_inited || s_in_deep_sleep) {
        sub_display_init(false);
    }

    int64_t t_start = esp_timer_get_time();

    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x12), TAG, "SPI cmd 0x12 failed");
    sub_display_wait_busy(pdMS_TO_TICKS(1000));
    ESP_RETURN_ON_ERROR(epd_configure_base_registers(), TAG, "Base registers config failed");

    ESP_RETURN_ON_ERROR(epd_commit_ram_dma(0x24, s_current_frame), TAG, "Commit RAM 0x24 failed");
    ESP_RETURN_ON_ERROR(epd_commit_ram_dma(0x26, s_current_frame), TAG, "Commit RAM 0x26 failed");

    uint8_t d_upd[] = {0xF7};
    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x22), TAG, "SPI cmd 0x22 failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(d_upd, sizeof(d_upd)), TAG, "SPI data 0x22 failed");

    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x20), TAG, "SPI cmd 0x20 failed");
    sub_display_wait_busy(pdMS_TO_TICKS(5000));

    memcpy(s_previous_frame, s_current_frame, EPD_BUFFER_SIZE);

    int64_t t_elapsed_ms = (esp_timer_get_time() - t_start) / 1000LL;
    ESP_LOGI(TAG, "Full OTP Refresh completed in %lld ms", (long long)t_elapsed_ms);

    return ESP_OK;
}

/**
 * @brief Clear display to pure white and trigger full OTP refresh.
 *
 * @details Clears and discharges electrophoretic microcapsules to protect against permanent burn-in.
 *          Ensures SPI2 and SSD1681 are initialized and awake even when invoked directly from
 *          deep-sleep ULP power-off wakes (ORCH_FLOW_CRITICAL_OFF).
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_clear_to_white_full(void)
{
    if (!s_inited || s_in_deep_sleep) {
        sub_display_init(false);
    }
    memset(s_current_frame, 0xFF, EPD_BUFFER_SIZE);
    memset(s_previous_frame, 0xFF, EPD_BUFFER_SIZE);
    ESP_LOGI(TAG, "Clearing e-Paper display to pure white for storage / burn-in protection...");
    return sub_display_refresh_full();
}

/**
 * @brief Epd load custom lut.
 *
 * @param[in]    lut_buffer      Parameter lut_buffer.
 *
 * @return Return value of type static void.
 */
static esp_err_t epd_load_custom_lut(const uint8_t *lut_buffer)
{
    if (lut_buffer == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x32), TAG, "SPI cmd 0x32 failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(&lut_buffer[0], 153), TAG, "SPI data 0x32 failed");

    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x3F), TAG, "SPI cmd 0x3F failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(&lut_buffer[153], 1), TAG, "SPI data 0x3F failed");

    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x03), TAG, "SPI cmd 0x03 failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(&lut_buffer[154], 1), TAG, "SPI data 0x03 failed");

    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x04), TAG, "SPI cmd 0x04 failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(&lut_buffer[155], 3), TAG, "SPI data 0x04 failed");

    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x2C), TAG, "SPI cmd 0x2C failed");
    return hal_spi_write_data(&lut_buffer[158], 1);
}

/**
 * @brief Execute fast partial refresh (~300ms) with software LUT.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_refresh_partial(void)
{
    if (!s_inited || s_in_deep_sleep) {
        sub_display_init(false);
    }

    int64_t t_start = esp_timer_get_time();

    ESP_RETURN_ON_ERROR(epd_commit_ram_dma(0x24, s_current_frame), TAG, "Commit RAM 0x24 failed");

    ESP_RETURN_ON_ERROR(epd_load_custom_lut(WF_PARTIAL_1IN54), TAG, "Custom LUT load failed");

    static const uint8_t disp_option[10] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00};
    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x37), TAG, "SPI cmd 0x37 failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(disp_option, sizeof(disp_option)), TAG, "SPI data 0x37 failed");

    uint8_t d_border[] = {0x80};
    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x3C), TAG, "SPI cmd 0x3C failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(d_border, sizeof(d_border)), TAG, "SPI data 0x3C failed");

    uint8_t d_upd[] = {0xCF};
    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x22), TAG, "SPI cmd 0x22 failed");
    ESP_RETURN_ON_ERROR(hal_spi_write_data(d_upd, sizeof(d_upd)), TAG, "SPI data 0x22 failed");

    ESP_RETURN_ON_ERROR(hal_spi_write_cmd(0x20), TAG, "SPI cmd 0x20 failed");
    sub_display_wait_busy(pdMS_TO_TICKS(2000));

    memcpy(s_previous_frame, s_current_frame, EPD_BUFFER_SIZE);

    int64_t t_elapsed_ms = (esp_timer_get_time() - t_start) / 1000LL;
    ESP_LOGI(TAG, "Partial Refresh completed in %lld ms (Target: ~300 ms)", (long long)t_elapsed_ms);

    return ESP_OK;
}

/**
 * @brief Retrieve the latest cached SSD1681 on-glass temperature in centi-degrees Celsius.
 *
 * @return Cached glass temperature in centi-°C (0 if not yet sampled).
 */
int16_t sub_display_get_glass_temp_centi_c(void)
{
    return s_last_glass_temp_centi_c;
}

/**
 * @brief Read SSD1681 on-glass integrated temperature sensor (SPI Cmd 0x1B).
 *
 * @param[out]   out_temp_c      Surface glass temperature in Celsius.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_read_glass_temp(float *out_temp_c)
{
    if (out_temp_c == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    if (s_inited) {
        *out_temp_c = (float)s_last_glass_temp_centi_c / 100.0f;
        return ESP_OK;
    }

    uint8_t temp_raw[2] = {0};

    hal_spi_write_cmd(0x18);
    uint8_t t_sel[] = {0x80};
    hal_spi_write_data(t_sel, sizeof(t_sel));

    hal_spi_write_cmd(0x22);
    uint8_t t_load[] = {0xB1};
    hal_spi_write_data(t_load, sizeof(t_load));

    hal_spi_write_cmd(0x20);
    sub_display_wait_busy(pdMS_TO_TICKS(100));

    esp_err_t err = hal_spi_read_data(0x1B, temp_raw, sizeof(temp_raw));
    if (err == ESP_OK) {
        int8_t temp_int = (int8_t)temp_raw[0];
        float temp_frac = (temp_raw[1] & 0x80) ? 0.5f : 0.0f;
        float glass_temp = (float)temp_int + ((temp_int >= 0) ? temp_frac : -temp_frac);

        if (glass_temp < -40.0f || glass_temp > 85.0f || temp_raw[0] == 0xFF || temp_raw[0] == 0x00) {
            *out_temp_c = (float)s_last_glass_temp_centi_c / 100.0f;
            return ESP_ERR_INVALID_RESPONSE;
        }
        s_last_glass_temp_centi_c = (int16_t)(glass_temp * 100.0f);
        *out_temp_c = glass_temp;
    } else {
        *out_temp_c = (float)s_last_glass_temp_centi_c / 100.0f;
    }
    return err;
}

/**
 * @brief Put SSD1681 into Deep Sleep Mode 1 (Command 0x10, Data 0x01 @ 1.0 µA).
 *
 * @details Crucially retains RAM contents while the 3.3V rail remains held.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_display_enter_deep_sleep(void)
{
    if (!s_inited || s_in_deep_sleep) {
        return ESP_OK;
    }

    sub_display_wait_busy(pdMS_TO_TICKS(5000));

    uint8_t d_sleep[] = {0x01};
    hal_spi_write_cmd(0x10);
    hal_spi_write_data(d_sleep, sizeof(d_sleep));
    s_in_deep_sleep = true;
    return ESP_OK;
}
