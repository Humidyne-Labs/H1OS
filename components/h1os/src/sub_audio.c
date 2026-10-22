/**
 * @file sub_audio.c
 * @brief Layer 2: ES8311 codec and NS4168 audio driver implementation
 *
 * Copyright (c) 2026 Humidyne Labs
 * SPDX-License-Identifier: MIT
 */

#include "h1os/sub_audio.h"

#include "driver/gpio.h"
#include "driver/i2s_std.h"
#include "esp_attr.h"
#include "esp_log.h"
#include "esp_pm.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "h1os/hal_i2c.h"
#include "h1os/hal_types.h"
#include "sdkconfig.h"

#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif
#include <string.h>

static const char *TAG = "sub_audio";

#define ES8311_REG_RESET       0x00
#define ES8311_REG_SYS_PWR_ANA 0x0D
#define ES8311_REG_SYS_LP_MOD  0x0F
#define ES8311_REG_DAC_PWR     0x12
#define ES8311_REG_DAC_VOL     0x32
#define ES8311_REG_FLAG        0xFC
#define ES8311_REG_CHIP_ID1    0xFD
#define ES8311_REG_CHIP_ID2    0xFE

#define FRAME_SIZE 0x100

typedef enum {
    AUDIO_CMD_TONE = 0,
    AUDIO_CMD_CHIME,
    AUDIO_CMD_PCM,
} audio_cmd_type_t;

typedef struct {
    audio_cmd_type_t type;
    union {
        struct {
            uint32_t frequency_hz;
            uint32_t duration_ms;
        } tone;
        struct {
            uint8_t chime_type;
        } chime;
        struct {
            const int16_t *samples;
            size_t sample_count;
            uint32_t sample_rate_hz;
        } pcm;
    } params;

    SemaphoreHandle_t done_sem;
    esp_err_t *result;
} audio_cmd_t;

typedef struct {
    uint8_t reg;
    uint8_t val;
} es8311_reg_entry_t;

static i2s_chan_handle_t s_tx_chan = NULL;

static bool s_audio_inited     = false;
static bool s_i2s_chan_enabled = false;
static bool s_codec_in_standby = false;
static bool s_pa_enabled       = false;
static bool s_low_power_mode   = true;

RTC_DATA_ATTR static bool s_rtc_codec_in_standby = false;

static QueueHandle_t s_audio_queue       = NULL;
static TaskHandle_t  s_audio_task_handle = NULL;
static volatile bool s_audio_is_busy     = false;

static uint8_t s_volume_pct = 0;

#if CONFIG_PM_ENABLE
static esp_pm_lock_handle_t s_audio_pm_lock = NULL;
#endif

/**
 * @brief Acquire 240 MHz CPU frequency lock for I2S/APB clock stability.
 */
static inline void audio_cpu_max_acquire(void)
{
#if CONFIG_PM_ENABLE
    if (s_audio_pm_lock == NULL) {
        esp_pm_lock_create(ESP_PM_CPU_FREQ_MAX, 0, "sub_audio", &s_audio_pm_lock);
    }
    if (s_audio_pm_lock != NULL) {
        esp_pm_lock_acquire(s_audio_pm_lock);
    }
#endif
}

/**
 * @brief Release 240 MHz CPU frequency lock.
 */
static inline void audio_cpu_max_release(void)
{
#if CONFIG_PM_ENABLE
    if (s_audio_pm_lock != NULL) {
        esp_pm_lock_release(s_audio_pm_lock);
    }
#endif
}

static const uint8_t es8311_perceptual_vol_table[101] = {
    0x00, 0x3A, 0x48, 0x51, 0x57, 0x5D,
    0x61, 0x65, 0x68, 0x6B, 0x6E, 0x71,
    0x73, 0x75, 0x77, 0x79, 0x7B, 0x7D,
    0x7E, 0x80, 0x81, 0x83, 0x84, 0x85,
    0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C,
    0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92,
    0x93, 0x94, 0x95, 0x96, 0x97, 0x98,
    0x99, 0x99, 0x9A, 0x9B, 0x9C, 0x9D,
    0x9E, 0x9E, 0x9F, 0xA0, 0xA1, 0xA2,
    0xA2, 0xA3, 0xA4, 0xA5, 0xA5, 0xA6,
    0xA7, 0xA8, 0xA8, 0xA9, 0xAA, 0xAA,
    0xAB, 0xAC, 0xAC, 0xAD, 0xAE, 0xAE,
    0xAF, 0xB0, 0xB0, 0xB1, 0xB2, 0xB2,
    0xB3, 0xB3, 0xB4, 0xB5, 0xB5, 0xB6,
    0xB6, 0xB7, 0xB7, 0xB8, 0xB9, 0xB9,
    0xBA, 0xBA, 0xBB, 0xBC, 0xBC, 0xBD,
    0xBD, 0xBE, 0xBE, 0xBF, 0xBF
};

/*
 * Stage 1: Pre-charge sequence
 * Resets digital logic, configures system clocks, power management,
 * analog references, microphone bias, and digital audio serial interface (SDP).
 */
