/*******************************************************************************
 * Font: humid1_font_plex_sans_bold_12 (IBM Plex Sans Bold)
 * Size: 12 px @ 188 DPI (SSD1681 1-bit E-Paper Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Raster Mode: autohint-mono (FT_LOAD_TARGET_MONO + Dropout Control)
 * License: SIL Open Font License 1.1 (IBM Corp.) / Font Awesome Free License
 ******************************************************************************/

#include "lvgl.h"

#ifndef HUMID1_FONT_PLEX_SANS_BOLD_12
#define HUMID1_FONT_PLEX_SANS_BOLD_12 1
#endif

#if HUMID1_FONT_PLEX_SANS_BOLD_12

extern const lv_font_t humid1_font_plex_sans_normal_12;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x9) */
    0xff, 0xd0, 0xc0,
    /* U+0022 "" (4x4) */
    0xff, 0xff,
    /* U+0023 "#" (7x9) */
    0x26, 0x4b, 0xfb, 0x24, 0x49, 0xbf, 0xa4, 0xc8,
    /* U+0024 "$" (6x11) */
    0x31, 0xef, 0xbc, 0xf1, 0xf3, 0xcd, 0xff, 0xe3, 0x00,
    /* U+0025 "%" (11x9) */
    0x71, 0x9b, 0x23, 0x68, 0x6f, 0x07, 0x5c, 0x1e, 0xc2, 0xd8, 0x9b, 0x31,
    0xc0,
    /* U+0026 "&" (8x9) */
    0x38, 0x68, 0x68, 0x78, 0x77, 0xde, 0xcc, 0xcc, 0x7e,
    /* U+0027 "'" (2x4) */
    0xff,
    /* U+0028 "(" (4x11) */
    0x36, 0x4c, 0xcc, 0xcc, 0x46, 0x30,
    /* U+0029 ")" (4x11) */
    0xc6, 0x23, 0x33, 0x33, 0x26, 0xc0,
    /* U+002A "" (6x7) */
    0x30, 0xcf, 0xde, 0x7b, 0x34, 0x80,
    /* U+002B "+" (6x6) */
    0x30, 0xcf, 0xcc, 0x30, 0xc0,
    /* U+002C "," (2x4) */
    0xf6,
    /* U+002D "-" (4x1) */
    0xf0,
    /* U+002E "." (2x1) */
    0xc0,
    /* U+002F "/" (5x12) */
    0x18, 0xc4, 0x23, 0x10, 0x8c, 0x42, 0x31, 0x80,
    /* U+0030 "0" (6x9) */
    0x79, 0x2c, 0xf3, 0xcf, 0x3c, 0xd2, 0x78,
    /* U+0031 "1" (7x9) */
    0x38, 0xf3, 0x62, 0xc1, 0x83, 0x06, 0x0c, 0x7e,
    /* U+0032 "2" (6x9) */
    0x7b, 0x30, 0xc3, 0x1c, 0xe7, 0x38, 0xfc,
    /* U+0033 "3" (6x9) */
    0x7b, 0x30, 0xc3, 0x30, 0x30, 0xf3, 0x78,
    /* U+0034 "4" (7x9) */
    0x1c, 0x38, 0xb1, 0x64, 0xc9, 0xbf, 0x86, 0x0c,
    /* U+0035 "5" (6x9) */
    0xfb, 0x0c, 0x3e, 0xcc, 0x30, 0xf3, 0xf8,
    /* U+0036 "6" (6x9) */
    0x31, 0x86, 0x3e, 0xcf, 0x3c, 0xf3, 0x78,
    /* U+0037 "7" (6x9) */
    0xff, 0x3c, 0xc2, 0x18, 0x61, 0x0c, 0x30,
    /* U+0038 "8" (6x9) */
    0x7b, 0x3c, 0xf3, 0x33, 0x3c, 0xf3, 0x78,
    /* U+0039 "9" (6x9) */
    0x7b, 0x3c, 0xf3, 0xcd, 0xf1, 0x86, 0x70,
    /* U+003A ":" (2x7) */
    0xc0, 0x0c,
    /* U+003B ";" (2x7) */
    0xc3, 0xd8,
    /* U+003C "<" (5x8) */
    0x08, 0xdd, 0xcc, 0x38, 0xe1,
    /* U+003D "=" (6x4) */
    0xfc, 0x00, 0x3f,
    /* U+003E ">" (5x8) */
    0x86, 0x18, 0x73, 0xb3, 0x10,
    /* U+003F "?" (6x9) */
    0x7b, 0x30, 0xc3, 0x30, 0x00, 0x00, 0x30,
    /* U+0040 "@" (9x11) */
    0x3e, 0x31, 0x90, 0x73, 0xdb, 0x6d, 0xb6, 0xdb, 0x3e, 0x40, 0x30, 0x07,
    0x80,
    /* U+0041 "A" (8x9) */
    0x18, 0x1c, 0x3c, 0x34, 0x26, 0x7e, 0x62, 0x43, 0xc3,
    /* U+0042 "B" (7x9) */
    0xf9, 0x9b, 0x36, 0x6f, 0xd8, 0xf1, 0xe3, 0xfc,
    /* U+0043 "C" (7x9) */
    0x3c, 0xcf, 0x06, 0x0c, 0x18, 0x31, 0x33, 0x3c,
    /* U+0044 "D" (7x9) */
    0xf9, 0x9b, 0x1e, 0x3c, 0x78, 0xf1, 0xe6, 0xf8,
    /* U+0045 "E" (6x9) */
    0xff, 0x0c, 0x30, 0xfb, 0x0c, 0x30, 0xfc,
    /* U+0046 "F" (6x9) */
    0xff, 0x0c, 0x30, 0xfb, 0x0c, 0x30, 0xc0,
    /* U+0047 "G" (7x9) */
    0x3c, 0xdf, 0x06, 0x0c, 0xf8, 0xf1, 0xb7, 0x7e,
    /* U+0048 "H" (7x9) */
    0xc7, 0x8f, 0x1e, 0x3f, 0xf8, 0xf1, 0xe3, 0xc6,
    /* U+0049 "I" (4x9) */
    0xf6, 0x66, 0x66, 0x66, 0xf0,
    /* U+004A "J" (6x9) */
    0x7c, 0x30, 0xc3, 0x0c, 0x30, 0xf3, 0x78,
    /* U+004B "K" (7x9) */
    0xc7, 0x9b, 0x66, 0xcf, 0x9f, 0x33, 0x67, 0xc6,
    /* U+004C "L" (5x9) */
    0xc6, 0x31, 0x8c, 0x63, 0x18, 0xf8,
    /* U+004D "M" (8x9) */
    0xc3, 0xe7, 0xe7, 0xff, 0xdb, 0xdb, 0xd3, 0xc3, 0xc3,
    /* U+004E "N" (7x9) */
    0xc7, 0xcf, 0x9f, 0xbd, 0x7b, 0xf3, 0xe7, 0xc6,
    /* U+004F "O" (7x9) */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xf1, 0xb6, 0x38,
    /* U+0050 "P" (7x9) */
    0xfd, 0x8f, 0x1e, 0x3f, 0xd8, 0x30, 0x60, 0xc0,
    /* U+0051 "Q" (7x12) */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0x7c, 0x70, 0x40, 0xc0,
    /* U+0052 "R" (7x9) */
    0xfd, 0x8f, 0x1e, 0x3f, 0xd9, 0xb3, 0x66, 0xc6,
    /* U+0053 "S" (6x9) */
    0x7b, 0x2c, 0x3e, 0xfc, 0xf0, 0xf3, 0xf8,
    /* U+0054 "T" (6x9) */
    0xfc, 0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0x30,
    /* U+0055 "U" (7x9) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0x7c,
    /* U+0056 "V" (7x9) */
    0xc2, 0x8d, 0x9b, 0x32, 0x47, 0x8f, 0x1c, 0x18,
    /* U+0057 "W" (11x9) */
    0xc6, 0x68, 0xcd, 0xb9, 0xb7, 0xb6, 0xb4, 0x52, 0x8e, 0x71, 0xce, 0x31,
    0xc0,
    /* U+0058 "X" (8x9) */
    0x66, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0xc7,
    /* U+0059 "Y" (8x9) */
    0xc3, 0x66, 0x76, 0x3c, 0x3c, 0x18, 0x18, 0x18, 0x18,
    /* U+005A "Z" (6x9) */
    0xfc, 0x31, 0x8e, 0x31, 0x86, 0x30, 0xfc,
    /* U+005B "[" (3x11) */
    0xfb, 0x6d, 0xb6, 0xdb, 0x80,
    /* U+005C "" (4x12) */
    0x88, 0xc4, 0x46, 0x62, 0x33, 0x11,
    /* U+005D "]" (3x11) */
    0xed, 0xb6, 0xdb, 0x6f, 0x80,
    /* U+005E "^" (6x5) */
    0x31, 0xc5, 0xb6, 0x8c,
    /* U+005F "_" (6x1) */
    0xfc,
    /* U+0060 "`" (2x2) */
    0xd0,
    /* U+0061 "a" (6x7) */
    0x79, 0x30, 0xdf, 0xcf, 0x37, 0xc0,
    /* U+0062 "b" (6x10) */
    0xc3, 0x0c, 0x3e, 0xcf, 0x3c, 0xf3, 0xcf, 0xe0,
    /* U+0063 "c" (6x7) */
    0x7b, 0x2c, 0x30, 0xc3, 0x37, 0x80,
    /* U+0064 "d" (6x10) */
    0x0c, 0x30, 0xdf, 0xcf, 0x3c, 0xf3, 0xcd, 0xf0,
    /* U+0065 "e" (6x7) */
    0x7b, 0x3c, 0xff, 0xc3, 0x27, 0x80,
    /* U+0066 "f" (4x10) */
    0x76, 0x6f, 0x66, 0x66, 0x66,
    /* U+0067 "g" (7x11) */
    0x06, 0x79, 0x9b, 0x36, 0x67, 0x98, 0x3f, 0x47, 0x8d, 0xf0,
    /* U+0068 "h" (6x10) */
    0xc3, 0x0c, 0x3e, 0xcf, 0x3c, 0xf3, 0xcf, 0x30,
    /* U+0069 "i" (2x10) */
    0xc3, 0xff, 0xf0,
    /* U+006A "j" (3x13) */
    0x60, 0x36, 0xdb, 0x6d, 0xbe,
    /* U+006B "k" (6x10) */
    0xc3, 0x0c, 0x33, 0xdb, 0xcf, 0x36, 0xdf, 0x30,
    /* U+006C "l" (3x10) */
    0xdb, 0x6d, 0xb6, 0xdc,
    /* U+006D "m" (10x7) */
    0xff, 0xb3, 0x3c, 0xcf, 0x33, 0xcc, 0xf3, 0x3c, 0xcc,
    /* U+006E "n" (6x7) */
    0xfb, 0x3c, 0xf3, 0xcf, 0x3c, 0xc0,
    /* U+006F "o" (6x7) */
    0x7b, 0x3c, 0xf3, 0xcf, 0x37, 0x80,
    /* U+0070 "p" (6x10) */
    0xfb, 0x3c, 0xf3, 0xcf, 0x3f, 0xb0, 0xc3, 0x00,
    /* U+0071 "q" (6x10) */
    0x7f, 0x3c, 0xf3, 0xcf, 0x37, 0xc3, 0x0c, 0x30,
    /* U+0072 "r" (4x7) */
    0xfc, 0xcc, 0xcc, 0xc0,
    /* U+0073 "s" (5x7) */
    0x7e, 0x39, 0xf3, 0xcf, 0xc0,
    /* U+0074 "t" (4x9) */
    0x66, 0xf6, 0x66, 0x66, 0x30,
    /* U+0075 "u" (6x7) */
    0xcf, 0x3c, 0xf3, 0xcf, 0x37, 0xc0,
    /* U+0076 "v" (6x7) */
    0xc5, 0x36, 0xda, 0x68, 0xe3, 0x00,
    /* U+0077 "w" (10x7) */
    0xcc, 0xd3, 0x34, 0xe9, 0xfe, 0x73, 0x8c, 0xe3, 0x30,
    /* U+0078 "x" (6x7) */
    0x6d, 0xb3, 0x8c, 0x39, 0xbc, 0xc0,
    /* U+0079 "y" (6x10) */
    0xc5, 0x36, 0xda, 0x68, 0xe3, 0x8c, 0x31, 0x80,
    /* U+007A "z" (5x7) */
    0xf8, 0xcc, 0xe6, 0x63, 0xe0,
    /* U+007B "{" (4x11) */
    0x76, 0x66, 0x68, 0x66, 0x66, 0x70,
    /* U+007C "|" (2x11) */
    0xff, 0xff, 0xfc,
    /* U+007D "}" (4x11) */
    0xe6, 0x66, 0x61, 0x66, 0x66, 0xe0,
    /* U+007E "~" (5x2) */
    0xe1, 0xc0,
    /* U+00B0 "" (4x5) */
    0x69, 0x99, 0x60,
    /* U+00B1 "" (6x8) */
    0x30, 0xcf, 0xcc, 0x30, 0xc0, 0x3f,
    /* U+00B2 "" (3x4) */
    0xe5, 0x70,
    /* U+00B3 "" (3x4) */
    0xe8, 0xf0,
    /* U+00B5 "" (6x10) */
    0xcf, 0x3c, 0xf3, 0xcf, 0x3f, 0xf0, 0xc3, 0x00,
    /* U+00B7 "" (2x1) */
    0xc0,
    /* U+00D7 "" (5x6) */
    0x0e, 0xdc, 0xed, 0xc4,
    /* U+00F7 "" (6x7) */
    0x30, 0x00, 0x3f, 0x00, 0x03, 0x00,
    /* U+0394 "" (7x9) */
    0x38, 0x70, 0xa3, 0x66, 0xcd, 0xb1, 0xe3, 0xfe,
    /* U+03A9 "" (7x9) */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xfb, 0x36, 0xee,
    /* U+03B1 "" (7x7) */
    0x77, 0xbb, 0x36, 0x6c, 0xdb, 0x9d, 0x80,
    /* U+03B2 "" (6x13) */
    0x7b, 0x3c, 0xf3, 0xcf, 0x4c, 0xf3, 0xcf, 0xec, 0x30, 0xc0,
    /* U+03B3 "" (6x10) */
    0xcd, 0x36, 0x9e, 0x78, 0xe3, 0x0c, 0x30, 0xc0,
    /* U+03B4 "" (6x10) */
    0xfb, 0x87, 0x1e, 0xdf, 0x3c, 0xf3, 0xc9, 0xe0,
    /* U+03B5 "" (5x7) */
    0x7e, 0x70, 0xec, 0x61, 0xe0,
    /* U+03B8 "" (6x10) */
    0x79, 0x2c, 0xf3, 0xcf, 0xfc, 0xf3, 0x49, 0xe0,
    /* U+03BB "" (7x10) */
    0x60, 0x60, 0xc1, 0x83, 0x87, 0x1a, 0x34, 0x4d, 0x8c,
    /* U+03BC "" (6x10) */
    0xcf, 0x3c, 0xf3, 0xcf, 0x3f, 0xf0, 0xc3, 0x00,
    /* U+03C0 "" (7x7) */
    0xfe, 0xd9, 0xb3, 0x66, 0xcd, 0x99, 0x80,
    /* U+03C3 "" (7x7) */
    0x7f, 0x93, 0x36, 0x6c, 0xd9, 0x1e, 0x00,
    /* U+03C4 "" (5x7) */
    0xf9, 0x8c, 0x63, 0x18, 0xe0,
    /* U+03C6 "" (8x10) */
    0x4e, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0x7e, 0x18, 0x18, 0x18,
    /* U+03C9 "" (8x7) */
    0x42, 0xc3, 0xdb, 0xdb, 0xdb, 0xdb, 0x7e,
    /* U+2013 "" (6x1) */
    0xfc,
    /* U+2014 "" (8x1) */
    0xff,
    /* U+2018 "" (2x4) */
    0x6f,
    /* U+2019 "" (2x4) */
    0xf6,
    /* U+201C "" (5x4) */
    0x4c, 0xb7, 0xb0,
    /* U+201D "" (5x4) */
    0xde, 0xd3, 0x20,
    /* U+2022 "" (4x4) */
    0xff, 0xff,
    /* U+2026 "" (10x1) */
    0xcc, 0xc0,
    /* U+2030 "" (16x9) */
    0x71, 0x80, 0xd9, 0x00, 0xda, 0x00, 0xde, 0x00, 0x75, 0xce, 0x0f, 0x7b,
    0x0b, 0x7b, 0x13, 0x7b, 0x31, 0xce,
    /* U+2190 "" (9x5) */
    0x30, 0x30, 0x3f, 0xec, 0x03, 0x00,
    /* U+2191 "" (5x9) */
    0x21, 0x1d, 0xf2, 0x10, 0x84, 0x20,
    /* U+2192 "" (9x5) */
    0x06, 0x01, 0xbf, 0xe0, 0x60, 0x60,
    /* U+2193 "" (5x8) */
    0x21, 0x08, 0x42, 0x7d, 0xc4,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 45, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 61, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 95, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 5, .adv_w = 121, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 13, .adv_w = 115, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 22, .adv_w = 187, .box_w = 11, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 35, .adv_w = 138, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 44, .adv_w = 51, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 45, .adv_w = 65, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 51, .adv_w = 65, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 57, .adv_w = 115, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 63, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 68, .adv_w = 60, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 69, .adv_w = 77, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 70, .adv_w = 60, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 71, .adv_w = 88, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 79, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 86, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 101, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 108, .adv_w = 115, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 116, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 123, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 130, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 137, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 144, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 151, .adv_w = 63, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 153, .adv_w = 63, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 155, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 160, .adv_w = 115, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 163, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 96, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 173, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 188, .adv_w = 132, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 197, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 125, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 134, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 221, .adv_w = 117, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 112, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 235, .adv_w = 138, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 243, .adv_w = 139, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 83, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 256, .adv_w = 107, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 263, .adv_w = 134, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 271, .adv_w = 102, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 277, .adv_w = 157, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 139, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 294, .adv_w = 137, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 302, .adv_w = 126, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 310, .adv_w = 137, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 321, .adv_w = 129, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 329, .adv_w = 120, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 336, .adv_w = 112, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 343, .adv_w = 133, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 351, .adv_w = 125, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 359, .adv_w = 187, .box_w = 11, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 372, .adv_w = 129, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 381, .adv_w = 125, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 390, .adv_w = 117, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 397, .adv_w = 64, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 402, .adv_w = 88, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 408, .adv_w = 64, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 413, .adv_w = 115, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 417, .adv_w = 107, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 418, .adv_w = 115, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 419, .adv_w = 109, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 425, .adv_w = 117, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 433, .adv_w = 99, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 439, .adv_w = 117, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 447, .adv_w = 108, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 453, .adv_w = 69, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 458, .adv_w = 106, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 468, .adv_w = 114, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 476, .adv_w = 55, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 479, .adv_w = 55, .box_w = 3, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 484, .adv_w = 111, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 492, .adv_w = 58, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 496, .adv_w = 172, .box_w = 10, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 505, .adv_w = 114, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 511, .adv_w = 108, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 517, .adv_w = 117, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 525, .adv_w = 117, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 533, .adv_w = 78, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 537, .adv_w = 97, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 542, .adv_w = 74, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 547, .adv_w = 114, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 553, .adv_w = 103, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 559, .adv_w = 161, .box_w = 10, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 568, .adv_w = 108, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 574, .adv_w = 103, .box_w = 6, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 582, .adv_w = 99, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 587, .adv_w = 71, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 593, .adv_w = 77, .box_w = 2, .box_h = 11, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 596, .adv_w = 71, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 602, .adv_w = 115, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 604, .adv_w = 90, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 607, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 613, .adv_w = 67, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 615, .adv_w = 66, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 617, .adv_w = 116, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 625, .adv_w = 69, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 626, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 630, .adv_w = 115, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 636, .adv_w = 131, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 644, .adv_w = 137, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 652, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 659, .adv_w = 117, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 669, .adv_w = 104, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 677, .adv_w = 108, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 685, .adv_w = 101, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 690, .adv_w = 111, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 698, .adv_w = 103, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 707, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 715, .adv_w = 126, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 722, .adv_w = 113, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 729, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 734, .adv_w = 148, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 744, .adv_w = 148, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 751, .adv_w = 113, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 752, .adv_w = 150, .box_w = 8, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 753, .adv_w = 58, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 754, .adv_w = 58, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 755, .adv_w = 103, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 758, .adv_w = 103, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 761, .adv_w = 83, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 763, .adv_w = 172, .box_w = 10, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 765, .adv_w = 265, .box_w = 16, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 783, .adv_w = 173, .box_w = 9, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 789, .adv_w = 173, .box_w = 5, .box_h = 9, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 795, .adv_w = 173, .box_w = 9, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 801, .adv_w = 173, .box_w = 5, .box_h = 8, .ofs_x = 3, .ofs_y = 0}
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

