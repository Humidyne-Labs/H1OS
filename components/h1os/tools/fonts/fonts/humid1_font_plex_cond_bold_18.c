/*******************************************************************************
 * Font: humid1_font_plex_cond_bold_18 (IBM Plex Cond Bold)
 * Size: 18 px @ 188 DPI (SSD1681 1-bit E-Paper Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Raster Mode: autohint-mono (FT_LOAD_TARGET_MONO + Dropout Control)
 * License: SIL Open Font License 1.1 (IBM Corp.) / Font Awesome Free License
 ******************************************************************************/

#include "lvgl.h"

#ifndef HUMID1_FONT_PLEX_COND_BOLD_18
#define HUMID1_FONT_PLEX_COND_BOLD_18 1
#endif

#if HUMID1_FONT_PLEX_COND_BOLD_18

extern const lv_font_t humid1_font_plex_sans_bold_18;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (3x13) */
    0xff, 0xff, 0xfa, 0x43, 0xfe,
    /* U+0022 "" (6x6) */
    0xcf, 0x3c, 0xf3, 0xcf, 0x30,
    /* U+0023 "#" (10x13) */
    0x19, 0x84, 0x41, 0x11, 0xff, 0x7f, 0xcc, 0xc3, 0x30, 0xcc, 0xff, 0xbf,
    0xe2, 0x20, 0x88, 0x66, 0x00,
    /* U+0024 "$" (9x17) */
    0x18, 0x0c, 0x0f, 0x8f, 0xfe, 0xb7, 0x43, 0xa1, 0xf8, 0x7f, 0x07, 0xc2,
    0xe1, 0x7c, 0xbf, 0xf8, 0xf8, 0x30, 0x18, 0x00,
    /* U+0025 "%" (14x13) */
    0x78, 0x73, 0xf1, 0x8c, 0xce, 0x33, 0x70, 0xcd, 0x83, 0xff, 0xe7, 0xbf,
    0xc1, 0xf3, 0x06, 0xcc, 0x3b, 0x31, 0xcc, 0xc6, 0x3f, 0x38, 0x78,
    /* U+0026 "&" (11x13) */
    0x3e, 0x0f, 0xe1, 0xdc, 0x3b, 0x87, 0x70, 0x7c, 0x0e, 0x3b, 0xe7, 0xe7,
    0xdc, 0xf3, 0x9e, 0x7e, 0xe7, 0x8e,
    /* U+0027 "'" (2x6) */
    0xff, 0xf0,
    /* U+0028 "(" (5x16) */
    0x19, 0xdc, 0xe6, 0x73, 0x9c, 0xe7, 0x39, 0xc7, 0x38, 0xe3,
    /* U+0029 ")" (5x16) */
    0xc7, 0x1c, 0xe3, 0x9c, 0xe7, 0x39, 0xce, 0x77, 0x3b, 0x98,
    /* U+002A "" (8x9) */
    0x18, 0x18, 0x99, 0xff, 0xff, 0x18, 0x3c, 0x66, 0x64,
    /* U+002B "+" (8x8) */
    0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18,
    /* U+002C "," (3x5) */
    0xff, 0xbc,
    /* U+002D "-" (5x2) */
    0xff, 0xc0,
    /* U+002E "." (3x3) */
    0xff, 0x80,
    /* U+002F "/" (7x17) */
    0x06, 0x1c, 0x30, 0x60, 0xc3, 0x06, 0x0c, 0x38, 0x60, 0xc1, 0x86, 0x0c,
    0x18, 0x60, 0xc0,
    /* U+0030 "0" (9x13) */
    0x3e, 0x3f, 0x98, 0xdc, 0x7e, 0x3f, 0x1f, 0x8f, 0xc7, 0xe3, 0xf1, 0xd8,
    0xcf, 0xe3, 0xe0,
    /* U+0031 "1" (9x13) */
    0x3e, 0x3f, 0x1b, 0x9d, 0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x03,
    0x8f, 0xf7, 0xf8,
    /* U+0032 "2" (8x13) */
    0x3c, 0xfe, 0xe7, 0x47, 0x07, 0x07, 0x0e, 0x1c, 0x38, 0x70, 0xe0, 0xff,
    0xff,
    /* U+0033 "3" (8x13) */
    0x3c, 0xff, 0xc7, 0x07, 0x07, 0x3e, 0x3e, 0x07, 0x07, 0x47, 0xc7, 0xfe,
    0x7c,
    /* U+0034 "4" (9x13) */
    0x0f, 0x0f, 0x85, 0xc6, 0xe3, 0x73, 0x39, 0x9d, 0x8e, 0xff, 0xff, 0xc1,
    0xc0, 0xe0, 0x70,
    /* U+0035 "5" (8x13) */
    0xfe, 0xfe, 0xc0, 0xc0, 0xdc, 0xfe, 0xc7, 0x07, 0x07, 0x47, 0xc7, 0xfe,
    0x7c,
    /* U+0036 "6" (9x13) */
    0x0e, 0x0e, 0x0e, 0x0e, 0x07, 0x07, 0x7b, 0xfd, 0xc7, 0xe3, 0xf1, 0xf8,
    0xef, 0xe3, 0xe0,
    /* U+0037 "7" (8x13) */
    0xff, 0xff, 0xc7, 0xc7, 0x06, 0x0e, 0x0e, 0x0c, 0x1c, 0x1c, 0x18, 0x38,
    0x38,
    /* U+0038 "8" (8x13) */
    0x7e, 0xff, 0xe7, 0xe7, 0xe7, 0x3c, 0x7e, 0xe7, 0xe7, 0xe7, 0xe7, 0x7e,
    0x3c,
    /* U+0039 "9" (9x13) */
    0x3e, 0x3f, 0xb8, 0xfc, 0x7e, 0x3f, 0x1f, 0xfe, 0xf7, 0x07, 0x03, 0x83,
    0x83, 0x83, 0x80,
    /* U+003A ":" (3x10) */
    0xff, 0x80, 0x07, 0xfc,
    /* U+003B ";" (3x12) */
    0xff, 0x80, 0x07, 0xfd, 0xe0,
    /* U+003C "<" (7x11) */
    0x02, 0x1c, 0x7b, 0xcf, 0x1c, 0x3c, 0x1c, 0x1e, 0x1c, 0x08,
    /* U+003D "=" (8x6) */
    0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
    /* U+003E ">" (7x11) */
    0x81, 0x83, 0xc3, 0xc1, 0xe1, 0xc7, 0xbc, 0xf1, 0x82, 0x00,
    /* U+003F "?" (8x13) */
    0x3c, 0x7e, 0xe7, 0x47, 0x07, 0x0f, 0x3e, 0x38, 0x38, 0x00, 0x38, 0x38,
    0x38,
    /* U+0040 "@" (13x16) */
    0x0f, 0x81, 0xff, 0x0c, 0x1c, 0xc0, 0x66, 0x03, 0xe7, 0x6f, 0x7f, 0x7b,
    0x1b, 0xd8, 0xde, 0xc6, 0xf6, 0x37, 0xff, 0xe6, 0xe7, 0x1c, 0x00, 0xff,
    0x01, 0xf8,
    /* U+0041 "A" (11x13) */
    0x0e, 0x03, 0xe0, 0x6c, 0x0d, 0x81, 0xb0, 0x77, 0x0e, 0xe1, 0x8c, 0x3f,
    0xcf, 0xf9, 0x83, 0x30, 0x6e, 0x0e,
    /* U+0042 "B" (9x13) */
    0xff, 0x7f, 0xf8, 0xfc, 0x7e, 0x3f, 0xf3, 0xfd, 0xc7, 0xe3, 0xf1, 0xf8,
    0xff, 0xef, 0xf0,
    /* U+0043 "C" (10x13) */
    0x1f, 0x1f, 0xe7, 0x1b, 0x84, 0xe0, 0x38, 0x0e, 0x03, 0x80, 0xe0, 0x38,
    0x47, 0x1d, 0xfe, 0x1f, 0x00,
    /* U+0044 "D" (9x13) */
    0xfe, 0x7f, 0xb9, 0xdc, 0x7e, 0x3f, 0x1f, 0x8f, 0xc7, 0xe3, 0xf1, 0xf9,
    0xdf, 0xef, 0xe0,
    /* U+0045 "E" (8x13) */
    0xff, 0xff, 0xe0, 0xe0, 0xe0, 0xfe, 0xfe, 0xe0, 0xe0, 0xe0, 0xe0, 0xff,
    0xff,
    /* U+0046 "F" (8x13) */
    0xff, 0xff, 0xe0, 0xe0, 0xe0, 0xfe, 0xfe, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
    0xe0,
    /* U+0047 "G" (10x13) */
    0x1f, 0x1f, 0xe7, 0x1f, 0x82, 0xe0, 0x38, 0x0e, 0x3f, 0x8f, 0xe0, 0xf8,
    0x37, 0x1d, 0xff, 0x1e, 0xc0,
    /* U+0048 "H" (10x13) */
    0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xff, 0xff, 0xff, 0x87, 0xe1, 0xf8,
    0x7e, 0x1f, 0x87, 0xe1, 0xc0,
    /* U+0049 "I" (6x13) */
    0xff, 0xf7, 0x1c, 0x71, 0xc7, 0x1c, 0x71, 0xc7, 0x3f, 0xfc,
    /* U+004A "J" (8x13) */
    0x7f, 0x7f, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x47, 0xe7, 0x7e,
    0x3c,
    /* U+004B "K" (10x13) */
    0xe1, 0xf8, 0xee, 0x3b, 0x9c, 0xe6, 0x3b, 0x8f, 0xe3, 0xf8, 0xf7, 0x39,
    0xce, 0x3b, 0x87, 0xe1, 0xc0,
    /* U+004C "L" (7x13) */
    0xe1, 0xc3, 0x87, 0x0e, 0x1c, 0x38, 0x70, 0xe1, 0xc3, 0x87, 0xff, 0xe0,
    /* U+004D "M" (11x13) */
    0xe0, 0xfe, 0x3f, 0xc7, 0xfd, 0xff, 0xbf, 0xd5, 0xfa, 0xbf, 0x77, 0xe4,
    0xfc, 0x9f, 0x93, 0xf0, 0x7e, 0x0e,
    /* U+004E "N" (10x13) */
    0xf1, 0xfc, 0x7f, 0x1f, 0xe7, 0xf9, 0xfb, 0x7e, 0xdf, 0xb7, 0xe7, 0xf9,
    0xfe, 0x3f, 0x8f, 0xe3, 0xc0,
    /* U+004F "O" (10x13) */
    0x1e, 0x1f, 0xe7, 0x3b, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xf8,
    0x77, 0x39, 0xfe, 0x1e, 0x00,
    /* U+0050 "P" (9x13) */
    0xfe, 0x7f, 0xb8, 0xfc, 0x7e, 0x3f, 0x1f, 0xfd, 0xfe, 0xe0, 0x70, 0x38,
    0x1c, 0x0e, 0x00,
    /* U+0051 "Q" (10x17) */
    0x1e, 0x1f, 0xe7, 0x3b, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xf8,
    0x7e, 0x1d, 0xfe, 0x3f, 0x87, 0xc0, 0xe0, 0x3c, 0x07, 0x00,
    /* U+0052 "R" (9x13) */
    0xfe, 0x7f, 0xb8, 0xfc, 0x7e, 0x3f, 0x1f, 0xfd, 0xfc, 0xe6, 0x73, 0x39,
    0xdc, 0x6e, 0x38,
    /* U+0053 "S" (9x13) */
    0x3e, 0x3f, 0xf8, 0xdc, 0x0e, 0x07, 0xf1, 0xfc, 0x3f, 0x03, 0x81, 0xf0,
    0xff, 0xe7, 0xe0,
    /* U+0054 "T" (9x13) */
    0xff, 0xff, 0xc7, 0x03, 0x81, 0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07,
    0x03, 0x81, 0xc0,
    /* U+0055 "U" (9x13) */
    0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f, 0xc7, 0xe3, 0xf1, 0xf8,
    0xef, 0xe3, 0xe0,
    /* U+0056 "V" (10x13) */
    0xe0, 0xd8, 0x36, 0x1d, 0xc7, 0x71, 0x8c, 0x63, 0x38, 0xec, 0x1b, 0x06,
    0xc1, 0xb0, 0x78, 0x0e, 0x00,
    /* U+0057 "W" (14x13) */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf9, 0xe7, 0xe7, 0x9d, 0xb7, 0x66, 0xcd,
    0x9b, 0x36, 0x6c, 0xd9, 0xb3, 0x63, 0xcf, 0x0e, 0x1c, 0x38, 0x70,
    /* U+0058 "X" (9x13) */
    0xe1, 0xf1, 0xdc, 0xce, 0xe3, 0xe1, 0xf0, 0x70, 0x7c, 0x36, 0x3b, 0x98,
    0xdc, 0x7c, 0x18,
    /* U+0059 "Y" (11x13) */
    0xe0, 0xee, 0x39, 0xc7, 0x18, 0xc3, 0xb8, 0x36, 0x07, 0xc0, 0x70, 0x0e,
    0x01, 0xc0, 0x38, 0x07, 0x00, 0xe0,
    /* U+005A "Z" (8x13) */
    0xff, 0xff, 0x07, 0x0e, 0x0e, 0x1c, 0x38, 0x38, 0x70, 0x60, 0xe0, 0xff,
    0xff,
    /* U+005B "[" (3x17) */
    0xff, 0x6d, 0xb6, 0xdb, 0x6d, 0xb7, 0xe0,
    /* U+005C "" (7x17) */
    0xc1, 0x83, 0x03, 0x06, 0x0c, 0x0c, 0x18, 0x30, 0x60, 0x60, 0xc1, 0x81,
    0x83, 0x06, 0x0e,
    /* U+005D "]" (3x17) */
    0xfd, 0xb6, 0xdb, 0x6d, 0xb6, 0xdf, 0xe0,
    /* U+005E "^" (8x8) */
    0x18, 0x3c, 0x3c, 0x6e, 0x66, 0xe7, 0xc3, 0x42,
    /* U+005F "_" (8x2) */
    0xff, 0xff,
    /* U+0060 "`" (3x4) */
    0xdb, 0xb0,
    /* U+0061 "a" (8x10) */
    0x3e, 0x7f, 0x67, 0x07, 0x7f, 0xff, 0xe7, 0xe7, 0xff, 0x77,
    /* U+0062 "b" (8x14) */
    0xe0, 0xe0, 0xe0, 0xe0, 0xee, 0xfe, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7,
    0xfe, 0xee,
    /* U+0063 "c" (8x10) */
    0x3c, 0x7e, 0xe7, 0xe0, 0xe0, 0xe0, 0xe0, 0xe7, 0x7e, 0x3c,
    /* U+0064 "d" (8x14) */
    0x07, 0x07, 0x07, 0x07, 0x77, 0x7f, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7,
    0x7f, 0x77,
    /* U+0065 "e" (8x10) */
    0x3c, 0x7e, 0xe7, 0xe7, 0xff, 0xff, 0xe0, 0xe2, 0x7f, 0x3c,
    /* U+0066 "f" (5x14) */
    0x3b, 0xdc, 0xef, 0xfd, 0xce, 0x73, 0x9c, 0xe7, 0x38,
    /* U+0067 "g" (9x16) */
    0x07, 0x03, 0x9f, 0x1f, 0xce, 0x77, 0x3b, 0x9c, 0xfc, 0x3e, 0x60, 0x3f,
    0xc7, 0xfc, 0x3e, 0x1f, 0xfe, 0xfc,
    /* U+0068 "h" (8x14) */
    0xe0, 0xe0, 0xe0, 0xe0, 0xee, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7,
    0xe7, 0xe7,
    /* U+0069 "i" (3x14) */
    0xff, 0x8f, 0xff, 0xff, 0xff, 0xc0,
    /* U+006A "j" (5x18) */
    0x39, 0xce, 0x03, 0x9c, 0xe7, 0x39, 0xce, 0x73, 0x9c, 0xe7, 0xff, 0x80,
    /* U+006B "k" (8x14) */
    0xe0, 0xe0, 0xe0, 0xe0, 0xe3, 0xe7, 0xee, 0xec, 0xfc, 0xfc, 0xfe, 0xe6,
    0xe7, 0xe3,
    /* U+006C "l" (4x14) */
    0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xf7,
    /* U+006D "m" (13x10) */
    0xee, 0x77, 0xff, 0xf9, 0xcf, 0xce, 0x7e, 0x73, 0xf3, 0x9f, 0x9c, 0xfc,
    0xe7, 0xe7, 0x3f, 0x39, 0xc0,
    /* U+006E "n" (8x10) */
    0xee, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7,
    /* U+006F "o" (8x10) */
    0x3c, 0x7e, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0x7e, 0x3c,
    /* U+0070 "p" (8x14) */
    0xee, 0xfe, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xfe, 0xee, 0xe0, 0xe0,
    0xe0, 0xe0,
    /* U+0071 "q" (8x14) */
    0x77, 0x7f, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0x7f, 0x77, 0x07, 0x07,
    0x07, 0x07,
    /* U+0072 "r" (5x10) */
    0xef, 0xf9, 0xce, 0x73, 0x9c, 0xe7, 0x00,
    /* U+0073 "s" (7x10) */
    0x7d, 0xff, 0x97, 0x0f, 0xcf, 0xc3, 0xa7, 0xfe, 0xf8,
    /* U+0074 "t" (5x13) */
    0x73, 0x9d, 0xff, 0xb9, 0xce, 0x73, 0x9c, 0xf3, 0x80,
    /* U+0075 "u" (8x10) */
    0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0x77,
    /* U+0076 "v" (9x10) */
    0xe3, 0xf1, 0x98, 0xcc, 0xe7, 0x71, 0xb0, 0xd8, 0x6c, 0x3c, 0x0e, 0x00,
    /* U+0077 "w" (13x10) */
    0xe7, 0x1b, 0x38, 0xd9, 0xe6, 0xcf, 0x76, 0x5b, 0x3e, 0xd8, 0xf2, 0xc7,
    0x9e, 0x3c, 0xe1, 0xc7, 0x00,
    /* U+0078 "x" (9x10) */
    0xe3, 0xb9, 0x9d, 0xc6, 0xc3, 0xe0, 0xe0, 0xf8, 0x6c, 0x77, 0x31, 0xc0,
    /* U+0079 "y" (9x14) */
    0xe3, 0xb1, 0xd8, 0xce, 0x63, 0x71, 0xb0, 0xd8, 0x6c, 0x1e, 0x0e, 0x07,
    0x03, 0x87, 0x83, 0xc0,
    /* U+007A "z" (7x10) */
    0xff, 0xfc, 0x38, 0xe3, 0x87, 0x1c, 0x70, 0xff, 0xfc,
    /* U+007B "{" (5x17) */
    0x39, 0xcc, 0x63, 0x18, 0xc6, 0xe7, 0x0c, 0x63, 0x18, 0xc7, 0x38,
    /* U+007C "|" (2x16) */
    0xff, 0xff, 0xff, 0xff,
    /* U+007D "}" (5x17) */
    0xe7, 0x18, 0xc6, 0x31, 0x8c, 0x39, 0xd8, 0xc6, 0x31, 0x9c, 0xe0,
    /* U+007E "~" (8x3) */
    0xf0, 0xff, 0x0e,
    /* U+00B0 "" (6x7) */
    0x7b, 0xfc, 0xf3, 0xcf, 0xe7, 0x80,
    /* U+00B1 "" (8x11) */
    0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18, 0x00, 0x00, 0xff, 0xff,
    /* U+00B2 "" (5x7) */
    0x74, 0xc6, 0x77, 0x73, 0xe0,
    /* U+00B3 "" (5x7) */
    0xf4, 0xc6, 0xe1, 0xcf, 0xc0,
    /* U+00B5 "" (8x14) */
    0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0xd7, 0xe0, 0xe0,
    0xe0, 0xe0,
    /* U+00B7 "" (3x3) */
    0xff, 0x80,
    /* U+00D7 "" (7x8) */
    0x41, 0xcd, 0xf9, 0xe3, 0xcf, 0xf9, 0xa1,
    /* U+00F7 "" (8x10) */
    0x38, 0x38, 0x38, 0x00, 0xff, 0xff, 0x00, 0x38, 0x38, 0x38,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 61, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 84, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 5, .adv_w = 130, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 10, .adv_w = 162, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 27, .adv_w = 154, .box_w = 9, .box_h = 17, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 47, .adv_w = 255, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 70, .adv_w = 188, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 70, .box_w = 2, .box_h = 6, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 90, .adv_w = 88, .box_w = 5, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 100, .adv_w = 88, .box_w = 5, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 110, .adv_w = 160, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 119, .adv_w = 156, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 127, .adv_w = 82, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 129, .adv_w = 104, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 131, .adv_w = 82, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 122, .box_w = 7, .box_h = 17, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 148, .adv_w = 156, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 163, .adv_w = 156, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 178, .adv_w = 156, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 191, .adv_w = 156, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 204, .adv_w = 156, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 219, .adv_w = 156, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 232, .adv_w = 156, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 247, .adv_w = 156, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 260, .adv_w = 156, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 273, .adv_w = 156, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 288, .adv_w = 88, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 292, .adv_w = 88, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 297, .adv_w = 156, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 156, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 313, .adv_w = 156, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 323, .adv_w = 130, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 336, .adv_w = 234, .box_w = 13, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 362, .adv_w = 178, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 380, .adv_w = 173, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 395, .adv_w = 170, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 412, .adv_w = 181, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 427, .adv_w = 158, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 440, .adv_w = 152, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 453, .adv_w = 186, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 470, .adv_w = 188, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 487, .adv_w = 114, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 497, .adv_w = 146, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 510, .adv_w = 181, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 527, .adv_w = 138, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 539, .adv_w = 213, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 557, .adv_w = 188, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 574, .adv_w = 185, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 591, .adv_w = 171, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 606, .adv_w = 185, .box_w = 10, .box_h = 17, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 628, .adv_w = 176, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 643, .adv_w = 160, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 658, .adv_w = 152, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 673, .adv_w = 181, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 688, .adv_w = 172, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 705, .adv_w = 255, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 728, .adv_w = 176, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 743, .adv_w = 167, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 761, .adv_w = 157, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 774, .adv_w = 87, .box_w = 3, .box_h = 17, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 781, .adv_w = 122, .box_w = 7, .box_h = 17, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 796, .adv_w = 87, .box_w = 3, .box_h = 17, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 803, .adv_w = 156, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 811, .adv_w = 144, .box_w = 8, .box_h = 2, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 813, .adv_w = 156, .box_w = 3, .box_h = 4, .ofs_x = 3, .ofs_y = 11},
    {.bitmap_index = 815, .adv_w = 149, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 825, .adv_w = 158, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 839, .adv_w = 135, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 849, .adv_w = 158, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 863, .adv_w = 146, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 873, .adv_w = 98, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 882, .adv_w = 144, .box_w = 9, .box_h = 16, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 900, .adv_w = 156, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 914, .adv_w = 75, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 920, .adv_w = 77, .box_w = 5, .box_h = 18, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 932, .adv_w = 151, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 946, .adv_w = 80, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 953, .adv_w = 233, .box_w = 13, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 970, .adv_w = 156, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 980, .adv_w = 146, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 990, .adv_w = 158, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1004, .adv_w = 158, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1018, .adv_w = 106, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1025, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1034, .adv_w = 98, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1043, .adv_w = 156, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1053, .adv_w = 141, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1065, .adv_w = 218, .box_w = 13, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1082, .adv_w = 144, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1094, .adv_w = 143, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1110, .adv_w = 134, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1119, .adv_w = 97, .box_w = 5, .box_h = 17, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1130, .adv_w = 107, .box_w = 2, .box_h = 16, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 1134, .adv_w = 97, .box_w = 5, .box_h = 17, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1145, .adv_w = 156, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1148, .adv_w = 122, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1154, .adv_w = 156, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1165, .adv_w = 92, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1170, .adv_w = 92, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 1175, .adv_w = 157, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1189, .adv_w = 93, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1191, .adv_w = 156, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1198, .adv_w = 156, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 1}
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
    3, 13, 3, 15, 3, 34, 3, 43, 3, 87, 3, 88, 3, 90, 6, 3,
    6, 8, 6, 11, 7, 53, 7, 55, 7, 56, 7, 58, 8, 13, 8, 15,
    8, 53, 8, 55, 8, 56, 8, 87, 8, 88, 8, 90, 9, 75, 11, 13,
    11, 15, 11, 34, 11, 43, 13, 3, 13, 8, 13, 11, 13, 32, 13, 34,
    13, 36, 13, 40, 13, 48, 13, 50, 13, 53, 13, 55, 13, 56, 13, 58,
    13, 59, 13, 87, 13, 88, 13, 90, 13, 98, 13, 99, 14, 34, 14, 42,
    14, 43, 14, 52, 14, 53, 14, 55, 14, 56, 14, 57, 14, 58, 14, 59,
    14, 75, 14, 87, 14, 88, 14, 89, 14, 90, 14, 91, 15, 3, 15, 8,
    15, 11, 15, 32, 15, 34, 15, 36, 15, 40, 15, 48, 15, 50, 15, 53,
    15, 55, 15, 56, 15, 58, 15, 59, 15, 87, 15, 88, 15, 90, 15, 98,
    15, 99, 16, 16, 16, 34, 16, 36, 16, 40, 16, 43, 16, 48, 16, 50,
    16, 52, 16, 66, 16, 68, 16, 69, 16, 70, 16, 72, 16, 80, 16, 82,
    27, 53, 27, 55, 27, 56, 27, 57, 27, 58, 28, 53, 28, 55, 28, 56,
    28, 57, 28, 58, 32, 13, 32, 15, 33, 34, 33, 42, 33, 43, 33, 52,
    33, 53, 33, 55, 33, 56, 33, 57, 33, 58, 33, 59, 33, 88, 33, 89,
    33, 90, 33, 91, 34, 3, 34, 8, 34, 11, 34, 13, 34, 15, 34, 32,
    34, 53, 34, 55, 34, 58, 34, 98, 34, 99, 35, 16, 35, 58, 35, 64,
    36, 7, 36, 14, 36, 16, 36, 33, 36, 57, 36, 58, 36, 64, 37, 14,
    39, 7, 39, 13, 39, 15, 39, 16, 39, 33, 39, 34, 39, 36, 39, 40,
    39, 43, 39, 48, 39, 50, 39, 64, 39, 66, 39, 68, 39, 69, 39, 70,
    39, 71, 39, 72, 39, 75, 39, 78, 39, 79, 39, 80, 39, 81, 39, 82,
    39, 83, 39, 84, 39, 85, 39, 86, 39, 87, 39, 88, 39, 89, 39, 90,
    39, 91, 40, 3, 40, 8, 40, 11, 40, 43, 40, 53, 40, 55, 40, 56,
    40, 57, 40, 58, 40, 98, 40, 99, 43, 64, 44, 10, 44, 13, 44, 14,
    44, 15, 44, 91, 45, 3, 45, 8, 45, 11, 45, 14, 45, 32, 45, 33,
    45, 36, 45, 40, 45, 48, 45, 50, 45, 53, 45, 54, 45, 55, 45, 56,
    45, 58, 45, 68, 45, 69, 45, 70, 45, 80, 45, 82, 45, 85, 45, 87,
    45, 88, 45, 90, 45, 98, 45, 99, 48, 3, 48, 8, 48, 11, 48, 13,
    48, 15, 48, 16, 48, 34, 48, 43, 48, 53, 48, 55, 48, 56, 48, 57,
    48, 58, 48, 59, 48, 64, 49, 7, 49, 13, 49, 15, 49, 16, 49, 34,
    49, 43, 49, 57, 49, 58, 49, 59, 49, 64, 49, 66, 49, 68, 49, 69,
    49, 70, 49, 72, 49, 80, 49, 81, 49, 82, 49, 84, 50, 3, 50, 8,
    50, 11, 50, 13, 50, 15, 50, 16, 50, 34, 50, 43, 50, 53, 50, 55,
    50, 56, 50, 57, 50, 58, 50, 59, 50, 64, 51, 58, 52, 16, 52, 64,
    53, 7, 53, 13, 53, 14, 53, 15, 53, 16, 53, 27, 53, 28, 53, 33,
    53, 34, 53, 36, 53, 40, 53, 42, 53, 43, 53, 48, 53, 50, 53, 52,
    53, 64, 53, 66, 53, 68, 53, 69, 53, 70, 53, 71, 53, 72, 53, 78,
    53, 79, 53, 80, 53, 81, 53, 82, 53, 83, 53, 84, 53, 86, 53, 87,
    53, 88, 53, 89, 53, 90, 53, 91, 54, 64, 55, 7, 55, 13, 55, 14,
    55, 15, 55, 16, 55, 27, 55, 28, 55, 33, 55, 34, 55, 36, 55, 40,
    55, 43, 55, 48, 55, 50, 55, 52, 55, 64, 55, 66, 55, 68, 55, 69,
    55, 70, 55, 72, 55, 78, 55, 79, 55, 80, 55, 81, 55, 82, 55, 83,
    55, 84, 55, 86, 56, 7, 56, 13, 56, 15, 56, 16, 56, 34, 56, 43,
    56, 64, 56, 66, 57, 14, 57, 33, 57, 36, 57, 40, 57, 48, 57, 50,
    58, 3, 58, 7, 58, 8, 58, 10, 58, 11, 58, 13, 58, 14, 58, 15,
    58, 16, 58, 32, 58, 34, 58, 53, 58, 58, 58, 64, 58, 66, 58, 68,
    58, 70, 58, 72, 58, 80, 58, 98, 58, 99, 59, 14, 60, 75, 64, 36,
    64, 40, 64, 43, 64, 48, 64, 50, 64, 52, 64, 53, 64, 54, 64, 55,
    64, 56, 64, 58, 64, 66, 64, 68, 64, 69, 64, 70, 64, 72, 64, 75,
    64, 77, 64, 80, 64, 82, 64, 84, 64, 85, 64, 86, 64, 87, 64, 88,
    66, 13, 66, 15, 66, 16, 66, 53, 66, 58, 66, 64, 67, 53, 67, 55,
    67, 56, 67, 58, 67, 64, 68, 34, 68, 43, 68, 59, 68, 99, 70, 53,
    70, 58, 70, 64, 71, 3, 71, 8, 71, 10, 71, 11, 71, 13, 71, 15,
    71, 32, 71, 53, 71, 55, 71, 56, 71, 58, 71, 64, 71, 98, 71, 99,
    72, 10, 72, 16, 72, 64, 72, 75, 73, 53, 73, 55, 73, 56, 73, 58,
    75, 55, 75, 58, 76, 34, 76, 59, 76, 64, 78, 3, 78, 8, 78, 11,
    78, 53, 78, 55, 78, 56, 78, 58, 78, 87, 78, 88, 78, 90, 79, 53,
    79, 55, 79, 56, 79, 58, 80, 53, 80, 58, 80, 64, 81, 53, 81, 55,
    81, 56, 81, 58, 81, 64, 82, 55, 82, 58, 83, 7, 83, 13, 83, 15,
    83, 16, 83, 34, 83, 43, 83, 53, 83, 57, 83, 58, 83, 59, 83, 64,
    83, 66, 84, 53, 84, 58, 84, 64, 85, 64, 85, 99, 86, 53, 86, 55,
    86, 58, 87, 7, 87, 13, 87, 15, 87, 34, 87, 43, 87, 64, 88, 7,
    88, 13, 88, 15, 88, 33, 88, 34, 88, 43, 88, 53, 88, 55, 88, 56,
    88, 58, 88, 64, 88, 66, 88, 68, 88, 69, 88, 70, 88, 72, 88, 80,
    88, 82, 89, 7, 89, 14, 89, 53, 89, 58, 90, 7, 90, 13, 90, 15,
    90, 34, 90, 64, 91, 13, 91, 15, 91, 34, 91, 57, 98, 13, 98, 15,
    98, 34, 98, 43, 99, 13, 99, 15, 99, 34, 99, 43,
};

