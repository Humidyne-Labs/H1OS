/*******************************************************************************
 * Font: humid1_font_plex_mono_normal_14 (IBM Plex Mono Normal)
 * Size: 14 px @ 188 DPI (SSD1681 1-bit E-Paper Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Raster Mode: autohint-mono (FT_LOAD_TARGET_MONO + Dropout Control)
 * License: SIL Open Font License 1.1 (IBM Corp.) / Font Awesome Free License
 ******************************************************************************/

#include "lvgl.h"

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
    /* U+0021 "!" (2x11) */
    0x55, 0x54, 0x3c,
    /* U+0022 "" (4x4) */
    0x99, 0x99,
    /* U+0023 "#" (8x11) */
    0x14, 0x14, 0x14, 0x14, 0x67, 0x24, 0x24, 0xee, 0x28, 0x28, 0x28,
    /* U+0024 "$" (7x15) */
    0x10, 0x21, 0xf6, 0xb9, 0x12, 0x34, 0x3e, 0x16, 0x26, 0x4e, 0xb7, 0xc2,
    0x04, 0x00,
    /* U+0025 "%" (8x11) */
    0x61, 0x92, 0x92, 0x92, 0x94, 0x60, 0x06, 0x29, 0x49, 0x49, 0x86,
    /* U+0026 "&" (8x11) */
    0x38, 0x44, 0x40, 0x40, 0x60, 0x73, 0x9a, 0x8a, 0x84, 0xca, 0x7b,
    /* U+0027 "'" (1x4) */
    0xf0,
    /* U+0028 "(" (4x14) */
    0x22, 0x48, 0x88, 0x88, 0x88, 0x44, 0x21,
    /* U+0029 ")" (4x14) */
    0x44, 0x22, 0x11, 0x11, 0x11, 0x22, 0x48,
    /* U+002A "" (7x7) */
    0x10, 0x22, 0x4f, 0xf1, 0x05, 0x11, 0x00,
    /* U+002B "+" (7x7) */
    0x10, 0x20, 0x47, 0xf1, 0x02, 0x04, 0x00,
    /* U+002C "," (2x4) */
    0xfa,
    /* U+002D "-" (4x1) */
    0xf0,
    /* U+002E "." (2x2) */
    0xf0,
    /* U+002F "/" (6x14) */
    0x04, 0x10, 0x82, 0x18, 0x41, 0x08, 0x20, 0x84, 0x10, 0x42, 0x00,
    /* U+0030 "0" (7x11) */
    0x38, 0x8a, 0x0c, 0x18, 0x32, 0x64, 0xc1, 0x82, 0x88, 0xe0,
    /* U+0031 "1" (7x11) */
    0x30, 0xa2, 0x40, 0x81, 0x02, 0x04, 0x08, 0x10, 0x23, 0xf8,
    /* U+0032 "2" (7x11) */
    0x79, 0x9a, 0x10, 0x20, 0x41, 0x06, 0x18, 0x61, 0x83, 0xf8,
    /* U+0033 "3" (6x11) */
    0x79, 0x10, 0x41, 0x0c, 0xc0, 0xc1, 0x07, 0x37, 0x80,
    /* U+0034 "4" (8x11) */
    0x0c, 0x0c, 0x14, 0x34, 0x24, 0x44, 0x44, 0x84, 0xff, 0x04, 0x04,
    /* U+0035 "5" (6x11) */
    0xfe, 0x08, 0x20, 0xbb, 0x30, 0x41, 0x06, 0x27, 0x80,
    /* U+0036 "6" (7x11) */
    0x18, 0x61, 0x82, 0x0b, 0xd8, 0xe0, 0xc1, 0x82, 0x88, 0xe0,
    /* U+0037 "7" (7x11) */
    0xff, 0x0a, 0x10, 0x60, 0x81, 0x04, 0x08, 0x30, 0x40, 0x80,
    /* U+0038 "8" (7x11) */
    0x79, 0x9a, 0x14, 0x2c, 0xc6, 0x33, 0x41, 0x83, 0x8d, 0xf0,
    /* U+0039 "9" (7x11) */
    0x38, 0x8a, 0x0c, 0x18, 0x38, 0xde, 0x82, 0x0c, 0x30, 0xc0,
    /* U+003A ":" (2x8) */
    0xf0, 0x0f,
    /* U+003B ";" (2x10) */
    0xf0, 0x0f, 0xa0,
    /* U+003C "<" (6x8) */
    0x04, 0x33, 0x30, 0x81, 0x83, 0x03,
    /* U+003D "=" (7x4) */
    0xfe, 0x00, 0x07, 0xf0,
    /* U+003E ">" (6x8) */
    0x83, 0x03, 0x03, 0x04, 0x63, 0x30,
    /* U+003F "?" (5x11) */
    0x76, 0x62, 0x11, 0x98, 0x80, 0x01, 0x8c,
    /* U+0040 "@" (6x13) */
    0x39, 0x38, 0x67, 0xa6, 0x9a, 0x69, 0xa6, 0x78, 0x10, 0x38,
    /* U+0041 "A" (7x11) */
    0x30, 0x60, 0xa3, 0x44, 0x89, 0x11, 0x7e, 0x85, 0x0e, 0x08,
    /* U+0042 "B" (6x11) */
    0xfa, 0x18, 0x61, 0x87, 0xe8, 0x61, 0x86, 0x1f, 0x80,
    /* U+0043 "C" (6x11) */
    0x39, 0x18, 0x60, 0x82, 0x08, 0x20, 0x85, 0x13, 0x80,
    /* U+0044 "D" (6x11) */
    0xf2, 0x28, 0x61, 0x86, 0x18, 0x61, 0x86, 0x2f, 0x00,
    /* U+0045 "E" (6x11) */
    0xfe, 0x08, 0x20, 0x83, 0xf8, 0x20, 0x82, 0x0f, 0xc0,
    /* U+0046 "F" (6x11) */
    0xfe, 0x08, 0x20, 0x83, 0xf8, 0x20, 0x82, 0x08, 0x00,
    /* U+0047 "G" (6x11) */
    0x39, 0x38, 0x60, 0x82, 0x09, 0xe1, 0x85, 0x37, 0x40,
    /* U+0048 "H" (6x11) */
    0x86, 0x18, 0x61, 0x87, 0xf8, 0x61, 0x86, 0x18, 0x40,
    /* U+0049 "I" (6x11) */
    0xfc, 0x41, 0x04, 0x10, 0x41, 0x04, 0x10, 0x4f, 0xc0,
    /* U+004A "J" (5x11) */
    0xf8, 0x42, 0x10, 0x84, 0x21, 0x8c, 0xdc,
    /* U+004B "K" (6x11) */
    0x86, 0x39, 0xa4, 0xa3, 0xcd, 0x26, 0x8a, 0x18, 0x40,
    /* U+004C "L" (6x11) */
    0x82, 0x08, 0x20, 0x82, 0x08, 0x20, 0x82, 0x0f, 0xc0,
    /* U+004D "M" (6x11) */
    0xcf, 0x3c, 0xed, 0xb6, 0xda, 0x61, 0x86, 0x18, 0x40,
    /* U+004E "N" (6x11) */
    0xc7, 0x1c, 0x69, 0xa6, 0xd9, 0x65, 0x8e, 0x38, 0xc0,
    /* U+004F "O" (7x11) */
    0x38, 0x8a, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x82, 0x88, 0xe0,
    /* U+0050 "P" (6x11) */
    0xfa, 0x18, 0x61, 0x87, 0xe8, 0x20, 0x82, 0x08, 0x00,
    /* U+0051 "Q" (7x13) */
    0x38, 0x8a, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x82, 0xd8, 0xe0, 0x81, 0xc0,
    /* U+0052 "R" (6x11) */
    0xfa, 0x18, 0x61, 0x87, 0xe9, 0x24, 0x8a, 0x28, 0x40,
    /* U+0053 "S" (7x11) */
    0x7d, 0x8e, 0x04, 0x0c, 0x0f, 0x81, 0x81, 0x83, 0x8d, 0xf0,
    /* U+0054 "T" (8x11) */
    0xff, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    /* U+0055 "U" (6x11) */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x61, 0x87, 0x37, 0x80,
    /* U+0056 "V" (7x11) */
    0x83, 0x0e, 0x16, 0x24, 0x49, 0x12, 0x34, 0x28, 0x60, 0xc0,
    /* U+0057 "W" (8x11) */
    0xc1, 0x41, 0x41, 0x59, 0x59, 0x5a, 0x56, 0x56, 0x66, 0x66, 0x66,
    /* U+0058 "X" (7x11) */
    0x87, 0x89, 0x33, 0x43, 0x06, 0x0e, 0x34, 0x4d, 0x8a, 0x18,
    /* U+0059 "Y" (7x11) */
    0x83, 0x8d, 0x13, 0x62, 0x87, 0x04, 0x08, 0x10, 0x20, 0x40,
    /* U+005A "Z" (7x11) */
    0xfe, 0x0c, 0x10, 0x41, 0x82, 0x08, 0x10, 0x41, 0x03, 0xf8,
    /* U+005B "[" (4x14) */
    0xf8, 0x88, 0x88, 0x88, 0x88, 0x88, 0x8f,
    /* U+005C "" (6x14) */
    0x81, 0x04, 0x08, 0x20, 0x81, 0x04, 0x10, 0x20, 0x82, 0x04, 0x10,
    /* U+005D "]" (4x14) */
    0xf1, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1f,
    /* U+005E "^" (7x6) */
    0x30, 0x71, 0x22, 0x68, 0x50, 0xc0,
    /* U+005F "_" (7x1) */
    0xfe,
    /* U+0060 "`" (2x3) */
    0xa4,
    /* U+0061 "a" (7x8) */
    0x79, 0x08, 0x13, 0xe8, 0x50, 0xa3, 0x3b,
    /* U+0062 "b" (6x11) */
    0x82, 0x08, 0x2e, 0xce, 0x18, 0x61, 0x86, 0x3f, 0x80,
    /* U+0063 "c" (6x8) */
    0x79, 0x38, 0x20, 0x82, 0x04, 0xde,
    /* U+0064 "d" (6x11) */
    0x04, 0x10, 0x5d, 0xce, 0x18, 0x61, 0x87, 0x17, 0xc0,
    /* U+0065 "e" (6x8) */
    0x79, 0x38, 0x7f, 0x82, 0x04, 0xde,
    /* U+0066 "f" (6x11) */
    0x1c, 0x41, 0x3f, 0x10, 0x41, 0x04, 0x10, 0x4f, 0xc0,
    /* U+0067 "g" (7x12) */
    0x06, 0x71, 0x12, 0x24, 0x47, 0x10, 0x20, 0x7d, 0x06, 0x0b, 0xe0,
    /* U+0068 "h" (6x11) */
    0x82, 0x08, 0x2e, 0xce, 0x18, 0x61, 0x86, 0x18, 0x40,
    /* U+0069 "i" (6x11) */
    0x30, 0xc0, 0x3c, 0x10, 0x41, 0x04, 0x10, 0x4f, 0xc0,
    /* U+006A "j" (5x14) */
    0x18, 0xc1, 0xe1, 0x08, 0x42, 0x10, 0x84, 0x21, 0x78,
    /* U+006B "k" (6x11) */
    0x82, 0x08, 0x23, 0x9a, 0xce, 0x34, 0x9a, 0x28, 0x40,
    /* U+006C "l" (6x11) */
    0xf0, 0x41, 0x04, 0x10, 0x41, 0x04, 0x10, 0x4f, 0xc0,
    /* U+006D "m" (7x8) */
    0xff, 0x26, 0x4c, 0x99, 0x32, 0x64, 0xc9,
    /* U+006E "n" (6x8) */
    0xbb, 0x38, 0x61, 0x86, 0x18, 0x61,
    /* U+006F "o" (6x8) */
    0x79, 0x28, 0x61, 0x86, 0x14, 0x9e,
    /* U+0070 "p" (6x11) */
    0xbb, 0x38, 0x61, 0x86, 0x18, 0xfe, 0x82, 0x08, 0x00,
    /* U+0071 "q" (6x11) */
    0x77, 0x38, 0x61, 0x86, 0x1c, 0x5f, 0x04, 0x10, 0x40,
    /* U+0072 "r" (6x8) */
    0xec, 0xc2, 0x08, 0x20, 0x82, 0x3e,
    /* U+0073 "s" (6x8) */
    0x7a, 0x18, 0x38, 0x1c, 0x18, 0x5e,
    /* U+0074 "t" (7x11) */
    0x20, 0x40, 0x87, 0xf2, 0x04, 0x08, 0x10, 0x20, 0x40, 0xf8,
    /* U+0075 "u" (6x8) */
    0x86, 0x18, 0x61, 0x86, 0x1c, 0x5f,
    /* U+0076 "v" (6x8) */
    0x86, 0x14, 0x52, 0x48, 0xa3, 0x0c,
    /* U+0077 "w" (8x8) */
    0x99, 0x59, 0x59, 0x59, 0x56, 0x66, 0x66, 0x66,
    /* U+0078 "x" (6x8) */
    0xc5, 0x22, 0x8c, 0x31, 0xa4, 0xe1,
    /* U+0079 "y" (6x11) */
    0x86, 0x14, 0xd2, 0x48, 0xc3, 0x0c, 0x20, 0x8c, 0x00,
    /* U+007A "z" (6x8) */
    0xfc, 0x30, 0x84, 0x21, 0x0c, 0x3f,
    /* U+007B "{" (5x14) */
    0x39, 0x08, 0x41, 0x0b, 0x82, 0x10, 0x88, 0x42, 0x1c,
    /* U+007C "|" (1x14) */
    0xff, 0xfc,
    /* U+007D "}" (5x14) */
    0xe1, 0x08, 0x44, 0x20, 0xe8, 0x42, 0x08, 0x42, 0x70,
    /* U+007E "~" (7x3) */
    0x63, 0x2a, 0x70,
    /* U+00B0 "" (5x5) */
    0x74, 0x63, 0x17, 0x00,
    /* U+00B1 "" (7x9) */
    0x10, 0x20, 0x47, 0xf1, 0x02, 0x04, 0x00, 0xfe,
    /* U+00B2 "" (4x5) */
    0x71, 0x24, 0xf0,
    /* U+00B3 "" (3x5) */
    0xe7, 0x1e,
    /* U+00B5 "" (6x10) */
    0x86, 0x18, 0x61, 0x86, 0x1f, 0xe0, 0x82, 0x00,
    /* U+00B7 "" (2x2) */
    0xf0,
    /* U+00D7 "" (5x7) */
    0x0c, 0xdc, 0xcd, 0x4c, 0x20,
    /* U+00F7 "" (7x8) */
    0x10, 0x20, 0x00, 0x0f, 0xe0, 0x04, 0x08,
    /* U+0394 "" (7x10) */
    0x18, 0x50, 0xa1, 0x46, 0x48, 0x91, 0x63, 0x83, 0xfc,
    /* U+03A9 "" (6x10) */
    0x7b, 0x28, 0x61, 0x86, 0x18, 0x62, 0x5b, 0x70,
    /* U+03BC "" (6x10) */
    0x86, 0x18, 0x61, 0x86, 0x1f, 0xe0, 0x82, 0x00,
    /* U+03C0 "" (7x7) */
    0xfe, 0x89, 0x12, 0x24, 0x48, 0x91, 0x80,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 134, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 134, .box_w = 2, .box_h = 11, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 134, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 5, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 16, .adv_w = 134, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 30, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 41, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 134, .box_w = 1, .box_h = 4, .ofs_x = 4, .ofs_y = 7},
    {.bitmap_index = 53, .adv_w = 134, .box_w = 4, .box_h = 14, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 60, .adv_w = 134, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 67, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 74, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 81, .adv_w = 134, .box_w = 2, .box_h = 4, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 82, .adv_w = 134, .box_w = 4, .box_h = 1, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 83, .adv_w = 134, .box_w = 2, .box_h = 2, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 84, .adv_w = 134, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 95, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 145, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 154, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 164, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 184, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 134, .box_w = 2, .box_h = 8, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 196, .adv_w = 134, .box_w = 2, .box_h = 10, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 199, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 205, .adv_w = 134, .box_w = 7, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 209, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 215, .adv_w = 134, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 222, .adv_w = 134, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 232, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 242, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 260, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 269, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 278, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 296, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 305, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 314, .adv_w = 134, .box_w = 5, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 321, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 330, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 348, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 357, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 367, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 134, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 388, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 397, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 407, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 418, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 427, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 437, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 448, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 458, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 468, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 478, .adv_w = 134, .box_w = 4, .box_h = 14, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 485, .adv_w = 134, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 496, .adv_w = 134, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 503, .adv_w = 134, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 509, .adv_w = 134, .box_w = 7, .box_h = 1, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 510, .adv_w = 134, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = 9},
    {.bitmap_index = 511, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 518, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 527, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 533, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 542, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 548, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 557, .adv_w = 134, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 568, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 577, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 586, .adv_w = 134, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 595, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 604, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 613, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 620, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 626, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 632, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 641, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 650, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 656, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 662, .adv_w = 134, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 672, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 678, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 684, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 692, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 698, .adv_w = 134, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 707, .adv_w = 134, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 713, .adv_w = 134, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 722, .adv_w = 134, .box_w = 1, .box_h = 14, .ofs_x = 4, .ofs_y = -3},
    {.bitmap_index = 724, .adv_w = 134, .box_w = 5, .box_h = 14, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 733, .adv_w = 134, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 736, .adv_w = 134, .box_w = 5, .box_h = 5, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 740, .adv_w = 134, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 748, .adv_w = 134, .box_w = 4, .box_h = 5, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 751, .adv_w = 134, .box_w = 3, .box_h = 5, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 753, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 761, .adv_w = 134, .box_w = 2, .box_h = 2, .ofs_x = 3, .ofs_y = 4},
    {.bitmap_index = 762, .adv_w = 134, .box_w = 5, .box_h = 7, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 767, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 774, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 783, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 791, .adv_w = 134, .box_w = 6, .box_h = 10, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 799, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0}
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
const lv_font_t humid1_font_plex_mono_normal_14 = {
#else
lv_font_t humid1_font_plex_mono_normal_14 = {
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
    .fallback = &humid1_font_plex_sans_normal_14,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_MONO_NORMAL_14 */
