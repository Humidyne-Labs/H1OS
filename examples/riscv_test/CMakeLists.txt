cmake_minimum_required(VERSION 3.20)

# Minimal component set for ULP test suite (bypasses unused components like esp_lcd)
set(COMPONENTS main ulp esp_hw_support driver soc esp_rom hal esp_timer esp_system freertos log esp_pm esptool_py partition_table)

# Fallback IDF_PATH validation
if(DEFINED ENV{IDF_PATH} AND NOT "$ENV{IDF_PATH}" STREQUAL "")
    set(IDF_PATH "$ENV{IDF_PATH}")
elseif(NOT DEFINED IDF_PATH OR IDF_PATH STREQUAL "")
    message(FATAL_ERROR "IDF_PATH is not set. Set it to your ESP-IDF installation directory before configuring this project.")
endif()

include("${IDF_PATH}/tools/cmake/project.cmake")
project(riscv_test)
