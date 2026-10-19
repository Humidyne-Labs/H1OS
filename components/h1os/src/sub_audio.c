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
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "h1os/h1os.h"
#include "h1os/hal_i2c.h"
#include "h1os/hal_types.h"
#include "h1os/sub_power.h"

#include <math.h>
#include <string.h>

static const char *TAG = "sub_audio";

#define ES8311_REG_RESET 0x00
#define ES8311_REG_SYS_PWR_ANA 0x0D
#define ES8311_REG_SYS_LP_MOD 0x0F
#define ES8311_REG_DAC_PWR 0x12
#define ES8311_REG_DAC_VOL 0x32
#define ES8311_REG_FLAG 0xFC
#define ES8311_REG_CHIP_ID1 0xFD
#define ES8311_REG_CHIP_ID2 0xFE

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

static i2s_chan_handle_t s_tx_chan = NULL;

static bool s_audio_inited = false;
static bool s_i2s_chan_enabled = false;
static bool s_codec_in_standby = false;

static bool s_low_power_mode = true;

static QueueHandle_t s_audio_queue = NULL;
static TaskHandle_t s_audio_task_handle = NULL;
static volatile bool s_audio_is_busy = false;

static uint8_t s_volume_pct = 0;

static const uint8_t es8311_perceptual_vol_table[101] = {
    0x00, 0x3A, 0x48, 0x51, 0x57, 0x5D, 0x61, 0x65, 0x68, 0x6B, 0x6E, 0x71, 0x73, 0x75, 0x77, 0x79, 0x7B,
    0x7D, 0x7E, 0x80, 0x81, 0x83, 0x84, 0x85, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90,
    0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9E, 0x9F,
    0xA0, 0xA1, 0xA2, 0xA2, 0xA3, 0xA4, 0xA5, 0xA5, 0xA6, 0xA7, 0xA8, 0xA8, 0xA9, 0xAA, 0xAA, 0xAB, 0xAC,
    0xAC, 0xAD, 0xAE, 0xAE, 0xAF, 0xB0, 0xB0, 0xB1, 0xB2, 0xB2, 0xB3, 0xB3, 0xB4, 0xB5, 0xB5, 0xB6, 0xB6,
    0xB7, 0xB7, 0xB8, 0xB9, 0xB9, 0xBA, 0xBA, 0xBB, 0xBC, 0xBC, 0xBD, 0xBD, 0xBE, 0xBE, 0xBF, 0xBF};

static inline uint8_t volume_pct_to_es8311_reg(uint8_t pct)
{
    if (pct > 100)
        pct = 100;
    return es8311_perceptual_vol_table[pct];
}

static void audio_worker_task(void *pvParameters);
static void sub_audio_park_warm(void);

static esp_err_t es8311_write_reg(uint8_t reg, uint8_t val)
{
    uint8_t buf[2] = {reg, val};
    return hal_i2c_write(HAL_I2C_ADDR_ES8311, buf, sizeof(buf), pdMS_TO_TICKS(50));
}

static esp_err_t es8311_read_reg(uint8_t reg, uint8_t *val)
{
    return hal_i2c_write_read(HAL_I2C_ADDR_ES8311, &reg, 1, val, 1, pdMS_TO_TICKS(50));
}

static esp_err_t sub_audio_read_chip_id(uint16_t *chip_id)
{
    if (s_tx_chan != NULL && !s_i2s_chan_enabled)
        return ESP_ERR_INVALID_STATE;

    uint8_t id1 = 0, id2 = 0;

    esp_err_t err1 = es8311_read_reg(ES8311_REG_CHIP_ID1, &id1);
    esp_err_t err2 = es8311_read_reg(ES8311_REG_CHIP_ID2, &id2);

    *chip_id = (id1 << 8) | id2;

    if (err1 != ESP_OK || err2 != ESP_OK || *chip_id != 0x8311) {
        return ESP_ERR_NOT_FOUND;
    }

    return ESP_OK;
}

