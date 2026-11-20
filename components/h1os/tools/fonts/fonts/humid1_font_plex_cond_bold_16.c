/*******************************************************************************
 * Font: humid1_font_plex_cond_bold_16 (cond bold)
 * Size: 16 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_font_plex_sans_bold_16 (LVGL >= 9.6.0 Ready)
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

#ifndef HUMID1_FONT_PLEX_COND_BOLD_16
#define HUMID1_FONT_PLEX_COND_BOLD_16 1
#endif

#if HUMID1_FONT_PLEX_COND_BOLD_16

#ifndef LV_FONT_DECLARE
#define LV_FONT_DECLARE(font_name) extern const lv_font_t font_name
#endif
LV_FONT_DECLARE(humid1_font_plex_sans_bold_16);

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (3x12) */
    0xff, 0xff, 0xf6, 0x1b, 0xe0,
    /* U+0022 "" (5x4) */
    0xde, 0xf7, 0xb0,
    /* U+0023 "#" (9x12) */
    0x1b, 0x0d, 0x86, 0x83, 0x47, 0xfb, 0xfc, 0xd9, 0xfe, 0xff, 0x1e, 0x0b,
    0x0d, 0x80,
    /* U+0024 "$" (6x11) */
    0x3b, 0xff, 0x70, 0xf1, 0xe3, 0xc7, 0x9f, 0xff, 0x80,
    /* U+0025 "%" (12x12) */
    0x70, 0xc7, 0x88, 0x59, 0x8d, 0x90, 0xdb, 0x05, 0xae, 0x7e, 0xf3, 0x4b,
    0x0d, 0xb0, 0xcb, 0x18, 0xf1, 0x86,
    /* U+0026 "&" (9x12) */
    0x38, 0x3e, 0x33, 0x09, 0x87, 0xc3, 0xc1, 0xc7, 0xb7, 0xcf, 0x63, 0xbf,
    0xcf, 0x30,
    /* U+0027 "'" (2x4) */
    0xff,
    /* U+0028 "(" (3x14) */
    0x6f, 0xed, 0xb6, 0xdb, 0x76, 0xc0,
    /* U+0029 ")" (4x14) */
    0xcc, 0x66, 0x66, 0x67, 0x66, 0x66, 0xcc,
    /* U+002A "" (6x7) */
    0x30, 0xcb, 0x7f, 0x79, 0xed, 0x80,
    /* U+002B "+" (7x8) */
    0x30, 0x60, 0xc7, 0xef, 0xe6, 0x0c, 0x18,
    /* U+002C "," (2x4) */
    0xfe,
    /* U+002D "-" (4x2) */
    0x7f,
    /* U+002E "." (3x3) */
    0xdf, 0x00,
    /* U+002F "/" (6x12) */
    0x0c, 0x71, 0x86, 0x38, 0xc3, 0x1c, 0x71, 0x86, 0x38,
    /* U+0030 "0" (8x12) */
    0x3c, 0x7e, 0x76, 0x67, 0x67, 0xe7, 0xe7, 0x67, 0x67, 0x76, 0x7e, 0x3c,
    /* U+0031 "1" (6x12) */
    0x1c, 0xf7, 0xff, 0x5c, 0x71, 0xc7, 0x1c, 0x71, 0xc7,
    /* U+0032 "2" (7x12) */
    0x7d, 0xff, 0x38, 0x70, 0xe1, 0xc7, 0x1c, 0x71, 0xe3, 0xff, 0xf0,
    /* U+0033 "3" (7x12) */
    0x7d, 0xfd, 0x38, 0x70, 0xef, 0x9f, 0x87, 0x0e, 0x1f, 0xff, 0xc0,
    /* U+0034 "4" (9x12) */
    0x06, 0x07, 0x03, 0x83, 0xc3, 0xe1, 0xb1, 0xd8, 0xcc, 0xff, 0xff, 0xc1,
    0x80, 0xc0,
    /* U+0035 "5" (8x12) */
    0x7c, 0x7c, 0x60, 0xe0, 0xf8, 0xfc, 0x0e, 0x0e, 0x0f, 0x0f, 0xfe, 0xfc,
    /* U+0036 "6" (7x12) */
    0x3c, 0xfb, 0x86, 0x0d, 0x9f, 0xbb, 0xe7, 0xcf, 0xdf, 0xf1, 0xc0,
    /* U+0037 "7" (8x12) */
    0xff, 0xff, 0x06, 0x0e, 0x0e, 0x0c, 0x1c, 0x1c, 0x18, 0x38, 0x38, 0x30,
    /* U+0038 "8" (7x12) */
    0x38, 0xfb, 0xbf, 0x37, 0xef, 0x9f, 0x77, 0xc7, 0x0d, 0xf9, 0xe0,
    /* U+0039 "9" (7x12) */
    0x79, 0xfb, 0xbf, 0x3e, 0x7d, 0xdf, 0x9f, 0x0e, 0x3f, 0xf3, 0xc0,
    /* U+003A ":" (3x9) */
    0xdf, 0x00, 0x37, 0xc0,
    /* U+003B ";" (3x11) */
    0xff, 0x80, 0x07, 0xfb, 0x00,
    /* U+003C "<" (7x8) */
    0x06, 0x1c, 0xf7, 0x8e, 0x1f, 0x0f, 0x07,
    /* U+003D "=" (7x5) */
    0xff, 0xfc, 0x07, 0xff, 0xe0,
    /* U+003E ">" (7x8) */
    0x81, 0x81, 0xc1, 0xe1, 0xe7, 0xbc, 0x60,
    /* U+003F "?" (7x12) */
    0x7d, 0xfd, 0x38, 0x70, 0xe3, 0x8e, 0x1c, 0x00, 0x70, 0xe1, 0xc0,
    /* U+0040 "@" (11x14) */
    0x0f, 0x07, 0xf1, 0xc3, 0x37, 0xed, 0xf7, 0xf6, 0xfc, 0xdf, 0x9b, 0xf3,
    0x7b, 0xfb, 0x33, 0x30, 0x03, 0xf8, 0x3e, 0x00,
    /* U+0041 "A" (10x12) */
    0x0e, 0x07, 0x81, 0xf0, 0x7c, 0x3b, 0x0e, 0xe3, 0x39, 0xfe, 0x7f, 0xdc,
    0x7e, 0x1f, 0x87,
    /* U+0042 "B" (8x12) */
    0xfc, 0xfe, 0xe7, 0xe7, 0xe7, 0xfe, 0xfe, 0xe7, 0xe7, 0xe7, 0xfe, 0xfc,
    /* U+0043 "C" (8x12) */
    0x1f, 0x7f, 0x70, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0x70, 0x7f, 0x1f,
    /* U+0044 "D" (9x12) */
    0xfc, 0x7f, 0x39, 0xdc, 0x6e, 0x3f, 0x1f, 0x8f, 0xc7, 0xe3, 0x73, 0xbf,
    0x9f, 0x80,
    /* U+0045 "E" (6x12) */
    0xff, 0xfe, 0x38, 0xe3, 0xff, 0xf8, 0xe3, 0x8f, 0xff,
    /* U+0046 "F" (6x12) */
    0xff, 0xfe, 0x38, 0xe3, 0xff, 0xf8, 0xe3, 0x8e, 0x38,
    /* U+0047 "G" (9x12) */
    0x0f, 0x8f, 0xcc, 0x4c, 0x06, 0x03, 0x7f, 0xbf, 0xc7, 0xf3, 0xb9, 0xdf,
    0xe3, 0xe0,
    /* U+0048 "H" (9x12) */
    0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0xff, 0xff, 0xc7, 0xe3, 0xf1, 0xf8,
    0xfc, 0x70,
    /* U+0049 "I" (6x12) */
    0xff, 0xf7, 0x8c, 0x30, 0xc3, 0x0c, 0x30, 0xe7, 0xff,
    /* U+004A "J" (5x15) */
    0x39, 0xce, 0x73, 0x9c, 0xe7, 0x39, 0xce, 0x73, 0xff, 0xc0,
    /* U+004B "K" (9x12) */
    0xe3, 0xf3, 0xbb, 0x9d, 0xcf, 0xc7, 0xe3, 0xf1, 0xdc, 0xee, 0x73, 0xb9,
    0xdc, 0x70,
    /* U+004C "L" (7x12) */
    0xe1, 0xc3, 0x87, 0x0e, 0x1c, 0x38, 0x70, 0xe1, 0xc3, 0xff, 0xf0,
    /* U+004D "M" (12x12) */
    0xf0, 0xff, 0x0f, 0xf9, 0xff, 0x9f, 0xf9, 0xff, 0x9f, 0xff, 0xff, 0xff,
    0xef, 0x7e, 0xf7, 0xef, 0x7e, 0xe7,
    /* U+004E "N" (10x12) */
    0xf1, 0xfc, 0x7f, 0x9f, 0xe7, 0xfd, 0xff, 0x7e, 0xff, 0xbf, 0xe7, 0xf9,
    0xfe, 0x3f, 0x8f,
    /* U+004F "O" (9x12) */
    0x3e, 0x3f, 0x98, 0xfc, 0x7e, 0x1f, 0x0f, 0x87, 0xc3, 0xe3, 0xb1, 0xdf,
    0xc7, 0xc0,
    /* U+0050 "P" (8x12) */
    0xfc, 0xfe, 0xe7, 0xe7, 0xe7, 0xe7, 0xfe, 0xfc, 0xe0, 0xe0, 0xe0, 0xe0,
    /* U+0051 "Q" (10x15) */
    0x3f, 0x1f, 0xef, 0x3f, 0x87, 0xe1, 0xf8, 0x7e, 0x1f, 0x87, 0xe1, 0xfc,
    0xf7, 0xf8, 0xfc, 0x07, 0x80, 0xf0, 0x1c,
    /* U+0052 "R" (8x12) */
    0xfc, 0xfe, 0xee, 0xe6, 0xe6, 0xee, 0xfe, 0xfc, 0xec, 0xee, 0xe7, 0xe3,
    /* U+0053 "S" (7x12) */
    0x3d, 0xff, 0x97, 0x0f, 0x1f, 0x9f, 0x0f, 0x0f, 0x1f, 0xf7, 0xc0,
    /* U+0054 "T" (8x12) */
    0xff, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    /* U+0055 "U" (9x12) */
    0xe3, 0xf1, 0xf8, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f, 0xc7, 0xe3, 0xbb, 0x9f,
    0xc7, 0xc0,
    /* U+0056 "V" (10x12) */
    0xe1, 0xf8, 0x77, 0x39, 0xce, 0x73, 0x8c, 0xc3, 0xf0, 0xfc, 0x1f, 0x07,
    0x81, 0xe0, 0x78,
    /* U+0057 "W" (14x12) */
    0xe3, 0x9f, 0x8e, 0x76, 0x79, 0xdd, 0xe7, 0x77, 0xd9, 0xdf, 0xe7, 0xff,
    0x8f, 0xbe, 0x3e, 0xf8, 0xf3, 0xc3, 0xcf, 0x07, 0x1c,
    /* U+0058 "X" (10x12) */
    0xe1, 0xdc, 0xe7, 0x38, 0xfc, 0x1f, 0x07, 0x81, 0xe0, 0xfc, 0x3f, 0x1c,
    0xe7, 0x3b, 0x87,
    /* U+0059 "Y" (9x12) */
    0xe3, 0xb1, 0xdd, 0xc6, 0xe3, 0xe1, 0xf0, 0x70, 0x38, 0x1c, 0x0e, 0x07,
    0x03, 0x80,
    /* U+005A "Z" (8x12) */
    0xff, 0xff, 0x06, 0x0e, 0x1c, 0x1c, 0x38, 0x38, 0x70, 0x70, 0xff, 0xff,
    /* U+005B "[" (3x14) */
    0xff, 0x6d, 0xb6, 0xdb, 0x6f, 0xc0,
    /* U+005C "" (6x12) */
    0xe1, 0x86, 0x1c, 0x70, 0xc3, 0x0e, 0x18, 0x61, 0xc3,
    /* U+005D "]" (4x14) */
    0xff, 0x33, 0x33, 0x33, 0x33, 0x33, 0xff,
    /* U+005E "^" (7x7) */
    0x30, 0x61, 0xe3, 0x4c, 0xd9, 0xa1, 0x80,
    /* U+005F "_" (5x1) */
    0xf8,
    /* U+0060 "`" (4x3) */
    0xe7, 0x30,
    /* U+0061 "a" (7x9) */
    0x78, 0xf8, 0x3b, 0xff, 0xfd, 0xf3, 0xff, 0x76,
    /* U+0062 "b" (8x12) */
    0xe0, 0xe0, 0xe0, 0xfc, 0xfe, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xfe, 0xfc,
    /* U+0063 "c" (6x9) */
    0x3d, 0xfe, 0x38, 0xe3, 0x8e, 0x3f, 0x7c,
    /* U+0064 "d" (7x12) */
    0x0e, 0x1c, 0x3b, 0xff, 0xfd, 0xf1, 0xe3, 0xc7, 0xdf, 0xfb, 0xb0,
    /* U+0065 "e" (7x9) */
    0x3c, 0xff, 0x9f, 0xff, 0xfc, 0x38, 0x3f, 0x3e,
    /* U+0066 "f" (7x12) */
    0x1e, 0x78, 0xc3, 0xef, 0xc6, 0x0c, 0x18, 0x30, 0x60, 0xc1, 0x80,
    /* U+0067 "g" (8x13) */
    0x7f, 0xff, 0xe7, 0xc7, 0xc7, 0xc7, 0xe7, 0xff, 0x7f, 0x07, 0x8e, 0xfe,
    0xfc,
    /* U+0068 "h" (8x12) */
    0xe0, 0xe0, 0xe0, 0xfe, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7,
    /* U+0069 "i" (3x12) */
    0xc8, 0x7f, 0xff, 0xff, 0xf0,
    /* U+006A "j" (5x16) */
    0x39, 0xc6, 0x73, 0x9c, 0xe7, 0x39, 0xce, 0x73, 0x9f, 0xfe,
    /* U+006B "k" (8x12) */
    0xe0, 0xe0, 0xe0, 0xe7, 0xee, 0xfe, 0xfc, 0xfc, 0xfc, 0xee, 0xe7, 0xe7,
    /* U+006C "l" (3x12) */
    0xff, 0xff, 0xff, 0xff, 0xf0,
    /* U+006D "m" (12x9) */
    0xfe, 0xef, 0xff, 0xe7, 0x7e, 0x73, 0xe7, 0x3e, 0x73, 0xe7, 0x3e, 0x73,
    0xe7, 0x30,
    /* U+006E "n" (8x9) */
    0xfe, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7,
    /* U+006F "o" (7x9) */
    0x39, 0xfb, 0xbe, 0x3c, 0x78, 0xfb, 0xfe, 0x38,
    /* U+0070 "p" (8x13) */
    0xfc, 0xfe, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xfe, 0xfc, 0xe0, 0xe0, 0xe0,
    0xe0,
    /* U+0071 "q" (8x13) */
    0x7f, 0xff, 0xe7, 0xc7, 0xc7, 0xc7, 0xe7, 0xff, 0x7f, 0x07, 0x07, 0x07,
    0x07,
    /* U+0072 "r" (5x9) */
    0xdf, 0xf9, 0xce, 0x73, 0x9c, 0xe0,
    /* U+0073 "s" (6x9) */
    0x7f, 0xfe, 0x3c, 0x7c, 0xf1, 0xff, 0xf8,
    /* U+0074 "t" (6x11) */
    0x30, 0xc7, 0xff, 0x71, 0xc7, 0x1c, 0x71, 0xf3, 0xc0,
    /* U+0075 "u" (8x9) */
    0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0x7f, 0x7f,
    /* U+0076 "v" (9x9) */
    0xe3, 0xb3, 0x9d, 0xce, 0xe3, 0xe1, 0xf0, 0xf8, 0x38, 0x1c, 0x00,
    /* U+0077 "w" (13x9) */
    0xe7, 0x3b, 0x39, 0x9f, 0xfc, 0xff, 0xe7, 0xff, 0x1e, 0xf0, 0xf7, 0x87,
    0xbc, 0x39, 0xe0,
    /* U+0078 "x" (8x9) */
    0xe7, 0x77, 0x3e, 0x3e, 0x3c, 0x3e, 0x7e, 0x77, 0xe7,
    /* U+0079 "y" (8x13) */
    0xe7, 0xe7, 0x77, 0x76, 0x7e, 0x3e, 0x3e, 0x3c, 0x1c, 0x1c, 0x38, 0x78,
    0x70,
    /* U+007A "z" (7x9) */
    0x7e, 0xfc, 0x70, 0xe3, 0x86, 0x1c, 0x7f, 0xfe,
    /* U+007B "{" (6x14) */
    0x1c, 0xf3, 0x8e, 0x38, 0xef, 0x3c, 0x38, 0xe3, 0x8e, 0x3c, 0x70,
    /* U+007C "|" (2x16) */
    0xff, 0xff, 0xff, 0xff,
    /* U+007D "}" (5x14) */
    0xc7, 0x18, 0xc6, 0x39, 0xef, 0x73, 0x18, 0xce, 0x60,
    /* U+007E "~" (7x3) */
    0xe1, 0xfc, 0x70,
    /* U+00B0 "" (5x6) */
    0x77, 0xf7, 0xbf, 0xb8,
    /* U+00B1 "" (7x10) */
    0x30, 0x60, 0xc7, 0xff, 0xc6, 0x0c, 0x18, 0xfd, 0xf8,
    /* U+00B2 "" (5x7) */
    0xf7, 0x8e, 0x66, 0x7b, 0xe0,
    /* U+00B3 "" (5x8) */
    0x67, 0xac, 0xef, 0x1f, 0xfe,
    /* U+00B5 "" (8x13) */
    0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xef, 0xff, 0xff, 0xe0, 0xe0, 0xe0,
    0xe0,
    /* U+00B7 "" (3x3) */
    0xdf, 0x00,
    /* U+00D7 "" (6x6) */
    0xcf, 0xf7, 0x9c, 0x7b, 0x30,
    /* U+00F7 "" (7x8) */
    0x30, 0x60, 0x07, 0xff, 0xc0, 0x0c, 0x18,
    /* U+0394 "" (10x12) */
    0x1e, 0x07, 0x81, 0xe0, 0xfc, 0x3f, 0x0c, 0xc3, 0x39, 0xce, 0x71, 0x98,
    0x6f, 0xff, 0xff,
    /* U+03A9 "" (11x12) */
    0x1f, 0x07, 0xf1, 0xc7, 0x38, 0xe7, 0x0c, 0xe1, 0x9c, 0x33, 0x86, 0x31,
    0xc7, 0x33, 0xef, 0xfd, 0xf0,
    /* U+03BC "" (8x13) */
    0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xef, 0xff, 0xff, 0xe0, 0xe0, 0xe0,
    0xe0,
    /* U+2013 "" (5x2) */
    0xff, 0xc0,
    /* U+2014 "" (12x2) */
    0xff, 0xff, 0xff,
    /* U+2018 "" (4x4) */
    0x77, 0xee,
    /* U+2019 "" (4x4) */
    0x76, 0xee,
    /* U+201C "" (7x4) */
    0x66, 0xdf, 0xb7, 0x60,
    /* U+201D "" (7x4) */
    0x7e, 0xdd, 0xb7, 0x60,
    /* U+2022 "" (4x5) */
    0x7f, 0xff, 0x60,
    /* U+2026 "" (11x3) */
    0xcc, 0xdd, 0xdf, 0x33, 0x00,
    /* U+2030 "" (16x12) */
    0x61, 0x80, 0xf1, 0x00, 0xb3, 0x00, 0xb2, 0x00, 0xb6, 0x00, 0xb4, 0xc6,
    0xfd, 0xef, 0x69, 0x6d, 0x1b, 0x69, 0x11, 0x6d, 0x31, 0xef, 0x30, 0xc6,
    /* U+2190 "" (11x5) */
    0x20, 0x08, 0x03, 0xff, 0xa0, 0x02, 0x00,
    /* U+2191 "" (5x11) */
    0x23, 0xbe, 0x42, 0x10, 0x84, 0x21, 0x08,
    /* U+2192 "" (11x5) */
    0x00, 0x80, 0x1b, 0xff, 0x80, 0x60, 0x08,
    /* U+2193 "" (5x11) */
    0x21, 0x08, 0x42, 0x10, 0x84, 0xfb, 0x88,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 58, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 67, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 5, .adv_w = 115, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 8, .adv_w = 145, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 22, .adv_w = 135, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 31, .adv_w = 209, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 175, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 63, .adv_w = 66, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 64, .adv_w = 82, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 70, .adv_w = 82, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 77, .adv_w = 121, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 83, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 90, .adv_w = 66, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 91, .adv_w = 72, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 92, .adv_w = 66, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 99, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 124, .adv_w = 135, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 135, .adv_w = 135, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 135, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 160, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 172, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 183, .adv_w = 128, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 195, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 206, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 66, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 221, .adv_w = 71, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 226, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 233, .adv_w = 128, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 238, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 245, .adv_w = 114, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 256, .adv_w = 201, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 276, .adv_w = 162, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 291, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 303, .adv_w = 150, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 167, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 329, .adv_w = 126, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 338, .adv_w = 127, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 347, .adv_w = 162, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 361, .adv_w = 175, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 95, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 384, .adv_w = 81, .box_w = 5, .box_h = 15, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 394, .adv_w = 155, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 408, .adv_w = 133, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 419, .adv_w = 218, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 437, .adv_w = 189, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 452, .adv_w = 180, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 466, .adv_w = 148, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 478, .adv_w = 185, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 497, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 509, .adv_w = 131, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 520, .adv_w = 133, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 532, .adv_w = 173, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 546, .adv_w = 153, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 561, .adv_w = 224, .box_w = 14, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 582, .adv_w = 162, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 597, .adv_w = 148, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 611, .adv_w = 131, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 623, .adv_w = 74, .box_w = 3, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 629, .adv_w = 99, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 638, .adv_w = 74, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 645, .adv_w = 128, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 652, .adv_w = 87, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 653, .adv_w = 88, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 10},
    {.bitmap_index = 655, .adv_w = 142, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 663, .adv_w = 149, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 675, .adv_w = 122, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 682, .adv_w = 144, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 693, .adv_w = 140, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 701, .adv_w = 94, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 712, .adv_w = 149, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 725, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 737, .adv_w = 75, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 742, .adv_w = 76, .box_w = 5, .box_h = 16, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 752, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 764, .adv_w = 75, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 769, .adv_w = 227, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 783, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 792, .adv_w = 141, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 800, .adv_w = 149, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 813, .adv_w = 149, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 826, .adv_w = 108, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 832, .adv_w = 119, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 839, .adv_w = 108, .box_w = 6, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 848, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 857, .adv_w = 135, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 868, .adv_w = 199, .box_w = 13, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 883, .adv_w = 137, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 892, .adv_w = 136, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 905, .adv_w = 112, .box_w = 7, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 913, .adv_w = 95, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 924, .adv_w = 123, .box_w = 2, .box_h = 16, .ofs_x = 3, .ofs_y = -4},
    {.bitmap_index = 928, .adv_w = 95, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 937, .adv_w = 128, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 940, .adv_w = 103, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 944, .adv_w = 128, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 953, .adv_w = 92, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 958, .adv_w = 92, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 963, .adv_w = 153, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 976, .adv_w = 64, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 978, .adv_w = 128, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 983, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 990, .adv_w = 155, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1005, .adv_w = 177, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1022, .adv_w = 148, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1035, .adv_w = 112, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1037, .adv_w = 224, .box_w = 12, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1040, .adv_w = 56, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 1042, .adv_w = 56, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 1044, .adv_w = 113, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 1048, .adv_w = 107, .box_w = 7, .box_h = 4, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 1052, .adv_w = 91, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1055, .adv_w = 191, .box_w = 11, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1060, .adv_w = 294, .box_w = 16, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1084, .adv_w = 203, .box_w = 11, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1091, .adv_w = 112, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1098, .adv_w = 203, .box_w = 11, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1105, .adv_w = 112, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0}
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

const lv_font_t humid1_font_plex_cond_bold_16 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 23,
    .base_line = 5,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 12,
    .x_height = 9,
#endif
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = -2,
    .underline_thickness = 1,
#if LV_VERSION_CHECK(9, 3, 0) || (LVGL_VERSION_MAJOR == 9 && LVGL_VERSION_MINOR >= 3) || LVGL_VERSION_MAJOR > 9
    .static_bitmap = 0,
#endif
    .dsc = &font_dsc,
#if LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_font_plex_sans_bold_16,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_COND_BOLD_16 */
