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

### H1OS_NAME

```cpp
#define H1OS_NAME "H1OS"
```

Defined in components/h1os/include/h1os/h1os.h:33

---

### H1OS_SUBTITLE

```cpp
#define H1OS_SUBTITLE "Class-E Environmental Operating System"
```

Defined in components/h1os/include/h1os/h1os.h:34

---

### H1OS_VERSION_MAJOR

```cpp
#define H1OS_VERSION_MAJOR 2
```

Defined in components/h1os/include/h1os/h1os.h:35

---

### H1OS_VERSION_MINOR

```cpp
#define H1OS_VERSION_MINOR 0
```

Defined in components/h1os/include/h1os/h1os.h:36

---

### H1OS_VERSION_PATCH

```cpp
#define H1OS_VERSION_PATCH 0
```

Defined in components/h1os/include/h1os/h1os.h:37

---

### H1OS_VERSION_TAG

```cpp
#define H1OS_VERSION_TAG "dev"
```

Defined in components/h1os/include/h1os/h1os.h:38

---

### H1OS_VERSION_STRING

```cpp
#define H1OS_VERSION_STRING "2.0.0-dev"
```

Defined in components/h1os/include/h1os/h1os.h:39

---

### SUB_NVS_NAMESPACE

```cpp
#define SUB_NVS_NAMESPACE "h1os"
```

Defined in components/h1os/include/h1os/sub_nvs.h:22

---

### RTC_REG_CONTROL_1

```cpp
#define RTC_REG_CONTROL_1 0x00
```

Defined in components/h1os/src/sub_rtc.c:17

---

### RTC_REG_CONTROL_2

```cpp
#define RTC_REG_CONTROL_2 0x01
```

Defined in components/h1os/src/sub_rtc.c:18

---

### RTC_REG_OFFSET

```cpp
#define RTC_REG_OFFSET 0x02
```

Defined in components/h1os/src/sub_rtc.c:19

---

### RTC_REG_RAM_BYTE

```cpp
#define RTC_REG_RAM_BYTE 0x03
```

Defined in components/h1os/src/sub_rtc.c:20

---

### RTC_REG_SECONDS

```cpp
#define RTC_REG_SECONDS 0x04
```

Defined in components/h1os/src/sub_rtc.c:21

---

### RTC_REG_MINUTES

```cpp
#define RTC_REG_MINUTES 0x05
```

Defined in components/h1os/src/sub_rtc.c:22

---

### RTC_REG_HOURS

```cpp
#define RTC_REG_HOURS 0x06
```

Defined in components/h1os/src/sub_rtc.c:23

---

### RTC_REG_DAYS

```cpp
#define RTC_REG_DAYS 0x07
```

Defined in components/h1os/src/sub_rtc.c:24

---

### RTC_REG_WEEKDAYS

```cpp
#define RTC_REG_WEEKDAYS 0x08
```

Defined in components/h1os/src/sub_rtc.c:25

---

### RTC_REG_MONTHS

```cpp
#define RTC_REG_MONTHS 0x09
```

Defined in components/h1os/src/sub_rtc.c:26

---

### RTC_REG_YEARS

```cpp
#define RTC_REG_YEARS 0x0A
```

Defined in components/h1os/src/sub_rtc.c:27

---

### RTC_REG_ALARM_SEC

```cpp
#define RTC_REG_ALARM_SEC 0x0B
```

Defined in components/h1os/src/sub_rtc.c:28

---

### RTC_REG_TIMER_VALUE

```cpp
#define RTC_REG_TIMER_VALUE 0x10
```

Defined in components/h1os/src/sub_rtc.c:29

---

### RTC_REG_TIMER_MODE

```cpp
#define RTC_REG_TIMER_MODE 0x11
```

Defined in components/h1os/src/sub_rtc.c:30

---

### CTRL1_STOP_MASK

```cpp
#define CTRL1_STOP_MASK (1 << 5)
```

Defined in components/h1os/src/sub_rtc.c:33

---

### CTRL1_12_24_MASK

```cpp
#define CTRL1_12_24_MASK (1 << 1)
```

Defined in components/h1os/src/sub_rtc.c:34

---

### CTRL1_CAP_SEL_12_5PF

```cpp
#define CTRL1_CAP_SEL_12_5PF (1 << 0)
```

Defined in components/h1os/src/sub_rtc.c:35

---

### CTRL1_SW_RESET_CMD

```cpp
#define CTRL1_SW_RESET_CMD 0x58
```

Defined in components/h1os/src/sub_rtc.c:36

---

### CTRL2_AF_MASK

```cpp
#define CTRL2_AF_MASK (1 << 6)
```

Defined in components/h1os/src/sub_rtc.c:39

---

### CTRL2_TF_MASK

```cpp
#define CTRL2_TF_MASK (1 << 3)
```

Defined in components/h1os/src/sub_rtc.c:40

---

### CTRL2_AIE_MASK

```cpp
#define CTRL2_AIE_MASK (1 << 7)
```

Defined in components/h1os/src/sub_rtc.c:41

---

### CTRL2_COF_OFF

```cpp
#define CTRL2_COF_OFF 0x07
```

Defined in components/h1os/src/sub_rtc.c:42

---

### TIMER_CLK_4096_HZ

```cpp
#define TIMER_CLK_4096_HZ (0 << 3)
```

Defined in components/h1os/src/sub_rtc.c:45

---

### TIMER_CLK_64_HZ

```cpp
#define TIMER_CLK_64_HZ (1 << 3)
```

Defined in components/h1os/src/sub_rtc.c:46

---

### TIMER_CLK_1_HZ

```cpp
#define TIMER_CLK_1_HZ (2 << 3)
```

Defined in components/h1os/src/sub_rtc.c:47

---

### TIMER_CLK_1_60_HZ

```cpp
#define TIMER_CLK_1_60_HZ (3 << 3)
```

Defined in components/h1os/src/sub_rtc.c:48

---

### TIMER_ENABLE_BIT

```cpp
#define TIMER_ENABLE_BIT (1 << 2)
```

Defined in components/h1os/src/sub_rtc.c:49

---

### TIMER_INT_ENABLE_BIT

```cpp
#define TIMER_INT_ENABLE_BIT (1 << 1)
```

Defined in components/h1os/src/sub_rtc.c:50

---

### HAL_PIN_POWER_HOLD

```cpp
#define HAL_PIN_POWER_HOLD GPIO_NUM_17
```

Defined in components/h1os/include/h1os/hal_types.h:30

Master LDO Power Latch (BAT_CTRL): Active HIGH.

---

### HAL_PIN_BATTERY_ADC

```cpp
#define HAL_PIN_BATTERY_ADC GPIO_NUM_4
```

Defined in components/h1os/include/h1os/hal_types.h:31

Battery Voltage Sensing: ADC1_CHANNEL_3 (1:2 divider).

---

### HAL_PIN_STATUS_LED

```cpp
#define HAL_PIN_STATUS_LED GPIO_NUM_3
```

Defined in components/h1os/include/h1os/hal_types.h:32

User LED: Open-Drain, Active LOW (0 = ON, 1 = OFF).

---

### HAL_PIN_BUTTON_BOOT

```cpp
#define HAL_PIN_BUTTON_BOOT GPIO_NUM_0
```

Defined in components/h1os/include/h1os/hal_types.h:35

Hardware BOOT0 Key: Active LOW (internal pullup req).

---

### HAL_PIN_BUTTON_POWER

```cpp
#define HAL_PIN_BUTTON_POWER GPIO_NUM_18
```

Defined in components/h1os/include/h1os/hal_types.h:36

Hardware BAT_KEY: Active LOW (internal pullup req).

---

### HAL_PIN_I2C_SDA

```cpp
#define HAL_PIN_I2C_SDA GPIO_NUM_47
```

Defined in components/h1os/include/h1os/hal_types.h:39

Shared I2C Serial Data (SHTC3, PCF85063, ES8311).

---

### HAL_PIN_I2C_SCL

```cpp
#define HAL_PIN_I2C_SCL GPIO_NUM_48
```

Defined in components/h1os/include/h1os/hal_types.h:40

Shared I2C Serial Clock.

---

### HAL_PIN_RTC_INT

```cpp
#define HAL_PIN_RTC_INT GPIO_NUM_5
```

Defined in components/h1os/include/h1os/hal_types.h:41

PCF85063A INT: Open-Drain (internal pullup mandatory).

---

### HAL_PIN_EPD_3V3_EN

```cpp
#define HAL_PIN_EPD_3V3_EN GPIO_NUM_6
```

Defined in components/h1os/include/h1os/hal_types.h:44

EPD 3.3V Rail Gate: Active LOW (0 = Rail ON).

---

### HAL_PIN_EPD_BUSY

```cpp
#define HAL_PIN_EPD_BUSY GPIO_NUM_8
```

Defined in components/h1os/include/h1os/hal_types.h:45

Display Busy Line: Active HIGH (1 = Busy, 0 = Idle).

---

### HAL_PIN_EPD_RST

```cpp
#define HAL_PIN_EPD_RST GPIO_NUM_9
```

Defined in components/h1os/include/h1os/hal_types.h:46

Display Hardware Reset: Active LOW.

---

### HAL_PIN_EPD_DC

```cpp
#define HAL_PIN_EPD_DC GPIO_NUM_10
```

Defined in components/h1os/include/h1os/hal_types.h:47

Display Data / Command: 0 = Cmd, 1 = Data.

---

### HAL_PIN_EPD_CS

```cpp
#define HAL_PIN_EPD_CS GPIO_NUM_11
```

Defined in components/h1os/include/h1os/hal_types.h:48

Display SPI Chip Select: Active LOW.

---

### HAL_PIN_EPD_SCK

```cpp
#define HAL_PIN_EPD_SCK GPIO_NUM_12
```

Defined in components/h1os/include/h1os/hal_types.h:49

Display SPI Serial Clock (up to 20MHz).

---

### HAL_PIN_EPD_MOSI

```cpp
#define HAL_PIN_EPD_MOSI GPIO_NUM_13
```

Defined in components/h1os/include/h1os/hal_types.h:50

Display SPI Master Out Slave In.

---

### HAL_PIN_PA_EN

```cpp
#define HAL_PIN_PA_EN GPIO_NUM_42
```

Defined in components/h1os/include/h1os/hal_types.h:53

Amp Power Gate: Active LOW (1 = Power Cut, 0 = ON).

---

### HAL_PIN_PA_CTRL

```cpp
#define HAL_PIN_PA_CTRL GPIO_NUM_46
```

Defined in components/h1os/include/h1os/hal_types.h:54

Amp Standby/Mute: Active HIGH (0 = Mute, 1 = Enable).

---

### HAL_PIN_I2S_MCLK

```cpp
#define HAL_PIN_I2S_MCLK GPIO_NUM_14
```

Defined in components/h1os/include/h1os/hal_types.h:55

Master Clock (256 * Fs).

---

### HAL_PIN_I2S_SCLK

```cpp
#define HAL_PIN_I2S_SCLK GPIO_NUM_15
```

Defined in components/h1os/include/h1os/hal_types.h:56

Bit / Serial Clock.

---

### HAL_PIN_I2S_ASDOUT

```cpp
#define HAL_PIN_I2S_ASDOUT GPIO_NUM_16
```

Defined in components/h1os/include/h1os/hal_types.h:57

Codec Audio Out to ESP32 (DIN).

---

### HAL_PIN_I2S_LRCK

```cpp
#define HAL_PIN_I2S_LRCK GPIO_NUM_38
```

Defined in components/h1os/include/h1os/hal_types.h:58

Word Select / Frame Sync (WS).

---

### HAL_PIN_I2S_DSDIN

```cpp
#define HAL_PIN_I2S_DSDIN GPIO_NUM_45
```

Defined in components/h1os/include/h1os/hal_types.h:59

ESP32 Audio Out to Codec (DOUT).

---

### HAL_PIN_SD_CLK

```cpp
#define HAL_PIN_SD_CLK GPIO_NUM_39
```

Defined in components/h1os/include/h1os/hal_types.h:62

MicroSD Clock.

---

### HAL_PIN_SD_MISO

```cpp
#define HAL_PIN_SD_MISO GPIO_NUM_40
```

Defined in components/h1os/include/h1os/hal_types.h:63

MicroSD MISO / D0.

---

### HAL_PIN_SD_MOSI

```cpp
#define HAL_PIN_SD_MOSI GPIO_NUM_41
```

Defined in components/h1os/include/h1os/hal_types.h:64

MicroSD MOSI / CMD.

---

### HAL_I2C_ADDR_ES8311

```cpp
#define HAL_I2C_ADDR_ES8311 0x18
```

Defined in components/h1os/include/h1os/hal_types.h:69

Everest Semi Audio Codec.

---

### HAL_I2C_ADDR_PCF85063

```cpp
#define HAL_I2C_ADDR_PCF85063 0x51
```

Defined in components/h1os/include/h1os/hal_types.h:70

NXP Calendar RTC.

---

### HAL_I2C_ADDR_SHTC3

```cpp
#define HAL_I2C_ADDR_SHTC3 0x70
```

Defined in components/h1os/include/h1os/hal_types.h:71

Sensirion Temp / Humidity Sensor.

---

### HAL_I2C_FREQ_HZ

```cpp
#define HAL_I2C_FREQ_HZ 400000
```

Defined in components/h1os/include/h1os/hal_types.h:73

Fast-mode 400 kHz.

---

### HAL_EPD_WIDTH_PX

```cpp
#define HAL_EPD_WIDTH_PX 200
```

Defined in components/h1os/include/h1os/hal_types.h:78

---

### HAL_EPD_HEIGHT_PX

```cpp
#define HAL_EPD_HEIGHT_PX 200
```

Defined in components/h1os/include/h1os/hal_types.h:79

---

### HAL_EPD_DPI

```cpp
#define HAL_EPD_DPI 188
```

Defined in components/h1os/include/h1os/hal_types.h:80

---

### HAL_EPD_FRAME_SIZE_BYTES

```cpp
#define HAL_EPD_FRAME_SIZE_BYTES ((HAL_EPD_WIDTH_PX * HAL_EPD_HEIGHT_PX) / 8)
```

Defined in components/h1os/include/h1os/hal_types.h:81

---

### HAL_PARTITION_EPD_FRAME

```cpp
#define HAL_PARTITION_EPD_FRAME "epd_frame"
```

Defined in components/h1os/include/h1os/hal_types.h:83

16KB dedicated SPI flash partition

---

### HAL_PARTITION_STORAGE

```cpp
#define HAL_PARTITION_STORAGE "storage"
```

Defined in components/h1os/include/h1os/hal_types.h:84

SPIFFS / LittleFS partition.

---

### MAGNUS_A

```cpp
#define MAGNUS_A 17.625f
```

Defined in components/h1os/src/orch_math.c:11

---

### MAGNUS_B

```cpp
#define MAGNUS_B 243.04f
```

Defined in components/h1os/src/orch_math.c:12

---

### ES8311_REG_RESET

```cpp
#define ES8311_REG_RESET 0x00
```

Defined in components/h1os/src/sub_audio.c:22

---

### ES8311_REG_SYS_PWR_ANA

```cpp
#define ES8311_REG_SYS_PWR_ANA 0x0D
```

Defined in components/h1os/src/sub_audio.c:23

---

### ES8311_REG_DAC_PWR

```cpp
#define ES8311_REG_DAC_PWR 0x12
```

Defined in components/h1os/src/sub_audio.c:24

---

### ES8311_REG_DAC_VOL

```cpp
#define ES8311_REG_DAC_VOL 0x32
```

Defined in components/h1os/src/sub_audio.c:25

---

### ES8311_REG_FLAG

```cpp
#define ES8311_REG_FLAG 0xFC
```

Defined in components/h1os/src/sub_audio.c:26

---

### ES8311_REG_CHIP_ID1

```cpp
#define ES8311_REG_CHIP_ID1 0xFD
```

Defined in components/h1os/src/sub_audio.c:27

---

### ES8311_REG_CHIP_ID2

```cpp
#define ES8311_REG_CHIP_ID2 0xFE
```

Defined in components/h1os/src/sub_audio.c:28

---

### LIPO_TABLE_SIZE

```cpp
#define LIPO_TABLE_SIZE (sizeof(s_lipo_table) / sizeof(s_lipo_table[0]))
```

Defined in components/h1os/src/sub_power.c:47

---

### ORCH_RTC_MAGIC

```cpp
#define ORCH_RTC_MAGIC 0x534C4154
```

Defined in components/h1os/include/h1os/orch_state.h:21

---

### ORCH_RING_CAPACITY

```cpp
#define ORCH_RING_CAPACITY 32
```

Defined in components/h1os/include/h1os/orch_state.h:22

---

### ORCH_FLAG_NONE

```cpp
#define ORCH_FLAG_NONE 0
```

Defined in components/h1os/include/h1os/orch_state.h:85

---

### ORCH_FLAG_EPD_FRAME_VALID

```cpp
#define ORCH_FLAG_EPD_FRAME_VALID (1 << 0)
```

Defined in components/h1os/include/h1os/orch_state.h:86

---

### ORCH_FLAG_CRITICAL_BATTERY

```cpp
#define ORCH_FLAG_CRITICAL_BATTERY (1 << 1)
```

Defined in components/h1os/include/h1os/orch_state.h:87

---

### ORCH_FLAG_THERMAL_LOCKOUT

```cpp
#define ORCH_FLAG_THERMAL_LOCKOUT (1 << 2)
```

Defined in components/h1os/include/h1os/orch_state.h:88

---

### SUB_SDCARD_MOUNT_POINT

```cpp
#define SUB_SDCARD_MOUNT_POINT "/sdcard"
```

Defined in components/h1os/include/h1os/sub_sdcard.h:26

---

### SHTC3_CMD_WAKEUP

```cpp
#define SHTC3_CMD_WAKEUP 0x3517
```

Defined in components/h1os/src/sub_sensor.c:22

---

### SHTC3_CMD_SLEEP

```cpp
#define SHTC3_CMD_SLEEP 0xB098
```

Defined in components/h1os/src/sub_sensor.c:23

---

### SHTC3_CMD_MEAS_NORMAL_T_FIRST

```cpp
#define SHTC3_CMD_MEAS_NORMAL_T_FIRST 0x7866
```

Defined in components/h1os/src/sub_sensor.c:24

---

### SHTC3_CMD_MEAS_LOWPWR_T_FIRST

```cpp
#define SHTC3_CMD_MEAS_LOWPWR_T_FIRST 0x609C
```

Defined in components/h1os/src/sub_sensor.c:25

---

### EPD_WIDTH

```cpp
#define EPD_WIDTH 200
```

