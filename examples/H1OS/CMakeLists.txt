cmake_minimum_required(VERSION 3.20)

# Resolve local extra components using an absolute path
list(APPEND EXTRA_COMPONENT_DIRS "${CMAKE_CURRENT_LIST_DIR}/../../components")

# Fallback IDF_PATH validation
if(DEFINED ENV{IDF_PATH} AND NOT "$ENV{IDF_PATH}" STREQUAL "")
    set(IDF_PATH "$ENV{IDF_PATH}")
elseif(NOT DEFINED IDF_PATH OR IDF_PATH STREQUAL "")
    message(FATAL_ERROR "IDF_PATH is not set. Set it to your ESP-IDF installation directory before configuring this project.")
endif()

# Force CMake to use the ESP-IDF virtual environment Python
set(PYTHON "C:/Users/Matt/.espressif/python_env/idf6.1_py3.14_env/Scripts/python.exe" CACHE FILEPATH "Path to Python interpreter" FORCE)
set(ENV{PYTHON} "C:/Users/Matt/.espressif/python_env/idf6.1_py3.14_env/Scripts/python.exe")

include("${IDF_PATH}/tools/cmake/project.cmake")
project(h1os)