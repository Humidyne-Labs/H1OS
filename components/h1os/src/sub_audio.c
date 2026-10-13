/**
 * @file sub_audio.c
 * @brief Layer 2: ES8311 Codec & NS4168 Audio Implementation
 *
 * SPDX-License-Identifier: MIT
 */

#include "h1os/sub_audio.h"
#include "h1os/hal_i2c.h"
#include "h1os/hal_types.h"
#include "driver/gpio.h"
#include "driver/i2s_std.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include <math.h>

static const char *TAG = "sub_audio";

#define ES8311_REG_RESET        0x00
#define ES8311_REG_SYS_PWR_ANA  0x0D
#define ES8311_REG_DAC_PWR      0x12
#define ES8311_REG_DAC_VOL      0x32
#define ES8311_REG_FLAG         0xFC  /* Read-only status flag: Bits 6:4 = FLAG_CSM_CHIP */
#define ES8311_REG_CHIP_ID1     0xFD  /* Expected: 0x83 */
#define ES8311_REG_CHIP_ID2     0xFE  /* Expected: 0x11 */

/* Audio Worker Command Types */
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
    SemaphoreHandle_t done_sem; /* Set for synchronous caller, NULL for async */
    esp_err_t        *result;   /* Pointer to store execution result */
} audio_cmd_t;

static i2s_chan_handle_t s_tx_chan = NULL;
static bool s_audio_inited = false;
static bool s_i2s_chan_enabled = false;
static QueueHandle_t     s_audio_queue       = NULL;
static TaskHandle_t      s_audio_task_handle = NULL;
static volatile bool     s_audio_is_busy     = false;
static uint8_t           s_volume_pct        = 50; /* Default 50% perceptual volume */

/*
 * Perceptual Volume Lookup Table (0% to 100%)
 * Maps 0%-100% input to Register 0x32 values using a logarithmic scale:
 *   - 100% = 191 (0xBF) ->   0.0 dB (Unity Gain / Max Unclipped)
 *   -   1% =  58 (0x3A) -> -66.5 dB (Barely audible)
 *   -   0% =   0 (0x00) -> -95.5 dB (Digital Mute)
 */
static const uint8_t es8311_perceptual_vol_table[101] = {
    0x00, 0x3A, 0x48, 0x51, 0x57, 0x5D, 0x61, 0x65, 0x68, 0x6B, //  0% -  9%
    0x6E, 0x71, 0x73, 0x75, 0x77, 0x79, 0x7B, 0x7D, 0x7E, 0x80, // 10% - 19%
    0x81, 0x83, 0x84, 0x85, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, // 20% - 29%
    0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, // 30% - 39%
    0x97, 0x98, 0x99, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9E, // 40% - 49%
    0x9F, 0xA0, 0xA1, 0xA2, 0xA2, 0xA3, 0xA4, 0xA5, 0xA5, 0xA6, // 50% - 59%
    0xA7, 0xA8, 0xA8, 0xA9, 0xAA, 0xAA, 0xAB, 0xAC, 0xAC, 0xAD, // 60% - 69%
    0xAE, 0xAE, 0xAF, 0xB0, 0xB0, 0xB1, 0xB2, 0xB2, 0xB3, 0xB3, // 70% - 79%
    0xB4, 0xB5, 0xB5, 0xB6, 0xB6, 0xB7, 0xB7, 0xB8, 0xB9, 0xB9, // 80% - 89%
    0xBA, 0xBA, 0xBB, 0xBC, 0xBC, 0xBD, 0xBD, 0xBE, 0xBE, 0xBF, // 90% - 99%
    0xBF                                                       // 100%
};

static inline uint8_t volume_pct_to_es8311_reg(uint8_t pct)
{
    if (pct > 100) pct = 100;
    return es8311_perceptual_vol_table[pct];
}

/* Forward declaration */
static void audio_worker_task(void *pvParameters);