Defined in components/h1os/include/h1os/sub_display.h:23

---

### EPD_HEIGHT

```cpp
#define EPD_HEIGHT 200
```

Defined in components/h1os/include/h1os/sub_display.h:24

---

### EPD_BUFFER_SIZE

```cpp
#define EPD_BUFFER_SIZE ((EPD_WIDTH * EPD_HEIGHT) / 8)
```

Defined in components/h1os/include/h1os/sub_display.h:25

---

### LVGL_I1_PALETTE_SIZE

```cpp
#define LVGL_I1_PALETTE_SIZE 8
```

Defined in components/h1os/src/h1os_lvgl.cpp:34

---

### SDA_BIT_MASK

```cpp
#define SDA_BIT_MASK (1UL << (HAL_PIN_I2C_SDA - 32))
```

Defined in components/h1os/src/orch_wake_stub.c:19

---

### SCL_BIT_MASK

```cpp
#define SCL_BIT_MASK (1UL << (HAL_PIN_I2C_SCL - 32))
```

Defined in components/h1os/src/orch_wake_stub.c:20

---

### I2C_ADDR_SHTC3

```cpp
#define I2C_ADDR_SHTC3 0x70
```

Defined in components/h1os/src/orch_wake_stub.c:22

---

### CONFIG_H1OS_EPD_PARTIAL_REFRESH_LIMIT

```cpp
#define CONFIG_H1OS_EPD_PARTIAL_REFRESH_LIMIT 6
```

Defined in components/h1os/src/orch_display_sync.c:17

## Enumerations

---

### h1os_splash_type_t

```cpp
enum h1os_splash_type_t
```

Defined in components/h1os/include/h1os/h1os.h:55

| Value | Description |
|-------|-------------|
| `H1OS_SPLASH_BOOT` |  |
| `H1OS_SPLASH_WAKE` |  |
| `H1OS_SPLASH_SLEEP` |  |
| `H1OS_SPLASH_SHUTDOWN` |  |
| `H1OS_SPLASH_MAX` |  |

---

### h1os_chime_type_t

```cpp
enum h1os_chime_type_t
```

Defined in components/h1os/include/h1os/h1os.h:63

| Value | Description |
|-------|-------------|
| `H1OS_CHIME_BOOT` |  |
| `H1OS_CHIME_WAKE` |  |
| `H1OS_CHIME_SLEEP` |  |
| `H1OS_CHIME_SHUTDOWN` |  |
| `H1OS_CHIME_ALARM` |  |
| `H1OS_CHIME_MAX` |  |

---

### h1os_time_format_t

```cpp
enum h1os_time_format_t
```

Defined in components/h1os/include/h1os/h1os_time.h:20

| Value | Description |
|-------|-------------|
| `H1OS_TIME_FMT_24H_SEC` | "14:35:08" |
| `H1OS_TIME_FMT_24H_MIN` | "14:35" |
| `H1OS_TIME_FMT_12H_SEC` | "02:35:08 PM" |
| `H1OS_TIME_FMT_12H_MIN` | "02:35 PM" |

---

### h1os_date_format_t

```cpp
enum h1os_date_format_t
```

Defined in components/h1os/include/h1os/h1os_time.h:27

| Value | Description |
|-------|-------------|
| `H1OS_DATE_FMT_MM_DD_YY` | "09/26/26" |
| `H1OS_DATE_FMT_DOW` | "Saturday" |
| `H1OS_DATE_FMT_MM_DD_YY_DOW` | "09/26/26 Saturday" |

---

### hal_btn_mask_t

```cpp
enum hal_btn_mask_t
```

Defined in components/h1os/include/h1os/hal_types.h:89

| Value | Description |
|-------|-------------|
| `HAL_BTN_NONE` |  |
| `HAL_BTN_BOOT` |  |
| `HAL_BTN_POWER` |  |

---

### h1os_init_mode_t

```cpp
enum h1os_init_mode_t
```

Defined in components/h1os/include/h1os/hal_types.h:98

Initialization Modes for Dynamic Hardware Configuration.

| Value | Description |
|-------|-------------|
| `H1OS_INIT_MODE_BOOT` | Boot initialization: all hardware subsystems & LVGL initialized. |
| `H1OS_INIT_MODE_WAKE` | Wake initialization: fast display refresh retaining existing framebuffers. |
| `H1OS_INIT_MODE_SUB_EXEC` | Sub-execution initialization: scaled-back runtime (I2C + sensor only). |

---

### h1os_sleep_mode_t

```cpp
enum h1os_sleep_mode_t
```

Defined in components/h1os/include/h1os/hal_types.h:107

Sleep Execution Modes.

| Value | Description |
|-------|-------------|
| `H1OS_SLEEP_MODE_LIGHT` | Light sleep (RAM preserved, clock gated). |
| `H1OS_SLEEP_MODE_DEEP` | Deep sleep (Power down, RTC slow memory preserved). |

---

### orch_flow_type_t

```cpp
enum orch_flow_type_t
```

Defined in components/h1os/include/h1os/orch_flow.h:24

| Value | Description |
|-------|-------------|
| `ORCH_FLOW_COLD_BOOT` |  |
| `ORCH_FLOW_A_SPRINT` |  |
| `ORCH_FLOW_B_MAIN_WAKE` |  |
| `ORCH_FLOW_BOOTLOADER_JUMP` |  |
| `ORCH_FLOW_CRITICAL_OFF` |  |

---

### audio_cmd_type_t

```cpp
enum audio_cmd_type_t
```

Defined in components/h1os/src/sub_audio.c:31

| Value | Description |
|-------|-------------|
| `AUDIO_CMD_TONE` |  |
| `AUDIO_CMD_CHIME` |  |
| `AUDIO_CMD_PCM` |  |

---

### orch_ulp_dispatch_t

```cpp
enum orch_ulp_dispatch_t
```

Defined in components/h1os/include/h1os/orch_state.h:24

| Value | Description |
|-------|-------------|
| `ULP_DISPATCH_NONE` |  |
| `ULP_DISPATCH_SENSOR_SPRINT` |  |
| `ULP_DISPATCH_MAIN_WAKE` |  |
| `ULP_DISPATCH_CRITICAL_SHUTDOWN` |  |
| `ULP_DISPATCH_BOOTLOADER_JUMP` |  |
| `ULP_DISPATCH_POWER_OFF` |  |
## Typedefs

---

### h1os_boot_cb_t

```cpp
using h1os_boot_cb_t = void(*)
```

Defined in components/h1os/include/h1os/h1os.h:72

---

### h1os_wake_cb_t

```cpp
using h1os_wake_cb_t = void(*)
```

Defined in components/h1os/include/h1os/h1os.h:73

---

### h1os_pre_sleep_cb_t

```cpp
using h1os_pre_sleep_cb_t = void(*)
```

Defined in components/h1os/include/h1os/h1os.h:74

---

### h1os_shutdown_cb_t

```cpp
using h1os_shutdown_cb_t = void(*)
```

Defined in components/h1os/include/h1os/h1os.h:75

---

### h1os_splash_cb_t

```cpp
using h1os_splash_cb_t = void(*)
```

Defined in components/h1os/include/h1os/h1os.h:76

---

### h1os_chime_cb_t

```cpp
using h1os_chime_cb_t = void(*)
```

Defined in components/h1os/include/h1os/h1os.h:77

---

### h1os_time_sync_cb_t

```cpp
using h1os_time_sync_cb_t = esp_err_t(*)
```

Defined in components/h1os/include/h1os/h1os_time.h:36

Callback for external network/remote time acquisition (SNTP, GPS, BLE).

## Functions

---

### h1os_get_version

`static` `inline`

```cpp
static inline const char * h1os_get_version(void)
```

Defined in components/h1os/include/h1os/h1os.h:136

Get the H1OS semantic version string.

---

### h1os_start

```cpp
esp_err_t h1os_start(const h1os_lifecycle_t * config)
```

Defined in components/h1os/include/h1os/h1os.h:144

Initialize H1OS and dispatch application lifecycle.

---

### h1os_get_telemetry

```cpp
esp_err_t h1os_get_telemetry(h1os_telemetry_t * out_telemetry)
```

Defined in components/h1os/include/h1os/h1os.h:149

Retrieve current Tri-Node environmental telemetry.

---

### h1os_sleep

```cpp
esp_err_t h1os_sleep(uint32_t sleep_sec)
```

Defined in components/h1os/include/h1os/h1os.h:154

Put the platform into ultra-low-power deep sleep.

---

### h1os_reset_session_timer

```cpp
void h1os_reset_session_timer(void)
```

Defined in components/h1os/include/h1os/h1os.h:159

Reset the interactive session inactivity timer (extends session by timeout_sec).

---

### h1os_shutdown

```cpp
void h1os_shutdown(void)
```

Defined in components/h1os/include/h1os/h1os.h:164

Orderly system shutdown and physical battery power cut.

---

### h1os_shutdown_for_storage

```cpp
void h1os_shutdown_for_storage(void)
```

Defined in components/h1os/include/h1os/h1os.h:170

Shutdown for long-term storage: clears display to pure white before cutting power.

Protects e-Paper electrophoretic microcapsules against permanent dye migration and burn-in.

---

### hal_io_early_init

```cpp
esp_err_t hal_io_early_init(void)
```

Defined in components/h1os/include/h1os/hal_io.h:28

Early boot initialization of essential system pins.

Releases RTC pad holds on buttons/interrupts, asserts BAT_CTRL HIGH immediately, asserts EPD_3V3_EN LOW (rail on), and ensures audio amp is muted/cut.

#### Returns
ESP_OK on success, or driver error code.

---

### hal_io_lock_power_latch

```cpp
esp_err_t hal_io_lock_power_latch(bool enable)
```

Defined in components/h1os/include/h1os/hal_io.h:36

Asserts and locks the battery LDO enable latch (GPIO 17).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `enable` | `bool` | True to drive HIGH and lock; False to drive LOW (power cut). |

---

### hal_io_set_sensor_rail

```cpp
esp_err_t hal_io_set_sensor_rail(bool enable)
```

Defined in components/h1os/include/h1os/hal_io.h:44

Controls the 3.3V switched peripheral rail (GPIO 6, Active LOW).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `enable` | `bool` | True to turn rail ON (drive 0); False to turn OFF (drive 1). |

---

### hal_io_set_led

```cpp
esp_err_t hal_io_set_led(bool on)
```

Defined in components/h1os/include/h1os/hal_io.h:52

Controls user status LED (GPIO 3, Active LOW).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `on` | `bool` | True to turn LED ON (drive 0); False to turn OFF (drive 1). |

---

### hal_io_release_power_latch

`static` `inline`

```cpp
static inline esp_err_t hal_io_release_power_latch(void)
```

Defined in components/h1os/include/h1os/hal_io.h:59

Releases the battery LDO power latch (GPIO 17 LOW, pad hold disabled) for physical power-down.

#### Returns
ESP_OK on success.

---

### hal_io_read_buttons

```cpp
hal_btn_mask_t hal_io_read_buttons(void)
```

Defined in components/h1os/include/h1os/hal_io.h:69

Samples instantaneous state of hardware tactile buttons.

#### Returns
Bitmask of currently depressed buttons (HAL_BTN_BOOT | HAL_BTN_POWER).

---

### hal_io_button_is_pressed

`static` `inline`

```cpp
static inline bool hal_io_button_is_pressed(gpio_num_t pin)
```

Defined in components/h1os/include/h1os/hal_io.h:77

Stateless check if a specific button pin is actively held down (Active LOW).

#### Returns
true if depressed, false otherwise

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `pin` | `gpio_num_t` | GPIO_NUM_0 (BOOT) or GPIO_NUM_18 (POWER) |

---

### hal_io_isolate_sleep_pads

```cpp
esp_err_t hal_io_isolate_sleep_pads(void)
```

Defined in components/h1os/include/h1os/hal_io.h:92

Configures and locks all lines subject to parasitic leakage prior to deep sleep.

* Latches GPIO 11 (EPD_CS) and GPIO 9 (EPD_RST) HIGH via gpio_hold_en().
* Cuts audio power: GPIO 42 (PA_EN) = HIGH, GPIO 46 (PA_CTRL) = LOW.
* Protects SD bus: GPIO 39-41 set to High-Z with pull-ups.
* Freezes BAT_CTRL (GPIO 17) HIGH and EPD_3V3_EN (GPIO 6) LOW with RTC pad holds.

#### Returns
ESP_OK on success.

---

### hal_io_release_pad_holds

```cpp
esp_err_t hal_io_release_pad_holds(void)
```

Defined in components/h1os/include/h1os/hal_io.h:99

Releases RTC pad holds upon waking from deep sleep.

#### Returns
ESP_OK on success.

---

### hal_check_usb_ll

```cpp
bool hal_check_usb_ll(void)
```

Defined in components/h1os/include/h1os/hal_io.h:106

Check if USB Serial/JTAG is connected to an active host via SOF packets.

#### Returns
true if USB host connection detected, false otherwise.

---

### hal_io_early_init

```cpp
esp_err_t hal_io_early_init(void)
```

Defined in components/h1os/src/hal_io.c:18

Early boot initialization of essential system pins.

Releases RTC pad holds on buttons/interrupts, asserts BAT_CTRL HIGH immediately, asserts EPD_3V3_EN LOW (rail on), and ensures audio amp is muted/cut.

#### Returns
ESP_OK on success, or driver error code.

---

### hal_io_lock_power_latch

```cpp
esp_err_t hal_io_lock_power_latch(bool enable)
```

Defined in components/h1os/src/hal_io.c:86

Asserts and locks the battery LDO enable latch (GPIO 17).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `enable` | `bool` | True to drive HIGH and lock; False to drive LOW (power cut). |

---

### hal_io_set_sensor_rail

```cpp
esp_err_t hal_io_set_sensor_rail(bool enable)
```

Defined in components/h1os/src/hal_io.c:111

Controls the 3.3V switched peripheral rail (GPIO 6, Active LOW).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `enable` | `bool` | True to turn rail ON (drive 0); False to turn OFF (drive 1). |

---

### hal_io_set_led

```cpp
esp_err_t hal_io_set_led(bool on)
```

Defined in components/h1os/src/hal_io.c:128

Controls user status LED (GPIO 3, Active LOW).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `on` | `bool` | True to turn LED ON (drive 0); False to turn OFF (drive 1). |

---

### hal_io_read_buttons

```cpp
hal_btn_mask_t hal_io_read_buttons(void)
```

Defined in components/h1os/src/hal_io.c:134

Samples instantaneous state of hardware tactile buttons.

#### Returns
Bitmask of currently depressed buttons (HAL_BTN_BOOT | HAL_BTN_POWER).

---

### hal_io_isolate_sleep_pads

```cpp
esp_err_t hal_io_isolate_sleep_pads(void)
```

Defined in components/h1os/src/hal_io.c:146

Configures and locks all lines subject to parasitic leakage prior to deep sleep.

* Latches GPIO 11 (EPD_CS) and GPIO 9 (EPD_RST) HIGH via gpio_hold_en().
* Cuts audio power: GPIO 42 (PA_EN) = HIGH, GPIO 46 (PA_CTRL) = LOW.
* Protects SD bus: GPIO 39-41 set to High-Z with pull-ups.
* Freezes BAT_CTRL (GPIO 17) HIGH and EPD_3V3_EN (GPIO 6) LOW with RTC pad holds.

#### Returns
ESP_OK on success.

---

### hal_io_release_pad_holds

```cpp
esp_err_t hal_io_release_pad_holds(void)
```

Defined in components/h1os/src/hal_io.c:196

Releases RTC pad holds upon waking from deep sleep.

#### Returns
ESP_OK on success.

---

### hal_check_usb_ll

```cpp
bool hal_check_usb_ll(void)
```

Defined in components/h1os/src/hal_io.c:213

Check if USB Serial/JTAG is connected to an active host via SOF packets.

#### Returns
true if USB host connection detected, false otherwise.

---

### hal_i2c_init

```cpp
esp_err_t hal_i2c_init(void)
```

Defined in components/h1os/include/h1os/hal_i2c.h:29

Initializes the shared I2C master bus hardware.

Installs ESP-IDF I2C driver on GPIO 47 / GPIO 48 and creates recursive mutex.

#### Returns
ESP_OK on success, or driver error code.

---

### hal_i2c_deinit

```cpp
esp_err_t hal_i2c_deinit(void)
```

Defined in components/h1os/include/h1os/hal_i2c.h:36

Deinitializes the shared I2C master bus and releases mutex.

#### Returns
ESP_OK on success.

---

### hal_i2c_write

```cpp
esp_err_t hal_i2c_write(uint8_t dev_addr, const uint8_t * write_data, size_t write_len, uint32_t timeout_ms)
```

Defined in components/h1os/include/h1os/hal_i2c.h:47

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

### hal_i2c_read

```cpp
esp_err_t hal_i2c_read(uint8_t dev_addr, uint8_t * read_data, size_t read_len, uint32_t timeout_ms)
```

Defined in components/h1os/include/h1os/hal_i2c.h:58

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

### hal_i2c_write_read

```cpp
esp_err_t hal_i2c_write_read(uint8_t dev_addr, const uint8_t * write_data, size_t write_len, uint8_t * read_data, size_t read_len, uint32_t timeout_ms)
```

Defined in components/h1os/include/h1os/hal_i2c.h:71

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

### hal_i2c_probe

```cpp
esp_err_t hal_i2c_probe(uint8_t dev_addr)
```

Defined in components/h1os/include/h1os/hal_i2c.h:82

Probes if an I2C device with given 7-bit address responds on the bus.

#### Returns
ESP_OK if device ACKed, ESP_ERR_NOT_FOUND or other error on NACK/timeout.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `dev_addr` | `uint8_t` | 7-bit device address. |

---

### hal_spi_init

```cpp
esp_err_t hal_spi_init(void)
```

Defined in components/h1os/include/h1os/hal_spi.h:25

Initializes SPI2 Master host with DMA channel enabled for display communication.

#### Returns
ESP_OK on success, or driver error code.

---

### hal_spi_deinit

```cpp
esp_err_t hal_spi_deinit(void)
```

Defined in components/h1os/include/h1os/hal_spi.h:32

Deinitializes SPI2 Master host and releases bus resources.

#### Returns
ESP_OK on success.

---

### hal_spi_write_cmd

```cpp
esp_err_t hal_spi_write_cmd(uint8_t cmd)
```

Defined in components/h1os/include/h1os/hal_spi.h:40

Transmits a single command byte to the SSD1681 controller (DC = 0).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `cmd` | `uint8_t` | Command byte. |

---

### hal_spi_write_data