/*-----------------
 *    KERNING
 *----------------*/

static const uint8_t kern_pair_glyph_ids[] = {
    3, 13, 3, 15, 3, 34, 3, 43, 3, 104, 3, 126, 6, 3, 6, 8,
    6, 11, 6, 121, 6, 122, 6, 123, 6, 124, 7, 53, 7, 55, 7, 56,
    7, 58, 8, 13, 8, 15, 8, 87, 8, 126, 9, 75, 11, 13, 11, 15,
    11, 87, 11, 126, 13, 3, 13, 8, 13, 11, 13, 32, 13, 36, 13, 40,
    13, 48, 13, 50, 13, 53, 13, 54, 13, 55, 13, 56, 13, 58, 13, 85,
    13, 87, 13, 88, 13, 90, 13, 98, 13, 99, 13, 108, 13, 111, 13, 114,
    13, 116, 13, 121, 13, 122, 13, 123, 13, 124, 14, 42, 14, 53, 14, 57,
    14, 58, 14, 59, 14, 89, 14, 112, 15, 3, 15, 8, 15, 11, 15, 32,
    15, 36, 15, 40, 15, 48, 15, 50, 15, 53, 15, 54, 15, 55, 15, 56,
    15, 58, 15, 85, 15, 87, 15, 88, 15, 90, 15, 98, 15, 99, 15, 108,
    15, 111, 15, 114, 15, 116, 15, 121, 15, 122, 15, 123, 15, 124, 16, 16,
    16, 34, 16, 36, 16, 40, 16, 48, 16, 50, 16, 52, 16, 66, 16, 68,
    16, 69, 16, 70, 16, 72, 16, 78, 16, 79, 16, 80, 16, 82, 16, 83,
    16, 100, 16, 104, 16, 106, 16, 107, 16, 108, 16, 109, 16, 110, 16, 111,
    16, 112, 16, 113, 16, 114, 16, 115, 16, 116, 16, 117, 16, 118, 27, 53,
    27, 58, 28, 53, 28, 58, 32, 13, 32, 15, 32, 126, 33, 43, 33, 53,
    33, 55, 33, 57, 33, 58, 34, 13, 34, 15, 34, 58, 34, 121, 34, 123,
    34, 126, 35, 64, 36, 64, 37, 14, 37, 119, 37, 120, 39, 13, 39, 15,
    39, 16, 39, 34, 39, 43, 39, 64, 39, 126, 40, 53, 40, 55, 40, 58,
    40, 98, 40, 121, 40, 122, 40, 123, 40, 124, 43, 13, 43, 15, 43, 16,
    43, 34, 43, 64, 43, 126, 44, 10, 44, 13, 44, 15, 44, 91, 44, 126,
    45, 3, 45, 8, 45, 11, 45, 13, 45, 15, 45, 16, 45, 34, 45, 58,
    45, 64, 45, 89, 45, 91, 45, 98, 45, 121, 45, 122, 45, 123, 45, 124,
    45, 126, 48, 3, 48, 8, 48, 11, 48, 13, 48, 15, 48, 16, 48, 34,
    48, 43, 48, 53, 48, 55, 48, 56, 48, 57, 48, 58, 48, 59, 48, 64,
    48, 121, 48, 122, 48, 123, 48, 124, 48, 126, 49, 13, 49, 15, 49, 16,
    49, 34, 49, 43, 49, 57, 49, 64, 49, 126, 50, 3, 50, 8, 50, 11,
    50, 13, 50, 15, 50, 16, 50, 34, 50, 43, 50, 53, 50, 55, 50, 56,
    50, 57, 50, 58, 50, 59, 50, 64, 50, 121, 50, 122, 50, 123, 50, 124,
    50, 126, 52, 7, 52, 16, 52, 33, 52, 52, 52, 53, 52, 55, 52, 56,
    52, 58, 52, 64, 52, 85, 52, 98, 52, 99, 52, 121, 52, 122, 52, 123,
    52, 124, 53, 13, 53, 14, 53, 15, 53, 16, 53, 34, 53, 43, 53, 64,
    53, 66, 53, 68, 53, 69, 53, 70, 53, 72, 53, 78, 53, 79, 53, 80,
    53, 81, 53, 82, 53, 83, 53, 84, 53, 86, 53, 91, 53, 119, 53, 120,
    53, 126, 55, 7, 55, 13, 55, 15, 55, 16, 55, 27, 55, 28, 55, 33,
    55, 34, 55, 36, 55, 40, 55, 43, 55, 48, 55, 50, 55, 52, 55, 64,
    55, 66, 55, 68, 55, 69, 55, 70, 55, 72, 55, 80, 55, 82, 55, 126,
    56, 7, 56, 13, 56, 15, 56, 16, 56, 33, 56, 34, 56, 36, 56, 40,
    56, 43, 56, 48, 56, 50, 56, 64, 56, 66, 56, 68, 56, 69, 56, 70,
    56, 72, 56, 80, 56, 82, 56, 126, 58, 7, 58, 13, 58, 14, 58, 15,
    58, 16, 58, 27, 58, 28, 58, 33, 58, 34, 58, 36, 58, 40, 58, 43,
    58, 48, 58, 50, 58, 52, 58, 64, 58, 66, 58, 68, 58, 69, 58, 70,
    58, 72, 58, 75, 58, 78, 58, 79, 58, 80, 58, 81, 58, 82, 58, 83,
    58, 84, 58, 86, 58, 87, 58, 88, 58, 89, 58, 90, 58, 91, 58, 119,
    58, 120, 58, 126, 59, 13, 59, 15, 59, 64, 59, 126, 64, 36, 64, 40,
    64, 43, 64, 48, 64, 50, 64, 52, 64, 53, 64, 54, 64, 55, 64, 56,
    64, 58, 64, 66, 64, 68, 64, 69, 64, 70, 64, 71, 64, 77, 64, 80,
    64, 82, 64, 84, 64, 85, 64, 86, 64, 87, 64, 88, 64, 106, 64, 108,
    64, 109, 64, 110, 64, 111, 64, 114, 64, 115, 64, 116, 64, 117, 64, 118,
    66, 53, 66, 55, 66, 58, 66, 121, 66, 123, 70, 53, 70, 55, 70, 58,
    70, 64, 70, 121, 70, 122, 70, 123, 70, 124, 71, 2, 71, 3, 71, 8,
    71, 10, 71, 11, 71, 32, 71, 36, 71, 40, 71, 48, 71, 50, 71, 53,
    71, 55, 71, 56, 71, 57, 71, 58, 71, 62, 71, 94, 71, 98, 71, 99,
    71, 121, 71, 122, 71, 123, 71, 124, 73, 53, 73, 58, 74, 98, 74, 99,
    75, 122, 75, 124, 76, 58, 77, 58, 77, 98, 77, 99, 77, 121, 77, 122,
    77, 123, 77, 124, 78, 53, 78, 55, 78, 56, 78, 58, 78, 121, 78, 123,
    79, 53, 79, 58, 80, 53, 80, 55, 80, 56, 80, 58, 80, 64, 80, 121,
    80, 122, 80, 123, 80, 124, 83, 13, 83, 15, 83, 34, 83, 64, 83, 99,
    83, 126, 84, 53, 84, 58, 84, 64, 85, 53, 85, 58, 87, 3, 87, 8,
    87, 11, 87, 71, 87, 98, 87, 99, 87, 121, 87, 122, 87, 123, 87, 124,
    88, 64, 89, 7, 89, 14, 89, 53, 89, 58, 89, 119, 89, 120, 90, 3,
    90, 8, 90, 11, 90, 71, 90, 99, 90, 121, 90, 122, 90, 123, 90, 124,
    92, 75, 98, 74, 98, 108, 98, 116, 99, 13, 99, 15, 99, 43, 99, 108,
    99, 114, 99, 116, 99, 126, 104, 98, 104, 121, 104, 122, 104, 123, 104, 124,
    108, 7, 108, 13, 108, 14, 108, 15, 108, 16, 108, 64, 108, 104, 108, 106,
    108, 109, 108, 110, 108, 112, 108, 115, 108, 117, 108, 118, 108, 119, 108, 120,
    108, 126, 109, 64, 109, 121, 109, 122, 109, 123, 109, 124, 111, 64, 112, 3,
    112, 8, 112, 11, 112, 13, 112, 15, 112, 16, 112, 27, 112, 28, 112, 104,
    112, 112, 112, 121, 112, 122, 112, 123, 112, 124, 112, 126, 115, 64, 119, 58,
    120, 36, 120, 40, 120, 48, 120, 50, 120, 68, 120, 69, 120, 70, 120, 80,
    120, 82, 120, 106, 120, 108, 120, 109, 120, 110, 120, 111, 120, 115, 120, 117,
    120, 118, 121, 13, 121, 15, 121, 34, 121, 36, 121, 40, 121, 48, 121, 50,
    121, 52, 121, 57, 121, 66, 121, 68, 121, 69, 121, 70, 121, 72, 121, 78,
    121, 79, 121, 80, 121, 82, 121, 83, 121, 84, 121, 89, 121, 100, 121, 104,
    121, 106, 121, 107, 121, 109, 121, 110, 121, 112, 121, 113, 121, 115, 121, 117,
    121, 118, 121, 126, 122, 13, 122, 14, 122, 15, 122, 27, 122, 28, 122, 34,
    122, 36, 122, 40, 122, 43, 122, 48, 122, 50, 122, 52, 122, 57, 122, 66,
    122, 68, 122, 69, 122, 70, 122, 72, 122, 78, 122, 79, 122, 80, 122, 81,
    122, 82, 122, 83, 122, 84, 122, 86, 122, 87, 122, 88, 122, 89, 122, 90,
    122, 91, 122, 100, 122, 104, 122, 106, 122, 107, 122, 108, 122, 109, 122, 110,
    122, 111, 122, 112, 122, 113, 122, 114, 122, 115, 122, 116, 122, 117, 122, 118,
    122, 119, 122, 120, 122, 126, 123, 53, 123, 71, 123, 85, 123, 87, 123, 88,
    123, 90, 123, 108, 124, 53, 124, 55, 124, 56, 124, 58, 126, 3, 126, 8,
    126, 11, 126, 32, 126, 36, 126, 40, 126, 48, 126, 50, 126, 53, 126, 54,
    126, 55, 126, 56, 126, 58, 126, 85, 126, 87, 126, 88, 126, 90, 126, 98,
    126, 99, 126, 108, 126, 111, 126, 114, 126, 116, 126, 121, 126, 122, 126, 123,
    126, 124, 127, 3, 127, 8, 127, 11, 127, 121, 127, 122, 127, 123, 127, 124,
};

