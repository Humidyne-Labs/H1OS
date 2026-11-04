/*******************************************************************************
 * Font: humid1_font_plex_cond_bold_16 (IBM Plex Cond Bold)
 * Size: 16 px @ 188 DPI (SSD1681 1-bit E-Paper Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Raster Mode: autohint-mono (FT_LOAD_TARGET_MONO + Dropout Control)
 * License: SIL Open Font License 1.1 (IBM Corp.) / Font Awesome Free License
 ******************************************************************************/

#include "lvgl.h"

#ifndef HUMID1_FONT_PLEX_COND_BOLD_16
#define HUMID1_FONT_PLEX_COND_BOLD_16 1
#endif

#if HUMID1_FONT_PLEX_COND_BOLD_16

extern const lv_font_t humid1_font_plex_sans_bold_16;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x12) */
    0xff, 0xfd, 0x3f,
    /* U+0022 "" (5x5) */
    0xde, 0xf7, 0xbd, 0x80,
    /* U+0023 "#" (9x12) */
    0x13, 0x09, 0x84, 0x8f, 0xf7, 0xf9, 0x90, 0x89, 0xfe, 0xff, 0x12, 0x09,
    0x0c, 0x80,
    /* U+0024 "$" (7x15) */
    0x18, 0xfb, 0xfe, 0xed, 0x9f, 0x1e, 0x1f, 0x1e, 0x3f, 0x7f, 0xe7, 0xc3,
    0x06, 0x00,
    /* U+0025 "%" (13x12) */
    0x70, 0xe6, 0xc6, 0x36, 0x61, 0xb3, 0x0d, 0xb0, 0x7d, 0xf9, 0xdf, 0xe1,
    0xb3, 0x0d, 0x98, 0xcc, 0xc4, 0x66, 0x61, 0xe0,
    /* U+0026 "&" (9x12) */
    0x3c, 0x3f, 0x19, 0x8c, 0xc7, 0xc3, 0xcf, 0xf7, 0x9e, 0xc7, 0x63, 0xbf,
    0xef, 0x30,
    /* U+0027 "'" (2x5) */
    0xff, 0xc0,
    /* U+0028 "(" (4x15) */
    0x36, 0x64, 0xcc, 0xcc, 0xcc, 0xcc, 0x66, 0x30,
    /* U+0029 ")" (4x15) */
    0xc6, 0x62, 0x33, 0x33, 0x33, 0x32, 0x66, 0xc0,
    /* U+002A "" (8x7) */
    0x18, 0x08, 0x6b, 0xff, 0x1c, 0x36, 0x77,
    /* U+002B "+" (7x7) */
    0x30, 0x63, 0xff, 0xf3, 0x06, 0x0c, 0x00,
    /* U+002C "," (2x5) */
    0xfd, 0x80,
    /* U+002D "-" (4x2) */
    0xff,
    /* U+002E "." (2x3) */
    0xfc,
    /* U+002F "/" (6x15) */
    0x0c, 0x30, 0xc6, 0x18, 0x61, 0x0c, 0x30, 0x86, 0x18, 0x63, 0x0c, 0x00,
    /* U+0030 "0" (7x12) */
    0x38, 0xfb, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc7, 0x8d, 0xf1, 0xc0,
    /* U+0031 "1" (7x12) */
    0x79, 0xf3, 0x66, 0xc1, 0x83, 0x06, 0x0c, 0x18, 0x33, 0xff, 0xf0,
    /* U+0032 "2" (7x12) */
    0x7d, 0xff, 0x1a, 0x30, 0x61, 0xc7, 0x1c, 0x71, 0xc3, 0xff, 0xf0,
    /* U+0033 "3" (7x12) */
    0x3d, 0xfd, 0x18, 0x30, 0x67, 0x8f, 0x03, 0x07, 0x8f, 0xf3, 0xc0,
    /* U+0034 "4" (9x12) */
    0x0e, 0x0f, 0x07, 0x82, 0xc3, 0x61, 0x31, 0x98, 0xcc, 0xff, 0xff, 0xc1,
    0x80, 0xc0,
    /* U+0035 "5" (7x12) */
    0xfd, 0xfb, 0x06, 0x0d, 0xdf, 0xf1, 0x83, 0x07, 0x8f, 0xf3, 0xc0,
    /* U+0036 "6" (8x12) */
    0x1c, 0x38, 0x70, 0x60, 0xde, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0x7e, 0x3c,
    /* U+0037 "7" (7x12) */
    0xff, 0xff, 0x1e, 0x70, 0xc1, 0x87, 0x0c, 0x18, 0x70, 0xc1, 0x80,
    /* U+0038 "8" (7x12) */
    0x7d, 0xff, 0x1e, 0x3c, 0x6f, 0x9f, 0x63, 0xc7, 0x8f, 0xfb, 0xe0,
    /* U+0039 "9" (8x12) */
    0x3c, 0x7e, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0x7b, 0x06, 0x0e, 0x1c, 0x38,
    /* U+003A ":" (2x9) */
    0xfc, 0x0f, 0xc0,
    /* U+003B ";" (2x11) */
    0xfc, 0x0f, 0xd8,
    /* U+003C "<" (6x10) */
    0x04, 0x33, 0xdc, 0xe3, 0x87, 0x0f, 0x0c, 0x10,
    /* U+003D "=" (7x6) */
    0xff, 0xfc, 0x00, 0x0f, 0xff, 0xc0,
    /* U+003E ">" (6x10) */
    0x83, 0x87, 0x0e, 0x1c, 0x73, 0x9c, 0xe2, 0x00,
    /* U+003F "?" (6x12) */
    0x7b, 0xfc, 0xd3, 0x0c, 0x33, 0x8c, 0x00, 0xc3, 0x0c,
    /* U+0040 "@" (12x14) */
    0x0f, 0x83, 0x0c, 0x60, 0x66, 0x02, 0xcd, 0xbd, 0xfb, 0xd9, 0xbd, 0x9b,
    0xd9, 0xbd, 0xfe, 0x6c, 0xe6, 0x00, 0x30, 0x00, 0xf8,
    /* U+0041 "A" (9x12) */
    0x1e, 0x0f, 0x07, 0x83, 0xc3, 0x71, 0x98, 0xcc, 0xfe, 0x7f, 0xb0, 0xd8,
    0x7c, 0x30,
    /* U+0042 "B" (8x12) */
    0xfc, 0xfe, 0xc6, 0xc6, 0xc6, 0xfc, 0xfe, 0xc3, 0xc3, 0xc3, 0xff, 0xfe,
    /* U+0043 "C" (8x12) */
    0x3c, 0x7e, 0x67, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc2, 0xe7, 0x7e, 0x3c,
    /* U+0044 "D" (8x12) */
    0xfc, 0xfe, 0xc6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc6, 0xfe, 0xfc,
    /* U+0045 "E" (7x12) */
    0xff, 0xff, 0x06, 0x0c, 0x1f, 0xbf, 0x60, 0xc1, 0x83, 0xff, 0xf0,
    /* U+0046 "F" (7x12) */
    0xff, 0xff, 0x06, 0x0c, 0x1f, 0xbf, 0x60, 0xc1, 0x83, 0x06, 0x00,
    /* U+0047 "G" (9x12) */
    0x3e, 0x3f, 0x98, 0xf8, 0x0c, 0x06, 0x3f, 0x1f, 0x83, 0xc1, 0xb1, 0xdf,
    0xe7, 0xb0,
    /* U+0048 "H" (8x12) */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xff, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    /* U+0049 "I" (5x12) */
    0xff, 0xd8, 0xc6, 0x31, 0x8c, 0x63, 0x3f, 0xf0,
    /* U+004A "J" (6x12) */
    0x7d, 0xf0, 0xc3, 0x0c, 0x30, 0xc3, 0x4f, 0x3f, 0xde,
    /* U+004B "K" (8x12) */
    0xc7, 0xc6, 0xce, 0xcc, 0xd8, 0xf8, 0xfc, 0xec, 0xce, 0xc6, 0xc7, 0xc3,
    /* U+004C "L" (6x12) */
    0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0x30, 0xc3, 0x0f, 0xff,
    /* U+004D "M" (10x12) */
    0xe1, 0xf8, 0x7f, 0x3f, 0xcf, 0xda, 0xf7, 0xbc, 0xcf, 0x33, 0xcc, 0xf0,
    0x3c, 0x0f, 0x03,
    /* U+004E "N" (8x12) */
    0xe3, 0xe3, 0xe3, 0xf3, 0xd3, 0xdb, 0xdb, 0xcb, 0xcf, 0xc7, 0xc7, 0xc7,
    /* U+004F "O" (9x12) */
    0x3e, 0x3f, 0x98, 0xd8, 0x3c, 0x1e, 0x0f, 0x07, 0x83, 0xc1, 0xb1, 0x9f,
    0xc7, 0xc0,
    /* U+0050 "P" (8x12) */
    0xfe, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xfe, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0,
    /* U+0051 "Q" (9x15) */
    0x3e, 0x3f, 0x98, 0xd8, 0x3c, 0x1e, 0x0f, 0x07, 0x83, 0xc1, 0xb1, 0x9f,
    0xc7, 0xc0, 0xc0, 0x78, 0x1c,
    /* U+0052 "R" (8x12) */
    0xfe, 0xfe, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xfe, 0xce, 0xc6, 0xc7, 0xc3,
    /* U+0053 "S" (7x12) */
    0x7d, 0xff, 0x16, 0x0e, 0x1f, 0x8f, 0x83, 0x07, 0x8f, 0xf3, 0xc0,
    /* U+0054 "T" (8x12) */
    0xff, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    /* U+0055 "U" (8x12) */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x7e, 0x3c,
    /* U+0056 "V" (9x12) */
    0xe1, 0xb0, 0xd8, 0xec, 0x67, 0x31, 0x98, 0xcc, 0x6c, 0x1e, 0x0f, 0x07,
    0x83, 0x80,
    /* U+0057 "W" (13x12) */
    0xc6, 0x3e, 0x39, 0xb3, 0xcd, 0x9e, 0x6c, 0xf3, 0x74, 0x99, 0xa6, 0x8d,
    0x3c, 0x79, 0xe3, 0xcf, 0x1e, 0x38, 0x61, 0x80,
    /* U+0058 "X" (9x12) */
    0x61, 0xb9, 0xcc, 0xc7, 0xe1, 0xe0, 0xf0, 0x78, 0x3c, 0x37, 0x19, 0x98,
    0xfc, 0x30,
    /* U+0059 "Y" (8x12) */
    0xc3, 0xe7, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    /* U+005A "Z" (7x12) */
    0xff, 0xfc, 0x38, 0x61, 0xc7, 0x0c, 0x38, 0x61, 0xc3, 0xff, 0xf0,
    /* U+005B "[" (3x16) */
    0xff, 0x6d, 0xb6, 0xdb, 0x6d, 0xbf,
    /* U+005C "" (6x15) */
    0xc3, 0x0c, 0x10, 0x61, 0x86, 0x0c, 0x30, 0xc1, 0x06, 0x18, 0x60, 0xc0,
    /* U+005D "]" (3x16) */
    0xfd, 0xb6, 0xdb, 0x6d, 0xb6, 0xff,
    /* U+005E "^" (7x6) */
    0x38, 0x71, 0xb6, 0x6c, 0x78, 0xc0,
    /* U+005F "_" (7x2) */
    0xff, 0xfc,
    /* U+0060 "`" (3x3) */
    0xcc, 0x80,
    /* U+0061 "a" (7x9) */
    0x3d, 0xfd, 0x18, 0x37, 0xff, 0xf1, 0xff, 0x76,
    /* U+0062 "b" (7x12) */
    0xc1, 0x83, 0x06, 0xef, 0xf8, 0xf1, 0xe3, 0xc7, 0x8f, 0xfe, 0xe0,
    /* U+0063 "c" (6x9) */
    0x39, 0xfc, 0xf0, 0xc3, 0x0c, 0xdf, 0x78,
    /* U+0064 "d" (7x12) */
    0x06, 0x0c, 0x1b, 0xbf, 0xf8, 0xf1, 0xe3, 0xc7, 0x8f, 0xfb, 0xb0,
    /* U+0065 "e" (7x9) */
    0x38, 0xfb, 0x1f, 0xff, 0xf8, 0x31, 0x3f, 0x3c,
    /* U+0066 "f" (5x12) */
    0x3b, 0xd9, 0xff, 0xb1, 0x8c, 0x63, 0x18, 0xc0,
    /* U+0067 "g" (8x14) */
    0x06, 0x06, 0x7c, 0xfe, 0xc6, 0xc6, 0xfe, 0x3c, 0xc0, 0xfe, 0x3f, 0xc3,
    0xff, 0x7e,
    /* U+0068 "h" (7x12) */
    0xc1, 0x83, 0x06, 0xef, 0xf8, 0xf1, 0xe3, 0xc7, 0x8f, 0x1e, 0x30,
    /* U+0069 "i" (2x12) */
    0xf3, 0xff, 0xff,
    /* U+006A "j" (3x15) */
    0x6c, 0x36, 0xdb, 0x6d, 0xb7, 0xf8,
    /* U+006B "k" (7x12) */
    0xc1, 0x83, 0x06, 0x7c, 0xdb, 0x3e, 0x7c, 0xf9, 0x9b, 0x36, 0x70,
    /* U+006C "l" (3x12) */
    0xdb, 0x6d, 0xb6, 0xdb, 0xf0,
    /* U+006D "m" (12x9) */
    0xdc, 0xed, 0xff, 0xe6, 0x3c, 0x63, 0xc6, 0x3c, 0x63, 0xc6, 0x3c, 0x63,
    0xc6, 0x30,
    /* U+006E "n" (7x9) */
    0xdd, 0xff, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,
    /* U+006F "o" (7x9) */
    0x38, 0xfb, 0x1e, 0x3c, 0x78, 0xf1, 0xbe, 0x38,
    /* U+0070 "p" (7x12) */
    0xdd, 0xff, 0x1e, 0x3c, 0x78, 0xf1, 0xff, 0xdd, 0x83, 0x06, 0x00,
    /* U+0071 "q" (7x12) */
    0x77, 0xff, 0x1e, 0x3c, 0x78, 0xf1, 0xff, 0x76, 0x0c, 0x18, 0x30,
    /* U+0072 "r" (5x9) */
    0xdf, 0xf1, 0x8c, 0x63, 0x18, 0xc0,
    /* U+0073 "s" (6x9) */
    0x7b, 0xfc, 0xb0, 0x78, 0x3c, 0xff, 0x78,
    /* U+0074 "t" (5x11) */
    0x63, 0x3f, 0xf6, 0x31, 0x8c, 0x63, 0xce,
    /* U+0075 "u" (7x9) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xff, 0x76,
    /* U+0076 "v" (8x9) */
    0xc7, 0xe6, 0x66, 0x66, 0x66, 0x3c, 0x3c, 0x3c, 0x3c,
    /* U+0077 "w" (12x9) */
    0xc6, 0x36, 0x73, 0x6f, 0x66, 0xf6, 0x6f, 0x66, 0x96, 0x29, 0x43, 0x9c,
    0x39, 0xc0,
    /* U+0078 "x" (8x9) */
    0xe7, 0x66, 0x3c, 0x3c, 0x18, 0x3c, 0x3c, 0x66, 0xe7,
    /* U+0079 "y" (8x12) */
    0xe3, 0x67, 0x66, 0x76, 0x36, 0x34, 0x3c, 0x1c, 0x1c, 0x18, 0x78, 0x70,
    /* U+007A "z" (6x9) */
    0xff, 0xf1, 0xce, 0x31, 0x8e, 0x3f, 0xfc,
    /* U+007B "{" (5x16) */
    0x39, 0xcc, 0x63, 0x18, 0xdc, 0xe1, 0x8c, 0x63, 0x18, 0xe7,
    /* U+007C "|" (2x15) */
    0xff, 0xff, 0xff, 0xfc,
    /* U+007D "}" (5x16) */
    0xe7, 0x18, 0xc6, 0x31, 0x87, 0x3b, 0x18, 0xc6, 0x33, 0x9c,
    /* U+007E "~" (7x3) */
    0xf1, 0xfc, 0x78,
    /* U+00B0 "" (6x6) */
    0x7b, 0xfc, 0xf3, 0xfd, 0xe0,
    /* U+00B1 "" (7x10) */
    0x30, 0x63, 0xff, 0xf3, 0x06, 0x0c, 0x00, 0xff, 0xfc,
    /* U+00B2 "" (4x6) */
    0xfb, 0x36, 0xcf,
    /* U+00B3 "" (3x6) */
    0xf5, 0x1b, 0xc0,
    /* U+00B5 "" (7x12) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xff, 0xf7, 0x83, 0x06, 0x00,
    /* U+00B7 "" (2x3) */
    0xfc,
    /* U+00D7 "" (7x7) */
    0x05, 0x9d, 0xf1, 0xc7, 0x8d, 0xb1, 0x00,
    /* U+00F7 "" (7x8) */
    0x30, 0x60, 0x07, 0xff, 0xe0, 0x0c, 0x18,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 54, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 75, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 116, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 7, .adv_w = 144, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 137, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 35, .adv_w = 226, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 55, .adv_w = 167, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 69, .adv_w = 62, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 71, .adv_w = 78, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 79, .adv_w = 78, .box_w = 4, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 87, .adv_w = 142, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 94, .adv_w = 138, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 101, .adv_w = 73, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 103, .adv_w = 92, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 104, .adv_w = 73, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 108, .box_w = 6, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 117, .adv_w = 138, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 128, .adv_w = 138, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 138, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 138, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 161, .adv_w = 138, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 138, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 186, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 138, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 209, .adv_w = 138, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 232, .adv_w = 78, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 235, .adv_w = 78, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 238, .adv_w = 138, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 246, .adv_w = 138, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 252, .adv_w = 138, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 260, .adv_w = 116, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 269, .adv_w = 208, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 290, .adv_w = 158, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 304, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 151, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 328, .adv_w = 161, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 340, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 351, .adv_w = 135, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 362, .adv_w = 165, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 167, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 102, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 396, .adv_w = 130, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 405, .adv_w = 161, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 417, .adv_w = 123, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 426, .adv_w = 189, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 441, .adv_w = 167, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 453, .adv_w = 164, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 467, .adv_w = 152, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 479, .adv_w = 164, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 496, .adv_w = 156, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 508, .adv_w = 142, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 519, .adv_w = 135, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 531, .adv_w = 161, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 543, .adv_w = 153, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 557, .adv_w = 226, .box_w = 13, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 577, .adv_w = 157, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 591, .adv_w = 148, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 603, .adv_w = 140, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 614, .adv_w = 77, .box_w = 3, .box_h = 16, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 620, .adv_w = 108, .box_w = 6, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 632, .adv_w = 77, .box_w = 3, .box_h = 16, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 638, .adv_w = 138, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 644, .adv_w = 128, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 646, .adv_w = 138, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 10},
    {.bitmap_index = 648, .adv_w = 132, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 656, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 667, .adv_w = 120, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 674, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 685, .adv_w = 130, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 693, .adv_w = 87, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 701, .adv_w = 128, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 715, .adv_w = 138, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 726, .adv_w = 67, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 729, .adv_w = 68, .box_w = 3, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 735, .adv_w = 134, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 746, .adv_w = 71, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 751, .adv_w = 207, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 765, .adv_w = 138, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 773, .adv_w = 130, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 781, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 792, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 803, .adv_w = 94, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 809, .adv_w = 116, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 816, .adv_w = 88, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 823, .adv_w = 138, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 831, .adv_w = 125, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 840, .adv_w = 194, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 854, .adv_w = 128, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 863, .adv_w = 127, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 875, .adv_w = 119, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 882, .adv_w = 87, .box_w = 5, .box_h = 16, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 892, .adv_w = 95, .box_w = 2, .box_h = 15, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 896, .adv_w = 87, .box_w = 5, .box_h = 16, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 906, .adv_w = 138, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 909, .adv_w = 108, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 914, .adv_w = 138, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 923, .adv_w = 82, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 926, .adv_w = 82, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 929, .adv_w = 140, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 940, .adv_w = 83, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 941, .adv_w = 138, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 948, .adv_w = 138, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x0005, 0x0007, 0x0027, 0x0047,
};