```cpp
esp_err_t hal_spi_write_data(const uint8_t * data, size_t len)
```

Defined in components/h1os/include/h1os/hal_spi.h:49

Transmits data bytes to the SSD1681 controller (DC = 1).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `data` | `const uint8_t *` | Pointer to buffer containing payload. |
| `len` | `size_t` | Length of data in bytes. |

---

### hal_spi_write_frame_dma

```cpp
esp_err_t hal_spi_write_frame_dma(const uint8_t * frame_buffer)
```

Defined in components/h1os/include/h1os/hal_spi.h:57

Transmits a full 5000-byte frame buffer via DMA transfer.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `frame_buffer` | `const uint8_t *` | Pointer to 5000-byte buffer. |

---

### hal_spi_read_data

```cpp
esp_err_t hal_spi_read_data(uint8_t cmd, uint8_t * out_data, size_t len)
```

Defined in components/h1os/include/h1os/hal_spi.h:67

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

### sub_nvs_init

```cpp
esp_err_t sub_nvs_init(void)
```

Defined in components/h1os/include/h1os/sub_nvs.h:27

Initialize the NVS flash storage subsystem.

---

### sub_nvs_set_str

```cpp
esp_err_t sub_nvs_set_str(const char * key, const char * value)
```

Defined in components/h1os/include/h1os/sub_nvs.h:32

Store a string value in NVS.

---

### sub_nvs_get_str

```cpp
esp_err_t sub_nvs_get_str(const char * key, char * out_val, size_t max_len)
```

Defined in components/h1os/include/h1os/sub_nvs.h:37

Retrieve a string value from NVS.

---

### sub_nvs_set_u32

```cpp
esp_err_t sub_nvs_set_u32(const char * key, uint32_t value)
```

Defined in components/h1os/include/h1os/sub_nvs.h:42

Store an unsigned 32-bit integer in NVS.

---

### sub_nvs_get_u32

```cpp
esp_err_t sub_nvs_get_u32(const char * key, uint32_t * out_val)
```

Defined in components/h1os/include/h1os/sub_nvs.h:47

Retrieve an unsigned 32-bit integer from NVS.

---

### sub_nvs_set_blob

```cpp
esp_err_t sub_nvs_set_blob(const char * key, const void * data, size_t len)
```

Defined in components/h1os/include/h1os/sub_nvs.h:52

Store a binary blob in NVS.

---

### sub_nvs_get_blob

```cpp
esp_err_t sub_nvs_get_blob(const char * key, void * out_data, size_t * inout_len)
```

Defined in components/h1os/include/h1os/sub_nvs.h:57

Retrieve a binary blob from NVS.

---

### sub_nvs_erase_key

```cpp
esp_err_t sub_nvs_erase_key(const char * key)
```

Defined in components/h1os/include/h1os/sub_nvs.h:62

Erase a specific key from NVS.

---

### sub_nvs_erase_all

```cpp
esp_err_t sub_nvs_erase_all(void)
```

Defined in components/h1os/include/h1os/sub_nvs.h:67

Perform a factory reset wiping the entire H1OS NVS namespace.

---

### sub_rtc_init

```cpp
esp_err_t sub_rtc_init(void)
```

Defined in components/h1os/include/h1os/sub_rtc.h:29

Initialize PCF85063A RTC.

Disables CLKOUT push-pull square wave to eliminate continuous trace leakage, verifies oscillator status, and clears residual timer/alarm flags.

#### Returns
ESP_OK on success, or an I2C communication error.

---

### sub_rtc_get_time

```cpp
esp_err_t sub_rtc_get_time(struct tm * out_time)
```

Defined in components/h1os/include/h1os/sub_rtc.h:37

Read current date and time into POSIX struct tm.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_time` | `struct tm *` | Pointer to struct tm populated with current RTC timestamp. |

---

### sub_rtc_set_time

```cpp
esp_err_t sub_rtc_set_time(const struct tm * time)
```

Defined in components/h1os/include/h1os/sub_rtc.h:45

Set RTC calendar date and time.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `time` | `const struct tm *` | Pointer to struct tm containing target timestamp. |

---

### sub_rtc_arm_countdown

```cpp
esp_err_t sub_rtc_arm_countdown(uint32_t seconds)
```

Defined in components/h1os/include/h1os/sub_rtc.h:54

Arm hardware countdown timer.

Drives open-drain interrupt line GPIO 5 LOW upon expiration.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `seconds` | `uint32_t` | Countdown interval in seconds (1 to 15300s). |

---

### sub_rtc_cancel_countdown

```cpp
esp_err_t sub_rtc_cancel_countdown(void)
```

Defined in components/h1os/include/h1os/sub_rtc.h:60

Cancel and disarm hardware countdown timer.

#### Returns
ESP_OK on success.

---

### sub_rtc_get_remaining_seconds

```cpp
esp_err_t sub_rtc_get_remaining_seconds(uint32_t * out_sec)
```

Defined in components/h1os/include/h1os/sub_rtc.h:69

Read remaining seconds on the active countdown timer.

Used for zero-hour collision avoidance.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_sec` | `uint32_t *` | Remaining seconds until countdown expiration. |

---

### sub_rtc_get_and_clear_interrupts

```cpp
esp_err_t sub_rtc_get_and_clear_interrupts(bool * out_alarm, bool * out_timer)
```

Defined in components/h1os/include/h1os/sub_rtc.h:79

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

### hal_i2c_init

```cpp
esp_err_t hal_i2c_init(void)
```

Defined in components/h1os/src/hal_i2c.c:18

Initializes the shared I2C master bus hardware.

Installs ESP-IDF I2C driver on GPIO 47 / GPIO 48 and creates recursive mutex.

#### Returns
ESP_OK on success, or driver error code.

---

### hal_i2c_deinit

```cpp
esp_err_t hal_i2c_deinit(void)
```

Defined in components/h1os/src/hal_i2c.c:56

Deinitializes the shared I2C master bus and releases mutex.

#### Returns
ESP_OK on success.

---

### hal_i2c_write

```cpp
esp_err_t hal_i2c_write(uint8_t dev_addr, const uint8_t * write_data, size_t write_len, uint32_t timeout_ms)
```

Defined in components/h1os/src/hal_i2c.c:75

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

### hal_i2c_read

```cpp
esp_err_t hal_i2c_read(uint8_t dev_addr, uint8_t * read_data, size_t read_len, uint32_t timeout_ms)
```

Defined in components/h1os/src/hal_i2c.c:107

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

### hal_i2c_write_read

```cpp
esp_err_t hal_i2c_write_read(uint8_t dev_addr, const uint8_t * write_data, size_t write_len, uint8_t * read_data, size_t read_len, uint32_t timeout_ms)
```

Defined in components/h1os/src/hal_i2c.c:139

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

### hal_i2c_probe

```cpp
esp_err_t hal_i2c_probe(uint8_t dev_addr)
```

Defined in components/h1os/src/hal_i2c.c:174

Probes if an I2C device with given 7-bit address responds on the bus.

#### Returns
ESP_OK if device ACKed, ESP_ERR_NOT_FOUND or other error on NACK/timeout.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `dev_addr` | `uint8_t` | 7-bit device address. |

---

### epd_set_cs

`static` `inline`

```cpp
static inline void epd_set_cs(uint8_t level)
```

Defined in components/h1os/src/hal_spi.c:18

---

### epd_set_dc

`static` `inline`

```cpp
static inline void epd_set_dc(uint8_t level)
```

Defined in components/h1os/src/hal_spi.c:22

---

### hal_spi_init

```cpp
esp_err_t hal_spi_init(void)
```

Defined in components/h1os/src/hal_spi.c:26

Initializes SPI2 Master host with DMA channel enabled for display communication.

#### Returns
ESP_OK on success, or driver error code.

---

### hal_spi_deinit

```cpp
esp_err_t hal_spi_deinit(void)
```

Defined in components/h1os/src/hal_spi.c:106

Deinitializes SPI2 Master host and releases bus resources.

#### Returns
ESP_OK on success.

---

### hal_spi_write_cmd

```cpp
esp_err_t hal_spi_write_cmd(uint8_t cmd)
```

Defined in components/h1os/src/hal_spi.c:127

Transmits a single command byte to the SSD1681 controller (DC = 0).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `cmd` | `uint8_t` | Command byte. |

---

### hal_spi_write_data

```cpp
esp_err_t hal_spi_write_data(const uint8_t * data, size_t len)
```

Defined in components/h1os/src/hal_spi.c:147

Transmits data bytes to the SSD1681 controller (DC = 1).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `data` | `const uint8_t *` | Pointer to buffer containing payload. |
| `len` | `size_t` | Length of data in bytes. |

---

### hal_spi_write_frame_dma

```cpp
esp_err_t hal_spi_write_frame_dma(const uint8_t * frame_buffer)
```

Defined in components/h1os/src/hal_spi.c:166

Transmits a full 5000-byte frame buffer via DMA transfer.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `frame_buffer` | `const uint8_t *` | Pointer to 5000-byte buffer. |

---

### hal_spi_read_data

```cpp
esp_err_t hal_spi_read_data(uint8_t cmd, uint8_t * out_data, size_t len)
```

Defined in components/h1os/src/hal_spi.c:185

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

### sub_nvs_init

```cpp
esp_err_t sub_nvs_init(void)
```

Defined in components/h1os/src/sub_nvs.c:18

Initialize the NVS flash storage subsystem.

---

### sub_nvs_set_str

```cpp
esp_err_t sub_nvs_set_str(const char * key, const char * value)
```

Defined in components/h1os/src/sub_nvs.c:45

Store a string value in NVS.

---

### sub_nvs_get_str

```cpp
esp_err_t sub_nvs_get_str(const char * key, char * out_val, size_t max_len)
```

Defined in components/h1os/src/sub_nvs.c:62

Retrieve a string value from NVS.

---

### sub_nvs_set_u32

```cpp
esp_err_t sub_nvs_set_u32(const char * key, uint32_t value)
```

Defined in components/h1os/src/sub_nvs.c:77

Store an unsigned 32-bit integer in NVS.

---

### sub_nvs_get_u32

```cpp
esp_err_t sub_nvs_get_u32(const char * key, uint32_t * out_val)
```

Defined in components/h1os/src/sub_nvs.c:94

Retrieve an unsigned 32-bit integer from NVS.

---

### sub_nvs_set_blob

```cpp
esp_err_t sub_nvs_set_blob(const char * key, const void * data, size_t len)
```

Defined in components/h1os/src/sub_nvs.c:108

Store a binary blob in NVS.

---

### sub_nvs_get_blob

```cpp
esp_err_t sub_nvs_get_blob(const char * key, void * out_data, size_t * inout_len)
```

Defined in components/h1os/src/sub_nvs.c:125

Retrieve a binary blob from NVS.

---

### sub_nvs_erase_key

```cpp
esp_err_t sub_nvs_erase_key(const char * key)
```

Defined in components/h1os/src/sub_nvs.c:139

Erase a specific key from NVS.

---

### sub_nvs_erase_all

```cpp
esp_err_t sub_nvs_erase_all(void)
```

Defined in components/h1os/src/sub_nvs.c:156

Perform a factory reset wiping the entire H1OS NVS namespace.

---

### bcd2dec

`static` `inline`

```cpp
static inline uint8_t bcd2dec(uint8_t val)
```

Defined in components/h1os/src/sub_rtc.c:53

---

### dec2bcd

`static` `inline`

```cpp
static inline uint8_t dec2bcd(uint8_t val)
```

Defined in components/h1os/src/sub_rtc.c:57

---

### pcf85063_read_reg

`static`

```cpp
static esp_err_t pcf85063_read_reg(uint8_t reg, uint8_t * val, size_t len)
```

Defined in components/h1os/src/sub_rtc.c:61

---

### pcf85063_write_reg

`static`

```cpp
static esp_err_t pcf85063_write_reg(uint8_t reg, const uint8_t * val, size_t len)
```

Defined in components/h1os/src/sub_rtc.c:66

---

### pcf85063_write_reg_u8

`static`

```cpp
static esp_err_t pcf85063_write_reg_u8(uint8_t reg, uint8_t val)
```

Defined in components/h1os/src/sub_rtc.c:75

---

### sub_rtc_init

```cpp
esp_err_t sub_rtc_init(void)
```

Defined in components/h1os/src/sub_rtc.c:80

Initialize PCF85063A RTC.

Disables CLKOUT push-pull square wave to eliminate continuous trace leakage, verifies oscillator status, and clears residual timer/alarm flags.

#### Returns
ESP_OK on success, or an I2C communication error.

---

### sub_rtc_get_time

```cpp
esp_err_t sub_rtc_get_time(struct tm * out_time)
```

Defined in components/h1os/src/sub_rtc.c:120

Read current date and time into POSIX struct tm.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_time` | `struct tm *` | Pointer to struct tm populated with current RTC timestamp. |

---

### sub_rtc_set_time

```cpp
esp_err_t sub_rtc_set_time(const struct tm * time)
```

Defined in components/h1os/src/sub_rtc.c:144

Set RTC calendar date and time.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `time` | `const struct tm *` | Pointer to struct tm containing target timestamp. |

---

### sub_rtc_arm_countdown

```cpp
esp_err_t sub_rtc_arm_countdown(uint32_t seconds)
```

Defined in components/h1os/src/sub_rtc.c:174

Arm hardware countdown timer.

Drives open-drain interrupt line GPIO 5 LOW upon expiration.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `seconds` | `uint32_t` | Countdown interval in seconds (1 to 15300s). |

---

### sub_rtc_cancel_countdown

```cpp
esp_err_t sub_rtc_cancel_countdown(void)
```

Defined in components/h1os/src/sub_rtc.c:210

Cancel and disarm hardware countdown timer.

#### Returns
ESP_OK on success.

---

### sub_rtc_get_remaining_seconds

```cpp
esp_err_t sub_rtc_get_remaining_seconds(uint32_t * out_sec)
```

Defined in components/h1os/src/sub_rtc.c:222

Read remaining seconds on the active countdown timer.

Used for zero-hour collision avoidance.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_sec` | `uint32_t *` | Remaining seconds until countdown expiration. |

---

### sub_rtc_get_and_clear_interrupts

```cpp
esp_err_t sub_rtc_get_and_clear_interrupts(bool * out_alarm, bool * out_timer)
```

Defined in components/h1os/src/sub_rtc.c:250

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

### h1os_lvgl_init

```cpp
esp_err_t h1os_lvgl_init(bool is_wake_cycle)
```

Defined in components/h1os/include/h1os/h1os_lvgl.h:24

Initialize LVGL v9 graphics subsystem, 1-bit display buffer, and keypad input driver.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `is_wake_cycle` | `bool` | True if resuming from sleep (enables differential partial flush). |

---

### h1os_lvgl_set_first_flush_mode

```cpp
void h1os_lvgl_set_first_flush_mode(bool full_refresh)
```

Defined in components/h1os/include/h1os/h1os_lvgl.h:31

Explicitly override whether the first flush executes a full or partial refresh.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `full_refresh` | `bool` | True for full OTP flashing refresh, False for differential partial. |

---

### h1os_lvgl_start

```cpp
esp_err_t h1os_lvgl_start(int priority, int core_id)
```

Defined in components/h1os/include/h1os/h1os_lvgl.h:36

Start the LVGL background FreeRTOS task.

---

### h1os_lvgl_stop

```cpp
esp_err_t h1os_lvgl_stop(void)
```

Defined in components/h1os/include/h1os/h1os_lvgl.h:41

Stop the LVGL background task.

---

### h1os_lvgl_lock

```cpp
bool h1os_lvgl_lock(uint32_t timeout_ms)
```

Defined in components/h1os/include/h1os/h1os_lvgl.h:46

Acquire LVGL reentrant mutex lock.

---

### h1os_lvgl_unlock

```cpp
void h1os_lvgl_unlock(void)
```

Defined in components/h1os/include/h1os/h1os_lvgl.h:51

Release LVGL reentrant mutex lock.

---

### h1os_lvgl_has_pending_tasks

```cpp
bool h1os_lvgl_has_pending_tasks(void)
```

Defined in components/h1os/include/h1os/h1os_lvgl.h:56

Check if the LVGL display pipeline has pending render/flush tasks.

---

### h1os_lvgl_get_indev

```cpp
lv_indev_t * h1os_lvgl_get_indev(void)
```

Defined in components/h1os/include/h1os/h1os_lvgl.h:61

Retrieve the LVGL keypad input device handle.

---

### h1os_time_set_timezone

```cpp
esp_err_t h1os_time_set_timezone(const char * tz_str)
```

Defined in components/h1os/include/h1os/h1os_time.h:41

Configure POSIX timezone string.

---

### h1os_time_register_sync_cb

```cpp
esp_err_t h1os_time_register_sync_cb(h1os_time_sync_cb_t cb, void * user_data)
```

Defined in components/h1os/include/h1os/h1os_time.h:46

Register external time sync callback.

---

### h1os_time_sync_now

```cpp
esp_err_t h1os_time_sync_now(uint32_t timeout_ms)
```

Defined in components/h1os/include/h1os/h1os_time.h:51

Trigger time synchronization using registered callback.

---

### h1os_time_sync_system_to_rtc

```cpp
esp_err_t h1os_time_sync_system_to_rtc(void)
```

Defined in components/h1os/include/h1os/h1os_time.h:56

Synchronize internal system clock into PCF85063A RTC hardware.

---

### h1os_time_sync_rtc_to_system

```cpp
esp_err_t h1os_time_sync_rtc_to_system(void)
```

Defined in components/h1os/include/h1os/h1os_time.h:61

Synchronize PCF85063A RTC hardware into internal POSIX system clock.

---

### h1os_time_get_formatted

```cpp
esp_err_t h1os_time_get_formatted(h1os_time_format_t fmt, char * dest, size_t max_len)
```

Defined in components/h1os/include/h1os/h1os_time.h:66

Format current local time into destination buffer.

---

### h1os_time_get_date_formatted

```cpp
esp_err_t h1os_time_get_date_formatted(h1os_date_format_t fmt, char * dest, size_t max_len)
```

Defined in components/h1os/include/h1os/h1os_time.h:71

Format current local date into destination buffer.

---

### hal_flash_init

```cpp
esp_err_t hal_flash_init(void)
```

Defined in components/h1os/include/h1os/hal_flash.h:25

Finds and verifies the dedicated "epd_frame" partition.

#### Returns
ESP_OK on success, or ESP_ERR_NOT_FOUND if partition is missing.

---

### hal_flash_read_frame

```cpp
esp_err_t hal_flash_read_frame(uint8_t * out_buffer, size_t len)
```

Defined in components/h1os/include/h1os/hal_flash.h:34

