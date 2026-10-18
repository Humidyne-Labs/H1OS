idf_component_register(
    SRCS "power_hold_hook.c"
    INCLUDE_DIRS "."
    PRIV_REQUIRES bootloader_support soc esp_rom hal
)

target_link_options(${COMPONENT_LIB} INTERFACE
    "-Wl,-u,bootloader_before_init"
)
