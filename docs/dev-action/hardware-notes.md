# Part I

The estimated baseline idle current for this setup during full deep sleep is **9 µA to 12 µA** at the 3.3V silicon rail (at 25°C), expanding to **12 µA to 20 µA** at the board level when powered through a dedicated ultra-low quiescent current ($I_Q$) regulator.

### Component Current Breakdown

| **IC / Peripheral**      | **Operating Mode**                                             | **Typical Current (Ityp​)**        | **Max / Operating Conditions**                                                                                           |
| ------------------------ | -------------------------------------------------------------- | --------------------------------- | ------------------------------------------------------------------------------------------------------------------------ |
| **ESP32-S3**             | Deep Sleep (RTC slow memory powered, ULP halted)<br><br><br>   | 7.0 µA<br><br><br>                | 8.0 µA if RTC peripherals remain powered up. Modules with un-gated Octal PSRAM add 15–30 µA standby leakage.<br><br><br> |
| **ES8311**               | Power-Down Mode (Control register `0x0D` sequence)<br><br><br> | < 1.0 µA (0.0 µA typ)<br><br><br> | Validated with MCLK, SCLK, and LRCK clocks stopped.<br><br><br>                                                          |
| **PCF85063A**            | Running (32.768 kHz quartz active, interface idle)<br><br><br> | 0.22 µA (220 nA)<br><br><br>      | 0.45 µA max at 25°C; requires CLKOUT disabled (`COF[2:0] = 111`).<br><br><br>                                            |
| **SSD1681**              | Deep Sleep Mode 1 (Command `0x10, 0x01`)<br><br><br>           | 1.0 µA<br><br><br>                | 2.0 µA max; maintains display state and RAM retention. Requires HW reset to exit.<br><br><br>                            |
| **SHTC3** *(if present)* | Sleep Mode (Command `0xB098`)<br><br><br>                      | 0.3 µA<br><br><br>                | 0.6 µA max; requires wake-up command `0x3517` before I2C access.<br><br><br>                                             |

### Hardware Modifiers & Parasitic Leakage Vectors

- **LDO Quiescent Current ($I_Q$):** An ultra-low $I_Q$ regulator (such as an RT9080 or TPS7A02) contributes 1.5 µA to 3 µA. Standard development board regulators (such as the AP2112K or ME6211) consume 40 µA to 55 µA of continuous quiescent current regardless of downstream sleep states.

- **I2C Bus State (GPIO 47 / 48):** Lines must remain pulled high to 3.3V via external $10\ \text{k}\Omega$ resistors. Because all devices release the open-drain lines in sleep, quiescent current through the pull-ups is 0 µA.

- **SSD1681 SPI Pin Retention:** The display `CS` must be latched HIGH and `RST` must be latched HIGH via RTC/digital pad hold before sleep. A floating `CS` pin allows parasitic current to drain through the display controller's internal interface clamping network.

- **ES8311 I2S Bus Isolation:** MCLK, BCLK, and WS signals must be set to High-Z or held low. Leaving any digital audio clock line high-impedance floating can float the input gates of the codec, causing leakage into $PVDD$.

### Pre-Sleep Firmware Verification Checklist

1. **Gate the PCF85063A CLKOUT Pin:** Confirm bits `COF[2:0]` in register `0x01` (`Control_2`) are set to `111` to eliminate the active push-pull clock output.

2. **Commit SSD1681 to Mode 1:** Transmit `0x10, 0x01` over SPI, poll `BUSY` until high-level completion clears, and hold `CS` and `RESET` high using `gpio_hold_en()`.

3. **Power Down the ES8311:** Execute the software standby power-down sequence via register `0x0D`, verify the write ACK, and stop the ESP-IDF I2S master clock driver.

4. **Put Environmental Sensors to Sleep:** If using the SHTC3, dispatch `0xB098` over I2C prior to terminating the bus.

5. **Isolate Digital Pads:** Enable `gpio_deep_sleep_hold_en()` on active SPI/I2C GPIOs to prevent line floating during core regulator shutdown.

6. **Enter Deep Sleep:** Invoke `esp_deep_sleep_start()` with wakeup configured exclusively via external RTC interrupt or timer.

# Part II

Accounting for the **ETA6098** charger and **MP1605** buck converter, total system idle current drawn from the battery ($V_{BAT}$ at 3.7V to 4.2V) increases to an estimated **21 µA to 28 µA typical**, while the regulated 3.3V rail itself will see approximately **12 µA to 16 µA**.

### System Power Architecture Breakdown

