## Verdict

Mostly correct and the right pattern — the pin numbers line up with the hardware (`RTC_CNTL_PAD_HOLD_REG` is indexed by RTCIO number, which equals the GPIO number for GPIO0–21 on S3, so `BIT(17)`/`BIT(6)` are valid), and hold-release→configure→hold is the correct order since hold latches the live pad state. **One real gap: GPIO 42's hold will not survive deep sleep**, and two smaller caveats are worth double-checking.

---

## What's Correct

- **Hook structure**: `bootloader_before_init` / `bootloader_after_init` + the `bootloader_hooks_include` linker symbol is exactly the documented custom-bootloader-hooks mechanism [1](#4-0) .
- **Pre-init safety**: only ROM (`esp_rom_gpio_pad_select_gpio`) and inline LL calls are used in `before_init` — no ESP_LOG, no driver APIs. This satisfies the "can't use other components in bootloader space" constraint [2](#4-1) .
- **RTCIO pads**: `RTC_CNTL_PAD_HOLD_REG` is the per-RTCIO hold register — right choice for GPIO 6 and 17, which are RTC-capable.
- **GPIO 42 hold**: `gpio_ll_hold_en` correctly writes `RTC_CNTL_DIG_PAD_HOLD_REG` via `GPIO_HOLD_MASK[42]` — that's the right register for a non-RTCIO digital pad [3](#4-2) .
- **Hooks run on every reset** including deep-sleep wake, so the latch re-asserts at each boot — which is presumably the intent for `POWER_HOLD`.

## Gap 1: GPIO 42 will drop during deep sleep

On S3, a digital pad's hold bit alone does **not** hold it through deep sleep — the comment in `gpio_hal.h` is explicit: "the state of digital gpio cannot be held during Deep-sleep, and it will resume the hold function when the chip wakes up... `gpio_deep_sleep_hold_en` should also be called" [4](#4-3) . What you have now holds GPIO 42 at runtime and across light-sleep isolation, but in deep sleep the pad floats unless `RTC_CNTL_DG_PAD_AUTOHOLD_EN_M` is set via `gpio_ll_deep_sleep_hold_en()` (which clears `DG_PAD_FORCE_UNHOLD` and sets `AUTOHOLD_EN`) [5](#4-4) .

Your app must call `gpio_deep_sleep_hold_en()` (or the LL macro, which requires `PERIPH_RCC_ATOMIC`) before `esp_deep_sleep_start()` — or better, move PA_EN to an RTCIO pad if board revision permits, since `RTC_CNTL_PAD_HOLD_REG` holds work in the RTC domain directly.

## Caveat 2: App startup can release the holds

The bootloader latch is not permanent:

- Any `rtc_gpio_deinit()` / `gpio_reset_pin()` / fresh `gpio_config()` on GPIO 6, 17, or 42 in the app changes the pad, and `rtc_gpio_hold_dis`/power-down drops the hold [6](#4-5) .
- Your deep-sleep path (`ext1_wakeup_prepare`-style pad prep) calls `rtcio_hal_hold_enable` on wake pins — unrelated, but if your `sub_power` code reconfigures GPIO 6/17, it'll silently unlatch them.

Re-assert the holds in `app_main` early too (or audit that nothing touches these pads), and when releasing a digital hold after wake, re-configure the pin to the desired state *first* — the pad reverts to its default level otherwise [7](#4-6) .

## Caveat 3: Output routing relies on reset defaults

`esp_rom_gpio_pad_select_gpio()` sets the IO_MUX function, but the output value reaches the pad through the GPIO matrix signal `SIG_GPIO_OUT_IDX`. That works because `GPIO_FUNCn_OUT_SEL` resets to the GPIO matrix default — nothing in your code overrides it — but if any earlier bootloader code (e.g., strapping-pin recovery, flash-encryption GPIO handling) touched `FUNC_OUT_SEL` for these pins, the level wouldn't propagate. Belt-and-suspenders: add `esp_rom_gpio_connect_out_signal(pin, SIG_GPIO_OUT_IDX, 0, 0)` after `pad_select_gpio` — it's ROM-resident and safe pre-cache. (I can't cite the S3 ROM signature from the indexed context, so verify the symbol exists in your IDF version's `esp_rom_gpio.h`.)

## Minor

- `GPIO_ENABLE_REG`/`GPIO_OUT_REG` audit reads in `after_init` only cover GPIO 0–31; if you want the same check for GPIO 42, use

Wiki pages you might want to explore:
- [SoC Capabilities and Hardware Abstraction (espressif/esp-idf)](/wiki/espressif/esp-idf#3.2)
- [Boot and ROM Configuration (espressif/esp-idf)](/wiki/espressif/esp-idf#3.3)

### Citations

**File:** docs/en/api-guides/bootloader.rst (L182-195)
```text
Custom Bootloader
-----------------

The current bootloader implementation allows a project to extend it or modify it. There are two ways of doing it: by implementing hooks or by overriding it. Both ways are presented in :example:`custom_bootloader` folder in ESP-IDF examples:

* :example:`custom_bootloader/bootloader_hooks` presents how to connect some hooks to the bootloader initialization
* :example:`custom_bootloader/bootloader_override` presents how to override the bootloader implementation

In the bootloader space, you cannot use the drivers and functions from other components unless they explicitly support run in bootloader. If necessary, then the required functionality should be placed in the project's `bootloader_components` directory (note that this will increase its size). Examples of components that can be used in the bootloader are:

* :example:`storage/nvs/nvs_bootloader`

If the bootloader grows too large then it can collide with the partition table, which is flashed at offset 0x8000 by default. Increase the :menuitem:`partition table offset <CONFIG_PARTITION_TABLE_OFFSET>` value to place the partition table later in the flash. This increases the space available for the bootloader.

```

**File:** components/esp_hal_gpio/esp32s3/include/hal/gpio_ll.h (L424-448)
```text
static inline void _gpio_ll_deep_sleep_hold_en(gpio_dev_t *hw)
{
    CLEAR_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_DG_PAD_FORCE_UNHOLD);
    SET_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_DG_PAD_AUTOHOLD_EN_M);
}

/// use a macro to wrap the function, force the caller to use it in a critical section
/// the critical section needs to declare the __DECLARE_RCC_ATOMIC_ENV variable in advance
/// When operating RTC_CNTL_DIG_ISO_REG, PERIPH_RCC_ATOMIC() must be used to ensure atomicity.
#define gpio_ll_deep_sleep_hold_en(...) (void)__DECLARE_RCC_ATOMIC_ENV; _gpio_ll_deep_sleep_hold_en(__VA_ARGS__)

/**
  * @brief Disable all digital gpio pad hold function during Deep-sleep.
  *
  * @param hw Peripheral GPIO hardware instance address.
  */
static inline void _gpio_ll_deep_sleep_hold_dis(gpio_dev_t *hw)
{
    CLEAR_PERI_REG_MASK(RTC_CNTL_DIG_ISO_REG, RTC_CNTL_DG_PAD_AUTOHOLD_EN_M);
}

/// use a macro to wrap the function, force the caller to use it in a critical section
/// the critical section needs to declare the __DECLARE_RCC_ATOMIC_ENV variable in advance
/// When operating RTC_CNTL_DIG_ISO_REG, PERIPH_RCC_ATOMIC() must be used to ensure atomicity.
#define gpio_ll_deep_sleep_hold_dis(...) (void)__DECLARE_RCC_ATOMIC_ENV; _gpio_ll_deep_sleep_hold_dis(__VA_ARGS__)
```

**File:** components/esp_hal_gpio/esp32s3/include/hal/gpio_ll.h (L471-485)
```text
static inline void gpio_ll_hold_en(gpio_dev_t *hw, uint32_t gpio_num)
{
    SET_PERI_REG_MASK(RTC_CNTL_DIG_PAD_HOLD_REG, GPIO_HOLD_MASK[gpio_num]);
}

/**
  * @brief Disable gpio pad hold function.
  *
  * @param hw Peripheral GPIO hardware instance address.
  * @param gpio_num GPIO number, only support output GPIOs
  */
static inline void gpio_ll_hold_dis(gpio_dev_t *hw, uint32_t gpio_num)
{
    CLEAR_PERI_REG_MASK(RTC_CNTL_DIG_PAD_HOLD_REG, GPIO_HOLD_MASK[gpio_num]);
}
```

**File:** components/esp_hal_gpio/include/hal/gpio_hal.h (L292-296)
```text
  * On ESP32/S2/C3/S3/C2, the state of digital gpio cannot be held during Deep-sleep, and it will resume the hold
  * function when the chip wakes up from Deep-sleep. If the digital gpio also needs to be held during Deep-sleep,
  * `gpio_deep_sleep_hold_en` should also be called.
  *
  * Power down or call gpio_hold_dis will disable this function.
```

**File:** components/esp_hal_gpio/include/hal/gpio_hal.h (L303-317)
```text
/**
  * @brief Disable gpio pad hold function.
  *
  * When the chip is woken up from Deep-sleep, the gpio will be set to the default mode, so, the gpio will output
  * the default level if this function is called. If you don't want the level changes, the gpio should be configured to
  * a known state before this function is called.
  *  e.g.
  *     If you hold gpio18 high during Deep-sleep, after the chip is woken up and `gpio_hold_dis` is called,
  *     gpio18 will output low level(because gpio18 is input mode by default). If you don't want this behavior,
  *     you should configure gpio18 as output mode and set it to high level before calling `gpio_hold_dis`.
  *
  * @param hal Context of the HAL layer
  * @param gpio_num GPIO number, only support output GPIOs
  */
#define gpio_hal_hold_dis(hal, gpio_num) gpio_ll_hold_dis((hal)->dev, gpio_num)
```

**File:** components/esp_driver_gpio/include/driver/rtc_io.h (L279-291)
```text
/**
 * @brief Disable hold function on an RTC IO pad
 *
 * Disabling hold function will allow the pad receive the values of
 * input enable, output enable, output value, function, drive strength from
 * RTC_IO peripheral.
 *
 * @param gpio_num GPIO number (e.g. GPIO_NUM_12)
 * @return
 *     - ESP_OK Success
 *     - ESP_ERR_INVALID_ARG The IO is not an RTC IO
 */
esp_err_t rtc_gpio_hold_dis(gpio_num_t gpio_num);
```
