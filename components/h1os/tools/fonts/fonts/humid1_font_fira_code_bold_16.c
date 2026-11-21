/*******************************************************************************
 * Font: humid1_font_fira_code_bold_16 (fira_code bold)
 * Size: 16 px @ 188.15 DPI (1-bit Monochrome Embedded Display)
 * Bpp: 1 (Uncompressed Bilevel Monochrome)
 * Conversion Pipeline: otsu-adaptive (epd-font v1.0.23)
 * LVGL Fallback Pointer: &humid1_icon_fa7_solid_16 (LVGL >= 9.6.0 Ready)
 * License: MIT AND OFL-1.1
 ******************************************************************************/

#ifdef __has_include
    #if __has_include("lvgl.h")
        #ifndef LV_LVGL_H_INCLUDE_SIMPLE
            #define LV_LVGL_H_INCLUDE_SIMPLE
        #endif
    #endif
#endif

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif

#ifndef HUMID1_FONT_FIRA_CODE_BOLD_16
#define HUMID1_FONT_FIRA_CODE_BOLD_16 1
#endif

#if HUMID1_FONT_FIRA_CODE_BOLD_16

extern const lv_font_t humid1_icon_fa7_solid_16;

/*-----------------
 *    BITMAPS
 *----------------*/

static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " (0x0) */
    /* U+0021 "!" (3x11) */
    0xed, 0xb6, 0xd8, 0x5d, 0x80,
    /* U+0022 "" (5x5) */
    0xde, 0xf7, 0xb4, 0x80,
    /* U+0023 "#" (8x11) */
    0x36, 0x76, 0xff, 0xff, 0x66, 0x66, 0x6e, 0xfe, 0xfe, 0xec, 0xcc,
    /* U+0024 "$" (8x16) */
    0x10, 0x18, 0x18, 0x7e, 0xfe, 0xd8, 0xf8, 0x78, 0x3e, 0x1f, 0x1f, 0x1f,
    0xfe, 0x7e, 0x18, 0x18,
    /* U+0025 "%" (10x11) */
    0x73, 0x36, 0xcd, 0xe3, 0xd8, 0x6c, 0x03, 0x01, 0xb8, 0x7e, 0x36, 0xcd,
    0xa2, 0x38,
    /* U+0026 "&" (8x11) */
    0x7c, 0xec, 0xe0, 0xe0, 0x7f, 0x7f, 0xc6, 0xc6, 0xc6, 0xfe, 0x7c,
    /* U+0027 "'" (2x5) */
    0xff, 0x80,
    /* U+0028 "(" (5x15) */
    0x39, 0x9d, 0xce, 0x63, 0x18, 0xc6, 0x39, 0xc7, 0x1c, 0x60,
    /* U+0029 ")" (5x15) */
    0xc7, 0x1c, 0xe3, 0x9c, 0xe7, 0x39, 0xce, 0xe7, 0x73, 0x00,
    /* U+002A "" (8x8) */
    0x18, 0x98, 0xff, 0xff, 0x3c, 0x7c, 0x66, 0x04,
    /* U+002B "+" (8x8) */
    0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18,
    /* U+002C "," (4x6) */
    0xef, 0xe6, 0xec,
    /* U+002D "-" (7x2) */
    0xff, 0xfc,
    /* U+002E "." (4x3) */
    0xef, 0xe0,
    /* U+002F "/" (8x14) */
    0x02, 0x07, 0x06, 0x06, 0x0c, 0x0c, 0x18, 0x18, 0x30, 0x30, 0x60, 0x60,
    0xc0, 0xc0,
    /* U+0030 "0" (8x11) */
    0x7c, 0x7e, 0xe6, 0xcf, 0xcf, 0xdf, 0xd7, 0xf7, 0xe6, 0x7e, 0x7c,
    /* U+0031 "1" (8x11) */
    0x3c, 0x7c, 0xfc, 0x5c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x7f, 0x7f,
    /* U+0032 "2" (7x11) */
    0x7d, 0xfc, 0x18, 0x30, 0xe3, 0x86, 0x18, 0x61, 0xff, 0xf8,
    /* U+0033 "3" (7x11) */
    0xfd, 0xfc, 0x18, 0x73, 0xc7, 0x83, 0x83, 0x07, 0xff, 0xf0,
    /* U+0034 "4" (8x11) */
    0x38, 0x38, 0x30, 0x70, 0x66, 0xee, 0xee, 0xff, 0xff, 0x0e, 0x0e,
    /* U+0035 "5" (8x11) */
    0xfe, 0xfe, 0xe0, 0xe0, 0xfe, 0xfe, 0x07, 0x07, 0x07, 0xfe, 0x7c,
    /* U+0036 "6" (8x11) */
    0x3e, 0x74, 0xe0, 0xe0, 0xfe, 0xe7, 0xc7, 0xe7, 0xe7, 0x7e, 0x3c,
    /* U+0037 "7" (8x11) */
    0xff, 0xff, 0x06, 0x0e, 0x0c, 0x1c, 0x18, 0x38, 0x30, 0x70, 0x70,
    /* U+0038 "8" (8x11) */
    0x7e, 0xee, 0xe6, 0xe6, 0x7c, 0x7e, 0xef, 0xc7, 0xc7, 0xff, 0x7e,
    /* U+0039 "9" (8x11) */
    0x7c, 0xfe, 0xc7, 0xc7, 0xc7, 0xff, 0x7f, 0x0e, 0x1e, 0x7c, 0x70,
    /* U+003A ":" (3x9) */
    0x5f, 0xb0, 0x1f, 0xe0,
    /* U+003B ";" (3x12) */
    0x5f, 0xb0, 0x3f, 0xef, 0x60,
    /* U+003C "<" (7x8) */
    0x0e, 0x3d, 0xe7, 0x0e, 0x0f, 0x07, 0x87,
    /* U+003D "=" (7x6) */
    0xff, 0xfc, 0x00, 0x0f, 0xff, 0xc0,
    /* U+003E ">" (8x10) */
    0x40, 0xe0, 0x78, 0x1e, 0x0f, 0x0f, 0x1e, 0x78, 0xe0, 0x40,
    /* U+003F "?" (7x11) */
    0x7f, 0xfc, 0x18, 0x71, 0xc7, 0x0c, 0x00, 0x10, 0x70, 0xe0,
    /* U+0040 "@" (10x12) */
    0x7f, 0x38, 0xe0, 0x18, 0x06, 0x3c, 0x9b, 0x3e, 0xcf, 0xb3, 0xec, 0xfb,
    0x27, 0xf8, 0xde,
    /* U+0041 "A" (10x11) */
    0x1e, 0x07, 0x83, 0xe0, 0xdc, 0x37, 0x1c, 0xc7, 0x31, 0xfe, 0x7f, 0xb8,
    0x6e, 0x1c,
    /* U+0042 "B" (8x11) */
    0xfc, 0xfe, 0xe7, 0xe7, 0xfe, 0xfe, 0xe7, 0xe7, 0xe7, 0xff, 0xfe,
    /* U+0043 "C" (8x11) */
    0x3f, 0x7f, 0xe0, 0xe0, 0xc0, 0xc0, 0xc0, 0xe0, 0xe0, 0x7f, 0x3e,
    /* U+0044 "D" (8x11) */
    0xfc, 0xfe, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xfe, 0xfc,
    /* U+0045 "E" (8x11) */
    0xff, 0xff, 0xe0, 0xe0, 0xfe, 0xfe, 0xe0, 0xe0, 0xe0, 0xff, 0xff,
    /* U+0046 "F" (7x11) */
    0xff, 0xff, 0x06, 0x0e, 0x1f, 0xbf, 0x60, 0xc1, 0x83, 0x00,
    /* U+0047 "G" (9x11) */
    0x1f, 0x1f, 0xdc, 0x0c, 0x0e, 0x07, 0x3f, 0x8e, 0xc3, 0x71, 0xbf, 0xcf,
    0xc0,
    /* U+0048 "H" (8x11) */
    0xc7, 0xc7, 0xc7, 0xc7, 0xff, 0xff, 0xe7, 0xc7, 0xc7, 0xc7, 0xc7,
    /* U+0049 "I" (7x11) */
    0xff, 0xfc, 0xe1, 0xc3, 0x87, 0x0e, 0x1c, 0x39, 0xff, 0xf8,
    /* U+004A "J" (8x11) */
    0x7f, 0x7f, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x0e, 0xfe, 0xfc,
    /* U+004B "K" (9x11) */
    0xe7, 0x73, 0xbb, 0x9f, 0x8f, 0xc7, 0xe3, 0xf1, 0xdc, 0xee, 0x73, 0xb9,
    0xe0,
    /* U+004C "L" (8x11) */
    0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xff, 0xff,
    /* U+004D "M" (9x11) */
    0x73, 0xb9, 0xdc, 0xee, 0xf7, 0x7b, 0xff, 0xf7, 0xfb, 0xed, 0xf0, 0xf8,
    0x60,
    /* U+004E "N" (8x11) */
    0xe7, 0xf7, 0xf7, 0xf7, 0xff, 0xdf, 0xdf, 0xdf, 0xcf, 0xcf, 0xcf,
    /* U+004F "O" (9x11) */
    0x3f, 0x3f, 0x9c, 0xfc, 0x7e, 0x3f, 0x1f, 0x8f, 0xc7, 0x73, 0xbf, 0x8f,
    0x80,
    /* U+0050 "P" (8x11) */
    0xfe, 0xff, 0xe7, 0xe7, 0xe7, 0xff, 0xfe, 0xe0, 0xe0, 0xe0, 0xe0,
    /* U+0051 "Q" (10x14) */
    0x3e, 0x1f, 0xc7, 0x39, 0x8e, 0x63, 0xb8, 0xe6, 0x39, 0x8e, 0x73, 0x9f,
    0xc3, 0xf0, 0x0e, 0x01, 0xc0, 0x20,
    /* U+0052 "R" (8x11) */
    0xfe, 0xff, 0xe7, 0xe7, 0xe7, 0xfe, 0xfc, 0xee, 0xee, 0xe7, 0xe7,
    /* U+0053 "S" (9x11) */
    0x3f, 0x3f, 0xdc, 0x0e, 0x07, 0xe1, 0xf8, 0x1e, 0x07, 0x43, 0xff, 0xdf,
    0xc0,
    /* U+0054 "T" (9x11) */
    0xff, 0xff, 0xc7, 0x03, 0x81, 0xc0, 0xe0, 0x70, 0x38, 0x1c, 0x0e, 0x07,
    0x00,
    /* U+0055 "U" (8x11) */
    0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xc7, 0xe7, 0xfe, 0x7c,
    /* U+0056 "V" (9x11) */
    0xe1, 0xf0, 0xd8, 0xee, 0x77, 0x31, 0x98, 0xdc, 0x7c, 0x3e, 0x0f, 0x07,
    0x80,
    /* U+0057 "W" (10x11) */
    0xc1, 0xf3, 0x6e, 0xdb, 0xf6, 0xfd, 0x9f, 0x67, 0x79, 0xde, 0x77, 0x9d,
    0xe7, 0x30,
    /* U+0058 "X" (9x11) */
    0x63, 0xb9, 0x8d, 0xc7, 0xc1, 0xe0, 0xf0, 0xf8, 0x6e, 0x73, 0x39, 0xf8,
    0xe0,
    /* U+0059 "Y" (9x11) */
    0xe1, 0xb1, 0xdc, 0xc6, 0xe3, 0xe0, 0xf0, 0x70, 0x38, 0x1c, 0x0e, 0x07,
    0x00,
    /* U+005A "Z" (8x11) */
    0xff, 0xff, 0x0e, 0x0e, 0x1c, 0x38, 0x30, 0x70, 0xe0, 0xff, 0xff,
    /* U+005B "[" (5x15) */
    0xff, 0xf9, 0xce, 0x73, 0x9c, 0xe7, 0x39, 0xce, 0x7d, 0xe0,
    /* U+005C "" (8x15) */
    0xc0, 0xc0, 0xe0, 0x60, 0x70, 0x30, 0x38, 0x18, 0x1c, 0x0c, 0x0e, 0x06,
    0x06, 0x03, 0x02,
    /* U+005D "]" (5x15) */
    0xff, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31, 0xff, 0xe0,
    /* U+005E "^" (8x6) */
    0x18, 0x3c, 0x7c, 0x6e, 0xe6, 0xc3,
    /* U+005F "_" (8x2) */
    0xff, 0xff,
    /* U+0060 "`" (4x3) */
    0xcf, 0x30,
    /* U+0061 "a" (8x9) */
    0x7c, 0xfe, 0x0e, 0x06, 0x7e, 0xe6, 0xc6, 0xff, 0xff,
    /* U+0062 "b" (8x12) */
    0xe0, 0xe0, 0xe0, 0xec, 0xfe, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xfe, 0xfe,
    /* U+0063 "c" (7x9) */
    0x1c, 0xfd, 0xcf, 0x0e, 0x1c, 0x38, 0x3f, 0x3e,
    /* U+0064 "d" (8x12) */
    0x07, 0x07, 0x07, 0x37, 0xff, 0xe7, 0xc7, 0xc7, 0xc7, 0xe7, 0xff, 0x7f,
    /* U+0065 "e" (8x9) */
    0x3c, 0x7e, 0xe7, 0xc7, 0xff, 0xfe, 0xe0, 0xfe, 0x7e,
    /* U+0066 "f" (8x12) */
    0x1f, 0x3f, 0x38, 0x38, 0xfe, 0xfe, 0x38, 0x38, 0x38, 0x38, 0x38, 0x38,
    /* U+0067 "g" (8x14) */
    0x01, 0x3f, 0xfe, 0xe6, 0xe6, 0xee, 0x7e, 0x60, 0xfc, 0x7f, 0x07, 0xc7,
    0xfe, 0x38,
    /* U+0068 "h" (7x12) */
    0xe1, 0xc3, 0x87, 0x6f, 0xfc, 0xf9, 0xf3, 0xe7, 0xcf, 0x9f, 0x30,
    /* U+0069 "i" (8x13) */
    0x18, 0x38, 0x18, 0x00, 0x78, 0xf8, 0x18, 0x18, 0x18, 0x18, 0x18, 0xfe,
    0xff,
    /* U+006A "j" (7x16) */
    0x0c, 0x38, 0x30, 0x07, 0xcf, 0xc3, 0x87, 0x0e, 0x1c, 0x38, 0x70, 0xc3,
    0x9e, 0x78,
    /* U+006B "k" (8x12) */
    0xe0, 0xe0, 0xe0, 0xe3, 0xe7, 0xee, 0xfc, 0xfc, 0xfc, 0xee, 0xe7, 0xe7,
    /* U+006C "l" (7x12) */
    0xf1, 0xe0, 0xc1, 0x83, 0x06, 0x0c, 0x18, 0x30, 0x70, 0xf8, 0xf0,
    /* U+006D "m" (9x9) */
    0x5b, 0x7f, 0xfb, 0x7d, 0xbe, 0xdf, 0x6f, 0xb7, 0xdb, 0xed, 0x80,
    /* U+006E "n" (7x9) */
    0x4d, 0xff, 0x9f, 0x3e, 0x7c, 0xf9, 0xf3, 0xe6,
    /* U+006F "o" (8x9) */
    0x38, 0x7e, 0xe6, 0xc7, 0xc7, 0xc7, 0xe7, 0xfe, 0x7c,
    /* U+0070 "p" (8x12) */
    0x4c, 0xfe, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xfe, 0xfe, 0xe0, 0xe0, 0xe0,
    /* U+0071 "q" (8x13) */
    0x32, 0x7f, 0xe7, 0xc7, 0xc7, 0xc7, 0xe7, 0xff, 0x7f, 0x07, 0x07, 0x07,
    0x02,
    /* U+0072 "r" (8x9) */
    0x67, 0xff, 0x7f, 0x7b, 0x70, 0x70, 0x70, 0xf8, 0xfc,
    /* U+0073 "s" (8x9) */
    0x3c, 0x7e, 0xe0, 0xf0, 0x7e, 0x1e, 0x07, 0xfe, 0xfc,
    /* U+0074 "t" (7x11) */
    0x10, 0x63, 0xf7, 0xf3, 0x06, 0x0c, 0x18, 0x30, 0x7c, 0x78,
    /* U+0075 "u" (8x9) */
    0xc6, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xff, 0x7f,
    /* U+0076 "v" (8x8) */
    0xc7, 0xe6, 0xe6, 0x66, 0x6c, 0x3c, 0x3c, 0x38,
    /* U+0077 "w" (9x8) */
    0xc1, 0xf6, 0xdb, 0x6f, 0xb7, 0x7b, 0xbd, 0xde, 0xe6,
    /* U+0078 "x" (8x8) */
    0xe6, 0x6e, 0x3c, 0x38, 0x3c, 0x6e, 0xe6, 0xc7,
    /* U+0079 "y" (8x13) */
    0xc3, 0xc7, 0xe7, 0xe6, 0x6e, 0x6e, 0x7c, 0x3c, 0x3c, 0x18, 0x78, 0xf0,
    0x40,
    /* U+007A "z" (7x8) */
    0x7e, 0x1c, 0x70, 0xc3, 0x0e, 0x3f, 0xff,
    /* U+007B "{" (6x15) */
    0x3c, 0xe3, 0x0c, 0x30, 0xcf, 0x38, 0xf0, 0xc3, 0x0c, 0x30, 0xe3, 0xc0,
    /* U+007C "|" (2x19) */
    0xff, 0xff, 0xff, 0xff, 0xfc,
    /* U+007D "}" (6x15) */
    0xe1, 0xc3, 0x1c, 0x71, 0xc3, 0xc7, 0x39, 0xc7, 0x0c, 0x31, 0xce, 0x00,
    /* U+007E "~" (8x4) */
    0x60, 0xfb, 0x9e, 0x04,
    /* U+00B0 "" (6x5) */
    0x7b, 0xfc, 0xf3, 0x78,
    /* U+00B1 "" (7x9) */
    0x18, 0x30, 0xe7, 0xf3, 0x83, 0x00, 0x7f, 0xfe,
    /* U+00B2 "" (5x5) */
    0x7a, 0xc6, 0xef, 0x80,
    /* U+00B3 "" (4x5) */
    0xf3, 0x73, 0xf0,
    /* U+00B5 "" (7x11) */
    0xe7, 0xcf, 0x9f, 0x3e, 0x7c, 0xff, 0xff, 0xc1, 0x83, 0x00,
    /* U+00B7 "" (4x3) */
    0xef, 0xe0,
    /* U+00D7 "" (6x6) */
    0xcb, 0xf7, 0x9e, 0xff, 0x30,
    /* U+00F7 "" (7x10) */
    0x18, 0x70, 0x60, 0x0f, 0xff, 0xc0, 0x0c, 0x38, 0x30,
    /* U+0394 "" (10x11) */
    0x1e, 0x07, 0x83, 0xe0, 0xdc, 0x37, 0x1c, 0xc7, 0x31, 0x8e, 0x63, 0xbf,
    0xef, 0xfc,
    /* U+03A9 "" (9x11) */
    0x3e, 0x3f, 0x98, 0xfc, 0x7e, 0x1f, 0x0d, 0x8e, 0xc7, 0x33, 0x3b, 0xdd,
    0xe0,
    /* U+03B1 "" (8x9) */
    0x30, 0x7f, 0xee, 0xc6, 0xc6, 0xc6, 0xce, 0xff, 0x7b,
    /* U+03B2 "" (8x16) */
    0x7c, 0xfe, 0xc6, 0xc6, 0xce, 0xdc, 0xde, 0xc7, 0xc7, 0xc7, 0xff, 0xfe,
    0xc0, 0xc0, 0xc0, 0x80,
    /* U+03B3 "" (9x13) */
    0x21, 0x71, 0xdc, 0xe6, 0x63, 0x70, 0xf0, 0x78, 0x3c, 0x1c, 0x0e, 0x07,
    0x03, 0x80, 0x80,
    /* U+03B4 "" (8x12) */
    0x3e, 0x7e, 0x60, 0x70, 0x3c, 0x6e, 0xe7, 0xc7, 0xc7, 0xe7, 0xfe, 0x7c,
    /* U+03B5 "" (8x9) */
    0x3c, 0x7e, 0xe0, 0x60, 0x7c, 0xf0, 0xe0, 0xff, 0x7f,
    /* U+03B8 "" (8x12) */
    0x3c, 0x7e, 0xe6, 0xc7, 0xc7, 0xff, 0xff, 0xc7, 0xc7, 0xe6, 0x7e, 0x3c,
    /* U+03BB "" (8x12) */
    0x60, 0x70, 0x38, 0x18, 0x3c, 0x3c, 0x6c, 0x6c, 0x6e, 0xe6, 0xc7, 0xc3,
    /* U+03BC "" (7x11) */
    0xe7, 0xcf, 0x9f, 0x3e, 0x7c, 0xff, 0xff, 0xc1, 0x83, 0x00,
    /* U+03C0 "" (9x8) */
    0xff, 0xbb, 0x8c, 0xc6, 0x63, 0x31, 0x98, 0xce, 0x66,
    /* U+03C3 "" (8x9) */
    0x1f, 0x7f, 0xe6, 0xc7, 0xc7, 0xc7, 0xe7, 0xfe, 0x7c,
    /* U+03C4 "" (9x8) */
    0xff, 0x8e, 0x07, 0x03, 0x81, 0xc0, 0xe0, 0x7c, 0x1e,
    /* U+03C6 "" (9x13) */
    0x67, 0x37, 0xdb, 0x7d, 0xbc, 0xde, 0x6f, 0xb6, 0xff, 0x3f, 0x06, 0x03,
    0x01, 0x80, 0x80,
    /* U+03C9 "" (9x9) */
    0x61, 0x30, 0xf8, 0x7d, 0xbe, 0xdf, 0x6f, 0xb7, 0xff, 0x77, 0x80,
    /* U+2013 "" (9x2) */
    0xff, 0xff, 0xc0,
    /* U+2014 "" (10x2) */
    0xff, 0xff, 0xf0,
    /* U+2018 "" (3x6) */
    0x2d, 0xfe, 0xc0,
    /* U+2019 "" (3x6) */
    0x7f, 0xbd, 0x80,
    /* U+201C "" (7x6) */
    0x22, 0xcd, 0x9b, 0x7e, 0xec, 0xc0,
    /* U+201D "" (7x6) */
    0x67, 0xfd, 0xbb, 0x36, 0xc9, 0x80,
    /* U+2022 "" (4x5) */
    0x6f, 0xff, 0x60,
    /* U+2026 "" (9x2) */
    0xed, 0xf6, 0xc0,
    /* U+2030 "" (8x11) */
    0xe0, 0xb0, 0xb0, 0xe7, 0x3c, 0xe0, 0x00, 0xe7, 0xbd, 0xbd, 0xe7,
    /* U+2190 "" (10x10) */
    0x0c, 0x07, 0x03, 0x81, 0xc0, 0xff, 0xdf, 0xe3, 0x00, 0xe0, 0x1c, 0x03,
    0x00,
    /* U+2191 "" (10x11) */
    0x08, 0x07, 0x03, 0xe1, 0xfe, 0xed, 0xd3, 0x20, 0xc0, 0x30, 0x0c, 0x03,
    0x00, 0xc0,
    /* U+2192 "" (9x10) */
    0x1c, 0x07, 0x01, 0xc0, 0xff, 0xff, 0xfc, 0x1c, 0x1c, 0x1c, 0x04, 0x00,
    /* U+2193 "" (10x11) */
    0x0c, 0x03, 0x00, 0xc0, 0x30, 0x0c, 0x13, 0x2e, 0xdd, 0xfe, 0x3f, 0x07,
    0x80, 0xc0,
};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 154, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 154, .box_w = 3, .box_h = 11, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 5, .adv_w = 154, .box_w = 5, .box_h = 5, .ofs_x = 2, .ofs_y = 7},
    {.bitmap_index = 9, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 20, .adv_w = 154, .box_w = 8, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 36, .adv_w = 154, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 50, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 61, .adv_w = 154, .box_w = 2, .box_h = 5, .ofs_x = 4, .ofs_y = 7},
    {.bitmap_index = 63, .adv_w = 154, .box_w = 5, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 73, .adv_w = 154, .box_w = 5, .box_h = 15, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 83, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 91, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 99, .adv_w = 154, .box_w = 4, .box_h = 6, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 102, .adv_w = 154, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 104, .adv_w = 154, .box_w = 4, .box_h = 3, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 106, .adv_w = 154, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 120, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 131, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 152, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 162, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 173, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 184, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 195, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 206, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 154, .box_w = 3, .box_h = 9, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 232, .adv_w = 154, .box_w = 3, .box_h = 12, .ofs_x = 3, .ofs_y = -3},
    {.bitmap_index = 237, .adv_w = 154, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 244, .adv_w = 154, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 250, .adv_w = 154, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 260, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 270, .adv_w = 154, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 285, .adv_w = 154, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 299, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 310, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 321, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 332, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 343, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 353, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 366, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 377, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 387, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 398, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 411, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 422, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 435, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 446, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 459, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 470, .adv_w = 154, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 488, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 499, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 512, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 525, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 536, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 549, .adv_w = 154, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 563, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 576, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 589, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 600, .adv_w = 154, .box_w = 5, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 610, .adv_w = 154, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 625, .adv_w = 154, .box_w = 5, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 635, .adv_w = 154, .box_w = 8, .box_h = 6, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 641, .adv_w = 154, .box_w = 8, .box_h = 2, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 643, .adv_w = 154, .box_w = 4, .box_h = 3, .ofs_x = 3, .ofs_y = 10},
    {.bitmap_index = 645, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 654, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 666, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 674, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 686, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 695, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 707, .adv_w = 154, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 721, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 732, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 745, .adv_w = 154, .box_w = 7, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 759, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 771, .adv_w = 154, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 782, .adv_w = 154, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 793, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 801, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 810, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 822, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 835, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 844, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 853, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 863, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 872, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 880, .adv_w = 154, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 889, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 897, .adv_w = 154, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 910, .adv_w = 154, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 917, .adv_w = 154, .box_w = 6, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 929, .adv_w = 154, .box_w = 2, .box_h = 19, .ofs_x = 4, .ofs_y = -5},
    {.bitmap_index = 934, .adv_w = 154, .box_w = 6, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 946, .adv_w = 154, .box_w = 8, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 950, .adv_w = 154, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 954, .adv_w = 154, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 962, .adv_w = 154, .box_w = 5, .box_h = 5, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 966, .adv_w = 154, .box_w = 4, .box_h = 5, .ofs_x = 3, .ofs_y = 5},
    {.bitmap_index = 969, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 979, .adv_w = 154, .box_w = 4, .box_h = 3, .ofs_x = 3, .ofs_y = 4},
    {.bitmap_index = 981, .adv_w = 154, .box_w = 6, .box_h = 6, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 986, .adv_w = 154, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 995, .adv_w = 154, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1009, .adv_w = 154, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1022, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1031, .adv_w = 154, .box_w = 8, .box_h = 16, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1047, .adv_w = 154, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1062, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1074, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1083, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1095, .adv_w = 154, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1107, .adv_w = 154, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1117, .adv_w = 154, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1126, .adv_w = 154, .box_w = 8, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1135, .adv_w = 154, .box_w = 9, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1144, .adv_w = 154, .box_w = 9, .box_h = 13, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1159, .adv_w = 154, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1170, .adv_w = 154, .box_w = 9, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1173, .adv_w = 154, .box_w = 10, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1176, .adv_w = 154, .box_w = 3, .box_h = 6, .ofs_x = 3, .ofs_y = 7},
    {.bitmap_index = 1179, .adv_w = 154, .box_w = 3, .box_h = 6, .ofs_x = 3, .ofs_y = 7},
    {.bitmap_index = 1182, .adv_w = 154, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1188, .adv_w = 154, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 1194, .adv_w = 154, .box_w = 4, .box_h = 5, .ofs_x = 3, .ofs_y = 3},
    {.bitmap_index = 1197, .adv_w = 154, .box_w = 9, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1200, .adv_w = 154, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1211, .adv_w = 154, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1224, .adv_w = 154, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1238, .adv_w = 154, .box_w = 9, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1250, .adv_w = 154, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0}
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

const lv_font_t humid1_font_fira_code_bold_16 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,
    .line_height = 22,
    .base_line = 6,
#if LV_VERSION_CHECK(9, 6, 0) || LVGL_VERSION_MAJOR >= 10
    .cap_height = 11,
    .x_height = 8,
#endif
    .subpx = LV_FONT_SUBPX_NONE,
    .underline_position = -1,
    .underline_thickness = 1,
#if LV_VERSION_CHECK(9, 3, 0) || (LVGL_VERSION_MAJOR == 9 && LVGL_VERSION_MINOR >= 3) || LVGL_VERSION_MAJOR > 9
    .static_bitmap = 0,
#endif
    .dsc = &font_dsc,
#if LVGL_VERSION_MAJOR >= 9
    .fallback = &humid1_icon_fa7_solid_16,
#endif
    .user_data = NULL,
};

#endif /* #if HUMID1_FONT_FIRA_CODE_BOLD_16 */
