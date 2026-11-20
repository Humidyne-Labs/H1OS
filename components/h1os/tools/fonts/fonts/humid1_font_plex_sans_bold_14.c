/*******************************************************************************
 * Font: humid1_font_plex_sans_bold_14 (sans bold)
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

#ifndef HUMID1_FONT_PLEX_SANS_BOLD_14
#define HUMID1_FONT_PLEX_SANS_BOLD_14 1
#endif

#if HUMID1_FONT_PLEX_SANS_BOLD_14

extern const lv_font_t humid1_font_plex_sans_normal_14;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (3x10) */
    0xff, 0xe4, 0x82, 0xfc,
    /* U+0022 "" (6x5) */
    0xdf, 0x7d, 0xf7, 0xdc,
    /* U+0023 "#" (9x10) */
    0x33, 0x19, 0x1f, 0xec, 0xc2, 0x61, 0x31, 0x99, 0xfe, 0x44, 0x22, 0x00,
    /* U+0024 "$" (7x12) */
    0x30, 0xfb, 0xf6, 0x8f, 0x1f, 0x0f, 0x8f, 0x17, 0xf9, 0xe1, 0x80,
    /* U+0025 "%" (12x10) */
    0x70, 0xcf, 0x98, 0xd9, 0x8d, 0xb0, 0xff, 0xe7, 0xff, 0x0d, 0xb1, 0x9b,
    0x39, 0xf3, 0x0e,
    /* U+0026 "&" (9x10) */
    0x38, 0x3e, 0x3b, 0x0f, 0x87, 0xbf, 0xdf, 0x7d, 0x9e, 0xff, 0x3d, 0xc0,
    /* U+0027 "'" (2x5) */
    0xff, 0xc0,
    /* U+0028 "(" (5x13) */
    0x3b, 0x98, 0xce, 0x73, 0x9c, 0xe3, 0x18, 0xe3, 0x80,
    /* U+0029 ")" (5x13) */
    0xe3, 0x1c, 0x63, 0x1c, 0xe7, 0x31, 0x9c, 0xce, 0x00,
    /* U+002A "" (8x7) */
    0x18, 0x18, 0xff, 0xfe, 0x38, 0x7c, 0x66,
    /* U+002B "+" (6x7) */
    0x10, 0xc3, 0x3f, 0xfc, 0xc3, 0x00,
    /* U+002C "," (3x5) */
    0x5f, 0xac,
    /* U+002D "-" (5x2) */
    0xff, 0xc0,
    /* U+002E "." (3x3) */
    0x5f, 0x00,
    /* U+002F "/" (6x12) */
    0x0c, 0x31, 0xc6, 0x18, 0xc3, 0x0c, 0x61, 0x86, 0x30,
    /* U+0030 "0" (8x10) */
    0x3c, 0x7e, 0x67, 0xe7, 0xe7, 0xe7, 0xe7, 0x67, 0x7e, 0x3c,
    /* U+0031 "1" (7x10) */
    0x78, 0xf3, 0x64, 0xc1, 0x83, 0x06, 0x0c, 0xff, 0xfc,
    /* U+0032 "2" (7x10) */
    0x79, 0xfb, 0x38, 0x70, 0xc3, 0x1c, 0x70, 0xff, 0xfc,
    /* U+0033 "3" (8x10) */
    0x3c, 0x7e, 0x47, 0x06, 0x1e, 0x1e, 0x07, 0x47, 0xfe, 0x3c,
    /* U+0034 "4" (8x10) */
    0x0e, 0x1e, 0x1e, 0x3e, 0x6e, 0x6e, 0xff, 0xff, 0x0e, 0x0e,
    /* U+0035 "5" (7x10) */
    0xfd, 0xfb, 0x06, 0xcf, 0xf9, 0xc3, 0xe7, 0xfc, 0xf0,
    /* U+0036 "6" (8x10) */
    0x1e, 0x38, 0x70, 0x7c, 0x7f, 0xe7, 0xe7, 0x67, 0x7f, 0x3c,
    /* U+0037 "7" (7x10) */
    0xff, 0xff, 0x3e, 0x61, 0xc3, 0x86, 0x1c, 0x30, 0xe0,
    /* U+0038 "8" (8x10) */
    0x3c, 0x7e, 0x67, 0x67, 0x3e, 0x7e, 0x67, 0xe7, 0x7f, 0x3e,
    /* U+0039 "9" (8x10) */
    0x3c, 0x7e, 0xe7, 0xe7, 0xe7, 0x7f, 0x36, 0x0e, 0x1c, 0x38,
    /* U+003A ":" (3x8) */
    0x5f, 0x80, 0xbf,
    /* U+003B ";" (3x10) */
    0x5f, 0x80, 0xbf, 0x58,
    /* U+003C "<" (6x9) */
    0x04, 0x33, 0xde, 0xf1, 0xe3, 0xc3, 0x04,
    /* U+003D "=" (6x6) */
    0xff, 0xf0, 0x00, 0xff, 0xf0,
    /* U+003E ">" (5x7) */
    0xc7, 0x1c, 0x77, 0x73, 0x00,
    /* U+003F "?" (6x10) */
    0x73, 0xe9, 0xc7, 0x79, 0x80, 0x08, 0x71, 0x80,
    /* U+0040 "@" (11x12) */
    0x1f, 0x06, 0x31, 0x01, 0x67, 0xb9, 0xb7, 0x26, 0x64, 0xdc, 0xda, 0xcd,
    0xc8, 0x00, 0xc0, 0x0f, 0x80,
    /* U+0041 "A" (9x10) */
    0x1e, 0x0f, 0x07, 0x86, 0xe3, 0x31, 0x99, 0xfe, 0xff, 0x61, 0xf0, 0xc0,
    /* U+0042 "B" (8x10) */
    0xfe, 0xfe, 0xe7, 0xe7, 0xfe, 0xfe, 0xe7, 0xe7, 0xff, 0xfe,
    /* U+0043 "C" (8x10) */
    0x3c, 0x7e, 0xe6, 0xc0, 0xc0, 0xc0, 0xc0, 0xe7, 0x7e, 0x3c,
    /* U+0044 "D" (8x10) */
    0xfc, 0xfe, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xfe, 0xfc,
    /* U+0045 "E" (7x10) */
    0xff, 0xff, 0x87, 0x0f, 0xdf, 0xb8, 0x70, 0xff, 0xfc,
    /* U+0046 "F" (7x10) */
    0xff, 0xff, 0x87, 0x0f, 0xdf, 0xb8, 0x70, 0xe1, 0xc0,
    /* U+0047 "G" (8x10) */
    0x3c, 0x7f, 0xe7, 0xc0, 0xcf, 0xcf, 0xc3, 0xe7, 0x7f, 0x3b,
    /* U+0048 "H" (8x10) */
    0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0xff, 0xe7, 0xe7, 0xe7, 0xe7,
    /* U+0049 "I" (5x10) */
    0xff, 0xd8, 0xc6, 0x31, 0x8c, 0xff, 0xc0,
    /* U+004A "J" (7x10) */
    0x3e, 0x7c, 0x18, 0x30, 0x60, 0xc1, 0xf7, 0x7e, 0x78,
    /* U+004B "K" (9x10) */
    0xe7, 0x73, 0xbb, 0x9f, 0x8f, 0xc7, 0xf3, 0xb9, 0xce, 0xe7, 0x71, 0xc0,
    /* U+004C "L" (6x10) */
    0xe3, 0x8e, 0x38, 0xe3, 0x8e, 0x38, 0xff, 0xf0,
    /* U+004D "M" (10x10) */
    0xe1, 0xf8, 0xff, 0x3f, 0xdf, 0xff, 0xf7, 0x7c, 0xdf, 0x27, 0xc1, 0xf0,
    0x70,
    /* U+004E "N" (8x10) */
    0xe3, 0xf3, 0xf3, 0xfb, 0xfb, 0xdf, 0xcf, 0xcf, 0xc7, 0xc7,
    /* U+004F "O" (8x10) */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e, 0x3c,
    /* U+0050 "P" (8x10) */
    0xfe, 0xff, 0xe7, 0xe7, 0xff, 0xfe, 0xe0, 0xe0, 0xe0, 0xe0,
    /* U+0051 "Q" (8x13) */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e, 0x3c, 0x18, 0x1e,
    0x0e,
    /* U+0052 "R" (8x10) */
    0xfe, 0xff, 0xe7, 0xe7, 0xe7, 0xff, 0xfe, 0xee, 0xee, 0xe7,
    /* U+0053 "S" (7x10) */
    0x7d, 0xff, 0x97, 0x0f, 0xcf, 0xc1, 0xe7, 0xfe, 0xf8,
    /* U+0054 "T" (8x10) */
    0xff, 0xff, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c,
    /* U+0055 "U" (8x10) */
    0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xe7, 0x7e, 0x3c,
    /* U+0056 "V" (9x10) */
    0xe1, 0xb1, 0xd8, 0xce, 0x63, 0x71, 0xb0, 0xd8, 0x7c, 0x1e, 0x0e, 0x00,
    /* U+0057 "W" (13x10) */
    0xc7, 0x3e, 0x79, 0xb3, 0xcd, 0xde, 0x6e, 0xf7, 0x36, 0xf1, 0xe7, 0x8f,
    0x3c, 0x79, 0xe1, 0xcf, 0x00,
    /* U+0058 "X" (9x10) */
    0x73, 0xb9, 0xcf, 0xc7, 0xc1, 0xe0, 0xf0, 0xfc, 0x6e, 0x73, 0xf1, 0xc0,
    /* U+0059 "Y" (9x10) */
    0xe3, 0xb9, 0xdd, 0xc7, 0xe3, 0xe0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x00,
    /* U+005A "Z" (7x10) */
    0xff, 0xfc, 0x38, 0xe3, 0x8e, 0x1c, 0x70, 0xff, 0xfc,
    /* U+005B "[" (3x13) */
    0xff, 0xff, 0xff, 0xff, 0xfe,
    /* U+005C "" (6x12) */
    0xc3, 0x0c, 0x18, 0x61, 0xc3, 0x0c, 0x18, 0x61, 0x83,
    /* U+005D "]" (3x13) */
    0xff, 0xff, 0xff, 0xff, 0xfe,
    /* U+005E "^" (7x6) */
    0x38, 0xf1, 0xf7, 0x6c, 0xf8, 0x80,
    /* U+005F "_" (7x2) */
    0xfe, 0xfc,
    /* U+0060 "`" (3x3) */
    0xcd, 0x80,
    /* U+0061 "a" (8x7) */
    0x3c, 0x7e, 0x06, 0x7e, 0x6e, 0xff, 0x77,
    /* U+0062 "b" (7x10) */
    0xc1, 0x83, 0x06, 0xef, 0xf9, 0xf1, 0xe7, 0xff, 0xb8,
    /* U+0063 "c" (7x7) */
    0x3c, 0xfd, 0x97, 0x06, 0x4f, 0xcf, 0x00,
    /* U+0064 "d" (7x10) */
    0x0e, 0x1c, 0x3b, 0xff, 0xf9, 0xf3, 0xe7, 0xfe, 0xfc,
    /* U+0065 "e" (8x7) */
    0x3c, 0x7e, 0x66, 0xff, 0x60, 0x7e, 0x3c,
    /* U+0066 "f" (5x10) */
    0x3b, 0xdd, 0xff, 0xb9, 0xce, 0x73, 0x80,
    /* U+0067 "g" (8x12) */
    0x02, 0x06, 0x3c, 0x7e, 0x66, 0x6e, 0x7c, 0x7e, 0x7f, 0xc3, 0xe7, 0x7e,
    /* U+0068 "h" (7x10) */
    0xc1, 0x83, 0x06, 0xef, 0xf9, 0xf3, 0xe7, 0xcf, 0x9c,
    /* U+0069 "i" (3x10) */
    0xdc, 0x6d, 0xb6, 0xd8,
    /* U+006A "j" (4x13) */
    0x67, 0x06, 0x66, 0x66, 0x66, 0x6e, 0xe0,
    /* U+006B "k" (7x10) */
    0xc1, 0x83, 0x06, 0x7d, 0xdf, 0x3e, 0x7e, 0xcf, 0x9c,
    /* U+006C "l" (3x10) */
    0xdb, 0x6d, 0xb6, 0xec,
    /* U+006D "m" (11x7) */
    0xdd, 0xdf, 0xff, 0x3b, 0xe7, 0x7c, 0xef, 0x9d, 0xf3, 0xb8,
    /* U+006E "n" (7x7) */
    0xdd, 0xff, 0x3e, 0x7c, 0xf9, 0xf3, 0x80,
    /* U+006F "o" (7x7) */
    0x3c, 0xfd, 0x9f, 0x36, 0x6f, 0xcf, 0x00,
    /* U+0070 "p" (7x10) */
    0xdd, 0xff, 0x3e, 0x3c, 0xff, 0xf7, 0x60, 0xc1, 0x80,
    /* U+0071 "q" (7x10) */
    0x7f, 0xff, 0x3e, 0x7c, 0xff, 0xdf, 0x87, 0x0e, 0x1c,
    /* U+0072 "r" (5x7) */
    0xff, 0xf9, 0x8c, 0x63, 0x00,
    /* U+0073 "s" (6x7) */
    0x7b, 0xec, 0x3e, 0x1f, 0xff, 0x80,
    /* U+0074 "t" (5x9) */
    0x73, 0xbf, 0xf7, 0x39, 0xcf, 0x38,
    /* U+0075 "u" (7x7) */
    0xcf, 0x9f, 0x3e, 0x7c, 0xff, 0xdb, 0x80,
    /* U+0076 "v" (8x7) */
    0xe7, 0x66, 0x66, 0x7e, 0x3c, 0x3c, 0x3c,
    /* U+0077 "w" (12x7) */
    0xe6, 0x36, 0x77, 0x6f, 0x66, 0xf6, 0x3d, 0xe3, 0x9c, 0x39, 0xc0,
    /* U+0078 "x" (7x7) */
    0xcf, 0xd9, 0xe3, 0xc7, 0x9f, 0xb3, 0x80,
    /* U+0079 "y" (8x10) */
    0xe7, 0xe6, 0x66, 0x6e, 0x7c, 0x3c, 0x3c, 0x38, 0x78, 0x70,
    /* U+007A "z" (6x7) */
    0xff, 0xf3, 0x9c, 0xe3, 0xff, 0xc0,
    /* U+007B "{" (5x13) */
    0x39, 0x8c, 0x63, 0x3b, 0x9c, 0x31, 0x8c, 0x63, 0x80,
    /* U+007C "|" (2x13) */
    0xff, 0xff, 0xff, 0xc0,
    /* U+007D "}" (4x13) */
    0xce, 0xee, 0xe6, 0x77, 0xee, 0xee, 0xc0,
    /* U+007E "~" (6x3) */
    0xe3, 0xf1, 0xc0,
    /* U+00B0 "" (5x5) */
    0x76, 0xe7, 0xb7, 0x00,
    /* U+00B1 "" (6x9) */
    0x30, 0xcf, 0xff, 0x30, 0xc0, 0x3f, 0xfc,
    /* U+00B2 "" (5x5) */
    0x73, 0xcc, 0xcf, 0x80,
    /* U+00B3 "" (3x5) */
    0xed, 0xde,
    /* U+00B5 "" (7x10) */
    0xcf, 0x9f, 0x3e, 0x7c, 0xff, 0xff, 0xe0, 0xc1, 0x80,
    /* U+00B7 "" (3x3) */
    0xfd, 0x00,
    /* U+00D7 "" (6x6) */
    0x47, 0xb7, 0x8e, 0x7f, 0x30,
    /* U+00F7 "" (7x8) */
    0x30, 0x70, 0x07, 0xff, 0xc2, 0x0e, 0x18,
    /* U+0394 "" (8x10) */
    0x3c, 0x3c, 0x7c, 0x7e, 0x6e, 0x66, 0xe7, 0xe7, 0xff, 0xff,
    /* U+03A9 "" (9x10) */
    0x3c, 0x3f, 0x39, 0xd8, 0x6c, 0x36, 0x1b, 0x9c, 0xec, 0xf7, 0xfb, 0xc0,
    /* U+03BC "" (7x10) */
    0xcf, 0x9f, 0x3e, 0x7c, 0xff, 0xfd, 0xe0, 0xc1, 0x80,
    /* U+2013 "" (7x2) */
    0xff, 0xfc,
    /* U+2014 "" (10x2) */
    0x7f, 0xff, 0xf0,
    /* U+2018 "" (2x4) */
    0x7f,
    /* U+2019 "" (3x4) */
    0xdd, 0x40,
    /* U+201C "" (6x4) */
    0x4f, 0x2d, 0xf3,
    /* U+201D "" (6x4) */
    0xcf, 0xf4, 0xf6,
    /* U+2022 "" (4x4) */
    0xff, 0xff,
    /* U+2026 "" (11x3) */
    0x44, 0x7d, 0xdf, 0x39, 0x80,
    /* U+2030 "" (18x10) */
    0x70, 0xc0, 0x3e, 0x60, 0x0d, 0x98, 0x03, 0x6c, 0x00, 0xff, 0xe3, 0x9f,
    0xfd, 0xb0, 0xdb, 0x6c, 0x66, 0xdb, 0x39, 0xf6, 0xcc, 0x38, 0xe0,
    /* U+2190 "" (10x6) */
    0x30, 0x1c, 0x0f, 0xff, 0xfe, 0x70, 0x0c, 0x00,
    /* U+2191 "" (7x10) */
    0x10, 0x71, 0xf7, 0xf3, 0x87, 0x0e, 0x1c, 0x38, 0x70,
    /* U+2192 "" (9x6) */
    0x06, 0x03, 0xbf, 0xff, 0xf0, 0x70, 0x30,
    /* U+2193 "" (7x10) */
    0x38, 0x70, 0xe1, 0xc3, 0x87, 0x3f, 0xbe, 0x38, 0x20,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 53, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 75, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 118, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 8, .adv_w = 134, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 20, .adv_w = 135, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 31, .adv_w = 223, .box_w = 12, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 46, .adv_w = 164, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 58, .adv_w = 63, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 60, .adv_w = 76, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 69, .adv_w = 76, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 78, .adv_w = 150, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 85, .adv_w = 134, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 91, .adv_w = 73, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 93, .adv_w = 91, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 95, .adv_w = 73, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 97, .adv_w = 111, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 106, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 116, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 144, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 154, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 163, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 173, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 182, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 192, .adv_w = 134, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 202, .adv_w = 78, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 78, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 209, .adv_w = 134, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 134, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 221, .adv_w = 134, .box_w = 5, .box_h = 7, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 226, .adv_w = 114, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 234, .adv_w = 203, .box_w = 11, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 251, .adv_w = 158, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 263, .adv_w = 151, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 273, .adv_w = 149, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 283, .adv_w = 159, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 293, .adv_w = 138, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 302, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 311, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 321, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 331, .adv_w = 100, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 338, .adv_w = 130, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 347, .adv_w = 162, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 359, .adv_w = 122, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 367, .adv_w = 184, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 380, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 390, .adv_w = 161, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 400, .adv_w = 152, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 410, .adv_w = 161, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 423, .adv_w = 154, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 433, .adv_w = 144, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 442, .adv_w = 132, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 452, .adv_w = 157, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 462, .adv_w = 150, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 474, .adv_w = 226, .box_w = 13, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 491, .adv_w = 157, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 503, .adv_w = 151, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 515, .adv_w = 139, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 524, .adv_w = 77, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 529, .adv_w = 111, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 538, .adv_w = 77, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 543, .adv_w = 134, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 549, .adv_w = 124, .box_w = 7, .box_h = 2, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 551, .adv_w = 134, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 553, .adv_w = 131, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 560, .adv_w = 139, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 569, .adv_w = 117, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 576, .adv_w = 139, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 585, .adv_w = 127, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 592, .adv_w = 85, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 599, .adv_w = 126, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 611, .adv_w = 136, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 620, .adv_w = 68, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 624, .adv_w = 68, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 631, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 640, .adv_w = 71, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 644, .adv_w = 202, .box_w = 11, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 654, .adv_w = 136, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 661, .adv_w = 127, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 668, .adv_w = 139, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 677, .adv_w = 139, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 686, .adv_w = 94, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 691, .adv_w = 115, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 697, .adv_w = 89, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 703, .adv_w = 136, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 710, .adv_w = 125, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 717, .adv_w = 196, .box_w = 12, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 728, .adv_w = 131, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 735, .adv_w = 123, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 745, .adv_w = 121, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 751, .adv_w = 86, .box_w = 5, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 760, .adv_w = 99, .box_w = 2, .box_h = 13, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 764, .adv_w = 86, .box_w = 4, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 771, .adv_w = 134, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 774, .adv_w = 106, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 778, .adv_w = 134, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 785, .adv_w = 78, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 789, .adv_w = 77, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 791, .adv_w = 138, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 800, .adv_w = 83, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 802, .adv_w = 134, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 807, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 814, .adv_w = 157, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 824, .adv_w = 160, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 836, .adv_w = 142, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 845, .adv_w = 132, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 847, .adv_w = 175, .box_w = 10, .box_h = 2, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 850, .adv_w = 70, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 851, .adv_w = 70, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 853, .adv_w = 126, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 856, .adv_w = 126, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 859, .adv_w = 100, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 861, .adv_w = 210, .box_w = 11, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 866, .adv_w = 317, .box_w = 18, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 889, .adv_w = 210, .box_w = 10, .box_h = 6, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 897, .adv_w = 210, .box_w = 7, .box_h = 10, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 906, .adv_w = 210, .box_w = 9, .box_h = 6, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 913, .adv_w = 210, .box_w = 7, .box_h = 10, .ofs_x = 3, .ofs_y = 0}
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

const lv_font_t humid1_font_plex_sans_bold_14 = {
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
    .fallback = &humid1_font_plex_sans_normal_14,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_SANS_BOLD_14 */
