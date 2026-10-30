/**
 * @file sub_audio.c
 * @brief Layer 2: ES8311 codec and NS4150B/NS4168 audio driver implementation
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
#include "esp_rom_sys.h"
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

#define SUB_AUDIO_TASK_STACK_WORKER        4096U /**< Audio worker task stack depth (4 KB floor).        */
#define SUB_AUDIO_TASK_PRIO_WORKER         6     /**< High-priority audio DMA pump priority.             */
#define SUB_AUDIO_AMP_POWER_ON_DELAY_MS    120U  /**< Class-D amplifier power-up settling delay (120ms). */
#define SUB_AUDIO_AMP_POWER_OFF_DELAY_MS   80U   /**< Class-D amplifier power-down muting delay (80ms).  */
#define SUB_AUDIO_DEFAULT_WAIT_TIMEOUT_MS  500U  /**< Default playback completion wait timeout.          */
#define SUB_AUDIO_QUEUE_DEPTH              8U    /**< Static audio command queue depth (8 slots).        */
#define SUB_AUDIO_DMA_DESC_NUM             4U    /**< Number of I2S DMA descriptors (4 x 256 = 64 ms).   */
#define SUB_AUDIO_CSM_SETTLE_TIMEOUT_MS    100U  /**< Maximum wait for ES8311 CSM to exit state S0.      */
#define SUB_AUDIO_CSM_QUIESCE_DELAY_US     2000U /**< Post-suspend CSM power-down hold before clk stop.  */

/* Authoritative Everest Semiconductor ES8311 Register Map (es8311_user_guide_v8.pdf & es8311_reg.h) */
#define ES8311_REG_RESET       0x00 /**< Reset control (Default 0x1F: CSM_ON=0, all RST_*=1).         */
#define ES8311_REG_CLK_MGR1    0x01 /**< Clock manager 1 (Default 0x00: all clocks gated off).        */
#define ES8311_REG_CLK_MGR2    0x02 /**< Clock manager 2 (Pre-divider & pre-multiplier).              */
#define ES8311_REG_CLK_MGR3    0x03 /**< Clock manager 3 (ADC oversampling ratio).                    */
#define ES8311_REG_CLK_MGR4    0x04 /**< Clock manager 4 (DAC oversampling ratio).                    */
#define ES8311_REG_CLK_MGR5    0x05 /**< Clock manager 5 (ADC/DAC digital clock dividers).            */
#define ES8311_REG_CLK_MGR6    0x06 /**< Clock manager 6 (BCLK divider).                              */
#define ES8311_REG_CLK_MGR7    0x07 /**< Clock manager 7 (Bit 5 TRI_BLRCK, Bit 4 TRI_ADCDAT).         */
#define ES8311_REG_CLK_MGR8    0x08 /**< Clock manager 8 (LRCK divider low byte).                     */
#define ES8311_REG_SDPIN       0x09 /**< Serial data port input (Bit 6 SDPIN_MUTE).                   */
#define ES8311_REG_SDPOUT      0x0A /**< Serial data port output (Bit 6 SDPOUT_MUTE).                 */
#define ES8311_REG_SYS_PWR_A   0x0B /**< System power-up time control 1 (CSM_COUNT1).                 */
#define ES8311_REG_SYS_PWR_B   0x0C /**< System power-up time control 2 (CSM_COUNT2).                 */
#define ES8311_REG_SYS_PWR_ANA 0x0D /**< System analog/bias/reference power-down (Default 0xFC).      */
#define ES8311_REG_SYS_PDN_MOD 0x0E /**< System PGA/ADC modulator power-down (Default 0x6A).          */
#define ES8311_REG_SYS_LP_MOD  0x0F /**< System low-power mode enables (0xFF = all LP blocks active). */
#define ES8311_REG_SYS_IBIAS   0x10 /**< System master/DAC bias current control (Default 0x13).       */
#define ES8311_REG_SYS_INT11   0x11 /**< System internal bias control (Default 0x7C).                 */
#define ES8311_REG_DAC_PWR     0x12 /**< DAC power control (Default 0x02: PDN_DAC=1, ENREFR=0).       */
#define ES8311_REG_SYS_HPSW    0x13 /**< System headphone driver switch (Default 0x00: HPSW=0).       */
#define ES8311_REG_SYS_MIC_PGA 0x14 /**< System DMIC/analog MIC mux & PGA gain (Default 0x10).        */
#define ES8311_REG_ADC_RAMP    0x15 /**< ADC soft-ramp rate & DMIC sense (Default 0x00).              */
#define ES8311_REG_ADC_SCALE   0x16 /**< ADC microphone gain scale (Default 0x04).                    */
#define ES8311_REG_ADC_VOL     0x17 /**< ADC digital volume (Default 0x00: -95.5 dB).                 */
#define ES8311_REG_ADC_HPF     0x1B /**< ADC high-pass filter coefficient S2 (Default 0x0C).          */
#define ES8311_REG_ADC_EQ      0x1C /**< ADC equalizer bypass & HPF S1 (Default 0x4C: EQ bypassed).   */
#define ES8311_REG_DAC_MUTE    0x31 /**< DAC digital mute control (0x60 = DSM & DEM muted).           */
#define ES8311_REG_DAC_VOL     0x32 /**< DAC digital volume (Default 0x00: -95.5 dB).                 */
#define ES8311_REG_DAC_RAMP_EQ 0x37 /**< DAC ramp rate & EQ bypass (Default 0x08: DAC_EQBYPASS=1).    */
#define ES8311_REG_GPIO_CFG    0x44 /**< GPIO & ADCDAT loopback mux (Default 0x00).                   */
#define ES8311_REG_GP_CTRL     0x45 /**< GP pull-up/pull-down control (Bit 0 PULLUP_SE: 1=pullup off).*/
#define ES8311_REG_FLAG        0xFC /**< CSM & clock status flag register (Bits 6:4 FLAG_CSM_CHIP).   */
#define ES8311_REG_CHIP_ID1    0xFD /**< Chip ID high byte (0x83).                                    */
#define ES8311_REG_CHIP_ID2    0xFE /**< Chip ID low byte (0x11).                                     */

#define FRAME_SIZE 0x100

