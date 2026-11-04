/*******************************************************************************
 * Font: humid1_font_plex_sans_bold_20 (IBM Plex Sans Bold)
 * Size: 20 px @ 188 DPI (SSD1681 1-bit E-Paper Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Raster Mode: autohint-mono (FT_LOAD_TARGET_MONO + Dropout Control)
 * License: SIL Open Font License 1.1 (IBM Corp.) / Font Awesome Free License
 ******************************************************************************/

#include "lvgl.h"

#ifndef HUMID1_FONT_PLEX_SANS_BOLD_20
#define HUMID1_FONT_PLEX_SANS_BOLD_20 1
#endif

#if HUMID1_FONT_PLEX_SANS_BOLD_20

extern const lv_font_t humid1_font_plex_sans_normal_20;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (3x14) */
    0xff, 0xff, 0xfa, 0x48, 0x7f, 0xc0,
    /* U+0022 "" (7x6) */
    0xef, 0xdf, 0xbf, 0x7e, 0xfd, 0xc0,
    /* U+0023 "#" (12x14) */
    0x0c, 0x40, 0x8c, 0x18, 0xc7, 0xff, 0x7f, 0xf1, 0x8c, 0x18, 0x81, 0x18,
    0x31, 0x8f, 0xfe, 0xff, 0xe3, 0x18, 0x31, 0x02, 0x30,
    /* U+0024 "$" (10x18) */
    0x0e, 0x03, 0x83, 0xf1, 0xff, 0xe7, 0xb9, 0x8e, 0x63, 0xf8, 0x7f, 0x0f,
    0xe0, 0x7c, 0x1f, 0x47, 0xf9, 0xff, 0xf8, 0xf8, 0x0e, 0x03, 0x80,
    /* U+0025 "%" (18x14) */
    0x7c, 0x0e, 0x3f, 0x87, 0x0e, 0xe1, 0x83, 0xb8, 0xc0, 0xee, 0x70, 0x3f,
    0x98, 0x07, 0xcc, 0xf0, 0x06, 0x7e, 0x01, 0xb9, 0xc0, 0xce, 0x70, 0x63,
    0x9c, 0x18, 0xe7, 0x0c, 0x1f, 0x86, 0x03, 0xc0,
    /* U+0026 "&" (13x14) */
    0x1f, 0x01, 0xfe, 0x1c, 0x70, 0xe3, 0x87, 0xb8, 0x1f, 0x80, 0xf8, 0xef,
    0xe7, 0xe7, 0xf7, 0x1f, 0x38, 0x79, 0xe3, 0xe7, 0xff, 0x1f, 0x9c,
    /* U+0027 "'" (3x6) */
    0xff, 0xff, 0xc0,
    /* U+0028 "(" (6x18) */
    0x1c, 0xe3, 0x1c, 0x73, 0x8e, 0x38, 0xe3, 0x8e, 0x38, 0xe1, 0xc7, 0x0c,
    0x38, 0x70,
    /* U+0029 ")" (6x18) */
    0xe1, 0xc7, 0x0e, 0x38, 0x71, 0xc7, 0x1c, 0x71, 0xc7, 0x1c, 0xe3, 0x9c,
    0x73, 0x80,
    /* U+002A "" (11x10) */
    0x0e, 0x01, 0xc0, 0x38, 0x77, 0x7f, 0xfe, 0x7f, 0x07, 0xc1, 0xdc, 0x71,
    0xc6, 0x30,
    /* U+002B "+" (9x10) */
    0x1c, 0x0e, 0x07, 0x03, 0x8f, 0xff, 0xfc, 0x70, 0x38, 0x1c, 0x0e, 0x00,
    /* U+002C "," (3x6) */
    0xff, 0xb5, 0x80,
    /* U+002D "-" (6x3) */
    0xff, 0xff, 0xc0,
    /* U+002E "." (3x3) */
    0xff, 0x80,
    /* U+002F "/" (8x19) */
    0x03, 0x03, 0x07, 0x06, 0x06, 0x0e, 0x0c, 0x0c, 0x1c, 0x18, 0x18, 0x38,
    0x30, 0x30, 0x70, 0x60, 0x60, 0xe0, 0xe0,
    /* U+0030 "0" (11x14) */
    0x1f, 0x07, 0xf1, 0xc7, 0x70, 0x7e, 0x0f, 0xc1, 0xf8, 0x3f, 0x07, 0xe0,
    0xfc, 0x1f, 0x83, 0x38, 0xe3, 0xf8, 0x3e, 0x00,
    /* U+0031 "1" (11x14) */
    0x1f, 0x07, 0xe1, 0xdc, 0x3b, 0x8e, 0x70, 0x8e, 0x01, 0xc0, 0x38, 0x07,
    0x00, 0xe0, 0x1c, 0x03, 0x87, 0xfe, 0xff, 0xc0,
    /* U+0032 "2" (10x14) */
    0x3f, 0x1f, 0xee, 0x3d, 0x87, 0x01, 0xc0, 0x70, 0x38, 0x1e, 0x0f, 0x07,
    0x87, 0x83, 0xc0, 0xff, 0xff, 0xf0,
    /* U+0033 "3" (10x14) */
    0x3f, 0x1f, 0xe6, 0x1c, 0x07, 0x01, 0xc7, 0xc1, 0xf8, 0x0e, 0x01, 0xc0,
    0x76, 0x1f, 0x8f, 0x7f, 0x8f, 0x80,
    /* U+0034 "4" (11x14) */
    0x07, 0x81, 0xf0, 0x3e, 0x0f, 0xc1, 0xb8, 0x67, 0x1c, 0xe3, 0x1c, 0xe3,
    0x9f, 0xff, 0xff, 0x81, 0xc0, 0x38, 0x07, 0x00,
    /* U+0035 "5" (10x14) */
    0xff, 0xbf, 0xee, 0x03, 0x80, 0xe0, 0x3b, 0xcf, 0xfb, 0xcf, 0x01, 0xc0,
    0x74, 0x1f, 0x8e, 0xff, 0x9f, 0x80,
    /* U+0036 "6" (10x14) */
    0x0f, 0x07, 0x83, 0xc1, 0xe0, 0x70, 0x1b, 0xcf, 0xfb, 0xcf, 0xe1, 0xf8,
    0x7e, 0x1d, 0xce, 0x7f, 0x87, 0x80,
    /* U+0037 "7" (10x14) */
    0xff, 0xff, 0xfe, 0x1f, 0x87, 0xe3, 0x80, 0xe0, 0x70, 0x1c, 0x07, 0x03,
    0x80, 0xe0, 0x38, 0x1c, 0x07, 0x00,
    /* U+0038 "8" (10x14) */
    0x3f, 0x1f, 0xee, 0x1f, 0x87, 0xe1, 0xcf, 0xc7, 0xf9, 0xce, 0xe1, 0xf8,
    0x7e, 0x1f, 0xcf, 0x7f, 0x8f, 0xc0,
    /* U+0039 "9" (10x14) */
    0x1e, 0x1f, 0xef, 0x3b, 0x87, 0xe1, 0xf8, 0x7f, 0x3d, 0xff, 0x3d, 0x80,
    0xe0, 0x70, 0x3c, 0x1e, 0x0f, 0x00,
    /* U+003A ":" (3x11) */
    0xff, 0x80, 0x00, 0xff, 0x80,
    /* U+003B ";" (3x13) */
    0xff, 0x80, 0x07, 0xfd, 0xac,
    /* U+003C "<" (8x12) */
    0x01, 0x07, 0x0f, 0x3e, 0x78, 0xf0, 0xf0, 0x7c, 0x1e, 0x0f, 0x03, 0x01,
    /* U+003D "=" (9x7) */
    0xff, 0xff, 0xc0, 0x00, 0x00, 0x07, 0xff, 0xfe,
    /* U+003E ">" (8x12) */
    0x80, 0xe0, 0xf0, 0x7c, 0x1e, 0x0f, 0x0f, 0x3e, 0x78, 0xf0, 0xc0, 0x80,
    /* U+003F "?" (9x14) */
    0x3e, 0x7f, 0xb8, 0xe8, 0x70, 0x38, 0x3c, 0xfc, 0x70, 0x38, 0x00, 0x00,
    0x07, 0x83, 0xc1, 0xe0,
    /* U+0040 "@" (16x17) */
    0x07, 0xe0, 0x1f, 0xf8, 0x38, 0x1c, 0x70, 0x0e, 0x67, 0x66, 0xe7, 0xe3,
    0xce, 0x63, 0xce, 0x63, 0xce, 0x63, 0xce, 0x63, 0xce, 0x67, 0xc7, 0xfe,
    0x67, 0x3c, 0x70, 0x00, 0x38, 0x00, 0x1f, 0xf0, 0x07, 0xf0,
    /* U+0041 "A" (12x14) */
    0x0f, 0x01, 0xf0, 0x1f, 0x81, 0xf8, 0x1b, 0x83, 0x9c, 0x39, 0xc3, 0x1c,
    0x7f, 0xe7, 0xfe, 0x60, 0xee, 0x06, 0xe0, 0x7e, 0x07,
    /* U+0042 "B" (11x14) */
    0xff, 0x1f, 0xf3, 0x87, 0x70, 0xee, 0x1d, 0xc3, 0xbf, 0xe7, 0xfe, 0xe0,
    0xfc, 0x1f, 0x83, 0xf0, 0x7f, 0xfd, 0xff, 0x00,
    /* U+0043 "C" (11x14) */
    0x1f, 0x87, 0xf9, 0xff, 0xb8, 0x7e, 0x09, 0xc0, 0x38, 0x07, 0x00, 0xe0,
    0x1c, 0x01, 0xc3, 0xbf, 0xf3, 0xfc, 0x3f, 0x00,
    /* U+0044 "D" (11x14) */
    0xff, 0x1f, 0xf3, 0xff, 0x70, 0xee, 0x0f, 0xc1, 0xf8, 0x3f, 0x07, 0xe0,
    0xfc, 0x1f, 0x87, 0x7f, 0xef, 0xf9, 0xfe, 0x00,
    /* U+0045 "E" (10x14) */
    0xff, 0xff, 0xff, 0xff, 0x80, 0xe0, 0x3f, 0xef, 0xfb, 0xfe, 0xe0, 0x38,
    0x0e, 0x03, 0xff, 0xff, 0xff, 0xf0,
    /* U+0046 "F" (10x14) */
    0xff, 0xff, 0xff, 0xff, 0x80, 0xe0, 0x3f, 0xef, 0xfb, 0xfe, 0xe0, 0x38,
    0x0e, 0x03, 0x80, 0xe0, 0x38, 0x00,
    /* U+0047 "G" (12x14) */
    0x0f, 0x83, 0xfc, 0x7f, 0xe7, 0x0f, 0xe0, 0x0e, 0x00, 0xe3, 0xfe, 0x3f,
    0xe0, 0x7e, 0x07, 0x70, 0xf7, 0xff, 0x3f, 0xf1, 0xf7,
    /* U+0048 "H" (11x14) */
    0xe0, 0xfc, 0x1f, 0x83, 0xf0, 0x7e, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xe0,
    0xfc, 0x1f, 0x83, 0xf0, 0x7e, 0x0f, 0xc1, 0xc0,
    /* U+0049 "I" (7x14) */
    0xff, 0xfc, 0xe1, 0xc3, 0x87, 0x0e, 0x1c, 0x38, 0x70, 0xe1, 0xcf, 0xff,
    0xc0,
    /* U+004A "J" (9x14) */
    0x3f, 0x9f, 0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x03, 0x81, 0xd8,
    0xfc, 0x77, 0xf1, 0xf0,
    /* U+004B "K" (12x14) */
    0xe0, 0xee, 0x1c, 0xe3, 0xce, 0x78, 0xe7, 0x0e, 0xe0, 0xfe, 0x0f, 0xf0,
    0xf7, 0x8f, 0x38, 0xe3, 0xce, 0x1e, 0xe0, 0xee, 0x0f,
    /* U+004C "L" (9x14) */
    0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07, 0x03, 0x81, 0xc0, 0xe0, 0x70, 0x38,
    0x1f, 0xff, 0xff, 0xfc,
    /* U+004D "M" (13x14) */
    0xf0, 0x7f, 0x83, 0xfe, 0x3f, 0xf1, 0xff, 0x9f, 0xfe, 0xff, 0xb6, 0xfd,
    0xf7, 0xe7, 0x3f, 0x39, 0xf8, 0x8f, 0xc4, 0x7e, 0x03, 0xf0, 0x1c,
    /* U+004E "N" (11x14) */
    0xf0, 0xfe, 0x1f, 0xe3, 0xfc, 0x7f, 0xcf, 0xf9, 0xfb, 0xbf, 0x77, 0xe7,
    0xfc, 0xff, 0x8f, 0xf1, 0xfe, 0x1f, 0xc3, 0xc0,
    /* U+004F "O" (12x14) */
    0x1f, 0x83, 0xfc, 0x7f, 0xe7, 0x0e, 0xe0, 0x7e, 0x07, 0xe0, 0x7e, 0x07,
    0xe0, 0x7e, 0x07, 0x70, 0xe7, 0xfe, 0x3f, 0xc1, 0xf8,
    /* U+0050 "P" (11x14) */
    0xff, 0x9f, 0xfb, 0x83, 0xf0, 0x7e, 0x0f, 0xc1, 0xff, 0xf7, 0xfc, 0xe0,
    0x1c, 0x03, 0x80, 0x70, 0x0e, 0x01, 0xc0, 0x00,
    /* U+0051 "Q" (12x18) */
    0x0f, 0x83, 0xfc, 0x7f, 0xe7, 0x0e, 0xe0, 0x7e, 0x07, 0xe0, 0x7e, 0x07,
    0xe0, 0x7e, 0x07, 0xe0, 0x77, 0x0e, 0x7f, 0xe3, 0xfc, 0x0f, 0x80, 0x70,
    0x07, 0xc0, 0x3c,
    /* U+0052 "R" (11x14) */
    0xff, 0x9f, 0xfb, 0x83, 0xf0, 0x7e, 0x0f, 0xc1, 0xff, 0xf7, 0xfc, 0xe3,
    0x9c, 0x73, 0x8f, 0x70, 0xee, 0x1f, 0xc1, 0xc0,
    /* U+0053 "S" (10x14) */
    0x3f, 0x1f, 0xfe, 0x1b, 0x80, 0xe0, 0x3f, 0x87, 0xf8, 0xff, 0x01, 0xd0,
    0x76, 0x1f, 0xff, 0x7f, 0x8f, 0x80,
    /* U+0054 "T" (11x14) */
    0xff, 0xff, 0xff, 0xff, 0x87, 0x00, 0xe0, 0x1c, 0x03, 0x80, 0x70, 0x0e,
    0x01, 0xc0, 0x38, 0x07, 0x00, 0xe0, 0x1c, 0x00,
    /* U+0055 "U" (11x14) */
    0xe0, 0xfc, 0x1f, 0x83, 0xf0, 0x7e, 0x0f, 0xc1, 0xf8, 0x3f, 0x07, 0xe0,
    0xfc, 0x1f, 0xc7, 0xbf, 0xe7, 0xfc, 0x3e, 0x00,
    /* U+0056 "V" (13x14) */
    0xf0, 0x3b, 0x83, 0x9c, 0x1c, 0xe0, 0xe3, 0x8e, 0x1c, 0x70, 0xe3, 0x83,
    0xb8, 0x1d, 0xc0, 0xee, 0x03, 0x60, 0x1f, 0x00, 0xf8, 0x03, 0x80,
    /* U+0057 "W" (18x14) */
    0xe1, 0xe1, 0xf8, 0x78, 0x7e, 0x1e, 0x3b, 0x8f, 0x8e, 0x63, 0x63, 0x9c,
    0xdc, 0xe7, 0x37, 0x31, 0xdc, 0xdc, 0x77, 0x37, 0x0d, 0x8f, 0xc3, 0xe3,
    0xe0, 0xf8, 0x78, 0x3e, 0x1e, 0x07, 0x07, 0x80,
    /* U+0058 "X" (12x14) */
    0xe0, 0xff, 0x0e, 0x79, 0xc3, 0x9c, 0x3f, 0x81, 0xf0, 0x0f, 0x01, 0xf0,
    0x1f, 0x83, 0xb8, 0x79, 0xc7, 0x1e, 0xe0, 0xee, 0x0f,
    /* U+0059 "Y" (12x14) */
    0xe0, 0xfe, 0x0e, 0x71, 0xc7, 0x1c, 0x3b, 0x83, 0xf8, 0x1f, 0x01, 0xf0,
    0x0e, 0x00, 0xe0, 0x0e, 0x00, 0xe0, 0x0e, 0x00, 0xe0,
    /* U+005A "Z" (10x14) */
    0xff, 0xff, 0xff, 0xfc, 0x0f, 0x07, 0x83, 0xc0, 0xe0, 0x70, 0x38, 0x1c,
    0x0f, 0x03, 0xff, 0xff, 0xff, 0xf0,
    /* U+005B "[" (4x18) */
    0xff, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xff,
    /* U+005C "" (8x19) */
    0xc0, 0xe0, 0x60, 0x60, 0x70, 0x70, 0x30, 0x38, 0x38, 0x18, 0x1c, 0x1c,
    0x0c, 0x0e, 0x0e, 0x06, 0x06, 0x07, 0x03,
    /* U+005D "]" (5x18) */
    0xff, 0xce, 0x73, 0x9c, 0xe7, 0x39, 0xce, 0x73, 0x9c, 0xe7, 0xff, 0xc0,
    /* U+005E "^" (10x8) */
    0x0e, 0x07, 0x83, 0xf0, 0xfc, 0x73, 0x9c, 0xee, 0x1f, 0x87,
    /* U+005F "_" (10x2) */
    0xff, 0xff, 0xf0,
    /* U+0060 "`" (4x5) */
    0x2e, 0x77, 0x30,
    /* U+0061 "a" (10x11) */
    0x3e, 0x1f, 0xc6, 0x38, 0x0e, 0x3f, 0x9f, 0xee, 0x3b, 0x8e, 0xe3, 0xbf,
    0x77, 0xcc,
    /* U+0062 "b" (10x15) */
    0xe0, 0x38, 0x0e, 0x03, 0x80, 0xef, 0x3f, 0xef, 0x3f, 0x87, 0xe1, 0xf8,
    0x7e, 0x1f, 0x87, 0xf3, 0xff, 0xee, 0xf0,
    /* U+0063 "c" (9x11) */
    0x1e, 0x3f, 0x9c, 0xfc, 0x0e, 0x07, 0x03, 0x81, 0xc0, 0x73, 0xbf, 0x87,
    0x80,
    /* U+0064 "d" (10x15) */
    0x01, 0xc0, 0x70, 0x1c, 0x07, 0x3d, 0xdf, 0xff, 0x3f, 0x87, 0xe1, 0xf8,
    0x7e, 0x1f, 0x87, 0xf3, 0xdf, 0xf3, 0xdc,
    /* U+0065 "e" (10x11) */
    0x1f, 0x1f, 0xe7, 0x3b, 0x87, 0xff, 0xff, 0xfe, 0x03, 0x80, 0x71, 0x9f,
    0xf1, 0xf0,
    /* U+0066 "f" (7x15) */
    0x3e, 0xfd, 0xc3, 0x8f, 0xff, 0xdc, 0x38, 0x70, 0xe1, 0xc3, 0x87, 0x0e,
    0x1c, 0x00,
    /* U+0067 "g" (11x17) */
    0x01, 0xc0, 0x38, 0xfe, 0x3f, 0xee, 0x1d, 0xc3, 0xb8, 0x73, 0xfc, 0x1f,
    0x1c, 0x03, 0x80, 0x7f, 0xe3, 0xff, 0xc1, 0xf8, 0x3f, 0xfe, 0x7f, 0x80,
    /* U+0068 "h" (9x15) */
    0xe0, 0x70, 0x38, 0x1c, 0x0e, 0xf7, 0xfb, 0x8f, 0xc7, 0xe3, 0xf1, 0xf8,
    0xfc, 0x7e, 0x3f, 0x1f, 0x8e,
    /* U+0069 "i" (3x15) */
    0xff, 0x8f, 0xff, 0xff, 0xff, 0xf8,
    /* U+006A "j" (5x19) */
    0x39, 0xce, 0x03, 0x9c, 0xe7, 0x39, 0xce, 0x73, 0x9c, 0xe7, 0x3f, 0xfc,
    /* U+006B "k" (10x15) */
    0xe0, 0x38, 0x0e, 0x03, 0x80, 0xe3, 0xb9, 0xee, 0xf3, 0xb8, 0xfc, 0x3f,
    0x8f, 0xf3, 0x9c, 0xe7, 0xb8, 0xee, 0x3c,
    /* U+006C "l" (5x15) */
    0xe7, 0x39, 0xce, 0x73, 0x9c, 0xe7, 0x39, 0xce, 0x7d, 0xe0,
    /* U+006D "m" (15x11) */
    0xef, 0x3d, 0xff, 0xfb, 0x8e, 0x3f, 0x1c, 0x7e, 0x38, 0xfc, 0x71, 0xf8,
    0xe3, 0xf1, 0xc7, 0xe3, 0x8f, 0xc7, 0x1f, 0x8e, 0x38,
    /* U+006E "n" (9x11) */
    0xef, 0x7f, 0xb8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f, 0xc7, 0xe3, 0xf1, 0xf8,
    0xe0,
    /* U+006F "o" (10x11) */
    0x1e, 0x1f, 0xe7, 0x3b, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0x73, 0x9f,
    0xe1, 0xe0,
    /* U+0070 "p" (10x15) */
    0xef, 0x3f, 0xef, 0x3f, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xf3, 0xff,
    0xee, 0xf3, 0x80, 0xe0, 0x38, 0x0e, 0x00,
    /* U+0071 "q" (10x15) */
    0x3d, 0xdf, 0xff, 0x3f, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xf3, 0xdf,
    0xf3, 0xdc, 0x07, 0x01, 0xc0, 0x70, 0x1c,
    /* U+0072 "r" (7x11) */
    0xef, 0xff, 0xff, 0x8e, 0x1c, 0x38, 0x70, 0xe1, 0xc3, 0x80,
    /* U+0073 "s" (9x11) */
    0x3e, 0x3f, 0xf8, 0xdc, 0x0f, 0xe3, 0xf8, 0xfe, 0x07, 0x63, 0xff, 0x9f,
    0x80,
    /* U+0074 "t" (7x14) */
    0x70, 0xe1, 0xc7, 0xff, 0xee, 0x1c, 0x38, 0x70, 0xe1, 0xc3, 0x87, 0xe7,
    0xc0,
    /* U+0075 "u" (9x11) */
    0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f, 0xc7, 0xe3, 0xbf, 0xde,
    0xe0,
    /* U+0076 "v" (10x11) */
    0xe0, 0xdc, 0x77, 0x1d, 0xc6, 0x33, 0x8e, 0xe3, 0xb8, 0x6c, 0x1f, 0x07,
    0xc1, 0xe0,
    /* U+0077 "w" (15x11) */
    0xc3, 0x87, 0xc7, 0x1f, 0x9e, 0x3f, 0x3e, 0x76, 0x6c, 0xcc, 0xdb, 0x9f,
    0xbf, 0x3e, 0x7c, 0x3c, 0x78, 0x78, 0xf0, 0xf1, 0xe0,
    /* U+0078 "x" (10x11) */
    0xe3, 0xfc, 0xe7, 0x70, 0xfc, 0x3e, 0x07, 0x03, 0xe0, 0xfc, 0x77, 0x38,
    0xee, 0x3c,
    /* U+0079 "y" (10x15) */
    0xe1, 0xf8, 0x7e, 0x19, 0xce, 0x73, 0x9c, 0xc3, 0x70, 0xfc, 0x3e, 0x07,
    0x81, 0xe0, 0x70, 0x1c, 0x1f, 0x07, 0x80,
    /* U+007A "z" (9x11) */
    0xff, 0xff, 0xc1, 0xe1, 0xe1, 0xe0, 0xe0, 0xf0, 0xf0, 0xf0, 0x7f, 0xff,
    0xe0,
    /* U+007B "{" (6x18) */
    0x1c, 0xf3, 0x8e, 0x38, 0xe3, 0x9e, 0xf3, 0xc7, 0x8e, 0x38, 0xe3, 0x8e,
    0x3c, 0x70,
    /* U+007C "|" (3x18) */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc,
    /* U+007D "}" (7x18) */
    0xf1, 0xf0, 0xe1, 0xc3, 0x87, 0x0e, 0x1c, 0x1e, 0x3c, 0xe1, 0xc3, 0x87,
    0x0e, 0x1c, 0xf9, 0xe0,
    /* U+007E "~" (10x4) */
    0x70, 0x3f, 0x00, 0xfc, 0x0e,
    /* U+00B0 "" (7x8) */
    0x38, 0xfb, 0xbe, 0x3c, 0x78, 0xdf, 0x1c,
    /* U+00B1 "" (9x13) */
    0x1c, 0x0e, 0x07, 0x03, 0x8f, 0xff, 0xfc, 0x70, 0x38, 0x1c, 0x00, 0x00,
    0x1f, 0xff, 0xf8,
    /* U+00B2 "" (6x7) */
    0x7b, 0x30, 0xc7, 0x3b, 0x8f, 0xc0,
    /* U+00B3 "" (6x7) */
    0xf9, 0x30, 0xce, 0x0f, 0x3f, 0x80,
    /* U+00B5 "" (9x15) */
    0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f, 0xc7, 0xe3, 0xff, 0xf6,
    0xfc, 0x0e, 0x07, 0x03, 0x80,
    /* U+00B7 "" (3x3) */
    0xff, 0x80,
    /* U+00D7 "" (8x9) */
    0x42, 0xc3, 0xe7, 0x7e, 0x3c, 0x3c, 0x7e, 0xe7, 0xc3,
    /* U+00F7 "" (9x11) */
    0x1c, 0x0e, 0x07, 0x00, 0x0f, 0xff, 0xfc, 0x00, 0x00, 0x1c, 0x0e, 0x07,
    0x00,
    /* U+0394 "" (12x14) */
    0x0f, 0x00, 0xf0, 0x1f, 0x81, 0xf8, 0x39, 0xc3, 0x9c, 0x39, 0xc7, 0x0e,
    0x70, 0xe7, 0x0e, 0xe0, 0x7f, 0xff, 0xff, 0xff, 0xff,
    /* U+03A9 "" (12x14) */
    0x1f, 0x83, 0xfc, 0x7f, 0xef, 0x0f, 0xe0, 0x7e, 0x07, 0xe0, 0x7e, 0x07,
    0xe0, 0x67, 0x8e, 0x39, 0xcf, 0x9f, 0xf9, 0xff, 0x9f,
    /* U+03B1 "" (12x11) */
    0x3c, 0x77, 0xee, 0x67, 0xee, 0x3c, 0xe3, 0xce, 0x1c, 0xe3, 0xce, 0x3c,
    0xe7, 0xe7, 0xef, 0x3c, 0x70,
    /* U+03B2 "" (10x19) */
    0x3e, 0x1f, 0xcf, 0x3b, 0x8e, 0xe3, 0xb8, 0xee, 0xf3, 0xbe, 0xe3, 0xf8,
    0x7e, 0x1f, 0x87, 0xe3, 0xff, 0xee, 0xf3, 0x80, 0xe0, 0x38, 0x0e, 0x00,
    /* U+03B3 "" (11x15) */
    0xe0, 0xfe, 0x18, 0xc7, 0x1c, 0xe3, 0x98, 0x77, 0x06, 0xe0, 0xd8, 0x1f,
    0x01, 0xc0, 0x38, 0x07, 0x00, 0xe0, 0x1c, 0x03, 0x80,
    /* U+03B4 "" (10x15) */
    0x7f, 0x9f, 0xe7, 0x80, 0xf8, 0x1f, 0x0f, 0xe7, 0x3b, 0x87, 0xe1, 0xf8,
    0x7e, 0x1f, 0x87, 0x73, 0x9f, 0xe1, 0xe0,
    /* U+03B5 "" (9x11) */
    0x3f, 0x7f, 0xf8, 0x5c, 0x07, 0xe3, 0xf3, 0x81, 0xc0, 0xe1, 0xbf, 0xcf,
    0xc0,
    /* U+03B8 "" (10x15) */
    0x1e, 0x1f, 0xe7, 0x3b, 0x87, 0xe1, 0xf8, 0x7f, 0xff, 0xff, 0xe1, 0xf8,
    0x7e, 0x1f, 0x87, 0x73, 0x9f, 0xe1, 0xe0,
    /* U+03BB "" (10x15) */
    0x78, 0x1e, 0x01, 0xc0, 0x70, 0x1c, 0x07, 0x01, 0xe0, 0xf8, 0x36, 0x1d,
    0xc7, 0x71, 0xcc, 0xe3, 0xb8, 0xfe, 0x1c,
    /* U+03BC "" (10x15) */
    0xe3, 0xb8, 0xee, 0x3b, 0x8e, 0xe3, 0xb8, 0xee, 0x3b, 0x8e, 0xe3, 0xbf,
    0xfd, 0x9f, 0x80, 0xe0, 0x38, 0x0e, 0x00,
    /* U+03C0 "" (12x11) */
    0xff, 0xff, 0xff, 0x39, 0xc3, 0x9c, 0x39, 0xc3, 0x9c, 0x39, 0xc3, 0x9c,
    0x39, 0xc3, 0x9e, 0x38, 0xe0,
    /* U+03C3 "" (11x11) */
    0x1f, 0xef, 0xfd, 0xce, 0x70, 0xee, 0x1d, 0xc3, 0xb8, 0x77, 0x0e, 0x73,
    0x8f, 0xf0, 0x78, 0x00,
    /* U+03C4 "" (9x11) */
    0xff, 0xff, 0xc7, 0x03, 0x81, 0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0f, 0x83,
    0xc0,
    /* U+03C6 "" (13x15) */
    0x21, 0xe3, 0x9f, 0xb9, 0xcf, 0xce, 0x7e, 0x73, 0xf3, 0x9f, 0x9c, 0xfc,
    0xe7, 0x77, 0x73, 0xff, 0x87, 0xf0, 0x0e, 0x00, 0x70, 0x03, 0x80, 0x1c,
    0x00,
    /* U+03C9 "" (14x11) */
    0x60, 0x39, 0xc1, 0xee, 0x03, 0xf9, 0xc7, 0xe7, 0x1f, 0x9c, 0x7e, 0x71,
    0xf9, 0xc7, 0xe7, 0x1d, 0xf7, 0xe3, 0x8f, 0x00,
    /* U+2013 "" (10x2) */
    0xff, 0xff, 0xf0,
    /* U+2014 "" (14x2) */
    0xff, 0xff, 0xff, 0xf0,
    /* U+2018 "" (3x6) */
    0x6b, 0x7f, 0xc0,
    /* U+2019 "" (3x6) */
    0xff, 0xb5, 0x80,
    /* U+201C "" (8x6) */
    0x63, 0x42, 0xc6, 0xe7, 0xe7, 0xe7,
    /* U+201D "" (8x6) */
    0xe7, 0xe7, 0xe7, 0x63, 0x46, 0xc6,
    /* U+2022 "" (6x6) */
    0x7b, 0xff, 0xff, 0xfd, 0xe0,
    /* U+2026 "" (15x3) */
    0xe3, 0x8f, 0xc7, 0x1f, 0x8e, 0x38,
    /* U+2030 "" (26x14) */
    0x7c, 0x0e, 0x00, 0x3f, 0x87, 0x00, 0x0e, 0xe1, 0x80, 0x03, 0xb8, 0xc0,
    0x00, 0xee, 0x70, 0x00, 0x3f, 0x98, 0x00, 0x07, 0xcc, 0xf0, 0xf0, 0x06,
    0x7e, 0x7e, 0x01, 0xb9, 0xf9, 0xc0, 0xce, 0x7e, 0x70, 0x63, 0x9f, 0x9c,
    0x18, 0xe7, 0xe7, 0x0c, 0x1f, 0x9f, 0x86, 0x03, 0xc3, 0xc0,
    /* U+2190 "" (14x8) */
    0x0c, 0x00, 0xf0, 0x07, 0x80, 0x3f, 0xff, 0xff, 0xfd, 0xe0, 0x03, 0xc0,
    0x03, 0x00,
    /* U+2191 "" (10x14) */
    0x0c, 0x07, 0x83, 0xf1, 0xfe, 0xff, 0xdb, 0x60, 0xc0, 0x30, 0x0c, 0x03,
    0x00, 0xc0, 0x30, 0x0c, 0x03, 0x00,
    /* U+2192 "" (14x8) */
    0x00, 0xc0, 0x03, 0xc0, 0x07, 0xbf, 0xff, 0xff, 0xfc, 0x01, 0xe0, 0x0f,
    0x00, 0x30,
    /* U+2193 "" (10x14) */
    0x0c, 0x03, 0x00, 0xc0, 0x30, 0x0c, 0x03, 0x00, 0xc0, 0x30, 0x6d, 0xbf,
    0xf7, 0xf8, 0xfc, 0x1e, 0x03, 0x00,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 76, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 102, .box_w = 3, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 6, .adv_w = 158, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 12, .adv_w = 202, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 33, .adv_w = 192, .box_w = 10, .box_h = 18, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 56, .adv_w = 312, .box_w = 18, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 231, .box_w = 13, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 111, .adv_w = 86, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 114, .adv_w = 108, .box_w = 6, .box_h = 18, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 128, .adv_w = 108, .box_w = 6, .box_h = 18, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 142, .adv_w = 192, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 156, .adv_w = 192, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 168, .adv_w = 99, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 171, .adv_w = 129, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 174, .adv_w = 99, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 176, .adv_w = 147, .box_w = 8, .box_h = 19, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 195, .adv_w = 192, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 215, .adv_w = 192, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 235, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 253, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 271, .adv_w = 192, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 291, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 309, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 345, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 363, .adv_w = 192, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 381, .adv_w = 106, .box_w = 3, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 386, .adv_w = 106, .box_w = 3, .box_h = 13, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 391, .adv_w = 192, .box_w = 8, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 403, .adv_w = 192, .box_w = 9, .box_h = 7, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 411, .adv_w = 192, .box_w = 8, .box_h = 12, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 423, .adv_w = 160, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 439, .adv_w = 289, .box_w = 16, .box_h = 17, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 473, .adv_w = 219, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 494, .adv_w = 213, .box_w = 11, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 514, .adv_w = 208, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 534, .adv_w = 223, .box_w = 11, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 554, .adv_w = 194, .box_w = 10, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 572, .adv_w = 187, .box_w = 10, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 590, .adv_w = 230, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 611, .adv_w = 232, .box_w = 11, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 631, .adv_w = 138, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 644, .adv_w = 179, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 660, .adv_w = 223, .box_w = 12, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 681, .adv_w = 170, .box_w = 9, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 697, .adv_w = 262, .box_w = 13, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 720, .adv_w = 232, .box_w = 11, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 740, .adv_w = 228, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 761, .adv_w = 210, .box_w = 11, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 781, .adv_w = 228, .box_w = 12, .box_h = 18, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 808, .adv_w = 216, .box_w = 11, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 828, .adv_w = 200, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 846, .adv_w = 187, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 866, .adv_w = 222, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 886, .adv_w = 208, .box_w = 13, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 909, .adv_w = 311, .box_w = 18, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 941, .adv_w = 215, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 962, .adv_w = 208, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 983, .adv_w = 194, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1001, .adv_w = 107, .box_w = 4, .box_h = 18, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 1010, .adv_w = 147, .box_w = 8, .box_h = 19, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1029, .adv_w = 107, .box_w = 5, .box_h = 18, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1041, .adv_w = 192, .box_w = 10, .box_h = 8, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 1051, .adv_w = 178, .box_w = 10, .box_h = 2, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1054, .adv_w = 192, .box_w = 4, .box_h = 5, .ofs_x = 3, .ofs_y = 12},
    {.bitmap_index = 1057, .adv_w = 182, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1071, .adv_w = 195, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1090, .adv_w = 165, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1103, .adv_w = 195, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1122, .adv_w = 180, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1136, .adv_w = 116, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1150, .adv_w = 177, .box_w = 11, .box_h = 17, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1174, .adv_w = 191, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1191, .adv_w = 92, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1197, .adv_w = 92, .box_w = 5, .box_h = 19, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 1209, .adv_w = 185, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1228, .adv_w = 97, .box_w = 5, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1238, .adv_w = 286, .box_w = 15, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1259, .adv_w = 191, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1272, .adv_w = 180, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1286, .adv_w = 195, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1305, .adv_w = 195, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1324, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1334, .adv_w = 161, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1347, .adv_w = 123, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1360, .adv_w = 191, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1373, .adv_w = 172, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1387, .adv_w = 269, .box_w = 15, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1408, .adv_w = 179, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1422, .adv_w = 171, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1441, .adv_w = 166, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1454, .adv_w = 119, .box_w = 6, .box_h = 18, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1468, .adv_w = 129, .box_w = 3, .box_h = 18, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 1475, .adv_w = 119, .box_w = 7, .box_h = 18, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1491, .adv_w = 192, .box_w = 10, .box_h = 4, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1496, .adv_w = 150, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1503, .adv_w = 192, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1518, .adv_w = 111, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1524, .adv_w = 110, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 1530, .adv_w = 193, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1547, .adv_w = 115, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 1549, .adv_w = 192, .box_w = 8, .box_h = 9, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1558, .adv_w = 192, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1571, .adv_w = 218, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1592, .adv_w = 228, .box_w = 12, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1613, .adv_w = 213, .box_w = 12, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1630, .adv_w = 195, .box_w = 10, .box_h = 19, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1654, .adv_w = 173, .box_w = 11, .box_h = 15, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1675, .adv_w = 180, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1694, .adv_w = 169, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1707, .adv_w = 184, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1726, .adv_w = 172, .box_w = 10, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1745, .adv_w = 197, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1764, .adv_w = 210, .box_w = 12, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1781, .adv_w = 188, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1797, .adv_w = 160, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1810, .adv_w = 247, .box_w = 13, .box_h = 15, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1835, .adv_w = 246, .box_w = 14, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1855, .adv_w = 188, .box_w = 10, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1858, .adv_w = 250, .box_w = 14, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1862, .adv_w = 96, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 1865, .adv_w = 96, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 1868, .adv_w = 171, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 1874, .adv_w = 171, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 1880, .adv_w = 138, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1885, .adv_w = 287, .box_w = 15, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1891, .adv_w = 442, .box_w = 26, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1937, .adv_w = 288, .box_w = 14, .box_h = 8, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 1951, .adv_w = 288, .box_w = 10, .box_h = 14, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 1969, .adv_w = 288, .box_w = 14, .box_h = 8, .ofs_x = 2, .ofs_y = 3},
    {.bitmap_index = 1983, .adv_w = 288, .box_w = 10, .box_h = 14, .ofs_x = 4, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x0005, 0x0007, 0x0027, 0x0047, 0x02e4, 0x02f9,
    0x0301, 0x0302, 0x0303, 0x0304, 0x0305, 0x0308, 0x030b, 0x030c, 0x0310, 0x0313,
    0x0314, 0x0316, 0x0319, 0x1f63, 0x1f64, 0x1f68, 0x1f69, 0x1f6c, 0x1f6d, 0x1f72,
    0x1f76, 0x1f80, 0x20e0, 0x20e1, 0x20e2, 0x20e3,
};

