set(bsp_srcs
    "src/bsp_common.c"
    "src/bsp_button.c"
    "src/bsp_power.c"
    "src/bsp_sdcard.c"
    "src/hal_io.c"
    "src/hal_i2c.c"
    "src/hal_spi.c"
    "src/hal_flash.c"
    "src/sub_sensor.c"
    "src/sub_rtc.c"
    "src/sub_power.c"
    "src/sub_audio.c"
    "src/sub_display.cpp"
    "src/orch_state.c"
    "src/orch_math.c"
    "src/orch_flow.c"
    "src/orch_display_sync.c"
    "src/orch_wake_stub.c"
    "src/bsp_lvgl.cpp"
    "src/bsp_nvs.c"
    "src/bsp_wifi.c"
    "src/bsp_time.c"
    "src/bsp_prov.c"
    "src/bsp_ota.c"
    "src/bsp_font_montserrat_14_1bpp.c"
    "src/bsp_font_montserrat_20_1bpp.c"
)

set(bsp_requires
    esp_driver_gpio
    esp_driver_i2c
    esp_driver_i2s
    esp_driver_spi
    esp_driver_sdmmc
    sdmmc
    esp_adc
    esp_timer
    nvs_flash
    fatfs
    log
    freertos
    esp_wifi
    esp_netif
    esp_event
    network_provisioning
    bt
    protocomm
    app_update
    esp_https_ota
    mbedtls
    esp-tls
    lvgl
    esp_mmap_assets
    esp_lv_fs
    esp_driver_tsens
    esp_pm
    esp_partition
    spi_flash
    esp_hw_support
    ulp
)

if(CONFIG_BSP_ENABLE_THINGSBOARD)
    list(APPEND bsp_srcs "src/bsp_tb.c")
    list(APPEND bsp_requires mqtt cjson)
endif()

idf_component_register(
    SRCS ${bsp_srcs}
    INCLUDE_DIRS "include"
    REQUIRES ${bsp_requires}
)

idf_build_set_property(BOOTLOADER_EXTRA_COMPONENT_DIRS "${CMAKE_CURRENT_LIST_DIR}/bootloader_components" APPEND)

if(CONFIG_ULP_COPROC_ENABLED)
    set(ulp_app_name "ulp_${COMPONENT_NAME}")
    set(ulp_sources "ulp/main.c")
    set(ulp_exp_dep_srcs "src/hal_io.c")
    ulp_embed_binary(${ulp_app_name} "${ulp_sources}" "${ulp_exp_dep_srcs}" TYPE "riscv")
endif()