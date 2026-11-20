/*******************************************************************************
 * Font: humid1_font_plex_cond_bold_14 (cond bold)
 * Size: 14 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_font_plex_sans_bold_14 (LVGL >= 9.6.0 Ready)
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

#ifndef HUMID1_FONT_PLEX_COND_BOLD_14
#define HUMID1_FONT_PLEX_COND_BOLD_14 1
#endif

#if HUMID1_FONT_PLEX_COND_BOLD_14

extern const lv_font_t humid1_font_plex_sans_bold_14;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x10) */
    0xff, 0xfc, 0xf0,
    /* U+0022 "" (5x4) */
    0xfe, 0xb5, 0xa0,
    /* U+0023 "#" (8x10) */
    0x16, 0x14, 0x7e, 0x7f, 0x3c, 0xfe, 0xfe, 0x28, 0x68, 0x68,
    /* U+0024 "$" (5x12) */
    0x23, 0xff, 0x4e, 0x78, 0xe7, 0x3f, 0xdc, 0x40,
    /* U+0025 "%" (11x10) */
    0x71, 0x0e, 0x23, 0x48, 0x69, 0x47, 0x7c, 0xea, 0xc2, 0x58, 0x4b, 0x11,
    0xc2, 0x38,
    /* U+0026 "&" (8x10) */
    0x70, 0xf8, 0xd8, 0x70, 0xf3, 0xf2, 0xde, 0xce, 0xfe, 0x7f,
    /* U+0027 "'" (2x4) */
    0xff,
    /* U+0028 "(" (3x12) */
    0x7b, 0x69, 0x24, 0xdb, 0x30,
    /* U+0029 ")" (3x12) */
    0x9b, 0x36, 0xdb, 0x6b, 0x40,
    /* U+002A "" (5x7) */
    0x21, 0x3f, 0xf7, 0x6c, 0x40,
    /* U+002B "+" (6x7) */
    0x20, 0x82, 0x3f, 0xf8, 0x82, 0x00,
    /* U+002C "," (3x4) */
    0x6f, 0xe0,
    /* U+002D "-" (4x2) */
    0x7f,
    /* U+002E "." (2x2) */
    0xf0,
    /* U+002F "/" (5x10) */
    0x18, 0xc6, 0x63, 0x19, 0x8c, 0x66, 0x00,
    /* U+0030 "0" (7x10) */
    0x38, 0xf9, 0xb3, 0x7e, 0xfd, 0xdb, 0xb6, 0x7c, 0x70,
    /* U+0031 "1" (5x10) */
    0x3b, 0xff, 0xf3, 0x9c, 0xe7, 0x39, 0xc0,
    /* U+0032 "2" (6x10) */
    0x7b, 0xf0, 0xc7, 0x1c, 0xe7, 0x18, 0xff, 0xf0,
    /* U+0033 "3" (6x10) */
    0xfb, 0xf1, 0xde, 0x78, 0x70, 0xc7, 0xff, 0xe0,
    /* U+0034 "4" (7x10) */
    0x0c, 0x38, 0x71, 0xe6, 0xcd, 0xbf, 0xff, 0x0c, 0x18,
    /* U+0035 "5" (7x10) */
    0xf9, 0xf3, 0x07, 0x8f, 0x81, 0x83, 0x0f, 0xfd, 0xf0,
    /* U+0036 "6" (7x10) */
    0x3c, 0xf9, 0x83, 0x47, 0xdd, 0xd9, 0xb3, 0x7c, 0x70,
    /* U+0037 "7" (7x10) */
    0xfe, 0xfc, 0x30, 0x61, 0xc3, 0x06, 0x1c, 0x30, 0xe0,
    /* U+0038 "8" (6x10) */
    0x7b, 0xfc, 0xfb, 0x7b, 0xec, 0xe3, 0xfc, 0xe0,
    /* U+0039 "9" (6x10) */
    0x7b, 0xfc, 0xf3, 0xcd, 0xf3, 0xc7, 0xff, 0xe0,
    /* U+003A ":" (2x8) */
    0xf0, 0x0f,
    /* U+003B ";" (4x10) */
    0x67, 0x60, 0x00, 0x66, 0x6e,
    /* U+003C "<" (6x6) */
    0x1d, 0xee, 0x38, 0x78, 0x70,
    /* U+003D "=" (6x5) */
    0xfb, 0xf0, 0x3e, 0xfc,
    /* U+003E ">" (7x6) */
    0xe0, 0xf0, 0x70, 0xf7, 0x9c, 0x00,
    /* U+003F "?" (6x10) */
    0x7b, 0xf0, 0xc7, 0x38, 0xc0, 0x0c, 0x30, 0xc0,
    /* U+0040 "@" (9x11) */
    0x1e, 0x3f, 0x9f, 0xff, 0xfb, 0x6d, 0x36, 0xdb, 0xff, 0xd9, 0x3f, 0x0f,
    0x80,
    /* U+0041 "A" (9x10) */
    0x1c, 0x0f, 0x0f, 0x86, 0xc3, 0x73, 0xb9, 0xfc, 0xfe, 0xe3, 0xf1, 0xc0,
    /* U+0042 "B" (7x10) */
    0xf9, 0xfb, 0x3e, 0x6f, 0xdf, 0xb3, 0xe7, 0xfd, 0xf0,
    /* U+0043 "C" (7x10) */
    0x3e, 0xff, 0x87, 0x0c, 0x18, 0x38, 0x70, 0x7e, 0x7c,
    /* U+0044 "D" (7x10) */
    0xf9, 0xfb, 0x1e, 0x3c, 0x78, 0xf1, 0xe7, 0xfd, 0xf0,
    /* U+0045 "E" (5x10) */
    0xff, 0xf1, 0x8f, 0xff, 0x18, 0xff, 0xc0,
    /* U+0046 "F" (5x10) */
    0xff, 0xf1, 0x8f, 0xff, 0x18, 0xc6, 0x00,
    /* U+0047 "G" (8x10) */
    0x0f, 0x3e, 0x60, 0x60, 0xee, 0xee, 0xe6, 0xe6, 0x7e, 0x3e,
    /* U+0048 "H" (8x10) */
    0xc7, 0xc7, 0xc7, 0xc7, 0xff, 0xff, 0xc7, 0xc7, 0xc7, 0xc7,
    /* U+0049 "I" (5x10) */
    0xfb, 0xcc, 0x63, 0x18, 0xc6, 0x77, 0xc0,
    /* U+004A "J" (5x13) */
    0x39, 0xce, 0x73, 0x9c, 0xe7, 0x39, 0xcf, 0xee, 0x00,
    /* U+004B "K" (7x10) */
    0xc7, 0x9f, 0x77, 0xcf, 0x9f, 0x3f, 0x66, 0xcf, 0x8c,
    /* U+004C "L" (6x10) */
    0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0x30, 0xff, 0xf0,
    /* U+004D "M" (10x10) */
    0xe1, 0xfc, 0x7f, 0x3f, 0xcf, 0xf3, 0xff, 0xff, 0xef, 0x7b, 0xce, 0xf3,
    0x30,
    /* U+004E "N" (8x10) */
    0xe3, 0xf3, 0xf3, 0xfb, 0xfb, 0xdf, 0xcf, 0xcf, 0xc7, 0xc7,
    /* U+004F "O" (8x10) */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e, 0x3c,
    /* U+0050 "P" (7x10) */
    0xf9, 0xfb, 0x3e, 0x7f, 0xdf, 0x38, 0x70, 0xe1, 0xc0,
    /* U+0051 "Q" (9x12) */
    0x3c, 0x3f, 0xb8, 0xd8, 0x7c, 0x3e, 0x1f, 0x0f, 0xc6, 0x7f, 0x1f, 0x01,
    0x80, 0xe0,
    /* U+0052 "R" (7x10) */
    0xf9, 0xfb, 0x36, 0x6f, 0xdf, 0x37, 0x66, 0xcf, 0x8c,
    /* U+0053 "S" (6x10) */
    0x7b, 0xfc, 0x38, 0xf1, 0xf1, 0xc7, 0xff, 0xc0,
    /* U+0054 "T" (7x10) */
    0xfe, 0xfc, 0x60, 0xc1, 0x83, 0x06, 0x0c, 0x18, 0x30,
    /* U+0055 "U" (8x10) */
    0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc6, 0xe6, 0x7e, 0x3c,
    /* U+0056 "V" (9x10) */
    0xe3, 0xf1, 0x99, 0xce, 0xe7, 0x61, 0xf0, 0xf8, 0x78, 0x1c, 0x0e, 0x00,
    /* U+0057 "W" (13x10) */
    0xe7, 0x3f, 0x39, 0x99, 0xcc, 0xde, 0xe6, 0xff, 0x3f, 0xf0, 0xf7, 0x87,
    0xbc, 0x39, 0xe1, 0xce, 0x00,
    /* U+0058 "X" (9x10) */
    0xe3, 0x3b, 0x8d, 0x87, 0xc1, 0xc0, 0xe0, 0xf8, 0xec, 0x67, 0x71, 0xc0,
    /* U+0059 "Y" (8x10) */
    0xe7, 0x66, 0x66, 0x3c, 0x3c, 0x1c, 0x18, 0x18, 0x18, 0x18,
    /* U+005A "Z" (7x10) */
    0xfe, 0xfc, 0x30, 0xe1, 0x87, 0x0c, 0x38, 0xff, 0xfc,
    /* U+005B "[" (3x13) */
    0xff, 0x6d, 0xb6, 0xdb, 0x7e,
    /* U+005C "" (5x10) */
    0xc3, 0x18, 0xc3, 0x18, 0xc3, 0x18, 0xc0,
    /* U+005D "]" (3x13) */
    0xfd, 0xb6, 0xdb, 0x6d, 0xfe,
    /* U+005E "^" (6x6) */
    0x21, 0xc5, 0x36, 0xca, 0x30,
    /* U+005F "_" (5x1) */
    0xf8,
    /* U+0060 "`" (4x3) */
    0xce, 0x70,
    /* U+0061 "a" (6x8) */
    0x7b, 0xf0, 0xdf, 0xff, 0x3f, 0xfb,
    /* U+0062 "b" (7x11) */
    0xe1, 0xc3, 0x87, 0xef, 0xdd, 0xf3, 0xe7, 0xef, 0xfb, 0xf0,
    /* U+0063 "c" (5x8) */
    0x7f, 0xf1, 0x8c, 0x63, 0xef,
    /* U+0064 "d" (6x11) */
    0x0c, 0x30, 0xdf, 0xff, 0x3c, 0xf3, 0xcf, 0xf6, 0xc0,
    /* U+0065 "e" (6x8) */
    0x7b, 0xfc, 0xff, 0xff, 0x0f, 0xdf,
    /* U+0066 "f" (6x11) */
    0x3d, 0xf7, 0x1e, 0xf9, 0xc7, 0x1c, 0x71, 0xc7, 0x00,
    /* U+0067 "g" (7x11) */
    0x7d, 0xfb, 0x3e, 0x7c, 0xf9, 0xff, 0xbe, 0x0d, 0xfb, 0xe0,
    /* U+0068 "h" (7x11) */
    0xe1, 0xc3, 0x87, 0xef, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xb8,
    /* U+0069 "i" (2x11) */
    0xf3, 0xff, 0xfc,
    /* U+006A "j" (5x14) */
    0x31, 0xc0, 0x73, 0x9c, 0xe7, 0x39, 0xce, 0x7f, 0x78,
    /* U+006B "k" (7x11) */
    0xe1, 0xc3, 0x87, 0x7f, 0xdf, 0xbe, 0x7c, 0xfd, 0xdf, 0xb8,
    /* U+006C "l" (3x11) */
    0xff, 0xff, 0xff, 0xff, 0x80,
    /* U+006D "m" (11x8) */
    0xff, 0xdf, 0xff, 0xbb, 0xf7, 0x7e, 0xef, 0xdd, 0xfb, 0xbf, 0x77,
    /* U+006E "n" (7x8) */
    0xfd, 0xff, 0xbf, 0x7e, 0xfd, 0xfb, 0xf7,
    /* U+006F "o" (6x8) */
    0x7b, 0xfc, 0xf3, 0xcf, 0x3f, 0xde,
    /* U+0070 "p" (7x11) */
    0xfd, 0xfb, 0xbe, 0x7c, 0xfd, 0xff, 0x7e, 0xe1, 0xc3, 0x80,
    /* U+0071 "q" (7x11) */
    0x7f, 0xff, 0x3e, 0x7c, 0xf9, 0xff, 0xbf, 0x0e, 0x1c, 0x38,
    /* U+0072 "r" (5x8) */
    0xdf, 0xb9, 0x8c, 0x63, 0x18,
    /* U+0073 "s" (5x8) */
    0x7f, 0xf1, 0xe7, 0x8f, 0xfe,
    /* U+0074 "t" (5x9) */
    0x23, 0xfe, 0xc6, 0x31, 0x8f, 0x38,
    /* U+0075 "u" (7x8) */
    0xef, 0xdf, 0xbf, 0x7e, 0xfd, 0xff, 0xbf,
    /* U+0076 "v" (8x8) */
    0xe7, 0xe6, 0x6e, 0x7e, 0x7c, 0x3c, 0x3c, 0x38,
    /* U+0077 "w" (11x8) */
    0xee, 0x7d, 0xdd, 0xbf, 0xbf, 0xe7, 0xfc, 0xf7, 0x8e, 0xf1, 0xdc,
    /* U+0078 "x" (7x8) */
    0xe6, 0xdd, 0xf1, 0xe3, 0xcf, 0x9b, 0xf3,
    /* U+0079 "y" (7x11) */
    0xe6, 0xcd, 0xbb, 0xe3, 0xc7, 0x8e, 0x0c, 0x38, 0xe1, 0x80,
    /* U+007A "z" (6x8) */
    0xfd, 0xf1, 0x8e, 0x31, 0xcf, 0xff,
    /* U+007B "{" (5x13) */
    0x39, 0xcc, 0x63, 0x7b, 0xce, 0x31, 0x8c, 0x71, 0x80,
    /* U+007C "|" (1x14) */
    0xff, 0xfc,
    /* U+007D "}" (4x13) */
    0xce, 0x66, 0x67, 0x76, 0x66, 0xee, 0x80,
    /* U+007E "~" (6x3) */
    0xc3, 0xf3, 0x80,
    /* U+00B0 "" (5x5) */
    0x33, 0xf2, 0xf3, 0x00,
    /* U+00B1 "" (6x9) */
    0x20, 0x8f, 0xbf, 0x20, 0x82, 0x3e, 0xfc,
    /* U+00B2 "" (5x6) */
    0x73, 0xc6, 0x66, 0x7c,
    /* U+00B3 "" (4x6) */
    0xef, 0xe3, 0x3e,
    /* U+00B5 "" (7x11) */
    0xcf, 0x9f, 0x3e, 0x7c, 0xf9, 0xff, 0xff, 0xc1, 0x83, 0x00,
    /* U+00B7 "" (2x2) */
    0xf0,
    /* U+00D7 "" (5x6) */
    0x8e, 0xdc, 0xed, 0xc4,
    /* U+00F7 "" (6x7) */
    0x20, 0x8f, 0xbf, 0x00, 0x82, 0x00,
    /* U+0394 "" (8x10) */
    0x1c, 0x1c, 0x3e, 0x36, 0x36, 0x66, 0x63, 0x63, 0xff, 0xff,
    /* U+03A9 "" (10x10) */
    0x1e, 0x0f, 0xc7, 0x39, 0x86, 0x61, 0x98, 0x66, 0x18, 0xcc, 0x77, 0xbd,
    0xf0,
    /* U+03BC "" (7x11) */
    0xcf, 0x9f, 0x3e, 0x7c, 0xf9, 0xff, 0xff, 0xc1, 0x83, 0x00,
    /* U+2013 "" (6x2) */
    0x7b, 0xf0,
    /* U+2014 "" (11x2) */
    0xff, 0xff, 0xfc,
    /* U+2018 "" (3x4) */
    0x6f, 0xf0,
    /* U+2019 "" (3x3) */
    0x7f, 0x00,
    /* U+201C "" (6x3) */
    0x6d, 0x3d, 0x80,
    /* U+201D "" (6x3) */
    0x7f, 0xfd, 0x80,
    /* U+2022 "" (4x5) */
    0xef, 0xff, 0xe0,
    /* U+2026 "" (9x2) */
    0xdd, 0xec, 0xc0,
    /* U+2030 "" (15x10) */
    0x71, 0x00, 0xe2, 0x03, 0x48, 0x06, 0x94, 0x27, 0x7c, 0xee, 0xaf, 0x42,
    0x5e, 0x84, 0xbd, 0x11, 0xde, 0x23, 0x98,
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
    {.bitmap_index = 0, .adv_w = 58, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 101, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 6, .adv_w = 127, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 16, .adv_w = 118, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 24, .adv_w = 183, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 38, .adv_w = 153, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 48, .adv_w = 58, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 49, .adv_w = 71, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 54, .adv_w = 71, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 59, .adv_w = 106, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 64, .adv_w = 112, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 70, .adv_w = 58, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 72, .adv_w = 63, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 73, .adv_w = 58, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 74, .adv_w = 86, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 81, .adv_w = 112, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 90, .adv_w = 112, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 97, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 113, .adv_w = 118, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 112, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 131, .adv_w = 112, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 140, .adv_w = 112, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 149, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 157, .adv_w = 112, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 58, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 62, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 172, .adv_w = 112, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 177, .adv_w = 112, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 181, .adv_w = 112, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 187, .adv_w = 100, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 195, .adv_w = 176, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 208, .adv_w = 142, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 135, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 229, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 238, .adv_w = 146, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 247, .adv_w = 110, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 254, .adv_w = 112, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 261, .adv_w = 141, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 271, .adv_w = 153, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 281, .adv_w = 83, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 288, .adv_w = 71, .box_w = 5, .box_h = 13, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 297, .adv_w = 136, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 116, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 314, .adv_w = 191, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 166, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 337, .adv_w = 158, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 347, .adv_w = 129, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 356, .adv_w = 162, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 370, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 379, .adv_w = 114, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 387, .adv_w = 116, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 396, .adv_w = 151, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 406, .adv_w = 134, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 418, .adv_w = 196, .box_w = 13, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 435, .adv_w = 141, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 447, .adv_w = 130, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 457, .adv_w = 114, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 466, .adv_w = 65, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 471, .adv_w = 86, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 478, .adv_w = 65, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 483, .adv_w = 112, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 488, .adv_w = 76, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 489, .adv_w = 77, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 491, .adv_w = 124, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 497, .adv_w = 130, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 507, .adv_w = 107, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 512, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 521, .adv_w = 122, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 527, .adv_w = 82, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 536, .adv_w = 130, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 546, .adv_w = 135, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 556, .adv_w = 66, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 559, .adv_w = 66, .box_w = 5, .box_h = 14, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 568, .adv_w = 128, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 578, .adv_w = 66, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 583, .adv_w = 199, .box_w = 11, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 594, .adv_w = 135, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 601, .adv_w = 123, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 607, .adv_w = 130, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 617, .adv_w = 130, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 627, .adv_w = 94, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 632, .adv_w = 104, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 637, .adv_w = 95, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 643, .adv_w = 135, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 650, .adv_w = 118, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 658, .adv_w = 174, .box_w = 11, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 669, .adv_w = 120, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 676, .adv_w = 119, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 686, .adv_w = 98, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 692, .adv_w = 84, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 701, .adv_w = 108, .box_w = 1, .box_h = 14, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 703, .adv_w = 84, .box_w = 4, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 710, .adv_w = 112, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 713, .adv_w = 90, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 717, .adv_w = 112, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 724, .adv_w = 81, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 728, .adv_w = 81, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 731, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 741, .adv_w = 56, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 742, .adv_w = 112, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 746, .adv_w = 112, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 752, .adv_w = 135, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 762, .adv_w = 155, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 775, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 785, .adv_w = 98, .box_w = 6, .box_h = 2, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 787, .adv_w = 196, .box_w = 11, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 790, .adv_w = 49, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 792, .adv_w = 49, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 794, .adv_w = 99, .box_w = 6, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 797, .adv_w = 93, .box_w = 6, .box_h = 3, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 800, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 803, .adv_w = 168, .box_w = 9, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 806, .adv_w = 257, .box_w = 15, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 825, .adv_w = 178, .box_w = 9, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 829, .adv_w = 98, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 830, .adv_w = 178, .box_w = 9, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 834, .adv_w = 98, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 0}
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

const lv_font_t humid1_font_plex_cond_bold_14 = {
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
    .fallback = &humid1_font_plex_sans_bold_14,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_COND_BOLD_14 */
