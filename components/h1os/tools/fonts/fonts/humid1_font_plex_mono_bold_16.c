/*******************************************************************************
 * Font: humid1_font_plex_mono_bold_16 (mono bold)
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

#ifndef HUMID1_FONT_PLEX_MONO_BOLD_16
#define HUMID1_FONT_PLEX_MONO_BOLD_16 1
#endif

#if HUMID1_FONT_PLEX_MONO_BOLD_16

#ifndef LV_FONT_DECLARE
#define LV_FONT_DECLARE(font_name) extern const lv_font_t font_name
#endif
LV_FONT_DECLARE(humid1_font_plex_sans_bold_16);

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (4x11) */
    0xee, 0xee, 0x66, 0x40, 0xef, 0xe0,
    /* U+0022 "" (7x5) */
    0xef, 0xdf, 0xbf, 0x7e, 0xe0,
    /* U+0023 "#" (9x11) */
    0x1b, 0x0d, 0x86, 0xcf, 0x77, 0x79, 0xb3, 0xdf, 0xef, 0x36, 0x3b, 0x1b,
    0x80,
    /* U+0024 "$" (8x15) */
    0x18, 0x18, 0x7e, 0xff, 0xfa, 0xf8, 0xf8, 0x7e, 0x1f, 0x1b, 0xdf, 0xfe,
    0x7c, 0x18, 0x18,
    /* U+0025 "%" (9x11) */
    0x71, 0xfc, 0xf6, 0xdb, 0x6f, 0xa3, 0x98, 0xde, 0x69, 0x64, 0xb3, 0xf0,
    0xc0,
    /* U+0026 "&" (9x11) */
    0x3c, 0x3f, 0x19, 0x0e, 0x03, 0x03, 0xdd, 0xff, 0xde, 0xe7, 0x3f, 0xde,
    0xe0,
    /* U+0027 "'" (3x5) */
    0xff, 0xfe,
    /* U+0028 "(" (5x14) */
    0x3b, 0x99, 0xcc, 0x63, 0x18, 0xc6, 0x38, 0xc7, 0x1c,
    /* U+0029 ")" (5x14) */
    0xc3, 0x1c, 0x63, 0x8c, 0x63, 0x19, 0xcc, 0xe6, 0x60,
    /* U+002A "" (8x8) */
    0x18, 0x18, 0xff, 0xff, 0x7c, 0x7c, 0xee, 0x66,
    /* U+002B "+" (8x8) */
    0x38, 0x38, 0x38, 0xff, 0xff, 0x38, 0x38, 0x38,
    /* U+002C "," (4x5) */
    0xfe, 0xec, 0xc0,
    /* U+002D "-" (5x2) */
    0xff, 0xc0,
    /* U+002E "." (4x3) */
    0xef, 0xe0,
    /* U+002F "/" (7x14) */
    0x06, 0x1c, 0x38, 0x61, 0xc3, 0x86, 0x1c, 0x38, 0x61, 0xc3, 0x86, 0x1c,
    0x00,
    /* U+0030 "0" (9x11) */
    0x3e, 0x3f, 0x9c, 0xfc, 0x7e, 0x3f, 0x7f, 0xbf, 0xc7, 0x73, 0xbf, 0x8f,
    0x80,
    /* U+0031 "1" (9x11) */
    0x7e, 0x3f, 0x3f, 0x9b, 0xcd, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0x7f, 0xff,
    0xe0,
    /* U+0032 "2" (8x11) */
    0x7c, 0xfe, 0xef, 0x47, 0x0f, 0x0e, 0x3c, 0x78, 0xf0, 0xff, 0xff,
    /* U+0033 "3" (8x11) */
    0x7c, 0xff, 0x47, 0x07, 0x3e, 0x3e, 0x07, 0x07, 0xc7, 0xfe, 0x7c,
    /* U+0034 "4" (9x11) */
    0x0f, 0x07, 0x87, 0xc7, 0xe3, 0x73, 0x39, 0x9d, 0xff, 0xff, 0x83, 0x81,
    0xc0,
    /* U+0035 "5" (8x11) */
    0xff, 0xff, 0xc0, 0xc0, 0xde, 0xff, 0x47, 0x07, 0xc7, 0xff, 0x7c,
    /* U+0036 "6" (9x11) */
    0x0f, 0x0f, 0x0e, 0x0e, 0x07, 0x73, 0xff, 0xcf, 0xc7, 0x73, 0xbf, 0xc7,
    0x80,
    /* U+0037 "7" (8x11) */
    0xff, 0xff, 0xc7, 0xc7, 0x0e, 0x0e, 0x1c, 0x1c, 0x1c, 0x38, 0x38,
    /* U+0038 "8" (9x11) */
    0x3e, 0x3f, 0x9c, 0xee, 0x73, 0xf1, 0xf9, 0xcf, 0xc7, 0x73, 0xbf, 0xcf,
    0x80,
    /* U+0039 "9" (9x11) */
    0x3e, 0x3f, 0xbc, 0xfc, 0x7f, 0x3b, 0xfc, 0xee, 0x0e, 0x0f, 0x0f, 0x0f,
    0x00,
    /* U+003A ":" (4x8) */
    0xef, 0xe0, 0x0e, 0xfe,
    /* U+003B ";" (4x10) */
    0xef, 0xe0, 0x0f, 0xee, 0xcc,
    /* U+003C "<" (7x10) */
    0x02, 0x1c, 0x7b, 0xcf, 0x1e, 0x1e, 0x0f, 0x0e, 0x04,
    /* U+003D "=" (8x6) */
    0xff, 0xff, 0x00, 0x00, 0xff, 0xff,
    /* U+003E ">" (7x10) */
    0x81, 0xc1, 0xe1, 0xf0, 0xe1, 0xcf, 0xbc, 0xe1, 0x00,
    /* U+003F "?" (8x11) */
    0x7c, 0xfe, 0xef, 0x0f, 0x0e, 0x3e, 0x38, 0x00, 0x38, 0x38, 0x38,
    /* U+0040 "@" (9x13) */
    0x1e, 0x1f, 0x98, 0x6d, 0xf6, 0xff, 0x6f, 0xb7, 0xdb, 0x6f, 0xb7, 0xd8,
    0x07, 0xc1, 0xe0,
    /* U+0041 "A" (10x11) */
    0x1e, 0x0f, 0x83, 0xe0, 0xdc, 0x37, 0x1c, 0xc7, 0xf9, 0xfe, 0x63, 0xb8,
    0xee, 0x1c,
    /* U+0042 "B" (8x11) */
    0xfc, 0xfe, 0xe7, 0xe7, 0xfe, 0xfe, 0xe7, 0xe7, 0xe7, 0xff, 0xfc,
    /* U+0043 "C" (9x11) */
    0x1e, 0x1f, 0x9c, 0xee, 0x66, 0x07, 0x01, 0x80, 0xe6, 0x73, 0x9f, 0x87,
    0x80,
    /* U+0044 "D" (8x11) */
    0xfc, 0xfe, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xfe, 0xfc,
    /* U+0045 "E" (8x11) */
    0xff, 0xff, 0xe0, 0xe0, 0xfe, 0xfe, 0xe0, 0xe0, 0xe0, 0xff, 0xff,
    /* U+0046 "F" (8x11) */
    0xff, 0xff, 0xe0, 0xe0, 0xfe, 0xfe, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
    /* U+0047 "G" (9x11) */
    0x1e, 0x3f, 0x9c, 0xee, 0x66, 0x07, 0x3f, 0x9e, 0xe7, 0x73, 0xbf, 0xce,
    0xe0,
    /* U+0048 "H" (8x11) */
    0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7,
    /* U+0049 "I" (7x11) */
    0xff, 0xfc, 0xe1, 0xc3, 0x87, 0x0e, 0x1c, 0x39, 0xff, 0xf8,
    /* U+004A "J" (9x11) */
    0x3f, 0x9f, 0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xcf, 0xf7, 0x3f, 0x8f,
    0x80,
    /* U+004B "K" (9x11) */
    0xe7, 0x73, 0xbb, 0x9f, 0x8f, 0xc7, 0xe3, 0xf9, 0xdc, 0xef, 0x73, 0xb9,
    0xe0,
    /* U+004C "L" (8x11) */
    0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xff, 0xff,
    /* U+004D "M" (9x11) */
    0xf3, 0xf9, 0xff, 0xff, 0xff, 0xff, 0x6f, 0xb7, 0xd3, 0xe1, 0xf0, 0xf8,
    0x60,
    /* U+004E "N" (8x11) */
    0xe7, 0xf7, 0xf7, 0xf7, 0xf7, 0xdf, 0xdf, 0xdf, 0xcf, 0xcf, 0xcf,
    /* U+004F "O" (9x11) */
    0x1e, 0x3f, 0x9c, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f, 0xc7, 0x73, 0xbf, 0x87,
    0x80,
    /* U+0050 "P" (8x11) */
    0xfe, 0xff, 0xe7, 0xe7, 0xe7, 0xff, 0xfe, 0xe0, 0xe0, 0xe0, 0xe0,
    /* U+0051 "Q" (9x14) */
    0x1e, 0x3f, 0x9c, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f, 0xc7, 0x73, 0xbf, 0x8f,
    0x81, 0x80, 0xf8, 0x7c,
    /* U+0052 "R" (8x11) */
    0xfe, 0xff, 0xe7, 0xe7, 0xe7, 0xff, 0xfe, 0xee, 0xee, 0xe7, 0xe7,
    /* U+0053 "S" (8x11) */
    0x3e, 0xff, 0xe2, 0xe0, 0xf8, 0x7e, 0x1f, 0x07, 0xc7, 0xfe, 0x7c,
    /* U+0054 "T" (9x11) */
    0xff, 0xff, 0xc7, 0x03, 0x81, 0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07,
    0x00,
    /* U+0055 "U" (8x11) */
    0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xe7, 0xe7, 0xfe, 0x7c,
    /* U+0056 "V" (9x11) */
    0xe3, 0xf1, 0xdc, 0xee, 0x77, 0x33, 0xb8, 0xdc, 0x7e, 0x3e, 0x1f, 0x07,
    0x80,
    /* U+0057 "W" (10x11) */
    0xc1, 0xf0, 0x6c, 0xdb, 0xb6, 0xfd, 0xbf, 0x6f, 0x7b, 0xde, 0x77, 0x9d,
    0xe7, 0x78,
    /* U+0058 "X" (9x11) */
    0xf3, 0xb9, 0xdf, 0xc7, 0xe3, 0xe0, 0xf0, 0xf8, 0x7e, 0x77, 0x39, 0xf8,
    0xe0,
    /* U+0059 "Y" (9x11) */
    0xe3, 0xb9, 0xdc, 0xc6, 0xe3, 0xf0, 0xf0, 0x78, 0x38, 0x1c, 0x0e, 0x07,
    0x00,
    /* U+005A "Z" (8x11) */
    0xff, 0xff, 0x0f, 0x1e, 0x1c, 0x38, 0x78, 0x70, 0xe0, 0xff, 0xff,
    /* U+005B "[" (5x14) */
    0xff, 0xf1, 0x8c, 0x63, 0x18, 0xc6, 0x31, 0x8f, 0xfc,
    /* U+005C "" (7x14) */
    0xe0, 0xc1, 0xc3, 0x83, 0x07, 0x0e, 0x0c, 0x1c, 0x38, 0x30, 0x70, 0xe0,
    0xc0,
    /* U+005D "]" (6x14) */
    0xfd, 0xf0, 0xc3, 0x0c, 0x30, 0xc3, 0x0c, 0x30, 0xc3, 0x7f, 0xf0,
    /* U+005E "^" (8x7) */
    0x3c, 0x3c, 0x7c, 0x6e, 0xe6, 0xc7, 0xc3,
    /* U+005F "_" (8x2) */
    0xff, 0xff,
    /* U+0060 "`" (4x4) */
    0x6e, 0x73,
    /* U+0061 "a" (8x8) */
    0x7c, 0xfe, 0x46, 0x7f, 0xef, 0xc7, 0xff, 0x73,
    /* U+0062 "b" (8x12) */
    0xe0, 0xe0, 0xe0, 0xe0, 0xee, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0xee,
    /* U+0063 "c" (8x8) */
    0x3c, 0x7e, 0xe6, 0xe0, 0xe0, 0xe6, 0x7f, 0x3c,
    /* U+0064 "d" (9x12) */
    0x03, 0x81, 0xc0, 0xe0, 0x73, 0xbb, 0xfd, 0xcf, 0xc7, 0xe3, 0xb9, 0xdf,
    0xe7, 0x70,
    /* U+0065 "e" (8x8) */
    0x3c, 0xfe, 0xe7, 0xe7, 0xff, 0xe0, 0xfe, 0x3e,
    /* U+0066 "f" (8x12) */
    0x1f, 0x1f, 0x38, 0x38, 0xff, 0xff, 0x38, 0x38, 0x38, 0x38, 0xff, 0xff,
    /* U+0067 "g" (8x13) */
    0x03, 0x07, 0x7c, 0xfe, 0xe6, 0xfe, 0x7c, 0xc0, 0xfe, 0x7f, 0xc3, 0xff,
    0xfe,
    /* U+0068 "h" (8x12) */
    0xe0, 0xe0, 0xe0, 0xe0, 0xee, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7,
    /* U+0069 "i" (8x12) */
    0x1c, 0x1c, 0x1c, 0x00, 0xfc, 0xfc, 0x1c, 0x1c, 0x1c, 0x1c, 0xff, 0xff,
    /* U+006A "j" (6x15) */
    0x1c, 0x71, 0xc0, 0xff, 0xf1, 0xc7, 0x1c, 0x71, 0xc7, 0x1f, 0xff, 0x80,
    /* U+006B "k" (8x12) */
    0xe0, 0xe0, 0xe0, 0xe0, 0xe7, 0xee, 0xfc, 0xf8, 0xfc, 0xee, 0xee, 0xe7,
    /* U+006C "l" (8x12) */
    0xf8, 0xf8, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38, 0xff, 0xff,
    /* U+006D "m" (9x8) */
    0xdb, 0xff, 0xfb, 0x79, 0xbc, 0xde, 0x6f, 0x37, 0x9b,
    /* U+006E "n" (8x8) */
    0xee, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7,
    /* U+006F "o" (8x8) */
    0x7c, 0xfe, 0xe7, 0xc7, 0xc7, 0xe7, 0xfe, 0x7c,
    /* U+0070 "p" (8x11) */
    0xee, 0xff, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0xee, 0xe0, 0xe0, 0xe0,
    /* U+0071 "q" (9x11) */
    0x3b, 0xbf, 0xdc, 0xfc, 0x7e, 0x3b, 0x9d, 0xfe, 0x77, 0x03, 0x81, 0xc0,
    0xe0,
    /* U+0072 "r" (8x8) */
    0xfb, 0xff, 0x3c, 0x38, 0x38, 0x38, 0xfe, 0xfe,
    /* U+0073 "s" (8x8) */
    0x7e, 0xfe, 0xe0, 0xfe, 0x7e, 0x07, 0xfe, 0x7c,
    /* U+0074 "t" (7x11) */
    0x38, 0x70, 0xe7, 0xff, 0xe7, 0x0e, 0x1c, 0x38, 0x7c, 0x78,
    /* U+0075 "u" (8x8) */
    0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0x77,
    /* U+0076 "v" (9x8) */
    0xe3, 0xb9, 0xdc, 0xee, 0xe3, 0x71, 0xf0, 0x78, 0x3c,
    /* U+0077 "w" (10x8) */
    0xcd, 0xf7, 0x6d, 0xdb, 0xf6, 0xf7, 0x9d, 0xe7, 0x79, 0xde,
    /* U+0078 "x" (9x8) */
    0x73, 0xbb, 0x8f, 0x83, 0xc1, 0xe1, 0xf9, 0xdd, 0xc7,
    /* U+0079 "y" (9x11) */
    0xe3, 0xb9, 0xdc, 0xe6, 0xe3, 0xf1, 0xf0, 0x78, 0x38, 0x1c, 0x3e, 0x1e,
    0x00,
    /* U+007A "z" (8x8) */
    0xfe, 0xfe, 0x0e, 0x1c, 0x78, 0xf0, 0xff, 0xff,
    /* U+007B "{" (7x14) */
    0x1e, 0x7c, 0xc1, 0xc1, 0x83, 0x9e, 0x7c, 0x1c, 0x30, 0xe1, 0x83, 0xe3,
    0xc0,
    /* U+007C "|" (3x14) */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xc0,
    /* U+007D "}" (7x14) */
    0xf8, 0xf8, 0x70, 0xc3, 0x86, 0x0f, 0x8f, 0x30, 0x70, 0x60, 0xe7, 0xdf,
    0x00,
    /* U+007E "~" (8x4) */
    0x73, 0xfb, 0xdf, 0x8e,
    /* U+00B0 "" (6x6) */
    0x7b, 0xfc, 0xf3, 0xfd, 0xe0,
    /* U+00B1 "" (8x11) */
    0x18, 0x38, 0x38, 0xff, 0xff, 0x38, 0x38, 0x18, 0x00, 0xff, 0xff,
    /* U+00B2 "" (4x6) */
    0xef, 0x36, 0xcf,
    /* U+00B3 "" (4x6) */
    0xfb, 0x37, 0xbf,
    /* U+00B5 "" (8x11) */
    0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0xf7, 0xc0, 0xe0, 0xe0,
    /* U+00B7 "" (4x3) */
    0xef, 0xe0,
    /* U+00D7 "" (7x7) */
    0x47, 0xdd, 0xf1, 0xe7, 0xdd, 0xd1, 0x80,
    /* U+00F7 "" (8x10) */
    0x10, 0x38, 0x38, 0x00, 0xff, 0xff, 0x00, 0x38, 0x38, 0x10,
    /* U+0394 "" (8x11) */
    0x3c, 0x7c, 0x7c, 0x7e, 0x6e, 0xee, 0xe6, 0xe7, 0xe7, 0xff, 0xff,
    /* U+03A9 "" (9x11) */
    0x3e, 0x3f, 0x9c, 0xfc, 0x7e, 0x3f, 0x1f, 0x8e, 0xe7, 0x37, 0x7b, 0xfd,
    0xe0,
    /* U+03BC "" (8x11) */
    0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0xf7, 0xc0, 0xe0, 0xe0,
    /* U+2013 "" (8x2) */
    0xff, 0xff,
    /* U+2014 "" (10x2) */
    0xff, 0xff, 0xf0,
    /* U+2018 "" (4x5) */
    0x76, 0x6e, 0xe0,
    /* U+2019 "" (4x5) */
    0x7f, 0xee, 0xc0,
    /* U+201C "" (9x5) */
    0x39, 0x99, 0xdc, 0xce, 0xef, 0x70,
    /* U+201D "" (8x5) */
    0xf7, 0xe7, 0xee, 0xce, 0xcc,
    /* U+2022 "" (5x5) */
    0x7f, 0xff, 0xf7, 0x80,
    /* U+2026 "" (9x3) */
    0x6d, 0xf6, 0xdb, 0x60,
    /* U+2030 "" (9x11) */
    0x70, 0x6c, 0x36, 0x0e, 0x00, 0x73, 0xc0, 0x00, 0x77, 0x3f, 0x9f, 0xce,
    0xe0,
    /* U+2190 "" (9x8) */
    0x08, 0x0c, 0x0e, 0x0f, 0xff, 0xfb, 0xc0, 0xe0, 0x10,
    /* U+2191 "" (7x11) */
    0x10, 0x71, 0xf7, 0xfd, 0xa3, 0x06, 0x0c, 0x18, 0x30, 0x60,
    /* U+2192 "" (9x8) */
    0x04, 0x07, 0x01, 0xdf, 0xff, 0xf8, 0x38, 0x38, 0x08,
    /* U+2193 "" (7x11) */
    0x18, 0x30, 0x60, 0xc1, 0x83, 0x36, 0xff, 0x7c, 0x70, 0x40,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 154, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 154, .box_w = 4, .box_h = 11, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 6, .adv_w = 154, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 11, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 24, .adv_w = 154, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 39, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 65, .adv_w = 154, .box_w = 3, .box_h = 5, .ofs_x = 3, .ofs_y = 7},
    {.bitmap_index = 67, .adv_w = 154, .box_w = 5, .box_h = 14, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 76, .adv_w = 154, .box_w = 5, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 85, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 93, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 101, .adv_w = 154, .box_w = 4, .box_h = 5, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 104, .adv_w = 154, .box_w = 5, .box_h = 2, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 106, .adv_w = 154, .box_w = 4, .box_h = 3, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 108, .adv_w = 154, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 121, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 147, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 158, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 182, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 193, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 206, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 230, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 243, .adv_w = 154, .box_w = 4, .box_h = 8, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 247, .adv_w = 154, .box_w = 4, .box_h = 10, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 252, .adv_w = 154, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 261, .adv_w = 154, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 267, .adv_w = 154, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 276, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 154, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 302, .adv_w = 154, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 316, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 340, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 351, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 362, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 373, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 386, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 397, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 407, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 420, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 433, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 444, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 457, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 468, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 481, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 492, .adv_w = 154, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 508, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 519, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 530, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 543, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 554, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 567, .adv_w = 154, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 581, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 594, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 607, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 618, .adv_w = 154, .box_w = 5, .box_h = 14, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 627, .adv_w = 154, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 640, .adv_w = 154, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 651, .adv_w = 154, .box_w = 8, .box_h = 7, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 658, .adv_w = 154, .box_w = 8, .box_h = 2, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 660, .adv_w = 154, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 9},
    {.bitmap_index = 662, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 670, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 682, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 690, .adv_w = 154, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 704, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 712, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 724, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 737, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 749, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 761, .adv_w = 154, .box_w = 6, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 773, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 785, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 797, .adv_w = 154, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 806, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 814, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 822, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 833, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 846, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 854, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 862, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 872, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 880, .adv_w = 154, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 889, .adv_w = 154, .box_w = 10, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 899, .adv_w = 154, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 908, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 921, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 929, .adv_w = 154, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 942, .adv_w = 154, .box_w = 3, .box_h = 14, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 948, .adv_w = 154, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 961, .adv_w = 154, .box_w = 8, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 965, .adv_w = 154, .box_w = 6, .box_h = 6, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 970, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 981, .adv_w = 154, .box_w = 4, .box_h = 6, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 984, .adv_w = 154, .box_w = 4, .box_h = 6, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 987, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 998, .adv_w = 154, .box_w = 4, .box_h = 3, .ofs_x = 3, .ofs_y = 4},
    {.bitmap_index = 1000, .adv_w = 154, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 1007, .adv_w = 154, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1017, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1028, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1041, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1052, .adv_w = 154, .box_w = 8, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 1054, .adv_w = 154, .box_w = 10, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1057, .adv_w = 154, .box_w = 4, .box_h = 5, .ofs_x = 3, .ofs_y = 7},
    {.bitmap_index = 1060, .adv_w = 154, .box_w = 4, .box_h = 5, .ofs_x = 3, .ofs_y = 7},
    {.bitmap_index = 1063, .adv_w = 154, .box_w = 9, .box_h = 5, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 1069, .adv_w = 154, .box_w = 8, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1074, .adv_w = 154, .box_w = 5, .box_h = 5, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 1078, .adv_w = 154, .box_w = 9, .box_h = 3, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1082, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1095, .adv_w = 154, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1104, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1114, .adv_w = 154, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1123, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0}
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

const lv_font_t humid1_font_plex_mono_bold_16 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 22,
    .base_line = 5,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 11,
    .x_height = 8,
#endif
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = -2,
    .underline_thickness = 2,
#if LV_VERSION_CHECK(9, 3, 0) || (LVGL_VERSION_MAJOR == 9 && LVGL_VERSION_MINOR >= 3) || LVGL_VERSION_MAJOR > 9
    .static_bitmap = 0,
#endif
    .dsc = &font_dsc,
#if LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_font_plex_sans_bold_16,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_PLEX_MONO_BOLD_16 */