static const int8_t kern_pair_values[] = {
    -26, -26, -14, -12, 7, 6, 6, -17, -17, -17, -12, -10, -6, -17, -26, -26,
    4, 3, 4, 7, 6, 6, 20, -26, -26, -14, -12, -26, -26, -26, -23, 6,
    -12, -12, -12, -12, -26, -17, -12, -26, 9, -20, -14, -13, -14, -17, -4, -9,
    -5, -5, -13, -10, -6, -12, -17, -6, -3, -1, -1, -10, -1, -5, -26, -26,
    -26, -23, 6, -12, -12, -12, -12, -26, -17, -12, -26, 9, -20, -14, -13, -14,
    -17, -55, -24, -9, -9, -9, -9, -9, -6, -14, -10, -10, -10, -10, -10, -10,
    -12, -9, -3, -4, -14, -12, -9, -3, -4, -14, -35, -35, -9, -6, -6, -3,
    -9, -9, -6, -12, -12, -4, -3, -6, -3, -3, -14, -14, -14, 6, 6, -14,
    -16, -16, -20, -17, -14, -7, -6, -18, -3, -3, -6, -3, -6, -3, -16, 4,
    -12, -29, -29, -24, -9, -21, -9, -9, -16, -9, -9, -40, -12, -9, -10, -9,
    -2, -13, -3, -9, -9, -9, -9, -10, -9, -9, -4, -7, -6, -4, -12, -6,
    -7, -3, -3, -3, -3, -7, -7, -4, -3, -12, -6, -3, -24, 3, 3, -16,
    3, 3, -23, -23, -23, -10, -17, -3, -12, -12, -12, -12, -21, -4, -16, -12,
    -25, -3, -3, -3, -3, -3, -7, -12, -9, -10, -23, -20, -3, -3, -3, -12,
    -12, -13, -6, -3, -7, -7, -7, -9, -12, -3, -29, -9, -32, -32, -26, -20,
    -16, -10, -7, -7, -43, -4, -6, -6, -6, -9, -6, -4, -6, -4, -3, -3,
    -3, -12, -12, -13, -6, -3, -7, -7, -7, -9, -12, -3, -29, -9, -10, -17,
    -9, -26, -13, -26, -29, -12, -12, -9, -16, -7, -7, -1, -13, -7, -7, -3,
    -23, -17, -16, -16, -16, -4, -20, -13, -13, -16, -13, -16, -13, -17, -13, -7,
    -10, -7, -6, -14, -20, -10, -17, -10, -17, -19, -9, -9, -9, -16, -7, -7,
    -12, -7, -7, -7, -29, -10, -10, -10, -10, -12, -6, -6, -10, -6, -10, -6,
    -7, -7, -10, -12, -12, -14, -8, -9, -20, -9, -12, -9, -9, -9, -9, -9,
    1, -16, 1, 6, 1, -26, -17, -26, -29, 1, -20, 1, 1, -32, -16, -16,
    -16, -16, -16, 1, 3, -12, 6, -29, -29, -14, -29, -29, -17, -23, -20, -29,
    -20, -32, -9, -17, -12, -17, 10, 16, -16, -17, -12, -12, -19, -10, -20, -14,
    3, 3, 6, -20, -16, 3, -19, -10, -7, -17, -14, 2, 1, 2, 1, -16,
    -17, -17, 9, 9, 7, 9, -15, -15, 9, 7, 10, 7, 9, -18, 7, 12,
    8, 10, 16, 9, -16, -10, -7, -16, -7, -9, 4, 5, 6, -4, -4, -4,
    -16, -10, -7, -16, -2, -2, -2, -16, -10, -7, -16, -16, -17, -17, -19, -10,
    -7, -17, -14, -7, -9, -7, -23, -23, -9, -12, -7, -3, -6, -6, -3, -23,
    -3, -16, -14, -14, 6, 6, -13, -7, -14, -6, -20, -20, -9, -6, -20, -6,
    -14, -14, -3, -6, -6, -10, -3, -3, -12, -14, -3, -3, -3, -3, -5, -3,
    -3, -9, -10, -10, -9, -9, -19, -19, -10, -23, 3, 3, 3, 3, -14, -14,
    -12, -16, -17, -17, -14, -17,
};

static const lv_font_fmt_txt_kern_pair_t kern_pairs = {
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 534,
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
const lv_font_t humid1_font_plex_cond_bold_18 = {
#else
lv_font_t humid1_font_plex_cond_bold_18 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 24,
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
    .fallback = &humid1_font_plex_sans_bold_18,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_COND_BOLD_18 */