typedef enum {
    AUDIO_CMD_TONE = 0,
    AUDIO_CMD_CHIME,
    AUDIO_CMD_PCM,
    AUDIO_CMD_STOP,
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

static StaticQueue_t s_audio_queue_struct;
static uint8_t       s_audio_queue_storage[SUB_AUDIO_QUEUE_DEPTH * sizeof(audio_cmd_t)];
static QueueHandle_t s_audio_queue                = NULL;
static volatile TaskHandle_t s_audio_task_handle  = NULL;
static volatile bool s_audio_is_busy              = false;

static uint8_t s_volume_pct = 0;

static StaticSemaphore_t s_cmd_sync_sem_buffer;
static SemaphoreHandle_t s_cmd_sync_sem = NULL;
static StaticSemaphore_t s_audio_idle_sem_buffer;
static SemaphoreHandle_t s_audio_idle_sem = NULL;
static StaticSemaphore_t s_audio_stop_sem_buffer;
static SemaphoreHandle_t s_audio_stop_sem = NULL;
static int16_t           s_audio_work_buffer[FRAME_SIZE];

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
        (void)esp_pm_lock_create(ESP_PM_CPU_FREQ_MAX, 0, "sub_audio", &s_audio_pm_lock);
    }
    if (s_audio_pm_lock != NULL) {
        (void)esp_pm_lock_acquire(s_audio_pm_lock);
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
        (void)esp_pm_lock_release(s_audio_pm_lock);
    }
#endif
}

static const uint8_t es8311_perceptual_vol_table[101] = {
    0x00, 0x3A, 0x48, 0x51, 0x57,
    0x5D, 0x61, 0x65, 0x68, 0x6B,
    0x6E, 0x71, 0x73, 0x75, 0x77,
    0x79, 0x7B, 0x7D, 0x7E, 0x80,
    0x81, 0x83, 0x84, 0x85, 0x87,
    0x88, 0x89, 0x8A, 0x8B, 0x8C,
    0x8D, 0x8E, 0x8F, 0x90, 0x91,
    0x92, 0x93, 0x94, 0x95, 0x96,
    0x97, 0x98, 0x99, 0x99, 0x9A,
    0x9B, 0x9C, 0x9D, 0x9E, 0x9E,
    0x9F, 0xA0, 0xA1, 0xA2, 0xA2,
    0xA3, 0xA4, 0xA5, 0xA5, 0xA6,
    0xA7, 0xA8, 0xA8, 0xA9, 0xAA,
    0xAA, 0xAB, 0xAC, 0xAC, 0xAD,
    0xAE, 0xAE, 0xAF, 0xB0, 0xB0,
    0xB1, 0xB2, 0xB2, 0xB3, 0xB3,
    0xB4, 0xB5, 0xB5, 0xB6, 0xB6,
    0xB7, 0xB7, 0xB8, 0xB9, 0xB9,
    0xBA, 0xBA, 0xBB, 0xBC, 0xBC,
    0xBD, 0xBD, 0xBE, 0xBE, 0xBF,
    0xBF
};

/*
 * Stage 1: Open / Pre-charge sequence (aligned with Espressif es8311_open() & es8311_user_guide_v8.pdf)
 * Configures clock dividers, analog bias references, internal reference routing (0x44=0x58),
 * serial data port (SDP) format, and starts the Chip State Machine (CSM) with MCLK/BCLK/LRCK active.
 */
static const es8311_reg_entry_t s_es8311_init_pre_charge[] =
{
    /* I2C Noise Filter Lock & System Pre-Charge                                                       */
    {0x44, 0x08}, /**< REG44: GPIO/I2C internal timing config (I2C_WL=1)                               */
    {0x44, 0x08}, /**< REG44: Repeated write to guarantee stable I2C latch on wakeup                   */

    {0x0D, 0xFA}, /**< REG0D: System power down (PDN_ANA..DACVREF=1, PDN_VREF=0, VMIDSEL=2 pre-charge) */

    /* Clock Manager Dividers (MCLK = 256 * Fs = 4.096 MHz, Fs = 16 kHz)                               */
    {0x01, 0x30}, /**< REG01: Enable MCLK_ON (Bit 5) & BCLK_ON (Bit 4) prior to divider configuration  */
    {0x02, 0x00}, /**< REG02: Pre-divider DIV_PRE=0 (/1), MULT_PRE=0 (x1)                              */
    {0x03, 0x10}, /**< REG03: ADC oversampling ratio (ADC_OSR=16 -> 64x Fs)                            */
    {0x16, 0x24}, /**< REG16: ADC microphone gain scale (ADC_SCALE=4, internal bit 5)                  */
    {0x04, 0x20}, /**< REG04: DAC oversampling ratio (DAC_OSR=32 -> 64x Fs)                            */
    {0x05, 0x00}, /**< REG05: Clock dividers DIV_CLKADC=0 (/1), DIV_CLKDAC=0 (/1)                      */
    {0x0B, 0x00}, /**< REG0B: Power-up sequence time control 1 (CSM_COUNT1=0)                          */
    {0x0C, 0x00}, /**< REG0C: Power-up sequence time control 2 (CSM_COUNT2=0)                          */

    /* System Analog Bias & Reference Trimming                                                         */
    {0x10, 0x1F}, /**< REG10: System analog bias (VY1SEL=3, VX2OFF=1, IBIAS_SW=3 active bias)          */
    {0x11, 0x7F}, /**< REG11: System internal bias control (0x7F active operation)                     */

    /* Chip State Machine (CSM) Enable & Clock Un-Gating                                               */
    {0x00, 0x80}, /**< REG00: CSM_ON=1 (Bit 7), MSC=0 (slave mode), SEQ_DIS=0, release all RST_*=0     */
    {0x01, 0x3F}, /**< REG01: Enable MCLK, BCLK, CLKADC, CLKDAC, ANACLKADC, and ANACLKDAC              */
    {0x06, 0x03}, /**< REG06: BCLK divider (DIV_BCLK=3 -> /4)                                          */
    {0x07, 0x00}, /**< REG07: TRI_BLRCK=0, TRI_ADCDAT=0, DIV_LRCK[11:8]=0                              */
    {0x08, 0xFF}, /**< REG08: LRCK divider low byte (DIV_LRCK[7:0]=0xFF -> /256)                       */

    /* Output Switch, Filter Configuration & Internal Reference Signal Routing                         */
    {0x13, 0x10}, /**< REG13: HPSW=1 (Bit 4: enable output switch to speaker/headphone driver)         */
    {0x1B, 0x0A}, /**< REG1B: ADC high-pass filter coefficient S2 (ADC_HPFS2=10)                       */
    {0x1C, 0x6A}, /**< REG1C: ADC_EQBYPASS=1 (Bit 6), ADC_HPF=1 (Bit 5), ADC_HPFS1=10                  */
    {0x44, 0x58}, /**< REG44: ADCDAT_SEL=5 (internal reference signal for DAC startup stability)       */

    /* Serial Data Port (SDP) Format (16-bit Philips I2S, DAC-only mode)                               */
    {0x09, 0x0C}, /**< REG09: SDPIN (DAC input): SDPIN_MUTE=0, SDPIN_WL=3 (16-bit), I2S format         */
    {0x0A, 0x4C}, /**< REG0A: SDPOUT (ADC output): SDPOUT_MUTE=1 (muted in DAC-only mode), 16-bit      */
};