static esp_err_t sub_audio_flush_frame(void)
{
    esp_err_t ret = ESP_OK;
    int16_t postroll[FRAME_SIZE] = {0};
    size_t postroll_written = 0;
    ret = i2s_channel_write(s_tx_chan, postroll, sizeof(postroll), &postroll_written, pdMS_TO_TICKS(100));
    ret = ((ret == ESP_OK) && (postroll_written == sizeof(postroll))) ? ESP_OK : ESP_ERR_INVALID_STATE;
    vTaskDelay(pdMS_TO_TICKS(20));
    return ret;
}

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

bool sub_audio_is_ready(void)
{
    return (sub_audio_wait_until_ready(10) == ESP_OK);
}

typedef struct {
    uint8_t reg;
    uint8_t val;
} es8311_reg_entry_t;

static const es8311_reg_entry_t s_es8311_init_pre_charge[] = {

    {0x44, 0x08},
    {0x44, 0x08},

    {0x0D, 0xFA},

    {0x01, 0x30},
    {0x02, 0x00},
    {0x03, 0x10},
    {0x16, 0x24},
    {0x04, 0x20},
    {0x05, 0x00},
    {0x0B, 0x00},
    {0x0C, 0x00},

    {0x10, 0x1F},
    {0x11, 0x7F},

    {0x00, 0x80},
    {0x01, 0x3F},
    {0x06, 0x03},
    {0x07, 0x00},
    {0x08, 0xFF},

    {0x13, 0x10},
    {0x1B, 0x0A},
    {0x1C, 0x6A},
    {0x44, 0x58},

    {0x09, 0x0C},
    {0x0A, 0x0C},
};

static const es8311_reg_entry_t s_es8311_init_post_charge[] = {

    {0x17, 0xBF},
    {0x0E, 0x02},
    {0x12, 0x00},
    {0x14, 0x1A},
    {0x0D, 0x01},
    {0x15, 0x40},

    {0x37, 0x08},
    {0x45, 0x00},

    {0x31, 0x00},
};

static esp_err_t es8311_write_table(const es8311_reg_entry_t *table, size_t count)
{
    esp_err_t ret = ESP_OK;
    for (size_t i = 0; i < count; i++) {
        ret |= es8311_write_reg(table[i].reg, table[i].val);
    }
    return ret;
}

static esp_err_t es8311_init_dac_registers(void)
{
    esp_err_t ret = ESP_OK;

    ret |= es8311_write_table(s_es8311_init_pre_charge,
                              sizeof(s_es8311_init_pre_charge) / sizeof(s_es8311_init_pre_charge[0]));

    vTaskDelay(pdMS_TO_TICKS(35));

    ret |= es8311_write_table(s_es8311_init_post_charge,
                              sizeof(s_es8311_init_post_charge) / sizeof(s_es8311_init_post_charge[0]));

    ret |= es8311_write_reg(0x0F, s_low_power_mode ? 0x80 : 0x00);

    return ret;
}

