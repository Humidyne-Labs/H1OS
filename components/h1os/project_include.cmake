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

# Fallback for ESP-IDF < v6.1 where subproject/CMakeLists.txt ignored EXTRA_COMPONENT_DIRS (Issue #7855)
idf_build_get_property(_h1os_idf_path IDF_PATH)
if(EXISTS "${_h1os_idf_path}/components/bootloader/subproject/CMakeLists.txt")
    file(READ "${_h1os_idf_path}/components/bootloader/subproject/CMakeLists.txt" _h1os_bl_subproj_cmake)
    if(NOT _h1os_bl_subproj_cmake MATCHES "foreach\\(extra_component_dir \\$\\{EXTRA_COMPONENT_DIRS\\}\\)")
        idf_build_get_property(_h1os_extra_cmake_args EXTRA_CMAKE_ARGS)
        if(NOT "-DPROJECT_EXTRA_COMPONENTS=${_h1os_bl_comp_dir}" IN_LIST _h1os_extra_cmake_args)
            idf_build_set_property(
                EXTRA_CMAKE_ARGS
                "-DPROJECT_EXTRA_COMPONENTS=${_h1os_bl_comp_dir}"
                APPEND
            )
        endif()
        unset(_h1os_extra_cmake_args)
    endif()
    unset(_h1os_bl_subproj_cmake)
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
unset(_h1os_idf_path)
unset(_h1os_build_dir)
