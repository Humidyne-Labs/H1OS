# Solomon Systech SSD1681 1.54" E-Paper Display Subsystem

## 1. Physical Specifications & Hardware Architecture
- **Display Panel:** 1.54-inch Monochrome Active Matrix E-Paper Display (200x200 resolution)
- **Controller IC:** Solomon Systech SSD1681
- **Bus Interface:** 4-Wire SPI (Mode 0: CPOL=0, CPHA=0) on `SPI2_HOST`
  - SPI SCK: `GPIO 12`
  - SPI MOSI / SDA: `GPIO 13` (Bidirectional data line)
  - Chip Select (CS#): `GPIO 11` (Active LOW)
  - Data / Command (D/C#): `GPIO 10` (LOW = Command, HIGH = Data)
  - Hardware Reset (RST#): `GPIO 9` (Active LOW)
  - Controller Busy (BUSY): `GPIO 8` (Active HIGH: `1 = Panel Refreshing / Busy`, `0 = Idle / Ready`)
- **Power Rail:** `EPD_3V3_EN` (`GPIO 6`, Active LOW: `0 = ON`, `1 = OFF`).
- **Framebuffer Dimensions:** $200 \times 200 \text{ pixels} \div 8 \text{ bits/byte} = 5,000 \text{ bytes}$ (1-bit monochrome: `0 = Black`, `1 = White`).

---

## 2. SPI Timing, Speeds & Multi-Device Configuration

The SSD1681 uses two distinct SPI device configurations on `SPI2_HOST`:
1. **Transmit (Write) Handle (20 MHz SPI Master DMA):**
   - Clock Speed: **20 MHz**
   - Mode: 0 (CPOL=0, CPHA=0)
   - CS Pin: Manual software control or hardware CS
   - Max Transfer: 5,008 bytes (Full 5,000-byte framebuffer in a single DMA burst)
2. **Read Handle (2 MHz Half-Duplex 3-Wire SPI):**
   - Clock Speed: **2 MHz**
   - Flags: `SPI_DEVICE_HALFDUPLEX | SPI_DEVICE_3WIRE`
   - Purpose: Reading on-glass temperature sensor from bidirectional SDA pin (`GPIO 13`).

---

## 3. SSD1681 Register Map & Commands

| Register Address | Command Name | Description | Parameters / Payload |
|---|---|---|---|
| **0x01** | `DRIVER_OUTPUT_CONTROL` | Configures multiplexer line count | 3 Bytes: `[0xC7, 0x00, 0x00]` (200 Mux lines) |
| **0x03** | `GATE_VOLTAGE_CONTROL` | Gate driving voltage | 1 Byte: `0x17` (+19V / -19V) |
| **0x04** | `SOURCE_VOLTAGE_CONTROL` | Source driving voltages (VSH1, VSH2, VSL) | 3 Bytes: `[0x41, 0xB0, 0x32]` |
| **0x10** | `DEEP_SLEEP_MODE` | Enters deep sleep | 1 Byte: `0x01` (Mode 1: RAM retained, Iq ~ 1.0 µA) |
| **0x11** | `DATA_ENTRY_MODE` | RAM address counter auto-increment | 1 Byte: `0x03` (X increment, Y increment) |
| **0x12** | `SW_RESET` | Software reset | None. Requires `wait_busy()`. |
| **0x18** | `TEMP_SENSOR_SELECTION` | Selects internal thermal sensor | 1 Byte: `0x80` (Internal sensor) |
| **0x1B** | `TEMP_SENSOR_READ` | Reads 2-byte calibrated on-glass temperature | Read 2 Bytes: `[temp_int, temp_frac]` |
| **0x20** | `MASTER_ACTIVATION` | Triggers display update execution | None. Requires `wait_busy()`. |
| **0x22** | `DISPLAY_UPDATE_CONTROL_2` | Refresh sequence selection | `0xB1` (Load Clock/Temp)<br>`0xC7` / `0xF7` (Full Refresh)<br>`0xCF` (Partial Refresh) |
| **0x24** | `WRITE_RAM_NEW` | Writes New Frame to display RAM | 5,000 Bytes |
| **0x26** | `WRITE_RAM_OLD` | Writes Previous Frame to shadow RAM | 5,000 Bytes |
| **0x2C** | `VCOM_VOLTAGE_CONTROL` | Sets VCOM driving voltage | 1 Byte: `0x28` (-1.0V) |
| **0x32** | `WRITE_LUT_REGISTER` | Custom waveform LUT payload | 153 Bytes (`WF_PARTIAL_1IN54[0..152]`) |
| **0x37** | `DISPLAY_OPTION` | Partial Ping-Pong scan options | 10 Bytes: `[0, 0, 0, 0, 0, 0x40, 0, 0, 0, 0]` |
| **0x3C** | `BORDER_WAVEFORM_CONTROL` | Border pin driving waveform | 1 Byte: `0x05` (Full OTP), `0x80` (Partial LUT0 Floating) |
| **0x3F** | `EOPT_REGISTER` | End of frame pulse control | 1 Byte: `0x02` (`WF_PARTIAL_1IN54[153]`) |
| **0x44** | `SET_RAM_X_WINDOW` | RAM X start/end bytes | 2 Bytes: `[0x00, 0x18]` (0 to 24 = 25 bytes = 200 pixels) |
| **0x45** | `SET_RAM_Y_WINDOW` | RAM Y start/end lines | 4 Bytes: `[0x00, 0x00, 0xC7, 0x00]` (0 to 199 lines) |
| **0x4E** | `SET_RAM_X_COUNTER` | RAM X initial address counter | 1 Byte: `0x00` |
| **0x4F** | `SET_RAM_Y_COUNTER` | RAM Y initial address counter | 2 Bytes: `[0x00, 0x00]` |

---

## 4. The 159-Byte Partial LUT Multi-Register Split

The 159-byte partial refresh waveform `WF_PARTIAL_1IN54` cannot be written into a single register. The Solomon Systech SSD1681 requires it to be partitioned across **five distinct configuration registers**:

```c
void epd_load_custom_lut(const uint8_t *lut_buffer) {
    // 1. Core Look-Up Tables 0-4, Timing Groups 0-11, and Frame Rates (153 bytes)
    hal_spi_write_cmd(0x32);
    hal_spi_write_data(&lut_buffer[0], 153);

    // 2. End of Frame Pulse Timing (EOPT) (1 byte)
    hal_spi_write_cmd(0x3F);
    hal_spi_write_data(&lut_buffer[153], 1);

    // 3. Gate Driving Voltage (1 byte)
    hal_spi_write_cmd(0x03);
    hal_spi_write_data(&lut_buffer[154], 1);

    // 4. Source Driving Voltages (VSH1, VSH2, VSL) (3 bytes)
    hal_spi_write_cmd(0x04);
    hal_spi_write_data(&lut_buffer[155], 3);

    // 5. VCOM Modulation Voltage (1 byte)
    hal_spi_write_cmd(0x2C);
    hal_spi_write_data(&lut_buffer[158], 1);
}
```

---

## 5. Differential Ping-Pong Refresh Sequence

To update the display in **~300 ms without full-screen flashing**:
1. Write updated framebuffer to `0x24` (New RAM).
2. **DO NOT OVERWRITE** `0x26` (Old RAM)! The controller physically compares RAM `0x24` against RAM `0x26` to apply electrostatic pulses only to pixels that change state.
3. Call `epd_load_custom_lut(WF_PARTIAL_1IN54)`.
4. Configure Display Option: Write 10 bytes `[0, 0, 0, 0, 0, 0x40, 0, 0, 0, 0]` to `0x37`.
5. Set Border Waveform: Write `0x80` to `0x3C` (Border floating).
6. Trigger Update: Write `0xCF` to `0x22`, then `0x20` (Master Activation).
7. Wait for BUSY pin low.
8. Synchronize local software shadow buffer (`memcpy(s_prev, s_curr, 5000)`).

---

## 6. On-Glass Temperature Sensor Readout (Command 0x1B)

The SSD1681 includes an internal on-glass thermistor used to compensate electrophoretic pigment viscosity.

### Invariant: Continuous CS# Hold
Under 4-wire SPI on the SSD1681, **CS# must remain held LOW continuously** across both the Command Phase and Data Read Phase:
```
CS#  ──┐                                                        ┌──
       └────────────────────────────────────────────────────────┘
       │ <──── Command Phase ────> │ <───── Read Phase ───────> │
DC#  ──┐                           ┌───────────────────────────────
       └───────────────────────────┘
MOSI ───[ 0x1B: Read Temp Cmd ]───► ───[ High-Z / Input ]─────────
MISO ───[ Tristate ]──────────────► ───[ Byte 0: Int ][ Byte 1: Frac ]──
```

### Mathematical Decoding
```c
int8_t temp_int   = (int8_t)raw_bytes[0];
float  temp_frac  = (raw_bytes[1] & 0x80) ? 0.5f : 0.0f;
float  glass_temp = (float)temp_int + ((temp_int >= 0) ? temp_frac : -temp_frac);
```

---

## 7. Deep Sleep Mode 1 & Wakeup Procedures

### Entry Procedure
1. Wait for panel idle: `sub_display_wait_busy()`.
2. Send Command `0x10`, data `0x01` (Deep Sleep Mode 1).
3. The display enters ultra-low power standby (<1.0 µA) with RAM contents retained.

### Wakeup Procedure
1. Hardware Reset Pulse on `RST#` (`GPIO 9`): 10 ms HIGH, 10 ms LOW, 10 ms HIGH.
2. Software Reset: Command `0x12` + wait busy.
3. Re-apply core registers (`0x01`, `0x11`, `0x44`, `0x45`, `0x3C`, `0x22 0xB1`, `0x20`).
4. If waking from deep sleep, pre-synchronize shadow RAM (`0x26`) with the frame restored from flash so differential updates resume seamlessly!