esp_err_t sub_audio_init(void)
{
    if (s_audio_inited)
        return ESP_OK;

    sub_power_cpu_max_acquire();

    sub_audio_park_warm();

    uint16_t chip_id = 0x0000;
    sub_audio_read_chip_id(&chip_id);
    if (chip_id != 0x8311) {
        ESP_LOGE(TAG, "Chip ID NOT Valid (0x%04X)", chip_id);
        s_audio_inited = false;
        sub_power_cpu_max_release();
        return ESP_ERR_INVALID_VERSION;
    } else {
        ESP_LOGI(TAG, "Chip ID Valid (0x%04X)", chip_id);
    }

    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_0, I2S_ROLE_MASTER);
    chan_cfg.auto_clear = true;
    chan_cfg.dma_desc_num = 4;
    chan_cfg.dma_frame_num = FRAME_SIZE;

    esp_err_t err = i2s_new_channel(&chan_cfg, &s_tx_chan, NULL);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to create I2S TX channel: %s", esp_err_to_name(err));
        sub_power_cpu_max_release();
        return err;
    }

    i2s_std_config_t std_cfg = {
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(16000),
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
    std_cfg.slot_cfg.slot_mask = I2S_STD_SLOT_LEFT;

    err = i2s_channel_init_std_mode(s_tx_chan, &std_cfg);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to init I2S std mode: %s", esp_err_to_name(err));
        i2s_del_channel(s_tx_chan);
        s_tx_chan = NULL;
        sub_power_cpu_max_release();
        return err;
    }

    err = i2s_channel_enable(s_tx_chan);
    if (err == ESP_OK) {
        s_i2s_chan_enabled = true;
    }
    vTaskDelay(pdMS_TO_TICKS(5));

    err = es8311_init_dac_registers();
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "ES8311 register initialization returned error: %d", err);
    } else {
        ESP_LOGI(TAG, "ES8311 Codec & NS4168 Amp initialized successfully (16kHz Mono, Vol: %u%%)", s_volume_pct);
    }

    uint8_t vol_reg = volume_pct_to_es8311_reg(s_volume_pct);
    es8311_write_reg(0x32, vol_reg);
    es8311_write_reg(0x31, (s_volume_pct == 0) ? 0x60 : 0x00);

    sub_audio_flush_frame();

    if (s_audio_queue == NULL) {
        s_audio_queue = xQueueCreate(8, sizeof(audio_cmd_t));
        if (s_audio_queue != NULL) {
            TaskHandle_t current_task = xTaskGetCurrentTaskHandle();
            BaseType_t res = xTaskCreatePinnedToCore(audio_worker_task, "h1os_audio_worker", 4096, (void *)current_task,
                                                     6, &s_audio_task_handle, tskNO_AFFINITY);
            if (res == pdPASS) {
                if (ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(500)) == 0) {
                    ESP_LOGE(TAG, "Audio worker task startup timeout (>500ms). Deleting orphan task.");
                    vTaskDelete(s_audio_task_handle);
                    s_audio_task_handle = NULL;
                    vQueueDelete(s_audio_queue);
                    s_audio_queue = NULL;
                    sub_power_cpu_max_release();
                    return ESP_ERR_TIMEOUT;
                }
            } else {
                ESP_LOGE(TAG, "Failed to create audio worker task: %d", res);
                vQueueDelete(s_audio_queue);
                s_audio_queue = NULL;
                sub_power_cpu_max_release();
                return ESP_ERR_NO_MEM;
            }
        } else {
            sub_power_cpu_max_release();
            return ESP_ERR_NO_MEM;
        }
    }

    sub_power_cpu_max_release();
    s_audio_inited = true;
    return ESP_OK;
}

static void sub_audio_park_warm(void)
{
    gpio_set_level(HAL_PIN_PA_CTRL, 0);
    vTaskDelay(pdMS_TO_TICKS(25));
}

esp_err_t sub_audio_standby(void)
{
    gpio_set_level(HAL_PIN_PA_CTRL, 0);

    vTaskDelay(pdMS_TO_TICKS(25));

    es8311_write_reg(0x31, 0x60);
    es8311_write_reg(0x32, 0x00);

    es8311_write_reg(0x12, 0x02);
    es8311_write_reg(0x0E, 0xFF);
    es8311_write_reg(0x14, 0x00);
    es8311_write_reg(0x17, 0x00);
    es8311_write_reg(0x15, 0x00);
    es8311_write_reg(0x45, 0x00);

    es8311_write_reg(0x0D, 0xFC);

    es8311_write_reg(0x00, 0x1F);
    es8311_write_reg(0x01, 0x00);

    s_codec_in_standby = true;

    if (s_tx_chan != NULL && s_i2s_chan_enabled) {
        i2s_channel_disable(s_tx_chan);
        s_i2s_chan_enabled = false;
    }

    return ESP_OK;
}