static const int8_t kern_pair_values[] = {
    -17, -17, -10, -8, -10, -17, -12, -12, -12, -13, -13, -13, -13, -8, -7, -4,
    -12, -17, -17, 5, -17, 13, -17, -17, 5, -17, -17, -17, -17, -15, -8, -8,
    -8, -8, -13, -7, -12, -8, -13, -5, -9, -8, -9, -10, -12, -8, -5, -5,
    -13, -15, -15, -15, -15, -6, -9, -6, -10, -6, -7, -6, -17, -17, -17, -15,
    -8, -8, -8, -8, -13, -7, -12, -8, -13, -5, -9, -8, -9, -10, -12, -8,
    -5, -5, -13, -15, -15, -15, -15, -36, -9, -4, -4, -4, -4, -4, -8, -7,
    -7, -7, -5, -2, -2, -7, -7, -2, -2, -9, -7, -2, -3, -7, -12, -3,
    -9, -2, -5, -7, -5, -7, -7, -8, -10, -8, -10, -23, -23, -23, -6, -6,
    -6, -8, -8, 4, 4, -13, -13, -13, 4, -12, -8, 3, 3, 3, -19, -19,
    -16, -17, -14, -27, -19, -7, -6, -8, -4, -6, -4, -6, -4, -5, -5, -7,
    -4, -16, -5, 2, 2, 2, 2, 2, -17, -17, -17, 4, 4, 2, 3, -17,
    4, 2, 2, -15, -16, -15, -16, -15, 4, -2, -2, -2, -8, -8, -9, -6,
    -6, -5, -6, -4, -6, -10, -3, -19, -5, -5, -5, -5, -8, -19, -19, -17,
    -14, -13, -7, -29, -19, -2, -2, -2, -8, -8, -9, -6, -6, -5, -6, -4,
    -6, -10, -3, -19, -5, -5, -5, -5, -8, -2, -7, -2, -3, -4, -3, -3,
    -8, -12, -1, -2, -3, -6, -3, -6, -3, -13, -9, -13, -19, -12, -11, -15,
    -13, -12, -12, -12, -15, -9, -9, -12, -9, -12, -9, -13, -9, -10, -9, -9,
    -13, -7, -12, -12, -12, -6, -6, -6, -10, -6, -6, -11, -6, -6, -6, -15,
    -8, -7, -7, -7, -8, -7, -7, -12, -7, -8, -8, -10, -4, -5, -4, -4,
    -10, -4, -4, -10, -6, -5, -5, -5, -4, -5, -5, -8, -11, -13, -10, -13,
    -17, -10, -10, -8, -13, -10, -10, -13, -10, -10, -8, -17, -12, -12, -12, -12,
    -12, -6, -9, -9, -12, -10, -12, -9, -12, -8, -7, -8, -8, -7, -10, -10,
    -10, -13, 6, 6, 3, 6, -19, -19, -10, -19, -19, -12, -15, -13, -15, -10,
    -17, -6, -12, -10, -12, -5, -11, -12, -10, -8, -12, -7, -13, -10, -12, -13,
    -12, -6, -9, -7, -12, -18, -12, -12, -13, -6, -9, -7, -7, -12, -7, -12,
    -12, -7, -7, -7, -7, 4, 6, 6, 5, 6, 6, 3, 3, 3, 3, 5,
    7, 5, 3, 6, 3, 3, 5, 8, 6, 6, 6, 6, -11, -11, 4, 4,
    2, 2, -9, -3, -4, -4, -6, -6, -6, -6, -11, -7, -5, -11, -8, -8,
    -11, -11, -12, -7, -5, -12, -12, -9, -7, -9, -7, -15, -15, -8, -15, 10,
    -15, -12, -10, -10, -5, -4, 5, 5, 5, 1, 2, 4, 4, 5, 4, 5,
    -10, -6, -7, -7, -8, -7, -7, 4, 4, 4, 1, 4, 5, 5, 5, 5,
    2, 6, 6, 6, -12, -12, -13, 8, 6, 8, -12, -12, -13, -12, -13, -12,
    -4, -9, -1, -9, -3, -13, -6, -2, -2, -1, -6, -2, -2, -2, -1, -1,
    -9, -12, -9, -7, -9, -7, -9, -21, -21, -21, 3, 3, 2, 1, 1, 4,
    2, -23, -21, -23, -21, 3, -12, -10, 3, 3, 3, 3, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 3, 2, 2, 2, -15, -15, -13, -7, -7, -7, -7,
    -4, -3, -8, -9, -9, -9, -4, -4, -4, -9, -9, -4, -4, -3, -4, -13,
    -9, -4, -9, -7, -4, -4, -9, -9, -9, -15, -15, -15, -15, -4, -4, -15,
    -8, -8, -15, -8, -8, -7, -3, -13, -15, -15, -15, -12, -8, -8, -15, -8,
    -15, -8, -13, -7, -3, -4, -7, -5, -8, -8, -15, -15, -10, -3, -10, -12,
    -5, -6, -8, -5, -15, -6, -15, -15, -15, -15, -15, 2, 2, 3, 2, 1,
    2, 4, 2, 1, 1, 1, -17, -17, -17, -15, -8, -8, -8, -8, -13, -7,
    -12, -8, -13, -5, -9, -8, -9, -10, -12, -8, -5, -5, -13, -15, -15, -15,
    -15, -12, -12, -12, -13, -13, -13, -13,
};

static const lv_font_fmt_txt_kern_pair_t kern_pairs = {
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 696,
    .glyph_ids_size = 0
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
static lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};

/*-----------------
 *  PUBLIC FONT
 *----------------*/

#if LVGL_VERSION_MAJOR >= 8
const lv_font_t humid1_font_plex_sans_bold_12 = {
#else
lv_font_t humid1_font_plex_sans_bold_12 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 17,
    .base_line = 4,
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_font_plex_sans_normal_12,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_SANS_BOLD_12 */