/*
 * Stage 2: Start / Post-charge sequence (DAC-only playback configuration)
 * Powers up DAC analog and VMID mid-rail reference (0x0D=0x01) while keeping the unused microphone
 * PGA and ADC modulator powered down (0x0E=0x62, 0x14=0x00, 0x17=0x00), disables DAC soft-start
 * volume ramp (0x37=0x08: DAC_RAMPRATE=0, DAC_EQBYPASS=1), and unmutes the DAC path (0x31=0x00).
 */
static const es8311_reg_entry_t s_es8311_init_post_charge[] =
{
    {0x17, 0x00}, /**< REG17: ADC_VOLUME=0x00 (-95.5 dB; unused microphone ADC path muted)             */
    {0x0E, 0x62}, /**< REG0E: PDN_PGA=1 (Bit 6), PDN_MOD=1 (Bit 5: unused mic PGA & ADC mod OFF)       */
    {0x12, 0x00}, /**< REG12: PDN_DAC=0 (Bit 1: enable DAC analog block), ENREFR=0                     */
    {0x14, 0x00}, /**< REG14: DMIC_ON=0, LINSEL=0 (no analog mic input selected), PGAGAIN=0 (0 dB)     */
    {0x0D, 0x01}, /**< REG0D: Power on analog reference & fast-charge VMID mid-rail buffer (0x01)      */
    {0x15, 0x40}, /**< REG15: ADC_RAMPRATE=4, DMIC_SENSE=0                                             */
    {0x37, 0x08}, /**< REG37: DAC_RAMPRATE=0 (soft-ramp OFF for 50ms chirps), DAC_EQBYPASS=1 (Bit 3)   */
    {0x45, 0x00}, /**< REG45: Normal active I2S operation                                              */
    {0x31, 0x00}, /**< REG31: DAC_DSMMUTE=0, DAC_DEMUTE=0 (unmute DAC output path)                     */
};

/*
 * Stage 3: De-initialization / Low-Power Suspend sequence (<1.0 uA)
 * Strictly follows Espressif reference driver es8311_suspend() (_3rd_party_ref_codec/es8311.c:222-240)
 * and ES8311 Datasheet Rev 1.6 Page 8 Note 4:
 * - Soft-mutes DAC (0x31=0x60) and zeros DAC/ADC digital volumes (0x32=0x00, 0x17=0x00).
 * - Powers down analog modulator/DAC/PGA/HPSW (0x0E=0xFF, 0x12=0x02, 0x13=0x00, 0x14=0x00) and
 *   steps Reg 0x0D to 0xFA while CSM is still active.
 * - Executes the mandatory CSM state-machine shutdown sequence (0x02=0x10 -> 0x00=0x00 -> 0x00=0x1F
 *   -> 0x01=0x30 -> 0x01=0x00).
 * - Writes 0x0D=0xFC and 0x02=0x00 AFTER 0x00=0x1F and 0x01=0x00 so the CSM reset transition cannot
 *   revert Reg 0x0D back to its pre-charge state (0xFA) and leave analog references biased during sleep.
 */
static const es8311_reg_entry_t s_es8311_deinit[] =
{
    /* 1. Soft-Mute DAC & Zero Digital Volumes */
    {0x31, 0x60}, /**< REG31: DAC_DSMMUTE=1, DAC_DEMUTE=1 (mute DSM & DEM outputs)                     */
    {0x32, 0x00}, /**< REG32: DAC_VOLUME=0x00 (-95.5 dB minimum digital attenuation)                   */
    {0x17, 0x00}, /**< REG17: ADC_VOLUME=0x00 (-95.5 dB minimum digital attenuation)                   */

    /* 2. Power Down Analog Stages & Step VMID Reference to Pre-Charge State (0xFA) */
    {0x0E, 0xFF}, /**< REG0E: Power down analog PGA and ADC modulator blocks (es8311_suspend)          */
    {0x12, 0x02}, /**< REG12: PDN_DAC=1 (power down DAC), ENREFR=0 (POR default)                       */
    {0x13, 0x00}, /**< REG13: HPSW=0 (open headphone/speaker output switch)                            */
    {0x14, 0x00}, /**< REG14: DMIC_ON=0, LINSEL=0 (disconnect analog mic input), PGAGAIN=0             */
    {0x0D, 0xFA}, /**< REG0D: Step analog power control to 0xFA prior to CSM reset (es8311_suspend)    */
    {0x15, 0x00}, /**< REG15: ADC_RAMPRATE=0, DMIC_SENSE=0                                             */

    /* 3. Mute Serial Data Ports, Tri-State I2S Outputs & Restore Low-Power Bias Defaults */
    {0x09, 0x4C}, /**< REG09: SDPIN_MUTE=1, 16-bit I2S input muted                                     */
    {0x0A, 0x4C}, /**< REG0A: SDPOUT_MUTE=1, 16-bit I2S output muted                                   */
    {0x07, 0x30}, /**< REG07: TRI_BLRCK=1, TRI_ADCDAT=1 (tri-state BCLK, LRCK, and ASDOUT Pin 7)       */
    {0x44, 0x00}, /**< REG44: ADC2DAC_SEL=0, ADCDAT_SEL=0 (disconnect internal reference routing)      */
    {0x0F, 0xFF}, /**< REG0F: Enable all 8 low-power reference/DAC/PGA bits (0xFF)                     */
    {0x10, 0x13}, /**< REG10: DAC_IBIAS_SW=0, VX2OFF=0, VY1SEL=2, IBIAS_SW=3 (POR default 0x13)        */
    {0x11, 0x7C}, /**< REG11: Restore system internal bias register to POR default (0x7C)              */

    /* 4. Execute Official Espressif CSM Reset & Clock Gating Handshake (es8311_suspend) */
    {0x02, 0x10}, /**< REG02: Set MULT_PRE=2 prior to CSM reset transition                             */
    {0x00, 0x00}, /**< REG00: Clear CSM_ON=0 while holding digital resets de-asserted                  */
    {0x00, 0x1F}, /**< REG00: Assert all digital resets (RST_DIG/CMG/MST/ADC_DIG/DAC_DIG=1, POR 0x1F)  */
    {0x01, 0x30}, /**< REG01: Gate internal ADC/DAC clocks while keeping MCLK/BCLK enabled             */
    {0x01, 0x00}, /**< REG01: Gate off all internal clocks (0x00)                                      */

    /* 5. Final Analog Power-Down (0x0D=0xFC) & Bus Pull-Up Disarm AFTER CSM Reset (0x00=0x1F) */
    {0x45, 0x03}, /**< REG45: PULLDOWN_ADCDAT=1 (Bit 1), PULLUP_SE=1 (Bit 0: BCLK/LRCK pull-ups OFF)   */
    {0x0D, 0xFC}, /**< REG0D: Power down all analog/bias/VREF blocks & VMID=00 (<1.0 uA standby)       */
    {0x02, 0x00}, /**< REG02: Clear clock pre-multiplier to 0x00                                       */
};

