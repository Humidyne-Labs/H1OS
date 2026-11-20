/*******************************************************************************
 * Font: humid1_font_plex_sans_normal_12 (sans normal)
 * Size: 12 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_icon_fa7_solid_12 (LVGL >= 9.6.0 Ready)
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

#ifndef HUMID1_FONT_PLEX_SANS_NORMAL_12
#define HUMID1_FONT_PLEX_SANS_NORMAL_12 1
#endif

#if HUMID1_FONT_PLEX_SANS_NORMAL_12

extern const lv_font_t humid1_icon_fa7_solid_12;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (1x9) */
    0xfd, 0x80,
    /* U+0022 "" (4x4) */
    0xff, 0xff,
    /* U+0023 "#" (8x9) */
    0x12, 0x14, 0x7f, 0x24, 0x24, 0xfe, 0x2c, 0x28, 0x68,
    /* U+0024 "$" (5x11) */
    0x23, 0xbf, 0x4e, 0x38, 0xe5, 0xfb, 0x88,
    /* U+0025 "%" (10x9) */
    0x61, 0x2c, 0x89, 0x22, 0x50, 0x69, 0x82, 0x91, 0x24, 0xcb, 0x21, 0x80,
    /* U+0026 "&" (7x9) */
    0x30, 0xb1, 0x23, 0x87, 0x32, 0xa3, 0x66, 0x7a,
    /* U+0027 "'" (2x4) */
    0xff,
    /* U+0028 "(" (3x12) */
    0x2b, 0x49, 0x24, 0x99, 0x10,
    /* U+0029 ")" (3x12) */
    0x89, 0x32, 0x49, 0x69, 0x40,
    /* U+002A "" (5x5) */
    0x21, 0x3e, 0xed, 0x00,
    /* U+002B "+" (6x6) */
    0x61, 0x8f, 0xd8, 0x61, 0x80,
    /* U+002C "," (1x3) */
    0xe0,
    /* U+002D "-" (3x1) */
    0xe0,
    /* U+002E "." (1x2) */
    0xc0,
    /* U+002F "/" (4x11) */
    0x11, 0x13, 0x22, 0x64, 0x44, 0xc0,
    /* U+0030 "0" (6x9) */
    0x7b, 0x28, 0x61, 0x86, 0x18, 0x72, 0x78,
    /* U+0031 "1" (6x9) */
    0x73, 0xc9, 0x04, 0x10, 0x41, 0x0c, 0xfc,
    /* U+0032 "2" (6x9) */
    0x73, 0x60, 0x82, 0x18, 0xc6, 0x30, 0xfc,
    /* U+0033 "3" (5x9) */
    0x74, 0xc6, 0xe1, 0x84, 0x33, 0xf0,
    /* U+0034 "4" (6x9) */
    0x18, 0xe2, 0x92, 0x4a, 0x2f, 0xc2, 0x08,
    /* U+0035 "5" (5x9) */
    0xfc, 0x21, 0x6d, 0x84, 0x33, 0x70,
    /* U+0036 "6" (6x9) */
    0x31, 0x84, 0x3e, 0xce, 0x18, 0x73, 0x78,
    /* U+0037 "7" (5x9) */
    0xfc, 0x62, 0x21, 0x18, 0x84, 0x60,
    /* U+0038 "8" (5x9) */
    0x74, 0xe2, 0xed, 0xc6, 0x3b, 0x70,
    /* U+0039 "9" (6x9) */
    0x7b, 0x38, 0x73, 0x7c, 0x31, 0x84, 0x60,
    /* U+003A ":" (1x7) */
    0xc6,
    /* U+003B ";" (1x8) */
    0xc7,
    /* U+003C "<" (5x7) */
    0x19, 0xb1, 0x86, 0x0c, 0x20,
    /* U+003D "=" (6x4) */
    0xfc, 0x00, 0x3f,
    /* U+003E ">" (5x7) */
    0xc3, 0x06, 0x33, 0x62, 0x00,
    /* U+003F "?" (5x9) */
    0x76, 0xc2, 0x33, 0x10, 0x04, 0x20,
    /* U+0040 "@" (9x10) */
    0x3e, 0x31, 0xbf, 0x75, 0x9a, 0x4d, 0x26, 0x97, 0xae, 0x60, 0x1f, 0x00,
    /* U+0041 "A" (8x9) */
    0x18, 0x18, 0x2c, 0x24, 0x24, 0x7e, 0x46, 0x42, 0xc3,
    /* U+0042 "B" (6x9) */
    0xfa, 0x38, 0x63, 0xfa, 0x38, 0x63, 0xf8,
    /* U+0043 "C" (6x9) */
    0x7b, 0x38, 0x20, 0x82, 0x08, 0x33, 0x78,
    /* U+0044 "D" (6x9) */
    0xf2, 0x28, 0xe1, 0x86, 0x18, 0xe2, 0xf0,
    /* U+0045 "E" (5x9) */
    0xfc, 0x21, 0x0f, 0xc2, 0x10, 0xf8,
    /* U+0046 "F" (5x9) */
    0xfc, 0x21, 0x0f, 0xc2, 0x10, 0x80,
    /* U+0047 "G" (7x9) */
    0x38, 0x8e, 0x04, 0x08, 0xf0, 0x61, 0xa3, 0x3a,
    /* U+0048 "H" (7x9) */
    0xc7, 0x8f, 0x1e, 0x3f, 0xf8, 0xf1, 0xe3, 0xc6,
    /* U+0049 "I" (4x9) */
    0xfc, 0xcc, 0xcc, 0xcc, 0xf0,
    /* U+004A "J" (5x9) */
    0x78, 0x42, 0x10, 0x84, 0x3b, 0x70,
    /* U+004B "K" (6x9) */
    0x8e, 0x69, 0x28, 0xf3, 0x49, 0xa2, 0x8c,
    /* U+004C "L" (6x9) */
    0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0x3e, 0xfc,
    /* U+004D "M" (7x9) */
    0xc7, 0x8f, 0x3d, 0x5b, 0xb2, 0x64, 0xc1, 0x82,
    /* U+004E "N" (6x9) */
    0xc7, 0x1e, 0x69, 0xb6, 0x59, 0xe3, 0x8c,
    /* U+004F "O" (7x9) */
    0x38, 0x9a, 0x1c, 0x18, 0x30, 0x61, 0xa2, 0x38,
    /* U+0050 "P" (6x9) */
    0xfa, 0x38, 0x63, 0xfa, 0x08, 0x20, 0x80,
    /* U+0051 "Q" (7x11) */
    0x38, 0x9a, 0x1c, 0x18, 0x30, 0x61, 0xe2, 0x78, 0x20, 0x70,
    /* U+0052 "R" (6x9) */
    0xfa, 0x38, 0x63, 0xfa, 0x68, 0xa3, 0x84,
    /* U+0053 "S" (5x9) */
    0x76, 0xe1, 0x87, 0x0c, 0x33, 0x70,
    /* U+0054 "T" (6x9) */
    0xfc, 0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0x30,
    /* U+0055 "U" (6x9) */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x73, 0x78,
    /* U+0056 "V" (7x9) */
    0xc2, 0x8d, 0x1b, 0x22, 0x45, 0x8a, 0x0c, 0x18,
    /* U+0057 "W" (11x9) */
    0xc4, 0x69, 0xc9, 0x39, 0x25, 0x26, 0xa4, 0xd7, 0x8c, 0x61, 0x8c, 0x31,
    0x80,
    /* U+0058 "X" (6x9) */
    0x87, 0x25, 0x9c, 0x31, 0xc5, 0xb3, 0x84,
    /* U+0059 "Y" (7x9) */
    0xc6, 0x89, 0xb1, 0x43, 0x82, 0x04, 0x08, 0x10,
    /* U+005A "Z" (6x9) */
    0xfc, 0x30, 0x84, 0x30, 0x84, 0x30, 0xfc,
    /* U+005B "[" (3x12) */
    0xfb, 0x6d, 0xb6, 0xdb, 0x70,
    /* U+005C "" (4x11) */
    0x88, 0x8c, 0x44, 0x42, 0x22, 0x10,
    /* U+005D "]" (3x12) */
    0xed, 0xb6, 0xdb, 0x6d, 0xf0,
    /* U+005E "^" (5x5) */
    0x23, 0x95, 0x98, 0x80,
    /* U+005F "_" (6x1) */
    0xfc,
    /* U+0060 "`" (2x2) */
    0xd0,
    /* U+0061 "a" (6x7) */
    0x72, 0x60, 0x9e, 0x8a, 0x6e, 0xc0,
    /* U+0062 "b" (5x10) */
    0x84, 0x21, 0x6d, 0xc6, 0x31, 0xdd, 0x80,
    /* U+0063 "c" (5x7) */
    0x76, 0xe1, 0x08, 0x6d, 0xc0,
    /* U+0064 "d" (5x10) */
    0x08, 0x42, 0xfd, 0xc6, 0x31, 0xdb, 0x40,
    /* U+0065 "e" (5x7) */
    0x76, 0xe3, 0xf8, 0x6d, 0xc0,
    /* U+0066 "f" (4x10) */
    0x74, 0x4f, 0x44, 0x44, 0x44,
    /* U+0067 "g" (6x11) */
    0x0d, 0xcd, 0xa2, 0x99, 0xc8, 0x3f, 0x86, 0x3f, 0x80,
    /* U+0068 "h" (5x10) */
    0x84, 0x21, 0x6d, 0xc6, 0x31, 0x8c, 0x40,
    /* U+0069 "i" (1x10) */
    0x9f, 0xc0,
    /* U+006A "j" (2x13) */
    0x41, 0x55, 0x55, 0xc0,
    /* U+006B "k" (5x10) */
    0x84, 0x21, 0x3b, 0x73, 0x96, 0x94, 0xc0,
    /* U+006C "l" (2x10) */
    0xaa, 0xaa, 0xb0,
    /* U+006D "m" (9x7) */
    0xb3, 0x6e, 0xe2, 0x31, 0x18, 0x8c, 0x46, 0x22,
    /* U+006E "n" (5x7) */
    0xb6, 0xe3, 0x18, 0xc6, 0x20,
    /* U+006F "o" (5x7) */
    0x76, 0xe3, 0x18, 0xed, 0xc0,
    /* U+0070 "p" (5x10) */
    0xb6, 0xe3, 0x18, 0xee, 0xd0, 0x84, 0x00,
    /* U+0071 "q" (5x10) */
    0x7e, 0xe3, 0x18, 0xed, 0xa1, 0x08, 0x40,
    /* U+0072 "r" (3x7) */
    0xfa, 0x49, 0x20,
    /* U+0073 "s" (4x7) */
    0xe8, 0x8e, 0x1b, 0xe0,
    /* U+0074 "t" (4x9) */
    0x44, 0xf4, 0x44, 0x44, 0x70,
    /* U+0075 "u" (5x7) */
    0x8c, 0x63, 0x18, 0xef, 0xe0,
    /* U+0076 "v" (6x7) */
    0xc5, 0x34, 0x92, 0x38, 0xc3, 0x00,
    /* U+0077 "w" (9x7) */
    0xcc, 0xa6, 0x53, 0x2a, 0xa7, 0x71, 0x98, 0xcc,
    /* U+0078 "x" (5x7) */
    0x9e, 0x9c, 0xc7, 0x6a, 0x60,
    /* U+0079 "y" (6x10) */
    0xc5, 0x34, 0x92, 0x78, 0xc3, 0x0c, 0x21, 0x80,
    /* U+007A "z" (5x7) */
    0xf8, 0xcc, 0x46, 0x63, 0xe0,
    /* U+007B "{" (3x12) */
    0x69, 0x2d, 0x32, 0x49, 0x30,
    /* U+007C "|" (2x12) */
    0xff, 0xff, 0xff,
    /* U+007D "}" (3x12) */
    0xc9, 0x24, 0x5a, 0x49, 0x60,
    /* U+007E "~" (5x2) */
    0xe1, 0xc0,
    /* U+00B0 "" (4x5) */
    0x6f, 0x9b, 0xe0,
    /* U+00B1 "" (6x8) */
    0x61, 0x8f, 0xd8, 0x61, 0x80, 0x3f,
    /* U+00B2 "" (3x4) */
    0xe5, 0x70,
    /* U+00B3 "" (3x4) */
    0xec, 0xf0,
    /* U+00B5 "" (5x10) */
    0x8c, 0x63, 0x18, 0xef, 0xf0, 0x84, 0x00,
    /* U+00B7 "" (1x2) */
    0xc0,
    /* U+00D7 "" (5x6) */
    0x8e, 0xdc, 0xed, 0xc4,
    /* U+00F7 "" (6x7) */
    0x20, 0x00, 0x3f, 0x00, 0x82, 0x00,
    /* U+0394 "" (7x9) */
    0x30, 0x70, 0xe3, 0x44, 0xc8, 0xb1, 0x63, 0xfe,
    /* U+03A9 "" (7x9) */
    0x38, 0x9a, 0x1c, 0x18, 0x30, 0x51, 0x36, 0xee,
    /* U+03BC "" (6x9) */
    0x8a, 0x28, 0xa2, 0x8b, 0x6e, 0xe0, 0x80,
    /* U+2013 "" (6x1) */
    0xfc,
    /* U+2014 "" (8x1) */
    0xff,
    /* U+2018 "" (1x4) */
    0xf0,
    /* U+2019 "" (1x3) */
    0xe0,
    /* U+201C "" (4x4) */
    0x99, 0x99,
    /* U+201D "" (4x4) */
    0x99, 0x92,
    /* U+2022 "" (3x3) */
    0xff, 0x80,
    /* U+2026 "" (9x2) */
    0x88, 0xc4, 0x40,
    /* U+2030 "" (14x9) */
    0x61, 0x02, 0xc8, 0x09, 0x20, 0x25, 0x00, 0x69, 0x98, 0x29, 0x51, 0x25,
    0x4c, 0xb7, 0x21, 0x98,
    /* U+2190 "" (8x5) */
    0x20, 0x40, 0xff, 0x40, 0x20,
    /* U+2191 "" (5x8) */
    0x77, 0xea, 0x42, 0x10, 0x84,
    /* U+2192 "" (8x5) */
    0x04, 0x02, 0xff, 0x02, 0x04,
    /* U+2193 "" (5x8) */
    0x21, 0x08, 0x42, 0x55, 0xc4,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 45, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 57, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 87, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 4, .adv_w = 130, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 13, .adv_w = 115, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 20, .adv_w = 182, .box_w = 10, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 32, .adv_w = 136, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 40, .adv_w = 49, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 41, .adv_w = 65, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 46, .adv_w = 65, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 51, .adv_w = 99, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 55, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 60, .adv_w = 56, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 61, .adv_w = 77, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 62, .adv_w = 56, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 63, .adv_w = 80, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 69, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 76, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 83, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 90, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 96, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 109, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 116, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 128, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 135, .adv_w = 60, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 136, .adv_w = 60, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 137, .adv_w = 115, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 115, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 145, .adv_w = 115, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 94, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 156, .adv_w = 172, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 168, .adv_w = 127, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 177, .adv_w = 127, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 184, .adv_w = 122, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 191, .adv_w = 131, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 114, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 204, .adv_w = 109, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 210, .adv_w = 135, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 218, .adv_w = 137, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 226, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 231, .adv_w = 102, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 237, .adv_w = 127, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 244, .adv_w = 98, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 156, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 259, .adv_w = 137, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 266, .adv_w = 137, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 274, .adv_w = 120, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 281, .adv_w = 137, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 291, .adv_w = 126, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 298, .adv_w = 115, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 304, .adv_w = 111, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 311, .adv_w = 132, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 318, .adv_w = 121, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 326, .adv_w = 178, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 123, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 346, .adv_w = 118, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 113, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 361, .adv_w = 62, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 366, .adv_w = 80, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 372, .adv_w = 62, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 377, .adv_w = 115, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 381, .adv_w = 108, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 382, .adv_w = 115, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 383, .adv_w = 105, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 389, .adv_w = 114, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 396, .adv_w = 98, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 401, .adv_w = 114, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 408, .adv_w = 107, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 413, .adv_w = 65, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 418, .adv_w = 103, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 427, .adv_w = 111, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 434, .adv_w = 51, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 436, .adv_w = 51, .box_w = 2, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 440, .adv_w = 105, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 447, .adv_w = 55, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 450, .adv_w = 169, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 458, .adv_w = 111, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 463, .adv_w = 108, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 468, .adv_w = 114, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 475, .adv_w = 114, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 482, .adv_w = 74, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 485, .adv_w = 95, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 489, .adv_w = 70, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 494, .adv_w = 111, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 499, .adv_w = 98, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 505, .adv_w = 153, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 513, .adv_w = 102, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 518, .adv_w = 99, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 526, .adv_w = 94, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 531, .adv_w = 68, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 536, .adv_w = 68, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 539, .adv_w = 68, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 544, .adv_w = 115, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 546, .adv_w = 90, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 549, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 555, .adv_w = 66, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 557, .adv_w = 66, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 559, .adv_w = 112, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 566, .adv_w = 68, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 567, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 571, .adv_w = 115, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 577, .adv_w = 127, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 585, .adv_w = 138, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 593, .adv_w = 114, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 600, .adv_w = 113, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 601, .adv_w = 150, .box_w = 8, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 602, .adv_w = 55, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 603, .adv_w = 55, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 604, .adv_w = 96, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 606, .adv_w = 96, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 608, .adv_w = 79, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 610, .adv_w = 162, .box_w = 9, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 613, .adv_w = 257, .box_w = 14, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 629, .adv_w = 164, .box_w = 8, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 634, .adv_w = 164, .box_w = 5, .box_h = 8, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 639, .adv_w = 164, .box_w = 8, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 644, .adv_w = 164, .box_w = 5, .box_h = 8, .ofs_x = 3, .ofs_y = 0}
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

const lv_font_t humid1_font_plex_sans_normal_12 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 17,
    .base_line = 4,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 9,
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
    .fallback = &humid1_icon_fa7_solid_12,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_SANS_NORMAL_12 */
