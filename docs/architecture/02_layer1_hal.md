# Layer 1: Hardware Abstraction Layer (HAL) Specification

## 1. Overview
Layer 1 is the lowest layer of H1OS. It is written in pure C, interacts directly with the ESP-IDF hardware drivers, and enforces the following architectural invariant:
> **Layer 1 contains ZERO application state, ZERO math logic, and ZERO power-management decisions.** It exposes stateless primitives ("How the thing gets done") to Layer 2 and Layer 3 by directly poking hardware registers.

### Architectural Stubs Policy (The Bones Phase)
During the initial structural bring-up of H1OS, HAL driver functions may implement valid function signatures with clean return codes and null/stub bodies. This guarantees the architectural skeleton links cleanly before low-level registers are actively manipulated using [`docs/perf_and_drivers/`](file:///c:/Users/Matt/Documents/GitHub/esp32-s3_bsp/docs/perf_and_drivers/).

---

## 2. File Manifest

| File | Purpose | Key Responsibilities |
| :--- | :--- | :--- |
| `hal_types.h` | Base Types & Constants | Pinout definitions, bitmasks, common result codes (`esp_err_t`). |
| `hal_io.c/.h` | GPIO & Pad Control | Pad holds, rail switches, power latch release, stateless button pin reading. |
| `hal_i2c.c/.h` | Shared I2C Bus Master | Mutex-protected bus transactions, register reads/writes. |
| `hal_spi.c/.h` | EPD SPI Master Bus | Fast DMA transfers (20 MHz write), 3-wire read (2 MHz). |
| `hal_flash.c/.h`| Raw Partition Storage | Sector erase, raw partition read/write (`epd_frame`). |

---

## 3. Component Details & API Signatures

### 3.1 `hal_types.h`
Defines all hardware fixed constants for the Waveshare ESP32-S3 ePaper 1.54" V2 board:
```c
#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

// GPIO Pinout Mappings (Waveshare ESP32-S3 ePaper 1.54" V2 Hardware Truth)
#define HAL_PIN_POWER_HOLD     17  // BAT_CTRL: High = LDO enabled (Latched in bootloader)
#define HAL_PIN_EPD_3V3_EN      6  // EPD & Sensor Power: Active LOW (0 = ON)
#define HAL_PIN_EPD_BUSY        8  // Active HIGH (1 = Busy, 0 = Idle)
#define HAL_PIN_EPD_RST         9  // Active LOW
#define HAL_PIN_EPD_DC         10  // Push-Pull (0 = Command, 1 = Data)
#define HAL_PIN_EPD_CS         11  // Active LOW
#define HAL_PIN_EPD_SCK        12  // SPI2 SCK
#define HAL_PIN_EPD_MOSI       13  // SPI2 MOSI
#define HAL_PIN_I2C_SDA        47  // Shared I2C0 Bus (SHTC3, PCF85063, ES8311) - Ext 4.7k Pullup
#define HAL_PIN_I2C_SCL        48  // Shared I2C0 Bus (SHTC3, PCF85063, ES8311) - Ext 4.7k Pullup
#define HAL_PIN_RTC_INT         5  // PCF85063A INT (Open-drain, NO onboard pullup -> internal pullup req)
#define HAL_PIN_BATTERY_ADC     4  // ADC1_CHANNEL_3 (1:2 divider: 100k / 100k)
#define HAL_PIN_BUTTON_BOOT     0  // Active LOW (internal pullup req)
#define HAL_PIN_BUTTON_POWER   18  // Active LOW (BAT_KEY, internal pullup req)
#define HAL_PIN_PA_EN          42  // Audio Power Rail: Active LOW (0 = ON)
#define HAL_PIN_PA_CTRL        46  // Class-D Amp Shutdown: Active HIGH (0 = Muted/Standby)
#define HAL_PIN_STATUS_LED      3  // Open-Drain, Active LOW (0 = ON, 1 = OFF)

// MicroSD 1-Bit Slot Pins
#define HAL_PIN_SD_CLK         39
#define HAL_PIN_SD_MOSI        40  // CMD
#define HAL_PIN_SD_MISO        41  // D0

// Flash Partition Constants
#define HAL_PARTITION_EPD_FRAME "epd_frame"
#define HAL_EPD_FRAME_SIZE_BYTES 5000
```

---

### 3.2 `hal_io.c/.h` (Base Pin, Pad Hold & Power Latch Hardware Driver)

- **Power Latch Rule (Bootloader Ownership):**
  - `GPIO 17` (`BAT_CTRL` = 1, LDO on) is asserted in the **2nd-stage bootloader hook** (`h1os_boot_hook`) and locked with RTC IO pad holds (`rtc_gpio_hold_en`).
  - `hal_io` never decides when to power on. Its sole responsibility regarding power latching is providing `hal_io_release_power_latch()` when an orderly shutdown is executed.
- **Power Rail Policy (Keep Gates Open - Zero Glitch Strategy):**
  - Both `GPIO 17` (`BAT_CTRL` = 1) and `GPIO 6` (`EPD_3V3_EN` = 0, Active LOW = rail ON) remain permanently asserted and latched with RTC pad holds during deep sleep.
  - `GPIO 42` (`PA_EN` = 0, rail ON) remains energized while awake to prevent ES8311 ESD diode clamping on the shared I2C bus.
- **Stateless Button Reading:**
  - `hal_io` provides raw register level checks without timers, event queues, or callback tables:
    ```c
    bool hal_io_button_is_pressed(gpio_num_t pin);
    ```

```c
esp_err_t hal_io_early_init(void);
esp_err_t hal_io_release_power_latch(void);
esp_err_t hal_io_set_sensor_rail(bool enable);
esp_err_t hal_io_isolate_sleep_pads(void);
esp_err_t hal_io_release_pad_holds(void);
bool      hal_io_button_is_pressed(gpio_num_t pin);
```

---

### 3.3 `hal_i2c.c/.h` (Mutex-Protected I2C Master Bus)
- Utilizes ESP-IDF Driver V2 (`i2c_master_bus_handle_t`).
- Protects the physical bus (`GPIO 47` SDA / `GPIO 48` SCL) with a recursive mutex.
- Provides atomic register-level write-read transactions.

```c
esp_err_t hal_i2c_init(void);
esp_err_t hal_i2c_deinit(void);

esp_err_t hal_i2c_write(uint8_t dev_addr, const uint8_t *data, size_t len, TickType_t timeout);
esp_err_t hal_i2c_read(uint8_t dev_addr, uint8_t *data, size_t len, TickType_t timeout);
esp_err_t hal_i2c_write_reg(uint8_t dev_addr, uint8_t reg, const uint8_t *data, size_t len, TickType_t timeout);
esp_err_t hal_i2c_read_reg(uint8_t dev_addr, uint8_t reg, uint8_t *data, size_t len, TickType_t timeout);
```

---

### 3.4 `hal_spi.c/.h` (DMA Display SPI Master Bus)
- Configured for SSD1681 display controller: 20 MHz DMA write, half-duplex 3-wire read on MOSI (2 MHz).

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
esp_err_t hal_flash_read_frame(uint8_t *dest, size_t len);
esp_err_t hal_flash_write_frame(const uint8_t *src, size_t len);
```
