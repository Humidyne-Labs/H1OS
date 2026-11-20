/*******************************************************************************
 * Font: humid1_font_plex_mono_normal_14 (mono normal)
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

#ifndef HUMID1_FONT_PLEX_MONO_NORMAL_14
#define HUMID1_FONT_PLEX_MONO_NORMAL_14 1
#endif

#if HUMID1_FONT_PLEX_MONO_NORMAL_14

extern const lv_font_t humid1_font_plex_sans_normal_14;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x10) */
    0xff, 0x54, 0xf0,
    /* U+0022 "" (4x4) */
    0xdd, 0xdd,
    /* U+0023 "#" (8x10) */
    0x12, 0x16, 0x16, 0x77, 0x34, 0x24, 0xe7, 0x2c, 0x2c, 0x68,
    /* U+0024 "$" (7x12) */
    0x10, 0xfb, 0x54, 0x8d, 0x0e, 0x07, 0x0b, 0x17, 0xa9, 0xe0, 0x80,
    /* U+0025 "%" (8x10) */
    0x71, 0xd2, 0x92, 0xd4, 0x70, 0x06, 0x29, 0x29, 0x49, 0xc6,
    /* U+0026 "&" (8x10) */
    0x38, 0x64, 0x60, 0x60, 0x30, 0x73, 0xce, 0xce, 0x4e, 0x7b,
    /* U+0027 "'" (2x4) */
    0xff,
    /* U+0028 "(" (4x13) */
    0x36, 0x4c, 0x88, 0x88, 0x8c, 0x46, 0x30,
    /* U+0029 ")" (4x13) */
    0x84, 0x62, 0x23, 0x33, 0x22, 0x64, 0x80,
    /* U+002A "" (7x7) */
    0x10, 0x23, 0xdb, 0xe3, 0x8d, 0x11, 0x00,
    /* U+002B "+" (7x7) */
    0x10, 0x20, 0x47, 0xf1, 0x02, 0x04, 0x00,
    /* U+002C "," (2x4) */
    0xfe,
    /* U+002D "-" (4x1) */
    0xf0,
    /* U+002E "." (2x2) */
    0xf0,
    /* U+002F "/" (6x13) */
    0x04, 0x30, 0x82, 0x18, 0x43, 0x0c, 0x21, 0x84, 0x10, 0xc0,
    /* U+0030 "0" (7x10) */
    0x79, 0x9a, 0x14, 0x3b, 0x76, 0xe1, 0xc2, 0xcc, 0xf0,
    /* U+0031 "1" (7x10) */
    0x38, 0xf3, 0x64, 0xc1, 0x83, 0x06, 0x0c, 0x19, 0xfc,
    /* U+0032 "2" (7x10) */
    0x79, 0x98, 0x10, 0x20, 0xc3, 0x0c, 0x30, 0xc1, 0xfc,
    /* U+0033 "3" (6x10) */
    0x7b, 0x30, 0x43, 0x38, 0x30, 0x41, 0x8d, 0xe0,
    /* U+0034 "4" (7x10) */
    0x18, 0x30, 0xa3, 0x44, 0x99, 0x22, 0x7f, 0x08, 0x10,
    /* U+0035 "5" (7x10) */
    0xfd, 0x83, 0x06, 0x0f, 0x99, 0x81, 0x83, 0xcc, 0xf0,
    /* U+0036 "6" (7x10) */
    0x18, 0x61, 0x86, 0x0f, 0x99, 0xa1, 0xc3, 0xcc, 0xf0,
    /* U+0037 "7" (7x10) */
    0xff, 0x0e, 0x30, 0x60, 0x83, 0x04, 0x18, 0x30, 0x40,
    /* U+0038 "8" (7x10) */
    0x79, 0x8b, 0x16, 0x27, 0x98, 0xa1, 0xc3, 0xc4, 0xf0,
    /* U+0039 "9" (7x10) */
    0x79, 0x9a, 0x14, 0x3c, 0xef, 0x83, 0x06, 0x18, 0x60,
    /* U+003A ":" (2x7) */
    0xf0, 0x3c,
    /* U+003B ";" (2x9) */
    0xf0, 0x3f, 0x80,
    /* U+003C "<" (6x8) */
    0x04, 0x73, 0x30, 0xc0, 0xc1, 0xc1,
    /* U+003D "=" (7x4) */
    0xfe, 0x00, 0x07, 0xf0,
    /* U+003E ">" (6x8) */
    0x83, 0x83, 0x83, 0x0c, 0xee, 0x20,
    /* U+003F "?" (6x10) */
    0x7b, 0x30, 0x43, 0x1c, 0xc3, 0x00, 0x30, 0xc0,
    /* U+0040 "@" (6x12) */
    0x79, 0x18, 0x67, 0xb6, 0x9a, 0x69, 0x9e, 0x04, 0x0e,
    /* U+0041 "A" (8x10) */
    0x18, 0x1c, 0x3c, 0x34, 0x26, 0x26, 0x7e, 0x62, 0x43, 0xc3,
    /* U+0042 "B" (7x10) */
    0xf9, 0x9b, 0x16, 0x6f, 0x98, 0xb1, 0xe3, 0xc5, 0xf0,
    /* U+0043 "C" (6x10) */
    0x39, 0x1c, 0x30, 0x82, 0x0c, 0x30, 0x44, 0xe0,
    /* U+0044 "D" (7x10) */
    0xf9, 0x9b, 0x16, 0x3c, 0x78, 0xf1, 0xe2, 0xcd, 0xf0,
    /* U+0045 "E" (6x10) */
    0xff, 0x0c, 0x30, 0xff, 0x0c, 0x30, 0xc3, 0xf0,
    /* U+0046 "F" (7x10) */
    0xff, 0x83, 0x06, 0x0f, 0xd8, 0x30, 0x60, 0xc1, 0x80,
    /* U+0047 "G" (6x10) */
    0x7b, 0x3c, 0x20, 0x82, 0x78, 0x71, 0xc5, 0xd0,
    /* U+0048 "H" (7x10) */
    0xc7, 0x8f, 0x1e, 0x3f, 0xf8, 0xf1, 0xe3, 0xc7, 0x8c,
    /* U+0049 "I" (6x10) */
    0xfc, 0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0x33, 0xf0,
    /* U+004A "J" (6x10) */
    0x7c, 0x30, 0xc3, 0x0c, 0x30, 0xc3, 0xcd, 0xe0,
    /* U+004B "K" (7x10) */
    0xc7, 0x9b, 0x66, 0x8f, 0x1f, 0x36, 0x66, 0xc5, 0x8c,
    /* U+004C "L" (7x10) */
    0xc1, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0xfc,
    /* U+004D "M" (7x10) */
    0xc7, 0x9f, 0xbd, 0xfb, 0x72, 0xe1, 0xc3, 0x87, 0x0c,
    /* U+004E "N" (6x10) */
    0xc7, 0x9e, 0x69, 0xb6, 0x59, 0x67, 0x8e, 0x30,
    /* U+004F "O" (7x10) */
    0x79, 0x9b, 0x14, 0x38, 0x70, 0xe1, 0xe2, 0xcc, 0xf0,
    /* U+0050 "P" (7x10) */
    0xfd, 0x8b, 0x1e, 0x3c, 0x5f, 0xb0, 0x60, 0xc1, 0x80,
    /* U+0051 "Q" (7x12) */
    0x79, 0x9b, 0x14, 0x38, 0x70, 0xe1, 0xe2, 0xcc, 0xf0, 0x40, 0xe0,
    /* U+0052 "R" (7x10) */
    0xfd, 0x8b, 0x1e, 0x3c, 0x5f, 0xb6, 0x64, 0xcd, 0x8c,
    /* U+0053 "S" (7x10) */
    0x7d, 0x8b, 0x06, 0x07, 0x03, 0x81, 0x83, 0x84, 0xf0,
    /* U+0054 "T" (8x10) */
    0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    /* U+0055 "U" (7x10) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe2, 0xcc, 0xf0,
    /* U+0056 "V" (7x10) */
    0x87, 0x0f, 0x16, 0x24, 0xc9, 0x9a, 0x34, 0x38, 0x60,
    /* U+0057 "W" (8x10) */
    0xc1, 0xc1, 0x59, 0x59, 0x5b, 0x57, 0x57, 0x76, 0x66, 0x66,
    /* U+0058 "X" (7x10) */
    0xc7, 0x99, 0xb3, 0xc3, 0x07, 0x1e, 0x26, 0xc5, 0x0c,
    /* U+0059 "Y" (8x10) */
    0xc3, 0x63, 0x66, 0x36, 0x3c, 0x1c, 0x18, 0x18, 0x18, 0x18,
    /* U+005A "Z" (7x10) */
    0xfe, 0x18, 0x30, 0xc1, 0x06, 0x18, 0x20, 0xc1, 0xfc,
    /* U+005B "[" (4x13) */
    0xf8, 0x88, 0x88, 0x88, 0x88, 0x88, 0xf0,
    /* U+005C "" (6x13) */
    0xc1, 0x04, 0x18, 0x20, 0xc3, 0x04, 0x18, 0x20, 0x83, 0x04,
    /* U+005D "]" (5x13) */
    0xf8, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x3f, 0x80,
    /* U+005E "^" (7x6) */
    0x30, 0x71, 0x22, 0x68, 0x50, 0xc0,
    /* U+005F "_" (7x1) */
    0xfe,
    /* U+0060 "`" (2x3) */
    0xa4,
    /* U+0061 "a" (7x7) */
    0x79, 0x98, 0x33, 0xec, 0xd9, 0x9d, 0x80,
    /* U+0062 "b" (7x10) */
    0xc1, 0x83, 0x07, 0xcc, 0xd8, 0xf1, 0xe3, 0xcd, 0xf0,
    /* U+0063 "c" (6x7) */
    0x39, 0x1c, 0x30, 0xc1, 0x13, 0x80,
    /* U+0064 "d" (6x10) */
    0x04, 0x10, 0x5d, 0xce, 0x18, 0x61, 0xcd, 0xd0,
    /* U+0065 "e" (7x7) */
    0x79, 0x9b, 0x17, 0xfc, 0x18, 0x9f, 0x00,
    /* U+0066 "f" (7x10) */
    0x1e, 0x20, 0x47, 0xf1, 0x02, 0x04, 0x08, 0x11, 0xf8,
    /* U+0067 "g" (7x11) */
    0x06, 0xf3, 0x36, 0x2c, 0xcf, 0x30, 0x3e, 0x87, 0x0d, 0xf0,
    /* U+0068 "h" (6x10) */
    0xc3, 0x0c, 0x36, 0xcf, 0x1c, 0x71, 0xc7, 0x10,
    /* U+0069 "i" (7x10) */
    0x10, 0x30, 0x07, 0x81, 0x02, 0x04, 0x08, 0x11, 0xfc,
    /* U+006A "j" (5x13) */
    0x18, 0xc1, 0xf1, 0x8c, 0x63, 0x18, 0xc6, 0x3f, 0x80,
    /* U+006B "k" (7x10) */
    0xc1, 0x83, 0x06, 0x6d, 0x9e, 0x3c, 0x6c, 0xcd, 0x8c,
    /* U+006C "l" (6x10) */
    0xf0, 0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0x33, 0xf0,
    /* U+006D "m" (7x7) */
    0xa5, 0x6e, 0x4c, 0x99, 0x32, 0x64, 0x80,
    /* U+006E "n" (6x7) */
    0xdb, 0x3c, 0x71, 0xc7, 0x1c, 0x40,
    /* U+006F "o" (7x7) */
    0x79, 0x9a, 0x14, 0x38, 0x59, 0x9e, 0x00,
    /* U+0070 "p" (7x10) */
    0xf9, 0x9b, 0x1e, 0x3c, 0x79, 0xbe, 0x60, 0xc1, 0x80,
    /* U+0071 "q" (6x10) */
    0x77, 0x38, 0x61, 0x87, 0x37, 0x41, 0x04, 0x10,
    /* U+0072 "r" (7x7) */
    0xfe, 0x60, 0xc1, 0x83, 0x06, 0x3f, 0x00,
    /* U+0073 "s" (6x7) */
    0x7f, 0x1c, 0x1f, 0x07, 0x17, 0x80,
    /* U+0074 "t" (6x10) */
    0x20, 0x82, 0x3f, 0x20, 0x82, 0x08, 0x20, 0xf0,
    /* U+0075 "u" (6x7) */
    0xc7, 0x1c, 0x71, 0xc7, 0x37, 0xc0,
    /* U+0076 "v" (7x7) */
    0x87, 0x89, 0x32, 0x46, 0x87, 0x0c, 0x00,
    /* U+0077 "w" (8x7) */
    0xd9, 0xd9, 0x59, 0x57, 0x56, 0x66, 0x66,
    /* U+0078 "x" (6x7) */
    0xc5, 0xb3, 0x8c, 0x39, 0x3c, 0x40,
    /* U+0079 "y" (7x10) */
    0x87, 0x89, 0x32, 0x46, 0x87, 0x0c, 0x18, 0x21, 0xc0,
    /* U+007A "z" (6x7) */
    0xfc, 0x31, 0x8c, 0x63, 0x0f, 0xc0,
    /* U+007B "{" (6x13) */
    0x3c, 0x82, 0x04, 0x10, 0x4f, 0x04, 0x10, 0x42, 0x08, 0x3c,
    /* U+007C "|" (1x13) */
    0xff, 0xf8,
    /* U+007D "}" (6x13) */
    0xf0, 0x41, 0x0c, 0x20, 0x81, 0xc8, 0x20, 0xc1, 0x04, 0xf0,
    /* U+007E "~" (7x3) */
    0x63, 0x6a, 0x70,
    /* U+00B0 "" (5x5) */
    0x74, 0xa7, 0x27, 0x00,
    /* U+00B1 "" (7x9) */
    0x10, 0x20, 0x47, 0xf1, 0x02, 0x04, 0x00, 0xfe,
    /* U+00B2 "" (4x5) */
    0x71, 0x36, 0xf0,
    /* U+00B3 "" (3x5) */
    0xe7, 0x1e,
    /* U+00B5 "" (6x10) */
    0xc7, 0x1c, 0x71, 0xc7, 0x1f, 0x70, 0xc3, 0x00,
    /* U+00B7 "" (2x2) */
    0xf0,
    /* U+00D7 "" (6x6) */
    0xc5, 0xb3, 0x8e, 0x6f, 0x10,
    /* U+00F7 "" (7x7) */
    0x30, 0x60, 0x07, 0xf0, 0x06, 0x0c, 0x00,
    /* U+0394 "" (7x10) */
    0x30, 0x71, 0xe3, 0x44, 0xc9, 0xb1, 0x62, 0x87, 0xfc,
    /* U+03A9 "" (7x10) */
    0x79, 0x9b, 0x14, 0x38, 0x70, 0xf1, 0x66, 0x69, 0xdc,
    /* U+03BC "" (6x10) */
    0xc7, 0x1c, 0x71, 0xc7, 0x1f, 0x70, 0xc3, 0x00,
    /* U+2013 "" (7x1) */
    0xfe,
    /* U+2014 "" (8x1) */
    0xff,
    /* U+2018 "" (2x4) */
    0x5f,
    /* U+2019 "" (3x4) */
    0x7b, 0x40,
    /* U+201C "" (6x4) */
    0x65, 0xb4, 0xf3,
    /* U+201D "" (6x4) */
    0x6d, 0xb4, 0xf2,
    /* U+2022 "" (4x4) */
    0x7f, 0xf7,
    /* U+2026 "" (7x2) */
    0xb7, 0x6c,
    /* U+2030 "" (8x10) */
    0x60, 0x90, 0x90, 0x62, 0x3c, 0x60, 0x3f, 0x2d, 0x2d, 0x3f,
    /* U+2190 "" (8x5) */
    0x30, 0x60, 0xff, 0x60, 0x30,
    /* U+2191 "" (5x10) */
    0x23, 0xbe, 0x52, 0x10, 0x84, 0x21, 0x00,
    /* U+2192 "" (8x5) */
    0x0c, 0x06, 0xff, 0x06, 0x0c,
    /* U+2193 "" (5x10) */
    0x21, 0x08, 0x42, 0x10, 0xbf, 0x71, 0x00,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 134, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 134, .box_w = 2, .box_h = 10, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 134, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 5, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 134, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 26, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 36, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 46, .adv_w = 134, .box_w = 2, .box_h = 4, .ofs_x = 3, .ofs_y = 6},
    {.bitmap_index = 47, .adv_w = 134, .box_w = 4, .box_h = 13, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 54, .adv_w = 134, .box_w = 4, .box_h = 13, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 61, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 68, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 75, .adv_w = 134, .box_w = 2, .box_h = 4, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 76, .adv_w = 134, .box_w = 4, .box_h = 1, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 77, .adv_w = 134, .box_w = 2, .box_h = 2, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 78, .adv_w = 134, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 88, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 97, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 106, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 123, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 132, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 159, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 177, .adv_w = 134, .box_w = 2, .box_h = 7, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 134, .box_w = 2, .box_h = 9, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 182, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 188, .adv_w = 134, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 192, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 206, .adv_w = 134, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 215, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 234, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 242, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 259, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 268, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 276, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 285, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 293, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 301, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 310, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 319, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 328, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 336, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 345, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 134, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 365, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 374, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 383, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 393, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 402, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 421, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 430, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 440, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 134, .box_w = 4, .box_h = 13, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 456, .adv_w = 134, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 466, .adv_w = 134, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 475, .adv_w = 134, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 481, .adv_w = 134, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 482, .adv_w = 134, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = 8},
    {.bitmap_index = 483, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 490, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 499, .adv_w = 134, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 505, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 513, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 520, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 529, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 539, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 547, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 556, .adv_w = 134, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 565, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 574, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 582, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 589, .adv_w = 134, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 595, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 602, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 611, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 619, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 626, .adv_w = 134, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 632, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 640, .adv_w = 134, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 646, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 653, .adv_w = 134, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 660, .adv_w = 134, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 666, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 675, .adv_w = 134, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 681, .adv_w = 134, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 691, .adv_w = 134, .box_w = 1, .box_h = 13, .ofs_x = 4, .ofs_y = -2},
    {.bitmap_index = 693, .adv_w = 134, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 703, .adv_w = 134, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 706, .adv_w = 134, .box_w = 5, .box_h = 5, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 710, .adv_w = 134, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 718, .adv_w = 134, .box_w = 4, .box_h = 5, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 721, .adv_w = 134, .box_w = 3, .box_h = 5, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 723, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 731, .adv_w = 134, .box_w = 2, .box_h = 2, .ofs_x = 3, .ofs_y = 3},
    {.bitmap_index = 732, .adv_w = 134, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 737, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 744, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 753, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 762, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 770, .adv_w = 134, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 771, .adv_w = 134, .box_w = 8, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 772, .adv_w = 134, .box_w = 2, .box_h = 4, .ofs_x = 3, .ofs_y = 6},
    {.bitmap_index = 773, .adv_w = 134, .box_w = 3, .box_h = 4, .ofs_x = 3, .ofs_y = 6},
    {.bitmap_index = 775, .adv_w = 134, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 778, .adv_w = 134, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 781, .adv_w = 134, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 783, .adv_w = 134, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 785, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 795, .adv_w = 134, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 800, .adv_w = 134, .box_w = 5, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 807, .adv_w = 134, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 812, .adv_w = 134, .box_w = 5, .box_h = 10, .ofs_x = 2, .ofs_y = 0}
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

const lv_font_t humid1_font_plex_mono_normal_14 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 19,
    .base_line = 4,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 10,
    .x_height = 7,
#endif
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = -2,
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

#endif /* #if HUMID1_FONT_PLEX_MONO_NORMAL_14 */
