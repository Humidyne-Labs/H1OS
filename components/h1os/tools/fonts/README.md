# `epd-font` v1.0.23 — Portable Embedded Firmware Font Distribution (`h1os`)

> **A 1-bit EPD font generator and asset pipeline for embedded displays**

- **Repository**: [https://github.com/Humidyne-Labs/epd-font](https://github.com/Humidyne-Labs/epd-font)
- **Version**: `v1.0.23`
- **Lead Designer & Developer**: [Humiditron](https://github.com/humiditron) (Humidyne Labs) & AI/LLM Development Partner
- **Pipeline & Tooling License**: MIT License (`LICENSE`)
- **Upstream Font & Icon Licenses**: SIL OFL 1.1, CC-BY 4.0, ISC, MIT (see `licenses/`)

## 1. Bundle Contents

- `humid1_epd_vault.json.gz`: Pre-rasterized 1-bit Strike Vault static build blob.
- `esp32s3-N8R8-hw_scheme.json` & `generic_hw.json`: Hardware partition scheme files (`3 MByte` = `3,145,728` bytes single partition budget, zero hardcoded fallbacks).
- `fonts/`: Pre-generated LVGL `>= 9.6.0` `.c` modules and `.h` headers (`humid1_fonts.h`, `h1os_fonts.h` / configured `compat_header`).
- `metrics/`: Per-strike `char_widths_<symbol>.csv` and `kern_pairs_<symbol>.csv` telemetry/layout manifests for DuckDB SQL and `embedded-ops` MCP tools.
- `tools/humid1_fw_emit.py` & `tools/humid1_cmake_font_builder.py`: Zero-dependency ESP-IDF CMake Python scripts.
- `CMakeLists.txt` & `cmake/epd_font_esp_idf.cmake`: Example ESP-IDF CMake integration files.
- `schemes/`: Declarative JSON font scheme configuration files.
- `licenses/`: Complete upstream font and icon license files (`FontAwesome7_LICENSE.txt`, `Lucide_ISC_LICENSE.txt`, `Noto_OFL.txt`, `Phosphor_MIT_LICENSE.txt`, `Tabler_MIT_LICENSE.txt`, `Terminus_OFL.txt`, `epd-font_MIT_LICENSE.txt`, `font_awsome_v7.3.1_LICENSE.txt`, `ibm-plex-font_LICENSE.txt`, `lucide_icons_v1.67.0_LICENSE.txt`, `noto_v2.013_LICENSE.txt`, `phosphor_icons_v2.1.0_LICENSE.txt`, `tabler_icons_v3.50.0_LICENSE.txt`, `terminus_v4.49.1_OFL.TXT`).
- `rom_space_estimate.txt` & `total_disk_size.txt`: Approximate `.rodata` ROM space breakdown per build, per font-file pair, and per strike against the `3 MByte` (`3,145,728` bytes) hardware partition.

## 2. Quick ESP-IDF CMake Integration

```cmake
include(${CMAKE_CURRENT_LIST_DIR}/cmake/epd_font_esp_idf.cmake)
epd_font_generate_lvgl_target(
    TARGET_NAME humid1_epd_fonts
    SCHEME      ${CMAKE_CURRENT_LIST_DIR}/schemes/h1os_full.scheme.json
    VAULT       ${CMAKE_CURRENT_LIST_DIR}/humid1_epd_vault.json.gz
    OUT_DIR     ${CMAKE_CURRENT_BINARY_DIR}/generated_fonts
)
target_link_libraries(${COMPONENT_LIB} PUBLIC humid1_epd_fonts)
```

## 3. Included Font & Icon Strikes (108 Strikes)

| Strike Symbol | Family | Style | Size | Source Asset | Glyphs | Kerning Pairs |
| :--- | :--- | :--- | :--- | :--- | ---: | ---: |
| `humid1_font_noto_sans_bold_14` | `noto_sans` | `bold` | `14 px` | `NotoSans-Black.ttf` | `119` | `0` |
| `humid1_font_noto_sans_bold_16` | `noto_sans` | `bold` | `16 px` | `NotoSans-Black.ttf` | `119` | `0` |
| `humid1_font_noto_sans_bold_20` | `noto_sans` | `bold` | `20 px` | `NotoSans-Black.ttf` | `119` | `0` |
| `humid1_font_noto_sans_italic_14` | `noto_sans` | `italic` | `14 px` | `NotoSans-SemiBoldItalic.ttf` | `119` | `0` |
| `humid1_font_noto_sans_italic_16` | `noto_sans` | `italic` | `16 px` | `NotoSans-SemiBoldItalic.ttf` | `119` | `0` |
| `humid1_font_noto_sans_normal_14` | `noto_sans` | `normal` | `14 px` | `NotoSans-Medium.ttf` | `119` | `0` |
| `humid1_font_noto_sans_normal_16` | `noto_sans` | `normal` | `16 px` | `NotoSans-Medium.ttf` | `119` | `0` |
| `humid1_font_noto_sans_normal_20` | `noto_sans` | `normal` | `20 px` | `NotoSans-Medium.ttf` | `119` | `0` |
| `humid1_font_plex_cond_bold_14` | `cond` | `bold` | `14 px` | `NotoSans-SemiCondensedBlack.ttf` | `119` | `0` |
| `humid1_font_plex_cond_bold_16` | `cond` | `bold` | `16 px` | `NotoSans-SemiCondensedBlack.ttf` | `119` | `0` |
| `humid1_font_plex_cond_bold_18` | `cond` | `bold` | `18 px` | `NotoSans-SemiCondensedBlack.ttf` | `119` | `0` |
| `humid1_font_plex_cond_bold_20` | `cond` | `bold` | `20 px` | `NotoSans-SemiCondensedBlack.ttf` | `119` | `0` |
| `humid1_font_plex_cond_bold_24` | `cond` | `bold` | `24 px` | `NotoSans-SemiCondensedBlack.ttf` | `119` | `0` |
| `humid1_font_plex_cond_italic_14` | `cond` | `italic` | `14 px` | `NotoSans-SemiCondensedSemiBoldItalic.ttf` | `119` | `0` |
| `humid1_font_plex_cond_italic_16` | `cond` | `italic` | `16 px` | `NotoSans-SemiCondensedSemiBoldItalic.ttf` | `119` | `0` |
| `humid1_font_plex_cond_italic_18` | `cond` | `italic` | `18 px` | `NotoSans-SemiCondensedSemiBoldItalic.ttf` | `119` | `0` |
| `humid1_font_plex_cond_italic_20` | `cond` | `italic` | `20 px` | `NotoSans-SemiCondensedSemiBoldItalic.ttf` | `119` | `0` |
| `humid1_font_plex_cond_normal_14` | `cond` | `normal` | `14 px` | `NotoSans-SemiCondensedMedium.ttf` | `119` | `0` |
| `humid1_font_plex_cond_normal_16` | `cond` | `normal` | `16 px` | `NotoSans-SemiCondensedMedium.ttf` | `119` | `0` |
| `humid1_font_plex_cond_normal_18` | `cond` | `normal` | `18 px` | `NotoSans-SemiCondensedMedium.ttf` | `119` | `0` |
| `humid1_font_plex_cond_normal_20` | `cond` | `normal` | `20 px` | `NotoSans-SemiCondensedMedium.ttf` | `119` | `0` |
| `humid1_font_plex_cond_normal_24` | `cond` | `normal` | `24 px` | `NotoSans-SemiCondensedMedium.ttf` | `119` | `0` |
| `humid1_font_plex_math_regular_14` | `math` | `regular` | `14 px` | `NotoSansMath-Regular.ttf` | `131` | `0` |
| `humid1_font_plex_math_regular_16` | `math` | `regular` | `16 px` | `NotoSansMath-Regular.ttf` | `131` | `0` |
| `humid1_font_plex_math_regular_20` | `math` | `regular` | `20 px` | `NotoSansMath-Regular.ttf` | `131` | `0` |
| `humid1_font_plex_math_regular_24` | `math` | `regular` | `24 px` | `NotoSansMath-Regular.ttf` | `131` | `0` |
| `humid1_font_plex_mono_bold_12` | `mono` | `bold` | `12 px` | `IBMPlexMono-ExtraBold.ttf` | `119` | `0` |
| `humid1_font_plex_mono_bold_14` | `mono` | `bold` | `14 px` | `IBMPlexMono-ExtraBold.ttf` | `119` | `0` |
| `humid1_font_plex_mono_bold_16` | `mono` | `bold` | `16 px` | `IBMPlexMono-ExtraBold.ttf` | `119` | `0` |
| `humid1_font_plex_mono_bold_18` | `mono` | `bold` | `18 px` | `IBMPlexMono-ExtraBold.ttf` | `119` | `0` |
| `humid1_font_plex_mono_bold_20` | `mono` | `bold` | `20 px` | `IBMPlexMono-ExtraBold.ttf` | `119` | `0` |
| `humid1_font_plex_mono_bold_24` | `mono` | `bold` | `24 px` | `IBMPlexMono-ExtraBold.ttf` | `119` | `0` |
| `humid1_font_plex_mono_bold_32` | `mono` | `bold` | `32 px` | `IBMPlexMono-ExtraBold.ttf` | `119` | `0` |
| `humid1_font_plex_mono_italic_12` | `mono` | `italic` | `12 px` | `IBMPlexMono-SemiBoldItalic.ttf` | `119` | `0` |
| `humid1_font_plex_mono_italic_14` | `mono` | `italic` | `14 px` | `IBMPlexMono-SemiBoldItalic.ttf` | `119` | `0` |
| `humid1_font_plex_mono_italic_16` | `mono` | `italic` | `16 px` | `IBMPlexMono-SemiBoldItalic.ttf` | `119` | `0` |
| `humid1_font_plex_mono_italic_18` | `mono` | `italic` | `18 px` | `IBMPlexMono-SemiBoldItalic.ttf` | `119` | `0` |
| `humid1_font_plex_mono_italic_20` | `mono` | `italic` | `20 px` | `IBMPlexMono-SemiBoldItalic.ttf` | `119` | `0` |
| `humid1_font_plex_mono_normal_12` | `mono` | `normal` | `12 px` | `IBMPlexMono-Medium.ttf` | `119` | `0` |
| `humid1_font_plex_mono_normal_14` | `mono` | `normal` | `14 px` | `IBMPlexMono-Medium.ttf` | `119` | `0` |
| `humid1_font_plex_mono_normal_16` | `mono` | `normal` | `16 px` | `IBMPlexMono-Medium.ttf` | `119` | `0` |
| `humid1_font_plex_mono_normal_18` | `mono` | `normal` | `18 px` | `IBMPlexMono-Medium.ttf` | `119` | `0` |
| `humid1_font_plex_mono_normal_20` | `mono` | `normal` | `20 px` | `IBMPlexMono-Medium.ttf` | `119` | `0` |
| `humid1_font_plex_mono_normal_24` | `mono` | `normal` | `24 px` | `IBMPlexMono-Medium.ttf` | `119` | `0` |
| `humid1_font_plex_mono_normal_32` | `mono` | `normal` | `32 px` | `IBMPlexMono-Medium.ttf` | `119` | `0` |
| `humid1_font_plex_sans_bold_12` | `sans` | `bold` | `12 px` | `IBMPlexSans-ExtraBold.ttf` | `119` | `0` |
| `humid1_font_plex_sans_bold_14` | `sans` | `bold` | `14 px` | `IBMPlexSans-ExtraBold.ttf` | `119` | `0` |
| `humid1_font_plex_sans_bold_16` | `sans` | `bold` | `16 px` | `IBMPlexSans-ExtraBold.ttf` | `119` | `0` |
| `humid1_font_plex_sans_bold_18` | `sans` | `bold` | `18 px` | `IBMPlexSans-ExtraBold.ttf` | `119` | `0` |
| `humid1_font_plex_sans_bold_20` | `sans` | `bold` | `20 px` | `IBMPlexSans-ExtraBold.ttf` | `119` | `0` |
| `humid1_font_plex_sans_bold_24` | `sans` | `bold` | `24 px` | `IBMPlexSans-ExtraBold.ttf` | `119` | `0` |
| `humid1_font_plex_sans_bold_32` | `sans` | `bold` | `32 px` | `IBMPlexSans-ExtraBold.ttf` | `119` | `0` |
| `humid1_font_plex_sans_italic_12` | `sans` | `italic` | `12 px` | `IBMPlexSans-SemiBoldItalic.ttf` | `119` | `0` |
| `humid1_font_plex_sans_italic_14` | `sans` | `italic` | `14 px` | `IBMPlexSans-SemiBoldItalic.ttf` | `119` | `0` |
| `humid1_font_plex_sans_italic_16` | `sans` | `italic` | `16 px` | `IBMPlexSans-SemiBoldItalic.ttf` | `119` | `0` |
| `humid1_font_plex_sans_italic_18` | `sans` | `italic` | `18 px` | `IBMPlexSans-SemiBoldItalic.ttf` | `119` | `0` |
| `humid1_font_plex_sans_italic_20` | `sans` | `italic` | `20 px` | `IBMPlexSans-SemiBoldItalic.ttf` | `119` | `0` |
| `humid1_font_plex_sans_italic_24` | `sans` | `italic` | `24 px` | `IBMPlexSans-SemiBoldItalic.ttf` | `119` | `0` |
| `humid1_font_plex_sans_normal_12` | `sans` | `normal` | `12 px` | `IBMPlexSans-Medium.ttf` | `119` | `0` |
| `humid1_font_plex_sans_normal_14` | `sans` | `normal` | `14 px` | `IBMPlexSans-Medium.ttf` | `119` | `0` |
| `humid1_font_plex_sans_normal_16` | `sans` | `normal` | `16 px` | `IBMPlexSans-Medium.ttf` | `119` | `0` |
| `humid1_font_plex_sans_normal_18` | `sans` | `normal` | `18 px` | `IBMPlexSans-Medium.ttf` | `119` | `0` |
| `humid1_font_plex_sans_normal_20` | `sans` | `normal` | `20 px` | `IBMPlexSans-Medium.ttf` | `119` | `0` |
| `humid1_font_plex_sans_normal_24` | `sans` | `normal` | `24 px` | `IBMPlexSans-Medium.ttf` | `119` | `0` |
| `humid1_font_plex_sans_normal_32` | `sans` | `normal` | `32 px` | `IBMPlexSans-Medium.ttf` | `119` | `0` |
| `humid1_font_plex_serif_bold_16` | `serif` | `bold` | `16 px` | `NotoSerif-Black.ttf` | `119` | `0` |
| `humid1_font_plex_serif_bold_18` | `serif` | `bold` | `18 px` | `NotoSerif-Black.ttf` | `119` | `0` |
| `humid1_font_plex_serif_bold_20` | `serif` | `bold` | `20 px` | `NotoSerif-Black.ttf` | `119` | `0` |
| `humid1_font_plex_serif_bold_24` | `serif` | `bold` | `24 px` | `NotoSerif-Black.ttf` | `119` | `0` |
| `humid1_font_plex_serif_italic_16` | `serif` | `italic` | `16 px` | `NotoSerif-MediumItalic.ttf` | `119` | `0` |
| `humid1_font_plex_serif_italic_18` | `serif` | `italic` | `18 px` | `NotoSerif-MediumItalic.ttf` | `119` | `0` |
| `humid1_font_plex_serif_italic_20` | `serif` | `italic` | `20 px` | `NotoSerif-MediumItalic.ttf` | `119` | `0` |
| `humid1_font_plex_serif_italic_24` | `serif` | `italic` | `24 px` | `NotoSerif-MediumItalic.ttf` | `119` | `0` |
| `humid1_font_plex_serif_normal_16` | `serif` | `normal` | `16 px` | `NotoSerif-Medium.ttf` | `119` | `0` |
| `humid1_font_plex_serif_normal_18` | `serif` | `normal` | `18 px` | `NotoSerif-Medium.ttf` | `119` | `0` |
| `humid1_font_plex_serif_normal_20` | `serif` | `normal` | `20 px` | `NotoSerif-Medium.ttf` | `119` | `0` |
| `humid1_font_plex_serif_normal_24` | `serif` | `normal` | `24 px` | `NotoSerif-Medium.ttf` | `119` | `0` |
| `humid1_font_terminus_bold_12` | `terminus` | `bold` | `12 px` | `Terminus-Bold-12.ttf` | `131` | `0` |
| `humid1_font_terminus_bold_14` | `terminus` | `bold` | `14 px` | `Terminus-Bold-14.ttf` | `131` | `0` |
| `humid1_font_terminus_bold_16` | `terminus` | `bold` | `16 px` | `Terminus-Bold-16.ttf` | `131` | `0` |
| `humid1_font_terminus_bold_20` | `terminus` | `bold` | `20 px` | `Terminus-Bold-20.ttf` | `131` | `0` |
| `humid1_font_terminus_normal_12` | `terminus` | `normal` | `12 px` | `Terminus-Normal-12.ttf` | `131` | `0` |
| `humid1_font_terminus_normal_14` | `terminus` | `normal` | `14 px` | `Terminus-Normal-14.ttf` | `131` | `0` |
| `humid1_font_terminus_normal_16` | `terminus` | `normal` | `16 px` | `Terminus-Normal-16.ttf` | `131` | `0` |
| `humid1_font_terminus_normal_20` | `terminus` | `normal` | `20 px` | `Terminus-Normal-20.ttf` | `131` | `0` |
| `humid1_icon_fa7_solid_12` | `icon_fa7` | `solid` | `12 px` | `FontAwesome7-Solid.ttf` | `87` | `0` |
| `humid1_icon_fa7_solid_14` | `icon_fa7` | `solid` | `14 px` | `FontAwesome7-Solid.ttf` | `87` | `0` |
| `humid1_icon_fa7_solid_16` | `icon_fa7` | `solid` | `16 px` | `FontAwesome7-Solid.ttf` | `87` | `0` |
| `humid1_icon_fa7_solid_18` | `icon_fa7` | `solid` | `18 px` | `FontAwesome7-Solid.ttf` | `87` | `0` |
| `humid1_icon_fa7_solid_20` | `icon_fa7` | `solid` | `20 px` | `FontAwesome7-Solid.ttf` | `87` | `0` |
| `humid1_icon_fa7_solid_24` | `icon_fa7` | `solid` | `24 px` | `FontAwesome7-Solid.ttf` | `87` | `0` |
| `humid1_icon_fa7_solid_32` | `icon_fa7` | `solid` | `32 px` | `FontAwesome7-Solid.ttf` | `87` | `0` |
| `humid1_icon_lucide_regular_14` | `icon_lucide` | `regular` | `14 px` | `Lucide-Regular.ttf` | `81` | `0` |
| `humid1_icon_lucide_regular_16` | `icon_lucide` | `regular` | `16 px` | `Lucide-Regular.ttf` | `81` | `0` |
| `humid1_icon_lucide_regular_20` | `icon_lucide` | `regular` | `20 px` | `Lucide-Regular.ttf` | `81` | `0` |
| `humid1_icon_lucide_regular_24` | `icon_lucide` | `regular` | `24 px` | `Lucide-Regular.ttf` | `81` | `0` |
| `humid1_icon_phosphor_fill_16` | `icon_phosphor` | `fill` | `16 px` | `Phosphor-Fill.ttf` | `129` | `0` |
| `humid1_icon_phosphor_fill_20` | `icon_phosphor` | `fill` | `20 px` | `Phosphor-Fill.ttf` | `129` | `0` |
| `humid1_icon_phosphor_regular_14` | `icon_phosphor` | `regular` | `14 px` | `Phosphor-Regular.ttf` | `129` | `0` |
| `humid1_icon_phosphor_regular_16` | `icon_phosphor` | `regular` | `16 px` | `Phosphor-Regular.ttf` | `129` | `0` |
| `humid1_icon_phosphor_regular_20` | `icon_phosphor` | `regular` | `20 px` | `Phosphor-Regular.ttf` | `129` | `0` |
| `humid1_icon_phosphor_regular_24` | `icon_phosphor` | `regular` | `24 px` | `Phosphor-Regular.ttf` | `129` | `0` |
| `humid1_icon_tabler_filled_16` | `icon_tabler` | `filled` | `16 px` | `Tabler-Filled.ttf` | `151` | `0` |
| `humid1_icon_tabler_filled_20` | `icon_tabler` | `filled` | `20 px` | `Tabler-Filled.ttf` | `151` | `0` |
| `humid1_icon_tabler_regular_14` | `icon_tabler` | `regular` | `14 px` | `Tabler-Regular.ttf` | `70` | `0` |
| `humid1_icon_tabler_regular_16` | `icon_tabler` | `regular` | `16 px` | `Tabler-Regular.ttf` | `70` | `0` |
| `humid1_icon_tabler_regular_20` | `icon_tabler` | `regular` | `20 px` | `Tabler-Regular.ttf` | `70` | `0` |
| `humid1_icon_tabler_regular_24` | `icon_tabler` | `regular` | `24 px` | `Tabler-Regular.ttf` | `70` | `0` |
