/*******************************************************************************
 * Font: humid1_font_plex_cond_normal_14 (IBM Plex Cond Normal)
 * Size: 14 px @ 188 DPI (SSD1681 1-bit E-Paper Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Raster Mode: autohint-mono (FT_LOAD_TARGET_MONO + Dropout Control)
 * License: SIL Open Font License 1.1 (IBM Corp.) / Font Awesome Free License
 ******************************************************************************/

#include "lvgl.h"

#ifndef HUMID1_FONT_PLEX_COND_NORMAL_14
#define HUMID1_FONT_PLEX_COND_NORMAL_14 1
#endif

#if HUMID1_FONT_PLEX_COND_NORMAL_14

extern const lv_font_t humid1_font_plex_sans_normal_14;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (1x11) */
    0xff, 0x60,
    /* U+0022 "" (3x4) */
    0xb6, 0xd0,
    /* U+0023 "#" (7x11) */
    0x24, 0x48, 0x97, 0xf2, 0x89, 0x12, 0x7f, 0x48, 0x91, 0x20,
    /* U+0024 "$" (5x13) */
    0x23, 0xab, 0x4a, 0x71, 0xc7, 0x2d, 0x6a, 0xe2, 0x00,
    /* U+0025 "%" (10x11) */
    0x61, 0x24, 0x49, 0x22, 0x48, 0x94, 0x1a, 0x60, 0xa4, 0x49, 0x12, 0x48,
    0x92, 0x18,
    /* U+0026 "&" (7x11) */
    0x30, 0x91, 0x22, 0x43, 0x0e, 0xe5, 0x46, 0x8d, 0x19, 0xc8,
    /* U+0027 "'" (1x4) */
    0xf0,
    /* U+0028 "(" (3x14) */
    0x29, 0x49, 0x24, 0x91, 0x26, 0x40,
    /* U+0029 ")" (3x14) */
    0x89, 0x12, 0x49, 0x25, 0x29, 0x00,
    /* U+002A "" (4x5) */
    0x44, 0xf6, 0x90,
    /* U+002B "+" (5x6) */
    0x21, 0x3e, 0x42, 0x10,
    /* U+002C "," (1x4) */
    0xf0,
    /* U+002D "-" (3x1) */
    0xe0,
    /* U+002E "." (1x2) */
    0xc0,
    /* U+002F "/" (4x14) */
    0x11, 0x11, 0x22, 0x22, 0x44, 0x44, 0x88,
    /* U+0030 "0" (6x11) */
    0x79, 0x28, 0x61, 0x86, 0x18, 0x61, 0x85, 0x27, 0x80,
    /* U+0031 "1" (6x11) */
    0x63, 0x8a, 0x08, 0x20, 0x82, 0x08, 0x20, 0x8f, 0xc0,
    /* U+0032 "2" (6x11) */
    0x72, 0x28, 0x82, 0x08, 0x41, 0x08, 0x43, 0x0f, 0xc0,
    /* U+0033 "3" (5x11) */
    0x74, 0x42, 0x10, 0xb8, 0x61, 0x0c, 0x5c,
    /* U+0034 "4" (7x11) */
    0x18, 0x30, 0xa1, 0x44, 0x89, 0x12, 0x44, 0xfe, 0x10, 0x20,
    /* U+0035 "5" (5x11) */
    0xfc, 0x21, 0x0f, 0x4c, 0x21, 0x0c, 0xdc,
    /* U+0036 "6" (6x11) */
    0x10, 0x84, 0x10, 0xbb, 0x38, 0x61, 0x87, 0x37, 0x80,
    /* U+0037 "7" (6x11) */
    0xfe, 0x18, 0xc2, 0x08, 0x41, 0x04, 0x20, 0x82, 0x00,
    /* U+0038 "8" (6x11) */
    0x7a, 0x38, 0x61, 0x85, 0xec, 0xe1, 0x87, 0x37, 0x80,
    /* U+0039 "9" (6x11) */
    0x7b, 0x28, 0x61, 0x87, 0x37, 0x42, 0x08, 0x42, 0x00,
    /* U+003A ":" (1x8) */
    0xc3,
    /* U+003B ";" (1x10) */
    0xc3, 0xc0,
    /* U+003C "<" (6x9) */
    0x04, 0x31, 0x18, 0x83, 0x02, 0x06, 0x0c,
    /* U+003D "=" (6x4) */
    0xfc, 0x00, 0x3f,
    /* U+003E ">" (6x9) */
    0x83, 0x02, 0x06, 0x04, 0x31, 0x18, 0xc0,
    /* U+003F "?" (5x11) */
    0x74, 0x42, 0x11, 0x31, 0x00, 0x02, 0x10,
    /* U+0040 "@" (10x13) */
    0x1e, 0x08, 0x64, 0x0a, 0x79, 0xa2, 0x68, 0x9a, 0x26, 0x89, 0xa2, 0x67,
    0xe4, 0x01, 0x80, 0x1f, 0x00,
    /* U+0041 "A" (8x11) */
    0x18, 0x18, 0x18, 0x24, 0x24, 0x24, 0x26, 0x7e, 0x42, 0x42, 0xc1,
    /* U+0042 "B" (6x11) */
    0xfa, 0x18, 0x61, 0x87, 0xe8, 0x61, 0x86, 0x1f, 0x80,
    /* U+0043 "C" (6x11) */
    0x39, 0x18, 0x60, 0x82, 0x08, 0x20, 0x85, 0x13, 0x80,
    /* U+0044 "D" (7x11) */
    0xf9, 0x0a, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x0b, 0xe0,
    /* U+0045 "E" (5x11) */
    0xfc, 0x21, 0x08, 0x7e, 0x10, 0x84, 0x3e,
    /* U+0046 "F" (5x11) */
    0xfc, 0x21, 0x08, 0x7e, 0x10, 0x84, 0x20,
    /* U+0047 "G" (7x11) */
    0x3c, 0x8e, 0x04, 0x08, 0x11, 0xe0, 0xc1, 0x82, 0x8c, 0xe8,
    /* U+0048 "H" (7x11) */
    0x83, 0x06, 0x0c, 0x18, 0x3f, 0xe0, 0xc1, 0x83, 0x06, 0x08,
    /* U+0049 "I" (4x11) */
    0xf4, 0x44, 0x44, 0x44, 0x44, 0xf0,
    /* U+004A "J" (5x11) */
    0x78, 0x42, 0x10, 0x84, 0x21, 0x0e, 0x5c,
    /* U+004B "K" (6x11) */
    0x86, 0x29, 0xa4, 0xa3, 0x8d, 0x26, 0x8a, 0x38, 0x40,
    /* U+004C "L" (5x11) */
    0x84, 0x21, 0x08, 0x42, 0x10, 0x84, 0x3e,
    /* U+004D "M" (8x11) */
    0xc3, 0xc3, 0xa5, 0xa5, 0xa5, 0x99, 0x99, 0x91, 0x81, 0x81, 0x81,
    /* U+004E "N" (7x11) */
    0xc3, 0x86, 0x8d, 0x1b, 0x32, 0x64, 0xc5, 0x8b, 0x0e, 0x18,
    /* U+004F "O" (7x11) */
    0x38, 0x8a, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x82, 0x88, 0xe0,
    /* U+0050 "P" (6x11) */
    0xfa, 0x18, 0x61, 0x87, 0xe8, 0x20, 0x82, 0x08, 0x00,
    /* U+0051 "Q" (7x13) */
    0x38, 0x8a, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x82, 0xd8, 0xe0, 0x81, 0x80,
    /* U+0052 "R" (6x11) */
    0xfa, 0x18, 0x61, 0x87, 0xe9, 0xa2, 0x8a, 0x18, 0x40,
    /* U+0053 "S" (6x11) */
    0x7a, 0x38, 0x20, 0xc0, 0xe0, 0xc1, 0x86, 0x37, 0x80,
    /* U+0054 "T" (7x11) */
    0xfe, 0x20, 0x40, 0x81, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40,
    /* U+0055 "U" (6x11) */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x61, 0x87, 0x37, 0x80,
    /* U+0056 "V" (7x11) */
    0xc2, 0x85, 0x0a, 0x36, 0x44, 0x89, 0x14, 0x38, 0x30, 0x60,
    /* U+0057 "W" (11x11) */
    0xc6, 0x28, 0xc5, 0x29, 0xa5, 0x24, 0xa4, 0x94, 0x8a, 0x51, 0x4a, 0x31,
    0x86, 0x30, 0xc6, 0x00,
    /* U+0058 "X" (6x11) */
    0x86, 0x34, 0x92, 0x70, 0xc3, 0x1c, 0x4a, 0x38, 0x40,
    /* U+0059 "Y" (7x11) */
    0x82, 0x89, 0x13, 0x62, 0x85, 0x04, 0x08, 0x10, 0x20, 0x40,
    /* U+005A "Z" (6x11) */
    0xfc, 0x30, 0x86, 0x10, 0xc2, 0x10, 0x42, 0x0f, 0xc0,
    /* U+005B "[" (2x14) */
    0xea, 0xaa, 0xaa, 0xb0,
    /* U+005C "" (4x14) */
    0x88, 0x88, 0x44, 0x44, 0x22, 0x22, 0x11,
    /* U+005D "]" (2x14) */
    0xd5, 0x55, 0x55, 0x70,
    /* U+005E "^" (6x6) */
    0x31, 0x44, 0x92, 0x8a, 0x10,
    /* U+005F "_" (6x1) */
    0xfc,
    /* U+0060 "`" (1x2) */
    0xc0,
    /* U+0061 "a" (6x8) */
    0x72, 0x20, 0x9e, 0x8a, 0x29, 0x9b,
    /* U+0062 "b" (6x11) */
    0x82, 0x08, 0x2e, 0xce, 0x18, 0x61, 0x86, 0x2f, 0x80,
    /* U+0063 "c" (5x8) */
    0x76, 0x61, 0x08, 0x42, 0x2e,
    /* U+0064 "d" (6x11) */
    0x04, 0x10, 0x5d, 0xce, 0x18, 0x61, 0x87, 0x17, 0xc0,
    /* U+0065 "e" (6x8) */
    0x79, 0x18, 0x7f, 0x82, 0x0c, 0xde,
    /* U+0066 "f" (4x11) */
    0x74, 0x4f, 0x44, 0x44, 0x44, 0x40,
    /* U+0067 "g" (6x12) */
    0x0d, 0xc8, 0xa2, 0x89, 0xc8, 0x20, 0x7a, 0x18, 0x5e,
    /* U+0068 "h" (5x11) */
    0x84, 0x21, 0x6c, 0xc6, 0x31, 0x8c, 0x62,
    /* U+0069 "i" (1x11) */
    0x9f, 0xe0,
    /* U+006A "j" (2x14) */
    0x41, 0x55, 0x55, 0x70,
    /* U+006B "k" (5x11) */
    0x84, 0x21, 0x19, 0x53, 0x9c, 0x94, 0xe2,
    /* U+006C "l" (2x11) */
    0xaa, 0xaa, 0xac,
    /* U+006D "m" (9x8) */
    0xb3, 0x66, 0x62, 0x31, 0x18, 0x8c, 0x46, 0x23, 0x11,
    /* U+006E "n" (5x8) */
    0xb6, 0x63, 0x18, 0xc6, 0x31,
    /* U+006F "o" (6x8) */
    0x7b, 0x38, 0x61, 0x86, 0x1c, 0xde,
    /* U+0070 "p" (6x11) */
    0xbb, 0x38, 0x61, 0x86, 0x18, 0xbe, 0x82, 0x08, 0x00,
    /* U+0071 "q" (6x11) */
    0x77, 0x38, 0x61, 0x86, 0x1c, 0x5f, 0x04, 0x10, 0x40,
    /* U+0072 "r" (3x8) */
    0xba, 0x49, 0x24,
    /* U+0073 "s" (5x8) */
    0x74, 0x61, 0xc1, 0x86, 0x2e,
    /* U+0074 "t" (4x10) */
    0x44, 0xf4, 0x44, 0x44, 0x47,
    /* U+0075 "u" (5x8) */
    0x8c, 0x63, 0x18, 0xc6, 0x2f,
    /* U+0076 "v" (6x8) */
    0x85, 0x14, 0x92, 0x48, 0xc3, 0x0c,
    /* U+0077 "w" (9x8) */
    0xcc, 0xa6, 0x53, 0x2a, 0x95, 0x52, 0x98, 0xcc, 0x66,
    /* U+0078 "x" (5x8) */
    0x8c, 0x94, 0xc6, 0x2a, 0x51,
    /* U+0079 "y" (6x11) */
    0x85, 0x34, 0x92, 0x48, 0xc3, 0x0c, 0x20, 0x86, 0x00,
    /* U+007A "z" (5x8) */
    0xf8, 0xc4, 0x42, 0x23, 0x1f,
    /* U+007B "{" (3x14) */
    0x69, 0x24, 0xa2, 0x49, 0x24, 0xc0,
    /* U+007C "|" (1x14) */
    0xff, 0xfc,
    /* U+007D "}" (3x14) */
    0xc9, 0x24, 0x8a, 0x49, 0x25, 0x80,
    /* U+007E "~" (6x2) */
    0xe0, 0x70,
    /* U+00B0 "" (4x5) */
    0x69, 0x99, 0x60,
    /* U+00B1 "" (5x9) */
    0x21, 0x09, 0xf2, 0x10, 0x00, 0xf8,
    /* U+00B2 "" (4x5) */
    0x71, 0x24, 0xf0,
    /* U+00B3 "" (3x5) */
    0xe5, 0x1e,
    /* U+00B5 "" (5x11) */
    0x8c, 0x63, 0x18, 0xc6, 0x3f, 0x84, 0x20,
    /* U+00B7 "" (1x2) */
    0xc0,
    /* U+00D7 "" (5x5) */
    0xcb, 0x8c, 0xa8, 0x80,
    /* U+00F7 "" (5x6) */
    0x20, 0x01, 0xf0, 0x10,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 47, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 58, .box_w = 1, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 86, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 4, .adv_w = 143, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 14, .adv_w = 121, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 23, .adv_w = 187, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 37, .adv_w = 140, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 47, .adv_w = 49, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 48, .adv_w = 68, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 54, .adv_w = 68, .box_w = 3, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 60, .adv_w = 93, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 63, .adv_w = 121, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 67, .adv_w = 56, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 68, .adv_w = 81, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 69, .adv_w = 56, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 70, .adv_w = 78, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 77, .adv_w = 121, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 86, .adv_w = 121, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 95, .adv_w = 121, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 121, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 121, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 121, .adv_w = 121, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 128, .adv_w = 121, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 137, .adv_w = 121, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 121, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 155, .adv_w = 121, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 164, .adv_w = 58, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 58, .box_w = 1, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 167, .adv_w = 121, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 121, .box_w = 6, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 177, .adv_w = 121, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 184, .adv_w = 97, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 191, .adv_w = 180, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 208, .adv_w = 130, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 219, .adv_w = 132, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 126, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 237, .adv_w = 136, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 247, .adv_w = 118, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 254, .adv_w = 113, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 261, .adv_w = 140, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 271, .adv_w = 143, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 281, .adv_w = 81, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 103, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 294, .adv_w = 129, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 303, .adv_w = 101, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 310, .adv_w = 164, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 321, .adv_w = 143, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 331, .adv_w = 143, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 341, .adv_w = 123, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 350, .adv_w = 143, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 362, .adv_w = 129, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 371, .adv_w = 118, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 380, .adv_w = 116, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 390, .adv_w = 137, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 399, .adv_w = 123, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 409, .adv_w = 181, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 425, .adv_w = 124, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 434, .adv_w = 120, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 444, .adv_w = 117, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 453, .adv_w = 64, .box_w = 2, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 457, .adv_w = 78, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 464, .adv_w = 64, .box_w = 2, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 468, .adv_w = 121, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 473, .adv_w = 114, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 474, .adv_w = 121, .box_w = 1, .box_h = 2, .ofs_x = 3, .ofs_y = 9},
    {.bitmap_index = 475, .adv_w = 108, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 481, .adv_w = 117, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 490, .adv_w = 102, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 495, .adv_w = 117, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 504, .adv_w = 111, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 510, .adv_w = 66, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 516, .adv_w = 107, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 525, .adv_w = 115, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 532, .adv_w = 51, .box_w = 1, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 534, .adv_w = 51, .box_w = 2, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 538, .adv_w = 107, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 545, .adv_w = 55, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 548, .adv_w = 176, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 557, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 562, .adv_w = 113, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 568, .adv_w = 117, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 577, .adv_w = 117, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 586, .adv_w = 74, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 589, .adv_w = 98, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 594, .adv_w = 71, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 599, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 604, .adv_w = 100, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 610, .adv_w = 156, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 619, .adv_w = 103, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 624, .adv_w = 101, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 633, .adv_w = 94, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 638, .adv_w = 69, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 644, .adv_w = 65, .box_w = 1, .box_h = 14, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 646, .adv_w = 69, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 652, .adv_w = 121, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 654, .adv_w = 95, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 657, .adv_w = 121, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 663, .adv_w = 72, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 666, .adv_w = 72, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 668, .adv_w = 116, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 675, .adv_w = 66, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 676, .adv_w = 121, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 680, .adv_w = 121, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 2}
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
    3, 13, 3, 15, 3, 52, 3, 53, 3, 55, 3, 56, 3, 58, 3, 87,
    3, 88, 3, 89, 3, 90, 3, 91, 6, 3, 6, 8, 6, 11, 7, 53,
    7, 55, 7, 58, 8, 13, 8, 15, 8, 34, 8, 87, 9, 53, 9, 55,
    9, 58, 9, 72, 9, 75, 11, 13, 11, 15, 11, 34, 11, 43, 13, 3,
    13, 8, 13, 11, 13, 32, 13, 36, 13, 40, 13, 48, 13, 50, 13, 53,
    13, 54, 13, 55, 13, 56, 13, 58, 13, 68, 13, 69, 13, 70, 13, 71,
    13, 72, 13, 80, 13, 82, 13, 84, 13, 85, 13, 86, 13, 87, 13, 88,
    13, 90, 13, 98, 13, 99, 14, 53, 14, 57, 14, 58, 15, 3, 15, 8,
    15, 11, 15, 32, 15, 36, 15, 40, 15, 48, 15, 50, 15, 53, 15, 54,
    15, 55, 15, 56, 15, 58, 15, 68, 15, 69, 15, 70, 15, 71, 15, 72,
    15, 80, 15, 82, 15, 84, 15, 85, 15, 86, 15, 87, 15, 88, 15, 90,
    15, 98, 15, 99, 16, 16, 16, 34, 16, 43, 16, 66, 16, 68, 16, 69,
    16, 70, 16, 72, 16, 80, 16, 82, 27, 53, 27, 55, 27, 58, 28, 53,
    28, 55, 28, 58, 32, 13, 32, 15, 32, 56, 34, 3, 34, 8, 34, 11,
    34, 53, 34, 58, 34, 99, 35, 64, 36, 64, 37, 3, 37, 8, 37, 11,
    37, 13, 37, 15, 37, 16, 37, 34, 37, 43, 37, 53, 37, 55, 37, 56,
    37, 57, 37, 58, 37, 59, 37, 64, 37, 98, 37, 99, 39, 13, 39, 15,
    39, 16, 39, 34, 39, 64, 40, 53, 40, 58, 43, 64, 44, 14, 45, 3,
    45, 8, 45, 11, 45, 13, 45, 15, 45, 16, 45, 34, 45, 53, 45, 58,
    45, 59, 45, 64, 45, 89, 45, 91, 45, 98, 48, 13, 48, 15, 48, 64,
    49, 7, 49, 13, 49, 15, 49, 16, 49, 34, 49, 43, 49, 59, 49, 64,
    49, 72, 50, 13, 50, 15, 50, 64, 52, 14, 53, 3, 53, 8, 53, 10,
    53, 11, 53, 13, 53, 15, 53, 16, 53, 34, 53, 53, 53, 58, 53, 64,
    53, 66, 53, 68, 53, 69, 53, 70, 53, 72, 53, 80, 53, 82, 53, 84,
    54, 13, 54, 15, 54, 16, 54, 34, 54, 64, 55, 7, 55, 13, 55, 14,
    55, 15, 55, 16, 55, 27, 55, 28, 55, 33, 55, 34, 55, 36, 55, 40,
    55, 43, 55, 48, 55, 50, 55, 64, 55, 66, 55, 68, 55, 69, 55, 70,
    55, 72, 55, 78, 55, 79, 55, 80, 55, 81, 55, 82, 55, 83, 55, 84,
    55, 86, 56, 3, 56, 8, 56, 10, 56, 11, 56, 32, 56, 98, 57, 14,
    57, 33, 58, 7, 58, 13, 58, 14, 58, 15, 58, 16, 58, 27, 58, 28,
    58, 33, 58, 34, 58, 36, 58, 40, 58, 43, 58, 48, 58, 50, 58, 52,
    58, 64, 58, 66, 58, 67, 58, 68, 58, 69, 58, 70, 58, 71, 58, 72,
    58, 73, 58, 74, 58, 75, 58, 76, 58, 77, 58, 78, 58, 79, 58, 80,
    58, 81, 58, 82, 58, 83, 58, 84, 58, 85, 58, 86, 58, 87, 58, 88,
    58, 89, 58, 90, 58, 91, 59, 13, 59, 15, 59, 64, 59, 91, 64, 36,
    64, 40, 64, 48, 64, 50, 64, 53, 64, 54, 64, 55, 64, 56, 64, 57,
    64, 58, 64, 59, 64, 68, 64, 70, 64, 72, 64, 75, 64, 80, 64, 87,
    66, 3, 66, 8, 66, 11, 66, 53, 66, 55, 66, 58, 67, 53, 68, 16,
    68, 34, 68, 43, 68, 98, 68, 99, 70, 53, 70, 58, 70, 64, 71, 3,
    71, 8, 71, 10, 71, 11, 71, 32, 71, 53, 71, 55, 71, 56, 71, 58,
    71, 64, 71, 98, 71, 99, 73, 53, 76, 14, 76, 53, 76, 58, 76, 98,
    76, 99, 77, 13, 77, 15, 77, 16, 77, 34, 77, 43, 77, 56, 77, 57,
    77, 59, 77, 64, 78, 53, 78, 58, 79, 53, 80, 53, 80, 58, 80, 64,
    81, 53, 83, 7, 83, 13, 83, 15, 83, 16, 83, 34, 83, 43, 83, 64,
    83, 72, 84, 53, 85, 3, 85, 8, 85, 11, 85, 13, 85, 15, 85, 32,
    85, 34, 85, 43, 85, 52, 85, 56, 85, 57, 85, 59, 85, 62, 85, 64,
    85, 87, 85, 90, 85, 91, 85, 94, 85, 98, 85, 99, 87, 3, 87, 8,
    87, 11, 87, 64, 87, 98, 87, 99, 88, 13, 88, 15, 88, 53, 88, 64,
    89, 3, 89, 8, 89, 11, 89, 34, 89, 43, 89, 57, 89, 64, 90, 3,
    90, 8, 90, 11, 90, 13, 90, 15, 90, 64, 90, 98, 90, 99, 91, 53,
    92, 75, 98, 13, 98, 15, 98, 34, 98, 43, 99, 13, 99, 15, 99, 34,
    99, 36, 99, 40, 99, 42, 99, 43, 99, 48, 99, 50, 99, 57, 99, 66,
    99, 68, 99, 69, 99, 70, 99, 72, 99, 80, 99, 82, 99, 99,
};