static esp_err_t es8311_write_reg(uint8_t reg, uint8_t val)
{
    uint8_t buf[2] = { reg, val };
    return hal_i2c_write(HAL_I2C_ADDR_ES8311, buf, sizeof(buf), pdMS_TO_TICKS(50));
}

static esp_err_t es8311_read_reg(uint8_t reg, uint8_t *val)
{
    return hal_i2c_write_read(HAL_I2C_ADDR_ES8311, &reg, 1, val, 1, pdMS_TO_TICKS(50));
}

esp_err_t sub_audio_wait_until_ready(uint32_t timeout_ms)
{
    uint8_t id1 = 0, id2 = 0;
    esp_err_t err1 = es8311_read_reg(ES8311_REG_CHIP_ID1, &id1);
    esp_err_t err2 = es8311_read_reg(ES8311_REG_CHIP_ID2, &id2);
    if (err1 != ESP_OK || err2 != ESP_OK || id1 != 0x83 || id2 != 0x11) {
        ESP_LOGE(TAG, "ES8311 Chip ID validation failed (0x%02X, 0x%02X)", id1, id2);
        return ESP_ERR_NOT_FOUND;
    }

    uint32_t elapsed_ms = 0;
    const uint32_t step_ms = 5;
    while (elapsed_ms < timeout_ms) {
        uint8_t flag = 0;
        if (es8311_read_reg(ES8311_REG_FLAG, &flag) == ESP_OK) {
            uint8_t csm_state = (flag >> 4) & 0x07; /* Bits 6:4 = FLAG_CSM_CHIP */
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

static esp_err_t es8311_init_dac_registers(void)
{
    esp_err_t ret = ESP_OK;

    /* 1. Wake chip and set low-power analog baseline */
    ret |= es8311_write_reg(0x0D, 0xFA);

    /* 2. Silicon errata I2C noise immunity (written twice) */
    ret |= es8311_write_reg(0x44, 0x08);
    ret |= es8311_write_reg(0x44, 0x08);

    /* 3. Clock tree & reference biasing */
    ret |= es8311_write_reg(0x01, 0x30);
    ret |= es8311_write_reg(0x02, 0x00);
    ret |= es8311_write_reg(0x03, 0x10);
    ret |= es8311_write_reg(0x16, 0x24); /* ADC gain scale */
    ret |= es8311_write_reg(0x04, 0x10);
    ret |= es8311_write_reg(0x05, 0x00);
    ret |= es8311_write_reg(0x0B, 0x00);
    ret |= es8311_write_reg(0x0C, 0x00);
    ret |= es8311_write_reg(0x10, 0x1F); /* Reg 0x10: Analog bias generator adjust */
    ret |= es8311_write_reg(0x11, 0x7F); /* Reg 0x11: Internal VMID buffer impedance */
    ret |= es8311_write_reg(0x00, 0x80); /* CSM power on */

    /* 4. Slave mode & MCLK selection */
    ret |= es8311_write_reg(0x00, 0x80); /* Slave mode (MSC = 0, CSM_ON = 1) */
    ret |= es8311_write_reg(0x01, 0x3F); /* Use MCLK pin, all clocks on */
    ret |= es8311_write_reg(0x06, 0x00); /* Normal SCLK polarity */
    ret |= es8311_write_reg(0x13, 0x10); /* Internal reference bias */
    ret |= es8311_write_reg(0x1B, 0x0A);
    ret |= es8311_write_reg(0x1C, 0x6A);
    ret |= es8311_write_reg(0x44, 0x58); /* Internal reference signal routing */

    /* 5. 16-bit 16kHz Philips I2S Sample Rate & Clock Dividers */
    ret |= es8311_write_reg(0x09, 0x0C); /* 16-bit Philips I2S, SDP in unmute */
    ret |= es8311_write_reg(0x0A, 0x0C); /* SDP out unmute */
    ret |= es8311_write_reg(0x02, 0x00); /* Pre-divider = 1, Pre-multiplier = 1 */
    ret |= es8311_write_reg(0x05, 0x00); /* ADC/DAC clock dividers = 1 */
    ret |= es8311_write_reg(0x03, 0x10); /* Single speed, ADC OSR */
    ret |= es8311_write_reg(0x04, 0x20); /* DAC OSR = 0x20 for 16kHz Fs */
    ret |= es8311_write_reg(0x07, 0x00); /* Master LRCK divider high byte */
    ret |= es8311_write_reg(0x08, 0xFF); /* Master LRCK divider low byte */
    ret |= es8311_write_reg(0x06, 0x03); /* BCLK divider = 4 (reg value 3) */

    /* 6. Power on DAC and Analog Blocks */
    ret |= es8311_write_reg(0x00, 0x80);
    ret |= es8311_write_reg(0x01, 0x3F);
    ret |= es8311_write_reg(0x09, 0x0C);
    ret |= es8311_write_reg(0x0A, 0x0C);
    ret |= es8311_write_reg(0x17, 0xBF);
    ret |= es8311_write_reg(0x0E, 0x02); /* Analog blocks power on / VROI */
    ret |= es8311_write_reg(0x12, 0x00); /* DAC analog power ON (PDN_DAC = 0) */
    ret |= es8311_write_reg(0x14, 0x1A);
    ret |= es8311_write_reg(0x0D, 0x01); /* Analog reference & normal VMID */
    ret |= es8311_write_reg(0x15, 0x40);
    ret |= es8311_write_reg(0x37, 0x08);
    ret |= es8311_write_reg(0x45, 0x00);

    /* 7. Volume and Unmute (using configured s_volume_pct) */
    uint8_t vol_reg = volume_pct_to_es8311_reg(s_volume_pct);
    ret |= es8311_write_reg(0x32, vol_reg);
    ret |= es8311_write_reg(0x31, (s_volume_pct == 0) ? 0x60 : 0x00); /* Unmute DAC DSM/DEM if vol > 0 */

    return ret;
}

esp_err_t sub_audio_init(void)
{
    if (s_audio_inited) return ESP_OK;

    /* 1. Ensure Power Rail (GPIO 42: 0 = Power ON) & PA CTRL (GPIO 46: 0 = Mute) are at correct levels */
    gpio_set_level(HAL_PIN_PA_EN, 0);   /* Rail MUST stay ON (0) to prevent I2C clamping */
    gpio_set_level(HAL_PIN_PA_CTRL, 0); /* Keep amplifier muted initially */
    vTaskDelay(pdMS_TO_TICKS(15));

    /* 2. Probe ES8311 silicon over I2C */
    uint8_t chip_id_reg = 0xFD;
    uint8_t chip_id[2] = {0};
    esp_err_t err = hal_i2c_write_read(HAL_I2C_ADDR_ES8311, &chip_id_reg, 1, chip_id, 2, 50);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "ES8311 Codec I2C Probe: Detected Chip ID 0x%02X%02X (Expected: 0x8311)", chip_id[0], chip_id[1]);
    } else {
        ESP_LOGW(TAG, "ES8311 Codec I2C Probe failed (%s) - attempting init anyway", esp_err_to_name(err));
    }

    /* 3. Configure I2S TX Channel (16-bit 16kHz Philips Master with MCLK) */
    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_0, I2S_ROLE_MASTER);
    chan_cfg.auto_clear   = true;
    chan_cfg.dma_desc_num = 4;
    chan_cfg.dma_frame_num = 256;

    err = i2s_new_channel(&chan_cfg, &s_tx_chan, NULL);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to create I2S TX channel: %s", esp_err_to_name(err));
        return err;
    }

    i2s_std_config_t std_cfg = {
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(16000),
        .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO),
        .gpio_cfg = {
            .mclk = HAL_PIN_I2S_MCLK,
            .bclk = HAL_PIN_I2S_SCLK,
            .ws   = HAL_PIN_I2S_LRCK,
            .dout = HAL_PIN_I2S_DSDIN,
            .din  = I2S_GPIO_UNUSED,
            .invert_flags = {
                .mclk_inv = false,
                .bclk_inv = false,
                .ws_inv   = false,
            },
        },
    };
    std_cfg.clk_cfg.mclk_multiple = I2S_MCLK_MULTIPLE_256; /* 16 kHz * 256 = 4.096 MHz required for ES8311 PLL */
    std_cfg.slot_cfg.slot_mask    = I2S_STD_SLOT_LEFT;

    err = i2s_channel_init_std_mode(s_tx_chan, &std_cfg);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to init I2S std mode: %s", esp_err_to_name(err));
        i2s_del_channel(s_tx_chan);
        s_tx_chan = NULL;
        return err;
    }

    /* 4. Enable I2S channel to supply MCLK/BCLK during codec register setup */
    err = i2s_channel_enable(s_tx_chan);
    if (err == ESP_OK) {
        s_i2s_chan_enabled = true;
    }
    vTaskDelay(pdMS_TO_TICKS(5));

    /* 5. Initialize complete 22-register ES8311 clock tree and DAC */
    err = es8311_init_dac_registers();
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "ES8311 register initialization returned error: %d", err);
    } else {
        ESP_LOGI(TAG, "ES8311 Codec & NS4168 Amp initialized successfully (16kHz Mono, Vol: %u%%)", s_volume_pct);
    }

    /* 6. Spawn audio background worker task and command queue */
    if (s_audio_queue == NULL) {
        s_audio_queue = xQueueCreate(8, sizeof(audio_cmd_t));
        if (s_audio_queue != NULL) {
            xTaskCreatePinnedToCore(
                audio_worker_task,
                "h1os_audio_worker",
                4096,
                NULL,
                4,
                &s_audio_task_handle,
                1
            );
        }
    }

    s_audio_inited = true;

    /* 7. Enter quiet standby immediately so amplifier and I2S clocks stay silent/quiescent */
    sub_audio_standby();

    return ESP_OK;
}

