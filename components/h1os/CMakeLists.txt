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
    lvgl__lvgl
    esp_driver_tsens
    esp_pm
    esp_partition
    spi_flash
    esp_hw_support
    ulp
)

set(GEN_FONT_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated_fonts")
file(MAKE_DIRECTORY "${GEN_FONT_DIR}")

# Ensure components/h1os/project_include.cmake is evaluated BEFORE ESP-IDF's
# internal components/bootloader/project_include.cmake creates the bootloader ExternalProject.
# Because bootloader is a CONFIG_ONLY component, adding h1os to its PRIV_REQUIRES
# strictly orders h1os before bootloader in __BUILD_COMPONENT_TARGETS without affecting linking.
if(CMAKE_BUILD_EARLY_EXPANSION)
    macro(idf_component_register)
        set(options WHOLE_ARCHIVE)
        set(single_value KCONFIG KCONFIG_PROJBUILD)
        set(multi_value SRCS SRC_DIRS EXCLUDE_SRCS
                        INCLUDE_DIRS PRIV_INCLUDE_DIRS LDFRAGMENTS REQUIRES
                        PRIV_REQUIRES REQUIRED_IDF_TARGETS EMBED_FILES EMBED_TXTFILES)
        cmake_parse_arguments(_ "${options}" "${single_value}" "${multi_value}" "${ARGN}")
        if("${COMPONENT_NAME}" STREQUAL "bootloader")
            list(APPEND __PRIV_REQUIRES "h1os")
        endif()
        set(__component_priv_requires "${__PRIV_REQUIRES}")
        set(__component_requires "${__REQUIRES}")
        set(__component_kconfig "${__KCONFIG}")
        set(__component_kconfig_projbuild "${__KCONFIG_PROJBUILD}")
        set(__component_include_dirs "${__INCLUDE_DIRS}")
        set(__component_registered 1)
        return()
    endmacro()
endif()

idf_component_register(
    SRCS ${h1os_srcs}
    INCLUDE_DIRS "include" "include/h1os" "${GEN_FONT_DIR}"
    REQUIRES ${bsp_requires}
)

# -----------------------------------------------------------------------------
# Dynamic 1-BPP Typography Generation
# -----------------------------------------------------------------------------

# Resolve LVGL root directory for header include references
idf_component_get_property(lvgl_dir lvgl__lvgl COMPONENT_DIR)
if(NOT lvgl_dir)
    idf_component_get_property(lvgl_dir lvgl COMPONENT_DIR)
endif()

# Point to vendored font assets in the repo tools directory
set(FONT_SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/../../tools/fonts")
set(FONT_GEN_SCRIPT "${CMAKE_CURRENT_LIST_DIR}/../../tools/generate_1bpp_fonts.py")

set(GENERATED_FONT_SRCS
    "${GEN_FONT_DIR}/h1os_font_montserrat_14_1bpp.c"
    "${GEN_FONT_DIR}/h1os_font_montserrat_16_1bpp.c"
    "${GEN_FONT_DIR}/h1os_font_montserrat_18_1bpp.c"
    "${GEN_FONT_DIR}/h1os_font_montserrat_20_1bpp.c"
    "${GEN_FONT_DIR}/h1os_font_montserrat_24_1bpp.c"
    "${GEN_FONT_DIR}/h1os_font_montserrat_32_1bpp.c"
)
set(GENERATED_FONT_HDR "${GEN_FONT_DIR}/h1os_fonts.h")

idf_build_get_property(python_bin PYTHON)

add_custom_command(
    OUTPUT ${GENERATED_FONT_SRCS} ${GENERATED_FONT_HDR}
    COMMAND "${python_bin}" "${FONT_GEN_SCRIPT}"
            --lvgl-font-dir "${FONT_SRC_DIR}"
            --lvgl-root "${lvgl_dir}"
            --out-dir "${GEN_FONT_DIR}"
            --all
    DEPENDS "${FONT_GEN_SCRIPT}"
            "${FONT_SRC_DIR}/Montserrat-Medium.ttf"
            "${FONT_SRC_DIR}/FontAwesome5-Solid+Brands+Regular.woff"
    COMMENT "Synthesizing H1OS 1-BPP Typography & Font Licenses from Vendored Assets..."
    VERBATIM
)

# Register generated sources and header to prevent build race conditions
target_sources(${COMPONENT_LIB} PRIVATE ${GENERATED_FONT_SRCS} ${GENERATED_FONT_HDR})


# -----------------------------------------------------------------------------
# ULP Junk
# -----------------------------------------------------------------------------

if(CONFIG_ULP_COPROC_ENABLED)
    set(ulp_app_name "ulp_${COMPONENT_NAME}")
    set(ulp_sources "ulp/main.c")
    set(ulp_exp_dep_srcs "src/hal_io.c" "src/orch_wake_stub.c")
    ulp_embed_binary(${ulp_app_name} "${ulp_sources}" "${ulp_exp_dep_srcs}")
endif()