static void sub_audio_render_tone_samples(uint32_t frequency_hz, uint32_t duration_ms)
{
    const uint32_t sample_rate = 16000;
    const uint32_t total_samples = (sample_rate * duration_ms) / 1000;
    const uint32_t ramp_samples = (total_samples > 64) ? 32 : (total_samples / 4);

    int16_t buffer[FRAME_SIZE];
    uint32_t samples_generated = 0;

    float phase = 0.0f;
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

static esp_err_t sub_audio_prepare_and_unmute(void)
{
    if (!s_audio_inited || s_tx_chan == NULL) {
        esp_err_t err = sub_audio_init();
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

    if (gpio_get_level(HAL_PIN_PA_CTRL) == 0) {
        gpio_set_level(HAL_PIN_PA_CTRL, 1);
        vTaskDelay(pdMS_TO_TICKS(50));
    }

    return ESP_OK;
}

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

static esp_err_t sub_audio_exec_pcm(const int16_t *samples, size_t sample_count, uint32_t sample_rate_hz)
{
    (void)sample_rate_hz;
    esp_err_t ret = sub_audio_prepare_and_unmute();
    if (ret != ESP_OK)
        return ret;

    sub_audio_render_pcm_samples(samples, sample_count);
    return ESP_OK;
}

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
            sub_power_cpu_max_acquire();

            esp_err_t res = ESP_OK;

            switch (cmd.type) {
            case AUDIO_CMD_TONE:
                res = sub_audio_exec_tone(cmd.params.tone.frequency_hz, cmd.params.tone.duration_ms);
                break;
            case AUDIO_CMD_CHIME:
                res = sub_audio_exec_chime(cmd.params.chime.chime_type);
                break;
            case AUDIO_CMD_PCM:
                res = sub_audio_exec_pcm(cmd.params.pcm.samples, cmd.params.pcm.sample_count,
                                         cmd.params.pcm.sample_rate_hz);
                break;
            }

            if (cmd.result) {
                *cmd.result = res;
            }

            if (cmd.done_sem) {
                xSemaphoreGive(cmd.done_sem);
            }

            sub_power_cpu_max_release();
            s_audio_is_busy = false;
        }
    }
}

static esp_err_t sub_audio_send_command(const audio_cmd_t *cmd, bool is_sync, uint32_t wait_ms)
{
    if (s_audio_queue == NULL) {
        esp_err_t err = sub_audio_init();
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

esp_err_t sub_audio_play(sub_audio_type_t type, const void *data, size_t len)
{
    if (data == NULL)
        return ESP_ERR_INVALID_ARG;

    audio_cmd_t cmd = {0};

    switch (type) {
    case SUB_AUDIO_TONE: {
        const uint32_t *params = (const uint32_t *)data;
        if (len < 2 && len < (2 * sizeof(uint32_t)))
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
        if (len == 0)
            return ESP_ERR_INVALID_ARG;
        cmd.type = AUDIO_CMD_PCM;
        cmd.params.pcm.samples = (const int16_t *)data;
        cmd.params.pcm.sample_count = len;
        cmd.params.pcm.sample_rate_hz = 16000;
        break;
    }
    default:
        return ESP_ERR_INVALID_ARG;
    }

    return sub_audio_send_command(&cmd, false, 50);
}

bool sub_audio_is_busy(void)
{
    if (s_audio_is_busy)
        return true;
    if (s_audio_queue && uxQueueMessagesWaiting(s_audio_queue) > 0)
        return true;
    return false;
}

esp_err_t sub_audio_wait_idle(uint32_t timeout_ms)
{
    uint32_t elapsed = 0;
    while (sub_audio_is_busy() && elapsed < timeout_ms) {
        vTaskDelay(pdMS_TO_TICKS(10));
        elapsed += 10;
    }
    return sub_audio_is_busy() ? ESP_ERR_TIMEOUT : ESP_OK;
}

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

    s_audio_inited = false;
    return ESP_OK;
}

esp_err_t sub_audio_set_volume(uint8_t volume_pct)
{
    if (volume_pct > 100)
        volume_pct = 100;
    s_volume_pct = volume_pct;

    if (s_audio_inited && s_i2s_chan_enabled) {
        uint8_t vol_reg = volume_pct_to_es8311_reg(s_volume_pct);
        es8311_write_reg(ES8311_REG_DAC_VOL, vol_reg);
    }
    return ESP_OK;
}

uint8_t sub_audio_get_volume(void)
{
    return s_volume_pct;
}

esp_err_t sub_audio_set_low_power_mode(bool enable)
{
    s_low_power_mode = enable;
    if (s_audio_inited && s_i2s_chan_enabled) {
        return es8311_write_reg(ES8311_REG_SYS_LP_MOD, enable ? 0x80 : 0x00);
    }
    return ESP_OK;
}

bool sub_audio_get_low_power_mode(void)
{
    return s_low_power_mode;
}