#define S_ES8311_INIT_PRE_CHARGE_SIZE    (sizeof(s_es8311_init_pre_charge)  / sizeof(s_es8311_init_pre_charge[0]))  /**< Pre Charge Table Size Macro  */
#define S_ES8311_INIT_POST_CHARGE_SIZE   (sizeof(s_es8311_init_post_charge) / sizeof(s_es8311_init_post_charge[0])) /**< Post Charge Table Size Macro */
#define S_ES8311_DEINIT_SIZE             (sizeof(s_es8311_deinit)           / sizeof(s_es8311_deinit[0]))           /**< Deinit Table Size Macro      */

/**
 * @brief Convert perceptual volume percentage (0..100%) to ES8311 DAC_VOLUME register byte.
 *
 * @param[in]    pct             Volume percentage (0..100).
 *
 * @return ES8311 Register 0x32 value.
 */
static inline uint8_t volume_pct_to_es8311_reg(uint8_t pct)
{
    if (pct > 100) {
        pct = 100;
    }
    return es8311_perceptual_vol_table[pct];
}

static void audio_worker_task(void *pvParameters);
static esp_err_t sub_audio_park_warm(bool park_mute);

/**
 * @brief Write a single 8-bit value to an ES8311 control register over shared I2C.
 *
 * @param[in]    reg             Register address.
 * @param[in]    val             Register value.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t es8311_write_reg(uint8_t reg, uint8_t val)
{
    uint8_t buf[2] = {reg, val};
    return hal_i2c_write(HAL_I2C_ADDR_ES8311, buf, sizeof(buf), pdMS_TO_TICKS(50));
}

/**
 * @brief Read a single 8-bit value from an ES8311 control register over shared I2C.
 *
 * @param[in]    reg             Register address.
 * @param[out]   val             Pointer to receive register value.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t es8311_read_reg(uint8_t reg, uint8_t *val)
{
    return hal_i2c_write_read(HAL_I2C_ADDR_ES8311, &reg, 1, val, 1, pdMS_TO_TICKS(50));
}

/**
 * @brief Read and validate the 16-bit ES8311 Chip ID (0xFD=0x83, 0xFE=0x11).
 *
 * @param[out]   chip_id         Pointer to store 16-bit chip ID.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t sub_audio_read_chip_id(uint16_t *chip_id)
{
    if (chip_id == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t id1 = 0, id2 = 0;

    esp_err_t err1 = es8311_read_reg(ES8311_REG_CHIP_ID1, &id1);
    esp_err_t err2 = es8311_read_reg(ES8311_REG_CHIP_ID2, &id2);

    *chip_id = (uint16_t)((id1 << 8) | id2);

    if (err1 != ESP_OK || err2 != ESP_OK || *chip_id != 0x8311U) {
        return ESP_ERR_NOT_FOUND;
    }

    return ESP_OK;
}

/**
 * @brief Drain the full 4-descriptor (64 ms) I2S DMA ring with silent PCM frames so short chirps play completely.
 *
 * @details Because the I2S TX channel uses 4 DMA descriptors of 256 samples each (1024 samples = 64 ms at 16 kHz),
 *          a 50 ms button chirp (800 samples) is copied into the empty DMA descriptors instantaneously (<1 ms).
 *          Writing SUB_AUDIO_DMA_DESC_NUM (4) zero-filled frames forces the I2S DMA engine to clock out all
 *          preceding tone descriptors before returning, guaranteeing 100% of every 50 ms chirp is heard.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t sub_audio_flush_frame(void)
{
    esp_err_t ret = ESP_ERR_INVALID_STATE;
    if (s_audio_inited && s_i2s_chan_enabled && s_tx_chan != NULL) {
        int16_t *buffer = s_audio_work_buffer;
        memset(buffer, 0x0000, sizeof(s_audio_work_buffer));

        ret = ESP_OK;
        for (uint32_t i = 0U; i < SUB_AUDIO_DMA_DESC_NUM; i++) {
            size_t buffer_written = 0;
            esp_err_t w_err = i2s_channel_write(s_tx_chan,
                                                buffer,
                                                sizeof(s_audio_work_buffer),
                                                &buffer_written,
                                                pdMS_TO_TICKS(100));
            if (w_err != ESP_OK || buffer_written != sizeof(s_audio_work_buffer)) {
                ret = ESP_ERR_INVALID_STATE;
                break;
            }
        }

        /* Allow final 256-sample silent descriptor (~16 ms at 16 kHz) to exit the I2S serializer */
        vTaskDelay(pdMS_TO_TICKS(20));
    }
    return ret;
}

/**
 * @brief Poll ES8311 over I2C to confirm Chip ID (0x8311) and wait for Chip State Machine (Reg 0xFC bits 6:4) to exit state S0.
 *
 * @param[in]    timeout_ms      Maximum wait time in milliseconds.
 *
 * @return ESP_OK if codec is verified and in active CSM state, or error.
 */
