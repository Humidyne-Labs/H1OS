# Evaluated early during project configuration to register the BSP's
# 2nd-stage bootloader hook component without polluting application CMakeLists.txt
set(_h1os_bl_comp_dir "${CMAKE_CURRENT_LIST_DIR}/bootloader_components")

idf_build_get_property(_h1os_bl_extra_dirs BOOTLOADER_EXTRA_COMPONENT_DIRS)
if(NOT "${_h1os_bl_comp_dir}" IN_LIST _h1os_bl_extra_dirs)
    idf_build_set_property(
        BOOTLOADER_EXTRA_COMPONENT_DIRS
        "${_h1os_bl_comp_dir}"
        APPEND
    )
endif()

# Self-healing ExternalProject stamp: if build/bootloader/CMakeCache.txt was previously
# configured without bootloader_components, remove ONLY CMakeCache.txt and the configure
# stamp file (preserving bootloader-prefix/tmp/bootloader-cfgcmd.txt) so Ninja reconfigures it.
idf_build_get_property(_h1os_build_dir BUILD_DIR)
if(_h1os_build_dir AND EXISTS "${_h1os_build_dir}/bootloader/CMakeCache.txt")
    file(READ "${_h1os_build_dir}/bootloader/CMakeCache.txt" _h1os_bl_cache)
    if(NOT _h1os_bl_cache MATCHES "bootloader_components")
        message(STATUS "H1OS BSP: Invalidating stale bootloader configure stamp to link h1os_boot_hook...")
        file(REMOVE
            "${_h1os_build_dir}/bootloader/CMakeCache.txt"
            "${_h1os_build_dir}/bootloader-prefix/src/bootloader-stamp/bootloader-configure"
        )
    endif()
    unset(_h1os_bl_cache)
endif()

unset(_h1os_bl_comp_dir)
unset(_h1os_bl_extra_dirs)
unset(_h1os_build_dir)

# ==============================================================================
# H1OS Partition & CLI Tool Extension Provisioning
# Auto-provisions canonical `partitions.csv` and `idf_ext.py` into ${CMAKE_SOURCE_DIR}
# for all applications (in-tree examples and external components).
# ==============================================================================
set(H1OS_PARTITION_DIR "${CMAKE_CURRENT_LIST_DIR}/partition")

# 0. Auto-provision canonical 8MB Dual-OTA partitions.csv into the app root if missing.
#    Because `h1os` is processed before `partition_table` in ESP-IDF's project_include
#    phase, this prevents `parttool.py` FileNotFoundError in clean app directories.
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/partitions.csv" AND EXISTS "${H1OS_PARTITION_DIR}/partitions.csv")
    message(STATUS "[H1OS] Auto-provisioning canonical partitions.csv -> ${CMAKE_SOURCE_DIR}/partitions.csv")
    configure_file("${H1OS_PARTITION_DIR}/partitions.csv" "${CMAKE_SOURCE_DIR}/partitions.csv" COPYONLY)
endif()

# 1. Auto-provision idf_ext.py into the app root for instant CLI discovery.
if(NOT EXISTS "${CMAKE_SOURCE_DIR}/idf_ext.py" AND EXISTS "${CMAKE_CURRENT_LIST_DIR}/idf_ext.py")
    message(STATUS "[H1OS] Auto-provisioning idf_ext.py -> ${CMAKE_SOURCE_DIR}/idf_ext.py")
    configure_file("${CMAKE_CURRENT_LIST_DIR}/idf_ext.py" "${CMAKE_SOURCE_DIR}/idf_ext.py" COPYONLY)
endif()

unset(H1OS_PARTITION_DIR)
