cmake_minimum_required(VERSION 3.16)

# Locate local H1OS components
set(EXTRA_COMPONENT_DIRS "../../components")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(h1os)