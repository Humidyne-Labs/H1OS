/*******************************************************************************
 * Font: humid1_font_plex_mono_normal_12 (IBM Plex Mono Normal)
 * Size: 12 px @ 188 DPI (SSD1681 1-bit E-Paper Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Raster Mode: autohint-mono (FT_LOAD_TARGET_MONO + Dropout Control)
 * License: SIL Open Font License 1.1 (IBM Corp.) / Font Awesome Free License
 ******************************************************************************/

#include "lvgl.h"

#ifndef HUMID1_FONT_PLEX_MONO_NORMAL_12
#define HUMID1_FONT_PLEX_MONO_NORMAL_12 1
#endif

#if HUMID1_FONT_PLEX_MONO_NORMAL_12

extern const lv_font_t humid1_font_plex_sans_normal_12;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (2x8) */
    0xaa, 0x83,
    /* U+0022 "" (3x3) */
    0xb6, 0x80,
    /* U+0023 "#" (7x8) */
    0x14, 0x49, 0x99, 0x42, 0x9d, 0xd2, 0x24,
    /* U+0024 "$" (6x11) */
    0x20, 0x8f, 0xa8, 0xa1, 0xc2, 0xc9, 0xa7, 0xe2, 0x00,
    /* U+0025 "%" (7x8) */
    0x63, 0x2a, 0x63, 0x00, 0xc6, 0x54, 0xc6,
    /* U+0026 "&" (6x8) */
    0x71, 0x04, 0x1b, 0x9a, 0x68, 0x9d,
    /* U+0027 "'" (1x3) */
    0xe0,
    /* U+0028 "(" (3x10) */
    0x2a, 0x49, 0x24, 0x44,
    /* U+0029 ")" (3x10) */
    0x89, 0x12, 0x4a, 0x50,
    /* U+002A "" (7x5) */
    0x10, 0x23, 0xf8, 0x82, 0x80,
    /* U+002B "+" (5x5) */
    0x21, 0x3e, 0x42, 0x00,
    /* U+002C "," (2x3) */
    0x58,
    /* U+002D "-" (3x1) */
    0xe0,
    /* U+002E "." (2x1) */
    0xc0,
    /* U+002F "/" (5x10) */
    0x08, 0x44, 0x22, 0x11, 0x08, 0x44, 0x00,
    /* U+0030 "0" (6x8) */
    0x7b, 0x38, 0x69, 0x86, 0x1c, 0xde,
    /* U+0031 "1" (5x8) */
    0x65, 0x08, 0x42, 0x10, 0x9f,
    /* U+0032 "2" (5x8) */
    0x74, 0x42, 0x11, 0x13, 0x1f,
    /* U+0033 "3" (5x8) */
    0x74, 0x42, 0xe0, 0x86, 0x3e,
    /* U+0034 "4" (6x8) */
    0x18, 0x62, 0x92, 0x4a, 0x2f, 0xc2,
    /* U+0035 "5" (5x8) */
    0xfc, 0x21, 0xe8, 0x86, 0x3e,
    /* U+0036 "6" (6x8) */
    0x31, 0x84, 0x2e, 0xc6, 0x18, 0x5e,
    /* U+0037 "7" (6x8) */
    0xfe, 0x20, 0x84, 0x10, 0xc2, 0x08,
    /* U+0038 "8" (6x8) */
    0x7a, 0x18, 0x5e, 0xce, 0x18, 0x5e,
    /* U+0039 "9" (6x8) */
    0x7a, 0x18, 0x61, 0x7c, 0x21, 0x8c,
    /* U+003A ":" (2x6) */
    0xc0, 0x30,
    /* U+003B ";" (2x7) */
    0xc0, 0xe8,
    /* U+003C "<" (5x6) */
    0x1b, 0x20, 0xc1, 0x04,
    /* U+003D "=" (5x3) */
    0xf8, 0x3e,
    /* U+003E ">" (5x6) */
    0xc1, 0x82, 0x64, 0x40,
    /* U+003F "?" (4x8) */
    0xe9, 0x11, 0x64, 0x06,
    /* U+0040 "@" (6x9) */
    0x7b, 0x19, 0xe9, 0xa6, 0x99, 0xf0, 0x78,
    /* U+0041 "A" (6x8) */
    0x21, 0x45, 0x14, 0xcb, 0xe8, 0xa1,
    /* U+0042 "B" (5x8) */
    0xf4, 0x63, 0xe8, 0xc6, 0x3e,
    /* U+0043 "C" (5x8) */
    0x7e, 0x61, 0x08, 0x43, 0x2f,
    /* U+0044 "D" (5x8) */
    0xf4, 0xe3, 0x18, 0xc6, 0x7e,
    /* U+0045 "E" (5x8) */
    0xfc, 0x21, 0xf8, 0x42, 0x1f,
    /* U+0046 "F" (5x8) */
    0xfc, 0x21, 0xf8, 0x42, 0x10,
    /* U+0047 "G" (6x8) */
    0x7b, 0x18, 0x20, 0x9e, 0x1c, 0x5f,
    /* U+0048 "H" (5x8) */
    0x8c, 0x63, 0xf8, 0xc6, 0x31,
    /* U+0049 "I" (5x8) */
    0xf9, 0x08, 0x42, 0x10, 0x9f,
    /* U+004A "J" (5x8) */
    0x78, 0x42, 0x10, 0x86, 0x2e,
    /* U+004B "K" (6x8) */
    0x8a, 0x6b, 0x28, 0xf2, 0x48, 0xa3,
    /* U+004C "L" (5x8) */
    0x84, 0x21, 0x08, 0x42, 0x1f,
    /* U+004D "M" (6x8) */
    0xcf, 0x3d, 0x6d, 0xa6, 0x18, 0x61,
    /* U+004E "N" (5x8) */
    0xce, 0x73, 0x5a, 0xce, 0x73,
    /* U+004F "O" (6x8) */
    0x7b, 0x38, 0x61, 0x86, 0x1c, 0xde,
    /* U+0050 "P" (5x8) */
    0xf4, 0x63, 0x1f, 0x42, 0x10,
    /* U+0051 "Q" (6x10) */
    0x7b, 0x38, 0x61, 0x86, 0x18, 0x9e, 0x20, 0xe0,
    /* U+0052 "R" (5x8) */
    0xf4, 0x63, 0x1f, 0x5a, 0x51,
    /* U+0053 "S" (6x8) */
    0x7a, 0x18, 0x10, 0x3c, 0x18, 0x5e,
    /* U+0054 "T" (7x8) */
    0xfe, 0x20, 0x40, 0x81, 0x02, 0x04, 0x08,
    /* U+0055 "U" (5x8) */
    0x8c, 0x63, 0x18, 0xc6, 0x2e,
    /* U+0056 "V" (6x8) */
    0x86, 0x28, 0x92, 0x51, 0x45, 0x08,
    /* U+0057 "W" (6x8) */
    0x86, 0x1b, 0x6d, 0xb7, 0x5d, 0x72,
    /* U+0058 "X" (6x8) */
    0x8b, 0x25, 0x0c, 0x31, 0x48, 0xa3,
    /* U+0059 "Y" (7x8) */
    0xc6, 0x88, 0xa1, 0x41, 0x02, 0x04, 0x08,
    /* U+005A "Z" (6x8) */
    0xfc, 0x30, 0x84, 0x21, 0x0c, 0x3f,
    /* U+005B "[" (4x11) */
    0xf8, 0x88, 0x88, 0x88, 0x88, 0xf0,
    /* U+005C "" (5x10) */
    0x82, 0x10, 0x82, 0x10, 0x42, 0x18, 0x40,
    /* U+005D "]" (4x11) */
    0xf1, 0x11, 0x11, 0x11, 0x11, 0xf0,
    /* U+005E "^" (5x4) */
    0x22, 0x93, 0x10,
    /* U+005F "_" (5x1) */
    0xf8,
    /* U+0060 "`" (2x2) */
    0x90,
    /* U+0061 "a" (6x6) */
    0x70, 0x27, 0xa2, 0x89, 0xf0,
    /* U+0062 "b" (5x8) */
    0x84, 0x2d, 0x98, 0xc6, 0x3e,
    /* U+0063 "c" (5x6) */
    0x74, 0x61, 0x08, 0xb8,
    /* U+0064 "d" (5x8) */
    0x08, 0x5b, 0x38, 0xc6, 0x2f,
    /* U+0065 "e" (6x6) */
    0x7a, 0x1f, 0xe0, 0xc5, 0xe0,
    /* U+0066 "f" (5x8) */
    0x39, 0x3e, 0x42, 0x10, 0x9f,
    /* U+0067 "g" (6x9) */
    0x0d, 0xc8, 0xa2, 0x72, 0x0f, 0xa1, 0xf8,
    /* U+0068 "h" (5x8) */
    0x84, 0x2d, 0x98, 0xc6, 0x31,
    /* U+0069 "i" (5x8) */
    0x20, 0x38, 0x42, 0x10, 0x9f,
    /* U+006A "j" (4x10) */
    0x10, 0xf1, 0x11, 0x11, 0x1f,
    /* U+006B "k" (5x8) */
    0x84, 0x23, 0x6e, 0x4a, 0x71,
    /* U+006C "l" (5x8) */
    0xe1, 0x08, 0x42, 0x10, 0x9f,
    /* U+006D "m" (5x6) */
    0xfd, 0x6b, 0x5a, 0xd4,
    /* U+006E "n" (5x6) */
    0xb6, 0x63, 0x18, 0xc4,
    /* U+006F "o" (6x6) */
    0x7a, 0x18, 0x61, 0x85, 0xe0,
    /* U+0070 "p" (5x8) */
    0xb6, 0x63, 0x18, 0xfa, 0x10,
    /* U+0071 "q" (5x8) */
    0x6c, 0xe3, 0x18, 0xbc, 0x21,
    /* U+0072 "r" (6x6) */
    0xec, 0xc2, 0x08, 0x23, 0xe0,
    /* U+0073 "s" (5x6) */
    0x74, 0x20, 0xf8, 0xb8,
    /* U+0074 "t" (6x8) */
    0x20, 0x8f, 0xc8, 0x20, 0x82, 0x0f,
    /* U+0075 "u" (5x6) */
    0x8c, 0x63, 0x18, 0xbc,
    /* U+0076 "v" (5x6) */
    0x8c, 0x52, 0xa5, 0x10,
    /* U+0077 "w" (7x6) */
    0x93, 0x65, 0xb3, 0x66, 0xcc, 0x80,
    /* U+0078 "x" (5x6) */
    0x8a, 0x8c, 0x65, 0x44,
    /* U+0079 "y" (5x8) */
    0x8c, 0x54, 0xa3, 0x10, 0x98,
    /* U+007A "z" (5x6) */
    0xf8, 0xcc, 0xcc, 0x7c,
    /* U+007B "{" (5x11) */
    0x39, 0x08, 0x21, 0x70, 0x42, 0x21, 0x0e,
    /* U+007C "|" (1x10) */
    0xff, 0xc0,
    /* U+007D "}" (5x11) */
    0xe1, 0x08, 0x84, 0x1d, 0x08, 0x21, 0x38,
    /* U+007E "~" (6x3) */
    0xc6, 0xa1, 0x80,
    /* U+00B0 "" (4x4) */
    0x69, 0x96,
    /* U+00B1 "" (5x7) */
    0x21, 0x3e, 0x42, 0x03, 0xe0,
    /* U+00B2 "" (4x4) */
    0x71, 0x6f,
    /* U+00B3 "" (3x4) */
    0xe8, 0xf0,
    /* U+00B5 "" (5x8) */
    0x8c, 0x63, 0x18, 0xfe, 0x10,
    /* U+00B7 "" (2x1) */
    0xc0,
    /* U+00D7 "" (5x5) */
    0x8a, 0x88, 0xa8, 0x80,
    /* U+00F7 "" (5x6) */
    0x20, 0x01, 0xf0, 0x10,
    /* U+0394 "" (6x8) */
    0x30, 0xc2, 0x92, 0x49, 0x18, 0x7f,
    /* U+03A9 "" (6x8) */
    0x7a, 0x38, 0x61, 0x86, 0x14, 0xb7,
    /* U+03BC "" (5x8) */
    0x8c, 0x63, 0x18, 0xfe, 0x10,
    /* U+03C0 "" (6x6) */
    0xfd, 0x24, 0x92, 0x49, 0x30,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 115, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 115, .box_w = 2, .box_h = 8, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 115, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 4, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 11, .adv_w = 115, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 20, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 27, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 33, .adv_w = 115, .box_w = 1, .box_h = 3, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 34, .adv_w = 115, .box_w = 3, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 38, .adv_w = 115, .box_w = 3, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 42, .adv_w = 115, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 47, .adv_w = 115, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 51, .adv_w = 115, .box_w = 2, .box_h = 3, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 52, .adv_w = 115, .box_w = 3, .box_h = 1, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 53, .adv_w = 115, .box_w = 2, .box_h = 1, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 54, .adv_w = 115, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 61, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 67, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 72, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 77, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 82, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 93, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 99, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 115, .box_w = 2, .box_h = 6, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 115, .box_w = 2, .box_h = 7, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 121, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 115, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 127, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 131, .adv_w = 115, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 135, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 142, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 148, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 153, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 158, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 163, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 173, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 184, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 189, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 200, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 222, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 227, .adv_w = 115, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 235, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 240, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 246, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 253, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 258, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 270, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 276, .adv_w = 115, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 283, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 289, .adv_w = 115, .box_w = 4, .box_h = 11, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 295, .adv_w = 115, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 302, .adv_w = 115, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 308, .adv_w = 115, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 311, .adv_w = 115, .box_w = 5, .box_h = 1, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 312, .adv_w = 115, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 313, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 318, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 323, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 332, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 337, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 342, .adv_w = 115, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 349, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 359, .adv_w = 115, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 364, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 369, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 374, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 378, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 382, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 387, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 392, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 397, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 402, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 406, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 412, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 416, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 420, .adv_w = 115, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 426, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 430, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 435, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 439, .adv_w = 115, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 446, .adv_w = 115, .box_w = 1, .box_h = 10, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 448, .adv_w = 115, .box_w = 5, .box_h = 11, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 455, .adv_w = 115, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 458, .adv_w = 115, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 460, .adv_w = 115, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 465, .adv_w = 115, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 467, .adv_w = 115, .box_w = 3, .box_h = 4, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 469, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 474, .adv_w = 115, .box_w = 2, .box_h = 1, .ofs_x = 3, .ofs_y = 3},
    {.bitmap_index = 475, .adv_w = 115, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 479, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 483, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 489, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 495, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 500, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0}
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
const lv_font_t humid1_font_plex_mono_normal_12 = {
#else
lv_font_t humid1_font_plex_mono_normal_12 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 17,
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
    .fallback = &humid1_font_plex_sans_normal_12,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_MONO_NORMAL_12 */
