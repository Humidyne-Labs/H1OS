Here is the complete, detailed architectural guide covering the ESP32-S3 RTC domain, bidirectional IO ownership transitions, concurrent timer and GPIO interrupt handling on the ULP, and precise pulse-delay measurement.

---

### 1. ESP32-S3 RTC Domain & External Interrupts Deep-Dive

#### Power Domain Architecture

The ESP32-S3 divides its silicon into two primary power and clock domains:

* **HP (High-Performance) Domain:** Dual-core Xtensa LX7, system SRAM, standard GPIO matrix, and high-speed digital peripherals. This domain is powered off during deep sleep.
* **LP / RTC Domain:** Low-power RTC controller, RTC SLOW memory (8 KB, where ULP code and data reside), RTC FAST memory (8 KB), and the ULP RISC-V coprocessor core. It remains powered by the `VDD3P3_RTC` analog rail during deep sleep.

```
                  +----------------------------------------------+
                  |               ESP32-S3 SoC                   |
                  |                                              |
                  |  [ HP Domain ] (Powered OFF in Deep Sleep)   |
                  |  +----------------------------------------+  |
                  |  |  Dual Xtensa LX7 Cores                 |  |
                  |  |  Standard HP GPIO Matrix / IO MUX      |  |
                  |  +----------------------------------------+  |
                  |                       ^                      |
                  |         RTC_MUX / Hardware Handover          |
                  |                       v                      |
                  |  [ LP / RTC Domain ] (Powered in Deep Sleep) |
                  |  +----------------------------------------+  |
                  |  |  ULP RISC-V Coprocessor                |  |
                  |  |  RTC Controller & Timer Modules        |  |
                  |  |  RTC IO MUX (GPIO 0 - GPIO 21 only)    |  |
                  |  +----------------------------------------+  |
                  +----------------------------------------------+

```

#### Pin Restrictions

Only **GPIO 0 through GPIO 21** feature RTC pad logic (`RTCIO_CHANNEL_0` through `RTCIO_CHANNEL_21`). Pins numbered 26 and above exist exclusively in the digital HP domain. If you attempt to access GPIOs outside the 0–21 range from the ULP or configure them as RTC wakeup sources, they will float or disconnect as soon as the HP domain shuts down.

#### Trigger Modes: Level vs. Edge in RTC Logic

1. **Level Triggering:** Handled directly by the analog comparator/RTC wakeup logic (`ESP_GPIO_WAKEUP_GPIO_LOW` or `ESP_GPIO_WAKEUP_GPIO_HIGH`). It holds the wakeup line active as long as the voltage level persists.
2. **Edge Triggering:** The RTC controller can latch rising or falling edge transitions into the RTC interrupt status register (`RTC_CNTL_INT_ST_RTC_REG`).
3. **ULP Operating Modes:**
* **Always-Running Polling:** The ULP RISC-V remains awake in RTC Slow Memory, running instructions at $\sim$17.5 MHz (drawing $\sim 10\text{–}20\ \mu\text{A}$).
* **Halted/Periodic Mode:** The ULP executes `ulp_riscv_halt()`, cutting its internal dynamic current to near zero ($<2\ \mu\text{A}$). The hardware RTC timer or an external RTC GPIO edge event then restarts the ULP at its entry point (`main()`).



---

### 2. IO Ownership: Handing Pins Between Main CPU and ULP

#### Does the Main App need to release the IO for the ULP?

**Yes.** When the ESP32-S3 powers on, pins are attached to the **HP Digital GPIO Matrix**. The main CPU must explicitly reassign the pin's physical pad to the **RTC Subsystem** (`RTC_MUX`) before entering deep sleep. If this is skipped, the ULP's `ulp_riscv_gpio_*` calls will read high-impedance floating logic or fail to register level transitions.

```c
// Handover: HP Digital Matrix -> RTC Subsystem (Executed by Main CPU)
rtc_gpio_init(GPIO_NUM_4);
rtc_gpio_set_direction(GPIO_NUM_4, RTC_GPIO_MODE_INPUT_ONLY);
rtc_gpio_pullup_en(GPIO_NUM_4);
rtc_gpio_pulldown_dis(GPIO_NUM_4);

```

#### Does the ULP need to release the IO for the Main App?

**Yes, if the Main CPU needs to use that pin with HP peripherals.**
If the main application only reads digital high/low levels, it can still read the RTC register. However, if the main application needs that pin for high-speed hardware peripherals (SPI, UART, I2C, MCPWM, or the HP GPIO matrix with standard interrupt handlers), the pin **must be detached from the RTC domain and returned to the HP GPIO matrix**:

```c
// Handover: RTC Subsystem -> HP Digital Matrix (Executed by Main CPU on wake)
rtc_gpio_deinit(GPIO_NUM_4); // Clears RTC_MUX routing
gpio_config_t io_conf = {
    .pin_bit_mask = (1ULL << GPIO_NUM_4),
    .mode = GPIO_MODE_INPUT,
    .pull_up_en = GPIO_PULLUP_ENABLE,
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .intr_type = GPIO_INTR_ANYEDGE,
};
gpio_config(&io_conf);

```

The ULP itself does not need to run an "unmount" instruction before halting; the handover is controlled by the `RTC_MUX` register configurations applied by the main CPU.

---

### 3. Handling Concurrent Periodic Timer Wakes and External GPIO Interrupts

To service both **periodic polling routines** (e.g., reading an environmental sensor or checking a battery every 10 seconds) and **asynchronous external interrupts** (e.g., an instant button press or trigger pulse), configure the RTC controller to target the ULP with two distinct wake sources:

1. **Hardware RTC Timer:** Wakes the ULP on a periodic interval.
2. **RTC GPIO Interrupt:** Wakes the ULP instantly on an external line transition.

When the ULP halts (`ulp_riscv_halt()`), it draws minimal current. When woken, the ULP reads the RTC interrupt status register to identify the wakeup source and acts accordingly:

```
[ULP Halted in RTC Memory (<2 uA)]
            |
            +<------------------------------------+
            |                                     |
   [Wake Event Occurs]                            |
   ├── Periodic RTC Timer Tick                    |
   └── External RTC GPIO Edge / Level             |
            |                                     |
   [ULP Restarts at main()]                       |
            |                                     |
   [Inspect Wake Cause Register]                  |
   ├── Timer Bit Set?    -> Run periodic task     |
   └── GPIO Bit Set?     -> Measure pulse/delay   |
            |                                     |
   [Clear Interrupt Flags & Reset Timer]          |
            |                                     |
   [ulp_riscv_halt()] ----------------------------+

```

---

### 4. Implementation Code

#### Project Build File (`main/CMakeLists.txt`)

```cmake
idf_component_register(
    SRCS "main.c"
    INCLUDE_DIRS "."
)

# Compiles ULP RISC-V code and exports header "ulp_main.h"
ulp_embed_binary(ulp_main "ulp/main.c")

```

#### ULP RISC-V Firmware (`main/ulp/main.c`)

This implementation handles concurrent wakeups: determining if an interrupt or periodic timer fired, timing IO pulses accurately, and waking the main CPU when thresholds are exceeded.

```c
#include <stdint.h>
#include "ulp_riscv.h"
#include "ulp_riscv_utils.h"
#include "ulp_riscv_gpio.h"

#define SENSOR_PIN GPIO_NUM_4

// Shared memory variables (readable by Main CPU via ulp_main.h)
volatile uint32_t ulp_pulse_duration_us = 0;
volatile uint32_t ulp_periodic_tick_count = 0;
volatile uint32_t ulp_last_wake_cause = 0; // 1 = Timer, 2 = GPIO Edge

int main(void) {
    // Configure SENSOR_PIN within the RTC subsystem
    ulp_riscv_gpio_init(SENSOR_PIN);
    ulp_riscv_gpio_input_enable(SENSOR_PIN);

    // Read current pin state
    uint32_t pin_level = ulp_riscv_gpio_get_level(SENSOR_PIN);

    // Detect if woke by active-low pulse (GPIO event) or periodic timer
    if (pin_level == 0) {
        ulp_last_wake_cause = 2; // External GPIO Trigger

        // ==========================================
        // COUNT DELAY / MEASURE PULSE DURATION
        // ==========================================
        uint32_t duration = 0;

        // RTC_FAST_CLK runs at ~17.5 MHz (approx 17.5 cycles/us)
        // With loop instruction overhead, 14-17 cycles approximates 1 us
        while (ulp_riscv_gpio_get_level(SENSOR_PIN) == 0) {
            duration++;
            ulp_riscv_delay_cycles(17);

            // Guard against infinite stalls if line gets stuck low
            if (duration > 1000000) { 
                break;
            }
        }

        ulp_pulse_duration_us = duration;

        // Wake the main processor if pulse exceeds threshold (e.g., > 1 ms)
        if (duration > 1000) {
            ulp_riscv_wakeup_main_processor();
            // Halt ULP while main CPU services the event
            ulp_riscv_halt();
        }
    } else {
        ulp_last_wake_cause = 1; // Periodic Timer Wake
        ulp_periodic_tick_count++;

        // Example: wake main processor after 60 timer cycles
        if (ulp_periodic_tick_count >= 60) {
            ulp_riscv_wakeup_main_processor();
            ulp_riscv_halt();
        }
    }

    // Halt and wait for next hardware event (Timer or GPIO edge)
    ulp_riscv_halt();
    return 0;
}

```