Reads the persisted 5000-byte EPD frame from flash.

#### Returns
ESP_OK on success, or flash read error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_buffer` | `uint8_t *` | Destination buffer (must be at least 5000 bytes). |
| `len` | `size_t` | Number of bytes to read (typically 5000). |

---

### hal_flash_write_frame

```cpp
esp_err_t hal_flash_write_frame(const uint8_t * frame_data, size_t len)
```

Defined in components/h1os/include/h1os/hal_flash.h:43

Erases the partition sector and writes the 5000-byte frame.

#### Returns
ESP_OK on success, or flash write error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `frame_data` | `const uint8_t *` | Pointer to 5000-byte frame to commit. |
| `len` | `size_t` | Length in bytes (must be <= partition size). |

---

### orch_flow_determine_wakeup

```cpp
orch_flow_type_t orch_flow_determine_wakeup(void)
```

Defined in components/h1os/include/h1os/orch_flow.h:37

Inspect system wake source and arbitrate target flow.

#### Returns
Detected flow type.

---

### orch_flow_execute_sub_sprint

```cpp
void orch_flow_execute_sub_sprint(void)
```

Defined in components/h1os/include/h1os/orch_flow.h:45

Execute Flow A Headless Sub-Execution Sprint.

Powers on sensor rail, takes rapid low-power SHTC3 reading in <4ms, commits sample to RTC Slow Memory ring buffer, and re-enters deep sleep immediately. Zero measurable thermal impact on sensor cavity.

---

### orch_flow_is_thermal_lockout

```cpp
bool orch_flow_is_thermal_lockout(void)
```

Defined in components/h1os/include/h1os/orch_flow.h:53

Check whether system is in Thermal Lockout state.

If true, active dissipation from CPU/Display/Wi-Fi has perturbed board equilibrium.

#### Returns
True if in lockout, False if in thermal equilibrium.

---

### orch_flow_set_thermal_lockout

```cpp
void orch_flow_set_thermal_lockout(bool enable, uint32_t duration_sec)
```

Defined in components/h1os/include/h1os/orch_flow.h:61

Arm or disarm thermal lockout gatekeeper.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `enable` | `bool` | True to arm thermal lockout (e.g. after display refresh or Wi-Fi). |
| `duration_sec` | `uint32_t` | Duration of lockout in seconds (typically 30-60s). |

---

### orch_flow_query_telemetry

```cpp
esp_err_t orch_flow_query_telemetry(float * out_temp_c, float * out_rh_pct, float * out_dew_c)
```

Defined in components/h1os/include/h1os/orch_flow.h:73

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

### orch_flow_transition_to_sleep

```cpp
esp_err_t orch_flow_transition_to_sleep(uint32_t sleep_sec)
```

Defined in components/h1os/include/h1os/orch_flow.h:78

Transition system to deep sleep.

---

### orch_flow_stand_down_and_sleep

`static` `inline`

```cpp
static inline esp_err_t orch_flow_stand_down_and_sleep(uint32_t sleep_sec)
```

Defined in components/h1os/include/h1os/orch_flow.h:80

---

### orch_math_calc_sat_vapor_pressure

```cpp
float orch_math_calc_sat_vapor_pressure(float temp_c)
```

Defined in components/h1os/include/h1os/orch_math.h:34

Calculate saturation vapor pressure e_s(T) in hPa.

Formula: e_s(T) = 6.112 * exp((17.625 * T) / (243.04 + T))

#### Returns
Saturation vapor pressure in hPa.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `temp_c` | `float` | Temperature in Celsius. |

---

### orch_math_calc_vapor_pressure

```cpp
float orch_math_calc_vapor_pressure(float temp_c, float rh_pct)
```

Defined in components/h1os/include/h1os/orch_math.h:44

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

### orch_math_calc_dew_point

```cpp
float orch_math_calc_dew_point(float temp_c, float rh_pct)
```

Defined in components/h1os/include/h1os/orch_math.h:54

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

### orch_math_reconstruct_ambient_rh

```cpp
float orch_math_reconstruct_ambient_rh(float vapor_pressure_hpa, float amb_floor_temp_c)
```

Defined in components/h1os/include/h1os/orch_math.h:64

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

### orch_math_calc_absolute_humidity

```cpp
float orch_math_calc_absolute_humidity(float vapor_pressure_hpa, float amb_temp_c)
```

Defined in components/h1os/include/h1os/orch_math.h:74

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

### orch_math_update_ewma

```cpp
float orch_math_update_ewma(float current_sample, float previous_ewma, float alpha)
```

Defined in components/h1os/include/h1os/orch_math.h:85

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

### orch_math_is_plateau_settled

```cpp
bool orch_math_is_plateau_settled(int16_t initial_temp_centi_c, int16_t current_temp_centi_c, int16_t gate_threshold_centi_c)
```

Defined in components/h1os/include/h1os/orch_math.h:96

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

### sub_audio_init

```cpp
esp_err_t sub_audio_init(void)
```

Defined in components/h1os/include/h1os/sub_audio.h:28

Initialize ES8311 codec and NS4168 amplifier.

Configures I2S audio bus and sets codec to active run mode.

#### Returns
ESP_OK on success, or an error code.

---

### sub_audio_standby

```cpp
esp_err_t sub_audio_standby(void)
```

Defined in components/h1os/include/h1os/sub_audio.h:37

Put ES8311 codec into ultra-low-power software standby (Reg 0x0D = 0x00 @ <1.0 µA) and pull NS4168 PA_CTRL LOW.

Keeps power rails on so I2C bus is NOT clamped by unpowered chip protection diodes.

#### Returns
ESP_OK on success.

---

### sub_audio_deinit

```cpp
esp_err_t sub_audio_deinit(void)
```

Defined in components/h1os/include/h1os/sub_audio.h:44

Teardown audio subsystem, stop background worker task, and delete I2S channel.

#### Returns
ESP_OK on success.

---

### sub_audio_wait_until_ready

```cpp
esp_err_t sub_audio_wait_until_ready(uint32_t timeout_ms)
```

Defined in components/h1os/include/h1os/sub_audio.h:53

Poll ES8311 over I2C to confirm Chip ID (0xFD=0x83, 0xFE=0x11) and wait for Chip State Machine (Reg 0xFC bits 6:4) to exit power-down state S0.

#### Returns
ESP_OK if codec is verified and in active CSM state, or error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ms` | `uint32_t` | Maximum wait time in milliseconds. |

---

### sub_audio_is_ready

```cpp
bool sub_audio_is_ready(void)
```

Defined in components/h1os/include/h1os/sub_audio.h:60

Quick status check of whether ES8311 codec is ready.

#### Returns
true if communication and active CSM state verified.

---

### sub_audio_play_pcm

```cpp
esp_err_t sub_audio_play_pcm(const int16_t * samples, size_t sample_count, uint32_t sample_rate_hz)
```

Defined in components/h1os/include/h1os/sub_audio.h:70

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

### sub_audio_play_pcm_async

```cpp
esp_err_t sub_audio_play_pcm_async(const int16_t * samples, size_t sample_count, uint32_t sample_rate_hz)
```

Defined in components/h1os/include/h1os/sub_audio.h:81

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

### sub_audio_play_tone

```cpp
esp_err_t sub_audio_play_tone(uint32_t frequency_hz, uint32_t duration_ms)
```

Defined in components/h1os/include/h1os/sub_audio.h:90

Play synthesized audio chime/tone synchronously.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `frequency_hz` | `uint32_t` | Frequency in Hertz (e.g. 1000 for 1 kHz). |
| `duration_ms` | `uint32_t` | Duration in milliseconds. |

---

### sub_audio_play_tone_async

```cpp
esp_err_t sub_audio_play_tone_async(uint32_t frequency_hz, uint32_t duration_ms)
```

Defined in components/h1os/include/h1os/sub_audio.h:99

Play synthesized audio chime/tone asynchronously via worker task.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `frequency_hz` | `uint32_t` | Frequency in Hertz (e.g. 1000 for 1 kHz). |
| `duration_ms` | `uint32_t` | Duration in milliseconds. |

---

### sub_audio_play_chime

```cpp
esp_err_t sub_audio_play_chime(uint8_t type)
```

Defined in components/h1os/include/h1os/sub_audio.h:107

Play standard H1OS acoustic presentation chime synchronously.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `type` | `uint8_t` | Chime type (BOOT, WAKE, SLEEP, SHUTDOWN, ALARM). |

---

### sub_audio_play_chime_async

```cpp
esp_err_t sub_audio_play_chime_async(uint8_t type)
```

Defined in components/h1os/include/h1os/sub_audio.h:115

Play standard H1OS acoustic presentation chime asynchronously.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `type` | `uint8_t` | Chime type (BOOT, WAKE, SLEEP, SHUTDOWN, ALARM). |

---

### sub_audio_is_busy

```cpp
bool sub_audio_is_busy(void)
```

Defined in components/h1os/include/h1os/sub_audio.h:122

Check if audio playback is currently active or queue has pending items.

#### Returns
true if playing or queued, false if idle in standby.

---

### sub_audio_wait_idle

```cpp
esp_err_t sub_audio_wait_idle(uint32_t timeout_ms)
```

Defined in components/h1os/include/h1os/sub_audio.h:130

Wait until background audio worker completes all playback and enters standby.

#### Returns
ESP_OK if idle, ESP_ERR_TIMEOUT if still active.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ms` | `uint32_t` | Maximum time to wait in milliseconds. |

---

### sub_power_init

```cpp
esp_err_t sub_power_init(void)
```

Defined in components/h1os/include/h1os/sub_power.h:25

Initialize Battery ADC subsystem (ADC1 Channel 3 on GPIO 4 with 12 dB atten and eFuse cal).

#### Returns
ESP_OK on success, or an error code.

---

### sub_power_deinit

```cpp
esp_err_t sub_power_deinit(void)
```

Defined in components/h1os/include/h1os/sub_power.h:31

Deinitialize ADC handles.

#### Returns
ESP_OK on success.

---

### sub_power_read_battery

```cpp
esp_err_t sub_power_read_battery(uint16_t * out_mv, uint8_t * out_pct)
```

Defined in components/h1os/include/h1os/sub_power.h:40

Sample calibrated battery voltage with 16-sample trimmed outlier filtering.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_mv` | `uint16_t *` | Battery voltage in millivolts (e.g. 3850 mV). |
| `out_pct` | `uint8_t *` | Estimated state of charge (0 to 100%). |

---

### sub_power_get_ulp_cal_params

```cpp
esp_err_t sub_power_get_ulp_cal_params(uint32_t * out_scale, int32_t * out_offset_mv)
```

Defined in components/h1os/include/h1os/sub_power.h:49

Extract linear calibration coefficients (scale and offset) for ULP coprocessor hand-off.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_scale` | `uint32_t *` | Multiplier scaled by 4096. |
| `out_offset_mv` | `int32_t *` | Voltage offset in millivolts. |

---

### sub_power_enter_deep_sleep

```cpp
esp_err_t sub_power_enter_deep_sleep(uint32_t sleep_seconds, uint64_t ext1_pins_mask)
```

Defined in components/h1os/include/h1os/sub_power.h:59

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

### sub_power_cut_power_latch

```cpp
void sub_power_cut_power_latch(void)
```

Defined in components/h1os/include/h1os/sub_power.h:65

Power off system completely by releasing battery power latch (GPIO 17).

Used for critical low-battery shutdown or explicit user power-off.

---

### sub_power_connected_usb

```cpp
bool sub_power_connected_usb(void)
```

Defined in components/h1os/include/h1os/sub_power.h:73

Check to see if USB is connected.

Used for charger detection.

#### Returns
true if usb is connected, or false if disconnected.

---

### h1os_time_set_timezone

```cpp
esp_err_t h1os_time_set_timezone(const char * tz_str)
```

Defined in components/h1os/src/h1os_time.c:20

Configure POSIX timezone string.

---

### h1os_time_register_sync_cb

```cpp
esp_err_t h1os_time_register_sync_cb(h1os_time_sync_cb_t cb, void * user_data)
```

Defined in components/h1os/src/h1os_time.c:31

Register external time sync callback.

---

### h1os_time_sync_system_to_rtc

```cpp
esp_err_t h1os_time_sync_system_to_rtc(void)
```

Defined in components/h1os/src/h1os_time.c:38

Synchronize internal system clock into PCF85063A RTC hardware.

---

### h1os_time_sync_rtc_to_system

```cpp
esp_err_t h1os_time_sync_rtc_to_system(void)
```

Defined in components/h1os/src/h1os_time.c:56

Synchronize PCF85063A RTC hardware into internal POSIX system clock.

---

### h1os_time_sync_now

```cpp
esp_err_t h1os_time_sync_now(uint32_t timeout_ms)
```

Defined in components/h1os/src/h1os_time.c:79

Trigger time synchronization using registered callback.

---

### h1os_time_get_formatted

```cpp
esp_err_t h1os_time_get_formatted(h1os_time_format_t fmt, char * dest, size_t max_len)
```

Defined in components/h1os/src/h1os_time.c:97

Format current local time into destination buffer.

---

### h1os_time_get_date_formatted

```cpp
esp_err_t h1os_time_get_date_formatted(h1os_date_format_t fmt, char * dest, size_t max_len)
```

Defined in components/h1os/src/h1os_time.c:119

Format current local date into destination buffer.

---

### hal_flash_init

```cpp
esp_err_t hal_flash_init(void)
```

Defined in components/h1os/src/hal_flash.c:15

Finds and verifies the dedicated "epd_frame" partition.

#### Returns
ESP_OK on success, or ESP_ERR_NOT_FOUND if partition is missing.

---

### hal_flash_read_frame

```cpp
esp_err_t hal_flash_read_frame(uint8_t * out_buffer, size_t len)
```

Defined in components/h1os/src/hal_flash.c:34

Reads the persisted 5000-byte EPD frame from flash.

#### Returns
ESP_OK on success, or flash read error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_buffer` | `uint8_t *` | Destination buffer (must be at least 5000 bytes). |
| `len` | `size_t` | Number of bytes to read (typically 5000). |

---

### hal_flash_write_frame

```cpp
esp_err_t hal_flash_write_frame(const uint8_t * frame_data, size_t len)
```

Defined in components/h1os/src/hal_flash.c:50

Erases the partition sector and writes the 5000-byte frame.

#### Returns
ESP_OK on success, or flash write error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `frame_data` | `const uint8_t *` | Pointer to 5000-byte frame to commit. |
| `len` | `size_t` | Length in bytes (must be <= partition size). |

---

### orch_flow_determine_wakeup

```cpp
orch_flow_type_t orch_flow_determine_wakeup(void)
```

Defined in components/h1os/src/orch_flow.c:34

Inspect system wake source and arbitrate target flow.

#### Returns
Detected flow type.

---

### orch_flow_execute_sub_sprint

```cpp
void orch_flow_execute_sub_sprint(void)
```

Defined in components/h1os/src/orch_flow.c:80

Execute Flow A Headless Sub-Execution Sprint.

Powers on sensor rail, takes rapid low-power SHTC3 reading in <4ms, commits sample to RTC Slow Memory ring buffer, and re-enters deep sleep immediately. Zero measurable thermal impact on sensor cavity.

---

### orch_flow_is_thermal_lockout

```cpp
bool orch_flow_is_thermal_lockout(void)
```

Defined in components/h1os/src/orch_flow.c:175

Check whether system is in Thermal Lockout state.

If true, active dissipation from CPU/Display/Wi-Fi has perturbed board equilibrium.

#### Returns
True if in lockout, False if in thermal equilibrium.

---

### orch_flow_set_thermal_lockout

```cpp
void orch_flow_set_thermal_lockout(bool enable, uint32_t duration_sec)
```

Defined in components/h1os/src/orch_flow.c:180

Arm or disarm thermal lockout gatekeeper.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `enable` | `bool` | True to arm thermal lockout (e.g. after display refresh or Wi-Fi). |
| `duration_sec` | `uint32_t` | Duration of lockout in seconds (typically 30-60s). |

---

### orch_flow_query_telemetry

```cpp
esp_err_t orch_flow_query_telemetry(float * out_temp_c, float * out_rh_pct, float * out_dew_c)
```

Defined in components/h1os/src/orch_flow.c:191

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

### orch_flow_transition_to_sleep

```cpp
esp_err_t orch_flow_transition_to_sleep(uint32_t sleep_sec)
```

Defined in components/h1os/src/orch_flow.c:228

Transition system to deep sleep.

---

### orch_math_calc_sat_vapor_pressure

```cpp
float orch_math_calc_sat_vapor_pressure(float temp_c)
```

Defined in components/h1os/src/orch_math.c:14

Calculate saturation vapor pressure e_s(T) in hPa.

Formula: e_s(T) = 6.112 * exp((17.625 * T) / (243.04 + T))

#### Returns
Saturation vapor pressure in hPa.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `temp_c` | `float` | Temperature in Celsius. |

---

### orch_math_calc_vapor_pressure

```cpp
float orch_math_calc_vapor_pressure(float temp_c, float rh_pct)
```

Defined in components/h1os/src/orch_math.c:20

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

### orch_math_calc_dew_point

```cpp
float orch_math_calc_dew_point(float temp_c, float rh_pct)
```

Defined in components/h1os/src/orch_math.c:29

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

### orch_math_reconstruct_ambient_rh

```cpp
float orch_math_reconstruct_ambient_rh(float vapor_pressure_hpa, float amb_floor_temp_c)
```

Defined in components/h1os/src/orch_math.c:42

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

### orch_math_calc_absolute_humidity

```cpp
float orch_math_calc_absolute_humidity(float vapor_pressure_hpa, float amb_temp_c)
```

Defined in components/h1os/src/orch_math.c:53

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

### orch_math_update_ewma

```cpp
float orch_math_update_ewma(float current_sample, float previous_ewma, float alpha)
```

Defined in components/h1os/src/orch_math.c:61

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

### orch_math_is_plateau_settled

```cpp
bool orch_math_is_plateau_settled(int16_t initial_temp_centi_c, int16_t current_temp_centi_c, int16_t gate_threshold_centi_c)
```

Defined in components/h1os/src/orch_math.c:68

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

### audio_worker_task

`static`

```cpp
static void audio_worker_task(void * pvParameters)
```

Defined in components/h1os/src/sub_audio.c:489

---

### es8311_write_reg

`static`

```cpp
static esp_err_t es8311_write_reg(uint8_t reg, uint8_t val)
```

Defined in components/h1os/src/sub_audio.c:67

---

### es8311_read_reg

`static`

```cpp
static esp_err_t es8311_read_reg(uint8_t reg, uint8_t * val)
```