static const es8311_reg_entry_t s_es8311_init_pre_charge[] =
{
    /* Analog / System startup */
    {0x44, 0x08}, /**< REG44: Set internal analog bias / reference current                                     */
    {0x44, 0x08}, /**< REG44: Write repeated to ensure stable latching during startup                          */

    {0x0D, 0xFA}, /**< REG0D: System power down control - power down digital/modulators prior to configuration */

    /* Clock & Power Setup */
    {0x01, 0x30}, /**< REG01: Clock management - enable dig_mclk, BCLK/MCLK source selection                   */
    {0x02, 0x00}, /**< REG02: Clock divider - pre-divider/MCLK division ratio                                  */
    {0x03, 0x10}, /**< REG03: ADC clock divider (DIV_CLKADC) & DAC clock divider (DIV_CLKDAC)                  */
    {0x16, 0x24}, /**< REG16: Internal analog LDO & bandgap voltage reference control                          */
    {0x04, 0x20}, /**< REG04: Master BCLK divider / master mode clock timing                                   */
    {0x05, 0x00}, /**< REG05: Master LRCK divider high byte (DIV_LRCK[11:8])                                   */
    {0x0B, 0x00}, /**< REG0B: Clock gating / internal clock route enables                                      */
    {0x0C, 0x00}, /**< REG0C: Digital system reset / clock synchronization                                     */

    /* Digital Audio Serial Interface (SDP) Setup */
    {0x10, 0x1F}, /**< REG10: SDP in/out format (e.g., standard I2S format, 16/24/32-bit data length)          */
    {0x11, 0x7F}, /**< REG11: SDP control - slave/master mode, tri-state, clock polarity                       */

    /* System Reset & Power Configuration */
    {0x00, 0x80}, /**< REG00: Chip control - CSM (Clock State Machine) reset / digital reset                   */
    {0x01, 0x3F}, /**< REG01: Clock management - un-gate digital clocks for ADC, DAC, and SDP                  */
    {0x06, 0x03}, /**< REG06: Master LRCK divider low byte (DIV_LRCK[7:0])                                     */
    {0x07, 0x00}, /**< REG07: Master LRCK divider fine adjustment / BCLK-to-LRCK ratio                         */
    {0x08, 0xFF}, /**< REG08: Master mode BCLK divider settings                                                */

    /* Analog Front-End (PGA / MIC / Reference) */
    {0x13, 0x10}, /**< REG13: Analog bias circuit power up / current trimming                                  */
    {0x1B, 0x0A}, /**< REG1B: ADC Analog PGA / input amplifier gain stage                                      */
    {0x1C, 0x6A}, /**< REG1C: MIC bias generator enable, level tuning (e.g., 2.0V/2.4V), and reference voltage */
    {0x44, 0x58}, /**< REG44: Analog charge pump / fast charge control for DC blocking caps                    */

    /* Serial Data Port (SDP) Routing */
    {0x09, 0x0C}, /**< REG09: SDP input configuration (DAC data channel select, unmute, polarity)              */
    {0x0A, 0x0C}, /**< REG0A: SDP output configuration (ADC data channel select, tri-state control)            */
};

/*
 * Stage 2: Post-charge sequence
 * Powers up ADC/DAC analog stages, unmutes signal paths, enables speaker/HP driver.
 */
static const es8311_reg_entry_t s_es8311_init_post_charge[] =
{
    /* Analog Power Up */
    {0x17, 0xBF}, /**< REG17: ADC & DAC analog circuitry power-up, reference buffer enable        */
    {0x0E, 0x02}, /**< REG0E: Modulator & interpolator/decimator filter power-up                  */
    {0x12, 0x00}, /**< REG12: System power-up - activate CSM (Clock State Machine)                */
    {0x14, 0x1A}, /**< REG14: Analog output power control - enable DAC buffer & class-D/AB driver */
    {0x0D, 0x01}, /**< REG0D: Clear power-down bits to wake DAC/ADC digital modulators            */
    {0x15, 0x40}, /**< REG15: Output amplifier power & low-noise bias settings                    */

    /* Digital Processing & Dynamic Range Control (DRC) */
    {0x37, 0x08}, /**< REG37: DAC digital filter configuration & mute/demute slope rate           */
    {0x45, 0x00}, /**< REG45: DAC DRC / limiter control disable or baseline setup                 */

    /* Volume / Path Enable */
    {0x31, 0x00}, /**< REG31: DAC digital mute control (0x00 = unmute DAC channel)                */
};

/*
 * Stage 3: De-initialization / Shutdown sequence
 * Soft mutes output, turns off driver amps, powers down ADC/DAC analog blocks and clocks.
 */