esp_err_t sub_audio_standby(void)
{
    /* 1. Mute external amplifier immediately */
    gpio_set_level(HAL_PIN_PA_CTRL, 0);

    /* 2. Soft-mute DAC DSM */
    es8311_write_reg(0x31, 0x60);
    vTaskDelay(pdMS_TO_TICKS(5));

    /* 3. Full zero-heat silicon suspension (<1.0 µA) per reference es8311_suspend() */
    es8311_write_reg(0x32, 0x00); /* Mute volume */
    es8311_write_reg(0x17, 0x00);
    es8311_write_reg(0x0E, 0xFF); /* Power down PGA & ADC Modulator */
    es8311_write_reg(0x12, 0x02); /* Power down DAC output stage */
    es8311_write_reg(0x14, 0x00); /* Power down ADC */
    es8311_write_reg(0x0D, 0xFA);
    es8311_write_reg(0x15, 0x00);
    es8311_write_reg(0x02, 0x10);
    es8311_write_reg(0x00, 0x00);
    es8311_write_reg(0x00, 0x1F); /* Assert digital reset */
    es8311_write_reg(0x01, 0x30);
    es8311_write_reg(0x01, 0x00); /* Gate all clocks */
    es8311_write_reg(0x45, 0x00);
    es8311_write_reg(0x0D, 0xFC); /* Completely power down analog references & VMID */
    es8311_write_reg(0x02, 0x00);

    /* 4. Disable active I2S clock oscillation to stop digital switching dissipation */
    if (s_tx_chan != NULL && s_i2s_chan_enabled) {
        i2s_channel_disable(s_tx_chan);
        s_i2s_chan_enabled = false;
    }

    return ESP_OK;
}


