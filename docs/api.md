# API Reference

## Classes

| Name | Description |
|------|-------------|
| [`h1os_ui_msg_t`](#h1os_ui_msg_t) | Message envelope for the Core 0 -> Core 1 asynchronous UI mutation queue. |
| [`h1os_lifecycle_t`](#h1os_lifecycle_t) | Declarative application lifecycle configuration structure. |
| [`h1os_telemetry_t`](#h1os_telemetry_t) | Comprehensive environmental telemetry and system metrics snapshot. |
| [`h1os_wake_context_t`](#h1os_wake_context_t) | Platform wakeup context descriptor. |
| [`h1os_session_config_t`](#h1os_session_config_t) | Lifecycle session timeout, clock scaling, flow slicing, and sync configuration. |
| [`orch_persisted_state_t`](#orch_persisted_state_t) | Master persistent state block allocated in RTC Slow SRAM. |
| [`h1os_autonomy_metrics_t`](#h1os_autonomy_metrics_t) | Empirical battery autonomy metrics over total elapsed runtime. |
| [`orch_tri_node_sample_t`](#orch_tri_node_sample_t) | Compact 16-byte Tri-Node sample entry in RTC Slow SRAM. |
| [`orch_nvs_runtime_blob_t`](#orch_nvs_runtime_blob_t) | Compact 12-byte atomic battery autonomy runtime blob committed to Flash NVS. |
| [`h1os_presentation_config_t`](#h1os_presentation_config_t) | Presentation splash, audio chime, and master volume configuration. |

## Macros

---

{#h1os_lifecycle_default_config}

### H1OS_LIFECYCLE_DEFAULT_CONFIG

```cpp
#define H1OS_LIFECYCLE_DEFAULT_CONFIG() {                                                                      \
    .session = {                                                       \
        .inactivity_timeout_sec = H1OS_DEFAULT_INACTIVITY_TIMEOUT_SEC, \
        .clk_mode = SYS_CLK_MODE_DYNAMIC,                              \
        .flow_a_period_sec = H1OS_DEFAULT_FLOW_A_PERIOD_SEC,           \
        .flow_b_period_sec = H1OS_DEFAULT_FLOW_B_PERIOD_SEC,           \
        .sync_wait_ms = 0U,                                            \
        .sync_timeout_ms = 5000U,                                      \
    },                                                                 \
    .presentation = { 0 }                                              \
}
```

Defined in h1os/h1os.h:57

Default compound literal macro for standard lifecycle session configuration.

---

{#sub_nvs_namespace}

### SUB_NVS_NAMESPACE

```cpp
#define SUB_NVS_NAMESPACE "h1os"
```

Defined in h1os/sub_nvs.h:21

Default NVS partition namespace for H1OS settings.

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

{#sub_power_vbat_trim_offset_mv}

### SUB_POWER_VBAT_TRIM_OFFSET_MV

```cpp
#define SUB_POWER_VBAT_TRIM_OFFSET_MV 80
```

Defined in h1os/sub_power.h:18

Empirical ADC calibration trim offset in millivolts (+76..+80 mV).

---

{#orch_rtc_magic}

### ORCH_RTC_MAGIC

```cpp
#define ORCH_RTC_MAGIC 0x534C4154U
```

Defined in h1os/orch_state.h:20

RTC state validation magic word ('SLAT').

---

{#orch_ring_capacity}

### ORCH_RING_CAPACITY

```cpp
#define ORCH_RING_CAPACITY 32
```

Defined in h1os/orch_state.h:21

Fixed capacity of historical telemetry sample ring buffer.

---

{#orch_tsens_default_intercept_centi_c}

### ORCH_TSENS_DEFAULT_INTERCEPT_CENTI_C

```cpp
#define ORCH_TSENS_DEFAULT_INTERCEPT_CENTI_C 2052
```

Defined in h1os/orch_state.h:22

Default TSENS Q12 fixed-point intercept in centi-°C (20.52°C).

---

{#orch_nvs_autonomy_commit_interval_sec}

### ORCH_NVS_AUTONOMY_COMMIT_INTERVAL_SEC

```cpp
#define ORCH_NVS_AUTONOMY_COMMIT_INTERVAL_SEC 3600U
```

Defined in h1os/orch_state.h:23

Minimum elapsed deep sleep interval between unattended NVS commits (1 hour).

---

{#sample_flag_valid_cold}

### SAMPLE_FLAG_VALID_COLD

```cpp
#define SAMPLE_FLAG_VALID_COLD 0x01
```

Defined in h1os/orch_state.h:73

Steady-state sample captured during quiescent sleep.

---

{#sample_flag_thermal_settled}

### SAMPLE_FLAG_THERMAL_SETTLED

```cpp
#define SAMPLE_FLAG_THERMAL_SETTLED 0x02
```

Defined in h1os/orch_state.h:74

Thermal plateau settled indicator.

---

{#sample_delta_gate_centi_c}

### SAMPLE_DELTA_GATE_CENTI_C

```cpp
#define SAMPLE_DELTA_GATE_CENTI_C 20
```

Defined in h1os/orch_state.h:75

Maximum allowable drift for steady state (0.20°C).

---

{#orch_flag_none}

### ORCH_FLAG_NONE

```cpp
#define ORCH_FLAG_NONE 0
```

Defined in h1os/orch_state.h:163

No persistent flags active.

---

{#orch_flag_epd_frame_valid}

### ORCH_FLAG_EPD_FRAME_VALID

```cpp
#define ORCH_FLAG_EPD_FRAME_VALID (1 << 0)
```

Defined in h1os/orch_state.h:164

Flash partition contains valid preserved display frame.

---

{#orch_flag_critical_battery}

### ORCH_FLAG_CRITICAL_BATTERY

```cpp
#define ORCH_FLAG_CRITICAL_BATTERY (1 << 1)
```

Defined in h1os/orch_state.h:165

Battery below brownout threshold.

---

{#orch_flag_thermal_lockout}

### ORCH_FLAG_THERMAL_LOCKOUT

```cpp
#define ORCH_FLAG_THERMAL_LOCKOUT (1 << 2)
```

Defined in h1os/orch_state.h:166

Self-heating lockout active.

---

{#orch_flag_rh_alert_active}

### ORCH_FLAG_RH_ALERT_ACTIVE

```cpp
#define ORCH_FLAG_RH_ALERT_ACTIVE (1 << 3)
```

Defined in h1os/orch_state.h:167

Settled RH outside configured humidor target bounds.

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
#define H1OS_VERSION_MINOR 4
```

Defined in h1os/h1os_version.h:18

Minor version number (backward-compatible features).

---

{#h1os_version_patch}

### H1OS_VERSION_PATCH

```cpp
#define H1OS_VERSION_PATCH 11
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
#define H1OS_VERSION_STRING "2.4.11-dev"
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

{#orch_tsens_settling_delay_us}

### ORCH_TSENS_SETTLING_DELAY_US

```cpp
#define ORCH_TSENS_SETTLING_DELAY_US 400U
```

Defined in h1os/orch_wake_stub.h:20

Minimum analog settling delay following TSENS power-up (400 µs).

---

{#orch_tsens_ready_poll_interval_us}

### ORCH_TSENS_READY_POLL_INTERVAL_US

```cpp
#define ORCH_TSENS_READY_POLL_INTERVAL_US 5U
```

Defined in h1os/orch_wake_stub.h:21

Polling step interval while awaiting TSENS ready bit (5 µs).

---

{#orch_tsens_ready_timeout_cycles}

### ORCH_TSENS_READY_TIMEOUT_CYCLES

```cpp
#define ORCH_TSENS_READY_TIMEOUT_CYCLES 1000U
```

Defined in h1os/orch_wake_stub.h:22

Maximum polling loop iterations (1000 * 5 µs = 5 ms bound).

---

{#orch_shtc3_conversion_total_us}

### ORCH_SHTC3_CONVERSION_TOTAL_US

```cpp
#define ORCH_SHTC3_CONVERSION_TOTAL_US 18000U
```

Defined in h1os/orch_wake_stub.h:23

Sensirion SHTC3 maximum measurement duration with safety margin (18.0 ms).

---

{#orch_tsens_estimated_sample_us}

### ORCH_TSENS_ESTIMATED_SAMPLE_US

```cpp
#define ORCH_TSENS_ESTIMATED_SAMPLE_US 450U
```

Defined in h1os/orch_wake_stub.h:24

Nominal TSENS acquisition duration (settling + ready poll).

Remainder wait: 17,550 µs

---

{#orch_shtc3_post_tsens_delay_us}

### ORCH_SHTC3_POST_TSENS_DELAY_US

```cpp
#define ORCH_SHTC3_POST_TSENS_DELAY_US (ORCH_SHTC3_CONVERSION_TOTAL_US - ORCH_TSENS_ESTIMATED_SAMPLE_US)
```

Defined in h1os/orch_wake_stub.h:27

## Enumerations

---

{#h1os_wake_state_t}

### h1os_wake_state_t

```cpp
enum h1os_wake_state_t
```

Defined in h1os/h1os.h:73

High-level application wake state classification (MANDATE-04).

| Value | Description |
|-------|-------------|
| `H1OS_WAKE_STATE_BOOT` | Cold boot / power-on reset cycle. |
| `H1OS_WAKE_STATE_INTERACTIVE_SESSION` | User tactile button wake into interactive UI session. |
| `H1OS_WAKE_STATE_RTC_FLOW_B` | Unattended periodic RTC countdown Flow B refresh & sync. |

---

{#h1os_splash_type_t}

### h1os_splash_type_t

```cpp
enum h1os_splash_type_t
```

Defined in h1os/h1os.h:102

Graphical splash screen trigger types.

| Value | Description |
|-------|-------------|
| `H1OS_SPLASH_BOOT` | Initial cold boot / power-on splash screen. |
| `H1OS_SPLASH_SLEEP` | Transition to unattended deep sleep splash screen. |
| `H1OS_SPLASH_SHUTDOWN` | Orderly physical power-down splash screen. |
| `H1OS_SPLASH_MAX` | Maximum splash enum value. |

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

{#h1os_chime_type_t}

### h1os_chime_type_t

```cpp
enum h1os_chime_type_t
```

Defined in h1os/hal_types.h:92

Acoustic chime sound pattern types.

| Value | Description |
|-------|-------------|
| `H1OS_CHIME_BOOT` | Ascending multi-tone power-on chime. |
| `H1OS_CHIME_SLEEP` | Descending sleep preparation chime. |
| `H1OS_CHIME_SHUTDOWN` | Dual-tone shutdown confirmation chime. |
| `H1OS_CHIME_ALARM` | Repetitive alert chime pattern. |
| `H1OS_CHIME_MAX` | Maximum chime enum value. |

---

{#sys_clk_mode_t}

### sys_clk_mode_t

```cpp
enum sys_clk_mode_t
```

Defined in h1os/hal_types.h:103

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

Acoustic data buffer type for consolidated sub_audio_play dispatch.

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

Defined in h1os/sub_power.h:28

Deep sleep cycle execution modes.

| Value | Description |
|-------|-------------|
| `SUB_POWER_SLEEP_FULL_CYCLE` | Normal Flow B sleep: arms PCF85063A countdown & resets slice_counter. |
| `SUB_POWER_SLEEP_FLOW_A_BURST` | Flow A sample sleep: preserves running PCF85063A countdown & slice_counter. |

---

{#h1os_battery_state_t}

### h1os_battery_state_t

```cpp
enum h1os_battery_state_t
```

Defined in h1os/sub_power.h:36

Battery operational state machine.

| Value | Description |
|-------|-------------|
| `H1OS_BATTERY_DISCHARGING` | Normal autonomous battery discharge. |
| `H1OS_BATTERY_CHARGING` | Voltage rising over consecutive reads. |
| `H1OS_BATTERY_CHARGED` | Saturated voltage (>=4180 mV) or USB host. |

---

{#h1os_wake_btn_t}

### h1os_wake_btn_t

```cpp
enum h1os_wake_btn_t
```

Defined in h1os/orch_state.h:28

Waking button identifier reported by ULP coprocessor (ulp_last_wake_btn).

| Value | Description |
|-------|-------------|
| `H1OS_WAKE_BTN_NONE` | Wake was not triggered by a physical button. |
| `H1OS_WAKE_BTN_BOOT` | Woken by BOOT0 button (GPIO 0). |
| `H1OS_WAKE_BTN_POWER` | Woken by POWER button (GPIO 18). |

---

{#ulp_wake_cause_t}

### ulp_wake_cause_t

```cpp
enum ulp_wake_cause_t
```

Defined in h1os/orch_state.h:37

ULP coprocessor wake causes (ulp_last_wake_cause).

| Value | Description |
|-------|-------------|
| `ULP_WAKE_CAUSE_NONE` | Uninitialized / no wake registered. |
| `ULP_WAKE_CAUSE_BOOT_BTN` | BOOT0 button event (short tap: session wake, long hold: DFU jump). |
| `ULP_WAKE_CAUSE_PWR_BTN` | POWER button event (short tap: session wake, long hold: shutdown). |
| `ULP_WAKE_CAUSE_LONG_OVERFLOW` | Flow B presentation refresh (slice_counter reached overflow_limit). |
| `ULP_WAKE_CAUSE_SENSOR_TICK` | Flow A sensor burst wake stub (slice_counter < overflow_limit). |
| `ULP_WAKE_CAUSE_RTC_INT_STUCK` | PCF85063A INT line stuck LOW hardware bus fault. |
| `ULP_WAKE_CAUSE_CRITICAL_BATTERY` | Battery dropped below 3250 mV brownout emergency floor. |

---

{#orch_ulp_dispatch_t}

### orch_ulp_dispatch_t

```cpp
enum orch_ulp_dispatch_t
```

Defined in h1os/orch_state.h:50

ULP coprocessor dispatch wakeup reasons.

| Value | Description |
|-------|-------------|
| `ULP_DISPATCH_NONE` | No dispatch action required. |
| `ULP_DISPATCH_SENSOR_SAMPLE` | Headless Flow A sensor sample burst dispatch. |
| `ULP_DISPATCH_MAIN_WAKE` | Interactive Flow B UI presentation wake dispatch. |
| `ULP_DISPATCH_CRITICAL_SHUTDOWN` | Low-battery brownout threshold cut dispatch. |
| `ULP_DISPATCH_BOOTLOADER_JUMP` | BOOT0 held down during sleep: jump to download mode. |
| `ULP_DISPATCH_POWER_OFF` | BAT_KEY long-press held down during sleep: power off. |

---

{#orch_sensor_err_t}

### orch_sensor_err_t

```cpp
enum orch_sensor_err_t
```

Defined in h1os/orch_state.h:62

SHTC3 sensor acquisition error codes reported by wake stub.

| Value | Description |
|-------|-------------|
| `ORCH_SENSOR_ERR_NONE` | Normal operation: reading acknowledged and verified. |
| `ORCH_SENSOR_ERR_NACK_WAKE` | SHTC3 wake command (0x3517) NACKed. |
| `ORCH_SENSOR_ERR_NACK_MEASURE` | SHTC3 measurement command (0x7866) NACKed. |
| `ORCH_SENSOR_ERR_NACK_ADDR_RD` | SHTC3 read address (0x71) NACKed. |
| `ORCH_SENSOR_ERR_CRC_FAIL` | CRC-8 checksum verification failed on received bytes. |
| `ORCH_SENSOR_ERR_BUS_STUCK` | SDA or SCL line held low prior to starting transfer. |
| `ORCH_SENSOR_ERR_NACK_SLEEP` | SHTC3 sleep command (0xB098) NACKed. |
| `ORCH_SENSOR_ERR_SCL_STUCK` | SCL clock line held low beyond clock-stretch timeout. |
## Typedefs

---

{#h1os_boot_cb_t}

### h1os_boot_cb_t

```cpp
using h1os_boot_cb_t = void(*)
```

Defined in h1os/h1os.h:114

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

Defined in h1os/h1os.h:122

Interactive wake callback signature (Timer / RTC Alarm / Button Tap).

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `ctx` |  | Pointer to populated wake context struct. |
| `user_data` |  | User context pointer configured in [h1os_lifecycle_t](#h1os_lifecycle_t). |

---

{#h1os_sync_cb_t}

### h1os_sync_cb_t

```cpp
using h1os_sync_cb_t = void(*)
```

Defined in h1os/h1os.h:133

Parallel data synchronization callback signature (MANDATE-04).

Invoked on Core 0 after Core 1 LVGL task startup so network/bus I/O overlaps in parallel with physical SSD1681 display refresh.

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

Defined in h1os/h1os.h:141

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

Defined in h1os/h1os.h:148

Callback executed immediately prior to battery power cut.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `user_data` |  | User context pointer configured in [h1os_lifecycle_t](#h1os_lifecycle_t). |

---

{#h1os_error_cb_t}

### h1os_error_cb_t

```cpp
using h1os_error_cb_t = void(*)
```

Defined in h1os/h1os.h:157

Fatal startup or lifecycle error callback signature (MANDATE-06).

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `err` |  | Error code that triggered the fatal condition. |
| `context` |  | Null-terminated diagnostic string identifying the failing stage. |
| `user_data` |  | User context pointer configured in [h1os_lifecycle_t](#h1os_lifecycle_t). |

---

{#h1os_splash_cb_t}

### h1os_splash_cb_t

```cpp
using h1os_splash_cb_t = void(*)
```

Defined in h1os/h1os.h:165

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

Defined in h1os/h1os.h:173

Acoustic presentation chime playback callback signature.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `type` |  | Type of chime pattern requested. |
| `user_data` |  | User context pointer configured in [h1os_lifecycle_t](#h1os_lifecycle_t). |

---

{#hal_io_button_cb_t}

### hal_io_button_cb_t

```cpp
using hal_io_button_cb_t = void(*)
```

Defined in h1os/hal_io.h:24

Callback signature for tactile button state-change interrupts.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `btn_mask` |  | Bitmask of currently depressed buttons (HAL_BTN_BOOT | HAL_BTN_POWER). |
| `arg` |  | Optional user context pointer registered with [hal_io_register_button_cb()](#hal_io_register_button_cb). |

---

{#h1os_ui_fn_t}

### h1os_ui_fn_t

```cpp
using h1os_ui_fn_t = void(*)
```

Defined in h1os/h1os_lvgl.h:27

Asynchronous UI mutation callback signature executed on Core 1 inside the LVGL context.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `arg` |  | User argument pointer passed to [h1os_ui_post()](#h1os_ui_post). |

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

Defined in h1os/h1os.h:269

Get the H1OS semantic version string.

#### Returns
Null-terminated semantic version string (e.g. "2.4.9-dev").

---

{#h1os_start}

### h1os_start

```cpp
esp_err_t h1os_start(const h1os_lifecycle_t * config)
```

Defined in h1os/h1os.h:287

Initialize H1OS and dispatch application lifecycle.

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

{#h1os_set_flow_periods}

### h1os_set_flow_periods

```cpp
esp_err_t h1os_set_flow_periods(uint32_t flow_a_sec, uint32_t flow_b_sec)
```

Defined in h1os/h1os.h:306

Dynamically configure Flow A and Flow B sleep intervals at runtime.

Enforces all silicon constraints, ordering invariants, and remainder slice floors. Updates active RTC Slow Memory state and immediately arms the hardware RTC countdown timer with the new Flow A period.

#### Returns

* ESP_OK: Flow periods validated, committed to RTC Slow Memory, and hardware timer armed.
* ESP_ERR_INVALID_ARG: Any boundary, prescaler, ordering, or remainder invariant violated.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `flow_a_sec` | `uint32_t` | Headless sensor acquisition interval (60s .. 14400s / 4h). Must be an exact multiple of 60 seconds if > 255s. |
| `flow_b_sec` | `uint32_t` | Display refresh and network wake interval (300s .. 86400s / 24h). Must be strictly greater than flow_a_sec. Any remainder (flow_b_sec % flow_a_sec) must be >= 60 seconds. |

---

{#h1os_sync_hold}

### h1os_sync_hold

```cpp
void h1os_sync_hold(void)
```

Defined in h1os/h1os.h:315

Hold the deep-sleep barrier open for an asynchronous synchronization task.

When called inside on_sync(), prevents unattended RTC Flow B wakes from entering deep sleep when on_sync() returns, deferring sleep until [h1os_sync_notify_complete()](#h1os_sync_notify_complete) is called or session.sync_timeout_ms expires.

---

{#h1os_sync_notify_complete}

### h1os_sync_notify_complete

```cpp
void h1os_sync_notify_complete(void)
```

Defined in h1os/h1os.h:324

Signal that Core 0 data synchronization is complete (`BARRIER_SYNC_DONE`).

Releases the pre-flush inbound sync gate (if `session.sync_wait_ms > 0`) so Core 1 flushes any queued UI updates in a single physical refresh, and satisfies the sync half of the deep-sleep barrier.

---

{#h1os_display_notify_quiescent}

### h1os_display_notify_quiescent

```cpp
void h1os_display_notify_quiescent(void)
```

Defined in h1os/h1os.h:329

Signal that the Core 1 LVGL / SSD1681 display pipeline is quiescent (`BARRIER_DISPLAY_DONE`).

---

{#h1os_set_volume}

### h1os_set_volume

```cpp
esp_err_t h1os_set_volume(uint8_t volume_pct)
```

Defined in h1os/h1os.h:343

Set audio subsystem output volume percentage.

Controls ES8311 DAC gain and NS4168 power state. 0% volume automatically mutes the output and puts the amplifier into low-power standby.

#### Returns

* ESP_OK: Volume level configured successfully.
* ESP_ERR_INVALID_STATE: Audio subsystem not initialized.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `volume_pct` | `uint8_t` | Desired volume percentage (0 = Mute, 100 = 0 dB Maximum). |

---

{#h1os_get_telemetry}

### h1os_get_telemetry

```cpp
esp_err_t h1os_get_telemetry(h1os_telemetry_t * out_telemetry)
```

Defined in h1os/h1os.h:357

Retrieve current Tri-Node environmental telemetry.

Copies the latest validated psychrometric invariants, sensor readings, and battery metrics into the caller-provided telemetry structure.

#### Returns

* ESP_OK: Telemetry snapshot copied successfully.
* ESP_ERR_INVALID_ARG: Null pointer passed.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_telemetry` | [`h1os_telemetry_t`](#h1os_telemetry_t) * | Pointer to destination telemetry structure. Must not be NULL. |

---

{#h1os_get_telemetry_history}

### h1os_get_telemetry_history

```cpp
esp_err_t h1os_get_telemetry_history(orch_tri_node_sample_t * out_samples, size_t max_samples, size_t * out_count)
```

Defined in h1os/h1os.h:373

Retrieve historical Tri-Node telemetry samples from the RTC Slow SRAM ring buffer in chronological order.

Designed for batch wireless telemetry publishing (Wi-Fi MQTT / BLE GATT) and local SD card logging without exposing Layer 3 internal structures to the application layer.

#### Returns

* ESP_OK: Historical samples copied in oldest-to-newest chronological order.
* ESP_ERR_INVALID_ARG: Null pointer or zero capacity passed.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_samples` | [`orch_tri_node_sample_t`](#orch_tri_node_sample_t) * | Destination array of [orch_tri_node_sample_t](#orch_tri_node_sample_t) elements. Must not be NULL. |
| `max_samples` | `size_t` | Maximum capacity of out_samples array (up to ORCH_RING_CAPACITY = 32). |
| `out_count` | `size_t *` | Number of valid chronological samples copied into out_samples. Must not be NULL. |

---

{#h1os_set_rh_alert_bounds}

### h1os_set_rh_alert_bounds

```cpp
esp_err_t h1os_set_rh_alert_bounds(uint16_t rh_low_centi_pct, uint16_t rh_high_centi_pct)
```

Defined in h1os/h1os.h:388

Configure relative humidity target alert thresholds in centi-percent (1% = 100, e.g.

6200..7200).

Persisted in RTC Slow SRAM so humidor out-of-bounds excursions are evaluated deterministically across deep sleep cycles (set both to 0 to disable alert evaluation).

#### Returns

* ESP_OK: Alert bounds configured successfully.
* ESP_ERR_INVALID_ARG: Invalid range (low > high or > 10000).

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `rh_low_centi_pct` | `uint16_t` | Lower relative humidity alert threshold in centi-% (0..10000). |
| `rh_high_centi_pct` | `uint16_t` | Upper relative humidity alert threshold in centi-% (0..10000). |

---

{#h1os_sleep}

### h1os_sleep

```cpp
esp_err_t h1os_sleep(uint32_t sleep_sec)
```

Defined in h1os/h1os.h:402

Put the platform into ultra-low-power deep sleep.

Arms the PCF85063A countdown timer, isolates GPIO sleep pads, holds power latch, and enters ESP32-S3 deep sleep.

#### Returns

* ESP_OK: Sleep transition armed.
* ESP_ERR_INVALID_ARG: sleep_sec out of supported hardware range.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `sleep_sec` | `uint32_t` | Duration of sleep in seconds before hardware wake. |

---

{#h1os_reset_session_timer}

### h1os_reset_session_timer

```cpp
void h1os_reset_session_timer(void)
```

Defined in h1os/h1os.h:410

Reset the interactive session inactivity timer.

Extends the interactive user session by inactivity_timeout_sec, preventing premature deep sleep while user interaction or animation is underway.

---

{#h1os_is_session_active}

### h1os_is_session_active

```cpp
bool h1os_is_session_active(void)
```

Defined in h1os/h1os.h:417

Check whether an interactive inactivity countdown session is active.

#### Returns
True if running in an interactive user session, false during unattended wakes.

---

{#h1os_shutdown}

### h1os_shutdown

```cpp
void h1os_shutdown(void)
```

Defined in h1os/h1os.h:425

Orderly system shutdown and physical battery power cut.

Invokes lifecycle on_shutdown hook, safely isolates peripherals, deactivates displays, and releases GPIO 17 BAT_CTRL power latch.

---

{#h1os_shutdown_for_storage}

### h1os_shutdown_for_storage

```cpp
void h1os_shutdown_for_storage(void)
```

Defined in h1os/h1os.h:433

Shutdown for long-term storage.

Performs pure white full OTP refresh on electrophoretic display before cutting power latch, protecting e-Paper microcapsules against dye migration and burn-in.

---

{#h1os_display_force_clear}

### h1os_display_force_clear

```cpp
esp_err_t h1os_display_force_clear(void)
```

Defined in h1os/h1os.h:445

Force a driver-level electrophoretic display clear and full waveform scrub.

> [!NOTE]
> This is a hardware driver-level operation on the SSD1681 controller (not an LVGL widget call). It writes pure white (0xFF) to both black/white and red RAM planes, triggers a full OTP waveform refresh cycle (~2.5s), waits for hardware BUSY de-assertion, and resets the partial refresh counter. Use to eliminate electrophoretic microcapsule ghosting or initialize the panel.

#### Returns
ESP_OK on success, or an error code from the display driver.

---

{#h1os_audio_play_raw}

### h1os_audio_play_raw

```cpp
esp_err_t h1os_audio_play_raw(const int16_t * ptr, size_t len, size_t * bytes_written)
```

Defined in h1os/h1os.h:455

Play raw 16-bit signed Mono PCM audio asynchronously from memory (C header arrays or RAM buffer).

#### Returns
ESP_OK on success, ESP_ERR_INVALID_ARG on NULL ptr, or I2S/DMA driver error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `ptr` | `const int16_t *` | Pointer to 16-bit signed PCM buffer in Flash or RAM. Must not be NULL. |
| `len` | `size_t` | Length of sample buffer in bytes. |
| `bytes_written` | `size_t *` | Pointer to receive count of bytes queued. Can be NULL. |

---

{#h1os_audio_play_tone}

### h1os_audio_play_tone

```cpp
esp_err_t h1os_audio_play_tone(uint32_t freq_hz, uint32_t duration_ms)
```

Defined in h1os/h1os.h:464

Synthesize and play a pure sine tone asynchronously at specified frequency and duration.

#### Returns
ESP_OK on success, or driver error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `freq_hz` | `uint32_t` | Tone frequency in Hertz (100..10000 Hz). |
| `duration_ms` | `uint32_t` | Tone duration in milliseconds (10..5000 ms). |

---

{#h1os_audio_play_chime}

### h1os_audio_play_chime

```cpp
esp_err_t h1os_audio_play_chime(h1os_chime_type_t chime_type)
```

Defined in h1os/h1os.h:472

Play a predefined acoustic presentation chime asynchronously.

#### Returns
ESP_OK on success, or driver error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `chime_type` | [`h1os_chime_type_t`](#h1os_chime_type_t) | Predefined chime pattern (H1OS_CHIME_BOOT, H1OS_CHIME_SLEEP, etc.). |

---

{#h1os_sdcard_is_mounted}

### h1os_sdcard_is_mounted

```cpp
bool h1os_sdcard_is_mounted(void)
```

Defined in h1os/h1os.h:479

Check if a MicroSD card is actively mounted in the FATFS filesystem.

#### Returns
true if mounted and ready for file I/O, false otherwise.

---

{#h1os_sdcard_get_capacity_mb}

### h1os_sdcard_get_capacity_mb

```cpp
esp_err_t h1os_sdcard_get_capacity_mb(uint32_t * out_capacity_mb)
```

Defined in h1os/h1os.h:487

Retrieve total capacity of the mounted MicroSD card in megabytes.

#### Returns
ESP_OK on success, ESP_ERR_INVALID_STATE if card is not mounted, or ESP_ERR_INVALID_ARG.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_capacity_mb` | `uint32_t *` | Pointer to receive card capacity in megabytes (MB). |

---

{#h1os_sdcard_mount_async}

### h1os_sdcard_mount_async

```cpp
esp_err_t h1os_sdcard_mount_async(void)
```

Defined in h1os/h1os.h:494

Asynchronously mount the MicroSD card in a background FreeRTOS task.

#### Returns
ESP_OK if already mounted or mount task dispatched successfully.

---

{#h1os_sdcard_unmount}

### h1os_sdcard_unmount

```cpp
esp_err_t h1os_sdcard_unmount(void)
```

Defined in h1os/h1os.h:501

Unmount the MicroSD card and release SDMMC host peripheral resources.

#### Returns
ESP_OK on success.

---

{#h1os_led_start_breathing}

### h1os_led_start_breathing

```cpp
void h1os_led_start_breathing(uint32_t period_ms)
```

Defined in h1os/h1os.h:508

Start non-blocking hardware LEDC fade breathing effect on the status LED (GPIO 3).

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `period_ms` | `uint32_t` | Full breathing cycle period in milliseconds (e.g. 2000 ms). |

---

{#h1os_led_stop_breathing}

### h1os_led_stop_breathing

```cpp
void h1os_led_stop_breathing(void)
```

Defined in h1os/h1os.h:513

Stop the status LED breathing effect and turn the LED off.

---

{#h1os_led_set}

### h1os_led_set

```cpp
void h1os_led_set(bool on)
```

Defined in h1os/h1os.h:520

Set the status LED static state (true = ON, false = OFF).

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `on` | `bool` | True to illuminate LED, false to turn off. |

---

{#hal_io_early_init}

### hal_io_early_init

```cpp
esp_err_t hal_io_early_init(void)
```

Defined in h1os/hal_io.h:37

Early boot initialization of non-latched application pins and GPIO ISR service.

Releases sleep pad holds on dynamic peripheral/wake pins, configures amplifier mute (GPIO 46), status LED (GPIO 3), buttons (GPIO 0/18 with edge interrupts and hardware glitch filters), and RTC INT (GPIO 5). Note: Master power rails (GPIO 17 BAT_CTRL, GPIO 6 EPD_3V3_EN, GPIO 42 PA_EN) are strictly latched in the 2nd-stage bootloader (h1os_boot_hook.c).

#### Returns
ESP_OK on success, or driver error code.

---

{#hal_io_register_button_cb}

### hal_io_register_button_cb

```cpp
esp_err_t hal_io_register_button_cb(hal_io_button_cb_t cb, void * arg)
```

Defined in h1os/hal_io.h:47

Register an asynchronous callback invoked when tactile buttons change state after 15 ms esp_timer debounce.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `cb` | [`hal_io_button_cb_t`](#hal_io_button_cb_t) | Callback function pointer (or NULL to unregister). |
| `arg` | `void *` | Optional context pointer passed to cb. |

---

{#hal_io_set_led}

### hal_io_set_led

```cpp
esp_err_t hal_io_set_led(bool on)
```

Defined in h1os/hal_io.h:56

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

Defined in h1os/hal_io.h:65

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

Defined in h1os/hal_io.h:74

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

Defined in h1os/hal_io.h:86

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

Defined in h1os/hal_io.h:97

Starts an asynchronous periodic esp_timer to "breathe" (fade in and fade out) the status LED.

Uses hardware LEDC PWM fading paced by a lightweight esp_timer callback (zero dedicated FreeRTOS task stack).

#### Returns
ESP_OK on success, or error code if timer creation fails.

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

Defined in h1os/hal_io.h:104

Stops the asynchronous LED breathing timer and turns the LED off immediately.

#### Returns
ESP_OK on success.

---

{#hal_led_is_breathing}

### hal_led_is_breathing

```cpp
bool hal_led_is_breathing(void)
```

Defined in h1os/hal_io.h:111

Queries whether the asynchronous LED breathing timer is actively running.

#### Returns
True if breathing timer is active, false otherwise.

---

{#hal_led_pwm_deinit}

### hal_led_pwm_deinit

```cpp
esp_err_t hal_led_pwm_deinit(void)
```

Defined in h1os/hal_io.h:118

Deinitializes LEDC hardware PWM and restores GPIO 3 to static GPIO mode.

#### Returns
ESP_OK on success.

---

{#hal_io_release_power_latch}

### hal_io_release_power_latch

```cpp
esp_err_t hal_io_release_power_latch(void)
```

Defined in h1os/hal_io.h:127

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

Defined in h1os/hal_io.h:134

Samples instantaneous or debounced state of hardware tactile buttons.

#### Returns
Bitmask of currently depressed buttons (HAL_BTN_BOOT | HAL_BTN_POWER).

---

{#hal_io_button_is_pressed}

### hal_io_button_is_pressed

`static` `inline`

```cpp
static inline bool hal_io_button_is_pressed(gpio_num_t pin)
```

Defined in h1os/hal_io.h:143

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

Defined in h1os/hal_io.h:158

Configures and locks dynamic peripheral lines prior to deep sleep.

* Latches GPIO 11 (EPD_CS), GPIO 9 (EPD_RST), and GPIO 10 (EPD_DC) HIGH via gpio_hold_en().
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

Defined in h1os/hal_io.h:165

Releases sleep pad holds on dynamic peripheral/wake pins upon waking from deep sleep.

#### Returns
ESP_OK on success.

---

{#hal_check_usb_ll}

### hal_check_usb_ll

```cpp
bool hal_check_usb_ll(void)
```

Defined in h1os/hal_io.h:172

Check if USB Serial/JTAG is connected to an active host via SOF packets.

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

Installs ESP-IDF I2C driver on GPIO 47 / GPIO 48 and creates recursive mutex.

#### Returns

* ESP_OK: Bus initialized and mutex created successfully.
* ESP_ERR_INVALID_STATE: Driver already installed.
* ESP_FAIL: Hardware initialization failed.

---

{#hal_i2c_deinit}

### hal_i2c_deinit

```cpp
esp_err_t hal_i2c_deinit(void)
```

Defined in h1os/hal_i2c.h:36

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

{#hal_i2c_read}

### hal_i2c_read

```cpp
esp_err_t hal_i2c_read(uint8_t dev_addr, uint8_t * read_data, size_t read_len, uint32_t timeout_ms)
```

Defined in h1os/hal_i2c.h:66

Execute an atomic register read transaction over I2C.

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

{#hal_i2c_write_read}

### hal_i2c_write_read

```cpp
esp_err_t hal_i2c_write_read(uint8_t dev_addr, const uint8_t * write_data, size_t write_len, uint8_t * read_data, size_t read_len, uint32_t timeout_ms)
```

Defined in h1os/hal_i2c.h:83

Execute an atomic write-then-read combined transaction (Repeated START).

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

{#hal_i2c_probe}

### hal_i2c_probe

```cpp
esp_err_t hal_i2c_probe(uint8_t dev_addr)
```

Defined in h1os/hal_i2c.h:96

Probe if an I2C device responds with ACK at given 7-bit address.

#### Returns

* ESP_OK: Device responded with ACK.
* ESP_ERR_NOT_FOUND: Device NACKed address byte.
* ESP_ERR_TIMEOUT: Transaction timed out.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `dev_addr` | `uint8_t` | 7-bit device address to probe. |

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

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `data` | `const uint8_t *` | Pointer to buffer containing data buffer. Must not be NULL. |
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

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `frame_buffer` | `const uint8_t *` | Pointer to 5000-byte buffer. Must not be NULL. |

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

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `cmd` | `uint8_t` | Command to write before reading. |
| `out_data` | `uint8_t *` | Buffer to receive read bytes. Must not be NULL. |
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

---

{#sub_nvs_set_str}

### sub_nvs_set_str

```cpp
esp_err_t sub_nvs_set_str(const char * key, const char * value)
```

Defined in h1os/sub_nvs.h:38

Store a null-terminated string value in NVS.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `key` | `const char *` | Unique key identifier string. |
| `value` | `const char *` | String data buffer to persist. |

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

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `key` | `const char *` | Unique key identifier string. |
| `out_val` | `char *` | Destination character buffer. |
| `max_len` | `size_t` | Capacity of destination buffer. |

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

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `key` | `const char *` | Unique key identifier string. |
| `value` | `uint32_t` | Integer value to persist. |

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

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `key` | `const char *` | Unique key identifier string. |
| `out_val` | `uint32_t *` | Destination pointer for integer. |

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

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `key` | `const char *` | Unique key identifier string. |
| `data` | `const void *` | Pointer to binary data buffer. |
| `len` | `size_t` | Length of data in bytes. |

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

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `key` | `const char *` | Unique key identifier string. |
| `out_data` | `void *` | Destination buffer for binary data. |
| `inout_len` | `size_t *` | On entry: capacity of buffer; on exit: actual read bytes. |

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

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `key` | `const char *` | Key identifier string to erase. |

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

---

{#sub_rtc_init}

### sub_rtc_init

```cpp
esp_err_t sub_rtc_init(void)
```

Defined in h1os/sub_rtc.h:29

Initialize PCF85063A real-time clock over shared I2C bus.

Disables CLKOUT push-pull square wave to eliminate continuous trace leakage, verifies oscillator integrity, and clears residual timer/alarm flags.

#### Returns
ESP_OK on success, or I2C communication error.

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

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_time` | `struct tm *` | Pointer to struct tm populated with current RTC timestamp. Must not be NULL. |

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

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `time` | `const struct tm *` | Pointer to struct tm containing target timestamp. Must not be NULL. |

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

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_sec` | `uint32_t *` | Destination pointer for remaining seconds. Must not be NULL. |

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

{#sub_rtc_is_oscillator_valid}

### sub_rtc_is_oscillator_valid

```cpp
bool sub_rtc_is_oscillator_valid(void)
```

Defined in h1os/sub_rtc.h:98

Check whether PCF85063A oscillator integrity is valid.

Checks Bit 7 (OS flag) in the Seconds register. If OS is set (1), oscillator stopped or power was lost and the clock is uncalibrated.

#### Returns
True if oscillator has run continuously, false if stopped/uncalibrated.

---

{#h1os_lvgl_init}

### h1os_lvgl_init

```cpp
esp_err_t h1os_lvgl_init(bool is_wake_cycle)
```

Defined in h1os/h1os_lvgl.h:49

Initialize LVGL v9 graphics subsystem, 1-bit display buffer, and keypad input driver.

Configures the bilevel draw buffer, registers the display flush callback, and sets up keypad input navigation.

#### Returns

* ESP_OK: LVGL core initialized successfully.
* ESP_ERR_NO_MEM: Insufficient memory for draw buffer allocation.

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

Defined in h1os/h1os_lvgl.h:56

Explicitly override whether the first flush executes a full or partial refresh.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `full_refresh` | `bool` | True for full OTP flashing refresh, False for differential partial. |

---

{#h1os_lvgl_request_full_refresh}

### h1os_lvgl_request_full_refresh

`static` `inline`

```cpp
static inline void h1os_lvgl_request_full_refresh(void)
```

Defined in h1os/h1os_lvgl.h:64

Request a full OTP flashing waveform refresh on the next LVGL display flush.

Convenience inline wrapper around h1os_lvgl_set_first_flush_mode(true) for Layer 4 theme polarity switches (Light/Dark) and manual anti-ghosting scrubs.

---

{#h1os_lvgl_start}

### h1os_lvgl_start

```cpp
esp_err_t h1os_lvgl_start(int32_t priority, int32_t core_id)
```

Defined in h1os/h1os_lvgl.h:81

Start the LVGL background FreeRTOS task.

Spawns the dedicated presentation task pinned to Core 1 for decoupled UI rendering.

#### Returns

* ESP_OK: Task created and running.
* ESP_FAIL: Task creation failed.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `priority` | `int32_t` | FreeRTOS task priority (e.g. 5). |
| `core_id` | `int32_t` | CPU core affinity (0 or 1). |

---

{#h1os_lvgl_stop}

### h1os_lvgl_stop

```cpp
esp_err_t h1os_lvgl_stop(void)
```

Defined in h1os/h1os_lvgl.h:91

Stop the LVGL background task.

Signals the event loop to terminate cleanly via event-driven semaphore synchronization and waits for task exit.

#### Returns

* ESP_OK: Task stopped successfully.

---

{#h1os_lvgl_lock}

### h1os_lvgl_lock

```cpp
bool h1os_lvgl_lock(uint32_t timeout_ms)
```

Defined in h1os/h1os_lvgl.h:103

Acquire LVGL reentrant mutex lock.

Must be acquired before creating, modifying, or deleting any LVGL widgets or objects from tasks other than the LVGL event loop.

#### Returns
True if mutex was successfully acquired within timeout, false otherwise.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ms` | `uint32_t` | Mutex acquisition timeout in milliseconds. |

---

{#h1os_lvgl_unlock}

### h1os_lvgl_unlock

```cpp
void h1os_lvgl_unlock(void)
```

Defined in h1os/h1os_lvgl.h:110

Release LVGL reentrant mutex lock.

Releases the mutex acquired via [h1os_lvgl_lock()](#h1os_lvgl_lock).

---

{#h1os_ui_post}

### h1os_ui_post

```cpp
esp_err_t h1os_ui_post(h1os_ui_fn_t fn, void * arg, uint32_t timeout_ms)
```

Defined in h1os/h1os_lvgl.h:129

Enqueue an asynchronous UI mutation callback to execute on Core 1 (`h1os_lvgl_port_task`).

Thread-safe, lock-free producer API backed by a 16-slot static FreeRTOS queue. Immediately wakes the Core 1 LVGL task via `xTaskNotifyGive()` to drain the queue inside its `[h1os_lvgl_lock()](#h1os_lvgl_lock)` critical section before `lv_timer_handler()`.

#### Returns

* ESP_OK: Mutation successfully queued and Core 1 notified.
* ESP_ERR_INVALID_ARG: fn is NULL.
* ESP_ERR_INVALID_STATE: LVGL subsystem not initialized.
* ESP_ERR_TIMEOUT: Queue full after timeout_ms.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `fn` | [`h1os_ui_fn_t`](#h1os_ui_fn_t) | Callback function to execute on Core 1. Must not be NULL. |
| `arg` | `void *` | Opaque argument passed to fn. |
| `timeout_ms` | `uint32_t` | Maximum time to wait if the 16-slot queue is full (0 for non-blocking). |

---

{#h1os_lvgl_set_sync_gate}

### h1os_lvgl_set_sync_gate

```cpp
void h1os_lvgl_set_sync_gate(uint32_t wait_ms)
```

Defined in h1os/h1os_lvgl.h:141

Arm a pre-flush inbound synchronization gate on Core 1 for single-refresh coalescing.

When `wait_ms > 0`, the Core 1 LVGL task defers `lv_timer_handler()` (and thus physical SSD1681 display flushing) for up to `wait_ms` or until `[h1os_lvgl_release_sync_gate()](#h1os_lvgl_release_sync_gate)` is called by `[h1os_sync_notify_complete()](#h1os_sync_notify_complete)`, ensuring initial `on_wake()` widgets and inbound `on_sync()` mutations coalesce into a single physical e-Paper refresh.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `wait_ms` | `uint32_t` | Maximum gate hold duration in milliseconds (0 disables the gate). |

---

{#h1os_lvgl_release_sync_gate}

### h1os_lvgl_release_sync_gate

```cpp
void h1os_lvgl_release_sync_gate(void)
```

Defined in h1os/h1os_lvgl.h:146

Release the pre-flush inbound synchronization gate and wake Core 1 immediately.

---

{#h1os_lvgl_has_pending_tasks}

### h1os_lvgl_has_pending_tasks

```cpp
bool h1os_lvgl_has_pending_tasks(void)
```

Defined in h1os/h1os_lvgl.h:153

Check if the LVGL display pipeline has pending render/flush tasks.

#### Returns
True if display driver is currently flushing, UI queue has items, or widgets are invalidated.

---

{#h1os_lvgl_wait_idle}

### h1os_lvgl_wait_idle

```cpp
esp_err_t h1os_lvgl_wait_idle(uint32_t timeout_ms)
```

Defined in h1os/h1os_lvgl.h:165

Event-driven wait until the LVGL display pipeline completes all pending renders and flushes.

Blocks on a static binary semaphore signaled immediately by the Core 1 LVGL task when idle, eliminating 20 ms polling loops during pre-sleep teardown.

#### Returns
ESP_OK when pipeline is idle, ESP_ERR_TIMEOUT on expiration.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ms` | `uint32_t` | Maximum wait time in milliseconds. |

---

{#h1os_lvgl_get_indev}

### h1os_lvgl_get_indev

```cpp
lv_indev_t * h1os_lvgl_get_indev(void)
```

Defined in h1os/h1os_lvgl.h:172

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

#### Returns

* ESP_OK: Timezone configured and applied.
* ESP_ERR_INVALID_ARG: Null pointer provided.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `tz_str` | `const char *` | POSIX TZ format string (e.g. "EST5EDT,M3.2.0,M11.1.0"). |

---

{#h1os_time_register_sync_cb}

### h1os_time_register_sync_cb

```cpp
esp_err_t h1os_time_register_sync_cb(h1os_time_sync_cb_t cb, void * user_data)
```

Defined in h1os/h1os_time.h:70

Register external time synchronization provider callback.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `cb` | [`h1os_time_sync_cb_t`](#h1os_time_sync_cb_t) | Time acquisition callback function pointer. |
| `user_data` | `void *` | User context pointer passed to callback. |

---

{#h1os_time_sync_now}

### h1os_time_sync_now

```cpp
esp_err_t h1os_time_sync_now(uint32_t timeout_ms)
```

Defined in h1os/h1os_time.h:79

Execute immediate time synchronization via registered provider.

#### Returns
ESP_OK on success, or provider error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ms` | `uint32_t` | Synchronization timeout in milliseconds. |

---

{#h1os_time_sync_system_to_rtc}

### h1os_time_sync_system_to_rtc

```cpp
esp_err_t h1os_time_sync_system_to_rtc(void)
```

Defined in h1os/h1os_time.h:86

Synchronize internal POSIX system clock to external PCF85063A hardware RTC.

#### Returns
ESP_OK on success, or I2C bus communication error.

---

{#h1os_time_sync_rtc_to_system}

### h1os_time_sync_rtc_to_system

```cpp
esp_err_t h1os_time_sync_rtc_to_system(void)
```

Defined in h1os/h1os_time.h:93

Synchronize external PCF85063A hardware RTC to internal POSIX system clock.

#### Returns
ESP_OK on success, or I2C bus communication error.

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

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `fmt` | [`h1os_time_format_t`](#h1os_time_format_t) | Requested time presentation format. |
| `dest` | `char *` | Pointer to destination character buffer. |
| `max_len` | `size_t` | Capacity of destination buffer in bytes. |

---

{#h1os_time_get_date_formatted}

### h1os_time_get_date_formatted

```cpp
esp_err_t h1os_time_get_date_formatted(h1os_date_format_t fmt, char * dest, size_t max_len)
```

Defined in h1os/h1os_time.h:115

Format current local calendar date into destination buffer.

#### Returns
ESP_OK on success, or ESP_ERR_INVALID_ARG if buffer too small.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `fmt` | [`h1os_date_format_t`](#h1os_date_format_t) | Requested date presentation format. |
| `dest` | `char *` | Pointer to destination character buffer. |
| `max_len` | `size_t` | Capacity of destination buffer in bytes. |

---

{#h1os_time_is_valid}

### h1os_time_is_valid

```cpp
bool h1os_time_is_valid(void)
```

Defined in h1os/h1os_time.h:126

Check whether the current hardware RTC timestamp is calibrated and valid.

Performs deterministic verification:

1. Verifies PCF85063A hardware oscillator integrity (Seconds register OS flag == 0).
1. Compares active RTC calendar timestamp against firmware compile-time epoch (**DATE** and **TIME**).

#### Returns
True if hardware RTC is calibrated and past firmware compile epoch, false otherwise.

---

{#hal_flash_init}

### hal_flash_init

```cpp
esp_err_t hal_flash_init(void)
```

Defined in h1os/hal_flash.h:27

Initialize raw flash partition driver for display framebuffer persistence.

Locates the dedicated 16KB "epd_frame" partition in SPI flash.

#### Returns

* ESP_OK: Partition located and validated.
* ESP_ERR_NOT_FOUND: "epd_frame" partition not present in partition table.

---

{#hal_flash_read_frame}

### hal_flash_read_frame

```cpp
esp_err_t hal_flash_read_frame(uint8_t * out_buffer, size_t len)
```

Defined in h1os/hal_flash.h:40

Read preserved 1-bit frame data from SPI flash partition.

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

{#hal_flash_write_frame}

### hal_flash_write_frame

```cpp
esp_err_t hal_flash_write_frame(const uint8_t * frame_data, size_t len)
```

Defined in h1os/hal_flash.h:55

Erase and write 1-bit frame data into SPI flash partition.

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

{#orch_flow_determine_wakeup}

### orch_flow_determine_wakeup

```cpp
orch_flow_type_t orch_flow_determine_wakeup(void)
```

Defined in h1os/orch_flow.h:37

Evaluate hardware reset cause and RTC state to determine execution flow.

#### Returns
Selected execution flow type.

---

{#orch_flow_is_thermal_lockout}

### orch_flow_is_thermal_lockout

```cpp
bool orch_flow_is_thermal_lockout(void)
```

Defined in h1os/orch_flow.h:44

Check whether thermal self-heating lockout is currently active.

#### Returns
True if radio/CPU self-heating is actively decaying.

---

{#orch_flow_query_telemetry}

### orch_flow_query_telemetry

```cpp
esp_err_t orch_flow_query_telemetry(float * out_temp_c, float * out_rh_pct, float * out_dew_c)
```

Defined in h1os/orch_flow.h:55

Query current filtered Tri-Node environmental telemetry.

#### Returns
ESP_OK on success, or ESP_ERR_INVALID_ARG if any pointer is NULL.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_temp_c` | `float *` | Pointer to store ambient temperature in Celsius. |
| `out_rh_pct` | `float *` | Pointer to store ambient relative humidity %. |
| `out_dew_c` | `float *` | Pointer to store calculated dew point in Celsius. |

---

{#orch_flow_transition_to_sleep}

### orch_flow_transition_to_sleep

```cpp
esp_err_t orch_flow_transition_to_sleep(uint32_t sleep_sec)
```

Defined in h1os/orch_flow.h:64

Prepare platform subsystems and enter target low-power sleep state.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `sleep_sec` | `uint32_t` | Target sleep duration in seconds. |

---

{#orch_math_calc_sat_vapor_pressure}

### orch_math_calc_sat_vapor_pressure

```cpp
float orch_math_calc_sat_vapor_pressure(float temp_c)
```

Defined in h1os/orch_math.h:25

Calculate saturation vapor pressure using August-Roche-Magnus approximation.

#### Returns
Saturation vapor pressure in hectopascals (hPa).

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `temp_c` | `float` | Temperature in degrees Celsius. |

---

{#orch_math_calc_vapor_pressure}

### orch_math_calc_vapor_pressure

```cpp
float orch_math_calc_vapor_pressure(float temp_c, float rh_pct)
```

Defined in h1os/orch_math.h:35

Calculate actual water vapor partial pressure from temperature and relative humidity.

#### Returns
Actual vapor pressure in hectopascals (hPa).

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `temp_c` | `float` | Temperature in degrees Celsius. |
| `rh_pct` | `float` | Relative humidity percentage (0..100%). |

---

{#orch_math_calc_dew_point}

### orch_math_calc_dew_point

```cpp
float orch_math_calc_dew_point(float temp_c, float rh_pct)
```

Defined in h1os/orch_math.h:45

Calculate dew point temperature from temperature and relative humidity.

#### Returns
Dew point in degrees Celsius.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `temp_c` | `float` | Temperature in degrees Celsius. |
| `rh_pct` | `float` | Relative humidity percentage (0..100%). |

---

{#orch_math_calc_psychrometrics}

### orch_math_calc_psychrometrics

```cpp
void orch_math_calc_psychrometrics(float temp_c, float rh_pct, float * out_vp_hpa, float * out_dew_c)
```

Defined in h1os/orch_math.h:55

Calculate vapor pressure and dew point directly from factory-calibrated SHTC3 readings.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `temp_c` | `float` | Settled SHTC3 temperature in Celsius. |
| `rh_pct` | `float` | Settled SHTC3 relative humidity %. |
| `out_vp_hpa` | `float *` | Pointer to store vapor pressure in hPa. |
| `out_dew_c` | `float *` | Pointer to store dew point in Celsius. |

---

{#orch_math_calc_absolute_humidity}

### orch_math_calc_absolute_humidity

```cpp
float orch_math_calc_absolute_humidity(float vapor_pressure_hpa, float amb_temp_c)
```

Defined in h1os/orch_math.h:65

Calculate absolute humidity in grams per cubic meter (g/m³).

#### Returns
Absolute humidity in g/m³.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `vapor_pressure_hpa` | `float` | Water vapor pressure in hPa. |
| `amb_temp_c` | `float` | Ambient temperature in Celsius. |

---

{#orch_math_update_ewma}

### orch_math_update_ewma

```cpp
float orch_math_update_ewma(float current_sample, float previous_ewma, float alpha)
```

Defined in h1os/orch_math.h:76

Update an Exponentially Weighted Moving Average (EWMA) filter.

#### Returns
Updated EWMA value.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `current_sample` | `float` | New sample value. |
| `previous_ewma` | `float` | Previous EWMA value. |
| `alpha` | `float` | Smoothing factor (0.0 to 1.0). |

---

{#orch_math_is_plateau_settled}

### orch_math_is_plateau_settled

```cpp
bool orch_math_is_plateau_settled(int16_t initial_temp_centi_c, int16_t current_temp_centi_c, int16_t gate_threshold_centi_c)
```

Defined in h1os/orch_math.h:87

Check if temperature trend has settled onto a stable thermal plateau.

#### Returns
True if |initial - current| <= gate_threshold.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `initial_temp_centi_c` | `int16_t` | Initial reference temperature in centi-degrees Celsius. |
| `current_temp_centi_c` | `int16_t` | Current sampled temperature in centi-degrees Celsius. |
| `gate_threshold_centi_c` | `int16_t` | Maximum allowable absolute delta in centi-degrees Celsius. |

---

{#sub_audio_init}

### sub_audio_init

```cpp
esp_err_t sub_audio_init(uint8_t volume_pct)
```

Defined in h1os/sub_audio.h:40

Initialize ES8311 audio codec and NS4168 amplifier hardware.

Configures I2S master bus (16-bit 16kHz mono), performs codec register initialization over shared I2C, and sets up the asynchronous FreeRTOS audio worker task.

#### Returns
ESP_OK on success, or driver error code.

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

Mutes amplifier (GPIO 46 LOW), maintains class-D power gate energized (GPIO 42 LOW per ERRATA E4), and enters software power-down on ES8311.

#### Returns
ESP_OK on success.

---

{#sub_audio_deinit}

### sub_audio_deinit

```cpp
esp_err_t sub_audio_deinit(void)
```

Defined in h1os/sub_audio.h:57

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

#### Returns
ESP_OK if audio worker is ready, ESP_ERR_TIMEOUT otherwise.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ms` | `uint32_t` | Maximum time to wait in milliseconds. |

---

{#sub_audio_is_ready}

### sub_audio_is_ready

```cpp
bool sub_audio_is_ready(void)
```

Defined in h1os/sub_audio.h:73

Check if audio subsystem is initialized and ready to accept commands.

#### Returns
True if audio worker is operational, false otherwise.

---

{#sub_audio_play}

### sub_audio_play

```cpp
esp_err_t sub_audio_play(sub_audio_type_t type, const void * data, size_t len)
```

Defined in h1os/sub_audio.h:84

Dispatch audio playback command to background worker task.

#### Returns
ESP_OK if command was queued to worker, or error code.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `type` | [`sub_audio_type_t`](#sub_audio_type_t) | Acoustic data buffer type (SUB_AUDIO_TONE, SUB_AUDIO_CHIME, SUB_AUDIO_PCM). |
| `data` | `const void *` | Pointer to data buffer data buffer or parameters struct. |
| `len` | `size_t` | Length of data data buffer in bytes. |

---

{#sub_audio_is_busy}

### sub_audio_is_busy

```cpp
bool sub_audio_is_busy(void)
```

Defined in h1os/sub_audio.h:91

Check if audio playback is actively streaming.

#### Returns
True if amplifier is active and audio samples are playing.

---

{#sub_audio_wait_idle}

### sub_audio_wait_idle

```cpp
esp_err_t sub_audio_wait_idle(uint32_t timeout_ms)
```

Defined in h1os/sub_audio.h:100

Block until all pending audio commands finish playback and amplifier enters standby.

#### Returns
ESP_OK when playback is idle, ESP_ERR_TIMEOUT on expiration.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ms` | `uint32_t` | Maximum wait time in milliseconds. |

---

{#sub_audio_set_volume}

### sub_audio_set_volume

```cpp
esp_err_t sub_audio_set_volume(uint8_t volume_pct)
```

Defined in h1os/sub_audio.h:109

Set master audio volume percentage (0..100%).

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `volume_pct` | `uint8_t` | Output volume (0 = Mute, 100 = 0 dB Max). |

---

{#sub_audio_get_volume}

### sub_audio_get_volume

```cpp
uint8_t sub_audio_get_volume(void)
```

Defined in h1os/sub_audio.h:116

Retrieve current audio volume percentage.

#### Returns
Current volume level (0..100%).

---

{#sub_audio_set_low_power_mode}

### sub_audio_set_low_power_mode

```cpp
esp_err_t sub_audio_set_low_power_mode(bool enable)
```

Defined in h1os/sub_audio.h:125

Enable or disable aggressive codec low-power mode.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `enable` | `bool` | True to enable analog power-down when idle. |

---

{#sub_audio_get_low_power_mode}

### sub_audio_get_low_power_mode

```cpp
bool sub_audio_get_low_power_mode(void)
```

Defined in h1os/sub_audio.h:132

Query whether codec low-power mode is enabled.

#### Returns
True if low-power mode is active.

---

{#sub_power_get_battery_status}

### sub_power_get_battery_status

```cpp
esp_err_t sub_power_get_battery_status(uint16_t * out_mv, uint8_t * out_pct, h1os_battery_state_t * out_state)
```

Defined in h1os/sub_power.h:60

Retrieve calibrated resting battery voltage, SoC percentage, and charge state.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_mv` | `uint16_t *` | Battery terminal voltage in millivolts. |
| `out_pct` | `uint8_t *` | State-of-charge percentage (0..100%). |
| `out_state` | [`h1os_battery_state_t`](#h1os_battery_state_t) * | Battery operational state (DISCHARGING, CHARGING, CHARGED). |

---

{#sub_power_mv_to_soc_tenths}

### sub_power_mv_to_soc_tenths

```cpp
uint16_t sub_power_mv_to_soc_tenths(uint16_t mv)
```

Defined in h1os/sub_power.h:71

Map battery terminal voltage to State-of-Charge in tenths of a percent (0..1000 = 0.0%..100.0%).

#### Returns
State of charge in tenths of a percent (0 to 1000).

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `mv` | `uint16_t` | Terminal voltage in millivolts. |

---

{#sub_power_calc_autonomy}

### sub_power_calc_autonomy

```cpp
void sub_power_calc_autonomy(uint16_t initial_soc_x10, uint16_t current_soc_x10, uint32_t total_sleep_sec, uint32_t total_app_ms, h1os_autonomy_metrics_t * out_metrics)
```

Defined in h1os/sub_power.h:82

Calculate empirical battery autonomy metrics over total elapsed runtime.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `initial_soc_x10` | `uint16_t` | Starting SoC for the current discharge lap in tenths of a % (0..1000). |
| `current_soc_x10` | `uint16_t` | Current evaluated SoC in tenths of a % (0..1000). |
| `total_sleep_sec` | `uint32_t` | Cumulative deep sleep time in seconds. |
| `total_app_ms` | `uint32_t` | Cumulative main processor active runtime in milliseconds. |
| `out_metrics` | [`h1os_autonomy_metrics_t`](#h1os_autonomy_metrics_t) * | Destination structure for calculated autonomy metrics. |

---

{#sub_power_init}

### sub_power_init

```cpp
esp_err_t sub_power_init(void)
```

Defined in h1os/sub_power.h:95

Initialize battery ADC channel and calibration engine.

Configures ADC1 Channel 3 on GPIO 4 with curve fitting calibration.

#### Returns
ESP_OK on success.

---

{#sub_power_deinit}

### sub_power_deinit

```cpp
esp_err_t sub_power_deinit(void)
```

Defined in h1os/sub_power.h:102

Deinitialize battery ADC driver.

#### Returns
ESP_OK on success.

---

{#sub_power_read_battery}

### sub_power_read_battery

```cpp
esp_err_t sub_power_read_battery(uint16_t * out_mv, uint8_t * out_pct)
```

Defined in h1os/sub_power.h:112

Sample current battery terminal voltage and calculate state-of-charge.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_mv` | `uint16_t *` | Pointer to store sampled voltage in millivolts. |
| `out_pct` | `uint8_t *` | Pointer to store state-of-charge percentage (0..100%). |

---

{#sub_power_get_ulp_cal_params}

### sub_power_get_ulp_cal_params

```cpp
esp_err_t sub_power_get_ulp_cal_params(uint32_t * out_scale, int32_t * out_offset_mv)
```

Defined in h1os/sub_power.h:122

Retrieve two-point calibration parameters for ULP coprocessor ADC readings.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_scale` | `uint32_t *` | Pointer to store scale multiplier. |
| `out_offset_mv` | `int32_t *` | Pointer to store offset in millivolts. |

---

{#sub_power_init_ulp}

### sub_power_init_ulp

```cpp
esp_err_t sub_power_init_ulp(uint32_t flow_a_period_sec)
```

Defined in h1os/sub_power.h:131

Initialize ULP-RISC-V coprocessor firmware for background monitoring.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `flow_a_period_sec` | `uint32_t` | Headless sensor burst interval in seconds. |

---

{#sub_power_set_sleep_slices}

### sub_power_set_sleep_slices

```cpp
void sub_power_set_sleep_slices(uint32_t flow_a_sec, uint32_t flow_b_sec, uint32_t overflow, uint32_t remainder_sec)
```

Defined in h1os/sub_power.h:141

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

Defined in h1os/sub_power.h:152

Enter target deep sleep mode with wake pin configuration.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `sleep_seconds` | `uint32_t` | Sleep duration in seconds. |
| `ext1_pins_mask` | `uint64_t` | Bitmask of GPIOs to configure for EXT1 wake. |
| `mode` | [`sub_power_sleep_mode_t`](#sub_power_sleep_mode_t) | Sleep mode (SUB_POWER_SLEEP_FULL_CYCLE or SUB_POWER_SLEEP_FLOW_A_BURST). |

---

{#sub_power_enter_deep_sleep}

### sub_power_enter_deep_sleep

```cpp
esp_err_t sub_power_enter_deep_sleep(uint32_t sleep_seconds, uint64_t ext1_pins_mask)
```

Defined in h1os/sub_power.h:162

Enter full cycle deep sleep with wake pin configuration.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `sleep_seconds` | `uint32_t` | Sleep duration in seconds. |
| `ext1_pins_mask` | `uint64_t` | Bitmask of GPIOs for EXT1 wake. |

---

{#sub_power_cut_power_latch}

### sub_power_cut_power_latch

```cpp
void sub_power_cut_power_latch(void)
```

Defined in h1os/sub_power.h:167

Cut master power latch (releases GPIO 17 BAT_CTRL).

---

{#sub_power_connected_usb}

### sub_power_connected_usb

```cpp
bool sub_power_connected_usb(void)
```

Defined in h1os/sub_power.h:174

Check if USB VBUS connection is actively present.

#### Returns
True if connected to USB power.

---

{#sub_power_init_dfs}

### sub_power_init_dfs

```cpp
esp_err_t sub_power_init_dfs(sys_clk_mode_t mode)
```

Defined in h1os/sub_power.h:183

Initialize Dynamic Frequency Scaling (DFS) power management.

#### Returns
ESP_OK on success.

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

Defined in h1os/sub_power.h:190

Acquire CPU frequency lock at 240 MHz for compute/display intensive operations.

#### Returns
ESP_OK on success.

---

{#sub_power_cpu_max_release}

### sub_power_cpu_max_release

```cpp
esp_err_t sub_power_cpu_max_release(void)
```

Defined in h1os/sub_power.h:197

Release CPU frequency lock, allowing DFS to downclock to 80 MHz.

#### Returns
ESP_OK on success.

---

{#orch_state_get}

### orch_state_get

```cpp
volatile orch_persisted_state_t * orch_state_get(void)
```

Defined in h1os/orch_state.h:177

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

Defined in h1os/orch_state.h:182

Reset persisted state in RTC Slow Memory to clean factory defaults.

---

{#orch_state_push_sample}

### orch_state_push_sample

```cpp
void orch_state_push_sample(const orch_tri_node_sample_t * sample)
```

Defined in h1os/orch_state.h:189

Push a new sample into the RTC circular ring buffer.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `sample` | const [`orch_tri_node_sample_t`](#orch_tri_node_sample_t) * | Pointer to sample struct to store. |

---

{#orch_state_get_latest_sample}

### orch_state_get_latest_sample

```cpp
bool orch_state_get_latest_sample(orch_tri_node_sample_t * out_sample)
```

Defined in h1os/orch_state.h:198

Retrieve the most recent sample from the ring buffer.

#### Returns
True if a sample was retrieved, false if ring buffer is empty.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_sample` | [`orch_tri_node_sample_t`](#orch_tri_node_sample_t) * | Destination struct for sample copy. Must not be NULL. |

---

{#orch_state_get_latest_valid_sample}

### orch_state_get_latest_valid_sample

```cpp
bool orch_state_get_latest_valid_sample(orch_tri_node_sample_t * out_sample)
```

Defined in h1os/orch_state.h:207

Retrieve the most recent thermally settled, valid sample from the ring buffer.

#### Returns
True if a valid settled sample was located, false otherwise.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_sample` | [`orch_tri_node_sample_t`](#orch_tri_node_sample_t) * | Destination struct for sample copy. Must not be NULL. |

---

{#orch_state_get_ring_chronological}

### orch_state_get_ring_chronological

```cpp
bool orch_state_get_ring_chronological(orch_tri_node_sample_t * out_samples, size_t max_samples, size_t * out_count)
```

Defined in h1os/orch_state.h:218

Copy historical samples from the RTC ring buffer in chronological order (oldest to newest).

#### Returns
True if at least one sample was copied, false if ring buffer is empty or arguments invalid.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_samples` | [`orch_tri_node_sample_t`](#orch_tri_node_sample_t) * | Destination array for samples. Must not be NULL. |
| `max_samples` | `size_t` | Capacity of destination array. |
| `out_count` | `size_t *` | Number of samples copied. Must not be NULL. |

---

{#orch_state_save_runtimes_to_nvs}

### orch_state_save_runtimes_to_nvs

```cpp
void orch_state_save_runtimes_to_nvs(void)
```

Defined in h1os/orch_state.h:223

Save cumulative battery autonomy runtimes to Flash NVS.

---

{#orch_state_load_runtimes_from_nvs}

### orch_state_load_runtimes_from_nvs

```cpp
void orch_state_load_runtimes_from_nvs(void)
```

Defined in h1os/orch_state.h:228

Restore cumulative battery autonomy runtimes from Flash NVS.

---

{#orch_state_reset_discharge_lap}

### orch_state_reset_discharge_lap

```cpp
void orch_state_reset_discharge_lap(uint16_t current_soc_x10)
```

Defined in h1os/orch_state.h:235

Reset discharge lap runtimes on charger unplug or cycle anchor.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `current_soc_x10` | `uint16_t` | Starting SoC in tenths of a percent (0..1000) for the new discharge lap. |

---

{#sub_sdcard_mount}

### sub_sdcard_mount

```cpp
esp_err_t sub_sdcard_mount(void)
```

Defined in h1os/sub_sdcard.h:27

Mount MicroSD card into FATFS VFS in 1-bit SDMMC mode.

#### Returns
ESP_OK on success, or mount failure error.

---

{#sub_sdcard_mount_async}

### sub_sdcard_mount_async

```cpp
esp_err_t sub_sdcard_mount_async(void)
```

Defined in h1os/sub_sdcard.h:34

Mount MicroSD card asynchronously in background task.

#### Returns
ESP_OK if mount task dispatched successfully.

---

{#sub_sdcard_unmount}

### sub_sdcard_unmount

```cpp
esp_err_t sub_sdcard_unmount(void)
```

Defined in h1os/sub_sdcard.h:41

Unmount MicroSD card and release SDMMC host peripheral.

#### Returns
ESP_OK on success.

---

{#sub_sdcard_is_mounted}

### sub_sdcard_is_mounted

```cpp
bool sub_sdcard_is_mounted(void)
```

Defined in h1os/sub_sdcard.h:48

Check if MicroSD card is actively mounted in VFS.

#### Returns
True if filesystem is mounted and accessible.

---

{#sub_sdcard_get_capacity_mb}

### sub_sdcard_get_capacity_mb

```cpp
esp_err_t sub_sdcard_get_capacity_mb(uint32_t * out_capacity_mb)
```

Defined in h1os/sub_sdcard.h:57

Query total storage capacity of mounted MicroSD card in megabytes.

#### Returns
ESP_OK on success, or ESP_ERR_INVALID_STATE if not mounted.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_capacity_mb` | `uint32_t *` | Pointer to store total capacity in MB. Must not be NULL. |

---

{#sub_sdcard_format}

### sub_sdcard_format

```cpp
esp_err_t sub_sdcard_format(void)
```

Defined in h1os/sub_sdcard.h:64

Format mounted MicroSD card with clean FAT32 filesystem.

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

Enables 3.3V power rail (GPIO 6), performs hardware reset pulse, and initializes display RAM registers via SPI DMA.

#### Returns
ESP_OK on success, or SPI communication error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `is_wake_cycle` | `bool` | True if resuming from sleep (bypasses full OTP clear). |

---

{#sub_display_deinit}

### sub_display_deinit

```cpp
esp_err_t sub_display_deinit(void)
```

Defined in h1os/sub_display.h:44

Deinitialize SSD1681 display subsystem and release SPI bus resources.

#### Returns
ESP_OK on success.

---

{#sub_display_get_framebuffer}

### sub_display_get_framebuffer

```cpp
uint8_t * sub_display_get_framebuffer(void)
```

Defined in h1os/sub_display.h:51

Retrieve direct pointer to the active 5000-byte internal RAM framebuffer.

#### Returns
Pointer to packed 1-bit monochrome pixel array.

---

{#sub_display_clear}

### sub_display_clear

```cpp
void sub_display_clear(uint8_t color)
```

Defined in h1os/sub_display.h:58

Clear internal RAM framebuffer to pure color.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `color` | `uint8_t` | 0x00 for solid black, 0xFF for solid white. |

---

{#sub_display_sync_previous_frame}

### sub_display_sync_previous_frame

```cpp
esp_err_t sub_display_sync_previous_frame(const uint8_t * prev_frame)
```

Defined in h1os/sub_display.h:67

Synchronize SSD1681 previous-frame RAM with historical frame for differential refresh.

#### Returns
ESP_OK on success.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `prev_frame` | `const uint8_t *` | Pointer to 5000-byte preserved previous framebuffer. |

---

{#sub_display_wait_busy}

### sub_display_wait_busy

```cpp
esp_err_t sub_display_wait_busy(TickType_t timeout_ticks)
```

Defined in h1os/sub_display.h:76

Block until SSD1681 BUSY line deasserts (panel update complete).

#### Returns
ESP_OK when panel idle, ESP_ERR_TIMEOUT on timeout.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `timeout_ticks` | `TickType_t` | FreeRTOS tick timeout. |

---

{#sub_display_refresh_full}

### sub_display_refresh_full

```cpp
esp_err_t sub_display_refresh_full(void)
```

Defined in h1os/sub_display.h:85

Execute full OTP flashing refresh on electrophoretic panel.

Completely clears DC bias and ghosting artifacts. Takes ~2.4 seconds.

#### Returns
ESP_OK on success.

---

{#sub_display_clear_to_white_full}

### sub_display_clear_to_white_full

```cpp
esp_err_t sub_display_clear_to_white_full(void)
```

Defined in h1os/sub_display.h:94

Clear panel to solid white and trigger full OTP refresh.

Mandatory prior to long-term storage or battery disconnection.

#### Returns
ESP_OK on success.

---

{#sub_display_refresh_partial}

### sub_display_refresh_partial

```cpp
esp_err_t sub_display_refresh_partial(void)
```

Defined in h1os/sub_display.h:103

Execute fast differential partial refresh on panel without screen flash.

Updates only changed pixels. Takes ~300ms.

#### Returns
ESP_OK on success.

---

{#sub_display_read_glass_temp}

### sub_display_read_glass_temp

```cpp
esp_err_t sub_display_read_glass_temp(float * out_temp_c)
```

Defined in h1os/sub_display.h:112

Read temperature from SSD1681 embedded on-glass thermal sensor.

#### Returns
ESP_OK on success, or SPI read error.

#### Parameters

| Parameter | Type | Description |
|-----------|------|-------------|
| `out_temp_c` | `float *` | Pointer to store glass temperature in degrees Celsius. |

---

{#sub_display_get_glass_temp_centi_c}

### sub_display_get_glass_temp_centi_c

```cpp
int16_t sub_display_get_glass_temp_centi_c(void)
```

Defined in h1os/sub_display.h:119

Retrieve the latest cached SSD1681 on-glass temperature in centi-degrees Celsius.

#### Returns
Cached glass temperature in centi-°C (0 if not yet sampled).

---

{#sub_display_enter_deep_sleep}

### sub_display_enter_deep_sleep

```cpp
esp_err_t sub_display_enter_deep_sleep(void)
```

Defined in h1os/sub_display.h:126

Put SSD1681 into Deep Sleep Mode 1 (<1uA quiescent drain).

#### Returns
ESP_OK on success.

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
Full version string (e.g. "2.4.11-dev").

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

{#orch_wake_stub_install}

### orch_wake_stub_install

```cpp
void orch_wake_stub_install(void)
```

Defined in h1os/orch_wake_stub.h:34

Install the deep sleep wake stub into RTC Fast Memory.

Registers [bsp_wake_stub()](#bsp_wake_stub) with esp_set_deep_sleep_wake_stub().

---

{#bsp_wake_stub}

### bsp_wake_stub

```cpp
void bsp_wake_stub(void)
```

Defined in h1os/orch_wake_stub.h:42

Second-stage wake stub executed directly in RTC Fast Memory upon deep sleep wake.

Executes fast sub-3ms Flow A sensor bursts using bitbanged I2C without booting the main ESP-IDF OS or spinning up the 160/240 MHz PLL clocks.

---

{#orch_display_sync_mark_dirty}

### orch_display_sync_mark_dirty

```cpp
void orch_display_sync_mark_dirty(void)
```

Defined in h1os/orch_display_sync.h:23

Mark current display frame as dirty, scheduling a deferred SPI flash backup.

---

{#orch_display_sync_save_if_dirty}

### orch_display_sync_save_if_dirty

```cpp
esp_err_t orch_display_sync_save_if_dirty(void)
```

Defined in h1os/orch_display_sync.h:32

Commit active display framebuffer to SPI flash if marked dirty.

#### Returns

* ESP_OK: Flash partition written or buffer not dirty.
* ESP_FAIL: Flash write failed.

---

{#orch_display_sync_restore_to_framebuffer}

### orch_display_sync_restore_to_framebuffer

```cpp
esp_err_t orch_display_sync_restore_to_framebuffer(void)
```

Defined in h1os/orch_display_sync.h:41

Restore preserved display framebuffer from SPI flash into RAM buffer.

#### Returns

* ESP_OK: Previous frame restored successfully.
* ESP_FAIL: Flash read error.

---

{#orch_display_sync_should_full_refresh}

### orch_display_sync_should_full_refresh

```cpp
bool orch_display_sync_should_full_refresh(void)
```

Defined in h1os/orch_display_sync.h:50

Determine whether the next display update requires a full OTP flash refresh.

Evaluates monotonic partial refresh counter against panel DC bias clearance quota (typically 6).

#### Returns
True if full refresh is mandated to prevent panel ghosting/burn-in.

---

{#orch_display_sync_record_partial_refresh}

### orch_display_sync_record_partial_refresh

```cpp
void orch_display_sync_record_partial_refresh(void)
```

Defined in h1os/orch_display_sync.h:55

Increment the consecutive partial refresh counter.

---

{#orch_display_sync_record_full_refresh}

### orch_display_sync_record_full_refresh

```cpp
void orch_display_sync_record_full_refresh(void)
```

Defined in h1os/orch_display_sync.h:60

Reset the partial refresh counter following a full OTP refresh.

---

{#orch_display_sync_get_partial_count}

### orch_display_sync_get_partial_count

```cpp
uint16_t orch_display_sync_get_partial_count(void)
```

Defined in h1os/orch_display_sync.h:67

Retrieve current monotonic partial refresh counter value.

#### Returns
Number of partial refreshes executed since last full refresh.

{#h1os_ui_msg_t}

## h1os_ui_msg_t

```cpp
#include <h1os/h1os_lvgl.h>
```

```cpp
struct h1os_ui_msg_t
```

Defined in h1os/h1os_lvgl.h:32

Message envelope for the Core 0 -> Core 1 asynchronous UI mutation queue.

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| [`h1os_ui_fn_t`](#h1os_ui_fn_t) | [`fn`](#fn)  | Callback function to execute on Core 1 under LVGL lock. |
| `void *` | [`arg`](#arg)  | Opaque data buffer pointer passed to fn. |

---

{#fn}

#### fn

```cpp
h1os_ui_fn_t fn
```

Type: [`h1os_ui_fn_t`](#h1os_ui_fn_t)

Defined in h1os/h1os_lvgl.h:33

Callback function to execute on Core 1 under LVGL lock.

---

{#arg}

#### arg

```cpp
void * arg
```

Defined in h1os/h1os_lvgl.h:34

Opaque data buffer pointer passed to fn.

{#h1os_lifecycle_t}

## h1os_lifecycle_t

```cpp
#include <h1os/h1os.h>
```

```cpp
struct h1os_lifecycle_t
```

Defined in h1os/h1os.h:200

Declarative application lifecycle configuration structure.

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| [`h1os_boot_cb_t`](#h1os_boot_cb_t) | [`on_boot`](#on_boot)  | System boot / power-on reset hook. |
| [`h1os_wake_cb_t`](#h1os_wake_cb_t) | [`on_wake`](#on_wake)  | Interactive wake hook (Timer / RTC Alarm / Button Tap). |
| [`h1os_sync_cb_t`](#h1os_sync_cb_t) | [`on_sync`](#on_sync)  | Optional parallel network/storage sync hook on Core 0. |
| [`h1os_pre_sleep_cb_t`](#h1os_pre_sleep_cb_t) | [`on_pre_sleep`](#on_pre_sleep)  | Hook executed immediately prior to entering deep sleep. |
| [`h1os_shutdown_cb_t`](#h1os_shutdown_cb_t) | [`on_shutdown`](#on_shutdown)  | Hook executed immediately prior to battery power cut. |
| [`h1os_error_cb_t`](#h1os_error_cb_t) | [`on_error`](#on_error)  | Optional fatal startup/lifecycle error hook. |
| [`h1os_presentation_config_t`](#h1os_presentation_config_t) | [`presentation`](#presentation)  | Presentation splash, chime hooks, and volume settings. |
| [`h1os_session_config_t`](#h1os_session_config_t) | [`session`](#session)  | Session timeout, clock mode, flow periods & sync wait. |
| `void *` | [`user_data`](#user_data)  | Arbitrary user context pointer passed to lifecycle hooks. |

---

{#on_boot}

#### on_boot

```cpp
h1os_boot_cb_t on_boot
```

Type: [`h1os_boot_cb_t`](#h1os_boot_cb_t)

Defined in h1os/h1os.h:201

System boot / power-on reset hook.

---

{#on_wake}

#### on_wake

```cpp
h1os_wake_cb_t on_wake
```

Type: [`h1os_wake_cb_t`](#h1os_wake_cb_t)

Defined in h1os/h1os.h:202

Interactive wake hook (Timer / RTC Alarm / Button Tap).

---

{#on_sync}

#### on_sync

```cpp
h1os_sync_cb_t on_sync
```

Type: [`h1os_sync_cb_t`](#h1os_sync_cb_t)

Defined in h1os/h1os.h:203

Optional parallel network/storage sync hook on Core 0.

---

{#on_pre_sleep}

#### on_pre_sleep

```cpp
h1os_pre_sleep_cb_t on_pre_sleep
```

Type: [`h1os_pre_sleep_cb_t`](#h1os_pre_sleep_cb_t)

Defined in h1os/h1os.h:204

Hook executed immediately prior to entering deep sleep.

---

{#on_shutdown}

#### on_shutdown

```cpp
h1os_shutdown_cb_t on_shutdown
```

Type: [`h1os_shutdown_cb_t`](#h1os_shutdown_cb_t)

Defined in h1os/h1os.h:205

Hook executed immediately prior to battery power cut.

---

{#on_error}

#### on_error

```cpp
h1os_error_cb_t on_error
```

Type: [`h1os_error_cb_t`](#h1os_error_cb_t)

Defined in h1os/h1os.h:206

Optional fatal startup/lifecycle error hook.

---

{#presentation}

#### presentation

```cpp
h1os_presentation_config_t presentation
```

Type: [`h1os_presentation_config_t`](#h1os_presentation_config_t)

Defined in h1os/h1os.h:208

Presentation splash, chime hooks, and volume settings.

---

{#session}

#### session

```cpp
h1os_session_config_t session
```

Type: [`h1os_session_config_t`](#h1os_session_config_t)

Defined in h1os/h1os.h:209

Session timeout, clock mode, flow periods & sync wait.

---

{#user_data}

#### user_data

```cpp
void * user_data
```

Defined in h1os/h1os.h:211

Arbitrary user context pointer passed to lifecycle hooks.

{#h1os_telemetry_t}

## h1os_telemetry_t

```cpp
#include <h1os/h1os.h>
```

```cpp
struct h1os_telemetry_t
```

Defined in h1os/h1os.h:217

Comprehensive environmental telemetry and system metrics snapshot.

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `float` | [`ambient_temp_c`](#ambient_temp_c)  | Trusted steady-state SHTC3 ambient temperature in degrees Celsius. |
| `float` | [`ambient_temp_f`](#ambient_temp_f)  | Trusted steady-state SHTC3 ambient temperature in degrees Fahr. |
| `float` | [`ambient_temp_k`](#ambient_temp_k)  | Trusted steady-state SHTC3 ambient temperature in Kelvin (derived). |
| `float` | [`ambient_rh_pct`](#ambient_rh_pct)  | Trusted steady-state SHTC3 relative humidity percentage (0..100%). |
| `float` | [`dew_point_c`](#dew_point_c)  | Psychrometrically calculated dew point in degrees Celsius. |
| `float` | [`dew_point_f`](#dew_point_f)  | Psychrometrically calculated dew point in degrees Fahrenheit. |
| `float` | [`dew_point_k`](#dew_point_k)  | Psychrometrically calculated dew point in Kelvin (derived). |
| `float` | [`vapor_pressure_hpa`](#vapor_pressure_hpa)  | Calculated water vapor partial pressure in hectopascals (hPa). |
| `float` | [`sat_vapor_pressure_hpa`](#sat_vapor_pressure_hpa)  | Calculated saturation vapor pressure in hectopascals (hPa). |
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
| `uint32_t` | [`sample_count`](#sample_count)  | Total monotonic environmental telemetry sample count. |
| `uint32_t` | [`boot_count`](#boot_count)  | Total monotonic system boot cycles. |
| `uint32_t` | [`wake_count`](#wake_count)  | Total monotonic deep sleep wake cycles (Flow A + Flow B + Button). |
| `uint32_t` | [`flow_b_count`](#flow_b_count)  | Monotonic unattended RTC Flow B presentation wake cycles. |
| `uint32_t` | [`button_wake_count`](#button_wake_count)  | Monotonic interactive tactile button wake cycles. |
| `uint8_t` | [`ulp_dispatch_reason`](#ulp_dispatch_reason)  | Reason code from last ULP coprocessor dispatch. |
| `uint32_t` | [`flow_a_period_sec`](#flow_a_period_sec)  | Active Flow A sensor sample interval in seconds. |
| `uint32_t` | [`flow_b_period_sec`](#flow_b_period_sec)  | Active Flow B display refresh interval in seconds. |
| `uint16_t` | [`battery_mv`](#battery_mv)  | Sampled battery terminal voltage in millivolts. |
| `uint16_t` | [`boot_vbat_mv`](#boot_vbat_mv)  | Initial non-USB battery voltage captured on boot in millivolts. |
| `uint8_t` | [`battery_percent`](#battery_percent)  | Estimated battery state-of-charge percentage (0..100%). |
| `bool` | [`is_usb_powered`](#is_usb_powered)  | True if USB VBUS power connection is actively detected. |
| [`h1os_battery_state_t`](#h1os_battery_state_t) | [`battery_state`](#battery_state)  | Charge / discharge / charged operational state. |
| [`h1os_autonomy_metrics_t`](#h1os_autonomy_metrics_t) | [`autonomy`](#autonomy)  | Empirical battery autonomy metrics over total elapsed runtime. |
| `uint32_t` | [`sensor_fail_count`](#sensor_fail_count)  | Total count of failed wake-stub sensor sample attempts. |
| `uint8_t` | [`last_sensor_error`](#last_sensor_error)  | Most recent sensor error enum code ([orch_sensor_err_t](#orch_sensor_err_t)). |
| `bool` | [`is_rh_alert_active`](#is_rh_alert_active)  | True if settled RH is outside configured humidor target bounds. |

---

{#ambient_temp_c}

#### ambient_temp_c

```cpp
float ambient_temp_c
```

Defined in h1os/h1os.h:218

Trusted steady-state SHTC3 ambient temperature in degrees Celsius.

---

{#ambient_temp_f}

#### ambient_temp_f

```cpp
float ambient_temp_f
```

Defined in h1os/h1os.h:219

Trusted steady-state SHTC3 ambient temperature in degrees Fahr.

---

{#ambient_temp_k}

#### ambient_temp_k

```cpp
float ambient_temp_k
```

Defined in h1os/h1os.h:220

Trusted steady-state SHTC3 ambient temperature in Kelvin (derived).

---

{#ambient_rh_pct}

#### ambient_rh_pct

```cpp
float ambient_rh_pct
```

Defined in h1os/h1os.h:221

Trusted steady-state SHTC3 relative humidity percentage (0..100%).

---

{#dew_point_c}

#### dew_point_c

```cpp
float dew_point_c
```

Defined in h1os/h1os.h:222

Psychrometrically calculated dew point in degrees Celsius.

---

{#dew_point_f}

#### dew_point_f

```cpp
float dew_point_f
```

Defined in h1os/h1os.h:223

Psychrometrically calculated dew point in degrees Fahrenheit.

---

{#dew_point_k}

#### dew_point_k

```cpp
float dew_point_k
```

Defined in h1os/h1os.h:224

Psychrometrically calculated dew point in Kelvin (derived).

---

{#vapor_pressure_hpa}

#### vapor_pressure_hpa

```cpp
float vapor_pressure_hpa
```

Defined in h1os/h1os.h:225

Calculated water vapor partial pressure in hectopascals (hPa).

---

{#sat_vapor_pressure_hpa}

#### sat_vapor_pressure_hpa

```cpp
float sat_vapor_pressure_hpa
```

Defined in h1os/h1os.h:226

Calculated saturation vapor pressure in hectopascals (hPa).

---

{#absolute_humidity_g}

#### absolute_humidity_g

```cpp
float absolute_humidity_g
```

Defined in h1os/h1os.h:227

Calculated absolute humidity in grams per cubic meter (g/m³).

---

{#window_low_c}

#### window_low_c

```cpp
float window_low_c
```

Defined in h1os/h1os.h:229

Valid Window Floor (minimum over valid 32-sample window).

---

{#window_high_c}

#### window_high_c

```cpp
float window_high_c
```

Defined in h1os/h1os.h:230

Valid Window Ceiling (maximum over valid 32-sample window).

---

{#window_avg_shtc3_c}

#### window_avg_shtc3_c

```cpp
float window_avg_shtc3_c
```

Defined in h1os/h1os.h:231

Short-term valid SHTC3 sensor window average in degrees Celsius.

---

{#window_avg_die_c}

#### window_avg_die_c

```cpp
float window_avg_die_c
```

Defined in h1os/h1os.h:232

Short-term valid MCU Die internal sensor window average.

---

{#temp_historical_c}

#### temp_historical_c

```cpp
float temp_historical_c
```

Defined in h1os/h1os.h:233

Long-term light EWMA historical baseline temperature.

---

{#rh_historical_pct}

#### rh_historical_pct

```cpp
float rh_historical_pct
```

Defined in h1os/h1os.h:234

Long-term light EWMA historical baseline relative humidity.

---

{#raw_shtc3_temp_c}

#### raw_shtc3_temp_c

```cpp
float raw_shtc3_temp_c
```

Defined in h1os/h1os.h:236

Instantaneous raw Sensirion SHTC3 temperature in degrees Celsius.

---

{#mcu_die_temp_c}

#### mcu_die_temp_c

```cpp
float mcu_die_temp_c
```

Defined in h1os/h1os.h:237

Instantaneous ESP32-S3 internal TSENS die temperature.

---

{#epd_glass_temp_c}

#### epd_glass_temp_c

```cpp
float epd_glass_temp_c
```

Defined in h1os/h1os.h:238

Instantaneous SSD1681 display on-glass temperature sensor reading.

---

{#trinode_temp_c}

#### trinode_temp_c

```cpp
float trinode_temp_c
```

Defined in h1os/h1os.h:239

Tri-Node verification consensus: (T_valid + T_die + T_glass) / 3.0.

---

{#trinode_delta_c}

#### trinode_delta_c

```cpp
float trinode_delta_c
```

Defined in h1os/h1os.h:240

Cross-node verification delta: T_valid - T_trinode.

---

{#trinode_confidence_pct}

#### trinode_confidence_pct

```cpp
uint8_t trinode_confidence_pct
```

Defined in h1os/h1os.h:241

0-100% cross-node range verification confidence score.

---

{#is_thermally_settled}

#### is_thermally_settled

```cpp
bool is_thermally_settled
```

Defined in h1os/h1os.h:243

True if steady-state thermal criteria (|T2-T1| <= gate) are met.

---

{#valid_trend}

#### valid_trend

```cpp
uint16_t valid_trend
```

Defined in h1os/h1os.h:244

Monotonic count of consecutive thermally settled Flow A samples.

---

{#sample_count}

#### sample_count

```cpp
uint32_t sample_count
```

Defined in h1os/h1os.h:245

Total monotonic environmental telemetry sample count.

---

{#boot_count}

#### boot_count

```cpp
uint32_t boot_count
```

Defined in h1os/h1os.h:246

Total monotonic system boot cycles.

---

{#wake_count}

#### wake_count

```cpp
uint32_t wake_count
```

Defined in h1os/h1os.h:247

Total monotonic deep sleep wake cycles (Flow A + Flow B + Button).

---

{#flow_b_count}

#### flow_b_count

```cpp
uint32_t flow_b_count
```

Defined in h1os/h1os.h:248

Monotonic unattended RTC Flow B presentation wake cycles.

---

{#button_wake_count}

#### button_wake_count

```cpp
uint32_t button_wake_count
```

Defined in h1os/h1os.h:249

Monotonic interactive tactile button wake cycles.

---

{#ulp_dispatch_reason}

#### ulp_dispatch_reason

```cpp
uint8_t ulp_dispatch_reason
```

Defined in h1os/h1os.h:250

Reason code from last ULP coprocessor dispatch.

---

{#flow_a_period_sec}

#### flow_a_period_sec

```cpp
uint32_t flow_a_period_sec
```

Defined in h1os/h1os.h:251

Active Flow A sensor sample interval in seconds.

---

{#flow_b_period_sec}

#### flow_b_period_sec

```cpp
uint32_t flow_b_period_sec
```

Defined in h1os/h1os.h:252

Active Flow B display refresh interval in seconds.

---

{#battery_mv}

#### battery_mv

```cpp
uint16_t battery_mv
```

Defined in h1os/h1os.h:253

Sampled battery terminal voltage in millivolts.

---

{#boot_vbat_mv}

#### boot_vbat_mv

```cpp
uint16_t boot_vbat_mv
```

Defined in h1os/h1os.h:254

Initial non-USB battery voltage captured on boot in millivolts.

---

{#battery_percent}

#### battery_percent

```cpp
uint8_t battery_percent
```

Defined in h1os/h1os.h:255

Estimated battery state-of-charge percentage (0..100%).

---

{#is_usb_powered}

#### is_usb_powered

```cpp
bool is_usb_powered
```

Defined in h1os/h1os.h:256

True if USB VBUS power connection is actively detected.

---

{#battery_state}

#### battery_state

```cpp
h1os_battery_state_t battery_state
```

Type: [`h1os_battery_state_t`](#h1os_battery_state_t)

Defined in h1os/h1os.h:257

Charge / discharge / charged operational state.

---

{#autonomy}

#### autonomy

```cpp
h1os_autonomy_metrics_t autonomy
```

Type: [`h1os_autonomy_metrics_t`](#h1os_autonomy_metrics_t)

Defined in h1os/h1os.h:258

Empirical battery autonomy metrics over total elapsed runtime.

---

{#sensor_fail_count}

#### sensor_fail_count

```cpp
uint32_t sensor_fail_count
```

Defined in h1os/h1os.h:259

Total count of failed wake-stub sensor sample attempts.

---

{#last_sensor_error}

#### last_sensor_error

```cpp
uint8_t last_sensor_error
```

Defined in h1os/h1os.h:260

Most recent sensor error enum code ([orch_sensor_err_t](#orch_sensor_err_t)).

---

{#is_rh_alert_active}

#### is_rh_alert_active

```cpp
bool is_rh_alert_active
```

Defined in h1os/h1os.h:261

True if settled RH is outside configured humidor target bounds.

{#h1os_wake_context_t}

## h1os_wake_context_t

```cpp
#include <h1os/h1os.h>
```

```cpp
struct h1os_wake_context_t
```

Defined in h1os/h1os.h:84

Platform wakeup context descriptor.

Populated during boot and passed to the application lifecycle on_wake and on_sync hooks.

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `esp_reset_reason_t` | [`reset_reason`](#reset_reason)  | Hardware reset reason code. |
| `uint32_t` | [`wakeup_causes`](#wakeup_causes)  | Bitmap of wakeup sources (esp_sleep_get_wakeup_causes). |
| [`h1os_wake_state_t`](#h1os_wake_state_t) | [`wake_state`](#wake_state)  | Explicit wake state classification (BOOT, INTERACTIVE, RTC_FLOW_B). |
| `uint32_t` | [`boot_count`](#boot_count-1)  | Monotonic system boot cycle count. |
| `uint32_t` | [`wake_count`](#wake_count-1)  | Monotonic total deep sleep wake cycle count (Flow A + Flow B + Button). |
| `uint32_t` | [`flow_b_count`](#flow_b_count-1)  | Monotonic unattended RTC Flow B presentation wake cycle count. |
| `uint32_t` | [`button_wake_count`](#button_wake_count-1)  | Monotonic interactive tactile button wake cycle count. |
| `bool` | [`woke_from_button`](#woke_from_button)  | True if system woke due to physical button actuation. |
| `uint8_t` | [`wake_button`](#wake_button)  | Waking button ID ([h1os_wake_btn_t](#h1os_wake_btn_t): 0=None, 1=BOOT, 2=POWER). |
| `uint8_t` | [`ulp_dispatch_reason`](#ulp_dispatch_reason-1)  | Reason code from last ULP coprocessor dispatch (h1os_ulp_reason_t). |
| `uint32_t` | [`sleep_duration_sec`](#sleep_duration_sec)  | Configured sleep interval prior to wake in seconds. |
| `void *` | [`user_data`](#user_data-1)  | User context pointer passed to lifecycle. |

---

{#reset_reason}

#### reset_reason

```cpp
esp_reset_reason_t reset_reason
```

Defined in h1os/h1os.h:85

Hardware reset reason code.

---

{#wakeup_causes}

#### wakeup_causes

```cpp
uint32_t wakeup_causes
```

Defined in h1os/h1os.h:86

Bitmap of wakeup sources (esp_sleep_get_wakeup_causes).

---

{#wake_state}

#### wake_state

```cpp
h1os_wake_state_t wake_state
```

Type: [`h1os_wake_state_t`](#h1os_wake_state_t)

Defined in h1os/h1os.h:87

Explicit wake state classification (BOOT, INTERACTIVE, RTC_FLOW_B).

---

{#boot_count-1}

#### boot_count

```cpp
uint32_t boot_count
```

Defined in h1os/h1os.h:88

Monotonic system boot cycle count.

---

{#wake_count-1}

#### wake_count

```cpp
uint32_t wake_count
```

Defined in h1os/h1os.h:89

Monotonic total deep sleep wake cycle count (Flow A + Flow B + Button).

---

{#flow_b_count-1}

#### flow_b_count

```cpp
uint32_t flow_b_count
```

Defined in h1os/h1os.h:90

Monotonic unattended RTC Flow B presentation wake cycle count.

---

{#button_wake_count-1}

#### button_wake_count

```cpp
uint32_t button_wake_count
```

Defined in h1os/h1os.h:91

Monotonic interactive tactile button wake cycle count.

---

{#woke_from_button}

#### woke_from_button

```cpp
bool woke_from_button
```

Defined in h1os/h1os.h:92

True if system woke due to physical button actuation.

---

{#wake_button}

#### wake_button

```cpp
uint8_t wake_button
```

Defined in h1os/h1os.h:93

Waking button ID ([h1os_wake_btn_t](#h1os_wake_btn_t): 0=None, 1=BOOT, 2=POWER).

---

{#ulp_dispatch_reason-1}

#### ulp_dispatch_reason

```cpp
uint8_t ulp_dispatch_reason
```

Defined in h1os/h1os.h:94

Reason code from last ULP coprocessor dispatch (h1os_ulp_reason_t).

---

{#sleep_duration_sec}

#### sleep_duration_sec

```cpp
uint32_t sleep_duration_sec
```

Defined in h1os/h1os.h:95

Configured sleep interval prior to wake in seconds.

---

{#user_data-1}

#### user_data

```cpp
void * user_data
```

Defined in h1os/h1os.h:96

User context pointer passed to lifecycle.

{#h1os_session_config_t}

## h1os_session_config_t

```cpp
#include <h1os/h1os.h>
```

```cpp
struct h1os_session_config_t
```

Defined in h1os/h1os.h:188

Lifecycle session timeout, clock scaling, flow slicing, and sync configuration.

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint32_t` | [`inactivity_timeout_sec`](#inactivity_timeout_sec)  | Interactive session idle sleep timeout in seconds. |
| [`sys_clk_mode_t`](#sys_clk_mode_t) | [`clk_mode`](#clk_mode)  | CPU clock scaling mode (SYS_CLK_MODE_DYNAMIC by default). |
| `uint32_t` | [`flow_a_period_sec`](#flow_a_period_sec-1)  | Period between headless sensor sample bursts in seconds. |
| `uint32_t` | [`flow_b_period_sec`](#flow_b_period_sec-1)  | Period between unattended display flushes in seconds. |
| `uint32_t` | [`sync_wait_ms`](#sync_wait_ms)  | Inbound sync pre-flush gate window in ms (0 = immediate flush). |
| `uint32_t` | [`sync_timeout_ms`](#sync_timeout_ms)  | Max barrier wait for async on_sync completion before sleep. |

---

{#inactivity_timeout_sec}

#### inactivity_timeout_sec

```cpp
uint32_t inactivity_timeout_sec
```

Defined in h1os/h1os.h:189

Interactive session idle sleep timeout in seconds.

---

{#clk_mode}

#### clk_mode

```cpp
sys_clk_mode_t clk_mode
```

Type: [`sys_clk_mode_t`](#sys_clk_mode_t)

Defined in h1os/h1os.h:190

CPU clock scaling mode (SYS_CLK_MODE_DYNAMIC by default).

---

{#flow_a_period_sec-1}

#### flow_a_period_sec

```cpp
uint32_t flow_a_period_sec
```

Defined in h1os/h1os.h:191

Period between headless sensor sample bursts in seconds.

---

{#flow_b_period_sec-1}

#### flow_b_period_sec

```cpp
uint32_t flow_b_period_sec
```

Defined in h1os/h1os.h:192

Period between unattended display flushes in seconds.

---

{#sync_wait_ms}

#### sync_wait_ms

```cpp
uint32_t sync_wait_ms
```

Defined in h1os/h1os.h:193

Inbound sync pre-flush gate window in ms (0 = immediate flush).

---

{#sync_timeout_ms}

#### sync_timeout_ms

```cpp
uint32_t sync_timeout_ms
```

Defined in h1os/h1os.h:194

Max barrier wait for async on_sync completion before sleep.

{#orch_persisted_state_t}

## orch_persisted_state_t

```cpp
#include <h1os/orch_state.h>
```

```cpp
struct orch_persisted_state_t
```

Defined in h1os/orch_state.h:106

Master persistent state block allocated in RTC Slow SRAM.

Retained across all deep sleep cycles and wake stub executions.

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint32_t` | [`magic`](#magic)  | State validation magic word (ORCH_RTC_MAGIC). |
| `uint32_t` | [`boot_count`](#boot_count-2)  | Total monotonic system boot cycles. |
| `uint32_t` | [`wake_count`](#wake_count-2)  | Monotonic deep sleep wake cycle count (Flow A + Flow B + Button). |
| `uint32_t` | [`flow_b_counter`](#flow_b_counter)  | Monotonic unattended RTC Flow B presentation wake cycle count. |
| `uint32_t` | [`button_wake_count`](#button_wake_count-2)  | Monotonic interactive tactile button wake cycle count. |
| `uint8_t` | [`flags`](#flags)  | Operating state flags (ORCH_FLAG_*). |
| `uint8_t` | [`ulp_dispatch_reason`](#ulp_dispatch_reason-2)  | Reason code from last ULP coprocessor dispatch. |
| `uint16_t` | [`last_vbat_mv`](#last_vbat_mv)  | Last sampled battery terminal voltage in millivolts. |
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
| `uint32_t` | [`total_sleep_sec`](#total_sleep_sec)  | Cumulative seconds spent in deep sleep. |
| `uint32_t` | [`total_app_run_ms`](#total_app_run_ms)  | Cumulative milliseconds executing main processor application. |
| `uint32_t` | [`last_nvs_commit_sec`](#last_nvs_commit_sec)  | Sleep timestamp (total_sleep_sec) of last successful NVS runtime commit. |
| `uint16_t` | [`initial_soc_x10`](#initial_soc_x10)  | State of Charge at start of discharge lap in tenths of % (0..1000). |
| `uint8_t` | [`_pad_soc`](#_pad_soc)  | Alignment padding to 32-bit boundary. |
| `uint32_t` | [`sensor_fail_count`](#sensor_fail_count-1)  | Monotonic count of failed wake-stub sensor reads. |
| `uint8_t` | [`last_sensor_error`](#last_sensor_error-1)  | Last error code ([orch_sensor_err_t](#orch_sensor_err_t)). |
| `uint8_t` | [`_pad_sensor`](#_pad_sensor)  | Alignment padding to 32-bit boundary. |
| `uint16_t` | [`rh_alert_low_centi_pct`](#rh_alert_low_centi_pct)  | Lower RH alert threshold in centi-% (0 = disabled). |
| `uint16_t` | [`rh_alert_high_centi_pct`](#rh_alert_high_centi_pct)  | Upper RH alert threshold in centi-% (0 = disabled). |

---

{#magic}

#### magic

```cpp
uint32_t magic
```

Defined in h1os/orch_state.h:107

State validation magic word (ORCH_RTC_MAGIC).

---

{#boot_count-2}

#### boot_count

```cpp
uint32_t boot_count
```

Defined in h1os/orch_state.h:108

Total monotonic system boot cycles.

---

{#wake_count-2}

#### wake_count

```cpp
uint32_t wake_count
```

Defined in h1os/orch_state.h:109

Monotonic deep sleep wake cycle count (Flow A + Flow B + Button).

---

{#flow_b_counter}

#### flow_b_counter

```cpp
uint32_t flow_b_counter
```

Defined in h1os/orch_state.h:110

Monotonic unattended RTC Flow B presentation wake cycle count.

---

{#button_wake_count-2}

#### button_wake_count

```cpp
uint32_t button_wake_count
```

Defined in h1os/orch_state.h:111

Monotonic interactive tactile button wake cycle count.

---

{#flags}

#### flags

```cpp
uint8_t flags
```

Defined in h1os/orch_state.h:112

Operating state flags (ORCH_FLAG_*).

---

{#ulp_dispatch_reason-2}

#### ulp_dispatch_reason

```cpp
uint8_t ulp_dispatch_reason
```

Defined in h1os/orch_state.h:113

Reason code from last ULP coprocessor dispatch.

---

{#last_vbat_mv}

#### last_vbat_mv

```cpp
uint16_t last_vbat_mv
```

Defined in h1os/orch_state.h:114

Last sampled battery terminal voltage in millivolts.

---

{#boot_vbat_mv-1}

#### boot_vbat_mv

```cpp
uint16_t boot_vbat_mv
```

Defined in h1os/orch_state.h:115

Initial non-USB battery voltage captured on boot in millivolts.

---

{#sample_interval_sec}

#### sample_interval_sec

```cpp
uint32_t sample_interval_sec
```

Defined in h1os/orch_state.h:117

Interval between Flow A sensor samples in seconds.

---

{#flow_b_period_sec-2}

#### flow_b_period_sec

```cpp
uint32_t flow_b_period_sec
```

Defined in h1os/orch_state.h:118

Interval between Flow B display refreshes in seconds.

---

{#last_ewma_sample_seq}

#### last_ewma_sample_seq

```cpp
uint32_t last_ewma_sample_seq
```

Defined in h1os/orch_state.h:119

Sample sequence number of last processed EWMA & ring debug update.

---

{#epd_partial_refresh_count}

#### epd_partial_refresh_count

```cpp
uint16_t epd_partial_refresh_count
```

Defined in h1os/orch_state.h:121

Consecutive differential partial refreshes on EPD.

---

{#valid_trend-1}

#### valid_trend

```cpp
uint16_t valid_trend
```

Defined in h1os/orch_state.h:122

Monotonic count of consecutive settled steady-state samples.

---

{#window_low_temp_centi_c}

#### window_low_temp_centi_c

```cpp
int16_t window_low_temp_centi_c
```

Defined in h1os/orch_state.h:124

Valid Window Floor (minimum over active window) in centi-°C.

---

{#window_high_temp_centi_c}

#### window_high_temp_centi_c

```cpp
int16_t window_high_temp_centi_c
```

Defined in h1os/orch_state.h:125

Valid Window Ceiling (maximum over active window) in centi-°C.

---

{#last_glass_temp_centi_c}

#### last_glass_temp_centi_c

```cpp
int16_t last_glass_temp_centi_c
```

Defined in h1os/orch_state.h:126

Last sampled EPD glass temperature in centi-°C.

---

{#window_avg_shtc3_c-1}

#### window_avg_shtc3_c

```cpp
float window_avg_shtc3_c
```

Defined in h1os/orch_state.h:128

Short-term valid SHTC3 window average in degrees Celsius.

---

{#window_avg_die_c-1}

#### window_avg_die_c

```cpp
float window_avg_die_c
```

Defined in h1os/orch_state.h:129

Short-term valid MCU Die window average in degrees Celsius.

---

{#temp_historical_c-1}

#### temp_historical_c

```cpp
float temp_historical_c
```

Defined in h1os/orch_state.h:130

Long-term light EWMA baseline temperature.

---

{#rh_historical_pct-1}

#### rh_historical_pct

```cpp
float rh_historical_pct
```

Defined in h1os/orch_state.h:131

Long-term light EWMA baseline relative humidity.

---

{#ambient_temp_c-1}

#### ambient_temp_c

```cpp
float ambient_temp_c
```

Defined in h1os/orch_state.h:133

Trusted steady-state SHTC3 ambient temperature in °C.

---

{#ambient_rh_pct-1}

#### ambient_rh_pct

```cpp
float ambient_rh_pct
```

Defined in h1os/orch_state.h:134

Trusted steady-state SHTC3 ambient relative humidity in %.

---

{#dew_point_c-1}

#### dew_point_c

```cpp
float dew_point_c
```

Defined in h1os/orch_state.h:135

Calculated dew point temperature in °C.

---

{#vapor_pressure_hpa-1}

#### vapor_pressure_hpa

```cpp
float vapor_pressure_hpa
```

Defined in h1os/orch_state.h:136

Calculated water vapor partial pressure in hPa.

---

{#trinode_temp_c-1}

#### trinode_temp_c

```cpp
float trinode_temp_c
```

Defined in h1os/orch_state.h:138

Tri-Node verification average: (T_valid + T_die + T_glass) / 3.0.

---

{#trinode_delta_c-1}

#### trinode_delta_c

```cpp
float trinode_delta_c
```

Defined in h1os/orch_state.h:139

Cross-sensor verification delta: T_valid - T_trinode.

---

{#trinode_confidence_pct-1}

#### trinode_confidence_pct

```cpp
uint8_t trinode_confidence_pct
```

Defined in h1os/orch_state.h:140

0-100% cross-sensor range verification score.

---

{#ewma_inited}

#### ewma_inited

```cpp
bool ewma_inited
```

Defined in h1os/orch_state.h:141

True if EWMA filters have been seeded with initial samples.

---

{#tsens_cal_centi_c}

#### tsens_cal_centi_c

```cpp
int16_t tsens_cal_centi_c
```

Defined in h1os/orch_state.h:142

Factory calibrated TSENS eFuse offset in centi-degrees Celsius.

---

{#tsens_offset_centi_c}

#### tsens_offset_centi_c

```cpp
int16_t tsens_offset_centi_c
```

Defined in h1os/orch_state.h:143

Pre-computed TSENS fixed-point intercept (2052 + tsens_cal_centi_c).

---

{#ring}

#### ring

```cpp
orch_tri_node_sample_t ring[32]
```

Defined in h1os/orch_state.h:145

Circular ring buffer of historical telemetry samples.

---

{#ring_head}

#### ring_head

```cpp
uint8_t ring_head
```

Defined in h1os/orch_state.h:147

Write head index into circular ring buffer (0..ORCH_RING_CAPACITY-1).

---

{#total_samples}

#### total_samples

```cpp
uint32_t total_samples
```

Defined in h1os/orch_state.h:148

Total lifetime samples recorded across all sessions.

---

{#total_sleep_sec}

#### total_sleep_sec

```cpp
uint32_t total_sleep_sec
```

Defined in h1os/orch_state.h:150

Cumulative seconds spent in deep sleep.

---

{#total_app_run_ms}

#### total_app_run_ms

```cpp
uint32_t total_app_run_ms
```

Defined in h1os/orch_state.h:151

Cumulative milliseconds executing main processor application.

---

{#last_nvs_commit_sec}

#### last_nvs_commit_sec

```cpp
uint32_t last_nvs_commit_sec
```

Defined in h1os/orch_state.h:152

Sleep timestamp (total_sleep_sec) of last successful NVS runtime commit.

---

{#initial_soc_x10}

#### initial_soc_x10

```cpp
uint16_t initial_soc_x10
```

Defined in h1os/orch_state.h:153

State of Charge at start of discharge lap in tenths of % (0..1000).

---

{#_pad_soc}

#### _pad_soc

```cpp
uint8_t _pad_soc[2]
```

Defined in h1os/orch_state.h:154

Alignment padding to 32-bit boundary.

---

{#sensor_fail_count-1}

#### sensor_fail_count

```cpp
uint32_t sensor_fail_count
```

Defined in h1os/orch_state.h:155

Monotonic count of failed wake-stub sensor reads.

---

{#last_sensor_error-1}

#### last_sensor_error

```cpp
uint8_t last_sensor_error
```

Defined in h1os/orch_state.h:156

Last error code ([orch_sensor_err_t](#orch_sensor_err_t)).

---

{#_pad_sensor}

#### _pad_sensor

```cpp
uint8_t _pad_sensor[3]
```

Defined in h1os/orch_state.h:157

Alignment padding to 32-bit boundary.

---

{#rh_alert_low_centi_pct}

#### rh_alert_low_centi_pct

```cpp
uint16_t rh_alert_low_centi_pct
```

Defined in h1os/orch_state.h:158

Lower RH alert threshold in centi-% (0 = disabled).

---

{#rh_alert_high_centi_pct}

#### rh_alert_high_centi_pct

```cpp
uint16_t rh_alert_high_centi_pct
```

Defined in h1os/orch_state.h:159

Upper RH alert threshold in centi-% (0 = disabled).

{#h1os_autonomy_metrics_t}

## h1os_autonomy_metrics_t

```cpp
#include <h1os/sub_power.h>
```

```cpp
struct h1os_autonomy_metrics_t
```

Defined in h1os/sub_power.h:45

Empirical battery autonomy metrics over total elapsed runtime.

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `float` | [`avg_draw_ma`](#avg_draw_ma)  | Average current draw over total elapsed runtime in mA. |
| `float` | [`autonomy_days`](#autonomy_days)  | Remaining days at current duty cycle (-1.0f if calibrating). |
| `float` | [`mah_spent_lap`](#mah_spent_lap)  | Total mAh consumed since initial_soc_x10. |

---

{#avg_draw_ma}

#### avg_draw_ma

```cpp
float avg_draw_ma
```

Defined in h1os/sub_power.h:46

Average current draw over total elapsed runtime in mA.

---

{#autonomy_days}

#### autonomy_days

```cpp
float autonomy_days
```

Defined in h1os/sub_power.h:47

Remaining days at current duty cycle (-1.0f if calibrating).

---

{#mah_spent_lap}

#### mah_spent_lap

```cpp
float mah_spent_lap
```

Defined in h1os/sub_power.h:48

Total mAh consumed since initial_soc_x10.

{#orch_tri_node_sample_t}

## orch_tri_node_sample_t

```cpp
#include <h1os/orch_state.h>
```

```cpp
struct orch_tri_node_sample_t
```

Defined in h1os/orch_state.h:81

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

Defined in h1os/orch_state.h:82

SHTC3 temperature in centi-degrees Celsius (1°C = 100).

---

{#shtc3_rh_centi_pct}

#### shtc3_rh_centi_pct

```cpp
uint16_t shtc3_rh_centi_pct
```

Defined in h1os/orch_state.h:83

SHTC3 relative humidity in centi-percent (1% = 100).

---

{#mcu_tsens_centi_c}

#### mcu_tsens_centi_c

```cpp
int16_t mcu_tsens_centi_c
```

Defined in h1os/orch_state.h:84

ESP32-S3 internal TSENS die temperature in centi-degrees Celsius.

---

{#epd_glass_centi_c}

#### epd_glass_centi_c

```cpp
int16_t epd_glass_centi_c
```

Defined in h1os/orch_state.h:85

SSD1681 on-glass thermal sensor in centi-degrees Celsius.

---

{#timestamp_sec}

#### timestamp_sec

```cpp
uint32_t timestamp_sec
```

Defined in h1os/orch_state.h:86

Sample epoch timestamp in seconds.

---

{#quality_flags}

#### quality_flags

```cpp
uint8_t quality_flags
```

Defined in h1os/orch_state.h:87

Sample qualification bitmask (SAMPLE_FLAG_*).

---

{#_pad}

#### _pad

```cpp
uint8_t _pad[3]
```

Defined in h1os/orch_state.h:88

Alignment padding to 32-bit boundary.

{#orch_nvs_runtime_blob_t}

## orch_nvs_runtime_blob_t

```cpp
#include <h1os/orch_state.h>
```

```cpp
struct orch_nvs_runtime_blob_t
```

Defined in h1os/orch_state.h:94

Compact 12-byte atomic battery autonomy runtime blob committed to Flash NVS.

### Public Attributes

| Return | Name | Description |
|--------|------|-------------|
| `uint32_t` | [`total_sleep_sec`](#total_sleep_sec-1)  | Cumulative seconds spent in deep sleep. |
| `uint32_t` | [`total_app_run_ms`](#total_app_run_ms-1)  | Cumulative milliseconds executing main processor application. |
| `uint16_t` | [`initial_soc_x10`](#initial_soc_x10-1)  | State of Charge at start of discharge lap in tenths of % (0..1000). |
| `uint16_t` | [`reserved`](#reserved)  | 16-bit alignment padding / reserved. |

---

{#total_sleep_sec-1}

#### total_sleep_sec

```cpp
uint32_t total_sleep_sec
```

Defined in h1os/orch_state.h:95

Cumulative seconds spent in deep sleep.

---

{#total_app_run_ms-1}

#### total_app_run_ms

```cpp
uint32_t total_app_run_ms
```

Defined in h1os/orch_state.h:96

Cumulative milliseconds executing main processor application.

---

{#initial_soc_x10-1}

#### initial_soc_x10

```cpp
uint16_t initial_soc_x10
```

Defined in h1os/orch_state.h:97

State of Charge at start of discharge lap in tenths of % (0..1000).

---

{#reserved}

#### reserved

```cpp
uint16_t reserved
```

Defined in h1os/orch_state.h:98

16-bit alignment padding / reserved.

{#h1os_presentation_config_t}

## h1os_presentation_config_t

```cpp
#include <h1os/h1os.h>
```

```cpp
struct h1os_presentation_config_t
```

Defined in h1os/h1os.h:178

Presentation splash, audio chime, and master volume configuration.

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

Defined in h1os/h1os.h:179

Presentation splash screen rendering hook.

---

{#on_chime}

#### on_chime

```cpp
h1os_chime_cb_t on_chime
```

Type: [`h1os_chime_cb_t`](#h1os_chime_cb_t)

Defined in h1os/h1os.h:180

Presentation chime playback hook.

---

{#chime_mask}

#### chime_mask

```cpp
uint8_t chime_mask
```

Defined in h1os/h1os.h:181

Bitmask of enabled audio chime types.

---

{#volume_pct}

#### volume_pct

```cpp
uint8_t volume_pct
```

Defined in h1os/h1os.h:182

Acoustic presentation master volume (0..100%).

Generated by [Moxygen](https://0state.com/moxygen)