static const es8311_reg_entry_t s_es8311_deinit[] =
{
    /* Soft Mute Outputs */
    {0x31, 0x60}, /**< REG31: DAC digital mute enable (mute DAC, enable soft-ramp to prevent pops) */
    {0x32, 0x00}, /**< REG32: DAC digital volume set to minimum (-95.5 dB)                         */

    /* Power Down Driver & Analog Blocks */
    {0x12, 0x02}, /**< REG12: Stop CSM / place internal state machines into standby                */
    {0x0E, 0xFF}, /**< REG0E: Power down digital modulators, decimation, and interpolation filters */
    {0x13, 0x00}, /**< REG13: Power down internal analog bias current generator                    */
    {0x14, 0x00}, /**< REG14: Power down output amplifier / headphone driver                       */
    {0x17, 0x00}, /**< REG17: Power down DAC and ADC analog circuits                               */
    {0x15, 0x00}, /**< REG15: Power down class-D / analog output stages                            */
    {0x1C, 0x00}, /**< REG1C: Power down microphone bias generator and reference                   */
    {0x45, 0x00}, /**< REG45: Reset DRC control registers                                          */

    /* Power Down Digital System & References (Preserve RST_REG=0 in REG00 so 0x0D=0xFC is retained) */
    {0x0D, 0xFC}, /**< REG0D: Assert power down across all analog & VMID system blocks (<1.0 uA)   */
    {0x00, 0x1E}, /**< REG00: Reset digital/DAC/ADC/CSM blocks, CSM_ON=0, RST_REG=0 (retain regs)  */
    {0x01, 0x00}, /**< REG01: Disable all internal digital clocks (enter ultra-low-power standby)  */
};

/**
 * @brief Volume pct to es8311 reg.
 *
 * @param[in]    pct             Parameter pct.
 *
 * @return Return value of type static inline uint8_t.
 */
static inline uint8_t volume_pct_to_es8311_reg(uint8_t pct)
{
    if (pct > 100) pct = 100;
    return es8311_perceptual_vol_table[pct];
}

static void audio_worker_task(void *pvParameters);
static esp_err_t sub_audio_park_warm(bool enable);

/**
 * @brief Es8311 write reg.
 *
 * @param[in]    reg             Parameter reg.
 * @param[in]    val             Parameter val.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t es8311_write_reg(uint8_t reg, uint8_t val)
{
    uint8_t buf[2] = {reg, val};
    return hal_i2c_write(HAL_I2C_ADDR_ES8311, buf, sizeof(buf), pdMS_TO_TICKS(50));
}

/**
 * @brief Es8311 read reg.
 *
 * @param[in]    reg             Parameter reg.
 * @param[in]    val             Parameter val.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t es8311_read_reg(uint8_t reg, uint8_t *val)
{
    return hal_i2c_write_read(HAL_I2C_ADDR_ES8311, &reg, 1, val, 1, pdMS_TO_TICKS(50));
}

/**
 * @brief Sub audio read chip id.
 *
 * @param[out]   chip_id         Pointer to store 16-bit chip ID.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t sub_audio_read_chip_id(uint16_t *chip_id)
{
    if (chip_id == NULL)
        return ESP_ERR_INVALID_ARG;

    uint8_t id1 = 0, id2 = 0;

    esp_err_t err1 = es8311_read_reg(ES8311_REG_CHIP_ID1, &id1);
    esp_err_t err2 = es8311_read_reg(ES8311_REG_CHIP_ID2, &id2);

    *chip_id = (uint16_t)((id1 << 8) | id2);

    if (err1 != ESP_OK || err2 != ESP_OK || *chip_id != 0x8311) {
        return ESP_ERR_NOT_FOUND;
    }

    return ESP_OK;
}

/**
 * @brief Sub audio flush frame (single zero-frame write serving as valid I2S transfer pipeline indicator).
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t sub_audio_flush_frame(void)
{
    esp_err_t ret = ESP_ERR_INVALID_STATE;
    if (s_audio_inited && s_i2s_chan_enabled) {
        int16_t buffer[FRAME_SIZE];
        memset(buffer, 0x0000, sizeof(buffer));

        size_t buffer_written = 0;
        ret = i2s_channel_write(s_tx_chan, buffer, sizeof(buffer), &buffer_written, pdMS_TO_TICKS(100));
        ret = ((ret == ESP_OK) && (buffer_written == sizeof(buffer))) ? ESP_OK : ESP_ERR_INVALID_STATE;

        /* ~16ms to stream one frame at 16Khz */
        vTaskDelay(pdMS_TO_TICKS(20));
    }
    return ret;
}

/**
 * @brief Poll ES8311 over I2C to confirm Chip ID (0xFD=0x83, 0xFE=0x11) and wait for Chip State Machine (Reg 0xFC bits 6:4) to exit power-down state S0.
 *
 * @param[in]    timeout_ms      Maximum wait time in milliseconds.
 *
 * @return ESP_OK if codec is verified and in active CSM state, or error.
 */
esp_err_t sub_audio_wait_until_ready(uint32_t timeout_ms)
{
    uint16_t chip_id = 0x0000;
    if (sub_audio_read_chip_id(&chip_id) != ESP_OK)
        return ESP_ERR_INVALID_STATE;

    uint32_t elapsed_ms = 0;
    const uint32_t step_ms = 5;
    while (elapsed_ms < timeout_ms) {
        uint8_t flag = 0;
        if (es8311_read_reg(ES8311_REG_FLAG, &flag) == ESP_OK) {
            uint8_t csm_state = (flag >> 4) & 0x07;
            if (csm_state != 0) {
                ESP_LOGD(TAG, "ES8311 CSM active in state S%u after %lu ms", csm_state, (unsigned long)elapsed_ms);
                return ESP_OK;
            }
        }
        vTaskDelay(pdMS_TO_TICKS(step_ms));
        elapsed_ms += step_ms;
    }

    ESP_LOGW(TAG, "ES8311 CSM ready check timed out after %lu ms", (unsigned long)timeout_ms);
    return ESP_ERR_TIMEOUT;
}