/* Internal helper: clean teardown sequence per ES8311 hardware spec */
static void sub_audio_teardown_clean(void)
{
    /* Step 1: Flush 1,024 zero samples (64 ms = full DMA ring buffer) so short tones
     * (such as 15 ms button clicks) completely clock out to the DAC before muting! */
    if (s_tx_chan != NULL && s_i2s_chan_enabled) {
        int16_t silence[256] = {0};
        size_t written = 0;
        for (int i = 0; i < 4; i++) {
            i2s_channel_write(s_tx_chan, silence, sizeof(silence), &written, pdMS_TO_TICKS(50));
        }
    }
    vTaskDelay(pdMS_TO_TICKS(20));

    /* Step 2: Trigger ES8311 soft-mute to ramp down volume smoothly to zero cross */
    es8311_write_reg(0x31, 0x40); /* DAC_DSMMUTE = 1 */

    /* Step 3: Wait ~15 ms for soft-ramp down (based on DAC_RAMPRATE in 0x37) */
    vTaskDelay(pdMS_TO_TICKS(15));

    /* Step 4: Safely gate/shutdown Class D Amplifier without pops */
    gpio_set_level(HAL_PIN_PA_CTRL, 0);

    /* Step 5: Enter ultra-low-power silicon standby */
    sub_audio_standby();
}

