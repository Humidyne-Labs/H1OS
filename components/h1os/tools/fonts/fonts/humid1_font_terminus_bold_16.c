/*******************************************************************************
 * Font: humid1_font_terminus_bold_16 (IBM Plex Terminus Bold)
 * Size: 16 px @ 188 DPI (SSD1681 1-bit E-Paper Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Raster Mode: exact-mono (FT_LOAD_TARGET_MONO + Dropout Control)
 * License: SIL Open Font License 1.1 (IBM Corp.) / Font Awesome Free License
 ******************************************************************************/

#include "lvgl.h"

#ifndef HUMID1_FONT_TERMINUS_BOLD_16
#define HUMID1_FONT_TERMINUS_BOLD_16 1
#endif

#if HUMID1_FONT_TERMINUS_BOLD_16

extern const lv_font_t humid1_font_terminus_normal_16;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x10) */
    0xff, 0xfc, 0xf0,
    /* U+0022 "" (6x3) */
    0xcf, 0x3c, 0xc0,
    /* U+0023 "#" (7x10) */
    0x6c, 0xd9, 0xb7, 0xf6, 0xcd, 0xbf, 0xb6, 0x6c, 0xd8,
    /* U+0024 "$" (7x13) */
    0x10, 0x21, 0xf6, 0xbd, 0x1a, 0x1f, 0x0b, 0x17, 0xad, 0xf0, 0x81, 0x00,
    /* U+0025 "%" (8x10) */
    0x66, 0xd6, 0x6c, 0x0c, 0x18, 0x18, 0x30, 0x36, 0x6b, 0x66,
    /* U+0026 "&" (7x10) */
    0x38, 0xd9, 0xb1, 0xc7, 0x7b, 0xb3, 0x66, 0xdc, 0xec,
    /* U+0027 "'" (2x3) */
    0xfc,
    /* U+0028 "(" (4x10) */
    0x36, 0xcc, 0xcc, 0xcc, 0x63,
    /* U+0029 ")" (4x10) */
    0xc6, 0x33, 0x33, 0x33, 0x6c,
    /* U+002A "" (7x5) */
    0x6c, 0x73, 0xf9, 0xc6, 0xc0,
    /* U+002B "+" (6x5) */
    0x30, 0xcf, 0xcc, 0x30,
    /* U+002C "," (3x3) */
    0x6f, 0x00,
    /* U+002D "-" (7x1) */
    0xfe,
    /* U+002E "." (2x2) */
    0xf0,
    /* U+002F "/" (6x10) */
    0x0c, 0x31, 0x86, 0x30, 0xc6, 0x18, 0xc3, 0x00,
    /* U+0030 "0" (7x10) */
    0x7d, 0x8f, 0x1e, 0x7d, 0xfe, 0xf9, 0xe3, 0xc6, 0xf8,
    /* U+0031 "1" (6x10) */
    0x31, 0xcf, 0x0c, 0x30, 0xc3, 0x0c, 0x33, 0xf0,
    /* U+0032 "2" (7x10) */
    0x7d, 0x8f, 0x18, 0x30, 0xc3, 0x0c, 0x30, 0xc1, 0xfc,
    /* U+0033 "3" (7x10) */
    0x7d, 0x8f, 0x18, 0x33, 0xc0, 0xc1, 0xe3, 0xc6, 0xf8,
    /* U+0034 "4" (7x10) */
    0x06, 0x1c, 0x79, 0xb6, 0x78, 0xff, 0x83, 0x06, 0x0c,
    /* U+0035 "5" (7x10) */
    0xff, 0x83, 0x06, 0x0f, 0xc0, 0xc1, 0x83, 0xc6, 0xf8,
    /* U+0036 "6" (7x10) */
    0x3c, 0xc3, 0x06, 0x0f, 0xd8, 0xf1, 0xe3, 0xc6, 0xf8,
    /* U+0037 "7" (7x10) */
    0xfe, 0x0c, 0x18, 0x60, 0xc3, 0x06, 0x18, 0x30, 0x60,
    /* U+0038 "8" (7x10) */
    0x7d, 0x8f, 0x1e, 0x37, 0xd8, 0xf1, 0xe3, 0xc6, 0xf8,
    /* U+0039 "9" (7x10) */
    0x7d, 0x8f, 0x1e, 0x3c, 0x6f, 0xc1, 0x83, 0x0c, 0xf0,
    /* U+003A ":" (2x7) */
    0xf0, 0x3c,
    /* U+003B ";" (3x8) */
    0x6c, 0x00, 0xde,
    /* U+003C "<" (6x9) */
    0x0c, 0x63, 0x18, 0xc1, 0x83, 0x06, 0x0c,
    /* U+003D "=" (7x4) */
    0xfe, 0x00, 0x07, 0xf0,
    /* U+003E ">" (6x9) */
    0xc1, 0x83, 0x06, 0x0c, 0x63, 0x18, 0xc0,
    /* U+003F "?" (7x10) */
    0x7d, 0x8f, 0x1e, 0x30, 0xc3, 0x06, 0x00, 0x18, 0x30,
    /* U+0040 "@" (7x10) */
    0x7d, 0x8f, 0x3e, 0xbd, 0x7a, 0xf5, 0xe7, 0xc0, 0xfc,
    /* U+0041 "A" (7x10) */
    0x7d, 0x8f, 0x1e, 0x3c, 0x7f, 0xf1, 0xe3, 0xc7, 0x8c,
    /* U+0042 "B" (7x10) */
    0xfd, 0x8f, 0x1e, 0x3f, 0xd8, 0xf1, 0xe3, 0xc7, 0xf8,
    /* U+0043 "C" (7x10) */
    0x7d, 0x8f, 0x1e, 0x0c, 0x18, 0x30, 0x63, 0xc6, 0xf8,
    /* U+0044 "D" (7x10) */
    0xf9, 0x9b, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xcd, 0xf0,
    /* U+0045 "E" (7x10) */
    0xff, 0x83, 0x06, 0x0f, 0x98, 0x30, 0x60, 0xc1, 0xfc,
    /* U+0046 "F" (7x10) */
    0xff, 0x83, 0x06, 0x0f, 0x98, 0x30, 0x60, 0xc1, 0x80,
    /* U+0047 "G" (7x10) */
    0x7d, 0x8f, 0x1e, 0x0c, 0x1b, 0xf1, 0xe3, 0xc6, 0xf8,
    /* U+0048 "H" (7x10) */
    0xc7, 0x8f, 0x1e, 0x3f, 0xf8, 0xf1, 0xe3, 0xc7, 0x8c,
    /* U+0049 "I" (4x10) */
    0xf6, 0x66, 0x66, 0x66, 0x6f,
    /* U+004A "J" (7x10) */
    0x1e, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x66, 0xcc, 0xf0,
    /* U+004B "K" (7x10) */
    0xc7, 0x8f, 0x36, 0xcf, 0x1e, 0x36, 0x66, 0xc7, 0x8c,
    /* U+004C "L" (7x10) */
    0xc1, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0xfc,
    /* U+004D "M" (7x10) */
    0x83, 0x8f, 0xbf, 0xfd, 0x78, 0xf1, 0xe3, 0xc7, 0x8c,
    /* U+004E "N" (7x10) */
    0xc7, 0x8f, 0x1f, 0x3f, 0x7b, 0xf3, 0xe3, 0xc7, 0x8c,
    /* U+004F "O" (7x10) */
    0x7d, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6, 0xf8,
    /* U+0050 "P" (7x10) */
    0xfd, 0x8f, 0x1e, 0x3c, 0x7f, 0xb0, 0x60, 0xc1, 0x80,
    /* U+0051 "Q" (7x11) */
    0x7d, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xde, 0xf8, 0x18,
    /* U+0052 "R" (7x10) */
    0xfd, 0x8f, 0x1e, 0x3c, 0x7f, 0xbc, 0x6c, 0xcd, 0x8c,
    /* U+0053 "S" (7x10) */
    0x7d, 0x8f, 0x06, 0x07, 0xc0, 0xc1, 0xe3, 0xc6, 0xf8,
    /* U+0054 "T" (8x10) */
    0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    /* U+0055 "U" (7x10) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6, 0xf8,
    /* U+0056 "V" (7x10) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x6d, 0x9b, 0x36, 0x38, 0x70,
    /* U+0057 "W" (7x10) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x7a, 0xff, 0xf7, 0xc7, 0x04,
    /* U+0058 "X" (7x10) */
    0xc7, 0x8d, 0xb3, 0x63, 0x87, 0x1b, 0x36, 0xc7, 0x8c,
    /* U+0059 "Y" (8x10) */
    0xc3, 0xc3, 0x66, 0x66, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x18,
    /* U+005A "Z" (7x10) */
    0xfe, 0x0c, 0x18, 0x61, 0x86, 0x18, 0x60, 0xc1, 0xfc,
    /* U+005B "[" (4x10) */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcf,
    /* U+005C "" (6x10) */
    0xc3, 0x06, 0x18, 0x30, 0xc1, 0x86, 0x0c, 0x30,
    /* U+005D "]" (4x10) */
    0xf3, 0x33, 0x33, 0x33, 0x3f,
    /* U+005E "^" (6x3) */
    0x31, 0xec, 0xc0,
    /* U+005F "_" (7x1) */
    0xfe,
    /* U+0060 "`" (3x2) */
    0xcc,
    /* U+0061 "a" (7x7) */
    0x7c, 0x0d, 0xfe, 0x3c, 0x78, 0xdf, 0x80,
    /* U+0062 "b" (7x10) */
    0xc1, 0x83, 0x07, 0xec, 0x78, 0xf1, 0xe3, 0xc7, 0xf8,
    /* U+0063 "c" (7x7) */
    0x7d, 0x8f, 0x06, 0x0c, 0x18, 0xdf, 0x00,
    /* U+0064 "d" (7x10) */
    0x06, 0x0c, 0x1b, 0xfc, 0x78, 0xf1, 0xe3, 0xc6, 0xfc,
    /* U+0065 "e" (7x7) */
    0x7d, 0x8f, 0x1f, 0xfc, 0x18, 0x1f, 0x00,
    /* U+0066 "f" (7x10) */
    0x1e, 0x60, 0xc7, 0xe3, 0x06, 0x0c, 0x18, 0x30, 0x60,
    /* U+0067 "g" (7x10) */
    0x7f, 0x8f, 0x1e, 0x3c, 0x78, 0xdf, 0x83, 0x06, 0xf8,
    /* U+0068 "h" (7x10) */
    0xc1, 0x83, 0x07, 0xec, 0x78, 0xf1, 0xe3, 0xc7, 0x8c,
    /* U+0069 "i" (4x10) */
    0x66, 0x0e, 0x66, 0x66, 0x6f,
    /* U+006A "j" (6x13) */
    0x0c, 0x30, 0x07, 0x0c, 0x30, 0xc3, 0x0c, 0x3c, 0xf3, 0x78,
    /* U+006B "k" (7x10) */
    0xc1, 0x83, 0x06, 0x3c, 0xdb, 0x3c, 0x6c, 0xcd, 0x8c,
    /* U+006C "l" (4x10) */
    0xe6, 0x66, 0x66, 0x66, 0x6f,
    /* U+006D "m" (7x7) */
    0xfd, 0xaf, 0x5e, 0xbd, 0x7a, 0xf5, 0x80,
    /* U+006E "n" (7x7) */
    0xfd, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0x80,
    /* U+006F "o" (7x7) */
    0x7d, 0x8f, 0x1e, 0x3c, 0x78, 0xdf, 0x00,
    /* U+0070 "p" (7x10) */
    0xfd, 0x8f, 0x1e, 0x3c, 0x78, 0xff, 0x60, 0xc1, 0x80,
    /* U+0071 "q" (7x10) */
    0x7f, 0x8f, 0x1e, 0x3c, 0x78, 0xdf, 0x83, 0x06, 0x0c,
    /* U+0072 "r" (7x7) */
    0xdf, 0xe3, 0x86, 0x0c, 0x18, 0x30, 0x00,
    /* U+0073 "s" (7x7) */
    0x7f, 0x83, 0x03, 0xe0, 0x60, 0xff, 0x00,
    /* U+0074 "t" (7x10) */
    0x30, 0x60, 0xc7, 0xe3, 0x06, 0x0c, 0x18, 0x30, 0x3c,
    /* U+0075 "u" (7x7) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xdf, 0x80,
    /* U+0076 "v" (7x7) */
    0xc7, 0x8f, 0x1b, 0x66, 0xc7, 0x0e, 0x00,
    /* U+0077 "w" (7x7) */
    0xc7, 0x8f, 0x5e, 0xbd, 0x7a, 0xdf, 0x00,
    /* U+0078 "x" (7x7) */
    0xc7, 0x8d, 0xb1, 0xc6, 0xd8, 0xf1, 0x80,
    /* U+0079 "y" (7x10) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xdf, 0x83, 0x06, 0xf8,
    /* U+007A "z" (7x7) */
    0xfe, 0x18, 0x61, 0x86, 0x18, 0x3f, 0x80,
    /* U+007B "{" (5x10) */
    0x3b, 0x18, 0xcc, 0x31, 0x8c, 0x61, 0xc0,
    /* U+007C "|" (2x10) */
    0xff, 0xff, 0xf0,
    /* U+007D "}" (5x10) */
    0xe1, 0x8c, 0x61, 0x98, 0xc6, 0x37, 0x00,
    /* U+007E "~" (8x3) */
    0x73, 0xdb, 0xce,
    /* U+00B0 "" (5x4) */
    0x76, 0xf6, 0xe0,
    /* U+00B1 "" (6x7) */
    0x30, 0xcf, 0xcc, 0x30, 0x0f, 0xc0,
    /* U+00B2 "" (5x6) */
    0x76, 0xc6, 0x66, 0x7c,
    /* U+00B3 "" (5x6) */
    0xf0, 0xdc, 0x31, 0xf8,
    /* U+00B5 "" (7x10) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x79, 0xfd, 0xe0, 0xc1, 0x80,
    /* U+00B7 "" (2x2) */
    0xf0,
    /* U+00D7 "" (7x6) */
    0xc6, 0xd8, 0xe1, 0xc6, 0xd8, 0xc0,
    /* U+00F7 "" (6x7) */
    0x30, 0xc0, 0x3f, 0x00, 0xc3, 0x00,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 128, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 128, .box_w = 2, .box_h = 10, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 128, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 6, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 128, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 27, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 37, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 46, .adv_w = 128, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = 8},
    {.bitmap_index = 47, .adv_w = 128, .box_w = 4, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 128, .box_w = 4, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 57, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 62, .adv_w = 128, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 66, .adv_w = 128, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 68, .adv_w = 128, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 69, .adv_w = 128, .box_w = 2, .box_h = 2, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 70, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 78, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 87, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 95, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 113, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 131, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 140, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 149, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 158, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 128, .box_w = 2, .box_h = 7, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 128, .box_w = 3, .box_h = 8, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 172, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 128, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 183, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 190, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 208, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 226, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 235, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 244, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 253, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 262, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 271, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 280, .adv_w = 128, .box_w = 4, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 285, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 294, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 303, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 312, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 321, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 330, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 348, .adv_w = 128, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 358, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 367, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 386, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 395, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 404, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 413, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 422, .adv_w = 128, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 432, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 441, .adv_w = 128, .box_w = 4, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 446, .adv_w = 128, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 454, .adv_w = 128, .box_w = 4, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 459, .adv_w = 128, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 462, .adv_w = 128, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 463, .adv_w = 128, .box_w = 3, .box_h = 2, .ofs_x = 2, .ofs_y = 10},
    {.bitmap_index = 464, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 471, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 480, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 487, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 496, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 503, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 512, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 521, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 530, .adv_w = 128, .box_w = 4, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 535, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 545, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 554, .adv_w = 128, .box_w = 4, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 559, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 566, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 573, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 580, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 589, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 598, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 605, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 612, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 621, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 628, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 635, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 642, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 649, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 658, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 665, .adv_w = 128, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 672, .adv_w = 128, .box_w = 2, .box_h = 10, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 675, .adv_w = 128, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 682, .adv_w = 128, .box_w = 8, .box_h = 3, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 685, .adv_w = 128, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 688, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 694, .adv_w = 128, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 698, .adv_w = 128, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 702, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 711, .adv_w = 128, .box_w = 2, .box_h = 2, .ofs_x = 3, .ofs_y = 3},
    {.bitmap_index = 712, .adv_w = 128, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 718, .adv_w = 128, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1}
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
    .kern_dsc = NULL,
    .kern_scale = 0,
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
const lv_font_t humid1_font_terminus_bold_16 = {
#else
lv_font_t humid1_font_terminus_bold_16 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 16,
    .base_line = 4,
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_font_terminus_normal_16,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_TERMINUS_BOLD_16 */
