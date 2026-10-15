# API Reference

## Classes

| Name | Description |
|------|-------------|
| [`audio_cmd_t`](#audio_cmd_t) |  |
| [`h1os_lifecycle_t`](#h1os_lifecycle_t) |  |
| [`h1os_telemetry_t`](#h1os_telemetry_t) |  |
| [`h1os_wake_context_t`](#h1os_wake_context_t) |  |
| [`orch_persisted_state_t`](#orch_persisted_state_t) |  |
| [`orch_tri_node_sample_t`](#orch_tri_node_sample_t) |  |
| [`[struct].s_lipo_table`](#structs_lipo_table) |  |
| [`[struct].params.pcm`](#structparamspcm) |  |
| [`[struct].params.tone`](#structparamstone) |  |
| [`[struct].session`](#structsession) |  |
| [`[struct].params.chime`](#structparamschime) |  |
| [`[struct].presentation`](#structpresentation) |  |

## Macros

---

{#h1os_name}

### H1OS_NAME

```cpp
#define H1OS_NAME "H1OS"
```

Defined in h1os/h1os.h:33

---

{#h1os_subtitle}

### H1OS_SUBTITLE

```cpp
#define H1OS_SUBTITLE "E-Class Environmental Operating System"
```

Defined in h1os/h1os.h:34

---

{#h1os_version_major}

### H1OS_VERSION_MAJOR

```cpp
#define H1OS_VERSION_MAJOR 2
```

Defined in h1os/h1os.h:35

---

{#h1os_version_minor}

### H1OS_VERSION_MINOR

```cpp
#define H1OS_VERSION_MINOR 0
```

Defined in h1os/h1os.h:36

---

{#h1os_version_patch}

### H1OS_VERSION_PATCH

```cpp
#define H1OS_VERSION_PATCH 0
```

Defined in h1os/h1os.h:37

---

{#h1os_version_tag}

### H1OS_VERSION_TAG

```cpp
#define H1OS_VERSION_TAG "dev"
```

Defined in h1os/h1os.h:38

---

{#h1os_version_string}

### H1OS_VERSION_STRING

```cpp
#define H1OS_VERSION_STRING "2.0.0-dev"
```

Defined in h1os/h1os.h:39

---

{#sub_nvs_namespace}

### SUB_NVS_NAMESPACE

```cpp
#define SUB_NVS_NAMESPACE "h1os"
```

Defined in h1os/sub_nvs.h:22

---

{#rtc_reg_control_1}

### RTC_REG_CONTROL_1

```cpp
#define RTC_REG_CONTROL_1 0x00
```

Defined in sub_rtc.c:17

---

{#rtc_reg_control_2}

### RTC_REG_CONTROL_2

```cpp
#define RTC_REG_CONTROL_2 0x01
```

Defined in sub_rtc.c:18

---

{#rtc_reg_offset}

### RTC_REG_OFFSET

```cpp
#define RTC_REG_OFFSET 0x02
```

Defined in sub_rtc.c:19

---

{#rtc_reg_ram_byte}

### RTC_REG_RAM_BYTE

```cpp
#define RTC_REG_RAM_BYTE 0x03
```

Defined in sub_rtc.c:20

---

{#rtc_reg_seconds}

### RTC_REG_SECONDS

```cpp
#define RTC_REG_SECONDS 0x04
```

Defined in sub_rtc.c:21

---

{#rtc_reg_minutes}

### RTC_REG_MINUTES

```cpp
#define RTC_REG_MINUTES 0x05
```

Defined in sub_rtc.c:22

---

{#rtc_reg_hours}

### RTC_REG_HOURS

```cpp
#define RTC_REG_HOURS 0x06
```

Defined in sub_rtc.c:23

---

{#rtc_reg_days}

### RTC_REG_DAYS

```cpp
#define RTC_REG_DAYS 0x07
```

Defined in sub_rtc.c:24

---

{#rtc_reg_weekdays}

### RTC_REG_WEEKDAYS

```cpp
#define RTC_REG_WEEKDAYS 0x08
```

Defined in sub_rtc.c:25

---

{#rtc_reg_months}

### RTC_REG_MONTHS

```cpp
#define RTC_REG_MONTHS 0x09
```

Defined in sub_rtc.c:26

---

{#rtc_reg_years}

### RTC_REG_YEARS

```cpp
#define RTC_REG_YEARS 0x0A
```

Defined in sub_rtc.c:27

---

{#rtc_reg_alarm_sec}

### RTC_REG_ALARM_SEC

```cpp
#define RTC_REG_ALARM_SEC 0x0B
```

Defined in sub_rtc.c:28

---

{#rtc_reg_timer_value}

### RTC_REG_TIMER_VALUE

```cpp
#define RTC_REG_TIMER_VALUE 0x10
```

Defined in sub_rtc.c:29

---

{#rtc_reg_timer_mode}

### RTC_REG_TIMER_MODE

```cpp
#define RTC_REG_TIMER_MODE 0x11
```

Defined in sub_rtc.c:30

---

{#ctrl1_stop_mask}

### CTRL1_STOP_MASK

```cpp
#define CTRL1_STOP_MASK (1 << 5)
```

Defined in sub_rtc.c:33

---

{#ctrl1_12_24_mask}

### CTRL1_12_24_MASK

```cpp
#define CTRL1_12_24_MASK (1 << 1)
```

Defined in sub_rtc.c:34

---

{#ctrl1_cap_sel_12_5pf}

### CTRL1_CAP_SEL_12_5PF

```cpp
#define CTRL1_CAP_SEL_12_5PF (1 << 0)
```

Defined in sub_rtc.c:35

---

{#ctrl1_sw_reset_cmd}

### CTRL1_SW_RESET_CMD

```cpp
#define CTRL1_SW_RESET_CMD 0x58
```

Defined in sub_rtc.c:36

---

{#ctrl2_af_mask}

### CTRL2_AF_MASK

```cpp
#define CTRL2_AF_MASK (1 << 6)
```

Defined in sub_rtc.c:39

---

{#ctrl2_tf_mask}

### CTRL2_TF_MASK

```cpp
#define CTRL2_TF_MASK (1 << 3)
```

Defined in sub_rtc.c:40

---

{#ctrl2_aie_mask}

### CTRL2_AIE_MASK

```cpp
#define CTRL2_AIE_MASK (1 << 7)
```

Defined in sub_rtc.c:41

---

{#ctrl2_cof_off}

### CTRL2_COF_OFF

```cpp
#define CTRL2_COF_OFF 0x07
```

Defined in sub_rtc.c:42

---

{#timer_clk_4096_hz}

### TIMER_CLK_4096_HZ

```cpp
#define TIMER_CLK_4096_HZ (0 << 3)
```

Defined in sub_rtc.c:45

---

{#timer_clk_64_hz}

### TIMER_CLK_64_HZ

```cpp
#define TIMER_CLK_64_HZ (1 << 3)
```

Defined in sub_rtc.c:46

---

{#timer_clk_1_hz}

### TIMER_CLK_1_HZ

```cpp
#define TIMER_CLK_1_HZ (2 << 3)
```

Defined in sub_rtc.c:47

---

{#timer_clk_1_60_hz}

### TIMER_CLK_1_60_HZ

```cpp
#define TIMER_CLK_1_60_HZ (3 << 3)
```

Defined in sub_rtc.c:48

---

{#timer_enable_bit}

### TIMER_ENABLE_BIT

```cpp
#define TIMER_ENABLE_BIT (1 << 2)
```

Defined in sub_rtc.c:49

---

{#timer_int_enable_bit}

### TIMER_INT_ENABLE_BIT

```cpp
#define TIMER_INT_ENABLE_BIT (1 << 1)
```

Defined in sub_rtc.c:50

---

{#hal_pin_power_hold}

### HAL_PIN_POWER_HOLD

```cpp
#define HAL_PIN_POWER_HOLD GPIO_NUM_17
```

Defined in h1os/hal_types.h:30

Master LDO Power Latch (BAT_CTRL): Active HIGH.

---

{#hal_pin_battery_adc}

### HAL_PIN_BATTERY_ADC

```cpp
#define HAL_PIN_BATTERY_ADC GPIO_NUM_4
```

Defined in h1os/hal_types.h:31

Battery Voltage Sensing: ADC1_CHANNEL_3 (1:2 divider).

---

{#hal_pin_status_led}

### HAL_PIN_STATUS_LED

```cpp
#define HAL_PIN_STATUS_LED GPIO_NUM_3
```

Defined in h1os/hal_types.h:32

User LED: Open-Drain, Active LOW (0 = ON, 1 = OFF).

---

{#hal_pin_button_boot}

### HAL_PIN_BUTTON_BOOT

```cpp
#define HAL_PIN_BUTTON_BOOT GPIO_NUM_0
```

Defined in h1os/hal_types.h:35

Hardware BOOT0 Key: Active LOW (internal pullup req).

---

{#hal_pin_button_power}

### HAL_PIN_BUTTON_POWER

```cpp
#define HAL_PIN_BUTTON_POWER GPIO_NUM_18
```

Defined in h1os/hal_types.h:36

Hardware BAT_KEY: Active LOW (internal pullup req).

---

{#hal_pin_i2c_sda}

### HAL_PIN_I2C_SDA

```cpp
#define HAL_PIN_I2C_SDA GPIO_NUM_47
```

Defined in h1os/hal_types.h:39

Shared I2C Serial Data (SHTC3, PCF85063, ES8311).

---

{#hal_pin_i2c_scl}

### HAL_PIN_I2C_SCL

```cpp
#define HAL_PIN_I2C_SCL GPIO_NUM_48
```

Defined in h1os/hal_types.h:40

Shared I2C Serial Clock.

---

{#hal_pin_rtc_int}

### HAL_PIN_RTC_INT

```cpp
#define HAL_PIN_RTC_INT GPIO_NUM_5
```

Defined in h1os/hal_types.h:41

PCF85063A INT: Open-Drain (internal pullup mandatory).

---

{#hal_pin_epd_3v3_en}

### HAL_PIN_EPD_3V3_EN

```cpp
#define HAL_PIN_EPD_3V3_EN GPIO_NUM_6
```

Defined in h1os/hal_types.h:44

EPD 3.3V Rail Gate: Active LOW (0 = Rail ON).

---

{#hal_pin_epd_busy}

### HAL_PIN_EPD_BUSY

```cpp
#define HAL_PIN_EPD_BUSY GPIO_NUM_8
```

Defined in h1os/hal_types.h:45

Display Busy Line: Active HIGH (1 = Busy, 0 = Idle).

---

{#hal_pin_epd_rst}

### HAL_PIN_EPD_RST

```cpp
#define HAL_PIN_EPD_RST GPIO_NUM_9
```

Defined in h1os/hal_types.h:46

Display Hardware Reset: Active LOW.

---

{#hal_pin_epd_dc}

### HAL_PIN_EPD_DC

```cpp
#define HAL_PIN_EPD_DC GPIO_NUM_10
```

Defined in h1os/hal_types.h:47

Display Data / Command: 0 = Cmd, 1 = Data.

---

{#hal_pin_epd_cs}

### HAL_PIN_EPD_CS

```cpp
#define HAL_PIN_EPD_CS GPIO_NUM_11
```

Defined in h1os/hal_types.h:48

Display SPI Chip Select: Active LOW.

---

{#hal_pin_epd_sck}

### HAL_PIN_EPD_SCK

```cpp
#define HAL_PIN_EPD_SCK GPIO_NUM_12
```

Defined in h1os/hal_types.h:49

Display SPI Serial Clock (up to 20MHz).

---

{#hal_pin_epd_mosi}

### HAL_PIN_EPD_MOSI

```cpp
#define HAL_PIN_EPD_MOSI GPIO_NUM_13
```

Defined in h1os/hal_types.h:50

Display SPI Master Out Slave In.

---

{#hal_pin_pa_en}

### HAL_PIN_PA_EN

```cpp
#define HAL_PIN_PA_EN GPIO_NUM_42
```

Defined in h1os/hal_types.h:53

Amp Power Gate: Active LOW (1 = Power Cut, 0 = ON).

---

{#hal_pin_pa_ctrl}

### HAL_PIN_PA_CTRL

```cpp
#define HAL_PIN_PA_CTRL GPIO_NUM_46
```

Defined in h1os/hal_types.h:54

Amp Standby/Mute: Active HIGH (0 = Mute, 1 = Enable).

---

{#hal_pin_i2s_mclk}

### HAL_PIN_I2S_MCLK

```cpp
#define HAL_PIN_I2S_MCLK GPIO_NUM_14
```

Defined in h1os/hal_types.h:55

Master Clock (256 * Fs).

---

{#hal_pin_i2s_sclk}

### HAL_PIN_I2S_SCLK

```cpp
#define HAL_PIN_I2S_SCLK GPIO_NUM_15
```

Defined in h1os/hal_types.h:56

Bit / Serial Clock.

---

{#hal_pin_i2s_asdout}

### HAL_PIN_I2S_ASDOUT

```cpp
#define HAL_PIN_I2S_ASDOUT GPIO_NUM_16
```

Defined in h1os/hal_types.h:57

Codec Audio Out to ESP32 (DIN).

---

{#hal_pin_i2s_lrck}

### HAL_PIN_I2S_LRCK

```cpp
#define HAL_PIN_I2S_LRCK GPIO_NUM_38
```

Defined in h1os/hal_types.h:58

Word Select / Frame Sync (WS).

---

{#hal_pin_i2s_dsdin}

### HAL_PIN_I2S_DSDIN

```cpp
#define HAL_PIN_I2S_DSDIN GPIO_NUM_45
```

Defined in h1os/hal_types.h:59

ESP32 Audio Out to Codec (DOUT).

---

{#hal_pin_sd_clk}

### HAL_PIN_SD_CLK

```cpp
#define HAL_PIN_SD_CLK GPIO_NUM_39
```

Defined in h1os/hal_types.h:62

MicroSD Clock.

---

{#hal_pin_sd_miso}

### HAL_PIN_SD_MISO

```cpp
#define HAL_PIN_SD_MISO GPIO_NUM_40
```

Defined in h1os/hal_types.h:63

MicroSD MISO / D0.

---

{#hal_pin_sd_mosi}

### HAL_PIN_SD_MOSI

```cpp
#define HAL_PIN_SD_MOSI GPIO_NUM_41
```

Defined in h1os/hal_types.h:64

MicroSD MOSI / CMD.

---

{#hal_i2c_addr_es8311}

### HAL_I2C_ADDR_ES8311

```cpp
#define HAL_I2C_ADDR_ES8311 0x18
```

Defined in h1os/hal_types.h:69

Everest Semi Audio Codec.

---

{#hal_i2c_addr_pcf85063}

### HAL_I2C_ADDR_PCF85063

```cpp
#define HAL_I2C_ADDR_PCF85063 0x51
```

Defined in h1os/hal_types.h:70

NXP Calendar RTC.

---

{#hal_i2c_addr_shtc3}

### HAL_I2C_ADDR_SHTC3

```cpp
#define HAL_I2C_ADDR_SHTC3 0x70
```

Defined in h1os/hal_types.h:71

Sensirion Temp / Humidity Sensor.

---

{#hal_i2c_freq_hz}

### HAL_I2C_FREQ_HZ

```cpp
#define HAL_I2C_FREQ_HZ 400000
```

Defined in h1os/hal_types.h:73

Fast-mode 400 kHz.

---

{#hal_epd_width_px}

### HAL_EPD_WIDTH_PX

```cpp
#define HAL_EPD_WIDTH_PX 200
```

Defined in h1os/hal_types.h:78

---

{#hal_epd_height_px}

### HAL_EPD_HEIGHT_PX

```cpp
#define HAL_EPD_HEIGHT_PX 200
```

Defined in h1os/hal_types.h:79

---

{#hal_epd_dpi}

### HAL_EPD_DPI

```cpp
#define HAL_EPD_DPI 188
```

Defined in h1os/hal_types.h:80

---

{#hal_epd_frame_size_bytes}

### HAL_EPD_FRAME_SIZE_BYTES

```cpp
#define HAL_EPD_FRAME_SIZE_BYTES ((HAL_EPD_WIDTH_PX * HAL_EPD_HEIGHT_PX) / 8)
```

Defined in h1os/hal_types.h:81

---

{#hal_partition_epd_frame}

### HAL_PARTITION_EPD_FRAME

```cpp
#define HAL_PARTITION_EPD_FRAME "epd_frame"
```

Defined in h1os/hal_types.h:83

16KB dedicated SPI flash partition

---

{#hal_partition_storage}

### HAL_PARTITION_STORAGE

```cpp
#define HAL_PARTITION_STORAGE "storage"
```

Defined in h1os/hal_types.h:84

SPIFFS / LittleFS partition.

---

{#orch_historical_ewma_alpha}

### ORCH_HISTORICAL_EWMA_ALPHA

```cpp
#define ORCH_HISTORICAL_EWMA_ALPHA 0.25f
```

Defined in orch_flow.c:34

---

{#orch_leakage_margin_c}

### ORCH_LEAKAGE_MARGIN_C

```cpp
#define ORCH_LEAKAGE_MARGIN_C 0.30f
```

Defined in orch_flow.c:35

---

{#orch_trinode_span_c}

### ORCH_TRINODE_SPAN_C

```cpp
#define ORCH_TRINODE_SPAN_C 15.0f
```

Defined in orch_flow.c:36

---

{#magnus_a}

### MAGNUS_A

```cpp
#define MAGNUS_A 17.625f
```

Defined in orch_math.c:11

---

{#magnus_b}

### MAGNUS_B

```cpp
#define MAGNUS_B 243.04f
```

Defined in orch_math.c:12

---

{#es8311_reg_reset}

### ES8311_REG_RESET

```cpp
#define ES8311_REG_RESET 0x00
```

Defined in sub_audio.c:34

---

{#es8311_reg_sys_pwr_ana}

### ES8311_REG_SYS_PWR_ANA

```cpp
#define ES8311_REG_SYS_PWR_ANA 0x0D
```

Defined in sub_audio.c:35

---

{#es8311_reg_sys_lp_mod}

### ES8311_REG_SYS_LP_MOD

```cpp
#define ES8311_REG_SYS_LP_MOD 0x0F
```

Defined in sub_audio.c:36

---

{#es8311_reg_dac_pwr}

### ES8311_REG_DAC_PWR

```cpp
#define ES8311_REG_DAC_PWR 0x12
```

Defined in sub_audio.c:37

---

{#es8311_reg_dac_vol}

### ES8311_REG_DAC_VOL

```cpp
#define ES8311_REG_DAC_VOL 0x32
```

Defined in sub_audio.c:38

---

{#es8311_reg_flag}

### ES8311_REG_FLAG

```cpp
#define ES8311_REG_FLAG 0xFC
```

Defined in sub_audio.c:39

---

{#es8311_reg_chip_id1}

### ES8311_REG_CHIP_ID1

```cpp
#define ES8311_REG_CHIP_ID1 0xFD
```

Defined in sub_audio.c:40

---

{#es8311_reg_chip_id2}

### ES8311_REG_CHIP_ID2

```cpp
#define ES8311_REG_CHIP_ID2 0xFE
```

Defined in sub_audio.c:41

---

{#frame_size}

### FRAME_SIZE

```cpp
#define FRAME_SIZE 0x100
```

Defined in sub_audio.c:43

---

{#lipo_table_size}

### LIPO_TABLE_SIZE

```cpp
#define LIPO_TABLE_SIZE (sizeof(s_lipo_table) / sizeof(s_lipo_table[0]))
```

Defined in sub_power.c:47

---

{#orch_rtc_magic}

### ORCH_RTC_MAGIC

```cpp
#define ORCH_RTC_MAGIC 0x534C4154
```

Defined in h1os/orch_state.h:21

---

{#orch_ring_capacity}

### ORCH_RING_CAPACITY

```cpp
#define ORCH_RING_CAPACITY 32
```

Defined in h1os/orch_state.h:22

---

{#sample_flag_valid_cold}

### SAMPLE_FLAG_VALID_COLD

```cpp
#define SAMPLE_FLAG_VALID_COLD 0x01
```

Defined in h1os/orch_state.h:33

---

{#sample_flag_thermal_settled}

### SAMPLE_FLAG_THERMAL_SETTLED

```cpp
#define SAMPLE_FLAG_THERMAL_SETTLED 0x02
```

Defined in h1os/orch_state.h:34

---

{#sample_delta_gate_centi_c}

### SAMPLE_DELTA_GATE_CENTI_C

```cpp
#define SAMPLE_DELTA_GATE_CENTI_C 20
```

Defined in h1os/orch_state.h:35

---

{#orch_flag_none}

### ORCH_FLAG_NONE

```cpp
#define ORCH_FLAG_NONE 0
```

Defined in h1os/orch_state.h:105

---

{#orch_flag_epd_frame_valid}

### ORCH_FLAG_EPD_FRAME_VALID

```cpp
#define ORCH_FLAG_EPD_FRAME_VALID (1 << 0)
```

Defined in h1os/orch_state.h:106

---

{#orch_flag_critical_battery}

### ORCH_FLAG_CRITICAL_BATTERY

```cpp
#define ORCH_FLAG_CRITICAL_BATTERY (1 << 1)
```

Defined in h1os/orch_state.h:107

---

{#orch_flag_thermal_lockout}

### ORCH_FLAG_THERMAL_LOCKOUT

```cpp
#define ORCH_FLAG_THERMAL_LOCKOUT (1 << 2)
```

Defined in h1os/orch_state.h:108

---

{#sub_sdcard_mount_point}

### SUB_SDCARD_MOUNT_POINT

```cpp
#define SUB_SDCARD_MOUNT_POINT "/sdcard"
```

Defined in h1os/sub_sdcard.h:26

---

{#shtc3_cmd_wakeup}

### SHTC3_CMD_WAKEUP

```cpp
#define SHTC3_CMD_WAKEUP 0x3517
```

Defined in sub_sensor.c:22

---

{#shtc3_cmd_sleep}

### SHTC3_CMD_SLEEP

```cpp
#define SHTC3_CMD_SLEEP 0xB098
```

Defined in sub_sensor.c:23

---

{#shtc3_cmd_meas_normal_t_first}

### SHTC3_CMD_MEAS_NORMAL_T_FIRST

```cpp
#define SHTC3_CMD_MEAS_NORMAL_T_FIRST 0x7866
```

Defined in sub_sensor.c:24

---

{#shtc3_cmd_meas_lowpwr_t_first}

### SHTC3_CMD_MEAS_LOWPWR_T_FIRST

```cpp
#define SHTC3_CMD_MEAS_LOWPWR_T_FIRST 0x609C
```

Defined in sub_sensor.c:25

---

{#epd_width}

### EPD_WIDTH

```cpp
#define EPD_WIDTH 200
```

Defined in h1os/sub_display.h:23

---

{#epd_height}

### EPD_HEIGHT

```cpp
#define EPD_HEIGHT 200
```

Defined in h1os/sub_display.h:24

---

{#epd_buffer_size}

### EPD_BUFFER_SIZE

```cpp
#define EPD_BUFFER_SIZE ((EPD_WIDTH * EPD_HEIGHT) / 8)
```

Defined in h1os/sub_display.h:26

---

{#lvgl_i1_palette_size}

### LVGL_I1_PALETTE_SIZE

```cpp
#define LVGL_I1_PALETTE_SIZE 8
```

Defined in h1os_lvgl.cpp:34

---

{#sens_sar_peri_clk_gate_conf_reg}

### SENS_SAR_PERI_CLK_GATE_CONF_REG

```cpp
#define SENS_SAR_PERI_CLK_GATE_CONF_REG (DR_REG_SENS_BASE + 0x104)
```

Defined in orch_wake_stub.c:25

---

{#sens_tsens_clk_en}

### SENS_TSENS_CLK_EN

```cpp
#define SENS_TSENS_CLK_EN (1UL << 29)
```

Defined in orch_wake_stub.c:28

---

{#sda_bit_mask}

### SDA_BIT_MASK

```cpp
#define SDA_BIT_MASK (1UL << (HAL_PIN_I2C_SDA - 32))
```

Defined in orch_wake_stub.c:31

---

{#scl_bit_mask}

### SCL_BIT_MASK

```cpp
#define SCL_BIT_MASK (1UL << (HAL_PIN_I2C_SCL - 32))
```

Defined in orch_wake_stub.c:32

---

{#i2c_addr_shtc3}

### I2C_ADDR_SHTC3

```cpp
#define I2C_ADDR_SHTC3 0x70
```

Defined in orch_wake_stub.c:34

---

{#i2c_addr_pcf85063}

### I2C_ADDR_PCF85063

```cpp
#define I2C_ADDR_PCF85063 0x51
```

Defined in orch_wake_stub.c:35

---

{#rtc_reg_timer_val}

### RTC_REG_TIMER_VAL

```cpp
#define RTC_REG_TIMER_VAL 0x10
```

Defined in orch_wake_stub.c:36

---

{#rtc_timer_te_bit}

### RTC_TIMER_TE_BIT

```cpp
#define RTC_TIMER_TE_BIT (1 << 2)
```

Defined in orch_wake_stub.c:38

---

{#rtc_timer_tcf_mask}

### RTC_TIMER_TCF_MASK

```cpp
#define RTC_TIMER_TCF_MASK (3 << 3)
```

Defined in orch_wake_stub.c:39

---

{#rtc_timer_tcf_min}

### RTC_TIMER_TCF_MIN

```cpp
#define RTC_TIMER_TCF_MIN (3 << 3)
```

Defined in orch_wake_stub.c:40

---

{#config_h1os_epd_partial_refresh_limit}

### CONFIG_H1OS_EPD_PARTIAL_REFRESH_LIMIT

```cpp
#define CONFIG_H1OS_EPD_PARTIAL_REFRESH_LIMIT 6
```

Defined in orch_display_sync.c:17

## Enumerations

---

{#h1os_splash_type_t}

### h1os_splash_type_t

```cpp
enum h1os_splash_type_t
```

Defined in h1os/h1os.h:55

| Value | Description |
|-------|-------------|
| `H1OS_SPLASH_BOOT` |  |
| `H1OS_SPLASH_WAKE` |  |
| `H1OS_SPLASH_SLEEP` |  |
| `H1OS_SPLASH_SHUTDOWN` |  |
| `H1OS_SPLASH_MAX` |  |

---

{#h1os_chime_type_t}

### h1os_chime_type_t

```cpp
enum h1os_chime_type_t
```

Defined in h1os/h1os.h:63

| Value | Description |
|-------|-------------|
| `H1OS_CHIME_BOOT` |  |
| `H1OS_CHIME_WAKE` |  |
| `H1OS_CHIME_SLEEP` |  |
| `H1OS_CHIME_SHUTDOWN` |  |
| `H1OS_CHIME_ALARM` |  |
| `H1OS_CHIME_MAX` |  |

---

{#h1os_time_format_t}

### h1os_time_format_t

```cpp
enum h1os_time_format_t
```

Defined in h1os/h1os_time.h:20

| Value | Description |
|-------|-------------|
| `H1OS_TIME_FMT_24H_SEC` | "14:35:08" |
| `H1OS_TIME_FMT_24H_MIN` | "14:35" |
| `H1OS_TIME_FMT_12H_SEC` | "02:35:08 PM" |
| `H1OS_TIME_FMT_12H_MIN` | "02:35 PM" |

---

{#h1os_date_format_t}

### h1os_date_format_t

```cpp
enum h1os_date_format_t
```

Defined in h1os/h1os_time.h:27

| Value | Description |
|-------|-------------|
| `H1OS_DATE_FMT_MM_DD_YY` | "09/26/26" |
| `H1OS_DATE_FMT_DOW` | "Saturday" |
| `H1OS_DATE_FMT_MM_DD_YY_DOW` | "09/26/26 Saturday" |

---

{#hal_btn_mask_t}

### hal_btn_mask_t

```cpp
enum hal_btn_mask_t
```

Defined in h1os/hal_types.h:89

| Value | Description |
|-------|-------------|
| `HAL_BTN_NONE` |  |
| `HAL_BTN_BOOT` |  |
| `HAL_BTN_POWER` |  |

---

{#h1os_init_mode_t}

### h1os_init_mode_t

```cpp
enum h1os_init_mode_t
```

Defined in h1os/hal_types.h:98

Initialization Modes for Dynamic Hardware Configuration.

| Value | Description |
|-------|-------------|
| `H1OS_INIT_MODE_BOOT` | Boot initialization: all hardware subsystems & LVGL initialized. |
| `H1OS_INIT_MODE_WAKE` | Wake initialization: fast display refresh retaining existing framebuffers. |
| `H1OS_INIT_MODE_SUB_EXEC` | Sub-execution initialization: scaled-back runtime (I2C + sensor only). |

---

{#h1os_sleep_mode_t}

### h1os_sleep_mode_t

```cpp
enum h1os_sleep_mode_t
```

Defined in h1os/hal_types.h:107

Sleep Execution Modes.

| Value | Description |
|-------|-------------|
| `H1OS_SLEEP_MODE_LIGHT` | Light sleep (RAM preserved, clock gated). |
| `H1OS_SLEEP_MODE_DEEP` | Deep sleep (Power down, RTC slow memory preserved). |

---

{#orch_flow_type_t}

### orch_flow_type_t

```cpp
enum orch_flow_type_t
```

Defined in h1os/orch_flow.h:24

| Value | Description |
|-------|-------------|
| `ORCH_FLOW_BOOT` | Initial system boot / power-on reset. |
| `ORCH_FLOW_A_SAMPLE` | Headless sensor sample burst. |
| `ORCH_FLOW_B_MAIN_WAKE` | Full UI wake / Button wake / RTC timer expiry. |
| `ORCH_FLOW_BOOTLOADER_JUMP` | ROM bootloader download mode. |
| `ORCH_FLOW_CRITICAL_OFF` | Low battery shutdown or power cut. |

---

{#audio_cmd_type_t}

### audio_cmd_type_t

```cpp
enum audio_cmd_type_t
```

Defined in sub_audio.c:46

| Value | Description |
|-------|-------------|
| `AUDIO_CMD_TONE` |  |
| `AUDIO_CMD_CHIME` |  |
| `AUDIO_CMD_PCM` |  |

---

{#orch_ulp_dispatch_t}

### orch_ulp_dispatch_t

```cpp
enum orch_ulp_dispatch_t
```

Defined in h1os/orch_state.h:24

| Value | Description |
|-------|-------------|
| `ULP_DISPATCH_NONE` |  |
| `ULP_DISPATCH_SENSOR_SAMPLE` |  |
| `ULP_DISPATCH_MAIN_WAKE` |  |
| `ULP_DISPATCH_CRITICAL_SHUTDOWN` |  |
| `ULP_DISPATCH_BOOTLOADER_JUMP` |  |
| `ULP_DISPATCH_POWER_OFF` |  |
## Typedefs

---

{#h1os_boot_cb_t}

### h1os_boot_cb_t

```cpp
using h1os_boot_cb_t = void(*)
```

Defined in h1os/h1os.h:72

---

{#h1os_wake_cb_t}

### h1os_wake_cb_t

```cpp
using h1os_wake_cb_t = void(*)
```

Defined in h1os/h1os.h:73

---

{#h1os_pre_sleep_cb_t}

### h1os_pre_sleep_cb_t

```cpp
using h1os_pre_sleep_cb_t = void(*)
```

Defined in h1os/h1os.h:74

---

{#h1os_shutdown_cb_t}

### h1os_shutdown_cb_t

```cpp
using h1os_shutdown_cb_t = void(*)
```

Defined in h1os/h1os.h:75

---

{#h1os_splash_cb_t}

### h1os_splash_cb_t

```cpp
using h1os_splash_cb_t = void(*)
```

Defined in h1os/h1os.h:76

---

{#h1os_chime_cb_t}

### h1os_chime_cb_t

```cpp
using h1os_chime_cb_t = void(*)
```

Defined in h1os/h1os.h:77

---

{#h1os_time_sync_cb_t}

### h1os_time_sync_cb_t

```cpp
using h1os_time_sync_cb_t = esp_err_t(*)
```

Defined in h1os/h1os_time.h:36

Callback for external network/remote time acquisition (SNTP, GPS, BLE).

## Functions

---

{#h1os_get_version}

### h1os_get_version

`static` `inline`

```cpp
static inline const char * h1os_get_version(void)
```

Defined in h1os/h1os.h:149

Get the H1OS semantic version string.

---

{#h1os_start}

### h1os_start

```cpp
esp_err_t h1os_start(const h1os_lifecycle_t * config)
```

Defined in h1os/h1os.h:157

Initialize H1OS and dispatch application lifecycle.

---

{#h1os_set_volume}

### h1os_set_volume

```cpp
esp_err_t h1os_set_volume(uint8_t volume_pct)
```

Defined in h1os/h1os.h:162

Set audio subsystem output volume percentage (0% = Mute, 100% = 0 dB Max).

---

{#h1os_get_telemetry}

### h1os_get_telemetry

```cpp
esp_err_t h1os_get_telemetry(h1os_telemetry_t * out_telemetry)
```

Defined in h1os/h1os.h:167

Retrieve current Tri-Node environmental telemetry.

---

{#h1os_sleep}

### h1os_sleep

```cpp
esp_err_t h1os_sleep(uint32_t sleep_sec)
```

Defined in h1os/h1os.h:172

Put the platform into ultra-low-power deep sleep.

---

{#h1os_reset_session_timer}

### h1os_reset_session_timer

```cpp
void h1os_reset_session_timer(void)
```

Defined in h1os/h1os.h:177

Reset the interactive session inactivity timer (extends session by timeout_sec).

---

{#h1os_is_session_active}

### h1os_is_session_active

```cpp
bool h1os_is_session_active(void)
```

Defined in h1os/h1os.h:184

Check whether an interactive inactivity countdown session is active.

#### Returns
true if running in an interactive user session, false during unattended wakes.

---

{#h1os_shutdown}

### h1os_shutdown

```cpp
void h1os_shutdown(void)
```

Defined in h1os/h1os.h:189

Orderly system shutdown and physical battery power cut.

---

{#h1os_shutdown_for_storage}

### h1os_shutdown_for_storage

```cpp
void h1os_shutdown_for_storage(void)
```

Defined in h1os/h1os.h:195

Shutdown for long-term storage: clears display to pure white before cutting power.

Protects e-Paper electrophoretic microcapsules against permanent dye migration and burn-in.

---

{#hal_io_early_init}

### hal_io_early_init

```cpp
esp_err_t hal_io_early_init(void)
```

Defined in h1os/hal_io.h:30

Early boot initialization of non-latched application pins.

Releases sleep pad holds on dynamic peripheral/wake pins, configures amplifier mute (GPIO 46), status LED (GPIO 3), buttons (GPIO 0/18), and RTC INT (GPIO 5). Note: Master power rails (GPIO 17 BAT_CTRL, GPIO 6 EPD_3V3_EN, GPIO 42 PA_EN) are strictly latched in the 2nd-stage bootloader (h1os_boot_hook.c).

#### Returns
ESP_OK on success, or driver error code.

---

{#hal_io_set_led}

### hal_io_set_led

```cpp
esp_err_t hal_io_set_led(bool on)
```

Defined in h1os/hal_io.h:38

Controls user status LED (GPIO 3, Active LOW).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `on` | `bool` | True to turn LED ON (drive 0); False to turn OFF (drive 1). |

---

{#hal_io_release_power_latch}

### hal_io_release_power_latch

```cpp
esp_err_t hal_io_release_power_latch(void)
```

Defined in h1os/hal_io.h:47

Releases the battery LDO power latch (GPIO 17 LOW, pad hold disabled) for physical power-down.

Strictly for system shutdown; assertion of GPIO 17 is handled exclusively by the 2nd-stage bootloader.

#### Returns
ESP_OK on success.

---

{#hal_io_read_buttons}

### hal_io_read_buttons

```cpp
hal_btn_mask_t hal_io_read_buttons(void)
```

Defined in h1os/hal_io.h:54

Samples instantaneous state of hardware tactile buttons.

#### Returns
Bitmask of currently depressed buttons (HAL_BTN_BOOT | HAL_BTN_POWER).

---

{#hal_io_button_is_pressed}

### hal_io_button_is_pressed

`static` `inline`

```cpp
static inline bool hal_io_button_is_pressed(gpio_num_t pin)
```

Defined in h1os/hal_io.h:62

Stateless check if a specific button pin is actively held down (Active LOW).

#### Returns
true if depressed, false otherwise

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `pin` | `gpio_num_t` | GPIO_NUM_0 (BOOT) or GPIO_NUM_18 (POWER) |

---

{#hal_io_isolate_sleep_pads}

### hal_io_isolate_sleep_pads

```cpp
esp_err_t hal_io_isolate_sleep_pads(void)
```

Defined in h1os/hal_io.h:76

Configures and locks dynamic peripheral lines prior to deep sleep.

* Latches GPIO 11 (EPD_CS) and GPIO 9 (EPD_RST) HIGH via gpio_hold_en().
* Holds amplifier mute GPIO 46 (PA_CTRL) LOW.
* Configures RTC IO pull-ups on wake inputs (GPIO 0, GPIO 5, GPIO 18).
* Preserves 2nd-stage bootloader holds on GPIO 17 (BAT_CTRL), GPIO 6 (EPD_3V3_EN), and GPIO 42 (PA_EN).

#### Returns
ESP_OK on success.

---

{#hal_io_release_pad_holds}

### hal_io_release_pad_holds

```cpp
esp_err_t hal_io_release_pad_holds(void)
```

Defined in h1os/hal_io.h:83

Releases sleep pad holds on dynamic peripheral/wake pins upon waking from deep sleep.

#### Returns
ESP_OK on success.

---

{#hal_check_usb_ll}

### hal_check_usb_ll

```cpp
bool hal_check_usb_ll(void)
```

Defined in h1os/hal_io.h:90

Check if USB Serial/JTAG is connected to an active host via SOF packets.

#### Returns
true if USB host connection detected, false otherwise.

---

{#hal_io_early_init-1}

### hal_io_early_init

```cpp
esp_err_t hal_io_early_init(void)
```

Defined in hal_io.c:18

Early boot initialization of non-latched application pins.

Releases sleep pad holds on dynamic peripheral/wake pins, configures amplifier mute (GPIO 46), status LED (GPIO 3), buttons (GPIO 0/18), and RTC INT (GPIO 5). Note: Master power rails (GPIO 17 BAT_CTRL, GPIO 6 EPD_3V3_EN, GPIO 42 PA_EN) are strictly latched in the 2nd-stage bootloader (h1os_boot_hook.c).

#### Returns
ESP_OK on success, or driver error code.

---

{#hal_io_release_power_latch-1}

### hal_io_release_power_latch

```cpp
esp_err_t hal_io_release_power_latch(void)
```

Defined in hal_io.c:71

Releases the battery LDO power latch (GPIO 17 LOW, pad hold disabled) for physical power-down.

Strictly for system shutdown; assertion of GPIO 17 is handled exclusively by the 2nd-stage bootloader.

#### Returns
ESP_OK on success.

---

{#hal_io_set_led-1}

### hal_io_set_led

```cpp
esp_err_t hal_io_set_led(bool on)
```

Defined in hal_io.c:81

Controls user status LED (GPIO 3, Active LOW).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `on` | `bool` | True to turn LED ON (drive 0); False to turn OFF (drive 1). |

---

{#hal_io_read_buttons-1}

### hal_io_read_buttons

```cpp
hal_btn_mask_t hal_io_read_buttons(void)
```

Defined in hal_io.c:87

Samples instantaneous state of hardware tactile buttons.

#### Returns
Bitmask of currently depressed buttons (HAL_BTN_BOOT | HAL_BTN_POWER).

---

{#hal_io_isolate_sleep_pads-1}

### hal_io_isolate_sleep_pads

```cpp
esp_err_t hal_io_isolate_sleep_pads(void)
```

Defined in hal_io.c:99

Configures and locks dynamic peripheral lines prior to deep sleep.

* Latches GPIO 11 (EPD_CS) and GPIO 9 (EPD_RST) HIGH via gpio_hold_en().
* Holds amplifier mute GPIO 46 (PA_CTRL) LOW.
* Configures RTC IO pull-ups on wake inputs (GPIO 0, GPIO 5, GPIO 18).
* Preserves 2nd-stage bootloader holds on GPIO 17 (BAT_CTRL), GPIO 6 (EPD_3V3_EN), and GPIO 42 (PA_EN).

#### Returns
ESP_OK on success.

---

{#hal_io_release_pad_holds-1}

### hal_io_release_pad_holds

```cpp
esp_err_t hal_io_release_pad_holds(void)
```

Defined in hal_io.c:143

Releases sleep pad holds on dynamic peripheral/wake pins upon waking from deep sleep.

#### Returns
ESP_OK on success.

---

{#hal_check_usb_ll-1}

### hal_check_usb_ll

```cpp
bool hal_check_usb_ll(void)
```

Defined in hal_io.c:160

Check if USB Serial/JTAG is connected to an active host via SOF packets.

#### Returns
true if USB host connection detected, false otherwise.

---

{#hal_i2c_init}

### hal_i2c_init

```cpp
esp_err_t hal_i2c_init(void)
```

Defined in h1os/hal_i2c.h:29

Initializes the shared I2C master bus hardware.

Installs ESP-IDF I2C driver on GPIO 47 / GPIO 48 and creates recursive mutex.

#### Returns
ESP_OK on success, or driver error code.

---

{#hal_i2c_deinit}

### hal_i2c_deinit

```cpp
esp_err_t hal_i2c_deinit(void)
```

Defined in h1os/hal_i2c.h:36

Deinitializes the shared I2C master bus and releases mutex.

#### Returns
ESP_OK on success.

---

{#hal_i2c_write}

### hal_i2c_write

```cpp
esp_err_t hal_i2c_write(uint8_t dev_addr, const uint8_t * write_data, size_t write_len, uint32_t timeout_ms)
```

Defined in h1os/hal_i2c.h:47

Executes an atomic register write transaction over I2C.

#### Returns
ESP_OK on success, ESP_ERR_TIMEOUT, or NACK error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `dev_addr` | `uint8_t` | 7-bit I2C device address. |
| `write_data` | `const uint8_t *` | Pointer to data buffer to transmit. |
| `write_len` | `size_t` | Length of write buffer in bytes. |
| `timeout_ms` | `uint32_t` | Timeout budget in milliseconds. |

---

{#hal_i2c_read}

### hal_i2c_read

```cpp
esp_err_t hal_i2c_read(uint8_t dev_addr, uint8_t * read_data, size_t read_len, uint32_t timeout_ms)
```

Defined in h1os/hal_i2c.h:58

Executes an atomic register read transaction over I2C.

#### Returns
ESP_OK on success, ESP_ERR_TIMEOUT, or NACK error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `dev_addr` | `uint8_t` | 7-bit I2C device address. |
| `read_data` | `uint8_t *` | Pointer to buffer to receive data. |
| `read_len` | `size_t` | Number of bytes to read. |
| `timeout_ms` | `uint32_t` | Timeout budget in milliseconds. |

---

{#hal_i2c_write_read}

### hal_i2c_write_read

```cpp
esp_err_t hal_i2c_write_read(uint8_t dev_addr, const uint8_t * write_data, size_t write_len, uint8_t * read_data, size_t read_len, uint32_t timeout_ms)
```

Defined in h1os/hal_i2c.h:71

Executes an atomic write-then-read combined transaction (Repeated START).

#### Returns
ESP_OK on success, ESP_ERR_TIMEOUT, or NACK error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `dev_addr` | `uint8_t` | 7-bit I2C device address. |
| `write_data` | `const uint8_t *` | Register address or command bytes to write. |
| `write_len` | `size_t` | Number of bytes to write. |
| `read_data` | `uint8_t *` | Destination buffer for read bytes. |
| `read_len` | `size_t` | Number of bytes to read. |
| `timeout_ms` | `uint32_t` | Timeout budget in milliseconds. |

---

{#hal_i2c_probe}

### hal_i2c_probe

```cpp
esp_err_t hal_i2c_probe(uint8_t dev_addr)
```

Defined in h1os/hal_i2c.h:82

Probes if an I2C device with given 7-bit address responds on the bus.

#### Returns
ESP_OK if device ACKed, ESP_ERR_NOT_FOUND or other error on NACK/timeout.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `dev_addr` | `uint8_t` | 7-bit device address. |

---

{#hal_spi_init}

### hal_spi_init

```cpp
esp_err_t hal_spi_init(void)
```

Defined in h1os/hal_spi.h:25

Initializes SPI2 Master host with DMA channel enabled for display communication.

#### Returns
ESP_OK on success, or driver error code.

---

{#hal_spi_deinit}

### hal_spi_deinit

```cpp
esp_err_t hal_spi_deinit(void)
```

Defined in h1os/hal_spi.h:32

Deinitializes SPI2 Master host and releases bus resources.

#### Returns
ESP_OK on success.

---

{#hal_spi_write_cmd}

### hal_spi_write_cmd

```cpp
esp_err_t hal_spi_write_cmd(uint8_t cmd)
```

Defined in h1os/hal_spi.h:40

Transmits a single command byte to the SSD1681 controller (DC = 0).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `cmd` | `uint8_t` | Command byte. |

---

{#hal_spi_write_data}

### hal_spi_write_data

```cpp
esp_err_t hal_spi_write_data(const uint8_t * data, size_t len)
```

Defined in h1os/hal_spi.h:49

Transmits data bytes to the SSD1681 controller (DC = 1).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `data` | `const uint8_t *` | Pointer to buffer containing payload. |
| `len` | `size_t` | Length of data in bytes. |

---

{#hal_spi_write_frame_dma}

### hal_spi_write_frame_dma

```cpp
esp_err_t hal_spi_write_frame_dma(const uint8_t * frame_buffer)
```

Defined in h1os/hal_spi.h:57

Transmits a full 5000-byte frame buffer via DMA transfer.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `frame_buffer` | `const uint8_t *` | Pointer to 5000-byte buffer. |

---

{#hal_spi_read_data}

### hal_spi_read_data

```cpp
esp_err_t hal_spi_read_data(uint8_t cmd, uint8_t * out_data, size_t len)
```

Defined in h1os/hal_spi.h:67

Reads data from SSD1681 (e.g.

on-glass thermal sensor Cmd 0x1B).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `cmd` | `uint8_t` | Command to write before reading. |
| `out_data` | `uint8_t *` | Buffer to receive read bytes. |
| `len` | `size_t` | Number of bytes to read. |

---

{#sub_nvs_init}

### sub_nvs_init

```cpp
esp_err_t sub_nvs_init(void)
```

Defined in h1os/sub_nvs.h:27

Initialize the NVS flash storage subsystem.

---

{#sub_nvs_set_str}

### sub_nvs_set_str

```cpp
esp_err_t sub_nvs_set_str(const char * key, const char * value)
```

Defined in h1os/sub_nvs.h:32

Store a string value in NVS.

---

{#sub_nvs_get_str}

### sub_nvs_get_str

```cpp
esp_err_t sub_nvs_get_str(const char * key, char * out_val, size_t max_len)
```

Defined in h1os/sub_nvs.h:37

Retrieve a string value from NVS.

---

{#sub_nvs_set_u32}

### sub_nvs_set_u32

```cpp
esp_err_t sub_nvs_set_u32(const char * key, uint32_t value)
```

Defined in h1os/sub_nvs.h:42

Store an unsigned 32-bit integer in NVS.

---

{#sub_nvs_get_u32}

### sub_nvs_get_u32

```cpp
esp_err_t sub_nvs_get_u32(const char * key, uint32_t * out_val)
```

Defined in h1os/sub_nvs.h:47

Retrieve an unsigned 32-bit integer from NVS.

---

{#sub_nvs_set_blob}

### sub_nvs_set_blob

```cpp
esp_err_t sub_nvs_set_blob(const char * key, const void * data, size_t len)
```

Defined in h1os/sub_nvs.h:52

Store a binary blob in NVS.

---

{#sub_nvs_get_blob}

### sub_nvs_get_blob

```cpp
esp_err_t sub_nvs_get_blob(const char * key, void * out_data, size_t * inout_len)
```

Defined in h1os/sub_nvs.h:57

Retrieve a binary blob from NVS.

---

{#sub_nvs_erase_key}

### sub_nvs_erase_key

```cpp
esp_err_t sub_nvs_erase_key(const char * key)
```

Defined in h1os/sub_nvs.h:62

Erase a specific key from NVS.

---

{#sub_nvs_erase_all}

### sub_nvs_erase_all

```cpp
esp_err_t sub_nvs_erase_all(void)
```

Defined in h1os/sub_nvs.h:67

Perform a factory reset wiping the entire H1OS NVS namespace.

---

{#sub_rtc_init}

### sub_rtc_init

```cpp
esp_err_t sub_rtc_init(void)
```

Defined in h1os/sub_rtc.h:29

Initialize PCF85063A RTC.

Disables CLKOUT push-pull square wave to eliminate continuous trace leakage, verifies oscillator status, and clears residual timer/alarm flags.

#### Returns
ESP_OK on success, or an I2C communication error.

---

{#sub_rtc_get_time}

### sub_rtc_get_time

```cpp
esp_err_t sub_rtc_get_time(struct tm * out_time)
```

Defined in h1os/sub_rtc.h:37

Read current date and time into POSIX struct tm.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_time` | `struct tm *` | Pointer to struct tm populated with current RTC timestamp. |

---

{#sub_rtc_set_time}

### sub_rtc_set_time

```cpp
esp_err_t sub_rtc_set_time(const struct tm * time)
```

Defined in h1os/sub_rtc.h:45

Set RTC calendar date and time.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `time` | `const struct tm *` | Pointer to struct tm containing target timestamp. |

---

{#sub_rtc_arm_countdown}

### sub_rtc_arm_countdown

```cpp
esp_err_t sub_rtc_arm_countdown(uint32_t seconds)
```

Defined in h1os/sub_rtc.h:54

Arm hardware countdown timer.

Drives open-drain interrupt line GPIO 5 LOW upon expiration.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `seconds` | `uint32_t` | Countdown interval in seconds (1 to 15300s). |

---

{#sub_rtc_cancel_countdown}

### sub_rtc_cancel_countdown

```cpp
esp_err_t sub_rtc_cancel_countdown(void)
```

Defined in h1os/sub_rtc.h:60

Cancel and disarm hardware countdown timer.

#### Returns
ESP_OK on success.

---

{#sub_rtc_get_remaining_seconds}

### sub_rtc_get_remaining_seconds

```cpp
esp_err_t sub_rtc_get_remaining_seconds(uint32_t * out_sec)
```

Defined in h1os/sub_rtc.h:69

Read remaining seconds on the active countdown timer.

Used for zero-hour collision avoidance.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_sec` | `uint32_t *` | Remaining seconds until countdown expiration. |

---

{#sub_rtc_get_and_clear_interrupts}

### sub_rtc_get_and_clear_interrupts

```cpp
esp_err_t sub_rtc_get_and_clear_interrupts(bool * out_alarm, bool * out_timer)
```

Defined in h1os/sub_rtc.h:79

Inspect and acknowledge RTC interrupt flags.

Clears TF (Timer Flag) and AF (Alarm Flag) in Control_2 to deassert GPIO 5.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_alarm` | `bool *` | Set to true if an alarm interrupt triggered. |
| `out_timer` | `bool *` | Set to true if a countdown timer interrupt triggered. |

---

{#hal_i2c_init-1}

### hal_i2c_init

```cpp
esp_err_t hal_i2c_init(void)
```

Defined in hal_i2c.c:18

Initializes the shared I2C master bus hardware.

Installs ESP-IDF I2C driver on GPIO 47 / GPIO 48 and creates recursive mutex.

#### Returns
ESP_OK on success, or driver error code.

---

{#hal_i2c_deinit-1}

### hal_i2c_deinit

```cpp
esp_err_t hal_i2c_deinit(void)
```

Defined in hal_i2c.c:56

Deinitializes the shared I2C master bus and releases mutex.

#### Returns
ESP_OK on success.

---

{#hal_i2c_write-1}

### hal_i2c_write

```cpp
esp_err_t hal_i2c_write(uint8_t dev_addr, const uint8_t * write_data, size_t write_len, uint32_t timeout_ms)
```

Defined in hal_i2c.c:75

Executes an atomic register write transaction over I2C.

#### Returns
ESP_OK on success, ESP_ERR_TIMEOUT, or NACK error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `dev_addr` | `uint8_t` | 7-bit I2C device address. |
| `write_data` | `const uint8_t *` | Pointer to data buffer to transmit. |
| `write_len` | `size_t` | Length of write buffer in bytes. |
| `timeout_ms` | `uint32_t` | Timeout budget in milliseconds. |

---

{#hal_i2c_read-1}

### hal_i2c_read

```cpp
esp_err_t hal_i2c_read(uint8_t dev_addr, uint8_t * read_data, size_t read_len, uint32_t timeout_ms)
```

Defined in hal_i2c.c:107

Executes an atomic register read transaction over I2C.

#### Returns
ESP_OK on success, ESP_ERR_TIMEOUT, or NACK error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `dev_addr` | `uint8_t` | 7-bit I2C device address. |
| `read_data` | `uint8_t *` | Pointer to buffer to receive data. |
| `read_len` | `size_t` | Number of bytes to read. |
| `timeout_ms` | `uint32_t` | Timeout budget in milliseconds. |

---

{#hal_i2c_write_read-1}

### hal_i2c_write_read

```cpp
esp_err_t hal_i2c_write_read(uint8_t dev_addr, const uint8_t * write_data, size_t write_len, uint8_t * read_data, size_t read_len, uint32_t timeout_ms)
```

Defined in hal_i2c.c:139

Executes an atomic write-then-read combined transaction (Repeated START).

#### Returns
ESP_OK on success, ESP_ERR_TIMEOUT, or NACK error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `dev_addr` | `uint8_t` | 7-bit I2C device address. |
| `write_data` | `const uint8_t *` | Register address or command bytes to write. |
| `write_len` | `size_t` | Number of bytes to write. |
| `read_data` | `uint8_t *` | Destination buffer for read bytes. |
| `read_len` | `size_t` | Number of bytes to read. |
| `timeout_ms` | `uint32_t` | Timeout budget in milliseconds. |

---

{#hal_i2c_probe-1}

### hal_i2c_probe

```cpp
esp_err_t hal_i2c_probe(uint8_t dev_addr)
```

Defined in hal_i2c.c:174

Probes if an I2C device with given 7-bit address responds on the bus.

#### Returns
ESP_OK if device ACKed, ESP_ERR_NOT_FOUND or other error on NACK/timeout.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `dev_addr` | `uint8_t` | 7-bit device address. |

---

{#epd_set_cs}

### epd_set_cs

`static` `inline`

```cpp
static inline void epd_set_cs(uint8_t level)
```

Defined in hal_spi.c:19

---

{#epd_set_dc}

### epd_set_dc

`static` `inline`

```cpp
static inline void epd_set_dc(uint8_t level)
```

Defined in hal_spi.c:23

---

{#hal_spi_init-1}

### hal_spi_init

```cpp
esp_err_t hal_spi_init(void)
```

Defined in hal_spi.c:27

Initializes SPI2 Master host with DMA channel enabled for display communication.

#### Returns
ESP_OK on success, or driver error code.

---

{#hal_spi_deinit-1}

### hal_spi_deinit

```cpp
esp_err_t hal_spi_deinit(void)
```

Defined in hal_spi.c:107

Deinitializes SPI2 Master host and releases bus resources.

#### Returns
ESP_OK on success.

---

{#hal_spi_write_cmd-1}

### hal_spi_write_cmd

```cpp
esp_err_t hal_spi_write_cmd(uint8_t cmd)
```

Defined in hal_spi.c:128

Transmits a single command byte to the SSD1681 controller (DC = 0).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `cmd` | `uint8_t` | Command byte. |

---

{#hal_spi_write_data-1}

### hal_spi_write_data

```cpp
esp_err_t hal_spi_write_data(const uint8_t * data, size_t len)
```

Defined in hal_spi.c:148

Transmits data bytes to the SSD1681 controller (DC = 1).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `data` | `const uint8_t *` | Pointer to buffer containing payload. |
| `len` | `size_t` | Length of data in bytes. |

---

{#hal_spi_write_frame_dma-1}

### hal_spi_write_frame_dma

```cpp
esp_err_t hal_spi_write_frame_dma(const uint8_t * frame_buffer)
```

Defined in hal_spi.c:167

Transmits a full 5000-byte frame buffer via DMA transfer.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `frame_buffer` | `const uint8_t *` | Pointer to 5000-byte buffer. |

---

{#hal_spi_read_data-1}

### hal_spi_read_data

```cpp
esp_err_t hal_spi_read_data(uint8_t cmd, uint8_t * out_data, size_t len)
```

Defined in hal_spi.c:186

Reads data from SSD1681 (e.g.

on-glass thermal sensor Cmd 0x1B).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `cmd` | `uint8_t` | Command to write before reading. |
| `out_data` | `uint8_t *` | Buffer to receive read bytes. |
| `len` | `size_t` | Number of bytes to read. |

---

{#sub_nvs_init-1}

### sub_nvs_init

```cpp
esp_err_t sub_nvs_init(void)
```

Defined in sub_nvs.c:18

Initialize the NVS flash storage subsystem.

---

{#sub_nvs_set_str-1}

### sub_nvs_set_str

```cpp
esp_err_t sub_nvs_set_str(const char * key, const char * value)
```

Defined in sub_nvs.c:45

Store a string value in NVS.

---

{#sub_nvs_get_str-1}

### sub_nvs_get_str

```cpp
esp_err_t sub_nvs_get_str(const char * key, char * out_val, size_t max_len)
```

Defined in sub_nvs.c:62

Retrieve a string value from NVS.

---

{#sub_nvs_set_u32-1}

### sub_nvs_set_u32

```cpp
esp_err_t sub_nvs_set_u32(const char * key, uint32_t value)
```

Defined in sub_nvs.c:77

Store an unsigned 32-bit integer in NVS.

---

{#sub_nvs_get_u32-1}

### sub_nvs_get_u32

```cpp
esp_err_t sub_nvs_get_u32(const char * key, uint32_t * out_val)
```

Defined in sub_nvs.c:94

Retrieve an unsigned 32-bit integer from NVS.

---

{#sub_nvs_set_blob-1}

### sub_nvs_set_blob

```cpp
esp_err_t sub_nvs_set_blob(const char * key, const void * data, size_t len)
```

Defined in sub_nvs.c:108

Store a binary blob in NVS.

---

{#sub_nvs_get_blob-1}

### sub_nvs_get_blob

```cpp
esp_err_t sub_nvs_get_blob(const char * key, void * out_data, size_t * inout_len)
```

Defined in sub_nvs.c:125

Retrieve a binary blob from NVS.

---

{#sub_nvs_erase_key-1}

### sub_nvs_erase_key

```cpp
esp_err_t sub_nvs_erase_key(const char * key)
```

Defined in sub_nvs.c:139

Erase a specific key from NVS.

---

{#sub_nvs_erase_all-1}

### sub_nvs_erase_all

```cpp
esp_err_t sub_nvs_erase_all(void)
```

Defined in sub_nvs.c:156

Perform a factory reset wiping the entire H1OS NVS namespace.

---

{#bcd2dec}

### bcd2dec

`static` `inline`

```cpp
static inline uint8_t bcd2dec(uint8_t val)
```

Defined in sub_rtc.c:53

---

{#dec2bcd}

### dec2bcd

`static` `inline`

```cpp
static inline uint8_t dec2bcd(uint8_t val)
```

Defined in sub_rtc.c:57

---

{#pcf85063_read_reg}

### pcf85063_read_reg

`static`

```cpp
static esp_err_t pcf85063_read_reg(uint8_t reg, uint8_t * val, size_t len)
```

Defined in sub_rtc.c:61

---

{#pcf85063_write_reg}

### pcf85063_write_reg

`static`

```cpp
static esp_err_t pcf85063_write_reg(uint8_t reg, const uint8_t * val, size_t len)
```

Defined in sub_rtc.c:66

---

{#pcf85063_write_reg_u8}

### pcf85063_write_reg_u8

`static`

```cpp
static esp_err_t pcf85063_write_reg_u8(uint8_t reg, uint8_t val)
```

Defined in sub_rtc.c:75

---

{#sub_rtc_init-1}

### sub_rtc_init

```cpp
esp_err_t sub_rtc_init(void)
```

Defined in sub_rtc.c:80

Initialize PCF85063A RTC.

Disables CLKOUT push-pull square wave to eliminate continuous trace leakage, verifies oscillator status, and clears residual timer/alarm flags.

#### Returns
ESP_OK on success, or an I2C communication error.

---

{#sub_rtc_get_time-1}

### sub_rtc_get_time

```cpp
esp_err_t sub_rtc_get_time(struct tm * out_time)
```

Defined in sub_rtc.c:120

Read current date and time into POSIX struct tm.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_time` | `struct tm *` | Pointer to struct tm populated with current RTC timestamp. |

---

{#sub_rtc_set_time-1}

### sub_rtc_set_time

```cpp
esp_err_t sub_rtc_set_time(const struct tm * time)
```

Defined in sub_rtc.c:144

Set RTC calendar date and time.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `time` | `const struct tm *` | Pointer to struct tm containing target timestamp. |

---

{#sub_rtc_arm_countdown-1}

### sub_rtc_arm_countdown

```cpp
esp_err_t sub_rtc_arm_countdown(uint32_t seconds)
```

Defined in sub_rtc.c:174

Arm hardware countdown timer.

Drives open-drain interrupt line GPIO 5 LOW upon expiration.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `seconds` | `uint32_t` | Countdown interval in seconds (1 to 15300s). |

---

{#sub_rtc_cancel_countdown-1}

### sub_rtc_cancel_countdown

```cpp
esp_err_t sub_rtc_cancel_countdown(void)
```

Defined in sub_rtc.c:210

Cancel and disarm hardware countdown timer.

#### Returns
ESP_OK on success.

---

{#sub_rtc_get_remaining_seconds-1}

### sub_rtc_get_remaining_seconds

```cpp
esp_err_t sub_rtc_get_remaining_seconds(uint32_t * out_sec)
```

Defined in sub_rtc.c:222

Read remaining seconds on the active countdown timer.

Used for zero-hour collision avoidance.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_sec` | `uint32_t *` | Remaining seconds until countdown expiration. |

---

{#sub_rtc_get_and_clear_interrupts-1}

### sub_rtc_get_and_clear_interrupts

```cpp
esp_err_t sub_rtc_get_and_clear_interrupts(bool * out_alarm, bool * out_timer)
```

Defined in sub_rtc.c:250

Inspect and acknowledge RTC interrupt flags.

Clears TF (Timer Flag) and AF (Alarm Flag) in Control_2 to deassert GPIO 5.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_alarm` | `bool *` | Set to true if an alarm interrupt triggered. |
| `out_timer` | `bool *` | Set to true if a countdown timer interrupt triggered. |

---

{#h1os_lvgl_init}

### h1os_lvgl_init

```cpp
esp_err_t h1os_lvgl_init(bool is_wake_cycle)
```

Defined in h1os/h1os_lvgl.h:24

Initialize LVGL v9 graphics subsystem, 1-bit display buffer, and keypad input driver.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `is_wake_cycle` | `bool` | True if resuming from sleep (enables differential partial flush). |

---

{#h1os_lvgl_set_first_flush_mode}

### h1os_lvgl_set_first_flush_mode

```cpp
void h1os_lvgl_set_first_flush_mode(bool full_refresh)
```

Defined in h1os/h1os_lvgl.h:31

Explicitly override whether the first flush executes a full or partial refresh.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `full_refresh` | `bool` | True for full OTP flashing refresh, False for differential partial. |

---

{#h1os_lvgl_start}

### h1os_lvgl_start

```cpp
esp_err_t h1os_lvgl_start(int priority, int core_id)
```

Defined in h1os/h1os_lvgl.h:36

Start the LVGL background FreeRTOS task.

---

{#h1os_lvgl_stop}

### h1os_lvgl_stop

```cpp
esp_err_t h1os_lvgl_stop(void)
```

Defined in h1os/h1os_lvgl.h:41

Stop the LVGL background task.

---

{#h1os_lvgl_lock}

### h1os_lvgl_lock

```cpp
bool h1os_lvgl_lock(uint32_t timeout_ms)
```

Defined in h1os/h1os_lvgl.h:46

Acquire LVGL reentrant mutex lock.

---

{#h1os_lvgl_unlock}

### h1os_lvgl_unlock

```cpp
void h1os_lvgl_unlock(void)
```

Defined in h1os/h1os_lvgl.h:51

Release LVGL reentrant mutex lock.

---

{#h1os_lvgl_has_pending_tasks}

### h1os_lvgl_has_pending_tasks

```cpp
bool h1os_lvgl_has_pending_tasks(void)
```

Defined in h1os/h1os_lvgl.h:56

Check if the LVGL display pipeline has pending render/flush tasks.

---

{#h1os_lvgl_get_indev}

### h1os_lvgl_get_indev

```cpp
lv_indev_t * h1os_lvgl_get_indev(void)
```

Defined in h1os/h1os_lvgl.h:61

Retrieve the LVGL keypad input device handle.

---

{#h1os_time_set_timezone}

### h1os_time_set_timezone

```cpp
esp_err_t h1os_time_set_timezone(const char * tz_str)
```

Defined in h1os/h1os_time.h:41

Configure POSIX timezone string.

---

{#h1os_time_register_sync_cb}

### h1os_time_register_sync_cb

```cpp
esp_err_t h1os_time_register_sync_cb(h1os_time_sync_cb_t cb, void * user_data)
```

Defined in h1os/h1os_time.h:46

Register external time sync callback.

---

{#h1os_time_sync_now}

### h1os_time_sync_now

```cpp
esp_err_t h1os_time_sync_now(uint32_t timeout_ms)
```

Defined in h1os/h1os_time.h:51

Trigger time synchronization using registered callback.

---

{#h1os_time_sync_system_to_rtc}

### h1os_time_sync_system_to_rtc

```cpp
esp_err_t h1os_time_sync_system_to_rtc(void)
```

Defined in h1os/h1os_time.h:56

Synchronize internal system clock into PCF85063A RTC hardware.

---

{#h1os_time_sync_rtc_to_system}

### h1os_time_sync_rtc_to_system

```cpp
esp_err_t h1os_time_sync_rtc_to_system(void)
```

Defined in h1os/h1os_time.h:61

Synchronize PCF85063A RTC hardware into internal POSIX system clock.

---

{#h1os_time_get_formatted}

### h1os_time_get_formatted

```cpp
esp_err_t h1os_time_get_formatted(h1os_time_format_t fmt, char * dest, size_t max_len)
```

Defined in h1os/h1os_time.h:66

Format current local time into destination buffer.

---

{#h1os_time_get_date_formatted}

### h1os_time_get_date_formatted

```cpp
esp_err_t h1os_time_get_date_formatted(h1os_date_format_t fmt, char * dest, size_t max_len)
```

Defined in h1os/h1os_time.h:71

Format current local date into destination buffer.

---

{#hal_flash_init}

### hal_flash_init

```cpp
esp_err_t hal_flash_init(void)
```

Defined in h1os/hal_flash.h:25

Finds and verifies the dedicated "epd_frame" partition.

#### Returns
ESP_OK on success, or ESP_ERR_NOT_FOUND if partition is missing.

---

{#hal_flash_read_frame}

### hal_flash_read_frame

```cpp
esp_err_t hal_flash_read_frame(uint8_t * out_buffer, size_t len)
```

Defined in h1os/hal_flash.h:34

Reads the persisted 5000-byte EPD frame from flash.

#### Returns
ESP_OK on success, or flash read error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_buffer` | `uint8_t *` | Destination buffer (must be at least 5000 bytes). |
| `len` | `size_t` | Number of bytes to read (typically 5000). |

---

{#hal_flash_write_frame}

### hal_flash_write_frame

```cpp
esp_err_t hal_flash_write_frame(const uint8_t * frame_data, size_t len)
```

Defined in h1os/hal_flash.h:43

Erases the partition sector and writes the 5000-byte frame.

#### Returns
ESP_OK on success, or flash write error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `frame_data` | `const uint8_t *` | Pointer to 5000-byte frame to commit. |
| `len` | `size_t` | Length in bytes (must be <= partition size). |

---

{#orch_flow_determine_wakeup}

### orch_flow_determine_wakeup

```cpp
orch_flow_type_t orch_flow_determine_wakeup(void)
```

Defined in h1os/orch_flow.h:37

Inspect system wake source and arbitrate target flow.

#### Returns
Detected flow type.

---

{#orch_flow_execute_sensor_sample}

### orch_flow_execute_sensor_sample

```cpp
void orch_flow_execute_sensor_sample(void)
```

Defined in h1os/orch_flow.h:46

Execute Flow A Headless Sensor Sample Burst.

Powers on sensor rail, takes rapid low-power SHTC3 reading in <4ms, commits sample to RTC Slow Memory ring buffer, and re-enters deep sleep immediately. Zero measurable thermal impact on sensor cavity.

---

{#orch_flow_is_thermal_lockout}

### orch_flow_is_thermal_lockout

```cpp
bool orch_flow_is_thermal_lockout(void)
```

Defined in h1os/orch_flow.h:54

Check whether system is in Thermal Lockout state.

If true, active dissipation from CPU/Display/Wi-Fi has perturbed board equilibrium.

#### Returns
True if in lockout, False if in thermal equilibrium.

---

{#orch_flow_set_thermal_lockout}

### orch_flow_set_thermal_lockout

```cpp
void orch_flow_set_thermal_lockout(bool enable, uint32_t duration_sec)
```

Defined in h1os/orch_flow.h:62

Arm or disarm thermal lockout gatekeeper.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `enable` | `bool` | True to arm thermal lockout (e.g. after display refresh or Wi-Fi). |
| `duration_sec` | `uint32_t` | Duration of lockout in seconds (typically 30-60s). |

---

{#orch_flow_query_telemetry}

### orch_flow_query_telemetry

```cpp
esp_err_t orch_flow_query_telemetry(float * out_temp_c, float * out_rh_pct, float * out_dew_c)
```

Defined in h1os/orch_flow.h:76

Query current environmental telemetry through the Thermal Lockout MUX.

If in thermal equilibrium, takes fresh sensor reading. If in thermal lockout, transparently returns pristine cold reading from RTC ring buffer.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_temp_c` | `float *` | Reconstructed ambient temperature in Celsius. |
| `out_rh_pct` | `float *` | Reconstructed ambient relative humidity in percent. |
| `out_dew_c` | `float *` | True dew point in Celsius. |

---

{#orch_flow_transition_to_sleep}

### orch_flow_transition_to_sleep

```cpp
esp_err_t orch_flow_transition_to_sleep(uint32_t sleep_sec)
```

Defined in h1os/orch_flow.h:85

Execute coordinated 8-step sleep transition sequence to deep sleep.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `sleep_sec` | `uint32_t` | Sleep duration in seconds. |

---

{#orch_math_calc_sat_vapor_pressure}

### orch_math_calc_sat_vapor_pressure

```cpp
float orch_math_calc_sat_vapor_pressure(float temp_c)
```

Defined in h1os/orch_math.h:34

Calculate saturation vapor pressure e_s(T) in hPa.

Formula: e_s(T) = 6.112 * exp((17.625 * T) / (243.04 + T))

#### Returns
Saturation vapor pressure in hPa.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `temp_c` | `float` | Temperature in Celsius. |

---

{#orch_math_calc_vapor_pressure}

### orch_math_calc_vapor_pressure

```cpp
float orch_math_calc_vapor_pressure(float temp_c, float rh_pct)
```

Defined in h1os/orch_math.h:44

Calculate actual water vapor pressure (e) in hPa.

Formula: e = (rh_pct / 100.0) * e_s(temp_c)

#### Returns
Actual water vapor pressure in hPa.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `temp_c` | `float` | Temperature in Celsius. |
| `rh_pct` | `float` | Relative humidity in percent (0 - 100). |

---

{#orch_math_calc_dew_point}

### orch_math_calc_dew_point

```cpp
float orch_math_calc_dew_point(float temp_c, float rh_pct)
```

Defined in h1os/orch_math.h:54

Calculate true dew point (T_dew) in Celsius from physical vapor pressure.

Invariant against package heating because vapor mass in air does not change with temperature.

#### Returns
Dew point in Celsius.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `temp_c` | `float` | Measured package temperature in Celsius. |
| `rh_pct` | `float` | Measured package relative humidity in percent. |

---

{#orch_math_reconstruct_ambient_rh}

### orch_math_reconstruct_ambient_rh

```cpp
float orch_math_reconstruct_ambient_rh(float vapor_pressure_hpa, float amb_floor_temp_c)
```

Defined in h1os/orch_math.h:64

Reconstruct true ambient relative humidity using the ambient baseline floor temperature.

Formula: RH_amb = (e / e_s(temp_ambient_floor)) * 100.0%

#### Returns
Reconstructed ambient relative humidity in percent (clamped to [0, 100]).

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `vapor_pressure_hpa` | `float` | Invariant vapor pressure in hPa. |
| `amb_floor_temp_c` | `float` | Ambient floor temperature in Celsius. |

---

{#orch_math_calc_absolute_humidity}

### orch_math_calc_absolute_humidity

```cpp
float orch_math_calc_absolute_humidity(float vapor_pressure_hpa, float amb_temp_c)
```

Defined in h1os/orch_math.h:74

Calculate absolute humidity (vapor density) in grams per cubic meter (g/m³).

Formula: d_v = 216.7 * (e / (273.15 + T_ambient))

#### Returns
Vapor density in g/m³.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `vapor_pressure_hpa` | `float` | Vapor pressure in hPa. |
| `amb_temp_c` | `float` | Ambient temperature in Celsius. |

---

{#orch_math_update_ewma}

### orch_math_update_ewma

```cpp
float orch_math_update_ewma(float current_sample, float previous_ewma, float alpha)
```

Defined in h1os/orch_math.h:85

Update continuous recursive EWMA filter.

S_t = alpha * X_t + (1 - alpha) * S_{t-1}

#### Returns
Filtered result.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `current_sample` | `float` | New sample value. |
| `previous_ewma` | `float` | Previous filtered value. |
| `alpha` | `float` | Weight coefficient (typically 0.25 to 0.35). |

---

{#orch_math_is_plateau_settled}

### orch_math_is_plateau_settled

```cpp
bool orch_math_is_plateau_settled(int16_t initial_temp_centi_c, int16_t current_temp_centi_c, int16_t gate_threshold_centi_c)
```

Defined in h1os/orch_math.h:96

Evaluates whether sensor package has settled to thermal plateau.

Formula: Delta T = initial_temp - current_temp >= gate_threshold

#### Returns
True if thermally settled.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `initial_temp_centi_c` | `int16_t` | Initial sleep entry baseline temp (centi-°C). |
| `current_temp_centi_c` | `int16_t` | Current sample temp (centi-°C). |
| `gate_threshold_centi_c` | `int16_t` | Threshold drop (typically 5 to 20 centi-°C, i.e. 0.05 - 0.20 °C). |

---

{#sub_audio_init}

### sub_audio_init

```cpp
esp_err_t sub_audio_init(void)
```

Defined in h1os/sub_audio.h:28

Initialize ES8311 codec and NS4168 amplifier.

Configures I2S audio bus and sets codec to active run mode.

#### Returns
ESP_OK on success, or an error code.

---

{#sub_audio_standby}

### sub_audio_standby

```cpp
esp_err_t sub_audio_standby(void)
```

Defined in h1os/sub_audio.h:37

Put ES8311 codec into ultra-low-power software standby (Reg 0x0D = 0x00 @ <1.0 µA) and pull NS4168 PA_CTRL LOW.

Keeps power rails on so I2C bus is NOT clamped by unpowered chip protection diodes.

#### Returns
ESP_OK on success.

---

{#sub_audio_deinit}

### sub_audio_deinit

```cpp
esp_err_t sub_audio_deinit(void)
```

Defined in h1os/sub_audio.h:44

Teardown audio subsystem, stop background worker task, and delete I2S channel.

#### Returns
ESP_OK on success.

---

{#sub_audio_wait_until_ready}

### sub_audio_wait_until_ready

```cpp
esp_err_t sub_audio_wait_until_ready(uint32_t timeout_ms)
```

Defined in h1os/sub_audio.h:53

Poll ES8311 over I2C to confirm Chip ID (0xFD=0x83, 0xFE=0x11) and wait for Chip State Machine (Reg 0xFC bits 6:4) to exit power-down state S0.

#### Returns
ESP_OK if codec is verified and in active CSM state, or error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ms` | `uint32_t` | Maximum wait time in milliseconds. |

---

{#sub_audio_is_ready}

### sub_audio_is_ready

```cpp
bool sub_audio_is_ready(void)
```

Defined in h1os/sub_audio.h:60

Quick status check of whether ES8311 codec is ready.

#### Returns
true if communication and active CSM state verified.

---

{#sub_audio_play_pcm}

### sub_audio_play_pcm

```cpp
esp_err_t sub_audio_play_pcm(const int16_t * samples, size_t sample_count, uint32_t sample_rate_hz)
```

Defined in h1os/sub_audio.h:70

Play raw 16-bit signed PCM audio samples synchronously.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `samples` | `const int16_t *` | Pointer to 16-bit signed Mono PCM samples. |
| `sample_count` | `size_t` | Number of int16_t samples. |
| `sample_rate_hz` | `uint32_t` | Sample rate in Hz (default: 16000). |

---

{#sub_audio_play_pcm_async}

### sub_audio_play_pcm_async

```cpp
esp_err_t sub_audio_play_pcm_async(const int16_t * samples, size_t sample_count, uint32_t sample_rate_hz)
```

Defined in h1os/sub_audio.h:81

Play raw 16-bit signed PCM audio samples asynchronously in background worker task.

Note: Caller must ensure the buffer remains valid until playback finishes (e.g., const/static buffer).

#### Returns
ESP_OK on success, ESP_ERR_NO_MEM / ESP_ERR_TIMEOUT if queue full.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `samples` | `const int16_t *` | Pointer to 16-bit signed Mono PCM samples. |
| `sample_count` | `size_t` | Number of int16_t samples. |
| `sample_rate_hz` | `uint32_t` | Sample rate in Hz (default: 16000). |

---

{#sub_audio_play_tone}

### sub_audio_play_tone

```cpp
esp_err_t sub_audio_play_tone(uint32_t frequency_hz, uint32_t duration_ms)
```

Defined in h1os/sub_audio.h:90

Play synthesized audio chime/tone synchronously.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `frequency_hz` | `uint32_t` | Frequency in Hertz (e.g. 1000 for 1 kHz). |
| `duration_ms` | `uint32_t` | Duration in milliseconds. |

---

{#sub_audio_play_tone_async}

### sub_audio_play_tone_async

```cpp
esp_err_t sub_audio_play_tone_async(uint32_t frequency_hz, uint32_t duration_ms)
```

Defined in h1os/sub_audio.h:99

Play synthesized audio chime/tone asynchronously via worker task.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `frequency_hz` | `uint32_t` | Frequency in Hertz (e.g. 1000 for 1 kHz). |
| `duration_ms` | `uint32_t` | Duration in milliseconds. |

---

{#sub_audio_play_chime}

### sub_audio_play_chime

```cpp
esp_err_t sub_audio_play_chime(uint8_t type)
```

Defined in h1os/sub_audio.h:107

Play standard H1OS acoustic presentation chime synchronously.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `type` | `uint8_t` | Chime type (BOOT, WAKE, SLEEP, SHUTDOWN, ALARM). |

---

{#sub_audio_play_chime_async}

### sub_audio_play_chime_async

```cpp
esp_err_t sub_audio_play_chime_async(uint8_t type)
```

Defined in h1os/sub_audio.h:115

Play standard H1OS acoustic presentation chime asynchronously.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `type` | `uint8_t` | Chime type (BOOT, WAKE, SLEEP, SHUTDOWN, ALARM). |

---

{#sub_audio_is_busy}

### sub_audio_is_busy

```cpp
bool sub_audio_is_busy(void)
```

Defined in h1os/sub_audio.h:122

Check if audio playback is currently active or queue has pending items.

#### Returns
true if playing or queued, false if idle in standby.

---

{#sub_audio_wait_idle}

### sub_audio_wait_idle

```cpp
esp_err_t sub_audio_wait_idle(uint32_t timeout_ms)
```

Defined in h1os/sub_audio.h:130

Wait until background audio worker completes all playback and enters standby.

#### Returns
ESP_OK if idle, ESP_ERR_TIMEOUT if still active.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ms` | `uint32_t` | Maximum time to wait in milliseconds. |

---

{#sub_audio_set_volume}

### sub_audio_set_volume

```cpp
esp_err_t sub_audio_set_volume(uint8_t volume_pct)
```

Defined in h1os/sub_audio.h:139

Set ES8311 DAC output volume percentage (0% = Mute, 100% = 0 dB full-scale).

Persists across standby/wake cycles.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `volume_pct` | `uint8_t` | Volume percentage (0 - 100). |

---

{#sub_audio_get_volume}

### sub_audio_get_volume

```cpp
uint8_t sub_audio_get_volume(void)
```

Defined in h1os/sub_audio.h:146

Get currently configured output volume percentage (0 - 100).

#### Returns
Current volume percentage.

---

{#sub_audio_set_low_power_mode}

### sub_audio_set_low_power_mode

```cpp
esp_err_t sub_audio_set_low_power_mode(bool enable)
```

Defined in h1os/sub_audio.h:157

Configure ES8311 DAC power mode (Low-Power vs Normal).

In low-power mode (default upon init), ES8311 operates with LPDAC enabled (Reg 0x0F bit 7 = 1), significantly reducing active DAC bias current. Normal mode provides standard bias.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `enable` | `bool` | true for Low-Power Mode (default), false for Normal Power Mode. |

---

{#sub_audio_get_low_power_mode}

### sub_audio_get_low_power_mode

```cpp
bool sub_audio_get_low_power_mode(void)
```

Defined in h1os/sub_audio.h:164

Query whether audio subsystem is in Low-Power Mode.

#### Returns
true if Low-Power Mode is active, false if Normal Power Mode.

---

{#sub_power_init}

### sub_power_init

```cpp
esp_err_t sub_power_init(void)
```

Defined in h1os/sub_power.h:25

Initialize Battery ADC subsystem (ADC1 Channel 3 on GPIO 4 with 12 dB atten and eFuse cal).

#### Returns
ESP_OK on success, or an error code.

---

{#sub_power_deinit}

### sub_power_deinit

```cpp
esp_err_t sub_power_deinit(void)
```

Defined in h1os/sub_power.h:31

Deinitialize ADC handles.

#### Returns
ESP_OK on success.

---

{#sub_power_read_battery}

### sub_power_read_battery

```cpp
esp_err_t sub_power_read_battery(uint16_t * out_mv, uint8_t * out_pct)
```

Defined in h1os/sub_power.h:40

Sample calibrated battery voltage with 16-sample trimmed outlier filtering.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_mv` | `uint16_t *` | Battery voltage in millivolts (e.g. 3850 mV). |
| `out_pct` | `uint8_t *` | Estimated state of charge (0 to 100%). |

---

{#sub_power_get_ulp_cal_params}

### sub_power_get_ulp_cal_params

```cpp
esp_err_t sub_power_get_ulp_cal_params(uint32_t * out_scale, int32_t * out_offset_mv)
```

Defined in h1os/sub_power.h:49

Extract linear calibration coefficients (scale and offset) for ULP coprocessor hand-off.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_scale` | `uint32_t *` | Multiplier scaled by 4096. |
| `out_offset_mv` | `int32_t *` | Voltage offset in millivolts. |

---

{#sub_power_enter_deep_sleep}

### sub_power_enter_deep_sleep

```cpp
esp_err_t sub_power_enter_deep_sleep(uint32_t sleep_seconds, uint64_t ext1_pins_mask)
```

Defined in h1os/sub_power.h:59

Configure EXT1 wake sources and enter deep sleep.

Maintains RTC pad holds on power latch (GPIO 17) and EPD rail (GPIO 6) to keep rails active.

#### Returns
Does not return on success (enters deep sleep).

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `sleep_seconds` | `uint32_t` | Timer duration in seconds (0 = timer disabled). |
| `ext1_pins_mask` | `uint64_t` | Bitmask of RTC GPIO pins for wakeup (e.g. GPIO 0, 18, 5). |

---

{#sub_power_cut_power_latch}

### sub_power_cut_power_latch

```cpp
void sub_power_cut_power_latch(void)
```

Defined in h1os/sub_power.h:65

Power off system completely by releasing battery power latch (GPIO 17).

Used for critical low-battery shutdown or explicit user power-off.

---

{#sub_power_connected_usb}

### sub_power_connected_usb

```cpp
bool sub_power_connected_usb(void)
```

Defined in h1os/sub_power.h:73

Check to see if USB is connected.

Used for charger detection.

#### Returns
true if usb is connected, or false if disconnected.

---

{#h1os_time_set_timezone-1}

### h1os_time_set_timezone

```cpp
esp_err_t h1os_time_set_timezone(const char * tz_str)
```

Defined in h1os_time.c:21

Configure POSIX timezone string.

---

{#h1os_time_register_sync_cb-1}

### h1os_time_register_sync_cb

```cpp
esp_err_t h1os_time_register_sync_cb(h1os_time_sync_cb_t cb, void * user_data)
```

Defined in h1os_time.c:32

Register external time sync callback.

---

{#h1os_time_sync_system_to_rtc-1}

### h1os_time_sync_system_to_rtc

```cpp
esp_err_t h1os_time_sync_system_to_rtc(void)
```

Defined in h1os_time.c:39

Synchronize internal system clock into PCF85063A RTC hardware.

---

{#h1os_time_sync_rtc_to_system-1}

### h1os_time_sync_rtc_to_system

```cpp
esp_err_t h1os_time_sync_rtc_to_system(void)
```

Defined in h1os_time.c:57

Synchronize PCF85063A RTC hardware into internal POSIX system clock.

---

{#h1os_time_sync_now-1}

### h1os_time_sync_now

```cpp
esp_err_t h1os_time_sync_now(uint32_t timeout_ms)
```

Defined in h1os_time.c:80

Trigger time synchronization using registered callback.

---

{#h1os_time_get_formatted-1}

### h1os_time_get_formatted

```cpp
esp_err_t h1os_time_get_formatted(h1os_time_format_t fmt, char * dest, size_t max_len)
```

Defined in h1os_time.c:98

Format current local time into destination buffer.

---

{#h1os_time_get_date_formatted-1}

### h1os_time_get_date_formatted

```cpp
esp_err_t h1os_time_get_date_formatted(h1os_date_format_t fmt, char * dest, size_t max_len)
```

Defined in h1os_time.c:120

Format current local date into destination buffer.

---

{#hal_flash_init-1}

### hal_flash_init

```cpp
esp_err_t hal_flash_init(void)
```

Defined in hal_flash.c:16

Finds and verifies the dedicated "epd_frame" partition.

#### Returns
ESP_OK on success, or ESP_ERR_NOT_FOUND if partition is missing.

---

{#hal_flash_read_frame-1}

### hal_flash_read_frame

```cpp
esp_err_t hal_flash_read_frame(uint8_t * out_buffer, size_t len)
```

Defined in hal_flash.c:35

Reads the persisted 5000-byte EPD frame from flash.

#### Returns
ESP_OK on success, or flash read error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_buffer` | `uint8_t *` | Destination buffer (must be at least 5000 bytes). |
| `len` | `size_t` | Number of bytes to read (typically 5000). |

---

{#hal_flash_write_frame-1}

### hal_flash_write_frame

```cpp
esp_err_t hal_flash_write_frame(const uint8_t * frame_data, size_t len)
```

Defined in hal_flash.c:51

Erases the partition sector and writes the 5000-byte frame.

#### Returns
ESP_OK on success, or flash write error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `frame_data` | `const uint8_t *` | Pointer to 5000-byte frame to commit. |
| `len` | `size_t` | Length in bytes (must be <= partition size). |

---

{#orch_flow_determine_wakeup-1}

### orch_flow_determine_wakeup

```cpp
orch_flow_type_t orch_flow_determine_wakeup(void)
```

Defined in orch_flow.c:42

Inspect system wake source and arbitrate target flow.

#### Returns
Detected flow type.

---

{#orch_flow_execute_sensor_sample-1}

### orch_flow_execute_sensor_sample

```cpp
void orch_flow_execute_sensor_sample(void)
```

Defined in orch_flow.c:89

Execute Flow A Headless Sensor Sample Burst.

Powers on sensor rail, takes rapid low-power SHTC3 reading in <4ms, commits sample to RTC Slow Memory ring buffer, and re-enters deep sleep immediately. Zero measurable thermal impact on sensor cavity.

---

{#orch_flow_is_thermal_lockout-1}

### orch_flow_is_thermal_lockout

```cpp
bool orch_flow_is_thermal_lockout(void)
```

Defined in orch_flow.c:96

Check whether system is in Thermal Lockout state.

If true, active dissipation from CPU/Display/Wi-Fi has perturbed board equilibrium.

#### Returns
True if in lockout, False if in thermal equilibrium.

---

{#orch_flow_set_thermal_lockout-1}

### orch_flow_set_thermal_lockout

```cpp
void orch_flow_set_thermal_lockout(bool enable, uint32_t duration_sec)
```

Defined in orch_flow.c:102

Arm or disarm thermal lockout gatekeeper.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `enable` | `bool` | True to arm thermal lockout (e.g. after display refresh or Wi-Fi). |
| `duration_sec` | `uint32_t` | Duration of lockout in seconds (typically 30-60s). |

---

{#orch_flow_query_telemetry-1}

### orch_flow_query_telemetry

```cpp
esp_err_t orch_flow_query_telemetry(float * out_temp_c, float * out_rh_pct, float * out_dew_c)
```

Defined in orch_flow.c:113

Query current environmental telemetry through the Thermal Lockout MUX.

If in thermal equilibrium, takes fresh sensor reading. If in thermal lockout, transparently returns pristine cold reading from RTC ring buffer.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_temp_c` | `float *` | Reconstructed ambient temperature in Celsius. |
| `out_rh_pct` | `float *` | Reconstructed ambient relative humidity in percent. |
| `out_dew_c` | `float *` | True dew point in Celsius. |

---

{#orch_flow_transition_to_sleep-1}

### orch_flow_transition_to_sleep

```cpp
esp_err_t orch_flow_transition_to_sleep(uint32_t sleep_sec)
```

Defined in orch_flow.c:279

Execute coordinated 8-step sleep transition sequence to deep sleep.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `sleep_sec` | `uint32_t` | Sleep duration in seconds. |

---

{#orch_math_calc_sat_vapor_pressure-1}

### orch_math_calc_sat_vapor_pressure

```cpp
float orch_math_calc_sat_vapor_pressure(float temp_c)
```

Defined in orch_math.c:14

Calculate saturation vapor pressure e_s(T) in hPa.

Formula: e_s(T) = 6.112 * exp((17.625 * T) / (243.04 + T))

#### Returns
Saturation vapor pressure in hPa.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `temp_c` | `float` | Temperature in Celsius. |

---

{#orch_math_calc_vapor_pressure-1}

### orch_math_calc_vapor_pressure

```cpp
float orch_math_calc_vapor_pressure(float temp_c, float rh_pct)
```

Defined in orch_math.c:20

Calculate actual water vapor pressure (e) in hPa.

Formula: e = (rh_pct / 100.0) * e_s(temp_c)

#### Returns
Actual water vapor pressure in hPa.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `temp_c` | `float` | Temperature in Celsius. |
| `rh_pct` | `float` | Relative humidity in percent (0 - 100). |

---

{#orch_math_calc_dew_point-1}

### orch_math_calc_dew_point

```cpp
float orch_math_calc_dew_point(float temp_c, float rh_pct)
```

Defined in orch_math.c:29

Calculate true dew point (T_dew) in Celsius from physical vapor pressure.

Invariant against package heating because vapor mass in air does not change with temperature.

#### Returns
Dew point in Celsius.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `temp_c` | `float` | Measured package temperature in Celsius. |
| `rh_pct` | `float` | Measured package relative humidity in percent. |

---

{#orch_math_reconstruct_ambient_rh-1}

### orch_math_reconstruct_ambient_rh

```cpp
float orch_math_reconstruct_ambient_rh(float vapor_pressure_hpa, float amb_floor_temp_c)
```

Defined in orch_math.c:42

Reconstruct true ambient relative humidity using the ambient baseline floor temperature.

Formula: RH_amb = (e / e_s(temp_ambient_floor)) * 100.0%

#### Returns
Reconstructed ambient relative humidity in percent (clamped to [0, 100]).

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `vapor_pressure_hpa` | `float` | Invariant vapor pressure in hPa. |
| `amb_floor_temp_c` | `float` | Ambient floor temperature in Celsius. |

---

{#orch_math_calc_absolute_humidity-1}

### orch_math_calc_absolute_humidity

```cpp
float orch_math_calc_absolute_humidity(float vapor_pressure_hpa, float amb_temp_c)
```

Defined in orch_math.c:53

Calculate absolute humidity (vapor density) in grams per cubic meter (g/m³).

Formula: d_v = 216.7 * (e / (273.15 + T_ambient))

#### Returns
Vapor density in g/m³.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `vapor_pressure_hpa` | `float` | Vapor pressure in hPa. |
| `amb_temp_c` | `float` | Ambient temperature in Celsius. |

---

{#orch_math_update_ewma-1}

### orch_math_update_ewma

```cpp
float orch_math_update_ewma(float current_sample, float previous_ewma, float alpha)
```

Defined in orch_math.c:61

Update continuous recursive EWMA filter.

S_t = alpha * X_t + (1 - alpha) * S_{t-1}

#### Returns
Filtered result.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `current_sample` | `float` | New sample value. |
| `previous_ewma` | `float` | Previous filtered value. |
| `alpha` | `float` | Weight coefficient (typically 0.25 to 0.35). |

---

{#orch_math_is_plateau_settled-1}

### orch_math_is_plateau_settled

```cpp
bool orch_math_is_plateau_settled(int16_t initial_temp_centi_c, int16_t current_temp_centi_c, int16_t gate_threshold_centi_c)
```

Defined in orch_math.c:68

Evaluates whether sensor package has settled to thermal plateau.

Formula: Delta T = initial_temp - current_temp >= gate_threshold

#### Returns
True if thermally settled.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `initial_temp_centi_c` | `int16_t` | Initial sleep entry baseline temp (centi-°C). |
| `current_temp_centi_c` | `int16_t` | Current sample temp (centi-°C). |
| `gate_threshold_centi_c` | `int16_t` | Threshold drop (typically 5 to 20 centi-°C, i.e. 0.05 - 0.20 °C). |

---

{#volume_pct_to_es8311_reg}

### volume_pct_to_es8311_reg

`static` `inline`

```cpp
static inline uint8_t volume_pct_to_es8311_reg(uint8_t pct)
```

Defined in sub_audio.c:105

---

{#audio_worker_task}

### audio_worker_task

`static`

```cpp
static void audio_worker_task(void * pvParameters)
```

Defined in sub_audio.c:562

---

{#sub_audio_park_warm}

### sub_audio_park_warm

`static`

```cpp
static void sub_audio_park_warm(void)
```

Defined in sub_audio.c:340

---

{#es8311_write_reg}

### es8311_write_reg

`static`

```cpp
static esp_err_t es8311_write_reg(uint8_t reg, uint8_t val)
```

Defined in sub_audio.c:115

---

{#es8311_read_reg}

### es8311_read_reg

`static`

```cpp
static esp_err_t es8311_read_reg(uint8_t reg, uint8_t * val)
```

Defined in sub_audio.c:121

---

{#sub_audio_read_chip_id}

### sub_audio_read_chip_id

`static`

```cpp
static esp_err_t sub_audio_read_chip_id(uint16_t * chip_id)
```

Defined in sub_audio.c:126

---

{#sub_audio_wait_until_ready-1}

### sub_audio_wait_until_ready

```cpp
esp_err_t sub_audio_wait_until_ready(uint32_t timeout_ms)
```

Defined in sub_audio.c:146

Poll ES8311 over I2C to confirm Chip ID (0xFD=0x83, 0xFE=0x11) and wait for Chip State Machine (Reg 0xFC bits 6:4) to exit power-down state S0.

#### Returns
ESP_OK if codec is verified and in active CSM state, or error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ms` | `uint32_t` | Maximum wait time in milliseconds. |

---

{#sub_audio_is_ready-1}

### sub_audio_is_ready

```cpp
bool sub_audio_is_ready(void)
```

Defined in sub_audio.c:172

Quick status check of whether ES8311 codec is ready.

#### Returns
true if communication and active CSM state verified.

---

{#es8311_init_dac_registers}

### es8311_init_dac_registers

`static`

```cpp
static esp_err_t es8311_init_dac_registers(void)
```

Defined in sub_audio.c:177

---

{#sub_audio_init-1}

### sub_audio_init

```cpp
esp_err_t sub_audio_init(void)
```

Defined in sub_audio.c:238

Initialize ES8311 codec and NS4168 amplifier.

Configures I2S audio bus and sets codec to active run mode.

#### Returns
ESP_OK on success, or an error code.

---

{#sub_audio_standby-1}

### sub_audio_standby

```cpp
esp_err_t sub_audio_standby(void)
```

Defined in sub_audio.c:349

Put ES8311 codec into ultra-low-power software standby (Reg 0x0D = 0x00 @ <1.0 µA) and pull NS4168 PA_CTRL LOW.

Keeps power rails on so I2C bus is NOT clamped by unpowered chip protection diodes.

#### Returns
ESP_OK on success.

---

{#sub_audio_render_tone_samples}

### sub_audio_render_tone_samples

`static`

```cpp
static void sub_audio_render_tone_samples(uint32_t frequency_hz, uint32_t duration_ms)
```

Defined in sub_audio.c:388

---

{#sub_audio_render_pcm_samples}

### sub_audio_render_pcm_samples

`static`

```cpp
static void sub_audio_render_pcm_samples(const int16_t * samples, size_t sample_count)
```

Defined in sub_audio.c:431

---

{#sub_audio_prepare_and_unmute}

### sub_audio_prepare_and_unmute

`static`

```cpp
static esp_err_t sub_audio_prepare_and_unmute(void)
```

Defined in sub_audio.c:453

---

{#sub_audio_exec_tone}

### sub_audio_exec_tone

`static`

```cpp
static esp_err_t sub_audio_exec_tone(uint32_t frequency_hz, uint32_t duration_ms)
```

Defined in sub_audio.c:480

---

{#sub_audio_exec_pcm}

### sub_audio_exec_pcm

`static`

```cpp
static esp_err_t sub_audio_exec_pcm(const int16_t * samples, size_t sample_count, uint32_t sample_rate_hz)
```

Defined in sub_audio.c:492

---

{#sub_audio_exec_chime}

### sub_audio_exec_chime

`static`

```cpp
static esp_err_t sub_audio_exec_chime(uint8_t type)
```

Defined in sub_audio.c:503

---

{#sub_audio_send_command}

### sub_audio_send_command

`static`

```cpp
static esp_err_t sub_audio_send_command(const audio_cmd_t * cmd, bool is_sync, uint32_t wait_ms)
```

Defined in sub_audio.c:597

---

{#sub_audio_play_tone-1}

### sub_audio_play_tone

```cpp
esp_err_t sub_audio_play_tone(uint32_t frequency_hz, uint32_t duration_ms)
```

Defined in sub_audio.c:632

Play synthesized audio chime/tone synchronously.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `frequency_hz` | `uint32_t` | Frequency in Hertz (e.g. 1000 for 1 kHz). |
| `duration_ms` | `uint32_t` | Duration in milliseconds. |

---

{#sub_audio_play_tone_async-1}

### sub_audio_play_tone_async

```cpp
esp_err_t sub_audio_play_tone_async(uint32_t frequency_hz, uint32_t duration_ms)
```

Defined in sub_audio.c:641

Play synthesized audio chime/tone asynchronously via worker task.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `frequency_hz` | `uint32_t` | Frequency in Hertz (e.g. 1000 for 1 kHz). |
| `duration_ms` | `uint32_t` | Duration in milliseconds. |

---

{#sub_audio_play_chime-1}

### sub_audio_play_chime

```cpp
esp_err_t sub_audio_play_chime(uint8_t type)
```

Defined in sub_audio.c:650

Play standard H1OS acoustic presentation chime synchronously.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `type` | `uint8_t` | Chime type (BOOT, WAKE, SLEEP, SHUTDOWN, ALARM). |

---

{#sub_audio_play_chime_async-1}

### sub_audio_play_chime_async

```cpp
esp_err_t sub_audio_play_chime_async(uint8_t type)
```

Defined in sub_audio.c:659

Play standard H1OS acoustic presentation chime asynchronously.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `type` | `uint8_t` | Chime type (BOOT, WAKE, SLEEP, SHUTDOWN, ALARM). |

---

{#sub_audio_play_pcm-1}

### sub_audio_play_pcm

```cpp
esp_err_t sub_audio_play_pcm(const int16_t * samples, size_t sample_count, uint32_t sample_rate_hz)
```

Defined in sub_audio.c:668

Play raw 16-bit signed PCM audio samples synchronously.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `samples` | `const int16_t *` | Pointer to 16-bit signed Mono PCM samples. |
| `sample_count` | `size_t` | Number of int16_t samples. |
| `sample_rate_hz` | `uint32_t` | Sample rate in Hz (default: 16000). |

---

{#sub_audio_play_pcm_async-1}

### sub_audio_play_pcm_async

```cpp
esp_err_t sub_audio_play_pcm_async(const int16_t * samples, size_t sample_count, uint32_t sample_rate_hz)
```

Defined in sub_audio.c:677

Play raw 16-bit signed PCM audio samples asynchronously in background worker task.

Note: Caller must ensure the buffer remains valid until playback finishes (e.g., const/static buffer).

#### Returns
ESP_OK on success, ESP_ERR_NO_MEM / ESP_ERR_TIMEOUT if queue full.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `samples` | `const int16_t *` | Pointer to 16-bit signed Mono PCM samples. |
| `sample_count` | `size_t` | Number of int16_t samples. |
| `sample_rate_hz` | `uint32_t` | Sample rate in Hz (default: 16000). |

---

{#sub_audio_is_busy-1}

### sub_audio_is_busy

```cpp
bool sub_audio_is_busy(void)
```

Defined in sub_audio.c:686

Check if audio playback is currently active or queue has pending items.

#### Returns
true if playing or queued, false if idle in standby.

---

{#sub_audio_wait_idle-1}

### sub_audio_wait_idle

```cpp
esp_err_t sub_audio_wait_idle(uint32_t timeout_ms)
```

Defined in sub_audio.c:693

Wait until background audio worker completes all playback and enters standby.

#### Returns
ESP_OK if idle, ESP_ERR_TIMEOUT if still active.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ms` | `uint32_t` | Maximum time to wait in milliseconds. |

---

{#sub_audio_deinit-1}

### sub_audio_deinit

```cpp
esp_err_t sub_audio_deinit(void)
```

Defined in sub_audio.c:703

Teardown audio subsystem, stop background worker task, and delete I2S channel.

#### Returns
ESP_OK on success.

---

{#sub_audio_set_volume-1}

### sub_audio_set_volume

```cpp
esp_err_t sub_audio_set_volume(uint8_t volume_pct)
```

Defined in sub_audio.c:730

Set ES8311 DAC output volume percentage (0% = Mute, 100% = 0 dB full-scale).

Persists across standby/wake cycles.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `volume_pct` | `uint8_t` | Volume percentage (0 - 100). |

---

{#sub_audio_get_volume-1}

### sub_audio_get_volume

```cpp
uint8_t sub_audio_get_volume(void)
```

Defined in sub_audio.c:743

Get currently configured output volume percentage (0 - 100).

#### Returns
Current volume percentage.

---

{#sub_audio_set_low_power_mode-1}

### sub_audio_set_low_power_mode

```cpp
esp_err_t sub_audio_set_low_power_mode(bool enable)
```

Defined in sub_audio.c:749

Configure ES8311 DAC power mode (Low-Power vs Normal).

In low-power mode (default upon init), ES8311 operates with LPDAC enabled (Reg 0x0F bit 7 = 1), significantly reducing active DAC bias current. Normal mode provides standard bias.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `enable` | `bool` | true for Low-Power Mode (default), false for Normal Power Mode. |

---

{#sub_audio_get_low_power_mode-1}

### sub_audio_get_low_power_mode

```cpp
bool sub_audio_get_low_power_mode(void)
```

Defined in sub_audio.c:758

Query whether audio subsystem is in Low-Power Mode.

#### Returns
true if Low-Power Mode is active, false if Normal Power Mode.

---

{#mv_to_percent}

### mv_to_percent

`static`

```cpp
static uint8_t mv_to_percent(uint16_t mv)
```

Defined in sub_power.c:49

---

{#sub_power_init-1}

### sub_power_init

```cpp
esp_err_t sub_power_init(void)
```

Defined in sub_power.c:65

Initialize Battery ADC subsystem (ADC1 Channel 3 on GPIO 4 with 12 dB atten and eFuse cal).

#### Returns
ESP_OK on success, or an error code.

---

{#sub_power_deinit-1}

### sub_power_deinit

```cpp
esp_err_t sub_power_deinit(void)
```

Defined in sub_power.c:110

Deinitialize ADC handles.

#### Returns
ESP_OK on success.

---

{#compare_int}

### compare_int

`static`

```cpp
static int compare_int(const void * a, const void * b)
```

Defined in sub_power.c:127

---

{#sub_power_read_battery-1}

### sub_power_read_battery

```cpp
esp_err_t sub_power_read_battery(uint16_t * out_mv, uint8_t * out_pct)
```

Defined in sub_power.c:131

Sample calibrated battery voltage with 16-sample trimmed outlier filtering.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_mv` | `uint16_t *` | Battery voltage in millivolts (e.g. 3850 mV). |
| `out_pct` | `uint8_t *` | Estimated state of charge (0 to 100%). |

---

{#sub_power_get_ulp_cal_params-1}

### sub_power_get_ulp_cal_params

```cpp
esp_err_t sub_power_get_ulp_cal_params(uint32_t * out_scale, int32_t * out_offset_mv)
```

Defined in sub_power.c:174

Extract linear calibration coefficients (scale and offset) for ULP coprocessor hand-off.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_scale` | `uint32_t *` | Multiplier scaled by 4096. |
| `out_offset_mv` | `int32_t *` | Voltage offset in millivolts. |

---

{#sub_power_enter_deep_sleep-1}

### sub_power_enter_deep_sleep

```cpp
esp_err_t sub_power_enter_deep_sleep(uint32_t sleep_seconds, uint64_t ext1_pins_mask)
```

Defined in sub_power.c:198

Configure EXT1 wake sources and enter deep sleep.

Maintains RTC pad holds on power latch (GPIO 17) and EPD rail (GPIO 6) to keep rails active.

#### Returns
Does not return on success (enters deep sleep).

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `sleep_seconds` | `uint32_t` | Timer duration in seconds (0 = timer disabled). |
| `ext1_pins_mask` | `uint64_t` | Bitmask of RTC GPIO pins for wakeup (e.g. GPIO 0, 18, 5). |

---

{#sub_power_cut_power_latch-1}

### sub_power_cut_power_latch

```cpp
void sub_power_cut_power_latch(void)
```

Defined in sub_power.c:222

Power off system completely by releasing battery power latch (GPIO 17).

Used for critical low-battery shutdown or explicit user power-off.

---

{#sub_power_connected_usb-1}

### sub_power_connected_usb

```cpp
bool sub_power_connected_usb(void)
```

Defined in sub_power.c:228

Check to see if USB is connected.

Used for charger detection.

#### Returns
true if usb is connected, or false if disconnected.

---

{#orch_state_get}

### orch_state_get

```cpp
orch_persisted_state_t * orch_state_get(void)
```

Defined in h1os/orch_state.h:114

Retrieve pointer to the persistent state in RTC Slow Memory.

Initializes default structure on boot magic mismatch.

---

{#orch_state_reset}

### orch_state_reset

```cpp
void orch_state_reset(void)
```

Defined in h1os/orch_state.h:119

Reset persisted RTC state to default values.

---

{#orch_state_push_sample}

### orch_state_push_sample

```cpp
void orch_state_push_sample(const orch_tri_node_sample_t * sample)
```

Defined in h1os/orch_state.h:126

Push a new Tri-Node telemetry sample into the RTC ring buffer.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `sample` | const [`orch_tri_node_sample_t`](#orch_tri_node_sample_t) * | Pointer to sample data to commit. |

---

{#orch_state_get_latest_sample}

### orch_state_get_latest_sample

```cpp
bool orch_state_get_latest_sample(orch_tri_node_sample_t * out_sample)
```

Defined in h1os/orch_state.h:134

Get the latest committed sample from the ring buffer.

#### Returns
true if reading present, false if buffer empty.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_sample` | [`orch_tri_node_sample_t`](#orch_tri_node_sample_t) * | Destination pointer. |

---

{#orch_state_get_latest_valid_sample}

### orch_state_get_latest_valid_sample

```cpp
bool orch_state_get_latest_valid_sample(orch_tri_node_sample_t * out_sample)
```

Defined in h1os/orch_state.h:143

Get the newest sample in the ring buffer marked SAMPLE_FLAG_VALID_COLD.

Falls back to the latest sample if no sample has been marked valid yet.

#### Returns
true if a sample is returned, false if buffer empty.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_sample` | [`orch_tri_node_sample_t`](#orch_tri_node_sample_t) * | Destination pointer. |

---

{#sub_sdcard_mount}

### sub_sdcard_mount

```cpp
esp_err_t sub_sdcard_mount(void)
```

Defined in h1os/sub_sdcard.h:31

Mount MicroSD card using 1-bit SDMMC driver.

---

{#sub_sdcard_unmount}

### sub_sdcard_unmount

```cpp
esp_err_t sub_sdcard_unmount(void)
```

Defined in h1os/sub_sdcard.h:36

Unmount MicroSD card and release hardware bus resources.

---

{#sub_sdcard_is_mounted}

### sub_sdcard_is_mounted

```cpp
bool sub_sdcard_is_mounted(void)
```

Defined in h1os/sub_sdcard.h:41

Check if MicroSD card is mounted and ready for I/O.

---

{#sub_sdcard_get_capacity_mb}

### sub_sdcard_get_capacity_mb

```cpp
esp_err_t sub_sdcard_get_capacity_mb(uint32_t * out_capacity_mb)
```

Defined in h1os/sub_sdcard.h:46

Get total capacity of mounted card in megabytes.

---

{#sub_sdcard_format}

### sub_sdcard_format

```cpp
esp_err_t sub_sdcard_format(void)
```

Defined in h1os/sub_sdcard.h:51

Format mounted card as FAT32 filesystem.

---

{#sub_sensor_init}

### sub_sensor_init

```cpp
esp_err_t sub_sensor_init(void)
```

Defined in h1os/sub_sensor.h:26

Initialize sensor hardware interfaces (internal TSENS handle).

#### Returns
ESP_OK on success, or an error code.

---

{#sub_sensor_deinit}

### sub_sensor_deinit

```cpp
esp_err_t sub_sensor_deinit(void)
```

Defined in h1os/sub_sensor.h:32

Deinitialize internal sensor drivers to free resources.

#### Returns
ESP_OK on success.

---

{#sub_sensor_read_shtc3_raw}

### sub_sensor_read_shtc3_raw

```cpp
esp_err_t sub_sensor_read_shtc3_raw(uint16_t * out_raw_temp, uint16_t * out_raw_rh, bool low_power)
```

Defined in h1os/sub_sensor.h:42

Direct physical SHTC3 sensor readout (Wake -> Measure -> Read -> Sleep).

#### Returns
ESP_OK on success, ESP_ERR_INVALID_CRC on CRC mismatch, or I2C bus error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_raw_temp` | `uint16_t *` | Raw 16-bit Sensirion temperature register word. |
| `out_raw_rh` | `uint16_t *` | Raw 16-bit Sensirion relative humidity register word. |
| `low_power` | `bool` | True for 1ms fast low-power conversion, False for 15ms high-precision. |

---

{#sub_sensor_convert_shtc3_units}

### sub_sensor_convert_shtc3_units

```cpp
void sub_sensor_convert_shtc3_units(uint16_t raw_temp, uint16_t raw_rh, float * out_temp_c, float * out_rh_pct)
```

Defined in h1os/sub_sensor.h:52

Convert raw SHTC3 16-bit words into standard SI units.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `raw_temp` | `uint16_t` | Raw temperature word. |
| `raw_rh` | `uint16_t` | Raw relative humidity word. |
| `out_temp_c` | `float *` | Temperature in Celsius. |
| `out_rh_pct` | `float *` | Relative humidity in percent (0.0 to 100.0). |

---

{#sub_sensor_read_mcu_die_temp}

### sub_sensor_read_mcu_die_temp

```cpp
esp_err_t sub_sensor_read_mcu_die_temp(float * out_die_temp_c)
```

Defined in h1os/sub_sensor.h:60

Read ESP32-S3 internal silicon junction temperature via internal TSENS macro.

#### Returns
ESP_OK on success, or driver error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_die_temp_c` | `float *` | MCU die temperature in Celsius. |

---

{#orch_state_get-1}

### orch_state_get

```cpp
orch_persisted_state_t *RTC_IRAM_ATTR orch_state_get(void)
```

Defined in orch_state.c:14

Retrieve pointer to the persistent state in RTC Slow Memory.

Initializes default structure on boot magic mismatch.

---

{#orch_state_reset-1}

### orch_state_reset

```cpp
void RTC_IRAM_ATTR orch_state_reset(void)
```

Defined in orch_state.c:22

Reset persisted RTC state to default values.

---

{#orch_state_push_sample-1}

### orch_state_push_sample

```cpp
void RTC_IRAM_ATTR orch_state_push_sample(const orch_tri_node_sample_t * sample)
```

Defined in orch_state.c:38

Push a new Tri-Node telemetry sample into the RTC ring buffer.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `sample` | const [`orch_tri_node_sample_t`](#orch_tri_node_sample_t) * | Pointer to sample data to commit. |

---

{#orch_state_get_latest_sample-1}

### orch_state_get_latest_sample

```cpp
bool orch_state_get_latest_sample(orch_tri_node_sample_t * out_sample)
```

Defined in orch_state.c:48

Get the latest committed sample from the ring buffer.

#### Returns
true if reading present, false if buffer empty.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_sample` | [`orch_tri_node_sample_t`](#orch_tri_node_sample_t) * | Destination pointer. |

---

{#orch_state_get_latest_valid_sample-1}

### orch_state_get_latest_valid_sample

```cpp
bool orch_state_get_latest_valid_sample(orch_tri_node_sample_t * out_sample)
```

Defined in orch_state.c:60

Get the newest sample in the ring buffer marked SAMPLE_FLAG_VALID_COLD.

Falls back to the latest sample if no sample has been marked valid yet.

#### Returns
true if a sample is returned, false if buffer empty.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_sample` | [`orch_tri_node_sample_t`](#orch_tri_node_sample_t) * | Destination pointer. |

---

{#sub_sdcard_mount-1}

### sub_sdcard_mount

```cpp
esp_err_t sub_sdcard_mount(void)
```

Defined in sub_sdcard.c:21

Mount MicroSD card using 1-bit SDMMC driver.

---

{#sub_sdcard_unmount-1}

### sub_sdcard_unmount

```cpp
esp_err_t sub_sdcard_unmount(void)
```

Defined in sub_sdcard.c:65

Unmount MicroSD card and release hardware bus resources.

---

{#sub_sdcard_is_mounted-1}

### sub_sdcard_is_mounted

```cpp
bool sub_sdcard_is_mounted(void)
```

Defined in sub_sdcard.c:79

Check if MicroSD card is mounted and ready for I/O.

---

{#sub_sdcard_get_capacity_mb-1}

### sub_sdcard_get_capacity_mb

```cpp
esp_err_t sub_sdcard_get_capacity_mb(uint32_t * out_capacity_mb)
```

Defined in sub_sdcard.c:84

Get total capacity of mounted card in megabytes.

---

{#sub_sdcard_format-1}

### sub_sdcard_format

```cpp
esp_err_t sub_sdcard_format(void)
```

Defined in sub_sdcard.c:94

Format mounted card as FAT32 filesystem.

---

{#shtc3_calc_crc}

### shtc3_calc_crc

`static`

```cpp
static uint8_t shtc3_calc_crc(const uint8_t * data, size_t len)
```

Defined in sub_sensor.c:32

---

{#sub_sensor_init-1}

### sub_sensor_init

```cpp
esp_err_t sub_sensor_init(void)
```

Defined in sub_sensor.c:48

Initialize sensor hardware interfaces (internal TSENS handle).

#### Returns
ESP_OK on success, or an error code.

---

{#sub_sensor_deinit-1}

### sub_sensor_deinit

```cpp
esp_err_t sub_sensor_deinit(void)
```

Defined in sub_sensor.c:69

Deinitialize internal sensor drivers to free resources.

#### Returns
ESP_OK on success.

---

{#sub_sensor_read_shtc3_raw-1}

### sub_sensor_read_shtc3_raw

```cpp
esp_err_t sub_sensor_read_shtc3_raw(uint16_t * out_raw_temp, uint16_t * out_raw_rh, bool low_power)
```

Defined in sub_sensor.c:80

Direct physical SHTC3 sensor readout (Wake -> Measure -> Read -> Sleep).

#### Returns
ESP_OK on success, ESP_ERR_INVALID_CRC on CRC mismatch, or I2C bus error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_raw_temp` | `uint16_t *` | Raw 16-bit Sensirion temperature register word. |
| `out_raw_rh` | `uint16_t *` | Raw 16-bit Sensirion relative humidity register word. |
| `low_power` | `bool` | True for 1ms fast low-power conversion, False for 15ms high-precision. |

---

{#sub_sensor_convert_shtc3_units-1}

### sub_sensor_convert_shtc3_units

```cpp
void sub_sensor_convert_shtc3_units(uint16_t raw_temp, uint16_t raw_rh, float * out_temp_c, float * out_rh_pct)
```

Defined in sub_sensor.c:141

Convert raw SHTC3 16-bit words into standard SI units.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `raw_temp` | `uint16_t` | Raw temperature word. |
| `raw_rh` | `uint16_t` | Raw relative humidity word. |
| `out_temp_c` | `float *` | Temperature in Celsius. |
| `out_rh_pct` | `float *` | Relative humidity in percent (0.0 to 100.0). |

---

{#sub_sensor_read_mcu_die_temp-1}

### sub_sensor_read_mcu_die_temp

```cpp
esp_err_t sub_sensor_read_mcu_die_temp(float * out_die_temp_c)
```

Defined in sub_sensor.c:156

Read ESP32-S3 internal silicon junction temperature via internal TSENS macro.

#### Returns
ESP_OK on success, or driver error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_die_temp_c` | `float *` | MCU die temperature in Celsius. |

---

{#sub_display_init}

### sub_display_init

```cpp
esp_err_t sub_display_init(bool is_wake_cycle)
```

Defined in h1os/sub_display.h:36

Initialize SSD1681 display controller.

Wakes panel, initializes SPI interface, configures scanning geometry, and sets up BUSY synchronization semaphore.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `is_wake_cycle` | `bool` | True if resuming from deep sleep with persistent framebuffer. |

---

{#sub_display_get_framebuffer}

### sub_display_get_framebuffer

```cpp
uint8_t * sub_display_get_framebuffer(void)
```

Defined in h1os/sub_display.h:42

Get pointer to the active working framebuffer (5000 bytes, 1-bit per pixel).

Bit 1 = White, Bit 0 = Black.

---

{#sub_display_clear}

### sub_display_clear

```cpp
void sub_display_clear(uint8_t color)
```

Defined in h1os/sub_display.h:49

Clear active working framebuffer.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `color` | `uint8_t` | 0xFF for White, 0x00 for Black. |

---

{#sub_display_sync_previous_frame}

### sub_display_sync_previous_frame

```cpp
esp_err_t sub_display_sync_previous_frame(const uint8_t * prev_frame)
```

Defined in h1os/sub_display.h:58

Synchronize previous frame into shadow buffer and hardware RAM 0x26.

Essential on deep sleep wake to enable differential partial scanning against the glass.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `prev_frame` | `const uint8_t *` | Pointer to 5000-byte pre-sleep image buffer. |

---

{#sub_display_wait_busy}

### sub_display_wait_busy

```cpp
esp_err_t sub_display_wait_busy(TickType_t timeout_ticks)
```

Defined in h1os/sub_display.h:67

Synchronously wait for EPD panel to finish driving electrophoretic particles.

Blocks on binary semaphore driven by GPIO 8 (BUSY) falling edge.

#### Returns
ESP_OK on panel ready, ESP_ERR_TIMEOUT on expiration.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ticks` | `TickType_t` | Max FreeRTOS ticks to wait. |

---

{#sub_display_refresh_full}

### sub_display_refresh_full

```cpp
esp_err_t sub_display_refresh_full(void)
```

Defined in h1os/sub_display.h:75

Execute full display refresh (OTP factory waveform LUT).

Synchronizes old frame RAM (0x26) with new frame RAM (0x24).

#### Returns
ESP_OK on success.

---

{#sub_display_clear_to_white_full}

### sub_display_clear_to_white_full

```cpp
esp_err_t sub_display_clear_to_white_full(void)
```

Defined in h1os/sub_display.h:83

Clear display to pure white and trigger full OTP refresh.

Chemically neutralizes electrophoretic microcapsules to protect against permanent burn-in.

#### Returns
ESP_OK on success.

---

{#sub_display_refresh_partial}

### sub_display_refresh_partial

```cpp
esp_err_t sub_display_refresh_partial(void)
```

Defined in h1os/sub_display.h:90

Execute fast partial refresh (~300ms) with software LUT.

#### Returns
ESP_OK on success.

---

{#sub_display_read_glass_temp}

### sub_display_read_glass_temp

```cpp
esp_err_t sub_display_read_glass_temp(float * out_temp_c)
```

Defined in h1os/sub_display.h:98

Read SSD1681 on-glass integrated temperature sensor (SPI Cmd 0x1B).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_temp_c` | `float *` | Surface glass temperature in Celsius. |

---

{#sub_display_enter_deep_sleep}

### sub_display_enter_deep_sleep

```cpp
esp_err_t sub_display_enter_deep_sleep(void)
```

Defined in h1os/sub_display.h:106

Put SSD1681 into Deep Sleep Mode 1 (Command 0x10, Data 0x01 @ 1.0 µA).

Crucially retains RAM contents while the 3.3V rail remains held.

#### Returns
ESP_OK on success.

---

{#h1os_lvgl_port_task}

### h1os_lvgl_port_task

`static`

```cpp
static void h1os_lvgl_port_task(void * pvParameters)
```

Defined in h1os_lvgl.cpp:263

---

{#h1os_lvgl_lock-1}

### h1os_lvgl_lock

```cpp
bool h1os_lvgl_lock(uint32_t timeout_ms)
```

Defined in h1os_lvgl.cpp:38

Acquire LVGL reentrant mutex lock.

---

{#h1os_lvgl_unlock-1}

### h1os_lvgl_unlock

```cpp
void h1os_lvgl_unlock(void)
```

Defined in h1os_lvgl.cpp:43

Release LVGL reentrant mutex lock.

---

{#lvgl_tick_get_cb}

### lvgl_tick_get_cb

`static`

```cpp
static uint32_t lvgl_tick_get_cb(void)
```

Defined in h1os_lvgl.cpp:47

---

{#lvgl_keypad_read_cb}

### lvgl_keypad_read_cb

`static`

```cpp
static void lvgl_keypad_read_cb(lv_indev_t * indev, lv_indev_data_t * data)
```

Defined in h1os_lvgl.cpp:51

---

{#lvgl_display_flush_cb}

### lvgl_display_flush_cb

`static`

```cpp
static void lvgl_display_flush_cb(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map)
```

Defined in h1os_lvgl.cpp:68

---

{#h1os_lvgl_init-1}

### h1os_lvgl_init

```cpp
esp_err_t h1os_lvgl_init(bool is_wake_cycle)
```

Defined in h1os_lvgl.cpp:145

Initialize LVGL v9 graphics subsystem, 1-bit display buffer, and keypad input driver.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `is_wake_cycle` | `bool` | True if resuming from sleep (enables differential partial flush). |

---

{#h1os_lvgl_set_first_flush_mode-1}

### h1os_lvgl_set_first_flush_mode

```cpp
void h1os_lvgl_set_first_flush_mode(bool full_refresh)
```

Defined in h1os_lvgl.cpp:202

Explicitly override whether the first flush executes a full or partial refresh.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `full_refresh` | `bool` | True for full OTP flashing refresh, False for differential partial. |

---

{#h1os_lvgl_start-1}

### h1os_lvgl_start

```cpp
esp_err_t h1os_lvgl_start(int task_priority, int core_id)
```

Defined in h1os_lvgl.cpp:207

Start the LVGL background FreeRTOS task.

---

{#h1os_lvgl_stop-1}

### h1os_lvgl_stop

```cpp
esp_err_t h1os_lvgl_stop(void)
```

Defined in h1os_lvgl.cpp:231

Stop the LVGL background task.

---

{#h1os_lvgl_has_pending_tasks-1}

### h1os_lvgl_has_pending_tasks

```cpp
bool h1os_lvgl_has_pending_tasks(void)
```

Defined in h1os_lvgl.cpp:244

Check if the LVGL display pipeline has pending render/flush tasks.

---

{#h1os_lvgl_get_indev-1}

### h1os_lvgl_get_indev

```cpp
lv_indev_t * h1os_lvgl_get_indev(void)
```

Defined in h1os_lvgl.cpp:258

Retrieve the LVGL keypad input device handle.

---

{#epd_busy_isr_handler}

### epd_busy_isr_handler

`static`

```cpp
static void IRAM_ATTR epd_busy_isr_handler(void * arg)
```

Defined in sub_display.cpp:54

---

{#epd_reset_pulse}

### epd_reset_pulse

`static`

```cpp
static void epd_reset_pulse(void)
```

Defined in sub_display.cpp:63

---

{#sub_display_wait_busy-1}

### sub_display_wait_busy

```cpp
esp_err_t sub_display_wait_busy(TickType_t timeout_ticks)
```

Defined in sub_display.cpp:71

Synchronously wait for EPD panel to finish driving electrophoretic particles.

Blocks on binary semaphore driven by GPIO 8 (BUSY) falling edge.

#### Returns
ESP_OK on panel ready, ESP_ERR_TIMEOUT on expiration.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ticks` | `TickType_t` | Max FreeRTOS ticks to wait. |

---

{#epd_configure_base_registers}

### epd_configure_base_registers

`static`

```cpp
static void epd_configure_base_registers(void)
```

Defined in sub_display.cpp:101

---

{#sub_display_init-1}

### sub_display_init

```cpp
esp_err_t sub_display_init(bool is_wake_cycle)
```

Defined in sub_display.cpp:129

Initialize SSD1681 display controller.

Wakes panel, initializes SPI interface, configures scanning geometry, and sets up BUSY synchronization semaphore.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `is_wake_cycle` | `bool` | True if resuming from deep sleep with persistent framebuffer. |

---

{#sub_display_get_framebuffer-1}

### sub_display_get_framebuffer

```cpp
uint8_t * sub_display_get_framebuffer(void)
```

Defined in sub_display.cpp:184

Get pointer to the active working framebuffer (5000 bytes, 1-bit per pixel).

Bit 1 = White, Bit 0 = Black.

---

{#sub_display_clear-1}

### sub_display_clear

```cpp
void sub_display_clear(uint8_t color)
```

Defined in sub_display.cpp:189

Clear active working framebuffer.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `color` | `uint8_t` | 0xFF for White, 0x00 for Black. |

---

{#set_ram_counters}

### set_ram_counters

`static`

```cpp
static void set_ram_counters(void)
```

Defined in sub_display.cpp:194

---

{#sub_display_sync_previous_frame-1}

### sub_display_sync_previous_frame

```cpp
esp_err_t sub_display_sync_previous_frame(const uint8_t * prev_frame)
```

Defined in sub_display.cpp:204

Synchronize previous frame into shadow buffer and hardware RAM 0x26.

Essential on deep sleep wake to enable differential partial scanning against the glass.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `prev_frame` | `const uint8_t *` | Pointer to 5000-byte pre-sleep image buffer. |

---

{#sub_display_refresh_full-1}

### sub_display_refresh_full

```cpp
esp_err_t sub_display_refresh_full(void)
```

Defined in sub_display.cpp:219

Execute full display refresh (OTP factory waveform LUT).

Synchronizes old frame RAM (0x26) with new frame RAM (0x24).

#### Returns
ESP_OK on success.

---

{#sub_display_clear_to_white_full-1}

### sub_display_clear_to_white_full

```cpp
esp_err_t sub_display_clear_to_white_full(void)
```

Defined in sub_display.cpp:259

Clear display to pure white and trigger full OTP refresh.

Chemically neutralizes electrophoretic microcapsules to protect against permanent burn-in.

#### Returns
ESP_OK on success.

---

{#epd_load_custom_lut}

### epd_load_custom_lut

`static`

```cpp
static void epd_load_custom_lut(const uint8_t * lut_buffer)
```

Defined in sub_display.cpp:267

---

{#sub_display_refresh_partial-1}

### sub_display_refresh_partial

```cpp
esp_err_t sub_display_refresh_partial(void)
```

Defined in sub_display.cpp:292

Execute fast partial refresh (~300ms) with software LUT.

#### Returns
ESP_OK on success.

---

{#sub_display_read_glass_temp-1}

### sub_display_read_glass_temp

```cpp
esp_err_t sub_display_read_glass_temp(float * out_temp_c)
```

Defined in sub_display.cpp:331

Read SSD1681 on-glass integrated temperature sensor (SPI Cmd 0x1B).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_temp_c` | `float *` | Surface glass temperature in Celsius. |

---

{#sub_display_enter_deep_sleep-1}

### sub_display_enter_deep_sleep

```cpp
esp_err_t sub_display_enter_deep_sleep(void)
```

Defined in sub_display.cpp:362

Put SSD1681 into Deep Sleep Mode 1 (Command 0x10, Data 0x01 @ 1.0 µA).

Crucially retains RAM contents while the 3.3V rail remains held.

#### Returns
ESP_OK on success.

---

{#h1os_reset_session_timer-1}

### h1os_reset_session_timer

```cpp
void h1os_reset_session_timer(void)
```

Defined in h1os_lifecycle.c:45

Reset the interactive session inactivity timer (extends session by timeout_sec).

---

{#h1os_is_session_active-1}

### h1os_is_session_active

```cpp
bool h1os_is_session_active(void)
```

Defined in h1os_lifecycle.c:53

Check whether an interactive inactivity countdown session is active.

#### Returns
true if running in an interactive user session, false during unattended wakes.

---

{#h1os_trigger_chime}

### h1os_trigger_chime

`static`

```cpp
static void h1os_trigger_chime(h1os_chime_type_t type)
```

Defined in h1os_lifecycle.c:58

---

{#h1os_trigger_splash}

### h1os_trigger_splash

`static`

```cpp
static void h1os_trigger_splash(h1os_splash_type_t type)
```

Defined in h1os_lifecycle.c:67

---

{#h1os_session_monitor_task}

### h1os_session_monitor_task

`static`

```cpp
static void h1os_session_monitor_task(void * arg)
```

Defined in h1os_lifecycle.c:74

---

{#h1os_start-1}

### h1os_start

```cpp
esp_err_t h1os_start(const h1os_lifecycle_t * config)
```

Defined in h1os_lifecycle.c:94

Initialize H1OS and dispatch application lifecycle.

---

{#h1os_get_telemetry-1}

### h1os_get_telemetry

```cpp
esp_err_t h1os_get_telemetry(h1os_telemetry_t * out_telemetry)
```

Defined in h1os_lifecycle.c:242

Retrieve current Tri-Node environmental telemetry.

---

{#h1os_sleep-1}

### h1os_sleep

```cpp
esp_err_t h1os_sleep(uint32_t sleep_sec)
```

Defined in h1os_lifecycle.c:302

Put the platform into ultra-low-power deep sleep.

---

{#execute_system_shutdown}

### execute_system_shutdown

`static`

```cpp
static void execute_system_shutdown(bool force_clean_white)
```

Defined in h1os_lifecycle.c:313

---

{#h1os_shutdown-1}

### h1os_shutdown

```cpp
void h1os_shutdown(void)
```

Defined in h1os_lifecycle.c:365

Orderly system shutdown and physical battery power cut.

---

{#h1os_shutdown_for_storage-1}

### h1os_shutdown_for_storage

```cpp
void h1os_shutdown_for_storage(void)
```

Defined in h1os_lifecycle.c:374

Shutdown for long-term storage: clears display to pure white before cutting power.

Protects e-Paper electrophoretic microcapsules against permanent dye migration and burn-in.

---

{#h1os_set_volume-1}

### h1os_set_volume

```cpp
esp_err_t h1os_set_volume(uint8_t volume_pct)
```

Defined in h1os_lifecycle.c:379

Set audio subsystem output volume percentage (0% = Mute, 100% = 0 dB Max).

---

{#orch_wake_stub_install}

### orch_wake_stub_install

```cpp
void orch_wake_stub_install(void)
```

Defined in h1os/orch_wake_stub.h:26

Install the RTC deep sleep wake stub.

Called before entering deep sleep to arm the ultra-fast wake stub handler.

---

{#bsp_wake_stub}

### bsp_wake_stub

```cpp
void bsp_wake_stub(void)
```

Defined in h1os/orch_wake_stub.h:32

Master RTC Wake Stub entry function.

Marked with RTC_IRAM_ATTR to reside in RTC Fast Memory.

---

{#i2c_delay}

### i2c_delay

`static` `inline`

```cpp
static inline void RTC_IRAM_ATTR i2c_delay(void)
```

Defined in orch_wake_stub.c:43

---

{#sda_high}

### sda_high

`static` `inline`

```cpp
static inline void RTC_IRAM_ATTR sda_high(void)
```

Defined in orch_wake_stub.c:48

---

{#sda_low}

### sda_low

`static` `inline`

```cpp
static inline void RTC_IRAM_ATTR sda_low(void)
```

Defined in orch_wake_stub.c:54

---

{#scl_high}

### scl_high

`static` `inline`

```cpp
static inline void RTC_IRAM_ATTR scl_high(void)
```

Defined in orch_wake_stub.c:61

---

{#scl_low}

### scl_low

`static` `inline`

```cpp
static inline void RTC_IRAM_ATTR scl_low(void)
```

Defined in orch_wake_stub.c:67

---

{#sda_read}

### sda_read

`static` `inline`

```cpp
static inline uint8_t RTC_IRAM_ATTR sda_read(void)
```

Defined in orch_wake_stub.c:74

---

{#i2c_start}

### i2c_start

`static`

```cpp
static void RTC_IRAM_ATTR i2c_start(void)
```

Defined in orch_wake_stub.c:79

---

{#i2c_stop}

### i2c_stop

`static`

```cpp
static void RTC_IRAM_ATTR i2c_stop(void)
```

Defined in orch_wake_stub.c:90

---

{#i2c_write_byte}

### i2c_write_byte

`static`

```cpp
static bool RTC_IRAM_ATTR i2c_write_byte(uint8_t byte)
```

Defined in orch_wake_stub.c:100

---

{#i2c_read_byte}

### i2c_read_byte

`static`

```cpp
static uint8_t RTC_IRAM_ATTR i2c_read_byte(bool ack)
```

Defined in orch_wake_stub.c:126

---

{#shtc3_crc8}

### shtc3_crc8

`static`

```cpp
static uint8_t RTC_IRAM_ATTR shtc3_crc8(const uint8_t * data, size_t len)
```

Defined in orch_wake_stub.c:158

---

{#wake_stub_read_die_temp_centi_c}

### wake_stub_read_die_temp_centi_c

`static`

```cpp
static int16_t RTC_IRAM_ATTR wake_stub_read_die_temp_centi_c(int16_t cal_centi_c, int16_t fallback_centi_c)
```

Defined in orch_wake_stub.c:175

---

{#shtc3_send_sleep}

### shtc3_send_sleep

`static`

```cpp
static void RTC_IRAM_ATTR shtc3_send_sleep(void)
```

Defined in orch_wake_stub.c:213

---

{#bsp_wake_stub-1}

### bsp_wake_stub

```cpp
void RTC_IRAM_ATTR bsp_wake_stub(void)
```

Defined in orch_wake_stub.c:224

Master RTC Wake Stub entry function.

Marked with RTC_IRAM_ATTR to reside in RTC Fast Memory.

---

{#orch_wake_stub_install-1}

### orch_wake_stub_install

```cpp
void orch_wake_stub_install(void)
```

Defined in orch_wake_stub.c:412

Install the RTC deep sleep wake stub.

Called before entering deep sleep to arm the ultra-fast wake stub handler.

---

{#orch_display_sync_mark_dirty}

### orch_display_sync_mark_dirty

```cpp
void orch_display_sync_mark_dirty(void)
```

Defined in h1os/orch_display_sync.h:25

Mark the current display framebuffer as dirty (needs flash persistence on sleep).

---

{#orch_display_sync_save_if_dirty}

### orch_display_sync_save_if_dirty

```cpp
esp_err_t orch_display_sync_save_if_dirty(void)
```

Defined in h1os/orch_display_sync.h:32

Save working display framebuffer to "epd_frame" flash partition if dirty.

#### Returns
ESP_OK on success or if clean (no write needed).

---

{#orch_display_sync_restore_to_framebuffer}

### orch_display_sync_restore_to_framebuffer

```cpp
esp_err_t orch_display_sync_restore_to_framebuffer(void)
```

Defined in h1os/orch_display_sync.h:39

Restore framebuffer from "epd_frame" flash partition into display working buffer.

#### Returns
ESP_OK on success, ESP_ERR_NOT_FOUND if partition empty/invalid.

---

{#orch_display_sync_should_full_refresh}

### orch_display_sync_should_full_refresh

```cpp
bool orch_display_sync_should_full_refresh(void)
```

Defined in h1os/orch_display_sync.h:47

Determine if a full OTP display refresh is required.

Evaluates whether the anti-ghosting partial refresh limit has been reached.

#### Returns
true if full refresh required, false if differential partial refresh is permitted.

---

{#orch_display_sync_record_partial_refresh}

### orch_display_sync_record_partial_refresh

```cpp
void orch_display_sync_record_partial_refresh(void)
```

Defined in h1os/orch_display_sync.h:53

Record execution of a differential partial refresh.

Increments the accumulated partial refresh counter in persistent RTC memory.

---

{#orch_display_sync_record_full_refresh}

### orch_display_sync_record_full_refresh

```cpp
void orch_display_sync_record_full_refresh(void)
```

Defined in h1os/orch_display_sync.h:59

Record execution of a full OTP display refresh.

Resets the accumulated partial refresh counter back to 0.

---

{#orch_display_sync_get_partial_count}

### orch_display_sync_get_partial_count

```cpp
uint16_t orch_display_sync_get_partial_count(void)
```

Defined in h1os/orch_display_sync.h:64

Get the accumulated count of partial refreshes since the last full refresh.

---

{#orch_display_sync_mark_dirty-1}

### orch_display_sync_mark_dirty

```cpp
void orch_display_sync_mark_dirty(void)
```

Defined in orch_display_sync.c:24

Mark the current display framebuffer as dirty (needs flash persistence on sleep).

---

{#orch_display_sync_save_if_dirty-1}

### orch_display_sync_save_if_dirty

```cpp
esp_err_t orch_display_sync_save_if_dirty(void)
```

Defined in orch_display_sync.c:29

Save working display framebuffer to "epd_frame" flash partition if dirty.

#### Returns
ESP_OK on success or if clean (no write needed).

---

{#orch_display_sync_restore_to_framebuffer-1}

### orch_display_sync_restore_to_framebuffer

```cpp
esp_err_t orch_display_sync_restore_to_framebuffer(void)
```

Defined in orch_display_sync.c:50

Restore framebuffer from "epd_frame" flash partition into display working buffer.

#### Returns
ESP_OK on success, ESP_ERR_NOT_FOUND if partition empty/invalid.

---

{#orch_display_sync_should_full_refresh-1}

### orch_display_sync_should_full_refresh

```cpp
bool orch_display_sync_should_full_refresh(void)
```

Defined in orch_display_sync.c:71

Determine if a full OTP display refresh is required.

Evaluates whether the anti-ghosting partial refresh limit has been reached.

#### Returns
true if full refresh required, false if differential partial refresh is permitted.

---

{#orch_display_sync_record_partial_refresh-1}

### orch_display_sync_record_partial_refresh

```cpp
void orch_display_sync_record_partial_refresh(void)
```

Defined in orch_display_sync.c:85

Record execution of a differential partial refresh.

Increments the accumulated partial refresh counter in persistent RTC memory.

---

{#orch_display_sync_record_full_refresh-1}

### orch_display_sync_record_full_refresh

```cpp
void orch_display_sync_record_full_refresh(void)
```

Defined in orch_display_sync.c:93

Record execution of a full OTP display refresh.

Resets the accumulated partial refresh counter back to 0.

---

{#orch_display_sync_get_partial_count-1}

### orch_display_sync_get_partial_count

```cpp
uint16_t orch_display_sync_get_partial_count(void)
```

Defined in orch_display_sync.c:100

Get the accumulated count of partial refreshes since the last full refresh.

## Variables

---

{#tag}

### TAG

`static`

```cpp
const char * TAG = "HAL_IO"
```

Defined in hal_io.c:16

---

{#tag-1}

### TAG

`static`

```cpp
const char * TAG = "HAL_I2C"
```

Defined in hal_i2c.c:12

---

{#s_bus_handle}

### s_bus_handle

`static`

```cpp
i2c_master_bus_handle_t s_bus_handle = NULL
```

Defined in hal_i2c.c:14

---

{#s_i2c_mutex}

### s_i2c_mutex

`static`

```cpp
SemaphoreHandle_t s_i2c_mutex = NULL
```

Defined in hal_i2c.c:15

---

{#s_is_inited}

### s_is_inited

`static`

```cpp
bool s_is_inited = false
```

Defined in hal_i2c.c:16

---

{#tag-2}

### TAG

`static`

```cpp
const char * TAG = "HAL_SPI"
```

Defined in hal_spi.c:12

---

{#s_spi_dev}

### s_spi_dev

`static`

```cpp
spi_device_handle_t s_spi_dev = NULL
```

Defined in hal_spi.c:14

---

{#s_spi_read_dev}

### s_spi_read_dev

`static`

```cpp
spi_device_handle_t s_spi_read_dev = NULL
```

Defined in hal_spi.c:15

---

{#s_is_inited-1}

### s_is_inited

`static`

```cpp
bool s_is_inited = false
```

Defined in hal_spi.c:17

---

{#tag-3}

### TAG

`static`

```cpp
const char * TAG = "sub_nvs"
```

Defined in sub_nvs.c:15

---

{#s_nvs_initialized}

### s_nvs_initialized

`static`

```cpp
bool s_nvs_initialized = false
```

Defined in sub_nvs.c:16

---

{#tag-4}

### TAG

`static`

```cpp
const char * TAG = "sub_rtc"
```

Defined in sub_rtc.c:14

---

{#tag-5}

### TAG

`static`

```cpp
const char * TAG = "h1os_time"
```

Defined in h1os_time.c:16

---

{#s_sync_cb}

### s_sync_cb

`static`

```cpp
h1os_time_sync_cb_t s_sync_cb = NULL
```

Type: [`h1os_time_sync_cb_t`](#h1os_time_sync_cb_t)

Defined in h1os_time.c:18

---

{#s_sync_user_data}

### s_sync_user_data

`static`

```cpp
void * s_sync_user_data = NULL
```

Defined in h1os_time.c:19

---

{#tag-6}

### TAG

`static`

```cpp
const char * TAG = "HAL_FLASH"
```

Defined in hal_flash.c:12

---

{#s_part}

### s_part

`static`

```cpp
const esp_partition_t * s_part = NULL
```

Defined in hal_flash.c:14

---

{#tag-7}

### TAG

`static`

```cpp
const char * TAG = "orch_flow"
```

Defined in orch_flow.c:26

---

{#tag-8}

### TAG

`static`

```cpp
const char * TAG = "sub_audio"
```

Defined in sub_audio.c:31

---

{#s_tx_chan}

### s_tx_chan

`static`

```cpp
i2s_chan_handle_t s_tx_chan = NULL
```

Defined in sub_audio.c:72

---

{#s_audio_inited}

### s_audio_inited

`static`

```cpp
bool s_audio_inited = false
```

Defined in sub_audio.c:74

---

{#s_i2s_chan_enabled}

### s_i2s_chan_enabled

`static`

```cpp
bool s_i2s_chan_enabled = false
```

Defined in sub_audio.c:75

---

{#s_codec_in_standby}

### s_codec_in_standby

`static`

```cpp
bool s_codec_in_standby = false
```

Defined in sub_audio.c:76

---

{#s_low_power_mode}

### s_low_power_mode

`static`

```cpp
bool s_low_power_mode = true
```

Defined in sub_audio.c:77

---

{#s_audio_queue}

### s_audio_queue

`static`

```cpp
QueueHandle_t s_audio_queue = NULL
```

Defined in sub_audio.c:79

---

{#s_audio_task_handle}

### s_audio_task_handle

`static`

```cpp
TaskHandle_t s_audio_task_handle = NULL
```

Defined in sub_audio.c:80

---

{#s_audio_is_busy}

### s_audio_is_busy

`static`

```cpp
volatile bool s_audio_is_busy = false
```

Defined in sub_audio.c:81

---

{#s_volume_pct}

### s_volume_pct

`static`

```cpp
uint8_t s_volume_pct = 50
```

Defined in sub_audio.c:82

---

{#es8311_perceptual_vol_table}

### es8311_perceptual_vol_table

`static`

```cpp
const uint8_t es8311_perceptual_vol_table[101]
```

Defined in sub_audio.c:91

---

{#tag-9}

### TAG

`static`

```cpp
const char * TAG = "sub_power"
```

Defined in sub_power.c:21

---

{#s_adc_handle}

### s_adc_handle

`static`

```cpp
adc_oneshot_unit_handle_t s_adc_handle = NULL
```

Defined in sub_power.c:23

---

{#s_cali_handle}

### s_cali_handle

`static`

```cpp
adc_cali_handle_t s_cali_handle = NULL
```

Defined in sub_power.c:24

---

{#s_cali_valid}

### s_cali_valid

`static`

```cpp
bool s_cali_valid = false
```

Defined in sub_power.c:25

---

{#s_lipo_table}

### s_lipo_table

`static`

```cpp
const struct @103206253010331351125062271206070174360205162247 s_lipo_table[]
```

Defined in sub_power.c:45

---

{#s_persisted_state}

### s_persisted_state

`static`

```cpp
RTC_DATA_ATTR orch_persisted_state_t s_persisted_state
```

Type: RTC_DATA_ATTR [`orch_persisted_state_t`](#orch_persisted_state_t)

Defined in orch_state.c:12

---

{#tag-10}

### TAG

`static`

```cpp
const char * TAG = "sub_sdcard"
```

Defined in sub_sdcard.c:17

---

{#s_sd_card}

### s_sd_card

`static`

```cpp
sdmmc_card_t * s_sd_card = NULL
```

Defined in sub_sdcard.c:19

---

{#tag-11}

### TAG

`static`

```cpp
const char * TAG = "sub_sensor"
```

Defined in sub_sensor.c:19

---

{#s_tsens_handle}

### s_tsens_handle

`static`

```cpp
temperature_sensor_handle_t s_tsens_handle = NULL
```

Defined in sub_sensor.c:27

---

{#s_tsens_inited}

### s_tsens_inited

`static`

```cpp
bool s_tsens_inited = false
```

Defined in sub_sensor.c:29

---

{#tag-12}

### TAG

`static`

```cpp
const char * TAG = "h1os_lvgl"
```

Defined in h1os_lvgl.cpp:26

---

{#s_lv_display}

### s_lv_display

`static`

```cpp
lv_display_t * s_lv_display = NULL
```

Defined in h1os_lvgl.cpp:28

---

{#s_lv_keypad_indev}

### s_lv_keypad_indev

`static`

```cpp
lv_indev_t * s_lv_keypad_indev = NULL
```

Defined in h1os_lvgl.cpp:29

---

{#s_lvgl_task_handle}

### s_lvgl_task_handle

`static`

```cpp
TaskHandle_t s_lvgl_task_handle = NULL
```

Defined in h1os_lvgl.cpp:30

---

{#s_lvgl_task_running}

### s_lvgl_task_running

`static`

```cpp
bool s_lvgl_task_running = false
```

Defined in h1os_lvgl.cpp:31

---

{#s_first_boot_flush}

### s_first_boot_flush

`static`

```cpp
bool s_first_boot_flush = true
```

Defined in h1os_lvgl.cpp:32

---

{#tag-13}

### TAG

`static`

```cpp
const char * TAG = "sub_display"
```

Defined in sub_display.cpp:21

---

{#s_current_frame}

### s_current_frame

`static`

```cpp
uint8_t s_current_frame[((200 *200)/8)]
```

Defined in sub_display.cpp:24

---

{#s_previous_frame}

### s_previous_frame

`static`

```cpp
uint8_t s_previous_frame[((200 *200)/8)]
```

Defined in sub_display.cpp:25

---

{#s_busy_sem}

### s_busy_sem

`static`

```cpp
SemaphoreHandle_t s_busy_sem = NULL
```

Defined in sub_display.cpp:27

---

{#s_inited}

### s_inited

`static`

```cpp
bool s_inited = false
```

Defined in sub_display.cpp:29

---

{#wf_partial_1in54}

### WF_PARTIAL_1IN54

`static`

```cpp
const uint8_t WF_PARTIAL_1IN54[159]
```

Defined in sub_display.cpp:32

---

{#tag-14}

### TAG

`static`

```cpp
const char * TAG = "h1os_lifecycle"
```

Defined in h1os_lifecycle.c:38

---

{#s_app_lifecycle}

### s_app_lifecycle

`static`

```cpp
h1os_lifecycle_t s_app_lifecycle = {0}
```

Type: [`h1os_lifecycle_t`](#h1os_lifecycle_t)

Defined in h1os_lifecycle.c:40

---

{#s_session_expiry_us}

### s_session_expiry_us

`static`

```cpp
int64_t s_session_expiry_us = 0
```

Defined in h1os_lifecycle.c:41

---

{#s_session_task_handle}

### s_session_task_handle

`static`

```cpp
TaskHandle_t s_session_task_handle = NULL
```

Defined in h1os_lifecycle.c:42

---

{#s_session_running}

### s_session_running

`static`

```cpp
bool s_session_running = false
```

Defined in h1os_lifecycle.c:43

---

{#tag-15}

### TAG

`static`

```cpp
const char * TAG = "orch_display_sync"
```

Defined in orch_display_sync.c:20

---

{#s_frame_dirty}

### s_frame_dirty

`static`

```cpp
bool s_frame_dirty = false
```

Defined in orch_display_sync.c:22

{#audio_cmd_t}

## audio_cmd_t

```cpp
struct audio_cmd_t
```

Defined in sub_audio.c:52

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| [`audio_cmd_type_t`](#audio_cmd_type_t) | [`type`](#type)  |  |
| `union audio_cmd_t::@075142260334247171354103021266123360172342241057` | [`params`](#params)  |  |
| `SemaphoreHandle_t` | [`done_sem`](#done_sem)  |  |
| `esp_err_t *` | [`result`](#result)  |  |

---

{#type}

#### type

```cpp
audio_cmd_type_t type
```

Type: [`audio_cmd_type_t`](#audio_cmd_type_t)

Defined in sub_audio.c:53

---

{#params}

#### params

```cpp
union audio_cmd_t::@075142260334247171354103021266123360172342241057 params
```

Defined in sub_audio.c:67

---

{#done_sem}

#### done_sem

```cpp
SemaphoreHandle_t done_sem
```

Defined in sub_audio.c:68

---

{#result}

#### result

```cpp
esp_err_t * result
```

Defined in sub_audio.c:69

{#unionparams}

## [union].params

```cpp
union [union].params
```

Defined in sub_audio.c:54

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `struct audio_cmd_t::@075142260334247171354103021266123360172342241057::@342051060234134064244373243122027377274070330105` | [`tone`](#tone)  |  |
| `struct audio_cmd_t::@075142260334247171354103021266123360172342241057::@035007020164214261121213220013133270155350134061` | [`chime`](#chime)  |  |
| `struct audio_cmd_t::@075142260334247171354103021266123360172342241057::@174042257255263212372236347353345125072343133315` | [`pcm`](#pcm)  |  |

---

{#tone}

#### tone

```cpp
struct audio_cmd_t::@075142260334247171354103021266123360172342241057::@342051060234134064244373243122027377274070330105 tone
```

Defined in sub_audio.c:58

---

{#chime}

#### chime

```cpp
struct audio_cmd_t::@075142260334247171354103021266123360172342241057::@035007020164214261121213220013133270155350134061 chime
```

Defined in sub_audio.c:61

---

{#pcm}

#### pcm

```cpp
struct audio_cmd_t::@075142260334247171354103021266123360172342241057::@174042257255263212372236347353345125072343133315 pcm
```

Defined in sub_audio.c:66

{#structparamstone}

## [struct].params.tone

```cpp
struct [struct].params.tone
```

Defined in sub_audio.c:55

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint32_t` | [`frequency_hz`](#frequency_hz)  |  |
| `uint32_t` | [`duration_ms`](#duration_ms)  |  |

---

{#frequency_hz}

#### frequency_hz

```cpp
uint32_t frequency_hz
```

Defined in sub_audio.c:56

---

{#duration_ms}

#### duration_ms

```cpp
uint32_t duration_ms
```

Defined in sub_audio.c:57

{#structparamschime}

## [struct].params.chime

```cpp
struct [struct].params.chime
```

Defined in sub_audio.c:59

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint8_t` | [`chime_type`](#chime_type)  |  |

---

{#chime_type}

#### chime_type

```cpp
uint8_t chime_type
```

Defined in sub_audio.c:60

{#structparamspcm}

## [struct].params.pcm

```cpp
struct [struct].params.pcm
```

Defined in sub_audio.c:62

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `const int16_t *` | [`samples`](#samples)  |  |
| `size_t` | [`sample_count`](#sample_count)  |  |
| `uint32_t` | [`sample_rate_hz`](#sample_rate_hz)  |  |

---

{#samples}

#### samples

```cpp
const int16_t * samples
```

Defined in sub_audio.c:63

---

{#sample_count}

#### sample_count

```cpp
size_t sample_count
```

Defined in sub_audio.c:64

---

{#sample_rate_hz}

#### sample_rate_hz

```cpp
uint32_t sample_rate_hz
```

Defined in sub_audio.c:65

{#h1os_lifecycle_t}

## h1os_lifecycle_t

```cpp
#include <h1os/h1os.h>
```

```cpp
struct h1os_lifecycle_t
```

Defined in h1os/h1os.h:79

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| [`h1os_boot_cb_t`](#h1os_boot_cb_t) | [`on_boot`](#on_boot)  | System boot / power-on reset hook. |
| [`h1os_wake_cb_t`](#h1os_wake_cb_t) | [`on_wake`](#on_wake)  | Interactive wake hook (Timer / RTC Alarm / Button Tap). |
| [`h1os_pre_sleep_cb_t`](#h1os_pre_sleep_cb_t) | [`on_pre_sleep`](#on_pre_sleep)  | Hook executed immediately prior to entering deep sleep. |
| [`h1os_shutdown_cb_t`](#h1os_shutdown_cb_t) | [`on_shutdown`](#on_shutdown)  | Hook executed immediately prior to battery cut. |
| `struct h1os_lifecycle_t::@325134365353002276205315372127306003103261015120` | [`presentation`](#presentation)  |  |
| `struct h1os_lifecycle_t::@146034141124024227100041106135372254367321170003` | [`session`](#session)  |  |
| `void *` | [`user_data`](#user_data)  |  |

---

{#on_boot}

#### on_boot

```cpp
h1os_boot_cb_t on_boot
```

Type: [`h1os_boot_cb_t`](#h1os_boot_cb_t)

Defined in h1os/h1os.h:81

System boot / power-on reset hook.

---

{#on_wake}

#### on_wake

```cpp
h1os_wake_cb_t on_wake
```

Type: [`h1os_wake_cb_t`](#h1os_wake_cb_t)

Defined in h1os/h1os.h:82

Interactive wake hook (Timer / RTC Alarm / Button Tap).

---

{#on_pre_sleep}

#### on_pre_sleep

```cpp
h1os_pre_sleep_cb_t on_pre_sleep
```

Type: [`h1os_pre_sleep_cb_t`](#h1os_pre_sleep_cb_t)

Defined in h1os/h1os.h:83

Hook executed immediately prior to entering deep sleep.

---

{#on_shutdown}

#### on_shutdown

```cpp
h1os_shutdown_cb_t on_shutdown
```

Type: [`h1os_shutdown_cb_t`](#h1os_shutdown_cb_t)

Defined in h1os/h1os.h:84

Hook executed immediately prior to battery cut.

---

{#presentation}

#### presentation

```cpp
struct h1os_lifecycle_t::@325134365353002276205315372127306003103261015120 presentation
```

Defined in h1os/h1os.h:92

---

{#session}

#### session

```cpp
struct h1os_lifecycle_t::@146034141124024227100041106135372254367321170003 session
```

Defined in h1os/h1os.h:100

---

{#user_data}

#### user_data

```cpp
void * user_data
```

Defined in h1os/h1os.h:102

{#structpresentation}

## [struct].presentation

```cpp
struct [struct].presentation
```

Defined in h1os/h1os.h:87

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| [`h1os_splash_cb_t`](#h1os_splash_cb_t) | [`on_splash`](#on_splash)  | Custom splash rendering callback. |
| [`h1os_chime_cb_t`](#h1os_chime_cb_t) | [`on_chime`](#on_chime)  | Custom chime callback. |
| `uint8_t` | [`chime_mask`](#chime_mask)  | Hardware synthesized chime bitmask. |
| `uint8_t` | [`volume_pct`](#volume_pct)  | Initial audio output volume (0 - 100%, default 60% if 0). |

---

{#on_splash}

#### on_splash

```cpp
h1os_splash_cb_t on_splash
```

Type: [`h1os_splash_cb_t`](#h1os_splash_cb_t)

Defined in h1os/h1os.h:88

Custom splash rendering callback.

---

{#on_chime}

#### on_chime

```cpp
h1os_chime_cb_t on_chime
```

Type: [`h1os_chime_cb_t`](#h1os_chime_cb_t)

Defined in h1os/h1os.h:89

Custom chime callback.

---

{#chime_mask}

#### chime_mask

```cpp
uint8_t chime_mask
```

Defined in h1os/h1os.h:90

Hardware synthesized chime bitmask.

---

{#volume_pct}

#### volume_pct

```cpp
uint8_t volume_pct
```

Defined in h1os/h1os.h:91

Initial audio output volume (0 - 100%, default 60% if 0).

{#structsession}

## [struct].session

```cpp
struct [struct].session
```

Defined in h1os/h1os.h:95

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint32_t` | [`inactivity_timeout_sec`](#inactivity_timeout_sec)  | Inactivity sleep timer (default: 30s). |
| `bool` | [`enable_dfs_80mhz`](#enable_dfs_80mhz)  | Enable 80 MHz power droop while waiting for input (default: true). |
| `uint32_t` | [`flow_a_period_sec`](#flow_a_period_sec)  | Flow A headless sensor sample burst interval (default: 60s). |
| `uint32_t` | [`flow_b_period_sec`](#flow_b_period_sec)  | Flow B main application wake interval (default: 120s). |

---

{#inactivity_timeout_sec}

#### inactivity_timeout_sec

```cpp
uint32_t inactivity_timeout_sec
```

Defined in h1os/h1os.h:96

Inactivity sleep timer (default: 30s).

---

{#enable_dfs_80mhz}

#### enable_dfs_80mhz

```cpp
bool enable_dfs_80mhz
```

Defined in h1os/h1os.h:97

Enable 80 MHz power droop while waiting for input (default: true).

---

{#flow_a_period_sec}

#### flow_a_period_sec

```cpp
uint32_t flow_a_period_sec
```

Defined in h1os/h1os.h:98

Flow A headless sensor sample burst interval (default: 60s).

---

{#flow_b_period_sec}

#### flow_b_period_sec

```cpp
uint32_t flow_b_period_sec
```

Defined in h1os/h1os.h:99

Flow B main application wake interval (default: 120s).

{#h1os_telemetry_t}

## h1os_telemetry_t

```cpp
#include <h1os/h1os.h>
```

```cpp
struct h1os_telemetry_t
```

Defined in h1os/h1os.h:108

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `float` | [`ambient_temp_c`](#ambient_temp_c)  |  |
| `float` | [`ambient_temp_f`](#ambient_temp_f)  |  |
| `float` | [`ambient_rh_pct`](#ambient_rh_pct)  |  |
| `float` | [`dew_point_c`](#dew_point_c)  |  |
| `float` | [`dew_point_f`](#dew_point_f)  |  |
| `float` | [`absolute_humidity_g`](#absolute_humidity_g)  |  |
| `float` | [`window_low_c`](#window_low_c)  | Valid Window Floor (min over valid 32-sample window). |
| `float` | [`window_high_c`](#window_high_c)  | Valid Window Ceiling (max over valid 32-sample window). |
| `float` | [`window_avg_shtc3_c`](#window_avg_shtc3_c)  | Short-term valid SHTC3 window average. |
| `float` | [`window_avg_die_c`](#window_avg_die_c)  | Short-term valid MCU Die window average. |
| `float` | [`temp_historical_c`](#temp_historical_c)  | Long-term light EWMA temperature history. |
| `float` | [`rh_historical_pct`](#rh_historical_pct)  | Long-term light EWMA relative humidity history. |
| `float` | [`raw_shtc3_temp_c`](#raw_shtc3_temp_c)  |  |
| `float` | [`mcu_die_temp_c`](#mcu_die_temp_c)  |  |
| `float` | [`epd_glass_temp_c`](#epd_glass_temp_c)  |  |
| `float` | [`trinode_temp_c`](#trinode_temp_c)  | (T_valid + T_die + T_glass) / 3.0 |
| `float` | [`trinode_delta_c`](#trinode_delta_c)  | T_valid - T_trinode. |
| `uint8_t` | [`trinode_confidence_pct`](#trinode_confidence_pct)  | 0-100% linear confidence score |
| `bool` | [`is_thermally_settled`](#is_thermally_settled)  |  |
| `uint16_t` | [`valid_trend`](#valid_trend)  | Consecutive thermally settled Flow A samples. |
| `uint32_t` | [`sample_count`](#sample_count-1)  |  |
| `uint16_t` | [`battery_mv`](#battery_mv)  |  |
| `uint8_t` | [`battery_percent`](#battery_percent)  |  |
| `bool` | [`is_usb_powered`](#is_usb_powered)  |  |

---

{#ambient_temp_c}

#### ambient_temp_c

```cpp
float ambient_temp_c
```

Defined in h1os/h1os.h:110

---

{#ambient_temp_f}

#### ambient_temp_f

```cpp
float ambient_temp_f
```

Defined in h1os/h1os.h:111

---

{#ambient_rh_pct}

#### ambient_rh_pct

```cpp
float ambient_rh_pct
```

Defined in h1os/h1os.h:112

---

{#dew_point_c}

#### dew_point_c

```cpp
float dew_point_c
```

Defined in h1os/h1os.h:113

---

{#dew_point_f}

#### dew_point_f

```cpp
float dew_point_f
```

Defined in h1os/h1os.h:114

---

{#absolute_humidity_g}

#### absolute_humidity_g

```cpp
float absolute_humidity_g
```

Defined in h1os/h1os.h:115

---

{#window_low_c}

#### window_low_c

```cpp
float window_low_c
```

Defined in h1os/h1os.h:118

Valid Window Floor (min over valid 32-sample window).

---

{#window_high_c}

#### window_high_c

```cpp
float window_high_c
```

Defined in h1os/h1os.h:119

Valid Window Ceiling (max over valid 32-sample window).

---

{#window_avg_shtc3_c}

#### window_avg_shtc3_c

```cpp
float window_avg_shtc3_c
```

Defined in h1os/h1os.h:120

Short-term valid SHTC3 window average.

---

{#window_avg_die_c}

#### window_avg_die_c

```cpp
float window_avg_die_c
```

Defined in h1os/h1os.h:121

Short-term valid MCU Die window average.

---

{#temp_historical_c}

#### temp_historical_c

```cpp
float temp_historical_c
```

Defined in h1os/h1os.h:122

Long-term light EWMA temperature history.

---

{#rh_historical_pct}

#### rh_historical_pct

```cpp
float rh_historical_pct
```

Defined in h1os/h1os.h:123

Long-term light EWMA relative humidity history.

---

{#raw_shtc3_temp_c}

#### raw_shtc3_temp_c

```cpp
float raw_shtc3_temp_c
```

Defined in h1os/h1os.h:126

---

{#mcu_die_temp_c}

#### mcu_die_temp_c

```cpp
float mcu_die_temp_c
```

Defined in h1os/h1os.h:127

---

{#epd_glass_temp_c}

#### epd_glass_temp_c

```cpp
float epd_glass_temp_c
```

Defined in h1os/h1os.h:128

---

{#trinode_temp_c}

#### trinode_temp_c

```cpp
float trinode_temp_c
```

Defined in h1os/h1os.h:129

(T_valid + T_die + T_glass) / 3.0

---

{#trinode_delta_c}

#### trinode_delta_c

```cpp
float trinode_delta_c
```

Defined in h1os/h1os.h:130

T_valid - T_trinode.

---

{#trinode_confidence_pct}

#### trinode_confidence_pct

```cpp
uint8_t trinode_confidence_pct
```

Defined in h1os/h1os.h:131

0-100% linear confidence score

---

{#is_thermally_settled}

#### is_thermally_settled

```cpp
bool is_thermally_settled
```

Defined in h1os/h1os.h:134

---

{#valid_trend}

#### valid_trend

```cpp
uint16_t valid_trend
```

Defined in h1os/h1os.h:135

Consecutive thermally settled Flow A samples.

---

{#sample_count-1}

#### sample_count

```cpp
uint32_t sample_count
```

Defined in h1os/h1os.h:136

---

{#battery_mv}

#### battery_mv

```cpp
uint16_t battery_mv
```

Defined in h1os/h1os.h:137

---

{#battery_percent}

#### battery_percent

```cpp
uint8_t battery_percent
```

Defined in h1os/h1os.h:138

---

{#is_usb_powered}

#### is_usb_powered

```cpp
bool is_usb_powered
```

Defined in h1os/h1os.h:139

{#h1os_wake_context_t}

## h1os_wake_context_t

```cpp
#include <h1os/h1os.h>
```

```cpp
struct h1os_wake_context_t
```

Defined in h1os/h1os.h:44

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `esp_reset_reason_t` | [`reset_reason`](#reset_reason)  |  |
| `uint32_t` | [`wakeup_causes`](#wakeup_causes)  | Bitmap of wakeup sources (esp_sleep_get_wakeup_causes). |
| `uint32_t` | [`boot_count`](#boot_count)  |  |
| `uint32_t` | [`deep_sleep_count`](#deep_sleep_count)  |  |
| `bool` | [`woke_from_button`](#woke_from_button)  |  |
| `uint8_t` | [`wake_button`](#wake_button)  |  |
| `uint32_t` | [`sleep_duration_sec`](#sleep_duration_sec)  |  |
| `void *` | [`user_data`](#user_data-1)  |  |

---

{#reset_reason}

#### reset_reason

```cpp
esp_reset_reason_t reset_reason
```

Defined in h1os/h1os.h:45

---

{#wakeup_causes}

#### wakeup_causes

```cpp
uint32_t wakeup_causes
```

Defined in h1os/h1os.h:46

Bitmap of wakeup sources (esp_sleep_get_wakeup_causes).

---

{#boot_count}

#### boot_count

```cpp
uint32_t boot_count
```

Defined in h1os/h1os.h:47

---

{#deep_sleep_count}

#### deep_sleep_count

```cpp
uint32_t deep_sleep_count
```

Defined in h1os/h1os.h:48

---

{#woke_from_button}

#### woke_from_button

```cpp
bool woke_from_button
```

Defined in h1os/h1os.h:49

---

{#wake_button}

#### wake_button

```cpp
uint8_t wake_button
```

Defined in h1os/h1os.h:50

---

{#sleep_duration_sec}

#### sleep_duration_sec

```cpp
uint32_t sleep_duration_sec
```

Defined in h1os/h1os.h:51

---

{#user_data-1}

#### user_data

```cpp
void * user_data
```

Defined in h1os/h1os.h:52

{#orch_persisted_state_t}

## orch_persisted_state_t

```cpp
#include <h1os/orch_state.h>
```

```cpp
struct orch_persisted_state_t
```

Defined in h1os/orch_state.h:47

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint32_t` | [`magic`](#magic)  |  |
| `uint32_t` | [`boot_count`](#boot_count-1)  |  |
| `uint32_t` | [`wake_count`](#wake_count)  |  |
| `uint8_t` | [`flags`](#flags)  |  |
| `uint8_t` | [`ulp_dispatch_reason`](#ulp_dispatch_reason)  |  |
| `uint16_t` | [`last_vbat_mv`](#last_vbat_mv)  |  |
| `uint32_t` | [`sample_interval_sec`](#sample_interval_sec)  |  |
| `uint32_t` | [`flow_b_period_sec`](#flow_b_period_sec-1)  |  |
| `uint32_t` | [`wake_timestamp_epoch`](#wake_timestamp_epoch)  |  |
| `uint32_t` | [`ulp_vbat_scale`](#ulp_vbat_scale)  |  |
| `int32_t` | [`ulp_vbat_offset_mv`](#ulp_vbat_offset_mv)  |  |
| `uint16_t` | [`epd_partial_refresh_count`](#epd_partial_refresh_count)  |  |
| `uint16_t` | [`valid_trend`](#valid_trend-1)  |  |
| `int16_t` | [`amb_floor_temp_centi_c`](#amb_floor_temp_centi_c)  |  |
| `int16_t` | [`window_low_temp_centi_c`](#window_low_temp_centi_c)  |  |
| `int16_t` | [`window_high_temp_centi_c`](#window_high_temp_centi_c)  |  |
| `int16_t` | [`last_glass_temp_centi_c`](#last_glass_temp_centi_c)  |  |
| `float` | [`window_avg_shtc3_c`](#window_avg_shtc3_c-1)  |  |
| `float` | [`window_avg_die_c`](#window_avg_die_c-1)  |  |
| `float` | [`temp_historical_c`](#temp_historical_c-1)  |  |
| `float` | [`rh_historical_pct`](#rh_historical_pct-1)  |  |
| `float` | [`reconstructed_amb_temp_c`](#reconstructed_amb_temp_c)  |  |
| `float` | [`reconstructed_amb_rh_pct`](#reconstructed_amb_rh_pct)  |  |
| `float` | [`reconstructed_dew_point_c`](#reconstructed_dew_point_c)  |  |
| `float` | [`vapor_pressure_hpa`](#vapor_pressure_hpa)  |  |
| `float` | [`trinode_temp_c`](#trinode_temp_c-1)  |  |
| `float` | [`trinode_delta_c`](#trinode_delta_c-1)  |  |
| `uint8_t` | [`trinode_confidence_pct`](#trinode_confidence_pct-1)  |  |
| `bool` | [`ewma_inited`](#ewma_inited)  |  |
| `int16_t` | [`tsens_cal_centi_c`](#tsens_cal_centi_c)  |  |
| `uint8_t` | [`app_stage`](#app_stage)  |  |
| `uint8_t` | [`scratchpad_len`](#scratchpad_len)  |  |
| `uint8_t` | [`scratchpad`](#scratchpad)  |  |
| [`orch_tri_node_sample_t`](#orch_tri_node_sample_t) | [`ring`](#ring)  |  |
| `uint8_t` | [`ring_head`](#ring_head)  |  |
| `uint32_t` | [`total_samples`](#total_samples)  |  |

---

{#magic}

#### magic

```cpp
uint32_t magic
```

Defined in h1os/orch_state.h:48

---

{#boot_count-1}

#### boot_count

```cpp
uint32_t boot_count
```

Defined in h1os/orch_state.h:49

---

{#wake_count}

#### wake_count

```cpp
uint32_t wake_count
```

Defined in h1os/orch_state.h:50

---

{#flags}

#### flags

```cpp
uint8_t flags
```

Defined in h1os/orch_state.h:51

---

{#ulp_dispatch_reason}

#### ulp_dispatch_reason

```cpp
uint8_t ulp_dispatch_reason
```

Defined in h1os/orch_state.h:52

---

{#last_vbat_mv}

#### last_vbat_mv

```cpp
uint16_t last_vbat_mv
```

Defined in h1os/orch_state.h:53

---

{#sample_interval_sec}

#### sample_interval_sec

```cpp
uint32_t sample_interval_sec
```

Defined in h1os/orch_state.h:55

---

{#flow_b_period_sec-1}

#### flow_b_period_sec

```cpp
uint32_t flow_b_period_sec
```

Defined in h1os/orch_state.h:56

---

{#wake_timestamp_epoch}

#### wake_timestamp_epoch

```cpp
uint32_t wake_timestamp_epoch
```

Defined in h1os/orch_state.h:57

---

{#ulp_vbat_scale}

#### ulp_vbat_scale

```cpp
uint32_t ulp_vbat_scale
```

Defined in h1os/orch_state.h:60

---

{#ulp_vbat_offset_mv}

#### ulp_vbat_offset_mv

```cpp
int32_t ulp_vbat_offset_mv
```

Defined in h1os/orch_state.h:61

---

{#epd_partial_refresh_count}

#### epd_partial_refresh_count

```cpp
uint16_t epd_partial_refresh_count
```

Defined in h1os/orch_state.h:64

---

{#valid_trend-1}

#### valid_trend

```cpp
uint16_t valid_trend
```

Defined in h1os/orch_state.h:65

---

{#amb_floor_temp_centi_c}

#### amb_floor_temp_centi_c

```cpp
int16_t amb_floor_temp_centi_c
```

Defined in h1os/orch_state.h:68

---

{#window_low_temp_centi_c}

#### window_low_temp_centi_c

```cpp
int16_t window_low_temp_centi_c
```

Defined in h1os/orch_state.h:69

---

{#window_high_temp_centi_c}

#### window_high_temp_centi_c

```cpp
int16_t window_high_temp_centi_c
```

Defined in h1os/orch_state.h:70

---

{#last_glass_temp_centi_c}

#### last_glass_temp_centi_c

```cpp
int16_t last_glass_temp_centi_c
```

Defined in h1os/orch_state.h:71

---

{#window_avg_shtc3_c-1}

#### window_avg_shtc3_c

```cpp
float window_avg_shtc3_c
```

Defined in h1os/orch_state.h:74

---

{#window_avg_die_c-1}

#### window_avg_die_c

```cpp
float window_avg_die_c
```

Defined in h1os/orch_state.h:75

---

{#temp_historical_c-1}

#### temp_historical_c

```cpp
float temp_historical_c
```

Defined in h1os/orch_state.h:76

---

{#rh_historical_pct-1}

#### rh_historical_pct

```cpp
float rh_historical_pct
```

Defined in h1os/orch_state.h:77

---

{#reconstructed_amb_temp_c}

#### reconstructed_amb_temp_c

```cpp
float reconstructed_amb_temp_c
```

Defined in h1os/orch_state.h:80

---

{#reconstructed_amb_rh_pct}

#### reconstructed_amb_rh_pct

```cpp
float reconstructed_amb_rh_pct
```

Defined in h1os/orch_state.h:81

---

{#reconstructed_dew_point_c}

#### reconstructed_dew_point_c

```cpp
float reconstructed_dew_point_c
```

Defined in h1os/orch_state.h:82

---

{#vapor_pressure_hpa}

#### vapor_pressure_hpa

```cpp
float vapor_pressure_hpa
```

Defined in h1os/orch_state.h:83

---

{#trinode_temp_c-1}

#### trinode_temp_c

```cpp
float trinode_temp_c
```

Defined in h1os/orch_state.h:86

---

{#trinode_delta_c-1}

#### trinode_delta_c

```cpp
float trinode_delta_c
```

Defined in h1os/orch_state.h:87

---

{#trinode_confidence_pct-1}

#### trinode_confidence_pct

```cpp
uint8_t trinode_confidence_pct
```

Defined in h1os/orch_state.h:88

---

{#ewma_inited}

#### ewma_inited

```cpp
bool ewma_inited
```

Defined in h1os/orch_state.h:89

---

{#tsens_cal_centi_c}

#### tsens_cal_centi_c

```cpp
int16_t tsens_cal_centi_c
```

Defined in h1os/orch_state.h:90

---

{#app_stage}

#### app_stage

```cpp
uint8_t app_stage
```

Defined in h1os/orch_state.h:93

---

{#scratchpad_len}

#### scratchpad_len

```cpp
uint8_t scratchpad_len
```

Defined in h1os/orch_state.h:94

---

{#scratchpad}

#### scratchpad

```cpp
uint8_t scratchpad[32]
```

Defined in h1os/orch_state.h:95

---

{#ring}

#### ring

```cpp
orch_tri_node_sample_t ring[32]
```

Defined in h1os/orch_state.h:98

---

{#ring_head}

#### ring_head

```cpp
uint8_t ring_head
```

Defined in h1os/orch_state.h:100

---

{#total_samples}

#### total_samples

```cpp
uint32_t total_samples
```

Defined in h1os/orch_state.h:101

{#orch_tri_node_sample_t}

## orch_tri_node_sample_t

```cpp
#include <h1os/orch_state.h>
```

```cpp
struct orch_tri_node_sample_t
```

Defined in h1os/orch_state.h:37

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `int16_t` | [`shtc3_temp_centi_c`](#shtc3_temp_centi_c)  |  |
| `uint16_t` | [`shtc3_rh_centi_pct`](#shtc3_rh_centi_pct)  |  |
| `int16_t` | [`mcu_tsens_centi_c`](#mcu_tsens_centi_c)  |  |
| `int16_t` | [`epd_glass_centi_c`](#epd_glass_centi_c)  |  |
| `uint32_t` | [`timestamp_sec`](#timestamp_sec)  |  |
| `uint8_t` | [`quality_flags`](#quality_flags)  |  |
| `uint8_t` | [`_pad`](#_pad)  |  |

---

{#shtc3_temp_centi_c}

#### shtc3_temp_centi_c

```cpp
int16_t shtc3_temp_centi_c
```

Defined in h1os/orch_state.h:38

---

{#shtc3_rh_centi_pct}

#### shtc3_rh_centi_pct

```cpp
uint16_t shtc3_rh_centi_pct
```

Defined in h1os/orch_state.h:39

---

{#mcu_tsens_centi_c}

#### mcu_tsens_centi_c

```cpp
int16_t mcu_tsens_centi_c
```

Defined in h1os/orch_state.h:40

---

{#epd_glass_centi_c}

#### epd_glass_centi_c

```cpp
int16_t epd_glass_centi_c
```

Defined in h1os/orch_state.h:41

---

{#timestamp_sec}

#### timestamp_sec

```cpp
uint32_t timestamp_sec
```

Defined in h1os/orch_state.h:42

---

{#quality_flags}

#### quality_flags

```cpp
uint8_t quality_flags
```

Defined in h1os/orch_state.h:43

---

{#_pad}

#### _pad

```cpp
uint8_t _pad[3]
```

Defined in h1os/orch_state.h:44

{#structs_lipo_table}

## [struct].s_lipo_table

```cpp
struct [struct].s_lipo_table
```

Defined in sub_power.c:28

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint16_t` | [`mv`](#mv)  |  |
| `uint8_t` | [`pct`](#pct)  |  |

---

{#mv}

#### mv

```cpp
uint16_t mv
```

Defined in sub_power.c:29

---

{#pct}

#### pct

```cpp
uint8_t pct
```

Defined in sub_power.c:30

{#structparamspcm}

## [struct].params.pcm

```cpp
struct [struct].params.pcm
```

Defined in sub_audio.c:62

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `const int16_t *` | [`samples`](#samples)  |  |
| `size_t` | [`sample_count`](#sample_count)  |  |
| `uint32_t` | [`sample_rate_hz`](#sample_rate_hz)  |  |

---

{#samples}

#### samples

```cpp
const int16_t * samples
```

Defined in sub_audio.c:63

---

{#sample_count}

#### sample_count

```cpp
size_t sample_count
```

Defined in sub_audio.c:64

---

{#sample_rate_hz}

#### sample_rate_hz

```cpp
uint32_t sample_rate_hz
```

Defined in sub_audio.c:65

{#structparamstone}

## [struct].params.tone

```cpp
struct [struct].params.tone
```

Defined in sub_audio.c:55

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint32_t` | [`frequency_hz`](#frequency_hz)  |  |
| `uint32_t` | [`duration_ms`](#duration_ms)  |  |

---

{#frequency_hz}

#### frequency_hz

```cpp
uint32_t frequency_hz
```

Defined in sub_audio.c:56

---

{#duration_ms}

#### duration_ms

```cpp
uint32_t duration_ms
```

Defined in sub_audio.c:57

{#structsession}

## [struct].session

```cpp
struct [struct].session
```

Defined in h1os/h1os.h:95

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint32_t` | [`inactivity_timeout_sec`](#inactivity_timeout_sec)  | Inactivity sleep timer (default: 30s). |
| `bool` | [`enable_dfs_80mhz`](#enable_dfs_80mhz)  | Enable 80 MHz power droop while waiting for input (default: true). |
| `uint32_t` | [`flow_a_period_sec`](#flow_a_period_sec)  | Flow A headless sensor sample burst interval (default: 60s). |
| `uint32_t` | [`flow_b_period_sec`](#flow_b_period_sec)  | Flow B main application wake interval (default: 120s). |

---

{#inactivity_timeout_sec}

#### inactivity_timeout_sec

```cpp
uint32_t inactivity_timeout_sec
```

Defined in h1os/h1os.h:96

Inactivity sleep timer (default: 30s).

---

{#enable_dfs_80mhz}

#### enable_dfs_80mhz

```cpp
bool enable_dfs_80mhz
```

Defined in h1os/h1os.h:97

Enable 80 MHz power droop while waiting for input (default: true).

---

{#flow_a_period_sec}

#### flow_a_period_sec

```cpp
uint32_t flow_a_period_sec
```

Defined in h1os/h1os.h:98

Flow A headless sensor sample burst interval (default: 60s).

---

{#flow_b_period_sec}

#### flow_b_period_sec

```cpp
uint32_t flow_b_period_sec
```

Defined in h1os/h1os.h:99

Flow B main application wake interval (default: 120s).

{#structparamschime}

## [struct].params.chime

```cpp
struct [struct].params.chime
```

Defined in sub_audio.c:59

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint8_t` | [`chime_type`](#chime_type)  |  |

---

{#chime_type}

#### chime_type

```cpp
uint8_t chime_type
```

Defined in sub_audio.c:60

{#structpresentation}

## [struct].presentation

```cpp
struct [struct].presentation
```

Defined in h1os/h1os.h:87

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| [`h1os_splash_cb_t`](#h1os_splash_cb_t) | [`on_splash`](#on_splash)  | Custom splash rendering callback. |
| [`h1os_chime_cb_t`](#h1os_chime_cb_t) | [`on_chime`](#on_chime)  | Custom chime callback. |
| `uint8_t` | [`chime_mask`](#chime_mask)  | Hardware synthesized chime bitmask. |
| `uint8_t` | [`volume_pct`](#volume_pct)  | Initial audio output volume (0 - 100%, default 60% if 0). |

---

{#on_splash}

#### on_splash

```cpp
h1os_splash_cb_t on_splash
```

Type: [`h1os_splash_cb_t`](#h1os_splash_cb_t)

Defined in h1os/h1os.h:88

Custom splash rendering callback.

---

{#on_chime}

#### on_chime

```cpp
h1os_chime_cb_t on_chime
```

Type: [`h1os_chime_cb_t`](#h1os_chime_cb_t)

Defined in h1os/h1os.h:89

Custom chime callback.

---

{#chime_mask}

#### chime_mask

```cpp
uint8_t chime_mask
```

Defined in h1os/h1os.h:90

Hardware synthesized chime bitmask.

---

{#volume_pct}

#### volume_pct

```cpp
uint8_t volume_pct
```

Defined in h1os/h1os.h:91

Initial audio output volume (0 - 100%, default 60% if 0).

{#unionparams}

## [union].params

```cpp
union [union].params
```

Defined in sub_audio.c:54

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `struct audio_cmd_t::@075142260334247171354103021266123360172342241057::@342051060234134064244373243122027377274070330105` | [`tone`](#tone)  |  |
| `struct audio_cmd_t::@075142260334247171354103021266123360172342241057::@035007020164214261121213220013133270155350134061` | [`chime`](#chime)  |  |
| `struct audio_cmd_t::@075142260334247171354103021266123360172342241057::@174042257255263212372236347353345125072343133315` | [`pcm`](#pcm)  |  |

---

{#tone}

#### tone

```cpp
struct audio_cmd_t::@075142260334247171354103021266123360172342241057::@342051060234134064244373243122027377274070330105 tone
```

Defined in sub_audio.c:58

---

{#chime}

#### chime

```cpp
struct audio_cmd_t::@075142260334247171354103021266123360172342241057::@035007020164214261121213220013133270155350134061 chime
```

Defined in sub_audio.c:61

---

{#pcm}

#### pcm

```cpp
struct audio_cmd_t::@075142260334247171354103021266123360172342241057::@174042257255263212372236347353345125072343133315 pcm
```

Defined in sub_audio.c:66

{#structparamstone}

## [struct].params.tone

```cpp
struct [struct].params.tone
```

Defined in sub_audio.c:55

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint32_t` | [`frequency_hz`](#frequency_hz)  |  |
| `uint32_t` | [`duration_ms`](#duration_ms)  |  |

---

{#frequency_hz}

#### frequency_hz

```cpp
uint32_t frequency_hz
```

Defined in sub_audio.c:56

---

{#duration_ms}

#### duration_ms

```cpp
uint32_t duration_ms
```

Defined in sub_audio.c:57

{#structparamschime}

## [struct].params.chime

```cpp
struct [struct].params.chime
```

Defined in sub_audio.c:59

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint8_t` | [`chime_type`](#chime_type)  |  |

---

{#chime_type}

#### chime_type

```cpp
uint8_t chime_type
```

Defined in sub_audio.c:60

{#structparamspcm}

## [struct].params.pcm

```cpp
struct [struct].params.pcm
```

Defined in sub_audio.c:62

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `const int16_t *` | [`samples`](#samples)  |  |
| `size_t` | [`sample_count`](#sample_count)  |  |
| `uint32_t` | [`sample_rate_hz`](#sample_rate_hz)  |  |

---

{#samples}

#### samples

```cpp
const int16_t * samples
```

Defined in sub_audio.c:63

---

{#sample_count}

#### sample_count

```cpp
size_t sample_count
```

Defined in sub_audio.c:64

---

{#sample_rate_hz}

#### sample_rate_hz

```cpp
uint32_t sample_rate_hz
```

Defined in sub_audio.c:65

Generated by [Moxygen](https://0state.com/moxygen)