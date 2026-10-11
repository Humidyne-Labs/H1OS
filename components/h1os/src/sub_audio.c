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
#include <math.h>

static const char *TAG = "sub_audio";

#define ES8311_REG_SYS_PWR_ANA  0x0D
#define ES8311_REG_DAC_PWR      0x12
#define ES8311_REG_DAC_VOL      0x32

static i2s_chan_handle_t s_tx_chan = NULL;
static bool s_audio_inited = false;

static esp_err_t es8311_write_reg(uint8_t reg, uint8_t val)
{
    uint8_t buf[2] = { reg, val };
    return hal_i2c_write(HAL_I2C_ADDR_ES8311, buf, sizeof(buf), pdMS_TO_TICKS(50));
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

    /* 7. Volume and Unmute */
    ret |= es8311_write_reg(0x32, 0xBF); /* 0 dB nominal volume */
    ret |= es8311_write_reg(0x31, 0x00); /* Unmute DAC DSM/DEM */

    return ret;
}

esp_err_t sub_audio_init(void)
{
    if (s_audio_inited) return ESP_OK;

    /* 1. Configure Power Rail (GPIO 42: Active LOW: 0 = Power ON) & PA CTRL (GPIO 46: 0 = Mute) */
    gpio_config_t pa_cfg = {
        .pin_bit_mask = (1ULL << HAL_PIN_PA_EN) | (1ULL << HAL_PIN_PA_CTRL),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&pa_cfg);
    gpio_set_level(HAL_PIN_PA_EN, 0);   /* Rail MUST stay ON (0) to prevent I2C clamping */
    gpio_set_level(HAL_PIN_PA_CTRL, 0); /* Keep amplifier muted initially */
    vTaskDelay(pdMS_TO_TICKS(15));

    /* 2. Configure I2S TX Channel (16-bit 16kHz Philips Master) */
    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_0, I2S_ROLE_MASTER);
    esp_err_t err = i2s_new_channel(&chan_cfg, &s_tx_chan, NULL);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to create I2S TX channel: %s", esp_err_to_name(err));
        return err;
    }

    i2s_std_config_t std_cfg = {
        .clk_cfg = I2S_STD_CLK_DEFAULT_CONFIG(16000),
        .slot_cfg = I2S_STD_PHILIPS_SLOT_DEFAULT_CONFIG(I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_MONO),
        .gpio_cfg = {
            .mclk = I2S_GPIO_UNUSED,
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
    err = i2s_channel_init_std_mode(s_tx_chan, &std_cfg);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to init I2S std mode: %s", esp_err_to_name(err));
        i2s_del_channel(s_tx_chan);
        s_tx_chan = NULL;
        return err;
    }

    /* 3. Initialize complete 22-register ES8311 clock tree and DAC */
    err = es8311_init_dac_registers();
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "ES8311 register initialization returned error: %d", err);
    }

    s_audio_inited = true;
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
    if (s_tx_chan != NULL) {
        i2s_channel_disable(s_tx_chan);
    }

    return ESP_OK;
}

esp_err_t sub_audio_play_tone(uint32_t frequency_hz, uint32_t duration_ms)
{
    if (!s_audio_inited || s_tx_chan == NULL) {
        esp_err_t err = sub_audio_init();
        if (err != ESP_OK) return err;
    } else {
        /* Wakeup codec and restore operational DAC state */
        es8311_init_dac_registers();
    }

    /* Start I2S clocking and unmute amplifier */
    i2s_channel_enable(s_tx_chan);
    vTaskDelay(pdMS_TO_TICKS(5));
    gpio_set_level(HAL_PIN_PA_CTRL, 1);

    /* Generate sine wave samples at 16 kHz */
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

    /* Return to zero-heat deep standby */
    return sub_audio_standby();
}
