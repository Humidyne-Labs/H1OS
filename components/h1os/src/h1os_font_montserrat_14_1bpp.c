/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: --size 14 --bpp 1 --font C:\Users\Matt\Documents\GitHub\assets\tool_harness\lvgl__lvgl-v9.6.0\lvgl\tests\src\test_files\fonts\Montserrat-Bold.ttf -r 0x20-0x7F,176,8226 --font C:\Users\Matt\Documents\GitHub\assets\tool_harness\lvgl-9.6.0\scripts\generators\built_in_font\FontAwesome5-Solid+Brands+Regular.woff -r 61441,61448,61451,61452,61453,61457,61459,61461,61465,61468,61473,61478,61479,61480,61502,61507,61512,61515,61516,61517,61521,61522,61523,61524,61543,61544,61550,61552,61553,61556,61559,61560,61561,61563,61587,61589,61636,61637,61639,61641,61664,61671,61674,61683,61724,61732,61787,61931,62016,62017,62018,62019,62020,62087,62099,62212,62189,62810,63426,63650 --format lvgl --lv-font-name bsp_font_montserrat_14_1bpp -o components\esp32-s3_bsp\src\bsp_font_montserrat_14_1bpp.c --no-compress --no-prefilter --force-fast-kern-format
 ******************************************************************************/

#include "lvgl.h"


#ifndef BSP_FONT_MONTSERRAT_14_1BPP
#define BSP_FONT_MONTSERRAT_14_1BPP 1
#endif

