cmake_minimum_required(VERSION 3.16)

# Locate local H1OS component
set(EXTRA_COMPONENT_DIRS "../../components")

# Standardize H1OS component requirements + project-specific overrides
set(SDKCONFIG_DEFAULTS
    "${CMAKE_CURRENT_LIST_DIR}/../../components/h1os/sdkconfig.defaults"
    "${CMAKE_CURRENT_LIST_DIR}/sdkconfig.defaults"
)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(h1os_boilerplate)
