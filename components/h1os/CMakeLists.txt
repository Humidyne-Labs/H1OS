set(h1os_srcs
    "src/hal_io.c"
    "src/hal_i2c.c"
    "src/hal_spi.c"
    "src/hal_flash.c"
    "src/sub_sensor.c"
    "src/sub_rtc.c"
    "src/sub_power.c"
    "src/sub_audio.c"
    "src/sub_display.cpp"
    "src/sub_sdcard.c"
    "src/sub_nvs.c"
    "src/orch_state.c"
    "src/orch_math.c"
    "src/orch_flow.c"
    "src/orch_display_sync.c"
    "src/orch_wake_stub.c"
    "src/h1os_lifecycle.c"
    "src/h1os_lvgl.cpp"
    "src/h1os_time.c"
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
    lvgl
    esp_driver_tsens
    esp_pm
    esp_partition
    spi_flash
    esp_hw_support
    ulp
)

# Ensure generated_fonts directory exists so include directory checks pass during configure
set(GEN_FONT_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated_fonts")
file(MAKE_DIRECTORY "${GEN_FONT_DIR}")

# Register component with its static sources and include paths
idf_component_register(
    SRCS ${h1os_srcs}
    INCLUDE_DIRS "include" "include/h1os"
    REQUIRES ${bsp_requires}
)

target_include_directories(${COMPONENT_LIB} PUBLIC "${GEN_FONT_DIR}")

# -----------------------------------------------------------------------------
# Dynamic 1-BPP Typography Generation (Zero-Duplication Build-Time Asset Synthesizer)
# -----------------------------------------------------------------------------

# Locate LVGL component directory for font source assets
idf_component_get_property(lvgl_dir lvgl__lvgl COMPONENT_DIR)
if(NOT lvgl_dir)
    idf_component_get_property(lvgl_dir lvgl COMPONENT_DIR)
endif()
set(LVGL_FONT_SRC_DIR "${lvgl_dir}/scripts/generators/built_in_font")

set(GENERATED_FONT_SRCS
    "${GEN_FONT_DIR}/h1os_font_montserrat_14_1bpp.c"
    "${GEN_FONT_DIR}/h1os_font_montserrat_16_1bpp.c"
    "${GEN_FONT_DIR}/h1os_font_montserrat_18_1bpp.c"
    "${GEN_FONT_DIR}/h1os_font_montserrat_20_1bpp.c"
    "${GEN_FONT_DIR}/h1os_font_montserrat_24_1bpp.c"
    "${GEN_FONT_DIR}/h1os_font_montserrat_32_1bpp.c"
    "${GEN_FONT_DIR}/h1os_font_dejavu_14_1bpp.c"
    "${GEN_FONT_DIR}/h1os_font_dejavu_16_1bpp.c"
    "${GEN_FONT_DIR}/h1os_font_dejavu_20_1bpp.c"
)
set(GENERATED_FONT_HDR "${GEN_FONT_DIR}/h1os_fonts.h")

set(FONT_GEN_SCRIPT "${CMAKE_CURRENT_LIST_DIR}/../../tools/generate_1bpp_fonts.py")

idf_build_get_property(python_bin PYTHON)

add_custom_command(
    OUTPUT ${GENERATED_FONT_SRCS} ${GENERATED_FONT_HDR}
    COMMAND "${python_bin}" "${FONT_GEN_SCRIPT}"
            --lvgl-font-dir "${LVGL_FONT_SRC_DIR}"
            --lvgl-root "${lvgl_dir}"
            --out-dir "${GEN_FONT_DIR}"
            --all
    DEPENDS "${FONT_GEN_SCRIPT}"
            "${LVGL_FONT_SRC_DIR}/Montserrat-Medium.ttf"
            "${LVGL_FONT_SRC_DIR}/DejaVuSans.ttf"
            "${LVGL_FONT_SRC_DIR}/FontAwesome5-Solid+Brands+Regular.woff"
    COMMENT "Synthesizing H1OS 1-BPP Typography & Font Licenses from LVGL Assets..."
    VERBATIM
)

# Append generated font sources to the component library target
target_sources(${COMPONENT_LIB} PRIVATE ${GENERATED_FONT_SRCS})

idf_build_set_property(BOOTLOADER_EXTRA_COMPONENT_DIRS "${CMAKE_CURRENT_LIST_DIR}/bootloader_components" APPEND)

if(CONFIG_ULP_COPROC_ENABLED)
    set(ulp_app_name "ulp_${COMPONENT_NAME}")
    set(ulp_sources "ulp/main.c")
    set(ulp_exp_dep_srcs "src/hal_io.c")
    ulp_embed_binary(${ulp_app_name} "${ulp_sources}" "${ulp_exp_dep_srcs}" TYPE "riscv")
endif()