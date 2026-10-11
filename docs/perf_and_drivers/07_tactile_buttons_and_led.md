# Tactile Buttons, Status LED & User Interaction

## 1. Physical Specifications & Circuit Topologies

### Tactile Buttons (BOOT & POWER)
- **BOOT Button:** `GPIO 0` (`HAL_PIN_BUTTON_BOOT` / `BSP_PIN_BUTTON_BOOT`)
- **POWER Button:** `GPIO 18` (`HAL_PIN_BUTTON_POWER` / `BSP_PIN_BUTTON_POWER`)
- **Circuit Architecture:**
  - Active LOW pushbuttons: Pin connects directly to GND when physically depressed.
  - **External 100 kΩ pull-up resistors to 3.3V** are physically present on the PCB for both lines, ensuring a stable HIGH state when unpressed (~33 µA current sink when depressed).
  - Internal pull-up resistors (~45 kΩ) may be optionally enabled in parallel ($R_{\text{eff}} = 100\text{k} \parallel 45\text{k} \approx 31\text{ k}\Omega$) for enhanced EMI/noise immunity in noisy RF environments.
  - Both pins reside in the **RTC IO Domain** and can wake the processor from deep sleep via `EXT1`.

### Status LED
- **LED Pin:** `GPIO 3` (`HAL_PIN_STATUS_LED` / `BSP_PIN_LED_STATUS`)
- **Circuit Architecture:**
  - Cathode is connected directly to `GPIO 3`.
  - Anode is tied through a current-limiting resistor to the 3.3V rail.
  - **Open-Drain Active LOW:**
    - `0` (Low level / Sink): **LED ON**
    - `1` (High level / High-Z): **LED OFF**

---

## 2. Button State Machine & Timing Parameters

Button inputs are processed by an asynchronous non-blocking state machine driven by a 10 ms periodic hardware timer (`esp_timer`):

```
       [ STATE_BOOT_WAIT_RELEASE ]
                   │ (Pin Released / HIGH)
                   ▼
            [ STATE_IDLE ] ◄─────────────────────────┐
                   │                                 │
                   │ (Pin Pressed / LOW)             │ (Bounce / Glitch)
                   ▼                                 │
       [ STATE_DEBOUNCE_PRESS ] ─────────────────────┘
                   │
                   │ (Stable LOW >= 30 ms)
                   ▼
           [ STATE_PRESSED ] ────► Fired: PRESS_DOWN
                   │
                   ├── (Held >= 2000 ms) ──► Fired: LONG_PRESS (Auto Power-Off)
                   │
                   │ (Pin Released / HIGH)
                   ▼
      [ STATE_DEBOUNCE_RELEASE ]
                   │
                   │ (Stable HIGH >= 30 ms)
                   ▼
    [ STATE_WAIT_DOUBLE_CLICK ] ──► Fired: SHORT_CLICK / DOUBLE_CLICK
```

### Timing Thresholds
- **Timer Tick:** 10 ms (`TIMER_INTERVAL_MS`)
- **Debounce Window:** 30 ms (`debounce_ms`)
- **Long Press Window:** 2,000 ms (`long_press_ms`)
- **Double Click Window:** 300 ms (`double_click_ms`)

### Built-in Power Button Long-Press Action
If `auto_power_off_on_hold` is enabled (default `true`):
```c
if (btn == BSP_BUTTON_POWER && event == BSP_BUTTON_EVENT_LONG_PRESS) {
    ESP_LOGW(TAG, "Power button long-press detected! Initiating power off...");
    bsp_power_off();
}
```

---

## 3. Deep Sleep EXT1 Wakeup Configuration

To allow the user to wake the device from deep sleep by pressing either button:
```c
uint64_t ext1_pin_mask = (1ULL << GPIO_NUM_0) | (1ULL << GPIO_NUM_18);

// Ensure RTC IO pull-ups are enabled
rtc_gpio_init(GPIO_NUM_0);
rtc_gpio_set_direction(GPIO_NUM_0, RTC_GPIO_MODE_INPUT_ONLY);
rtc_gpio_pullup_en(GPIO_NUM_0);
rtc_gpio_pulldown_dis(GPIO_NUM_0);

rtc_gpio_init(GPIO_NUM_18);
rtc_gpio_set_direction(GPIO_NUM_18, RTC_GPIO_MODE_INPUT_ONLY);
rtc_gpio_pullup_en(GPIO_NUM_18);
rtc_gpio_pulldown_dis(GPIO_NUM_18);

// Arm EXT1 low-level wake trigger
esp_sleep_enable_ext1_wakeup_io(ext1_pin_mask, ESP_EXT1_WAKEUP_ANY_LOW);
```

### Button Release Gating Before Sleep Entry
Before calling `esp_deep_sleep_start()`, software must poll until both buttons are stable HIGH for at least 100 ms. Otherwise, the physical press that triggered the sleep command would immediately wake the device!