esp_err_t sub_audio_wait_until_ready(uint32_t timeout_ms)
{
    uint16_t chip_id = 0x0000;
    if (sub_audio_read_chip_id(&chip_id) != ESP_OK) {
        return ESP_ERR_INVALID_STATE;
    }

    uint32_t elapsed_ms    = 0;
    const uint32_t step_ms = 5;
    while (elapsed_ms < timeout_ms) {
        uint8_t flag = 0;
        if (es8311_read_reg(ES8311_REG_FLAG, &flag) == ESP_OK) {
            uint8_t csm_state = (flag >> 4) & 0x07U;
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
 * @brief Write a table of register/value pairs to the ES8311 over I2C.
 *
 * @param[in]    table           Pointer to register entry array.
 * @param[in]    count           Number of entries in table.
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
 * @brief Initialize ES8311 DAC registers for active playback (requires I2S MCLK/LRCK running per Note 5).
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t es8311_init_dac_registers(void)
{
    esp_err_t ret = ESP_OK;

    ret |= es8311_write_table(s_es8311_init_pre_charge, S_ES8311_INIT_PRE_CHARGE_SIZE);

    /* Delay for internal analog frontend pre-charge and CSM transition */
    vTaskDelay(pdMS_TO_TICKS(35));

    ret |= es8311_write_table(s_es8311_init_post_charge, S_ES8311_INIT_POST_CHARGE_SIZE);

    /* Default to low-power operating mode (Reg 0x0F = 0xFF: LPDAC and all LP reference modes enabled) */
    ret |= es8311_write_reg(ES8311_REG_SYS_LP_MOD, s_low_power_mode ? 0xFFU : 0x00U);

    return ret;
}

/**
 * @brief Initialize ES8311 codec and NS4150B/NS4168 amplifier for an interactive session.
 *
 * @details Called exclusively on Cold Boot or interactive Button Wake (never on unattended Flow A
 *          or Flow B wakes). Configures the I2S master bus, powers down the unused microphone ADC/PGA
 *          (0x0E=0x62, 0x14=0x00, 0x17=0x00), enables codec low-power operating mode (0x0F=0xFF) with
 *          soft-start ramp disabled (0x37=0x08), waits for the ES8311 CSM to exit state S0, and powers
 *          on the Class-D amplifier (120 ms settling) BEFORE returning so the boot chime and all 50 ms
 *          button chirps play instantaneously without leading or trailing truncation. When the 30-second
 *          interactive session times out, orch_flow_quiesce_peripherals() calls sub_audio_standby() to
 *          place the codec and amplifier into <1 uA deep standby across all subsequent sleep cycles.
 *
 * @param[in]    volume_pct      Initial master volume percentage (0..100%).
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_audio_init(uint8_t volume_pct)
{
    if (volume_pct > 100U) {
        volume_pct = 100U;
    }
    s_volume_pct = volume_pct;

    if (s_audio_inited) {
        return sub_audio_set_volume(volume_pct);
    }

    audio_cpu_max_acquire();

    /* Ensure Class-D amplifier is muted (GPIO 46 LOW) during codec pre-charge */
    (void)sub_audio_park_warm(true);

    /* Probe shared I2C bus for ES8311 (0x18) */
    esp_err_t err = hal_i2c_probe(HAL_I2C_ADDR_ES8311);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Device Not Found: %s", esp_err_to_name(err));
        s_audio_inited = false;
        audio_cpu_max_release();
        return ESP_ERR_NOT_FOUND;
    }

    uint16_t chip_id = 0x0000;
    err = sub_audio_read_chip_id(&chip_id);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Chip read failed: %s", esp_err_to_name(err));
        s_audio_inited = false;
        audio_cpu_max_release();
        return ESP_ERR_INVALID_RESPONSE;
    }

    if (chip_id != 0x8311U) {
        ESP_LOGE(TAG, "Chip ID invalid (0x%04X, expected 0x8311)", chip_id);
        s_audio_inited = false;
        audio_cpu_max_release();
        return ESP_ERR_INVALID_VERSION;
    }

    ESP_LOGI(TAG, "Chip ID valid (0x%04X)", chip_id);

    i2s_chan_config_t chan_cfg = I2S_CHANNEL_DEFAULT_CONFIG(I2S_NUM_0, I2S_ROLE_MASTER);
    chan_cfg.auto_clear        = true;
    chan_cfg.dma_desc_num      = SUB_AUDIO_DMA_DESC_NUM;
    chan_cfg.dma_frame_num     = FRAME_SIZE;

    err = i2s_new_channel(&chan_cfg, &s_tx_chan, NULL);
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
                .ws   = HAL_PIN_I2S_LRCK,
                .dout = HAL_PIN_I2S_DSDIN,
                .din  = I2S_GPIO_UNUSED,
                .invert_flags =
                    {
                        .mclk_inv = false,
                        .bclk_inv = false,
                        .ws_inv   = false,
                    },
            },
    };
    std_cfg.clk_cfg.mclk_multiple = I2S_MCLK_MULTIPLE_256;
    std_cfg.slot_cfg.slot_mask    = I2S_STD_SLOT_LEFT;

    err = i2s_channel_init_std_mode(s_tx_chan, &std_cfg);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to init I2S std mode: %s", esp_err_to_name(err));
        (void)i2s_del_channel(s_tx_chan);
        s_tx_chan = NULL;
        audio_cpu_max_release();
        return err;
    }

    /* Start MCLK/SCLK/LRCK prior to register programming per ES8311 Datasheet Page 8 Note 5 */
    err = i2s_channel_enable(s_tx_chan);
    if (err == ESP_OK) {
        s_i2s_chan_enabled = true;
    }
    vTaskDelay(pdMS_TO_TICKS(5));

    err = es8311_init_dac_registers();
    s_codec_in_standby     = false;
    s_rtc_codec_in_standby = false;
    if (err != ESP_OK) {
        ESP_LOGW(TAG, "ES8311 register initialization returned error: %s", esp_err_to_name(err));
    }

    /* Confirm CSM exited power-down state S0 before enabling amplifier or playing boot chime */
    (void)sub_audio_wait_until_ready(SUB_AUDIO_CSM_SETTLE_TIMEOUT_MS);

    if (s_audio_stop_sem == NULL) {
        s_audio_stop_sem = xSemaphoreCreateBinaryStatic(&s_audio_stop_sem_buffer);
    }

    if (s_audio_queue == NULL) {
        s_audio_queue = xQueueCreateStatic(SUB_AUDIO_QUEUE_DEPTH,
                                           sizeof(audio_cmd_t),
                                           s_audio_queue_storage,
                                           &s_audio_queue_struct);
    } else {
        (void)xQueueReset(s_audio_queue);
    }

    if (s_audio_task_handle == NULL) {
        TaskHandle_t current_task  = xTaskGetCurrentTaskHandle();
        TaskHandle_t worker_handle = NULL;
        BaseType_t res = xTaskCreatePinnedToCore(audio_worker_task,
                                                 "h1os_audio_worker",
                                                 SUB_AUDIO_TASK_STACK_WORKER,
                                                 (void *)current_task,
                                                 SUB_AUDIO_TASK_PRIO_WORKER,
                                                 &worker_handle,
                                                 tskNO_AFFINITY);
        if (res == pdPASS) {
            s_audio_task_handle = worker_handle;
            if (ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(500)) == 0) {
                ESP_LOGE(TAG, "Audio worker task startup timeout (>500ms). Deleting orphan task.");
                vTaskDelete(worker_handle);
                s_audio_task_handle = NULL;
                if (s_i2s_chan_enabled) {
                    (void)i2s_channel_disable(s_tx_chan);
                    s_i2s_chan_enabled = false;
                }
                (void)i2s_del_channel(s_tx_chan);
                s_tx_chan = NULL;
                audio_cpu_max_release();
                return ESP_ERR_TIMEOUT;
            }
        } else {
            ESP_LOGE(TAG, "Failed to create audio worker task: %ld", (long)res);
            if (s_i2s_chan_enabled) {
                (void)i2s_channel_disable(s_tx_chan);
                s_i2s_chan_enabled = false;
            }
            (void)i2s_del_channel(s_tx_chan);
            s_tx_chan = NULL;
            audio_cpu_max_release();
            return ESP_ERR_NO_MEM;
        }
    }

    s_audio_inited = true;

    /* Apply volume and enable Class-D amp (120 ms turn-on delay) so boot chime & chirps never clip */
    (void)sub_audio_set_volume(volume_pct);
    (void)sub_audio_park_warm(false);

    ESP_LOGI(TAG, "ES8311 Codec (LP=%u, Mic=OFF, Ramp=OFF) & Class-D Amp ready (16kHz Mono, Vol: %u%%)",
             s_low_power_mode ? 1U : 0U, volume_pct);

    audio_cpu_max_release();
    return ESP_OK;
}

