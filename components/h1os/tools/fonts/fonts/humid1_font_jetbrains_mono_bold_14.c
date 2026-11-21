/*******************************************************************************
 * Font: humid1_font_jetbrains_mono_bold_14 (jetbrains_mono bold)
 * Size: 14 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_icon_fa7_solid_14 (LVGL >= 9.6.0 Ready)
 * License: MIT AND OFL-1.1
 ******************************************************************************/

#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif

#ifndef HUMID1_FONT_JETBRAINS_MONO_BOLD_14
#define HUMID1_FONT_JETBRAINS_MONO_BOLD_14 1
#endif

#if HUMID1_FONT_JETBRAINS_MONO_BOLD_14

extern const lv_font_t humid1_icon_fa7_solid_14;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x10) */
    0xff, 0xf4, 0xf0,
    /* U+0022 "" (5x4) */
    0xde, 0xf7, 0xb0,
    /* U+0023 "#" (8x10) */
    0x12, 0x32, 0x7f, 0x7f, 0x26, 0x24, 0xff, 0x7e, 0x6c, 0x6c,
    /* U+0024 "$" (7x14) */
    0x10, 0x61, 0xf7, 0xed, 0x5e, 0x1e, 0x1e, 0x1f, 0xaf, 0xf3, 0xe1, 0x02,
    0x00,
    /* U+0025 "%" (8x10) */
    0x71, 0xd2, 0xd6, 0xfc, 0x08, 0x1e, 0x3f, 0x29, 0x4d, 0xc7,
    /* U+0026 "&" (7x10) */
    0x79, 0x9b, 0x03, 0x0e, 0x1e, 0xe7, 0x4e, 0xdd, 0xec,
    /* U+0027 "'" (2x4) */
    0xff,
    /* U+0028 "(" (5x13) */
    0x09, 0xdc, 0xcc, 0x63, 0x18, 0xc6, 0x18, 0xe3, 0x80,
    /* U+0029 ")" (4x12) */
    0xc6, 0x33, 0x33, 0x33, 0x33, 0xec,
    /* U+002A "" (7x8) */
    0x10, 0x62, 0xc7, 0xf3, 0x0f, 0x1b, 0x20,
    /* U+002B "+" (7x7) */
    0x30, 0x60, 0xe7, 0xf3, 0x06, 0x0c, 0x00,
    /* U+002C "," (3x4) */
    0x6f, 0x60,
    /* U+002D "-" (5x2) */
    0xf7, 0xc0,
    /* U+002E "." (3x3) */
    0x5f, 0x00,
    /* U+002F "/" (6x14) */
    0x04, 0x30, 0xc7, 0x18, 0x63, 0x0c, 0x31, 0x86, 0x38, 0xc3, 0x00,
    /* U+0030 "0" (7x10) */
    0x7d, 0x9b, 0x16, 0x3f, 0x7a, 0xf1, 0xe2, 0xec, 0xf0,
    /* U+0031 "1" (7x10) */
    0x79, 0xf2, 0x60, 0xc1, 0x83, 0x06, 0x0c, 0xff, 0xfc,
    /* U+0032 "2" (7x10) */
    0x7d, 0x9b, 0x30, 0x60, 0xc3, 0x0c, 0x30, 0xfd, 0xfc,
    /* U+0033 "3" (7x10) */
    0xfc, 0x38, 0x61, 0x83, 0xc1, 0x83, 0xe7, 0xfc, 0xf0,
    /* U+0034 "4" (6x10) */
    0x18, 0xe3, 0x18, 0xef, 0x3f, 0xff, 0x0c, 0x30,
    /* U+0035 "5" (6x10) */
    0xff, 0x0c, 0x36, 0xfc, 0x30, 0x43, 0xfd, 0xe0,
    /* U+0036 "6" (7x10) */
    0x18, 0x61, 0x83, 0x0f, 0xd9, 0xb1, 0xe3, 0xec, 0xf0,
    /* U+0037 "7" (7x10) */
    0xff, 0x9f, 0x30, 0x61, 0x83, 0x06, 0x18, 0x30, 0xc0,
    /* U+0038 "8" (7x10) */
    0x7d, 0x9b, 0x36, 0x67, 0x8f, 0xb3, 0x63, 0xec, 0xf0,
    /* U+0039 "9" (7x10) */
    0x7d, 0x9b, 0x1e, 0x3e, 0xcf, 0x87, 0x0c, 0x30, 0x60,
    /* U+003A ":" (3x8) */
    0xdd, 0x00, 0x3e,
    /* U+003B ";" (4x10) */
    0x67, 0x20, 0x00, 0x66, 0xec,
    /* U+003C "<" (6x7) */
    0x0c, 0xff, 0x30, 0xf0, 0x70, 0x40,
    /* U+003D "=" (6x5) */
    0xfd, 0xf0, 0x3f, 0xfc,
    /* U+003E ">" (6x7) */
    0xc1, 0xc1, 0xc3, 0x3f, 0xcc, 0x00,
    /* U+003F "?" (5x10) */
    0xf1, 0xc6, 0x37, 0xb1, 0x00, 0x47, 0x00,
    /* U+0040 "@" (8x13) */
    0x3e, 0x63, 0xc3, 0xcf, 0xdb, 0xdb, 0xdb, 0xdb, 0xdf, 0xc0, 0x60, 0x3c,
    0x08,
    /* U+0041 "A" (7x10) */
    0x38, 0x71, 0xe3, 0x46, 0xc9, 0xbf, 0x7e, 0xc7, 0x8c,
    /* U+0042 "B" (7x10) */
    0xfd, 0x9b, 0x1e, 0x6f, 0x99, 0xb1, 0xe3, 0xdd, 0xf0,
    /* U+0043 "C" (6x10) */
    0x7f, 0x3c, 0x70, 0xc3, 0x0c, 0x31, 0xfd, 0xe0,
    /* U+0044 "D" (7x10) */
    0xfd, 0xfb, 0x1e, 0x3c, 0x78, 0xf1, 0xe7, 0xfd, 0xf0,
    /* U+0045 "E" (6x10) */
    0xff, 0x0c, 0x30, 0xff, 0xfc, 0x30, 0xff, 0xf0,
    /* U+0046 "F" (7x10) */
    0xff, 0x83, 0x06, 0x0f, 0xdf, 0xb0, 0x60, 0xc1, 0x80,
    /* U+0047 "G" (7x10) */
    0x7d, 0x9b, 0x16, 0x0c, 0x1b, 0xf1, 0xe3, 0xfc, 0xf0,
    /* U+0048 "H" (7x10) */
    0xcf, 0x9f, 0x3e, 0x7f, 0xff, 0xf3, 0xe7, 0xcf, 0x9c,
    /* U+0049 "I" (6x10) */
    0xfc, 0xe3, 0x0c, 0x30, 0xc3, 0x0c, 0xff, 0xf0,
    /* U+004A "J" (7x10) */
    0x1e, 0x3c, 0x18, 0x30, 0x60, 0xc1, 0xe3, 0x7e, 0x78,
    /* U+004B "K" (7x10) */
    0xcf, 0x9b, 0x36, 0xcf, 0x9f, 0x37, 0x66, 0xcd, 0x8c,
    /* U+004C "L" (7x10) */
    0xc1, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xfd, 0xfc,
    /* U+004D "M" (7x10) */
    0xcf, 0x9f, 0xbf, 0xfb, 0x72, 0xe1, 0xc3, 0x87, 0x0c,
    /* U+004E "N" (7x10) */
    0xe7, 0xcf, 0x9f, 0xbf, 0x7a, 0xf7, 0xef, 0xcf, 0x9c,
    /* U+004F "O" (6x10) */
    0x7f, 0x3c, 0x71, 0xc7, 0x1c, 0x71, 0xed, 0xe0,
    /* U+0050 "P" (7x10) */
    0xfd, 0xff, 0x1e, 0x3f, 0xff, 0xb0, 0x60, 0xc1, 0x80,
    /* U+0051 "Q" (6x12) */
    0x7f, 0x3c, 0x71, 0xc7, 0x1c, 0x71, 0xed, 0xe1, 0x83,
    /* U+0052 "R" (7x10) */
    0xfd, 0x9b, 0x1e, 0x3f, 0xdf, 0x36, 0x66, 0xcd, 0x9c,
    /* U+0053 "S" (7x10) */
    0x7d, 0x9b, 0x06, 0x07, 0x87, 0x83, 0xe3, 0xfc, 0xf0,
    /* U+0054 "T" (7x10) */
    0xfe, 0x70, 0xc1, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x60,
    /* U+0055 "U" (7x10) */
    0xcf, 0x9f, 0x3e, 0x7c, 0xf9, 0xf3, 0xe7, 0xfc, 0xf0,
    /* U+0056 "V" (7x10) */
    0xc7, 0x8f, 0x36, 0x66, 0xcd, 0x9a, 0x3c, 0x38, 0x70,
    /* U+0057 "W" (8x10) */
    0xd9, 0xdb, 0xdb, 0x5b, 0x53, 0x57, 0x77, 0x76, 0x66, 0x66,
    /* U+0058 "X" (7x10) */
    0xcf, 0x99, 0xe3, 0xc3, 0x07, 0x1e, 0x36, 0xcd, 0x8c,
    /* U+0059 "Y" (7x10) */
    0xc7, 0x9b, 0x33, 0x47, 0x87, 0x0c, 0x18, 0x30, 0x60,
    /* U+005A "Z" (6x10) */
    0xfc, 0x71, 0xc6, 0x30, 0xc6, 0x18, 0xff, 0xf0,
    /* U+005B "[" (5x14) */
    0x77, 0xf9, 0xce, 0x73, 0x9c, 0xe7, 0x39, 0xcf, 0xb8,
    /* U+005C "" (6x14) */
    0xc3, 0x0e, 0x18, 0x60, 0xc3, 0x0c, 0x18, 0x61, 0xc3, 0x0c, 0x10,
    /* U+005D "]" (4x14) */
    0xff, 0x33, 0x33, 0x33, 0x33, 0x33, 0xff,
    /* U+005E "^" (6x5) */
    0x30, 0xe6, 0x93, 0xcc,
    /* U+005F "_" (7x2) */
    0xff, 0xfc,
    /* U+0060 "`" (2x2) */
    0xf0,
    /* U+0061 "a" (6x8) */
    0x3b, 0xfc, 0xcf, 0xff, 0x3c, 0xff,
    /* U+0062 "b" (7x10) */
    0xc1, 0x83, 0x67, 0xec, 0xf9, 0xf3, 0xe7, 0xfd, 0xf8,
    /* U+0063 "c" (7x8) */
    0x39, 0xfb, 0x3e, 0x0c, 0x18, 0xbf, 0x3c,
    /* U+0064 "d" (6x10) */
    0x0c, 0x37, 0xff, 0xcf, 0x3c, 0xf3, 0xfd, 0xf0,
    /* U+0065 "e" (7x8) */
    0x79, 0xfb, 0x37, 0xff, 0xd8, 0x3b, 0x3c,
    /* U+0066 "f" (7x10) */
    0x3e, 0x60, 0xc7, 0xff, 0xc6, 0x0c, 0x18, 0x30, 0x60,
    /* U+0067 "g" (6x11) */
    0x77, 0xfc, 0xf3, 0xcf, 0x3f, 0xcb, 0x0d, 0xf3, 0x00,
    /* U+0068 "h" (6x10) */
    0xc3, 0x0d, 0xbf, 0xcf, 0x3c, 0xf3, 0xcf, 0x30,
    /* U+0069 "i" (7x11) */
    0x30, 0x60, 0x03, 0x8f, 0x83, 0x06, 0x0c, 0x19, 0xff, 0xf8,
    /* U+006A "j" (6x14) */
    0x1c, 0x70, 0x1f, 0xfc, 0x71, 0xc7, 0x1c, 0x71, 0xc7, 0xfb, 0x80,
    /* U+006B "k" (7x10) */
    0xc1, 0x83, 0x1e, 0x6c, 0xdf, 0x3e, 0x6e, 0xcd, 0x8c,
    /* U+006C "l" (8x10) */
    0xf8, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1f, 0x0f,
    /* U+006D "m" (7x8) */
    0xad, 0xee, 0x5c, 0xb9, 0x72, 0xe5, 0xcb,
    /* U+006E "n" (7x8) */
    0xd9, 0xfb, 0x3e, 0x7c, 0xf9, 0xf3, 0xe7,
    /* U+006F "o" (7x8) */
    0x79, 0xfb, 0x36, 0x7c, 0xf9, 0xff, 0x3c,
    /* U+0070 "p" (7x11) */
    0xd9, 0xfb, 0x3e, 0x7c, 0xf9, 0xff, 0x7e, 0xc1, 0x83, 0x00,
    /* U+0071 "q" (6x11) */
    0x77, 0xfc, 0xf3, 0xcf, 0x3f, 0xdf, 0x0c, 0x30, 0x40,
    /* U+0072 "r" (7x8) */
    0xdd, 0xff, 0x1e, 0x3c, 0x18, 0x30, 0x60,
    /* U+0073 "s" (7x8) */
    0x79, 0xfb, 0x07, 0x83, 0xc0, 0xf3, 0xbe,
    /* U+0074 "t" (6x10) */
    0x20, 0xcf, 0xff, 0x30, 0xc3, 0x0c, 0x3c, 0x70,
    /* U+0075 "u" (7x8) */
    0xc5, 0x9f, 0x3e, 0x7c, 0xf9, 0xbf, 0x3c,
    /* U+0076 "v" (7x8) */
    0x87, 0x8f, 0x36, 0x66, 0xcf, 0x1e, 0x1c,
    /* U+0077 "w" (8x8) */
    0xc9, 0xdb, 0x5b, 0x5b, 0x57, 0x76, 0x76, 0x66,
    /* U+0078 "x" (7x8) */
    0xc5, 0xd9, 0xe1, 0xc3, 0x8f, 0x3b, 0x67,
    /* U+0079 "y" (7x11) */
    0x87, 0x8f, 0x33, 0x66, 0x8f, 0x0e, 0x18, 0x30, 0x60, 0x80,
    /* U+007A "z" (6x8) */
    0xff, 0xf1, 0xce, 0x31, 0x8f, 0xff,
    /* U+007B "{" (6x14) */
    0x0c, 0x71, 0x86, 0x18, 0x6f, 0x3c, 0x18, 0x61, 0x86, 0x1c, 0x10,
    /* U+007C "|" (2x14) */
    0xff, 0xff, 0xff, 0xd0,
    /* U+007D "}" (6x14) */
    0xc3, 0x83, 0x0c, 0x30, 0xc3, 0xcf, 0x30, 0xc3, 0x1c, 0xe3, 0x00,
    /* U+007E "~" (7x4) */
    0x41, 0xee, 0x78, 0x60,
    /* U+00B0 "" (4x4) */
    0xf9, 0xd6,
    /* U+00B1 "" (7x8) */
    0x30, 0x63, 0xf7, 0xf3, 0x06, 0x0e, 0x7f,
    /* U+00B2 "" (4x6) */
    0x6d, 0x13, 0x6f,
    /* U+00B3 "" (4x6) */
    0xf7, 0x23, 0x9f,
    /* U+00B5 "" (7x11) */
    0xcd, 0x9f, 0x3e, 0x7c, 0xf9, 0xff, 0x7e, 0xc1, 0x83, 0x00,
    /* U+00B7 "" (3x3) */
    0x5f, 0x00,
    /* U+00D7 "" (6x5) */
    0xcd, 0xe3, 0x9f, 0x4c,
    /* U+00F7 "" (6x7) */
    0x38, 0xc7, 0xff, 0x00, 0xc3, 0x00,
    /* U+0394 "" (7x10) */
    0x38, 0x71, 0xe3, 0x46, 0xc9, 0xb3, 0x66, 0xff, 0xfc,
    /* U+03A9 "" (7x10) */
    0x7d, 0x9b, 0x1e, 0x3c, 0x78, 0xf1, 0xf6, 0xef, 0xdc,
    /* U+03B1 "" (6x8) */
    0x77, 0xfc, 0xf3, 0xcf, 0x3f, 0xdf,
    /* U+03B2 "" (7x13) */
    0x7d, 0x9b, 0x1e, 0x6d, 0x9b, 0xb1, 0xe3, 0xfd, 0xf3, 0x06, 0x08, 0x00,
    /* U+03B3 "" (7x11) */
    0x87, 0x8f, 0x32, 0x66, 0x8f, 0x0e, 0x18, 0x30, 0x60, 0x40,
    /* U+03B4 "" (7x10) */
    0xfc, 0xc0, 0xc0, 0xc7, 0xd9, 0xf1, 0xe3, 0xfc, 0xf0,
    /* U+03B5 "" (7x8) */
    0x79, 0xfb, 0x03, 0x8f, 0x18, 0x33, 0xbe,
    /* U+03B8 "" (6x10) */
    0x7b, 0xbc, 0x71, 0xff, 0xfc, 0x73, 0xfd, 0xe0,
    /* U+03BB "" (7x10) */
    0x30, 0x60, 0xc1, 0xc3, 0x8d, 0x1b, 0x66, 0xcd, 0x8c,
    /* U+03BC "" (7x11) */
    0xcd, 0x9f, 0x3e, 0x7c, 0xf9, 0xff, 0x7e, 0xc1, 0x83, 0x00,
    /* U+03C0 "" (8x8) */
    0xff, 0xff, 0x66, 0x66, 0x66, 0x66, 0x67, 0x63,
    /* U+03C3 "" (7x8) */
    0x3d, 0xff, 0x36, 0x2c, 0x58, 0xbb, 0x3c,
    /* U+03C4 "" (7x8) */
    0xfd, 0xfc, 0xc1, 0x83, 0x06, 0x0f, 0x0e,
    /* U+03C6 "" (7x11) */
    0x99, 0x3a, 0x5c, 0xb9, 0x72, 0xff, 0xbe, 0x30, 0x60, 0x40,
    /* U+03C9 "" (7x8) */
    0x41, 0x9a, 0x1c, 0xb9, 0x72, 0xfd, 0xf6,
    /* U+2013 "" (6x1) */
    0xfc,
    /* U+2014 "" (9x2) */
    0xff, 0x7f, 0xc0,
    /* U+2018 "" (3x4) */
    0x6d, 0xf0,
    /* U+2019 "" (3x4) */
    0x6f, 0x60,
    /* U+201C "" (7x5) */
    0x66, 0xdb, 0xb6, 0xec, 0x80,
    /* U+201D "" (7x4) */
    0x6f, 0xdb, 0x36, 0x40,
    /* U+2022 "" (4x4) */
    0x7f, 0xf6,
    /* U+2026 "" (7x2) */
    0xb7, 0x6c,
    /* U+2030 "" (8x10) */
    0xe4, 0xb4, 0xb8, 0x70, 0x10, 0x20, 0x3f, 0x55, 0x95, 0x9f,
    /* U+2190 "" (7x9) */
    0x10, 0x41, 0x86, 0x0f, 0xf8, 0x18, 0x10, 0x10,
    /* U+2191 "" (8x10) */
    0x18, 0x3c, 0x6b, 0x89, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    /* U+2192 "" (7x8) */
    0x10, 0x30, 0x20, 0x2f, 0xe0, 0x82, 0x0c,
    /* U+2193 "" (8x10) */
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0xc9, 0x6a, 0x3c, 0x18,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 134, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 134, .box_w = 2, .box_h = 10, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 134, .box_w = 5, .box_h = 4, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 6, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 16, .adv_w = 134, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 29, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 39, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 48, .adv_w = 134, .box_w = 2, .box_h = 4, .ofs_x = 3, .ofs_y = 6},
    {.bitmap_index = 49, .adv_w = 134, .box_w = 5, .box_h = 13, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 58, .adv_w = 134, .box_w = 4, .box_h = 12, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 64, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 71, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 78, .adv_w = 134, .box_w = 3, .box_h = 4, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 80, .adv_w = 134, .box_w = 5, .box_h = 2, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 82, .adv_w = 134, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 84, .adv_w = 134, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 95, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 113, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 131, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 147, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 156, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 183, .adv_w = 134, .box_w = 3, .box_h = 8, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 186, .adv_w = 134, .box_w = 4, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 191, .adv_w = 134, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 197, .adv_w = 134, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 201, .adv_w = 134, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 207, .adv_w = 134, .box_w = 5, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 214, .adv_w = 134, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 227, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 236, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 245, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 253, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 262, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 270, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 279, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 288, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 297, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 305, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 314, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 323, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 332, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 341, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 350, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 358, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 367, .adv_w = 134, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 376, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 385, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 394, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 403, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 412, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 421, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 431, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 440, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 457, .adv_w = 134, .box_w = 5, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 466, .adv_w = 134, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 477, .adv_w = 134, .box_w = 4, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 484, .adv_w = 134, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 488, .adv_w = 134, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 490, .adv_w = 134, .box_w = 2, .box_h = 2, .ofs_x = 3, .ofs_y = 9},
    {.bitmap_index = 491, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 497, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 506, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 513, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 521, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 528, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 537, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 546, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 554, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 564, .adv_w = 134, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 575, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 584, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 594, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 601, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 608, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 615, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 625, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 634, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 641, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 648, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 656, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 663, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 670, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 678, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 685, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 695, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 701, .adv_w = 134, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 712, .adv_w = 134, .box_w = 2, .box_h = 14, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 716, .adv_w = 134, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 727, .adv_w = 134, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 731, .adv_w = 134, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 733, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 740, .adv_w = 134, .box_w = 4, .box_h = 6, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 743, .adv_w = 134, .box_w = 4, .box_h = 6, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 746, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 756, .adv_w = 134, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 4},
    {.bitmap_index = 758, .adv_w = 134, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 762, .adv_w = 134, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 768, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 777, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 786, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 792, .adv_w = 134, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 804, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 814, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 823, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 830, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 838, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 847, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 857, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 865, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 872, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 879, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 889, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 896, .adv_w = 134, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 897, .adv_w = 134, .box_w = 9, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 900, .adv_w = 134, .box_w = 3, .box_h = 4, .ofs_x = 3, .ofs_y = 7},
    {.bitmap_index = 902, .adv_w = 134, .box_w = 3, .box_h = 4, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 904, .adv_w = 134, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 909, .adv_w = 134, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 913, .adv_w = 134, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 915, .adv_w = 134, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 917, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 927, .adv_w = 134, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 935, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 945, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 952, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x0005, 0x0007, 0x0027, 0x0047, 0x02e4, 0x02f9,
    0x0301, 0x0302, 0x0303, 0x0304, 0x0305, 0x0308, 0x030b, 0x030c, 0x0310, 0x0313,
    0x0314, 0x0316, 0x0319, 0x1f63, 0x1f64, 0x1f68, 0x1f69, 0x1f6c, 0x1f6d, 0x1f72,
    0x1f76, 0x1f80, 0x20e0, 0x20e1, 0x20e2, 0x20e3,
};

static const lv_font_fmt_txt_cmap_t cmaps[] = {
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 176, .range_length = 8420, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 36, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

static const lv_font_fmt_txt_dsc_t font_dsc = {
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
};

/*-----------------
 *  PUBLIC FONT (LVGL >= 9.6.0)
 *----------------*/

const lv_font_t humid1_font_jetbrains_mono_bold_14 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 20,
    .base_line = 5,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 10,
    .x_height = 8,
#endif
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = -2,
    .underline_thickness = 1,
#if LV_VERSION_CHECK(9, 3, 0) || (LVGL_VERSION_MAJOR == 9 && LVGL_VERSION_MINOR >= 3) || LVGL_VERSION_MAJOR > 9
    .static_bitmap = 0,
#endif
    .dsc = &font_dsc,
#if LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_icon_fa7_solid_14,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_JETBRAINS_MONO_BOLD_14 */