/* Internal helper to stream tone samples without entering standby afterwards */
static void sub_audio_render_tone_samples(uint32_t frequency_hz, uint32_t duration_ms)
{
    const uint32_t sample_rate = 16000;
    const uint32_t total_samples = (sample_rate * duration_ms) / 1000;
    int16_t buffer[256];
    uint32_t samples_generated = 0;
    float phase = 0.0f;
    float phase_step = (2.0f * (float)M_PI * (float)frequency_hz) / (float)sample_rate;

    while (samples_generated < total_samples) {
        size_t chunk_size = total_samples - samples_generated;
        if (chunk_size > 256) chunk_size = 256;

        for (size_t i = 0; i < chunk_size; i++) {
            buffer[i] = (int16_t)(sinf(phase) * 12000.0f);
            phase += phase_step;
            if (phase >= 2.0f * (float)M_PI) phase -= 2.0f * (float)M_PI;
        }

        size_t bytes_written = 0;
        i2s_channel_write(s_tx_chan, buffer, chunk_size * sizeof(int16_t), &bytes_written, pdMS_TO_TICKS(100));
        samples_generated += chunk_size;
    }
}

/* Internal helper to stream raw 16-bit PCM buffer */
static void sub_audio_render_pcm_samples(const int16_t *samples, size_t sample_count)
{
    if (samples == NULL || sample_count == 0) return;

    size_t samples_sent = 0;
    while (samples_sent < sample_count) {
        size_t chunk = sample_count - samples_sent;
        if (chunk > 256) chunk = 256;

        size_t bytes_written = 0;
        i2s_channel_write(s_tx_chan, &samples[samples_sent], chunk * sizeof(int16_t), &bytes_written, pdMS_TO_TICKS(100));
        samples_sent += chunk;
    }
}

static esp_err_t sub_audio_prepare_and_unmute(void)
{
    if (!s_audio_inited || s_tx_chan == NULL) {
        esp_err_t err = sub_audio_init();
        if (err != ESP_OK) return err;
    }

    /* 1. Start I2S clocking (MCLK/BCLK) FIRST so ES8311 PLL and CSM have an active MCLK! */
    if (s_tx_chan != NULL && !s_i2s_chan_enabled) {
        esp_err_t chan_err = i2s_channel_enable(s_tx_chan);
        if (chan_err == ESP_OK) {
            s_i2s_chan_enabled = true;
        } else {
            ESP_LOGW(TAG, "i2s_channel_enable failed: %s", esp_err_to_name(chan_err));
        }
    }
    vTaskDelay(pdMS_TO_TICKS(5));

    /* 2. Wakeup codec and restore operational DAC state while MCLK is running */
    es8311_init_dac_registers();

    /* 3. Poll ES8311 Chip State Machine (Reg 0xFC bits 6:4) to verify active state */
    esp_err_t err = sub_audio_wait_until_ready(100);
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "Proceeding with playback despite CSM ready warning: %s", esp_err_to_name(err));
    }

    /* 4. Pre-roll zero samples into DMA pipeline to pre-charge DAC interpolator */
    int16_t preroll[64] = {0};
    size_t written = 0;
    i2s_channel_write(s_tx_chan, preroll, sizeof(preroll), &written, pdMS_TO_TICKS(50));

    /* 5. Unmute NS4168 Class D amplifier and allow 15 ms power-up turn-on time */
    gpio_set_level(HAL_PIN_PA_CTRL, 1);
    vTaskDelay(pdMS_TO_TICKS(15));

    return ESP_OK;
}

