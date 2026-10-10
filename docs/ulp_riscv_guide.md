# ⚡ ESP32-S3 ULP RISC-V Environmental Co-Processor Architecture & Build Guide

**Target Hardware:** Waveshare ESP32-S3-Touch-ePaper-1.54 V2 (`ESP32-S3-PICO-1-N8R8`)  
**Core:** 32-bit RV32IMC RISC-V Coprocessor (RTC Slow SRAM)  
**Document Type:** Technical Reference & Developer Guide  

---

## 1. Overview & Operational Philosophy

The ESP32-S3 features an independent **RV32IMC 32-bit RISC-V Ultra Low Power (ULP) Coprocessor** that operates inside the RTC Slow Memory domain (`0x5000_0000` to `0x5000_1FFF`).

While the Main Dual-Core Xtensa LX7 CPU and Octal PSRAM are completely powered down in Deep Sleep ($\sim 7\dots 12\,\mu\text{A}$), the ULP Coprocessor wakes every **60 seconds** to:
1. **Evaluate the Dual-Trigger Thermal Cooldown Gate**: Monitors rate of change ($dT/dt$) across consecutive samples.
2. **Execute Ultra-Low-Power SHTC3 Sampling**: Interrogates SHTC3 over I2C in $< 1.5\text{ ms}$ at $30\,\mu\text{A}$ ($< 0.15\,\mu\text{W}$).
3. **Populate the RTC Slow Memory Ring Buffer**: Stores raw 12-byte telemetry entries into `shared_ulp_data` without waking the Main CPU.

```
                              TIMELINE & EXECUTION LIFECYCLE
                              ═══════════════════════════════

   [DEEP SLEEP: 10 µA QUIESCENT FLOOR]
   ───────────────────────────────────────────────────────────────────────────
   • Every 60s RTC Timer: ULP RISC-V Coprocessor Wakes (~30 µA, < 1.5 ms execution)
     ├── 1. Probes SHTC3 Low-Power measurement (Cmd 0x609C, waits 900 µs).
     ├── 2. Computes Fixed-Point Temperature Delta (Centi-degrees Celsius).
     ├── 3. If thermal equilibrium reached (delta <= 0.15°C or timeout elapsed):
     │      └── Latches gate open & records sample into RTC Slow RAM Ring Buffer.
     └── 4. Returns immediately to 10 µA Deep Sleep.

   [ACTIVE WAKE: SCHEDULED DISPLAY REFRESH / BUTTON]
   ───────────────────────────────────────────────────────────────────────────
   • Main CPU Wakes via PCF85063A Alarm or User Button:
     ├── 1. Reads isolated SSD1681 on-glass temperature sensor (SPI Cmd 0x1B).
     ├── 2. Reads cold quiescent telemetry history directly from RTC Slow Memory.
     ├── 3. Applies Psychrometric Engine & Invariant ambient RH reconstruction.
     ├── 4. Performs fast partial E-Paper refresh.
     └── 5. Returns to Deep Sleep.
```

---

## 2. Memory Partitioning & Shared Data Layout

ESP32-S3 contains **16 KB of total RTC SRAM**, partitioned as follows:
- **RTC Slow Memory (8 KB @ `0x5000_0000`):** Shared between Main CPU and ULP RISC-V. Holds the ULP binary, stack, and 64-entry telemetry ring buffer (`bsp_ulp_shared_mem_t`).
- **RTC Fast Memory (8 KB @ `0x600F_E000`):** Holds the 5,000-byte E-Paper Frame Buffer (`RTC_FAST_ATTR s_rtc_frame_buffer`) to prevent exhausting Slow RAM.

### Shared Memory Contract (`bsp_ulp_shared.h`)

```c
typedef struct __attribute__((packed)) {
    uint32_t timestamp_sec;      /* Relative uptime or RTC epoch seconds */
    uint16_t raw_shtc3_temp_u16; /* SHTC3 Raw 16-bit Temperature word */
    uint16_t raw_shtc3_rh_u16;   /* SHTC3 Raw 16-bit Relative Humidity word */
    int16_t  raw_tsens_val;      /* TSENS raw ADC register / die temp (centi-°C) */
    uint8_t  flags;              /* Status flags (Bit 0: Valid reading) */
    uint8_t  reserved;
} bsp_ulp_raw_sample_t;

typedef struct __attribute__((packed)) {
    uint32_t magic;              /* BSP_ULP_MAGIC_TOKEN ("VAPR") */
    uint32_t head_index;         /* Circular buffer head index (0..63) */
    uint32_t total_samples;      /* Total monotonic samples captured */
    uint32_t poll_interval_sec;  /* Sampling period (60s) */
    bsp_ulp_raw_sample_t samples[BSP_ULP_RING_BUFFER_CAPACITY];
} bsp_ulp_shared_mem_t;
```

---

## 3. Toolchain & Build Environment

The ULP RISC-V environment is fully native and built directly into standard ESP-IDF v5.1+ / v6.x:
- **Compiler**: `riscv32-esp-elf-gcc` cross-compiler (automatically managed by ESP-IDF).
- **Language**: Native Freestanding C (`ulp_riscv.h`, `ulp_riscv_utils.h`, `ulp_riscv_gpio.h`).
- **Configuration**:
  - `CONFIG_ULP_COPROC_ENABLED=y`
  - `CONFIG_ULP_COPROC_TYPE_RISCV=y`
  - `CONFIG_ULP_COPROC_RESERVE_MEM=2048`

---

## 4. Hardware Power Architecture & Idle Current Breakdown

Based on empirical circuit analysis of the Waveshare ESP32-S3-Touch-ePaper-1.54 V2 board:

| Rail / Subsystem | Typical Quiescent Current ($I_{\text{typ}}$) | Condition / Operating Mode |
|---|---|---|
| **Battery Rail ($V_{\text{BAT}}$)** | **$21\,\mu\text{A} - 28\,\mu\text{A}$** | ETA6098 quiescent ($1.0\,\mu\text{A}$) + MP1605 buck converter in light-load PFM ($19-26\,\mu\text{A}$) |
| **Regulated 3.3V Rail** | **$12\,\mu\text{A} - 16\,\mu\text{A}$** | ESP32-S3 deep sleep ($7.0\,\mu\text{A}$) + PCF85063A ($0.22\,\mu\text{A}$) + SSD1681 Mode 1 ($1.0\,\mu\text{A}$) + SHTC3 ($0.3\,\mu\text{A}$) |
| **Active Refresh Surge** | **$\approx 65\text{ mA}$** | Main Xtensa CPU 240MHz + SPI EPD waveform drive ($1.5\text{ s}$) |

### Expected Battery Life (400 mAh LiPo):
$$\text{Average Current } I_{\text{avg}} = \frac{65\text{ mA} \times 1.5\text{ s} + 0.025\text{ mA} \times 60\text{ s}}{61.5\text{ s}} \approx 1.61\text{ mA} \implies \approx 10.3\text{ Days (60s interval)}$$
$$\text{At 300s (5-minute) interval: } I_{\text{avg}} \approx 0.35\text{ mA} \implies \approx 47.6\text{ Days (400 mAh LiPo)}$$
