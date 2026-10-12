# Sensirion SHTC3 Digital Temperature & Humidity Sensor

## 1. Physical Specifications & Bus Configuration
- **Manufacturer / IC:** Sensirion SHTC3
- **Bus Interface:** Shared Master I2C (`I2C_NUM_0`)
- **7-Bit Slave Address:** `0x70` (Fixed)
- **Bus Speed:** 400 kHz Fast-Mode
- **Pull-ups:** Hardware external 4.7 kΩ pull-ups to 3.3V on `GPIO 47` (SDA) and `GPIO 48` (SCL)
- **Power Rail:** Powered from `EPD_3V3_EN` (`GPIO 6`, Active LOW). Stays energized across deep sleep.

---

## 2. Command Set & Timing Requirements

The SHTC3 is a stateless, low-power environmental sensor that operates using 16-bit command codes transmitted MSB first:

| Command Name | 16-Bit Hex Code | Payload Transmitted | Required Post-Command Delay | Description |
|---|---|---|---|---|
| **WAKEUP** | `0x3517` | `[0x35, 0x17]` | **250 µs** (`esp_rom_delay_us(250)`) | Transitions sensor from sleep mode (<0.2 µA) to idle ready state. |
| **SLEEP** | `0xB098` | `[0xB0, 0x98]` | None (instantaneous) | Puts sensor into ultra-low-power sleep mode to prevent self-heating. |
| **READ_ID** | `0xEFC8` | `[0xEF, 0xC8]` | None | Reads 3 bytes: 2-byte Product ID + 1-byte CRC. Mask `0x0847`. |
| **SOFT_RESET** | `0x805D` | `[0x80, 0x5D]` | **200 µs** | Reinitializes digital control logic. |
| **MEAS_NORMAL_T_FIRST** | `0x7866` | `[0x78, 0x66]` | **15 ms** (`pdMS_TO_TICKS(15) + 1`) | Normal precision measurement (Temperature read first). Clock stretching disabled. |
| **MEAS_LOWPWR_T_FIRST** | `0x609C` | `[0x60, 0x9C]` | **1000 µs** (`esp_rom_delay_us(1000)`) | Low-power fast measurement (~1 ms). Clock stretching disabled. |

---

## 3. Readout Sequence & Payload Format

The SHTC3 readout sequence is strictly:
```
[I2C WAKE (0x3517)] ──> [Delay 250 µs] ──> [I2C MEAS (0x7866 / 0x609C)] ──> [Delay 15ms / 1ms]
       │
       ▼
[I2C READ 6 Bytes] ──> [I2C SLEEP (0xB098)] ──> [Verify CRC-8]
```

### 6-Byte Read Payload
When reading after a measurement command, the sensor returns 6 bytes:
- `rx_buf[0]`: Temperature MSB
- `rx_buf[1]`: Temperature LSB
- `rx_buf[2]`: Temperature CRC-8 Checksum
- `rx_buf[3]`: Relative Humidity MSB
- `rx_buf[4]`: Relative Humidity LSB
- `rx_buf[5]`: Relative Humidity CRC-8 Checksum

### Sensirion CRC-8 Algorithm
The polynomial is $x^8 + x^5 + x^4 + 1$ (`0x31`), initialized to `0xFF`:
```c
static uint8_t shtc3_calc_crc(const uint8_t *data, size_t len) {
    uint8_t crc = 0xFF;
    for (size_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (uint8_t bit = 8; bit > 0; --bit) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ 0x31;
            } else {
                crc = (crc << 1);
            }
        }
    }
    return crc;
}
```

---

## 4. Mathematical Conversion Formulas

### Floating-Point Conversion (Standard)
$$\text{Temperature } [^\circ\text{C}] = -45.0 + 175.0 \times \left(\frac{S_T}{2^{16} - 1}\right)$$
$$\text{Relative Humidity } [\%] = 100.0 \times \left(\frac{S_{RH}}{2^{16} - 1}\right)$$
Where $S_T = \text{raw\_temp}$ and $S_{RH} = \text{raw\_rh}$.

### Fixed-Point Centi-Unit Conversion (Integer Math for ULP / Wake Stub)
$$\text{Temp Centi-Deg } [0.01^\circ\text{C}] = -4500 + \frac{17500 \times S_T}{65535}$$
$$\text{RH Centi-Pct } [0.01\%] = \frac{10000 \times S_{RH}}{65535}$$

---

## 5. Audit & Translation Verification

| Parameter / Feature | Legacy Reference (`bsp_sensors.c`) | Clean-Slate (`sub_sensor.c` & `orch_wake_stub.c`) | Status |
|---|---|---|---|
| I2C Address | `0x70` | `HAL_I2C_ADDR_SHTC3` (`0x70`) | **PASS** |
| Wake Command | `0x3517` + 250 µs delay | `0x3517` + 250 µs delay | **PASS** |
| Normal Meas Command | `0x7866` + 15 ms delay | `0x7866` + 15 ms delay | **PASS** |
| Low Power Command | `0x609C` + 1000 µs delay | `0x609C` + 1000 µs delay | **PASS** |
| Sleep Command | `0xB098` (Sent immediately after read) | `0xB098` (Sent immediately after read) | **PASS** |
| CRC-8 Polynomial | `0x31` (Init `0xFF`) | `0x31` (Init `0xFF`) | **PASS** |
| Self-Heating Mitigation | Sleeps sensor immediately after readout | Sleeps sensor immediately after readout | **PASS** |
| ULP / Wake Stub Math | Fixed-point integer math | RTC Fast Memory wake stub integer math | **PASS** |