| **Rail / Domain**            | **Component**       | **Operating State**                                   | **Typical Current (Ityp​)**            | **Design Considerations**                                                                                                                         |
| ---------------------------- | ------------------- | ----------------------------------------------------- | ------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Battery Rail ($V_{BAT}$)** | **ETA6098**         | Quiescent / Battery Leakage ($V_{IN}$ unpowered)      | **1.0 µA**<br><br><br><br><br><br>    | Quiescent drain into the `BAT`/`BATS` pins when running solely from battery power.<br><br><br>                                                    |
| **Battery Rail ($V_{BAT}$)** | **MP1605**          | Active PFM Buck Conversion ($V_{IN} \to 3.3\text{V}$) | **19 µA – 26 µA**                     | Combines the IC base quiescent current ($I_Q \approx 11\ \mu\text{A}$) with light-load PFM conversion pulses servicing the 3.3V rail.<br><br><br> |
| **3.3V Rail (Load)**         | **ESP32-S3**        | Deep Sleep (RTC Slow Memory retained)                 | **7.0 µA**<br><br><br><br><br><br>    | ULP halted, main digital domains power-gated.<br><br><br>                                                                                         |
| **3.3V Rail (Load)**         | **ES8311**          | Software Power-Down Mode                              | **< 1.0 µA** (0.0 µA typ)<br><br><br> | Audio clocks gated; register `0x0D` power-down confirmed.<br><br><br>                                                                             |
| **3.3V Rail (Load)**         | **PCF85063A**       | Active Timekeeping (32.768 kHz)                       | **0.22 µA** (220 nA)<br><br><br>      | `CLKOUT` disabled (`COF[2:0] = 111`).<br><br><br>                                                                                                 |
| **3.3V Rail (Load)**         | **SSD1681**         | Deep Sleep Mode 1                                     | **1.0 µA**<br><br><br><br><br><br>    | RAM maintained; `CS` and `RESET` held high.<br><br><br>                                                                                           |
| **3.3V Rail (Load)**         | **SHTC3**           | Sleep Mode                                            | **0.3 µA**<br><br><br><br><br><br>    | Put into sleep via command `0xB098`.<br><br><br>                                                                                                  |
| **3.3V Rail (Load)**         | **MP1605 Feedback** | Resistor Ladder Ground Leakage                        | **3.0 µA – 6.0 µA**                   | Continuous drain through the $R_1 + R_2$ feedback divider network.                                                                                |

### Key Loss Vectors & Design Factors

- **MP1605 Feedback Divider Sizing:** ~~With the MP1605 reference voltage fixed at $V_{FB} = 0.6\text{V}$, the output voltage follows $V_{OUT} = 0.6\text{V} \times (1 + R_1 / R_2)$. Using typical low values (e.g., $R_1 = 450\text{ k}\Omega, R_2 = 100\text{ k}\Omega$) consumes $6\ \mu\text{A}$ continuously. Scaling to $R_1 \approx 900\text{ k}\Omega$ and $R_2 \approx 200\text{ k}\Omega$ limits divider bleed to $\approx 3\ \mu\text{A}$ without compromising stability.~~ Actual divider network values are $\approx 200\text{ k}\Omega$ and $\approx 44.2\text{ k}\Omega$.

- **Buck Converter PFM Light-Load Behavior:** At microamp load levels, the MP1605 operates in Advanced Asynchronous Modulation (AAM) pulse-skipping mode. Supplying $\approx 12.5\ \mu\text{A}$ of downstream 3.3V power from a 3.8V battery at $\approx 70\text{–}75\%$ light-load efficiency adds $\approx 7.5\ \mu\text{A}$ to the input draw, which sums directly with the internal $11\ \mu\text{A}$ $I_Q$ floor.

- **ETA6098 `STAT` Pin Leakage:** The open-drain `STAT` pin must not be pulled up to the 3.3V rail if that rail remains powered during battery-only operation. If pulled high to $V_{BAT}$ through a standard resistor, verify the downstream monitoring pin is high-impedance to avoid a path to ground.

### Implementation Verification Checklist

1. **Calculate MP1605 Divider Values:** Confirm $R_1 + R_2 \ge 1\text{ M}\Omega$ (e.g., $909\text{ k}\Omega$ and $200\text{ k}\Omega$ for 3.32V) to cap resistor leakage under $3.3\ \mu\text{A}$.

2. **Isolate Charger Monitoring Lines:** Set the ESP32-S3 GPIO monitoring ETA6098 `STAT` to High-Z input with internal pull-ups disabled (`gpio_pullup_dis`) prior to sleep.

3. **Latch Peripheral Control Lines:** Call `gpio_hold_en()` on the SSD1681 `CS` and `RESET` lines, and confirm $10\ \text{k}\Omega$ bus pull-ups on the shared I2C lines (GPIO 47/48) are referenced directly to the 3.3V rail.

4. **Bench Measurement:** Measure at the battery series lead using a precision current meter (or Nordic PPK2) at $V_{BAT} = 3.8\text{V}$; steady-state current should settle between $22\ \mu\text{A}$ and $27\ \mu\text{A}$.

# Part III

TBD