static const lv_font_fmt_txt_cmap_t cmaps[] = {
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 176, .range_length = 72, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 8, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/

static const uint8_t kern_pair_glyph_ids[] = {
    3, 13, 3, 15, 3, 34, 3, 53, 3, 56, 3, 87, 3, 88, 3, 90,
    6, 3, 6, 8, 6, 11, 7, 34, 7, 66, 7, 68, 7, 69, 7, 70,
    7, 80, 7, 82, 8, 13, 8, 15, 8, 34, 8, 43, 9, 75, 11, 13,
    11, 15, 11, 34, 11, 43, 13, 3, 13, 8, 13, 11, 13, 32, 13, 36,
    13, 40, 13, 48, 13, 50, 13, 53, 13, 54, 13, 55, 13, 56, 13, 58,
    13, 68, 13, 69, 13, 70, 13, 71, 13, 80, 13, 82, 13, 85, 13, 86,
    13, 87, 13, 88, 13, 90, 13, 98, 13, 99, 14, 42, 14, 53, 14, 55,
    14, 56, 14, 57, 14, 58, 14, 59, 14, 89, 14, 91, 15, 3, 15, 8,
    15, 11, 15, 32, 15, 36, 15, 40, 15, 48, 15, 50, 15, 53, 15, 54,
    15, 55, 15, 56, 15, 58, 15, 68, 15, 69, 15, 70, 15, 71, 15, 80,
    15, 82, 15, 85, 15, 86, 15, 87, 15, 88, 15, 90, 15, 98, 15, 99,
    16, 16, 16, 34, 16, 36, 16, 40, 16, 43, 16, 48, 16, 50, 16, 52,
    16, 66, 16, 68, 16, 69, 16, 70, 16, 72, 16, 80, 16, 82, 27, 53,
    27, 55, 27, 58, 28, 53, 28, 55, 28, 58, 32, 13, 32, 15, 32, 56,
    33, 57, 33, 58, 34, 3, 34, 8, 34, 11, 34, 32, 34, 53, 34, 55,
    34, 56, 34, 58, 34, 87, 34, 98, 34, 99, 35, 13, 35, 15, 35, 16,
    35, 53, 35, 55, 35, 57, 35, 58, 35, 64, 35, 89, 36, 98, 36, 99,
    37, 13, 37, 15, 37, 16, 37, 58, 39, 3, 39, 8, 39, 10, 39, 11,
    39, 13, 39, 15, 39, 16, 39, 34, 39, 64, 39, 98, 39, 99, 43, 64,
    44, 14, 45, 3, 45, 8, 45, 11, 45, 14, 45, 32, 45, 36, 45, 40,
    45, 48, 45, 50, 45, 53, 45, 54, 45, 55, 45, 56, 45, 58, 45, 85,
    45, 87, 45, 88, 45, 90, 45, 98, 45, 99, 48, 14, 48, 64, 49, 7,
    49, 13, 49, 15, 49, 16, 49, 33, 49, 34, 49, 43, 49, 52, 49, 55,
    49, 56, 49, 57, 49, 58, 49, 59, 49, 64, 49, 66, 49, 68, 49, 69,
    49, 70, 49, 72, 49, 78, 49, 79, 49, 80, 49, 81, 49, 82, 49, 83,
    49, 84, 49, 89, 49, 91, 50, 14, 50, 64, 51, 7, 51, 16, 51, 33,
    51, 58, 52, 16, 52, 64, 53, 3, 53, 8, 53, 10, 53, 11, 53, 13,
    53, 15, 53, 16, 53, 32, 53, 53, 53, 55, 53, 56, 53, 58, 53, 64,
    53, 72, 53, 98, 53, 99, 54, 16, 54, 64, 55, 7, 55, 13, 55, 14,
    55, 15, 55, 16, 55, 27, 55, 28, 55, 33, 55, 34, 55, 36, 55, 40,
    55, 43, 55, 48, 55, 50, 55, 52, 55, 64, 55, 66, 55, 68, 55, 69,
    55, 70, 55, 72, 55, 78, 55, 79, 55, 80, 55, 81, 55, 82, 55, 83,
    55, 84, 55, 86, 55, 87, 55, 88, 55, 89, 55, 91, 56, 16, 56, 64,
    57, 7, 57, 14, 57, 33, 57, 36, 57, 40, 57, 48, 57, 50, 58, 7,
    58, 10, 58, 13, 58, 14, 58, 15, 58, 16, 58, 27, 58, 28, 58, 34,
    58, 64, 58, 66, 58, 68, 58, 69, 58, 70, 58, 72, 58, 80, 58, 81,
    58, 82, 58, 84, 58, 91, 59, 14, 59, 36, 59, 40, 59, 48, 59, 50,
    64, 36, 64, 40, 64, 43, 64, 48, 64, 50, 64, 52, 64, 53, 64, 54,
    64, 55, 64, 56, 64, 58, 64, 68, 64, 69, 64, 70, 64, 72, 64, 75,
    64, 77, 64, 80, 64, 82, 64, 84, 64, 85, 64, 86, 64, 87, 64, 88,
    66, 16, 66, 53, 66, 58, 67, 53, 67, 55, 67, 56, 67, 58, 67, 64,
    68, 16, 68, 53, 68, 55, 68, 56, 68, 58, 68, 64, 68, 68, 68, 70,
    68, 80, 70, 53, 70, 58, 70, 64, 71, 3, 71, 8, 71, 10, 71, 11,
    71, 32, 71, 36, 71, 40, 71, 48, 71, 50, 71, 53, 71, 55, 71, 56,
    71, 57, 71, 58, 71, 59, 71, 62, 71, 64, 71, 74, 71, 87, 71, 88,
    71, 90, 71, 94, 71, 98, 71, 99, 72, 16, 72, 64, 72, 75, 73, 3,
    73, 8, 73, 11, 73, 53, 73, 55, 73, 56, 73, 58, 74, 98, 74, 99,
    76, 34, 76, 59, 76, 64, 77, 13, 77, 15, 77, 34, 77, 43, 77, 57,
    77, 59, 77, 64, 77, 91, 78, 53, 78, 55, 78, 58, 79, 3, 79, 8,
    79, 11, 79, 53, 79, 55, 79, 56, 79, 58, 80, 53, 80, 58, 80, 64,
    81, 53, 81, 55, 81, 56, 81, 58, 81, 64, 82, 55, 82, 58, 83, 13,
    83, 15, 83, 16, 83, 34, 83, 64, 83, 98, 84, 53, 84, 64, 85, 7,
    85, 14, 85, 53, 85, 58, 85, 68, 85, 69, 85, 70, 85, 80, 85, 82,
    85, 85, 86, 53, 86, 55, 86, 56, 86, 58, 87, 13, 87, 15, 87, 34,
    87, 64, 88, 13, 88, 15, 88, 64, 89, 14, 89, 53, 90, 7, 90, 13,
    90, 15, 90, 34, 90, 64, 91, 3, 91, 8, 91, 11, 91, 13, 91, 15,
    91, 34, 91, 57, 91, 64, 92, 75, 98, 13, 98, 15, 98, 43, 99, 13,
    99, 15, 99, 34, 99, 43, 99, 85,
};

static const int8_t kern_pair_values[] = {
    -23, -23, -13, 4, 4, 6, 5, 5, -15, -15, -15, 1, 3, 3, 3, 3,
    3, 3, -23, -23, -13, -10, 18, -23, -23, -13, -10, -23, -23, -23, -20, -10,
    -10, -10, -10, -23, -9, -15, -10, -23, -4, -4, -4, -4, -4, -4, -7, -2,
    -17, -13, -12, -13, -15, -8, -12, -9, -5, -10, -15, -5, -9, -5, -23, -23,
    -23, -20, -10, -10, -10, -10, -23, -9, -15, -10, -23, -4, -4, -4, -4, -4,
    -4, -7, -2, -17, -13, -12, -13, -15, -49, -22, -8, -8, -8, -8, -8, -5,
    -13, -9, -9, -9, -9, -9, -9, -10, -8, -13, -10, -8, -13, -31, -31, 4,
    -10, -10, -13, -13, -13, -13, -15, -14, -7, -18, -8, -15, -13, -4, -4, -6,
    -4, -5, -4, -5, -16, -3, 3, 3, -11, -11, -12, -10, 1, 1, 4, 1,
    -26, -26, -22, -19, -36, 1, 1, -22, -14, -20, -20, -20, -9, -15, -10, -10,
    -10, -10, -19, -4, -14, -10, -23, -7, -11, -8, -9, -20, -18, 4, -26, -8,
    -28, -28, -23, -3, -17, -14, -3, -1, -3, -9, -6, -6, -38, -4, -5, -5,
    -5, -8, -3, -3, -5, -4, -5, -3, -4, -1, -1, 4, -26, -6, -5, -5,
    -8, -9, -15, 4, 4, 5, 4, -23, -23, -26, 4, 4, 2, 1, 2, -20,
    -18, 3, 5, -10, -18, -9, -15, -9, -15, -17, -8, -8, -8, -14, -6, -6,
    -10, -6, -6, -7, -26, -9, -9, -9, -9, -10, -5, -5, -9, -5, -9, -5,
    -6, -6, -3, -3, -3, -4, -13, -18, -6, -10, -8, -8, -8, -8, -8, -14,
    5, -23, -15, -23, -26, -13, -13, -18, -28, -14, -14, -13, -14, -14, -14, -13,
    -13, -13, -13, -10, -5, -5, -5, -5, -26, -26, -13, -26, -26, -15, -20, -18,
    -26, -18, -28, -15, -10, -15, 9, 14, -14, -15, -10, -10, -17, -9, -18, -13,
    5, -18, -14, -17, -9, -6, -15, -13, -1, -12, -7, -3, -13, -10, -1, -1,
    -1, -14, -15, -15, 8, 8, 6, 8, 8, 4, 4, 4, 4, 6, 9, 6,
    4, 8, 1, 4, -16, 3, 4, 1, 3, 4, 6, 10, 8, 14, 8, -4,
    -4, -4, -14, -9, -6, -14, 5, 5, 4, 4, 5, 3, 3, 6, 3, 4,
    4, 6, 2, -14, -9, -14, -4, -4, -4, -14, -9, -6, -14, -14, -15, -15,
    -17, -9, -6, -15, -13, -6, -8, -20, -20, -8, -10, -20, 10, -14, -13, -2,
    -3, -6, -5, -1, -1, -1, -1, -1, -1, -12, -6, -3, -13, -17, -17, -8,
    -18, -13, -13, -13, -9, -9, -8, -17, -17, -9, -20, 1, 1, 1, 3, 3,
    3, 3, 1, 5, -13, -13, -14, -15, -15, -13, -15, 6,
};

static const lv_font_fmt_txt_kern_pair_t kern_pairs = {
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 460,
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
const lv_font_t humid1_font_plex_cond_bold_16 = {
#else
lv_font_t humid1_font_plex_cond_bold_16 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 22,
    .base_line = 5,
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc,
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_font_plex_sans_bold_16,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_COND_BOLD_16 */
