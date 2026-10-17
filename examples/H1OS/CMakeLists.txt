cmake_minimum_required(VERSION 3.20)

# Resolve local extra components using an absolute path
list(APPEND EXTRA_COMPONENT_DIRS "${CMAKE_CURRENT_LIST_DIR}/../../components")

# Fallback IDF_PATH validation
if(DEFINED ENV{IDF_PATH} AND NOT "$ENV{IDF_PATH}" STREQUAL "")
    set(IDF_PATH "$ENV{IDF_PATH}")
elseif(NOT DEFINED IDF_PATH OR IDF_PATH STREQUAL "")
    message(FATAL_ERROR "IDF_PATH is not set. Set it to your ESP-IDF installation directory before configuring this project.")
endif()


include("${IDF_PATH}/tools/cmake/project.cmake")
project(h1os)

# Suppress compiler warnings originating strictly within external/managed libraries (e.g., LVGL)
# without relaxing warning diagnostics on our own codebase:
if(TARGET __idf_lvgl__lvgl)
    # 1. Silence compiler warnings when building LVGL's own C/C++ source files (e.g., lv_freertos.c)
    target_compile_options(__idf_lvgl__lvgl PRIVATE -w)

    # 2. Treat LVGL headers as SYSTEM includes (-isystem) so any macro or header warnings
    #    included inside our code are suppressed, while our own code remains strictly checked
    set_target_properties(__idf_lvgl__lvgl PROPERTIES SYSTEM TRUE)
endif()