/**
 * @brief Quick status check of whether ES8311 codec is ready.
 *
 * @return true if communication and active CSM state verified.
 */
bool sub_audio_is_ready(void)
{
    return (sub_audio_wait_until_ready(10) == ESP_OK);
}

/**
 * @brief Es8311 write table.
 *
 * @param[in]    table           Parameter table.
 * @param[in]    count           Parameter count.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t es8311_write_table(const es8311_reg_entry_t *table, size_t count)
{
    esp_err_t ret = ESP_OK;
    for (size_t i = 0; i < count; i++) {
        ret |= es8311_write_reg(table[i].reg, table[i].val);
    }
    return ret;
}

/**
 * @brief Initialize es8311_init_dac_registers module resources.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t es8311_init_dac_registers(void)
{
    esp_err_t ret = ESP_OK;

    ret |= es8311_write_table(s_es8311_init_pre_charge,
                                sizeof(s_es8311_init_pre_charge) / sizeof(s_es8311_init_pre_charge[0]));

    /* Delay Needed for Internal Analog Frontend Charge Pump */
    vTaskDelay(pdMS_TO_TICKS(35));

    ret |= es8311_write_table(s_es8311_init_post_charge,
                                sizeof(s_es8311_init_post_charge) / sizeof(s_es8311_init_post_charge[0]));

    /* Low Power Mode DOES Affect Audio Quality Marginally */
    ret |= es8311_write_reg(ES8311_REG_SYS_LP_MOD, s_low_power_mode ? 0x80 : 0x00);

    return ret;
}

/**
 * @brief Initialize ES8311 codec and NS4168 amplifier.
 *
 * @details Configures I2S audio bus and sets codec to active run mode.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_audio_init(uint8_t volume_pct)
{
    if (s_audio_inited)
        return ESP_OK;

    audio_cpu_max_acquire();

    /* Disable Class D Audio Amp during codec pre-charge */
    sub_audio_park_warm(true);

    uint16_t chip_id = 0x0000;
    sub_audio_read_chip_id(&chip_id);
    if (chip_id != 0x8311) {
        ESP_LOGE(TAG, "Chip ID NOT Valid (0x%04X)", chip_id);
        s_audio_inited = false;
        audio_cpu_max_release();
        return ESP_ERR_INVALID_VERSION;
    } else {
        ESP_LOGI(TAG, "Chip ID Valid (0x%04X)", chip_id);
    }

    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_0, I2S_ROLE_MASTER);
    chan_cfg.auto_clear        = true;
    chan_cfg.dma_desc_num      = 4;
    chan_cfg.dma_frame_num     = FRAME_SIZE;

    esp_err_t err = i2s_new_channel(&chan_cfg, &s_tx_chan, NULL);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to create I2S TX channel: %s", esp_err_to_name(err));
        audio_cpu_max_release();
        return err;
    }

    i2s_std_config_t std_cfg = {
        .clk_cfg  = I2S_STD_CLK_DEFAULT_CONFIG(16000),
        .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO),
        .gpio_cfg =
            {
                .mclk = HAL_PIN_I2S_MCLK,
                .bclk = HAL_PIN_I2S_SCLK,
                .ws = HAL_PIN_I2S_LRCK,
                .dout = HAL_PIN_I2S_DSDIN,
                .din = I2S_GPIO_UNUSED,
                .invert_flags =
                    {
                        .mclk_inv = false,
                        .bclk_inv = false,
                        .ws_inv = false,
                    },
            },
    };
    std_cfg.clk_cfg.mclk_multiple = I2S_MCLK_MULTIPLE_256;
    std_cfg.slot_cfg.slot_mask    = I2S_STD_SLOT_LEFT;

    err = i2s_channel_init_std_mode(s_tx_chan, &std_cfg);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to init I2S std mode: %s", esp_err_to_name(err));
        i2s_del_channel(s_tx_chan);
        s_tx_chan = NULL;
        audio_cpu_max_release();
        return err;
    }

    err = i2s_channel_enable(s_tx_chan);
    if (err == ESP_OK) {
        s_i2s_chan_enabled = true;
    }
    vTaskDelay(pdMS_TO_TICKS(5));

    err = es8311_init_dac_registers();
    s_codec_in_standby     = false;
    s_rtc_codec_in_standby = false;
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "ES8311 register initialization returned error: %d", err);
    } else {
        ESP_LOGI(TAG, "ES8311 Codec & NS4168 Amp initialized successfully (16kHz Mono, Vol: %u%%)", s_volume_pct);
    }

    if (s_audio_queue == NULL) {
        s_audio_queue = xQueueCreate(8, sizeof(audio_cmd_t));
        if (s_audio_queue != NULL) {
            TaskHandle_t current_task = xTaskGetCurrentTaskHandle();
            BaseType_t res = xTaskCreatePinnedToCore(audio_worker_task,
                                                        "h1os_audio_worker",
                                                        4096,
                                                        (void *)current_task,
                                                        6,
                                                        &s_audio_task_handle,
                                                        tskNO_AFFINITY);
            if (res == pdPASS) {
                if (ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(500)) == 0) {
                    ESP_LOGE(TAG, "Audio worker task startup timeout (>500ms). Deleting orphan task.");
                    vTaskDelete(s_audio_task_handle);
                    s_audio_task_handle = NULL;
                    vQueueDelete(s_audio_queue);
                    s_audio_queue = NULL;
                    audio_cpu_max_release();
                    return ESP_ERR_TIMEOUT;
                }
            } else {
                ESP_LOGE(TAG, "Failed to create audio worker task: %d", res);
                vQueueDelete(s_audio_queue);
                s_audio_queue = NULL;
                audio_cpu_max_release();
                return ESP_ERR_NO_MEM;
            }
        } else {
            audio_cpu_max_release();
            return ESP_ERR_NO_MEM;
        }
    }

    s_audio_inited = true;

    /* Enable Class D Audio Amp (120 ms hardware startup) for zero-latency interactive session tones */
    sub_audio_park_warm(false);
    sub_audio_flush_frame();
    sub_audio_set_volume(volume_pct);

    audio_cpu_max_release();
    return ESP_OK;
}