/**
 * @brief Control Class-D amplifier hardware mute/shutdown state (HAL_PIN_PA_CTRL / GPIO 46).
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
        (void)gpio_set_level(HAL_PIN_PA_CTRL, target_level);
        s_pa_enabled = target_enabled;

        /* Allow Class-D amplifier startup (120 ms) or shutdown (80 ms) settling */
        vTaskDelay(pdMS_TO_TICKS(target_enabled ? SUB_AUDIO_AMP_POWER_ON_DELAY_MS : SUB_AUDIO_AMP_POWER_OFF_DELAY_MS));
    }

    return ESP_OK;
}

/**
 * @brief Put ES8311 codec into ultra-low-power software standby (<1.0 uA) and pull PA_CTRL LOW.
 *
 * @details Follows Espressif es8311_suspend() (_3rd_party_ref_codec/es8311.c:222-240) and
 *          ES8311 Datasheet Rev 1.6 Page 8 Note 4 & Note 5:
 *          1. Mutes the external Class-D amplifier (GPIO 46 = 0, 80 ms mute settling).
 *          2. On unattended deep-sleep wakes (Flow B) where sub_audio_init() was bypassed and
 *             s_rtc_codec_in_standby is already true, returns ESP_OK immediately without
 *             touching I2C or disturbing the persisted codec sleep state.
 *          3. Ensures input clocks (MCLK/LRCK) are running during the suspend sequence, writes
 *             s_es8311_deinit (ordering 0x0D=0xFC AFTER 0x00=0x1F and 0x01=0x00), waits 2 ms,
 *             and then disables the I2S TX channel.
 *
 * @return ESP_OK on success, or an error code.
 */
esp_err_t sub_audio_standby(void)
{
    /* 1. Always ensure Class-D amplifier is muted (GPIO 46 = 0) */
    (void)sub_audio_park_warm(true);

    /* 2. On unattended Flow B wakes, completely bypass codec sleep I2C writes as state persists across sleeps */
    if (!s_audio_inited && s_rtc_codec_in_standby && esp_reset_reason() == ESP_RST_DEEPSLEEP) {
        s_codec_in_standby = true;
        return ESP_OK;
    }

    /* 3. Per ES8311 Datasheet Page 8 Note 4 & Note 5, keep MCLK running while writing suspend registers */
    if (s_tx_chan != NULL && !s_i2s_chan_enabled) {
        if (i2s_channel_enable(s_tx_chan) == ESP_OK) {
            s_i2s_chan_enabled = true;
            esp_rom_delay_us(500);
        }
    }

    /* Write complete es8311_suspend sequence (with 0x0D=0xFC after 0x00=0x1F so CSM reset does not revert 0x0D) */
    esp_err_t ret = es8311_write_table(s_es8311_deinit, S_ES8311_DEINIT_SIZE);
    if (s_i2s_chan_enabled) {
        esp_rom_delay_us(SUB_AUDIO_CSM_QUIESCE_DELAY_US);
    }

    s_codec_in_standby     = true;
    s_rtc_codec_in_standby = (ret == ESP_OK);

    /* 4. Stop I2S input clocks AFTER low-power register configuration completes (Datasheet Note 4) */
    if (s_tx_chan != NULL && s_i2s_chan_enabled) {
        (void)i2s_channel_disable(s_tx_chan);
        s_i2s_chan_enabled = false;
    }

    ESP_LOGI(TAG, "ES8311 codec & Class-D amplifier placed in <1 uA deep standby (ret=%s)", esp_err_to_name(ret));
    return ret;
}

/**
 * @brief Synthesize and stream sine wave tone samples to I2S DMA.
 *
 * @param[in]    frequency_hz    Tone frequency in Hz.
 * @param[in]    duration_ms     Tone duration in milliseconds.
 */
static void sub_audio_render_tone_samples(uint32_t frequency_hz, uint32_t duration_ms)
{
    const uint32_t sample_rate   = 16000;
    const uint32_t total_samples = (sample_rate * duration_ms) / 1000;
    const uint32_t ramp_samples  = (total_samples > 64) ? 32 : (total_samples / 4);

    int16_t *buffer            = s_audio_work_buffer;
    uint32_t samples_generated = 0;

    float phase      = 0.0f;
    float phase_step = (2.0f * (float)M_PI * (float)frequency_hz) / (float)sample_rate;

    while (samples_generated < total_samples) {
        size_t chunk_size = total_samples - samples_generated;
        if (chunk_size > FRAME_SIZE) {
            chunk_size = FRAME_SIZE;
        }

        for (size_t i = 0; i < chunk_size; i++) {
            uint32_t idx = samples_generated + (uint32_t)i;
            float env    = 1.0f;
            if (ramp_samples > 0) {
                if (idx < ramp_samples) {
                    env = (float)idx / (float)ramp_samples;
                } else if (idx + ramp_samples >= total_samples) {
                    env = (float)(total_samples - 1 - idx) / (float)ramp_samples;
                }
            }
            buffer[i] = (int16_t)(sinf(phase) * 28000.0f * env);
            phase += phase_step;
            if (phase >= 2.0f * (float)M_PI) {
                phase -= 2.0f * (float)M_PI;
            }
        }

        if (chunk_size < FRAME_SIZE) {
            memset(&buffer[chunk_size], 0, (FRAME_SIZE - chunk_size) * sizeof(int16_t));
        }

        size_t bytes_written = 0;
        if (s_tx_chan != NULL) {
            (void)i2s_channel_write(s_tx_chan, buffer, sizeof(s_audio_work_buffer), &bytes_written, pdMS_TO_TICKS(100));
        }
        samples_generated += chunk_size;
    }
}

/**
 * @brief Stream raw 16-bit mono PCM samples to I2S DMA.
 *
 * @param[in]    samples         Pointer to PCM sample buffer.
 * @param[in]    sample_count    Number of 16-bit samples.
 */