static esp_err_t sub_audio_exec_tone(uint32_t frequency_hz, uint32_t duration_ms)
{
    esp_err_t ret = sub_audio_prepare_and_unmute();
    if (ret != ESP_OK) return ret;

    sub_audio_render_tone_samples(frequency_hz, duration_ms);
    sub_audio_teardown_clean();
    return ESP_OK;
}

static esp_err_t sub_audio_exec_pcm(const int16_t *samples, size_t sample_count, uint32_t sample_rate_hz)
{
    (void)sample_rate_hz; /* Pre-configured 16kHz */
    esp_err_t ret = sub_audio_prepare_and_unmute();
    if (ret != ESP_OK) return ret;

    sub_audio_render_pcm_samples(samples, sample_count);
    sub_audio_teardown_clean();
    return ESP_OK;
}

static esp_err_t sub_audio_exec_chime(uint8_t type)
{
    ESP_LOGI(TAG, "Executing acoustic presentation chime (Type %u)...", type);

    esp_err_t ret = sub_audio_prepare_and_unmute();
    if (ret != ESP_OK) return ret;

    switch (type) {
        case 0: /* H1OS_CHIME_BOOT: 4-tone ascending harmonic chord (523 -> 659 -> 784 -> 1046 Hz) */
            sub_audio_render_tone_samples(523, 70);
            vTaskDelay(pdMS_TO_TICKS(15));
            sub_audio_render_tone_samples(659, 70);
            vTaskDelay(pdMS_TO_TICKS(15));
            sub_audio_render_tone_samples(784, 70);
            vTaskDelay(pdMS_TO_TICKS(15));
            sub_audio_render_tone_samples(1046, 150);
            break;

        case 1: /* H1OS_CHIME_WAKE: 2-tone crisp wake (784 -> 1046 Hz) */
            sub_audio_render_tone_samples(784, 60);
            vTaskDelay(pdMS_TO_TICKS(10));
            sub_audio_render_tone_samples(1046, 120);
            break;

        case 2: /* H1OS_CHIME_SLEEP: 3-tone descending sequence (1046 -> 784 -> 659 Hz) */
            sub_audio_render_tone_samples(1046, 80);
            vTaskDelay(pdMS_TO_TICKS(15));
            sub_audio_render_tone_samples(784, 80);
            vTaskDelay(pdMS_TO_TICKS(15));
            sub_audio_render_tone_samples(659, 140);
            break;

        case 3: /* H1OS_CHIME_SHUTDOWN: 3-tone power-down sequence (784 -> 659 -> 523 Hz) */
            sub_audio_render_tone_samples(784, 90);
            vTaskDelay(pdMS_TO_TICKS(15));
            sub_audio_render_tone_samples(659, 90);
            vTaskDelay(pdMS_TO_TICKS(15));
            sub_audio_render_tone_samples(523, 180);
            break;

        case 4: /* H1OS_CHIME_ALARM: Attention pulses */
            for (int i = 0; i < 2; i++) {
                sub_audio_render_tone_samples(1760, 80);
                vTaskDelay(pdMS_TO_TICKS(10));
                sub_audio_render_tone_samples(880, 80);
                vTaskDelay(pdMS_TO_TICKS(20));
            }
            break;

        default:
            sub_audio_standby();
            return ESP_ERR_INVALID_ARG;
    }

    sub_audio_teardown_clean();
    return ESP_OK;
}