/**
 * @brief Control NS4168 Class-D amplifier hardware mute state (HAL_PIN_PA_CTRL / GPIO 46).
 *
 * @details NS4168 hardware requires minimum 120 ms startup when unmuting (PA_CTRL -> 1)
 *          and minimum 80 ms shutdown when muting (PA_CTRL -> 0).
 *
 * @param[in]    park_mute       true to mute/shutdown amplifier (PA_CTRL=0, 80ms), false to enable (PA_CTRL=1, 120ms).
 *
 * @return ESP_OK on success.
 */
static esp_err_t sub_audio_park_warm(bool park_mute)
{
    uint32_t target_level = park_mute ? 0U : 1U;
    bool target_enabled   = !park_mute;

    if (s_pa_enabled != target_enabled || (uint32_t)gpio_get_level(HAL_PIN_PA_CTRL) != target_level) {
        gpio_set_level(HAL_PIN_PA_CTRL, target_level);
        s_pa_enabled = target_enabled;

        /* Startup / Shutdown Times Confirmed: 120ms up (target_enabled=true), 80ms down (park_mute=true) */
        vTaskDelay(pdMS_TO_TICKS(target_enabled ? 120 : 80));
    }

    return ESP_OK;
}

/**
 * @brief Put ES8311 codec into ultra-low-power software standby (Reg 0x0D = 0xFC @ <1.0 µA) and pull NS4168 PA_CTRL LOW.
 *
 * @details Keeps power rails on so I2C bus is NOT clamped by unpowered chip protection diodes.
 *          On unattended deep-sleep wakes where the codec is already in verified standby,
 *          bypasses redundant I2C register writes to keep the codec completely undisturbed.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_audio_standby(void)
{
    /* Always ensure NS4168 Class-D amplifier is muted (GPIO 46 = 0, waits 80ms on active->mute transition) */
    sub_audio_park_warm(true);

    if (!s_audio_inited && s_rtc_codec_in_standby && esp_reset_reason() == ESP_RST_DEEPSLEEP) {
        s_codec_in_standby = true;
        return ESP_OK;
    }

    esp_err_t ret = es8311_write_table(s_es8311_deinit,
                                        sizeof(s_es8311_deinit) / sizeof(s_es8311_deinit[0]));

    s_codec_in_standby     = true;
    s_rtc_codec_in_standby = (ret == ESP_OK);

    if (s_tx_chan != NULL && s_i2s_chan_enabled) {
        i2s_channel_disable(s_tx_chan);
        s_i2s_chan_enabled = false;
    }

    return ret;
}

/**
 * @brief Sub audio render tone samples.
 *
 * @param[in]    frequency_hz    Parameter frequency_hz.
 * @param[in]    duration_ms     Parameter duration_ms.
 *
 * @return Return value of type static void.
 */
static void sub_audio_render_tone_samples(uint32_t frequency_hz, uint32_t duration_ms)
{
    const uint32_t sample_rate   = 16000;
    const uint32_t total_samples = (sample_rate * duration_ms) / 1000;
    const uint32_t ramp_samples  = (total_samples > 64) ? 32 : (total_samples / 4);

    int16_t buffer[FRAME_SIZE];
    uint32_t samples_generated = 0;

    float phase      = 0.0f;
    float phase_step = (2.0f * (float)M_PI * (float)frequency_hz) / (float)sample_rate;

    while (samples_generated < total_samples) {
        size_t chunk_size = total_samples - samples_generated;
        if (chunk_size > FRAME_SIZE)
            chunk_size = FRAME_SIZE;

        for (size_t i = 0; i < chunk_size; i++) {
            uint32_t idx = samples_generated + (uint32_t)i;
            float env = 1.0f;
            if (ramp_samples > 0) {
                if (idx < ramp_samples) {
                    env = (float)idx / (float)ramp_samples;
                } else if (idx + ramp_samples >= total_samples) {
                    env = (float)(total_samples - 1 - idx) / (float)ramp_samples;
                }
            }
            buffer[i] = (int16_t)(sinf(phase) * 28000.0f * env);
            phase += phase_step;
            if (phase >= 2.0f * (float)M_PI)
                phase -= 2.0f * (float)M_PI;
        }

        if (chunk_size < FRAME_SIZE) {
            memset(&buffer[chunk_size], 0, (FRAME_SIZE - chunk_size) * sizeof(int16_t));
        }

        size_t bytes_written = 0;
        i2s_channel_write(s_tx_chan, buffer, sizeof(buffer), &bytes_written, pdMS_TO_TICKS(100));
        samples_generated += chunk_size;
    }
}