#if BSP_FONT_MONTSERRAT_14_1BPP

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xf0, 0xf0,

    /* U+0022 "\"" */
    0xde, 0xf7, 0xb0,

    /* U+0023 "#" */
    0x33, 0x19, 0xbf, 0xff, 0xf3, 0x21, 0x33, 0xff,
    0xff, 0x66, 0x33, 0x0,

    /* U+0024 "$" */
    0x18, 0x18, 0x3e, 0xfe, 0xda, 0xd8, 0x78, 0x1e,
    0x1b, 0x9b, 0xff, 0x7c, 0x18, 0x18,

    /* U+0025 "%" */
    0x70, 0x8d, 0x98, 0xd9, 0xd, 0xa0, 0x76, 0x0,
    0x5e, 0xb, 0x30, 0xb3, 0x13, 0x32, 0x1e,

    /* U+0026 "&" */
    0x3c, 0x3f, 0x19, 0x8c, 0x83, 0x83, 0xef, 0x3f,
    0x8e, 0xff, 0xbe, 0x40,

    /* U+0027 "'" */
    0xff,

    /* U+0028 "(" */
    0x66, 0x6c, 0xcc, 0xcc, 0xcc, 0xc6, 0x66,

    /* U+0029 ")" */
    0x66, 0x63, 0x33, 0x33, 0x33, 0x36, 0x66,

    /* U+002A "*" */
    0x33, 0xff, 0xff, 0xfc, 0xc0,

    /* U+002B "+" */
    0x18, 0x30, 0x67, 0xff, 0xe3, 0x6, 0xc,

    /* U+002C "," */
    0xff, 0x80,

    /* U+002D "-" */
    0xff,

    /* U+002E "." */
    0xfc,

    /* U+002F "/" */
    0xc, 0x31, 0x86, 0x18, 0xc3, 0xc, 0x61, 0x86,
    0x30, 0xc3, 0x0,

    /* U+0030 "0" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xc3, 0xc3, 0xe7,
    0x7e, 0x3c,

    /* U+0031 "1" */
    0xff, 0x33, 0x33, 0x33, 0x33,

    /* U+0032 "2" */
    0x7d, 0xfd, 0x18, 0x30, 0xe3, 0x8e, 0x38, 0xff,
    0xfc,

    /* U+0033 "3" */
    0xff, 0xfc, 0x30, 0xc3, 0xc7, 0xc1, 0xc3, 0xfe,
    0xf0,

    /* U+0034 "4" */
    0x6, 0x3, 0x1, 0xc0, 0x60, 0x33, 0x1c, 0xcf,
    0xff, 0xff, 0x3, 0x0, 0xc0,

    /* U+0035 "5" */
    0x3e, 0x3e, 0x70, 0x7c, 0x7f, 0x3, 0x3, 0x43,
    0x7e, 0x3c,

    /* U+0036 "6" */
    0x1e, 0x7e, 0x60, 0xdc, 0xfe, 0xc3, 0xc3, 0xc3,
    0x7e, 0x3c,

    /* U+0037 "7" */
    0xff, 0xff, 0xc7, 0xc6, 0xe, 0xc, 0x1c, 0x18,
    0x38, 0x30,

    /* U+0038 "8" */
    0x3c, 0xff, 0xc3, 0xc3, 0xff, 0xff, 0xc3, 0xc3,
    0xff, 0x3c,

    /* U+0039 "9" */
    0x3c, 0xfe, 0xc3, 0xc3, 0xff, 0x7b, 0x3, 0x6,
    0x7e, 0x78,

    /* U+003A ":" */
    0xfc, 0x3f,

    /* U+003B ";" */
    0xfc, 0x3f, 0xe0,

    /* U+003C "<" */
    0x2, 0x3d, 0xe7, 0xf, 0x7, 0x83, 0x80,

    /* U+003D "=" */
    0xff, 0xfc, 0x0, 0xf, 0xff, 0xc0,

    /* U+003E ">" */
    0x81, 0xc1, 0xf0, 0x71, 0xff, 0x30, 0x0,

    /* U+003F "?" */
    0x3e, 0x7f, 0x63, 0x3, 0x7, 0xe, 0x1c, 0x0,
    0x1c, 0x1c,

    /* U+0040 "@" */
    0xf, 0xc0, 0xff, 0xc7, 0x83, 0x9b, 0xf6, 0xdf,
    0xcf, 0x63, 0x3d, 0x8c, 0xf6, 0x33, 0xcf, 0xf9,
    0xbd, 0xc7, 0x0, 0xf, 0xe0, 0xf, 0x80,

    /* U+0041 "A" */
    0xe, 0x1, 0xc0, 0x7c, 0xd, 0x83, 0x30, 0x63,
    0x1f, 0xe3, 0xfe, 0x60, 0xd8, 0x1c,

    /* U+0042 "B" */
    0xfe, 0x7f, 0xb0, 0xd8, 0x6f, 0xf7, 0xff, 0x7,
    0x83, 0xff, 0xff, 0x80,

    /* U+0043 "C" */
    0x1e, 0x3f, 0xd8, 0x58, 0xc, 0x6, 0x3, 0x0,
    0xc2, 0x7f, 0x8f, 0x0,

    /* U+0044 "D" */
    0xfe, 0x3f, 0xec, 0x3b, 0x3, 0xc0, 0xf0, 0x3c,
    0xf, 0xe, 0xff, 0xbf, 0x80,

    /* U+0045 "E" */
    0xff, 0xff, 0xc0, 0xc0, 0xfe, 0xfe, 0xc0, 0xc0,
    0xff, 0xff,

    /* U+0046 "F" */
    0xff, 0xff, 0xc0, 0xc0, 0xfe, 0xfe, 0xc0, 0xc0,
    0xc0, 0xc0,

    /* U+0047 "G" */
    0x1f, 0x3f, 0xd8, 0x58, 0xc, 0x6, 0xf, 0x6,
    0xc3, 0x7f, 0x8f, 0x80,

    /* U+0048 "H" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3f, 0xff, 0xff, 0x7,
    0x83, 0xc1, 0xe0, 0xc0,

    /* U+0049 "I" */
    0xff, 0xff, 0xf0,

    /* U+004A "J" */
    0x7e, 0xfc, 0x18, 0x30, 0x60, 0xc1, 0xa3, 0xfe,
    0x78,

    /* U+004B "K" */
    0xc3, 0xe3, 0xb3, 0x9b, 0x8f, 0x87, 0xe3, 0xb9,
    0x8c, 0xc7, 0x61, 0xc0,

    /* U+004C "L" */
    0xc1, 0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xff,
    0xfc,

    /* U+004D "M" */
    0xc0, 0x7c, 0x1f, 0x83, 0xf8, 0xff, 0xbf, 0xb6,
    0xf3, 0x9e, 0x73, 0xc4, 0x78, 0xc,

    /* U+004E "N" */
    0xc1, 0xf0, 0xfc, 0x7f, 0x3f, 0xde, 0xef, 0x3f,
    0x8f, 0xc3, 0xe0, 0xc0,

    /* U+004F "O" */
    0x1f, 0xf, 0xf1, 0xc3, 0x60, 0x3c, 0x7, 0x80,
    0xf0, 0x1b, 0xe, 0x7f, 0xc3, 0xe0,

    /* U+0050 "P" */
    0xfc, 0xfe, 0xc3, 0xc3, 0xc3, 0xfe, 0xfc, 0xc0,
    0xc0, 0xc0,

    /* U+0051 "Q" */
    0x1f, 0x7, 0xfc, 0x61, 0xcc, 0x6, 0xc0, 0x6c,
    0x6, 0xc0, 0x66, 0x1c, 0x7f, 0xc1, 0xf0, 0x7,
    0xe0, 0x1c,

    /* U+0052 "R" */
    0xfc, 0xfe, 0xc3, 0xc3, 0xc3, 0xfe, 0xfc, 0xce,
    0xc6, 0xc3,

    /* U+0053 "S" */
    0x3e, 0xfe, 0xc2, 0xc0, 0x78, 0x1e, 0x3, 0x83,
    0xff, 0x7c,

    /* U+0054 "T" */
    0xff, 0xff, 0xc6, 0x3, 0x1, 0x80, 0xc0, 0x60,
    0x30, 0x18, 0xc, 0x0,

    /* U+0055 "U" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0xc7, 0x7f, 0x1f, 0x0,

    /* U+0056 "V" */
    0xe0, 0xcc, 0x19, 0x87, 0x38, 0xc3, 0x38, 0x76,
    0x6, 0xc0, 0xf0, 0x1e, 0x1, 0xc0,

    /* U+0057 "W" */
    0xe1, 0x83, 0x61, 0xc7, 0x63, 0xc6, 0x73, 0xc6,
    0x33, 0x6e, 0x36, 0x6c, 0x3e, 0x6c, 0x1e, 0x3c,
    0x1c, 0x38, 0x1c, 0x38,

    /* U+0058 "X" */
    0xe1, 0x9c, 0xc3, 0x70, 0xf8, 0x1c, 0x7, 0x83,
    0xe0, 0xdc, 0x63, 0xb8, 0x60,

    /* U+0059 "Y" */
    0xe1, 0xd8, 0x63, 0x30, 0xec, 0x1e, 0x7, 0x80,
    0xc0, 0x30, 0xc, 0x3, 0x0,

    /* U+005A "Z" */
    0xff, 0xff, 0x6, 0xe, 0x1c, 0x38, 0x70, 0x60,
    0xff, 0xff,

    /* U+005B "[" */
    0xff, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xff,

    /* U+005C "\\" */
    0x60, 0xc1, 0x81, 0x83, 0x6, 0x4, 0xc, 0x18,
    0x10, 0x30, 0x60, 0x40, 0xc0,

    /* U+005D "]" */
    0xff, 0x33, 0x33, 0x33, 0x33, 0x33, 0xff,

    /* U+005E "^" */
    0x30, 0x71, 0xa2, 0x6c, 0xd8, 0x80,

    /* U+005F "_" */
    0xff, 0xfc,

    /* U+0060 "`" */
    0x63,

    /* U+0061 "a" */
    0x7d, 0xfc, 0x1b, 0xff, 0xf8, 0xff, 0xbb,

    /* U+0062 "b" */
    0xc0, 0xc0, 0xc0, 0xdc, 0xfe, 0xe7, 0xc3, 0xc3,
    0xe7, 0xfe, 0xdc,

    /* U+0063 "c" */
    0x3c, 0xff, 0x9e, 0xc, 0x1c, 0xdf, 0x9e,

    /* U+0064 "d" */
    0x3, 0x3, 0x3, 0x3b, 0x7f, 0xe7, 0xc3, 0xc3,
    0xe7, 0x7f, 0x3b,

    /* U+0065 "e" */
    0x3c, 0x7e, 0xe7, 0xff, 0xff, 0xe0, 0x7e, 0x3c,

    /* U+0066 "f" */
    0x3d, 0xe6, 0x3e, 0xf9, 0x86, 0x18, 0x61, 0x86,
    0x0,

    /* U+0067 "g" */
    0x3b, 0x7f, 0xe7, 0xc3, 0xc3, 0xe7, 0x7f, 0x3b,
    0x7, 0x7e, 0x7c,

    /* U+0068 "h" */
    0xc0, 0xc0, 0xc0, 0xde, 0xff, 0xe3, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3,

    /* U+0069 "i" */
    0x30, 0xff, 0xff,

    /* U+006A "j" */
    0x3, 0x0, 0x33, 0x33, 0x33, 0x33, 0x3f, 0xe0,

    /* U+006B "k" */
    0xc0, 0xc0, 0xc0, 0xc6, 0xcc, 0xdc, 0xf8, 0xfc,
    0xec, 0xce, 0xc7,

    /* U+006C "l" */
    0xff, 0xff, 0xfc,

    /* U+006D "m" */
    0xfd, 0xef, 0xff, 0xc6, 0x3c, 0x63, 0xc6, 0x3c,
    0x63, 0xc6, 0x3c, 0x63,

    /* U+006E "n" */
    0xde, 0xff, 0xe3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,

    /* U+006F "o" */
    0x3c, 0x7e, 0xe7, 0xc3, 0xc3, 0xe7, 0x7e, 0x3c,

    /* U+0070 "p" */
    0xdc, 0xfe, 0xe7, 0xc3, 0xc3, 0xe7, 0xfe, 0xdc,
    0xc0, 0xc0, 0xc0,

    /* U+0071 "q" */
    0x3b, 0x7f, 0xe7, 0xc3, 0xc3, 0xe7, 0x7f, 0x3b,
    0x3, 0x3, 0x3,

    /* U+0072 "r" */
    0xdf, 0xf9, 0x8c, 0x63, 0x18,

    /* U+0073 "s" */
    0x7d, 0xfb, 0x7, 0x83, 0xd1, 0xbf, 0x3c,

    /* U+0074 "t" */
    0x61, 0x8f, 0xbe, 0x61, 0x86, 0x18, 0x78, 0xe0,

    /* U+0075 "u" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc7, 0xff, 0x3b,

    /* U+0076 "v" */
    0xc3, 0xe3, 0x67, 0x66, 0x36, 0x3c, 0x3c, 0x1c,

    /* U+0077 "w" */
    0xc3, 0x1b, 0x38, 0xd9, 0xcc, 0xdb, 0x63, 0xdb,
    0x1e, 0xf0, 0xe3, 0x83, 0x1c,

    /* U+0078 "x" */
    0xe6, 0x6e, 0x3c, 0x38, 0x38, 0x7c, 0x6e, 0xc7,

    /* U+0079 "y" */
    0xc3, 0xe3, 0x66, 0x76, 0x36, 0x3c, 0x1c, 0x18,
    0x18, 0xf8, 0xf0,

    /* U+007A "z" */
    0xff, 0xfc, 0x70, 0xc3, 0xe, 0x3f, 0xff,

    /* U+007B "{" */
    0x3b, 0xd8, 0xc6, 0x33, 0x9c, 0x63, 0x18, 0xc7,
    0x9c,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xf0,

    /* U+007D "}" */
    0xe3, 0xc3, 0xc, 0x30, 0xc3, 0xcf, 0x30, 0xc3,
    0xc, 0xf3, 0x80,

    /* U+007E "~" */
    0x73, 0xfe, 0x70,

    /* U+00B0 "°" */
    0x74, 0x63, 0x17, 0x0,

    /* U+2022 "•" */
    0x6f, 0xf0,

    /* U+F001 "" */
    0x0, 0x0, 0x0, 0x7c, 0x7, 0xf8, 0x7f, 0xf0,
    0xff, 0x61, 0xf0, 0xc3, 0x1, 0x86, 0x3, 0xc,
    0x6, 0x18, 0x3c, 0x30, 0xfb, 0xe1, 0xff, 0xc0,
    0x8f, 0x0, 0x0,

    /* U+F008 "" */
    0x9f, 0xf7, 0xc0, 0x79, 0x1, 0x7c, 0x7, 0x9f,
    0xf6, 0x7f, 0xdf, 0x1, 0xe4, 0x5, 0xf0, 0x1e,
    0x7f, 0xd0,

    /* U+F00B "" */
    0xf7, 0xff, 0xdf, 0xff, 0x7f, 0xc0, 0x0, 0xf7,
    0xff, 0xdf, 0xff, 0x7f, 0xc0, 0x0, 0x0, 0x3,
    0xdf, 0xff, 0x7f, 0xfd, 0xff,

    /* U+F00C "" */
    0x0, 0x1c, 0x0, 0xf0, 0x7, 0x90, 0x3c, 0xe1,
    0xe3, 0xcf, 0x7, 0xf8, 0xf, 0xc0, 0x1e, 0x0,
    0x10, 0x0,

    /* U+F00D "" */
    0x40, 0xbc, 0xf7, 0xf8, 0xfc, 0x1e, 0xf, 0xc7,
    0xfb, 0xcf, 0x40, 0x80,

    /* U+F011 "" */
    0x3, 0x0, 0xcc, 0xc7, 0x33, 0x98, 0xc6, 0xc3,
    0xf, 0xc, 0x3c, 0x30, 0xf0, 0xc3, 0xe0, 0x1d,
    0x80, 0x67, 0x87, 0x8f, 0xfc, 0xf, 0xc0,

    /* U+F013 "" */
    0xf, 0x0, 0x78, 0x17, 0xe9, 0xff, 0xef, 0xff,
    0xb8, 0x79, 0xc3, 0x8e, 0x1c, 0xf9, 0xff, 0xff,
    0x9f, 0xfc, 0x1e, 0x0, 0xf0, 0x1, 0x0,

    /* U+F015 "" */
    0x1, 0x9c, 0x3, 0xdc, 0xe, 0x7c, 0x1d, 0xbc,
    0x3b, 0xdc, 0x67, 0xe6, 0xcf, 0xfb, 0x1f, 0xf8,
    0x1f, 0xf8, 0x1e, 0x78, 0x1e, 0x78, 0x1e, 0x78,

    /* U+F019 "" */
    0x3, 0x80, 0xe, 0x0, 0x38, 0x0, 0xe0, 0x3,
    0x80, 0xe, 0x1, 0xff, 0x3, 0xf8, 0x7, 0xc0,
    0xe, 0xf, 0xd7, 0xff, 0xff, 0xff, 0xef, 0xff,
    0xf0,

    /* U+F01C "" */
    0x1f, 0xf8, 0x1f, 0xf8, 0x30, 0xc, 0x70, 0xe,
    0x60, 0x6, 0xe0, 0x7, 0xfc, 0x3f, 0xfc, 0x3f,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff,

    /* U+F021 "" */
    0xf, 0x8c, 0x7f, 0xb3, 0x87, 0xdc, 0xf, 0xe0,
    0xff, 0x3, 0xf0, 0x0, 0x0, 0x0, 0xfc, 0xf,
    0xf0, 0x6f, 0x3, 0xbe, 0x1c, 0xdf, 0xe3, 0x1f,
    0x0,

    /* U+F026 "" */
    0x2, 0xc, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xe,
    0xc, 0x8,

    /* U+F027 "" */
    0x2, 0x1, 0x80, 0xe3, 0xf8, 0xfe, 0xff, 0x9f,
    0xe7, 0xfa, 0xe, 0x1, 0x80, 0x20,

    /* U+F028 "" */
    0x0, 0x8, 0x2, 0xc, 0x6, 0x26, 0xe, 0x32,
    0xfe, 0x19, 0xfe, 0xc9, 0xfe, 0x49, 0xfe, 0x49,
    0xfe, 0x89, 0xe, 0x13, 0x6, 0x32, 0x2, 0x6,
    0x0, 0xc,

    /* U+F03E "" */
    0xff, 0xff, 0x3f, 0xfc, 0xfb, 0xf3, 0xc7, 0xfe,
    0xf, 0x90, 0x3c, 0x0, 0xf0, 0x3, 0xff, 0xff,
    0xff, 0xf0,

    /* U+F043 "" */
    0xc, 0x3, 0x1, 0xe0, 0x78, 0x3f, 0x1f, 0xe7,
    0xfb, 0xff, 0xff, 0xf7, 0xfc, 0xfd, 0x9e, 0x7f,
    0x7, 0x80,

    /* U+F048 "" */
    0xc1, 0xe1, 0xf1, 0xf9, 0xfd, 0xff, 0xff, 0xff,
    0xbf, 0xcf, 0xe3, 0xf0, 0xf8, 0x30,

    /* U+F04B "" */
    0xe0, 0xf, 0x80, 0xfc, 0xf, 0xf0, 0xff, 0x8f,
    0xfe, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xf8, 0xfe,
    0xf, 0x80, 0xf0, 0x4, 0x0,

    /* U+F04C "" */
    0xf9, 0xff, 0x9f, 0xf9, 0xff, 0x9f, 0xf9, 0xff,
    0x9f, 0xf9, 0xff, 0x9f, 0xf9, 0xff, 0x9f, 0xf9,
    0xff, 0x9f,

    /* U+F04D "" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff,

    /* U+F051 "" */
    0xc1, 0xf0, 0xfc, 0x7f, 0x3f, 0xdf, 0xff, 0xff,
    0xfb, 0xf9, 0xf8, 0xf8, 0x78, 0x30,

    /* U+F052 "" */
    0x6, 0x0, 0xf0, 0x1f, 0x83, 0xfc, 0x7f, 0xe7,
    0xff, 0xff, 0xff, 0xff, 0x0, 0xf, 0xff, 0xff,
    0xff, 0xff,

    /* U+F053 "" */
    0x6, 0x1c, 0x71, 0xc7, 0x1c, 0x38, 0x38, 0x38,
    0x38, 0x38, 0x30,

    /* U+F054 "" */
    0xc1, 0xc1, 0xc1, 0xc1, 0xc1, 0xc3, 0x8e, 0x38,
    0xe3, 0x86, 0x0,

    /* U+F067 "" */
    0x6, 0x0, 0x60, 0x6, 0x0, 0x60, 0x6, 0xf,
    0xff, 0xff, 0xf0, 0x60, 0x6, 0x0, 0x60, 0x6,
    0x0, 0x60,

    /* U+F068 "" */
    0xff, 0xff, 0xff,

    /* U+F06E "" */
    0x7, 0xe0, 0x1c, 0x38, 0x39, 0x9c, 0x71, 0xce,
    0xf7, 0xcf, 0xf7, 0xcf, 0x73, 0x8e, 0x38, 0x1c,
    0x1c, 0x38, 0x7, 0xe0,

    /* U+F070 "" */
    0x40, 0x0, 0x38, 0x0, 0x7, 0xbf, 0x0, 0x78,
    0x70, 0xe, 0x4e, 0x8, 0xf9, 0xc7, 0x1f, 0x79,
    0xe3, 0xde, 0x38, 0x3f, 0x87, 0x7, 0xc0, 0xe0,
    0xe0, 0xf, 0x8e, 0x0, 0x1, 0xc0, 0x0, 0x10,

    /* U+F071 "" */
    0x1, 0x80, 0x3, 0xc0, 0x3, 0xc0, 0x7, 0xe0,
    0x7, 0xe0, 0xe, 0x70, 0x1e, 0x70, 0x1e, 0x78,
    0x3e, 0x7c, 0x3f, 0xfc, 0x7e, 0x7e, 0xfe, 0x7e,
    0xff, 0xff, 0xff, 0xfe,

    /* U+F074 "" */
    0x0, 0x10, 0x0, 0xef, 0xf, 0xfe, 0x7f, 0x19,
    0xb8, 0xc, 0x40, 0x60, 0x3, 0x84, 0x1d, 0xbb,
    0xe7, 0xff, 0xf, 0xc0, 0xe, 0x0, 0x10,

    /* U+F077 "" */
    0x6, 0x0, 0xf0, 0x1f, 0x83, 0x9c, 0x70, 0xee,
    0x7, 0xc0, 0x30,

    /* U+F078 "" */
    0x40, 0x2e, 0x7, 0x70, 0xe3, 0x9c, 0x1f, 0x80,
    0xf0, 0x6, 0x0,

    /* U+F079 "" */
    0x18, 0x0, 0xf, 0x7f, 0x87, 0xff, 0xe3, 0xfc,
    0x18, 0x5a, 0x6, 0x6, 0x1, 0x81, 0x81, 0x68,
    0x60, 0xff, 0x1f, 0xff, 0x87, 0xfb, 0xc0, 0x0,
    0x60,

    /* U+F07B "" */
    0x7c, 0x3, 0xf8, 0xf, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xc0,

    /* U+F093 "" */
    0x0, 0x0, 0xc, 0x0, 0x7c, 0x7, 0xf8, 0x3f,
    0xf0, 0xff, 0xc0, 0x78, 0x1, 0xe0, 0x7, 0x80,
    0x1e, 0xf, 0x37, 0xff, 0xff, 0xff, 0xaf, 0xff,
    0xf0,

    /* U+F095 "" */
    0x0, 0x3c, 0x1, 0xf0, 0x7, 0xc0, 0x1f, 0x0,
    0x7c, 0x0, 0xe0, 0x3, 0x80, 0x1c, 0x10, 0xf1,
    0xe7, 0x8f, 0xfc, 0x3f, 0xe0, 0x7e, 0x1, 0xc0,
    0x0,

    /* U+F0C4 "" */
    0x70, 0xf, 0x8f, 0xd9, 0xef, 0xbc, 0x7f, 0x81,
    0xf0, 0x1f, 0x7, 0xf8, 0xfb, 0xcd, 0x9e, 0xf8,
    0xf7, 0x0,

    /* U+F0C5 "" */
    0xf, 0xa0, 0x7d, 0xfb, 0xe1, 0xdf, 0xfe, 0xff,
    0xf7, 0xff, 0xbf, 0xfd, 0xff, 0xef, 0xff, 0x7f,
    0xfb, 0xff, 0xc0, 0xf, 0xf8, 0x7f, 0xc0,

    /* U+F0C7 "" */
    0xff, 0xc7, 0xff, 0x30, 0x1d, 0x80, 0xfc, 0x7,
    0xff, 0xff, 0xff, 0xff, 0x1f, 0xf8, 0xff, 0xc7,
    0xff, 0xff, 0xff, 0xf0,

    /* U+F0C9 "" */
    0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0xf,
    0xff, 0xff, 0xf0, 0x0, 0x0, 0xf, 0xff, 0xff,
    0xf0,

    /* U+F0E0 "" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0xfc, 0xdf,
    0xe7, 0xbf, 0x7f, 0x33, 0xff, 0x3f, 0xff, 0xff,
    0xff, 0xf0,

    /* U+F0E7 "" */
    0x7c, 0x3e, 0x1f, 0x1f, 0xf, 0xf7, 0xff, 0xfd,
    0xfc, 0xe, 0x6, 0x7, 0x3, 0x1, 0x80, 0x80,

    /* U+F0EA "" */
    0x1c, 0x7, 0xbc, 0x3f, 0xe1, 0xf0, 0xf, 0x7a,
    0x7b, 0xdb, 0xde, 0x1e, 0xf0, 0xf7, 0xff, 0xbf,
    0xfd, 0xfe, 0xf, 0xf0, 0x7f, 0x83, 0xf8,

    /* U+F0F3 "" */
    0x6, 0x0, 0xf0, 0x1f, 0x83, 0xfc, 0x3f, 0xc3,
    0xfc, 0x3f, 0xc7, 0xfe, 0x7f, 0xef, 0xff, 0xff,
    0xf0, 0x0, 0xf, 0x0, 0x60,

    /* U+F11C "" */
    0xff, 0xff, 0xff, 0xff, 0xca, 0x53, 0xca, 0x53,
    0xff, 0xff, 0xe5, 0xa7, 0xe5, 0xa7, 0xff, 0xff,
    0xc8, 0x13, 0xff, 0xff, 0xff, 0xff,

    /* U+F124 "" */
    0x0, 0x1c, 0x1, 0xf0, 0x3f, 0x83, 0xfe, 0x3f,
    0xfb, 0xff, 0xcf, 0xff, 0x1f, 0xf8, 0x3, 0xe0,
    0xf, 0x0, 0x3c, 0x0, 0xe0, 0x3, 0x80, 0x4,
    0x0,

    /* U+F15B "" */
    0xfd, 0x9f, 0xbb, 0xf7, 0xfe, 0xf, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfe,

    /* U+F1EB "" */
    0x0, 0x0, 0x3, 0xff, 0x3, 0xff, 0xf1, 0xe0,
    0x1e, 0xe0, 0x1, 0xd0, 0xfc, 0x20, 0xff, 0xc0,
    0x78, 0x78, 0x8, 0x4, 0x0, 0x0, 0x0, 0xc,
    0x0, 0x7, 0x80, 0x0, 0xc0, 0x0,

    /* U+F240 "" */
    0xff, 0xff, 0xbf, 0xff, 0xec, 0x0, 0x1f, 0x7f,
    0xf7, 0xdf, 0xfc, 0xf7, 0xff, 0x7c, 0x0, 0x1f,
    0xff, 0xfe, 0xff, 0xff, 0x80,

    /* U+F241 "" */
    0xff, 0xff, 0xbf, 0xff, 0xec, 0x0, 0x1f, 0x7f,
    0xc7, 0xdf, 0xf0, 0xf7, 0xfc, 0x7c, 0x0, 0x1f,
    0xff, 0xfe, 0xff, 0xff, 0x80,

    /* U+F242 "" */
    0xff, 0xff, 0xbf, 0xff, 0xec, 0x0, 0x1f, 0x7e,
    0x7, 0xdf, 0x80, 0xf7, 0xe0, 0x7c, 0x0, 0x1f,
    0xff, 0xfe, 0xff, 0xff, 0x80,

    /* U+F243 "" */
    0xff, 0xff, 0xbf, 0xff, 0xec, 0x0, 0x1f, 0x70,
    0x7, 0xdc, 0x0, 0xf7, 0x0, 0x7c, 0x0, 0x1f,
    0xff, 0xfe, 0xff, 0xff, 0x80,

    /* U+F244 "" */
    0xff, 0xff, 0xbf, 0xff, 0xec, 0x0, 0x1f, 0x0,
    0x7, 0xc0, 0x0, 0xf0, 0x0, 0x7c, 0x0, 0x1f,
    0xff, 0xfe, 0xff, 0xff, 0x80,

    /* U+F287 "" */
    0x0, 0x70, 0x0, 0x7c, 0x0, 0x37, 0x0, 0x8,
    0x0, 0xf6, 0x1, 0xbf, 0xff, 0xff, 0x18, 0x18,
    0x2, 0x0, 0x0, 0xdc, 0x0, 0x1f, 0x0, 0x1,
    0xc0,

    /* U+F293 "" */
    0x1f, 0xf, 0xf1, 0xef, 0x7c, 0xec, 0xad, 0xc1,
    0xfc, 0x7f, 0x8f, 0xe0, 0xf9, 0x4b, 0xe3, 0x3c,
    0xe7, 0xb8, 0x3e, 0x0,

    /* U+F2ED "" */
    0xf, 0xf, 0xff, 0x0, 0x7, 0xfe, 0x7f, 0xe6,
    0xf6, 0x6f, 0x66, 0xf6, 0x6f, 0x66, 0xf6, 0x6f,
    0x66, 0xf6, 0x7f, 0xe7, 0xfe,

    /* U+F304 "" */
    0x0, 0x30, 0x1, 0xe0, 0x7, 0xc0, 0x6f, 0x3,
    0xd8, 0x1f, 0x80, 0xfe, 0x7, 0xf0, 0x3f, 0x81,
    0xfc, 0xf, 0xe0, 0x3f, 0x0, 0xf8, 0x3, 0x80,
    0x0,

    /* U+F55A "" */
    0xf, 0xff, 0x87, 0xff, 0xf3, 0xf7, 0x3d, 0xfc,
    0x8f, 0xff, 0x87, 0xff, 0xe1, 0xf7, 0xf2, 0x3c,
    0xfd, 0xcf, 0x1f, 0xff, 0xc3, 0xff, 0xe0,

    /* U+F7C2 "" */
    0x1f, 0xc7, 0xfd, 0xa9, 0xf5, 0x3f, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xf7, 0xfc,

    /* U+F8A2 "" */
    0x0, 0x4, 0x0, 0x31, 0x80, 0xce, 0x3, 0xff,
    0xff, 0xff, 0xf3, 0x80, 0x6, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 63, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 65, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 98, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 7, .adv_w = 161, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 19, .adv_w = 143, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 33, .adv_w = 196, .box_w = 12, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 48, .adv_w = 163, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 60, .adv_w = 52, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 61, .adv_w = 80, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 68, .adv_w = 80, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 75, .adv_w = 97, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 80, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 87, .adv_w = 59, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 89, .adv_w = 86, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 90, .adv_w = 59, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 91, .adv_w = 88, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 102, .adv_w = 152, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 112, .adv_w = 88, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 132, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 126, .adv_w = 133, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 135, .adv_w = 154, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 148, .adv_w = 133, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 158, .adv_w = 143, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 139, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 178, .adv_w = 148, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 188, .adv_w = 143, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 59, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 200, .adv_w = 59, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 203, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 210, .adv_w = 134, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 216, .adv_w = 134, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 223, .adv_w = 132, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 232, .box_w = 14, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 256, .adv_w = 172, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 270, .adv_w = 171, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 282, .adv_w = 164, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 294, .adv_w = 185, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 150, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 317, .adv_w = 143, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 173, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 181, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 351, .adv_w = 73, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 121, .box_w = 7, .box_h = 10, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 363, .adv_w = 166, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 135, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 384, .adv_w = 214, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 398, .adv_w = 181, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 410, .adv_w = 189, .box_w = 11, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 424, .adv_w = 164, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 434, .adv_w = 189, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 452, .adv_w = 165, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 462, .adv_w = 143, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 472, .adv_w = 138, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 484, .adv_w = 177, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 496, .adv_w = 167, .box_w = 11, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 510, .adv_w = 261, .box_w = 16, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 530, .adv_w = 160, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 543, .adv_w = 151, .box_w = 10, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 556, .adv_w = 150, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 566, .adv_w = 82, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 573, .adv_w = 88, .box_w = 7, .box_h = 14, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 586, .adv_w = 82, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 593, .adv_w = 134, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 599, .adv_w = 112, .box_w = 7, .box_h = 2, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 601, .adv_w = 134, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 602, .adv_w = 138, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 609, .adv_w = 155, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 620, .adv_w = 132, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 627, .adv_w = 155, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 638, .adv_w = 141, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 646, .adv_w = 87, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 655, .adv_w = 157, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 666, .adv_w = 155, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 677, .adv_w = 67, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 680, .adv_w = 69, .box_w = 4, .box_h = 15, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 688, .adv_w = 148, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 699, .adv_w = 67, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 702, .adv_w = 235, .box_w = 12, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 714, .adv_w = 155, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 722, .adv_w = 147, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 730, .adv_w = 155, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 741, .adv_w = 155, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 752, .adv_w = 97, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 757, .adv_w = 119, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 764, .adv_w = 97, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 772, .adv_w = 154, .box_w = 8, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 780, .adv_w = 134, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 788, .adv_w = 210, .box_w = 13, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 801, .adv_w = 133, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 809, .adv_w = 134, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 820, .adv_w = 122, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 827, .adv_w = 88, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 836, .adv_w = 69, .box_w = 2, .box_h = 14, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 840, .adv_w = 88, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 851, .adv_w = 134, .box_w = 7, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 854, .adv_w = 94, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 858, .adv_w = 80, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 860, .adv_w = 224, .box_w = 15, .box_h = 14, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 887, .adv_w = 224, .box_w = 14, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 905, .adv_w = 224, .box_w = 14, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 926, .adv_w = 224, .box_w = 14, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 944, .adv_w = 154, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 956, .adv_w = 224, .box_w = 14, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 979, .adv_w = 224, .box_w = 13, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1002, .adv_w = 252, .box_w = 16, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1026, .adv_w = 224, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1051, .adv_w = 252, .box_w = 16, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1073, .adv_w = 224, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1098, .adv_w = 112, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1108, .adv_w = 168, .box_w = 10, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1122, .adv_w = 252, .box_w = 16, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1148, .adv_w = 224, .box_w = 14, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1166, .adv_w = 154, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1184, .adv_w = 196, .box_w = 9, .box_h = 12, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 1198, .adv_w = 196, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1219, .adv_w = 196, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1237, .adv_w = 196, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1255, .adv_w = 196, .box_w = 9, .box_h = 12, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 1269, .adv_w = 196, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1287, .adv_w = 140, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1298, .adv_w = 140, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 1309, .adv_w = 196, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1327, .adv_w = 196, .box_w = 12, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 1330, .adv_w = 252, .box_w = 16, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1350, .adv_w = 280, .box_w = 18, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1382, .adv_w = 252, .box_w = 16, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1410, .adv_w = 224, .box_w = 14, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1433, .adv_w = 196, .box_w = 12, .box_h = 7, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1444, .adv_w = 196, .box_w = 12, .box_h = 7, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1455, .adv_w = 280, .box_w = 18, .box_h = 11, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 1480, .adv_w = 224, .box_w = 14, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1500, .adv_w = 224, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1525, .adv_w = 224, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1550, .adv_w = 196, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1568, .adv_w = 196, .box_w = 13, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1591, .adv_w = 196, .box_w = 13, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1611, .adv_w = 196, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1628, .adv_w = 224, .box_w = 14, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1646, .adv_w = 140, .box_w = 9, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1662, .adv_w = 196, .box_w = 13, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1685, .adv_w = 196, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1706, .adv_w = 252, .box_w = 16, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1728, .adv_w = 224, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1753, .adv_w = 168, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1771, .adv_w = 280, .box_w = 18, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1801, .adv_w = 280, .box_w = 18, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1822, .adv_w = 280, .box_w = 18, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1843, .adv_w = 280, .box_w = 18, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1864, .adv_w = 280, .box_w = 18, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1885, .adv_w = 280, .box_w = 18, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1906, .adv_w = 280, .box_w = 18, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1931, .adv_w = 196, .box_w = 11, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1951, .adv_w = 196, .box_w = 12, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1972, .adv_w = 224, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1997, .adv_w = 280, .box_w = 18, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2020, .adv_w = 168, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2038, .adv_w = 225, .box_w = 14, .box_h = 8, .ofs_x = 0, .ofs_y = 1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0x1f72, 0xef51, 0xef58, 0xef5b, 0xef5c, 0xef5d, 0xef61,
    0xef63, 0xef65, 0xef69, 0xef6c, 0xef71, 0xef76, 0xef77, 0xef78,
    0xef8e, 0xef93, 0xef98, 0xef9b, 0xef9c, 0xef9d, 0xefa1, 0xefa2,
    0xefa3, 0xefa4, 0xefb7, 0xefb8, 0xefbe, 0xefc0, 0xefc1, 0xefc4,
    0xefc7, 0xefc8, 0xefc9, 0xefcb, 0xefe3, 0xefe5, 0xf014, 0xf015,
    0xf017, 0xf019, 0xf030, 0xf037, 0xf03a, 0xf043, 0xf06c, 0xf074,
    0xf0ab, 0xf13b, 0xf190, 0xf191, 0xf192, 0xf193, 0xf194, 0xf1d7,
    0xf1e3, 0xf23d, 0xf254, 0xf4aa, 0xf712, 0xf7f2
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 176, .range_length = 63475, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 62, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 1, 2, 0, 3, 4, 5,
    2, 6, 7, 8, 9, 10, 9, 10,
    11, 12, 0, 13, 14, 15, 16, 17,
    18, 19, 12, 20, 20, 0, 0, 0,
    21, 22, 23, 24, 25, 22, 26, 27,
    28, 29, 29, 30, 31, 32, 29, 29,
    22, 33, 34, 35, 3, 36, 30, 37,
    37, 38, 39, 40, 41, 42, 43, 0,
    44, 0, 45, 46, 47, 48, 49, 50,
    51, 45, 52, 52, 53, 48, 45, 45,
    46, 46, 54, 55, 56, 57, 51, 58,
    58, 59, 58, 60, 41, 0, 0, 9,
    61, 9, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 1, 2, 0, 3, 4, 5,
    2, 6, 7, 8, 9, 10, 9, 10,
    11, 12, 13, 14, 15, 16, 17, 12,
    18, 19, 20, 21, 21, 0, 0, 0,
    22, 23, 24, 25, 23, 25, 25, 25,
    23, 25, 25, 26, 25, 25, 25, 25,
    23, 25, 23, 25, 3, 27, 28, 29,
    29, 30, 31, 32, 33, 34, 35, 0,
    36, 0, 37, 38, 39, 39, 39, 40,
    39, 38, 41, 42, 38, 38, 43, 43,
    39, 43, 39, 43, 44, 45, 46, 47,
    47, 48, 49, 50, 0, 0, 35, 9,
    51, 9, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 1, 0, 0, 0, 0, 0, 2,
    0, 1, 0, 0, 2, 0, 0, 0,
    0, 1, 0, 0, 0, 0, 0, 0,
    0, 5, 4, 0, 2, 0, 4, 0,
    0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 10, 0, 5, -4,
    0, 0, 4, 0, -12, -13, 1, 10,
    4, 3, -9, 1, 9, 0, 8, 2,
    6, 0, -9, 0, 0, 3, 0, 0,
    0, 0, 0, 0, 13, 3, -1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 4, 0, -7,
    0, 0, 0, 0, 0, -4, 3, 4,
    0, 0, -2, 0, -1, 2, 0, -2,
    0, -2, -1, -4, 0, 0, 0, 0,
    -2, 0, 0, -3, -3, 0, 0, -2,
    0, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, -2, -2, 0,
    -3, 0, -5, 0, -28, 0, 0, -4,
    -11, 4, 7, 0, 0, -4, 2, 2,
    7, 4, -3, 4, 0, 0, -12, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -8, 0, 0, 2, 0, 6,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -5, -3, -9, 0, -9,
    -1, 0, 0, -7, 0, -1, 7, 0,
    -7, -3, -1, 1, 0, -3, 0, 0,
    -2, -15, 0, 2, 0, 6, -5, 0,
    -4, 0, -9, 2, 0, -18, -3, 5,
    2, 0, 0, 0, 0, 0, 0, 0,
    2, 0, -4, -1, -4, 0, -11, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 8, 0, 2, 0, 0, -4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, 0, 0, 0, 0, 0, 0,
    10, 3, 1, 0, 0, 0, 0, 0,
    23, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -8, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 2, 4, 2,
    7, -2, 0, 0, 4, -2, -8, -30,
    1, 5, 4, 0, -3, 0, 5, 0,
    6, 0, 6, 0, -22, 0, -3, 7,
    0, 7, -2, 4, 2, 0, 0, 1,
    -2, 0, 0, -3, 0, 0, 0, 18,
    0, 7, 0, 8, 4, 8, 3, 7,
    0, 0, -3, -8, 0, 0, 0, -2,
    1, -2, 0, 1, -5, -4, -4, 1,
    0, -2, 0, 0, 0, -9, 1, -5,
    0, -4, -8, 0, -6, -5, -7, 0,
    0, -15, 0, 0, 0, 0, 2, 0,
    0, 0, 0, 0, 2, 0, -4, -6,
    -4, -3, 0, 1, -12, 2, -15, 0,
    0, 0, -8, -2, 0, 20, -3, -4,
    2, 2, 0, 0, -4, 2, 0, 0,
    -13, -4, 7, 0, 12, -7, -2, -9,
    0, -9, 3, 0, -21, 0, 2, 2,
    0, -2, 0, 0, 2, 0, 0, -1,
    -2, -7, 0, -7, 0, -15, 0, 13,
    -4, 0, -8, 0, 8, 0, -16, -21,
    -16, -4, 7, 0, 0, -14, 0, 2,
    -6, 0, -3, 0, -4, -9, 0, -2,
    7, 0, 7, 0, 7, 0, 0, 3,
    7, -26, -14, 0, -14, 0, 3, 1,
    -14, -14, -5, -14, -7, -11, -7, -14,
    10, 0, 1, 0, 0, 0, 0, 0,
    1, 1, -3, -4, 0, -1, -1, -2,
    0, 0, -1, 0, 0, 0, -4, 0,
    -2, 0, -6, -4, 0, -6, -8, -8,
    -3, 0, -4, 0, -4, 0, 0, 0,
    0, 0, -2, 0, 0, 2, 0, 1,
    -2, 1, 0, 0, 0, 0, 0, 2,
    -1, 0, 0, 0, -1, 2, 2, 0,
    0, 0, 0, -2, 0, 0, 0, 0,
    0, 0, 0, 1, 0, 4, -1, 0,
    -3, 0, -4, 0, 0, -1, 0, 7,
    0, 0, -2, 0, 0, 0, 0, 0,
    0, 0, 0, -1, 0, -1, 0, 0,
    -2, 0, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -1, -1, 0, -2,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, -2, 0, -2, -2, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -2, 0, 0, 0, 0, -2, -4, -2,
    0, -3, 0, -7, -1, -7, 4, 0,
    0, -4, 2, 4, 5, 0, -6, 0,
    -2, 0, 0, -9, 2, -1, 2, -13,
    2, 0, 0, 1, -12, 0, -13, -2,
    -20, -1, 0, -11, 0, 4, 6, 0,
    4, 0, 0, 0, 0, 0, 0, 0,
    -5, -4, -5, 0, -7, 0, 0, 0,
    -2, 0, 0, 0, -2, 0, 0, 0,
    0, 0, -1, -1, 0, -1, -3, 0,
    0, 0, 0, 0, 0, 0, -2, -2,
    0, -2, -3, -2, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, -2, -2, 0, -2,
    0, -1, 0, -4, 2, 0, 0, -2,
    1, 2, 2, 0, 0, 0, 0, 0,
    0, -1, 0, 0, 0, 0, 0, 1,
    0, 0, -2, 0, -2, -1, -2, 0,
    0, 0, 0, 0, 0, 0, 2, 0,
    0, -2, 0, 0, 0, 0, -3, -3,
    -3, 0, -3, 0, 7, -1, 1, -6,
    0, 0, 5, -11, -11, -9, -4, 2,
    0, -2, -15, -4, 0, -4, 0, -4,
    3, -4, -13, 0, -5, 0, 0, 1,
    0, 2, -1, 0, 2, 2, -7, -8,
    0, -11, 0, 0, -5, -4, -7, -2,
    -5, 1, -2, 1, -5, 2, 0, 0,
    0, -2, 0, 0, 0, 1, 0, 2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, -1, 0, 0,
    -2, 0, -4, -5, -5, 0, 0, -7,
    0, 0, 0, 0, 0, 0, 0, -2,
    0, 0, 0, 0, 0, -2, 0, 0,
    0, 0, 2, 0, 0, 0, 0, 0,
    0, 0, 0, 12, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, -2, 0,
    2, 0, 8, -2, 0, -6, -2, -9,
    0, 0, -5, 0, 2, 0, 0, 0,
    0, 0, 0, 0, 0, 3, 0, 1,
    -2, 1, 0, 0, -1, 0, 0, 0,
    -2, 0, 0, 2, 0, -11, -7, 0,
    0, 0, -3, -11, 0, 0, -2, 2,
    0, -4, -1, -10, 0, -7, 0, 0,
    -4, -5, -4, -2, -2, 0, 0, -3,
    0, 0, -2, 0, 0, 0, 0, 0,
    0, 0, 2, 0, 2, 0, 2, 0,
    -4, 0, 0, 0, 0, 2, 0, 1,
    -4, -4, 0, -2, -2, -3, 0, 0,
    0, 0, 0, 0, -7, 0, -2, 0,
    -3, -2, 0, -5, -6, -7, -2, 0,
    -4, 2, -7, 0, 0, 0, 0, 0,
    18, 0, 0, 1, 0, 0, -4, 0,
    0, 2, 0, -9, 0, 0, 0, 0,
    0, -22, -5, 7, 7, -2, -10, 0,
    2, -3, 0, -11, -1, -3, 2, -16,
    -2, 5, 0, 3, -8, -3, -9, -8,
    -10, 0, 0, -13, 0, 12, 0, 0,
    -1, 0, 0, 0, 0, -1, -1, -2,
    -6, -8, -6, 0, -22, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -2,
    0, -1, -2, -3, 0, 0, -4, 0,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -1, 0, -4, 0, 0, 4,
    -1, 3, 0, -4, 2, -1, 0, -3,
    -2, 0, -3, -2, -2, 0, -3, -3,
    0, 0, -2, -1, -1, -3, -2, 0,
    0, -2, 0, 2, -1, 0, -4, 0,
    0, 0, 0, -4, 0, -3, 0, -3,
    0, -3, 2, 0, 0, 0, 0, 0,
    0, 0, 0, -4, 2, 0, -2, 0,
    -1, -2, -4, -1, -1, -1, 0, -1,
    -2, 0, 0, 0, 0, 0, 0, -2,
    -2, -2, 0, 0, 0, 0, 2, -1,
    0, -1, 0, 0, 0, 0, -1, -2,
    -1, -1, -2, -1, -1, 0, 3, 9,
    0, 0, -5, 0, -1, 4, 0, -2,
    -9, -3, 3, 1, 0, -9, -3, 2,
    -3, 2, 0, 1, -2, -6, 0, -3,
    1, 0, 0, -3, 0, 0, 0, 2,
    2, -4, -3, 0, -3, 0, 0, -3,
    -2, -2, 0, -3, 1, -3, 1, -3,
    7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -2, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -3, 0,
    0, -3, 0, 0, -2, -2, 0, 0,
    0, 0, -2, 0, 0, 0, 0, 0,
    -1, 0, 0, 0, 0, 0, -1, 0,
    0, 0, 0, 0, -3, 0, -4, 0,
    0, 0, -8, 0, 1, -5, 4, 0,
    -1, -10, 0, 0, -5, -2, 0, -9,
    -6, -7, 0, 0, -11, -2, -9, -9,
    -11, 0, -3, 0, 3, 14, -3, 0,
    -5, 0, 0, 0, -2, -3, -5, -4,
    -9, -10, -9, -6, -2, 0, 0, -1,
    0, 1, 0, 0, -16, 0, 7, 4,
    -4, -8, 0, 1, -4, 0, -11, -1,
    -2, 4, -19, -3, 1, 0, 0, -15,
    -2, -11, -2, -16, 0, 0, -16, 0,
    11, 1, 0, -1, 0, 0, 0, 0,
    0, -1, -1, -8, -1, -8, 0, -15,
    0, 0, 0, 0, -6, 0, -1, 0,
    -1, -6, -10, 0, 0, -1, -3, -7,
    -2, 0, -2, 0, 0, 0, 0, -10,
    -2, -7, -6, -3, -4, -6, -2, -3,
    0, -4, -1, -8, -3, 0, -2, 0,
    0, -2, -2, 0, 1, 0, -1, -7,
    -1, 0, 4, 0, -4, 0, 0, 0,
    0, 2, 0, 1, -4, 11, 0, -2,
    -2, -3, 0, 0, 0, 0, 0, 0,
    -7, 0, -2, 0, -3, -2, 0, -5,
    -6, -7, -2, 0, -4, 3, 9, 0,
    0, 0, 0, 0, 18, 0, 0, 1,
    0, 0, -4, 0, 0, 2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -1, -4, 0, 0,
    0, 0, 0, -1, 0, 0, 0, -2,
    -2, 0, 0, -4, -2, 0, 0, -4,
    0, 3, -1, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0,
    3, 4, 3, -1, 0, -6, -2, 0,
    7, -8, -7, -4, -4, 9, 5, 2,
    -19, -2, 4, -2, 0, -2, 4, -2,
    -8, 0, -2, 2, -3, -3, -7, -3,
    0, 0, 7, 4, 0, -6, 0, -12,
    0, 0, 10, -3, -8, 1, -3, -7,
    -7, -7, -2, 9, 2, 0, -3, 0,
    -5, 0, 3, 7, -6, -9, -9, -6,
    7, 0, 1, -17, -2, 2, -4, -2,
    -6, 0, -5, -9, -3, -3, -3, 0,
    0, -6, -6, -2, 0, 7, 6, -2,
    -12, 0, -12, 0, -1, -4, -8, -14,
    -1, -7, -4, -7, -4, -7, 5, 0,
    0, -3, 0, -4, -1, 0, -2, -5,
    0, 3, -8, 2, 0, 0, -13, 0,
    -2, -5, -4, -2, -7, -6, -8, -5,
    0, -7, -2, -6, -2, -7, -2, 0,
    0, 1, 10, -4, 0, -7, 0, 0,
    0, -2, -4, -6, -6, -7, -10, -7,
    -4, -4, 4, 0, -3, 0, -11, -2,
    2, 4, -7, -9, -4, -8, 8, -2,
    1, -22, -5, 4, -5, -4, -9, 0,
    -7, -10, -2, -2, -3, -2, -6, -7,
    -1, 0, 0, 7, 7, -1, -15, 0,
    -13, 0, -2, 8, -8, -16, -4, -8,
    -10, -11, -10, -8, 4, 0, 0, 0,
    0, -2, 0, 0, 2, -2, 4, 1,
    -3, 4, 0, 0, -4, 0, 0, 0,
    0, 1, 1, -2, 0, 0, 0, 0,
    0, 0, -2, 0, 0, 0, 0, 3,
    7, 0, 0, -2, 0, 0, 0, 0,
    0, -1, -1, -2, 0, -2, 0, 0,
    1, 3, 0, 0, 0, 0, 3, 1,
    -1, 0, 10, 0, 5, 1, 1, -4,
    0, 4, 0, 0, 0, 3, 0, 0,
    0, 0, 4, 0, 6, 1, 7, 0,
    0, 7, 0, 7, -1, 0, 0, 0,
    0, 22, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -13, 0, -2, 3,
    0, 7, -30, 0, 20, 2, -4, -4,
    2, 2, -1, 1, -11, 0, 0, 12,
    -13, -4, 7, 0, 7, -4, -2, -9,
    4, -4, 0, 0, -16, 10, 31, 0,
    0, 0, 0, 0, 27, 0, 0, 0,
    0, 4, 0, 4, 0, -13, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -2, 0, 0, -2, -1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -1, 4, -5, 0, 0, 1,
    -2, 0, 2, 27, -4, -2, 6, 5,
    -5, 2, 0, 0, 2, 2, -4, -7,
    12, 7, 17, 0, -2, -2, 10, -1,
    4, 0, -29, 7, 0, -2, 0, -5,
    0, 0, 25, 0, 2, -4, -5, -4,
    8, 4, 3, 0, 0, 0, 0, -6,
    0, 0, 0, -5, 0, 0, 0, 0,
    -4, -1, 0, 0, 0, -4, 0, -2,
    0, -10, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -14, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, -2, 0, -2, 0, -3, 0,
    -3, 0, -5, 0, 0, 0, -3, 2,
    -2, 0, 0, -5, -2, -5, 0, 0,
    -5, 0, -2, 0, -10, 0, -4, 0,
    0, -15, -2, -9, -4, -9, 0, 0,
    -14, 0, -5, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, -4, -3,
    -2, -4, 0, 0, 0, 0, -4, 0,
    -5, 4, -4, 4, 0, -1, -5, -1,
    -3, -2, 0, -2, -1, -1, 2, -5,
    -1, 0, 0, 0, -16, -3, -6, 0,
    -9, 0, -1, -10, -1, 0, 0, -1,
    -2, 0, -1, 0, 0, 0, 2, 0,
    -2, -3, -2, -1, 4, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 9, 0, 0, 0, 0, 0, 0,
    0, -4, 0, -1, 0, 0, 0, -4,
    2, 0, 0, 0, -5, -2, -4, 0,
    0, -6, 0, -2, 0, -10, 0, 0,
    0, 0, -21, 0, -4, -9, -11, 0,
    0, -14, 0, -2, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, -3,
    -2, -1, -3, 1, 0, 0, 3, -4,
    0, 9, 9, -2, -2, -7, 2, 9,
    3, 4, -5, 2, 8, 2, 6, 4,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 14, 10, -5, -2,
    2, -2, 2, 2, 10, 1, 0, 0,
    0, 2, 0, 2, 0, 8, 0, 0,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -1, 0, 0, 0, 0, 0,
    0, 0, 0, 6, 0, 0, 0, 0,
    -14, -2, -3, -7, -9, 0, 0, -14,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -1, 0, 0,
    0, 0, 0, 0, 0, 0, 6, 0,
    0, 0, 0, -14, -2, -3, -7, -9,
    0, 0, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, 0, 0, 0, -6, 2, 0, -2,
    3, 5, 2, -7, 0, 1, -2, 2,
    0, 3, 0, 0, 0, 0, -2, 0,
    -1, -1, -4, 0, -1, -9, 0, 13,
    -2, 0, -5, 0, 0, 0, -1, -4,
    0, -2, -7, -4, -7, -3, 0, 0,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -1, 0, 0, 0, 0,
    0, 0, 0, 0, 6, 0, 0, 0,
    0, -14, -2, -3, -7, -9, 0, 0,
    -14, 0, 0, 0, 0, 0, 0, 0,
    11, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, 0, -6, -2,
    -1, 7, -2, -2, -9, 1, 2, 1,
    -1, -5, 0, 5, 0, 3, 1, 3,
    -4, -10, -2, 0, -5, -2, -5, -9,
    -8, 0, -2, -4, -2, -4, -9, -1,
    -2, 0, -1, 0, -1, 0, 3, 0,
    3, -1, 3, 0, 8, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -1, -2, -2, 0, 0, -5, 0,
    -1, 0, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -13, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, -2, -2, 0, -3,
    0, 0, 0, 0, -2, 0, 0, -3,
    -2, 2, 0, -3, -3, -1, 0, -4,
    -1, -4, -2, -2, 0, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -14, 0, 6, 0, 0, -4, 0,
    0, 0, 0, 0, -3, 0, -2, 0,
    -2, 0, -1, 0, 0, -1, 0, -6,
    0, 0, 8, -4, -7, -8, 1, 4,
    4, 1, -7, 1, 3, 1, 7, 1,
    8, -1, -6, 0, 0, -4, 0, 0,
    -7, -5, 0, 0, -4, 0, -4, -4,
    0, -3, 0, 0, -3, 0, -2, 3,
    0, -3, -7, -3, -2, 8, 0, 0,
    -1, 0, -4, 0, 0, 4, -6, 0,
    2, -2, 3, 2, 0, -8, 0, -1,
    -1, 0, -2, 4, -3, 0, 0, 0,
    -5, -2, -5, 0, -7, 0, 0, -10,
    0, 8, -2, 0, -4, 0, 0, 6,
    0, -2, 0, -2, -7, 0, -7, -2,
    2, 0, 0, 0, 0, -1, 0, 0,
    2, -3, 1, 0, 0, -2, -1, 0,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -13, 0, 4, 0, 0, -2,
    0, 0, 0, 0, 0, 0, 0, -2,
    -2, -2, 0, 0, 0, 4, 4, 6,
    0, 0, 0, 7, 0, -15, -12, 0,
    10, 7, 4, -9, 1, 8, 0, 8,
    0, 4, 2, -22, 0, -2, 9, 0,
    5, -4, 4, 0, 0, 13, 0, 0,
    0, 0, -4, 0, 0, 0, 0, -1,
    4, 0, 8, 2, 8, 0, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 61,
    .right_class_cnt     = 51,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 2,
    .bpp = 1,
    .kern_classes = 1,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t bsp_font_montserrat_14_1bpp = {
#else
lv_font_t bsp_font_montserrat_14_1bpp = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 16,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if BSP_FONT_MONTSERRAT_14_1BPP*/

