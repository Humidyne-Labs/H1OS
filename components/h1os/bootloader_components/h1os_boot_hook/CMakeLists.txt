idf_component_register(
    SRCS "h1os_boot_hook.c"
    INCLUDE_DIRS "."
    PRIV_REQUIRES bootloader_support soc esp_rom hal
)

# Force the linker to pull strong hook implementations from this archive
# instead of falling back to weak defaults in bootloader_support.
target_link_options(${COMPONENT_LIB} INTERFACE
    "-Wl,-u,bootloader_before_init"
    "-Wl,-u,bootloader_after_init"
)