/*******************************************************************************
 * Font: humid1_font_plex_cond_italic_14 (cond italic)
 * Size: 14 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_font_plex_cond_normal_14 (LVGL >= 9.6.0 Ready)
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

#ifndef HUMID1_FONT_PLEX_COND_ITALIC_14
#define HUMID1_FONT_PLEX_COND_ITALIC_14 1
#endif

#if HUMID1_FONT_PLEX_COND_ITALIC_14

extern const lv_font_t humid1_font_plex_cond_normal_14;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (4x10) */
    0x32, 0x26, 0x64, 0x40, 0x4c,
    /* U+0022 "" (4x4) */
    0x5d, 0xd9,
    /* U+0023 "#" (8x10) */
    0x1a, 0x12, 0x7f, 0x7f, 0x24, 0x7e, 0xfe, 0x28, 0x68, 0x48,
    /* U+0024 "$" (6x10) */
    0x08, 0x73, 0xd8, 0x30, 0xe1, 0xc7, 0xfd, 0xe0,
    /* U+0025 "%" (9x10) */
    0x63, 0x79, 0x2d, 0x16, 0xee, 0xfe, 0xfc, 0x52, 0x4b, 0x65, 0x23, 0x80,
    /* U+0026 "&" (8x10) */
    0x1c, 0x3c, 0x36, 0x34, 0x38, 0x39, 0x4f, 0xce, 0x7e, 0x7e,
    /* U+0027 "'" (2x4) */
    0x7e,
    /* U+0028 "(" (5x12) */
    0x19, 0x88, 0xc4, 0x21, 0x08, 0xc2, 0x10, 0x80,
    /* U+0029 ")" (4x12) */
    0x22, 0x22, 0x32, 0x22, 0x64, 0xc8,
    /* U+002A "" (6x7) */
    0x10, 0x4f, 0x1f, 0x71, 0x41, 0x00,
    /* U+002B "+" (6x7) */
    0x20, 0x82, 0x3f, 0xf8, 0x82, 0x00,
    /* U+002C "," (2x4) */
    0xfa,
    /* U+002D "-" (3x2) */
    0x7c,
    /* U+002E "." (2x2) */
    0x70,
    /* U+002F "/" (6x10) */
    0x0c, 0x21, 0x84, 0x30, 0x86, 0x10, 0xc2, 0x00,
    /* U+0030 "0" (6x10) */
    0x18, 0xf6, 0x51, 0x45, 0x1c, 0xf3, 0x79, 0xc0,
    /* U+0031 "1" (5x10) */
    0x1b, 0xbc, 0x63, 0x18, 0x84, 0x63, 0x00,
    /* U+0032 "2" (6x10) */
    0x39, 0xf0, 0x41, 0x0c, 0x63, 0x18, 0xfb, 0xe0,
    /* U+0033 "3" (6x10) */
    0x3c, 0xf0, 0x43, 0x38, 0xe0, 0xc3, 0xfb, 0xc0,
    /* U+0034 "4" (6x10) */
    0x0c, 0x31, 0xcf, 0x6d, 0x2f, 0xff, 0x18, 0x60,
    /* U+0035 "5" (6x10) */
    0x3c, 0xf2, 0x1e, 0x7c, 0x30, 0xc3, 0xfb, 0xc0,
    /* U+0036 "6" (6x10) */
    0x3d, 0xe4, 0x3c, 0xfb, 0x68, 0xa6, 0xf9, 0xc0,
    /* U+0037 "7" (6x10) */
    0xff, 0xf1, 0x86, 0x30, 0xc6, 0x18, 0xc3, 0x00,
    /* U+0038 "8" (6x10) */
    0x1c, 0xf6, 0x49, 0x39, 0xe4, 0xf3, 0x7d, 0xe0,
    /* U+0039 "9" (5x10) */
    0x77, 0xf3, 0x1d, 0xfd, 0x62, 0xf7, 0x00,
    /* U+003A ":" (3x8) */
    0x64, 0x00, 0x16,
    /* U+003B ";" (3x9) */
    0x24, 0x00, 0x34, 0x80,
    /* U+003C "<" (6x6) */
    0x08, 0xcc, 0x30, 0x30, 0x30,
    /* U+003D "=" (6x4) */
    0xff, 0xef, 0xbf,
    /* U+003E ">" (5x6) */
    0xc3, 0x06, 0x37, 0x60,
    /* U+003F "?" (5x10) */
    0x73, 0xc6, 0x23, 0x31, 0x00, 0x86, 0x00,
    /* U+0040 "@" (9x10) */
    0x1e, 0x30, 0xb7, 0xb2, 0xda, 0x4d, 0x26, 0xb7, 0x7e, 0xc0, 0x1e, 0x00,
    /* U+0041 "A" (8x10) */
    0x06, 0x0e, 0x0e, 0x1a, 0x12, 0x32, 0x3e, 0x7f, 0x63, 0xc3,
    /* U+0042 "B" (7x10) */
    0x3c, 0x7c, 0x8b, 0x37, 0xcf, 0x99, 0xa3, 0x7d, 0xf0,
    /* U+0043 "C" (6x10) */
    0x3d, 0xf6, 0x30, 0xc2, 0x08, 0x30, 0xf9, 0xe0,
    /* U+0044 "D" (8x10) */
    0x3c, 0x3e, 0x23, 0x23, 0x63, 0x63, 0x62, 0x46, 0x7c, 0xf8,
    /* U+0045 "E" (7x10) */
    0x3e, 0x7c, 0x81, 0x07, 0xcf, 0x98, 0x20, 0x79, 0xf0,
    /* U+0046 "F" (7x10) */
    0x3e, 0x7c, 0x83, 0x07, 0xcf, 0x98, 0x20, 0x41, 0x80,
    /* U+0047 "G" (7x10) */
    0x1e, 0xfd, 0x86, 0x0c, 0xd3, 0xa1, 0x66, 0xfc, 0xf0,
    /* U+0048 "H" (8x10) */
    0x31, 0x31, 0x23, 0x63, 0x7f, 0x7f, 0x62, 0x46, 0x46, 0xc6,
    /* U+0049 "I" (5x10) */
    0x79, 0x8c, 0x42, 0x31, 0x8c, 0x67, 0x00,
    /* U+004A "J" (6x13) */
    0x0c, 0x30, 0x82, 0x18, 0x61, 0x86, 0x10, 0x43, 0x3c, 0xe0,
    /* U+004B "K" (8x10) */
    0x33, 0x36, 0x24, 0x2c, 0x78, 0x78, 0x68, 0x4c, 0x4c, 0xc4,
    /* U+004C "L" (5x10) */
    0x31, 0x88, 0xc6, 0x31, 0x88, 0x7f, 0xc0,
    /* U+004D "M" (11x10) */
    0x30, 0xe6, 0x18, 0xe7, 0x3c, 0xe7, 0xbc, 0xf5, 0x93, 0xa2, 0x64, 0x4c,
    0x99, 0x30,
    /* U+004E "N" (9x10) */
    0x30, 0x9c, 0xce, 0x6d, 0x26, 0x93, 0x69, 0x3c, 0x8e, 0x47, 0x63, 0x00,
    /* U+004F "O" (7x10) */
    0x3c, 0xfd, 0x9e, 0x1c, 0x30, 0x61, 0xe3, 0xfc, 0xf0,
    /* U+0050 "P" (7x10) */
    0x3c, 0x7c, 0x8b, 0x16, 0x6f, 0x9e, 0x20, 0x41, 0x80,
    /* U+0051 "Q" (7x12) */
    0x3c, 0xfd, 0x9e, 0x1c, 0x30, 0x61, 0xe3, 0xfc, 0xf0, 0x60, 0x60,
    /* U+0052 "R" (7x10) */
    0x3c, 0x7c, 0x99, 0x36, 0x6f, 0x9f, 0x3e, 0x4d, 0x98,
    /* U+0053 "S" (6x10) */
    0x1c, 0xf6, 0x18, 0x30, 0x60, 0x82, 0xf9, 0xc0,
    /* U+0054 "T" (6x10) */
    0xff, 0xf3, 0x08, 0x21, 0x86, 0x18, 0x61, 0x00,
    /* U+0055 "U" (7x10) */
    0x62, 0x8d, 0x1e, 0x3c, 0x78, 0xb3, 0x66, 0xf8, 0xe0,
    /* U+0056 "V" (7x10) */
    0xc7, 0x8f, 0x36, 0x6c, 0x8b, 0x14, 0x38, 0x60, 0xc0,
    /* U+0057 "W" (11x10) */
    0xc4, 0x79, 0x8b, 0x33, 0x6e, 0x6d, 0x49, 0xab, 0x3d, 0x47, 0x38, 0xe7,
    0x18, 0xc0,
    /* U+0058 "X" (8x10) */
    0x63, 0x26, 0x34, 0x3c, 0x18, 0x38, 0x38, 0x6c, 0xcc, 0x84,
    /* U+0059 "Y" (7x10) */
    0xc7, 0x99, 0x22, 0xc7, 0x0e, 0x18, 0x30, 0x60, 0xc0,
    /* U+005A "Z" (7x10) */
    0x7e, 0xfc, 0x30, 0xc1, 0x86, 0x18, 0x30, 0xfd, 0xf8,
    /* U+005B "[" (5x13) */
    0x39, 0x88, 0xc6, 0x31, 0x08, 0x46, 0x31, 0xce, 0x00,
    /* U+005C "" (3x10) */
    0xc9, 0x24, 0x9b, 0x64,
    /* U+005D "]" (5x13) */
    0x39, 0xc6, 0x31, 0x08, 0x46, 0x31, 0x08, 0xce, 0x00,
    /* U+005E "^" (6x6) */
    0x18, 0x62, 0x8b, 0x47, 0x10,
    /* U+005F "_" (5x1) */
    0xf8,
    /* U+0060 "`" (2x2) */
    0x90,
    /* U+0061 "a" (6x8) */
    0x75, 0xfc, 0xa2, 0x8a, 0x6f, 0xb6,
    /* U+0062 "b" (6x11) */
    0x30, 0x82, 0x0b, 0x7d, 0x94, 0x51, 0x4d, 0xfd, 0x80,
    /* U+0063 "c" (4x8) */
    0x77, 0xc8, 0x88, 0xfe,
    /* U+0064 "d" (6x11) */
    0x04, 0x10, 0xdb, 0x7f, 0x28, 0xa2, 0x9b, 0xed, 0x80,
    /* U+0065 "e" (5x8) */
    0x3b, 0xf3, 0xff, 0x43, 0xce,
    /* U+0066 "f" (6x14) */
    0x0c, 0x71, 0x8f, 0x38, 0x43, 0x0c, 0x30, 0x82, 0x18, 0xe3, 0x00,
    /* U+0067 "g" (7x11) */
    0x3a, 0x7d, 0x92, 0x24, 0x49, 0x9f, 0x34, 0x09, 0xf3, 0xc0,
    /* U+0068 "h" (7x11) */
    0x30, 0x40, 0x81, 0x67, 0xcc, 0xd9, 0x22, 0x44, 0x9b, 0x30,
    /* U+0069 "i" (4x11) */
    0x32, 0x02, 0x66, 0x64, 0x4c, 0xc0,
    /* U+006A "j" (6x14) */
    0x0c, 0x20, 0x02, 0x18, 0x61, 0x84, 0x10, 0xc3, 0x0c, 0x63, 0x80,
    /* U+006B "k" (7x11) */
    0x30, 0x60, 0x81, 0x36, 0xcf, 0x1c, 0x3c, 0x59, 0x93, 0x30,
    /* U+006C "l" (4x11) */
    0x33, 0x22, 0x66, 0x64, 0x44, 0xc0,
    /* U+006D "m" (10x8) */
    0x2c, 0xdf, 0xf6, 0x65, 0x91, 0x44, 0xd3, 0x3c, 0xcf, 0x32,
    /* U+006E "n" (7x8) */
    0x2c, 0xf9, 0x9b, 0x24, 0x48, 0x93, 0x66,
    /* U+006F "o" (5x8) */
    0x7a, 0x73, 0x18, 0xcf, 0xee,
    /* U+0070 "p" (6x11) */
    0x2d, 0xf6, 0x59, 0x45, 0x3f, 0xf6, 0xc2, 0x08, 0x00,
    /* U+0071 "q" (6x11) */
    0x75, 0xfc, 0xa2, 0x8a, 0x6f, 0xb4, 0x10, 0x43, 0x00,
    /* U+0072 "r" (5x8) */
    0x2b, 0xd8, 0xc4, 0x23, 0x18,
    /* U+0073 "s" (5x8) */
    0x3b, 0xd8, 0xe3, 0x8f, 0xfe,
    /* U+0074 "t" (4x9) */
    0x4f, 0xfc, 0xcc, 0x8e, 0xe0,
    /* U+0075 "u" (6x8) */
    0xcf, 0x3c, 0xf2, 0x9a, 0x6f, 0xb6,
    /* U+0076 "v" (6x8) */
    0x8e, 0x69, 0xa4, 0xb3, 0x8e, 0x30,
    /* U+0077 "w" (9x8) */
    0x99, 0xcc, 0xa6, 0x55, 0x6a, 0xa7, 0x73, 0x39, 0x98,
    /* U+0078 "x" (6x8) */
    0x65, 0xb3, 0x8c, 0x31, 0xed, 0xb2,
    /* U+0079 "y" (8x11) */
    0x23, 0x26, 0x26, 0x24, 0x3c, 0x38, 0x38, 0x10, 0x30, 0x60, 0xc0,
    /* U+007A "z" (6x8) */
    0x7d, 0xe1, 0x8c, 0x21, 0x0f, 0x3c,
    /* U+007B "{" (5x13) */
    0x19, 0xcc, 0x42, 0x73, 0x08, 0x42, 0x10, 0xc2, 0x00,
    /* U+007C "|" (1x14) */
    0xff, 0xfc,
    /* U+007D "}" (5x13) */
    0x31, 0x84, 0x21, 0x08, 0x67, 0x31, 0x19, 0xcc, 0x00,
    /* U+007E "~" (6x3) */
    0x43, 0xf3, 0x80,
    /* U+00B0 "" (4x5) */
    0xea, 0x1a, 0xe0,
    /* U+00B1 "" (6x9) */
    0x20, 0x82, 0x3f, 0xf8, 0x82, 0x3e, 0xfc,
    /* U+00B2 "" (4x6) */
    0x77, 0x32, 0x4f,
    /* U+00B3 "" (4x6) */
    0x77, 0x16, 0x3e,
    /* U+00B5 "" (7x11) */
    0x26, 0xcd, 0x9b, 0x24, 0x49, 0xbf, 0x7e, 0xc1, 0x02, 0x00,
    /* U+00B7 "" (2x2) */
    0xb0,
    /* U+00D7 "" (5x6) */
    0x8e, 0xdc, 0xed, 0xc4,
    /* U+00F7 "" (6x7) */
    0x20, 0x80, 0x3f, 0xf8, 0x82, 0x00,
    /* U+0394 "" (6x10) */
    0x1c, 0x71, 0xcd, 0x25, 0x94, 0x71, 0xff, 0xf0,
    /* U+03A9 "" (8x10) */
    0x1e, 0x3f, 0x63, 0x61, 0x61, 0x61, 0x63, 0x22, 0xe7, 0xef,
    /* U+03BC "" (7x11) */
    0x26, 0xcd, 0x9b, 0x24, 0x49, 0xbf, 0x7e, 0xc1, 0x02, 0x00,
    /* U+2013 "" (5x2) */
    0x7f, 0xc0,
    /* U+2014 "" (11x2) */
    0x7f, 0xff, 0xfc,
    /* U+2018 "" (2x3) */
    0x78,
    /* U+2019 "" (2x3) */
    0x78,
    /* U+201C "" (5x3) */
    0x4e, 0xac,
    /* U+201D "" (5x3) */
    0x5e, 0xac,
    /* U+2022 "" (3x4) */
    0xdf, 0xe0,
    /* U+2026 "" (9x2) */
    0x49, 0x64, 0xc0,
    /* U+2030 "" (13x10) */
    0x63, 0x07, 0x90, 0x2d, 0x01, 0x6e, 0x2e, 0xfb, 0xef, 0xd4, 0x53, 0xa4,
    0xbd, 0x65, 0x7a, 0x39, 0x80,
    /* U+2190 "" (9x3) */
    0x40, 0x7f, 0xd0, 0x00,
    /* U+2191 "" (4x2) */
    0x6f,
    /* U+2192 "" (9x3) */
    0x01, 0x7f, 0xc0, 0x40,
    /* U+2193 "" (3x3) */
    0x8c, 0x80,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 51, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 53, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 5, .adv_w = 85, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 7, .adv_w = 127, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 17, .adv_w = 108, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 25, .adv_w = 165, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 37, .adv_w = 136, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 47, .adv_w = 48, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 48, .adv_w = 63, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 56, .adv_w = 63, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 62, .adv_w = 107, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 68, .adv_w = 112, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 74, .adv_w = 54, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 75, .adv_w = 62, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 76, .adv_w = 53, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 77, .adv_w = 78, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 85, .adv_w = 105, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 93, .adv_w = 108, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 105, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 108, .adv_w = 108, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 116, .adv_w = 105, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 124, .adv_w = 105, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 132, .adv_w = 108, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 140, .adv_w = 108, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 148, .adv_w = 105, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 156, .adv_w = 105, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 163, .adv_w = 53, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 166, .adv_w = 53, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 170, .adv_w = 112, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 175, .adv_w = 112, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 178, .adv_w = 112, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 182, .adv_w = 88, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 189, .adv_w = 165, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 201, .adv_w = 119, .box_w = 8, .box_h = 10, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 118, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 117, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 132, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 238, .adv_w = 104, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 247, .adv_w = 101, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 256, .adv_w = 132, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 265, .adv_w = 136, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 275, .adv_w = 71, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 282, .adv_w = 62, .box_w = 6, .box_h = 13, .ofs_x = -2, .ofs_y = -3},
    {.bitmap_index = 292, .adv_w = 117, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 302, .adv_w = 99, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 309, .adv_w = 169, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 323, .adv_w = 145, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 335, .adv_w = 140, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 344, .adv_w = 116, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 353, .adv_w = 140, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 364, .adv_w = 117, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 373, .adv_w = 101, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 381, .adv_w = 102, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 389, .adv_w = 132, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 398, .adv_w = 113, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 407, .adv_w = 172, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 421, .adv_w = 114, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 431, .adv_w = 107, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 440, .adv_w = 105, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 62, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 458, .adv_w = 78, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 462, .adv_w = 62, .box_w = 5, .box_h = 13, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 471, .adv_w = 109, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 476, .adv_w = 78, .box_w = 5, .box_h = 1, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 477, .adv_w = 60, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 9},
    {.bitmap_index = 478, .adv_w = 113, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 484, .adv_w = 114, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 493, .adv_w = 92, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 497, .adv_w = 113, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 506, .adv_w = 106, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 511, .adv_w = 70, .box_w = 6, .box_h = 14, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 522, .adv_w = 113, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 532, .adv_w = 115, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 542, .adv_w = 55, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 548, .adv_w = 55, .box_w = 6, .box_h = 14, .ofs_x = -2, .ofs_y = -3},
    {.bitmap_index = 559, .adv_w = 107, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 569, .adv_w = 56, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 575, .adv_w = 174, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 585, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 592, .adv_w = 113, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 597, .adv_w = 114, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 606, .adv_w = 113, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 615, .adv_w = 79, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 620, .adv_w = 90, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 625, .adv_w = 77, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 630, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 636, .adv_w = 97, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 642, .adv_w = 151, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 651, .adv_w = 101, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 657, .adv_w = 99, .box_w = 8, .box_h = 11, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 668, .adv_w = 88, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 674, .adv_w = 67, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 683, .adv_w = 108, .box_w = 1, .box_h = 14, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 685, .adv_w = 67, .box_w = 5, .box_h = 13, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 694, .adv_w = 112, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 697, .adv_w = 81, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 700, .adv_w = 112, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 707, .adv_w = 71, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 710, .adv_w = 71, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 713, .adv_w = 116, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 723, .adv_w = 56, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 724, .adv_w = 112, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 728, .adv_w = 112, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 734, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 742, .adv_w = 142, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 752, .adv_w = 120, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 762, .adv_w = 94, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 764, .adv_w = 188, .box_w = 11, .box_h = 2, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 767, .adv_w = 39, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 768, .adv_w = 39, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 769, .adv_w = 80, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 771, .adv_w = 80, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 773, .adv_w = 71, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 775, .adv_w = 163, .box_w = 9, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 778, .adv_w = 236, .box_w = 13, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 795, .adv_w = 178, .box_w = 9, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 799, .adv_w = 98, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 800, .adv_w = 178, .box_w = 9, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 804, .adv_w = 98, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x0005, 0x0007, 0x0027, 0x0047, 0x02e4, 0x02f9,
    0x030c, 0x1f63, 0x1f64, 0x1f68, 0x1f69, 0x1f6c, 0x1f6d, 0x1f72, 0x1f76, 0x1f80,
    0x20e0, 0x20e1, 0x20e2, 0x20e3,
};

static const lv_font_fmt_txt_cmap_t cmaps[] = {
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 176, .range_length = 8420, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 24, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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

const lv_font_t humid1_font_plex_cond_italic_14 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 20,
    .base_line = 5,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 10,
    .x_height = 8,
#endif
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = -1,
    .underline_thickness = 1,
#if LV_VERSION_CHECK(9, 3, 0) || (LVGL_VERSION_MAJOR == 9 && LVGL_VERSION_MINOR >= 3) || LVGL_VERSION_MAJOR > 9
    .static_bitmap = 0,
#endif
    .dsc = &font_dsc,
#if LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_font_plex_cond_normal_14,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_COND_ITALIC_14 */
