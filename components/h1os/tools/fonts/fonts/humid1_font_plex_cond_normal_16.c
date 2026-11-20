/*******************************************************************************
 * Font: humid1_font_plex_cond_normal_16 (cond normal)
 * Size: 16 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_font_plex_sans_normal_16 (LVGL >= 9.6.0 Ready)
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

#ifndef HUMID1_FONT_PLEX_COND_NORMAL_16
#define HUMID1_FONT_PLEX_COND_NORMAL_16 1
#endif

#if HUMID1_FONT_PLEX_COND_NORMAL_16

extern const lv_font_t humid1_font_plex_sans_normal_16;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x12) */
    0xff, 0xff, 0x0f,
    /* U+0022 "" (4x4) */
    0x99, 0x99,
    /* U+0023 "#" (9x12) */
    0x1b, 0x09, 0x04, 0x82, 0x47, 0xf9, 0xb0, 0xd9, 0xfe, 0x24, 0x12, 0x09,
    0x05, 0x80,
    /* U+0024 "$" (6x13) */
    0x30, 0xef, 0xec, 0xb3, 0xc3, 0x8f, 0x36, 0xff, 0x8c, 0x30,
    /* U+0025 "%" (10x12) */
    0x61, 0x28, 0x89, 0x22, 0x58, 0x94, 0x2d, 0x6e, 0xa4, 0x29, 0x12, 0x44,
    0x92, 0x2c, 0x86,
    /* U+0026 "&" (9x12) */
    0x38, 0x24, 0x13, 0x09, 0x07, 0x81, 0x81, 0xc5, 0x12, 0x87, 0x43, 0x33,
    0xcf, 0x30,
    /* U+0027 "'" (1x4) */
    0xf0,
    /* U+0028 "(" (3x14) */
    0x6b, 0x69, 0x24, 0x92, 0x64, 0x80,
    /* U+0029 ")" (3x14) */
    0x99, 0x26, 0xdb, 0x6d, 0x2d, 0x00,
    /* U+002A "" (6x7) */
    0x30, 0xca, 0x7f, 0x31, 0xe4, 0x80,
    /* U+002B "+" (7x8) */
    0x30, 0x60, 0xc7, 0xf3, 0x06, 0x0c, 0x18,
    /* U+002C "," (2x4) */
    0xfa,
    /* U+002D "-" (4x1) */
    0xf0,
    /* U+002E "." (2x2) */
    0xf0,
    /* U+002F "/" (5x12) */
    0x08, 0xc6, 0x23, 0x18, 0x84, 0x62, 0x11, 0x80,
    /* U+0030 "0" (6x12) */
    0x39, 0x3c, 0x61, 0x86, 0x18, 0x61, 0x87, 0x14, 0xce,
    /* U+0031 "1" (5x12) */
    0x3b, 0xfe, 0xb1, 0x8c, 0x63, 0x18, 0xc6, 0x30,
    /* U+0032 "2" (7x12) */
    0x79, 0x98, 0x10, 0x20, 0xc1, 0x86, 0x18, 0x30, 0xc3, 0x07, 0xf0,
    /* U+0033 "3" (7x12) */
    0x79, 0x98, 0x10, 0x20, 0xcf, 0x03, 0x03, 0x06, 0x0e, 0x37, 0xc0,
    /* U+0034 "4" (8x12) */
    0x06, 0x0e, 0x0e, 0x16, 0x36, 0x26, 0x66, 0x46, 0xff, 0x06, 0x06, 0x06,
    /* U+0035 "5" (6x12) */
    0xff, 0x0c, 0x30, 0xc3, 0xe0, 0xc1, 0x04, 0x31, 0xfe,
    /* U+0036 "6" (6x12) */
    0x3d, 0x8c, 0x30, 0xbb, 0x3c, 0x61, 0x87, 0x14, 0xce,
    /* U+0037 "7" (7x12) */
    0xfe, 0x18, 0x30, 0x60, 0x83, 0x06, 0x18, 0x30, 0x41, 0x83, 0x00,
    /* U+0038 "8" (6x12) */
    0x7b, 0xfe, 0x73, 0xcd, 0xe7, 0xb3, 0x86, 0x1c, 0xde,
    /* U+0039 "9" (6x12) */
    0x7b, 0x38, 0x61, 0x87, 0x37, 0xc1, 0x0c, 0x31, 0x9c,
    /* U+003A ":" (2x9) */
    0xf0, 0x03, 0xc0,
    /* U+003B ";" (2x11) */
    0xf0, 0x03, 0xe8,
    /* U+003C "<" (6x7) */
    0x0c, 0xe6, 0x30, 0x70, 0x70, 0x40,
    /* U+003D "=" (7x4) */
    0xfe, 0x00, 0x07, 0xf0,
    /* U+003E ">" (6x7) */
    0xc1, 0xc1, 0xc3, 0x3b, 0x88, 0x00,
    /* U+003F "?" (5x12) */
    0xf4, 0xc2, 0x31, 0x99, 0x8c, 0x40, 0x18, 0xc0,
    /* U+0040 "@" (11x13) */
    0x1f, 0x06, 0x31, 0x81, 0x27, 0xa9, 0xb7, 0x22, 0x64, 0xcc, 0x99, 0x93,
    0x53, 0xb9, 0x00, 0x30, 0x03, 0xf0,
    /* U+0041 "A" (9x12) */
    0x0c, 0x06, 0x07, 0x02, 0xc1, 0x61, 0x90, 0x8c, 0x7e, 0x63, 0x30, 0xd0,
    0x78, 0x10,
    /* U+0042 "B" (7x12) */
    0xfd, 0x8f, 0x1e, 0x1c, 0x7f, 0xb1, 0xe1, 0xc3, 0x87, 0x1f, 0xe0,
    /* U+0043 "C" (7x12) */
    0x1e, 0xe5, 0x86, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x81, 0xc0, 0xf0,
    /* U+0044 "D" (8x12) */
    0xfc, 0xc6, 0xc3, 0xc3, 0xc1, 0xc1, 0xc1, 0xc1, 0xc3, 0xc3, 0xc6, 0xfc,
    /* U+0045 "E" (6x12) */
    0xff, 0x0c, 0x30, 0xc3, 0xfc, 0x30, 0xc3, 0x0c, 0x3f,
    /* U+0046 "F" (6x12) */
    0xff, 0x0c, 0x30, 0xc3, 0x0f, 0xf0, 0xc3, 0x0c, 0x30,
    /* U+0047 "G" (8x12) */
    0x1f, 0x32, 0x40, 0xc0, 0xc0, 0xc0, 0xcf, 0xc3, 0xc3, 0xc3, 0x73, 0x3f,
    /* U+0048 "H" (8x12) */
    0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xff, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1,
    /* U+0049 "I" (5x12) */
    0xfb, 0x88, 0x42, 0x10, 0x84, 0x21, 0x1d, 0xf0,
    /* U+004A "J" (4x15) */
    0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0xe0,
    /* U+004B "K" (8x12) */
    0xc2, 0xc6, 0xcc, 0xc8, 0xd8, 0xf0, 0xf8, 0xc8, 0xcc, 0xc6, 0xc6, 0xc3,
    /* U+004C "L" (6x12) */
    0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0x3f,
    /* U+004D "M" (11x12) */
    0xe0, 0xfc, 0x1f, 0x83, 0xf8, 0xff, 0x1f, 0xa2, 0xf6, 0xde, 0xdb, 0xca,
    0x79, 0xcf, 0x39, 0xe2, 0x30,
    /* U+004E "N" (9x12) */
    0xc1, 0xf0, 0xfc, 0x7e, 0x3d, 0x9e, 0xcf, 0x37, 0x9b, 0xc7, 0xe1, 0xf0,
    0xf8, 0x30,
    /* U+004F "O" (9x12) */
    0x3e, 0x31, 0x90, 0x78, 0x3c, 0x1e, 0x0f, 0x07, 0x83, 0xc1, 0xa0, 0xd8,
    0xc7, 0xc0,
    /* U+0050 "P" (7x12) */
    0xfd, 0x9f, 0x1e, 0x3c, 0x78, 0xff, 0x60, 0xc1, 0x83, 0x06, 0x00,
    /* U+0051 "Q" (10x14) */
    0x1e, 0x18, 0xc4, 0x1b, 0x02, 0xc0, 0xb0, 0x3c, 0x0b, 0x02, 0xc0, 0x90,
    0x66, 0x30, 0x78, 0x06, 0x00, 0xc0,
    /* U+0052 "R" (8x12) */
    0xf8, 0xcc, 0xc6, 0xc6, 0xc6, 0xc4, 0xf8, 0xc8, 0xcc, 0xc4, 0xc6, 0xc3,
    /* U+0053 "S" (6x12) */
    0x7f, 0x1c, 0x30, 0xc1, 0xc3, 0xc3, 0x04, 0x18, 0xfe,
    /* U+0054 "T" (8x12) */
    0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    /* U+0055 "U" (8x12) */
    0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc3, 0x43, 0x66, 0x3c,
    /* U+0056 "V" (9x12) */
    0xc1, 0xe0, 0x98, 0xcc, 0x66, 0x31, 0x10, 0xd8, 0x6c, 0x1c, 0x0e, 0x07,
    0x01, 0x00,
    /* U+0057 "W" (13x12) */
    0xc3, 0x1a, 0x18, 0xd1, 0xc6, 0xce, 0x36, 0x59, 0x32, 0xd8, 0xb2, 0xc7,
    0x96, 0x38, 0xe1, 0xc7, 0x06, 0x18, 0x30, 0xc0,
    /* U+0058 "X" (8x12) */
    0x43, 0x63, 0x26, 0x36, 0x1c, 0x18, 0x1c, 0x3c, 0x36, 0x62, 0x63, 0xc1,
    /* U+0059 "Y" (8x12) */
    0xc3, 0x43, 0x66, 0x26, 0x3c, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    /* U+005A "Z" (8x12) */
    0x7f, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60, 0xff,
    /* U+005B "[" (3x14) */
    0xfb, 0x6d, 0xb6, 0xdb, 0x6d, 0xc0,
    /* U+005C "" (5x12) */
    0xc2, 0x10, 0xc2, 0x10, 0xc6, 0x10, 0xc6, 0x10,
    /* U+005D "]" (4x14) */
    0xf3, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3f,
    /* U+005E "^" (6x7) */
    0x30, 0xc7, 0x92, 0x4a, 0x18, 0x40,
    /* U+005F "_" (6x1) */
    0xfc,
    /* U+0060 "`" (3x3) */
    0xd9, 0x80,
    /* U+0061 "a" (6x9) */
    0x79, 0x30, 0xc3, 0x7f, 0x38, 0xf3, 0x74,
    /* U+0062 "b" (7x12) */
    0xc1, 0x83, 0x07, 0xee, 0x78, 0xf0, 0xe1, 0xc3, 0x8f, 0x9f, 0xe0,
    /* U+0063 "c" (5x9) */
    0x3b, 0x31, 0x88, 0x63, 0x0c, 0x38,
    /* U+0064 "d" (7x12) */
    0x06, 0x0c, 0x1b, 0xbc, 0xf8, 0xe1, 0xc3, 0x87, 0x8f, 0x3b, 0xb0,
    /* U+0065 "e" (7x9) */
    0x38, 0x9b, 0x1f, 0xfc, 0x18, 0x30, 0x32, 0x3c,
    /* U+0066 "f" (6x12) */
    0x3c, 0xc6, 0x3e, 0x61, 0x86, 0x18, 0x61, 0x86, 0x18,
    /* U+0067 "g" (7x13) */
    0x3e, 0x9f, 0x1c, 0x38, 0x70, 0xf1, 0xa7, 0x7e, 0x0c, 0x1a, 0x67, 0x80,
    /* U+0068 "h" (7x12) */
    0xc1, 0x83, 0x07, 0xee, 0x78, 0xf1, 0xe3, 0xc7, 0x8f, 0x1e, 0x30,
    /* U+0069 "i" (2x12) */
    0xa3, 0xff, 0xff,
    /* U+006A "j" (4x16) */
    0x33, 0x03, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3e,
    /* U+006B "k" (7x12) */
    0xc1, 0x83, 0x06, 0x6c, 0x9b, 0x3c, 0x78, 0xd9, 0xb3, 0x36, 0x30,
    /* U+006C "l" (2x12) */
    0xff, 0xff, 0xff,
    /* U+006D "m" (11x9) */
    0xfd, 0xdd, 0xef, 0x18, 0xe3, 0x1c, 0x63, 0x8c, 0x71, 0x8e, 0x31, 0xc6,
    0x20,
    /* U+006E "n" (7x9) */
    0xfd, 0xcf, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,
    /* U+006F "o" (7x9) */
    0x38, 0x9b, 0x1c, 0x38, 0x70, 0xf1, 0xa6, 0x38,
    /* U+0070 "p" (7x13) */
    0xfd, 0xcf, 0x1e, 0x1c, 0x38, 0x71, 0xf3, 0xfd, 0x83, 0x06, 0x0c, 0x00,
    /* U+0071 "q" (7x13) */
    0x3e, 0x9f, 0x1c, 0x38, 0x70, 0xf1, 0xe7, 0x7e, 0x0c, 0x18, 0x30, 0x60,
    /* U+0072 "r" (5x9) */
    0x9f, 0x31, 0x8c, 0x63, 0x18, 0xc0,
    /* U+0073 "s" (6x9) */
    0x7b, 0x28, 0x38, 0x70, 0x60, 0xe6, 0xf0,
    /* U+0074 "t" (5x11) */
    0x23, 0x3e, 0xc6, 0x31, 0x8c, 0x63, 0x0e,
    /* U+0075 "u" (7x9) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe7, 0x7e,
    /* U+0076 "v" (7x9) */
    0xc2, 0x8d, 0x1b, 0x22, 0x45, 0x8e, 0x0c, 0x18,
    /* U+0077 "w" (11x9) */
    0xc6, 0x79, 0xcd, 0x39, 0xb7, 0xb6, 0xb4, 0xf7, 0x8e, 0x71, 0xce, 0x31,
    0x80,
    /* U+0078 "x" (6x9) */
    0x8f, 0x35, 0x9c, 0x31, 0xe5, 0xb3, 0x84,
    /* U+0079 "y" (7x13) */
    0xc3, 0x8d, 0x1b, 0x26, 0xc5, 0x8e, 0x1c, 0x18, 0x20, 0x41, 0x8e, 0x00,
    /* U+007A "z" (5x9) */
    0xf8, 0xc4, 0x62, 0x33, 0x18, 0xf8,
    /* U+007B "{" (5x14) */
    0x19, 0x8c, 0x63, 0x1b, 0x84, 0x31, 0x8c, 0x63, 0x0c,
    /* U+007C "|" (2x16) */
    0xff, 0xff, 0xff, 0xff,
    /* U+007D "}" (5x14) */
    0xe3, 0x8c, 0x63, 0x18, 0x66, 0x31, 0x8c, 0x63, 0x70,
    /* U+007E "~" (6x2) */
    0xe2, 0xf0,
    /* U+00B0 "" (5x5) */
    0x76, 0xe7, 0x3f, 0x00,
    /* U+00B1 "" (6x10) */
    0x30, 0xc3, 0x3f, 0x30, 0xc3, 0x0c, 0x03, 0xf0,
    /* U+00B2 "" (5x7) */
    0x70, 0xc6, 0x22, 0x33, 0xe0,
    /* U+00B3 "" (4x7) */
    0xe3, 0x3e, 0x33, 0xe0,
    /* U+00B5 "" (7x13) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe7, 0xff, 0x83, 0x06, 0x0c, 0x00,
    /* U+00B7 "" (2x2) */
    0xf0,
    /* U+00D7 "" (6x7) */
    0x87, 0x27, 0x8c, 0x7b, 0x38, 0x40,
    /* U+00F7 "" (6x8) */
    0x30, 0xc0, 0x00, 0xfc, 0x03, 0x0c,
    /* U+0394 "" (8x12) */
    0x18, 0x1c, 0x1c, 0x34, 0x34, 0x26, 0x26, 0x62, 0x63, 0x43, 0xc3, 0xff,
    /* U+03A9 "" (11x12) */
    0x1f, 0x06, 0x31, 0x83, 0x30, 0x66, 0x0c, 0xc1, 0x98, 0x33, 0x06, 0x60,
    0xc6, 0x30, 0xc6, 0x7d, 0xf0,
    /* U+03BC "" (7x13) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe7, 0xff, 0x83, 0x06, 0x0c, 0x00,
    /* U+2013 "" (7x1) */
    0xfe,
    /* U+2014 "" (14x1) */
    0xff, 0xfc,
    /* U+2018 "" (3x4) */
    0x6f, 0x60,
    /* U+2019 "" (3x4) */
    0x6b, 0x60,
    /* U+201C "" (5x4) */
    0x4a, 0x57, 0xb0,
    /* U+201D "" (5x4) */
    0x7a, 0xf7, 0xa0,
    /* U+2022 "" (4x4) */
    0x6f, 0xf6,
    /* U+2026 "" (9x2) */
    0xcd, 0xe4, 0x40,
    /* U+2030 "" (15x12) */
    0x61, 0x01, 0x44, 0x02, 0x48, 0x04, 0xb0, 0x09, 0x40, 0x16, 0xb1, 0xba,
    0x95, 0x05, 0x29, 0x12, 0x52, 0x24, 0xa4, 0x8b, 0x51, 0x0c, 0x60,
    /* U+2190 "" (11x5) */
    0x20, 0x08, 0x03, 0xff, 0xa0, 0x02, 0x00,
    /* U+2191 "" (5x11) */
    0x23, 0xbe, 0x42, 0x10, 0x84, 0x21, 0x08,
    /* U+2192 "" (11x5) */
    0x00, 0x80, 0x1b, 0xff, 0x80, 0x60, 0x08,
    /* U+2193 "" (5x11) */
    0x21, 0x08, 0x42, 0x10, 0x84, 0xfb, 0x88,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 58, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 61, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 96, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 5, .adv_w = 145, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 19, .adv_w = 132, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 29, .adv_w = 190, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 44, .adv_w = 167, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 58, .adv_w = 54, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 59, .adv_w = 70, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 65, .adv_w = 70, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 71, .adv_w = 123, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 77, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 84, .adv_w = 61, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 85, .adv_w = 72, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 86, .adv_w = 61, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 87, .adv_w = 86, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 95, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 128, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 112, .adv_w = 132, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 123, .adv_w = 132, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 132, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 155, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 164, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 184, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 193, .adv_w = 61, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 196, .adv_w = 63, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 199, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 205, .adv_w = 128, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 209, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 215, .adv_w = 101, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 223, .adv_w = 201, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 241, .adv_w = 147, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 255, .adv_w = 147, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 266, .adv_w = 145, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 277, .adv_w = 164, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 289, .adv_w = 125, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 298, .adv_w = 119, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 163, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 319, .adv_w = 168, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 331, .adv_w = 80, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 65, .box_w = 4, .box_h = 15, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 347, .adv_w = 142, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 359, .adv_w = 120, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 368, .adv_w = 207, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 385, .adv_w = 174, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 399, .adv_w = 176, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 413, .adv_w = 139, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 424, .adv_w = 178, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 442, .adv_w = 142, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 454, .adv_w = 126, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 463, .adv_w = 126, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 475, .adv_w = 166, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 487, .adv_w = 138, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 501, .adv_w = 212, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 521, .adv_w = 137, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 533, .adv_w = 131, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 545, .adv_w = 129, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 557, .adv_w = 74, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 563, .adv_w = 86, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 571, .adv_w = 74, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 578, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 584, .adv_w = 97, .box_w = 6, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 585, .adv_w = 67, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 587, .adv_w = 129, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 594, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 605, .adv_w = 111, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 611, .adv_w = 139, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 622, .adv_w = 130, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 630, .adv_w = 81, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 639, .adv_w = 141, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 651, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 662, .adv_w = 61, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 665, .adv_w = 61, .box_w = 4, .box_h = 16, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 673, .adv_w = 123, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 684, .adv_w = 61, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 687, .adv_w = 213, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 700, .adv_w = 142, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 708, .adv_w = 136, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 716, .adv_w = 141, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 728, .adv_w = 141, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 740, .adv_w = 95, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 746, .adv_w = 111, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 753, .adv_w = 86, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 760, .adv_w = 142, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 768, .adv_w = 117, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 776, .adv_w = 180, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 789, .adv_w = 122, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 796, .adv_w = 119, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 808, .adv_w = 106, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 814, .adv_w = 89, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 823, .adv_w = 123, .box_w = 2, .box_h = 16, .ofs_x = 3, .ofs_y = -4},
    {.bitmap_index = 827, .adv_w = 89, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 836, .adv_w = 128, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 838, .adv_w = 99, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 842, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 850, .adv_w = 82, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 855, .adv_w = 82, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 859, .adv_w = 142, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 871, .adv_w = 60, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 872, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 878, .adv_w = 128, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 884, .adv_w = 134, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 896, .adv_w = 175, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 913, .adv_w = 140, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 925, .adv_w = 112, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 926, .adv_w = 224, .box_w = 14, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 928, .adv_w = 43, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 930, .adv_w = 43, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 932, .adv_w = 87, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 935, .adv_w = 84, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 938, .adv_w = 88, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 940, .adv_w = 177, .box_w = 9, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 943, .adv_w = 267, .box_w = 15, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 966, .adv_w = 203, .box_w = 11, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 973, .adv_w = 112, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 980, .adv_w = 203, .box_w = 11, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 987, .adv_w = 112, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0}
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

const lv_font_t humid1_font_plex_cond_normal_16 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 23,
    .base_line = 5,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 12,
    .x_height = 9,
#endif
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = -2,
    .underline_thickness = 1,
#if LV_VERSION_CHECK(9, 3, 0) || (LVGL_VERSION_MAJOR == 9 && LVGL_VERSION_MINOR >= 3) || LVGL_VERSION_MAJOR > 9
    .static_bitmap = 0,
#endif
    .dsc = &font_dsc,
#if LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_font_plex_sans_normal_16,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_COND_NORMAL_16 */
