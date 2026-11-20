/*******************************************************************************
 * Font: humid1_font_noto_sans_italic_14 (noto_sans italic)
 * Size: 14 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_font_noto_sans_normal_14 (LVGL >= 9.6.0 Ready)
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

#ifndef HUMID1_FONT_NOTO_SANS_ITALIC_14
#define HUMID1_FONT_NOTO_SANS_ITALIC_14 1
#endif

#if HUMID1_FONT_NOTO_SANS_ITALIC_14

extern const lv_font_t humid1_font_noto_sans_normal_14;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (4x10) */
    0x33, 0x36, 0x66, 0x60, 0x4c,
    /* U+0022 "" (5x4) */
    0x5a, 0xd7, 0xa0,
    /* U+0023 "#" (9x10) */
    0x09, 0x0d, 0x9f, 0xef, 0xf1, 0x23, 0xfb, 0xfc, 0x48, 0x2c, 0x34, 0x00,
    /* U+0024 "$" (7x10) */
    0x04, 0x3c, 0xf9, 0x43, 0x83, 0x87, 0x8b, 0xfc, 0xf0,
    /* U+0025 "%" (10x10) */
    0x70, 0xbc, 0x49, 0x22, 0x5e, 0xf7, 0xfa, 0xd1, 0xa4, 0xc9, 0x22, 0x90,
    0xe0,
    /* U+0026 "&" (8x10) */
    0x1c, 0x3c, 0x64, 0x6c, 0x38, 0x73, 0xda, 0x8e, 0xfe, 0xf6,
    /* U+0027 "'" (2x4) */
    0x57,
    /* U+0028 "(" (4x12) */
    0x12, 0x64, 0xc8, 0x88, 0x88, 0x8c,
    /* U+0029 ")" (4x12) */
    0x23, 0x33, 0x33, 0x33, 0x26, 0xc8,
    /* U+002A "" (7x6) */
    0x19, 0xa0, 0xf9, 0xc6, 0x81, 0x00,
    /* U+002B "+" (6x7) */
    0x30, 0xc3, 0x3f, 0xfc, 0xc3, 0x00,
    /* U+002C "," (3x4) */
    0x2d, 0x60,
    /* U+002D "-" (4x2) */
    0x7f,
    /* U+002E "." (2x2) */
    0x70,
    /* U+002F "/" (6x10) */
    0x04, 0x30, 0x86, 0x30, 0xc6, 0x18, 0xc2, 0x00,
    /* U+0030 "0" (7x10) */
    0x1c, 0x7d, 0x9b, 0x36, 0x78, 0xf1, 0xe6, 0x7c, 0xf0,
    /* U+0031 "1" (5x10) */
    0x1b, 0xfe, 0x31, 0x18, 0xc6, 0x31, 0x00,
    /* U+0032 "2" (7x10) */
    0x1c, 0xfc, 0x18, 0x30, 0xe3, 0x8e, 0x30, 0xfd, 0xf8,
    /* U+0033 "3" (7x10) */
    0x1c, 0x7c, 0x08, 0x33, 0xc7, 0x81, 0x83, 0xfd, 0xf0,
    /* U+0034 "4" (7x10) */
    0x06, 0x1c, 0x78, 0xa2, 0x49, 0xbf, 0xff, 0x08, 0x10,
    /* U+0035 "5" (7x10) */
    0x3e, 0x7c, 0x81, 0xc7, 0xc1, 0xc1, 0x86, 0xfc, 0xf0,
    /* U+0036 "6" (6x10) */
    0x1c, 0xf6, 0x36, 0xff, 0x38, 0xf3, 0xf9, 0xc0,
    /* U+0037 "7" (7x10) */
    0xff, 0xfc, 0x30, 0x41, 0x86, 0x0c, 0x30, 0xc1, 0x80,
    /* U+0038 "8" (7x10) */
    0x1c, 0x7c, 0x89, 0x31, 0xc7, 0x91, 0xe3, 0x7c, 0x70,
    /* U+0039 "9" (6x10) */
    0x39, 0xfc, 0xf3, 0xcf, 0xf6, 0xc6, 0xf3, 0x80,
    /* U+003A ":" (3x8) */
    0x24, 0x00, 0x16,
    /* U+003B ";" (3x9) */
    0x24, 0x00, 0x34, 0x80,
    /* U+003C "<" (7x6) */
    0x0c, 0x73, 0x87, 0x03, 0x81, 0xc0,
    /* U+003D "=" (6x4) */
    0xff, 0xff, 0xff,
    /* U+003E ">" (6x6) */
    0xc1, 0xc1, 0xc3, 0x73, 0x00,
    /* U+003F "?" (6x10) */
    0x71, 0xe0, 0xc6, 0x39, 0x86, 0x00, 0x43, 0x00,
    /* U+0040 "@" (10x10) */
    0x1f, 0x0c, 0x34, 0xf6, 0x6d, 0x92, 0x6c, 0x9b, 0x6e, 0x6e, 0x40, 0x0f,
    0x80,
    /* U+0041 "A" (9x10) */
    0x07, 0x03, 0x83, 0xc1, 0x61, 0xb0, 0x88, 0xfc, 0xfe, 0x61, 0xe0, 0xc0,
    /* U+0042 "B" (8x10) */
    0x3e, 0x3f, 0x33, 0x33, 0x7e, 0x7e, 0x62, 0x66, 0x7e, 0xfc,
    /* U+0043 "C" (7x10) */
    0x1e, 0x7d, 0x86, 0x0c, 0x18, 0x30, 0x60, 0xfc, 0xf8,
    /* U+0044 "D" (9x10) */
    0x3e, 0x1f, 0x8c, 0x66, 0x32, 0x1b, 0x0d, 0x8c, 0xc6, 0x7e, 0x7e, 0x00,
    /* U+0045 "E" (8x10) */
    0x3f, 0x3e, 0x30, 0x30, 0x3e, 0x7c, 0x60, 0x60, 0x7c, 0xfc,
    /* U+0046 "F" (7x10) */
    0x7e, 0xf9, 0x83, 0x07, 0x9f, 0x30, 0x60, 0x81, 0x00,
    /* U+0047 "G" (8x10) */
    0x1f, 0x3f, 0x60, 0xc0, 0xce, 0xce, 0xc6, 0xc6, 0xfe, 0x7c,
    /* U+0048 "H" (10x10) */
    0x30, 0xcc, 0x23, 0x18, 0xc6, 0x3f, 0x9f, 0xe6, 0x11, 0x8c, 0x63, 0x30,
    0xc0,
    /* U+0049 "I" (6x10) */
    0x3c, 0xe3, 0x0c, 0x30, 0x86, 0x18, 0x63, 0xc0,
    /* U+004A "J" (6x13) */
    0x04, 0x30, 0xc3, 0x08, 0x61, 0x86, 0x18, 0x43, 0x3c, 0xe0,
    /* U+004B "K" (9x10) */
    0x31, 0x99, 0x8d, 0x87, 0x83, 0xc3, 0xe1, 0xb0, 0xcc, 0x66, 0x63, 0x00,
    /* U+004C "L" (6x10) */
    0x30, 0xc3, 0x0c, 0x61, 0x86, 0x18, 0x7f, 0xf0,
    /* U+004D "M" (12x10) */
    0x38, 0x73, 0x87, 0x38, 0xf2, 0x8a, 0x69, 0xe6, 0x96, 0x6b, 0x64, 0xe6,
    0x4e, 0x4c, 0xcc,
    /* U+004E "N" (10x10) */
    0x38, 0x4e, 0x33, 0x8c, 0xb3, 0x6c, 0x99, 0x26, 0x79, 0x1e, 0x43, 0xb0,
    0xc0,
    /* U+004F "O" (8x10) */
    0x1e, 0x3f, 0x63, 0xc1, 0xc1, 0xc3, 0xc3, 0xc7, 0xfe, 0x7c,
    /* U+0050 "P" (8x10) */
    0x3e, 0x3f, 0x33, 0x33, 0x63, 0x7e, 0x7c, 0x60, 0x60, 0xc0,
    /* U+0051 "Q" (8x12) */
    0x1e, 0x3f, 0x63, 0xc1, 0xc1, 0xc3, 0xc3, 0xc6, 0xfe, 0x7c, 0x0c, 0x0c,
    /* U+0052 "R" (8x10) */
    0x3e, 0x3f, 0x33, 0x33, 0x22, 0x7e, 0x7c, 0x6c, 0x6e, 0xe6,
    /* U+0053 "S" (7x10) */
    0x1e, 0x7c, 0x81, 0x83, 0x83, 0x83, 0x06, 0xfc, 0xf0,
    /* U+0054 "T" (7x10) */
    0xff, 0xfc, 0xc1, 0x83, 0x06, 0x08, 0x30, 0x60, 0xc0,
    /* U+0055 "U" (8x10) */
    0x61, 0x63, 0x63, 0x43, 0xc3, 0xc2, 0xc6, 0xc6, 0xfc, 0x78,
    /* U+0056 "V" (8x10) */
    0xc3, 0xc3, 0x46, 0x46, 0x4c, 0x48, 0x58, 0x70, 0x70, 0x60,
    /* U+0057 "W" (12x10) */
    0xc6, 0x3c, 0x63, 0xce, 0x2c, 0xa6, 0xca, 0x6d, 0xac, 0xd2, 0xcf, 0x38,
    0xe3, 0x86, 0x30,
    /* U+0058 "X" (9x10) */
    0x31, 0x99, 0x8d, 0x83, 0xc1, 0xc0, 0xe0, 0xf0, 0xc8, 0xc6, 0x63, 0x00,
    /* U+0059 "Y" (8x10) */
    0xc3, 0x46, 0x6c, 0x6c, 0x78, 0x30, 0x30, 0x20, 0x60, 0x60,
    /* U+005A "Z" (8x10) */
    0x3f, 0x3f, 0x06, 0x0c, 0x18, 0x30, 0x30, 0x60, 0xfc, 0xfc,
    /* U+005B "[" (5x13) */
    0x39, 0xc8, 0x46, 0x31, 0x88, 0x46, 0x31, 0xce, 0x00,
    /* U+005C "" (3x10) */
    0x92, 0x6d, 0xb2, 0x4c,
    /* U+005D "]" (6x13) */
    0x1c, 0x60, 0x86, 0x18, 0x61, 0x04, 0x30, 0xc3, 0x38, 0xe0,
    /* U+005E "^" (7x7) */
    0x08, 0x30, 0x71, 0xa2, 0x4c, 0xf0, 0x80,
    /* U+005F "_" (5x1) */
    0xf8,
    /* U+0060 "`" (3x2) */
    0xcc,
    /* U+0061 "a" (7x8) */
    0x36, 0xfb, 0x36, 0x68, 0xd1, 0xbe, 0x74,
    /* U+0062 "b" (7x11) */
    0x30, 0x60, 0xc1, 0x73, 0xec, 0x58, 0xb3, 0x66, 0xfb, 0x60,
    /* U+0063 "c" (5x8) */
    0x3b, 0xf1, 0x88, 0x63, 0xce,
    /* U+0064 "d" (7x11) */
    0x02, 0x0c, 0x19, 0xb7, 0xd9, 0xb3, 0x46, 0x8d, 0xf3, 0xa0,
    /* U+0065 "e" (6x8) */
    0x39, 0xfc, 0xff, 0xfa, 0x0f, 0x9e,
    /* U+0066 "f" (7x14) */
    0x0e, 0x1c, 0x60, 0xe3, 0xc2, 0x04, 0x18, 0x30, 0x60, 0x83, 0x0e, 0x18,
    0x00,
    /* U+0067 "g" (8x11) */
    0x1b, 0x3e, 0x66, 0x66, 0x66, 0x66, 0x7c, 0x74, 0x0c, 0xf8, 0x70,
    /* U+0068 "h" (7x11) */
    0x30, 0x60, 0xc1, 0x73, 0xee, 0x58, 0xb3, 0x66, 0x8f, 0x10,
    /* U+0069 "i" (4x11) */
    0x33, 0x03, 0x66, 0x66, 0x6c, 0xc0,
    /* U+006A "j" (6x14) */
    0x0c, 0x10, 0x03, 0x08, 0x61, 0x86, 0x18, 0xc3, 0x0c, 0xf3, 0x80,
    /* U+006B "k" (8x11) */
    0x30, 0x30, 0x30, 0x33, 0x26, 0x6c, 0x78, 0x78, 0x6c, 0x4c, 0xc6,
    /* U+006C "l" (4x11) */
    0x33, 0x33, 0x26, 0x66, 0x64, 0xc0,
    /* U+006D "m" (12x8) */
    0x2e, 0x63, 0xff, 0x73, 0x36, 0x62, 0x66, 0x26, 0x66, 0x46, 0x6c, 0x46,
    /* U+006E "n" (7x8) */
    0x2e, 0x7d, 0xcb, 0x16, 0x6c, 0xd1, 0xe2,
    /* U+006F "o" (6x8) */
    0x39, 0x3c, 0x71, 0x8f, 0x3f, 0x9e,
    /* U+0070 "p" (7x11) */
    0x2e, 0x7d, 0x8b, 0x16, 0x6c, 0xff, 0x6c, 0xc1, 0x82, 0x00,
    /* U+0071 "q" (7x11) */
    0x36, 0xfb, 0x36, 0x68, 0xd1, 0xbe, 0x74, 0x18, 0x30, 0x60,
    /* U+0072 "r" (6x8) */
    0x2d, 0xf7, 0x18, 0x61, 0x8c, 0x30,
    /* U+0073 "s" (6x8) */
    0x39, 0xf6, 0x0c, 0x18, 0x2f, 0xbc,
    /* U+0074 "t" (5x10) */
    0x23, 0x3f, 0xec, 0x63, 0x18, 0xe7, 0x00,
    /* U+0075 "u" (7x8) */
    0x47, 0x8f, 0x16, 0x6c, 0xd9, 0xbf, 0x74,
    /* U+0076 "v" (6x8) */
    0x8f, 0x3c, 0xb6, 0xd3, 0xce, 0x18,
    /* U+0077 "w" (10x8) */
    0xcc, 0xf7, 0x3d, 0x4b, 0x56, 0xf5, 0x39, 0xce, 0x73, 0x18,
    /* U+0078 "x" (7x8) */
    0x66, 0x4c, 0xf1, 0xc3, 0x8f, 0x3b, 0x66,
    /* U+0079 "y" (8x11) */
    0x23, 0x33, 0x32, 0x36, 0x34, 0x1c, 0x18, 0x18, 0x30, 0xf0, 0xc0,
    /* U+007A "z" (6x8) */
    0x7d, 0xf1, 0x84, 0x31, 0x8f, 0xbe,
    /* U+007B "{" (6x13) */
    0x1c, 0x63, 0x0c, 0x33, 0x8c, 0x18, 0x61, 0x86, 0x18, 0x20,
    /* U+007C "|" (1x14) */
    0xff, 0xfc,
    /* U+007D "}" (6x13) */
    0x30, 0xe1, 0x86, 0x10, 0x60, 0xc6, 0x30, 0x86, 0x38, 0xc0,
    /* U+007E "~" (6x3) */
    0x63, 0xf1, 0xc0,
    /* U+00B0 "" (4x5) */
    0x69, 0x99, 0x60,
    /* U+00B1 "" (6x9) */
    0x30, 0xc3, 0x3f, 0xfc, 0xc3, 0x3f, 0xfc,
    /* U+00B2 "" (5x6) */
    0x72, 0xc4, 0x44, 0x78,
    /* U+00B3 "" (5x6) */
    0x72, 0xc4, 0xe3, 0x78,
    /* U+00B5 "" (8x11) */
    0x23, 0x23, 0x62, 0x62, 0x66, 0x66, 0xee, 0xf4, 0xc0, 0xc0, 0x80,
    /* U+00B7 "" (2x2) */
    0xf0,
    /* U+00D7 "" (6x6) */
    0xc5, 0xb3, 0x8e, 0x6f, 0x10,
    /* U+00F7 "" (6x7) */
    0x10, 0xc0, 0x3f, 0xfc, 0x43, 0x00,
    /* U+0394 "" (7x10) */
    0x0c, 0x3c, 0x79, 0xb3, 0x6c, 0xd9, 0xe1, 0xff, 0xfc,
    /* U+03A9 "" (10x10) */
    0x0f, 0x0f, 0xe3, 0x1d, 0x83, 0x60, 0xd8, 0x26, 0x18, 0x8c, 0xf7, 0xb9,
    0xe0,
    /* U+03BC "" (8x11) */
    0x23, 0x23, 0x62, 0x62, 0x66, 0x66, 0xee, 0xf4, 0xc0, 0xc0, 0x80,
    /* U+2013 "" (6x2) */
    0x7f, 0xf0,
    /* U+2014 "" (13x2) */
    0x7f, 0xff, 0xff, 0xc0,
    /* U+2018 "" (3x3) */
    0x6b, 0x00,
    /* U+2019 "" (3x3) */
    0x7a, 0x00,
    /* U+201C "" (6x3) */
    0x6d, 0x6d, 0x80,
    /* U+201D "" (6x3) */
    0x6f, 0x69, 0x00,
    /* U+2022 "" (3x4) */
    0x7f, 0xb0,
    /* U+2026 "" (10x2) */
    0x4c, 0xf3, 0x30,
    /* U+2030 "" (15x10) */
    0x70, 0x81, 0xe2, 0x02, 0x48, 0x04, 0xb4, 0x2f, 0x7c, 0xfd, 0x6b, 0x46,
    0x94, 0x99, 0x29, 0x22, 0x94, 0x87, 0x38,
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
    {.bitmap_index = 0, .adv_w = 58, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 60, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 5, .adv_w = 97, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 8, .adv_w = 145, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 20, .adv_w = 123, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 29, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 42, .adv_w = 155, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 54, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 53, .adv_w = 72, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 59, .adv_w = 72, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 65, .adv_w = 123, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 71, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 77, .adv_w = 62, .box_w = 3, .box_h = 4, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 79, .adv_w = 71, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 80, .adv_w = 60, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 81, .adv_w = 89, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 89, .adv_w = 120, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 98, .adv_w = 123, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 120, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 114, .adv_w = 123, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 123, .adv_w = 120, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 132, .adv_w = 120, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 123, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 149, .adv_w = 123, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 158, .adv_w = 120, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 120, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 60, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 178, .adv_w = 60, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 182, .adv_w = 128, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 188, .adv_w = 128, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 191, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 196, .adv_w = 101, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 204, .adv_w = 188, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 136, .box_w = 9, .box_h = 10, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 229, .adv_w = 135, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 239, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 248, .adv_w = 151, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 260, .adv_w = 119, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 270, .adv_w = 115, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 279, .adv_w = 151, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 289, .adv_w = 155, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 302, .adv_w = 81, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 310, .adv_w = 71, .box_w = 6, .box_h = 13, .ofs_x = -2, .ofs_y = -3},
    {.bitmap_index = 320, .adv_w = 134, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 332, .adv_w = 113, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 340, .adv_w = 194, .box_w = 12, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 355, .adv_w = 166, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 368, .adv_w = 160, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 378, .adv_w = 133, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 160, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 400, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 410, .adv_w = 115, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 419, .adv_w = 117, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 428, .adv_w = 151, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 438, .adv_w = 129, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 448, .adv_w = 197, .box_w = 12, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 463, .adv_w = 130, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 475, .adv_w = 122, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 485, .adv_w = 120, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 495, .adv_w = 71, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 504, .adv_w = 89, .box_w = 3, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 508, .adv_w = 71, .box_w = 6, .box_h = 13, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 518, .adv_w = 125, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 525, .adv_w = 89, .box_w = 5, .box_h = 1, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 526, .adv_w = 69, .box_w = 3, .box_h = 2, .ofs_x = 2, .ofs_y = 9},
    {.bitmap_index = 527, .adv_w = 129, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 534, .adv_w = 130, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 544, .adv_w = 105, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 549, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 559, .adv_w = 121, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 565, .adv_w = 80, .box_w = 7, .box_h = 14, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 578, .adv_w = 129, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 589, .adv_w = 132, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 599, .adv_w = 63, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 605, .adv_w = 63, .box_w = 6, .box_h = 14, .ofs_x = -2, .ofs_y = -3},
    {.bitmap_index = 616, .adv_w = 122, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 627, .adv_w = 64, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 633, .adv_w = 199, .box_w = 12, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 645, .adv_w = 132, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 652, .adv_w = 129, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 658, .adv_w = 130, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 668, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 678, .adv_w = 91, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 684, .adv_w = 102, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 690, .adv_w = 88, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 697, .adv_w = 132, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 704, .adv_w = 111, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 710, .adv_w = 173, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 720, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 727, .adv_w = 113, .box_w = 8, .box_h = 11, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 738, .adv_w = 101, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 744, .adv_w = 76, .box_w = 6, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 754, .adv_w = 123, .box_w = 1, .box_h = 14, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 756, .adv_w = 76, .box_w = 6, .box_h = 13, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 766, .adv_w = 128, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 769, .adv_w = 92, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 772, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 779, .adv_w = 81, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 783, .adv_w = 81, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 787, .adv_w = 133, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 798, .adv_w = 64, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 799, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 804, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 810, .adv_w = 132, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 819, .adv_w = 162, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 832, .adv_w = 137, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 843, .adv_w = 108, .box_w = 6, .box_h = 2, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 845, .adv_w = 215, .box_w = 13, .box_h = 2, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 849, .adv_w = 45, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 851, .adv_w = 45, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 853, .adv_w = 91, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 856, .adv_w = 91, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 859, .adv_w = 81, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 861, .adv_w = 187, .box_w = 10, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 864, .adv_w = 269, .box_w = 15, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 883, .adv_w = 178, .box_w = 9, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 887, .adv_w = 98, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 888, .adv_w = 178, .box_w = 9, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 892, .adv_w = 98, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 0}
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

const lv_font_t humid1_font_noto_sans_italic_14 = {
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
    .fallback = &humid1_font_noto_sans_normal_14,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_NOTO_SANS_ITALIC_14 */