/**
 * @brief Sub audio render pcm samples.
 *
 * @param[in]    samples         Parameter samples.
 * @param[in]    sample_count    Parameter sample_count.
 *
 * @return Return value of type static void.
 */
static void sub_audio_render_pcm_samples(const int16_t *samples, size_t sample_count)
{
    if (samples == NULL || sample_count == 0)
        return;

    int16_t buffer[FRAME_SIZE];
    size_t samples_sent = 0;
    while (samples_sent < sample_count) {
        size_t chunk = sample_count - samples_sent;
        if (chunk > FRAME_SIZE)
            chunk = FRAME_SIZE;

        memcpy(buffer, &samples[samples_sent], chunk * sizeof(int16_t));
        if (chunk < FRAME_SIZE) {
            memset(&buffer[chunk], 0, (FRAME_SIZE - chunk) * sizeof(int16_t));
        }

        size_t bytes_written = 0;
        i2s_channel_write(s_tx_chan, buffer, sizeof(buffer), &bytes_written, pdMS_TO_TICKS(100));
        samples_sent += chunk;
    }
}

/**
 * @brief Sub audio prepare and unmute.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t sub_audio_prepare_and_unmute(void)
{
    if (!s_audio_inited || s_tx_chan == NULL) {
        esp_err_t err = sub_audio_init(s_volume_pct);
        if (err != ESP_OK)
            return err;
    }

    if (s_tx_chan != NULL && !s_i2s_chan_enabled) {
        esp_err_t chan_err = i2s_channel_enable(s_tx_chan);
        if (chan_err == ESP_OK) {
            s_i2s_chan_enabled = true;
        } else {
            ESP_LOGW(TAG, "i2s_channel_enable failed: %s", esp_err_to_name(chan_err));
        }
    }

    if (s_codec_in_standby) {
        es8311_init_dac_registers();
        s_codec_in_standby     = false;
        s_rtc_codec_in_standby = false;
        sub_audio_set_volume(s_volume_pct);
    }

    /* Enable Class D Audio Amp (waits 120ms if transitioning from muted) */
    sub_audio_park_warm(false);

    return ESP_OK;
}

/**
 * @brief Sub audio exec tone.
 *
 * @param[in]    frequency_hz    Parameter frequency_hz.
 * @param[in]    duration_ms     Parameter duration_ms.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t sub_audio_exec_tone(uint32_t frequency_hz, uint32_t duration_ms)
{
    ESP_LOGI(TAG, "Playing tone: %lu Hz for %lu ms (Vol: %u%%)", (unsigned long)frequency_hz,
             (unsigned long)duration_ms, s_volume_pct);
    esp_err_t ret = sub_audio_prepare_and_unmute();
    if (ret != ESP_OK)
        return ret;

    sub_audio_render_tone_samples(frequency_hz, duration_ms);
    return ESP_OK;
}

/**
 * @brief Sub audio exec pcm.
 *
 * @param[in]    samples         Parameter samples.
 * @param[in]    sample_count    Parameter sample_count.
 * @param[in]    sample_rate_hz  Parameter sample_rate_hz.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t sub_audio_exec_pcm(const int16_t *samples, size_t sample_count, uint32_t sample_rate_hz)
{
    (void)sample_rate_hz;
    esp_err_t ret = sub_audio_prepare_and_unmute();
    if (ret != ESP_OK)
        return ret;

    sub_audio_render_pcm_samples(samples, sample_count);
    return ESP_OK;
}

/**
 * @brief Sub audio exec chime.
 *
 * @param[in]    type            Parameter type.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t sub_audio_exec_chime(uint8_t type)
{
    ESP_LOGI(TAG, "Executing acoustic presentation chime (Type %u)...", type);

    esp_err_t ret = sub_audio_prepare_and_unmute();
    if (ret != ESP_OK)
        return ret;

    switch (type) {
    case H1OS_CHIME_BOOT:
        sub_audio_render_tone_samples(523, 70);
        vTaskDelay(pdMS_TO_TICKS(15));
        sub_audio_render_tone_samples(659, 70);
        vTaskDelay(pdMS_TO_TICKS(15));
        sub_audio_render_tone_samples(784, 70);
        vTaskDelay(pdMS_TO_TICKS(15));
        sub_audio_render_tone_samples(1046, 150);
        break;

    case H1OS_CHIME_SLEEP:
        sub_audio_render_tone_samples(1046, 80);
        vTaskDelay(pdMS_TO_TICKS(15));
        sub_audio_render_tone_samples(784, 80);
        vTaskDelay(pdMS_TO_TICKS(15));
        sub_audio_render_tone_samples(659, 140);
        break;

    case H1OS_CHIME_SHUTDOWN:
        sub_audio_render_tone_samples(784, 90);
        vTaskDelay(pdMS_TO_TICKS(15));
        sub_audio_render_tone_samples(659, 90);
        vTaskDelay(pdMS_TO_TICKS(15));
        sub_audio_render_tone_samples(523, 180);
        break;

    case H1OS_CHIME_ALARM:
        for (int i = 0; i < 2; i++) {
            sub_audio_render_tone_samples(1760, 80);
            vTaskDelay(pdMS_TO_TICKS(10));
            sub_audio_render_tone_samples(880, 80);
            vTaskDelay(pdMS_TO_TICKS(20));
        }
        break;

    default:
        return ESP_ERR_INVALID_ARG;
    }

    return ESP_OK;
}

/**
 * @brief Audio worker task.
 *
 * @param[in]    pvParameters    Parameter pvParameters.
 *
 * @return Return value of type static void.
 */
