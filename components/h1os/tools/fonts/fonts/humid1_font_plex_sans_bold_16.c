/*******************************************************************************
 * Font: humid1_font_plex_sans_bold_16 (sans bold)
 * Size: 16 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_font_plex_sans_normal_16 (LVGL >= 9.6.0 Ready)
 * License: MIT AND OFL-1.1
 ******************************************************************************/

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#elif defined(__has_include)
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

#ifndef HUMID1_FONT_PLEX_SANS_BOLD_16
#define HUMID1_FONT_PLEX_SANS_BOLD_16 1
#endif

#if HUMID1_FONT_PLEX_SANS_BOLD_16

#ifndef LV_FONT_DECLARE
#define LV_FONT_DECLARE(font_name) extern const lv_font_t font_name
#endif
LV_FONT_DECLARE(humid1_font_plex_sans_normal_16);

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (3x11) */
    0xff, 0xf6, 0xd0, 0xff, 0x80,
    /* U+0022 "" (7x5) */
    0xef, 0xdf, 0xbf, 0x7e, 0xe0,
    /* U+0023 "#" (10x11) */
    0x11, 0x8c, 0x63, 0x11, 0xff, 0x7f, 0x8c, 0xcf, 0xfb, 0xfe, 0x66, 0x19,
    0x86, 0x60,
    /* U+0024 "$" (8x13) */
    0x18, 0x7e, 0xff, 0xfa, 0xd8, 0xf8, 0x7e, 0x1f, 0x1f, 0xdf, 0xfe, 0x7c,
    0x18,
    /* U+0025 "%" (14x11) */
    0x78, 0x73, 0xe1, 0x8d, 0xcc, 0x37, 0x70, 0xfb, 0x81, 0xed, 0xe0, 0x7f,
    0xc3, 0xbb, 0x0c, 0xec, 0x63, 0xf3, 0x87, 0x80,
    /* U+0026 "&" (10x11) */
    0x3c, 0x1f, 0x86, 0x71, 0xd8, 0x7e, 0x1f, 0x7f, 0xff, 0xbe, 0xe7, 0xbf,
    0xf7, 0xdc,
    /* U+0027 "'" (3x5) */
    0xff, 0xfe,
    /* U+0028 "(" (5x14) */
    0x19, 0x9c, 0xc6, 0x73, 0x9c, 0xe3, 0x18, 0xe3, 0x1c,
    /* U+0029 ")" (5x14) */
    0xe3, 0x8c, 0x73, 0x9c, 0xe7, 0x39, 0xce, 0x67, 0x70,
    /* U+002A "" (9x8) */
    0x1c, 0x0e, 0x37, 0x7f, 0xf7, 0xe1, 0xf1, 0xdc, 0xce,
    /* U+002B "+" (8x8) */
    0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18,
    /* U+002C "," (3x5) */
    0xff, 0xbc,
    /* U+002D "-" (5x2) */
    0xff, 0xc0,
    /* U+002E "." (3x3) */
    0xff, 0x80,
    /* U+002F "/" (7x14) */
    0x06, 0x1c, 0x30, 0x61, 0xc3, 0x06, 0x1c, 0x30, 0x61, 0xc3, 0x06, 0x18,
    0x00,
    /* U+0030 "0" (9x11) */
    0x1e, 0x3f, 0x9c, 0xee, 0x7e, 0x3f, 0x1f, 0x8e, 0xe7, 0x73, 0xbf, 0x87,
    0x80,
    /* U+0031 "1" (9x11) */
    0x7e, 0x3f, 0x3f, 0x9f, 0xcd, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0x7f, 0xff,
    0xe0,
    /* U+0032 "2" (8x11) */
    0x7c, 0xfe, 0xef, 0x47, 0x0f, 0x0e, 0x3c, 0x78, 0xf0, 0xff, 0xff,
    /* U+0033 "3" (8x11) */
    0x7c, 0xfe, 0xcf, 0x0e, 0x3c, 0x3e, 0x0f, 0x07, 0xcf, 0xfe, 0x7c,
    /* U+0034 "4" (9x11) */
    0x0f, 0x07, 0x87, 0xc6, 0xe3, 0x73, 0x39, 0x9d, 0xff, 0xff, 0x83, 0x81,
    0xc0,
    /* U+0035 "5" (8x11) */
    0xff, 0xff, 0xe0, 0xc0, 0xde, 0xff, 0xe7, 0x07, 0xe7, 0xff, 0x7c,
    /* U+0036 "6" (8x11) */
    0x1e, 0x3c, 0x70, 0xe0, 0xee, 0xff, 0xe7, 0xc7, 0xe7, 0xfe, 0x3c,
    /* U+0037 "7" (8x11) */
    0xff, 0xff, 0xc7, 0xc6, 0xce, 0x0e, 0x1c, 0x1c, 0x1c, 0x38, 0x38,
    /* U+0038 "8" (8x11) */
    0x7c, 0xfe, 0xe7, 0xe7, 0x7e, 0x7e, 0xe7, 0xe7, 0xe7, 0xfe, 0x7c,
    /* U+0039 "9" (9x11) */
    0x3e, 0x3f, 0xbc, 0xfc, 0x7f, 0x3b, 0xfc, 0xfe, 0x0e, 0x0f, 0x0f, 0x0f,
    0x00,
    /* U+003A ":" (3x9) */
    0x7d, 0x80, 0x1f, 0x60,
    /* U+003B ";" (3x11) */
    0x7d, 0x80, 0x1f, 0x6f, 0x00,
    /* U+003C "<" (6x10) */
    0x04, 0x33, 0xde, 0xe3, 0x87, 0x8f, 0x0c, 0x10,
    /* U+003D "=" (8x6) */
    0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
    /* U+003E ">" (6x8) */
    0xc3, 0x87, 0x8f, 0x3d, 0xee, 0x30,
    /* U+003F "?" (8x11) */
    0x3c, 0x7e, 0xef, 0x07, 0x0e, 0x3c, 0x38, 0x00, 0x18, 0x38, 0x18,
    /* U+0040 "@" (13x13) */
    0x0f, 0x81, 0xef, 0x18, 0x0c, 0x9f, 0x6c, 0xf9, 0xec, 0xcf, 0x66, 0x7b,
    0x33, 0xcf, 0xf2, 0x77, 0x18, 0x00, 0x78, 0x00, 0xfc, 0x00,
    /* U+0041 "A" (11x11) */
    0x0f, 0x03, 0xe0, 0x7c, 0x0d, 0xc3, 0xb8, 0x77, 0x0f, 0xf3, 0xfe, 0x71,
    0xce, 0x1f, 0x83, 0x80,
    /* U+0042 "B" (9x11) */
    0xff, 0x7f, 0xb8, 0xfc, 0x7e, 0x3f, 0xfb, 0xff, 0xc7, 0xe3, 0xff, 0xff,
    0xc0,
    /* U+0043 "C" (9x11) */
    0x1e, 0x3f, 0xbc, 0xfc, 0x0e, 0x07, 0x03, 0x81, 0xc2, 0xf3, 0xbf, 0x8f,
    0x80,
    /* U+0044 "D" (10x11) */
    0xfe, 0x3f, 0xce, 0x7b, 0x8e, 0xe3, 0xf8, 0xfe, 0x3f, 0x8e, 0xe7, 0xbf,
    0xcf, 0xe0,
    /* U+0045 "E" (8x11) */
    0xff, 0xff, 0xe0, 0xe0, 0xe0, 0xfe, 0xfe, 0xe0, 0xe0, 0xff, 0xff,
    /* U+0046 "F" (8x11) */
    0xff, 0xff, 0xe0, 0xe0, 0xe0, 0xfe, 0xfe, 0xe0, 0xe0, 0xe0, 0xe0,
    /* U+0047 "G" (10x11) */
    0x3e, 0x1f, 0xef, 0x3b, 0x84, 0xe0, 0x39, 0xfe, 0x7f, 0x87, 0xf3, 0xdf,
    0xf3, 0xdc,
    /* U+0048 "H" (10x11) */
    0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe3, 0xff, 0xff, 0xff, 0x87, 0xe1, 0xf8,
    0x7e, 0x1c,
    /* U+0049 "I" (5x11) */
    0xff, 0xdc, 0xe7, 0x39, 0xce, 0x77, 0xfe,
    /* U+004A "J" (7x11) */
    0x7e, 0xfc, 0x38, 0x70, 0xe1, 0xc3, 0xa7, 0xef, 0xfd, 0xf0,
    /* U+004B "K" (10x11) */
    0xe3, 0xf8, 0xee, 0x73, 0xb8, 0xee, 0x3f, 0x8f, 0xf3, 0x9c, 0xe3, 0xb8,
    0xfe, 0x1c,
    /* U+004C "L" (7x11) */
    0xe1, 0xc3, 0x87, 0x0e, 0x1c, 0x38, 0x70, 0xe1, 0xff, 0xf8,
    /* U+004D "M" (11x11) */
    0xe0, 0xfe, 0x3f, 0xc7, 0xfd, 0xff, 0xff, 0xdf, 0xfb, 0xbf, 0x37, 0xe4,
    0xfc, 0x1f, 0x83, 0x80,
    /* U+004E "N" (10x11) */
    0xf1, 0xfc, 0x7f, 0x9f, 0xe7, 0xfd, 0xfb, 0x7e, 0xff, 0x9f, 0xe7, 0xf8,
    0xfe, 0x3c,
    /* U+004F "O" (10x11) */
    0x3e, 0x1f, 0xcf, 0x7b, 0x8e, 0xe1, 0xf8, 0x7e, 0x1f, 0x8e, 0xf7, 0x9f,
    0xc3, 0xe0,
    /* U+0050 "P" (9x11) */
    0xff, 0x7f, 0xf8, 0xfc, 0x7e, 0x3f, 0xff, 0xfd, 0xc0, 0xe0, 0x70, 0x38,
    0x00,
    /* U+0051 "Q" (10x14) */
    0x3e, 0x1f, 0xcf, 0x3b, 0x8e, 0xe1, 0xf8, 0x7e, 0x1f, 0x8e, 0xf3, 0x9f,
    0xe3, 0xe0, 0x70, 0x0f, 0x03, 0xc0,
    /* U+0052 "R" (9x11) */
    0xff, 0x7f, 0xf8, 0xfc, 0x7e, 0x3f, 0xff, 0xfd, 0xce, 0xe7, 0x73, 0xf8,
    0xe0,
    /* U+0053 "S" (9x11) */
    0x3e, 0x3f, 0xb9, 0x9c, 0x0f, 0xc3, 0xf8, 0x7c, 0x07, 0xe7, 0x7f, 0x9f,
    0x00,
    /* U+0054 "T" (9x11) */
    0xff, 0xff, 0xc7, 0x03, 0x81, 0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07,
    0x00,
    /* U+0055 "U" (9x11) */
    0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f, 0xc7, 0xf7, 0xbf, 0x8f,
    0x80,
    /* U+0056 "V" (10x11) */
    0xe0, 0xdc, 0x77, 0x1d, 0xc6, 0x33, 0x8e, 0xe3, 0xb0, 0x7c, 0x1f, 0x07,
    0x80, 0xe0,
    /* U+0057 "W" (15x11) */
    0xc7, 0x8f, 0xcf, 0x1b, 0x9e, 0x77, 0x3e, 0xe6, 0x7d, 0xcd, 0xdb, 0x1f,
    0x36, 0x3e, 0x7c, 0x7c, 0xf8, 0x79, 0xe0, 0xe1, 0xc0,
    /* U+0058 "X" (11x11) */
    0x71, 0xcf, 0x38, 0xee, 0x0f, 0xc1, 0xf0, 0x1e, 0x07, 0xc1, 0xfc, 0x3b,
    0x8e, 0x3b, 0xc7, 0x80,
    /* U+0059 "Y" (10x11) */
    0xf1, 0xdc, 0x73, 0xb8, 0xee, 0x1f, 0x07, 0xc0, 0xe0, 0x38, 0x0e, 0x03,
    0x80, 0xe0,
    /* U+005A "Z" (8x11) */
    0xff, 0xff, 0x0f, 0x0e, 0x1c, 0x3c, 0x78, 0x70, 0xf0, 0xff, 0xff,
    /* U+005B "[" (4x14) */
    0xff, 0xee, 0xee, 0xee, 0xee, 0xee, 0xff,
    /* U+005C "" (7x14) */
    0xc1, 0x83, 0x83, 0x06, 0x06, 0x0c, 0x1c, 0x18, 0x30, 0x70, 0x60, 0xc1,
    0xc0,
    /* U+005D "]" (3x14) */
    0xfd, 0xb6, 0xdb, 0x6d, 0xbf, 0xc0,
    /* U+005E "^" (8x7) */
    0x38, 0x3c, 0x7c, 0x6e, 0xe6, 0xc7, 0x40,
    /* U+005F "_" (9x2) */
    0xff, 0xff, 0xc0,
    /* U+0060 "`" (4x4) */
    0x6e, 0x73,
    /* U+0061 "a" (9x8) */
    0x3e, 0x3f, 0x81, 0xc7, 0xe7, 0x77, 0x39, 0xfe, 0xf7,
    /* U+0062 "b" (8x12) */
    0xe0, 0xe0, 0xe0, 0xe0, 0xee, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0xee,
    /* U+0063 "c" (8x8) */
    0x3e, 0x7f, 0x77, 0xf0, 0xf0, 0x77, 0x7f, 0x3e,
    /* U+0064 "d" (8x12) */
    0x07, 0x07, 0x07, 0x07, 0x77, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0x77,
    /* U+0065 "e" (9x8) */
    0x3e, 0x3f, 0x9d, 0xdf, 0xff, 0xfb, 0x81, 0xfc, 0x7c,
    /* U+0066 "f" (6x12) */
    0x3c, 0xf7, 0x1c, 0xff, 0xf7, 0x1c, 0x71, 0xc7, 0x1c,
    /* U+0067 "g" (9x13) */
    0x03, 0x01, 0xcf, 0x8f, 0xe6, 0x33, 0xf8, 0xf8, 0xc0, 0x7f, 0x3f, 0xf0,
    0xff, 0xf7, 0xf0,
    /* U+0068 "h" (8x12) */
    0xe0, 0xe0, 0xe0, 0xe0, 0xee, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7,
    /* U+0069 "i" (3x12) */
    0xff, 0x8f, 0xff, 0xff, 0xf0,
    /* U+006A "j" (4x15) */
    0x77, 0x70, 0x77, 0x77, 0x77, 0x77, 0x7f, 0xe0,
    /* U+006B "k" (8x12) */
    0xe0, 0xe0, 0xe0, 0xe0, 0xe7, 0xee, 0xfc, 0xfc, 0xfe, 0xee, 0xe7, 0xe7,
    /* U+006C "l" (4x12) */
    0xee, 0xee, 0xee, 0xee, 0xee, 0xf7,
    /* U+006D "m" (13x8) */
    0xee, 0xf7, 0xff, 0xb9, 0xdf, 0xce, 0x7e, 0x73, 0xf3, 0x9f, 0x9c, 0xfc,
    0xe7,
    /* U+006E "n" (8x8) */
    0xee, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7,
    /* U+006F "o" (9x8) */
    0x3e, 0x3f, 0x9d, 0xde, 0xff, 0x7b, 0xb9, 0xfc, 0x7c,
    /* U+0070 "p" (8x11) */
    0xee, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0xee, 0xe0, 0xe0, 0xe0,
    /* U+0071 "q" (8x11) */
    0x77, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0x77, 0x07, 0x07, 0x07,
    /* U+0072 "r" (5x8) */
    0xef, 0xfd, 0xce, 0x73, 0x9c,
    /* U+0073 "s" (7x8) */
    0x79, 0xfb, 0x07, 0xe7, 0xf1, 0xff, 0x3c,
    /* U+0074 "t" (6x11) */
    0x30, 0xc3, 0x3f, 0xfd, 0xc7, 0x1c, 0x70, 0xf3, 0xc0,
    /* U+0075 "u" (8x8) */
    0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0x77,
    /* U+0076 "v" (9x8) */
    0xe3, 0xb1, 0x9d, 0xce, 0xe3, 0x61, 0xf0, 0xf8, 0x38,
    /* U+0077 "w" (14x8) */
    0xe3, 0x9d, 0x9e, 0x67, 0x7b, 0x9d, 0xee, 0x3f, 0xf0, 0xf3, 0xc3, 0xcf,
    0x0f, 0x3c,
    /* U+0078 "x" (8x8) */
    0xe7, 0xee, 0x7c, 0x3c, 0x3c, 0x7c, 0xee, 0xc7,
    /* U+0079 "y" (9x11) */
    0xe3, 0xb1, 0x9d, 0xce, 0xe3, 0x61, 0xf0, 0xf8, 0x38, 0x1c, 0x3e, 0x1e,
    0x00,
    /* U+007A "z" (7x8) */
    0xff, 0xfc, 0x71, 0xc7, 0x1e, 0x3f, 0xff,
    /* U+007B "{" (6x14) */
    0x3c, 0xe3, 0x8e, 0x39, 0xef, 0x3c, 0x78, 0xe3, 0x8e, 0x38, 0xf0,
    /* U+007C "|" (3x14) */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xc0,
    /* U+007D "}" (5x14) */
    0xe7, 0x18, 0xc6, 0x39, 0xef, 0x73, 0x18, 0xce, 0x70,
    /* U+007E "~" (8x3) */
    0xf0, 0xff, 0x0e,
    /* U+00B0 "" (6x6) */
    0x73, 0xec, 0xf3, 0xf9, 0xc0,
    /* U+00B1 "" (8x11) */
    0x18, 0x38, 0x38, 0xff, 0xff, 0x38, 0x38, 0x38, 0x00, 0xff, 0xff,
    /* U+00B2 "" (4x6) */
    0xef, 0x36, 0xcf,
    /* U+00B3 "" (5x6) */
    0x72, 0xc6, 0x7d, 0xb8,
    /* U+00B5 "" (8x11) */
    0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0xf7, 0xe0, 0xe0, 0xe0,
    /* U+00B7 "" (3x3) */
    0x7d, 0x80,
    /* U+00D7 "" (7x7) */
    0x45, 0xcd, 0xf1, 0xe3, 0xcd, 0xd9, 0x80,
    /* U+00F7 "" (8x10) */
    0x10, 0x38, 0x38, 0x00, 0xff, 0xff, 0x00, 0x38, 0x38, 0x18,
    /* U+0394 "" (9x11) */
    0x1e, 0x1f, 0x0f, 0x86, 0xe7, 0x73, 0xb9, 0x8f, 0xc7, 0xe3, 0xff, 0xff,
    0xe0,
    /* U+03A9 "" (10x11) */
    0x3e, 0x1f, 0xef, 0x3b, 0x87, 0xe1, 0xf8, 0x7e, 0x39, 0xde, 0x37, 0x3d,
    0xff, 0x7c,
    /* U+03BC "" (9x11) */
    0xe7, 0x73, 0xb9, 0xdc, 0xee, 0x77, 0x3b, 0xff, 0xf7, 0xe0, 0x70, 0x38,
    0x00,
    /* U+2013 "" (9x2) */
    0xff, 0xff, 0xc0,
    /* U+2014 "" (11x2) */
    0xff, 0xff, 0xfc,
    /* U+2018 "" (3x5) */
    0x7b, 0xfe,
    /* U+2019 "" (3x5) */
    0xff, 0xbc,
    /* U+201C "" (7x5) */
    0x67, 0x9b, 0xbf, 0x7e, 0xe0,
    /* U+201D "" (7x5) */
    0xef, 0xdf, 0xbb, 0x3c, 0xc0,
    /* U+2022 "" (5x5) */
    0x77, 0xff, 0xf7, 0x00,
    /* U+2026 "" (13x3) */
    0xe7, 0x3f, 0x39, 0xf9, 0xce,
    /* U+2030 "" (21x11) */
    0x78, 0x70, 0x07, 0xc3, 0x00, 0x37, 0x30, 0x01, 0xbb, 0x80, 0x0f, 0xb8,
    0x00, 0x3d, 0xbc, 0x78, 0x1f, 0xf7, 0xe1, 0xdd, 0xb7, 0x0c, 0xed, 0xb8,
    0xc7, 0xef, 0xce, 0x1e, 0x3c,
    /* U+2190 "" (11x8) */
    0x10, 0x07, 0x01, 0xe0, 0x7f, 0xff, 0xfe, 0xf0, 0x0e, 0x00, 0xc0,
    /* U+2191 "" (7x11) */
    0x10, 0x71, 0xf7, 0xff, 0xe7, 0x0e, 0x1c, 0x38, 0x70, 0xe0,
    /* U+2192 "" (11x8) */
    0x01, 0x00, 0x70, 0x0f, 0x7f, 0xff, 0xfe, 0x07, 0x80, 0xe0, 0x18,
    /* U+2193 "" (7x11) */
    0x38, 0x70, 0xe1, 0xc3, 0x87, 0x3f, 0xff, 0x7c, 0x70, 0x40,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 60, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 86, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 5, .adv_w = 135, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 10, .adv_w = 153, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 24, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 37, .adv_w = 255, .box_w = 14, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 57, .adv_w = 188, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 71, .adv_w = 72, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 73, .adv_w = 87, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 82, .adv_w = 87, .box_w = 5, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 91, .adv_w = 171, .box_w = 9, .box_h = 8, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 100, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 108, .adv_w = 84, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 110, .adv_w = 104, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 112, .adv_w = 84, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 114, .adv_w = 127, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 127, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 140, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 153, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 164, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 188, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 210, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 221, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 232, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 245, .adv_w = 89, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 249, .adv_w = 89, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 254, .adv_w = 154, .box_w = 6, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 262, .adv_w = 154, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 268, .adv_w = 154, .box_w = 6, .box_h = 8, .ofs_x = 2, .ofs_y = 1},
    {.bitmap_index = 274, .adv_w = 131, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 285, .adv_w = 232, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 307, .adv_w = 180, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 323, .adv_w = 172, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 336, .adv_w = 170, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 349, .adv_w = 182, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 363, .adv_w = 158, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 374, .adv_w = 153, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 385, .adv_w = 187, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 399, .adv_w = 187, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 413, .adv_w = 114, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 420, .adv_w = 149, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 430, .adv_w = 185, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 444, .adv_w = 139, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 454, .adv_w = 210, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 470, .adv_w = 187, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 484, .adv_w = 184, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 498, .adv_w = 174, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 511, .adv_w = 184, .box_w = 10, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 529, .adv_w = 176, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 542, .adv_w = 165, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 555, .adv_w = 151, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 568, .adv_w = 179, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 581, .adv_w = 171, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 595, .adv_w = 259, .box_w = 15, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 616, .adv_w = 179, .box_w = 11, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 632, .adv_w = 173, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 646, .adv_w = 158, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 657, .adv_w = 88, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 664, .adv_w = 127, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 677, .adv_w = 88, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 683, .adv_w = 154, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 690, .adv_w = 141, .box_w = 9, .box_h = 2, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 693, .adv_w = 154, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 9},
    {.bitmap_index = 695, .adv_w = 150, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 704, .adv_w = 159, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 716, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 724, .adv_w = 159, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 736, .adv_w = 145, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 745, .adv_w = 97, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 754, .adv_w = 144, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 769, .adv_w = 156, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 781, .adv_w = 77, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 786, .adv_w = 77, .box_w = 4, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 794, .adv_w = 153, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 806, .adv_w = 81, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 812, .adv_w = 231, .box_w = 13, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 825, .adv_w = 156, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 833, .adv_w = 145, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 842, .adv_w = 159, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 853, .adv_w = 159, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 864, .adv_w = 108, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 869, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 876, .adv_w = 102, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 885, .adv_w = 156, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 893, .adv_w = 143, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 902, .adv_w = 224, .box_w = 14, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 916, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 924, .adv_w = 141, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 937, .adv_w = 139, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 944, .adv_w = 99, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 955, .adv_w = 113, .box_w = 3, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 961, .adv_w = 99, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 970, .adv_w = 154, .box_w = 8, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 973, .adv_w = 121, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 978, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 989, .adv_w = 89, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 992, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 996, .adv_w = 157, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1007, .adv_w = 95, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1009, .adv_w = 154, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 1016, .adv_w = 154, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1026, .adv_w = 179, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1039, .adv_w = 183, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1053, .adv_w = 162, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1066, .adv_w = 151, .box_w = 9, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1069, .adv_w = 200, .box_w = 11, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1072, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1074, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1076, .adv_w = 144, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1081, .adv_w = 144, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1086, .adv_w = 114, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1090, .adv_w = 240, .box_w = 13, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1095, .adv_w = 362, .box_w = 21, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1124, .adv_w = 240, .box_w = 11, .box_h = 8, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1135, .adv_w = 240, .box_w = 7, .box_h = 11, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 1145, .adv_w = 240, .box_w = 11, .box_h = 8, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1156, .adv_w = 240, .box_w = 7, .box_h = 11, .ofs_x = 4, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0000, 0x0001, 0x0002, 0x0003, 0x0005, 0x0007, 0x0027, 0x0047, 0x02e4, 0x02f9,
    0x030c, 0x1f63, 0x1f64, 0x1f68, 0x1f69, 0x1f6c, 0x1f6d, 0x1f72, 0x1f76, 0x1f80,
    0x20e0, 0x20e1, 0x20e2, 0x20e3,
};

static const lv_font_fmt_txt_cmap_t cmaps[] = {
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 176, .range_length = 8420, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 24, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

static const lv_font_fmt_txt_dsc_t font_dsc = {
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
};

/*-----------------
 *  PUBLIC FONT (LVGL >= 9.6.0)
 *----------------*/

const lv_font_t humid1_font_plex_sans_bold_16 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 22,
    .base_line = 5,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 11,
    .x_height = 8,
#endif
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = -1,
    .underline_thickness = 2,
#if LV_VERSION_CHECK(9, 3, 0) || (LVGL_VERSION_MAJOR == 9 && LVGL_VERSION_MINOR >= 3) || LVGL_VERSION_MAJOR > 9
    .static_bitmap = 0,
#endif
    .dsc = &font_dsc,
#if LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_font_plex_sans_normal_16,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_SANS_BOLD_16 */
