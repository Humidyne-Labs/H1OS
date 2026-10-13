idf_component_register(SRCS "h1os_boot_hook.c"
                       INCLUDE_DIRS "."
                       PRIV_REQUIRES soc esp_rom hal log)

# Force the linker to include bootloader_before_init() from this static library archive
target_link_libraries(${COMPONENT_LIB} INTERFACE "-u bootloader_hooks_include")

