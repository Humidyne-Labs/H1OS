idf_component_register(
    SRCS "main.c"
    INCLUDE_DIRS "."
    REQUIRES ulp esp_hw_support driver soc esp_rom hal esp_timer
)

set(ulp_app_name ulp_riscv_test)
set(ulp_sources "ulp/ulp_test_main.c")
set(ulp_exp_dep_srcs "main.c")
ulp_embed_binary(${ulp_app_name} "${ulp_sources}" "${ulp_exp_dep_srcs}" TYPE riscv)
