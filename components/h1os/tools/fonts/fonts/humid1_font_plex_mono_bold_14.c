/*******************************************************************************
 * Font: humid1_font_plex_mono_bold_14 (IBM Plex Mono Bold)
 * Size: 14 px @ 188 DPI (SSD1681 1-bit E-Paper Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Raster Mode: autohint-mono (FT_LOAD_TARGET_MONO + Dropout Control)
 * License: SIL Open Font License 1.1 (IBM Corp.) / Font Awesome Free License
 ******************************************************************************/

#include "lvgl.h"

#ifndef HUMID1_FONT_PLEX_MONO_BOLD_14
#define HUMID1_FONT_PLEX_MONO_BOLD_14 1
#endif

#if HUMID1_FONT_PLEX_MONO_BOLD_14

extern const lv_font_t humid1_font_plex_sans_bold_14;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x11) */
    0xff, 0xf8, 0xfc,
    /* U+0022 "" (5x5) */
    0xde, 0xf7, 0xbd, 0x80,
    /* U+0023 "#" (8x11) */
    0x36, 0x36, 0x36, 0xf7, 0x36, 0x24, 0x6c, 0xef, 0x6c, 0x6c, 0x6c,
    /* U+0024 "$" (7x14) */
    0x18, 0x31, 0xf7, 0xed, 0x9b, 0x1f, 0x1f, 0x1e, 0x3f, 0xff, 0xe1, 0x83,
    0x00,
    /* U+0025 "%" (8x11) */
    0x73, 0xdb, 0xda, 0xde, 0xdc, 0x70, 0x06, 0x2f, 0x6f, 0x6f, 0xc6,
    /* U+0026 "&" (8x11) */
    0x3c, 0x64, 0x60, 0x70, 0x70, 0x7b, 0xda, 0xce, 0xce, 0xc6, 0x7b,
    /* U+0027 "'" (2x5) */
    0xff, 0xc0,
    /* U+0028 "(" (5x13) */
    0x19, 0x98, 0x8c, 0x63, 0x18, 0xc2, 0x18, 0x61, 0x80,
    /* U+0029 ")" (5x13) */
    0xc3, 0x0c, 0x21, 0x8c, 0x63, 0x18, 0x8c, 0xcc, 0x00,
    /* U+002A "" (8x8) */
    0x18, 0x18, 0xff, 0xff, 0x3c, 0x3c, 0x66, 0x24,
    /* U+002B "+" (7x7) */
    0x30, 0x60, 0xc7, 0xf3, 0x06, 0x0c, 0x00,
    /* U+002C "," (4x5) */
    0x76, 0x66, 0xc0,
    /* U+002D "-" (4x1) */
    0xf0,
    /* U+002E "." (3x3) */
    0xff, 0x80,
    /* U+002F "/" (6x14) */
    0x0c, 0x30, 0xc6, 0x18, 0x63, 0x0c, 0x31, 0x86, 0x18, 0xc3, 0x00,
    /* U+0030 "0" (8x11) */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xdb, 0xc3, 0xc3, 0xc3, 0x66, 0x3c,
    /* U+0031 "1" (7x11) */
    0x79, 0xf3, 0x64, 0xc1, 0x83, 0x06, 0x0c, 0x18, 0x33, 0xf8,
    /* U+0032 "2" (7x11) */
    0x79, 0x89, 0x18, 0x30, 0x61, 0xc7, 0x1c, 0x71, 0xc3, 0xf8,
    /* U+0033 "3" (7x11) */
    0x7c, 0xcd, 0x18, 0x30, 0x67, 0x01, 0x83, 0x47, 0x8d, 0xe0,
    /* U+0034 "4" (9x11) */
    0x0e, 0x07, 0x05, 0x82, 0xc3, 0x61, 0x31, 0x98, 0x8c, 0xff, 0x83, 0x01,
    0x80,
    /* U+0035 "5" (7x11) */
    0xfd, 0x83, 0x06, 0x0f, 0xd9, 0xc1, 0x83, 0x87, 0x9b, 0xe0,
    /* U+0036 "6" (7x11) */
    0x18, 0x61, 0x83, 0x0d, 0xdd, 0xf1, 0xe3, 0xc6, 0x98, 0xe0,
    /* U+0037 "7" (7x11) */
    0xff, 0x8f, 0x18, 0x60, 0xc1, 0x86, 0x0c, 0x18, 0x60, 0xc0,
    /* U+0038 "8" (7x11) */
    0x7d, 0x8f, 0x1e, 0x34, 0x47, 0x31, 0xe3, 0xc7, 0x8d, 0xf0,
    /* U+0039 "9" (7x11) */
    0x38, 0xdb, 0x1e, 0x3c, 0x7d, 0xdd, 0x86, 0x0c, 0x30, 0xc0,
    /* U+003A ":" (3x8) */
    0xff, 0x81, 0xff,
    /* U+003B ";" (3x10) */
    0xff, 0x81, 0xfe, 0xd0,
    /* U+003C "<" (6x9) */
    0x04, 0x77, 0xb8, 0xc3, 0xc3, 0x83, 0x04,
    /* U+003D "=" (7x5) */
    0xfe, 0x00, 0x00, 0x0f, 0xe0,
    /* U+003E ">" (6x9) */
    0x83, 0x87, 0x87, 0x0c, 0xf7, 0x30, 0x80,
    /* U+003F "?" (7x11) */
    0x7d, 0xcd, 0x18, 0x30, 0x61, 0x8c, 0x00, 0x38, 0x70, 0xe0,
    /* U+0040 "@" (7x12) */
    0x3c, 0xcb, 0x1e, 0xff, 0x7e, 0xfd, 0xfb, 0xdf, 0x81, 0x81, 0xc0,
    /* U+0041 "A" (8x11) */
    0x1c, 0x3c, 0x3c, 0x3e, 0x36, 0x66, 0x66, 0x7e, 0x63, 0xe3, 0xc3,
    /* U+0042 "B" (7x11) */
    0xf9, 0x9b, 0x36, 0x6c, 0xdf, 0x31, 0xe3, 0xc7, 0x8f, 0xf0,
    /* U+0043 "C" (7x11) */
    0x3c, 0xcf, 0x1e, 0x0c, 0x18, 0x30, 0x60, 0xc6, 0xcc, 0xf0,
    /* U+0044 "D" (7x11) */
    0xf9, 0x9b, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc7, 0x9b, 0xe0,
    /* U+0045 "E" (6x11) */
    0xff, 0x0c, 0x30, 0xc3, 0xfc, 0x30, 0xc3, 0x0f, 0xc0,
    /* U+0046 "F" (7x11) */
    0xff, 0x83, 0x06, 0x0c, 0x1f, 0xb0, 0x60, 0xc1, 0x83, 0x00,
    /* U+0047 "G" (7x11) */
    0x3c, 0xdf, 0x1e, 0x0c, 0x1b, 0xf1, 0xe3, 0xc6, 0xdd, 0xd8,
    /* U+0048 "H" (7x11) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x7f, 0xf1, 0xe3, 0xc7, 0x8f, 0x18,
    /* U+0049 "I" (6x11) */
    0xfc, 0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0x30, 0xcf, 0xc0,
    /* U+004A "J" (6x11) */
    0x7c, 0x30, 0xc3, 0x0c, 0x30, 0xc3, 0xcf, 0x37, 0x80,
    /* U+004B "K" (7x11) */
    0xc7, 0x9b, 0x76, 0xcf, 0x1f, 0x3e, 0x6e, 0xcd, 0x9f, 0x18,
    /* U+004C "L" (7x11) */
    0xc1, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x83, 0xf8,
    /* U+004D "M" (7x11) */
    0xef, 0xdf, 0xbf, 0x7f, 0xfa, 0xf5, 0xeb, 0xd7, 0x8f, 0x18,
    /* U+004E "N" (7x11) */
    0xe7, 0xcf, 0x9f, 0xbd, 0x7a, 0xf5, 0xef, 0xcf, 0x9f, 0x38,
    /* U+004F "O" (8x11) */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x3c,
    /* U+0050 "P" (7x11) */
    0xfd, 0x8f, 0x1e, 0x3c, 0x78, 0xff, 0x60, 0xc1, 0x83, 0x00,
    /* U+0051 "Q" (8x14) */
    0x3c, 0x66, 0xc2, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x7e, 0x18,
    0x18, 0x1e,
    /* U+0052 "R" (7x11) */
    0xfd, 0x8f, 0x1e, 0x3c, 0x78, 0xff, 0x6e, 0xcd, 0x9f, 0x18,
    /* U+0053 "S" (7x11) */
    0x7d, 0x8b, 0x07, 0x0f, 0xdf, 0xdf, 0x83, 0x07, 0x8b, 0xe0,
    /* U+0054 "T" (8x11) */
    0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    /* U+0055 "U" (7x11) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc7, 0x8d, 0xf0,
    /* U+0056 "V" (8x11) */
    0xe3, 0xe3, 0x63, 0x66, 0x66, 0x76, 0x36, 0x36, 0x3c, 0x3c, 0x1c,
    /* U+0057 "W" (8x11) */
    0xc3, 0xc3, 0xc3, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xef, 0xe7, 0xe7,
    /* U+0058 "X" (8x11) */
    0x63, 0x66, 0x36, 0x3c, 0x3c, 0x1c, 0x3c, 0x3e, 0x66, 0x67, 0xe3,
    /* U+0059 "Y" (8x11) */
    0xc3, 0x66, 0x66, 0x7e, 0x3c, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x18,
    /* U+005A "Z" (7x11) */
    0xfe, 0x1c, 0x30, 0xe1, 0x87, 0x0c, 0x38, 0x61, 0xc3, 0xf8,
    /* U+005B "[" (5x13) */
    0xfe, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31, 0x8f, 0x80,
    /* U+005C "" (6x14) */
    0xc1, 0x06, 0x18, 0x20, 0xc3, 0x04, 0x18, 0x60, 0x83, 0x0c, 0x10,
    /* U+005D "]" (5x13) */
    0xf8, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x3f, 0x80,
    /* U+005E "^" (7x6) */
    0x38, 0xf1, 0x36, 0x6c, 0x70, 0x80,
    /* U+005F "_" (7x1) */
    0xfe,
    /* U+0060 "`" (3x3) */
    0xcd, 0x80,
    /* U+0061 "a" (7x8) */
    0x7c, 0x9c, 0x18, 0x37, 0xf8, 0xf1, 0xbf,
    /* U+0062 "b" (7x11) */
    0xc1, 0x83, 0x06, 0xee, 0xf8, 0xf1, 0xe3, 0xc7, 0x9f, 0xf0,
    /* U+0063 "c" (6x8) */
    0x3d, 0xbc, 0x30, 0xc3, 0x04, 0x4f,
    /* U+0064 "d" (7x11) */
    0x06, 0x0c, 0x1b, 0xfe, 0x78, 0xf1, 0xe3, 0xc7, 0xcd, 0xf8,
    /* U+0065 "e" (7x8) */
    0x3c, 0x8f, 0x1f, 0xfc, 0x18, 0x19, 0x1e,
    /* U+0066 "f" (7x11) */
    0x1e, 0x60, 0xc7, 0xf3, 0x06, 0x0c, 0x18, 0x30, 0x63, 0xf0,
    /* U+0067 "g" (7x12) */
    0x0c, 0xf3, 0x36, 0x6c, 0xcf, 0x30, 0x60, 0x7d, 0x0f, 0x1f, 0xe0,
    /* U+0068 "h" (7x11) */
    0xc1, 0x83, 0x06, 0xee, 0x78, 0xf1, 0xe3, 0xc7, 0x8f, 0x18,
    /* U+0069 "i" (7x11) */
    0x30, 0x00, 0x07, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x63, 0xf8,
    /* U+006A "j" (5x14) */
    0x18, 0x01, 0xf1, 0x8c, 0x63, 0x18, 0xc6, 0x31, 0xf8,
    /* U+006B "k" (7x11) */
    0xc1, 0x83, 0x06, 0x7d, 0xdf, 0x3c, 0x7c, 0xdd, 0x9b, 0x38,
    /* U+006C "l" (7x11) */
    0xf0, 0x60, 0xc1, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x63, 0xf8,
    /* U+006D "m" (8x8) */
    0xff, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb,
    /* U+006E "n" (7x8) */
    0xfd, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3,
    /* U+006F "o" (7x8) */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xdb, 0x1c,
    /* U+0070 "p" (7x11) */
    0xfd, 0x9f, 0x1e, 0x3c, 0x78, 0xf3, 0xfe, 0xc1, 0x83, 0x00,
    /* U+0071 "q" (7x11) */
    0x7f, 0xcf, 0x1e, 0x3c, 0x78, 0xf9, 0xbf, 0x06, 0x0c, 0x18,
    /* U+0072 "r" (7x8) */
    0xf6, 0x70, 0xc1, 0x83, 0x06, 0x0c, 0x7e,
    /* U+0073 "s" (6x8) */
    0x7f, 0x2c, 0x3e, 0xfc, 0x78, 0xfe,
    /* U+0074 "t" (7x11) */
    0x30, 0x60, 0xc7, 0xf3, 0x06, 0x0c, 0x18, 0x30, 0x60, 0x78,
    /* U+0075 "u" (7x8) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xbf,
    /* U+0076 "v" (7x8) */
    0xc7, 0x9f, 0x33, 0x66, 0xcf, 0x1e, 0x1c,
    /* U+0077 "w" (8x8) */
    0xd9, 0xd9, 0xdb, 0xd7, 0x57, 0x57, 0x57, 0x67,
    /* U+0078 "x" (7x8) */
    0xcf, 0xd9, 0xe1, 0xc3, 0x8f, 0x33, 0x67,
    /* U+0079 "y" (8x11) */
    0xe3, 0x63, 0x66, 0x76, 0x34, 0x3c, 0x3c, 0x18, 0x18, 0x18, 0x70,
    /* U+007A "z" (6x8) */
    0xfc, 0x71, 0x8e, 0x71, 0x8e, 0x3f,
    /* U+007B "{" (7x13) */
    0x3e, 0x60, 0xc1, 0xc1, 0x83, 0x38, 0x0c, 0x18, 0x70, 0xc1, 0x83, 0xe0,
    /* U+007C "|" (2x13) */
    0xff, 0xff, 0xff, 0xc0,
    /* U+007D "}" (7x13) */
    0xf8, 0x30, 0x61, 0xc3, 0x06, 0x03, 0x98, 0x30, 0x70, 0x60, 0xcf, 0x80,
    /* U+007E "~" (7x4) */
    0x67, 0x6e, 0x54, 0xe0,
    /* U+00B0 "" (6x5) */
    0x7b, 0x3c, 0xf3, 0x78,
    /* U+00B1 "" (7x10) */
    0x30, 0x60, 0xc7, 0xf3, 0x06, 0x0c, 0x00, 0x01, 0xfc,
    /* U+00B2 "" (4x5) */
    0xf3, 0x34, 0xf0,
    /* U+00B3 "" (4x5) */
    0xea, 0x6b, 0xe0,
    /* U+00B5 "" (7x10) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x7f, 0xfd, 0xe0, 0xc1, 0x80,
    /* U+00B7 "" (3x3) */
    0xff, 0x80,
    /* U+00D7 "" (6x7) */
    0x47, 0xb7, 0x8e, 0x7b, 0x34, 0x40,
    /* U+00F7 "" (7x8) */
    0x30, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x18,
    /* U+0394 "" (7x10) */
    0x38, 0x78, 0xf3, 0x66, 0xcc, 0xf9, 0xe3, 0xff, 0xfc,
    /* U+03A9 "" (7x10) */
    0x3c, 0xff, 0x1e, 0x3c, 0x78, 0xf1, 0xb6, 0x29, 0xdc,
    /* U+03BC "" (7x10) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x7f, 0xfd, 0xe0, 0xc1, 0x80,
    /* U+03C0 "" (8x7) */
    0xff, 0xff, 0x66, 0x66, 0x66, 0x67, 0x63,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 134, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 134, .box_w = 2, .box_h = 11, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 134, .box_w = 5, .box_h = 5, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 7, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 18, .adv_w = 134, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 31, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 42, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 53, .adv_w = 134, .box_w = 2, .box_h = 5, .ofs_x = 3, .ofs_y = 6},
    {.bitmap_index = 55, .adv_w = 134, .box_w = 5, .box_h = 13, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 64, .adv_w = 134, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 73, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 81, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 88, .adv_w = 134, .box_w = 4, .box_h = 5, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 91, .adv_w = 134, .box_w = 4, .box_h = 1, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 92, .adv_w = 134, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 134, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 105, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 116, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 126, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 136, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 134, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 159, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 189, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 209, .adv_w = 134, .box_w = 3, .box_h = 8, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 212, .adv_w = 134, .box_w = 3, .box_h = 10, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 216, .adv_w = 134, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 223, .adv_w = 134, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 228, .adv_w = 134, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 235, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 245, .adv_w = 134, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 256, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 267, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 277, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 297, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 306, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 326, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 336, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 345, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 364, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 374, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 384, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 394, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 405, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 415, .adv_w = 134, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 429, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 439, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 460, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 470, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 481, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 492, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 503, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 514, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 524, .adv_w = 134, .box_w = 5, .box_h = 13, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 533, .adv_w = 134, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 544, .adv_w = 134, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 553, .adv_w = 134, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 559, .adv_w = 134, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 560, .adv_w = 134, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 9},
    {.bitmap_index = 562, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 569, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 579, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 585, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 595, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 602, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 612, .adv_w = 134, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 623, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 633, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 643, .adv_w = 134, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 652, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 662, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 672, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 680, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 687, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 694, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 704, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 714, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 721, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 727, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 737, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 744, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 751, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 759, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 766, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 777, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 783, .adv_w = 134, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 795, .adv_w = 134, .box_w = 2, .box_h = 13, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 799, .adv_w = 134, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 811, .adv_w = 134, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 815, .adv_w = 134, .box_w = 6, .box_h = 5, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 819, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 828, .adv_w = 134, .box_w = 4, .box_h = 5, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 831, .adv_w = 134, .box_w = 4, .box_h = 5, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 834, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 843, .adv_w = 134, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 3},
    {.bitmap_index = 845, .adv_w = 134, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 851, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 858, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 867, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 876, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 885, .adv_w = 134, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x0005, 0x0007, 0x0027, 0x0047, 0x02e4, 0x02f9,
    0x030c, 0x0310,
};

static const lv_font_fmt_txt_cmap_t cmaps[] = {
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 176, .range_length = 785, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 12, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
const lv_font_t humid1_font_plex_mono_bold_14 = {
#else
lv_font_t humid1_font_plex_mono_bold_14 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 19,
    .base_line = 4,
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_font_plex_sans_bold_14,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_MONO_BOLD_14 */
