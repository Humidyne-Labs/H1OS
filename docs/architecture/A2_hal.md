# Layer 1: Hardware Abstraction Layer (HAL) Specification

## 1. Overview
Layer 1 is the lowest layer of H1OS. It is written in pure C, interacts directly with the ESP-IDF hardware drivers, and enforces the following architectural invariant:
> **Layer 1 contains ZERO application state, ZERO math logic, and ZERO power-management decisions.** It exposes stateless primitives ("How the thing gets done") to Layer 2 and Layer 3 by directly poking hardware registers.

---

## 2. File Manifest

| File | Purpose | Key Responsibilities |
| :--- | :--- | :--- |
| `hal_types.h` | Base Types & Constants | Pinout definitions, bitmasks, shared enums (`hal_btn_mask_t`, `h1os_wake_btn_t`, `h1os_chime_type_t`, `sys_clk_mode_t`). |
| `hal_io.c/.h` | GPIO, LEDC PWM & Pad Control | Pad holds, power latch release, LEDC hardware PWM/breathing on GPIO 3, stateless button reading, USB SOF check. |
| `hal_i2c.c/.h` | Shared I2C Bus Master | Mutex-protected bus transactions with cached peripheral device handles. |
| `hal_spi.c/.h` | EPD SPI Master Bus | Fast DMA transfers (20 MHz write), 3-wire half-duplex read (2 MHz). |
| `hal_flash.c/.h`| Raw Partition Storage | Sector erase, raw partition read/write (`epd_frame`). |

---

## 3. Component Details & API Signatures

### 3.1 `hal_types.h`
Defines all hardware fixed constants and base enums for the Waveshare ESP32-S3 ePaper 1.54" V2 board:
```c
#pragma once
#include "driver/gpio.h"
#include "esp_err.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/* Power & Sensing Rails */
#define HAL_PIN_POWER_HOLD     GPIO_NUM_17 // Master LDO Power Latch (BAT_CTRL): Active HIGH
#define HAL_PIN_BATTERY_ADC    GPIO_NUM_4  // Battery Voltage Sensing: ADC1_CHANNEL_3 (1:2 divider: 200k / 200k)
#define HAL_PIN_STATUS_LED     GPIO_NUM_3  // User LED: Open-Drain, Active LOW (0 = ON, 1 = OFF)

/* Input Buttons */
#define HAL_PIN_BUTTON_BOOT    GPIO_NUM_0  // Hardware BOOT0 Key: Active LOW (external 10k pullup on PCB)
#define HAL_PIN_BUTTON_POWER   GPIO_NUM_18 // Hardware BAT_KEY: Active LOW (external 10k pullup on PCB)

/* Shared I2C Master Bus */
#define HAL_PIN_I2C_SDA        GPIO_NUM_47 // Shared I2C Serial Data (SHTC3, PCF85063, ES8311)
#define HAL_PIN_I2C_SCL        GPIO_NUM_48 // Shared I2C Serial Clock (400 kHz)
#define HAL_PIN_RTC_INT        GPIO_NUM_5  // PCF85063A INT: Open-Drain (internal pullup mandatory)

/* Monochrome E-Paper Display (SSD1681) */
#define HAL_PIN_EPD_3V3_EN     GPIO_NUM_6  // EPD 3.3V Rail Gate: Active LOW (0 = Rail ON)
#define HAL_PIN_EPD_BUSY       GPIO_NUM_8  // Display Busy Line: Active HIGH (1 = Busy, 0 = Idle)
#define HAL_PIN_EPD_RST        GPIO_NUM_9  // Display Hardware Reset: Active LOW
#define HAL_PIN_EPD_DC         GPIO_NUM_10 // Display Data / Command: 0 = Cmd, 1 = Data
#define HAL_PIN_EPD_CS         GPIO_NUM_11 // Display SPI Chip Select: Active LOW
#define HAL_PIN_EPD_SCK        GPIO_NUM_12 // Display SPI Serial Clock (up to 20MHz)
#define HAL_PIN_EPD_MOSI       GPIO_NUM_13 // Display SPI Master Out Slave In

/* Audio Subsystem (ES8311 + NS4168) */
#define HAL_PIN_PA_EN          GPIO_NUM_42 // Amp Power Gate: Active LOW (1 = Power Cut, 0 = ON)
#define HAL_PIN_PA_CTRL        GPIO_NUM_46 // Amp Standby/Mute: Active HIGH (0 = Mute, 1 = Enable)
#define HAL_PIN_I2S_MCLK       GPIO_NUM_14 // Master Clock (256 * Fs)
#define HAL_PIN_I2S_SCLK       GPIO_NUM_15 // Bit / Serial Clock
#define HAL_PIN_I2S_ASDOUT     GPIO_NUM_16 // Codec Audio Out to ESP32 (DIN)
#define HAL_PIN_I2S_LRCK       GPIO_NUM_38 // Word Select / Frame Sync (WS)
#define HAL_PIN_I2S_DSDIN      GPIO_NUM_45 // ESP32 Audio Out to Codec (DOUT)

/* MicroSD Card (SDMMC 1-Bit Mode, external pullups, no CD pin wired) */
#define HAL_PIN_SD_CLK         GPIO_NUM_39 // MicroSD Clock
#define HAL_PIN_SD_MISO        GPIO_NUM_40 // MicroSD MISO / D0
#define HAL_PIN_SD_MOSI        GPIO_NUM_41 // MicroSD MOSI / CMD

/* Flash Partitions & Display Geometry */
#define HAL_PARTITION_EPD_FRAME  "epd_frame"
#define HAL_EPD_WIDTH_PX         200
#define HAL_EPD_HEIGHT_PX        200
#define HAL_EPD_FRAME_SIZE_BYTES 5000
```

