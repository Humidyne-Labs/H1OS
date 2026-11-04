/*******************************************************************************
 * Font: humid1_font_plex_sans_italic_12 (IBM Plex Sans Italic)
 * Size: 12 px @ 188 DPI (SSD1681 1-bit E-Paper Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Raster Mode: autohint-mono (FT_LOAD_TARGET_MONO + Dropout Control)
 * License: SIL Open Font License 1.1 (IBM Corp.) / Font Awesome Free License
 ******************************************************************************/

#include "lvgl.h"

#ifndef HUMID1_FONT_PLEX_SANS_ITALIC_12
#define HUMID1_FONT_PLEX_SANS_ITALIC_12 1
#endif

#if HUMID1_FONT_PLEX_SANS_ITALIC_12

extern const lv_font_t humid1_font_plex_sans_normal_12;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (3x8) */
    0x24, 0xa4, 0x86,
    /* U+0022 "" (4x3) */
    0x55, 0x90,
    /* U+0023 "#" (7x8) */
    0x14, 0x49, 0xf9, 0x44, 0x9f, 0x94, 0x48,
    /* U+0024 "$" (7x10) */
    0x08, 0x79, 0xca, 0x83, 0x03, 0x85, 0x52, 0x78, 0x40,
    /* U+0025 "%" (9x8) */
    0x71, 0x29, 0x25, 0x13, 0x66, 0xc8, 0xa4, 0x94, 0x8e,
    /* U+0026 "&" (8x8) */
    0x1c, 0x24, 0x24, 0x28, 0x73, 0x4c, 0xcc, 0x72,
    /* U+0027 "'" (2x3) */
    0x58,
    /* U+0028 "(" (3x10) */
    0x25, 0x49, 0x24, 0x88,
    /* U+0029 ")" (3x10) */
    0x44, 0x92, 0x4a, 0x50,
    /* U+002A "" (5x4) */
    0x27, 0x4c, 0xa0,
    /* U+002B "+" (5x6) */
    0x11, 0x3e, 0x42, 0x10,
    /* U+002C "," (2x3) */
    0x58,
    /* U+002D "-" (3x1) */
    0xe0,
    /* U+002E "." (2x1) */
    0xc0,
    /* U+002F "/" (6x10) */
    0x04, 0x20, 0x84, 0x10, 0x82, 0x10, 0x42, 0x00,
    /* U+0030 "0" (6x8) */
    0x39, 0x38, 0x61, 0x8e, 0x29, 0x9c,
    /* U+0031 "1" (5x8) */
    0x32, 0x84, 0x21, 0x10, 0x9f,
    /* U+0032 "2" (6x8) */
    0x39, 0x30, 0xc2, 0x10, 0x8c, 0x3e,
    /* U+0033 "3" (6x8) */
    0x1c, 0x90, 0x46, 0x04, 0x1c, 0xde,
    /* U+0034 "4" (6x8) */
    0x04, 0x31, 0x4d, 0x25, 0x2f, 0xc2,
    /* U+0035 "5" (6x8) */
    0x7d, 0x04, 0x1e, 0x88, 0x28, 0xbc,
    /* U+0036 "6" (5x8) */
    0x11, 0x11, 0x7c, 0xc6, 0x2e,
    /* U+0037 "7" (6x8) */
    0x7d, 0x18, 0x84, 0x10, 0x86, 0x10,
    /* U+0038 "8" (6x8) */
    0x39, 0x14, 0x8c, 0xca, 0x28, 0xbc,
    /* U+0039 "9" (6x8) */
    0x39, 0x18, 0x73, 0x78, 0x21, 0x18,
    /* U+003A ":" (2x6) */
    0x40, 0x20,
    /* U+003B ";" (3x7) */
    0x20, 0x04, 0xa0,
    /* U+003C "<" (6x6) */
    0x0c, 0xcc, 0x30, 0x30, 0x60,
    /* U+003D "=" (6x3) */
    0xfc, 0x0f, 0x80,
    /* U+003E ">" (5x6) */
    0x41, 0x82, 0x36, 0x40,
    /* U+003F "?" (5x8) */
    0x74, 0x42, 0x26, 0x20, 0x18,
    /* U+0040 "@" (9x10) */
    0x1e, 0x10, 0x96, 0xb4, 0x9a, 0x4d, 0x2a, 0xfd, 0x00, 0xc0, 0x3e, 0x00,
    /* U+0041 "A" (6x8) */
    0x0c, 0x51, 0x49, 0x25, 0xfc, 0x61,
    /* U+0042 "B" (6x8) */
    0x7d, 0x14, 0x7e, 0x86, 0x18, 0xbe,
    /* U+0043 "C" (6x8) */
    0x39, 0x18, 0x20, 0x82, 0x08, 0x9c,
    /* U+0044 "D" (6x8) */
    0x79, 0x14, 0x61, 0x86, 0x18, 0xbc,
    /* U+0045 "E" (6x8) */
    0x7d, 0x04, 0x3e, 0x82, 0x08, 0x3e,
    /* U+0046 "F" (6x8) */
    0x7d, 0x04, 0x3e, 0x82, 0x08, 0x20,
    /* U+0047 "G" (7x8) */
    0x3c, 0x8e, 0x04, 0x08, 0xd0, 0xa3, 0x3a,
    /* U+0048 "H" (7x8) */
    0x42, 0x85, 0x0f, 0xe8, 0x50, 0xa1, 0x42,
    /* U+0049 "I" (5x8) */
    0x38, 0x88, 0x42, 0x11, 0x1c,
    /* U+004A "J" (6x8) */
    0x3c, 0x10, 0x82, 0x08, 0x29, 0x1c,
    /* U+004B "K" (6x8) */
    0x45, 0x25, 0x28, 0xd2, 0x48, 0xa2,
    /* U+004C "L" (4x8) */
    0x44, 0x48, 0x88, 0x8f,
    /* U+004D "M" (8x8) */
    0x61, 0x63, 0x65, 0x99, 0x9a, 0x92, 0x82, 0x82,
    /* U+004E "N" (7x8) */
    0x42, 0xc5, 0x8c, 0xa9, 0x52, 0xa3, 0x46,
    /* U+004F "O" (7x8) */
    0x3c, 0x8e, 0x0c, 0x18, 0x30, 0xa3, 0x38,
    /* U+0050 "P" (6x8) */
    0x7d, 0x14, 0x61, 0xfa, 0x08, 0x20,
    /* U+0051 "Q" (7x10) */
    0x3c, 0x8e, 0x0c, 0x18, 0x30, 0xa1, 0x3c, 0x20, 0x60,
    /* U+0052 "R" (6x8) */
    0x7d, 0x14, 0x61, 0xfa, 0x48, 0xa2,
    /* U+0053 "S" (7x8) */
    0x3c, 0xc5, 0x01, 0x01, 0xc0, 0xa1, 0x3c,
    /* U+0054 "T" (6x8) */
    0xfc, 0x42, 0x08, 0x20, 0x82, 0x10,
    /* U+0055 "U" (7x8) */
    0x42, 0x85, 0x14, 0x28, 0x50, 0xa2, 0x38,
    /* U+0056 "V" (7x8) */
    0x83, 0x09, 0x12, 0x45, 0x0a, 0x18, 0x30,
    /* U+0057 "W" (10x8) */
    0x8c, 0x63, 0x19, 0x4a, 0x52, 0xa5, 0x29, 0x4c, 0x61, 0x18,
    /* U+0058 "X" (7x8) */
    0x22, 0x4c, 0x50, 0xc1, 0x85, 0x12, 0x42,
    /* U+0059 "Y" (6x8) */
    0x85, 0x14, 0x9c, 0x20, 0x82, 0x10,
    /* U+005A "Z" (7x8) */
    0x3e, 0x08, 0x20, 0xc1, 0x04, 0x10, 0x7e,
    /* U+005B "[" (4x11) */
    0x32, 0x24, 0x44, 0x44, 0x88, 0xc0,
    /* U+005C "" (1x10) */
    0xff, 0xc0,
    /* U+005D "]" (4x11) */
    0x31, 0x22, 0x22, 0x24, 0x44, 0xc0,
    /* U+005E "^" (5x5) */
    0x11, 0x53, 0x18, 0x00,
    /* U+005F "_" (6x1) */
    0xfc,
    /* U+0060 "`" (1x1) */
    0x80,
    /* U+0061 "a" (5x6) */
    0x7c, 0x63, 0x19, 0x7c,
    /* U+0062 "b" (6x8) */
    0x20, 0x83, 0xd9, 0x45, 0x14, 0xee,
    /* U+0063 "c" (5x6) */
    0x74, 0x61, 0x09, 0x70,
    /* U+0064 "d" (6x8) */
    0x04, 0x17, 0xa2, 0x8a, 0x29, 0x3e,
    /* U+0065 "e" (5x6) */
    0x74, 0x7d, 0x09, 0x78,
    /* U+0066 "f" (6x10) */
    0x1c, 0x43, 0x84, 0x20, 0x82, 0x08, 0x43, 0x00,
    /* U+0067 "g" (6x9) */
    0x04, 0xe4, 0x52, 0x79, 0x07, 0xa3, 0xf8,
    /* U+0068 "h" (6x8) */
    0x20, 0x83, 0xd9, 0x45, 0x14, 0xa3,
    /* U+0069 "i" (2x8) */
    0x46, 0xaa,
    /* U+006A "j" (4x10) */
    0x10, 0x12, 0x22, 0x24, 0x4c,
    /* U+006B "k" (6x8) */
    0x20, 0x82, 0x56, 0x71, 0x44, 0xa3,
    /* U+006C "l" (2x8) */
    0x56, 0xaa,
    /* U+006D "m" (9x6) */
    0x3b, 0xb2, 0x51, 0x29, 0x14, 0x8c, 0x44,
    /* U+006E "n" (6x6) */
    0x3d, 0x94, 0x51, 0x4a, 0x30,
    /* U+006F "o" (5x6) */
    0x74, 0x63, 0x19, 0x70,
    /* U+0070 "p" (6x8) */
    0x3d, 0x94, 0x51, 0x4e, 0xe8, 0x20,
    /* U+0071 "q" (5x8) */
    0x7c, 0x63, 0x1b, 0x78, 0x42,
    /* U+0072 "r" (5x6) */
    0x3b, 0x10, 0x84, 0x40,
    /* U+0073 "s" (5x6) */
    0x7a, 0x50, 0x78, 0xb8,
    /* U+0074 "t" (3x8) */
    0x4b, 0xa9, 0x26,
    /* U+0075 "u" (5x6) */
    0x8c, 0x63, 0x29, 0x7c,
    /* U+0076 "v" (5x6) */
    0x8c, 0xa5, 0x4a, 0x20,
    /* U+0077 "w" (8x6) */
    0x91, 0x9a, 0xaa, 0xac, 0xcc, 0xcc,
    /* U+0078 "x" (6x6) */
    0x44, 0xa3, 0x0c, 0x52, 0x20,
    /* U+0079 "y" (6x8) */
    0x45, 0x24, 0x94, 0x50, 0x84, 0x30,
    /* U+007A "z" (5x6) */
    0x78, 0x44, 0x44, 0x7c,
    /* U+007B "{" (4x11) */
    0x12, 0x22, 0x48, 0x44, 0x44, 0x40,
    /* U+007C "|" (3x10) */
    0x24, 0x94, 0x92, 0x50,
    /* U+007D "}" (4x11) */
    0x31, 0x22, 0x21, 0x24, 0x44, 0xc0,
    /* U+007E "~" (5x2) */
    0xe0, 0xc0,
    /* U+00B0 "" (4x4) */
    0x75, 0x97,
    /* U+00B1 "" (7x7) */
    0x08, 0x11, 0xf8, 0x81, 0x00, 0x3f, 0x00,
    /* U+00B2 "" (3x4) */
    0x65, 0x70,
    /* U+00B3 "" (3x4) */
    0xe8, 0xe0,
    /* U+00B5 "" (6x8) */
    0x25, 0x14, 0x51, 0x4a, 0xf8, 0x20,
    /* U+00B7 "" (2x1) */
    0xc0,
    /* U+00D7 "" (5x5) */
    0x42, 0xc8, 0xa8, 0x80,
    /* U+00F7 "" (5x6) */
    0x30, 0x01, 0xf0, 0x10,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 45, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 52, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 79, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 5, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 12, .adv_w = 111, .box_w = 7, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 21, .adv_w = 173, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 30, .adv_w = 129, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 38, .adv_w = 45, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 39, .adv_w = 63, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 43, .adv_w = 63, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 47, .adv_w = 87, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 50, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 54, .adv_w = 52, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 55, .adv_w = 74, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 56, .adv_w = 52, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 57, .adv_w = 73, .box_w = 6, .box_h = 10, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 65, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 71, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 76, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 82, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 115, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 115, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 123, .adv_w = 56, .box_w = 2, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 56, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 128, .adv_w = 115, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 115, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 136, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 140, .adv_w = 90, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 145, .adv_w = 166, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 157, .adv_w = 120, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 163, .adv_w = 120, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 116, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 125, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 181, .adv_w = 108, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 104, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 193, .adv_w = 127, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 200, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 207, .adv_w = 74, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 212, .adv_w = 96, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 218, .adv_w = 118, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 224, .adv_w = 94, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 151, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 236, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 243, .adv_w = 130, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 250, .adv_w = 113, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 256, .adv_w = 130, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 265, .adv_w = 120, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 271, .adv_w = 111, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 278, .adv_w = 107, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 284, .adv_w = 126, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 291, .adv_w = 114, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 298, .adv_w = 166, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 308, .adv_w = 114, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 111, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 321, .adv_w = 108, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 328, .adv_w = 61, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 334, .adv_w = 73, .box_w = 1, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 336, .adv_w = 61, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 342, .adv_w = 115, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 346, .adv_w = 105, .box_w = 6, .box_h = 1, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 347, .adv_w = 114, .box_w = 1, .box_h = 1, .ofs_x = 3, .ofs_y = 7},
    {.bitmap_index = 348, .adv_w = 112, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 352, .adv_w = 110, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 358, .adv_w = 94, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 362, .adv_w = 112, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 368, .adv_w = 98, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 372, .adv_w = 59, .box_w = 6, .box_h = 10, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 380, .adv_w = 98, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 387, .adv_w = 108, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 393, .adv_w = 51, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 395, .adv_w = 49, .box_w = 4, .box_h = 10, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 400, .adv_w = 100, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 406, .adv_w = 51, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 408, .adv_w = 163, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 415, .adv_w = 108, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 420, .adv_w = 106, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 424, .adv_w = 110, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 430, .adv_w = 110, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 435, .adv_w = 70, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 439, .adv_w = 90, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 443, .adv_w = 61, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 446, .adv_w = 108, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 450, .adv_w = 93, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 454, .adv_w = 142, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 460, .adv_w = 95, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 465, .adv_w = 93, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 471, .adv_w = 86, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 475, .adv_w = 63, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 481, .adv_w = 59, .box_w = 3, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 485, .adv_w = 63, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 491, .adv_w = 115, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 493, .adv_w = 87, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 495, .adv_w = 115, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 502, .adv_w = 65, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 504, .adv_w = 65, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 506, .adv_w = 109, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 512, .adv_w = 61, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 513, .adv_w = 115, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 517, .adv_w = 115, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 1}
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
    3, 13, 3, 15, 3, 34, 6, 3, 6, 8, 6, 11, 7, 53, 7, 58,
    8, 13, 8, 15, 8, 34, 8, 43, 11, 13, 11, 15, 11, 53, 11, 55,
    11, 56, 11, 58, 11, 59, 11, 85, 11, 87, 11, 88, 11, 89, 11, 90,
    11, 91, 13, 3, 13, 8, 13, 11, 13, 32, 13, 53, 13, 59, 14, 42,
    14, 43, 14, 52, 14, 53, 14, 55, 14, 57, 14, 58, 14, 59, 14, 89,
    14, 91, 15, 3, 15, 8, 15, 11, 15, 32, 15, 53, 15, 59, 16, 16,
    16, 34, 16, 66, 16, 68, 16, 69, 16, 70, 16, 72, 16, 80, 16, 82,
    16, 84, 27, 53, 27, 55, 27, 57, 27, 58, 28, 53, 28, 55, 28, 57,
    28, 58, 32, 13, 32, 15, 32, 34, 34, 3, 34, 7, 34, 8, 34, 11,
    34, 14, 34, 32, 34, 33, 34, 36, 34, 40, 34, 48, 34, 50, 34, 52,
    34, 53, 34, 54, 34, 55, 34, 56, 34, 58, 34, 66, 34, 68, 34, 69,
    34, 70, 34, 72, 34, 80, 34, 82, 34, 85, 34, 86, 34, 87, 34, 88,
    34, 90, 34, 98, 34, 99, 35, 3, 35, 8, 35, 11, 35, 13, 35, 15,
    35, 16, 35, 34, 35, 53, 35, 55, 35, 56, 35, 57, 35, 58, 35, 64,
    35, 66, 35, 68, 35, 69, 35, 70, 35, 72, 35, 80, 35, 82, 35, 85,
    35, 86, 35, 87, 35, 88, 35, 89, 35, 90, 35, 98, 35, 99, 37, 13,
    37, 15, 37, 16, 37, 53, 37, 55, 37, 58, 37, 64, 39, 7, 39, 13,
    39, 15, 39, 16, 39, 33, 39, 34, 39, 43, 39, 64, 39, 66, 39, 68,
    39, 69, 39, 70, 39, 71, 39, 72, 39, 75, 39, 78, 39, 79, 39, 80,
    39, 81, 39, 82, 39, 83, 39, 84, 39, 85, 39, 86, 39, 87, 39, 88,
    39, 89, 39, 90, 39, 91, 40, 58, 42, 14, 42, 33, 43, 64, 44, 10,
    44, 13, 44, 15, 44, 64, 44, 91, 45, 3, 45, 8, 45, 11, 45, 14,
    45, 32, 45, 53, 45, 55, 45, 58, 45, 64, 45, 87, 45, 90, 45, 98,
    45, 99, 48, 64, 49, 13, 49, 15, 49, 16, 49, 64, 50, 64, 51, 7,
    51, 14, 51, 33, 51, 36, 51, 40, 51, 43, 51, 48, 51, 50, 51, 53,
    51, 54, 51, 55, 51, 56, 51, 58, 51, 66, 51, 68, 51, 69, 51, 70,
    51, 72, 51, 80, 51, 82, 51, 86, 51, 90, 51, 98, 51, 99, 53, 7,
    53, 13, 53, 14, 53, 15, 53, 16, 53, 27, 53, 28, 53, 33, 53, 34,
    53, 43, 53, 64, 53, 66, 53, 68, 53, 69, 53, 70, 53, 72, 53, 78,
    53, 79, 53, 80, 53, 81, 53, 82, 53, 83, 53, 84, 53, 86, 53, 87,
    53, 88, 53, 89, 53, 90, 53, 91, 54, 64, 55, 13, 55, 15, 55, 98,
    55, 99, 56, 3, 56, 8, 56, 10, 56, 11, 56, 32, 56, 36, 56, 40,
    56, 48, 56, 50, 56, 52, 56, 53, 56, 98, 56, 99, 58, 7, 58, 13,
    58, 14, 58, 15, 58, 16, 58, 27, 58, 28, 58, 34, 58, 64, 58, 66,
    58, 68, 58, 69, 58, 70, 58, 72, 58, 78, 58, 79, 58, 80, 58, 81,
    58, 82, 58, 83, 58, 84, 59, 14, 64, 36, 64, 40, 64, 43, 64, 48,
    64, 50, 64, 52, 64, 53, 64, 54, 64, 55, 64, 56, 64, 58, 64, 66,
    64, 68, 64, 69, 64, 70, 64, 77, 64, 80, 64, 82, 64, 84, 64, 85,
    64, 86, 64, 87, 64, 88, 64, 90, 64, 91, 66, 53, 66, 58, 66, 64,
    67, 3, 67, 8, 67, 11, 67, 53, 67, 55, 67, 58, 67, 64, 68, 53,
    68, 58, 69, 64, 70, 53, 70, 58, 71, 13, 71, 15, 71, 64, 72, 10,
    72, 13, 72, 15, 72, 16, 72, 64, 72, 71, 72, 75, 73, 3, 73, 8,
    73, 11, 73, 53, 73, 55, 73, 58, 74, 64, 75, 53, 75, 58, 76, 13,
    76, 15, 76, 59, 76, 64, 77, 64, 78, 58, 78, 64, 79, 3, 79, 8,
    79, 11, 79, 53, 79, 55, 79, 58, 80, 3, 80, 8, 80, 11, 80, 13,
    80, 15, 80, 53, 80, 55, 80, 56, 80, 58, 80, 64, 80, 87, 80, 88,
    80, 90, 81, 3, 81, 8, 81, 11, 81, 53, 81, 55, 81, 58, 81, 64,
    82, 53, 82, 58, 83, 3, 83, 8, 83, 11, 83, 36, 83, 40, 83, 48,
    83, 50, 83, 56, 83, 87, 83, 90, 83, 98, 83, 99, 84, 3, 84, 8,
    84, 11, 84, 53, 84, 55, 84, 56, 84, 57, 84, 58, 84, 64, 84, 72,
    84, 85, 84, 87, 84, 88, 84, 89, 84, 90, 86, 53, 86, 55, 86, 58,
    87, 13, 87, 15, 87, 53, 87, 64, 88, 53, 89, 53, 90, 13, 90, 15,
    90, 53, 90, 64, 91, 3, 91, 8, 91, 11, 91, 13, 91, 15, 91, 34,
    91, 56, 91, 57, 91, 64, 91, 98, 91, 99, 98, 13, 98, 15, 99, 13,
    99, 15, 99, 34,
};