#### Main Application Firmware (`main/main.c`)

Manages binary loading, initial pin handovers to the RTC domain, wake source registration, and domain reclamation.

```c
#include <stdio.h>
#include "esp_sleep.h"
#include "driver/rtc_io.h"
#include "driver/gpio.h"
#include "ulp_riscv.h"
#include "ulp_main.h"
#include "esp_log.h"

static const char *TAG = "MAIN_CORE";
#define INPUT_PIN GPIO_NUM_4

extern const uint8_t ulp_main_bin_start[] asm("_binary_ulp_main_bin_start");
extern const uint8_t ulp_main_bin_end[]   asm("_binary_ulp_main_bin_end");

static void setup_ulp_environment(void) {
    // 1. Handover pin from HP Matrix to RTC Domain
    rtc_gpio_init(INPUT_PIN);
    rtc_gpio_set_direction(INPUT_PIN, RTC_GPIO_MODE_INPUT_ONLY);
    rtc_gpio_pullup_en(INPUT_PIN);
    rtc_gpio_pulldown_dis(INPUT_PIN);

    // 2. Load ULP binary into RTC Slow Memory
    ESP_ERROR_CHECK(ulp_riscv_load_binary(
        ulp_main_bin_start,
        (ulp_main_bin_end - ulp_main_bin_start)
    ));

    // 3. Configure periodic timer wakeup for ULP (e.g., every 5 seconds)
    // 5,000,000 microseconds = 5s
    ulp_set_wakeup_period(0, 5000000);

    // 4. Start ULP execution
    ESP_ERROR_CHECK(ulp_riscv_run());
    ESP_LOGI(TAG, "ULP running with concurrent timer/interrupt triggers.");
}

void app_main(void) {
    esp_sleep_wakeup_cause_t cause = esp_sleep_get_wakeup_cause();

    if (cause != ESP_SLEEP_WAKEUP_ULP) {
        ESP_LOGI(TAG, "Cold boot. Setting up ULP...");
        setup_ulp_environment();
    } else {
        ESP_LOGI(TAG, "Woken up by ULP co-processor!");

        // Read variables directly populated by the ULP
        ESP_LOGI(TAG, "Last Wake Cause: %s", (ulp_last_wake_cause == 2) ? "GPIO Pulse" : "Periodic Timer");
        ESP_LOGI(TAG, "Pulse Duration: %lu us", (unsigned long)ulp_pulse_duration_us);
        ESP_LOGI(TAG, "Timer Cycles: %lu", (unsigned long)ulp_periodic_tick_count);

        // OPTIONAL: If the main core needs this pin for high-speed HP peripherals:
        // rtc_gpio_deinit(INPUT_PIN);
        // ... execute high-speed operations on INPUT_PIN ...
        // rtc_gpio_init(INPUT_PIN); // Hand back to RTC before sleep!

        // Resume ULP execution
        ulp_riscv_run();
    }

    // Set Main Core to wake only when ULP invokes ulp_riscv_wakeup_main_processor()
    ESP_ERROR_CHECK(esp_sleep_enable_ulp_wakeup());

    ESP_LOGI(TAG, "Main core entering deep sleep...");
    esp_deep_sleep_start();
}

```

---

### 5. Timing Accuracy and Delay Calibration

`ulp_riscv_delay_cycles(cycles)` uses the **`RTC_FAST_CLK`** oscillator, which runs nominally at **$\sim$17.5 MHz**. Because this clock is driven by an internal RC oscillator rather than an external crystal, it drifts with operating temperature and chip-to-chip process variations ($\pm 5\%\text{ to }\pm 10\%$).

* **For microsecond precision:** In the main application before deep sleep, use `esp_clk_slowclk_cal()` to measure the actual frequency of the internal RC oscillator against the main XTAL, and pass the computed cycle-per-microsecond ratio into a shared ULP variable (e.g., `ulp_calibrated_cycles_per_us`).
* **For high stability:** Route a 32.768 kHz external crystal to `XTAL_32K_P` and `XTAL_32K_N` (`GPIO15` and `GPIO16`), selecting `External 32kHz crystal` as the RTC clock source in `menuconfig`. This eliminates frequency drift across deep sleep intervals.