---

### 3.2 `hal_io.c/.h` (Base Pin, Pad Hold & Power Latch Hardware Driver)

- **Power Latch Rule (Bootloader Ownership):**
  - `GPIO 17` (`BAT_CTRL` = 1, LDO on) is asserted in the **2nd-stage bootloader hook** (`h1os_boot_hook`) and locked with RTC IO pad holds (`RTC_CNTL_PAD_HOLD_REG`).
  - `hal_io` never decides when to power on. Its sole responsibility regarding power latching is providing `hal_io_release_power_latch()` when an orderly shutdown is executed.
- **Power Rail Policy (Keep Gates Open - Zero Glitch Strategy):**
  - Both `GPIO 17` (`BAT_CTRL` = 1) and `GPIO 6` (`EPD_3V3_EN` = 0, Active LOW = rail ON) remain permanently asserted and latched with RTC pad holds during deep sleep.
  - `GPIO 42` (`PA_EN` = 0, rail ON) remains energized across runtime and deep sleep to prevent unpowered ES8311 from pulling down the shared I2C bus.
- **Event-Driven Button ISR, Hardware Glitch Filtering & `esp_timer` LED Pacing (`v2.4.4-dev`):**
  - `hal_io_early_init()` installs the per-pin GPIO ISR dispatcher (`gpio_install_isr_service(0)`), enables the ESP32-S3 hardware pin glitch filters (`gpio_new_pin_glitch_filter`) on `GPIO 0` (`BOOT`) and `GPIO 18` (`POWER`), and arms `GPIO_INTR_ANYEDGE` interrupts coupled to a `15 ms` one-shot `esp_timer` debounce filter (`hal_io_register_button_cb`).
  - `hal_led_start_breathing()` drives the hardware LEDC fade engine via a periodic `esp_timer` alarm (`hal_led_breath_timer_cb`) rather than a dedicated FreeRTOS polling task, saving `2 KB` of task stack and eliminating `50 ms` polling wakes.

```c
typedef void (*hal_io_button_cb_t)(hal_btn_mask_t btn_mask, void *arg);

esp_err_t      hal_io_early_init(void);
esp_err_t      hal_io_register_button_cb(hal_io_button_cb_t cb, void *arg);
esp_err_t      hal_io_set_led(bool on);
esp_err_t      hal_led_pwm_init(void);
esp_err_t      hal_led_set_brightness(uint8_t brightness_pct);
esp_err_t      hal_led_fade_to(uint8_t target_pct, uint32_t duration_ms);
esp_err_t      hal_led_start_breathing(uint32_t cycle_period_ms);
esp_err_t      hal_led_stop_breathing(void);
bool           hal_led_is_breathing(void);
esp_err_t      hal_led_pwm_deinit(void);
esp_err_t      hal_io_release_power_latch(void);
hal_btn_mask_t hal_io_read_buttons(void);
static inline bool hal_io_button_is_pressed(gpio_num_t pin);
esp_err_t      hal_io_isolate_sleep_pads(void);
esp_err_t      hal_io_release_pad_holds(void);
bool           hal_check_usb_ll(void);
```

---

### 3.3 `hal_i2c.c/.h` (Mutex-Protected I2C Master Bus)
- Utilizes ESP-IDF Driver V2 (`i2c_master_bus_handle_t`) with cached `i2c_master_dev_handle_t` handles for onboard peripherals (`0x18`, `0x51`, `0x70`) to guarantee zero runtime heap churn.
- Protects the physical bus (`GPIO 47` SDA / `GPIO 48` SCL) with a recursive mutex.
- Provides atomic register-level write, read, write-read (`Repeated START`), and bus probe transactions.

```c
esp_err_t hal_i2c_init(void);
esp_err_t hal_i2c_deinit(void);

esp_err_t hal_i2c_write(uint8_t dev_addr, const uint8_t *write_data, size_t write_len, uint32_t timeout_ms);
esp_err_t hal_i2c_read(uint8_t dev_addr, uint8_t *read_data, size_t read_len, uint32_t timeout_ms);
esp_err_t hal_i2c_write_read(uint8_t dev_addr, const uint8_t *write_data, size_t write_len, uint8_t *read_data, size_t read_len, uint32_t timeout_ms);
esp_err_t hal_i2c_probe(uint8_t dev_addr);
```

---

### 3.4 `hal_spi.c/.h` (DMA Display SPI Master Bus)
- Configured for SSD1681 display controller: 20 MHz DMA write, half-duplex 3-wire read on MOSI (2 MHz) with continuous `CS#` hold across command and read phases.

```c
esp_err_t hal_spi_init(void);
esp_err_t hal_spi_deinit(void);

esp_err_t hal_spi_write_cmd(uint8_t cmd);
esp_err_t hal_spi_write_data(const uint8_t *data, size_t len);
esp_err_t hal_spi_write_frame_dma(const uint8_t *frame_buffer);
esp_err_t hal_spi_read_data(uint8_t cmd, uint8_t *out_data, size_t len);
```

---

### 3.5 `hal_flash.c/.h` (Raw Partition Storage)
- Manages raw sector-aligned read/write operations for the 16KB `epd_frame` partition.

```c
esp_err_t hal_flash_init(void);
esp_err_t hal_flash_read_frame(uint8_t *out_buffer, size_t len);
esp_err_t hal_flash_write_frame(const uint8_t *frame_data, size_t len);
```