Defined in components/h1os/src/sub_audio.c:73

---

### sub_audio_wait_until_ready

```cpp
esp_err_t sub_audio_wait_until_ready(uint32_t timeout_ms)
```

Defined in components/h1os/src/sub_audio.c:78

Poll ES8311 over I2C to confirm Chip ID (0xFD=0x83, 0xFE=0x11) and wait for Chip State Machine (Reg 0xFC bits 6:4) to exit power-down state S0.

#### Returns
ESP_OK if codec is verified and in active CSM state, or error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ms` | `uint32_t` | Maximum wait time in milliseconds. |

---

### sub_audio_is_ready

```cpp
bool sub_audio_is_ready(void)
```

Defined in components/h1os/src/sub_audio.c:107

Quick status check of whether ES8311 codec is ready.

#### Returns
true if communication and active CSM state verified.

---

### es8311_init_dac_registers

`static`

```cpp
static esp_err_t es8311_init_dac_registers(void)
```

Defined in components/h1os/src/sub_audio.c:112

---

### sub_audio_init

```cpp
esp_err_t sub_audio_init(void)
```

Defined in components/h1os/src/sub_audio.c:177

Initialize ES8311 codec and NS4168 amplifier.

Configures I2S audio bus and sets codec to active run mode.

#### Returns
ESP_OK on success, or an error code.

---

### sub_audio_standby

```cpp
esp_err_t sub_audio_standby(void)
```

Defined in components/h1os/src/sub_audio.c:274

Put ES8311 codec into ultra-low-power software standby (Reg 0x0D = 0x00 @ <1.0 µA) and pull NS4168 PA_CTRL LOW.

Keeps power rails on so I2C bus is NOT clamped by unpowered chip protection diodes.

#### Returns
ESP_OK on success.

---

### sub_audio_teardown_clean

`static`

```cpp
static void sub_audio_teardown_clean(void)
```

Defined in components/h1os/src/sub_audio.c:311

---

### sub_audio_render_tone_samples

`static`

```cpp
static void sub_audio_render_tone_samples(uint32_t frequency_hz, uint32_t duration_ms)
```

Defined in components/h1os/src/sub_audio.c:330

---

### sub_audio_render_pcm_samples

`static`

```cpp
static void sub_audio_render_pcm_samples(const int16_t * samples, size_t sample_count)
```

Defined in components/h1os/src/sub_audio.c:356

---

### sub_audio_prepare_and_unmute

`static`

```cpp
static esp_err_t sub_audio_prepare_and_unmute(void)
```

Defined in components/h1os/src/sub_audio.c:371

---

### sub_audio_exec_tone

`static`

```cpp
static esp_err_t sub_audio_exec_tone(uint32_t frequency_hz, uint32_t duration_ms)
```

Defined in components/h1os/src/sub_audio.c:409

---

### sub_audio_exec_pcm

`static`

```cpp
static esp_err_t sub_audio_exec_pcm(const int16_t * samples, size_t sample_count, uint32_t sample_rate_hz)
```

Defined in components/h1os/src/sub_audio.c:419

---

### sub_audio_exec_chime

`static`

```cpp
static esp_err_t sub_audio_exec_chime(uint8_t type)
```

Defined in components/h1os/src/sub_audio.c:430

---

### sub_audio_send_command

`static`

```cpp
static esp_err_t sub_audio_send_command(const audio_cmd_t * cmd, bool is_sync, uint32_t wait_ms)
```

Defined in components/h1os/src/sub_audio.c:524

---

### sub_audio_play_tone

```cpp
esp_err_t sub_audio_play_tone(uint32_t frequency_hz, uint32_t duration_ms)
```

Defined in components/h1os/src/sub_audio.c:559

Play synthesized audio chime/tone synchronously.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `frequency_hz` | `uint32_t` | Frequency in Hertz (e.g. 1000 for 1 kHz). |
| `duration_ms` | `uint32_t` | Duration in milliseconds. |

---

### sub_audio_play_tone_async

```cpp
esp_err_t sub_audio_play_tone_async(uint32_t frequency_hz, uint32_t duration_ms)
```

Defined in components/h1os/src/sub_audio.c:568

Play synthesized audio chime/tone asynchronously via worker task.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `frequency_hz` | `uint32_t` | Frequency in Hertz (e.g. 1000 for 1 kHz). |
| `duration_ms` | `uint32_t` | Duration in milliseconds. |

---

### sub_audio_play_chime

```cpp
esp_err_t sub_audio_play_chime(uint8_t type)
```

Defined in components/h1os/src/sub_audio.c:577

Play standard H1OS acoustic presentation chime synchronously.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `type` | `uint8_t` | Chime type (BOOT, WAKE, SLEEP, SHUTDOWN, ALARM). |

---

### sub_audio_play_chime_async

```cpp
esp_err_t sub_audio_play_chime_async(uint8_t type)
```

Defined in components/h1os/src/sub_audio.c:586

Play standard H1OS acoustic presentation chime asynchronously.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `type` | `uint8_t` | Chime type (BOOT, WAKE, SLEEP, SHUTDOWN, ALARM). |

---

### sub_audio_play_pcm

```cpp
esp_err_t sub_audio_play_pcm(const int16_t * samples, size_t sample_count, uint32_t sample_rate_hz)
```

Defined in components/h1os/src/sub_audio.c:595

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

### sub_audio_play_pcm_async

```cpp
esp_err_t sub_audio_play_pcm_async(const int16_t * samples, size_t sample_count, uint32_t sample_rate_hz)
```

Defined in components/h1os/src/sub_audio.c:604

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

### sub_audio_is_busy

```cpp
bool sub_audio_is_busy(void)
```

Defined in components/h1os/src/sub_audio.c:613

Check if audio playback is currently active or queue has pending items.

#### Returns
true if playing or queued, false if idle in standby.

---

### sub_audio_wait_idle

```cpp
esp_err_t sub_audio_wait_idle(uint32_t timeout_ms)
```

Defined in components/h1os/src/sub_audio.c:620

Wait until background audio worker completes all playback and enters standby.

#### Returns
ESP_OK if idle, ESP_ERR_TIMEOUT if still active.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ms` | `uint32_t` | Maximum time to wait in milliseconds. |

---

### sub_audio_deinit

```cpp
esp_err_t sub_audio_deinit(void)
```

Defined in components/h1os/src/sub_audio.c:630

Teardown audio subsystem, stop background worker task, and delete I2S channel.

#### Returns
ESP_OK on success.

---

### mv_to_percent

`static`

```cpp
static uint8_t mv_to_percent(uint16_t mv)
```

Defined in components/h1os/src/sub_power.c:49

---

### sub_power_init

```cpp
esp_err_t sub_power_init(void)
```

Defined in components/h1os/src/sub_power.c:65

Initialize Battery ADC subsystem (ADC1 Channel 3 on GPIO 4 with 12 dB atten and eFuse cal).

#### Returns
ESP_OK on success, or an error code.

---

### sub_power_deinit

```cpp
esp_err_t sub_power_deinit(void)
```

Defined in components/h1os/src/sub_power.c:110

Deinitialize ADC handles.

#### Returns
ESP_OK on success.

---

### compare_int

`static`

```cpp
static int compare_int(const void * a, const void * b)
```

Defined in components/h1os/src/sub_power.c:127

---

### sub_power_read_battery

```cpp
esp_err_t sub_power_read_battery(uint16_t * out_mv, uint8_t * out_pct)
```

Defined in components/h1os/src/sub_power.c:131

Sample calibrated battery voltage with 16-sample trimmed outlier filtering.

#### Returns
ESP_OK on success, or an error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_mv` | `uint16_t *` | Battery voltage in millivolts (e.g. 3850 mV). |
| `out_pct` | `uint8_t *` | Estimated state of charge (0 to 100%). |

---

### sub_power_get_ulp_cal_params

```cpp
esp_err_t sub_power_get_ulp_cal_params(uint32_t * out_scale, int32_t * out_offset_mv)
```

Defined in components/h1os/src/sub_power.c:174

Extract linear calibration coefficients (scale and offset) for ULP coprocessor hand-off.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_scale` | `uint32_t *` | Multiplier scaled by 4096. |
| `out_offset_mv` | `int32_t *` | Voltage offset in millivolts. |

---

### sub_power_enter_deep_sleep

```cpp
esp_err_t sub_power_enter_deep_sleep(uint32_t sleep_seconds, uint64_t ext1_pins_mask)
```

Defined in components/h1os/src/sub_power.c:198

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

### sub_power_cut_power_latch

```cpp
void sub_power_cut_power_latch(void)
```

Defined in components/h1os/src/sub_power.c:222

Power off system completely by releasing battery power latch (GPIO 17).

Used for critical low-battery shutdown or explicit user power-off.

---

### sub_power_connected_usb

```cpp
bool sub_power_connected_usb(void)
```

Defined in components/h1os/src/sub_power.c:228

Check to see if USB is connected.

Used for charger detection.

#### Returns
true if usb is connected, or false if disconnected.

---

### orch_state_get

```cpp
orch_persisted_state_t * orch_state_get(void)
```

Defined in components/h1os/include/h1os/orch_state.h:94

Retrieve pointer to the persistent state in RTC Slow Memory.

Initializes default structure on cold boot magic mismatch.

---

### orch_state_reset

```cpp
void orch_state_reset(void)
```

Defined in components/h1os/include/h1os/orch_state.h:99

Reset persisted RTC state to default values.

---

### orch_state_push_sample

```cpp
void orch_state_push_sample(const orch_tri_node_sample_t * sample)
```

Defined in components/h1os/include/h1os/orch_state.h:106