/* FreeRTOS Audio Background Worker Task */
static void audio_worker_task(void *pvParameters)
{
    audio_cmd_t cmd;
    ESP_LOGI(TAG, "Audio worker task initialized and active");

    while (1) {
        if (xQueueReceive(s_audio_queue, &cmd, portMAX_DELAY) == pdTRUE) {
            s_audio_is_busy = true;
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
            }

            if (cmd.result) {
                *cmd.result = res;
            }

            if (cmd.done_sem) {
                xSemaphoreGive(cmd.done_sem);
            }

            s_audio_is_busy = false;
        }
    }
}

static esp_err_t sub_audio_send_command(const audio_cmd_t *cmd, bool is_sync, uint32_t wait_ms)
{
    if (s_audio_queue == NULL) {
        esp_err_t err = sub_audio_init();
        if (err != ESP_OK) return err;
    }

    audio_cmd_t local_cmd = *cmd;
    SemaphoreHandle_t sync_sem = NULL;
    esp_err_t exec_result = ESP_OK;

    if (is_sync) {
        sync_sem = xSemaphoreCreateBinary();
        if (sync_sem == NULL) return ESP_ERR_NO_MEM;
        local_cmd.done_sem = sync_sem;
        local_cmd.result   = &exec_result;
    } else {
        local_cmd.done_sem = NULL;
        local_cmd.result   = NULL;
    }

    if (xQueueSend(s_audio_queue, &local_cmd, pdMS_TO_TICKS(wait_ms)) != pdTRUE) {
        if (sync_sem) vSemaphoreDelete(sync_sem);
        return ESP_ERR_TIMEOUT;
    }

    if (is_sync) {
        xSemaphoreTake(sync_sem, portMAX_DELAY);
        vSemaphoreDelete(sync_sem);
        return exec_result;
    }

    return ESP_OK;
}

esp_err_t sub_audio_play_tone(uint32_t frequency_hz, uint32_t duration_ms)
{
    audio_cmd_t cmd = {
        .type = AUDIO_CMD_TONE,
        .params.tone = { .frequency_hz = frequency_hz, .duration_ms = duration_ms },
    };
    return sub_audio_send_command(&cmd, true, 100);
}

esp_err_t sub_audio_play_tone_async(uint32_t frequency_hz, uint32_t duration_ms)
{
    audio_cmd_t cmd = {
        .type = AUDIO_CMD_TONE,
        .params.tone = { .frequency_hz = frequency_hz, .duration_ms = duration_ms },
    };
    return sub_audio_send_command(&cmd, false, 50);
}

esp_err_t sub_audio_play_chime(uint8_t type)
{
    audio_cmd_t cmd = {
        .type = AUDIO_CMD_CHIME,
        .params.chime = { .chime_type = type },
    };
    return sub_audio_send_command(&cmd, true, 100);
}

esp_err_t sub_audio_play_chime_async(uint8_t type)
{
    audio_cmd_t cmd = {
        .type = AUDIO_CMD_CHIME,
        .params.chime = { .chime_type = type },
    };
    return sub_audio_send_command(&cmd, false, 50);
}

esp_err_t sub_audio_play_pcm(const int16_t *samples, size_t sample_count, uint32_t sample_rate_hz)
{
    audio_cmd_t cmd = {
        .type = AUDIO_CMD_PCM,
        .params.pcm = { .samples = samples, .sample_count = sample_count, .sample_rate_hz = sample_rate_hz },
    };
    return sub_audio_send_command(&cmd, true, 100);
}

esp_err_t sub_audio_play_pcm_async(const int16_t *samples, size_t sample_count, uint32_t sample_rate_hz)
{
    audio_cmd_t cmd = {
        .type = AUDIO_CMD_PCM,
        .params.pcm = { .samples = samples, .sample_count = sample_count, .sample_rate_hz = sample_rate_hz },
    };
    return sub_audio_send_command(&cmd, false, 50);
}

bool sub_audio_is_busy(void)
{
    if (s_audio_is_busy) return true;
    if (s_audio_queue && uxQueueMessagesWaiting(s_audio_queue) > 0) return true;
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
    if (volume_pct > 100) volume_pct = 100;
    s_volume_pct = volume_pct;

    /* If codec is currently active (not in standby), update DAC volume register immediately */
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


