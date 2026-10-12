# MicroSD Card 1-Bit SDMMC & FATFS Storage Subsystem

## 1. Physical Specifications & Hardware Pinout
- **Storage Media:** MicroSD / SDHC / SDXC
- **Controller Interface:** ESP32-S3 SDMMC Host Peripheral (1-Bit Mode)
- **Pin Assignment:**
  - Clock (CLK): `GPIO 39` (`BSP_PIN_SD_CLK`)
  - Command (CMD): `GPIO 41` (`BSP_PIN_SD_MOSI`)
  - Data Line 0 (D0): `GPIO 40` (`BSP_PIN_SD_MISO`)
  - Card Detect (CD): Not Connected (`SDMMC_SLOT_NO_CD`)
  - Write Protect (WP): Not Connected (`SDMMC_SLOT_NO_WP`)
- **Mount Point:** `/sdcard` (`BSP_SDCARD_MOUNT_POINT`)
- **Operating Frequency:** 20 MHz (`SDMMC_FREQ_DEFAULT`)

---

## 2. SDMMC Host & Slot Configuration

Because the hardware routes only a single data line (D0) without dedicated hardware Card Detect or Write Protect pins, the driver must explicitly configure 1-bit mode:

```c
esp_vfs_fat_sdmmc_mount_config_t mount_config = {
    .format_if_mount_failed = false,
    .max_files              = 5,
    .allocation_unit_size   = 16 * 1024, // 16 KB cluster size
};

sdmmc_host_t host = SDMMC_HOST_DEFAULT();
host.max_freq_khz = SDMMC_FREQ_DEFAULT;  // 20,000 kHz
host.flags        = SDMMC_HOST_FLAG_1BIT;

sdmmc_slot_config_t slot_config = SDMMC_SLOT_CONFIG_DEFAULT();
slot_config.width = 1;
slot_config.clk   = (gpio_num_t)BSP_PIN_SD_CLK;
slot_config.cmd   = (gpio_num_t)BSP_PIN_SD_MOSI;
slot_config.d0    = (gpio_num_t)BSP_PIN_SD_MISO;
slot_config.cd    = SDMMC_SLOT_NO_CD;
slot_config.wp    = SDMMC_SLOT_NO_WP;
```

---

## 3. Card Absence & Error Suppression

Without a physical Card Detect switch, probing an empty card slot causes the SDMMC stack to attempt bus handshakes that time out. To prevent flooding the console with error stacks during normal boot:
1. Temporarily lower the logging levels of `sdmmc_common` and `vfs_fat_sdmmc` to `ESP_LOG_WARN`.
2. Execute `esp_vfs_fat_sdmmc_mount()`.
3. Restore previous log levels.
4. Catch `ESP_ERR_TIMEOUT` or `ESP_ERR_INVALID_RESPONSE` and return clean `ESP_ERR_NOT_FOUND`.

---

## 4. Capacity Calculation

Card capacity in gigabytes is decoded from the CSD register:

$$
\text{Capacity } [\text{GB}] = \frac{\text{card->csd.capacity}}{2048 \times 1024}
$$

```c
float bsp_sdcard_get_capacity_gb(void) {
    if (s_sd_card == NULL) return 0.0f;
    return (float)(s_sd_card->csd.capacity) / 2048.0f / 1024.0f;
}
```

---

## 5. Teardown & Unmount Lifecycle

Before system shutdown or entering deep sleep:
1. Flush any open file descriptors.
2. Call `esp_vfs_fat_sdcard_unmount(BSP_SDCARD_MOUNT_POINT, s_sd_card);`.
3. Tristate or deinitialize the SDMMC bus handles to prevent parasitic leakage through the SD card pins.
