set(h1os_srcs
    "src/hal_io.c"
    "src/hal_i2c.c"
    "src/hal_spi.c"
    "src/hal_flash.c"
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
    esp_driver_ledc
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
    esp_pm
    esp_partition
    spi_flash
    esp_hw_support
    ulp
)

set(H1OS_DISTRO_FONT_DIR "${CMAKE_CURRENT_LIST_DIR}/tools/fonts/fonts")
file(GLOB H1OS_DISTRO_FONT_SRCS "${H1OS_DISTRO_FONT_DIR}/*.c")

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
    SRCS ${h1os_srcs} ${H1OS_DISTRO_FONT_SRCS}
    INCLUDE_DIRS "include" "include/h1os" "tools/fonts/fonts"
    REQUIRES ${bsp_requires}
)

# -----------------------------------------------------------------------------
# 1-BPP Bilevel EPD Typography Suite (h1os_distro / IBM Plex + Modular Icons)
# -----------------------------------------------------------------------------

idf_component_get_property(lvgl_lib lvgl__lvgl COMPONENT_LIB)
if(TARGET ${lvgl_lib})
    target_compile_definitions(${lvgl_lib} PUBLIC "LV_FONT_DEFAULT=&humid1_font_plex_sans_normal_14")
    target_include_directories(${lvgl_lib} PUBLIC "${H1OS_DISTRO_FONT_DIR}")
endif()
target_compile_definitions(${COMPONENT_LIB} PUBLIC "LV_FONT_DEFAULT=&humid1_font_plex_sans_normal_14")

# -----------------------------------------------------------------------------
# ULP CoProc
# -----------------------------------------------------------------------------

if(CONFIG_ULP_COPROC_ENABLED)
    set(ulp_app_name "ulp_${COMPONENT_NAME}")
    set(ulp_sources "ulp/main.c")
    set(ulp_exp_dep_srcs "src/hal_io.c" "src/orch_wake_stub.c" "src/sub_power.c" "src/orch_flow.c" "src/h1os_lifecycle.c")
    ulp_embed_binary(${ulp_app_name} "${ulp_sources}" "${ulp_exp_dep_srcs}")
endif()

# -----------------------------------------------------------------------------
# Compiler Hardening & Safety Enforcements (H1OS Layer 3)
# -----------------------------------------------------------------------------
target_compile_options(${COMPONENT_LIB} PRIVATE
    -Wall
    -Wextra
    -Werror
    -Wshadow
    -Wdouble-promotion
    -Wformat=2
    -Wno-format-nonliteral
    $<$<COMPILE_LANGUAGE:C>:-Wstrict-prototypes>
    -Wno-missing-field-initializers
)
