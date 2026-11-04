/*******************************************************************************
 * Font: humid1_font_plex_mono_bold_16 (IBM Plex Mono Bold)
 * Size: 16 px @ 188 DPI (SSD1681 1-bit E-Paper Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Raster Mode: autohint-mono (FT_LOAD_TARGET_MONO + Dropout Control)
 * License: SIL Open Font License 1.1 (IBM Corp.) / Font Awesome Free License
 ******************************************************************************/

#include "lvgl.h"

#ifndef HUMID1_FONT_PLEX_MONO_BOLD_16
#define HUMID1_FONT_PLEX_MONO_BOLD_16 1
#endif

#if HUMID1_FONT_PLEX_MONO_BOLD_16

extern const lv_font_t humid1_font_plex_sans_bold_16;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (3x12) */
    0x6d, 0xb6, 0xda, 0x1f, 0xf0,
    /* U+0022 "" (6x5) */
    0xcf, 0x3c, 0xf3, 0xcc,
    /* U+0023 "#" (9x12) */
    0x1b, 0x0d, 0x8c, 0xde, 0x7f, 0x79, 0xb0, 0xd9, 0xef, 0xe7, 0xb3, 0x1b,
    0x0d, 0x80,
    /* U+0024 "$" (8x15) */
    0x18, 0x18, 0x7e, 0xfe, 0xda, 0xd8, 0xf8, 0x7e, 0x1f, 0x1b, 0x1b, 0xff,
    0x7e, 0x18, 0x18,
    /* U+0025 "%" (10x12) */
    0x70, 0xfe, 0x6d, 0x9b, 0x6c, 0xdb, 0x3e, 0x07, 0x78, 0x3f, 0x2c, 0xdb,
    0x36, 0xff, 0x1e,
    /* U+0026 "&" (9x12) */
    0x3c, 0x3f, 0x19, 0x0c, 0x07, 0x01, 0x9d, 0xef, 0xbe, 0xce, 0x63, 0x3e,
    0xcf, 0x70,
    /* U+0027 "'" (2x5) */
    0xff, 0xc0,
    /* U+0028 "(" (5x15) */
    0x19, 0x98, 0xcc, 0x63, 0x18, 0xc6, 0x30, 0xc6, 0x18, 0x60,
    /* U+0029 ")" (5x15) */
    0xc3, 0x0c, 0x61, 0x8c, 0x63, 0x18, 0xc6, 0x63, 0x33, 0x00,
    /* U+002A "" (8x8) */
    0x18, 0x18, 0xdb, 0xff, 0x7e, 0x3c, 0x7e, 0x66,
    /* U+002B "+" (8x8) */
    0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18,
    /* U+002C "," (3x5) */
    0x7f, 0xec,
    /* U+002D "-" (5x2) */
    0xff, 0xc0,
    /* U+002E "." (3x3) */
    0xff, 0x80,
    /* U+002F "/" (7x16) */
    0x06, 0x0c, 0x38, 0x60, 0xc3, 0x86, 0x0c, 0x38, 0x60, 0xc3, 0x86, 0x0c,
    0x38, 0x60,
    /* U+0030 "0" (9x12) */
    0x3e, 0x3f, 0x98, 0xd8, 0x3c, 0x1e, 0xcf, 0x67, 0x83, 0xc1, 0xb1, 0x9f,
    0xc7, 0xc0,
    /* U+0031 "1" (9x12) */
    0x3c, 0x1e, 0x1f, 0x1d, 0x84, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x1f,
    0xef, 0xf0,
    /* U+0032 "2" (8x12) */
    0x3c, 0x7e, 0xc7, 0x47, 0x07, 0x0f, 0x1e, 0x3c, 0x70, 0xe0, 0xff, 0xff,
    /* U+0033 "3" (8x12) */
    0x3c, 0x7f, 0x63, 0x03, 0x03, 0x1e, 0x1e, 0x03, 0x03, 0xe3, 0x7e, 0x3c,
    /* U+0034 "4" (9x12) */
    0x0e, 0x07, 0x07, 0x86, 0xc3, 0x63, 0x31, 0x99, 0x8c, 0xff, 0xff, 0xc1,
    0x80, 0xc0,
    /* U+0035 "5" (8x12) */
    0xfe, 0xfe, 0xc0, 0xc0, 0xdc, 0xfe, 0xc7, 0x03, 0x03, 0xc7, 0xfe, 0x7c,
    /* U+0036 "6" (8x12) */
    0x1c, 0x38, 0x70, 0x60, 0xdc, 0xfe, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e, 0x3c,
    /* U+0037 "7" (8x12) */
    0xff, 0xff, 0xc7, 0xc7, 0x06, 0x0e, 0x0c, 0x1c, 0x1c, 0x18, 0x38, 0x38,
    /* U+0038 "8" (8x12) */
    0x3c, 0xff, 0xc3, 0xc3, 0xc3, 0x7e, 0x7e, 0xc3, 0xc3, 0xc3, 0x7e, 0x3c,
    /* U+0039 "9" (8x12) */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7f, 0x3a, 0x06, 0x0c, 0x1c, 0x38,
    /* U+003A ":" (3x9) */
    0xff, 0x80, 0x3f, 0xe0,
    /* U+003B ";" (3x11) */
    0xff, 0x80, 0x3f, 0xda, 0x00,
    /* U+003C "<" (7x10) */
    0x02, 0x1c, 0xf7, 0x8e, 0x1c, 0x1e, 0x0f, 0x0e, 0x04,
    /* U+003D "=" (8x6) */
    0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
    /* U+003E ">" (7x10) */
    0x81, 0xc1, 0xe0, 0xf0, 0xe1, 0xcf, 0x78, 0xe1, 0x00,
    /* U+003F "?" (7x12) */
    0x38, 0xfb, 0x98, 0x30, 0x61, 0xc7, 0x0c, 0x00, 0x70, 0xe1, 0xc0,
    /* U+0040 "@" (8x14) */
    0x3c, 0x7e, 0x63, 0xcf, 0xdf, 0xdb, 0xdb, 0xdb, 0xdb, 0xdf, 0xcf, 0x60,
    0x7c, 0x3c,
    /* U+0041 "A" (9x12) */
    0x1e, 0x0f, 0x0f, 0x86, 0xc3, 0x71, 0x99, 0xcc, 0xfe, 0x7f, 0xb1, 0xf8,
    0x7c, 0x30,
    /* U+0042 "B" (7x12) */
    0xfd, 0xff, 0x1e, 0x3c, 0x7f, 0xbf, 0x63, 0xc7, 0x8f, 0xff, 0xe0,
    /* U+0043 "C" (8x12) */
    0x3c, 0x7e, 0x67, 0xc6, 0xc0, 0xc0, 0xc0, 0xc0, 0xc6, 0x67, 0x7e, 0x3c,
    /* U+0044 "D" (8x12) */
    0xfc, 0xfe, 0xc6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc6, 0xfe, 0xfc,
    /* U+0045 "E" (7x12) */
    0xff, 0xff, 0x06, 0x0c, 0x1f, 0xff, 0xe0, 0xc1, 0x83, 0xff, 0xf0,
    /* U+0046 "F" (8x12) */
    0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xfe, 0xfe, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    /* U+0047 "G" (8x12) */
    0x3c, 0x7e, 0x67, 0xc0, 0xc0, 0xcf, 0xcf, 0xc3, 0xc3, 0xe7, 0x7f, 0x3b,
    /* U+0048 "H" (7x12) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x7f, 0xff, 0xe3, 0xc7, 0x8f, 0x1e, 0x30,
    /* U+0049 "I" (7x12) */
    0xff, 0xfc, 0x60, 0xc1, 0x83, 0x06, 0x0c, 0x18, 0x33, 0xff, 0xf0,
    /* U+004A "J" (7x12) */
    0x7e, 0xfc, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x47, 0xcd, 0xf1, 0xe0,
    /* U+004B "K" (8x12) */
    0xc7, 0xce, 0xcc, 0xdc, 0xf8, 0xf8, 0xf8, 0xfc, 0xcc, 0xce, 0xc6, 0xc7,
    /* U+004C "L" (7x12) */
    0xc1, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x83, 0xff, 0xf0,
    /* U+004D "M" (8x12) */
    0xe7, 0xe7, 0xf7, 0xff, 0xdb, 0xdb, 0xdb, 0xdb, 0xd3, 0xc3, 0xc3, 0xc3,
    /* U+004E "N" (8x12) */
    0xe3, 0xe3, 0xf3, 0xf3, 0xfb, 0xdb, 0xdb, 0xdf, 0xcf, 0xcf, 0xc7, 0xc7,
    /* U+004F "O" (8x12) */
    0x3c, 0x7e, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xe6, 0x7e, 0x3c,
    /* U+0050 "P" (7x12) */
    0xfd, 0xfb, 0x1e, 0x3c, 0x78, 0xff, 0x7e, 0xc1, 0x83, 0x06, 0x00,
    /* U+0051 "Q" (8x15) */
    0x3c, 0x7e, 0xe6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x7e, 0x3c,
    0x18, 0x1e, 0x0e,
    /* U+0052 "R" (7x12) */
    0xfd, 0xfb, 0x1e, 0x3c, 0x78, 0xff, 0xfe, 0xdd, 0x9b, 0x3e, 0x30,
    /* U+0053 "S" (8x12) */
    0x3e, 0x7f, 0xc2, 0xc0, 0xe0, 0x7e, 0x3f, 0x03, 0x03, 0xc3, 0xfe, 0x7c,
    /* U+0054 "T" (9x12) */
    0xff, 0xff, 0xc6, 0x03, 0x01, 0x80, 0xc0, 0x60, 0x30, 0x18, 0x0c, 0x06,
    0x03, 0x00,
    /* U+0055 "U" (8x12) */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x7e, 0x3c,
    /* U+0056 "V" (9x12) */
    0xe1, 0xb0, 0xd8, 0xee, 0x77, 0x33, 0x98, 0xdc, 0x6e, 0x3e, 0x1f, 0x07,
    0x83, 0xc0,
    /* U+0057 "W" (9x12) */
    0xc1, 0xe0, 0xf0, 0x7b, 0xbd, 0xde, 0xaf, 0x57, 0xab, 0xd5, 0xfb, 0xfd,
    0xfe, 0xf0,
    /* U+0058 "X" (9x12) */
    0x63, 0xb9, 0xcc, 0xc7, 0xe1, 0xe0, 0xe0, 0x78, 0x7c, 0x37, 0x39, 0x98,
    0xfc, 0x70,
    /* U+0059 "Y" (8x12) */
    0xc3, 0xe7, 0x66, 0x66, 0x3c, 0x3c, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x18,
    /* U+005A "Z" (8x12) */
    0xff, 0xff, 0x07, 0x0e, 0x0c, 0x1c, 0x38, 0x30, 0x70, 0xe0, 0xff, 0xff,
    /* U+005B "[" (5x16) */
    0xff, 0xf1, 0x8c, 0x63, 0x18, 0xc6, 0x31, 0x8c, 0x63, 0xff,
    /* U+005C "" (7x16) */
    0xc0, 0xc1, 0x83, 0x03, 0x06, 0x0c, 0x0c, 0x18, 0x30, 0x30, 0x60, 0xc0,
    0xc1, 0x83,
    /* U+005D "]" (6x16) */
    0xff, 0xf0, 0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0x3f, 0xff,
    /* U+005E "^" (9x7) */
    0x1c, 0x0f, 0x0d, 0x86, 0x67, 0x33, 0x1f, 0x86,
    /* U+005F "_" (8x2) */
    0xff, 0xff,
    /* U+0060 "`" (3x4) */
    0x5b, 0x30,
    /* U+0061 "a" (8x9) */
    0x7c, 0xfe, 0x46, 0x06, 0x7e, 0xfe, 0xc6, 0xff, 0x77,
    /* U+0062 "b" (8x13) */
    0xc0, 0xc0, 0xc0, 0xc0, 0xdc, 0xfe, 0xc7, 0xc3, 0xc3, 0xc3, 0xc7, 0xfe,
    0xde,
    /* U+0063 "c" (7x9) */
    0x3c, 0xff, 0x16, 0x0c, 0x18, 0x31, 0xbf, 0x3c,
    /* U+0064 "d" (8x13) */
    0x03, 0x03, 0x03, 0x03, 0x3b, 0x7f, 0xe3, 0xc3, 0xc3, 0xc3, 0xe3, 0x7f,
    0x3b,
    /* U+0065 "e" (8x9) */
    0x3c, 0x7e, 0xc3, 0xff, 0xff, 0xc0, 0xe2, 0x7f, 0x3c,
    /* U+0066 "f" (8x13) */
    0x0f, 0x1f, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0xfe,
    0xfe,
    /* U+0067 "g" (8x14) */
    0x06, 0x06, 0x3c, 0x7e, 0x66, 0x66, 0x7e, 0x3c, 0x60, 0x7e, 0x3f, 0xc3,
    0xff, 0x7e,
    /* U+0068 "h" (7x13) */
    0xc1, 0x83, 0x06, 0x0d, 0xdf, 0xf1, 0xe3, 0xc7, 0x8f, 0x1e, 0x3c, 0x60,
    /* U+0069 "i" (7x13) */
    0x38, 0x70, 0xe0, 0x0f, 0x9f, 0x0e, 0x1c, 0x38, 0x70, 0xe7, 0xff, 0xe0,
    /* U+006A "j" (5x16) */
    0x18, 0xc6, 0x0f, 0xfc, 0x63, 0x18, 0xc6, 0x31, 0x8f, 0xfe,
    /* U+006B "k" (8x13) */
    0xc0, 0xc0, 0xc0, 0xc0, 0xc6, 0xcc, 0xd8, 0xf8, 0xf8, 0xdc, 0xcc, 0xce,
    0xc7,
    /* U+006C "l" (7x13) */
    0xf9, 0xf0, 0x60, 0xc1, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x67, 0xff, 0xe0,
    /* U+006D "m" (8x9) */
    0xd6, 0xff, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb,
    /* U+006E "n" (7x9) */
    0xdd, 0xff, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,
    /* U+006F "o" (8x9) */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xe7, 0x7e, 0x3c,
    /* U+0070 "p" (8x12) */
    0xdc, 0xfe, 0xc7, 0xc3, 0xc3, 0xc3, 0xc7, 0xfe, 0xdc, 0xc0, 0xc0, 0xc0,
    /* U+0071 "q" (8x12) */
    0x3b, 0x7f, 0xe3, 0xc3, 0xc3, 0xc3, 0xe3, 0x7f, 0x3b, 0x03, 0x03, 0x03,
    /* U+0072 "r" (8x9) */
    0xf7, 0xff, 0x38, 0x30, 0x30, 0x30, 0x30, 0xfc, 0xfc,
    /* U+0073 "s" (7x9) */
    0x7d, 0xff, 0x17, 0x07, 0xc1, 0xf1, 0xff, 0x7c,
    /* U+0074 "t" (8x12) */
    0x30, 0x30, 0x30, 0xff, 0xff, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3f, 0x1f,
    /* U+0075 "u" (7x9) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xff, 0x76,
    /* U+0076 "v" (8x9) */
    0xc3, 0xc7, 0xe6, 0x66, 0x66, 0x6c, 0x3c, 0x3c, 0x38,
    /* U+0077 "w" (9x9) */
    0xcc, 0xe6, 0xf7, 0x7b, 0xb5, 0x7b, 0xbd, 0xde, 0xe7, 0x73, 0x80,
    /* U+0078 "x" (8x9) */
    0xe7, 0x66, 0x7c, 0x3c, 0x38, 0x3c, 0x6e, 0xe6, 0xc7,
    /* U+0079 "y" (9x12) */
    0xe1, 0xb1, 0xdc, 0xc6, 0x63, 0x61, 0xb0, 0x78, 0x38, 0x1c, 0x0c, 0x1e,
    0x0e, 0x00,
    /* U+007A "z" (7x9) */
    0xff, 0xfc, 0x38, 0xe3, 0x8e, 0x38, 0x7f, 0xfe,
    /* U+007B "{" (7x16) */
    0x1e, 0x7c, 0xc1, 0x83, 0x03, 0x06, 0x78, 0xf0, 0x30, 0x61, 0x83, 0x06,
    0x0f, 0x9f,
    /* U+007C "|" (2x15) */
    0xff, 0xff, 0xff, 0xfc,
    /* U+007D "}" (7x16) */
    0xf9, 0xf0, 0x60, 0xc1, 0x86, 0x0c, 0x0f, 0x1e, 0x60, 0xc0, 0xc1, 0x83,
    0x3e, 0x7c,
    /* U+007E "~" (8x4) */
    0x73, 0xfb, 0xde, 0x8e,
    /* U+00B0 "" (6x7) */
    0x79, 0xec, 0xf3, 0xcd, 0xe7, 0x80,
    /* U+00B1 "" (8x10) */
    0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18, 0x00, 0xff, 0xff,
    /* U+00B2 "" (5x6) */
    0xf4, 0xc6, 0x6e, 0x7c,
    /* U+00B3 "" (4x6) */
    0xf3, 0x63, 0xbe,
    /* U+00B5 "" (7x11) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x7c, 0xff, 0xfb, 0xc1, 0x83, 0x00,
    /* U+00B7 "" (3x3) */
    0xff, 0x80,
    /* U+00D7 "" (7x8) */
    0x43, 0xcd, 0xf1, 0xc3, 0xcf, 0xf9, 0xa0,
    /* U+00F7 "" (8x10) */
    0x38, 0x38, 0x38, 0x00, 0xff, 0xff, 0x00, 0x38, 0x38, 0x38,
    /* U+0394 "" (8x11) */
    0x3c, 0x3c, 0x3e, 0x36, 0x76, 0x66, 0x67, 0xe3, 0xe3, 0xff, 0xff,
    /* U+03A9 "" (9x11) */
    0x3e, 0x3f, 0xb8, 0xdc, 0x7e, 0x3f, 0x1f, 0x8d, 0xc6, 0x76, 0x7b, 0xfd,
    0xe0,
    /* U+03BC "" (7x11) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x7c, 0xff, 0xfb, 0xc1, 0x83, 0x00,
    /* U+03C0 "" (9x8) */
    0xff, 0xff, 0xd8, 0xcc, 0x66, 0x33, 0x19, 0x8e, 0xc7,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 154, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 154, .box_w = 3, .box_h = 12, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 5, .adv_w = 154, .box_w = 6, .box_h = 5, .ofs_x = 2, .ofs_y = 8},
    {.bitmap_index = 9, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 23, .adv_w = 154, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 38, .adv_w = 154, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 53, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 67, .adv_w = 154, .box_w = 2, .box_h = 5, .ofs_x = 4, .ofs_y = 8},
    {.bitmap_index = 69, .adv_w = 154, .box_w = 5, .box_h = 15, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 79, .adv_w = 154, .box_w = 5, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 89, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 97, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 105, .adv_w = 154, .box_w = 3, .box_h = 5, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 107, .adv_w = 154, .box_w = 5, .box_h = 2, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 109, .adv_w = 154, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 154, .box_w = 7, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 125, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 153, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 177, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 191, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 203, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 215, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 227, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 239, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 154, .box_w = 3, .box_h = 9, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 255, .adv_w = 154, .box_w = 3, .box_h = 11, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 260, .adv_w = 154, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 269, .adv_w = 154, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 275, .adv_w = 154, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 284, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 295, .adv_w = 154, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 309, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 323, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 334, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 346, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 358, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 369, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 381, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 393, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 404, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 415, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 426, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 438, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 449, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 461, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 473, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 485, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 496, .adv_w = 154, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 511, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 522, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 534, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 548, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 560, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 574, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 588, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 602, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 614, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 626, .adv_w = 154, .box_w = 5, .box_h = 16, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 636, .adv_w = 154, .box_w = 7, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 650, .adv_w = 154, .box_w = 6, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 662, .adv_w = 154, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 670, .adv_w = 154, .box_w = 8, .box_h = 2, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 672, .adv_w = 154, .box_w = 3, .box_h = 4, .ofs_x = 3, .ofs_y = 10},
    {.bitmap_index = 674, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 683, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 696, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 704, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 717, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 726, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 739, .adv_w = 154, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 753, .adv_w = 154, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 765, .adv_w = 154, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 777, .adv_w = 154, .box_w = 5, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 787, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 800, .adv_w = 154, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 812, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 821, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 829, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 838, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 850, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 862, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 871, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 879, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 891, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 899, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 908, .adv_w = 154, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 919, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 928, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 942, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 950, .adv_w = 154, .box_w = 7, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 964, .adv_w = 154, .box_w = 2, .box_h = 15, .ofs_x = 4, .ofs_y = -2},
    {.bitmap_index = 968, .adv_w = 154, .box_w = 7, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 982, .adv_w = 154, .box_w = 8, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 986, .adv_w = 154, .box_w = 6, .box_h = 7, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 992, .adv_w = 154, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1002, .adv_w = 154, .box_w = 5, .box_h = 6, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 1006, .adv_w = 154, .box_w = 4, .box_h = 6, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 1009, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1019, .adv_w = 154, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 3},
    {.bitmap_index = 1021, .adv_w = 154, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1028, .adv_w = 154, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1038, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1049, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1062, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1072, .adv_w = 154, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 0}
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
const lv_font_t humid1_font_plex_mono_bold_16 = {
#else
lv_font_t humid1_font_plex_mono_bold_16 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 22,
    .base_line = 5,
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc,
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_font_plex_sans_bold_16,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_MONO_BOLD_16 */