static void sub_audio_render_pcm_samples(const int16_t *samples, size_t sample_count)
{
    if (samples == NULL || sample_count == 0) {
        return;
    }

    int16_t *buffer     = s_audio_work_buffer;
    size_t samples_sent = 0;
    while (samples_sent < sample_count) {
        size_t chunk = sample_count - samples_sent;
        if (chunk > FRAME_SIZE) {
            chunk = FRAME_SIZE;
        }

        memcpy(buffer, &samples[samples_sent], chunk * sizeof(int16_t));
        if (chunk < FRAME_SIZE) {
            memset(&buffer[chunk], 0, (FRAME_SIZE - chunk) * sizeof(int16_t));
        }

        size_t bytes_written = 0;
        if (s_tx_chan != NULL) {
            (void)i2s_channel_write(s_tx_chan, buffer, sizeof(s_audio_work_buffer), &bytes_written, pdMS_TO_TICKS(100));
        }
        samples_sent += chunk;
    }
}

/**
 * @brief Ensure I2S clocks, ES8311 DAC registers, and Class-D amplifier are active prior to playback.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t sub_audio_prepare_and_unmute(void)
{
    if (!s_audio_inited || s_tx_chan == NULL) {
        esp_err_t err = sub_audio_init(s_volume_pct);
        if (err != ESP_OK) {
            return err;
        }
    }

    /* 1. Ensure MCLK/SCLK/LRCK are running BEFORE waking ES8311 registers (Datasheet Page 8 Note 5) */
    if (s_tx_chan != NULL && !s_i2s_chan_enabled) {
        esp_err_t chan_err = i2s_channel_enable(s_tx_chan);
        if (chan_err == ESP_OK) {
            s_i2s_chan_enabled = true;
            vTaskDelay(pdMS_TO_TICKS(5));
        } else {
            ESP_LOGW(TAG, "i2s_channel_enable failed: %s", esp_err_to_name(chan_err));
        }
    }

    /* 2. If codec was placed into standby mid-session, re-initialize DAC registers and wait for CSM */
    if (s_codec_in_standby) {
        (void)es8311_init_dac_registers();
        s_codec_in_standby     = false;
        s_rtc_codec_in_standby = false;
        (void)sub_audio_wait_until_ready(SUB_AUDIO_CSM_SETTLE_TIMEOUT_MS);
        (void)sub_audio_set_volume(s_volume_pct);
    }

    /* 3. Ensure Class-D amplifier is unmuted (no-op with 0 ms delay when already warm in active session) */
    (void)sub_audio_park_warm(false);

    return ESP_OK;
}

/**
 * @brief Execute synthesized tone playback command.
 *
 * @param[in]    frequency_hz    Tone frequency in Hz.
 * @param[in]    duration_ms     Tone duration in ms.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t sub_audio_exec_tone(uint32_t frequency_hz, uint32_t duration_ms)
{
    ESP_LOGI(TAG, "Playing tone: %lu Hz for %lu ms (Vol: %u%%)", (unsigned long)frequency_hz,
             (unsigned long)duration_ms, s_volume_pct);
    esp_err_t ret = sub_audio_prepare_and_unmute();
    if (ret != ESP_OK) {
        return ret;
    }

    sub_audio_render_tone_samples(frequency_hz, duration_ms);
    return ESP_OK;
}

/**
 * @brief Execute raw PCM buffer playback command.
 *
 * @param[in]    samples         Pointer to 16-bit signed mono PCM samples.
 * @param[in]    sample_count    Number of samples.
 * @param[in]    sample_rate_hz  Sample rate in Hz.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t sub_audio_exec_pcm(const int16_t *samples, size_t sample_count, uint32_t sample_rate_hz)
{
    (void)sample_rate_hz;
    esp_err_t ret = sub_audio_prepare_and_unmute();
    if (ret != ESP_OK) {
        return ret;
    }

    sub_audio_render_pcm_samples(samples, sample_count);
    return ESP_OK;
}

/**
 * @brief Execute predefined acoustic presentation chime pattern.
 *
 * @param[in]    type            Chime pattern enumerator.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t sub_audio_exec_chime(uint8_t type)
{
    ESP_LOGI(TAG, "Executing acoustic presentation chime (Type %u)...", type);

    esp_err_t ret = sub_audio_prepare_and_unmute();
    if (ret != ESP_OK) {
        return ret;
    }

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
        for (int32_t i = 0; i < 2; i++) {
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
 * @brief Background FreeRTOS audio worker task.
 *
 * @details Streams synthesized tones, chimes, and PCM buffers at 240 MHz CPU clock and flushes
 *          the full 4-descriptor I2S DMA ring when the queue drains empty so short 50 ms button
 *          chirps are never clipped. The codec and Class-D amplifier remain warm during the
 *          active 30-second interactive session and enter <1 uA standby when the session ends.
 *
 * @param[in]    pvParameters    Creator task handle for startup synchronization.
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
            if (cmd.type == AUDIO_CMD_STOP) {
                break;
            }
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

            /* When queue drains empty, flush all 4 I2S DMA descriptors (64 ms) so trailing samples never clip */
            if (uxQueueMessagesWaiting(s_audio_queue) == 0) {
                (void)sub_audio_flush_frame();
            }

            if (cmd.result) {
                *cmd.result = res;
            }

            if (cmd.done_sem) {
                (void)xSemaphoreGive(cmd.done_sem);
            }

            audio_cpu_max_release();
            s_audio_is_busy = false;
            if (uxQueueMessagesWaiting(s_audio_queue) == 0 && s_audio_idle_sem != NULL) {
                (void)xSemaphoreGive(s_audio_idle_sem);
            }
        }
    }

    s_audio_is_busy     = false;
    s_audio_task_handle = NULL;
    if (s_audio_stop_sem != NULL) {
        (void)xSemaphoreGive(s_audio_stop_sem);
    }
    vTaskDelete(NULL);
}

/**
 * @brief Enqueue an audio command to the background worker task.
 *
 * @param[in]    cmd             Pointer to command descriptor.
 * @param[in]    is_sync         True to block until playback completes.
 * @param[in]    wait_ms         Queue send / completion timeout in ms.
 *
 * @return ESP_OK on success, or an error code.
 */