Push a new Tri-Node telemetry sample into the RTC ring buffer.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `sample` | const [`orch_tri_node_sample_t`](#orch_tri_node_sample_t) * | Pointer to sample data to commit. |

---

### orch_state_get_latest_sample

```cpp
bool orch_state_get_latest_sample(orch_tri_node_sample_t * out_sample)
```

Defined in components/h1os/include/h1os/orch_state.h:114

Get the latest committed cold reading from the ring buffer.

#### Returns
true if valid reading present, false if buffer empty.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_sample` | [`orch_tri_node_sample_t`](#orch_tri_node_sample_t) * | Destination pointer. |

---

### sub_sdcard_mount

```cpp
esp_err_t sub_sdcard_mount(void)
```

Defined in components/h1os/include/h1os/sub_sdcard.h:31

Mount MicroSD card using 1-bit SDMMC driver.

---

### sub_sdcard_unmount

```cpp
esp_err_t sub_sdcard_unmount(void)
```

Defined in components/h1os/include/h1os/sub_sdcard.h:36

Unmount MicroSD card and release hardware bus resources.

---

### sub_sdcard_is_mounted

```cpp
bool sub_sdcard_is_mounted(void)
```

Defined in components/h1os/include/h1os/sub_sdcard.h:41

Check if MicroSD card is mounted and ready for I/O.

---

### sub_sdcard_get_capacity_mb

```cpp
esp_err_t sub_sdcard_get_capacity_mb(uint32_t * out_capacity_mb)
```

Defined in components/h1os/include/h1os/sub_sdcard.h:46

Get total capacity of mounted card in megabytes.

---

### sub_sdcard_format

```cpp
esp_err_t sub_sdcard_format(void)
```

Defined in components/h1os/include/h1os/sub_sdcard.h:51

Format mounted card as FAT32 filesystem.

---

### sub_sensor_init

```cpp
esp_err_t sub_sensor_init(void)
```

Defined in components/h1os/include/h1os/sub_sensor.h:26

Initialize sensor hardware interfaces (internal TSENS handle).

#### Returns
ESP_OK on success, or an error code.

---

### sub_sensor_deinit

```cpp
esp_err_t sub_sensor_deinit(void)
```

Defined in components/h1os/include/h1os/sub_sensor.h:32

Deinitialize internal sensor drivers to free resources.

#### Returns
ESP_OK on success.

---

### sub_sensor_read_shtc3_raw

```cpp
esp_err_t sub_sensor_read_shtc3_raw(uint16_t * out_raw_temp, uint16_t * out_raw_rh, bool low_power)
```

Defined in components/h1os/include/h1os/sub_sensor.h:42

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

### sub_sensor_convert_shtc3_units

```cpp
void sub_sensor_convert_shtc3_units(uint16_t raw_temp, uint16_t raw_rh, float * out_temp_c, float * out_rh_pct)
```

Defined in components/h1os/include/h1os/sub_sensor.h:52

Convert raw SHTC3 16-bit words into standard SI units.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `raw_temp` | `uint16_t` | Raw temperature word. |
| `raw_rh` | `uint16_t` | Raw relative humidity word. |
| `out_temp_c` | `float *` | Temperature in Celsius. |
| `out_rh_pct` | `float *` | Relative humidity in percent (0.0 to 100.0). |

---

### sub_sensor_read_mcu_die_temp

```cpp
esp_err_t sub_sensor_read_mcu_die_temp(float * out_die_temp_c)
```

Defined in components/h1os/include/h1os/sub_sensor.h:60

Read ESP32-S3 internal silicon junction temperature via internal TSENS macro.

#### Returns
ESP_OK on success, or driver error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_die_temp_c` | `float *` | MCU die temperature in Celsius. |

---

### orch_state_get

```cpp
orch_persisted_state_t *RTC_IRAM_ATTR orch_state_get(void)
```

Defined in components/h1os/src/orch_state.c:14

Retrieve pointer to the persistent state in RTC Slow Memory.

Initializes default structure on cold boot magic mismatch.

---

### orch_state_reset

```cpp
void RTC_IRAM_ATTR orch_state_reset(void)
```

Defined in components/h1os/src/orch_state.c:22

Reset persisted RTC state to default values.

---

### orch_state_push_sample

```cpp
void RTC_IRAM_ATTR orch_state_push_sample(const orch_tri_node_sample_t * sample)
```

Defined in components/h1os/src/orch_state.c:34

Push a new Tri-Node telemetry sample into the RTC ring buffer.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `sample` | const [`orch_tri_node_sample_t`](#orch_tri_node_sample_t) * | Pointer to sample data to commit. |

---

### orch_state_get_latest_sample

```cpp
bool orch_state_get_latest_sample(orch_tri_node_sample_t * out_sample)
```

Defined in components/h1os/src/orch_state.c:44

Get the latest committed cold reading from the ring buffer.

#### Returns
true if valid reading present, false if buffer empty.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_sample` | [`orch_tri_node_sample_t`](#orch_tri_node_sample_t) * | Destination pointer. |

---

### sub_sdcard_mount

```cpp
esp_err_t sub_sdcard_mount(void)
```

Defined in components/h1os/src/sub_sdcard.c:20

Mount MicroSD card using 1-bit SDMMC driver.

---

### sub_sdcard_unmount

```cpp
esp_err_t sub_sdcard_unmount(void)
```

Defined in components/h1os/src/sub_sdcard.c:64

Unmount MicroSD card and release hardware bus resources.

---

### sub_sdcard_is_mounted

```cpp
bool sub_sdcard_is_mounted(void)
```

Defined in components/h1os/src/sub_sdcard.c:78

Check if MicroSD card is mounted and ready for I/O.

---

### sub_sdcard_get_capacity_mb

```cpp
esp_err_t sub_sdcard_get_capacity_mb(uint32_t * out_capacity_mb)
```

Defined in components/h1os/src/sub_sdcard.c:83

Get total capacity of mounted card in megabytes.

---

### sub_sdcard_format

```cpp
esp_err_t sub_sdcard_format(void)
```

Defined in components/h1os/src/sub_sdcard.c:93

Format mounted card as FAT32 filesystem.

---

### shtc3_calc_crc

`static`

```cpp
static uint8_t shtc3_calc_crc(const uint8_t * data, size_t len)
```

Defined in components/h1os/src/sub_sensor.c:31

---

### sub_sensor_init

```cpp
esp_err_t sub_sensor_init(void)
```

Defined in components/h1os/src/sub_sensor.c:47

Initialize sensor hardware interfaces (internal TSENS handle).

#### Returns
ESP_OK on success, or an error code.

---

### sub_sensor_deinit

```cpp
esp_err_t sub_sensor_deinit(void)
```

Defined in components/h1os/src/sub_sensor.c:68

Deinitialize internal sensor drivers to free resources.

#### Returns
ESP_OK on success.

---

### sub_sensor_read_shtc3_raw

```cpp
esp_err_t sub_sensor_read_shtc3_raw(uint16_t * out_raw_temp, uint16_t * out_raw_rh, bool low_power)
```

Defined in components/h1os/src/sub_sensor.c:79

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

### sub_sensor_convert_shtc3_units

```cpp
void sub_sensor_convert_shtc3_units(uint16_t raw_temp, uint16_t raw_rh, float * out_temp_c, float * out_rh_pct)
```

Defined in components/h1os/src/sub_sensor.c:140

Convert raw SHTC3 16-bit words into standard SI units.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `raw_temp` | `uint16_t` | Raw temperature word. |
| `raw_rh` | `uint16_t` | Raw relative humidity word. |
| `out_temp_c` | `float *` | Temperature in Celsius. |
| `out_rh_pct` | `float *` | Relative humidity in percent (0.0 to 100.0). |

---

### sub_sensor_read_mcu_die_temp

```cpp
esp_err_t sub_sensor_read_mcu_die_temp(float * out_die_temp_c)
```

Defined in components/h1os/src/sub_sensor.c:155

Read ESP32-S3 internal silicon junction temperature via internal TSENS macro.

#### Returns
ESP_OK on success, or driver error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_die_temp_c` | `float *` | MCU die temperature in Celsius. |

---

### sub_display_init

```cpp
esp_err_t sub_display_init(bool is_wake_cycle)
```

Defined in components/h1os/include/h1os/sub_display.h:35

Initialize SSD1681 display controller.

Wakes panel, initializes SPI interface, configures scanning geometry, and sets up BUSY synchronization semaphore.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `is_wake_cycle` | `bool` | True if resuming from deep sleep with persistent framebuffer. |

---

### sub_display_get_framebuffer

```cpp
uint8_t * sub_display_get_framebuffer(void)
```

Defined in components/h1os/include/h1os/sub_display.h:41

Get pointer to the active working framebuffer (5000 bytes, 1-bit per pixel).

Bit 1 = White, Bit 0 = Black.

---

### sub_display_clear

```cpp
void sub_display_clear(uint8_t color)
```

Defined in components/h1os/include/h1os/sub_display.h:48

Clear active working framebuffer.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `color` | `uint8_t` | 0xFF for White, 0x00 for Black. |

---

### sub_display_sync_previous_frame

```cpp
esp_err_t sub_display_sync_previous_frame(const uint8_t * prev_frame)
```

Defined in components/h1os/include/h1os/sub_display.h:57

Synchronize previous frame into shadow buffer and hardware RAM 0x26.

Essential on deep sleep wake to enable differential partial scanning against the glass.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `prev_frame` | `const uint8_t *` | Pointer to 5000-byte pre-sleep image buffer. |

---

### sub_display_wait_busy

```cpp
esp_err_t sub_display_wait_busy(TickType_t timeout_ticks)
```

Defined in components/h1os/include/h1os/sub_display.h:66

Synchronously wait for EPD panel to finish driving electrophoretic particles.

Blocks on binary semaphore driven by GPIO 8 (BUSY) falling edge.

#### Returns
ESP_OK on panel ready, ESP_ERR_TIMEOUT on expiration.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ticks` | `TickType_t` | Max FreeRTOS ticks to wait. |

---

### sub_display_refresh_full

```cpp
esp_err_t sub_display_refresh_full(void)
```

Defined in components/h1os/include/h1os/sub_display.h:74

Execute full display refresh (OTP factory waveform LUT).

Synchronizes old frame RAM (0x26) with new frame RAM (0x24).

#### Returns
ESP_OK on success.

---

### sub_display_clear_to_white_full

```cpp
esp_err_t sub_display_clear_to_white_full(void)
```

Defined in components/h1os/include/h1os/sub_display.h:82

Clear display to pure white and trigger full OTP refresh.

Chemically neutralizes electrophoretic microcapsules to protect against permanent burn-in.

#### Returns
ESP_OK on success.

---

### sub_display_refresh_partial

```cpp
esp_err_t sub_display_refresh_partial(void)
```

Defined in components/h1os/include/h1os/sub_display.h:89

Execute fast partial refresh (~300ms) with software LUT.

#### Returns
ESP_OK on success.

---

### sub_display_read_glass_temp

```cpp
esp_err_t sub_display_read_glass_temp(float * out_temp_c)
```

Defined in components/h1os/include/h1os/sub_display.h:97

Read SSD1681 on-glass integrated temperature sensor (SPI Cmd 0x1B).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_temp_c` | `float *` | Surface glass temperature in Celsius. |

---

### sub_display_enter_deep_sleep

```cpp
esp_err_t sub_display_enter_deep_sleep(void)
```

Defined in components/h1os/include/h1os/sub_display.h:105

Put SSD1681 into Deep Sleep Mode 1 (Command 0x10, Data 0x01 @ 1.0 µA).

Crucially retains RAM contents while the 3.3V rail remains held.

#### Returns
ESP_OK on success.

---

### h1os_lvgl_port_task

`static`

```cpp
static void h1os_lvgl_port_task(void * pvParameters)
```

Defined in components/h1os/src/h1os_lvgl.cpp:263

---

### h1os_lvgl_lock

```cpp
bool h1os_lvgl_lock(uint32_t timeout_ms)
```

Defined in components/h1os/src/h1os_lvgl.cpp:38

Acquire LVGL reentrant mutex lock.

---

### h1os_lvgl_unlock

```cpp
void h1os_lvgl_unlock(void)
```

Defined in components/h1os/src/h1os_lvgl.cpp:43

Release LVGL reentrant mutex lock.

---

### lvgl_tick_get_cb

`static`

```cpp
static uint32_t lvgl_tick_get_cb(void)
```

Defined in components/h1os/src/h1os_lvgl.cpp:47

---

### lvgl_keypad_read_cb

`static`

```cpp
static void lvgl_keypad_read_cb(lv_indev_t * indev, lv_indev_data_t * data)
```

Defined in components/h1os/src/h1os_lvgl.cpp:51

---

### lvgl_display_flush_cb

`static`

```cpp
static void lvgl_display_flush_cb(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map)
```

Defined in components/h1os/src/h1os_lvgl.cpp:68

---

### h1os_lvgl_init

```cpp
esp_err_t h1os_lvgl_init(bool is_wake_cycle)
```

Defined in components/h1os/src/h1os_lvgl.cpp:145

Initialize LVGL v9 graphics subsystem, 1-bit display buffer, and keypad input driver.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `is_wake_cycle` | `bool` | True if resuming from sleep (enables differential partial flush). |

---

### h1os_lvgl_set_first_flush_mode

```cpp
void h1os_lvgl_set_first_flush_mode(bool full_refresh)
```

Defined in components/h1os/src/h1os_lvgl.cpp:202

Explicitly override whether the first flush executes a full or partial refresh.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `full_refresh` | `bool` | True for full OTP flashing refresh, False for differential partial. |

---

### h1os_lvgl_start

```cpp
esp_err_t h1os_lvgl_start(int task_priority, int core_id)
```

Defined in components/h1os/src/h1os_lvgl.cpp:207

Start the LVGL background FreeRTOS task.

---

### h1os_lvgl_stop

```cpp
esp_err_t h1os_lvgl_stop(void)
```

Defined in components/h1os/src/h1os_lvgl.cpp:231

Stop the LVGL background task.

---

### h1os_lvgl_has_pending_tasks

```cpp
bool h1os_lvgl_has_pending_tasks(void)
```

Defined in components/h1os/src/h1os_lvgl.cpp:244

Check if the LVGL display pipeline has pending render/flush tasks.

---

### h1os_lvgl_get_indev

```cpp
lv_indev_t * h1os_lvgl_get_indev(void)
```

Defined in components/h1os/src/h1os_lvgl.cpp:258

Retrieve the LVGL keypad input device handle.

---

### epd_busy_isr_handler

`static`

```cpp
static void IRAM_ATTR epd_busy_isr_handler(void * arg)
```

Defined in components/h1os/src/sub_display.cpp:51

---

### epd_reset_pulse

`static`

```cpp
static void epd_reset_pulse(void)
```

Defined in components/h1os/src/sub_display.cpp:60

---

### sub_display_wait_busy

```cpp
esp_err_t sub_display_wait_busy(TickType_t timeout_ticks)
```

Defined in components/h1os/src/sub_display.cpp:68

Synchronously wait for EPD panel to finish driving electrophoretic particles.

Blocks on binary semaphore driven by GPIO 8 (BUSY) falling edge.

#### Returns
ESP_OK on panel ready, ESP_ERR_TIMEOUT on expiration.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ticks` | `TickType_t` | Max FreeRTOS ticks to wait. |

---

### sub_display_init

```cpp
esp_err_t sub_display_init(bool is_wake_cycle)
```

Defined in components/h1os/src/sub_display.cpp:94

Initialize SSD1681 display controller.

Wakes panel, initializes SPI interface, configures scanning geometry, and sets up BUSY synchronization semaphore.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `is_wake_cycle` | `bool` | True if resuming from deep sleep with persistent framebuffer. |

---

### sub_display_get_framebuffer

```cpp
uint8_t * sub_display_get_framebuffer(void)
```

Defined in components/h1os/src/sub_display.cpp:157

Get pointer to the active working framebuffer (5000 bytes, 1-bit per pixel).

Bit 1 = White, Bit 0 = Black.

---

### sub_display_clear

```cpp
void sub_display_clear(uint8_t color)
```

Defined in components/h1os/src/sub_display.cpp:162

Clear active working framebuffer.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `color` | `uint8_t` | 0xFF for White, 0x00 for Black. |

---

### set_ram_counters

`static`

```cpp
static void set_ram_counters(void)
```

Defined in components/h1os/src/sub_display.cpp:167

---

### sub_display_sync_previous_frame

```cpp
esp_err_t sub_display_sync_previous_frame(const uint8_t * prev_frame)
```

Defined in components/h1os/src/sub_display.cpp:177

Synchronize previous frame into shadow buffer and hardware RAM 0x26.

Essential on deep sleep wake to enable differential partial scanning against the glass.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `prev_frame` | `const uint8_t *` | Pointer to 5000-byte pre-sleep image buffer. |

---

### sub_display_refresh_full

```cpp
esp_err_t sub_display_refresh_full(void)
```

Defined in components/h1os/src/sub_display.cpp:192

Execute full display refresh (OTP factory waveform LUT).

Synchronizes old frame RAM (0x26) with new frame RAM (0x24).

#### Returns
ESP_OK on success.

---

### sub_display_clear_to_white_full

```cpp
esp_err_t sub_display_clear_to_white_full(void)
```

Defined in components/h1os/src/sub_display.cpp:221

Clear display to pure white and trigger full OTP refresh.

Chemically neutralizes electrophoretic microcapsules to protect against permanent burn-in.

#### Returns
ESP_OK on success.

---

### epd_load_custom_lut

`static`

```cpp
static void epd_load_custom_lut(const uint8_t * lut_buffer)
```

Defined in components/h1os/src/sub_display.cpp:229

---

### sub_display_refresh_partial

```cpp
esp_err_t sub_display_refresh_partial(void)
```

Defined in components/h1os/src/sub_display.cpp:254

Execute fast partial refresh (~300ms) with software LUT.

#### Returns
ESP_OK on success.

---

### sub_display_read_glass_temp

```cpp
esp_err_t sub_display_read_glass_temp(float * out_temp_c)
```

Defined in components/h1os/src/sub_display.cpp:293

Read SSD1681 on-glass integrated temperature sensor (SPI Cmd 0x1B).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_temp_c` | `float *` | Surface glass temperature in Celsius. |

---

### sub_display_enter_deep_sleep

```cpp
esp_err_t sub_display_enter_deep_sleep(void)
```

Defined in components/h1os/src/sub_display.cpp:316

Put SSD1681 into Deep Sleep Mode 1 (Command 0x10, Data 0x01 @ 1.0 µA).

Crucially retains RAM contents while the 3.3V rail remains held.

#### Returns
ESP_OK on success.

---

### h1os_reset_session_timer

```cpp
void h1os_reset_session_timer(void)
```

Defined in components/h1os/src/h1os_lifecycle.c:44

Reset the interactive session inactivity timer (extends session by timeout_sec).

---

### h1os_trigger_chime

`static`

```cpp
static void h1os_trigger_chime(h1os_chime_type_t type)
```

Defined in components/h1os/src/h1os_lifecycle.c:52

---

### h1os_session_monitor_task

`static`

```cpp
static void h1os_session_monitor_task(void * arg)
```

Defined in components/h1os/src/h1os_lifecycle.c:61

---

### h1os_start

```cpp
esp_err_t h1os_start(const h1os_lifecycle_t * config)
```

Defined in components/h1os/src/h1os_lifecycle.c:81

Initialize H1OS and dispatch application lifecycle.

---

### h1os_get_telemetry

```cpp
esp_err_t h1os_get_telemetry(h1os_telemetry_t * out_telemetry)
```

Defined in components/h1os/src/h1os_lifecycle.c:203

Retrieve current Tri-Node environmental telemetry.

---

### h1os_sleep

```cpp
esp_err_t h1os_sleep(uint32_t sleep_sec)
```

Defined in components/h1os/src/h1os_lifecycle.c:252

Put the platform into ultra-low-power deep sleep.

---

### execute_system_shutdown

`static`

```cpp
static void execute_system_shutdown(bool force_clean_white)
```

Defined in components/h1os/src/h1os_lifecycle.c:262

---

### h1os_shutdown

```cpp
void h1os_shutdown(void)
```

Defined in components/h1os/src/h1os_lifecycle.c:309

Orderly system shutdown and physical battery power cut.

---

### h1os_shutdown_for_storage

```cpp
void h1os_shutdown_for_storage(void)
```

Defined in components/h1os/src/h1os_lifecycle.c:318

Shutdown for long-term storage: clears display to pure white before cutting power.

Protects e-Paper electrophoretic microcapsules against permanent dye migration and burn-in.

---

### orch_wake_stub_install

```cpp
void orch_wake_stub_install(void)
```

Defined in components/h1os/include/h1os/orch_wake_stub.h:26

Install the RTC deep sleep wake stub.

Called before entering deep sleep to arm the ultra-fast wake stub handler.

---

### bsp_wake_stub

```cpp
void bsp_wake_stub(void)
```

Defined in components/h1os/include/h1os/orch_wake_stub.h:32

Master RTC Wake Stub entry function.

Marked with RTC_IRAM_ATTR to reside in RTC Fast Memory.

---

### i2c_delay

`static` `inline`

```cpp
static inline void RTC_IRAM_ATTR i2c_delay(void)
```

Defined in components/h1os/src/orch_wake_stub.c:25

---

### sda_high

`static` `inline`

```cpp
static inline void RTC_IRAM_ATTR sda_high(void)
```

Defined in components/h1os/src/orch_wake_stub.c:30

---

### sda_low

`static` `inline`

```cpp
static inline void RTC_IRAM_ATTR sda_low(void)
```

Defined in components/h1os/src/orch_wake_stub.c:36

---

### scl_high

`static` `inline`

```cpp
static inline void RTC_IRAM_ATTR scl_high(void)
```

Defined in components/h1os/src/orch_wake_stub.c:43

---

### scl_low

`static` `inline`

```cpp
static inline void RTC_IRAM_ATTR scl_low(void)
```

Defined in components/h1os/src/orch_wake_stub.c:49

---

### sda_read

`static` `inline`

```cpp
static inline uint8_t RTC_IRAM_ATTR sda_read(void)
```

Defined in components/h1os/src/orch_wake_stub.c:56

---

### i2c_start

`static`

```cpp
static void RTC_IRAM_ATTR i2c_start(void)
```

Defined in components/h1os/src/orch_wake_stub.c:61

---

### i2c_stop

`static`

```cpp
static void RTC_IRAM_ATTR i2c_stop(void)
```

Defined in components/h1os/src/orch_wake_stub.c:72

---

### i2c_write_byte

`static`

```cpp
static bool RTC_IRAM_ATTR i2c_write_byte(uint8_t byte)
```

Defined in components/h1os/src/orch_wake_stub.c:82

---

### i2c_read_byte

`static`

```cpp
static uint8_t RTC_IRAM_ATTR i2c_read_byte(bool ack)
```

Defined in components/h1os/src/orch_wake_stub.c:108

---

### shtc3_crc8

`static`

```cpp
static uint8_t RTC_IRAM_ATTR shtc3_crc8(const uint8_t * data, size_t len)
```

Defined in components/h1os/src/orch_wake_stub.c:140

---

### bsp_wake_stub

```cpp
void RTC_IRAM_ATTR bsp_wake_stub(void)
```

Defined in components/h1os/src/orch_wake_stub.c:157

Master RTC Wake Stub entry function.

Marked with RTC_IRAM_ATTR to reside in RTC Fast Memory.

---

### orch_wake_stub_install

```cpp
void orch_wake_stub_install(void)
```

Defined in components/h1os/src/orch_wake_stub.c:275

Install the RTC deep sleep wake stub.

Called before entering deep sleep to arm the ultra-fast wake stub handler.

---

### orch_display_sync_mark_dirty

```cpp
void orch_display_sync_mark_dirty(void)
```

Defined in components/h1os/include/h1os/orch_display_sync.h:25

Mark the current display framebuffer as dirty (needs flash persistence on sleep).

---

### orch_display_sync_save_if_dirty

```cpp
esp_err_t orch_display_sync_save_if_dirty(void)
```

Defined in components/h1os/include/h1os/orch_display_sync.h:32

Save working display framebuffer to "epd_frame" flash partition if dirty.

#### Returns
ESP_OK on success or if clean (no write needed).

---

### orch_display_sync_restore_to_framebuffer

```cpp
esp_err_t orch_display_sync_restore_to_framebuffer(void)
```

Defined in components/h1os/include/h1os/orch_display_sync.h:39

Restore framebuffer from "epd_frame" flash partition into display working buffer.

#### Returns
ESP_OK on success, ESP_ERR_NOT_FOUND if partition empty/invalid.

---

### orch_display_sync_should_full_refresh

```cpp
bool orch_display_sync_should_full_refresh(void)
```

Defined in components/h1os/include/h1os/orch_display_sync.h:47

Determine if a full OTP display refresh is required.

Evaluates whether the anti-ghosting partial refresh limit has been reached.

#### Returns
true if full refresh required, false if differential partial refresh is permitted.

---

### orch_display_sync_record_partial_refresh

```cpp
void orch_display_sync_record_partial_refresh(void)
```

Defined in components/h1os/include/h1os/orch_display_sync.h:53

Record execution of a differential partial refresh.

Increments the accumulated partial refresh counter in persistent RTC memory.

---

### orch_display_sync_record_full_refresh

```cpp
void orch_display_sync_record_full_refresh(void)
```

Defined in components/h1os/include/h1os/orch_display_sync.h:59

Record execution of a full OTP display refresh.

Resets the accumulated partial refresh counter back to 0.

---

### orch_display_sync_get_partial_count

```cpp
uint16_t orch_display_sync_get_partial_count(void)
```

Defined in components/h1os/include/h1os/orch_display_sync.h:64

Get the accumulated count of partial refreshes since the last full refresh.

---

### orch_display_sync_mark_dirty

```cpp
void orch_display_sync_mark_dirty(void)
```

Defined in components/h1os/src/orch_display_sync.c:24

Mark the current display framebuffer as dirty (needs flash persistence on sleep).

---

### orch_display_sync_save_if_dirty

```cpp
esp_err_t orch_display_sync_save_if_dirty(void)
```

Defined in components/h1os/src/orch_display_sync.c:29

Save working display framebuffer to "epd_frame" flash partition if dirty.

#### Returns
ESP_OK on success or if clean (no write needed).

---

### orch_display_sync_restore_to_framebuffer

```cpp
esp_err_t orch_display_sync_restore_to_framebuffer(void)
```

Defined in components/h1os/src/orch_display_sync.c:50

Restore framebuffer from "epd_frame" flash partition into display working buffer.

#### Returns
ESP_OK on success, ESP_ERR_NOT_FOUND if partition empty/invalid.

---

### orch_display_sync_should_full_refresh

```cpp
bool orch_display_sync_should_full_refresh(void)
```

Defined in components/h1os/src/orch_display_sync.c:71

Determine if a full OTP display refresh is required.

Evaluates whether the anti-ghosting partial refresh limit has been reached.

#### Returns
true if full refresh required, false if differential partial refresh is permitted.

---

### orch_display_sync_record_partial_refresh

```cpp
void orch_display_sync_record_partial_refresh(void)
```

Defined in components/h1os/src/orch_display_sync.c:85

Record execution of a differential partial refresh.

Increments the accumulated partial refresh counter in persistent RTC memory.

---

### orch_display_sync_record_full_refresh

```cpp
void orch_display_sync_record_full_refresh(void)
```

Defined in components/h1os/src/orch_display_sync.c:93

Record execution of a full OTP display refresh.

Resets the accumulated partial refresh counter back to 0.

---

### orch_display_sync_get_partial_count

```cpp
uint16_t orch_display_sync_get_partial_count(void)
```

Defined in components/h1os/src/orch_display_sync.c:100

Get the accumulated count of partial refreshes since the last full refresh.

## Variables

---

### TAG

`static`

```cpp
const char * TAG = "HAL_IO"
```

Defined in components/h1os/src/hal_io.c:16

---

### TAG

`static`

```cpp
const char * TAG = "HAL_I2C"
```

Defined in components/h1os/src/hal_i2c.c:12

---

### s_bus_handle

`static`

```cpp
i2c_master_bus_handle_t s_bus_handle = NULL
```

Defined in components/h1os/src/hal_i2c.c:14

---

### s_i2c_mutex

`static`

```cpp
SemaphoreHandle_t s_i2c_mutex = NULL
```

Defined in components/h1os/src/hal_i2c.c:15

---

### s_is_inited

`static`

```cpp
bool s_is_inited = false
```

Defined in components/h1os/src/hal_i2c.c:16

---

### TAG

`static`

```cpp
const char * TAG = "HAL_SPI"
```

Defined in components/h1os/src/hal_spi.c:12

---

### s_spi_dev

`static`

```cpp
spi_device_handle_t s_spi_dev = NULL
```

Defined in components/h1os/src/hal_spi.c:14

---

### s_spi_read_dev

`static`

```cpp
spi_device_handle_t s_spi_read_dev = NULL
```

Defined in components/h1os/src/hal_spi.c:15

---

### s_is_inited

`static`

```cpp
bool s_is_inited = false
```

Defined in components/h1os/src/hal_spi.c:16

---

### TAG

`static`

```cpp
const char * TAG = "sub_nvs"
```

Defined in components/h1os/src/sub_nvs.c:15

---

### s_nvs_initialized

`static`

```cpp
bool s_nvs_initialized = false
```

Defined in components/h1os/src/sub_nvs.c:16

---

### TAG

`static`

```cpp
const char * TAG = "sub_rtc"
```

Defined in components/h1os/src/sub_rtc.c:14

---

### TAG

`static`

```cpp
const char * TAG = "h1os_time"
```

Defined in components/h1os/src/h1os_time.c:16

---

### s_sync_cb

`static`

```cpp
h1os_time_sync_cb_t s_sync_cb = NULL
```

Type: [`h1os_time_sync_cb_t`](#h1os_time_sync_cb_t)

Defined in components/h1os/src/h1os_time.c:17

---

### s_sync_user_data

`static`

```cpp
void * s_sync_user_data = NULL
```

Defined in components/h1os/src/h1os_time.c:18

---

### TAG

`static`

```cpp
const char * TAG = "HAL_FLASH"
```

Defined in components/h1os/src/hal_flash.c:12

---

### s_part

`static`

```cpp
const esp_partition_t * s_part = NULL
```

Defined in components/h1os/src/hal_flash.c:13

---

### TAG

`static`

```cpp
const char * TAG = "orch_flow"
```

Defined in components/h1os/src/orch_flow.c:26

---

### s_lockout_until_us

`static`

```cpp
int64_t s_lockout_until_us = 0
```

Defined in components/h1os/src/orch_flow.c:28

---

### TAG

`static`

```cpp
const char * TAG = "sub_audio"
```

Defined in components/h1os/src/sub_audio.c:20

---

### s_tx_chan

`static`

```cpp
i2s_chan_handle_t s_tx_chan = NULL
```

Defined in components/h1os/src/sub_audio.c:57

---

### s_audio_inited

`static`

```cpp
bool s_audio_inited = false
```

Defined in components/h1os/src/sub_audio.c:58

---

### s_i2s_chan_enabled

`static`

```cpp
bool s_i2s_chan_enabled = false
```

Defined in components/h1os/src/sub_audio.c:59

---

### s_audio_queue

`static`

```cpp
QueueHandle_t s_audio_queue = NULL
```

Defined in components/h1os/src/sub_audio.c:60

---

### s_audio_task_handle

`static`

```cpp
TaskHandle_t s_audio_task_handle = NULL
```

Defined in components/h1os/src/sub_audio.c:61

---

### s_audio_is_busy

`static`

```cpp
volatile bool s_audio_is_busy = false
```

Defined in components/h1os/src/sub_audio.c:62

---

### TAG

`static`

```cpp
const char * TAG = "sub_power"
```

Defined in components/h1os/src/sub_power.c:21

---

### s_adc_handle

`static`

```cpp
adc_oneshot_unit_handle_t s_adc_handle = NULL
```

Defined in components/h1os/src/sub_power.c:23

---

### s_cali_handle

`static`

```cpp
adc_cali_handle_t s_cali_handle = NULL
```

Defined in components/h1os/src/sub_power.c:24

---

### s_cali_valid

`static`

```cpp
bool s_cali_valid = false
```

Defined in components/h1os/src/sub_power.c:25

---

### s_lipo_table

`static`

```cpp
const struct @002322170244110267335007143145207204254334113353 s_lipo_table[]
```

Defined in components/h1os/src/sub_power.c:45

---

### s_persisted_state

`static`

```cpp
RTC_DATA_ATTR orch_persisted_state_t s_persisted_state
```

Type: RTC_DATA_ATTR [`orch_persisted_state_t`](#orch_persisted_state_t)

Defined in components/h1os/src/orch_state.c:12

---

### TAG

`static`

```cpp
const char * TAG = "sub_sdcard"
```

Defined in components/h1os/src/sub_sdcard.c:17

---

### s_sd_card

`static`

```cpp
sdmmc_card_t * s_sd_card = NULL
```

Defined in components/h1os/src/sub_sdcard.c:18

---

### TAG

`static`

```cpp
const char * TAG = "sub_sensor"
```

Defined in components/h1os/src/sub_sensor.c:19

---

### s_tsens_handle

`static`

```cpp
temperature_sensor_handle_t s_tsens_handle = NULL
```

Defined in components/h1os/src/sub_sensor.c:27

---

### s_tsens_inited

`static`

```cpp
bool s_tsens_inited = false
```

Defined in components/h1os/src/sub_sensor.c:28

---

### TAG

`static`

```cpp
const char * TAG = "h1os_lvgl"
```

Defined in components/h1os/src/h1os_lvgl.cpp:26

---

### s_lv_display

`static`

```cpp
lv_display_t * s_lv_display = NULL
```

Defined in components/h1os/src/h1os_lvgl.cpp:28

---

### s_lv_keypad_indev

`static`

```cpp
lv_indev_t * s_lv_keypad_indev = NULL
```

Defined in components/h1os/src/h1os_lvgl.cpp:29

---

### s_lvgl_task_handle

`static`

```cpp
TaskHandle_t s_lvgl_task_handle = NULL
```

Defined in components/h1os/src/h1os_lvgl.cpp:30

---

### s_lvgl_task_running

`static`

```cpp
bool s_lvgl_task_running = false
```

Defined in components/h1os/src/h1os_lvgl.cpp:31

---

### s_first_boot_flush

`static`

```cpp
bool s_first_boot_flush = true
```

Defined in components/h1os/src/h1os_lvgl.cpp:32

---

### TAG

`static`

```cpp
const char * TAG = "sub_display"
```

Defined in components/h1os/src/sub_display.cpp:20

---

### s_current_frame

`static`

```cpp
uint8_t s_current_frame[EPD_BUFFER_SIZE]
```

Defined in components/h1os/src/sub_display.cpp:23

---

### s_previous_frame

`static`

```cpp
uint8_t s_previous_frame[EPD_BUFFER_SIZE]
```

Defined in components/h1os/src/sub_display.cpp:24

---

### s_busy_sem

`static`

```cpp
SemaphoreHandle_t s_busy_sem = NULL
```

Defined in components/h1os/src/sub_display.cpp:25

---

### s_inited

`static`

```cpp
bool s_inited = false
```

Defined in components/h1os/src/sub_display.cpp:26

---

### WF_PARTIAL_1IN54

`static`

```cpp
const uint8_t WF_PARTIAL_1IN54[159]
```

Defined in components/h1os/src/sub_display.cpp:29

---

### TAG

`static`

```cpp
const char * TAG = "h1os_lifecycle"
```

Defined in components/h1os/src/h1os_lifecycle.c:38

---

### s_app_lifecycle

`static`

```cpp
h1os_lifecycle_t s_app_lifecycle = {0}
```

Type: [`h1os_lifecycle_t`](#h1os_lifecycle_t)

Defined in components/h1os/src/h1os_lifecycle.c:39

---

### s_session_expiry_us

`static`

```cpp
int64_t s_session_expiry_us = 0
```

Defined in components/h1os/src/h1os_lifecycle.c:40

---

### s_session_task_handle

`static`

```cpp
TaskHandle_t s_session_task_handle = NULL
```

Defined in components/h1os/src/h1os_lifecycle.c:41

---

### s_session_running

`static`

```cpp
bool s_session_running = false
```

Defined in components/h1os/src/h1os_lifecycle.c:42

---

### TAG

`static`

```cpp
const char * TAG = "orch_display_sync"
```

Defined in components/h1os/src/orch_display_sync.c:20

---

### s_frame_dirty

`static`

```cpp
bool s_frame_dirty = false
```

Defined in components/h1os/src/orch_display_sync.c:22



## audio_cmd_t

```cpp
struct audio_cmd_t
```

Defined in components/h1os/src/sub_audio.c:37

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| [`audio_cmd_type_t`](#audio_cmd_type_t) | [`type`](#type)  |  |
| `union audio_cmd_t::@314331317146101264073125214271270352112311102220` | [`params`](#params)  |  |
| `SemaphoreHandle_t` | [`done_sem`](#done_sem)  |  |
| `esp_err_t *` | [`result`](#result)  |  |

---

#### type

```cpp
audio_cmd_type_t type
```

Type: [`audio_cmd_type_t`](#audio_cmd_type_t)

Defined in components/h1os/src/sub_audio.c:38

---

#### params

```cpp
union audio_cmd_t::@314331317146101264073125214271270352112311102220 params
```

Defined in components/h1os/src/sub_audio.c:52

---

#### done_sem

```cpp
SemaphoreHandle_t done_sem
```

Defined in components/h1os/src/sub_audio.c:53

---

#### result

```cpp
esp_err_t * result
```

Defined in components/h1os/src/sub_audio.c:54



## [union].params

```cpp
union [union].params
```

Defined in components/h1os/src/sub_audio.c:39

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `struct audio_cmd_t::@314331317146101264073125214271270352112311102220::@111152075243353105304245335051361226004373363135` | [`tone`](#tone)  |  |
| `struct audio_cmd_t::@314331317146101264073125214271270352112311102220::@101272124024340224361146157000014111126204144113` | [`chime`](#chime)  |  |
| `struct audio_cmd_t::@314331317146101264073125214271270352112311102220::@100050337062317073354053222303152317146347103231` | [`pcm`](#pcm)  |  |

---

#### tone

```cpp
struct audio_cmd_t::@314331317146101264073125214271270352112311102220::@111152075243353105304245335051361226004373363135 tone
```

Defined in components/h1os/src/sub_audio.c:43

---

#### chime

```cpp
struct audio_cmd_t::@314331317146101264073125214271270352112311102220::@101272124024340224361146157000014111126204144113 chime
```

Defined in components/h1os/src/sub_audio.c:46

---

#### pcm

```cpp
struct audio_cmd_t::@314331317146101264073125214271270352112311102220::@100050337062317073354053222303152317146347103231 pcm
```

Defined in components/h1os/src/sub_audio.c:51



## [struct].params.tone

```cpp
struct [struct].params.tone
```

Defined in components/h1os/src/sub_audio.c:40

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint32_t` | [`frequency_hz`](#frequency_hz)  |  |
| `uint32_t` | [`duration_ms`](#duration_ms)  |  |

---

#### frequency_hz

```cpp
uint32_t frequency_hz
```

Defined in components/h1os/src/sub_audio.c:41

---

#### duration_ms

```cpp
uint32_t duration_ms
```

Defined in components/h1os/src/sub_audio.c:42



## [struct].params.chime

```cpp
struct [struct].params.chime
```

Defined in components/h1os/src/sub_audio.c:44

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint8_t` | [`chime_type`](#chime_type)  |  |

---

#### chime_type

```cpp
uint8_t chime_type
```

Defined in components/h1os/src/sub_audio.c:45



## [struct].params.pcm

```cpp
struct [struct].params.pcm
```

Defined in components/h1os/src/sub_audio.c:47

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `const int16_t *` | [`samples`](#samples)  |  |
| `size_t` | [`sample_count`](#sample_count)  |  |
| `uint32_t` | [`sample_rate_hz`](#sample_rate_hz)  |  |

---

#### samples

```cpp
const int16_t * samples
```

Defined in components/h1os/src/sub_audio.c:48

---

#### sample_count

```cpp
size_t sample_count
```

Defined in components/h1os/src/sub_audio.c:49

---

#### sample_rate_hz

```cpp
uint32_t sample_rate_hz
```

Defined in components/h1os/src/sub_audio.c:50



## h1os_lifecycle_t

```cpp
#include <C:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/h1os/include/h1os/h1os.h>
```

```cpp
struct h1os_lifecycle_t
```

Defined in components/h1os/include/h1os/h1os.h:79

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| [`h1os_boot_cb_t`](#h1os_boot_cb_t) | [`on_boot`](#on_boot)  | Cold boot / power-on reset hook. |
| [`h1os_wake_cb_t`](#h1os_wake_cb_t) | [`on_wake`](#on_wake)  | Interactive wake hook (Timer / RTC Alarm / Button Tap). |
| [`h1os_pre_sleep_cb_t`](#h1os_pre_sleep_cb_t) | [`on_pre_sleep`](#on_pre_sleep)  | Hook executed immediately prior to entering deep sleep. |
| [`h1os_shutdown_cb_t`](#h1os_shutdown_cb_t) | [`on_shutdown`](#on_shutdown)  | Hook executed immediately prior to battery cut. |
| `struct h1os_lifecycle_t::@275102161223227315136356146000256100366356360027` | [`presentation`](#presentation)  |  |
| `struct h1os_lifecycle_t::@000226124311323177170300277332067211356300300233` | [`session`](#session)  |  |
| `void *` | [`user_data`](#user_data)  |  |

---

#### on_boot

```cpp
h1os_boot_cb_t on_boot
```

Type: [`h1os_boot_cb_t`](#h1os_boot_cb_t)

Defined in components/h1os/include/h1os/h1os.h:81

Cold boot / power-on reset hook.

---

#### on_wake

```cpp
h1os_wake_cb_t on_wake
```

Type: [`h1os_wake_cb_t`](#h1os_wake_cb_t)

Defined in components/h1os/include/h1os/h1os.h:82

Interactive wake hook (Timer / RTC Alarm / Button Tap).

---

#### on_pre_sleep

```cpp
h1os_pre_sleep_cb_t on_pre_sleep
```

Type: [`h1os_pre_sleep_cb_t`](#h1os_pre_sleep_cb_t)

Defined in components/h1os/include/h1os/h1os.h:83

Hook executed immediately prior to entering deep sleep.

---

#### on_shutdown

```cpp
h1os_shutdown_cb_t on_shutdown
```

Type: [`h1os_shutdown_cb_t`](#h1os_shutdown_cb_t)

Defined in components/h1os/include/h1os/h1os.h:84

Hook executed immediately prior to battery cut.

---

#### presentation

```cpp
struct h1os_lifecycle_t::@275102161223227315136356146000256100366356360027 presentation
```

Defined in components/h1os/include/h1os/h1os.h:91

---

#### session

```cpp
struct h1os_lifecycle_t::@000226124311323177170300277332067211356300300233 session
```

Defined in components/h1os/include/h1os/h1os.h:99

---

#### user_data

```cpp
void * user_data
```

Defined in components/h1os/include/h1os/h1os.h:101



## [struct].presentation

```cpp
struct [struct].presentation
```

Defined in components/h1os/include/h1os/h1os.h:87

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| [`h1os_splash_cb_t`](#h1os_splash_cb_t) | [`on_splash`](#on_splash)  | Custom splash rendering callback. |
| [`h1os_chime_cb_t`](#h1os_chime_cb_t) | [`on_chime`](#on_chime)  | Custom chime callback. |
| `uint8_t` | [`chime_mask`](#chime_mask)  | Hardware synthesized chime bitmask. |

---

#### on_splash

```cpp
h1os_splash_cb_t on_splash
```

Type: [`h1os_splash_cb_t`](#h1os_splash_cb_t)

Defined in components/h1os/include/h1os/h1os.h:88

Custom splash rendering callback.

---

#### on_chime

```cpp
h1os_chime_cb_t on_chime
```

Type: [`h1os_chime_cb_t`](#h1os_chime_cb_t)

Defined in components/h1os/include/h1os/h1os.h:89

Custom chime callback.

---

#### chime_mask

```cpp
uint8_t chime_mask
```

Defined in components/h1os/include/h1os/h1os.h:90

Hardware synthesized chime bitmask.



## [struct].session

```cpp
struct [struct].session
```

Defined in components/h1os/include/h1os/h1os.h:94

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint32_t` | [`inactivity_timeout_sec`](#inactivity_timeout_sec)  | Inactivity sleep timer (default: 30s). |
| `bool` | [`enable_dfs_80mhz`](#enable_dfs_80mhz)  | Enable 80 MHz power droop while waiting for input (default: true). |
| `uint32_t` | [`flow_a_period_sec`](#flow_a_period_sec)  | Flow A headless sensor sprint interval (default: 60s). |
| `uint32_t` | [`flow_b_period_sec`](#flow_b_period_sec)  | Flow B main application wake interval (default: 120s). |

---

#### inactivity_timeout_sec

```cpp
uint32_t inactivity_timeout_sec
```

Defined in components/h1os/include/h1os/h1os.h:95

Inactivity sleep timer (default: 30s).

---

#### enable_dfs_80mhz

```cpp
bool enable_dfs_80mhz
```

Defined in components/h1os/include/h1os/h1os.h:96

Enable 80 MHz power droop while waiting for input (default: true).

---

#### flow_a_period_sec

```cpp
uint32_t flow_a_period_sec
```

Defined in components/h1os/include/h1os/h1os.h:97

Flow A headless sensor sprint interval (default: 60s).

---

#### flow_b_period_sec

```cpp
uint32_t flow_b_period_sec
```

Defined in components/h1os/include/h1os/h1os.h:98

Flow B main application wake interval (default: 120s).



## h1os_telemetry_t

```cpp
#include <C:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/h1os/include/h1os/h1os.h>
```

```cpp
struct h1os_telemetry_t
```

Defined in components/h1os/include/h1os/h1os.h:107

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `float` | [`ambient_temp_c`](#ambient_temp_c)  |  |
| `float` | [`ambient_temp_f`](#ambient_temp_f)  |  |
| `float` | [`ambient_rh_pct`](#ambient_rh_pct)  |  |
| `float` | [`dew_point_c`](#dew_point_c)  |  |
| `float` | [`dew_point_f`](#dew_point_f)  |  |
| `float` | [`absolute_humidity_g`](#absolute_humidity_g)  |  |
| `float` | [`raw_shtc3_temp_c`](#raw_shtc3_temp_c)  |  |
| `float` | [`mcu_die_temp_c`](#mcu_die_temp_c)  |  |
| `float` | [`epd_glass_temp_c`](#epd_glass_temp_c)  |  |
| `bool` | [`is_thermally_settled`](#is_thermally_settled)  |  |
| `uint32_t` | [`sample_count`](#sample_count-1)  |  |
| `uint16_t` | [`battery_mv`](#battery_mv)  |  |
| `uint8_t` | [`battery_percent`](#battery_percent)  |  |
| `bool` | [`is_usb_powered`](#is_usb_powered)  |  |

---

#### ambient_temp_c

```cpp
float ambient_temp_c
```

Defined in components/h1os/include/h1os/h1os.h:109

---

#### ambient_temp_f

```cpp
float ambient_temp_f
```

Defined in components/h1os/include/h1os/h1os.h:110

---

#### ambient_rh_pct

```cpp
float ambient_rh_pct
```

Defined in components/h1os/include/h1os/h1os.h:111

---

#### dew_point_c

```cpp
float dew_point_c
```

Defined in components/h1os/include/h1os/h1os.h:112

---

#### dew_point_f

```cpp
float dew_point_f
```

Defined in components/h1os/include/h1os/h1os.h:113

---

#### absolute_humidity_g

```cpp
float absolute_humidity_g
```

Defined in components/h1os/include/h1os/h1os.h:114

---

#### raw_shtc3_temp_c

```cpp
float raw_shtc3_temp_c
```

Defined in components/h1os/include/h1os/h1os.h:117

---

#### mcu_die_temp_c

```cpp
float mcu_die_temp_c
```

Defined in components/h1os/include/h1os/h1os.h:118

---

#### epd_glass_temp_c

```cpp
float epd_glass_temp_c
```

Defined in components/h1os/include/h1os/h1os.h:119

---

#### is_thermally_settled

```cpp
bool is_thermally_settled
```

Defined in components/h1os/include/h1os/h1os.h:122

---

#### sample_count

```cpp
uint32_t sample_count
```

Defined in components/h1os/include/h1os/h1os.h:123

---

#### battery_mv

```cpp
uint16_t battery_mv
```

Defined in components/h1os/include/h1os/h1os.h:124

---

#### battery_percent

```cpp
uint8_t battery_percent
```

Defined in components/h1os/include/h1os/h1os.h:125

---

#### is_usb_powered

```cpp
bool is_usb_powered
```

Defined in components/h1os/include/h1os/h1os.h:126



## h1os_wake_context_t

```cpp
#include <C:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/h1os/include/h1os/h1os.h>
```

```cpp
struct h1os_wake_context_t
```

Defined in components/h1os/include/h1os/h1os.h:44

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

#### reset_reason

```cpp
esp_reset_reason_t reset_reason
```

Defined in components/h1os/include/h1os/h1os.h:45

---

#### wakeup_causes

```cpp
uint32_t wakeup_causes
```

Defined in components/h1os/include/h1os/h1os.h:46

Bitmap of wakeup sources (esp_sleep_get_wakeup_causes).

---

#### boot_count

```cpp
uint32_t boot_count
```

Defined in components/h1os/include/h1os/h1os.h:47

---

#### deep_sleep_count

```cpp
uint32_t deep_sleep_count
```

Defined in components/h1os/include/h1os/h1os.h:48

---

#### woke_from_button

```cpp
bool woke_from_button
```

Defined in components/h1os/include/h1os/h1os.h:49

---

#### wake_button

```cpp
uint8_t wake_button
```

Defined in components/h1os/include/h1os/h1os.h:50

---

#### sleep_duration_sec

```cpp
uint32_t sleep_duration_sec
```

Defined in components/h1os/include/h1os/h1os.h:51

---

#### user_data

```cpp
void * user_data
```

Defined in components/h1os/include/h1os/h1os.h:52



## orch_persisted_state_t

```cpp
#include <C:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/h1os/include/h1os/orch_state.h>
```

```cpp
struct orch_persisted_state_t
```

Defined in components/h1os/include/h1os/orch_state.h:43

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
| `int16_t` | [`amb_floor_temp_centi_c`](#amb_floor_temp_centi_c)  |  |
| `int16_t` | [`_pad`](#_pad)  |  |
| `float` | [`reconstructed_amb_temp_c`](#reconstructed_amb_temp_c)  |  |
| `float` | [`reconstructed_amb_rh_pct`](#reconstructed_amb_rh_pct)  |  |
| `float` | [`reconstructed_dew_point_c`](#reconstructed_dew_point_c)  |  |
| `float` | [`vapor_pressure_hpa`](#vapor_pressure_hpa)  |  |
| `bool` | [`ewma_inited`](#ewma_inited)  |  |
| `uint8_t` | [`app_stage`](#app_stage)  |  |
| `uint8_t` | [`scratchpad_len`](#scratchpad_len)  |  |
| `uint8_t` | [`scratchpad`](#scratchpad)  |  |
| [`orch_tri_node_sample_t`](#orch_tri_node_sample_t) | [`ring`](#ring)  |  |
| `uint8_t` | [`ring_head`](#ring_head)  |  |
| `uint32_t` | [`total_samples`](#total_samples)  |  |

---

#### magic

```cpp
uint32_t magic
```

Defined in components/h1os/include/h1os/orch_state.h:44

---

#### boot_count

```cpp
uint32_t boot_count
```

Defined in components/h1os/include/h1os/orch_state.h:45

---

#### wake_count

```cpp
uint32_t wake_count
```

Defined in components/h1os/include/h1os/orch_state.h:46

---

#### flags

```cpp
uint8_t flags
```

Defined in components/h1os/include/h1os/orch_state.h:47

---

#### ulp_dispatch_reason

```cpp
uint8_t ulp_dispatch_reason
```

Defined in components/h1os/include/h1os/orch_state.h:48

---

#### last_vbat_mv

```cpp
uint16_t last_vbat_mv
```

Defined in components/h1os/include/h1os/orch_state.h:49

---

#### sample_interval_sec

```cpp
uint32_t sample_interval_sec
```

Defined in components/h1os/include/h1os/orch_state.h:51

---

#### flow_b_period_sec

```cpp
uint32_t flow_b_period_sec
```

Defined in components/h1os/include/h1os/orch_state.h:52

---

#### wake_timestamp_epoch

```cpp
uint32_t wake_timestamp_epoch
```

Defined in components/h1os/include/h1os/orch_state.h:53

---

#### ulp_vbat_scale

```cpp
uint32_t ulp_vbat_scale
```

Defined in components/h1os/include/h1os/orch_state.h:56

---

#### ulp_vbat_offset_mv

```cpp
int32_t ulp_vbat_offset_mv
```

Defined in components/h1os/include/h1os/orch_state.h:57

---

#### epd_partial_refresh_count

```cpp
uint16_t epd_partial_refresh_count
```

Defined in components/h1os/include/h1os/orch_state.h:60

---

#### amb_floor_temp_centi_c

```cpp
int16_t amb_floor_temp_centi_c
```

Defined in components/h1os/include/h1os/orch_state.h:63

---

#### _pad

```cpp
int16_t _pad
```

Defined in components/h1os/include/h1os/orch_state.h:64

---

#### reconstructed_amb_temp_c

```cpp
float reconstructed_amb_temp_c
```

Defined in components/h1os/include/h1os/orch_state.h:67

---

#### reconstructed_amb_rh_pct

```cpp
float reconstructed_amb_rh_pct
```

Defined in components/h1os/include/h1os/orch_state.h:68

---

#### reconstructed_dew_point_c

```cpp
float reconstructed_dew_point_c
```

Defined in components/h1os/include/h1os/orch_state.h:69

---

#### vapor_pressure_hpa

```cpp
float vapor_pressure_hpa
```

Defined in components/h1os/include/h1os/orch_state.h:70

---

#### ewma_inited

```cpp
bool ewma_inited
```

Defined in components/h1os/include/h1os/orch_state.h:71

---

#### app_stage

```cpp
uint8_t app_stage
```

Defined in components/h1os/include/h1os/orch_state.h:74

---

#### scratchpad_len

```cpp
uint8_t scratchpad_len
```

Defined in components/h1os/include/h1os/orch_state.h:75

---

#### scratchpad

```cpp
uint8_t scratchpad[32]
```

Defined in components/h1os/include/h1os/orch_state.h:76

---

#### ring

```cpp
orch_tri_node_sample_t ring[32]
```

Defined in components/h1os/include/h1os/orch_state.h:79

---

#### ring_head

```cpp
uint8_t ring_head
```

Defined in components/h1os/include/h1os/orch_state.h:80

---

#### total_samples

```cpp
uint32_t total_samples
```

Defined in components/h1os/include/h1os/orch_state.h:81



## orch_tri_node_sample_t

```cpp
#include <C:/Users/Matt/Documents/GitHub/esp32-s3_bsp/components/h1os/include/h1os/orch_state.h>
```

```cpp
struct orch_tri_node_sample_t
```

Defined in components/h1os/include/h1os/orch_state.h:33

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `int16_t` | [`shtc3_temp_centi_c`](#shtc3_temp_centi_c)  |  |
| `uint16_t` | [`shtc3_rh_centi_pct`](#shtc3_rh_centi_pct)  |  |
| `int16_t` | [`mcu_tsens_centi_c`](#mcu_tsens_centi_c)  |  |
| `int16_t` | [`epd_glass_centi_c`](#epd_glass_centi_c)  |  |
| `uint32_t` | [`timestamp_sec`](#timestamp_sec)  |  |
| `uint8_t` | [`quality_flags`](#quality_flags)  |  |
| `uint8_t` | [`_pad`](#_pad-1)  |  |

---

#### shtc3_temp_centi_c

```cpp
int16_t shtc3_temp_centi_c
```

Defined in components/h1os/include/h1os/orch_state.h:34

---

#### shtc3_rh_centi_pct

```cpp
uint16_t shtc3_rh_centi_pct
```

Defined in components/h1os/include/h1os/orch_state.h:35

---

#### mcu_tsens_centi_c

```cpp
int16_t mcu_tsens_centi_c
```

Defined in components/h1os/include/h1os/orch_state.h:36

---

#### epd_glass_centi_c

```cpp
int16_t epd_glass_centi_c
```

Defined in components/h1os/include/h1os/orch_state.h:37

---

#### timestamp_sec

```cpp
uint32_t timestamp_sec
```

Defined in components/h1os/include/h1os/orch_state.h:38

---

#### quality_flags

```cpp
uint8_t quality_flags
```

Defined in components/h1os/include/h1os/orch_state.h:39

---

#### _pad

```cpp
uint8_t _pad[3]
```

Defined in components/h1os/include/h1os/orch_state.h:40



## [struct].s_lipo_table

```cpp
struct [struct].s_lipo_table
```

Defined in components/h1os/src/sub_power.c:28

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint16_t` | [`mv`](#mv)  |  |
| `uint8_t` | [`pct`](#pct)  |  |

---

#### mv

```cpp
uint16_t mv
```

Defined in components/h1os/src/sub_power.c:29

---

#### pct

```cpp
uint8_t pct
```

Defined in components/h1os/src/sub_power.c:30



## [struct].params.pcm

```cpp
struct [struct].params.pcm
```

Defined in components/h1os/src/sub_audio.c:47

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `const int16_t *` | [`samples`](#samples)  |  |
| `size_t` | [`sample_count`](#sample_count)  |  |
| `uint32_t` | [`sample_rate_hz`](#sample_rate_hz)  |  |

---

#### samples

```cpp
const int16_t * samples
```

Defined in components/h1os/src/sub_audio.c:48

---

#### sample_count

```cpp
size_t sample_count
```

Defined in components/h1os/src/sub_audio.c:49

---

#### sample_rate_hz

```cpp
uint32_t sample_rate_hz
```

Defined in components/h1os/src/sub_audio.c:50



## [struct].params.tone

```cpp
struct [struct].params.tone
```

Defined in components/h1os/src/sub_audio.c:40

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint32_t` | [`frequency_hz`](#frequency_hz)  |  |
| `uint32_t` | [`duration_ms`](#duration_ms)  |  |

---

#### frequency_hz

```cpp
uint32_t frequency_hz
```

Defined in components/h1os/src/sub_audio.c:41

---

#### duration_ms

```cpp
uint32_t duration_ms
```

Defined in components/h1os/src/sub_audio.c:42



## [struct].session

```cpp
struct [struct].session
```

Defined in components/h1os/include/h1os/h1os.h:94

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint32_t` | [`inactivity_timeout_sec`](#inactivity_timeout_sec)  | Inactivity sleep timer (default: 30s). |
| `bool` | [`enable_dfs_80mhz`](#enable_dfs_80mhz)  | Enable 80 MHz power droop while waiting for input (default: true). |
| `uint32_t` | [`flow_a_period_sec`](#flow_a_period_sec)  | Flow A headless sensor sprint interval (default: 60s). |
| `uint32_t` | [`flow_b_period_sec`](#flow_b_period_sec)  | Flow B main application wake interval (default: 120s). |

---

#### inactivity_timeout_sec

```cpp
uint32_t inactivity_timeout_sec
```

Defined in components/h1os/include/h1os/h1os.h:95

Inactivity sleep timer (default: 30s).

---

#### enable_dfs_80mhz

```cpp
bool enable_dfs_80mhz
```

Defined in components/h1os/include/h1os/h1os.h:96

Enable 80 MHz power droop while waiting for input (default: true).

---

#### flow_a_period_sec

```cpp
uint32_t flow_a_period_sec
```

Defined in components/h1os/include/h1os/h1os.h:97

Flow A headless sensor sprint interval (default: 60s).

---

#### flow_b_period_sec

```cpp
uint32_t flow_b_period_sec
```

Defined in components/h1os/include/h1os/h1os.h:98

Flow B main application wake interval (default: 120s).



## [struct].params.chime

```cpp
struct [struct].params.chime
```

Defined in components/h1os/src/sub_audio.c:44

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint8_t` | [`chime_type`](#chime_type)  |  |

---

#### chime_type

```cpp
uint8_t chime_type
```

Defined in components/h1os/src/sub_audio.c:45



## [struct].presentation

```cpp
struct [struct].presentation
```

Defined in components/h1os/include/h1os/h1os.h:87

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| [`h1os_splash_cb_t`](#h1os_splash_cb_t) | [`on_splash`](#on_splash)  | Custom splash rendering callback. |
| [`h1os_chime_cb_t`](#h1os_chime_cb_t) | [`on_chime`](#on_chime)  | Custom chime callback. |
| `uint8_t` | [`chime_mask`](#chime_mask)  | Hardware synthesized chime bitmask. |

---

#### on_splash

```cpp
h1os_splash_cb_t on_splash
```

Type: [`h1os_splash_cb_t`](#h1os_splash_cb_t)

Defined in components/h1os/include/h1os/h1os.h:88

Custom splash rendering callback.

---

#### on_chime

```cpp
h1os_chime_cb_t on_chime
```

Type: [`h1os_chime_cb_t`](#h1os_chime_cb_t)

Defined in components/h1os/include/h1os/h1os.h:89

Custom chime callback.

---

#### chime_mask

```cpp
uint8_t chime_mask
```

Defined in components/h1os/include/h1os/h1os.h:90

Hardware synthesized chime bitmask.



## [union].params

```cpp
union [union].params
```

Defined in components/h1os/src/sub_audio.c:39

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `struct audio_cmd_t::@314331317146101264073125214271270352112311102220::@111152075243353105304245335051361226004373363135` | [`tone`](#tone)  |  |
| `struct audio_cmd_t::@314331317146101264073125214271270352112311102220::@101272124024340224361146157000014111126204144113` | [`chime`](#chime)  |  |
| `struct audio_cmd_t::@314331317146101264073125214271270352112311102220::@100050337062317073354053222303152317146347103231` | [`pcm`](#pcm)  |  |

---

#### tone

```cpp
struct audio_cmd_t::@314331317146101264073125214271270352112311102220::@111152075243353105304245335051361226004373363135 tone
```

Defined in components/h1os/src/sub_audio.c:43

---

#### chime

```cpp
struct audio_cmd_t::@314331317146101264073125214271270352112311102220::@101272124024340224361146157000014111126204144113 chime
```

Defined in components/h1os/src/sub_audio.c:46

---

#### pcm

```cpp
struct audio_cmd_t::@314331317146101264073125214271270352112311102220::@100050337062317073354053222303152317146347103231 pcm
```

Defined in components/h1os/src/sub_audio.c:51



## [struct].params.tone

```cpp
struct [struct].params.tone
```

Defined in components/h1os/src/sub_audio.c:40

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint32_t` | [`frequency_hz`](#frequency_hz)  |  |
| `uint32_t` | [`duration_ms`](#duration_ms)  |  |

---

#### frequency_hz

```cpp
uint32_t frequency_hz
```

Defined in components/h1os/src/sub_audio.c:41

---

#### duration_ms

```cpp
uint32_t duration_ms
```

Defined in components/h1os/src/sub_audio.c:42



## [struct].params.chime

```cpp
struct [struct].params.chime
```

Defined in components/h1os/src/sub_audio.c:44

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint8_t` | [`chime_type`](#chime_type)  |  |

---

#### chime_type

```cpp
uint8_t chime_type
```

Defined in components/h1os/src/sub_audio.c:45



## [struct].params.pcm

```cpp
struct [struct].params.pcm
```

Defined in components/h1os/src/sub_audio.c:47

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `const int16_t *` | [`samples`](#samples)  |  |
| `size_t` | [`sample_count`](#sample_count)  |  |
| `uint32_t` | [`sample_rate_hz`](#sample_rate_hz)  |  |

---

#### samples

```cpp
const int16_t * samples
```

Defined in components/h1os/src/sub_audio.c:48

---

#### sample_count

```cpp
size_t sample_count
```

Defined in components/h1os/src/sub_audio.c:49

---

#### sample_rate_hz

```cpp
uint32_t sample_rate_hz
```

Defined in components/h1os/src/sub_audio.c:50

Generated by [Moxygen](https://0state.com/moxygen)