static void audio_worker_task(void *pvParameters)
{
    TaskHandle_t creator_task = (TaskHandle_t)pvParameters;
    audio_cmd_t cmd;
    ESP_LOGI(TAG, "Audio worker task initialized and active");

    if (creator_task != NULL) {
        xTaskNotifyGive(creator_task);
    }

    while (1) {
        if (xQueueReceive(s_audio_queue, &cmd, portMAX_DELAY) == pdTRUE) {
            s_audio_is_busy = true;
            audio_cpu_max_acquire();

            esp_err_t res = ESP_OK;

            switch (cmd.type) {
            case AUDIO_CMD_TONE:
                res = sub_audio_exec_tone(cmd.params.tone.frequency_hz, cmd.params.tone.duration_ms);
                break;
            case AUDIO_CMD_CHIME:
                res = sub_audio_exec_chime(cmd.params.chime.chime_type);
                break;
            case AUDIO_CMD_PCM:
                res = sub_audio_exec_pcm(cmd.params.pcm.samples, cmd.params.pcm.sample_count, cmd.params.pcm.sample_rate_hz);
                break;
            default:
                res = ESP_ERR_INVALID_ARG;
                break;
            }

            if (uxQueueMessagesWaiting(s_audio_queue) == 0) {
                sub_audio_flush_frame();
            }

            if (cmd.result) {
                *cmd.result = res;
            }

            if (cmd.done_sem) {
                xSemaphoreGive(cmd.done_sem);
            }

            audio_cpu_max_release();
            s_audio_is_busy = false;
        }
    }
}

/**
 * @brief Sub audio send command.
 *
 * @param[in]    cmd             Parameter cmd.
 * @param[in]    is_sync         Parameter is_sync.
 * @param[in]    wait_ms         Parameter wait_ms.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t sub_audio_send_command(const audio_cmd_t *cmd, bool is_sync, uint32_t wait_ms)
{
    if (s_audio_queue == NULL) {
        esp_err_t err = sub_audio_init(s_volume_pct);
        if (err != ESP_OK)
            return err;
    }

    audio_cmd_t local_cmd = *cmd;
    SemaphoreHandle_t sync_sem = NULL;
    esp_err_t exec_result = ESP_OK;

    if (is_sync) {
        sync_sem = xSemaphoreCreateBinary();
        if (sync_sem == NULL)
            return ESP_ERR_NO_MEM;
        local_cmd.done_sem = sync_sem;
        local_cmd.result = &exec_result;
    } else {
        local_cmd.done_sem = NULL;
        local_cmd.result = NULL;
    }

    if (xQueueSend(s_audio_queue, &local_cmd, pdMS_TO_TICKS(wait_ms)) != pdTRUE) {
        if (sync_sem)
            vSemaphoreDelete(sync_sem);
        return ESP_ERR_TIMEOUT;
    }

    if (is_sync) {
        xSemaphoreTake(sync_sem, portMAX_DELAY);
        vSemaphoreDelete(sync_sem);
        return exec_result;
    }

    return ESP_OK;
}

/**
 * @brief Unified asynchronous audio playback dispatcher.
 *
 * @details Enqueues the requested audio command into the background audio worker task.
 *
 * @param[in]    type            Type of playback: SUB_AUDIO_TONE, SUB_AUDIO_CHIME, or SUB_AUDIO_PCM.
 * @param[in]    data            Parameter data.
 * @param[in]    len             Length of data payload in bytes.
 *
 * @return ESP_OK on success, ESP_ERR_TIMEOUT if queue is full, or ESP_ERR_INVALID_ARG.
 */
