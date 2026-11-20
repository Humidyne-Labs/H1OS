/*******************************************************************************
 * Font: humid1_font_plex_sans_normal_14 (sans normal)
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

#ifndef HUMID1_FONT_PLEX_SANS_NORMAL_14
#define HUMID1_FONT_PLEX_SANS_NORMAL_14 1
#endif

#if HUMID1_FONT_PLEX_SANS_NORMAL_14

extern const lv_font_t humid1_icon_fa7_solid_14;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x10) */
    0xff, 0xd0, 0xf0,
    /* U+0022 "" (4x4) */
    0x99, 0x99,
    /* U+0023 "#" (8x10) */
    0x22, 0x26, 0x24, 0xff, 0x24, 0x64, 0xfe, 0x48, 0x48, 0x48,
    /* U+0024 "$" (7x12) */
    0x10, 0xfb, 0x54, 0x8d, 0x0e, 0x07, 0x0b, 0x17, 0x29, 0xe0, 0x80,
    /* U+0025 "%" (11x10) */
    0x70, 0x92, 0x32, 0x44, 0x49, 0x09, 0x6c, 0xea, 0x42, 0x48, 0xc9, 0x11,
    0x24, 0x18,
    /* U+0026 "&" (8x10) */
    0x38, 0x6c, 0x44, 0x68, 0x30, 0x73, 0xca, 0x86, 0xc6, 0x7b,
    /* U+0027 "'" (1x4) */
    0xf0,
    /* U+0028 "(" (3x13) */
    0x2d, 0x69, 0x24, 0x99, 0x32,
    /* U+0029 ")" (4x13) */
    0xc6, 0x22, 0x33, 0x33, 0x32, 0x26, 0xc0,
    /* U+002A "" (5x6) */
    0x21, 0x3e, 0xe5, 0x20,
    /* U+002B "+" (6x7) */
    0x10, 0x41, 0x3f, 0x10, 0x41, 0x00,
    /* U+002C "," (2x4) */
    0xfe,
    /* U+002D "-" (4x2) */
    0xff,
    /* U+002E "." (2x2) */
    0xf0,
    /* U+002F "/" (5x12) */
    0x08, 0xc6, 0x23, 0x18, 0x8c, 0x62, 0x11, 0x80,
    /* U+0030 "0" (7x10) */
    0x79, 0x9b, 0x14, 0x38, 0x70, 0xe1, 0xe2, 0xcc, 0xf0,
    /* U+0031 "1" (7x10) */
    0x38, 0xf3, 0x64, 0xc1, 0x83, 0x06, 0x0c, 0x19, 0xfc,
    /* U+0032 "2" (7x10) */
    0x79, 0x98, 0x10, 0x60, 0xc3, 0x0c, 0x30, 0xc1, 0xfc,
    /* U+0033 "3" (6x10) */
    0x7b, 0x30, 0xc3, 0x38, 0x30, 0x41, 0x8d, 0xe0,
    /* U+0034 "4" (7x10) */
    0x18, 0x30, 0xa1, 0x44, 0x99, 0x22, 0x7f, 0x08, 0x10,
    /* U+0035 "5" (7x10) */
    0xfd, 0x83, 0x06, 0x0f, 0x99, 0x81, 0x83, 0xcc, 0xf0,
    /* U+0036 "6" (7x10) */
    0x18, 0x61, 0x86, 0x0f, 0x99, 0xb1, 0xe3, 0xcc, 0xf0,
    /* U+0037 "7" (7x10) */
    0xff, 0x0a, 0x30, 0x60, 0x83, 0x04, 0x18, 0x30, 0x40,
    /* U+0038 "8" (7x10) */
    0x79, 0x9b, 0x16, 0x67, 0x99, 0xa1, 0xc3, 0xcc, 0xf0,
    /* U+0039 "9" (7x10) */
    0x79, 0x9a, 0x14, 0x3c, 0xef, 0x83, 0x04, 0x18, 0x60,
    /* U+003A ":" (2x8) */
    0xf0, 0x0f,
    /* U+003B ";" (2x10) */
    0xf0, 0x0f, 0x60,
    /* U+003C "<" (6x8) */
    0x04, 0x73, 0xb8, 0xe0, 0xe1, 0xc1,
    /* U+003D "=" (6x4) */
    0xfc, 0x00, 0x3f,
    /* U+003E ">" (6x8) */
    0x81, 0x83, 0x03, 0x0c, 0xc6, 0x20,
    /* U+003F "?" (6x10) */
    0x7b, 0x30, 0x41, 0x0c, 0xe3, 0x00, 0x30, 0xc0,
    /* U+0040 "@" (11x12) */
    0x1f, 0x04, 0x31, 0x01, 0x47, 0xa9, 0x33, 0x26, 0x64, 0xcc, 0x9a, 0x8d,
    0x88, 0x00, 0x80, 0x0f, 0x80,
    /* U+0041 "A" (9x10) */
    0x1c, 0x0e, 0x05, 0x06, 0xc3, 0x21, 0x11, 0xfc, 0xc2, 0x41, 0x60, 0xc0,
    /* U+0042 "B" (7x10) */
    0xfd, 0x8f, 0x1e, 0x3f, 0xd8, 0xf0, 0xe1, 0xc7, 0xf8,
    /* U+0043 "C" (7x10) */
    0x3c, 0xcf, 0x06, 0x08, 0x10, 0x30, 0x60, 0x66, 0x78,
    /* U+0044 "D" (8x10) */
    0xfc, 0xc6, 0xc2, 0xc3, 0xc3, 0xc3, 0xc3, 0xc2, 0xc6, 0xfc,
    /* U+0045 "E" (6x10) */
    0xff, 0x0c, 0x30, 0xff, 0x0c, 0x30, 0xc3, 0xf0,
    /* U+0046 "F" (6x10) */
    0xff, 0x0c, 0x30, 0xff, 0x0c, 0x30, 0xc3, 0x00,
    /* U+0047 "G" (8x10) */
    0x3c, 0x66, 0xc2, 0xc0, 0x80, 0x8f, 0xc3, 0xc3, 0x67, 0x3f,
    /* U+0048 "H" (8x10) */
    0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    /* U+0049 "I" (4x10) */
    0xf6, 0x66, 0x66, 0x66, 0x6f,
    /* U+004A "J" (5x10) */
    0x78, 0x42, 0x10, 0x84, 0x21, 0x9f, 0x80,
    /* U+004B "K" (8x10) */
    0xc6, 0xc4, 0xcc, 0xd8, 0xf0, 0xf8, 0xcc, 0xcc, 0xc6, 0xc3,
    /* U+004C "L" (6x10) */
    0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0x30, 0xc3, 0xf0,
    /* U+004D "M" (9x10) */
    0xc1, 0xf0, 0xf8, 0xfe, 0x5d, 0x6e, 0xe7, 0x23, 0x81, 0xc0, 0xe0, 0x40,
    /* U+004E "N" (8x10) */
    0xc3, 0xe3, 0xe3, 0xf3, 0xdb, 0xdb, 0xcf, 0xc7, 0xc7, 0xc3,
    /* U+004F "O" (8x10) */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c,
    /* U+0050 "P" (7x10) */
    0xfd, 0x8f, 0x0e, 0x1c, 0x7f, 0xb0, 0x60, 0xc1, 0x80,
    /* U+0051 "Q" (8x12) */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c, 0x18, 0x0c,
    /* U+0052 "R" (7x10) */
    0xfd, 0x8f, 0x0e, 0x1c, 0x7f, 0xb3, 0x62, 0xc7, 0x8c,
    /* U+0053 "S" (7x10) */
    0x79, 0x8a, 0x06, 0x07, 0x03, 0x81, 0x83, 0xc4, 0xf0,
    /* U+0054 "T" (7x10) */
    0xfe, 0x60, 0xc1, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x60,
    /* U+0055 "U" (7x10) */
    0xc3, 0x87, 0x0e, 0x1c, 0x38, 0x70, 0xe1, 0x46, 0x78,
    /* U+0056 "V" (8x10) */
    0xc1, 0x43, 0x63, 0x62, 0x22, 0x36, 0x34, 0x14, 0x1c, 0x18,
    /* U+0057 "W" (13x10) */
    0xc7, 0x1a, 0x38, 0x99, 0xcc, 0xca, 0x66, 0xdb, 0x16, 0xd0, 0xa2, 0x87,
    0x1c, 0x38, 0xe1, 0xc6, 0x00,
    /* U+0058 "X" (7x10) */
    0xc7, 0x8d, 0xb1, 0xc3, 0x87, 0x1a, 0x36, 0xc7, 0x0c,
    /* U+0059 "Y" (8x10) */
    0xc3, 0x63, 0x36, 0x3c, 0x1c, 0x18, 0x18, 0x18, 0x18, 0x18,
    /* U+005A "Z" (8x10) */
    0x7f, 0x06, 0x06, 0x0c, 0x18, 0x18, 0x30, 0x60, 0x60, 0xff,
    /* U+005B "[" (3x13) */
    0xfb, 0x6d, 0xb6, 0xdb, 0x6e,
    /* U+005C "" (5x12) */
    0x84, 0x30, 0x84, 0x30, 0x84, 0x30, 0x84, 0x30,
    /* U+005D "]" (3x13) */
    0xed, 0xb6, 0xdb, 0x6d, 0xbe,
    /* U+005E "^" (6x6) */
    0x30, 0xe6, 0x93, 0x86, 0x00,
    /* U+005F "_" (7x1) */
    0xfe,
    /* U+0060 "`" (2x3) */
    0xa4,
    /* U+0061 "a" (6x7) */
    0x72, 0x20, 0xbf, 0x8e, 0x3e, 0xc0,
    /* U+0062 "b" (7x10) */
    0xc1, 0x83, 0x07, 0xcc, 0xd8, 0xf1, 0xe3, 0xcd, 0xf0,
    /* U+0063 "c" (6x7) */
    0x7b, 0x28, 0x20, 0x83, 0x37, 0x80,
    /* U+0064 "d" (6x10) */
    0x04, 0x10, 0x5f, 0xce, 0x18, 0x61, 0xcd, 0xf0,
    /* U+0065 "e" (6x7) */
    0x7b, 0x38, 0xff, 0x83, 0x37, 0x80,
    /* U+0066 "f" (5x10) */
    0x3b, 0x19, 0xf6, 0x31, 0x8c, 0x63, 0x00,
    /* U+0067 "g" (6x11) */
    0x0d, 0xec, 0xa3, 0xc9, 0xe8, 0x3f, 0x86, 0x1f, 0x80,
    /* U+0068 "h" (6x10) */
    0xc3, 0x0c, 0x3e, 0xcf, 0x1c, 0x71, 0xc7, 0x10,
    /* U+0069 "i" (2x10) */
    0xb3, 0xff, 0xf0,
    /* U+006A "j" (3x13) */
    0x4c, 0x36, 0xdb, 0x6d, 0xac,
    /* U+006B "k" (6x10) */
    0xc3, 0x0c, 0x33, 0xdb, 0xcf, 0x36, 0xcf, 0x30,
    /* U+006C "l" (3x10) */
    0xdb, 0x6d, 0xb6, 0xcc,
    /* U+006D "m" (10x7) */
    0xfb, 0xb3, 0x3c, 0xc7, 0x31, 0xcc, 0x73, 0x1c, 0xc4,
    /* U+006E "n" (6x7) */
    0xfb, 0x3c, 0x71, 0xc7, 0x1c, 0x40,
    /* U+006F "o" (6x7) */
    0x7b, 0x38, 0x61, 0x87, 0x37, 0x80,
    /* U+0070 "p" (7x10) */
    0xf9, 0x9b, 0x1e, 0x3c, 0x79, 0xbe, 0x60, 0xc1, 0x80,
    /* U+0071 "q" (6x10) */
    0x7f, 0x38, 0x61, 0x87, 0x37, 0xc1, 0x04, 0x10,
    /* U+0072 "r" (4x7) */
    0xfc, 0xcc, 0xcc, 0xc0,
    /* U+0073 "s" (5x7) */
    0x74, 0x60, 0xe0, 0xc7, 0xc0,
    /* U+0074 "t" (5x9) */
    0x63, 0x3e, 0xc6, 0x31, 0x8c, 0x38,
    /* U+0075 "u" (6x7) */
    0xcf, 0x3c, 0xf3, 0xcf, 0x37, 0xc0,
    /* U+0076 "v" (7x7) */
    0xc6, 0x89, 0x93, 0x62, 0x87, 0x0e, 0x00,
    /* U+0077 "w" (10x7) */
    0x88, 0xe7, 0x29, 0xcb, 0x52, 0x57, 0x98, 0xc6, 0x30,
    /* U+0078 "x" (6x7) */
    0x8f, 0x67, 0x0c, 0x73, 0x68, 0xc0,
    /* U+0079 "y" (7x10) */
    0xc6, 0x89, 0x93, 0x62, 0x87, 0x0e, 0x08, 0x10, 0xc0,
    /* U+007A "z" (6x7) */
    0x7c, 0x31, 0x8c, 0x21, 0x8f, 0xc0,
    /* U+007B "{" (4x13) */
    0x32, 0x22, 0x6c, 0xcc, 0x62, 0x22, 0x30,
    /* U+007C "|" (1x13) */
    0xff, 0xf8,
    /* U+007D "}" (4x13) */
    0xc4, 0x44, 0x63, 0x33, 0x64, 0x44, 0xc0,
    /* U+007E "~" (6x2) */
    0xe2, 0x70,
    /* U+00B0 "" (5x5) */
    0x74, 0xe3, 0x37, 0x00,
    /* U+00B1 "" (6x9) */
    0x10, 0x41, 0x3f, 0x10, 0x41, 0x00, 0xfc,
    /* U+00B2 "" (5x5) */
    0x72, 0x8c, 0xcf, 0x80,
    /* U+00B3 "" (3x5) */
    0xe5, 0x9e,
    /* U+00B5 "" (6x10) */
    0xc7, 0x1c, 0x71, 0xc7, 0x3f, 0xf0, 0xc3, 0x00,
    /* U+00B7 "" (1x2) */
    0xc0,
    /* U+00D7 "" (6x6) */
    0x45, 0xb3, 0x8e, 0x6f, 0x10,
    /* U+00F7 "" (7x7) */
    0x30, 0x60, 0x07, 0xf0, 0x06, 0x0c, 0x00,
    /* U+0394 "" (8x10) */
    0x38, 0x38, 0x28, 0x6c, 0x64, 0x44, 0xc6, 0xc6, 0x83, 0xff,
    /* U+03A9 "" (8x10) */
    0x3c, 0x66, 0xc3, 0xc3, 0xc1, 0xc3, 0xc3, 0x67, 0x66, 0xe7,
    /* U+03BC "" (7x10) */
    0xc5, 0x8b, 0x16, 0x2c, 0x59, 0xbd, 0xe0, 0xc1, 0x80,
    /* U+2013 "" (8x1) */
    0xff,
    /* U+2014 "" (10x1) */
    0xff, 0xc0,
    /* U+2018 "" (2x4) */
    0x6f,
    /* U+2019 "" (2x4) */
    0xf6,
    /* U+201C "" (5x4) */
    0x4c, 0xb7, 0xb0,
    /* U+201D "" (5x4) */
    0xde, 0xd3, 0x20,
    /* U+2022 "" (4x4) */
    0x6f, 0xf6,
    /* U+2026 "" (10x2) */
    0xcc, 0xf3, 0x30,
    /* U+2030 "" (17x10) */
    0x70, 0x80, 0x48, 0xc0, 0x24, 0x40, 0x12, 0x40, 0x09, 0x6c, 0x73, 0xa9,
    0x2c, 0x24, 0xb2, 0x32, 0x59, 0x11, 0x25, 0x90, 0x63, 0x80,
    /* U+2190 "" (10x5) */
    0x30, 0x18, 0x0f, 0xfd, 0x80, 0x30, 0x00,
    /* U+2191 "" (6x10) */
    0x21, 0xcf, 0xad, 0x30, 0xc3, 0x0c, 0x30, 0xc0,
    /* U+2192 "" (10x5) */
    0x03, 0x00, 0x6f, 0xfc, 0x06, 0x03, 0x00,
    /* U+2193 "" (6x10) */
    0x30, 0xc3, 0x0c, 0x30, 0xcb, 0x7e, 0x70, 0x80,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 53, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 67, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 101, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 5, .adv_w = 152, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 134, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 26, .adv_w = 212, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 40, .adv_w = 158, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 50, .adv_w = 57, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 51, .adv_w = 75, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 56, .adv_w = 75, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 63, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 67, .adv_w = 134, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 73, .adv_w = 65, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 74, .adv_w = 90, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 75, .adv_w = 65, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 76, .adv_w = 93, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 84, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 93, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 102, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 128, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 137, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 155, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 164, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 173, .adv_w = 69, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 69, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 178, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 184, .adv_w = 134, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 187, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 193, .adv_w = 109, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 201, .adv_w = 201, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 218, .adv_w = 148, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 230, .adv_w = 148, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 239, .adv_w = 142, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 248, .adv_w = 153, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 258, .adv_w = 133, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 266, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 274, .adv_w = 158, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 284, .adv_w = 160, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 294, .adv_w = 93, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 299, .adv_w = 119, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 148, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 324, .adv_w = 182, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 336, .adv_w = 160, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 346, .adv_w = 159, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 356, .adv_w = 140, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 365, .adv_w = 159, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 377, .adv_w = 147, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 386, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 395, .adv_w = 129, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 404, .adv_w = 154, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 413, .adv_w = 141, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 423, .adv_w = 207, .box_w = 13, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 440, .adv_w = 143, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 138, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 459, .adv_w = 132, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 469, .adv_w = 73, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 474, .adv_w = 93, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 482, .adv_w = 73, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 487, .adv_w = 134, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 492, .adv_w = 126, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 493, .adv_w = 134, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = 8},
    {.bitmap_index = 494, .adv_w = 123, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 500, .adv_w = 133, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 509, .adv_w = 114, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 515, .adv_w = 133, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 523, .adv_w = 125, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 529, .adv_w = 76, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 536, .adv_w = 120, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 545, .adv_w = 130, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 553, .adv_w = 59, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 556, .adv_w = 59, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 561, .adv_w = 123, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 569, .adv_w = 64, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 573, .adv_w = 198, .box_w = 10, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 582, .adv_w = 130, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 588, .adv_w = 126, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 594, .adv_w = 133, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 603, .adv_w = 133, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 611, .adv_w = 86, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 615, .adv_w = 111, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 620, .adv_w = 82, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 626, .adv_w = 130, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 632, .adv_w = 115, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 639, .adv_w = 179, .box_w = 10, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 648, .adv_w = 119, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 654, .adv_w = 115, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 663, .adv_w = 109, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 669, .adv_w = 79, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 676, .adv_w = 79, .box_w = 1, .box_h = 13, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 678, .adv_w = 80, .box_w = 4, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 685, .adv_w = 134, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 687, .adv_w = 105, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 691, .adv_w = 134, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 698, .adv_w = 78, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 702, .adv_w = 77, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 704, .adv_w = 131, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 712, .adv_w = 80, .box_w = 1, .box_h = 2, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 713, .adv_w = 134, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 718, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 725, .adv_w = 148, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 735, .adv_w = 161, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 745, .adv_w = 133, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 754, .adv_w = 132, .box_w = 8, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 755, .adv_w = 175, .box_w = 10, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 757, .adv_w = 64, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 758, .adv_w = 64, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 759, .adv_w = 112, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 762, .adv_w = 112, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 765, .adv_w = 92, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 767, .adv_w = 190, .box_w = 10, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 770, .adv_w = 300, .box_w = 17, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 792, .adv_w = 191, .box_w = 10, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 799, .adv_w = 191, .box_w = 6, .box_h = 10, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 807, .adv_w = 191, .box_w = 10, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 814, .adv_w = 191, .box_w = 6, .box_h = 10, .ofs_x = 3, .ofs_y = 0}
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

const lv_font_t humid1_font_plex_sans_normal_14 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 19,
    .base_line = 4,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 10,
    .x_height = 7,
#endif
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = -1,
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

#endif /* #if HUMID1_FONT_PLEX_SANS_NORMAL_14 */