static const int8_t kern_pair_values[] = {
    -18, -18, 2, 6, 3, 4, 3, 7, 6, 2, 6, 2, -13, -13, -13, -11,
    -7, -11, -18, -18, -11, 7, 4, 4, 4, 4, 11, -18, -18, -11, -7, -18,
    -18, -18, -17, -11, -11, -11, -11, -20, -8, -15, -11, -17, -6, -6, -6, -4,
    -1, -6, -6, -1, -6, -4, -12, -9, -9, -11, -11, -11, -11, -13, -18, -18,
    -18, -17, -11, -11, -11, -11, -20, -8, -15, -11, -17, -6, -6, -6, -4, -1,
    -6, -6, -1, -6, -4, -12, -9, -9, -11, -11, -27, -15, -7, -8, -9, -9,
    -9, -8, -9, -9, -9, -4, -9, -9, -4, -9, -26, -26, 8, -11, -11, -11,
    -13, -13, -11, -13, -9, -2, -2, -2, -10, -10, -7, -6, -1, -6, -3, -2,
    -5, -6, -4, -17, -1, -1, -21, -21, -12, -13, -29, -7, -7, -16, -12, -15,
    -15, -15, 6, 6, 6, 3, -14, -15, 3, 8, 3, 5, -16, -11, -11, -20,
    -6, -24, -24, -13, -13, -8, -5, -31, -5, -11, -11, -20, 3, 6, 6, 4,
    6, -20, -20, -17, -13, 5, 4, -17, -15, -13, -13, -13, -17, -13, -13, -15,
    -8, -8, -7, -3, -13, -8, -15, -8, -15, -11, -4, -4, -7, -10, -5, -5,
    -6, -5, -5, -18, -7, -7, -7, -7, -10, -4, -4, -7, -4, -7, -4, -6,
    -4, 4, 4, 3, 4, 4, 4, -11, -6, -10, -17, -13, -17, -17, -9, -9,
    -9, -13, -7, -7, -6, -7, -7, -4, -17, -12, -2, -11, -11, -11, -3, -13,
    -2, -2, -4, -2, -1, -9, -9, -11, -9, -11, -9, -9, -2, -8, -4, -3,
    -6, -6, -6, 7, 7, 4, 4, -20, -20, -20, -20, -17, -13, -18, -12, 6,
    -17, 7, -13, -13, 9, 13, -13, -13, -6, -6, -6, -15, -7, -11, -16, 2,
    2, 2, 3, 3, -12, -12, -11, 7, 7, 6, 7, 6, 8, 6, 7, 6,
    -11, 6, 7, -12, -10, -6, -9, -4, -4, 1, 1, 1, 5, 3, 1, 3,
    3, 6, -12, -11, -12, -13, -12, -12, -16, -4, -17, -17, -5, -7, -3, -16,
    -4, -12, 1, 1, 1, 1, 1, 1, 3, 2, 1, 1, 1, 1, 1, 4,
    1, 1, 1, 1, 1, 3, 7, 7, 7, -13, 4, 4, -9, -9, -9, -8,
    2, 2, 2, 2, 1, 1, 4, 6, 6, 6, -15, -15, -16, 6, 3, -8,
    3, -11, -11, -8, -9, -11, -11, -11, -1, -1, -1, -8, -1, -1, -2, -1,
    -1, -1, -1, -3, -1, -1, -1,
};

static const lv_font_fmt_txt_kern_pair_t kern_pairs = {
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 423,
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
const lv_font_t humid1_font_plex_cond_normal_14 = {
#else
lv_font_t humid1_font_plex_cond_normal_14 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 19,
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
    .fallback = &humid1_font_plex_sans_normal_14,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_COND_NORMAL_14 */
