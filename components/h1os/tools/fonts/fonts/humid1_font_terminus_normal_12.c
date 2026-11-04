/*******************************************************************************
 * Font: humid1_font_terminus_normal_12 (IBM Plex Terminus Normal)
 * Size: 12 px @ 188 DPI (SSD1681 1-bit E-Paper Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Raster Mode: exact-mono (FT_LOAD_TARGET_MONO + Dropout Control)
 * License: SIL Open Font License 1.1 (IBM Corp.) / Font Awesome Free License
 ******************************************************************************/

#include "lvgl.h"

#ifndef HUMID1_FONT_TERMINUS_NORMAL_12
#define HUMID1_FONT_TERMINUS_NORMAL_12 1
#endif

#if HUMID1_FONT_TERMINUS_NORMAL_12

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (1x8) */
    0xfb,
    /* U+0022 "" (3x3) */
    0xb6, 0x80,
    /* U+0023 "#" (5x8) */
    0x52, 0xbe, 0xa5, 0x7d, 0x4a,
    /* U+0024 "$" (5x9) */
    0x23, 0xab, 0x47, 0x16, 0xae, 0x20,
    /* U+0025 "%" (6x8) */
    0x4a, 0xa5, 0x04, 0x20, 0xa5, 0x52,
    /* U+0026 "&" (5x8) */
    0x22, 0x94, 0x46, 0xca, 0x4d,
    /* U+0027 "'" (1x3) */
    0xe0,
    /* U+0028 "(" (3x8) */
    0x2a, 0x49, 0x11,
    /* U+0029 ")" (3x8) */
    0x88, 0x92, 0x54,
    /* U+002A "" (5x5) */
    0x51, 0x3e, 0x45, 0x00,
    /* U+002B "+" (5x5) */
    0x21, 0x3e, 0x42, 0x00,
    /* U+002C "," (2x3) */
    0x58,
    /* U+002D "-" (5x1) */
    0xf8,
    /* U+002E "." (1x2) */
    0xc0,
    /* U+002F "/" (4x8) */
    0x11, 0x22, 0x44, 0x88,
    /* U+0030 "0" (5x8) */
    0x74, 0x67, 0x5c, 0xc6, 0x2e,
    /* U+0031 "1" (3x8) */
    0x59, 0x24, 0x97,
    /* U+0032 "2" (5x8) */
    0x74, 0x62, 0x11, 0x11, 0x1f,
    /* U+0033 "3" (5x8) */
    0x74, 0x42, 0x60, 0x86, 0x2e,
    /* U+0034 "4" (5x8) */
    0x08, 0xca, 0x98, 0xfc, 0x21,
    /* U+0035 "5" (5x8) */
    0xfc, 0x21, 0xe0, 0x86, 0x2e,
    /* U+0036 "6" (5x8) */
    0x74, 0x21, 0xe8, 0xc6, 0x2e,
    /* U+0037 "7" (5x8) */
    0xf8, 0x42, 0x21, 0x10, 0x84,
    /* U+0038 "8" (5x8) */
    0x74, 0x62, 0xe8, 0xc6, 0x2e,
    /* U+0039 "9" (5x8) */
    0x74, 0x63, 0x17, 0x84, 0x2e,
    /* U+003A ":" (1x6) */
    0xcc,
    /* U+003B ";" (2x7) */
    0x50, 0x58,
    /* U+003C "<" (4x7) */
    0x12, 0x48, 0x42, 0x10,
    /* U+003D "=" (5x4) */
    0xf8, 0x01, 0xf0,
    /* U+003E ">" (4x7) */
    0x84, 0x21, 0x24, 0x80,
    /* U+003F "?" (5x8) */
    0x74, 0x62, 0x22, 0x00, 0x84,
    /* U+0040 "@" (5x8) */
    0x74, 0x67, 0x5a, 0xce, 0x0f,
    /* U+0041 "A" (5x8) */
    0x74, 0x63, 0x1f, 0xc6, 0x31,
    /* U+0042 "B" (5x8) */
    0xf4, 0x63, 0xe8, 0xc6, 0x3e,
    /* U+0043 "C" (5x8) */
    0x74, 0x61, 0x08, 0x42, 0x2e,
    /* U+0044 "D" (5x8) */
    0xe4, 0xa3, 0x18, 0xc6, 0x5c,
    /* U+0045 "E" (5x8) */
    0xfc, 0x21, 0xe8, 0x42, 0x1f,
    /* U+0046 "F" (5x8) */
    0xfc, 0x21, 0xe8, 0x42, 0x10,
    /* U+0047 "G" (5x8) */
    0x74, 0x61, 0x0b, 0xc6, 0x2e,
    /* U+0048 "H" (5x8) */
    0x8c, 0x63, 0xf8, 0xc6, 0x31,
    /* U+0049 "I" (3x8) */
    0xe9, 0x24, 0x97,
    /* U+004A "J" (5x8) */
    0x38, 0x84, 0x21, 0x4a, 0x4c,
    /* U+004B "K" (5x8) */
    0x8c, 0xa9, 0x8c, 0x52, 0x51,
    /* U+004C "L" (5x8) */
    0x84, 0x21, 0x08, 0x42, 0x1f,
    /* U+004D "M" (5x8) */
    0x8e, 0xeb, 0x58, 0xc6, 0x31,
    /* U+004E "N" (5x8) */
    0x8c, 0x73, 0x59, 0xc6, 0x31,
    /* U+004F "O" (5x8) */
    0x74, 0x63, 0x18, 0xc6, 0x2e,
    /* U+0050 "P" (5x8) */
    0xf4, 0x63, 0x1f, 0x42, 0x10,
    /* U+0051 "Q" (5x9) */
    0x74, 0x63, 0x18, 0xc6, 0xae, 0x08,
    /* U+0052 "R" (5x8) */
    0xf4, 0x63, 0x1f, 0x52, 0x51,
    /* U+0053 "S" (5x8) */
    0x74, 0x60, 0xe0, 0x86, 0x2e,
    /* U+0054 "T" (5x8) */
    0xf9, 0x08, 0x42, 0x10, 0x84,
    /* U+0055 "U" (5x8) */
    0x8c, 0x63, 0x18, 0xc6, 0x2e,
    /* U+0056 "V" (5x8) */
    0x8c, 0x62, 0xa5, 0x28, 0x84,
    /* U+0057 "W" (5x8) */
    0x8c, 0x63, 0x1a, 0xd7, 0x71,
    /* U+0058 "X" (5x8) */
    0x8c, 0x54, 0x42, 0x2a, 0x31,
    /* U+0059 "Y" (5x8) */
    0x8c, 0x54, 0xa2, 0x10, 0x84,
    /* U+005A "Z" (5x8) */
    0xf8, 0x44, 0x44, 0x42, 0x1f,
    /* U+005B "[" (3x8) */
    0xf2, 0x49, 0x27,
    /* U+005C "" (4x8) */
    0x88, 0x44, 0x22, 0x11,
    /* U+005D "]" (3x8) */
    0xe4, 0x92, 0x4f,
    /* U+005E "^" (5x3) */
    0x22, 0xa2,
    /* U+005F "_" (5x1) */
    0xf8,
    /* U+0060 "`" (2x2) */
    0x90,
    /* U+0061 "a" (5x6) */
    0x70, 0x5f, 0x18, 0xbc,
    /* U+0062 "b" (5x8) */
    0x84, 0x3d, 0x18, 0xc6, 0x3e,
    /* U+0063 "c" (5x6) */
    0x74, 0x61, 0x08, 0xb8,
    /* U+0064 "d" (5x8) */
    0x08, 0x5f, 0x18, 0xc6, 0x2f,
    /* U+0065 "e" (5x6) */
    0x74, 0x7f, 0x08, 0x3c,
    /* U+0066 "f" (4x8) */
    0x34, 0xe4, 0x44, 0x44,
    /* U+0067 "g" (5x8) */
    0x7c, 0x63, 0x18, 0xbc, 0x2e,
    /* U+0068 "h" (5x8) */
    0x84, 0x3d, 0x18, 0xc6, 0x31,
    /* U+0069 "i" (3x9) */
    0x48, 0x64, 0x92, 0xe0,
    /* U+006A "j" (4x11) */
    0x11, 0x03, 0x11, 0x11, 0x19, 0x60,
    /* U+006B "k" (4x8) */
    0x88, 0x9a, 0xcc, 0xa9,
    /* U+006C "l" (3x8) */
    0xc9, 0x24, 0x97,
    /* U+006D "m" (5x6) */
    0xf5, 0x6b, 0x5a, 0xd4,
    /* U+006E "n" (5x6) */
    0xf4, 0x63, 0x18, 0xc4,
    /* U+006F "o" (5x6) */
    0x74, 0x63, 0x18, 0xb8,
    /* U+0070 "p" (5x8) */
    0xf4, 0x63, 0x18, 0xfa, 0x10,
    /* U+0071 "q" (5x8) */
    0x7c, 0x63, 0x18, 0xbc, 0x21,
    /* U+0072 "r" (5x6) */
    0xbe, 0x21, 0x08, 0x40,
    /* U+0073 "s" (5x6) */
    0x7c, 0x1c, 0x10, 0xf8,
    /* U+0074 "t" (4x8) */
    0x44, 0xe4, 0x44, 0x43,
    /* U+0075 "u" (5x6) */
    0x8c, 0x63, 0x18, 0xbc,
    /* U+0076 "v" (5x6) */
    0x8c, 0x54, 0xa2, 0x10,
    /* U+0077 "w" (5x6) */
    0x8c, 0x6b, 0x5a, 0xb8,
    /* U+0078 "x" (5x6) */
    0x8a, 0x88, 0x45, 0x44,
    /* U+0079 "y" (5x8) */
    0x8c, 0x63, 0x18, 0xbc, 0x2e,
    /* U+007A "z" (5x6) */
    0xf8, 0x88, 0x88, 0x7c,
    /* U+007B "{" (4x8) */
    0x34, 0x48, 0x44, 0x43,
    /* U+007C "|" (1x8) */
    0xff,
    /* U+007D "}" (4x8) */
    0xc2, 0x21, 0x22, 0x2c,
    /* U+007E "~" (5x3) */
    0x4d, 0x64,
    /* U+00B0 "" (3x3) */
    0x55, 0x00,
    /* U+00B1 "" (5x7) */
    0x21, 0x3e, 0x42, 0x03, 0xe0,
    /* U+00B2 "" (4x5) */
    0x69, 0x24, 0xf0,
    /* U+00B3 "" (4x5) */
    0xe1, 0x61, 0xe0,
    /* U+00B5 "" (5x8) */
    0x8c, 0x63, 0x19, 0xf6, 0x10,
    /* U+00B7 "" (1x2) */
    0xc0,
    /* U+00D7 "" (5x5) */
    0x8a, 0x88, 0xa8, 0x80,
    /* U+00F7 "" (5x7) */
    0x21, 0x01, 0xf0, 0x10, 0x80,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 96, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 96, .box_w = 1, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 96, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 3, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 8, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 14, .adv_w = 96, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 20, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 25, .adv_w = 96, .box_w = 1, .box_h = 3, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 26, .adv_w = 96, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 29, .adv_w = 96, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 32, .adv_w = 96, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 36, .adv_w = 96, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 40, .adv_w = 96, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 41, .adv_w = 96, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 42, .adv_w = 96, .box_w = 1, .box_h = 2, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 43, .adv_w = 96, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 47, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 96, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 55, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 60, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 65, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 70, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 75, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 80, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 85, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 90, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 95, .adv_w = 96, .box_w = 1, .box_h = 6, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 96, .adv_w = 96, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 98, .adv_w = 96, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 102, .adv_w = 96, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 105, .adv_w = 96, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 109, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 114, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 124, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 144, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 149, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 154, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 159, .adv_w = 96, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 162, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 172, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 177, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 182, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 192, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 197, .adv_w = 96, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 203, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 208, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 218, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 223, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 238, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 243, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 248, .adv_w = 96, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 96, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 255, .adv_w = 96, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 258, .adv_w = 96, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 260, .adv_w = 96, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 261, .adv_w = 96, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 262, .adv_w = 96, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 266, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 271, .adv_w = 96, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 275, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 280, .adv_w = 96, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 284, .adv_w = 96, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 288, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 293, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 298, .adv_w = 96, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 302, .adv_w = 96, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 308, .adv_w = 96, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 312, .adv_w = 96, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 96, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 319, .adv_w = 96, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 323, .adv_w = 96, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 332, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 337, .adv_w = 96, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 341, .adv_w = 96, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 345, .adv_w = 96, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 349, .adv_w = 96, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 353, .adv_w = 96, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 357, .adv_w = 96, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 361, .adv_w = 96, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 365, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 370, .adv_w = 96, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 374, .adv_w = 96, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 378, .adv_w = 96, .box_w = 1, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 379, .adv_w = 96, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 383, .adv_w = 96, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 385, .adv_w = 96, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 387, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 392, .adv_w = 96, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 395, .adv_w = 96, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 398, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 403, .adv_w = 96, .box_w = 1, .box_h = 2, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 404, .adv_w = 96, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 408, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0}
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
const lv_font_t humid1_font_terminus_normal_12 = {
#else
lv_font_t humid1_font_terminus_normal_12 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 12,
    .base_line = 2,
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_TERMINUS_NORMAL_12 */
