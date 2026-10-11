# Layer 1: Hardware Abstraction Layer (HAL) Specification

## 1. Overview
Layer 1 is the lowest layer of the Clean-Slate BSP. It is written in pure C, interacts directly with the ESP-IDF hardware drivers, and enforces the following architectural invariant:
> **Layer 1 contains ZERO application state, ZERO math logic, and ZERO power-management decisions.** It exposes stateless, thread-safe primitives to Layer 2 and Layer 3.

---

## 2. File Manifest

| File | Purpose | Key Responsibilities |
| :--- | :--- | :--- |
| `hal_types.h` | Base Types & Constants | Pinout definitions, bitmasks, common result codes (`esp_err_t`). |
| `hal_io.c/.h` | GPIO & Pad Control | Power latch lock, EPD power switch, RTC pad hold/unhold. |
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
#define HAL_PIN_POWER_HOLD     17  // BAT_CTRL: High = LDO enabled
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
#define HAL_PIN_STATUS_LED      3  // Open-Drain, Active LOW (0 = ON, 1 = OFF)

// Flash Partition Constants
#define HAL_PARTITION_EPD_FRAME "epd_frame"
#define HAL_EPD_FRAME_SIZE_BYTES 5000
```

---

### 3.2 `hal_io.c/.h` (Base Pin & Power Rail Hardware Driver)
- **Power Rail Policy (Keep Gates Open - Zero Glitch Strategy)**:
  - Both `GPIO 17` (`BAT_CTRL` = 1, LDO on) and `GPIO 6` (`EPD_3V3_EN` = 0, Active LOW = rail ON) remain **permanently asserted and latched with RTC pad holds** (`rtc_gpio_hold_en`).
  - **Rationale:** Hard-cutting power rails causes ESD diode bus clamping on the ES8311, risks POR state loss on the PCF85063A RTC, and adds capacitor recharge inrush spikes. Because all onboard ICs possess native sub-microamp sleep modes (Total rail draw is only ~9.0 µA), keeping all rails energized eliminates all bus instability while maintaining maximum battery endurance.
- **Parasitic Leakage Isolation Protocol (Deep Sleep Pad State)**:
  Before entering deep sleep, `hal_io` configures and locks all lines subject to parasitic leakage:
  1. **EPD Interface Isolation:** Latches `GPIO 11 (EPD_CS)` HIGH and `GPIO 9 (EPD_RST)` HIGH via `gpio_hold_en()` to prevent floating line leakage through SSD1681 input gates.
  2. **Audio Power Amplifier Cut:** Drives `GPIO 42 (PA_EN)` HIGH (cut power) and `GPIO 46 (PA_CTRL)` LOW (mute/standby) to eliminate the NS4168 Class-D amplifier's 5–8 mA idle burn.
  3. **MicroSD Card Bus Protection:** Sets `GPIO 39-41` (SD CLK, MISO, MOSI) to High-Z with internal pull-ups enabled to prevent SD card negotiation leakage.
  4. **Charger STAT Pin:** Sets ETA6098 `STAT` pin to High-Z with internal pull-ups disabled (`gpio_pullup_dis`) during battery operation.
- **Early Boot Initialization (`hal_io_early_init`)**:
  - Releases RTC pad holds on tactile buttons and RTC interrupt line.
  - Re-asserts `GPIO 17` (`BAT_CTRL`) HIGH and `GPIO 6` (`EPD_3V3_EN`) LOW immediately to ensure seamless power delivery during wake transitions.
  - Ensures `PA_EN` (GPIO 42) remains HIGH and `PA_CTRL` (GPIO 46) remains LOW until audio is explicitly requested.

```c
esp_err_t hal_io_early_init(void);
esp_err_t hal_io_lock_power_latch(bool enable);
esp_err_t hal_io_set_sensor_rail(bool enable);
esp_err_t hal_io_isolate_sleep_pads(void);
esp_err_t hal_io_release_pad_holds(void);
esp_err_t hal_io_configure_button_pins(void);
```

---

### 3.3 `hal_i2c.c/.h` (Mutex-Protected I2C Master Bus)
- Utilizes ESP-IDF Driver V2 (`i2c_master_bus_handle_t`).
- Protects the physical bus (`GPIO 47` SDA / `GPIO 48` SCL) across multiple FreeRTOS tasks with a recursive mutex (`SemaphoreHandle_t`).
- Provides atomic register-level write-read transactions with configurable timeouts.

```c
esp_err_t hal_i2c_bus_init(void);
esp_err_t hal_i2c_bus_deinit(void);

// Atomic primitives with mutex acquisition
esp_err_t hal_i2c_write(uint8_t dev_addr, const uint8_t *data, size_t len, TickType_t timeout);
esp_err_t hal_i2c_read(uint8_t dev_addr, uint8_t *data, size_t len, TickType_t timeout);
esp_err_t hal_i2c_write_reg(uint8_t dev_addr, uint8_t reg, const uint8_t *data, size_t len, TickType_t timeout);
esp_err_t hal_i2c_read_reg(uint8_t dev_addr, uint8_t reg, uint8_t *data, size_t len, TickType_t timeout);
```

---

### 3.4 `hal_spi.c/.h` (DMA Display SPI Master Bus)
- Configured for SSD1681 display controller.
- Dedicated hardware handles for:
  - High-speed transmission (20 MHz, Mode 0, DMA Channel Auto) for display pixel memory updates.
  - Half-duplex 3-wire read (2 MHz, Mode 0, SDA read) for reading on-glass temperature sensor (Command `0x1B`).
- Synchronous polling transmission prevents context-switch overhead during byte-by-byte command streaming.

```c
esp_err_t hal_spi_bus_init(void);
esp_err_t hal_spi_bus_deinit(void);

esp_err_t hal_spi_write_cmd(uint8_t cmd);
esp_err_t hal_spi_write_data(const uint8_t *data, size_t len);
esp_err_t hal_spi_read_half_duplex(uint8_t cmd, uint8_t *rx_buf, size_t rx_len);
```

---

### 3.5 `hal_flash.c/.h` (Flash Partition Storage)
- Clean wrapper around `esp_partition` APIs.
- Bounds checking ensures operations never escape partition borders.
- Enforces SPI Flash sector alignment (4096-byte boundaries for erase cycles).

```c
esp_err_t hal_flash_read(const char *partition_name, uint32_t offset, void *dest, size_t len);
esp_err_t hal_flash_write(const char *partition_name, uint32_t offset, const void *src, size_t len);
esp_err_t hal_flash_erase(const char *partition_name, uint32_t offset, size_t size);
```

---

## 4. Hardware Failure Safeguards
1. **Bus Lockup Recovery**: If SDA is held LOW by a crashed peripheral during reset, `hal_i2c_bus_init()` emits 9 clock pulses on SCL with a STOP condition to force slave unlatch.
2. **Flash Wear Minimization**: Write operations reject duplicate writes by hashing or caching clean dirty bits in Layer 3.
