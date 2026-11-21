/*******************************************************************************
 * Font: humid1_font_jetbrains_mono_normal_14 (jetbrains_mono normal)
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

#ifndef HUMID1_FONT_JETBRAINS_MONO_NORMAL_14
#define HUMID1_FONT_JETBRAINS_MONO_NORMAL_14 1
#endif

#if HUMID1_FONT_JETBRAINS_MONO_NORMAL_14

extern const lv_font_t humid1_icon_fa7_solid_14;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x10) */
    0xff, 0xf4, 0xf0,
    /* U+0022 "" (5x4) */
    0xde, 0xf7, 0x20,
    /* U+0023 "#" (7x10) */
    0x24, 0x4b, 0xff, 0xf4, 0x89, 0x3f, 0x6c, 0xc9, 0x30,
    /* U+0024 "$" (6x14) */
    0x10, 0x47, 0xf7, 0xd3, 0x47, 0x87, 0x16, 0x5d, 0xde, 0x10, 0x40,
    /* U+0025 "%" (8x10) */
    0x71, 0x92, 0x94, 0xf4, 0x08, 0x16, 0x3f, 0x29, 0x49, 0xc7,
    /* U+0026 "&" (7x10) */
    0x79, 0x9b, 0x02, 0x0e, 0x16, 0xe7, 0x46, 0xdd, 0xec,
    /* U+0027 "'" (2x4) */
    0xfd,
    /* U+0028 "(" (5x14) */
    0x09, 0xd8, 0xcc, 0x63, 0x18, 0xc6, 0x18, 0xe3, 0x84,
    /* U+0029 ")" (4x12) */
    0xc6, 0x33, 0x33, 0x33, 0x33, 0x6c,
    /* U+002A "" (7x6) */
    0x10, 0x23, 0xf9, 0x83, 0x89, 0x80,
    /* U+002B "+" (7x7) */
    0x30, 0x60, 0xc7, 0xf3, 0x06, 0x04, 0x00,
    /* U+002C "," (3x4) */
    0x6d, 0x60,
    /* U+002D "-" (5x2) */
    0xf7, 0xc0,
    /* U+002E "." (2x2) */
    0xf0,
    /* U+002F "/" (6x14) */
    0x04, 0x30, 0xc2, 0x18, 0x61, 0x0c, 0x21, 0x86, 0x10, 0xc2, 0x00,
    /* U+0030 "0" (6x10) */
    0x7b, 0x38, 0x61, 0xb6, 0x58, 0x71, 0xcd, 0xe0,
    /* U+0031 "1" (7x10) */
    0x79, 0xf2, 0x60, 0xc1, 0x83, 0x06, 0x0c, 0x7d, 0xfc,
    /* U+0032 "2" (6x10) */
    0x7b, 0x38, 0x41, 0x0c, 0x63, 0x18, 0xe3, 0xf0,
    /* U+0033 "3" (6x10) */
    0xfc, 0x31, 0x8c, 0x3c, 0x30, 0x61, 0xcd, 0xe0,
    /* U+0034 "4" (6x10) */
    0x18, 0x63, 0x18, 0x67, 0x1f, 0xff, 0x04, 0x10,
    /* U+0035 "5" (6x10) */
    0xff, 0x0c, 0x36, 0xfc, 0x10, 0x41, 0xcd, 0xe0,
    /* U+0036 "6" (7x10) */
    0x10, 0x60, 0x83, 0x0f, 0xd8, 0xa1, 0xc2, 0xcc, 0xf0,
    /* U+0037 "7" (7x10) */
    0xff, 0x8a, 0x30, 0x60, 0x83, 0x04, 0x18, 0x30, 0x40,
    /* U+0038 "8" (6x10) */
    0x7b, 0x3c, 0x53, 0x39, 0xbc, 0x71, 0xcd, 0xe0,
    /* U+0039 "9" (7x10) */
    0x7d, 0x9a, 0x1c, 0x2c, 0xcf, 0x82, 0x0c, 0x30, 0x40,
    /* U+003A ":" (2x8) */
    0xf0, 0x0f,
    /* U+003B ";" (3x10) */
    0x6c, 0x00, 0x1b, 0x58,
    /* U+003C "<" (6x7) */
    0x0c, 0xee, 0x30, 0x70, 0x70, 0x40,
    /* U+003D "=" (6x5) */
    0xfc, 0x00, 0x3f, 0xfc,
    /* U+003E ">" (6x7) */
    0xc1, 0xc1, 0xc3, 0x1d, 0xcc, 0x00,
    /* U+003F "?" (5x10) */
    0xf0, 0xc6, 0x37, 0x31, 0x00, 0x47, 0x00,
    /* U+0040 "@" (7x12) */
    0x7d, 0x8e, 0x0c, 0xfb, 0x76, 0x6c, 0xd9, 0x9f, 0x03, 0x03, 0x80,
    /* U+0041 "A" (7x10) */
    0x30, 0x70, 0xe3, 0x44, 0x89, 0xbf, 0x66, 0xc5, 0x0c,
    /* U+0042 "B" (7x10) */
    0xf9, 0x9b, 0x16, 0x6f, 0x99, 0xb1, 0x63, 0xcd, 0xf0,
    /* U+0043 "C" (6x10) */
    0x7f, 0x3c, 0x70, 0xc3, 0x0c, 0x31, 0xcd, 0xe0,
    /* U+0044 "D" (6x10) */
    0xfb, 0x3c, 0x71, 0xc7, 0x1c, 0x71, 0xcf, 0xe0,
    /* U+0045 "E" (6x10) */
    0xff, 0x0c, 0x30, 0xff, 0x0c, 0x30, 0xc3, 0xf0,
    /* U+0046 "F" (6x10) */
    0xff, 0x0c, 0x30, 0xff, 0xfc, 0x30, 0xc3, 0x00,
    /* U+0047 "G" (6x10) */
    0x7f, 0x3c, 0x70, 0xc3, 0x7c, 0x71, 0xcd, 0xe0,
    /* U+0048 "H" (6x10) */
    0xc7, 0x1c, 0x71, 0xff, 0x3c, 0x71, 0xc7, 0x10,
    /* U+0049 "I" (6x10) */
    0xfc, 0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0x33, 0xf0,
    /* U+004A "J" (7x10) */
    0x1e, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0xe3, 0x66, 0x78,
    /* U+004B "K" (7x10) */
    0xc5, 0x9b, 0x26, 0xcf, 0x9b, 0x32, 0x66, 0xc5, 0x8c,
    /* U+004C "L" (7x10) */
    0xc1, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xfd, 0xfc,
    /* U+004D "M" (6x10) */
    0xcf, 0x3e, 0xef, 0xb6, 0x58, 0x61, 0x86, 0x10,
    /* U+004E "N" (6x10) */
    0xc7, 0x9e, 0x79, 0xf7, 0x5d, 0xf7, 0xcf, 0x30,
    /* U+004F "O" (6x10) */
    0x7b, 0x3c, 0x71, 0xc7, 0x1c, 0x71, 0xcd, 0xe0,
    /* U+0050 "P" (7x10) */
    0xfd, 0x8b, 0x1e, 0x3c, 0xdf, 0x30, 0x60, 0xc1, 0x80,
    /* U+0051 "Q" (6x13) */
    0x7b, 0x3c, 0x71, 0xc7, 0x1c, 0x71, 0xcd, 0xe0, 0x83, 0x04,
    /* U+0052 "R" (7x10) */
    0xfd, 0x9b, 0x1e, 0x3f, 0xdf, 0x36, 0x66, 0xcd, 0x8c,
    /* U+0053 "S" (6x10) */
    0x7f, 0x3c, 0x30, 0x78, 0x70, 0x61, 0xcd, 0xe0,
    /* U+0054 "T" (7x10) */
    0xfe, 0x60, 0xc1, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x60,
    /* U+0055 "U" (6x10) */
    0xc7, 0x1c, 0x71, 0xc7, 0x1c, 0x71, 0xcd, 0xe0,
    /* U+0056 "V" (7x10) */
    0x87, 0x8b, 0x12, 0x64, 0xcd, 0x1a, 0x1c, 0x38, 0x60,
    /* U+0057 "W" (8x10) */
    0xd9, 0xd9, 0x59, 0x5b, 0x53, 0x56, 0x76, 0x66, 0x66, 0x66,
    /* U+0058 "X" (7x10) */
    0xc4, 0x99, 0xa1, 0xc3, 0x06, 0x1e, 0x26, 0xcd, 0x0c,
    /* U+0059 "Y" (7x10) */
    0x87, 0x89, 0x33, 0x43, 0x86, 0x0c, 0x18, 0x30, 0x60,
    /* U+005A "Z" (6x10) */
    0xfc, 0x30, 0x86, 0x10, 0xc6, 0x10, 0xc3, 0xf0,
    /* U+005B "[" (3x14) */
    0xfe, 0x49, 0x24, 0x92, 0x4f, 0xc0,
    /* U+005C "" (6x14) */
    0x83, 0x04, 0x18, 0x60, 0x83, 0x04, 0x18, 0x60, 0x83, 0x0c, 0x10,
    /* U+005D "]" (4x13) */
    0xef, 0x33, 0x33, 0x33, 0x33, 0x33, 0xf0,
    /* U+005E "^" (6x5) */
    0x30, 0xe6, 0x93, 0xc4,
    /* U+005F "_" (6x2) */
    0xff, 0xf0,
    /* U+0060 "`" (2x2) */
    0x90,
    /* U+0061 "a" (6x8) */
    0x39, 0xf0, 0x4f, 0xfe, 0x1c, 0xdf,
    /* U+0062 "b" (6x10) */
    0xc3, 0x0d, 0xbf, 0xc7, 0x1c, 0x71, 0xcf, 0xe0,
    /* U+0063 "c" (6x8) */
    0x39, 0xfc, 0x70, 0xc3, 0x1c, 0xde,
    /* U+0064 "d" (6x10) */
    0x04, 0x17, 0x7f, 0xc7, 0x1c, 0x71, 0xcd, 0xf0,
    /* U+0065 "e" (6x8) */
    0x3b, 0xbc, 0x7f, 0xff, 0x0c, 0xde,
    /* U+0066 "f" (7x10) */
    0x3e, 0x60, 0xc7, 0xff, 0xc6, 0x0c, 0x18, 0x30, 0x60,
    /* U+0067 "g" (6x11) */
    0x77, 0xfc, 0x71, 0xc7, 0x37, 0xc9, 0x05, 0xf3, 0x00,
    /* U+0068 "h" (6x10) */
    0xc3, 0x0d, 0xbf, 0xc7, 0x1c, 0x71, 0xc7, 0x10,
    /* U+0069 "i" (7x11) */
    0x10, 0x20, 0x03, 0x87, 0x02, 0x04, 0x08, 0x10, 0x33, 0xf8,
    /* U+006A "j" (5x14) */
    0x08, 0x40, 0xf7, 0x84, 0x21, 0x08, 0x42, 0x3f, 0xa0,
    /* U+006B "k" (7x10) */
    0xc1, 0x83, 0x16, 0x6c, 0x9f, 0x3e, 0x64, 0xcd, 0x8c,
    /* U+006C "l" (8x10) */
    0xf8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1e, 0x0f,
    /* U+006D "m" (7x8) */
    0xad, 0xee, 0x5c, 0xb9, 0x72, 0xe5, 0xcb,
    /* U+006E "n" (6x8) */
    0x9b, 0xfc, 0x71, 0xc7, 0x1c, 0x71,
    /* U+006F "o" (6x8) */
    0x39, 0xfc, 0x71, 0xc7, 0x1c, 0xde,
    /* U+0070 "p" (6x10) */
    0x9b, 0xfc, 0x71, 0xc7, 0x1c, 0xfe, 0xc3, 0x00,
    /* U+0071 "q" (6x11) */
    0x77, 0xfc, 0x71, 0xc7, 0x1c, 0xdf, 0x04, 0x10, 0x40,
    /* U+0072 "r" (5x8) */
    0xb6, 0xe3, 0x08, 0x42, 0x10,
    /* U+0073 "s" (6x8) */
    0x7b, 0xfc, 0x1c, 0x3c, 0x1c, 0xdf,
    /* U+0074 "t" (6x10) */
    0x20, 0x8f, 0xff, 0x20, 0x82, 0x08, 0x30, 0x70,
    /* U+0075 "u" (6x8) */
    0x87, 0x1c, 0x71, 0xc7, 0x1c, 0xde,
    /* U+0076 "v" (6x8) */
    0x87, 0x1c, 0x53, 0x69, 0xa3, 0x8c,
    /* U+0077 "w" (7x8) */
    0x13, 0x66, 0xdd, 0x2a, 0x5d, 0xb3, 0x26,
    /* U+0078 "x" (6x8) */
    0xc5, 0x37, 0x8c, 0x31, 0xe4, 0xf1,
    /* U+0079 "y" (6x11) */
    0x87, 0x1c, 0xdb, 0x68, 0xe3, 0x8c, 0x30, 0x82, 0x00,
    /* U+007A "z" (6x8) */
    0xfd, 0xf0, 0x86, 0x31, 0x8c, 0x3f,
    /* U+007B "{" (6x14) */
    0x0c, 0x71, 0x86, 0x18, 0x6f, 0x3c, 0x18, 0x61, 0x86, 0x1c, 0x30,
    /* U+007C "|" (1x13) */
    0xff, 0xf8,
    /* U+007D "}" (6x14) */
    0xc3, 0x83, 0x0c, 0x30, 0xc3, 0xcf, 0x30, 0xc3, 0x0c, 0xe3, 0x00,
    /* U+007E "~" (7x3) */
    0xf7, 0x38, 0x20,
    /* U+00B0 "" (4x4) */
    0xf9, 0x96,
    /* U+00B1 "" (7x8) */
    0x30, 0x60, 0xc7, 0xf3, 0x06, 0x0c, 0x7f,
    /* U+00B2 "" (4x6) */
    0x6d, 0x13, 0x6f,
    /* U+00B3 "" (4x6) */
    0xf3, 0x23, 0x9f,
    /* U+00B5 "" (6x10) */
    0x87, 0x1c, 0x71, 0xc7, 0x1c, 0xfe, 0x83, 0x00,
    /* U+00B7 "" (2x2) */
    0xf0,
    /* U+00D7 "" (5x5) */
    0x9f, 0x99, 0xe9, 0x80,
    /* U+00F7 "" (6x7) */
    0x30, 0x40, 0x3f, 0x00, 0xc3, 0x00,
    /* U+0394 "" (7x10) */
    0x30, 0x70, 0xe3, 0x44, 0x89, 0x93, 0x62, 0xc5, 0xfc,
    /* U+03A9 "" (7x10) */
    0x7d, 0x9b, 0x1e, 0x3c, 0x78, 0xf1, 0xe6, 0xed, 0xdc,
    /* U+03B1 "" (6x8) */
    0x77, 0xfc, 0x71, 0xc7, 0x1c, 0xdf,
    /* U+03B2 "" (7x12) */
    0x7d, 0x9b, 0x16, 0x6d, 0x99, 0xb1, 0x63, 0xcd, 0xf3, 0x06, 0x00,
    /* U+03B3 "" (6x10) */
    0x87, 0x14, 0xd3, 0x68, 0xa3, 0x0c, 0x30, 0xc0,
    /* U+03B4 "" (7x10) */
    0xfc, 0xc0, 0xc0, 0xc7, 0xd9, 0xb1, 0xe3, 0xcc, 0xf0,
    /* U+03B5 "" (6x8) */
    0x7b, 0xbc, 0x1c, 0x73, 0x0c, 0x5f,
    /* U+03B8 "" (6x10) */
    0x7b, 0x3c, 0x71, 0xff, 0xfc, 0x71, 0xcd, 0xe0,
    /* U+03BB "" (7x10) */
    0x20, 0x60, 0xc1, 0x83, 0x8d, 0x13, 0x26, 0xc5, 0x0c,
    /* U+03BC "" (6x10) */
    0x87, 0x1c, 0x71, 0xc7, 0x1c, 0xfe, 0x83, 0x00,
    /* U+03C0 "" (7x8) */
    0xff, 0xfb, 0x26, 0x4c, 0x99, 0x33, 0x63,
    /* U+03C3 "" (6x8) */
    0x3d, 0xfc, 0x71, 0xc7, 0x1c, 0xde,
    /* U+03C4 "" (6x8) */
    0xff, 0xf3, 0x0c, 0x30, 0xc3, 0x07,
    /* U+03C6 "" (7x10) */
    0x99, 0x3a, 0x5c, 0xb9, 0x72, 0xfd, 0x3e, 0x10, 0x20,
    /* U+03C9 "" (7x8) */
    0x41, 0x8a, 0x1c, 0xb9, 0x72, 0xed, 0xf6,
    /* U+2013 "" (6x1) */
    0xfc,
    /* U+2014 "" (9x2) */
    0xff, 0x7f, 0xc0,
    /* U+2018 "" (3x4) */
    0x2d, 0xe0,
    /* U+2019 "" (3x4) */
    0x6d, 0x60,
    /* U+201C "" (6x4) */
    0x25, 0xb4, 0xf3,
    /* U+201D "" (6x4) */
    0x6d, 0xb4, 0xf2,
    /* U+2022 "" (3x4) */
    0xdf, 0xa0,
    /* U+2026 "" (7x2) */
    0xb7, 0x6c,
    /* U+2030 "" (8x10) */
    0xe4, 0xa0, 0xb8, 0x70, 0x10, 0x20, 0x3f, 0x55, 0x55, 0x9f,
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
    {.bitmap_index = 6, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 134, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 26, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 36, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 45, .adv_w = 134, .box_w = 2, .box_h = 4, .ofs_x = 3, .ofs_y = 6},
    {.bitmap_index = 46, .adv_w = 134, .box_w = 5, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 55, .adv_w = 134, .box_w = 4, .box_h = 12, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 61, .adv_w = 134, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 67, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 74, .adv_w = 134, .box_w = 3, .box_h = 4, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 76, .adv_w = 134, .box_w = 5, .box_h = 2, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 78, .adv_w = 134, .box_w = 2, .box_h = 2, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 79, .adv_w = 134, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 90, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 98, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 107, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 123, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 131, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 148, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 157, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 134, .box_w = 2, .box_h = 8, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 176, .adv_w = 134, .box_w = 3, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 180, .adv_w = 134, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 186, .adv_w = 134, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 190, .adv_w = 134, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 196, .adv_w = 134, .box_w = 5, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 203, .adv_w = 134, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 214, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 223, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 232, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 240, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 248, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 256, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 272, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 280, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 288, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 297, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 323, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 331, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 348, .adv_w = 134, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 358, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 367, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 384, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 392, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 401, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 420, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 429, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 437, .adv_w = 134, .box_w = 3, .box_h = 14, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 443, .adv_w = 134, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 454, .adv_w = 134, .box_w = 4, .box_h = 13, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 461, .adv_w = 134, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 465, .adv_w = 134, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 467, .adv_w = 134, .box_w = 2, .box_h = 2, .ofs_x = 3, .ofs_y = 9},
    {.bitmap_index = 468, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 474, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 482, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 488, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 496, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 502, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 511, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 520, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 528, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 538, .adv_w = 134, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 547, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 556, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 566, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 573, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 579, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 585, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 593, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 602, .adv_w = 134, .box_w = 5, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 607, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 613, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 621, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 627, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 633, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 640, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 646, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 655, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 661, .adv_w = 134, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 672, .adv_w = 134, .box_w = 1, .box_h = 13, .ofs_x = 4, .ofs_y = -1},
    {.bitmap_index = 674, .adv_w = 134, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 685, .adv_w = 134, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 688, .adv_w = 134, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 690, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 697, .adv_w = 134, .box_w = 4, .box_h = 6, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 700, .adv_w = 134, .box_w = 4, .box_h = 6, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 703, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 711, .adv_w = 134, .box_w = 2, .box_h = 2, .ofs_x = 3, .ofs_y = 4},
    {.bitmap_index = 712, .adv_w = 134, .box_w = 5, .box_h = 5, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 716, .adv_w = 134, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 722, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 731, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 740, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 746, .adv_w = 134, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 757, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 765, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 774, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 780, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 788, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 797, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 805, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 812, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 818, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 824, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 833, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 840, .adv_w = 134, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 841, .adv_w = 134, .box_w = 9, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 844, .adv_w = 134, .box_w = 3, .box_h = 4, .ofs_x = 3, .ofs_y = 7},
    {.bitmap_index = 846, .adv_w = 134, .box_w = 3, .box_h = 4, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 848, .adv_w = 134, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 851, .adv_w = 134, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 854, .adv_w = 134, .box_w = 3, .box_h = 4, .ofs_x = 3, .ofs_y = 3},
    {.bitmap_index = 856, .adv_w = 134, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 858, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 868, .adv_w = 134, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 876, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 886, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 893, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0}
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

const lv_font_t humid1_font_jetbrains_mono_normal_14 = {
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

#endif /* #if HUMID1_FONT_JETBRAINS_MONO_NORMAL_14 */
