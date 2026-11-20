/*******************************************************************************
 * Font: humid1_font_plex_cond_normal_14 (cond normal)
 * Size: 14 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_font_plex_sans_normal_14 (LVGL >= 9.6.0 Ready)
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

#ifndef HUMID1_FONT_PLEX_COND_NORMAL_14
#define HUMID1_FONT_PLEX_COND_NORMAL_14 1
#endif

#if HUMID1_FONT_PLEX_COND_NORMAL_14

extern const lv_font_t humid1_font_plex_sans_normal_14;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x10) */
    0xea, 0xa8, 0xa0,
    /* U+0022 "" (3x3) */
    0xb6, 0x80,
    /* U+0023 "#" (8x10) */
    0x12, 0x14, 0x14, 0x7f, 0x24, 0x24, 0xfe, 0x28, 0x28, 0x48,
    /* U+0024 "$" (5x12) */
    0x23, 0xbb, 0x4a, 0x38, 0xe5, 0x2f, 0x88, 0x40,
    /* U+0025 "%" (9x10) */
    0xc2, 0x52, 0x29, 0x15, 0xea, 0xd7, 0xa4, 0x52, 0x49, 0x25, 0x21, 0x80,
    /* U+0026 "&" (8x10) */
    0x70, 0x48, 0x48, 0x50, 0x60, 0xf2, 0x9a, 0x8c, 0x8e, 0x73,
    /* U+0027 "'" (1x3) */
    0xe0,
    /* U+0028 "(" (2x13) */
    0x5a, 0xaa, 0xab, 0x40,
    /* U+0029 ")" (2x13) */
    0xad, 0x55, 0x5e, 0x80,
    /* U+002A "" (5x6) */
    0x21, 0x2b, 0xf7, 0x28,
    /* U+002B "+" (5x7) */
    0x21, 0x09, 0xf2, 0x10, 0x80,
    /* U+002C "," (1x4) */
    0xf0,
    /* U+002D "-" (3x1) */
    0xe0,
    /* U+002E "." (1x2) */
    0xc0,
    /* U+002F "/" (5x10) */
    0x18, 0x84, 0x62, 0x11, 0x88, 0x46, 0x00,
    /* U+0030 "0" (6x10) */
    0x73, 0x68, 0xa2, 0x8e, 0x28, 0xa2, 0xd9, 0xc0,
    /* U+0031 "1" (4x10) */
    0x37, 0xf3, 0x33, 0x33, 0x33,
    /* U+0032 "2" (6x10) */
    0x72, 0x60, 0x82, 0x18, 0x42, 0x18, 0xc3, 0xf0,
    /* U+0033 "3" (6x10) */
    0x72, 0x20, 0x86, 0x70, 0x60, 0xc3, 0x0b, 0xc0,
    /* U+0034 "4" (7x10) */
    0x0c, 0x38, 0x51, 0x26, 0x48, 0xbf, 0x86, 0x0c, 0x18,
    /* U+0035 "5" (5x10) */
    0xfc, 0x21, 0x0f, 0x0c, 0x21, 0x1f, 0x80,
    /* U+0036 "6" (6x10) */
    0x39, 0x08, 0x2c, 0xca, 0x28, 0xe2, 0xc9, 0xc0,
    /* U+0037 "7" (7x10) */
    0xfe, 0x08, 0x30, 0x60, 0x83, 0x04, 0x08, 0x30, 0x40,
    /* U+0038 "8" (5x10) */
    0x77, 0x73, 0x37, 0x3a, 0x31, 0x8b, 0xc0,
    /* U+0039 "9" (6x10) */
    0x73, 0x68, 0xa2, 0x8d, 0xe0, 0x86, 0x3b, 0xc0,
    /* U+003A ":" (1x8) */
    0xc3,
    /* U+003B ";" (3x10) */
    0x6c, 0x00, 0x1a, 0x58,
    /* U+003C "<" (5x6) */
    0x09, 0xb1, 0x83, 0x04,
    /* U+003D "=" (5x4) */
    0xf8, 0x01, 0xf0,
    /* U+003E ">" (5x6) */
    0xc3, 0x06, 0x37, 0x60,
    /* U+003F "?" (4x10) */
    0xe1, 0x11, 0x24, 0x40, 0x44,
    /* U+0040 "@" (9x11) */
    0x1e, 0x30, 0x97, 0xb2, 0x5a, 0x2d, 0x16, 0x9b, 0x36, 0x80, 0x20, 0x0f,
    0x80,
    /* U+0041 "A" (8x10) */
    0x18, 0x18, 0x1c, 0x34, 0x24, 0x26, 0x7e, 0x62, 0x43, 0xc1,
    /* U+0042 "B" (6x10) */
    0xfb, 0x3c, 0x73, 0xfb, 0x3c, 0x71, 0xcf, 0xe0,
    /* U+0043 "C" (6x10) */
    0x3d, 0x8c, 0x30, 0x82, 0x08, 0x30, 0x60, 0xf0,
    /* U+0044 "D" (7x10) */
    0xf9, 0x9b, 0x1e, 0x1c, 0x38, 0x70, 0xe3, 0xcd, 0xf0,
    /* U+0045 "E" (5x10) */
    0xfe, 0x31, 0x8f, 0xe3, 0x18, 0xc7, 0xc0,
    /* U+0046 "F" (5x10) */
    0xfe, 0x31, 0x8f, 0xe3, 0x18, 0xc6, 0x00,
    /* U+0047 "G" (7x10) */
    0x3c, 0x81, 0x04, 0x08, 0xf0, 0x60, 0xe1, 0x66, 0x7c,
    /* U+0048 "H" (7x10) */
    0xc3, 0x87, 0x0e, 0x1f, 0xf8, 0x70, 0xe1, 0xc3, 0x84,
    /* U+0049 "I" (3x10) */
    0xf9, 0x24, 0x92, 0x5c,
    /* U+004A "J" (4x13) */
    0x33, 0x33, 0x33, 0x33, 0x33, 0x32, 0xe0,
    /* U+004B "K" (7x10) */
    0xc5, 0x9b, 0x66, 0x8f, 0x1e, 0x36, 0x64, 0xcd, 0x8c,
    /* U+004C "L" (5x10) */
    0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc7, 0xc0,
    /* U+004D "M" (9x10) */
    0xc1, 0xf0, 0xf8, 0x7c, 0x7f, 0x2e, 0x97, 0x5b, 0xb9, 0xcc, 0xe4, 0x40,
    /* U+004E "N" (7x10) */
    0xc3, 0xc7, 0x8f, 0x9d, 0x3b, 0x72, 0xe3, 0xc7, 0x84,
    /* U+004F "O" (8x10) */
    0x3c, 0x46, 0xc2, 0x83, 0x83, 0x83, 0x83, 0xc2, 0x46, 0x3c,
    /* U+0050 "P" (6x10) */
    0xfb, 0x3c, 0x71, 0xcf, 0xec, 0x30, 0xc3, 0x00,
    /* U+0051 "Q" (8x12) */
    0x3c, 0x66, 0xc3, 0x81, 0x81, 0x81, 0x81, 0xc3, 0x46, 0x3c, 0x04, 0x06,
    /* U+0052 "R" (7x10) */
    0xf9, 0x9b, 0x36, 0x6c, 0xdf, 0x36, 0x64, 0xcd, 0x8c,
    /* U+0053 "S" (5x10) */
    0x7e, 0x61, 0x86, 0x1c, 0x21, 0x0f, 0x80,
    /* U+0054 "T" (7x10) */
    0xfe, 0x20, 0x40, 0x81, 0x02, 0x04, 0x08, 0x10, 0x20,
    /* U+0055 "U" (7x10) */
    0x83, 0x06, 0x0c, 0x18, 0x30, 0x70, 0xe3, 0x44, 0x70,
    /* U+0056 "V" (8x10) */
    0xc3, 0xc2, 0x46, 0x66, 0x64, 0x24, 0x3c, 0x38, 0x18, 0x18,
    /* U+0057 "W" (12x10) */
    0xc6, 0x3c, 0x62, 0x4e, 0x24, 0xf6, 0x6b, 0x66, 0x94, 0x39, 0xc3, 0x9c,
    0x31, 0xc3, 0x08,
    /* U+0058 "X" (7x10) */
    0x42, 0xc8, 0x91, 0xc1, 0x83, 0x0b, 0x32, 0x47, 0x84,
    /* U+0059 "Y" (7x10) */
    0xc6, 0x8d, 0x91, 0x63, 0x83, 0x04, 0x08, 0x10, 0x20,
    /* U+005A "Z" (7x10) */
    0xfe, 0x18, 0x30, 0xc1, 0x86, 0x0c, 0x30, 0x61, 0xfc,
    /* U+005B "[" (3x12) */
    0xf2, 0x49, 0x24, 0x92, 0x70,
    /* U+005C "" (5x10) */
    0xc2, 0x10, 0xc2, 0x10, 0xc2, 0x10, 0xc0,
    /* U+005D "]" (3x12) */
    0xe4, 0x92, 0x49, 0x24, 0xf0,
    /* U+005E "^" (6x7) */
    0x20, 0x87, 0x14, 0xda, 0x28, 0xc0,
    /* U+005F "_" (5x1) */
    0xf8,
    /* U+0060 "`" (2x3) */
    0xb4,
    /* U+0061 "a" (5x8) */
    0x70, 0xc2, 0xfc, 0xc6, 0x7d,
    /* U+0062 "b" (6x11) */
    0x82, 0x08, 0x3e, 0xce, 0x18, 0x61, 0xc7, 0x3f, 0x80,
    /* U+0063 "c" (5x8) */
    0x7e, 0x21, 0x08, 0x43, 0x0f,
    /* U+0064 "d" (6x11) */
    0x0c, 0x30, 0xdf, 0xce, 0x38, 0xe3, 0x8f, 0x37, 0xc0,
    /* U+0065 "e" (6x8) */
    0x73, 0x28, 0xff, 0x82, 0x0c, 0x1e,
    /* U+0066 "f" (5x11) */
    0x3b, 0x19, 0xf6, 0x31, 0x8c, 0x63, 0x18,
    /* U+0067 "g" (6x12) */
    0x7f, 0x38, 0xe1, 0x86, 0x3c, 0xdf, 0x0c, 0x38, 0xbe,
    /* U+0068 "h" (6x11) */
    0x82, 0x08, 0x3e, 0xcf, 0x18, 0x61, 0x86, 0x18, 0x40,
    /* U+0069 "i" (1x11) */
    0xdf, 0xe0,
    /* U+006A "j" (2x15) */
    0x51, 0x55, 0x55, 0x5c,
    /* U+006B "k" (6x11) */
    0x82, 0x08, 0x22, 0x9b, 0xce, 0x3c, 0x92, 0x68, 0xc0,
    /* U+006C "l" (1x11) */
    0xff, 0xe0,
    /* U+006D "m" (10x8) */
    0xfb, 0xb3, 0x3c, 0xce, 0x33, 0x8c, 0xe3, 0x38, 0xce, 0x31,
    /* U+006E "n" (6x8) */
    0xbb, 0x3c, 0x61, 0x86, 0x18, 0x61,
    /* U+006F "o" (6x8) */
    0x73, 0x28, 0xe3, 0x8e, 0x3c, 0x9c,
    /* U+0070 "p" (6x12) */
    0xfb, 0x38, 0x61, 0x87, 0x1c, 0xfe, 0x82, 0x08, 0x20,
    /* U+0071 "q" (6x12) */
    0x7f, 0x38, 0xe1, 0x86, 0x3c, 0xdf, 0x0c, 0x30, 0xc3,
    /* U+0072 "r" (4x8) */
    0xbc, 0xc8, 0x88, 0x88,
    /* U+0073 "s" (5x8) */
    0x74, 0x21, 0xc3, 0x0c, 0x7e,
    /* U+0074 "t" (4x9) */
    0x4f, 0x64, 0x44, 0x46, 0x30,
    /* U+0075 "u" (6x8) */
    0x86, 0x18, 0x61, 0x8e, 0x3c, 0xdf,
    /* U+0076 "v" (7x8) */
    0xc7, 0x89, 0x33, 0x66, 0x87, 0x0e, 0x18,
    /* U+0077 "w" (10x8) */
    0xcc, 0xf3, 0x34, 0xc9, 0x7a, 0x73, 0x9c, 0xe3, 0x30, 0xcc,
    /* U+0078 "x" (6x8) */
    0x45, 0xb3, 0x8e, 0x38, 0xa6, 0xf1,
    /* U+0079 "y" (6x12) */
    0xc7, 0x14, 0xd2, 0x68, 0xa3, 0x8c, 0x10, 0xc2, 0x30,
    /* U+007A "z" (6x8) */
    0x78, 0x61, 0x8c, 0x31, 0x84, 0x3f,
    /* U+007B "{" (5x13) */
    0x19, 0x88, 0x42, 0x13, 0x8c, 0x21, 0x08, 0x61, 0x80,
    /* U+007C "|" (1x15) */
    0xff, 0xfe,
    /* U+007D "}" (5x13) */
    0xc3, 0x08, 0x42, 0x18, 0xe6, 0x21, 0x08, 0xcc, 0x00,
    /* U+007E "~" (5x2) */
    0xe1, 0xc0,
    /* U+00B0 "" (4x5) */
    0x6b, 0x99, 0xe0,
    /* U+00B1 "" (5x9) */
    0x21, 0x09, 0xf2, 0x10, 0x80, 0xf8,
    /* U+00B2 "" (4x6) */
    0x71, 0x12, 0x4f,
    /* U+00B3 "" (4x6) */
    0x71, 0x71, 0x1f,
    /* U+00B5 "" (6x12) */
    0x86, 0x18, 0x61, 0x8e, 0x3c, 0xfd, 0x82, 0x08, 0x20,
    /* U+00B7 "" (1x2) */
    0xc0,
    /* U+00D7 "" (5x6) */
    0x8e, 0xdc, 0xed, 0xc4,
    /* U+00F7 "" (5x7) */
    0x21, 0x01, 0xf0, 0x10, 0x80,
    /* U+0394 "" (7x10) */
    0x18, 0x30, 0xe1, 0x62, 0x4c, 0x91, 0x23, 0xc3, 0xfc,
    /* U+03A9 "" (9x10) */
    0x1e, 0x19, 0x98, 0x68, 0x34, 0x1a, 0x0d, 0x86, 0xc2, 0x33, 0x79, 0xc0,
    /* U+03BC "" (6x12) */
    0x86, 0x18, 0x61, 0x8e, 0x3c, 0xfd, 0x82, 0x08, 0x20,
    /* U+2013 "" (5x1) */
    0xf8,
    /* U+2014 "" (11x1) */
    0xff, 0xe0,
    /* U+2018 "" (2x3) */
    0x5c,
    /* U+2019 "" (2x3) */
    0x7c,
    /* U+201C "" (5x3) */
    0x5a, 0xb4,
    /* U+201D "" (5x3) */
    0x5a, 0xa4,
    /* U+2022 "" (3x4) */
    0xff, 0xf0,
    /* U+2026 "" (8x2) */
    0xdb, 0xdb,
    /* U+2030 "" (13x10) */
    0xe2, 0x05, 0x20, 0x29, 0x01, 0x5e, 0x6a, 0xd7, 0xfa, 0x64, 0x53, 0x24,
    0x99, 0x25, 0x7a, 0x19, 0x80,
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
    {.bitmap_index = 0, .adv_w = 54, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 84, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 5, .adv_w = 127, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 115, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 23, .adv_w = 166, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 35, .adv_w = 146, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 45, .adv_w = 47, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 46, .adv_w = 61, .box_w = 2, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 50, .adv_w = 61, .box_w = 2, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 54, .adv_w = 108, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 58, .adv_w = 112, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 63, .adv_w = 54, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 64, .adv_w = 63, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 65, .adv_w = 54, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 66, .adv_w = 75, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 73, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 81, .adv_w = 112, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 86, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 102, .adv_w = 115, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 112, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 118, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 126, .adv_w = 112, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 135, .adv_w = 112, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 54, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 151, .adv_w = 56, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 155, .adv_w = 112, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 159, .adv_w = 112, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 162, .adv_w = 112, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 166, .adv_w = 88, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 171, .adv_w = 176, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 184, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 129, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 202, .adv_w = 127, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 210, .adv_w = 144, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 219, .adv_w = 109, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 226, .adv_w = 104, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 142, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 242, .adv_w = 147, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 70, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 255, .adv_w = 57, .box_w = 4, .box_h = 13, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 262, .adv_w = 124, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 271, .adv_w = 105, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 278, .adv_w = 181, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 290, .adv_w = 152, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 299, .adv_w = 154, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 309, .adv_w = 122, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 317, .adv_w = 156, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 329, .adv_w = 124, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 338, .adv_w = 111, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 345, .adv_w = 110, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 145, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 363, .adv_w = 121, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 373, .adv_w = 185, .box_w = 12, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 120, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 397, .adv_w = 115, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 406, .adv_w = 113, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 415, .adv_w = 65, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 420, .adv_w = 75, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 427, .adv_w = 65, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 432, .adv_w = 112, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 438, .adv_w = 85, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 439, .adv_w = 58, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 440, .adv_w = 113, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 445, .adv_w = 124, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 454, .adv_w = 97, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 459, .adv_w = 122, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 468, .adv_w = 114, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 474, .adv_w = 71, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 481, .adv_w = 124, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 490, .adv_w = 124, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 499, .adv_w = 54, .box_w = 1, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 501, .adv_w = 54, .box_w = 2, .box_h = 15, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 505, .adv_w = 108, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 514, .adv_w = 54, .box_w = 1, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 516, .adv_w = 186, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 526, .adv_w = 124, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 532, .adv_w = 119, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 538, .adv_w = 124, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 547, .adv_w = 124, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 556, .adv_w = 84, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 560, .adv_w = 97, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 565, .adv_w = 75, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 570, .adv_w = 124, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 576, .adv_w = 103, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 583, .adv_w = 157, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 593, .adv_w = 107, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 599, .adv_w = 104, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 608, .adv_w = 93, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 614, .adv_w = 78, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 623, .adv_w = 108, .box_w = 1, .box_h = 15, .ofs_x = 3, .ofs_y = -4},
    {.bitmap_index = 625, .adv_w = 78, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 634, .adv_w = 112, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 636, .adv_w = 87, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 639, .adv_w = 112, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 645, .adv_w = 72, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 648, .adv_w = 72, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 651, .adv_w = 125, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 660, .adv_w = 52, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 661, .adv_w = 112, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 665, .adv_w = 112, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 670, .adv_w = 117, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 679, .adv_w = 153, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 691, .adv_w = 122, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 700, .adv_w = 98, .box_w = 5, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 701, .adv_w = 196, .box_w = 11, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 703, .adv_w = 37, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 704, .adv_w = 37, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 705, .adv_w = 76, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 707, .adv_w = 73, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 709, .adv_w = 77, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 711, .adv_w = 155, .box_w = 8, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 713, .adv_w = 234, .box_w = 13, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 730, .adv_w = 178, .box_w = 9, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 734, .adv_w = 98, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 735, .adv_w = 178, .box_w = 9, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 739, .adv_w = 98, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 0}
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

const lv_font_t humid1_font_plex_cond_normal_14 = {
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
    .fallback = &humid1_font_plex_sans_normal_14,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_COND_NORMAL_14 */