static const lv_font_fmt_txt_cmap_t cmaps[] = {
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 176, .range_length = 8420, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 36, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/

static const uint8_t kern_pair_glyph_ids[] = {
    3, 13, 3, 15, 3, 34, 3, 43, 3, 104, 3, 126, 6, 3, 6, 8,
    6, 11, 6, 121, 6, 122, 6, 123, 6, 124, 7, 34, 7, 58, 7, 66,
    7, 68, 7, 69, 7, 70, 7, 80, 7, 82, 7, 104, 7, 106, 7, 109,
    7, 112, 7, 115, 7, 117, 7, 118, 8, 13, 8, 15, 8, 34, 8, 53,
    8, 55, 8, 56, 8, 58, 8, 87, 8, 88, 8, 90, 8, 91, 8, 104,
    8, 108, 8, 114, 8, 116, 8, 126, 9, 75, 11, 13, 11, 15, 11, 34,
    11, 43, 11, 87, 11, 104, 11, 126, 13, 3, 13, 8, 13, 11, 13, 32,
    13, 34, 13, 36, 13, 40, 13, 48, 13, 50, 13, 53, 13, 55, 13, 56,
    13, 58, 13, 59, 13, 87, 13, 88, 13, 90, 13, 98, 13, 99, 13, 104,
    13, 108, 13, 112, 13, 116, 13, 121, 13, 122, 13, 123, 13, 124, 14, 42,
    14, 53, 14, 57, 14, 58, 14, 59, 14, 89, 14, 112, 15, 3, 15, 8,
    15, 11, 15, 32, 15, 34, 15, 36, 15, 40, 15, 48, 15, 50, 15, 53,
    15, 55, 15, 56, 15, 58, 15, 59, 15, 87, 15, 88, 15, 90, 15, 98,
    15, 99, 15, 104, 15, 108, 15, 112, 15, 116, 15, 121, 15, 122, 15, 123,
    15, 124, 16, 16, 16, 34, 16, 53, 16, 66, 16, 104, 16, 110, 16, 112,
    27, 53, 27, 55, 27, 57, 27, 58, 28, 53, 28, 55, 28, 57, 28, 58,
    32, 13, 32, 15, 32, 34, 32, 104, 32, 126, 33, 43, 33, 53, 33, 55,
    33, 57, 33, 58, 34, 3, 34, 8, 34, 11, 34, 14, 34, 32, 34, 33,
    34, 36, 34, 40, 34, 43, 34, 48, 34, 50, 34, 53, 34, 54, 34, 55,
    34, 56, 34, 58, 34, 85, 34, 87, 34, 88, 34, 90, 34, 98, 34, 99,
    34, 119, 34, 120, 34, 121, 34, 122, 34, 123, 34, 124, 35, 58, 35, 64,
    36, 64, 37, 13, 37, 15, 37, 16, 37, 34, 37, 43, 37, 53, 37, 55,
    37, 57, 37, 58, 37, 59, 37, 121, 37, 122, 37, 123, 37, 124, 37, 126,
    39, 7, 39, 13, 39, 15, 39, 16, 39, 33, 39, 34, 39, 36, 39, 40,
    39, 43, 39, 48, 39, 50, 39, 64, 39, 66, 39, 68, 39, 69, 39, 70,
    39, 72, 39, 78, 39, 79, 39, 80, 39, 81, 39, 82, 39, 83, 39, 84,
    39, 85, 39, 86, 39, 87, 39, 88, 39, 89, 39, 90, 39, 91, 39, 126,
    40, 14, 40, 119, 40, 120, 42, 14, 42, 33, 42, 119, 42, 120, 43, 64,
    44, 7, 44, 14, 44, 33, 44, 36, 44, 40, 44, 48, 44, 50, 44, 53,
    44, 55, 44, 68, 44, 69, 44, 70, 44, 80, 44, 82, 44, 85, 44, 98,
    44, 99, 44, 119, 44, 120, 44, 121, 44, 123, 45, 3, 45, 8, 45, 11,
    45, 14, 45, 32, 45, 33, 45, 36, 45, 40, 45, 48, 45, 50, 45, 53,
    45, 54, 45, 55, 45, 56, 45, 58, 45, 68, 45, 69, 45, 70, 45, 80,
    45, 82, 45, 85, 45, 87, 45, 88, 45, 90, 45, 98, 45, 99, 45, 119,
    45, 120, 45, 121, 45, 122, 45, 123, 45, 124, 48, 13, 48, 14, 48, 15,
    48, 16, 48, 58, 48, 64, 48, 119, 48, 120, 48, 126, 49, 13, 49, 15,
    49, 16, 49, 34, 49, 43, 49, 57, 49, 64, 49, 126, 50, 13, 50, 14,
    50, 15, 50, 16, 50, 58, 50, 64, 50, 119, 50, 120, 50, 126, 51, 7,
    51, 14, 51, 16, 51, 33, 51, 36, 51, 40, 51, 43, 51, 48, 51, 50,
    51, 53, 51, 54, 51, 55, 51, 56, 51, 58, 51, 66, 51, 68, 51, 69,
    51, 70, 51, 72, 51, 80, 51, 82, 51, 90, 51, 99, 51, 119, 51, 120,
    52, 7, 52, 16, 52, 33, 52, 52, 52, 53, 52, 55, 52, 56, 52, 58,
    52, 64, 52, 85, 52, 98, 52, 99, 52, 121, 52, 122, 52, 123, 52, 124,
    53, 7, 53, 13, 53, 14, 53, 15, 53, 16, 53, 27, 53, 28, 53, 33,
    53, 34, 53, 36, 53, 40, 53, 43, 53, 48, 53, 50, 53, 52, 53, 64,
    53, 66, 53, 68, 53, 69, 53, 70, 53, 71, 53, 72, 53, 78, 53, 79,
    53, 80, 53, 81, 53, 82, 53, 83, 53, 84, 53, 86, 53, 87, 53, 88,
    53, 89, 53, 90, 53, 91, 53, 119, 53, 120, 53, 126, 54, 13, 54, 15,
    54, 16, 54, 34, 54, 64, 54, 126, 55, 7, 55, 13, 55, 15, 55, 16,
    55, 27, 55, 28, 55, 33, 55, 34, 55, 36, 55, 40, 55, 43, 55, 48,
    55, 50, 55, 52, 55, 64, 55, 66, 55, 68, 55, 69, 55, 70, 55, 72,
    55, 80, 55, 82, 55, 126, 56, 3, 56, 8, 56, 10, 56, 11, 56, 16,
    56, 43, 56, 53, 56, 55, 56, 56, 56, 64, 56, 98, 56, 99, 57, 13,
    57, 15, 57, 34, 57, 64, 57, 91, 57, 126, 58, 7, 58, 13, 58, 14,
    58, 15, 58, 16, 58, 27, 58, 28, 58, 33, 58, 34, 58, 36, 58, 40,
    58, 43, 58, 48, 58, 50, 58, 52, 58, 64, 58, 66, 58, 68, 58, 69,
    58, 70, 58, 72, 58, 75, 58, 78, 58, 79, 58, 80, 58, 81, 58, 82,
    58, 83, 58, 84, 58, 86, 58, 87, 58, 88, 58, 89, 58, 90, 58, 91,
    58, 119, 58, 120, 58, 126, 59, 13, 59, 14, 59, 15, 59, 119, 59, 120,
    59, 126, 64, 36, 64, 40, 64, 43, 64, 48, 64, 50, 64, 52, 64, 53,
    64, 54, 64, 55, 64, 56, 64, 57, 64, 58, 64, 59, 64, 68, 64, 69,
    64, 70, 64, 72, 64, 75, 64, 77, 64, 80, 64, 82, 64, 84, 64, 85,
    64, 86, 64, 87, 64, 88, 64, 89, 64, 106, 64, 108, 64, 109, 64, 111,
    64, 112, 64, 114, 64, 115, 64, 116, 64, 117, 64, 118, 66, 13, 66, 15,
    66, 16, 66, 34, 66, 53, 66, 59, 66, 64, 66, 126, 67, 53, 67, 58,
    67, 64, 67, 121, 67, 123, 68, 34, 68, 53, 68, 58, 70, 53, 70, 58,
    70, 64, 71, 2, 71, 3, 71, 8, 71, 10, 71, 11, 71, 32, 71, 36,
    71, 40, 71, 48, 71, 50, 71, 53, 71, 55, 71, 56, 71, 57, 71, 58,
    71, 62, 71, 64, 71, 74, 71, 94, 71, 98, 71, 99, 71, 121, 71, 122,
    71, 123, 71, 124, 72, 10, 72, 16, 72, 34, 72, 64, 72, 75, 73, 53,
    73, 55, 73, 56, 73, 58, 73, 121, 73, 123, 75, 53, 75, 55, 75, 58,
    75, 121, 75, 123, 76, 7, 76, 14, 76, 33, 76, 36, 76, 40, 76, 43,
    76, 48, 76, 50, 76, 52, 76, 53, 76, 55, 76, 56, 76, 58, 76, 68,
    76, 69, 76, 70, 76, 80, 76, 82, 76, 84, 76, 85, 76, 86, 76, 87,
    76, 88, 76, 90, 76, 98, 76, 99, 76, 119, 76, 120, 76, 121, 76, 123,
    77, 34, 77, 64, 77, 121, 77, 122, 77, 123, 77, 124, 78, 53, 78, 55,
    78, 56, 78, 58, 78, 121, 78, 123, 79, 53, 79, 55, 79, 56, 79, 58,
    79, 121, 79, 123, 80, 53, 80, 58, 80, 64, 80, 121, 80, 123, 81, 53,
    81, 58, 81, 64, 81, 121, 81, 123, 82, 53, 83, 3, 83, 8, 83, 11,
    83, 13, 83, 15, 83, 34, 83, 64, 83, 98, 83, 99, 83, 122, 83, 124,
    83, 126, 84, 53, 84, 55, 84, 58, 84, 64, 85, 53, 85, 58, 86, 53,
    86, 55, 86, 58, 87, 7, 87, 13, 87, 15, 87, 16, 87, 34, 87, 43,
    87, 53, 87, 58, 87, 64, 87, 126, 88, 7, 88, 13, 88, 15, 88, 34,
    88, 43, 88, 53, 88, 58, 88, 64, 88, 126, 89, 58, 89, 64, 90, 7,
    90, 13, 90, 15, 90, 34, 90, 43, 90, 53, 90, 58, 90, 64, 90, 66,
    90, 72, 90, 126, 91, 3, 91, 8, 91, 11, 91, 13, 91, 15, 91, 34,
    91, 57, 91, 64, 91, 122, 91, 124, 91, 126, 92, 75, 98, 13, 98, 15,
    98, 34, 98, 43, 98, 74, 98, 104, 98, 108, 98, 116, 98, 126, 99, 13,
    99, 15, 99, 34, 99, 43, 99, 104, 99, 108, 99, 114, 99, 116, 99, 126,
    104, 3, 104, 7, 104, 8, 104, 11, 104, 14, 104, 32, 104, 33, 104, 98,
    104, 99, 104, 108, 104, 111, 104, 114, 104, 116, 104, 119, 104, 120, 104, 121,
    104, 122, 104, 123, 104, 124, 107, 64, 108, 7, 108, 13, 108, 15, 108, 64,
    108, 104, 108, 112, 108, 126, 109, 64, 109, 121, 109, 123, 110, 7, 110, 14,
    110, 64, 110, 100, 110, 106, 110, 107, 110, 109, 110, 113, 110, 115, 110, 117,
    110, 118, 110, 119, 110, 120, 111, 13, 111, 15, 111, 16, 111, 64, 111, 104,
    111, 112, 111, 126, 112, 3, 112, 8, 112, 11, 112, 14, 112, 33, 112, 98,
    112, 99, 112, 108, 112, 111, 112, 116, 112, 119, 112, 120, 112, 121, 112, 122,
    112, 123, 112, 124, 114, 99, 115, 13, 115, 15, 115, 16, 115, 64, 115, 104,
    115, 112, 115, 126, 116, 13, 116, 15, 116, 99, 116, 126, 117, 14, 117, 64,
    117, 111, 117, 119, 117, 120, 118, 14, 118, 64, 118, 111, 118, 119, 118, 120,
    119, 34, 119, 42, 119, 43, 119, 52, 119, 53, 119, 55, 119, 57, 119, 58,
    119, 59, 119, 89, 119, 91, 119, 104, 119, 112, 119, 116, 120, 34, 120, 42,
    120, 43, 120, 52, 120, 53, 120, 55, 120, 56, 120, 57, 120, 58, 120, 59,
    120, 89, 120, 91, 120, 104, 120, 112, 120, 116, 121, 13, 121, 15, 121, 34,
    121, 36, 121, 40, 121, 48, 121, 50, 121, 66, 121, 68, 121, 69, 121, 70,
    121, 80, 121, 82, 121, 104, 121, 106, 121, 109, 121, 110, 121, 115, 121, 117,
    121, 118, 121, 126, 122, 13, 122, 14, 122, 15, 122, 34, 122, 36, 122, 40,
    122, 43, 122, 48, 122, 50, 122, 52, 122, 66, 122, 68, 122, 69, 122, 70,
    122, 72, 122, 78, 122, 79, 122, 80, 122, 81, 122, 82, 122, 83, 122, 84,
    122, 86, 122, 89, 122, 91, 122, 100, 122, 104, 122, 106, 122, 107, 122, 109,
    122, 110, 122, 112, 122, 113, 122, 115, 122, 116, 122, 117, 122, 118, 122, 119,
    122, 120, 122, 126, 123, 13, 123, 15, 123, 34, 123, 36, 123, 40, 123, 48,
    123, 50, 123, 52, 123, 57, 123, 66, 123, 68, 123, 69, 123, 70, 123, 72,
    123, 78, 123, 79, 123, 80, 123, 82, 123, 83, 123, 84, 123, 89, 123, 100,
    123, 104, 123, 106, 123, 107, 123, 109, 123, 110, 123, 112, 123, 113, 123, 115,
    123, 117, 123, 118, 123, 126, 124, 13, 124, 14, 124, 15, 124, 27, 124, 28,
    124, 34, 124, 36, 124, 40, 124, 43, 124, 48, 124, 50, 124, 52, 124, 57,
    124, 66, 124, 68, 124, 69, 124, 70, 124, 72, 124, 78, 124, 79, 124, 80,
    124, 81, 124, 82, 124, 83, 124, 84, 124, 86, 124, 87, 124, 88, 124, 89,
    124, 90, 124, 91, 124, 100, 124, 104, 124, 106, 124, 107, 124, 108, 124, 109,
    124, 110, 124, 111, 124, 112, 124, 113, 124, 114, 124, 115, 124, 116, 124, 117,
    124, 118, 124, 119, 124, 120, 124, 126, 126, 3, 126, 8, 126, 11, 126, 32,
    126, 36, 126, 40, 126, 48, 126, 50, 126, 53, 126, 54, 126, 55, 126, 56,
    126, 58, 126, 59, 126, 85, 126, 87, 126, 88, 126, 90, 126, 98, 126, 99,
    126, 108, 126, 111, 126, 114, 126, 116, 126, 121, 126, 122, 126, 123, 126, 124,
    127, 3, 127, 8, 127, 11, 127, 121, 127, 122, 127, 123, 127, 124,
};

static const int8_t kern_pair_values[] = {
    -29, -29, -16, -13, -16, -29, -19, -19, -19, -22, -22, -22, -22, 2, -19, 3,
    3, 3, 3, 3, 3, 2, 3, 3, 5, 3, 3, 3, -29, -29, -16, 5,
    3, 5, 2, 8, 6, 6, 2, -16, 6, 3, 6, -29, 22, -29, -29, -16,
    -13, 8, -16, -29, -29, -29, -29, -26, 6, -13, -13, -13, -13, -22, -19, -13,
    -22, 10, -15, -13, -14, -16, -19, 6, -13, 6, -22, -26, -26, -26, -26, -10,
    -14, -10, -16, -10, -11, -10, -29, -29, -29, -26, 6, -13, -13, -13, -13, -22,
    -19, -13, -22, 10, -15, -13, -14, -16, -19, 6, -13, 6, -22, -26, -26, -26,
    -26, -61, -14, 6, -13, -14, -19, -14, -13, -10, -5, -16, -13, -10, -5, -16,
    -38, -38, -10, -10, -38, -10, -10, -10, -13, -13, -16, -16, -16, -5, -16, -6,
    -10, -10, -4, -10, -10, -21, -8, -17, -9, -22, -6, -10, -6, -5, -19, -16,
    -5, -5, -22, -21, -22, -21, -14, -20, -14, -13, -13, -14, -12, -10, -8, -10,
    -10, -15, -8, -10, -8, -10, -8, -13, -13, -32, -32, -27, -10, -28, -10, -10,
    -24, -10, -10, -45, -13, -10, -11, -10, -14, -10, -10, -10, -10, -11, -10, -13,
    -5, -8, -6, -5, -13, -6, -8, -32, 3, 3, 3, -10, -6, -10, -10, -27,
    -10, -14, -13, -13, -13, -13, -13, -8, -8, -8, -8, -8, -8, -8, -10, -10,
    -10, -14, -14, -10, -10, -29, -29, -29, -11, -19, -3, -13, -13, -13, -13, -24,
    -11, -23, -13, -28, -3, -3, -3, -3, -3, -6, -16, -10, -11, -26, -22, -11,
    -11, -27, -26, -27, -26, -13, 5, -13, -14, -16, -32, 5, 5, -13, -32, -32,
    -29, -23, -22, -11, -48, -32, -13, 5, -13, -14, -16, -32, 5, 5, -13, -8,
    -5, -6, -6, -3, -3, -11, -3, -3, -8, -4, -10, -4, -13, -3, -5, -5,
    -5, -8, -5, -5, -1, -3, -5, -5, -3, -11, -3, -4, -7, -6, -6, -13,
    -19, -2, -3, -5, -10, -5, -10, -5, -10, -22, -14, -22, -32, -13, -13, -10,
    -21, -8, -8, -18, -8, -8, -4, -26, -22, -21, -21, -21, -5, -26, -14, -14,
    -21, -14, -21, -14, -22, -14, -8, -11, -11, -10, -16, -14, -14, -22, -11, -11,
    -13, -8, -22, -11, -11, -19, -19, -21, -10, -10, -10, -17, -10, -10, -18, -10,
    -10, -10, -26, -13, -11, -11, -11, -13, -11, -11, -19, 5, 5, 3, 5, -16,
    -16, 1, 1, 1, -16, 3, 3, 3, 3, 2, 6, 3, 3, -18, -22, -16,
    -22, -29, -16, -16, -13, -22, -16, -16, -22, -16, -16, -14, -29, -21, -19, -19,
    -19, -20, -10, -14, -14, -19, -16, -19, -14, -19, -13, -11, -13, -13, -11, -16,
    -16, -16, -22, 10, -13, 10, -13, -13, 10, -32, -32, -16, -32, -32, -19, -26,
    -22, -26, -16, 6, -29, 8, -19, -16, -19, 8, 18, -18, -19, -16, -13, -21,
    -11, -22, -16, 6, -19, -22, -19, -14, 6, -11, -19, -30, -19, -19, 3, 3,
    6, 3, -22, 2, 3, 3, -21, -19, -16, -14, -14, 3, -15, -17, -21, -19,
    -19, 6, 10, 10, 8, 10, 10, 5, 5, 5, 5, 8, 11, 8, 4, 10,
    5, -20, 4, 5, 8, 13, 10, 10, 10, 10, 9, 7, 8, 18, 9, -18,
    -11, -8, -18, -13, -13, -13, -8, -10, -5, -5, -3, -11, -3, -4, -4, -2,
    -4, -4, -2, -10, -6, -2, -15, -9, -6, -9, -9, -6, -3, -3, -3, -4,
    -2, -2, -3, -3, -11, -11, -3, -3, 8, 8, -10, -10, -10, -10, -18, -11,
    -8, -18, -13, -13, -18, -11, -8, -18, -13, -13, -21, -19, -19, -14, -14, -21,
    -19, -16, -14, -14, -13, 10, 10, 10, -26, -26, -13, -26, 13, 16, 8, 8,
    -26, -21, -11, -17, -16, -8, -6, -14, -8, -16, -6, -15, -15, -5, -10, -10,
    -8, -11, -22, -15, -6, -13, -13, -6, -10, -11, -13, -16, -13, -13, 6, -10,
    -14, -14, -5, -10, -10, -11, -26, -4, -7, -14, 2, 2, 2, 3, 3, 3,
    3, 2, 2, 2, 3, 3, -16, -16, -13, -18, 10, -13, 10, 10, -16, -19,
    -19, -16, -22, -16, 13, 10, 13, -19, -16, -3, -16, -16, -5, -16, -6, -19,
    -16, -10, -3, -5, -16, -5, -5, -22, -21, -22, -21, -13, -6, -15, -15, -22,
    -10, -10, -15, -19, -14, -14, -3, -5, -3, -2, -3, -2, -3, -2, -3, -3,
    -3, -5, -5, -8, -8, -5, -14, -3, -4, -8, -35, -35, -35, -13, -8, -16,
    -16, -10, -6, -18, -13, -13, -38, -35, -38, -35, 8, -11, -11, -6, -19, -6,
    -9, -11, -10, -10, 10, -10, 3, -19, 2, 3, 3, 3, -19, 2, 3, 3,
    -5, -10, -8, -6, -14, -8, -10, -16, -10, -11, -5, -5, -10, -5, -5, -10,
    -8, -6, -14, -8, -3, -10, -16, -10, -11, -5, -5, -10, -5, -26, -26, -22,
    -11, -11, -11, -11, -13, -14, -14, -14, -14, -14, -22, -14, -14, -11, -14, -14,
    -14, -26, -26, -26, -26, -26, -13, -13, -26, -13, -13, -11, -22, -26, -26, -26,
    -21, -13, -13, -26, -13, -26, -13, -22, -11, -11, -13, -13, -26, -26, -16, -16,
    -19, -10, -13, -26, -10, -26, -26, -26, -26, -26, -26, -26, -22, -11, -11, -11,
    -11, -6, -5, -13, -14, -14, -14, -6, -6, -6, -14, -14, -6, -6, -5, -6,
    -22, -14, -6, -14, -11, -6, -6, -14, -14, -14, -26, -26, -26, -26, -6, -6,
    -26, -13, -13, -26, -13, -13, -11, -5, -22, -26, -26, -26, -21, -13, -13, -26,
    -13, -26, -13, -22, -11, -5, -6, -11, -8, -13, -13, -26, -26, -16, -5, -16,
    -19, -8, -10, -13, -8, -26, -10, -26, -26, -26, -26, -26, -29, -29, -29, -26,
    -13, -13, -13, -13, -22, -11, -19, -13, -22, 10, -8, -15, -13, -14, -16, -19,
    -13, -8, -8, -22, -26, -26, -26, -26, -19, -19, -19, -22, -22, -22, -22,
};

static const lv_font_fmt_txt_kern_pair_t kern_pairs = {
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 1007,
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
const lv_font_t humid1_font_plex_sans_bold_20 = {
#else
lv_font_t humid1_font_plex_sans_bold_20 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 27,
    .base_line = 6,
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc,
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_font_plex_sans_normal_20,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_SANS_BOLD_20 */
