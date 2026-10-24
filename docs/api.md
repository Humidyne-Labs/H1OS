# API Reference

## Classes

| Name | Description |
|------|-------------|
| [`audio_cmd_t`](#audio_cmd_t) |  |
| [`h1os_lifecycle_t`](#h1os_lifecycle_t) | Declarative application lifecycle configuration structure. |
| [`h1os_telemetry_t`](#h1os_telemetry_t) | Comprehensive environmental telemetry and system metrics snapshot. |
| [`CpuMaxTurboScope`](#cpumaxturboscope) |  |
| [`es8311_reg_entry_t`](#es8311_reg_entry_t) |  |
| [`h1os_wake_context_t`](#h1os_wake_context_t) | Platform wakeup context descriptor. |
| [`orch_persisted_state_t`](#orch_persisted_state_t) | Master persistent state block allocated in RTC Slow SRAM. |
| [`orch_tri_node_sample_t`](#orch_tri_node_sample_t) | Compact 16-byte Tri-Node sample entry in RTC Slow SRAM. |
| [`[struct].s_lipo_table`](#structs_lipo_table) |  |
| [`[struct].params.pcm`](#structparamspcm) |  |
| [`[struct].params.tone`](#structparamstone) |  |
| [`[struct].session`](#structsession) |  |
| [`[struct].params.chime`](#structparamschime) |  |
| [`[struct].presentation`](#structpresentation) |  |

## Macros

---

{#rtc_int_pin}

### RTC_INT_PIN

```cpp
#define RTC_INT_PIN GPIO_NUM_5
```

Defined in main.c:40

---

{#rtc_int_timeout_us}

### RTC_INT_TIMEOUT_US

```cpp
#define RTC_INT_TIMEOUT_US 50000
```

Defined in main.c:41

---

{#rtc_int_poll_us}

### RTC_INT_POLL_US

```cpp
#define RTC_INT_POLL_US 100
```

Defined in main.c:42

---

{#button_debounce_us}

### BUTTON_DEBOUNCE_US

```cpp
#define BUTTON_DEBOUNCE_US 30000
```

Defined in main.c:44

---

{#button_hold_us}

### BUTTON_HOLD_US

```cpp
#define BUTTON_HOLD_US 2500000
```

Defined in main.c:45

---

{#button_tap_min_ms}

### BUTTON_TAP_MIN_MS

```cpp
#define BUTTON_TAP_MIN_MS 50
```

Defined in main.c:46

---

{#button_tap_max_ms}

### BUTTON_TAP_MAX_MS

```cpp
#define BUTTON_TAP_MAX_MS 800
```

Defined in main.c:47

---

{#button_poll_us}

### BUTTON_POLL_US

```cpp
#define BUTTON_POLL_US 10000
```

Defined in main.c:48

---

{#button_release_timeout_us}

### BUTTON_RELEASE_TIMEOUT_US

```cpp
#define BUTTON_RELEASE_TIMEOUT_US 50000
```

Defined in main.c:49

---

{#pmu_rdy_spin_max}

### PMU_RDY_SPIN_MAX

```cpp
#define PMU_RDY_SPIN_MAX 50000
```

Defined in main.c:51

---

{#adc_conv_spin_max}

### ADC_CONV_SPIN_MAX

```cpp
#define ADC_CONV_SPIN_MAX 10000
```

Defined in main.c:52

---

{#ulp_dispatch_none}

### ULP_DISPATCH_NONE

```cpp
#define ULP_DISPATCH_NONE 0
```

Defined in main.c:54

---

{#ulp_dispatch_sensor_sample}

### ULP_DISPATCH_SENSOR_SAMPLE

```cpp
#define ULP_DISPATCH_SENSOR_SAMPLE 1
```

Defined in main.c:55

---

{#ulp_dispatch_main_wake}

### ULP_DISPATCH_MAIN_WAKE

```cpp
#define ULP_DISPATCH_MAIN_WAKE 2
```

Defined in main.c:56

---

{#ulp_dispatch_critical_shutdown}

### ULP_DISPATCH_CRITICAL_SHUTDOWN

```cpp
#define ULP_DISPATCH_CRITICAL_SHUTDOWN 3
```

Defined in main.c:57

---

{#ulp_dispatch_bootloader_jump}

### ULP_DISPATCH_BOOTLOADER_JUMP

```cpp
#define ULP_DISPATCH_BOOTLOADER_JUMP 4
```

Defined in main.c:58

---

{#ulp_dispatch_power_off}

### ULP_DISPATCH_POWER_OFF

```cpp
#define ULP_DISPATCH_POWER_OFF 5
```

Defined in main.c:59

---

{#hal_ledc_timer}

### HAL_LEDC_TIMER

```cpp
#define HAL_LEDC_TIMER LEDC_TIMER_0
```

Defined in hal_io.c:108

---

{#hal_ledc_mode}

### HAL_LEDC_MODE

```cpp
#define HAL_LEDC_MODE LEDC_LOW_SPEED_MODE
```

Defined in hal_io.c:109

---

{#hal_ledc_channel}

### HAL_LEDC_CHANNEL

```cpp
#define HAL_LEDC_CHANNEL LEDC_CHANNEL_0
```

Defined in hal_io.c:110

---

{#hal_ledc_duty_res}

### HAL_LEDC_DUTY_RES

```cpp
#define HAL_LEDC_DUTY_RES LEDC_TIMER_10_BIT
```

Defined in hal_io.c:111

---

{#hal_ledc_frequency}

### HAL_LEDC_FREQUENCY

```cpp
#define HAL_LEDC_FREQUENCY 5000
```

Defined in hal_io.c:112

---

{#sub_nvs_namespace}

### SUB_NVS_NAMESPACE

```cpp
#define SUB_NVS_NAMESPACE "h1os"
```

Defined in h1os/sub_nvs.h:21

Default NVS partition namespace for H1OS settings.

---

{#rtc_reg_control_1}

### RTC_REG_CONTROL_1

```cpp
#define RTC_REG_CONTROL_1 0x00
```

Defined in sub_rtc.c:21

---

{#rtc_reg_control_2}

### RTC_REG_CONTROL_2

```cpp
#define RTC_REG_CONTROL_2 0x01
```

Defined in sub_rtc.c:22

---

{#rtc_reg_offset}

### RTC_REG_OFFSET

```cpp
#define RTC_REG_OFFSET 0x02
```

Defined in sub_rtc.c:23

---

{#rtc_reg_ram_byte}

### RTC_REG_RAM_BYTE

```cpp
#define RTC_REG_RAM_BYTE 0x03
```

Defined in sub_rtc.c:24

---

{#rtc_reg_seconds}

### RTC_REG_SECONDS

```cpp
#define RTC_REG_SECONDS 0x04
```

Defined in sub_rtc.c:25

---

{#rtc_reg_minutes}

### RTC_REG_MINUTES

```cpp
#define RTC_REG_MINUTES 0x05
```

Defined in sub_rtc.c:26

---

{#rtc_reg_hours}

### RTC_REG_HOURS

```cpp
#define RTC_REG_HOURS 0x06
```

Defined in sub_rtc.c:27

---

{#rtc_reg_days}

### RTC_REG_DAYS

```cpp
#define RTC_REG_DAYS 0x07
```

Defined in sub_rtc.c:28

---

{#rtc_reg_weekdays}

### RTC_REG_WEEKDAYS

```cpp
#define RTC_REG_WEEKDAYS 0x08
```

Defined in sub_rtc.c:29

---

{#rtc_reg_months}

### RTC_REG_MONTHS

```cpp
#define RTC_REG_MONTHS 0x09
```

Defined in sub_rtc.c:30

---

{#rtc_reg_years}

### RTC_REG_YEARS

```cpp
#define RTC_REG_YEARS 0x0A
```

Defined in sub_rtc.c:31

---

{#rtc_reg_alarm_sec}

### RTC_REG_ALARM_SEC

```cpp
#define RTC_REG_ALARM_SEC 0x0B
```

Defined in sub_rtc.c:32

---

{#rtc_reg_timer_value}

### RTC_REG_TIMER_VALUE

```cpp
#define RTC_REG_TIMER_VALUE 0x10
```

Defined in sub_rtc.c:33

---

{#rtc_reg_timer_mode}

### RTC_REG_TIMER_MODE

```cpp
#define RTC_REG_TIMER_MODE 0x11
```

Defined in sub_rtc.c:34

---

{#ctrl1_stop_mask}

### CTRL1_STOP_MASK

```cpp
#define CTRL1_STOP_MASK (1 << 5)
```

Defined in sub_rtc.c:36

---

{#ctrl1_12_24_mask}

### CTRL1_12_24_MASK

```cpp
#define CTRL1_12_24_MASK (1 << 1)
```

Defined in sub_rtc.c:37

---

{#ctrl1_cap_sel_12_5pf}

### CTRL1_CAP_SEL_12_5PF

```cpp
#define CTRL1_CAP_SEL_12_5PF (1 << 0)
```

Defined in sub_rtc.c:38

---

{#ctrl1_sw_reset_cmd}

### CTRL1_SW_RESET_CMD

```cpp
#define CTRL1_SW_RESET_CMD 0x58
```

Defined in sub_rtc.c:39

---

{#ctrl2_af_mask}

### CTRL2_AF_MASK

```cpp
#define CTRL2_AF_MASK (1 << 6)
```

Defined in sub_rtc.c:41

---

{#ctrl2_tf_mask}

### CTRL2_TF_MASK

```cpp
#define CTRL2_TF_MASK (1 << 3)
```

Defined in sub_rtc.c:42

---

{#ctrl2_aie_mask}

### CTRL2_AIE_MASK

```cpp
#define CTRL2_AIE_MASK (1 << 7)
```

Defined in sub_rtc.c:43

---

{#ctrl2_cof_off}

### CTRL2_COF_OFF

```cpp
#define CTRL2_COF_OFF 0x07
```

Defined in sub_rtc.c:44

---

{#timer_clk_4096_hz}

### TIMER_CLK_4096_HZ

```cpp
#define TIMER_CLK_4096_HZ (0 << 3)
```

Defined in sub_rtc.c:46

---

{#timer_clk_64_hz}

### TIMER_CLK_64_HZ

```cpp
#define TIMER_CLK_64_HZ (1 << 3)
```

Defined in sub_rtc.c:47

---

{#timer_clk_1_hz}

### TIMER_CLK_1_HZ

```cpp
#define TIMER_CLK_1_HZ (2 << 3)
```

Defined in sub_rtc.c:48

---

{#timer_clk_1_60_hz}

### TIMER_CLK_1_60_HZ

```cpp
#define TIMER_CLK_1_60_HZ (3 << 3)
```

Defined in sub_rtc.c:49

---

{#timer_enable_bit}

### TIMER_ENABLE_BIT

```cpp
#define TIMER_ENABLE_BIT (1 << 2)
```

Defined in sub_rtc.c:50

---

{#timer_int_enable_bit}

### TIMER_INT_ENABLE_BIT

```cpp
#define TIMER_INT_ENABLE_BIT (1 << 1)
```

Defined in sub_rtc.c:51

---

{#timer_pulse_mode_bit}

### TIMER_PULSE_MODE_BIT

```cpp
#define TIMER_PULSE_MODE_BIT (1 << 0)
```

Defined in sub_rtc.c:52

---

{#hal_pin_power_hold}

### HAL_PIN_POWER_HOLD

```cpp
#define HAL_PIN_POWER_HOLD GPIO_NUM_17
```

Defined in h1os/hal_types.h:24

Master LDO Power Latch (BAT_CTRL): Active HIGH.

---

{#hal_pin_battery_adc}

### HAL_PIN_BATTERY_ADC

```cpp
#define HAL_PIN_BATTERY_ADC GPIO_NUM_4
```

Defined in h1os/hal_types.h:25

Battery Voltage Sensing: ADC1_CHANNEL_3 (1:2 divider).

---

{#hal_pin_status_led}

### HAL_PIN_STATUS_LED

```cpp
#define HAL_PIN_STATUS_LED GPIO_NUM_3
```

Defined in h1os/hal_types.h:26

User LED: Open-Drain, Active LOW (0 = ON, 1 = OFF).

---

{#hal_pin_button_boot}

### HAL_PIN_BUTTON_BOOT

```cpp
#define HAL_PIN_BUTTON_BOOT GPIO_NUM_0
```

Defined in h1os/hal_types.h:29

Hardware BOOT0 Key: Active LOW (external 10k pullup on PCB).

---

{#hal_pin_button_power}

### HAL_PIN_BUTTON_POWER

```cpp
#define HAL_PIN_BUTTON_POWER GPIO_NUM_18
```

Defined in h1os/hal_types.h:30

Hardware BAT_KEY: Active LOW (external 10k pullup on PCB).

---

{#hal_pin_i2c_sda}

### HAL_PIN_I2C_SDA

```cpp
#define HAL_PIN_I2C_SDA GPIO_NUM_47
```

Defined in h1os/hal_types.h:33

Shared I2C Serial Data (SHTC3, PCF85063, ES8311).

---

{#hal_pin_i2c_scl}

### HAL_PIN_I2C_SCL

```cpp
#define HAL_PIN_I2C_SCL GPIO_NUM_48
```

Defined in h1os/hal_types.h:34

Shared I2C Serial Clock.

---

{#hal_pin_rtc_int}

### HAL_PIN_RTC_INT

```cpp
#define HAL_PIN_RTC_INT GPIO_NUM_5
```

Defined in h1os/hal_types.h:35

PCF85063A INT: Open-Drain (internal pullup mandatory).

---

{#hal_pin_epd_3v3_en}

### HAL_PIN_EPD_3V3_EN

```cpp
#define HAL_PIN_EPD_3V3_EN GPIO_NUM_6
```

Defined in h1os/hal_types.h:38

EPD 3.3V Rail Gate: Active LOW (0 = Rail ON).

---

{#hal_pin_epd_busy}

### HAL_PIN_EPD_BUSY

```cpp
#define HAL_PIN_EPD_BUSY GPIO_NUM_8
```

Defined in h1os/hal_types.h:39

Display Busy Line: Active HIGH (1 = Busy, 0 = Idle).

---

{#hal_pin_epd_rst}

### HAL_PIN_EPD_RST

```cpp
#define HAL_PIN_EPD_RST GPIO_NUM_9
```

Defined in h1os/hal_types.h:40

Display Hardware Reset: Active LOW.

---

{#hal_pin_epd_dc}

### HAL_PIN_EPD_DC

```cpp
#define HAL_PIN_EPD_DC GPIO_NUM_10
```

Defined in h1os/hal_types.h:41

Display Data / Command: 0 = Cmd, 1 = Data.

---

{#hal_pin_epd_cs}

### HAL_PIN_EPD_CS

```cpp
#define HAL_PIN_EPD_CS GPIO_NUM_11
```

Defined in h1os/hal_types.h:42

Display SPI Chip Select: Active LOW.

---

{#hal_pin_epd_sck}

### HAL_PIN_EPD_SCK

```cpp
#define HAL_PIN_EPD_SCK GPIO_NUM_12
```

Defined in h1os/hal_types.h:43

Display SPI Serial Clock (up to 20MHz).

---

{#hal_pin_epd_mosi}

### HAL_PIN_EPD_MOSI

```cpp
#define HAL_PIN_EPD_MOSI GPIO_NUM_13
```

Defined in h1os/hal_types.h:44

Display SPI Master Out Slave In.

---

{#hal_pin_pa_en}

### HAL_PIN_PA_EN

```cpp
#define HAL_PIN_PA_EN GPIO_NUM_42
```

Defined in h1os/hal_types.h:47

Amp Power Gate: Active LOW (1 = Power Cut, 0 = ON).

---

{#hal_pin_pa_ctrl}

### HAL_PIN_PA_CTRL

```cpp
#define HAL_PIN_PA_CTRL GPIO_NUM_46
```

Defined in h1os/hal_types.h:48

Amp Standby/Mute: Active HIGH (0 = Mute, 1 = Enable).

---

{#hal_pin_i2s_mclk}

### HAL_PIN_I2S_MCLK

```cpp
#define HAL_PIN_I2S_MCLK GPIO_NUM_14
```

Defined in h1os/hal_types.h:49

Master Clock (256 * Fs).

---

{#hal_pin_i2s_sclk}

### HAL_PIN_I2S_SCLK

```cpp
#define HAL_PIN_I2S_SCLK GPIO_NUM_15
```

Defined in h1os/hal_types.h:50

Bit / Serial Clock.

---

{#hal_pin_i2s_asdout}

### HAL_PIN_I2S_ASDOUT

```cpp
#define HAL_PIN_I2S_ASDOUT GPIO_NUM_16
```

Defined in h1os/hal_types.h:51

Codec Audio Out to ESP32 (DIN).

---

{#hal_pin_i2s_lrck}

### HAL_PIN_I2S_LRCK

```cpp
#define HAL_PIN_I2S_LRCK GPIO_NUM_38
```

Defined in h1os/hal_types.h:52

Word Select / Frame Sync (WS).

---

{#hal_pin_i2s_dsdin}

### HAL_PIN_I2S_DSDIN

```cpp
#define HAL_PIN_I2S_DSDIN GPIO_NUM_45
```

Defined in h1os/hal_types.h:53

ESP32 Audio Out to Codec (DOUT).

---

{#hal_pin_sd_clk}

### HAL_PIN_SD_CLK

```cpp
#define HAL_PIN_SD_CLK GPIO_NUM_39
```

Defined in h1os/hal_types.h:56

MicroSD Clock.

---

{#hal_pin_sd_miso}

### HAL_PIN_SD_MISO

```cpp
#define HAL_PIN_SD_MISO GPIO_NUM_40
```

Defined in h1os/hal_types.h:57

MicroSD MISO / D0.

---

{#hal_pin_sd_mosi}

### HAL_PIN_SD_MOSI

```cpp
#define HAL_PIN_SD_MOSI GPIO_NUM_41
```

Defined in h1os/hal_types.h:58

MicroSD MOSI / CMD.

---

{#hal_i2c_addr_es8311}

### HAL_I2C_ADDR_ES8311

```cpp
#define HAL_I2C_ADDR_ES8311 0x18
```

Defined in h1os/hal_types.h:61

Everest Semi Audio Codec 7-bit address.

---

{#hal_i2c_addr_pcf85063}

### HAL_I2C_ADDR_PCF85063

```cpp
#define HAL_I2C_ADDR_PCF85063 0x51
```

Defined in h1os/hal_types.h:62

NXP Calendar RTC 7-bit address.

---

{#hal_i2c_addr_shtc3}

### HAL_I2C_ADDR_SHTC3

```cpp
#define HAL_I2C_ADDR_SHTC3 0x70
```

Defined in h1os/hal_types.h:63

Sensirion Temp / Humidity Sensor 7-bit address.

---

{#hal_i2c_freq_hz}

### HAL_I2C_FREQ_HZ

```cpp
#define HAL_I2C_FREQ_HZ 400000
```

Defined in h1os/hal_types.h:65

Shared I2C bus fast-mode operating clock frequency (400 kHz).

---

{#hal_epd_width_px}

### HAL_EPD_WIDTH_PX

```cpp
#define HAL_EPD_WIDTH_PX 200
```

Defined in h1os/hal_types.h:68

Display panel width in physical pixels.

---

{#hal_epd_height_px}

### HAL_EPD_HEIGHT_PX

```cpp
#define HAL_EPD_HEIGHT_PX 200
```

Defined in h1os/hal_types.h:69

Display panel height in physical pixels.

---

{#hal_epd_dpi}

### HAL_EPD_DPI

```cpp
#define HAL_EPD_DPI 188
```

Defined in h1os/hal_types.h:70

Display panel resolution in dots per inch.

Packed 1-bit frame buffer size (5000 bytes).

---

{#hal_epd_frame_size_bytes}

### HAL_EPD_FRAME_SIZE_BYTES

```cpp
#define HAL_EPD_FRAME_SIZE_BYTES ((HAL_EPD_WIDTH_PX * HAL_EPD_HEIGHT_PX) / 8)
```

Defined in h1os/hal_types.h:73

---

{#hal_partition_epd_frame}

### HAL_PARTITION_EPD_FRAME

```cpp
#define HAL_PARTITION_EPD_FRAME "epd_frame"
```

Defined in h1os/hal_types.h:76

16KB dedicated SPI flash partition for raw EPD frame.

---

{#hal_partition_storage}

### HAL_PARTITION_STORAGE

```cpp
#define HAL_PARTITION_STORAGE "storage"
```

Defined in h1os/hal_types.h:77

SPIFFS / LittleFS non-volatile file storage partition.

---

{#orch_historical_ewma_alpha}

### ORCH_HISTORICAL_EWMA_ALPHA

```cpp
#define ORCH_HISTORICAL_EWMA_ALPHA 0.25f
```

Defined in orch_flow.c:41

---

{#orch_trinode_span_c}

### ORCH_TRINODE_SPAN_C

```cpp
#define ORCH_TRINODE_SPAN_C 5.0f
```

Defined in orch_flow.c:42

---

{#magnus_a}

### MAGNUS_A

```cpp
#define MAGNUS_A 17.625f
```

Defined in orch_math.c:15

---

{#magnus_b}

### MAGNUS_B

```cpp
#define MAGNUS_B 243.04f
```

Defined in orch_math.c:16

---

{#m_pi}

### M_PI

```cpp
#define M_PI 3.14159265358979323846f
```

Defined in sub_audio.c:27

---

{#es8311_reg_reset}

### ES8311_REG_RESET

```cpp
#define ES8311_REG_RESET 0x00
```

Defined in sub_audio.c:33

---

{#es8311_reg_sys_pwr_ana}

### ES8311_REG_SYS_PWR_ANA

```cpp
#define ES8311_REG_SYS_PWR_ANA 0x0D
```

Defined in sub_audio.c:34

---

{#es8311_reg_sys_lp_mod}

### ES8311_REG_SYS_LP_MOD

```cpp
#define ES8311_REG_SYS_LP_MOD 0x0F
```

Defined in sub_audio.c:35

---

{#es8311_reg_dac_pwr}

### ES8311_REG_DAC_PWR

```cpp
#define ES8311_REG_DAC_PWR 0x12
```

Defined in sub_audio.c:36

---

{#es8311_reg_dac_vol}

### ES8311_REG_DAC_VOL

```cpp
#define ES8311_REG_DAC_VOL 0x32
```

Defined in sub_audio.c:37

---

{#es8311_reg_flag}

### ES8311_REG_FLAG

```cpp
#define ES8311_REG_FLAG 0xFC
```

Defined in sub_audio.c:38

---

{#es8311_reg_chip_id1}

### ES8311_REG_CHIP_ID1

```cpp
#define ES8311_REG_CHIP_ID1 0xFD
```

Defined in sub_audio.c:39

---

{#es8311_reg_chip_id2}

### ES8311_REG_CHIP_ID2

```cpp
#define ES8311_REG_CHIP_ID2 0xFE
```

Defined in sub_audio.c:40

---

{#frame_size}

### FRAME_SIZE

```cpp
#define FRAME_SIZE 0x100
```

Defined in sub_audio.c:42

---

{#s_es8311_init_pre_charge_size}

### S_ES8311_INIT_PRE_CHARGE_SIZE

```cpp
#define S_ES8311_INIT_PRE_CHARGE_SIZE (sizeof(s_es8311_init_pre_charge)  / sizeof(s_es8311_init_pre_charge[0]) )
```

Defined in sub_audio.c:241

Pre Charge Table Size Macro.

---

{#s_es8311_init_post_charge_size}

### S_ES8311_INIT_POST_CHARGE_SIZE

```cpp
#define S_ES8311_INIT_POST_CHARGE_SIZE (sizeof(s_es8311_init_post_charge) / sizeof(s_es8311_init_post_charge[0]))
```

Defined in sub_audio.c:242

Post Charge Table Size Macro.

---

{#s_es8311_deinit_size}

### S_ES8311_DEINIT_SIZE

```cpp
#define S_ES8311_DEINIT_SIZE (sizeof(s_es8311_deinit)           / sizeof(s_es8311_deinit[0])          )
```

Defined in sub_audio.c:243

Deinit Table Size Macro.

---

{#lipo_table_size}

### LIPO_TABLE_SIZE

```cpp
#define LIPO_TABLE_SIZE (sizeof(s_lipo_table) / sizeof(s_lipo_table[0]))
```

Defined in sub_power.c:65

---

{#orch_rtc_magic}

### ORCH_RTC_MAGIC

```cpp
#define ORCH_RTC_MAGIC 0x534C4154
```

Defined in h1os/orch_state.h:19

RTC state validation sentinel word ('SLAT').

---

{#orch_ring_capacity}

### ORCH_RING_CAPACITY

```cpp
#define ORCH_RING_CAPACITY 32
```

Defined in h1os/orch_state.h:20

Fixed capacity of historical telemetry sample ring buffer.

---

{#sample_flag_valid_cold}

### SAMPLE_FLAG_VALID_COLD

```cpp
#define SAMPLE_FLAG_VALID_COLD 0x01
```

Defined in h1os/orch_state.h:34

Steady-state sample captured during quiescent sleep.

---

{#sample_flag_thermal_settled}

### SAMPLE_FLAG_THERMAL_SETTLED

```cpp
#define SAMPLE_FLAG_THERMAL_SETTLED 0x02
```

Defined in h1os/orch_state.h:35

Thermal plateau settled indicator.

---

{#sample_delta_gate_centi_c}

### SAMPLE_DELTA_GATE_CENTI_C

```cpp
#define SAMPLE_DELTA_GATE_CENTI_C 20
```

Defined in h1os/orch_state.h:36

Maximum allowable drift for steady state (0.20°C).

---

{#orch_flag_none}

### ORCH_FLAG_NONE

```cpp
#define ORCH_FLAG_NONE 0
```

Defined in h1os/orch_state.h:101

No persistent flags active.

---

{#orch_flag_epd_frame_valid}

### ORCH_FLAG_EPD_FRAME_VALID

```cpp
#define ORCH_FLAG_EPD_FRAME_VALID (1 << 0)
```

Defined in h1os/orch_state.h:102

Flash partition contains valid preserved display frame.

---

{#orch_flag_critical_battery}

### ORCH_FLAG_CRITICAL_BATTERY

```cpp
#define ORCH_FLAG_CRITICAL_BATTERY (1 << 1)
```

Defined in h1os/orch_state.h:103

Battery below brownout threshold.

---

{#orch_flag_thermal_lockout}

### ORCH_FLAG_THERMAL_LOCKOUT

```cpp
#define ORCH_FLAG_THERMAL_LOCKOUT (1 << 2)
```

Defined in h1os/orch_state.h:104

Self-heating lockout active.

---

{#sub_sdcard_mount_point}

### SUB_SDCARD_MOUNT_POINT

```cpp
#define SUB_SDCARD_MOUNT_POINT "/sdcard"
```

Defined in h1os/sub_sdcard.h:20

VFS mount point prefix for MicroSD filesystem.

---

{#epd_width}

### EPD_WIDTH

```cpp
#define EPD_WIDTH 200
```

Defined in h1os/sub_display.h:21

Panel width in pixels.

---

{#epd_height}

### EPD_HEIGHT

```cpp
#define EPD_HEIGHT 200
```

Defined in h1os/sub_display.h:22

Panel height in pixels.

5000-byte 1-bit packed frame buffer size.

---

{#epd_buffer_size}

### EPD_BUFFER_SIZE

```cpp
#define EPD_BUFFER_SIZE ((EPD_WIDTH * EPD_HEIGHT) / 8)
```

Defined in h1os/sub_display.h:25

---

{#lvgl_i1_palette_size}

### LVGL_I1_PALETTE_SIZE

```cpp
#define LVGL_I1_PALETTE_SIZE 8
```

Defined in h1os_lvgl.cpp:41

---

{#h1os_version_major}

### H1OS_VERSION_MAJOR

```cpp
#define H1OS_VERSION_MAJOR 2
```

Defined in h1os/h1os_version.h:17

Major version number (breaking API changes).

---

{#h1os_version_minor}

### H1OS_VERSION_MINOR

```cpp
#define H1OS_VERSION_MINOR 3
```

Defined in h1os/h1os_version.h:18

Minor version number (backward-compatible features).

---

{#h1os_version_patch}

### H1OS_VERSION_PATCH

```cpp
#define H1OS_VERSION_PATCH 3
```

Defined in h1os/h1os_version.h:19

Patch version number (backward-compatible bug fixes).

---

{#h1os_version_tag}

### H1OS_VERSION_TAG

```cpp
#define H1OS_VERSION_TAG "dev"
```

Defined in h1os/h1os_version.h:20

Pre-release release track tag.

---

{#h1os_version_string}

### H1OS_VERSION_STRING

```cpp
#define H1OS_VERSION_STRING "2.3.3-dev"
```

Defined in h1os/h1os_version.h:21

Full human-readable semantic version string.

---

{#h1os_name}

### H1OS_NAME

```cpp
#define H1OS_NAME "H1OS"
```

Defined in h1os/h1os_version.h:23

Primary operating system designation.

---

{#h1os_subtitle}

### H1OS_SUBTITLE

```cpp
#define H1OS_SUBTITLE "E-Class Environmental Operating System"
```

Defined in h1os/h1os_version.h:24

System commercial subtitle.

---

{#h1os_version_val}

### H1OS_VERSION_VAL

```cpp
#define H1OS_VERSION_VAL(major, minor, patch) (((uint32_t)(major) << 16) | ((uint32_t)(minor) << 8) | (uint32_t)(patch))
```

Defined in h1os/h1os_version.h:29

Helper macro to compute a 32-bit numeric version code.

---

{#h1os_version_code}

### H1OS_VERSION_CODE

```cpp
#define H1OS_VERSION_CODE H1OS_VERSION_VAL(H1OS_VERSION_MAJOR, H1OS_VERSION_MINOR, H1OS_VERSION_PATCH)
```

Defined in h1os/h1os_version.h:35

Current H1OS version encoded as a single 32-bit unsigned integer: (MAJOR << 16) | (MINOR << 8) | PATCH Example: 2.1.0 => 0x00020100.

---

{#h1os_version_check}

### H1OS_VERSION_CHECK

```cpp
#define H1OS_VERSION_CHECK(major, minor, patch) (H1OS_VERSION_CODE >= H1OS_VERSION_VAL(major, minor, patch))
```

Defined in h1os/h1os_version.h:40

Compile-time version check macro: true if current version >= specified version.

---

{#h1os_build_date}

### H1OS_BUILD_DATE

```cpp
#define H1OS_BUILD_DATE __DATE__
```

Defined in h1os/h1os_version.h:42

Compilation build date string.

---

{#h1os_build_time}

### H1OS_BUILD_TIME

```cpp
#define H1OS_BUILD_TIME __TIME__
```

Defined in h1os/h1os_version.h:43

Compilation build time string.

---

{#h1os_pin_power_hold}

### H1OS_PIN_POWER_HOLD

```cpp
#define H1OS_PIN_POWER_HOLD 17
```

Defined in h1os_boot_hook.c:19

---

{#h1os_pin_epd_3v3_en}

### H1OS_PIN_EPD_3V3_EN

```cpp
#define H1OS_PIN_EPD_3V3_EN 6
```

Defined in h1os_boot_hook.c:20

---

{#h1os_pin_pa_en}

### H1OS_PIN_PA_EN

```cpp
#define H1OS_PIN_PA_EN 42
```

Defined in h1os_boot_hook.c:21

---

{#h1os_pin_pa_ctrl}

### H1OS_PIN_PA_CTRL

```cpp
#define H1OS_PIN_PA_CTRL 46
```

Defined in h1os_boot_hook.c:22

---

{#sens_sar_peri_clk_gate_conf_reg}

### SENS_SAR_PERI_CLK_GATE_CONF_REG

```cpp
#define SENS_SAR_PERI_CLK_GATE_CONF_REG (DR_REG_SENS_BASE + 0x104)
```

Defined in orch_wake_stub.c:28

---

{#sens_tsens_clk_en}

### SENS_TSENS_CLK_EN

```cpp
#define SENS_TSENS_CLK_EN (1UL << 29)
```

Defined in orch_wake_stub.c:31

---

{#sda_bit_mask}

### SDA_BIT_MASK

```cpp
#define SDA_BIT_MASK (1UL << (HAL_PIN_I2C_SDA - 32))
```

Defined in orch_wake_stub.c:35

---

{#scl_bit_mask}

### SCL_BIT_MASK

```cpp
#define SCL_BIT_MASK (1UL << (HAL_PIN_I2C_SCL - 32))
```

Defined in orch_wake_stub.c:36

---

{#i2c_addr_shtc3}

### I2C_ADDR_SHTC3

```cpp
#define I2C_ADDR_SHTC3 0x70
```

Defined in orch_wake_stub.c:38

---

{#i2c_addr_pcf85063}

### I2C_ADDR_PCF85063

```cpp
#define I2C_ADDR_PCF85063 0x51
```

Defined in orch_wake_stub.c:39

---

{#rtc_reg_control_2-1}

### RTC_REG_CONTROL_2

```cpp
#define RTC_REG_CONTROL_2 0x01
```

Defined in orch_wake_stub.c:40

---

{#rtc_reg_timer_val}

### RTC_REG_TIMER_VAL

```cpp
#define RTC_REG_TIMER_VAL 0x10
```

Defined in orch_wake_stub.c:41

---

{#rtc_reg_timer_mode-1}

### RTC_REG_TIMER_MODE

```cpp
#define RTC_REG_TIMER_MODE 0x11
```

Defined in orch_wake_stub.c:42

---

{#rtc_timer_clk_1_hz}

### RTC_TIMER_CLK_1_HZ

```cpp
#define RTC_TIMER_CLK_1_HZ (2 << 3)
```

Defined in orch_wake_stub.c:44

---

{#rtc_timer_clk_1_60_hz}

### RTC_TIMER_CLK_1_60_HZ

```cpp
#define RTC_TIMER_CLK_1_60_HZ (3 << 3)
```

Defined in orch_wake_stub.c:45

---

{#rtc_timer_int_en_bit}

### RTC_TIMER_INT_EN_BIT

```cpp
#define RTC_TIMER_INT_EN_BIT (1 << 1)
```

Defined in orch_wake_stub.c:46

---

{#rtc_timer_pulse_bit}

### RTC_TIMER_PULSE_BIT

```cpp
#define RTC_TIMER_PULSE_BIT (1 << 0)
```

Defined in orch_wake_stub.c:47

---

{#rtc_timer_te_bit}

### RTC_TIMER_TE_BIT

```cpp
#define RTC_TIMER_TE_BIT (1 << 2)
```

Defined in orch_wake_stub.c:49

---

{#rtc_timer_tcf_mask}

### RTC_TIMER_TCF_MASK

```cpp
#define RTC_TIMER_TCF_MASK (3 << 3)
```

Defined in orch_wake_stub.c:50

---

{#rtc_timer_tcf_min}

### RTC_TIMER_TCF_MIN

```cpp
#define RTC_TIMER_TCF_MIN (3 << 3)
```

Defined in orch_wake_stub.c:51

---

{#rtc_ctrl2_cof_off}

### RTC_CTRL2_COF_OFF

```cpp
#define RTC_CTRL2_COF_OFF 0x07
```

Defined in orch_wake_stub.c:52

---

{#config_h1os_epd_partial_refresh_limit}

### CONFIG_H1OS_EPD_PARTIAL_REFRESH_LIMIT

```cpp
#define CONFIG_H1OS_EPD_PARTIAL_REFRESH_LIMIT 6
```

Defined in orch_display_sync.c:20

## Enumerations

---

{#h1os_splash_type_t}

### h1os_splash_type_t

```cpp
enum h1os_splash_type_t
```

Defined in h1os/h1os.h:44

Graphical splash screen trigger types.

| Value | Description |
|-------|-------------|
| `H1OS_SPLASH_BOOT` | Initial cold boot / power-on splash screen. |
| `H1OS_SPLASH_SLEEP` | Transition to unattended deep sleep splash screen. |
| `H1OS_SPLASH_SHUTDOWN` | Orderly physical power-down splash screen. |
| `H1OS_SPLASH_MAX` | Sentinel maximum splash enum value. |

---

{#h1os_time_format_t}

### h1os_time_format_t

```cpp
enum h1os_time_format_t
```

Defined in h1os/h1os_time.h:25

Time presentation format options.

| Value | Description |
|-------|-------------|
| `H1OS_TIME_FMT_24H_SEC` | 24-hour time with seconds: "14:35:08" |
| `H1OS_TIME_FMT_24H_MIN` | 24-hour time without seconds: "14:35" |
| `H1OS_TIME_FMT_12H_SEC` | 12-hour time with seconds: "02:35:08 PM" |
| `H1OS_TIME_FMT_12H_MIN` | 12-hour time without seconds: "02:35 PM" |

---

{#h1os_date_format_t}

### h1os_date_format_t

```cpp
enum h1os_date_format_t
```

Defined in h1os/h1os_time.h:35

Date presentation format options.

| Value | Description |
|-------|-------------|
| `H1OS_DATE_FMT_MM_DD_YY` | Month/Day/Year format: "09/26/26". |
| `H1OS_DATE_FMT_DOW` | Day-of-week textual format: "Saturday". |
| `H1OS_DATE_FMT_MM_DD_YY_DOW` | Combined date and day: "09/26/26 Saturday". |

---

{#hal_btn_mask_t}

### hal_btn_mask_t

```cpp
enum hal_btn_mask_t
```

Defined in h1os/hal_types.h:83

Pushbutton actuation bitmask identifiers.

| Value | Description |
|-------|-------------|
| `HAL_BTN_NONE` | No buttons depressed. |
| `HAL_BTN_BOOT` | BOOT0 button depressed (GPIO 0). |
| `HAL_BTN_POWER` | POWER button depressed (GPIO 18). |

---

{#h1os_wake_btn_t}

### h1os_wake_btn_t

```cpp
enum h1os_wake_btn_t
```

Defined in h1os/hal_types.h:92

Waking button identifier reported by ULP coprocessor.

| Value | Description |
|-------|-------------|
| `H1OS_WAKE_BTN_NONE` | Wake was not triggered by a physical button. |
| `H1OS_WAKE_BTN_BOOT` | Woken by BOOT0 button (GPIO 0). |
| `H1OS_WAKE_BTN_POWER` | Woken by POWER button (GPIO 18). |

---

{#h1os_chime_type_t}

### h1os_chime_type_t

```cpp
enum h1os_chime_type_t
```

Defined in h1os/hal_types.h:101

Acoustic chime sound pattern types.

| Value | Description |
|-------|-------------|
| `H1OS_CHIME_BOOT` | Ascending multi-tone power-on chime. |
| `H1OS_CHIME_SLEEP` | Descending sleep preparation chime. |
| `H1OS_CHIME_SHUTDOWN` | Dual-tone shutdown confirmation chime. |
| `H1OS_CHIME_ALARM` | Repetitive alert chime pattern. |
| `H1OS_CHIME_MAX` | Sentinel maximum chime enum value. |

---

{#sys_clk_mode_t}

### sys_clk_mode_t

```cpp
enum sys_clk_mode_t
```

Defined in h1os/hal_types.h:112

System CPU clock frequency scaling and power profile modes.

| Value | Description |
|-------|-------------|
| `SYS_CLK_MODE_DYNAMIC` | Dynamic Frequency Scaling: 80 MHz baseline, 240 MHz turbo bursts (Default). |
| `SYS_CLK_MODE_FIXED_MAX` | Fixed Maximum Clock: Locked to max frequency (240 MHz), DFS disabled. |
| `SYS_CLK_MODE_FIXED_MIN` | Fixed Minimum Clock: Locked to base frequency (80 MHz), turbo disabled. |

---

{#orch_flow_type_t}

### orch_flow_type_t

```cpp
enum orch_flow_type_t
```

Defined in h1os/orch_flow.h:24

Execution flow lifecycle pathways.

| Value | Description |
|-------|-------------|
| `ORCH_FLOW_BOOT` | Initial system boot / cold power-on reset. |
| `ORCH_FLOW_A_SAMPLE` | Headless sub-3ms sensor sample burst. |
| `ORCH_FLOW_B_MAIN_WAKE` | Full interactive UI wake / Button wake / RTC timer expiry. |
| `ORCH_FLOW_BOOTLOADER_JUMP` | ROM bootloader download mode transition. |
| `ORCH_FLOW_CRITICAL_OFF` | Low battery shutdown or physical power cut. |

---

{#sub_audio_type_t}

### sub_audio_type_t

```cpp
enum sub_audio_type_t
```

Defined in h1os/sub_audio.h:24

Acoustic payload type for consolidated sub_audio_play dispatch.

| Value | Description |
|-------|-------------|
| `SUB_AUDIO_TONE` | Synthesized tone pattern (freq_hz, duration_ms). |
| `SUB_AUDIO_CHIME` | Standard acoustic presentation chime pattern. |
| `SUB_AUDIO_PCM` | Raw 16-bit signed Mono PCM buffer stream. |

---

{#sub_power_sleep_mode_t}

### sub_power_sleep_mode_t

```cpp
enum sub_power_sleep_mode_t
```

Defined in h1os/sub_power.h:24

Deep sleep cycle execution modes.

| Value | Description |
|-------|-------------|
| `SUB_POWER_SLEEP_FULL_CYCLE` | Normal Flow B sleep: arms PCF85063A countdown & resets slice_counter. |
| `SUB_POWER_SLEEP_FLOW_A_BURST` | Flow A sample sleep: preserves running PCF85063A countdown & slice_counter. |

---

{#audio_cmd_type_t}

### audio_cmd_type_t

```cpp
enum audio_cmd_type_t
```

Defined in sub_audio.c:44

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

Defined in h1os/orch_state.h:25

ULP coprocessor dispatch wakeup reasons.

| Value | Description |
|-------|-------------|
| `ULP_DISPATCH_NONE` | No dispatch action required. |
| `ULP_DISPATCH_SENSOR_SAMPLE` | Headless Flow A sensor sample burst dispatch. |
| `ULP_DISPATCH_MAIN_WAKE` | Interactive Flow B UI presentation wake dispatch. |
| `ULP_DISPATCH_CRITICAL_SHUTDOWN` | Low-battery brownout threshold cut dispatch. |
| `ULP_DISPATCH_BOOTLOADER_JUMP` | BOOT0 held down during sleep: jump to download mode. |
| `ULP_DISPATCH_POWER_OFF` | BAT_KEY long-press held down during sleep: power off. |
## Typedefs

---

{#h1os_boot_cb_t}

### h1os_boot_cb_t

```cpp
using h1os_boot_cb_t = void(*)
```

Defined in h1os/h1os.h:56

System boot and power-on reset callback signature.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `user_data` |  | User context pointer configured in [h1os_lifecycle_t](#h1os_lifecycle_t). |

---

{#h1os_wake_cb_t}

### h1os_wake_cb_t

```cpp
using h1os_wake_cb_t = void(*)
```

Defined in h1os/h1os.h:64

Interactive wake callback signature (Timer / RTC Alarm / Button Tap).

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `ctx` |  | Pointer to populated wake context struct. |
| `user_data` |  | User context pointer configured in [h1os_lifecycle_t](#h1os_lifecycle_t). |

---

{#h1os_pre_sleep_cb_t}

### h1os_pre_sleep_cb_t

```cpp
using h1os_pre_sleep_cb_t = void(*)
```

Defined in h1os/h1os.h:72

Callback executed immediately prior to entering deep sleep.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `sleep_sec` |  | Planned sleep interval in seconds. |
| `user_data` |  | User context pointer configured in [h1os_lifecycle_t](#h1os_lifecycle_t). |

---

{#h1os_shutdown_cb_t}

### h1os_shutdown_cb_t

```cpp
using h1os_shutdown_cb_t = void(*)
```

Defined in h1os/h1os.h:79

Callback executed immediately prior to battery power cut.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `user_data` |  | User context pointer configured in [h1os_lifecycle_t](#h1os_lifecycle_t). |

---

{#h1os_splash_cb_t}

### h1os_splash_cb_t

```cpp
using h1os_splash_cb_t = void(*)
```

Defined in h1os/h1os.h:87

Presentation splash screen rendering callback signature.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `type` |  | Type of splash screen being rendered. |
| `user_data` |  | User context pointer configured in [h1os_lifecycle_t](#h1os_lifecycle_t). |

---

{#h1os_chime_cb_t}

### h1os_chime_cb_t

```cpp
using h1os_chime_cb_t = void(*)
```

Defined in h1os/h1os.h:95

Acoustic presentation chime playback callback signature.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `type` |  | Type of chime pattern requested. |
| `user_data` |  | User context pointer configured in [h1os_lifecycle_t](#h1os_lifecycle_t). |

---

{#h1os_time_sync_cb_t}

### h1os_time_sync_cb_t

```cpp
using h1os_time_sync_cb_t = esp_err_t(*)
```

Defined in h1os/h1os_time.h:49

Callback for external network/remote time acquisition (SNTP, GPS, BLE).

#### Returns
ESP_OK if external time was synchronized, or error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ms` |  | Network acquisition timeout in milliseconds. |
| `user_data` |  | Arbitrary user context pointer. |

## Functions

---

{#h1os_get_version}

### h1os_get_version

`static` `inline`

```cpp
static inline const char * h1os_get_version(void)
```

Defined in h1os/h1os.h:165

Get the H1OS semantic version string.

#### Returns
Null-terminated semantic version string (e.g. "2.3.2-dev").

---

{#h1os_start}

### h1os_start

```cpp
esp_err_t h1os_start(const h1os_lifecycle_t * config)
```

Defined in h1os/h1os.h:183

Initialize H1OS and dispatch application lifecycle.

Configures hardware subsystems, determines boot/wake flow, initializes FreeRTOS tasks, and dispatches the configured application lifecycle hooks.

#### Returns

* ESP_OK: System initialized and lifecycle dispatched successfully.
* ESP_ERR_INVALID_ARG: Null pointer provided for configuration.
* ESP_FAIL: Hardware initialization failure.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `config` | const [`h1os_lifecycle_t`](#h1os_lifecycle_t) * | Parameter config. |

---

{#h1os_set_volume}

### h1os_set_volume

```cpp
esp_err_t h1os_set_volume(uint8_t volume_pct)
```

Defined in h1os/h1os.h:197

Set audio subsystem output volume percentage.

Set audio subsystem output volume percentage (0% = Mute, 100% = 0 dB Max).

Controls ES8311 DAC gain and NS4168 power state. 0% volume automatically mutes the output and puts the amplifier into low-power standby.

#### Returns

* ESP_OK: Volume level configured successfully.
* ESP_ERR_INVALID_STATE: Audio subsystem not initialized.

Set audio subsystem output volume percentage.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `volume_pct` | `uint8_t` | Parameter volume_pct. |

---

{#h1os_get_telemetry}

### h1os_get_telemetry

```cpp
esp_err_t h1os_get_telemetry(h1os_telemetry_t * out_telemetry)
```

Defined in h1os/h1os.h:211

Retrieve current Tri-Node environmental telemetry.

Copies the latest validated psychrometric invariants, sensor readings, and battery metrics into the caller-provided telemetry structure.

#### Returns

* ESP_OK: Telemetry snapshot copied successfully.
* ESP_ERR_INVALID_ARG: Null pointer passed.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_telemetry` | [`h1os_telemetry_t`](#h1os_telemetry_t) * | Parameter out_telemetry. |

---

{#h1os_sleep}

### h1os_sleep

```cpp
esp_err_t h1os_sleep(uint32_t sleep_sec)
```

Defined in h1os/h1os.h:225

Put the platform into ultra-low-power deep sleep.

Arms the PCF85063A countdown timer, isolates GPIO sleep pads, holds power latch, and enters ESP32-S3 deep sleep.

#### Returns

* ESP_OK: Sleep transition armed.
* ESP_ERR_INVALID_ARG: sleep_sec out of supported hardware range.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `sleep_sec` | `uint32_t` | Parameter sleep_sec. |

---

{#h1os_reset_session_timer}

### h1os_reset_session_timer

```cpp
void h1os_reset_session_timer(void)
```

Defined in h1os/h1os.h:233

Reset the interactive session inactivity timer.

Reset the interactive session inactivity timer (extends session by timeout_sec).

Extends the interactive user session by inactivity_timeout_sec, preventing premature deep sleep while user interaction or animation is underway.

Reset the interactive session inactivity timer.

---

{#h1os_is_session_active}

### h1os_is_session_active

```cpp
bool h1os_is_session_active(void)
```

Defined in h1os/h1os.h:240

Check whether an interactive inactivity countdown session is active.

#### Returns
True if running in an interactive user session, false during unattended wakes.

#### Returns
true if running in an interactive user session, false during unattended wakes.

---

{#h1os_shutdown}

### h1os_shutdown

```cpp
void h1os_shutdown(void)
```

Defined in h1os/h1os.h:248

Orderly system shutdown and physical battery power cut.

Invokes lifecycle on_shutdown hook, safely isolates peripherals, deactivates displays, and releases GPIO 17 BAT_CTRL power latch.

---

{#h1os_shutdown_for_storage}

### h1os_shutdown_for_storage

```cpp
void h1os_shutdown_for_storage(void)
```

Defined in h1os/h1os.h:256

Shutdown for long-term storage.

Shutdown for long-term storage: clears display to pure white before cutting power.

Performs pure white full OTP refresh on electrophoretic display before cutting power latch, protecting e-Paper microcapsules against dye migration and burn-in.

Shutdown for long-term storage.

Protects e-Paper electrophoretic microcapsules against permanent dye migration and burn-in.

---

{#ulp_raw_to_mv}

### ulp_raw_to_mv

`static` `inline`

```cpp
static inline uint32_t ulp_raw_to_mv(int32_t raw)
```

Defined in main.c:69

Converts raw ADC tick value to battery voltage in millivolts.

#### Returns
Calibrated voltage in millivolts.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `raw` | `int32_t` | Raw ADC reading. |

---

{#ulp_clear_gpio_wakeup_latch}

### ulp_clear_gpio_wakeup_latch

`static` `inline`

```cpp
static inline void ulp_clear_gpio_wakeup_latch(void)
```

Defined in main.c:82

Clear latched RTC GPIO status and ULP wakeup flip-flop.

---

{#ulp_disarm_and_wake_main}

### ulp_disarm_and_wake_main

`static` `inline`

```cpp
static inline void ulp_disarm_and_wake_main(void)
```

Defined in main.c:93

Disarm ULP GPIO wakeup and trigger main Xtensa processor wakeup once PMU is ready.

---

{#ulp_read_vbat_adc_bounded}

### ulp_read_vbat_adc_bounded

`static`

```cpp
static bool ulp_read_vbat_adc_bounded(int32_t * out_raw)
```

Defined in main.c:113

Perform a timeout-bounded SAR ADC1 read on ADC1_CHANNEL_3 (GPIO 4).

#### Returns
true if conversion completed within timeout, false if timed out.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_raw` | `int32_t *` | Raw 12-bit ADC value on success. |

---

{#ulp_dispatch_and_wake}

### ulp_dispatch_and_wake

`static`

```cpp
static void ulp_dispatch_and_wake(uint32_t rtcio_int_st, int boot_btn, int pwr_btn, int rtc_int, uint32_t vbat_mv)
```

Defined in main.c:151

Evaluates wakeup triggers and arbitrates wake/shutdown dispatch.

Handles button debounce, long-press detection, RTC countdown slicing, and critical battery cut.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `rtcio_int_st` | `uint32_t` | Raw RTC IO interrupt status bitmask. |
| `boot_btn` | `int` | BOOT0 button state (0 = pressed). |
| `pwr_btn` | `int` | POWER button state (0 = pressed). |
| `rtc_int` | `int` | RTC INT line state (0 = active). |
| `vbat_mv` | `uint32_t` | Current battery voltage in millivolts. |

---

{#main}

### main

```cpp
int main(void)
```

Defined in main.c:269

Main ULP-RISC-V entry point.

#### Returns
0 on halt.

---

{#hal_io_early_init}

### hal_io_early_init

```cpp
esp_err_t hal_io_early_init(void)
```

Defined in h1os/hal_io.h:27

Early boot initialization of non-latched application pins.

Releases sleep pad holds on dynamic peripheral/wake pins, configures amplifier mute (GPIO 46), status LED (GPIO 3), buttons (GPIO 0/18), and RTC INT (GPIO 5). Note: Master power rails (GPIO 17 BAT_CTRL, GPIO 6 EPD_3V3_EN, GPIO 42 PA_EN) are strictly latched in the 2nd-stage bootloader ([h1os_boot_hook.c](#h1os_boot_hookc)).

#### Returns
ESP_OK on success, or driver error code.

---

{#hal_io_set_led}

### hal_io_set_led

```cpp
esp_err_t hal_io_set_led(bool on)
```

Defined in h1os/hal_io.h:36

Controls user status LED (GPIO 3, Active LOW).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `on` | `bool` | True to turn LED ON (drive 0); False to turn OFF (drive 1). |

---

{#hal_led_pwm_init}

### hal_led_pwm_init

```cpp
esp_err_t hal_led_pwm_init(void)
```

Defined in h1os/hal_io.h:45

Initializes LEDC hardware PWM controller for user LED on GPIO 3.

Enables 10-bit hardware brightness resolution (0..100%) and hardware smooth fading.

#### Returns
ESP_OK on success.

---

{#hal_led_set_brightness}

### hal_led_set_brightness

```cpp
esp_err_t hal_led_set_brightness(uint8_t brightness_pct)
```

Defined in h1os/hal_io.h:54

Sets user LED brightness percentage using hardware PWM (0..100%).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `brightness_pct` | `uint8_t` | Brightness percentage: 0 = OFF, 100 = Maximum. |

---

{#hal_led_fade_to}

### hal_led_fade_to

```cpp
esp_err_t hal_led_fade_to(uint8_t target_pct, uint32_t duration_ms)
```

Defined in h1os/hal_io.h:66

Smoothly fades user LED to target brightness using hardware fade engine.

Non-blocking: hardware timer interpolates duty cycle with zero CPU overhead.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `target_pct` | `uint8_t` | Target brightness percentage (0..100%). |
| `duration_ms` | `uint32_t` | Duration of fade transition in milliseconds. |

---

{#hal_led_start_breathing}

### hal_led_start_breathing

```cpp
esp_err_t hal_led_start_breathing(uint32_t cycle_period_ms)
```

Defined in h1os/hal_io.h:77

Starts an asynchronous background task to "breathe" (fade in and fade out) the status LED.

Uses hardware LEDC PWM fading with FreeRTOS background pacing. Automatically yields CPU.

#### Returns
ESP_OK on success, or ESP_FAIL if task creation fails.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `cycle_period_ms` | `uint32_t` | Total duration of one breathe cycle in ms (fade-in + fade-out). Default: 2000 ms if 0. |

---

{#hal_led_stop_breathing}

### hal_led_stop_breathing

```cpp
esp_err_t hal_led_stop_breathing(void)
```

Defined in h1os/hal_io.h:84

Stops the asynchronous breathing task and turns the LED off.

#### Returns
ESP_OK on success.

---

{#hal_led_is_breathing}

### hal_led_is_breathing

```cpp
bool hal_led_is_breathing(void)
```

Defined in h1os/hal_io.h:91

Queries whether the asynchronous breathing task is actively running.

#### Returns
True if breathing task is active, false otherwise.

---

{#hal_led_pwm_deinit}

### hal_led_pwm_deinit

```cpp
esp_err_t hal_led_pwm_deinit(void)
```

Defined in h1os/hal_io.h:98

Deinitializes LEDC hardware PWM and restores GPIO 3 to static GPIO mode.

#### Returns
ESP_OK on success.

---

{#hal_io_release_power_latch}

### hal_io_release_power_latch

```cpp
esp_err_t hal_io_release_power_latch(void)
```

Defined in h1os/hal_io.h:107

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

Defined in h1os/hal_io.h:114

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

Defined in h1os/hal_io.h:123

Stateless check if a specific button pin is actively held down (Active LOW).

#### Returns
True if depressed, false otherwise.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `pin` | `gpio_num_t` | GPIO_NUM_0 (BOOT) or GPIO_NUM_18 (POWER). |

---

{#hal_io_isolate_sleep_pads}

### hal_io_isolate_sleep_pads

```cpp
esp_err_t hal_io_isolate_sleep_pads(void)
```

Defined in h1os/hal_io.h:138

Configures and locks dynamic peripheral lines prior to deep sleep.

* Latches GPIO 11 (EPD_CS) and GPIO 9 (EPD_RST) HIGH via gpio_hold_en().
* Holds amplifier mute GPIO 46 (PA_CTRL) LOW.
* Configures RTC IO pull-ups on wake inputs (GPIO 0, GPIO 5, GPIO 18).
* Preserves 2nd-stage bootloader holds on GPIO 17 (BAT_CTRL), GPIO 6 (EPD_3V3_EN), and GPIO 42 (PA_EN).

#### Returns
ESP_OK on success.

* Latches GPIO 11 (EPD_CS) and GPIO 9 (EPD_RST) HIGH via gpio_hold_en(). Holds amplifier mute GPIO 46 (PA_CTRL) LOW. Configures RTC IO pull-ups on wake inputs (GPIO 0, GPIO 5, GPIO 18). Preserves 2nd-stage bootloader holds on GPIO 17 (BAT_CTRL), GPIO 6 (EPD_3V3_EN), and GPIO 42 (PA_EN).

#### Returns
ESP_OK on success.

---

{#hal_io_release_pad_holds}

### hal_io_release_pad_holds

```cpp
esp_err_t hal_io_release_pad_holds(void)
```

Defined in h1os/hal_io.h:145

Releases sleep pad holds on dynamic peripheral/wake pins upon waking from deep sleep.

#### Returns
ESP_OK on success.

---

{#hal_check_usb_ll}

### hal_check_usb_ll

```cpp
bool hal_check_usb_ll(void)
```

Defined in h1os/hal_io.h:152

Check if USB Serial/JTAG is connected to an active host via SOF packets.

#### Returns
True if USB host connection detected, false otherwise.

USB Full-Speed hosts transmit a Start-Of-Frame (SOF) packet every 1.000 ms. Sampling both the SOF interrupt flag and frame counter delta across a single 1100 us window cuts active spin time from 3000 us to 1100 us per check.

#### Returns
true if USB host connection detected, false otherwise.

---

{#hal_io_early_init-1}

### hal_io_early_init

```cpp
esp_err_t hal_io_early_init(void)
```

Defined in hal_io.c:32

Early boot initialization of non-latched application pins.

Releases sleep pad holds on dynamic peripheral/wake pins, configures amplifier mute (GPIO 46), status LED (GPIO 3), buttons (GPIO 0/18), and RTC INT (GPIO 5). Note: Master power rails (GPIO 17 BAT_CTRL, GPIO 6 EPD_3V3_EN, GPIO 42 PA_EN) are strictly latched in the 2nd-stage bootloader ([h1os_boot_hook.c](#h1os_boot_hookc)).

#### Returns
ESP_OK on success, or driver error code.

---

{#hal_io_release_power_latch-1}

### hal_io_release_power_latch

```cpp
esp_err_t hal_io_release_power_latch(void)
```

Defined in hal_io.c:99

Releases the battery LDO power latch (GPIO 17 LOW, pad hold disabled) for physical power-down.

Strictly for system shutdown; assertion of GPIO 17 is handled exclusively by the 2nd-stage bootloader.

#### Returns
ESP_OK on success.

---

{#hal_led_pwm_init-1}

### hal_led_pwm_init

```cpp
esp_err_t hal_led_pwm_init(void)
```

Defined in hal_io.c:123

Initializes LEDC hardware PWM controller for user LED on GPIO 3.

Enables 10-bit hardware brightness resolution (0..100%) and hardware smooth fading.

#### Returns
ESP_OK on success.

---

{#hal_led_set_brightness-1}

### hal_led_set_brightness

```cpp
esp_err_t hal_led_set_brightness(uint8_t brightness_pct)
```

Defined in hal_io.c:175

Sets user LED brightness percentage using hardware PWM (0..100%).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `brightness_pct` | `uint8_t` | Brightness percentage: 0 = OFF, 100 = Maximum. |

---

{#hal_led_fade_to-1}

### hal_led_fade_to

```cpp
esp_err_t hal_led_fade_to(uint8_t target_pct, uint32_t duration_ms)
```

Defined in hal_io.c:200

Smoothly fades user LED to target brightness using hardware fade engine.

Non-blocking: hardware timer interpolates duty cycle with zero CPU overhead.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `target_pct` | `uint8_t` | Target brightness percentage (0..100%). |
| `duration_ms` | `uint32_t` | Duration of fade transition in milliseconds. |

---

{#led_breath_task}

### led_breath_task

`static`

```cpp
static void led_breath_task(void * arg)
```

Defined in hal_io.c:226

Led breath task.

#### Returns
Return value of type static void.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `arg` | `void *` | Parameter arg. |

---

{#hal_led_start_breathing-1}

### hal_led_start_breathing

```cpp
esp_err_t hal_led_start_breathing(uint32_t cycle_period_ms)
```

Defined in hal_io.c:266

Starts an asynchronous background task to "breathe" (fade in and fade out) the status LED.

Uses hardware LEDC PWM fading with FreeRTOS background pacing. Automatically yields CPU.

#### Returns
ESP_OK on success, or ESP_FAIL if task creation fails.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `cycle_period_ms` | `uint32_t` | Total duration of one breathe cycle in ms (fade-in + fade-out). Default: 2000 ms if 0. |

---

{#hal_led_stop_breathing-1}

### hal_led_stop_breathing

```cpp
esp_err_t hal_led_stop_breathing(void)
```

Defined in hal_io.c:298

Stops the asynchronous breathing task and turns the LED off.

#### Returns
ESP_OK on success.

---

{#hal_led_is_breathing-1}

### hal_led_is_breathing

```cpp
bool hal_led_is_breathing(void)
```

Defined in hal_io.c:323

Queries whether the asynchronous breathing task is actively running.

#### Returns
True if breathing task is active, false otherwise.

---

{#hal_led_pwm_deinit-1}

### hal_led_pwm_deinit

```cpp
esp_err_t hal_led_pwm_deinit(void)
```

Defined in hal_io.c:333

Deinitializes LEDC hardware PWM and restores GPIO 3 to static GPIO mode.

#### Returns
ESP_OK on success.

---

{#hal_io_set_led-1}

### hal_io_set_led

```cpp
esp_err_t hal_io_set_led(bool on)
```

Defined in hal_io.c:366

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

Defined in hal_io.c:383

Samples instantaneous state of hardware tactile buttons.

#### Returns
Bitmask of currently depressed buttons (HAL_BTN_BOOT | HAL_BTN_POWER).

---

{#hal_io_isolate_sleep_pads-1}

### hal_io_isolate_sleep_pads

```cpp
esp_err_t hal_io_isolate_sleep_pads(void)
```

Defined in hal_io.c:405

Configures and locks dynamic peripheral lines prior to deep sleep.

* Latches GPIO 11 (EPD_CS) and GPIO 9 (EPD_RST) HIGH via gpio_hold_en(). Holds amplifier mute GPIO 46 (PA_CTRL) LOW. Configures RTC IO pull-ups on wake inputs (GPIO 0, GPIO 5, GPIO 18). Preserves 2nd-stage bootloader holds on GPIO 17 (BAT_CTRL), GPIO 6 (EPD_3V3_EN), and GPIO 42 (PA_EN).

#### Returns
ESP_OK on success.

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

Defined in hal_io.c:449

Releases sleep pad holds on dynamic peripheral/wake pins upon waking from deep sleep.

#### Returns
ESP_OK on success.

---

{#hal_check_usb_ll-1}

### hal_check_usb_ll

```cpp
bool hal_check_usb_ll(void)
```

Defined in hal_io.c:482

Check if USB Serial/JTAG is connected to an active host via SOF packets.

USB Full-Speed hosts transmit a Start-Of-Frame (SOF) packet every 1.000 ms. Sampling both the SOF interrupt flag and frame counter delta across a single 1100 us window cuts active spin time from 3000 us to 1100 us per check.

#### Returns
true if USB host connection detected, false otherwise.

#### Returns
True if USB host connection detected, false otherwise.

---

{#hal_i2c_init}

### hal_i2c_init

```cpp
esp_err_t hal_i2c_init(void)
```

Defined in h1os/hal_i2c.h:29

Initialize shared I2C master bus hardware.

Initializes the shared I2C master bus hardware.

Installs ESP-IDF I2C driver on GPIO 47 / GPIO 48 and creates recursive mutex.

#### Returns

* ESP_OK: Bus initialized and mutex created successfully.
* ESP_ERR_INVALID_STATE: Driver already installed.
* ESP_FAIL: Hardware initialization failed.

Initialize shared I2C master bus hardware.

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

Deinitialize shared I2C master bus and release mutex.

Deinitializes the shared I2C master bus and releases mutex.

#### Returns
ESP_OK on success.

Deinitialize shared I2C master bus and release mutex.

#### Returns
ESP_OK on success.

---

{#hal_i2c_write}

### hal_i2c_write

```cpp
esp_err_t hal_i2c_write(uint8_t dev_addr, const uint8_t * write_data, size_t write_len, uint32_t timeout_ms)
```

Defined in h1os/hal_i2c.h:51

Execute an atomic register write transaction over I2C.

Executes an atomic register write transaction over I2C.

#### Returns

* ESP_OK: Write transaction acknowledged.
* ESP_ERR_TIMEOUT: Bus transaction timed out.
* ESP_ERR_INVALID_ARG: Null pointer.

Execute an atomic register write transaction over I2C.

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

Defined in h1os/hal_i2c.h:66

Execute an atomic register read transaction over I2C.

Executes an atomic register read transaction over I2C.

#### Returns

* ESP_OK: Read transaction completed successfully.
* ESP_ERR_TIMEOUT: Bus transaction timed out.
* ESP_ERR_INVALID_ARG: Null pointer.

Execute an atomic register read transaction over I2C.

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

Defined in h1os/hal_i2c.h:83

Execute an atomic write-then-read combined transaction (Repeated START).

Executes an atomic write-then-read combined transaction (Repeated START).

#### Returns

* ESP_OK: Combined transaction completed successfully.
* ESP_ERR_TIMEOUT: Bus transaction timed out.
* ESP_ERR_INVALID_ARG: Null pointer.

Execute an atomic write-then-read combined transaction (Repeated START).

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

Defined in h1os/hal_i2c.h:96

Probe if an I2C device responds with ACK at given 7-bit address.

Probes if an I2C device with given 7-bit address responds on the bus.

#### Returns

* ESP_OK: Device responded with ACK.
* ESP_ERR_NOT_FOUND: Device NACKed address byte.
* ESP_ERR_TIMEOUT: Transaction timed out.

Probe if an I2C device responds with ACK at given 7-bit address.

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

Defined in h1os/hal_spi.h:23

Initializes SPI2 Master host with DMA channel enabled for display communication.

#### Returns
ESP_OK on success, or driver error code.

---

{#hal_spi_deinit}

### hal_spi_deinit

```cpp
esp_err_t hal_spi_deinit(void)
```

Defined in h1os/hal_spi.h:30

Deinitializes SPI2 Master host and releases bus resources.

#### Returns
ESP_OK on success.

---

{#hal_spi_write_cmd}

### hal_spi_write_cmd

```cpp
esp_err_t hal_spi_write_cmd(uint8_t cmd)
```

Defined in h1os/hal_spi.h:39

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

Defined in h1os/hal_spi.h:58

Transmits a full 5000-byte frame buffer via DMA transfer.

#### Returns
ESP_OK on success.

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

Defined in h1os/hal_spi.h:69

Reads data from SSD1681 (e.g.

on-glass thermal sensor Cmd 0x1B).

#### Returns
ESP_OK on success.

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

Defined in h1os/sub_nvs.h:28

Initialize the NVS flash storage subsystem.

#### Returns
ESP_OK on success, or flash partition error.

#### Returns
ESP_OK on success, or an error code.

---

{#sub_nvs_set_str}

### sub_nvs_set_str

```cpp
esp_err_t sub_nvs_set_str(const char * key, const char * value)
```

Defined in h1os/sub_nvs.h:38

Store a null-terminated string value in NVS.

Store a string value in NVS.

#### Returns
ESP_OK on success.

Store a null-terminated string value in NVS.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `key` | `const char *` | Parameter key. |
| `value` | `const char *` | Parameter value. |

---

{#sub_nvs_get_str}

### sub_nvs_get_str

```cpp
esp_err_t sub_nvs_get_str(const char * key, char * out_val, size_t max_len)
```

Defined in h1os/sub_nvs.h:49

Retrieve a string value from NVS.

#### Returns
ESP_OK on success, or ESP_ERR_NVS_NOT_FOUND if key not present.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `key` | `const char *` | Parameter key. |
| `out_val` | `char *` | Parameter out_val. |
| `max_len` | `size_t` | Parameter max_len. |

---

{#sub_nvs_set_u32}

### sub_nvs_set_u32

```cpp
esp_err_t sub_nvs_set_u32(const char * key, uint32_t value)
```

Defined in h1os/sub_nvs.h:59

Store an unsigned 32-bit integer in NVS.

#### Returns
ESP_OK on success.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `key` | `const char *` | Parameter key. |
| `value` | `uint32_t` | Parameter value. |

---

{#sub_nvs_get_u32}

### sub_nvs_get_u32

```cpp
esp_err_t sub_nvs_get_u32(const char * key, uint32_t * out_val)
```

Defined in h1os/sub_nvs.h:69

Retrieve an unsigned 32-bit integer from NVS.

#### Returns
ESP_OK on success, or ESP_ERR_NVS_NOT_FOUND.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `key` | `const char *` | Parameter key. |
| `out_val` | `uint32_t *` | Parameter out_val. |

---

{#sub_nvs_set_blob}

### sub_nvs_set_blob

```cpp
esp_err_t sub_nvs_set_blob(const char * key, const void * data, size_t len)
```

Defined in h1os/sub_nvs.h:80

Store a binary blob in NVS.

#### Returns
ESP_OK on success.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `key` | `const char *` | Parameter key. |
| `data` | `const void *` | Parameter data. |
| `len` | `size_t` | Parameter len. |

---

{#sub_nvs_get_blob}

### sub_nvs_get_blob

```cpp
esp_err_t sub_nvs_get_blob(const char * key, void * out_data, size_t * inout_len)
```

Defined in h1os/sub_nvs.h:91

Retrieve a binary blob from NVS.

#### Returns
ESP_OK on success, or ESP_ERR_NVS_NOT_FOUND.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `key` | `const char *` | Parameter key. |
| `out_data` | `void *` | Parameter out_data. |
| `inout_len` | `size_t *` | Parameter inout_len. |

---

{#sub_nvs_erase_key}

### sub_nvs_erase_key

```cpp
esp_err_t sub_nvs_erase_key(const char * key)
```

Defined in h1os/sub_nvs.h:100

Erase a specific key from NVS.

#### Returns
ESP_OK on success.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `key` | `const char *` | Parameter key. |

---

{#sub_nvs_erase_all}

### sub_nvs_erase_all

```cpp
esp_err_t sub_nvs_erase_all(void)
```

Defined in h1os/sub_nvs.h:107

Perform a factory reset wiping the entire H1OS NVS namespace.

#### Returns
ESP_OK on success.

#### Returns
ESP_OK on success, or an error code.

---

{#sub_rtc_init}

### sub_rtc_init

```cpp
esp_err_t sub_rtc_init(void)
```

Defined in h1os/sub_rtc.h:29

Initialize PCF85063A real-time clock over shared I2C bus.

Initialize PCF85063A RTC.

Disables CLKOUT push-pull square wave to eliminate continuous trace leakage, verifies oscillator integrity, and clears residual timer/alarm flags.

#### Returns
ESP_OK on success, or I2C communication error.

Initialize PCF85063A real-time clock over shared I2C bus.

Disables CLKOUT push-pull square wave to eliminate continuous trace leakage, verifies oscillator status, and clears residual timer/alarm flags.

#### Returns
ESP_OK on success, or an I2C communication error.

---

{#sub_rtc_get_time}

### sub_rtc_get_time

```cpp
esp_err_t sub_rtc_get_time(struct tm * out_time)
```

Defined in h1os/sub_rtc.h:38

Read current date and time into POSIX struct tm.

#### Returns
ESP_OK on success, or an error code.

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

Defined in h1os/sub_rtc.h:47

Set RTC calendar date and time.

#### Returns
ESP_OK on success, or an error code.

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

Defined in h1os/sub_rtc.h:58

Arm hardware countdown timer.

Drives open-drain interrupt line GPIO 5 LOW upon expiration to wake platform.

#### Returns
ESP_OK on success, or error code.

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

Defined in h1os/sub_rtc.h:65

Cancel and disarm hardware countdown timer.

#### Returns
ESP_OK on success.

---

{#sub_rtc_get_remaining_seconds}

### sub_rtc_get_remaining_seconds

```cpp
esp_err_t sub_rtc_get_remaining_seconds(uint32_t * out_sec)
```

Defined in h1os/sub_rtc.h:76

Read remaining seconds on the active countdown timer.

Used for zero-hour collision avoidance.

#### Returns
ESP_OK on success, or error code.

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

Defined in h1os/sub_rtc.h:88

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

Defined in hal_i2c.c:27

Initializes the shared I2C master bus hardware.

Initialize shared I2C master bus hardware.

Installs ESP-IDF I2C driver on GPIO 47 / GPIO 48 and creates recursive mutex.

#### Returns
ESP_OK on success, or driver error code.

Initializes the shared I2C master bus hardware.

Installs ESP-IDF I2C driver on GPIO 47 / GPIO 48 and creates recursive mutex.

#### Returns

* ESP_OK: Bus initialized and mutex created successfully.
* ESP_ERR_INVALID_STATE: Driver already installed.
* ESP_FAIL: Hardware initialization failed.

---

{#hal_i2c_deinit-1}

### hal_i2c_deinit

```cpp
esp_err_t hal_i2c_deinit(void)
```

Defined in hal_i2c.c:71

Deinitializes the shared I2C master bus and releases mutex.

Deinitialize shared I2C master bus and release mutex.

#### Returns
ESP_OK on success.

Deinitializes the shared I2C master bus and releases mutex.

#### Returns
ESP_OK on success.

---

{#hal_i2c_write-1}

### hal_i2c_write

```cpp
esp_err_t hal_i2c_write(uint8_t dev_addr, const uint8_t * write_data, size_t write_len, uint32_t timeout_ms)
```

Defined in hal_i2c.c:100

Executes an atomic register write transaction over I2C.

Execute an atomic register write transaction over I2C.

#### Returns
ESP_OK on success, ESP_ERR_TIMEOUT, or NACK error.

Executes an atomic register write transaction over I2C.

#### Returns

* ESP_OK: Write transaction acknowledged.
* ESP_ERR_TIMEOUT: Bus transaction timed out.
* ESP_ERR_INVALID_ARG: Null pointer.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `dev_addr` | `uint8_t` | 7-bit I2C device address. |
| `write_data` | `const uint8_t *` | Pointer to data buffer to transmit. Must not be NULL. |
| `write_len` | `size_t` | Length of write buffer in bytes. |
| `timeout_ms` | `uint32_t` | Timeout budget in milliseconds. |

---

{#hal_i2c_read-1}

### hal_i2c_read

```cpp
esp_err_t hal_i2c_read(uint8_t dev_addr, uint8_t * read_data, size_t read_len, uint32_t timeout_ms)
```

Defined in hal_i2c.c:143

Executes an atomic register read transaction over I2C.

Execute an atomic register read transaction over I2C.

#### Returns
ESP_OK on success, ESP_ERR_TIMEOUT, or NACK error.

Executes an atomic register read transaction over I2C.

#### Returns

* ESP_OK: Read transaction completed successfully.
* ESP_ERR_TIMEOUT: Bus transaction timed out.
* ESP_ERR_INVALID_ARG: Null pointer.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `dev_addr` | `uint8_t` | 7-bit I2C device address. |
| `read_data` | `uint8_t *` | Pointer to buffer to receive data. Must not be NULL. |
| `read_len` | `size_t` | Number of bytes to read. |
| `timeout_ms` | `uint32_t` | Timeout budget in milliseconds. |

---

{#hal_i2c_write_read-1}

### hal_i2c_write_read

```cpp
esp_err_t hal_i2c_write_read(uint8_t dev_addr, const uint8_t * write_data, size_t write_len, uint8_t * read_data, size_t read_len, uint32_t timeout_ms)
```

Defined in hal_i2c.c:188

Executes an atomic write-then-read combined transaction (Repeated START).

Execute an atomic write-then-read combined transaction (Repeated START).

#### Returns
ESP_OK on success, ESP_ERR_TIMEOUT, or NACK error.

Executes an atomic write-then-read combined transaction (Repeated START).

#### Returns

* ESP_OK: Combined transaction completed successfully.
* ESP_ERR_TIMEOUT: Bus transaction timed out.
* ESP_ERR_INVALID_ARG: Null pointer.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `dev_addr` | `uint8_t` | 7-bit I2C device address. |
| `write_data` | `const uint8_t *` | Register address or command bytes to write. Must not be NULL. |
| `write_len` | `size_t` | Number of bytes to write. |
| `read_data` | `uint8_t *` | Destination buffer for read bytes. Must not be NULL. |
| `read_len` | `size_t` | Number of bytes to read. |
| `timeout_ms` | `uint32_t` | Timeout budget in milliseconds. |

---

{#hal_i2c_probe-1}

### hal_i2c_probe

```cpp
esp_err_t hal_i2c_probe(uint8_t dev_addr)
```

Defined in hal_i2c.c:229

Probes if an I2C device with given 7-bit address responds on the bus.

Probe if an I2C device responds with ACK at given 7-bit address.

#### Returns
ESP_OK if device ACKed, ESP_ERR_NOT_FOUND or other error on NACK/timeout.

Probes if an I2C device with given 7-bit address responds on the bus.

#### Returns

* ESP_OK: Device responded with ACK.
* ESP_ERR_NOT_FOUND: Device NACKed address byte.
* ESP_ERR_TIMEOUT: Transaction timed out.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `dev_addr` | `uint8_t` | 7-bit device address to probe. |

---

{#epd_set_cs}

### epd_set_cs

`static` `inline`

```cpp
static inline void epd_set_cs(uint8_t level)
```

Defined in hal_spi.c:30

Epd set cs.

#### Returns
Return value of type static inline void.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `level` | `uint8_t` | Parameter level. |

---

{#epd_set_dc}

### epd_set_dc

`static` `inline`

```cpp
static inline void epd_set_dc(uint8_t level)
```

Defined in hal_spi.c:42

Epd set dc.

#### Returns
Return value of type static inline void.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `level` | `uint8_t` | Parameter level. |

---

{#hal_spi_init-1}

### hal_spi_init

```cpp
esp_err_t hal_spi_init(void)
```

Defined in hal_spi.c:52

Initializes SPI2 Master host with DMA channel enabled for display communication.

#### Returns
ESP_OK on success, or driver error code.

---

{#hal_spi_deinit-1}

### hal_spi_deinit

```cpp
esp_err_t hal_spi_deinit(void)
```

Defined in hal_spi.c:134

Deinitializes SPI2 Master host and releases bus resources.

#### Returns
ESP_OK on success.

---

{#hal_spi_write_cmd-1}

### hal_spi_write_cmd

```cpp
esp_err_t hal_spi_write_cmd(uint8_t cmd)
```

Defined in hal_spi.c:162

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

Defined in hal_spi.c:190

Transmits data bytes to the SSD1681 controller (DC = 1).

#### Returns
ESP_OK on success.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `data` | `const uint8_t *` | Pointer to buffer containing payload. Must not be NULL. |
| `len` | `size_t` | Length of data in bytes. |

---

{#hal_spi_write_frame_dma-1}

### hal_spi_write_frame_dma

```cpp
esp_err_t hal_spi_write_frame_dma(const uint8_t * frame_buffer)
```

Defined in hal_spi.c:216

Transmits a full 5000-byte frame buffer via DMA transfer.

#### Returns
ESP_OK on success.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `frame_buffer` | `const uint8_t *` | Pointer to 5000-byte buffer. Must not be NULL. |

---

{#hal_spi_read_data-1}

### hal_spi_read_data

```cpp
esp_err_t hal_spi_read_data(uint8_t cmd, uint8_t * out_data, size_t len)
```

Defined in hal_spi.c:246

Reads data from SSD1681 (e.g.

on-glass thermal sensor Cmd 0x1B).

#### Returns
ESP_OK on success.

on-glass thermal sensor Cmd 0x1B).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `cmd` | `uint8_t` | Command to write before reading. |
| `out_data` | `uint8_t *` | Buffer to receive read bytes. Must not be NULL. |
| `len` | `size_t` | Number of bytes to read. |

---

{#sub_nvs_init-1}

### sub_nvs_init

```cpp
esp_err_t sub_nvs_init(void)
```

Defined in sub_nvs.c:26

Initialize the NVS flash storage subsystem.

#### Returns
ESP_OK on success, or an error code.

#### Returns
ESP_OK on success, or flash partition error.

---

{#sub_nvs_set_str-1}

### sub_nvs_set_str

```cpp
esp_err_t sub_nvs_set_str(const char * key, const char * value)
```

Defined in sub_nvs.c:62

Store a string value in NVS.

Store a null-terminated string value in NVS.

#### Returns
ESP_OK on success, or an error code.

Store a string value in NVS.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `key` | `const char *` | Unique key identifier string. |
| `value` | `const char *` | String payload to persist. |

---

{#sub_nvs_get_str-1}

### sub_nvs_get_str

```cpp
esp_err_t sub_nvs_get_str(const char * key, char * out_val, size_t max_len)
```

Defined in sub_nvs.c:91

Retrieve a string value from NVS.

#### Returns
ESP_OK on success, or an error code.

#### Returns
ESP_OK on success, or ESP_ERR_NVS_NOT_FOUND if key not present.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `key` | `const char *` | Unique key identifier string. |
| `out_val` | `char *` | Destination character buffer. |
| `max_len` | `size_t` | Capacity of destination buffer. |

---

{#sub_nvs_set_u32-1}

### sub_nvs_set_u32

```cpp
esp_err_t sub_nvs_set_u32(const char * key, uint32_t value)
```

Defined in sub_nvs.c:117

Store an unsigned 32-bit integer in NVS.

#### Returns
ESP_OK on success, or an error code.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `key` | `const char *` | Unique key identifier string. |
| `value` | `uint32_t` | Integer value to persist. |

---

{#sub_nvs_get_u32-1}

### sub_nvs_get_u32

```cpp
esp_err_t sub_nvs_get_u32(const char * key, uint32_t * out_val)
```

Defined in sub_nvs.c:145

Retrieve an unsigned 32-bit integer from NVS.

#### Returns
ESP_OK on success, or an error code.

#### Returns
ESP_OK on success, or ESP_ERR_NVS_NOT_FOUND.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `key` | `const char *` | Unique key identifier string. |
| `out_val` | `uint32_t *` | Destination pointer for integer. |

---

{#sub_nvs_set_blob-1}

### sub_nvs_set_blob

```cpp
esp_err_t sub_nvs_set_blob(const char * key, const void * data, size_t len)
```

Defined in sub_nvs.c:171

Store a binary blob in NVS.

#### Returns
ESP_OK on success, or an error code.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `key` | `const char *` | Unique key identifier string. |
| `data` | `const void *` | Pointer to binary data buffer. |
| `len` | `size_t` | Length of data in bytes. |

---

{#sub_nvs_get_blob-1}

### sub_nvs_get_blob

```cpp
esp_err_t sub_nvs_get_blob(const char * key, void * out_data, size_t * inout_len)
```

Defined in sub_nvs.c:200

Retrieve a binary blob from NVS.

#### Returns
ESP_OK on success, or an error code.

#### Returns
ESP_OK on success, or ESP_ERR_NVS_NOT_FOUND.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `key` | `const char *` | Unique key identifier string. |
| `out_data` | `void *` | Destination buffer for binary data. |
| `inout_len` | `size_t *` | On entry: capacity of buffer; on exit: actual read bytes. |

---

{#sub_nvs_erase_key-1}

### sub_nvs_erase_key

```cpp
esp_err_t sub_nvs_erase_key(const char * key)
```

Defined in sub_nvs.c:224

Erase a specific key from NVS.

#### Returns
ESP_OK on success, or an error code.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `key` | `const char *` | Key identifier string to erase. |

---

{#sub_nvs_erase_all-1}

### sub_nvs_erase_all

```cpp
esp_err_t sub_nvs_erase_all(void)
```

Defined in sub_nvs.c:249

Perform a factory reset wiping the entire H1OS NVS namespace.

#### Returns
ESP_OK on success, or an error code.

#### Returns
ESP_OK on success.

---

{#bcd2dec}

### bcd2dec

`static` `inline`

```cpp
static inline uint8_t bcd2dec(uint8_t val)
```

Defined in sub_rtc.c:61

Bcd2dec.

#### Returns
Return value of type static inline uint8_t.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `val` | `uint8_t` | Parameter val. |

---

{#dec2bcd}

### dec2bcd

`static` `inline`

```cpp
static inline uint8_t dec2bcd(uint8_t val)
```

Defined in sub_rtc.c:73

Dec2bcd.

#### Returns
Return value of type static inline uint8_t.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `val` | `uint8_t` | Parameter val. |

---

{#pcf85063_read_reg}

### pcf85063_read_reg

`static`

```cpp
static esp_err_t pcf85063_read_reg(uint8_t reg, uint8_t * val, size_t len)
```

Defined in sub_rtc.c:87

Pcf85063 read reg.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `reg` | `uint8_t` | Parameter reg. |
| `val` | `uint8_t *` | Parameter val. |
| `len` | `size_t` | Parameter len. |

---

{#pcf85063_write_reg}

### pcf85063_write_reg

`static`

```cpp
static esp_err_t pcf85063_write_reg(uint8_t reg, const uint8_t * val, size_t len)
```

Defined in sub_rtc.c:101

Pcf85063 write reg.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `reg` | `uint8_t` | Parameter reg. |
| `val` | `const uint8_t *` | Parameter val. |
| `len` | `size_t` | Parameter len. |

---

{#pcf85063_write_reg_u8}

### pcf85063_write_reg_u8

`static`

```cpp
static esp_err_t pcf85063_write_reg_u8(uint8_t reg, uint8_t val)
```

Defined in sub_rtc.c:121

Pcf85063 write reg u8.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `reg` | `uint8_t` | Parameter reg. |
| `val` | `uint8_t` | Parameter val. |

---

{#sub_rtc_init-1}

### sub_rtc_init

```cpp
esp_err_t sub_rtc_init(void)
```

Defined in sub_rtc.c:133

Initialize PCF85063A RTC.

Initialize PCF85063A real-time clock over shared I2C bus.

Disables CLKOUT push-pull square wave to eliminate continuous trace leakage, verifies oscillator status, and clears residual timer/alarm flags.

#### Returns
ESP_OK on success, or an I2C communication error.

Initialize PCF85063A RTC.

Disables CLKOUT push-pull square wave to eliminate continuous trace leakage, verifies oscillator integrity, and clears residual timer/alarm flags.

#### Returns
ESP_OK on success, or I2C communication error.

---

{#sub_rtc_get_time-1}

### sub_rtc_get_time

```cpp
esp_err_t sub_rtc_get_time(struct tm * out_time)
```

Defined in sub_rtc.c:183

Read current date and time into POSIX struct tm.

#### Returns
ESP_OK on success, or an error code.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_time` | `struct tm *` | Pointer to struct tm populated with current RTC timestamp. Must not be NULL. |

---

{#sub_rtc_set_time-1}

### sub_rtc_set_time

```cpp
esp_err_t sub_rtc_set_time(const struct tm * time)
```

Defined in sub_rtc.c:214

Set RTC calendar date and time.

#### Returns
ESP_OK on success, or an error code.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `time` | `const struct tm *` | Pointer to struct tm containing target timestamp. Must not be NULL. |

---

{#sub_rtc_arm_countdown-1}

### sub_rtc_arm_countdown

```cpp
esp_err_t sub_rtc_arm_countdown(uint32_t seconds)
```

Defined in sub_rtc.c:251

Arm hardware countdown timer.

Drives open-drain interrupt line GPIO 5 LOW upon expiration.

#### Returns
ESP_OK on success, or an error code.

Drives open-drain interrupt line GPIO 5 LOW upon expiration to wake platform.

#### Returns
ESP_OK on success, or error code.

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

Defined in sub_rtc.c:322

Cancel and disarm hardware countdown timer.

#### Returns
ESP_OK on success.

---

{#sub_rtc_get_remaining_seconds-1}

### sub_rtc_get_remaining_seconds

```cpp
esp_err_t sub_rtc_get_remaining_seconds(uint32_t * out_sec)
```

Defined in sub_rtc.c:341

Read remaining seconds on the active countdown timer.

Used for zero-hour collision avoidance.

#### Returns
ESP_OK on success, or an error code.

Used for zero-hour collision avoidance.

#### Returns
ESP_OK on success, or error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_sec` | `uint32_t *` | Destination pointer for remaining seconds. Must not be NULL. |

---

{#sub_rtc_get_and_clear_interrupts-1}

### sub_rtc_get_and_clear_interrupts

```cpp
esp_err_t sub_rtc_get_and_clear_interrupts(bool * out_alarm, bool * out_timer)
```

Defined in sub_rtc.c:381

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

Defined in h1os/h1os_lvgl.h:33

Initialize LVGL v9 graphics subsystem, 1-bit display buffer, and keypad input driver.

Configures the bilevel draw buffer, registers the display flush callback, and sets up keypad input navigation.

#### Returns

* ESP_OK: LVGL core initialized successfully.
* ESP_ERR_NO_MEM: Insufficient memory for draw buffer allocation.

#### Returns
ESP_OK on success, or an error code.

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

Defined in h1os/h1os_lvgl.h:40

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

Defined in h1os/h1os_lvgl.h:54

Start the LVGL background FreeRTOS task.

Spawns the dedicated presentation task pinned to Core 1 for decoupled UI rendering.

#### Returns

* ESP_OK: Task created and running.
* ESP_FAIL: Task creation failed.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `priority` | `int` | FreeRTOS task priority (e.g. 4). |
| `core_id` | `int` | Parameter core_id. |

---

{#h1os_lvgl_stop}

### h1os_lvgl_stop

```cpp
esp_err_t h1os_lvgl_stop(void)
```

Defined in h1os/h1os_lvgl.h:64

Stop the LVGL background task.

Signals the event loop to terminate cleanly and waits for task exit.

#### Returns

* ESP_OK: Task stopped successfully.

Safely handles being called from within an LVGL input callback on the LVGL task thread itself (e.g. long-press shutdown) without self-deletion.

#### Returns
ESP_OK on success, or an error code.

---

{#h1os_lvgl_lock}

### h1os_lvgl_lock

```cpp
bool h1os_lvgl_lock(uint32_t timeout_ms)
```

Defined in h1os/h1os_lvgl.h:76

Acquire LVGL reentrant mutex lock.

Must be acquired before creating, modifying, or deleting any LVGL widgets or objects from tasks other than the LVGL event loop.

#### Returns
True if mutex was successfully acquired within timeout, false otherwise.

#### Returns
True on success, false otherwise.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ms` | `uint32_t` | Parameter timeout_ms. |

---

{#h1os_lvgl_unlock}

### h1os_lvgl_unlock

```cpp
void h1os_lvgl_unlock(void)
```

Defined in h1os/h1os_lvgl.h:83

Release LVGL reentrant mutex lock.

Releases the mutex acquired via [h1os_lvgl_lock()](#h1os_lvgl_lock).

---

{#h1os_lvgl_has_pending_tasks}

### h1os_lvgl_has_pending_tasks

```cpp
bool h1os_lvgl_has_pending_tasks(void)
```

Defined in h1os/h1os_lvgl.h:90

Check if the LVGL display pipeline has pending render/flush tasks.

#### Returns
True if display driver is currently flushing or widgets are invalidated.

#### Returns
True on success, false otherwise.

---

{#h1os_lvgl_get_indev}

### h1os_lvgl_get_indev

```cpp
lv_indev_t * h1os_lvgl_get_indev(void)
```

Defined in h1os/h1os_lvgl.h:97

Retrieve the LVGL keypad input device handle.

#### Returns
Pointer to registered keypad indev instance for focus group binding.

---

{#h1os_time_set_timezone}

### h1os_time_set_timezone

```cpp
esp_err_t h1os_time_set_timezone(const char * tz_str)
```

Defined in h1os/h1os_time.h:60

Configure POSIX timezone string for local time conversions.

Configure POSIX timezone string.

#### Returns

* ESP_OK: Timezone configured and applied.
* ESP_ERR_INVALID_ARG: Null pointer provided.

Configure POSIX timezone string for local time conversions.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `tz_str` | `const char *` | Parameter tz_str. |

---

{#h1os_time_register_sync_cb}

### h1os_time_register_sync_cb

```cpp
esp_err_t h1os_time_register_sync_cb(h1os_time_sync_cb_t cb, void * user_data)
```

Defined in h1os/h1os_time.h:70

Register external time synchronization provider callback.

Register external time sync callback.

#### Returns
ESP_OK on success.

Register external time synchronization provider callback.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `cb` | [`h1os_time_sync_cb_t`](#h1os_time_sync_cb_t) | Parameter cb. |
| `user_data` | `void *` | Parameter user_data. |

---

{#h1os_time_sync_now}

### h1os_time_sync_now

```cpp
esp_err_t h1os_time_sync_now(uint32_t timeout_ms)
```

Defined in h1os/h1os_time.h:79

Execute immediate time synchronization via registered provider.

Trigger time synchronization using registered callback.

#### Returns
ESP_OK on success, or provider error code.

Execute immediate time synchronization via registered provider.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ms` | `uint32_t` | Parameter timeout_ms. |

---

{#h1os_time_sync_system_to_rtc}

### h1os_time_sync_system_to_rtc

```cpp
esp_err_t h1os_time_sync_system_to_rtc(void)
```

Defined in h1os/h1os_time.h:86

Synchronize internal POSIX system clock to external PCF85063A hardware RTC.

Synchronize internal system clock into PCF85063A RTC hardware.

#### Returns
ESP_OK on success, or I2C bus communication error.

Synchronize internal POSIX system clock to external PCF85063A hardware RTC.

#### Returns
ESP_OK on success, or an error code.

---

{#h1os_time_sync_rtc_to_system}

### h1os_time_sync_rtc_to_system

```cpp
esp_err_t h1os_time_sync_rtc_to_system(void)
```

Defined in h1os/h1os_time.h:93

Synchronize external PCF85063A hardware RTC to internal POSIX system clock.

Synchronize PCF85063A RTC hardware into internal POSIX system clock.

#### Returns
ESP_OK on success, or I2C bus communication error.

Synchronize external PCF85063A hardware RTC to internal POSIX system clock.

#### Returns
ESP_OK on success, or an error code.

---

{#h1os_time_get_formatted}

### h1os_time_get_formatted

```cpp
esp_err_t h1os_time_get_formatted(h1os_time_format_t fmt, char * dest, size_t max_len)
```

Defined in h1os/h1os_time.h:104

Format current local time into destination buffer.

#### Returns
ESP_OK on success, or ESP_ERR_INVALID_ARG if buffer too small.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `fmt` | [`h1os_time_format_t`](#h1os_time_format_t) | Parameter fmt. |
| `dest` | `char *` | Parameter dest. |
| `max_len` | `size_t` | Parameter max_len. |

---

{#h1os_time_get_date_formatted}

### h1os_time_get_date_formatted

```cpp
esp_err_t h1os_time_get_date_formatted(h1os_date_format_t fmt, char * dest, size_t max_len)
```

Defined in h1os/h1os_time.h:115

Format current local calendar date into destination buffer.

Format current local date into destination buffer.

#### Returns
ESP_OK on success, or ESP_ERR_INVALID_ARG if buffer too small.

Format current local calendar date into destination buffer.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `fmt` | [`h1os_date_format_t`](#h1os_date_format_t) | Parameter fmt. |
| `dest` | `char *` | Parameter dest. |
| `max_len` | `size_t` | Parameter max_len. |

---

{#hal_flash_init}

### hal_flash_init

```cpp
esp_err_t hal_flash_init(void)
```

Defined in h1os/hal_flash.h:27

Initialize raw flash partition driver for display framebuffer persistence.

Finds and verifies the dedicated "epd_frame" partition.

Locates the dedicated 16KB "epd_frame" partition in SPI flash.

#### Returns

* ESP_OK: Partition located and validated.
* ESP_ERR_NOT_FOUND: "epd_frame" partition not present in partition table.

Initialize raw flash partition driver for display framebuffer persistence.

#### Returns
ESP_OK on success, or ESP_ERR_NOT_FOUND if partition is missing.

---

{#hal_flash_read_frame}

### hal_flash_read_frame

```cpp
esp_err_t hal_flash_read_frame(uint8_t * out_buffer, size_t len)
```

Defined in h1os/hal_flash.h:40

Read preserved 1-bit frame data from SPI flash partition.

Reads the persisted 5000-byte EPD frame from flash.

#### Returns

* ESP_OK: Frame read successfully.
* ESP_ERR_INVALID_ARG: Null pointer or buffer overflow.
* ESP_FAIL: Flash read error.

Read preserved 1-bit frame data from SPI flash partition.

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

Defined in h1os/hal_flash.h:55

Erase and write 1-bit frame data into SPI flash partition.

Erases the partition sector and writes the 5000-byte frame.

Performs sector erase prior to flashing to guarantee bit integrity.

#### Returns

* ESP_OK: Frame written successfully.
* ESP_ERR_INVALID_ARG: Null pointer or invalid length.
* ESP_FAIL: Flash erase or write error.

Erase and write 1-bit frame data into SPI flash partition.

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

Evaluate hardware reset cause and RTC state to determine execution flow.

Inspect system wake source and arbitrate target flow.

#### Returns
Selected execution flow type.

Evaluate hardware reset cause and RTC state to determine execution flow.

#### Returns
Detected flow type.

---

{#orch_flow_is_thermal_lockout}

### orch_flow_is_thermal_lockout

```cpp
bool orch_flow_is_thermal_lockout(void)
```

Defined in h1os/orch_flow.h:44

Check whether thermal self-heating lockout is currently active.

Check whether system is in Thermal Lockout state.

#### Returns
True if radio/CPU self-heating is actively decaying.

Check whether thermal self-heating lockout is currently active.

Returns true until at least two consecutive Flow A samples have settled within SAMPLE_DELTA_GATE_CENTI_C (|temp2 - temp1| <= 0.20 C).

#### Returns
True if settling (lockout), False if board is in thermal steady state.

---

{#orch_flow_query_telemetry}

### orch_flow_query_telemetry

```cpp
esp_err_t orch_flow_query_telemetry(float * out_temp_c, float * out_rh_pct, float * out_dew_c)
```

Defined in h1os/orch_flow.h:55

Query current filtered Tri-Node environmental telemetry.

Query current environmental telemetry directly from factory-calibrated SHTC3 steady-state samples.

#### Returns
ESP_OK on success, or ESP_ERR_INVALID_ARG if any pointer is NULL.

Query current filtered Tri-Node environmental telemetry.

The SHTC3 is factory-calibrated and requires no synthetic offsets, reconstitutions, or taring. When consecutive Flow A samples satisfy |temp2 - temp1| <= SAMPLE_DELTA_GATE_CENTI_C, the board is at thermal steady state and the SHTC3 reading is trusted directly. The EPD glass and MCU die sensors serve strictly to verify that the SHTC3 is operating within a normal range.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_temp_c` | `float *` | Trusted SHTC3 ambient temperature in Celsius. |
| `out_rh_pct` | `float *` | Trusted SHTC3 ambient relative humidity in percent. |
| `out_dew_c` | `float *` | Calculated dew point in Celsius. |

---

{#orch_flow_transition_to_sleep}

### orch_flow_transition_to_sleep

```cpp
esp_err_t orch_flow_transition_to_sleep(uint32_t sleep_sec)
```

Defined in h1os/orch_flow.h:64

Prepare platform subsystems and enter target low-power sleep state.

Execute coordinated sleep transition sequence to deep sleep.

#### Returns
ESP_OK on success.

Prepare platform subsystems and enter target low-power sleep state.

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

Defined in h1os/orch_math.h:25

Calculate saturation vapor pressure using August-Roche-Magnus approximation.

Calculate saturation vapor pressure e_s(T) in hPa.

#### Returns
Saturation vapor pressure in hectopascals (hPa).

Calculate saturation vapor pressure using August-Roche-Magnus approximation.

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

Defined in h1os/orch_math.h:35

Calculate actual water vapor partial pressure from temperature and relative humidity.

Calculate actual water vapor pressure (e) in hPa.

#### Returns
Actual vapor pressure in hectopascals (hPa).

Calculate actual water vapor partial pressure from temperature and relative humidity.

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

Defined in h1os/orch_math.h:45

Calculate dew point temperature from temperature and relative humidity.

Calculate true dew point (T_dew) in Celsius from temperature and relative humidity.

#### Returns
Dew point in degrees Celsius.

Calculate dew point temperature from temperature and relative humidity.

#### Returns
Dew point in Celsius.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `temp_c` | `float` | Measured temperature in Celsius. |
| `rh_pct` | `float` | Measured relative humidity in percent. |

---

{#orch_math_calc_psychrometrics}

### orch_math_calc_psychrometrics

```cpp
void orch_math_calc_psychrometrics(float temp_c, float rh_pct, float * out_vp_hpa, float * out_dew_c)
```

Defined in h1os/orch_math.h:55

Calculate vapor pressure and dew point directly from factory-calibrated SHTC3 readings.

Calculate vapor pressure (e) and dew point (T_dew) directly from factory-calibrated SHTC3 readings.

Calculate vapor pressure and dew point directly from factory-calibrated SHTC3 readings.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `temp_c` | `float` | Settled SHTC3 temperature in Celsius. |
| `rh_pct` | `float` | Settled SHTC3 relative humidity in percent. |
| `out_vp_hpa` | `float *` | Output vapor pressure in hPa (optional, can be NULL). |
| `out_dew_c` | `float *` | Output dew point in Celsius (optional, can be NULL). |

---

{#orch_math_calc_absolute_humidity}

### orch_math_calc_absolute_humidity

```cpp
float orch_math_calc_absolute_humidity(float vapor_pressure_hpa, float amb_temp_c)
```

Defined in h1os/orch_math.h:65

Calculate absolute humidity in grams per cubic meter (g/m³).

Calculate absolute humidity (vapor density) in grams per cubic meter (g/m³).

#### Returns
Absolute humidity in g/m³.

Calculate absolute humidity in grams per cubic meter (g/m³).

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

Defined in h1os/orch_math.h:76

Update an Exponentially Weighted Moving Average (EWMA) filter.

Update continuous recursive EWMA filter.

#### Returns
Updated EWMA value.

Update an Exponentially Weighted Moving Average (EWMA) filter.

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

Defined in h1os/orch_math.h:87

Check if temperature trend has settled onto a stable thermal plateau.

Evaluates whether sensor package has settled to thermal plateau (|initial - current| <= gate_threshold).

#### Returns
True if |initial - current| <= gate_threshold.

Check if temperature trend has settled onto a stable thermal plateau.

Marked RTC_IRAM_ATTR so it can be safely called from the RTC Fast Memory deep sleep wake stub.

#### Returns
True if |initial - current| <= gate_threshold.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `initial_temp_centi_c` | `int16_t` | Previous/reference sample temp (centi-°C). |
| `current_temp_centi_c` | `int16_t` | Current sample temp (centi-°C). |
| `gate_threshold_centi_c` | `int16_t` | Maximum allowable absolute drift (typically 20 centi-°C = 0.20 °C). |

---

{#sub_audio_init}

### sub_audio_init

```cpp
esp_err_t sub_audio_init(uint8_t volume_pct)
```

Defined in h1os/sub_audio.h:40

Initialize ES8311 audio codec and NS4168 amplifier hardware.

Initialize ES8311 codec and NS4168 amplifier.

Configures I2S master bus (16-bit 16kHz mono), performs codec register initialization over shared I2C, and sets up the asynchronous FreeRTOS audio worker task.

#### Returns
ESP_OK on success, or driver error code.

Initialize ES8311 audio codec and NS4168 amplifier hardware.

Configures I2S audio bus and sets codec to active run mode.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `volume_pct` | `uint8_t` | Output volume (0 = Mute, 100 = 0 dB Max). |

---

{#sub_audio_standby}

### sub_audio_standby

```cpp
esp_err_t sub_audio_standby(void)
```

Defined in h1os/sub_audio.h:50

Put audio subsystem into low-power hardware standby.

Put ES8311 codec into ultra-low-power software standby (Reg 0x0D = 0xFC @ <1.0 µA) and pull NS4168 PA_CTRL LOW.

Mutes amplifier (GPIO 46 LOW), disables class-D power gate (GPIO 42 HIGH), and enters software power-down on ES8311.

#### Returns
ESP_OK on success.

Put audio subsystem into low-power hardware standby.

Keeps power rails on so I2C bus is NOT clamped by unpowered chip protection diodes. On unattended deep-sleep wakes where the codec is already in verified standby, bypasses redundant I2C register writes to keep the codec completely undisturbed.

#### Returns
ESP_OK on success, or an error code.

---

{#sub_audio_deinit}

### sub_audio_deinit

```cpp
esp_err_t sub_audio_deinit(void)
```

Defined in h1os/sub_audio.h:57

Deinitialize audio subsystem and release I2S and FreeRTOS resources.

Teardown audio subsystem, stop background worker task, and delete I2S channel.

#### Returns
ESP_OK on success.

Deinitialize audio subsystem and release I2S and FreeRTOS resources.

#### Returns
ESP_OK on success.

---

{#sub_audio_wait_until_ready}

### sub_audio_wait_until_ready

```cpp
esp_err_t sub_audio_wait_until_ready(uint32_t timeout_ms)
```

Defined in h1os/sub_audio.h:66

Block until audio subsystem initialization completes.

Poll ES8311 over I2C to confirm Chip ID (0xFD=0x83, 0xFE=0x11) and wait for Chip State Machine (Reg 0xFC bits 6:4) to exit power-down state S0.

#### Returns
ESP_OK if audio worker is ready, ESP_ERR_TIMEOUT otherwise.

Block until audio subsystem initialization completes.

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

Defined in h1os/sub_audio.h:73

Check if audio subsystem is initialized and ready to accept commands.

Quick status check of whether ES8311 codec is ready.

#### Returns
True if audio worker is operational, false otherwise.

Check if audio subsystem is initialized and ready to accept commands.

#### Returns
true if communication and active CSM state verified.

---

{#sub_audio_play}

### sub_audio_play

```cpp
esp_err_t sub_audio_play(sub_audio_type_t type, const void * data, size_t len)
```

Defined in h1os/sub_audio.h:84

Dispatch audio playback command to background worker task.

Unified asynchronous audio playback dispatcher.

#### Returns
ESP_OK if command was queued to worker, or error code.

Dispatch audio playback command to background worker task.

Enqueues the requested audio command into the background audio worker task.

#### Returns
ESP_OK on success, ESP_ERR_TIMEOUT if queue is full, or ESP_ERR_INVALID_ARG.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `type` | [`sub_audio_type_t`](#sub_audio_type_t) | Type of playback: SUB_AUDIO_TONE, SUB_AUDIO_CHIME, or SUB_AUDIO_PCM. |
| `data` | `const void *` | Parameter data. |
| `len` | `size_t` | Length of data payload in bytes. |

---

{#sub_audio_is_busy}

### sub_audio_is_busy

```cpp
bool sub_audio_is_busy(void)
```

Defined in h1os/sub_audio.h:91

Check if audio playback is actively streaming.

Check if audio playback is currently active or queue has pending items.

#### Returns
True if amplifier is active and audio samples are playing.

Check if audio playback is actively streaming.

#### Returns
true if playing or queued, false if idle in standby.

---

{#sub_audio_wait_idle}

### sub_audio_wait_idle

```cpp
esp_err_t sub_audio_wait_idle(uint32_t timeout_ms)
```

Defined in h1os/sub_audio.h:100

Block until all pending audio commands finish playback and amplifier enters standby.

Wait until background audio worker completes all playback and enters standby.

#### Returns
ESP_OK when playback is idle, ESP_ERR_TIMEOUT on expiration.

Block until all pending audio commands finish playback and amplifier enters standby.

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

Defined in h1os/sub_audio.h:109

Set master audio volume percentage (0..100%).

Set ES8311 DAC output volume percentage (0% = Mute, 100% = 0 dB full-scale).

#### Returns
ESP_OK on success.

Set master audio volume percentage (0..100%).

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

Defined in h1os/sub_audio.h:116

Retrieve current audio volume percentage.

Get currently configured output volume percentage (0 - 100).

#### Returns
Current volume level (0..100%).

Retrieve current audio volume percentage.

#### Returns
Current volume percentage.

---

{#sub_audio_set_low_power_mode}

### sub_audio_set_low_power_mode

```cpp
esp_err_t sub_audio_set_low_power_mode(bool enable)
```

Defined in h1os/sub_audio.h:125

Enable or disable aggressive codec low-power mode.

Configure ES8311 DAC power mode (Low-Power vs Normal).

#### Returns
ESP_OK on success.

Enable or disable aggressive codec low-power mode.

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

Defined in h1os/sub_audio.h:132

Query whether codec low-power mode is enabled.

Query whether audio subsystem is in Low-Power Mode.

#### Returns
True if low-power mode is active.

Query whether codec low-power mode is enabled.

#### Returns
true if Low-Power Mode is active, false if Normal Power Mode.

---

{#sub_power_init}

### sub_power_init

```cpp
esp_err_t sub_power_init(void)
```

Defined in h1os/sub_power.h:36

Initialize battery ADC channel and calibration engine.

Initialize Battery ADC subsystem (ADC1 Channel 3 on GPIO 4 with 12 dB atten and eFuse cal).

Configures ADC1 Channel 3 on GPIO 4 with curve fitting calibration.

#### Returns
ESP_OK on success.

Initialize battery ADC channel and calibration engine.

#### Returns
ESP_OK on success, or an error code.

---

{#sub_power_deinit}

### sub_power_deinit

```cpp
esp_err_t sub_power_deinit(void)
```

Defined in h1os/sub_power.h:43

Deinitialize battery ADC driver.

Deinitialize ADC handles.

#### Returns
ESP_OK on success.

Deinitialize battery ADC driver.

#### Returns
ESP_OK on success.

---

{#sub_power_read_battery}

### sub_power_read_battery

```cpp
esp_err_t sub_power_read_battery(uint16_t * out_mv, uint8_t * out_pct)
```

Defined in h1os/sub_power.h:53

Sample current battery terminal voltage and calculate state-of-charge.

Sample calibrated battery voltage with 16-sample trimmed outlier filtering.

#### Returns
ESP_OK on success.

Sample current battery terminal voltage and calculate state-of-charge.

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

Defined in h1os/sub_power.h:63

Retrieve two-point calibration parameters for ULP coprocessor ADC readings.

Extract linear calibration coefficients (scale and offset) for ULP coprocessor hand-off.

#### Returns
ESP_OK on success.

Retrieve two-point calibration parameters for ULP coprocessor ADC readings.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_scale` | `uint32_t *` | Multiplier scaled by 4096. |
| `out_offset_mv` | `int32_t *` | Voltage offset in millivolts. |

---

{#sub_power_init_ulp}

### sub_power_init_ulp

```cpp
esp_err_t sub_power_init_ulp(uint32_t flow_a_period_sec)
```

Defined in h1os/sub_power.h:72

Initialize ULP-RISC-V coprocessor firmware for background monitoring.

Initialize and start the ULP-RISC-V Coprocessor Reactive Monitor.

#### Returns
ESP_OK on success.

Initialize ULP-RISC-V coprocessor firmware for background monitoring.

Loads the binary into RTC Slow SRAM on cold boot, passes ADC eFuse calibration, configures the periodic wake timer (Flow A period), and arms the coprocessor.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `flow_a_period_sec` | `uint32_t` | Periodic wake interval for Flow A telemetry in seconds. |

---

{#sub_power_set_sleep_slices}

### sub_power_set_sleep_slices

```cpp
void sub_power_set_sleep_slices(uint32_t flow_a_sec, uint32_t flow_b_sec, uint32_t overflow, uint32_t remainder_sec)
```

Defined in h1os/sub_power.h:82

Configure ULP slice parameters prior to entering deep sleep.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `flow_a_sec` | `uint32_t` | Flow A sample interval in seconds. |
| `flow_b_sec` | `uint32_t` | Flow B display refresh interval in seconds. |
| `overflow` | `uint32_t` | Total slice overflow threshold. |
| `remainder_sec` | `uint32_t` | Final remainder slice duration in seconds. |

---

{#sub_power_enter_deep_sleep_mode}

### sub_power_enter_deep_sleep_mode

```cpp
esp_err_t sub_power_enter_deep_sleep_mode(uint32_t sleep_seconds, uint64_t ext1_pins_mask, sub_power_sleep_mode_t mode)
```

Defined in h1os/sub_power.h:93

Enter target deep sleep mode with wake pin configuration.

Configure EXT1 wake sources and enter deep sleep with operational mode arbitration.

#### Returns
ESP_OK on success.

Enter target deep sleep mode with wake pin configuration.

Maintains RTC pad holds on power latch (GPIO 17) and EPD rail (GPIO 6) to keep rails active.

#### Returns
Does not return on success (enters deep sleep).

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `sleep_seconds` | `uint32_t` | Timer duration in seconds (0 = timer disabled). |
| `ext1_pins_mask` | `uint64_t` | Bitmask of RTC GPIO pins for wakeup (e.g. GPIO 0, 18, 5). |
| `mode` | [`sub_power_sleep_mode_t`](#sub_power_sleep_mode_t) | Full cycle or Flow A burst mode. |

---

{#sub_power_enter_deep_sleep}

### sub_power_enter_deep_sleep

```cpp
esp_err_t sub_power_enter_deep_sleep(uint32_t sleep_seconds, uint64_t ext1_pins_mask)
```

Defined in h1os/sub_power.h:103

Enter full cycle deep sleep with wake pin configuration.

Configure EXT1 wake sources and enter deep sleep (defaults to SUB_POWER_SLEEP_FULL_CYCLE).

#### Returns
ESP_OK on success.

Enter full cycle deep sleep with wake pin configuration.

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

Defined in h1os/sub_power.h:108

Cut master power latch (releases GPIO 17 BAT_CTRL).

Power off system completely by releasing battery power latch (GPIO 17).

Cut master power latch (releases GPIO 17 BAT_CTRL).

Used for critical low-battery shutdown or explicit user power-off.

---

{#sub_power_connected_usb}

### sub_power_connected_usb

```cpp
bool sub_power_connected_usb(void)
```

Defined in h1os/sub_power.h:115

Check if USB VBUS connection is actively present.

Check to see if USB is connected.

#### Returns
True if connected to USB power.

Check if USB VBUS connection is actively present.

Used for charger detection.

#### Returns
true if usb is connected, or false if disconnected.

---

{#sub_power_init_dfs}

### sub_power_init_dfs

```cpp
esp_err_t sub_power_init_dfs(sys_clk_mode_t mode)
```

Defined in h1os/sub_power.h:124

Initialize Dynamic Frequency Scaling (DFS) power management.

#### Returns
ESP_OK on success.

Configures CPU frequency scaling based on the selected clock mode. SYS_CLK_MODE_DYNAMIC gates CPU cores to 80 MHz baseline during quiescent periods, allowing transient turbo scaling (CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ) during heavy UI/compute bursts. SYS_CLK_MODE_FIXED_MAX locks CPU cores permanently to maximum clock (CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ). SYS_CLK_MODE_FIXED_MIN locks CPU cores permanently to 80 MHz baseline.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `mode` | [`sys_clk_mode_t`](#sys_clk_mode_t) | Clock scaling mode (SYS_CLK_MODE_DYNAMIC, FIXED_MAX, FIXED_MIN). |

---

{#sub_power_cpu_max_acquire}

### sub_power_cpu_max_acquire

```cpp
esp_err_t sub_power_cpu_max_acquire(void)
```

Defined in h1os/sub_power.h:131

Acquire CPU frequency lock at 240 MHz for compute/display intensive operations.

Acquire 240 MHz CPU performance lock (e.g.

#### Returns
ESP_OK on success.

Acquire CPU frequency lock at 240 MHz for compute/display intensive operations.

during LVGL rendering blitz).

Boosts CPU cores from 80 MHz baseline to 240 MHz turbo clock.

#### Returns
ESP_OK on success.

---

{#sub_power_cpu_max_release}

### sub_power_cpu_max_release

```cpp
esp_err_t sub_power_cpu_max_release(void)
```

Defined in h1os/sub_power.h:138

Release CPU frequency lock, allowing DFS to downclock to 80 MHz.

Release 240 MHz CPU performance lock.

#### Returns
ESP_OK on success.

Release CPU frequency lock, allowing DFS to downclock to 80 MHz.

Allows CPU cores to gate back down to 80 MHz baseline.

#### Returns
ESP_OK on success.

---

{#h1os_time_set_timezone-1}

### h1os_time_set_timezone

```cpp
esp_err_t h1os_time_set_timezone(const char * tz_str)
```

Defined in h1os_time.c:32

Configure POSIX timezone string.

Configure POSIX timezone string for local time conversions.

#### Returns
ESP_OK on success, or an error code.

Configure POSIX timezone string.

#### Returns

* ESP_OK: Timezone configured and applied.
* ESP_ERR_INVALID_ARG: Null pointer provided.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `tz_str` | `const char *` | POSIX TZ format string (e.g. "EST5EDT,M3.2.0,M11.1.0"). |

---

{#h1os_time_register_sync_cb-1}

### h1os_time_register_sync_cb

```cpp
esp_err_t h1os_time_register_sync_cb(h1os_time_sync_cb_t cb, void * user_data)
```

Defined in h1os_time.c:51

Register external time sync callback.

Register external time synchronization provider callback.

#### Returns
ESP_OK on success, or an error code.

Register external time sync callback.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `cb` | [`h1os_time_sync_cb_t`](#h1os_time_sync_cb_t) | Time acquisition callback function pointer. |
| `user_data` | `void *` | User context pointer passed to callback. |

---

{#h1os_time_sync_system_to_rtc-1}

### h1os_time_sync_system_to_rtc

```cpp
esp_err_t h1os_time_sync_system_to_rtc(void)
```

Defined in h1os_time.c:63

Synchronize internal system clock into PCF85063A RTC hardware.

Synchronize internal POSIX system clock to external PCF85063A hardware RTC.

#### Returns
ESP_OK on success, or an error code.

Synchronize internal system clock into PCF85063A RTC hardware.

#### Returns
ESP_OK on success, or I2C bus communication error.

---

{#h1os_time_sync_rtc_to_system-1}

### h1os_time_sync_rtc_to_system

```cpp
esp_err_t h1os_time_sync_rtc_to_system(void)
```

Defined in h1os_time.c:90

Synchronize PCF85063A RTC hardware into internal POSIX system clock.

Synchronize external PCF85063A hardware RTC to internal POSIX system clock.

#### Returns
ESP_OK on success, or an error code.

Synchronize PCF85063A RTC hardware into internal POSIX system clock.

#### Returns
ESP_OK on success, or I2C bus communication error.

---

{#h1os_time_sync_now-1}

### h1os_time_sync_now

```cpp
esp_err_t h1os_time_sync_now(uint32_t timeout_ms)
```

Defined in h1os_time.c:124

Trigger time synchronization using registered callback.

Execute immediate time synchronization via registered provider.

#### Returns
ESP_OK on success, or an error code.

Trigger time synchronization using registered callback.

#### Returns
ESP_OK on success, or provider error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ms` | `uint32_t` | Synchronization timeout in milliseconds. |

---

{#h1os_time_get_formatted-1}

### h1os_time_get_formatted

```cpp
esp_err_t h1os_time_get_formatted(h1os_time_format_t fmt, char * dest, size_t max_len)
```

Defined in h1os_time.c:151

Format current local time into destination buffer.

#### Returns
ESP_OK on success, or an error code.

#### Returns
ESP_OK on success, or ESP_ERR_INVALID_ARG if buffer too small.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `fmt` | [`h1os_time_format_t`](#h1os_time_format_t) | Requested time presentation format. |
| `dest` | `char *` | Pointer to destination character buffer. |
| `max_len` | `size_t` | Capacity of destination buffer in bytes. |

---

{#h1os_time_get_date_formatted-1}

### h1os_time_get_date_formatted

```cpp
esp_err_t h1os_time_get_date_formatted(h1os_date_format_t fmt, char * dest, size_t max_len)
```

Defined in h1os_time.c:192

Format current local date into destination buffer.

Format current local calendar date into destination buffer.

#### Returns
ESP_OK on success, or an error code.

Format current local date into destination buffer.

#### Returns
ESP_OK on success, or ESP_ERR_INVALID_ARG if buffer too small.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `fmt` | [`h1os_date_format_t`](#h1os_date_format_t) | Requested date presentation format. |
| `dest` | `char *` | Pointer to destination character buffer. |
| `max_len` | `size_t` | Capacity of destination buffer in bytes. |

---

{#hal_flash_init-1}

### hal_flash_init

```cpp
esp_err_t hal_flash_init(void)
```

Defined in hal_flash.c:25

Finds and verifies the dedicated "epd_frame" partition.

Initialize raw flash partition driver for display framebuffer persistence.

#### Returns
ESP_OK on success, or ESP_ERR_NOT_FOUND if partition is missing.

Finds and verifies the dedicated "epd_frame" partition.

Locates the dedicated 16KB "epd_frame" partition in SPI flash.

#### Returns

* ESP_OK: Partition located and validated.
* ESP_ERR_NOT_FOUND: "epd_frame" partition not present in partition table.

---

{#hal_flash_read_frame-1}

### hal_flash_read_frame

```cpp
esp_err_t hal_flash_read_frame(uint8_t * out_buffer, size_t len)
```

Defined in hal_flash.c:52

Reads the persisted 5000-byte EPD frame from flash.

Read preserved 1-bit frame data from SPI flash partition.

#### Returns
ESP_OK on success, or flash read error.

Reads the persisted 5000-byte EPD frame from flash.

#### Returns

* ESP_OK: Frame read successfully.
* ESP_ERR_INVALID_ARG: Null pointer or buffer overflow.
* ESP_FAIL: Flash read error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_buffer` | `uint8_t *` | Destination buffer (capacity >= len). Must not be NULL. |
| `len` | `size_t` | Number of bytes to read (typically HAL_EPD_FRAME_SIZE_BYTES). |

---

{#hal_flash_write_frame-1}

### hal_flash_write_frame

```cpp
esp_err_t hal_flash_write_frame(const uint8_t * frame_data, size_t len)
```

Defined in hal_flash.c:76

Erases the partition sector and writes the 5000-byte frame.

Erase and write 1-bit frame data into SPI flash partition.

#### Returns
ESP_OK on success, or flash write error.

Erases the partition sector and writes the 5000-byte frame.

Performs sector erase prior to flashing to guarantee bit integrity.

#### Returns

* ESP_OK: Frame written successfully.
* ESP_ERR_INVALID_ARG: Null pointer or invalid length.
* ESP_FAIL: Flash erase or write error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `frame_data` | `const uint8_t *` | Pointer to 1-bit monochrome packed pixel buffer. |
| `len` | `size_t` | Number of bytes to write (typically HAL_EPD_FRAME_SIZE_BYTES). |

---

{#orch_flow_determine_wakeup-1}

### orch_flow_determine_wakeup

```cpp
orch_flow_type_t orch_flow_determine_wakeup(void)
```

Defined in orch_flow.c:51

Inspect system wake source and arbitrate target flow.

Evaluate hardware reset cause and RTC state to determine execution flow.

#### Returns
Detected flow type.

Inspect system wake source and arbitrate target flow.

#### Returns
Selected execution flow type.

---

{#orch_flow_is_thermal_lockout-1}

### orch_flow_is_thermal_lockout

```cpp
bool orch_flow_is_thermal_lockout(void)
```

Defined in orch_flow.c:113

Check whether system is in Thermal Lockout state.

Check whether thermal self-heating lockout is currently active.

Returns true until at least two consecutive Flow A samples have settled within SAMPLE_DELTA_GATE_CENTI_C (|temp2 - temp1| <= 0.20 C).

#### Returns
True if settling (lockout), False if board is in thermal steady state.

Check whether system is in Thermal Lockout state.

#### Returns
True if radio/CPU self-heating is actively decaying.

---

{#orch_flow_dump_ring_debug}

### orch_flow_dump_ring_debug

`static`

```cpp
static void orch_flow_dump_ring_debug(const volatile orch_persisted_state_t * st)
```

Defined in orch_flow.c:125

Orch flow dump ring debug.

#### Returns
Return value of type static void.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `st` | const volatile [`orch_persisted_state_t`](#orch_persisted_state_t) * | Parameter st. |

---

{#orch_flow_scan_ring_metrics}

### orch_flow_scan_ring_metrics

`static`

```cpp
static void orch_flow_scan_ring_metrics(volatile orch_persisted_state_t * st)
```

Defined in orch_flow.c:161

Orch flow scan ring metrics.

#### Returns
Return value of type static void.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `st` | volatile [`orch_persisted_state_t`](#orch_persisted_state_t) * | Parameter st. |

---

{#orch_flow_query_telemetry-1}

### orch_flow_query_telemetry

```cpp
esp_err_t orch_flow_query_telemetry(float * out_temp_c, float * out_rh_pct, float * out_dew_c)
```

Defined in orch_flow.c:216

Query current environmental telemetry directly from factory-calibrated SHTC3 steady-state samples.

Query current filtered Tri-Node environmental telemetry.

The SHTC3 is factory-calibrated and requires no synthetic offsets, reconstitutions, or taring. When consecutive Flow A samples satisfy |temp2 - temp1| <= SAMPLE_DELTA_GATE_CENTI_C, the board is at thermal steady state and the SHTC3 reading is trusted directly. The EPD glass and MCU die sensors serve strictly to verify that the SHTC3 is operating within a normal range.

#### Returns
ESP_OK on success.

Query current environmental telemetry directly from factory-calibrated SHTC3 steady-state samples.

#### Returns
ESP_OK on success, or ESP_ERR_INVALID_ARG if any pointer is NULL.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_temp_c` | `float *` | Pointer to store ambient temperature in Celsius. |
| `out_rh_pct` | `float *` | Pointer to store ambient relative humidity %. |
| `out_dew_c` | `float *` | Pointer to store calculated dew point in Celsius. |

---

{#orch_flow_quiesce_peripherals}

### orch_flow_quiesce_peripherals

`static`

```cpp
static void orch_flow_quiesce_peripherals(void)
```

Defined in orch_flow.c:337

Orch flow quiesce peripherals.

#### Returns
Return value of type static void.

---

{#orch_flow_execute_sleep}

### orch_flow_execute_sleep

`static`

```cpp
static esp_err_t orch_flow_execute_sleep(uint32_t sleep_sec)
```

Defined in orch_flow.c:360

Orch flow execute sleep.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `sleep_sec` | `uint32_t` | Parameter sleep_sec. |

---

{#orch_flow_transition_to_sleep-1}

### orch_flow_transition_to_sleep

```cpp
esp_err_t orch_flow_transition_to_sleep(uint32_t sleep_sec)
```

Defined in orch_flow.c:409

Execute coordinated sleep transition sequence to deep sleep.

Prepare platform subsystems and enter target low-power sleep state.

#### Returns
ESP_OK on success.

Execute coordinated sleep transition sequence to deep sleep.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `sleep_sec` | `uint32_t` | Target sleep duration in seconds. |

---

{#orch_math_calc_sat_vapor_pressure-1}

### orch_math_calc_sat_vapor_pressure

```cpp
float orch_math_calc_sat_vapor_pressure(float temp_c)
```

Defined in orch_math.c:27

Calculate saturation vapor pressure e_s(T) in hPa.

Calculate saturation vapor pressure using August-Roche-Magnus approximation.

Formula: e_s(T) = 6.112 * exp((17.625 * T) / (243.04 + T))

#### Returns
Saturation vapor pressure in hPa.

Calculate saturation vapor pressure e_s(T) in hPa.

#### Returns
Saturation vapor pressure in hectopascals (hPa).

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `temp_c` | `float` | Temperature in degrees Celsius. |

---

{#orch_math_calc_vapor_pressure-1}

### orch_math_calc_vapor_pressure

```cpp
float orch_math_calc_vapor_pressure(float temp_c, float rh_pct)
```

Defined in orch_math.c:42

Calculate actual water vapor pressure (e) in hPa.

Calculate actual water vapor partial pressure from temperature and relative humidity.

Formula: e = (rh_pct / 100.0) * e_s(temp_c)

#### Returns
Actual water vapor pressure in hPa.

Calculate actual water vapor pressure (e) in hPa.

#### Returns
Actual vapor pressure in hectopascals (hPa).

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `temp_c` | `float` | Temperature in degrees Celsius. |
| `rh_pct` | `float` | Relative humidity percentage (0..100%). |

---

{#orch_math_calc_dew_point-1}

### orch_math_calc_dew_point

```cpp
float orch_math_calc_dew_point(float temp_c, float rh_pct)
```

Defined in orch_math.c:66

Calculate true dew point (T_dew) in Celsius from temperature and relative humidity.

Calculate dew point temperature from temperature and relative humidity.

#### Returns
Dew point in Celsius.

Calculate true dew point (T_dew) in Celsius from temperature and relative humidity.

#### Returns
Dew point in degrees Celsius.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `temp_c` | `float` | Temperature in degrees Celsius. |
| `rh_pct` | `float` | Relative humidity percentage (0..100%). |

---

{#orch_math_calc_psychrometrics-1}

### orch_math_calc_psychrometrics

```cpp
void orch_math_calc_psychrometrics(float temp_c, float rh_pct, float * out_vp_hpa, float * out_dew_c)
```

Defined in orch_math.c:90

Calculate vapor pressure (e) and dew point (T_dew) directly from factory-calibrated SHTC3 readings.

Calculate vapor pressure and dew point directly from factory-calibrated SHTC3 readings.

Calculate vapor pressure (e) and dew point (T_dew) directly from factory-calibrated SHTC3 readings.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `temp_c` | `float` | Settled SHTC3 temperature in Celsius. |
| `rh_pct` | `float` | Settled SHTC3 relative humidity %. |
| `out_vp_hpa` | `float *` | Pointer to store vapor pressure in hPa. |
| `out_dew_c` | `float *` | Pointer to store dew point in Celsius. |

---

{#orch_math_calc_absolute_humidity-1}

### orch_math_calc_absolute_humidity

```cpp
float orch_math_calc_absolute_humidity(float vapor_pressure_hpa, float amb_temp_c)
```

Defined in orch_math.c:111

Calculate absolute humidity (vapor density) in grams per cubic meter (g/m³).

Calculate absolute humidity in grams per cubic meter (g/m³).

Formula: d_v = 216.7 * (e / (273.15 + T_ambient))

#### Returns
Vapor density in g/m³.

Calculate absolute humidity (vapor density) in grams per cubic meter (g/m³).

#### Returns
Absolute humidity in g/m³.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `vapor_pressure_hpa` | `float` | Water vapor pressure in hPa. |
| `amb_temp_c` | `float` | Ambient temperature in Celsius. |

---

{#orch_math_update_ewma-1}

### orch_math_update_ewma

```cpp
float orch_math_update_ewma(float current_sample, float previous_ewma, float alpha)
```

Defined in orch_math.c:132

Update continuous recursive EWMA filter.

Update an Exponentially Weighted Moving Average (EWMA) filter.

S_t = alpha * X_t + (1 - alpha) * S_{t-1}

#### Returns
Filtered result.

Update continuous recursive EWMA filter.

#### Returns
Updated EWMA value.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `current_sample` | `float` | New sample value. |
| `previous_ewma` | `float` | Previous EWMA value. |
| `alpha` | `float` | Smoothing factor (0.0 to 1.0). |

---

{#orch_math_is_plateau_settled-1}

### orch_math_is_plateau_settled

```cpp
bool RTC_IRAM_ATTR orch_math_is_plateau_settled(int16_t initial_temp_centi_c, int16_t current_temp_centi_c, int16_t gate_threshold_centi_c)
```

Defined in orch_math.c:156

Evaluates whether sensor package has settled to thermal plateau (|initial - current| <= gate_threshold).

Check if temperature trend has settled onto a stable thermal plateau.

Marked RTC_IRAM_ATTR so it can be safely called from the RTC Fast Memory deep sleep wake stub.

#### Returns
True if |initial - current| <= gate_threshold.

Evaluates whether sensor package has settled to thermal plateau (|initial - current| <= gate_threshold).

#### Returns
True if |initial - current| <= gate_threshold.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `initial_temp_centi_c` | `int16_t` | Initial reference temperature in centi-degrees Celsius. |
| `current_temp_centi_c` | `int16_t` | Current sampled temperature in centi-degrees Celsius. |
| `gate_threshold_centi_c` | `int16_t` | Maximum allowable absolute delta in centi-degrees Celsius. |

---

{#audio_cpu_max_acquire}

### audio_cpu_max_acquire

`static` `inline`

```cpp
static inline void audio_cpu_max_acquire(void)
```

Defined in sub_audio.c:103

Acquire 240 MHz CPU frequency lock for I2S/APB clock stability.

---

{#audio_cpu_max_release}

### audio_cpu_max_release

`static` `inline`

```cpp
static inline void audio_cpu_max_release(void)
```

Defined in sub_audio.c:118

Release 240 MHz CPU frequency lock.

---

{#volume_pct_to_es8311_reg}

### volume_pct_to_es8311_reg

`static` `inline`

```cpp
static inline uint8_t volume_pct_to_es8311_reg(uint8_t pct)
```

Defined in sub_audio.c:252

Volume pct to es8311 reg.

#### Returns
Return value of type static inline uint8_t.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `pct` | `uint8_t` | Parameter pct. |

---

{#audio_worker_task}

### audio_worker_task

`static`

```cpp
static void audio_worker_task(void * pvParameters)
```

Defined in sub_audio.c:847

Audio worker task.

#### Returns
Return value of type static void.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `pvParameters` | `void *` | Parameter pvParameters. |

---

{#sub_audio_park_warm}

### sub_audio_park_warm

`static`

```cpp
static esp_err_t sub_audio_park_warm(bool enable)
```

Defined in sub_audio.c:575

Control NS4168 Class-D amplifier hardware mute state (HAL_PIN_PA_CTRL / GPIO 46).

NS4168 hardware requires minimum 120 ms startup when unmuting (PA_CTRL -> 1) and minimum 80 ms shutdown when muting (PA_CTRL -> 0).

#### Returns
ESP_OK on success.

---

{#es8311_write_reg}

### es8311_write_reg

`static`

```cpp
static esp_err_t es8311_write_reg(uint8_t reg, uint8_t val)
```

Defined in sub_audio.c:269

Es8311 write reg.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `reg` | `uint8_t` | Parameter reg. |
| `val` | `uint8_t` | Parameter val. |

---

{#es8311_read_reg}

### es8311_read_reg

`static`

```cpp
static esp_err_t es8311_read_reg(uint8_t reg, uint8_t * val)
```

Defined in sub_audio.c:283

Es8311 read reg.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `reg` | `uint8_t` | Parameter reg. |
| `val` | `uint8_t *` | Parameter val. |

---

{#sub_audio_read_chip_id}

### sub_audio_read_chip_id

`static`

```cpp
static esp_err_t sub_audio_read_chip_id(uint16_t * chip_id)
```

Defined in sub_audio.c:295

Sub audio read chip id.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `chip_id` | `uint16_t *` | Pointer to store 16-bit chip ID. |

---

{#sub_audio_flush_frame}

### sub_audio_flush_frame

`static`

```cpp
static esp_err_t __unused sub_audio_flush_frame(void)
```

Defined in sub_audio.c:320

Sub audio flush frame (single zero-frame write serving as valid I2S transfer pipeline indicator).

#### Returns
ESP_OK on success, or an error code.

---

{#sub_audio_wait_until_ready-1}

### sub_audio_wait_until_ready

```cpp
esp_err_t sub_audio_wait_until_ready(uint32_t timeout_ms)
```

Defined in sub_audio.c:344

Poll ES8311 over I2C to confirm Chip ID (0xFD=0x83, 0xFE=0x11) and wait for Chip State Machine (Reg 0xFC bits 6:4) to exit power-down state S0.

Block until audio subsystem initialization completes.

#### Returns
ESP_OK if codec is verified and in active CSM state, or error.

Poll ES8311 over I2C to confirm Chip ID (0xFD=0x83, 0xFE=0x11) and wait for Chip State Machine (Reg 0xFC bits 6:4) to exit power-down state S0.

#### Returns
ESP_OK if audio worker is ready, ESP_ERR_TIMEOUT otherwise.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ms` | `uint32_t` | Maximum time to wait in milliseconds. |

---

{#sub_audio_is_ready-1}

### sub_audio_is_ready

```cpp
bool sub_audio_is_ready(void)
```

Defined in sub_audio.c:374

Quick status check of whether ES8311 codec is ready.

Check if audio subsystem is initialized and ready to accept commands.

#### Returns
true if communication and active CSM state verified.

Quick status check of whether ES8311 codec is ready.

#### Returns
True if audio worker is operational, false otherwise.

---

{#es8311_write_table}

### es8311_write_table

`static`

```cpp
static esp_err_t es8311_write_table(const es8311_reg_entry_t * table, size_t count)
```

Defined in sub_audio.c:387

Es8311 write table.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `table` | const [`es8311_reg_entry_t`](#es8311_reg_entry_t) * | Parameter table. |
| `count` | `size_t` | Parameter count. |

---

{#es8311_init_dac_registers}

### es8311_init_dac_registers

`static`

```cpp
static esp_err_t es8311_init_dac_registers(void)
```

Defined in sub_audio.c:401

Initialize es8311_init_dac_registers module resources.

#### Returns
ESP_OK on success, or an error code.

---

{#sub_audio_init-1}

### sub_audio_init

```cpp
esp_err_t sub_audio_init(uint8_t volume_pct)
```

Defined in sub_audio.c:425

Initialize ES8311 codec and NS4168 amplifier.

Initialize ES8311 audio codec and NS4168 amplifier hardware.

Configures I2S audio bus and sets codec to active run mode.

#### Returns
ESP_OK on success, or an error code.

Initialize ES8311 codec and NS4168 amplifier.

Configures I2S master bus (16-bit 16kHz mono), performs codec register initialization over shared I2C, and sets up the asynchronous FreeRTOS audio worker task.

#### Returns
ESP_OK on success, or driver error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `volume_pct` | `uint8_t` | Output volume (0 = Mute, 100 = 0 dB Max). |

---

{#sub_audio_standby-1}

### sub_audio_standby

```cpp
esp_err_t sub_audio_standby(void)
```

Defined in sub_audio.c:602

Put ES8311 codec into ultra-low-power software standby (Reg 0x0D = 0xFC @ <1.0 µA) and pull NS4168 PA_CTRL LOW.

Put audio subsystem into low-power hardware standby.

Keeps power rails on so I2C bus is NOT clamped by unpowered chip protection diodes. On unattended deep-sleep wakes where the codec is already in verified standby, bypasses redundant I2C register writes to keep the codec completely undisturbed.

#### Returns
ESP_OK on success, or an error code.

Put ES8311 codec into ultra-low-power software standby (Reg 0x0D = 0xFC @ <1.0 µA) and pull NS4168 PA_CTRL LOW.

Mutes amplifier (GPIO 46 LOW), disables class-D power gate (GPIO 42 HIGH), and enters software power-down on ES8311.

#### Returns
ESP_OK on success.

---

{#sub_audio_render_tone_samples}

### sub_audio_render_tone_samples

`static`

```cpp
static void sub_audio_render_tone_samples(uint32_t frequency_hz, uint32_t duration_ms)
```

Defined in sub_audio.c:633

Sub audio render tone samples.

#### Returns
Return value of type static void.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `frequency_hz` | `uint32_t` | Parameter frequency_hz. |
| `duration_ms` | `uint32_t` | Parameter duration_ms. |

---

{#sub_audio_render_pcm_samples}

### sub_audio_render_pcm_samples

`static`

```cpp
static void sub_audio_render_pcm_samples(const int16_t * samples, size_t sample_count)
```

Defined in sub_audio.c:684

Sub audio render pcm samples.

#### Returns
Return value of type static void.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `samples` | `const int16_t *` | Parameter samples. |
| `sample_count` | `size_t` | Parameter sample_count. |

---

{#sub_audio_prepare_and_unmute}

### sub_audio_prepare_and_unmute

`static`

```cpp
static esp_err_t sub_audio_prepare_and_unmute(void)
```

Defined in sub_audio.c:712

Sub audio prepare and unmute.

#### Returns
ESP_OK on success, or an error code.

---

{#sub_audio_exec_tone}

### sub_audio_exec_tone

`static`

```cpp
static esp_err_t sub_audio_exec_tone(uint32_t frequency_hz, uint32_t duration_ms)
```

Defined in sub_audio.c:750

Sub audio exec tone.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `frequency_hz` | `uint32_t` | Parameter frequency_hz. |
| `duration_ms` | `uint32_t` | Parameter duration_ms. |

---

{#sub_audio_exec_pcm}

### sub_audio_exec_pcm

`static`

```cpp
static esp_err_t sub_audio_exec_pcm(const int16_t * samples, size_t sample_count, uint32_t sample_rate_hz)
```

Defined in sub_audio.c:771

Sub audio exec pcm.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `samples` | `const int16_t *` | Parameter samples. |
| `sample_count` | `size_t` | Parameter sample_count. |
| `sample_rate_hz` | `uint32_t` | Parameter sample_rate_hz. |

---

{#sub_audio_exec_chime}

### sub_audio_exec_chime

`static`

```cpp
static esp_err_t sub_audio_exec_chime(uint8_t type)
```

Defined in sub_audio.c:789

Sub audio exec chime.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `type` | `uint8_t` | Parameter type. |

---

{#sub_audio_send_command}

### sub_audio_send_command

`static`

```cpp
static esp_err_t sub_audio_send_command(const audio_cmd_t * cmd, bool is_sync, uint32_t wait_ms)
```

Defined in sub_audio.c:902

Sub audio send command.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `cmd` | const [`audio_cmd_t`](#audio_cmd_t) * | Parameter cmd. |
| `is_sync` | `bool` | Parameter is_sync. |
| `wait_ms` | `uint32_t` | Parameter wait_ms. |

---

{#sub_audio_play-1}

### sub_audio_play

```cpp
esp_err_t sub_audio_play(sub_audio_type_t type, const void * data, size_t len)
```

Defined in sub_audio.c:953

Unified asynchronous audio playback dispatcher.

Dispatch audio playback command to background worker task.

Enqueues the requested audio command into the background audio worker task.

#### Returns
ESP_OK on success, ESP_ERR_TIMEOUT if queue is full, or ESP_ERR_INVALID_ARG.

Unified asynchronous audio playback dispatcher.

#### Returns
ESP_OK if command was queued to worker, or error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `type` | [`sub_audio_type_t`](#sub_audio_type_t) | Acoustic payload type (SUB_AUDIO_TONE, SUB_AUDIO_CHIME, SUB_AUDIO_PCM). |
| `data` | `const void *` | Pointer to payload data buffer or parameters struct. |
| `len` | `size_t` | Length of data payload in bytes. |

---

{#sub_audio_is_busy-1}

### sub_audio_is_busy

```cpp
bool sub_audio_is_busy(void)
```

Defined in sub_audio.c:998

Check if audio playback is currently active or queue has pending items.

Check if audio playback is actively streaming.

#### Returns
true if playing or queued, false if idle in standby.

Check if audio playback is currently active or queue has pending items.

#### Returns
True if amplifier is active and audio samples are playing.

---

{#sub_audio_wait_idle-1}

### sub_audio_wait_idle

```cpp
esp_err_t sub_audio_wait_idle(uint32_t timeout_ms)
```

Defined in sub_audio.c:1016

Wait until background audio worker completes all playback and enters standby.

Block until all pending audio commands finish playback and amplifier enters standby.

#### Returns
ESP_OK if idle, ESP_ERR_TIMEOUT if still active.

Wait until background audio worker completes all playback and enters standby.

#### Returns
ESP_OK when playback is idle, ESP_ERR_TIMEOUT on expiration.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ms` | `uint32_t` | Maximum wait time in milliseconds. |

---

{#sub_audio_deinit-1}

### sub_audio_deinit

```cpp
esp_err_t sub_audio_deinit(void)
```

Defined in sub_audio.c:1031

Teardown audio subsystem, stop background worker task, and delete I2S channel.

Deinitialize audio subsystem and release I2S and FreeRTOS resources.

#### Returns
ESP_OK on success.

Teardown audio subsystem, stop background worker task, and delete I2S channel.

#### Returns
ESP_OK on success.

---

{#sub_audio_set_volume-1}

### sub_audio_set_volume

```cpp
esp_err_t sub_audio_set_volume(uint8_t volume_pct)
```

Defined in sub_audio.c:1074

Set ES8311 DAC output volume percentage (0% = Mute, 100% = 0 dB full-scale).

Set master audio volume percentage (0..100%).

Persists across standby/wake cycles.

#### Returns
ESP_OK on success.

Set ES8311 DAC output volume percentage (0% = Mute, 100% = 0 dB full-scale).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `volume_pct` | `uint8_t` | Output volume (0 = Mute, 100 = 0 dB Max). |

---

{#sub_audio_get_volume-1}

### sub_audio_get_volume

```cpp
uint8_t sub_audio_get_volume(void)
```

Defined in sub_audio.c:1092

Get currently configured output volume percentage (0 - 100).

Retrieve current audio volume percentage.

#### Returns
Current volume percentage.

Get currently configured output volume percentage (0 - 100).

#### Returns
Current volume level (0..100%).

---

{#sub_audio_set_low_power_mode-1}

### sub_audio_set_low_power_mode

```cpp
esp_err_t sub_audio_set_low_power_mode(bool enable)
```

Defined in sub_audio.c:1106

Configure ES8311 DAC power mode (Low-Power vs Normal).

Enable or disable aggressive codec low-power mode.

In low-power mode (default upon init), ES8311 operates with LPDAC enabled (Reg 0x0F bit 7 = 1), significantly reducing active DAC bias current. Normal mode provides standard bias.

#### Returns
ESP_OK on success.

Configure ES8311 DAC power mode (Low-Power vs Normal).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `enable` | `bool` | True to enable analog power-down when idle. |

---

{#sub_audio_get_low_power_mode-1}

### sub_audio_get_low_power_mode

```cpp
bool sub_audio_get_low_power_mode(void)
```

Defined in sub_audio.c:1120

Query whether audio subsystem is in Low-Power Mode.

Query whether codec low-power mode is enabled.

#### Returns
true if Low-Power Mode is active, false if Normal Power Mode.

Query whether audio subsystem is in Low-Power Mode.

#### Returns
True if low-power mode is active.

---

{#asm}

### asm

```cpp
const uint8_t ulp_h1os_bin_start[] asm("_binary_ulp_h1os_bin_start")
```

Defined in sub_power.c:31

---

{#asm-1}

### asm

```cpp
const uint8_t ulp_h1os_bin_end[] asm("_binary_ulp_h1os_bin_end")
```

Defined in sub_power.c:32

---

{#mv_to_percent}

### mv_to_percent

`static`

```cpp
static uint8_t mv_to_percent(uint16_t mv)
```

Defined in sub_power.c:74

Mv to percent.

#### Returns
Return value of type static uint8_t.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `mv` | `uint16_t` | Parameter mv. |

---

{#sub_power_init-1}

### sub_power_init

```cpp
esp_err_t sub_power_init(void)
```

Defined in sub_power.c:97

Initialize Battery ADC subsystem (ADC1 Channel 3 on GPIO 4 with 12 dB atten and eFuse cal).

Initialize battery ADC channel and calibration engine.

#### Returns
ESP_OK on success, or an error code.

Initialize Battery ADC subsystem (ADC1 Channel 3 on GPIO 4 with 12 dB atten and eFuse cal).

Configures ADC1 Channel 3 on GPIO 4 with curve fitting calibration.

#### Returns
ESP_OK on success.

---

{#sub_power_deinit-1}

### sub_power_deinit

```cpp
esp_err_t sub_power_deinit(void)
```

Defined in sub_power.c:145

Deinitialize ADC handles.

Deinitialize battery ADC driver.

#### Returns
ESP_OK on success.

Deinitialize ADC handles.

#### Returns
ESP_OK on success.

---

{#sub_power_read_battery-1}

### sub_power_read_battery

```cpp
esp_err_t sub_power_read_battery(uint16_t * out_mv, uint8_t * out_pct)
```

Defined in sub_power.c:170

Sample calibrated battery voltage with 16-sample trimmed outlier filtering.

Sample current battery terminal voltage and calculate state-of-charge.

#### Returns
ESP_OK on success, or an error code.

Sample calibrated battery voltage with 16-sample trimmed outlier filtering.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_mv` | `uint16_t *` | Pointer to store sampled voltage in millivolts. |
| `out_pct` | `uint8_t *` | Pointer to store state-of-charge percentage (0..100%). |

---

{#sub_power_get_ulp_cal_params-1}

### sub_power_get_ulp_cal_params

```cpp
esp_err_t sub_power_get_ulp_cal_params(uint32_t * out_scale, int32_t * out_offset_mv)
```

Defined in sub_power.c:237

Extract linear calibration coefficients (scale and offset) for ULP coprocessor hand-off.

Retrieve two-point calibration parameters for ULP coprocessor ADC readings.

#### Returns
ESP_OK on success.

Extract linear calibration coefficients (scale and offset) for ULP coprocessor hand-off.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_scale` | `uint32_t *` | Pointer to store scale multiplier. |
| `out_offset_mv` | `int32_t *` | Pointer to store offset in millivolts. |

---

{#sub_power_init_ulp-1}

### sub_power_init_ulp

```cpp
esp_err_t sub_power_init_ulp(uint32_t flow_a_period_sec)
```

Defined in sub_power.c:269

Initialize and start the ULP-RISC-V Coprocessor Reactive Monitor.

Initialize ULP-RISC-V coprocessor firmware for background monitoring.

Loads the binary into RTC Slow SRAM on cold boot, passes ADC eFuse calibration, configures the periodic wake timer (Flow A period), and arms the coprocessor.

#### Returns
ESP_OK on success, or an error code.

Initialize and start the ULP-RISC-V Coprocessor Reactive Monitor.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `flow_a_period_sec` | `uint32_t` | Headless sensor burst interval in seconds. |

---

{#sub_power_set_sleep_slices-1}

### sub_power_set_sleep_slices

```cpp
void sub_power_set_sleep_slices(uint32_t flow_a_sec, uint32_t flow_b_sec, uint32_t overflow, uint32_t remainder_sec)
```

Defined in sub_power.c:321

Configure ULP slice parameters prior to entering deep sleep.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `flow_a_sec` | `uint32_t` | Flow A sample interval in seconds. |
| `flow_b_sec` | `uint32_t` | Flow B display refresh interval in seconds. |
| `overflow` | `uint32_t` | Total slice overflow threshold. |
| `remainder_sec` | `uint32_t` | Final remainder slice duration in seconds. |

---

{#sub_power_enter_deep_sleep_mode-1}

### sub_power_enter_deep_sleep_mode

```cpp
esp_err_t sub_power_enter_deep_sleep_mode(uint32_t sleep_seconds, uint64_t ext1_pins_mask, sub_power_sleep_mode_t mode)
```

Defined in sub_power.c:340

Configure EXT1 wake sources and enter deep sleep with operational mode arbitration.

Enter target deep sleep mode with wake pin configuration.

Maintains RTC pad holds on power latch (GPIO 17) and EPD rail (GPIO 6) to keep rails active.

#### Returns
Does not return on success (enters deep sleep).

Configure EXT1 wake sources and enter deep sleep with operational mode arbitration.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `sleep_seconds` | `uint32_t` | Sleep duration in seconds. |
| `ext1_pins_mask` | `uint64_t` | Bitmask of GPIOs to configure for EXT1 wake. |
| `mode` | [`sub_power_sleep_mode_t`](#sub_power_sleep_mode_t) | Sleep mode (SUB_POWER_SLEEP_FULL_CYCLE or SUB_POWER_SLEEP_FLOW_A_BURST). |

---

{#sub_power_enter_deep_sleep-1}

### sub_power_enter_deep_sleep

```cpp
esp_err_t sub_power_enter_deep_sleep(uint32_t sleep_seconds, uint64_t ext1_pins_mask)
```

Defined in sub_power.c:445

Configure EXT1 wake sources and enter deep sleep (defaults to SUB_POWER_SLEEP_FULL_CYCLE).

Enter full cycle deep sleep with wake pin configuration.

Maintains RTC pad holds on power latch (GPIO 17) and EPD rail (GPIO 6) to keep rails active.

#### Returns
Does not return on success (enters deep sleep).

Configure EXT1 wake sources and enter deep sleep (defaults to SUB_POWER_SLEEP_FULL_CYCLE).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `sleep_seconds` | `uint32_t` | Sleep duration in seconds. |
| `ext1_pins_mask` | `uint64_t` | Bitmask of GPIOs for EXT1 wake. |

---

{#sub_power_cut_power_latch-1}

### sub_power_cut_power_latch

```cpp
void sub_power_cut_power_latch(void)
```

Defined in sub_power.c:455

Power off system completely by releasing battery power latch (GPIO 17).

Cut master power latch (releases GPIO 17 BAT_CTRL).

Used for critical low-battery shutdown or explicit user power-off.

Power off system completely by releasing battery power latch (GPIO 17).

---

{#sub_power_connected_usb-1}

### sub_power_connected_usb

```cpp
bool sub_power_connected_usb(void)
```

Defined in sub_power.c:468

Check to see if USB is connected.

Check if USB VBUS connection is actively present.

Used for charger detection.

#### Returns
true if usb is connected, or false if disconnected.

Check to see if USB is connected.

#### Returns
True if connected to USB power.

---

{#sub_power_init_dfs-1}

### sub_power_init_dfs

```cpp
esp_err_t sub_power_init_dfs(sys_clk_mode_t mode)
```

Defined in sub_power.c:492

Initialize Dynamic Frequency Scaling (DFS) power management.

Configures CPU frequency scaling based on the selected clock mode. SYS_CLK_MODE_DYNAMIC gates CPU cores to 80 MHz baseline during quiescent periods, allowing transient turbo scaling (CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ) during heavy UI/compute bursts. SYS_CLK_MODE_FIXED_MAX locks CPU cores permanently to maximum clock (CONFIG_ESP_DEFAULT_CPU_FREQ_MHZ). SYS_CLK_MODE_FIXED_MIN locks CPU cores permanently to 80 MHz baseline.

#### Returns
ESP_OK on success, or an error code.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `mode` | [`sys_clk_mode_t`](#sys_clk_mode_t) | Clock scaling mode (SYS_CLK_MODE_DYNAMIC, FIXED_MAX, FIXED_MIN). |

---

{#sub_power_cpu_max_acquire-1}

### sub_power_cpu_max_acquire

```cpp
esp_err_t sub_power_cpu_max_acquire(void)
```

Defined in sub_power.c:540

Acquire 240 MHz CPU performance lock (e.g.

Acquire CPU frequency lock at 240 MHz for compute/display intensive operations.

during LVGL rendering blitz).

Boosts CPU cores from 80 MHz baseline to 240 MHz turbo clock.

#### Returns
ESP_OK on success.

Acquire 240 MHz CPU performance lock (e.g.

#### Returns
ESP_OK on success.

---

{#sub_power_cpu_max_release-1}

### sub_power_cpu_max_release

```cpp
esp_err_t sub_power_cpu_max_release(void)
```

Defined in sub_power.c:557

Release 240 MHz CPU performance lock.

Release CPU frequency lock, allowing DFS to downclock to 80 MHz.

Allows CPU cores to gate back down to 80 MHz baseline.

#### Returns
ESP_OK on success.

Release 240 MHz CPU performance lock.

#### Returns
ESP_OK on success.

---

{#orch_state_get}

### orch_state_get

```cpp
volatile orch_persisted_state_t * orch_state_get(void)
```

Defined in h1os/orch_state.h:114

Retrieve pointer to persistent state structure in RTC Slow SRAM.

Automatically initializes default values if magic word is invalid or corrupted.

#### Returns
Pointer to persistent state block in RTC Slow Memory.

---

{#orch_state_reset}

### orch_state_reset

```cpp
void orch_state_reset(void)
```

Defined in h1os/orch_state.h:119

Reset persisted state in RTC Slow Memory to clean factory defaults.

Reset persisted RTC state to default values.

Reset persisted state in RTC Slow Memory to clean factory defaults.

#### Returns
Return value of type void RTC_IRAM_ATTR.

---

{#orch_state_push_sample}

### orch_state_push_sample

```cpp
void orch_state_push_sample(const orch_tri_node_sample_t * sample)
```

Defined in h1os/orch_state.h:126

Push a new sample into the RTC circular ring buffer.

Push a new Tri-Node telemetry sample into the RTC ring buffer.

Push a new sample into the RTC circular ring buffer.

#### Returns
Return value of type void RTC_IRAM_ATTR.

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

Defined in h1os/orch_state.h:135

Retrieve the most recent sample from the ring buffer.

Get the latest committed sample from the ring buffer.

#### Returns
True if a sample was retrieved, false if ring buffer is empty.

Retrieve the most recent sample from the ring buffer.

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

Defined in h1os/orch_state.h:144

Retrieve the most recent thermally settled, valid sample from the ring buffer.

Get the newest sample in the ring buffer marked SAMPLE_FLAG_VALID_COLD.

#### Returns
True if a valid settled sample was located, false otherwise.

Retrieve the most recent thermally settled, valid sample from the ring buffer.

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

Defined in h1os/sub_sdcard.h:27

Mount MicroSD card into FATFS VFS in 1-bit SDMMC mode.

Mount MicroSD card using 1-bit SDMMC driver (synchronous).

#### Returns
ESP_OK on success, or mount failure error.

Mount MicroSD card into FATFS VFS in 1-bit SDMMC mode.

#### Returns
ESP_OK on success, or an error code.

---

{#sub_sdcard_mount_async}

### sub_sdcard_mount_async

```cpp
esp_err_t sub_sdcard_mount_async(void)
```

Defined in h1os/sub_sdcard.h:34

Mount MicroSD card asynchronously in background task.

Asynchronously mount MicroSD card in a background FreeRTOS task.

#### Returns
ESP_OK if mount task dispatched successfully.

Mount MicroSD card asynchronously in background task.

Does not block caller or freeze UI refresh if card is missing.

#### Returns
ESP_OK on success, or an error code.

---

{#sub_sdcard_unmount}

### sub_sdcard_unmount

```cpp
esp_err_t sub_sdcard_unmount(void)
```

Defined in h1os/sub_sdcard.h:41

Unmount MicroSD card and release SDMMC host peripheral.

Unmount MicroSD card and release hardware bus resources.

#### Returns
ESP_OK on success.

Unmount MicroSD card and release SDMMC host peripheral.

#### Returns
ESP_OK on success, or an error code.

---

{#sub_sdcard_is_mounted}

### sub_sdcard_is_mounted

```cpp
bool sub_sdcard_is_mounted(void)
```

Defined in h1os/sub_sdcard.h:48

Check if MicroSD card is actively mounted in VFS.

Check if MicroSD card is mounted and ready for I/O.

#### Returns
True if filesystem is mounted and accessible.

Check if MicroSD card is actively mounted in VFS.

#### Returns
True on success, false otherwise.

---

{#sub_sdcard_get_capacity_mb}

### sub_sdcard_get_capacity_mb

```cpp
esp_err_t sub_sdcard_get_capacity_mb(uint32_t * out_capacity_mb)
```

Defined in h1os/sub_sdcard.h:57

Query total storage capacity of mounted MicroSD card in megabytes.

Get total capacity of mounted card in megabytes.

#### Returns
ESP_OK on success, or ESP_ERR_INVALID_STATE if not mounted.

Query total storage capacity of mounted MicroSD card in megabytes.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_capacity_mb` | `uint32_t *` | Parameter out_capacity_mb. |

---

{#sub_sdcard_format}

### sub_sdcard_format

```cpp
esp_err_t sub_sdcard_format(void)
```

Defined in h1os/sub_sdcard.h:64

Format mounted MicroSD card with clean FAT32 filesystem.

Format mounted card as FAT32 filesystem.

#### Returns
ESP_OK on success.

Format mounted MicroSD card with clean FAT32 filesystem.

#### Returns
ESP_OK on success, or an error code.

---

{#orch_state_get-1}

### orch_state_get

```cpp
volatile orch_persisted_state_t *RTC_IRAM_ATTR orch_state_get(void)
```

Defined in orch_state.c:18

Retrieve pointer to persistent state structure in RTC Slow SRAM.

Automatically initializes default values if magic word is invalid or corrupted.

#### Returns
Pointer to persistent state block in RTC Slow Memory.

---

{#orch_state_reset-1}

### orch_state_reset

```cpp
void RTC_IRAM_ATTR orch_state_reset(void)
```

Defined in orch_state.c:31

Reset persisted RTC state to default values.

Reset persisted state in RTC Slow Memory to clean factory defaults.

#### Returns
Return value of type void RTC_IRAM_ATTR.

Reset persisted RTC state to default values.

---

{#orch_state_push_sample-1}

### orch_state_push_sample

```cpp
void RTC_IRAM_ATTR orch_state_push_sample(const orch_tri_node_sample_t * sample)
```

Defined in orch_state.c:55

Push a new Tri-Node telemetry sample into the RTC ring buffer.

Push a new sample into the RTC circular ring buffer.

#### Returns
Return value of type void RTC_IRAM_ATTR.

Push a new Tri-Node telemetry sample into the RTC ring buffer.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `sample` | const [`orch_tri_node_sample_t`](#orch_tri_node_sample_t) * | Pointer to sample struct to store. |

---

{#orch_state_get_latest_sample-1}

### orch_state_get_latest_sample

```cpp
bool orch_state_get_latest_sample(orch_tri_node_sample_t * out_sample)
```

Defined in orch_state.c:73

Get the latest committed sample from the ring buffer.

Retrieve the most recent sample from the ring buffer.

#### Returns
true if reading present, false if buffer empty.

Get the latest committed sample from the ring buffer.

#### Returns
True if a sample was retrieved, false if ring buffer is empty.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_sample` | [`orch_tri_node_sample_t`](#orch_tri_node_sample_t) * | Destination struct for sample copy. Must not be NULL. |

---

{#orch_state_get_latest_valid_sample-1}

### orch_state_get_latest_valid_sample

```cpp
bool orch_state_get_latest_valid_sample(orch_tri_node_sample_t * out_sample)
```

Defined in orch_state.c:96

Get the newest sample in the ring buffer marked SAMPLE_FLAG_VALID_COLD.

Retrieve the most recent thermally settled, valid sample from the ring buffer.

Falls back to the latest sample if no sample has been marked valid yet.

#### Returns
true if a sample is returned, false if buffer empty.

Get the newest sample in the ring buffer marked SAMPLE_FLAG_VALID_COLD.

#### Returns
True if a valid settled sample was located, false otherwise.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_sample` | [`orch_tri_node_sample_t`](#orch_tri_node_sample_t) * | Destination struct for sample copy. Must not be NULL. |

---

{#sdcard_mount_worker_task}

### sdcard_mount_worker_task

`static`

```cpp
static void sdcard_mount_worker_task(void * pvParameters)
```

Defined in sub_sdcard.c:36

Sdcard mount worker task.

#### Returns
Return value of type static void.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `pvParameters` | `void *` | Parameter pvParameters. |

---

{#sub_sdcard_mount_async-1}

### sub_sdcard_mount_async

```cpp
esp_err_t sub_sdcard_mount_async(void)
```

Defined in sub_sdcard.c:63

Asynchronously mount MicroSD card in a background FreeRTOS task.

Mount MicroSD card asynchronously in background task.

Does not block caller or freeze UI refresh if card is missing.

#### Returns
ESP_OK on success, or an error code.

Asynchronously mount MicroSD card in a background FreeRTOS task.

#### Returns
ESP_OK if mount task dispatched successfully.

---

{#sub_sdcard_mount-1}

### sub_sdcard_mount

```cpp
esp_err_t sub_sdcard_mount(void)
```

Defined in sub_sdcard.c:84

Mount MicroSD card using 1-bit SDMMC driver (synchronous).

Mount MicroSD card into FATFS VFS in 1-bit SDMMC mode.

#### Returns
ESP_OK on success, or an error code.

Mount MicroSD card using 1-bit SDMMC driver (synchronous).

#### Returns
ESP_OK on success, or mount failure error.

---

{#sub_sdcard_unmount-1}

### sub_sdcard_unmount

```cpp
esp_err_t sub_sdcard_unmount(void)
```

Defined in sub_sdcard.c:150

Unmount MicroSD card and release hardware bus resources.

Unmount MicroSD card and release SDMMC host peripheral.

#### Returns
ESP_OK on success, or an error code.

Unmount MicroSD card and release hardware bus resources.

#### Returns
ESP_OK on success.

---

{#sub_sdcard_is_mounted-1}

### sub_sdcard_is_mounted

```cpp
bool sub_sdcard_is_mounted(void)
```

Defined in sub_sdcard.c:172

Check if MicroSD card is mounted and ready for I/O.

Check if MicroSD card is actively mounted in VFS.

#### Returns
True on success, false otherwise.

Check if MicroSD card is mounted and ready for I/O.

#### Returns
True if filesystem is mounted and accessible.

---

{#sub_sdcard_get_capacity_mb-1}

### sub_sdcard_get_capacity_mb

```cpp
esp_err_t sub_sdcard_get_capacity_mb(uint32_t * out_capacity_mb)
```

Defined in sub_sdcard.c:184

Get total capacity of mounted card in megabytes.

Query total storage capacity of mounted MicroSD card in megabytes.

#### Returns
ESP_OK on success, or an error code.

Get total capacity of mounted card in megabytes.

#### Returns
ESP_OK on success, or ESP_ERR_INVALID_STATE if not mounted.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_capacity_mb` | `uint32_t *` | Pointer to store total capacity in MB. Must not be NULL. |

---

{#sub_sdcard_format-1}

### sub_sdcard_format

```cpp
esp_err_t sub_sdcard_format(void)
```

Defined in sub_sdcard.c:201

Format mounted card as FAT32 filesystem.

Format mounted MicroSD card with clean FAT32 filesystem.

#### Returns
ESP_OK on success, or an error code.

Format mounted card as FAT32 filesystem.

#### Returns
ESP_OK on success.

---

{#sub_display_init}

### sub_display_init

```cpp
esp_err_t sub_display_init(bool is_wake_cycle)
```

Defined in h1os/sub_display.h:37

Initialize SSD1681 electrophoretic display controller.

Initialize SSD1681 display controller.

Enables 3.3V power rail (GPIO 6), performs hardware reset pulse, and initializes display RAM registers via SPI DMA.

#### Returns
ESP_OK on success, or SPI communication error.

Initialize SSD1681 electrophoretic display controller.

Wakes panel, initializes SPI interface, configures scanning geometry, and sets up BUSY synchronization.

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

Defined in h1os/sub_display.h:44

Retrieve direct pointer to the active 5000-byte internal RAM framebuffer.

#### Returns
Pointer to packed 1-bit monochrome pixel array.

---

{#sub_display_clear}

### sub_display_clear

```cpp
void sub_display_clear(uint8_t color)
```

Defined in h1os/sub_display.h:51

Clear internal RAM framebuffer to pure color.

Clear active working framebuffer.

Clear internal RAM framebuffer to pure color.

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

Defined in h1os/sub_display.h:60

Synchronize SSD1681 previous-frame RAM with historical frame for differential refresh.

Synchronize previous frame into shadow buffer and hardware RAM 0x26.

#### Returns
ESP_OK on success.

Synchronize SSD1681 previous-frame RAM with historical frame for differential refresh.

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

Defined in h1os/sub_display.h:69

Block until SSD1681 BUSY line deasserts (panel update complete).

Synchronously wait for EPD panel to finish driving electrophoretic particles.

#### Returns
ESP_OK when panel idle, ESP_ERR_TIMEOUT on timeout.

Block until SSD1681 BUSY line deasserts (panel update complete).

Waits up to 15 ms for the SSD1681 state machine to assert BUSY HIGH (1) after a command (e.g. 0x20 Master Activation or 0x12 SW Reset), then polls until BUSY drops back LOW (0).

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

Defined in h1os/sub_display.h:78

Execute full OTP flashing refresh on electrophoretic panel.

Execute full display refresh (OTP factory waveform LUT).

Completely clears DC bias and ghosting artifacts. Takes ~2.4 seconds.

#### Returns
ESP_OK on success.

Execute full OTP flashing refresh on electrophoretic panel.

Synchronizes old frame RAM (0x26) with new frame RAM (0x24).

#### Returns
ESP_OK on success.

---

{#sub_display_clear_to_white_full}

### sub_display_clear_to_white_full

```cpp
esp_err_t sub_display_clear_to_white_full(void)
```

Defined in h1os/sub_display.h:87

Clear panel to solid white and trigger full OTP refresh.

Clear display to pure white and trigger full OTP refresh.

Mandatory prior to long-term storage or battery disconnection.

#### Returns
ESP_OK on success.

Clear panel to solid white and trigger full OTP refresh.

Chemically neutralizes electrophoretic microcapsules to protect against permanent burn-in. Ensures SPI2 and SSD1681 are initialized and awake even when invoked directly from deep-sleep ULP power-off wakes (ORCH_FLOW_CRITICAL_OFF).

#### Returns
ESP_OK on success.

---

{#sub_display_refresh_partial}

### sub_display_refresh_partial

```cpp
esp_err_t sub_display_refresh_partial(void)
```

Defined in h1os/sub_display.h:96

Execute fast differential partial refresh on panel without screen flash.

Execute fast partial refresh (~300ms) with software LUT.

Updates only changed pixels. Takes ~300ms.

#### Returns
ESP_OK on success.

Execute fast differential partial refresh on panel without screen flash.

#### Returns
ESP_OK on success.

---

{#sub_display_read_glass_temp}

### sub_display_read_glass_temp

```cpp
esp_err_t sub_display_read_glass_temp(float * out_temp_c)
```

Defined in h1os/sub_display.h:105

Read temperature from SSD1681 embedded on-glass thermal sensor.

Read SSD1681 on-glass integrated temperature sensor (SPI Cmd 0x1B).

#### Returns
ESP_OK on success, or SPI read error.

Read temperature from SSD1681 embedded on-glass thermal sensor.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_temp_c` | `float *` | Surface glass temperature in Celsius. |

---

{#sub_display_get_glass_temp_centi_c}

### sub_display_get_glass_temp_centi_c

```cpp
int16_t sub_display_get_glass_temp_centi_c(void)
```

Defined in h1os/sub_display.h:112

Retrieve the latest cached SSD1681 on-glass temperature in centi-degrees Celsius.

#### Returns
Cached glass temperature in centi-°C (0 if not yet sampled).

---

{#sub_display_enter_deep_sleep}

### sub_display_enter_deep_sleep

```cpp
esp_err_t sub_display_enter_deep_sleep(void)
```

Defined in h1os/sub_display.h:119

Put SSD1681 into Deep Sleep Mode 1 (<1uA quiescent drain).

Put SSD1681 into Deep Sleep Mode 1 (Command 0x10, Data 0x01 @ 1.0 µA).

#### Returns
ESP_OK on success.

Put SSD1681 into Deep Sleep Mode 1 (<1uA quiescent drain).

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

Defined in h1os_lvgl.cpp:442

H1os lvgl port task.

#### Returns
Return value of type static void.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `pvParameters` | `void *` | Parameter pvParameters. |

---

{#h1os_lvgl_lock-1}

### h1os_lvgl_lock

```cpp
bool h1os_lvgl_lock(uint32_t timeout_ms)
```

Defined in h1os_lvgl.cpp:63

Acquire LVGL reentrant mutex lock.

#### Returns
True on success, false otherwise.

Must be acquired before creating, modifying, or deleting any LVGL widgets or objects from tasks other than the LVGL event loop.

#### Returns
True if mutex was successfully acquired within timeout, false otherwise.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ms` | `uint32_t` | Mutex acquisition timeout in milliseconds. |

---

{#h1os_lvgl_unlock-1}

### h1os_lvgl_unlock

```cpp
void h1os_lvgl_unlock(void)
```

Defined in h1os_lvgl.cpp:76

Release LVGL reentrant mutex lock.

Releases the mutex acquired via [h1os_lvgl_lock()](#h1os_lvgl_lock).

---

{#lvgl_tick_get_cb}

### lvgl_tick_get_cb

`static`

```cpp
static uint32_t lvgl_tick_get_cb(void)
```

Defined in h1os_lvgl.cpp:89

Lvgl tick get cb.

#### Returns
Return value of type static uint32_t.

---

{#lvgl_keypad_read_cb}

### lvgl_keypad_read_cb

`static`

```cpp
static void lvgl_keypad_read_cb(lv_indev_t * indev, lv_indev_data_t * data)
```

Defined in h1os_lvgl.cpp:102

Lvgl keypad read cb.

#### Returns
Return value of type static void.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `indev` | `lv_indev_t *` | Parameter indev. |
| `data` | `lv_indev_data_t *` | Parameter data. |

---

{#lvgl_display_flush_cb}

### lvgl_display_flush_cb

`static`

```cpp
static void lvgl_display_flush_cb(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map)
```

Defined in h1os_lvgl.cpp:140

Lvgl display flush cb.

#### Returns
Return value of type static void.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `disp` | `lv_display_t *` | Parameter disp. |
| `area` | `const lv_area_t *` | Parameter area. |
| `px_map` | `uint8_t *` | Parameter px_map. |

---

{#h1os_lvgl_init-1}

### h1os_lvgl_init

```cpp
esp_err_t h1os_lvgl_init(bool is_wake_cycle)
```

Defined in h1os_lvgl.cpp:264

Initialize LVGL v9 graphics subsystem, 1-bit display buffer, and keypad input driver.

#### Returns
ESP_OK on success, or an error code.

Configures the bilevel draw buffer, registers the display flush callback, and sets up keypad input navigation.

#### Returns

* ESP_OK: LVGL core initialized successfully.
* ESP_ERR_NO_MEM: Insufficient memory for draw buffer allocation.

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

Defined in h1os_lvgl.cpp:334

Explicitly override whether the first flush executes a full or partial refresh.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `full_refresh` | `bool` | True for full OTP flashing refresh, False for differential partial. |

---

{#h1os_lvgl_start-1}

### h1os_lvgl_start

```cpp
esp_err_t h1os_lvgl_start(int priority, int core_id)
```

Defined in h1os_lvgl.cpp:347

Start the LVGL background FreeRTOS task.

#### Returns
ESP_OK on success, or an error code.

Spawns the dedicated presentation task pinned to Core 1 for decoupled UI rendering.

#### Returns

* ESP_OK: Task created and running.
* ESP_FAIL: Task creation failed.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `priority` | `int` | FreeRTOS task priority (e.g. 4). |
| `core_id` | `int` | CPU core affinity (0 or 1). |

---

{#h1os_lvgl_stop-1}

### h1os_lvgl_stop

```cpp
esp_err_t h1os_lvgl_stop(void)
```

Defined in h1os_lvgl.cpp:385

Stop the LVGL background task.

Safely handles being called from within an LVGL input callback on the LVGL task thread itself (e.g. long-press shutdown) without self-deletion.

#### Returns
ESP_OK on success, or an error code.

Signals the event loop to terminate cleanly and waits for task exit.

#### Returns

* ESP_OK: Task stopped successfully.

---

{#h1os_lvgl_has_pending_tasks-1}

### h1os_lvgl_has_pending_tasks

```cpp
bool h1os_lvgl_has_pending_tasks(void)
```

Defined in h1os_lvgl.cpp:410

Check if the LVGL display pipeline has pending render/flush tasks.

#### Returns
True on success, false otherwise.

#### Returns
True if display driver is currently flushing or widgets are invalidated.

---

{#h1os_lvgl_get_indev-1}

### h1os_lvgl_get_indev

```cpp
lv_indev_t * h1os_lvgl_get_indev(void)
```

Defined in h1os_lvgl.cpp:430

Retrieve the LVGL keypad input device handle.

#### Returns
Pointer to registered keypad indev instance for focus group binding.

---

{#h1os_version_get_major}

### h1os_version_get_major

`static` `inline`

```cpp
static inline uint32_t h1os_version_get_major(void)
```

Defined in h1os/h1os_version.h:49

Get major version integer.

#### Returns
Major version.

---

{#h1os_version_get_minor}

### h1os_version_get_minor

`static` `inline`

```cpp
static inline uint32_t h1os_version_get_minor(void)
```

Defined in h1os/h1os_version.h:58

Get minor version integer.

#### Returns
Minor version.

---

{#h1os_version_get_patch}

### h1os_version_get_patch

`static` `inline`

```cpp
static inline uint32_t h1os_version_get_patch(void)
```

Defined in h1os/h1os_version.h:67

Get patch version integer.

#### Returns
Patch version.

---

{#h1os_version_get_tag}

### h1os_version_get_tag

`static` `inline`

```cpp
static inline const char * h1os_version_get_tag(void)
```

Defined in h1os/h1os_version.h:76

Get version tag string.

#### Returns
Release tag string (e.g. "alpha").

---

{#h1os_version_get_string}

### h1os_version_get_string

`static` `inline`

```cpp
static inline const char * h1os_version_get_string(void)
```

Defined in h1os/h1os_version.h:85

Get complete version string.

#### Returns
Full version string (e.g. "2.3.3-dev").

---

{#h1os_version_get_code}

### h1os_version_get_code

`static` `inline`

```cpp
static inline uint32_t h1os_version_get_code(void)
```

Defined in h1os/h1os_version.h:94

Get 32-bit packed numeric version code.

#### Returns
32-bit version code.

---

{#h1os_version_get_build_date}

### h1os_version_get_build_date

`static` `inline`

```cpp
static inline const char * h1os_version_get_build_date(void)
```

Defined in h1os/h1os_version.h:103

Get build date string.

#### Returns
Build date string.

---

{#h1os_version_get_build_time}

### h1os_version_get_build_time

`static` `inline`

```cpp
static inline const char * h1os_version_get_build_time(void)
```

Defined in h1os/h1os_version.h:112

Get build time string.

#### Returns
Build time string.

---

{#epd_reset_pulse}

### epd_reset_pulse

`static`

```cpp
static void epd_reset_pulse(void)
```

Defined in sub_display.cpp:51

Epd reset pulse.

Wakes SSD1681 out of Deep Sleep Mode 1 (0x10 = 0x01) and resets state machine.

#### Returns
Return value of type static void.

---

{#sub_display_wait_busy-1}

### sub_display_wait_busy

```cpp
esp_err_t sub_display_wait_busy(TickType_t timeout_ticks)
```

Defined in sub_display.cpp:71

Synchronously wait for EPD panel to finish driving electrophoretic particles.

Block until SSD1681 BUSY line deasserts (panel update complete).

Waits up to 15 ms for the SSD1681 state machine to assert BUSY HIGH (1) after a command (e.g. 0x20 Master Activation or 0x12 SW Reset), then polls until BUSY drops back LOW (0).

#### Returns
ESP_OK on panel ready, ESP_ERR_TIMEOUT on expiration.

Synchronously wait for EPD panel to finish driving electrophoretic particles.

#### Returns
ESP_OK when panel idle, ESP_ERR_TIMEOUT on timeout.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ticks` | `TickType_t` | FreeRTOS tick timeout. |

---

{#epd_configure_base_registers}

### epd_configure_base_registers

`static`

```cpp
static void epd_configure_base_registers(void)
```

Defined in sub_display.cpp:99

Epd configure base registers.

#### Returns
Return value of type static void.

---

{#sub_display_init-1}

### sub_display_init

```cpp
esp_err_t sub_display_init(bool is_wake_cycle)
```

Defined in sub_display.cpp:131

Initialize SSD1681 display controller.

Initialize SSD1681 electrophoretic display controller.

Wakes panel, initializes SPI interface, configures scanning geometry, and sets up BUSY synchronization.

#### Returns
ESP_OK on success.

Initialize SSD1681 display controller.

Enables 3.3V power rail (GPIO 6), performs hardware reset pulse, and initializes display RAM registers via SPI DMA.

#### Returns
ESP_OK on success, or SPI communication error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `is_wake_cycle` | `bool` | True if resuming from sleep (bypasses full OTP clear). |

---

{#sub_display_get_framebuffer-1}

### sub_display_get_framebuffer

```cpp
uint8_t * sub_display_get_framebuffer(void)
```

Defined in sub_display.cpp:198

Retrieve direct pointer to the active 5000-byte internal RAM framebuffer.

#### Returns
Pointer to packed 1-bit monochrome pixel array.

---

{#sub_display_clear-1}

### sub_display_clear

```cpp
void sub_display_clear(uint8_t color)
```

Defined in sub_display.cpp:208

Clear active working framebuffer.

Clear internal RAM framebuffer to pure color.

Clear active working framebuffer.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `color` | `uint8_t` | 0x00 for solid black, 0xFF for solid white. |

---

{#epd_commit_ram_dma}

### epd_commit_ram_dma

`static`

```cpp
static void epd_commit_ram_dma(uint8_t ram_cmd, const uint8_t * frame_data)
```

Defined in sub_display.cpp:221

Epd commit ram dma.

#### Returns
Return value of type static void.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `ram_cmd` | `uint8_t` | Parameter ram_cmd. |
| `frame_data` | `const uint8_t *` | Parameter frame_data. |

---

{#sub_display_sync_previous_frame-1}

### sub_display_sync_previous_frame

```cpp
esp_err_t sub_display_sync_previous_frame(const uint8_t * prev_frame)
```

Defined in sub_display.cpp:244

Synchronize previous frame into shadow buffer and hardware RAM 0x26.

Synchronize SSD1681 previous-frame RAM with historical frame for differential refresh.

Essential on deep sleep wake to enable differential partial scanning against the glass.

#### Returns
ESP_OK on success.

Synchronize previous frame into shadow buffer and hardware RAM 0x26.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `prev_frame` | `const uint8_t *` | Pointer to 5000-byte preserved previous framebuffer. |

---

{#sub_display_refresh_full-1}

### sub_display_refresh_full

```cpp
esp_err_t sub_display_refresh_full(void)
```

Defined in sub_display.cpp:265

Execute full display refresh (OTP factory waveform LUT).

Execute full OTP flashing refresh on electrophoretic panel.

Synchronizes old frame RAM (0x26) with new frame RAM (0x24).

#### Returns
ESP_OK on success.

Execute full display refresh (OTP factory waveform LUT).

Completely clears DC bias and ghosting artifacts. Takes ~2.4 seconds.

#### Returns
ESP_OK on success.

---

{#sub_display_clear_to_white_full-1}

### sub_display_clear_to_white_full

```cpp
esp_err_t sub_display_clear_to_white_full(void)
```

Defined in sub_display.cpp:306

Clear display to pure white and trigger full OTP refresh.

Clear panel to solid white and trigger full OTP refresh.

Chemically neutralizes electrophoretic microcapsules to protect against permanent burn-in. Ensures SPI2 and SSD1681 are initialized and awake even when invoked directly from deep-sleep ULP power-off wakes (ORCH_FLOW_CRITICAL_OFF).

#### Returns
ESP_OK on success.

Clear display to pure white and trigger full OTP refresh.

Mandatory prior to long-term storage or battery disconnection.

#### Returns
ESP_OK on success.

---

{#epd_load_custom_lut}

### epd_load_custom_lut

`static`

```cpp
static void epd_load_custom_lut(const uint8_t * lut_buffer)
```

Defined in sub_display.cpp:324

Epd load custom lut.

#### Returns
Return value of type static void.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `lut_buffer` | `const uint8_t *` | Parameter lut_buffer. |

---

{#sub_display_refresh_partial-1}

### sub_display_refresh_partial

```cpp
esp_err_t sub_display_refresh_partial(void)
```

Defined in sub_display.cpp:350

Execute fast partial refresh (~300ms) with software LUT.

Execute fast differential partial refresh on panel without screen flash.

#### Returns
ESP_OK on success.

Execute fast partial refresh (~300ms) with software LUT.

Updates only changed pixels. Takes ~300ms.

#### Returns
ESP_OK on success.

---

{#sub_display_get_glass_temp_centi_c-1}

### sub_display_get_glass_temp_centi_c

```cpp
int16_t sub_display_get_glass_temp_centi_c(void)
```

Defined in sub_display.cpp:390

Retrieve the latest cached SSD1681 on-glass temperature in centi-degrees Celsius.

#### Returns
Cached glass temperature in centi-°C (0 if not yet sampled).

---

{#sub_display_read_glass_temp-1}

### sub_display_read_glass_temp

```cpp
esp_err_t sub_display_read_glass_temp(float * out_temp_c)
```

Defined in sub_display.cpp:402

Read SSD1681 on-glass integrated temperature sensor (SPI Cmd 0x1B).

Read temperature from SSD1681 embedded on-glass thermal sensor.

#### Returns
ESP_OK on success.

Read SSD1681 on-glass integrated temperature sensor (SPI Cmd 0x1B).

#### Returns
ESP_OK on success, or SPI read error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_temp_c` | `float *` | Pointer to store glass temperature in degrees Celsius. |

---

{#sub_display_enter_deep_sleep-1}

### sub_display_enter_deep_sleep

```cpp
esp_err_t sub_display_enter_deep_sleep(void)
```

Defined in sub_display.cpp:450

Put SSD1681 into Deep Sleep Mode 1 (Command 0x10, Data 0x01 @ 1.0 µA).

Put SSD1681 into Deep Sleep Mode 1 (<1uA quiescent drain).

Crucially retains RAM contents while the 3.3V rail remains held.

#### Returns
ESP_OK on success.

Put SSD1681 into Deep Sleep Mode 1 (Command 0x10, Data 0x01 @ 1.0 µA).

#### Returns
ESP_OK on success.

---

{#h1os_reset_session_timer-1}

### h1os_reset_session_timer

```cpp
void h1os_reset_session_timer(void)
```

Defined in h1os_lifecycle.c:47

Reset the interactive session inactivity timer (extends session by timeout_sec).

Reset the interactive session inactivity timer.

Reset the interactive session inactivity timer (extends session by timeout_sec).

Extends the interactive user session by inactivity_timeout_sec, preventing premature deep sleep while user interaction or animation is underway.

---

{#h1os_is_session_active-1}

### h1os_is_session_active

```cpp
bool h1os_is_session_active(void)
```

Defined in h1os_lifecycle.c:63

Check whether an interactive inactivity countdown session is active.

#### Returns
true if running in an interactive user session, false during unattended wakes.

#### Returns
True if running in an interactive user session, false during unattended wakes.

---

{#h1os_trigger_chime}

### h1os_trigger_chime

`static`

```cpp
static void h1os_trigger_chime(h1os_chime_type_t type)
```

Defined in h1os_lifecycle.c:75

H1os trigger chime.

#### Returns
Return value of type static void.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `type` | [`h1os_chime_type_t`](#h1os_chime_type_t) | Parameter type. |

---

{#h1os_trigger_splash}

### h1os_trigger_splash

`static`

```cpp
static void h1os_trigger_splash(h1os_splash_type_t type)
```

Defined in h1os_lifecycle.c:95

H1os trigger splash.

#### Returns
Return value of type static void.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `type` | [`h1os_splash_type_t`](#h1os_splash_type_t) | Parameter type. |

---

{#h1os_quiesce_lvgl_pipeline}

### h1os_quiesce_lvgl_pipeline

`static`

```cpp
static void h1os_quiesce_lvgl_pipeline(void)
```

Defined in h1os_lifecycle.c:105

Drain pending LVGL render/flush tasks and stop the Core 1 LVGL worker task.

---

{#h1os_session_monitor_task}

### h1os_session_monitor_task

`static`

```cpp
static void h1os_session_monitor_task(void * arg)
```

Defined in h1os_lifecycle.c:125

H1os session monitor task.

#### Returns
Return value of type static void.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `arg` | `void *` | Parameter arg. |

---

{#debug_dump_ulp_telemetry}

### debug_dump_ulp_telemetry

`static`

```cpp
static void debug_dump_ulp_telemetry(void)
```

Defined in h1os_lifecycle.c:156

Diagnostic dump of ULP wake telemetry and execution performance.

Isolated helper function for development; comment out the call in [h1os_start()](#h1os_start-1) for release builds.

#### Returns
Return value of type static void.

---

{#h1os_log_flow_banner}

### h1os_log_flow_banner

`static`

```cpp
static void h1os_log_flow_banner(orch_flow_type_t flow)
```

Defined in h1os_lifecycle.c:197

Logs a prominent, framed ASCII console banner identifying the active lifecycle flow.

#### Returns
Return value of type static void.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `flow` | [`orch_flow_type_t`](#orch_flow_type_t) | Parameter flow. |

---

{#h1os_early_system_bringup}

### h1os_early_system_bringup

`static`

```cpp
static orch_flow_type_t h1os_early_system_bringup(const h1os_lifecycle_t * config)
```

Defined in h1os_lifecycle.c:254

H1os early system bringup.

#### Returns
Return value of type static [orch_flow_type_t](#orch_flow_type_t).

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `config` | const [`h1os_lifecycle_t`](#h1os_lifecycle_t) * | Parameter config. |

---

{#h1os_handle_non_ui_flows}

### h1os_handle_non_ui_flows

`static`

```cpp
static bool h1os_handle_non_ui_flows(orch_flow_type_t flow)
```

Defined in h1os_lifecycle.c:308

H1os handle non ui flows.

#### Returns
True on success, false otherwise.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `flow` | [`orch_flow_type_t`](#orch_flow_type_t) | Parameter flow. |

---

{#h1os_launch_interactive_session}

### h1os_launch_interactive_session

`static`

```cpp
static esp_err_t h1os_launch_interactive_session(orch_flow_type_t flow)
```

Defined in h1os_lifecycle.c:335

H1os launch interactive session.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `flow` | [`orch_flow_type_t`](#orch_flow_type_t) | Parameter flow. |

---

{#h1os_start-1}

### h1os_start

```cpp
esp_err_t h1os_start(const h1os_lifecycle_t * config)
```

Defined in h1os_lifecycle.c:444

Initialize H1OS and dispatch application lifecycle.

#### Returns
ESP_OK on success, or an error code.

Configures hardware subsystems, determines boot/wake flow, initializes FreeRTOS tasks, and dispatches the configured application lifecycle hooks.

#### Returns

* ESP_OK: System initialized and lifecycle dispatched successfully.
* ESP_ERR_INVALID_ARG: Null pointer provided for configuration.
* ESP_FAIL: Hardware initialization failure.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `config` | const [`h1os_lifecycle_t`](#h1os_lifecycle_t) * | Pointer to valid lifecycle configuration structure. Must not be NULL. |

---

{#h1os_get_telemetry-1}

### h1os_get_telemetry

```cpp
esp_err_t h1os_get_telemetry(h1os_telemetry_t * out_telemetry)
```

Defined in h1os_lifecycle.c:466

Retrieve current Tri-Node environmental telemetry.

#### Returns
ESP_OK on success, or an error code.

Copies the latest validated psychrometric invariants, sensor readings, and battery metrics into the caller-provided telemetry structure.

#### Returns

* ESP_OK: Telemetry snapshot copied successfully.
* ESP_ERR_INVALID_ARG: Null pointer passed.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_telemetry` | [`h1os_telemetry_t`](#h1os_telemetry_t) * | Pointer to destination telemetry structure. Must not be NULL. |

---

{#h1os_sleep-1}

### h1os_sleep

```cpp
esp_err_t h1os_sleep(uint32_t sleep_sec)
```

Defined in h1os_lifecycle.c:534

Put the platform into ultra-low-power deep sleep.

#### Returns
ESP_OK on success, or an error code.

Arms the PCF85063A countdown timer, isolates GPIO sleep pads, holds power latch, and enters ESP32-S3 deep sleep.

#### Returns

* ESP_OK: Sleep transition armed.
* ESP_ERR_INVALID_ARG: sleep_sec out of supported hardware range.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `sleep_sec` | `uint32_t` | Duration of sleep in seconds before hardware wake. |

---

{#execute_system_shutdown}

### execute_system_shutdown

`static`

```cpp
static void execute_system_shutdown(bool force_clean_white)
```

Defined in h1os_lifecycle.c:560

Execute system shutdown.

#### Returns
Return value of type static void.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `force_clean_white` | `bool` | Parameter force_clean_white. |

---

{#h1os_shutdown-1}

### h1os_shutdown

```cpp
void h1os_shutdown(void)
```

Defined in h1os_lifecycle.c:609

Orderly system shutdown and physical battery power cut.

Invokes lifecycle on_shutdown hook, safely isolates peripherals, deactivates displays, and releases GPIO 17 BAT_CTRL power latch.

---

{#h1os_shutdown_for_storage-1}

### h1os_shutdown_for_storage

```cpp
void h1os_shutdown_for_storage(void)
```

Defined in h1os_lifecycle.c:623

Shutdown for long-term storage: clears display to pure white before cutting power.

Shutdown for long-term storage.

Protects e-Paper electrophoretic microcapsules against permanent dye migration and burn-in.

Shutdown for long-term storage: clears display to pure white before cutting power.

Performs pure white full OTP refresh on electrophoretic display before cutting power latch, protecting e-Paper microcapsules against dye migration and burn-in.

---

{#h1os_set_volume-1}

### h1os_set_volume

```cpp
esp_err_t h1os_set_volume(uint8_t volume_pct)
```

Defined in h1os_lifecycle.c:635

Set audio subsystem output volume percentage (0% = Mute, 100% = 0 dB Max).

Set audio subsystem output volume percentage.

#### Returns
ESP_OK on success, or an error code.

Set audio subsystem output volume percentage (0% = Mute, 100% = 0 dB Max).

Controls ES8311 DAC gain and NS4168 power state. 0% volume automatically mutes the output and puts the amplifier into low-power standby.

#### Returns

* ESP_OK: Volume level configured successfully.
* ESP_ERR_INVALID_STATE: Audio subsystem not initialized.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `volume_pct` | `uint8_t` | Desired volume percentage (0 = Mute, 100 = 0 dB Maximum). |

---

{#bootloader_hooks_include}

### bootloader_hooks_include

```cpp
void bootloader_hooks_include(void)
```

Defined in h1os_boot_hook.c:29

Dummy symbol to enforce linker inclusion of 2nd-stage bootloader hooks.

---

{#bootloader_before_init}

### bootloader_before_init

```cpp
void bootloader_before_init(void)
```

Defined in h1os_boot_hook.c:41

FIRST HOOK: Executes before any bootloader hardware initialization.

* Flash cache is DOWN, console is not configured (do NOT call ESP_LOG here). Immediately latches BAT_CTRL (GPIO 17) HIGH in < 25ms. Explicitly connects SIG_GPIO_OUT_IDX to prevent reliance on reset defaults.

---

{#bootloader_after_init}

### bootloader_after_init

```cpp
void bootloader_after_init(void)
```

Defined in h1os_boot_hook.c:77

SECOND HOOK: Executes after standard bootloader initialization.

* Console, SPI Flash cache, and clocks are now valid; ESP_LOG is operational.

---

{#orch_wake_stub_install}

### orch_wake_stub_install

```cpp
void orch_wake_stub_install(void)
```

Defined in h1os/orch_wake_stub.h:25

Install the deep sleep wake stub into RTC Fast Memory.

Install the RTC deep sleep wake stub.

Registers [bsp_wake_stub()](#bsp_wake_stub) with esp_set_deep_sleep_wake_stub().

Install the deep sleep wake stub into RTC Fast Memory.

Called before entering deep sleep to arm the ultra-fast wake stub handler.

---

{#bsp_wake_stub}

### bsp_wake_stub

```cpp
void bsp_wake_stub(void)
```

Defined in h1os/orch_wake_stub.h:33

Second-stage wake stub executed directly in RTC Fast Memory upon deep sleep wake.

Master RTC Wake Stub entry function.

Executes fast sub-3ms Flow A sensor bursts using bitbanged I2C without booting the main ESP-IDF OS or spinning up the 160/240 MHz PLL clocks.

Second-stage wake stub executed directly in RTC Fast Memory upon deep sleep wake.

Marked with RTC_IRAM_ATTR to reside in RTC Fast Memory.

#### Returns
Return value of type void RTC_IRAM_ATTR.

---

{#i2c_delay}

### i2c_delay

`static` `inline`

```cpp
static inline void RTC_IRAM_ATTR i2c_delay(void)
```

Defined in orch_wake_stub.c:60

I2c delay.

#### Returns
Return value of type static inline void RTC_IRAM_ATTR.

---

{#sda_high}

### sda_high

`static` `inline`

```cpp
static inline void RTC_IRAM_ATTR sda_high(void)
```

Defined in orch_wake_stub.c:70

Sda high.

#### Returns
Return value of type static inline void RTC_IRAM_ATTR.

---

{#sda_low}

### sda_low

`static` `inline`

```cpp
static inline void RTC_IRAM_ATTR sda_low(void)
```

Defined in orch_wake_stub.c:80

Sda low.

#### Returns
Return value of type static inline void RTC_IRAM_ATTR.

---

{#scl_high}

### scl_high

`static` `inline`

```cpp
static inline void RTC_IRAM_ATTR scl_high(void)
```

Defined in orch_wake_stub.c:91

Scl high.

#### Returns
Return value of type static inline void RTC_IRAM_ATTR.

---

{#scl_low}

### scl_low

`static` `inline`

```cpp
static inline void RTC_IRAM_ATTR scl_low(void)
```

Defined in orch_wake_stub.c:101

Scl low.

#### Returns
Return value of type static inline void RTC_IRAM_ATTR.

---

{#sda_read}

### sda_read

`static` `inline`

```cpp
static inline uint8_t RTC_IRAM_ATTR sda_read(void)
```

Defined in orch_wake_stub.c:112

Sda read.

#### Returns
Return value of type static inline uint8_t RTC_IRAM_ATTR.

---

{#i2c_start}

### i2c_start

`static`

```cpp
static void RTC_IRAM_ATTR i2c_start(void)
```

Defined in orch_wake_stub.c:122

Start i2c_start background operations.

#### Returns
Return value of type static void RTC_IRAM_ATTR.

---

{#i2c_stop}

### i2c_stop

`static`

```cpp
static void RTC_IRAM_ATTR i2c_stop(void)
```

Defined in orch_wake_stub.c:138

Stop i2c_stop background operations.

#### Returns
Return value of type static void RTC_IRAM_ATTR.

---

{#i2c_write_byte}

### i2c_write_byte

`static`

```cpp
static bool RTC_IRAM_ATTR i2c_write_byte(uint8_t byte)
```

Defined in orch_wake_stub.c:155

I2c write byte.

#### Returns
True on success, false otherwise.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `byte` | `uint8_t` | Parameter byte. |

---

{#i2c_read_byte}

### i2c_read_byte

`static`

```cpp
static uint8_t RTC_IRAM_ATTR i2c_read_byte(bool ack)
```

Defined in orch_wake_stub.c:187

I2c read byte.

#### Returns
Return value of type static uint8_t RTC_IRAM_ATTR.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `ack` | `bool` | Parameter ack. |

---

{#shtc3_crc8}

### shtc3_crc8

`static`

```cpp
static uint8_t RTC_IRAM_ATTR shtc3_crc8(const uint8_t * data, size_t len)
```

Defined in orch_wake_stub.c:225

Shtc3 crc8.

#### Returns
Return value of type static uint8_t RTC_IRAM_ATTR.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `data` | `const uint8_t *` | Parameter data. |
| `len` | `size_t` | Parameter len. |

---

{#wake_stub_read_die_temp_centi_c}

### wake_stub_read_die_temp_centi_c

`static`

```cpp
static int16_t RTC_IRAM_ATTR wake_stub_read_die_temp_centi_c(int16_t offset_centi_c, int16_t fallback_centi_c)
```

Defined in orch_wake_stub.c:249

Read internal ESP32-S3 SAR temperature sensor in centi-degrees Celsius using Q12 fixed-point math.

#### Returns
Sampled die temperature in centi-°C.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `offset_centi_c` | `int16_t` | Pre-computed intercept (2052 + tsens_cal_centi_c). |
| `fallback_centi_c` | `int16_t` | Fallback temperature if conversion fails. |

---

{#rtc_write_reg_retry}

### rtc_write_reg_retry

`static`

```cpp
static bool RTC_IRAM_ATTR rtc_write_reg_retry(uint8_t reg, uint8_t val)
```

Defined in orch_wake_stub.c:287

Write a register to PCF85063A over bit-banged I2C with up to 3 attempts.

---

{#rtc_rearm_countdown_stub}

### rtc_rearm_countdown_stub

`static`

```cpp
static void RTC_IRAM_ATTR rtc_rearm_countdown_stub(uint32_t seconds)
```

Defined in orch_wake_stub.c:311

Re-arm PCF85063A countdown timer in RTC Fast IRAM for remainder interval.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `seconds` | `uint32_t` | Remaining countdown interval in seconds. |

---

{#shtc3_send_sleep}

### shtc3_send_sleep

`static`

```cpp
static bool RTC_IRAM_ATTR shtc3_send_sleep(void)
```

Defined in orch_wake_stub.c:347

Reliable SHTC3 sleep dispatch with ACK verification.

#### Returns
Return value of sleep command wright status.

---

{#bsp_wake_stub-1}

### bsp_wake_stub

```cpp
void RTC_IRAM_ATTR bsp_wake_stub(void)
```

Defined in orch_wake_stub.c:371

Master RTC Wake Stub entry function.

Second-stage wake stub executed directly in RTC Fast Memory upon deep sleep wake.

Marked with RTC_IRAM_ATTR to reside in RTC Fast Memory.

#### Returns
Return value of type void RTC_IRAM_ATTR.

Master RTC Wake Stub entry function.

Executes fast sub-3ms Flow A sensor bursts using bitbanged I2C without booting the main ESP-IDF OS or spinning up the 160/240 MHz PLL clocks.

---

{#orch_wake_stub_install-1}

### orch_wake_stub_install

```cpp
void orch_wake_stub_install(void)
```

Defined in orch_wake_stub.c:535

Install the RTC deep sleep wake stub.

Install the deep sleep wake stub into RTC Fast Memory.

Called before entering deep sleep to arm the ultra-fast wake stub handler.

Install the RTC deep sleep wake stub.

Registers [bsp_wake_stub()](#bsp_wake_stub-1) with esp_set_deep_sleep_wake_stub().

---

{#orch_display_sync_mark_dirty}

### orch_display_sync_mark_dirty

```cpp
void orch_display_sync_mark_dirty(void)
```

Defined in h1os/orch_display_sync.h:23

Mark current display frame as dirty, scheduling a deferred SPI flash backup.

Mark the current display framebuffer as dirty (needs flash persistence on sleep).

Mark current display frame as dirty, scheduling a deferred SPI flash backup.

---

{#orch_display_sync_save_if_dirty}

### orch_display_sync_save_if_dirty

```cpp
esp_err_t orch_display_sync_save_if_dirty(void)
```

Defined in h1os/orch_display_sync.h:32

Commit active display framebuffer to SPI flash if marked dirty.

Save working display framebuffer to "epd_frame" flash partition if dirty.

#### Returns

* ESP_OK: Flash partition written or buffer not dirty.
* ESP_FAIL: Flash write failed.

Commit active display framebuffer to SPI flash if marked dirty.

#### Returns
ESP_OK on success or if clean (no write needed).

---

{#orch_display_sync_restore_to_framebuffer}

### orch_display_sync_restore_to_framebuffer

```cpp
esp_err_t orch_display_sync_restore_to_framebuffer(void)
```

Defined in h1os/orch_display_sync.h:41

Restore preserved display framebuffer from SPI flash into RAM buffer.

Restore framebuffer from "epd_frame" flash partition into display working buffer.

#### Returns

* ESP_OK: Previous frame restored successfully.
* ESP_FAIL: Flash read error.

Restore preserved display framebuffer from SPI flash into RAM buffer.

#### Returns
ESP_OK on success, ESP_ERR_NOT_FOUND if partition empty/invalid.

---

{#orch_display_sync_should_full_refresh}

### orch_display_sync_should_full_refresh

```cpp
bool orch_display_sync_should_full_refresh(void)
```

Defined in h1os/orch_display_sync.h:50

Determine whether the next display update requires a full OTP flash refresh.

Determine if a full OTP display refresh is required.

Evaluates monotonic partial refresh counter against panel DC bias clearance quota (typically 6).

#### Returns
True if full refresh is mandated to prevent panel ghosting/burn-in.

Determine whether the next display update requires a full OTP flash refresh.

Evaluates whether the anti-ghosting partial refresh limit has been reached.

#### Returns
true if full refresh required, false if differential partial refresh is permitted.

---

{#orch_display_sync_record_partial_refresh}

### orch_display_sync_record_partial_refresh

```cpp
void orch_display_sync_record_partial_refresh(void)
```

Defined in h1os/orch_display_sync.h:55

Increment the consecutive partial refresh counter.

Record execution of a differential partial refresh.

Increment the consecutive partial refresh counter.

Increments the accumulated partial refresh counter in persistent RTC memory.

---

{#orch_display_sync_record_full_refresh}

### orch_display_sync_record_full_refresh

```cpp
void orch_display_sync_record_full_refresh(void)
```

Defined in h1os/orch_display_sync.h:60

Reset the partial refresh counter following a full OTP refresh.

Record execution of a full OTP display refresh.

Reset the partial refresh counter following a full OTP refresh.

Resets the accumulated partial refresh counter back to 0.

---

{#orch_display_sync_get_partial_count}

### orch_display_sync_get_partial_count

```cpp
uint16_t orch_display_sync_get_partial_count(void)
```

Defined in h1os/orch_display_sync.h:67

Retrieve current monotonic partial refresh counter value.

Get the accumulated count of partial refreshes since the last full refresh.

#### Returns
Number of partial refreshes executed since last full refresh.

Retrieve current monotonic partial refresh counter value.

#### Returns
Return value of type uint16_t.

---

{#orch_display_sync_latch_glass_temp}

### orch_display_sync_latch_glass_temp

`static` `inline`

```cpp
static inline void orch_display_sync_latch_glass_temp(void)
```

Defined in orch_display_sync.c:30

Synchronize latest SSD1681 on-glass temperature into persisted RTC state.

---

{#orch_display_sync_mark_dirty-1}

### orch_display_sync_mark_dirty

```cpp
void orch_display_sync_mark_dirty(void)
```

Defined in orch_display_sync.c:41

Mark the current display framebuffer as dirty (needs flash persistence on sleep).

Mark current display frame as dirty, scheduling a deferred SPI flash backup.

Mark the current display framebuffer as dirty (needs flash persistence on sleep).

---

{#orch_display_sync_save_if_dirty-1}

### orch_display_sync_save_if_dirty

```cpp
esp_err_t orch_display_sync_save_if_dirty(void)
```

Defined in orch_display_sync.c:52

Save working display framebuffer to "epd_frame" flash partition if dirty.

Commit active display framebuffer to SPI flash if marked dirty.

#### Returns
ESP_OK on success or if clean (no write needed).

Save working display framebuffer to "epd_frame" flash partition if dirty.

#### Returns

* ESP_OK: Flash partition written or buffer not dirty.
* ESP_FAIL: Flash write failed.

---

{#orch_display_sync_restore_to_framebuffer-1}

### orch_display_sync_restore_to_framebuffer

```cpp
esp_err_t orch_display_sync_restore_to_framebuffer(void)
```

Defined in orch_display_sync.c:79

Restore framebuffer from "epd_frame" flash partition into display working buffer.

Restore preserved display framebuffer from SPI flash into RAM buffer.

#### Returns
ESP_OK on success, ESP_ERR_NOT_FOUND if partition empty/invalid.

Restore framebuffer from "epd_frame" flash partition into display working buffer.

#### Returns

* ESP_OK: Previous frame restored successfully.
* ESP_FAIL: Flash read error.

---

{#orch_display_sync_should_full_refresh-1}

### orch_display_sync_should_full_refresh

```cpp
bool orch_display_sync_should_full_refresh(void)
```

Defined in orch_display_sync.c:109

Determine if a full OTP display refresh is required.

Determine whether the next display update requires a full OTP flash refresh.

Evaluates whether the anti-ghosting partial refresh limit has been reached.

#### Returns
true if full refresh required, false if differential partial refresh is permitted.

Determine if a full OTP display refresh is required.

Evaluates monotonic partial refresh counter against panel DC bias clearance quota (typically 6).

#### Returns
True if full refresh is mandated to prevent panel ghosting/burn-in.

---

{#orch_display_sync_record_partial_refresh-1}

### orch_display_sync_record_partial_refresh

```cpp
void orch_display_sync_record_partial_refresh(void)
```

Defined in orch_display_sync.c:128

Record execution of a differential partial refresh.

Increment the consecutive partial refresh counter.

Increments the accumulated partial refresh counter in persistent RTC memory.

Record execution of a differential partial refresh.

---

{#orch_display_sync_record_full_refresh-1}

### orch_display_sync_record_full_refresh

```cpp
void orch_display_sync_record_full_refresh(void)
```

Defined in orch_display_sync.c:142

Record execution of a full OTP display refresh.

Reset the partial refresh counter following a full OTP refresh.

Resets the accumulated partial refresh counter back to 0.

Record execution of a full OTP display refresh.

---

{#orch_display_sync_get_partial_count-1}

### orch_display_sync_get_partial_count

```cpp
uint16_t orch_display_sync_get_partial_count(void)
```

Defined in orch_display_sync.c:154

Get the accumulated count of partial refreshes since the last full refresh.

Retrieve current monotonic partial refresh counter value.

#### Returns
Return value of type uint16_t.

Get the accumulated count of partial refreshes since the last full refresh.

#### Returns
Number of partial refreshes executed since last full refresh.

## Variables

---

{#wake_counter}

### wake_counter

```cpp
volatile uint32_t wake_counter = 0
```

Defined in main.c:22

---

{#last_wake_cause}

### last_wake_cause

```cpp
volatile uint32_t last_wake_cause = 0
```

Defined in main.c:23

---

{#last_wake_btn}

### last_wake_btn

```cpp
volatile uint32_t last_wake_btn = 0
```

Defined in main.c:24

---

{#slice_counter}

### slice_counter

```cpp
volatile uint32_t slice_counter = 0
```

Defined in main.c:25

---

{#overflow_limit}

### overflow_limit

```cpp
volatile uint32_t overflow_limit = 5
```

Defined in main.c:26

---

{#remainder_sec}

### remainder_sec

```cpp
volatile uint32_t remainder_sec = 0
```

Defined in main.c:27

---

{#rtc_int_stuck}

### rtc_int_stuck

```cpp
volatile uint32_t rtc_int_stuck = 0
```

Defined in main.c:28

---

{#dispatch_reason}

### dispatch_reason

```cpp
volatile uint32_t dispatch_reason = 0
```

Defined in main.c:29

---

{#gpio_status_raw}

### gpio_status_raw

```cpp
volatile uint32_t gpio_status_raw = 0
```

Defined in main.c:30

---

{#entry_ccount}

### entry_ccount

```cpp
volatile uint32_t entry_ccount = 0
```

Defined in main.c:31

---

{#exit_ccount}

### exit_ccount

```cpp
volatile uint32_t exit_ccount = 0
```

Defined in main.c:32

---

{#cal_scale}

### cal_scale

```cpp
volatile uint32_t cal_scale = 3100
```

Defined in main.c:34

---

{#cal_offset}

### cal_offset

```cpp
volatile int32_t cal_offset = 0
```

Defined in main.c:35

---

{#last_vbat_mv}

### last_vbat_mv

```cpp
volatile uint32_t last_vbat_mv = 4000
```

Defined in main.c:36

---

{#vbat_raw_adc}

### vbat_raw_adc

```cpp
volatile uint32_t vbat_raw_adc = 0
```

Defined in main.c:37

---

{#usb_connected}

### usb_connected

```cpp
volatile uint32_t usb_connected = 0
```

Defined in main.c:38

---

{#tag}

### TAG

`static`

```cpp
const char * TAG = "HAL_IO"
```

Defined in hal_io.c:23

---

{#s_led_pwm_active}

### s_led_pwm_active

`static`

```cpp
bool s_led_pwm_active = false
```

Defined in hal_io.c:114

---

{#s_breath_task}

### s_breath_task

`static`

```cpp
TaskHandle_t s_breath_task = NULL
```

Defined in hal_io.c:215

---

{#s_breathing_running}

### s_breathing_running

`static`

```cpp
volatile bool s_breathing_running = false
```

Defined in hal_io.c:216

---

{#s_breath_period_ms}

### s_breath_period_ms

`static`

```cpp
uint32_t s_breath_period_ms = 2000
```

Defined in hal_io.c:217

---

{#tag-1}

### TAG

`static`

```cpp
const char * TAG = "HAL_I2C"
```

Defined in hal_i2c.c:14

---

{#s_bus_handle}

### s_bus_handle

`static`

```cpp
i2c_master_bus_handle_t s_bus_handle = NULL
```

Defined in hal_i2c.c:16

---

{#s_i2c_mutex}

### s_i2c_mutex

`static`

```cpp
SemaphoreHandle_t s_i2c_mutex = NULL
```

Defined in hal_i2c.c:17

---

{#s_is_inited}

### s_is_inited

`static`

```cpp
bool s_is_inited = false
```

Defined in hal_i2c.c:18

---

{#tag-2}

### TAG

`static`

```cpp
const char * TAG = "HAL_SPI"
```

Defined in hal_spi.c:16

---

{#s_spi_dev}

### s_spi_dev

`static`

```cpp
spi_device_handle_t s_spi_dev = NULL
```

Defined in hal_spi.c:18

---

{#s_spi_read_dev}

### s_spi_read_dev

`static`

```cpp
spi_device_handle_t s_spi_read_dev = NULL
```

Defined in hal_spi.c:19

---

{#s_is_inited-1}

### s_is_inited

`static`

```cpp
bool s_is_inited = false
```

Defined in hal_spi.c:21

---

{#tag-3}

### TAG

`static`

```cpp
const char * TAG = "sub_nvs"
```

Defined in sub_nvs.c:18

---

{#s_nvs_initialized}

### s_nvs_initialized

`static`

```cpp
bool s_nvs_initialized = false
```

Defined in sub_nvs.c:19

---

{#tag-4}

### TAG

`static`

```cpp
const char * TAG = "sub_rtc"
```

Defined in sub_rtc.c:19

---

{#tag-5}

### TAG

`static`

```cpp
const char * TAG = "h1os_time"
```

Defined in h1os_time.c:20

---

{#s_sync_cb}

### s_sync_cb

`static`

```cpp
h1os_time_sync_cb_t s_sync_cb = NULL
```

Type: [`h1os_time_sync_cb_t`](#h1os_time_sync_cb_t)

Defined in h1os_time.c:22

---

{#s_sync_user_data}

### s_sync_user_data

`static`

```cpp
void * s_sync_user_data = NULL
```

Defined in h1os_time.c:23

---

{#tag-6}

### TAG

`static`

```cpp
const char * TAG = "HAL_FLASH"
```

Defined in hal_flash.c:16

---

{#s_part}

### s_part

`static`

```cpp
const esp_partition_t * s_part = NULL
```

Defined in hal_flash.c:18

---

{#tag-7}

### TAG

`static`

```cpp
const char * TAG = "orch_flow"
```

Defined in orch_flow.c:31

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

Defined in sub_audio.c:76

---

{#s_audio_inited}

### s_audio_inited

`static`

```cpp
bool s_audio_inited = false
```

Defined in sub_audio.c:78

---

{#s_i2s_chan_enabled}

### s_i2s_chan_enabled

`static`

```cpp
bool s_i2s_chan_enabled = false
```

Defined in sub_audio.c:79

---

{#s_codec_in_standby}

### s_codec_in_standby

`static`

```cpp
bool s_codec_in_standby = false
```

Defined in sub_audio.c:80

---

{#s_pa_enabled}

### s_pa_enabled

`static`

```cpp
bool s_pa_enabled = false
```

Defined in sub_audio.c:81

---

{#s_low_power_mode}

### s_low_power_mode

`static`

```cpp
bool s_low_power_mode = true
```

Defined in sub_audio.c:82

---

{#s_rtc_codec_in_standby}

### s_rtc_codec_in_standby

`static`

```cpp
RTC_DATA_ATTR bool s_rtc_codec_in_standby = false
```

Defined in sub_audio.c:84

---

{#s_audio_queue}

### s_audio_queue

`static`

```cpp
QueueHandle_t s_audio_queue = NULL
```

Defined in sub_audio.c:86

---

{#s_audio_task_handle}

### s_audio_task_handle

`static`

```cpp
TaskHandle_t s_audio_task_handle = NULL
```

Defined in sub_audio.c:87

---

{#s_audio_is_busy}

### s_audio_is_busy

`static`

```cpp
volatile bool s_audio_is_busy = false
```

Defined in sub_audio.c:88

---

{#s_volume_pct}

### s_volume_pct

`static`

```cpp
uint8_t s_volume_pct = 0
```

Defined in sub_audio.c:90

---

{#s_cmd_sync_sem_buffer}

### s_cmd_sync_sem_buffer

`static`

```cpp
StaticSemaphore_t s_cmd_sync_sem_buffer
```

Defined in sub_audio.c:92

---

{#s_cmd_sync_sem}

### s_cmd_sync_sem

`static`

```cpp
SemaphoreHandle_t s_cmd_sync_sem = NULL
```

Defined in sub_audio.c:93

---

{#s_audio_work_buffer}

### s_audio_work_buffer

`static`

```cpp
int16_t s_audio_work_buffer[0x100]
```

Defined in sub_audio.c:94

---

{#es8311_perceptual_vol_table}

### es8311_perceptual_vol_table

`static`

```cpp
const uint8_t es8311_perceptual_vol_table[101]
```

Defined in sub_audio.c:127

---

{#s_es8311_init_pre_charge}

### s_es8311_init_pre_charge

`static`

```cpp
const es8311_reg_entry_t s_es8311_init_pre_charge[]
```

Defined in sub_audio.c:152

---

{#s_es8311_init_post_charge}

### s_es8311_init_post_charge

`static`

```cpp
const es8311_reg_entry_t s_es8311_init_post_charge[]
```

Defined in sub_audio.c:196

---

{#s_es8311_deinit}

### s_es8311_deinit

`static`

```cpp
const es8311_reg_entry_t s_es8311_deinit[]
```

Defined in sub_audio.c:218

---

{#tag-9}

### TAG

`static`

```cpp
const char * TAG = "sub_power"
```

Defined in sub_power.c:34

---

{#s_adc_handle}

### s_adc_handle

`static`

```cpp
adc_oneshot_unit_handle_t s_adc_handle = NULL
```

Defined in sub_power.c:36

---

{#s_cali_handle}

### s_cali_handle

`static`

```cpp
adc_cali_handle_t s_cali_handle = NULL
```

Defined in sub_power.c:37

---

{#s_cali_valid}

### s_cali_valid

`static`

```cpp
bool s_cali_valid = false
```

Defined in sub_power.c:38

---

{#s_flow_a_sec}

### s_flow_a_sec

`static`

```cpp
uint32_t s_flow_a_sec = 60
```

Defined in sub_power.c:40

---

{#s_flow_b_sec}

### s_flow_b_sec

`static`

```cpp
uint32_t s_flow_b_sec = 300
```

Defined in sub_power.c:41

---

{#s_overflow_limit}

### s_overflow_limit

`static`

```cpp
uint32_t s_overflow_limit = 5
```

Defined in sub_power.c:42

---

{#s_remainder_sec}

### s_remainder_sec

`static`

```cpp
uint32_t s_remainder_sec = 0
```

Defined in sub_power.c:43

---

{#s_lipo_table}

### s_lipo_table

`static`

```cpp
const struct @103206253010331351125062271206070174360205162247 s_lipo_table[]
```

Defined in sub_power.c:63

---

{#s_persisted_state}

### s_persisted_state

`static`

```cpp
RTC_NOINIT_ATTR volatile orch_persisted_state_t s_persisted_state
```

Type: RTC_NOINIT_ATTR volatile [`orch_persisted_state_t`](#orch_persisted_state_t)

Defined in orch_state.c:16

---

{#tag-10}

### TAG

`static`

```cpp
const char * TAG = "sub_sdcard"
```

Defined in sub_sdcard.c:23

---

{#s_sd_card}

### s_sd_card

`static`

```cpp
sdmmc_card_t * s_sd_card = NULL
```

Defined in sub_sdcard.c:25

---

{#s_mount_task}

### s_mount_task

`static`

```cpp
TaskHandle_t s_mount_task = NULL
```

Defined in sub_sdcard.c:26

---

{#s_card_absent_latched}

### s_card_absent_latched

`static`

```cpp
bool s_card_absent_latched = false
```

Defined in sub_sdcard.c:27

---

{#tag-11}

### TAG

`static`

```cpp
const char * TAG = "h1os_lvgl"
```

Defined in h1os_lvgl.cpp:31

---

{#s_lv_display}

### s_lv_display

`static`

```cpp
lv_display_t * s_lv_display = NULL
```

Defined in h1os_lvgl.cpp:33

---

{#s_lv_keypad_indev}

### s_lv_keypad_indev

`static`

```cpp
lv_indev_t * s_lv_keypad_indev = NULL
```

Defined in h1os_lvgl.cpp:34

---

{#s_lvgl_task_handle}

### s_lvgl_task_handle

`static`

```cpp
TaskHandle_t s_lvgl_task_handle = NULL
```

Defined in h1os_lvgl.cpp:35

---

{#s_lvgl_task_running}

### s_lvgl_task_running

`static`

```cpp
volatile bool s_lvgl_task_running = false
```

Defined in h1os_lvgl.cpp:37

---

{#s_flush_in_progress}

### s_flush_in_progress

`static`

```cpp
volatile bool s_flush_in_progress = false
```

Defined in h1os_lvgl.cpp:38

---

{#s_first_boot_flush}

### s_first_boot_flush

`static`

```cpp
bool s_first_boot_flush = true
```

Defined in h1os_lvgl.cpp:39

---

{#tag-12}

### TAG

`static`

```cpp
const char * TAG = "sub_display"
```

Defined in sub_display.cpp:24

---

{#s_current_frame}

### s_current_frame

`static`

```cpp
uint8_t s_current_frame[((200 *200)/8)]
```

Defined in sub_display.cpp:26

---

{#s_previous_frame}

### s_previous_frame

`static`

```cpp
uint8_t s_previous_frame[((200 *200)/8)]
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

{#s_in_deep_sleep}

### s_in_deep_sleep

`static`

```cpp
bool s_in_deep_sleep = false
```

Defined in sub_display.cpp:30

---

{#s_last_glass_temp_centi_c}

### s_last_glass_temp_centi_c

`static`

```cpp
int16_t s_last_glass_temp_centi_c = 0
```

Defined in sub_display.cpp:31

---

{#wf_partial_1in54}

### WF_PARTIAL_1IN54

`static`

```cpp
const uint8_t WF_PARTIAL_1IN54[159]
```

Defined in sub_display.cpp:33

---

{#tag-13}

### TAG

`static`

```cpp
const char * TAG = "h1os_lifecycle"
```

Defined in h1os_lifecycle.c:36

---

{#s_app_lifecycle}

### s_app_lifecycle

`static`

```cpp
h1os_lifecycle_t s_app_lifecycle = {0}
```

Type: [`h1os_lifecycle_t`](#h1os_lifecycle_t)

Defined in h1os_lifecycle.c:38

---

{#s_session_expiry_us}

### s_session_expiry_us

`static`

```cpp
int64_t s_session_expiry_us = 0
```

Defined in h1os_lifecycle.c:39

---

{#s_session_task_handle}

### s_session_task_handle

`static`

```cpp
TaskHandle_t s_session_task_handle = NULL
```

Defined in h1os_lifecycle.c:40

---

{#s_session_running}

### s_session_running

`static`

```cpp
bool s_session_running = false
```

Defined in h1os_lifecycle.c:41

---

{#s_audio_initialized}

### s_audio_initialized

`static`

```cpp
bool s_audio_initialized = false
```

Defined in h1os_lifecycle.c:42

---

{#tag-14}

### TAG

`static`

```cpp
const char * TAG = "H1OS_BOOT_HOOK"
```

Defined in h1os_boot_hook.c:24

---

{#tag-15}

### TAG

`static`

```cpp
const char * TAG = "orch_display_sync"
```

Defined in orch_display_sync.c:23

---

{#s_frame_dirty}

### s_frame_dirty

`static`

```cpp
bool s_frame_dirty = false
```

Defined in orch_display_sync.c:25

{#audio_cmd_t}

## audio_cmd_t

```cpp
struct audio_cmd_t
```

Defined in sub_audio.c:50

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

Defined in sub_audio.c:51

---

{#params}

#### params

```cpp
union audio_cmd_t::@075142260334247171354103021266123360172342241057 params
```

Defined in sub_audio.c:65

---

{#done_sem}

#### done_sem

```cpp
SemaphoreHandle_t done_sem
```

Defined in sub_audio.c:67

---

{#result}

#### result

```cpp
esp_err_t * result
```

Defined in sub_audio.c:68

{#unionparams}

## [union].params

```cpp
union [union].params
```

Defined in sub_audio.c:52

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

Defined in sub_audio.c:56

---

{#chime}

#### chime

```cpp
struct audio_cmd_t::@075142260334247171354103021266123360172342241057::@035007020164214261121213220013133270155350134061 chime
```

Defined in sub_audio.c:59

---

{#pcm}

#### pcm

```cpp
struct audio_cmd_t::@075142260334247171354103021266123360172342241057::@174042257255263212372236347353345125072343133315 pcm
```

Defined in sub_audio.c:64

{#structparamstone}

## [struct].params.tone

```cpp
struct [struct].params.tone
```

Defined in sub_audio.c:53

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

Defined in sub_audio.c:54

---

{#duration_ms}

#### duration_ms

```cpp
uint32_t duration_ms
```

Defined in sub_audio.c:55

{#structparamschime}

## [struct].params.chime

```cpp
struct [struct].params.chime
```

Defined in sub_audio.c:57

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

Defined in sub_audio.c:58

{#structparamspcm}

## [struct].params.pcm

```cpp
struct [struct].params.pcm
```

Defined in sub_audio.c:60

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

Defined in sub_audio.c:61

---

{#sample_count}

#### sample_count

```cpp
size_t sample_count
```

Defined in sub_audio.c:62

---

{#sample_rate_hz}

#### sample_rate_hz

```cpp
uint32_t sample_rate_hz
```

Defined in sub_audio.c:63

{#h1os_lifecycle_t}

## h1os_lifecycle_t

```cpp
#include <h1os/h1os.h>
```

```cpp
struct h1os_lifecycle_t
```

Defined in h1os/h1os.h:100

Declarative application lifecycle configuration structure.

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| [`h1os_boot_cb_t`](#h1os_boot_cb_t) | [`on_boot`](#on_boot)  | System boot / power-on reset hook. |
| [`h1os_wake_cb_t`](#h1os_wake_cb_t) | [`on_wake`](#on_wake)  | Interactive wake hook (Timer / RTC Alarm / Button Tap). |
| [`h1os_pre_sleep_cb_t`](#h1os_pre_sleep_cb_t) | [`on_pre_sleep`](#on_pre_sleep)  | Hook executed immediately prior to entering deep sleep. |
| [`h1os_shutdown_cb_t`](#h1os_shutdown_cb_t) | [`on_shutdown`](#on_shutdown)  | Hook executed immediately prior to battery power cut. |
| `struct h1os_lifecycle_t::@325134365353002276205315372127306003103261015120` | [`presentation`](#presentation)  |  |
| `struct h1os_lifecycle_t::@146034141124024227100041106135372254367321170003` | [`session`](#session)  |  |
| `void *` | [`user_data`](#user_data)  | Arbitrary user context pointer passed to lifecycle hooks. |

---

{#on_boot}

#### on_boot

```cpp
h1os_boot_cb_t on_boot
```

Type: [`h1os_boot_cb_t`](#h1os_boot_cb_t)

Defined in h1os/h1os.h:101

System boot / power-on reset hook.

---

{#on_wake}

#### on_wake

```cpp
h1os_wake_cb_t on_wake
```

Type: [`h1os_wake_cb_t`](#h1os_wake_cb_t)

Defined in h1os/h1os.h:102

Interactive wake hook (Timer / RTC Alarm / Button Tap).

---

{#on_pre_sleep}

#### on_pre_sleep

```cpp
h1os_pre_sleep_cb_t on_pre_sleep
```

Type: [`h1os_pre_sleep_cb_t`](#h1os_pre_sleep_cb_t)

Defined in h1os/h1os.h:103

Hook executed immediately prior to entering deep sleep.

---

{#on_shutdown}

#### on_shutdown

```cpp
h1os_shutdown_cb_t on_shutdown
```

Type: [`h1os_shutdown_cb_t`](#h1os_shutdown_cb_t)

Defined in h1os/h1os.h:104

Hook executed immediately prior to battery power cut.

---

{#presentation}

#### presentation

```cpp
struct h1os_lifecycle_t::@325134365353002276205315372127306003103261015120 presentation
```

Defined in h1os/h1os.h:111

---

{#session}

#### session

```cpp
struct h1os_lifecycle_t::@146034141124024227100041106135372254367321170003 session
```

Defined in h1os/h1os.h:118

---

{#user_data}

#### user_data

```cpp
void * user_data
```

Defined in h1os/h1os.h:120

Arbitrary user context pointer passed to lifecycle hooks.

{#structpresentation}

## [struct].presentation

```cpp
struct [struct].presentation
```

Defined in h1os/h1os.h:106

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| [`h1os_splash_cb_t`](#h1os_splash_cb_t) | [`on_splash`](#on_splash)  | Presentation splash screen rendering hook. |
| [`h1os_chime_cb_t`](#h1os_chime_cb_t) | [`on_chime`](#on_chime)  | Presentation chime playback hook. |
| `uint8_t` | [`chime_mask`](#chime_mask)  | Bitmask of enabled audio chime types. |
| `uint8_t` | [`volume_pct`](#volume_pct)  | Acoustic presentation master volume (0..100%). |

---

{#on_splash}

#### on_splash

```cpp
h1os_splash_cb_t on_splash
```

Type: [`h1os_splash_cb_t`](#h1os_splash_cb_t)

Defined in h1os/h1os.h:107

Presentation splash screen rendering hook.

---

{#on_chime}

#### on_chime

```cpp
h1os_chime_cb_t on_chime
```

Type: [`h1os_chime_cb_t`](#h1os_chime_cb_t)

Defined in h1os/h1os.h:108

Presentation chime playback hook.

---

{#chime_mask}

#### chime_mask

```cpp
uint8_t chime_mask
```

Defined in h1os/h1os.h:109

Bitmask of enabled audio chime types.

---

{#volume_pct}

#### volume_pct

```cpp
uint8_t volume_pct
```

Defined in h1os/h1os.h:110

Acoustic presentation master volume (0..100%).

{#structsession}

## [struct].session

```cpp
struct [struct].session
```

Defined in h1os/h1os.h:113

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint32_t` | [`inactivity_timeout_sec`](#inactivity_timeout_sec)  | Interactive session idle sleep timeout in seconds. |
| [`sys_clk_mode_t`](#sys_clk_mode_t) | [`clk_mode`](#clk_mode)  | CPU clock scaling mode (SYS_CLK_MODE_DYNAMIC by default). |
| `uint32_t` | [`flow_a_period_sec`](#flow_a_period_sec)  | Period between headless sensor sample bursts in seconds. |
| `uint32_t` | [`flow_b_period_sec`](#flow_b_period_sec)  | Period between unattended display flushes in seconds. |

---

{#inactivity_timeout_sec}

#### inactivity_timeout_sec

```cpp
uint32_t inactivity_timeout_sec
```

Defined in h1os/h1os.h:114

Interactive session idle sleep timeout in seconds.

---

{#clk_mode}

#### clk_mode

```cpp
sys_clk_mode_t clk_mode
```

Type: [`sys_clk_mode_t`](#sys_clk_mode_t)

Defined in h1os/h1os.h:115

CPU clock scaling mode (SYS_CLK_MODE_DYNAMIC by default).

---

{#flow_a_period_sec}

#### flow_a_period_sec

```cpp
uint32_t flow_a_period_sec
```

Defined in h1os/h1os.h:116

Period between headless sensor sample bursts in seconds.

---

{#flow_b_period_sec}

#### flow_b_period_sec

```cpp
uint32_t flow_b_period_sec
```

Defined in h1os/h1os.h:117

Period between unattended display flushes in seconds.

{#h1os_telemetry_t}

## h1os_telemetry_t

```cpp
#include <h1os/h1os.h>
```

```cpp
struct h1os_telemetry_t
```

Defined in h1os/h1os.h:126

Comprehensive environmental telemetry and system metrics snapshot.

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `float` | [`ambient_temp_c`](#ambient_temp_c)  | Trusted steady-state SHTC3 ambient temperature in degrees Celsius. |
| `float` | [`ambient_temp_f`](#ambient_temp_f)  | Trusted steady-state SHTC3 ambient temperature in degrees Fahr. |
| `float` | [`ambient_rh_pct`](#ambient_rh_pct)  | Trusted steady-state SHTC3 relative humidity percentage (0..100%). |
| `float` | [`dew_point_c`](#dew_point_c)  | Psychrometrically calculated dew point in degrees Celsius. |
| `float` | [`dew_point_f`](#dew_point_f)  | Psychrometrically calculated dew point in degrees Fahrenheit. |
| `float` | [`vapor_pressure_hpa`](#vapor_pressure_hpa)  | Calculated water vapor partial pressure in hectopascals (hPa). |
| `float` | [`absolute_humidity_g`](#absolute_humidity_g)  | Calculated absolute humidity in grams per cubic meter (g/m³). |
| `float` | [`window_low_c`](#window_low_c)  | Valid Window Floor (minimum over valid 32-sample window). |
| `float` | [`window_high_c`](#window_high_c)  | Valid Window Ceiling (maximum over valid 32-sample window). |
| `float` | [`window_avg_shtc3_c`](#window_avg_shtc3_c)  | Short-term valid SHTC3 sensor window average in degrees Celsius. |
| `float` | [`window_avg_die_c`](#window_avg_die_c)  | Short-term valid MCU Die internal sensor window average. |
| `float` | [`temp_historical_c`](#temp_historical_c)  | Long-term light EWMA historical baseline temperature. |
| `float` | [`rh_historical_pct`](#rh_historical_pct)  | Long-term light EWMA historical baseline relative humidity. |
| `float` | [`raw_shtc3_temp_c`](#raw_shtc3_temp_c)  | Instantaneous raw Sensirion SHTC3 temperature in degrees Celsius. |
| `float` | [`mcu_die_temp_c`](#mcu_die_temp_c)  | Instantaneous ESP32-S3 internal TSENS die temperature. |
| `float` | [`epd_glass_temp_c`](#epd_glass_temp_c)  | Instantaneous SSD1681 display on-glass temperature sensor reading. |
| `float` | [`trinode_temp_c`](#trinode_temp_c)  | Tri-Node verification consensus: (T_valid + T_die + T_glass) / 3.0. |
| `float` | [`trinode_delta_c`](#trinode_delta_c)  | Cross-node verification delta: T_valid - T_trinode. |
| `uint8_t` | [`trinode_confidence_pct`](#trinode_confidence_pct)  | 0-100% cross-node range verification confidence score. |
| `bool` | [`is_thermally_settled`](#is_thermally_settled)  | True if steady-state thermal criteria (\|T2-T1\| <= gate) are met. |
| `uint16_t` | [`valid_trend`](#valid_trend)  | Monotonic count of consecutive thermally settled Flow A samples. |
| `uint32_t` | [`sample_count`](#sample_count-1)  | Total monotonic environmental telemetry sample count. |
| `uint32_t` | [`flow_a_period_sec`](#flow_a_period_sec-1)  | Active Flow A sensor sample interval in seconds. |
| `uint32_t` | [`flow_b_period_sec`](#flow_b_period_sec-1)  | Active Flow B display refresh interval in seconds. |
| `uint16_t` | [`battery_mv`](#battery_mv)  | Sampled battery terminal voltage in millivolts. |
| `uint16_t` | [`boot_vbat_mv`](#boot_vbat_mv)  | Initial non-USB battery voltage captured on boot in millivolts. |
| `uint8_t` | [`battery_percent`](#battery_percent)  | Estimated battery state-of-charge percentage (0..100%). |
| `bool` | [`is_usb_powered`](#is_usb_powered)  | True if USB VBUS power connection is actively detected. |

---

{#ambient_temp_c}

#### ambient_temp_c

```cpp
float ambient_temp_c
```

Defined in h1os/h1os.h:127

Trusted steady-state SHTC3 ambient temperature in degrees Celsius.

---

{#ambient_temp_f}

#### ambient_temp_f

```cpp
float ambient_temp_f
```

Defined in h1os/h1os.h:128

Trusted steady-state SHTC3 ambient temperature in degrees Fahr.

---

{#ambient_rh_pct}

#### ambient_rh_pct

```cpp
float ambient_rh_pct
```

Defined in h1os/h1os.h:129

Trusted steady-state SHTC3 relative humidity percentage (0..100%).

---

{#dew_point_c}

#### dew_point_c

```cpp
float dew_point_c
```

Defined in h1os/h1os.h:130

Psychrometrically calculated dew point in degrees Celsius.

---

{#dew_point_f}

#### dew_point_f

```cpp
float dew_point_f
```

Defined in h1os/h1os.h:131

Psychrometrically calculated dew point in degrees Fahrenheit.

---

{#vapor_pressure_hpa}

#### vapor_pressure_hpa

```cpp
float vapor_pressure_hpa
```

Defined in h1os/h1os.h:132

Calculated water vapor partial pressure in hectopascals (hPa).

---

{#absolute_humidity_g}

#### absolute_humidity_g

```cpp
float absolute_humidity_g
```

Defined in h1os/h1os.h:133

Calculated absolute humidity in grams per cubic meter (g/m³).

---

{#window_low_c}

#### window_low_c

```cpp
float window_low_c
```

Defined in h1os/h1os.h:135

Valid Window Floor (minimum over valid 32-sample window).

---

{#window_high_c}

#### window_high_c

```cpp
float window_high_c
```

Defined in h1os/h1os.h:136

Valid Window Ceiling (maximum over valid 32-sample window).

---

{#window_avg_shtc3_c}

#### window_avg_shtc3_c

```cpp
float window_avg_shtc3_c
```

Defined in h1os/h1os.h:137

Short-term valid SHTC3 sensor window average in degrees Celsius.

---

{#window_avg_die_c}

#### window_avg_die_c

```cpp
float window_avg_die_c
```

Defined in h1os/h1os.h:138

Short-term valid MCU Die internal sensor window average.

---

{#temp_historical_c}

#### temp_historical_c

```cpp
float temp_historical_c
```

Defined in h1os/h1os.h:139

Long-term light EWMA historical baseline temperature.

---

{#rh_historical_pct}

#### rh_historical_pct

```cpp
float rh_historical_pct
```

Defined in h1os/h1os.h:140

Long-term light EWMA historical baseline relative humidity.

---

{#raw_shtc3_temp_c}

#### raw_shtc3_temp_c

```cpp
float raw_shtc3_temp_c
```

Defined in h1os/h1os.h:142

Instantaneous raw Sensirion SHTC3 temperature in degrees Celsius.

---

{#mcu_die_temp_c}

#### mcu_die_temp_c

```cpp
float mcu_die_temp_c
```

Defined in h1os/h1os.h:143

Instantaneous ESP32-S3 internal TSENS die temperature.

---

{#epd_glass_temp_c}

#### epd_glass_temp_c

```cpp
float epd_glass_temp_c
```

Defined in h1os/h1os.h:144

Instantaneous SSD1681 display on-glass temperature sensor reading.

---

{#trinode_temp_c}

#### trinode_temp_c

```cpp
float trinode_temp_c
```

Defined in h1os/h1os.h:145

Tri-Node verification consensus: (T_valid + T_die + T_glass) / 3.0.

---

{#trinode_delta_c}

#### trinode_delta_c

```cpp
float trinode_delta_c
```

Defined in h1os/h1os.h:146

Cross-node verification delta: T_valid - T_trinode.

---

{#trinode_confidence_pct}

#### trinode_confidence_pct

```cpp
uint8_t trinode_confidence_pct
```

Defined in h1os/h1os.h:147

0-100% cross-node range verification confidence score.

---

{#is_thermally_settled}

#### is_thermally_settled

```cpp
bool is_thermally_settled
```

Defined in h1os/h1os.h:149

True if steady-state thermal criteria (|T2-T1| <= gate) are met.

---

{#valid_trend}

#### valid_trend

```cpp
uint16_t valid_trend
```

Defined in h1os/h1os.h:150

Monotonic count of consecutive thermally settled Flow A samples.

---

{#sample_count-1}

#### sample_count

```cpp
uint32_t sample_count
```

Defined in h1os/h1os.h:151

Total monotonic environmental telemetry sample count.

---

{#flow_a_period_sec-1}

#### flow_a_period_sec

```cpp
uint32_t flow_a_period_sec
```

Defined in h1os/h1os.h:152

Active Flow A sensor sample interval in seconds.

---

{#flow_b_period_sec-1}

#### flow_b_period_sec

```cpp
uint32_t flow_b_period_sec
```

Defined in h1os/h1os.h:153

Active Flow B display refresh interval in seconds.

---

{#battery_mv}

#### battery_mv

```cpp
uint16_t battery_mv
```

Defined in h1os/h1os.h:154

Sampled battery terminal voltage in millivolts.

---

{#boot_vbat_mv}

#### boot_vbat_mv

```cpp
uint16_t boot_vbat_mv
```

Defined in h1os/h1os.h:155

Initial non-USB battery voltage captured on boot in millivolts.

---

{#battery_percent}

#### battery_percent

```cpp
uint8_t battery_percent
```

Defined in h1os/h1os.h:156

Estimated battery state-of-charge percentage (0..100%).

---

{#is_usb_powered}

#### is_usb_powered

```cpp
bool is_usb_powered
```

Defined in h1os/h1os.h:157

True if USB VBUS power connection is actively detected.

{#cpumaxturboscope}

## CpuMaxTurboScope

```cpp
struct CpuMaxTurboScope
```

Defined in h1os_lvgl.cpp:43

### Public Methods

| Return | Name | Description |
|--------|------|-------------|
|  | [`CpuMaxTurboScope`](#cpumaxturboscope-1) `inline` |  |
|  | [`~CpuMaxTurboScope`](#cpumaxturboscope-2) `inline` |  |

---

{#cpumaxturboscope-1}

#### CpuMaxTurboScope

`inline`

```cpp
inline CpuMaxTurboScope()
```

Defined in h1os_lvgl.cpp:44

---

{#cpumaxturboscope-2}

#### ~CpuMaxTurboScope

`inline`

```cpp
inline ~CpuMaxTurboScope()
```

Defined in h1os_lvgl.cpp:48

{#es8311_reg_entry_t}

## es8311_reg_entry_t

```cpp
struct es8311_reg_entry_t
```

Defined in sub_audio.c:71

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint8_t` | [`reg`](#reg)  |  |
| `uint8_t` | [`val`](#val)  |  |

---

{#reg}

#### reg

```cpp
uint8_t reg
```

Defined in sub_audio.c:72

---

{#val}

#### val

```cpp
uint8_t val
```

Defined in sub_audio.c:73

{#h1os_wake_context_t}

## h1os_wake_context_t

```cpp
#include <h1os/h1os.h>
```

```cpp
struct h1os_wake_context_t
```

Defined in h1os/h1os.h:30

Platform wakeup context descriptor.

Populated during boot and passed to the application lifecycle on_wake hook.

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `esp_reset_reason_t` | [`reset_reason`](#reset_reason)  | Hardware reset reason code. |
| `uint32_t` | [`wakeup_causes`](#wakeup_causes)  | Bitmap of wakeup sources (esp_sleep_get_wakeup_causes). |
| `uint32_t` | [`boot_count`](#boot_count)  | Monotonic system boot cycle count. |
| `uint32_t` | [`deep_sleep_count`](#deep_sleep_count)  | Monotonic deep sleep wake cycle count. |
| `bool` | [`woke_from_button`](#woke_from_button)  | True if system woke due to physical button actuation. |
| `uint8_t` | [`wake_button`](#wake_button)  | Waking button ID ([h1os_wake_btn_t](#h1os_wake_btn_t): 0=None, 1=BOOT, 2=POWER). |
| `uint32_t` | [`sleep_duration_sec`](#sleep_duration_sec)  | Configured sleep interval prior to wake in seconds. |
| `void *` | [`user_data`](#user_data-1)  | User context pointer passed to lifecycle. |

---

{#reset_reason}

#### reset_reason

```cpp
esp_reset_reason_t reset_reason
```

Defined in h1os/h1os.h:31

Hardware reset reason code.

---

{#wakeup_causes}

#### wakeup_causes

```cpp
uint32_t wakeup_causes
```

Defined in h1os/h1os.h:32

Bitmap of wakeup sources (esp_sleep_get_wakeup_causes).

---

{#boot_count}

#### boot_count

```cpp
uint32_t boot_count
```

Defined in h1os/h1os.h:33

Monotonic system boot cycle count.

---

{#deep_sleep_count}

#### deep_sleep_count

```cpp
uint32_t deep_sleep_count
```

Defined in h1os/h1os.h:34

Monotonic deep sleep wake cycle count.

---

{#woke_from_button}

#### woke_from_button

```cpp
bool woke_from_button
```

Defined in h1os/h1os.h:35

True if system woke due to physical button actuation.

---

{#wake_button}

#### wake_button

```cpp
uint8_t wake_button
```

Defined in h1os/h1os.h:36

Waking button ID ([h1os_wake_btn_t](#h1os_wake_btn_t): 0=None, 1=BOOT, 2=POWER).

---

{#sleep_duration_sec}

#### sleep_duration_sec

```cpp
uint32_t sleep_duration_sec
```

Defined in h1os/h1os.h:37

Configured sleep interval prior to wake in seconds.

---

{#user_data-1}

#### user_data

```cpp
void * user_data
```

Defined in h1os/h1os.h:38

User context pointer passed to lifecycle.

{#orch_persisted_state_t}

## orch_persisted_state_t

```cpp
#include <h1os/orch_state.h>
```

```cpp
struct orch_persisted_state_t
```

Defined in h1os/orch_state.h:57

Master persistent state block allocated in RTC Slow SRAM.

Retained across all deep sleep cycles and wake stub executions.

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint32_t` | [`magic`](#magic)  | Sentinel validation magic word (ORCH_RTC_MAGIC). |
| `uint32_t` | [`boot_count`](#boot_count-1)  | Total monotonic system boot cycles. |
| `uint32_t` | [`wake_count`](#wake_count)  | Monotonic deep sleep wake cycle count. |
| `uint8_t` | [`flags`](#flags)  | Operating state flags (ORCH_FLAG_*). |
| `uint8_t` | [`ulp_dispatch_reason`](#ulp_dispatch_reason)  | Reason code from last ULP coprocessor dispatch. |
| `uint16_t` | [`last_vbat_mv`](#last_vbat_mv-1)  | Last sampled battery terminal voltage in millivolts. |
| `uint16_t` | [`boot_vbat_mv`](#boot_vbat_mv-1)  | Initial non-USB battery voltage captured on boot in millivolts. |
| `uint32_t` | [`sample_interval_sec`](#sample_interval_sec)  | Interval between Flow A sensor samples in seconds. |
| `uint32_t` | [`flow_b_period_sec`](#flow_b_period_sec-2)  | Interval between Flow B display refreshes in seconds. |
| `uint32_t` | [`last_ewma_sample_seq`](#last_ewma_sample_seq)  | Sample sequence number of last processed EWMA & ring debug update. |
| `uint16_t` | [`epd_partial_refresh_count`](#epd_partial_refresh_count)  | Consecutive differential partial refreshes on EPD. |
| `uint16_t` | [`valid_trend`](#valid_trend-1)  | Monotonic count of consecutive settled steady-state samples. |
| `int16_t` | [`window_low_temp_centi_c`](#window_low_temp_centi_c)  | Valid Window Floor (minimum over active window) in centi-°C. |
| `int16_t` | [`window_high_temp_centi_c`](#window_high_temp_centi_c)  | Valid Window Ceiling (maximum over active window) in centi-°C. |
| `int16_t` | [`last_glass_temp_centi_c`](#last_glass_temp_centi_c)  | Last sampled EPD glass temperature in centi-°C. |
| `float` | [`window_avg_shtc3_c`](#window_avg_shtc3_c-1)  | Short-term valid SHTC3 window average in degrees Celsius. |
| `float` | [`window_avg_die_c`](#window_avg_die_c-1)  | Short-term valid MCU Die window average in degrees Celsius. |
| `float` | [`temp_historical_c`](#temp_historical_c-1)  | Long-term light EWMA baseline temperature. |
| `float` | [`rh_historical_pct`](#rh_historical_pct-1)  | Long-term light EWMA baseline relative humidity. |
| `float` | [`ambient_temp_c`](#ambient_temp_c-1)  | Trusted steady-state SHTC3 ambient temperature in °C. |
| `float` | [`ambient_rh_pct`](#ambient_rh_pct-1)  | Trusted steady-state SHTC3 ambient relative humidity in %. |
| `float` | [`dew_point_c`](#dew_point_c-1)  | Calculated dew point temperature in °C. |
| `float` | [`vapor_pressure_hpa`](#vapor_pressure_hpa-1)  | Calculated water vapor partial pressure in hPa. |
| `float` | [`trinode_temp_c`](#trinode_temp_c-1)  | Tri-Node verification average: (T_valid + T_die + T_glass) / 3.0. |
| `float` | [`trinode_delta_c`](#trinode_delta_c-1)  | Cross-sensor verification delta: T_valid - T_trinode. |
| `uint8_t` | [`trinode_confidence_pct`](#trinode_confidence_pct-1)  | 0-100% cross-sensor range verification score. |
| `bool` | [`ewma_inited`](#ewma_inited)  | True if EWMA filters have been seeded with initial samples. |
| `int16_t` | [`tsens_cal_centi_c`](#tsens_cal_centi_c)  | Factory calibrated TSENS eFuse offset in centi-degrees Celsius. |
| `int16_t` | [`tsens_offset_centi_c`](#tsens_offset_centi_c)  | Pre-computed TSENS fixed-point intercept (2052 + tsens_cal_centi_c). |
| [`orch_tri_node_sample_t`](#orch_tri_node_sample_t) | [`ring`](#ring)  | Circular ring buffer of historical telemetry samples. |
| `uint8_t` | [`ring_head`](#ring_head)  | Write head index into circular ring buffer (0..ORCH_RING_CAPACITY-1). |
| `uint32_t` | [`total_samples`](#total_samples)  | Total lifetime samples recorded across all sessions. |

---

{#magic}

#### magic

```cpp
uint32_t magic
```

Defined in h1os/orch_state.h:58

Sentinel validation magic word (ORCH_RTC_MAGIC).

---

{#boot_count-1}

#### boot_count

```cpp
uint32_t boot_count
```

Defined in h1os/orch_state.h:59

Total monotonic system boot cycles.

---

{#wake_count}

#### wake_count

```cpp
uint32_t wake_count
```

Defined in h1os/orch_state.h:60

Monotonic deep sleep wake cycle count.

---

{#flags}

#### flags

```cpp
uint8_t flags
```

Defined in h1os/orch_state.h:61

Operating state flags (ORCH_FLAG_*).

---

{#ulp_dispatch_reason}

#### ulp_dispatch_reason

```cpp
uint8_t ulp_dispatch_reason
```

Defined in h1os/orch_state.h:62

Reason code from last ULP coprocessor dispatch.

---

{#last_vbat_mv-1}

#### last_vbat_mv

```cpp
uint16_t last_vbat_mv
```

Defined in h1os/orch_state.h:63

Last sampled battery terminal voltage in millivolts.

---

{#boot_vbat_mv-1}

#### boot_vbat_mv

```cpp
uint16_t boot_vbat_mv
```

Defined in h1os/orch_state.h:64

Initial non-USB battery voltage captured on boot in millivolts.

---

{#sample_interval_sec}

#### sample_interval_sec

```cpp
uint32_t sample_interval_sec
```

Defined in h1os/orch_state.h:66

Interval between Flow A sensor samples in seconds.

---

{#flow_b_period_sec-2}

#### flow_b_period_sec

```cpp
uint32_t flow_b_period_sec
```

Defined in h1os/orch_state.h:67

Interval between Flow B display refreshes in seconds.

---

{#last_ewma_sample_seq}

#### last_ewma_sample_seq

```cpp
uint32_t last_ewma_sample_seq
```

Defined in h1os/orch_state.h:68

Sample sequence number of last processed EWMA & ring debug update.

---

{#epd_partial_refresh_count}

#### epd_partial_refresh_count

```cpp
uint16_t epd_partial_refresh_count
```

Defined in h1os/orch_state.h:70

Consecutive differential partial refreshes on EPD.

---

{#valid_trend-1}

#### valid_trend

```cpp
uint16_t valid_trend
```

Defined in h1os/orch_state.h:71

Monotonic count of consecutive settled steady-state samples.

---

{#window_low_temp_centi_c}

#### window_low_temp_centi_c

```cpp
int16_t window_low_temp_centi_c
```

Defined in h1os/orch_state.h:73

Valid Window Floor (minimum over active window) in centi-°C.

---

{#window_high_temp_centi_c}

#### window_high_temp_centi_c

```cpp
int16_t window_high_temp_centi_c
```

Defined in h1os/orch_state.h:74

Valid Window Ceiling (maximum over active window) in centi-°C.

---

{#last_glass_temp_centi_c}

#### last_glass_temp_centi_c

```cpp
int16_t last_glass_temp_centi_c
```

Defined in h1os/orch_state.h:75

Last sampled EPD glass temperature in centi-°C.

---

{#window_avg_shtc3_c-1}

#### window_avg_shtc3_c

```cpp
float window_avg_shtc3_c
```

Defined in h1os/orch_state.h:77

Short-term valid SHTC3 window average in degrees Celsius.

---

{#window_avg_die_c-1}

#### window_avg_die_c

```cpp
float window_avg_die_c
```

Defined in h1os/orch_state.h:78

Short-term valid MCU Die window average in degrees Celsius.

---

{#temp_historical_c-1}

#### temp_historical_c

```cpp
float temp_historical_c
```

Defined in h1os/orch_state.h:79

Long-term light EWMA baseline temperature.

---

{#rh_historical_pct-1}

#### rh_historical_pct

```cpp
float rh_historical_pct
```

Defined in h1os/orch_state.h:80

Long-term light EWMA baseline relative humidity.

---

{#ambient_temp_c-1}

#### ambient_temp_c

```cpp
float ambient_temp_c
```

Defined in h1os/orch_state.h:82

Trusted steady-state SHTC3 ambient temperature in °C.

---

{#ambient_rh_pct-1}

#### ambient_rh_pct

```cpp
float ambient_rh_pct
```

Defined in h1os/orch_state.h:83

Trusted steady-state SHTC3 ambient relative humidity in %.

---

{#dew_point_c-1}

#### dew_point_c

```cpp
float dew_point_c
```

Defined in h1os/orch_state.h:84

Calculated dew point temperature in °C.

---

{#vapor_pressure_hpa-1}

#### vapor_pressure_hpa

```cpp
float vapor_pressure_hpa
```

Defined in h1os/orch_state.h:85

Calculated water vapor partial pressure in hPa.

---

{#trinode_temp_c-1}

#### trinode_temp_c

```cpp
float trinode_temp_c
```

Defined in h1os/orch_state.h:87

Tri-Node verification average: (T_valid + T_die + T_glass) / 3.0.

---

{#trinode_delta_c-1}

#### trinode_delta_c

```cpp
float trinode_delta_c
```

Defined in h1os/orch_state.h:88

Cross-sensor verification delta: T_valid - T_trinode.

---

{#trinode_confidence_pct-1}

#### trinode_confidence_pct

```cpp
uint8_t trinode_confidence_pct
```

Defined in h1os/orch_state.h:89

0-100% cross-sensor range verification score.

---

{#ewma_inited}

#### ewma_inited

```cpp
bool ewma_inited
```

Defined in h1os/orch_state.h:90

True if EWMA filters have been seeded with initial samples.

---

{#tsens_cal_centi_c}

#### tsens_cal_centi_c

```cpp
int16_t tsens_cal_centi_c
```

Defined in h1os/orch_state.h:91

Factory calibrated TSENS eFuse offset in centi-degrees Celsius.

---

{#tsens_offset_centi_c}

#### tsens_offset_centi_c

```cpp
int16_t tsens_offset_centi_c
```

Defined in h1os/orch_state.h:92

Pre-computed TSENS fixed-point intercept (2052 + tsens_cal_centi_c).

---

{#ring}

#### ring

```cpp
orch_tri_node_sample_t ring[32]
```

Defined in h1os/orch_state.h:94

Circular ring buffer of historical telemetry samples.

---

{#ring_head}

#### ring_head

```cpp
uint8_t ring_head
```

Defined in h1os/orch_state.h:96

Write head index into circular ring buffer (0..ORCH_RING_CAPACITY-1).

---

{#total_samples}

#### total_samples

```cpp
uint32_t total_samples
```

Defined in h1os/orch_state.h:97

Total lifetime samples recorded across all sessions.

{#orch_tri_node_sample_t}

## orch_tri_node_sample_t

```cpp
#include <h1os/orch_state.h>
```

```cpp
struct orch_tri_node_sample_t
```

Defined in h1os/orch_state.h:42

Compact 16-byte Tri-Node sample entry in RTC Slow SRAM.

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `int16_t` | [`shtc3_temp_centi_c`](#shtc3_temp_centi_c)  | SHTC3 temperature in centi-degrees Celsius (1°C = 100). |
| `uint16_t` | [`shtc3_rh_centi_pct`](#shtc3_rh_centi_pct)  | SHTC3 relative humidity in centi-percent (1% = 100). |
| `int16_t` | [`mcu_tsens_centi_c`](#mcu_tsens_centi_c)  | ESP32-S3 internal TSENS die temperature in centi-degrees Celsius. |
| `int16_t` | [`epd_glass_centi_c`](#epd_glass_centi_c)  | SSD1681 on-glass thermal sensor in centi-degrees Celsius. |
| `uint32_t` | [`timestamp_sec`](#timestamp_sec)  | Sample epoch timestamp in seconds. |
| `uint8_t` | [`quality_flags`](#quality_flags)  | Sample qualification bitmask (SAMPLE_FLAG_*). |
| `uint8_t` | [`_pad`](#_pad)  | Alignment padding to 32-bit boundary. |

---

{#shtc3_temp_centi_c}

#### shtc3_temp_centi_c

```cpp
int16_t shtc3_temp_centi_c
```

Defined in h1os/orch_state.h:43

SHTC3 temperature in centi-degrees Celsius (1°C = 100).

---

{#shtc3_rh_centi_pct}

#### shtc3_rh_centi_pct

```cpp
uint16_t shtc3_rh_centi_pct
```

Defined in h1os/orch_state.h:44

SHTC3 relative humidity in centi-percent (1% = 100).

---

{#mcu_tsens_centi_c}

#### mcu_tsens_centi_c

```cpp
int16_t mcu_tsens_centi_c
```

Defined in h1os/orch_state.h:45

ESP32-S3 internal TSENS die temperature in centi-degrees Celsius.

---

{#epd_glass_centi_c}

#### epd_glass_centi_c

```cpp
int16_t epd_glass_centi_c
```

Defined in h1os/orch_state.h:46

SSD1681 on-glass thermal sensor in centi-degrees Celsius.

---

{#timestamp_sec}

#### timestamp_sec

```cpp
uint32_t timestamp_sec
```

Defined in h1os/orch_state.h:47

Sample epoch timestamp in seconds.

---

{#quality_flags}

#### quality_flags

```cpp
uint8_t quality_flags
```

Defined in h1os/orch_state.h:48

Sample qualification bitmask (SAMPLE_FLAG_*).

---

{#_pad}

#### _pad

```cpp
uint8_t _pad[3]
```

Defined in h1os/orch_state.h:49

Alignment padding to 32-bit boundary.

{#structs_lipo_table}

## [struct].s_lipo_table

```cpp
struct [struct].s_lipo_table
```

Defined in sub_power.c:45

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

Defined in sub_power.c:46

---

{#pct}

#### pct

```cpp
uint8_t pct
```

Defined in sub_power.c:47

{#structparamspcm}

## [struct].params.pcm

```cpp
struct [struct].params.pcm
```

Defined in sub_audio.c:60

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

Defined in sub_audio.c:61

---

{#sample_count}

#### sample_count

```cpp
size_t sample_count
```

Defined in sub_audio.c:62

---

{#sample_rate_hz}

#### sample_rate_hz

```cpp
uint32_t sample_rate_hz
```

Defined in sub_audio.c:63

{#structparamstone}

## [struct].params.tone

```cpp
struct [struct].params.tone
```

Defined in sub_audio.c:53

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

Defined in sub_audio.c:54

---

{#duration_ms}

#### duration_ms

```cpp
uint32_t duration_ms
```

Defined in sub_audio.c:55

{#structsession}

## [struct].session

```cpp
struct [struct].session
```

Defined in h1os/h1os.h:113

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint32_t` | [`inactivity_timeout_sec`](#inactivity_timeout_sec)  | Interactive session idle sleep timeout in seconds. |
| [`sys_clk_mode_t`](#sys_clk_mode_t) | [`clk_mode`](#clk_mode)  | CPU clock scaling mode (SYS_CLK_MODE_DYNAMIC by default). |
| `uint32_t` | [`flow_a_period_sec`](#flow_a_period_sec)  | Period between headless sensor sample bursts in seconds. |
| `uint32_t` | [`flow_b_period_sec`](#flow_b_period_sec)  | Period between unattended display flushes in seconds. |

---

{#inactivity_timeout_sec}

#### inactivity_timeout_sec

```cpp
uint32_t inactivity_timeout_sec
```

Defined in h1os/h1os.h:114

Interactive session idle sleep timeout in seconds.

---

{#clk_mode}

#### clk_mode

```cpp
sys_clk_mode_t clk_mode
```

Type: [`sys_clk_mode_t`](#sys_clk_mode_t)

Defined in h1os/h1os.h:115

CPU clock scaling mode (SYS_CLK_MODE_DYNAMIC by default).

---

{#flow_a_period_sec}

#### flow_a_period_sec

```cpp
uint32_t flow_a_period_sec
```

Defined in h1os/h1os.h:116

Period between headless sensor sample bursts in seconds.

---

{#flow_b_period_sec}

#### flow_b_period_sec

```cpp
uint32_t flow_b_period_sec
```

Defined in h1os/h1os.h:117

Period between unattended display flushes in seconds.

{#structparamschime}

## [struct].params.chime

```cpp
struct [struct].params.chime
```

Defined in sub_audio.c:57

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

Defined in sub_audio.c:58

{#structpresentation}

## [struct].presentation

```cpp
struct [struct].presentation
```

Defined in h1os/h1os.h:106

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| [`h1os_splash_cb_t`](#h1os_splash_cb_t) | [`on_splash`](#on_splash)  | Presentation splash screen rendering hook. |
| [`h1os_chime_cb_t`](#h1os_chime_cb_t) | [`on_chime`](#on_chime)  | Presentation chime playback hook. |
| `uint8_t` | [`chime_mask`](#chime_mask)  | Bitmask of enabled audio chime types. |
| `uint8_t` | [`volume_pct`](#volume_pct)  | Acoustic presentation master volume (0..100%). |

---

{#on_splash}

#### on_splash

```cpp
h1os_splash_cb_t on_splash
```

Type: [`h1os_splash_cb_t`](#h1os_splash_cb_t)

Defined in h1os/h1os.h:107

Presentation splash screen rendering hook.

---

{#on_chime}

#### on_chime

```cpp
h1os_chime_cb_t on_chime
```

Type: [`h1os_chime_cb_t`](#h1os_chime_cb_t)

Defined in h1os/h1os.h:108

Presentation chime playback hook.

---

{#chime_mask}

#### chime_mask

```cpp
uint8_t chime_mask
```

Defined in h1os/h1os.h:109

Bitmask of enabled audio chime types.

---

{#volume_pct}

#### volume_pct

```cpp
uint8_t volume_pct
```

Defined in h1os/h1os.h:110

Acoustic presentation master volume (0..100%).

{#unionparams}

## [union].params

```cpp
union [union].params
```

Defined in sub_audio.c:52

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

Defined in sub_audio.c:56

---

{#chime}

#### chime

```cpp
struct audio_cmd_t::@075142260334247171354103021266123360172342241057::@035007020164214261121213220013133270155350134061 chime
```

Defined in sub_audio.c:59

---

{#pcm}

#### pcm

```cpp
struct audio_cmd_t::@075142260334247171354103021266123360172342241057::@174042257255263212372236347353345125072343133315 pcm
```

Defined in sub_audio.c:64

{#structparamstone}

## [struct].params.tone

```cpp
struct [struct].params.tone
```

Defined in sub_audio.c:53

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

Defined in sub_audio.c:54

---

{#duration_ms}

#### duration_ms

```cpp
uint32_t duration_ms
```

Defined in sub_audio.c:55

{#structparamschime}

## [struct].params.chime

```cpp
struct [struct].params.chime
```

Defined in sub_audio.c:57

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

Defined in sub_audio.c:58

{#structparamspcm}

## [struct].params.pcm

```cpp
struct [struct].params.pcm
```

Defined in sub_audio.c:60

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

Defined in sub_audio.c:61

---

{#sample_count}

#### sample_count

```cpp
size_t sample_count
```

Defined in sub_audio.c:62

---

{#sample_rate_hz}

#### sample_rate_hz

```cpp
uint32_t sample_rate_hz
```

Defined in sub_audio.c:63

Generated by [Moxygen](https://0state.com/moxygen)