static esp_err_t sub_audio_send_command(const audio_cmd_t *cmd, bool is_sync, uint32_t wait_ms)
{
    if (s_audio_queue == NULL || s_audio_task_handle == NULL) {
        esp_err_t err = sub_audio_init(s_volume_pct);
        if (err != ESP_OK) {
            return err;
        }
    }

    if (s_cmd_sync_sem == NULL) {
        s_cmd_sync_sem = xSemaphoreCreateBinaryStatic(&s_cmd_sync_sem_buffer);
    }

    audio_cmd_t local_cmd = *cmd;
    esp_err_t exec_result = ESP_OK;

    if (is_sync) {
        (void)xSemaphoreTake(s_cmd_sync_sem, 0);
        local_cmd.done_sem = s_cmd_sync_sem;
        local_cmd.result   = &exec_result;
    } else {
        local_cmd.done_sem = NULL;
        local_cmd.result   = NULL;
    }

    if (xQueueSend(s_audio_queue, &local_cmd, pdMS_TO_TICKS(wait_ms)) != pdTRUE) {
        return ESP_ERR_TIMEOUT;
    }

    if (is_sync) {
        const uint32_t timeout_ms = (wait_ms > 0) ? wait_ms : SUB_AUDIO_DEFAULT_WAIT_TIMEOUT_MS;
        if (xSemaphoreTake(s_cmd_sync_sem, pdMS_TO_TICKS(timeout_ms)) != pdTRUE) {
            ESP_LOGE(TAG, "Audio command timed out waiting for worker execution");
            return ESP_ERR_TIMEOUT;
        }
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
 * @param[in]    data            Pointer to payload parameters or PCM buffer.
 * @param[in]    len             Length of data payload in bytes.
 *
 * @return ESP_OK on success, ESP_ERR_TIMEOUT if queue is full, or ESP_ERR_INVALID_ARG.
 */
esp_err_t sub_audio_play(sub_audio_type_t type, const void *data, size_t len)
{
    if (data == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    audio_cmd_t cmd = {0};

    switch (type) {
    case SUB_AUDIO_TONE: {
        const uint32_t *params = (const uint32_t *)data;
        if (len < (2 * sizeof(uint32_t))) {
            return ESP_ERR_INVALID_ARG;
        }
        cmd.type                     = AUDIO_CMD_TONE;
        cmd.params.tone.frequency_hz = params[0];
        cmd.params.tone.duration_ms  = params[1];
        break;
    }
    case SUB_AUDIO_CHIME: {
        if (len < 1) {
            return ESP_ERR_INVALID_ARG;
        }
        cmd.type                    = AUDIO_CMD_CHIME;
        cmd.params.chime.chime_type = *(const uint8_t *)data;
        break;
    }
    case SUB_AUDIO_PCM: {
        if (len < sizeof(int16_t)) {
            return ESP_ERR_INVALID_ARG;
        }
        cmd.type                      = AUDIO_CMD_PCM;
        cmd.params.pcm.samples        = (const int16_t *)data;
        cmd.params.pcm.sample_count   = len / sizeof(int16_t);
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
    if (s_audio_is_busy) {
        return true;
    }

    if (s_audio_queue && uxQueueMessagesWaiting(s_audio_queue) > 0) {
        return true;
    }

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
    if (!sub_audio_is_busy()) {
        return ESP_OK;
    }
    if (s_audio_idle_sem == NULL) {
        s_audio_idle_sem = xSemaphoreCreateBinaryStatic(&s_audio_idle_sem_buffer);
    }

    TickType_t start_ticks   = xTaskGetTickCount();
    TickType_t timeout_ticks = pdMS_TO_TICKS(timeout_ms);

    while (sub_audio_is_busy()) {
        TickType_t elapsed = xTaskGetTickCount() - start_ticks;
        if (elapsed >= timeout_ticks) {
            return ESP_ERR_TIMEOUT;
        }
        (void)xSemaphoreTake(s_audio_idle_sem, timeout_ticks - elapsed);
    }
    return ESP_OK;
}

/**
 * @brief Teardown audio subsystem, stop background worker task cleanly, and delete I2S channel.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_audio_deinit(void)
{
    (void)sub_audio_wait_idle(1000);

    if (s_audio_task_handle != NULL && s_audio_queue != NULL) {
        if (s_audio_stop_sem == NULL) {
            s_audio_stop_sem = xSemaphoreCreateBinaryStatic(&s_audio_stop_sem_buffer);
        }
        (void)xSemaphoreTake(s_audio_stop_sem, 0);
        audio_cmd_t stop_cmd = {.type = AUDIO_CMD_STOP};
        if (xQueueSendToBack(s_audio_queue, &stop_cmd, pdMS_TO_TICKS(50)) != pdTRUE) {
            (void)xQueueReset(s_audio_queue);
            (void)xQueueSendToBack(s_audio_queue, &stop_cmd, 0);
        }
        (void)xSemaphoreTake(s_audio_stop_sem, pdMS_TO_TICKS(500));
        if (s_audio_task_handle != NULL) {
            vTaskDelete(s_audio_task_handle);
            s_audio_task_handle = NULL;
        }
    }

    (void)sub_audio_standby();

    if (s_tx_chan != NULL) {
        if (s_i2s_chan_enabled) {
            (void)i2s_channel_disable(s_tx_chan);
            s_i2s_chan_enabled = false;
        }
        (void)i2s_del_channel(s_tx_chan);
        s_tx_chan = NULL;
    }

    if (s_audio_queue != NULL) {
        (void)xQueueReset(s_audio_queue);
    }

#if CONFIG_PM_ENABLE
    if (s_audio_pm_lock != NULL) {
        (void)esp_pm_lock_delete(s_audio_pm_lock);
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
    if (volume_pct > 100) {
        volume_pct = 100;
    }
    s_volume_pct = volume_pct;

    if (s_audio_inited && s_i2s_chan_enabled && !s_codec_in_standby) {
        uint8_t vol_reg = volume_pct_to_es8311_reg(s_volume_pct);
        esp_err_t err   = es8311_write_reg(ES8311_REG_DAC_VOL, vol_reg);
        if (err != ESP_OK) {
            ESP_LOGE(TAG, "Failed to set volume register: %s", esp_err_to_name(err));
            return err;
        }
        ESP_LOGI(TAG, "Volume set to %u [0x%02X]", volume_pct, vol_reg);
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
 * @details In low-power mode (default upon init), ES8311 operates with LPDAC and all low-power
 *          reference modes enabled (Reg 0x0F = 0xFF), significantly reducing active DAC bias current.
 *          Normal mode sets Reg 0x0F = 0x00 for standard bias.
 *
 * @param[in]    enable          true for Low-Power Mode (default), false for Normal Power Mode.
 *
 * @return ESP_OK on success.
 */
esp_err_t sub_audio_set_low_power_mode(bool enable)
{
    s_low_power_mode = enable;
    if (s_audio_inited && s_i2s_chan_enabled && !s_codec_in_standby) {
        return es8311_write_reg(ES8311_REG_SYS_LP_MOD, enable ? 0xFFU : 0x00U);
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