static const int8_t kern_pair_values[] = {
    -17, -17, -15, -13, -13, -13, -12, -12, -17, -17, -15, -6, -17, -17, 5, 2,
    3, 2, 1, 3, 4, 4, 2, 4, 2, -17, -17, -17, -14, -15, 6, -6,
    -6, -4, -8, -3, -6, -8, -8, -5, -3, -17, -17, -17, -14, -15, 6, -23,
    -9, -3, -3, -3, -3, -3, -3, -3, -2, -8, -4, -2, -8, -8, -4, -2,
    -8, -22, -22, -4, -15, -2, -15, -15, -4, -6, -4, -3, -3, -3, -3, -3,
    -11, -2, -10, -1, -13, -4, -4, -4, -4, -1, -4, -4, -2, -3, -4, -2,
    -3, -6, -8, -2, -2, -2, -3, -3, -4, -2, -5, -4, -1, -4, -8, -10,
    -1, -1, -1, -1, -2, -1, -1, -1, -1, -2, -1, -2, -2, -2, -2, -6,
    -6, -6, -8, -6, -9, -11, -6, -15, -15, -8, -4, -7, -5, -19, -6, -6,
    -6, -6, -1, -6, -2, -4, -4, -6, -4, -6, -4, -4, -1, -5, -4, -2,
    -7, -4, -2, -8, -6, -4, -9, 2, 2, 2, 7, 2, -19, -19, -19, -8,
    -9, -13, -12, -13, 10, -10, -8, -13, -12, -11, -19, -19, -10, -19, -11, -5,
    -3, -4, -1, -1, -4, -1, -1, -5, -2, -5, -1, -8, -6, -6, -6, -6,
    -6, -6, -6, -4, -1, -2, -2, -5, -15, -10, -15, -13, -8, -8, -6, -11,
    -6, -8, -12, -12, -12, -12, -15, -9, -9, -12, -9, -12, -9, -12, -10, -7,
    -8, -10, -8, -10, -7, -12, -12, 8, 8, 3, 3, 2, 3, 6, 4, 4,
    4, 4, 2, 3, 8, 8, -8, -12, -10, -12, -12, -8, -8, -11, -8, -10,
    -10, -10, -10, -11, -8, -8, -10, -8, -10, -8, -8, -8, -19, -19, -12, -19,
    -19, -12, -15, -20, -13, -10, -15, -17, -17, -17, -17, -5, -17, -17, -9, -9,
    -11, -13, -8, -3, -2, -12, -10, 8, -8, -8, -8, -13, -9, -13, -8, -9,
    -9, 8, -13, -12, -10, -10, -6, 8, 6, 6, 10, 15, 6, 9, -7, -7,
    -7, -11, -7, -12, 8, -12, -12, 4, 4, 4, 6, 8, -12, 8, -7, -7,
    -7, -11, -7, -12, -8, -8, -8, -4, -4, -13, -9, -3, -13, -8, -5, -4,
    -5, -8, -8, -8, -13, -9, -13, -8, -12, -12, 6, 6, 6, 3, 3, 3,
    3, 2, 2, 2, 6, 6, -4, -4, -4, -12, -10, -4, -3, -13, -4, -3,
    -3, -3, -4, -4, -3, -12, -6, -10, -9, -9, -7, -10, -8, -10, -9, -9,
    -8, -12, 2, 2, 2, 3, 3, 4, 2, 2, 2, 4, 4, -10, -10, -10,
    -10, -10,
};

static const lv_font_fmt_txt_kern_pair_t kern_pairs = {
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 434,
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
const lv_font_t humid1_font_plex_sans_italic_12 = {
#else
lv_font_t humid1_font_plex_sans_italic_12 = {
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

#endif /* #if HUMID1_FONT_PLEX_SANS_ITALIC_12 */