esp_err_t sub_audio_play(sub_audio_type_t type, const void *data, size_t len)
{
    if (data == NULL)
        return ESP_ERR_INVALID_ARG;

    audio_cmd_t cmd = {0};

    switch (type) {
    case SUB_AUDIO_TONE: {
        const uint32_t *params = (const uint32_t *)data;
        if (len < (2 * sizeof(uint32_t)))
            return ESP_ERR_INVALID_ARG;
        cmd.type = AUDIO_CMD_TONE;
        cmd.params.tone.frequency_hz = params[0];
        cmd.params.tone.duration_ms = params[1];
        break;
    }
    case SUB_AUDIO_CHIME: {
        if (len < 1)
            return ESP_ERR_INVALID_ARG;
        cmd.type = AUDIO_CMD_CHIME;
        cmd.params.chime.chime_type = *(const uint8_t *)data;
        break;
    }
    case SUB_AUDIO_PCM: {
        if (len < sizeof(int16_t))
            return ESP_ERR_INVALID_ARG;
        cmd.type = AUDIO_CMD_PCM;
        cmd.params.pcm.samples = (const int16_t *)data;
        cmd.params.pcm.sample_count = len / sizeof(int16_t);
        cmd.params.pcm.sample_rate_hz = 16000;
        break;
    }
    default:
        return ESP_ERR_INVALID_ARG;
    }

    return sub_audio_send_command(&cmd, false, 50);
}

/**
 * @brief Check if audio playback is currently active or queue has pending items.
 *
 * @return true if playing or queued, false if idle in standby.
 */
bool sub_audio_is_busy(void)
{
    if (s_audio_is_busy)
        return true;

    if (s_audio_queue && uxQueueMessagesWaiting(s_audio_queue) > 0)
        return true;

    return false;
}

/**
 * @brief Wait until background audio worker completes all playback and enters standby.
 *
 * @param[in]    timeout_ms      Maximum time to wait in milliseconds.
 *
 * @return ESP_OK if idle, ESP_ERR_TIMEOUT if still active.
 */
esp_err_t sub_audio_wait_idle(uint32_t timeout_ms)
{
    uint32_t elapsed = 0;
    while (sub_audio_is_busy() && elapsed < timeout_ms) {
        vTaskDelay(pdMS_TO_TICKS(10));
        elapsed += 10;
    }
    return sub_audio_is_busy() ? ESP_ERR_TIMEOUT : ESP_OK;
}

/**
 * @brief Teardown audio subsystem, stop background worker task, and delete I2S channel.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_audio_deinit(void)
{
    sub_audio_standby();

    if (s_tx_chan != NULL) {
        if (s_i2s_chan_enabled) {
            i2s_channel_disable(s_tx_chan);
            s_i2s_chan_enabled = false;
        }
        i2s_del_channel(s_tx_chan);
        s_tx_chan = NULL;
    }

    if (s_audio_task_handle != NULL) {
        vTaskDelete(s_audio_task_handle);
        s_audio_task_handle = NULL;
    }

    if (s_audio_queue != NULL) {
        vQueueDelete(s_audio_queue);
        s_audio_queue = NULL;
    }

#if CONFIG_PM_ENABLE
    if (s_audio_pm_lock != NULL) {
        esp_pm_lock_delete(s_audio_pm_lock);
        s_audio_pm_lock = NULL;
    }
#endif

    s_audio_inited = false;
    return ESP_OK;
}

/**
 * @brief Set ES8311 DAC output volume percentage (0% = Mute, 100% = 0 dB full-scale).
 *
 * @details Persists across standby/wake cycles.
 *
 * @param[in]    volume_pct      Volume percentage (0 - 100).
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_audio_set_volume(uint8_t volume_pct)
{
    if (volume_pct > 100) volume_pct = 100;
    s_volume_pct = volume_pct;

    if (s_audio_inited && s_i2s_chan_enabled) {
        uint8_t vol_reg = volume_pct_to_es8311_reg(s_volume_pct);
        es8311_write_reg(ES8311_REG_DAC_VOL, vol_reg);
        ESP_LOGI(TAG, "Volume set to %d [0x%2X]", volume_pct, vol_reg);
    }
    return ESP_OK;
}

/**
 * @brief Get currently configured output volume percentage (0 - 100).
 *
 * @return Current volume percentage.
 */
uint8_t sub_audio_get_volume(void)
{
    return s_volume_pct;
}

/**
 * @brief Configure ES8311 DAC power mode (Low-Power vs Normal).
 *
 * @details In low-power mode (default upon init), ES8311 operates with LPDAC enabled (Reg 0x0F bit 7 = 1), significantly reducing active DAC bias current. Normal mode provides standard bias.
 *
 * @param[in]    enable          true for Low-Power Mode (default), false for Normal Power Mode.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_audio_set_low_power_mode(bool enable)
{
    s_low_power_mode = enable;
    if (s_audio_inited && s_i2s_chan_enabled) {
        return es8311_write_reg(ES8311_REG_SYS_LP_MOD, enable ? 0x80 : 0x00);
    }
    return ESP_OK;
}

/**
 * @brief Query whether audio subsystem is in Low-Power Mode.
 *
 * @return true if Low-Power Mode is active, false if Normal Power Mode.
 */
bool sub_audio_get_low_power_mode(void)
{
    return s_low_power_mode;
}
