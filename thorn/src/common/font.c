#include "common/font.h"

/* From https://github.com/dhepper/font8x8/blob/master/font8x8_block.h */
const unsigned long long int * font (int c) {
    static const char f[128][FONT_SIZE] = {
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+0000 (nul)
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+0001
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+0002
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+0003
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+0004
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+0005
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+0006
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+0007
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+0008
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+0009
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+000A
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+000B
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+000C
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+000D
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+000E
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+000F
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+0010
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+0011
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+0012
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+0013
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+0014
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+0015
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+0016
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+0017
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+0018
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+0019
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+001A
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+001B
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+001C
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+001D
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+001E
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+001F
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+0020 (space)
            {0x18, 0x3C, 0x3C, 0x18, 0x18, 0x00, 0x18, 0x00},// U+0021 (!)
            {0x36, 0x36, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+0022 (")
            {0x36, 0x36, 0x7F, 0x36, 0x7F, 0x36, 0x36, 0x00},// U+0023 (#)
            {0x0C, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x0C, 0x00},// U+0024 ($)
            {0x00, 0x63, 0x33, 0x18, 0x0C, 0x66, 0x63, 0x00},// U+0025 (%)
            {0x1C, 0x36, 0x1C, 0x6E, 0x3B, 0x33, 0x6E, 0x00},// U+0026 (&)
            {0x06, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00},// U+0027 (')
            {0x18, 0x0C, 0x06, 0x06, 0x06, 0x0C, 0x18, 0x00},// U+0028 (()
            {0x06, 0x0C, 0x18, 0x18, 0x18, 0x0C, 0x06, 0x00},// U+0029 ())
            {0x00, 0x66, 0x3C, 0xFF, 0x3C, 0x66, 0x00, 0x00},// U+002A (*)
            {0x00, 0x0C, 0x0C, 0x3F, 0x0C, 0x0C, 0x00, 0x00},// U+002B (+)
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x06},// U+002C (,)
            {0x00, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00},// U+002D (-)
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x00},// U+002E (.)
            {0x60, 0x30, 0x18, 0x0C, 0x06, 0x03, 0x01, 0x00},// U+002F (/)
            {0x3E, 0x63, 0x73, 0x7B, 0x6F, 0x67, 0x3E, 0x00},// U+0030 (0)
            {0x0C, 0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x3F, 0x00},// U+0031 (1)
            {0x1E, 0x33, 0x30, 0x1C, 0x06, 0x33, 0x3F, 0x00},// U+0032 (2)
            {0x1E, 0x33, 0x30, 0x1C, 0x30, 0x33, 0x1E, 0x00},// U+0033 (3)
            {0x38, 0x3C, 0x36, 0x33, 0x7F, 0x30, 0x78, 0x00},// U+0034 (4)
            {0x3F, 0x03, 0x1F, 0x30, 0x30, 0x33, 0x1E, 0x00},// U+0035 (5)
            {0x1C, 0x06, 0x03, 0x1F, 0x33, 0x33, 0x1E, 0x00},// U+0036 (6)
            {0x3F, 0x33, 0x30, 0x18, 0x0C, 0x0C, 0x0C, 0x00},// U+0037 (7)
            {0x1E, 0x33, 0x33, 0x1E, 0x33, 0x33, 0x1E, 0x00},// U+0038 (8)
            {0x1E, 0x33, 0x33, 0x3E, 0x30, 0x18, 0x0E, 0x00},// U+0039 (9)
            {0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x00},// U+003A (:)
            {0x00, 0x0C, 0x0C, 0x00, 0x00, 0x0C, 0x0C, 0x06},// U+003B (//)
            {0x18, 0x0C, 0x06, 0x03, 0x06, 0x0C, 0x18, 0x00},// U+003C (<)
            {0x00, 0x00, 0x3F, 0x00, 0x00, 0x3F, 0x00, 0x00},// U+003D (=)
            {0x06, 0x0C, 0x18, 0x30, 0x18, 0x0C, 0x06, 0x00},// U+003E (>)
            {0x1E, 0x33, 0x30, 0x18, 0x0C, 0x00, 0x0C, 0x00},// U+003F (?)
            {0x3E, 0x63, 0x7B, 0x7B, 0x7B, 0x03, 0x1E, 0x00},// U+0040 (@)
            {0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00},// U+0041 (A)
            {0x3F, 0x66, 0x66, 0x3E, 0x66, 0x66, 0x3F, 0x00},// U+0042 (B)
            {0x3C, 0x66, 0x03, 0x03, 0x03, 0x66, 0x3C, 0x00},// U+0043 (C)
            {0x1F, 0x36, 0x66, 0x66, 0x66, 0x36, 0x1F, 0x00},// U+0044 (D)
            {0x7F, 0x46, 0x16, 0x1E, 0x16, 0x46, 0x7F, 0x00},// U+0045 (E)
            {0x7F, 0x46, 0x16, 0x1E, 0x16, 0x06, 0x0F, 0x00},// U+0046 (F)
            {0x3C, 0x66, 0x03, 0x03, 0x73, 0x66, 0x7C, 0x00},// U+0047 (G)
            {0x33, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x33, 0x00},// U+0048 (H)
            {0x1E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},// U+0049 (I)
            {0x78, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E, 0x00},// U+004A (J)
            {0x67, 0x66, 0x36, 0x1E, 0x36, 0x66, 0x67, 0x00},// U+004B (K)
            {0x0F, 0x06, 0x06, 0x06, 0x46, 0x66, 0x7F, 0x00},// U+004C (L)
            {0x63, 0x77, 0x7F, 0x7F, 0x6B, 0x63, 0x63, 0x00},// U+004D (M)
            {0x63, 0x67, 0x6F, 0x7B, 0x73, 0x63, 0x63, 0x00},// U+004E (N)
            {0x1C, 0x36, 0x63, 0x63, 0x63, 0x36, 0x1C, 0x00},// U+004F (O)
            {0x3F, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x0F, 0x00},// U+0050 (P)
            {0x1E, 0x33, 0x33, 0x33, 0x3B, 0x1E, 0x38, 0x00},// U+0051 (Q)
            {0x3F, 0x66, 0x66, 0x3E, 0x36, 0x66, 0x67, 0x00},// U+0052 (R)
            {0x1E, 0x33, 0x07, 0x0E, 0x38, 0x33, 0x1E, 0x00},// U+0053 (S)
            {0x3F, 0x2D, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},// U+0054 (T)
            {0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3F, 0x00},// U+0055 (U)
            {0x33, 0x33, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00},// U+0056 (V)
            {0x63, 0x63, 0x63, 0x6B, 0x7F, 0x77, 0x63, 0x00},// U+0057 (W)
            {0x63, 0x63, 0x36, 0x1C, 0x1C, 0x36, 0x63, 0x00},// U+0058 (X)
            {0x33, 0x33, 0x33, 0x1E, 0x0C, 0x0C, 0x1E, 0x00},// U+0059 (Y)
            {0x7F, 0x63, 0x31, 0x18, 0x4C, 0x66, 0x7F, 0x00},// U+005A (Z)
            {0x1E, 0x06, 0x06, 0x06, 0x06, 0x06, 0x1E, 0x00},// U+005B ([)
            {0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x40, 0x00},// U+005C (\)
            {0x1E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1E, 0x00},// U+005D (])
            {0x08, 0x1C, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00},// U+005E (^)
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF},// U+005F (_)
            {0x0C, 0x0C, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00},// U+0060 (`)
            {0x00, 0x00, 0x1E, 0x30, 0x3E, 0x33, 0x6E, 0x00},// U+0061 (a)
            {0x07, 0x06, 0x06, 0x3E, 0x66, 0x66, 0x3B, 0x00},// U+0062 (b)
            {0x00, 0x00, 0x1E, 0x33, 0x03, 0x33, 0x1E, 0x00},// U+0063 (c)
            {0x38, 0x30, 0x30, 0x3e, 0x33, 0x33, 0x6E, 0x00},// U+0064 (d)
            {0x00, 0x00, 0x1E, 0x33, 0x3f, 0x03, 0x1E, 0x00},// U+0065 (e)
            {0x1C, 0x36, 0x06, 0x0f, 0x06, 0x06, 0x0F, 0x00},// U+0066 (f)
            {0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x1F},// U+0067 (g)
            {0x07, 0x06, 0x36, 0x6E, 0x66, 0x66, 0x67, 0x00},// U+0068 (h)
            {0x0C, 0x00, 0x0E, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},// U+0069 (i)
            {0x30, 0x00, 0x30, 0x30, 0x30, 0x33, 0x33, 0x1E},// U+006A (j)
            {0x07, 0x06, 0x66, 0x36, 0x1E, 0x36, 0x67, 0x00},// U+006B (k)
            {0x0E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x1E, 0x00},// U+006C (l)
            {0x00, 0x00, 0x33, 0x7F, 0x7F, 0x6B, 0x63, 0x00},// U+006D (m)
            {0x00, 0x00, 0x1F, 0x33, 0x33, 0x33, 0x33, 0x00},// U+006E (n)
            {0x00, 0x00, 0x1E, 0x33, 0x33, 0x33, 0x1E, 0x00},// U+006F (o)
            {0x00, 0x00, 0x3B, 0x66, 0x66, 0x3E, 0x06, 0x0F},// U+0070 (p)
            {0x00, 0x00, 0x6E, 0x33, 0x33, 0x3E, 0x30, 0x78},// U+0071 (q)
            {0x00, 0x00, 0x3B, 0x6E, 0x66, 0x06, 0x0F, 0x00},// U+0072 (r)
            {0x00, 0x00, 0x3E, 0x03, 0x1E, 0x30, 0x1F, 0x00},// U+0073 (s)
            {0x08, 0x0C, 0x3E, 0x0C, 0x0C, 0x2C, 0x18, 0x00},// U+0074 (t)
            {0x00, 0x00, 0x33, 0x33, 0x33, 0x33, 0x6E, 0x00},// U+0075 (u)
            {0x00, 0x00, 0x33, 0x33, 0x33, 0x1E, 0x0C, 0x00},// U+0076 (v)
            {0x00, 0x00, 0x63, 0x6B, 0x7F, 0x7F, 0x36, 0x00},// U+0077 (w)
            {0x00, 0x00, 0x63, 0x36, 0x1C, 0x36, 0x63, 0x00},// U+0078 (x)
            {0x00, 0x00, 0x33, 0x33, 0x33, 0x3E, 0x30, 0x1F},// U+0079 (y)
            {0x00, 0x00, 0x3F, 0x19, 0x0C, 0x26, 0x3F, 0x00},// U+007A (z)
            {0x38, 0x0C, 0x0C, 0x07, 0x0C, 0x0C, 0x38, 0x00},// U+007B ({)
            {0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x00},// U+007C (|)
            {0x07, 0x0C, 0x0C, 0x38, 0x0C, 0x0C, 0x07, 0x00},// U+007D (})
            {0x6E, 0x3B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},// U+007E (~)
            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // U+007F
    };
    return (unsigned long long int *) f[c];
}

void printc_location (point_t point, char c) {
    unsigned char const * bitmap = (unsigned char const *) font (c);
    for (int i = 0; i < FONT_SIZE; i++) {
        for (int j = 0; j < FONT_SIZE; j++) {
            bool is_on = bitmap[i] & (1 << j);

            point_t _point;
            for (int k = 0; k < FONT_FACTOR; k++) {
                for (int h = 0; h < FONT_FACTOR; h++) {
                    _point.x = point.x + j * FONT_FACTOR + k;
                    _point.y = point.y + i * FONT_FACTOR + h;
                    drawpx (_point, is_on ? font_fg : font_bg);
                }
            }
        }
    }
}

void printc (char c) {
    // Handle special characters, print otherwise
    switch (c) {
        case '\r':// Reset cursor to beginning of line
            cursor.x = 0;
            break;
        case '\n':// Move cursor to next line
            cursor.y += FONT_REAL_HEIGHT;
            break;
        case '\t':// Print minimum one space, then align forwards to tab grid
            cursor.x += FONT_TAB_REAL_WIDTH - cursor.x % (FONT_TAB_REAL_WIDTH);
            break;
        default:// Print character and update cursor
            // TODO dynamically deal with unprintable characters (i.e., check if bitmap is all '0')
            printc_location (cursor, c);
            cursor.x += FONT_REAL_WIDTH;
    }

    // If next printed char overflowed screen width move cursor to beginning of next line
    if (cursor.x + FONT_REAL_WIDTH >= get_max_width ()) {
        cursor.x = 0;
        cursor.y += FONT_REAL_HEIGHT;
    }
    // If next line would overflow screen height (ignoring line spacing) move to beginning of screen
    if (cursor.y + FONT_REAL_WIDTH - FONT_SPACING >= get_max_height ()) {
#ifdef FONT_SCROLLBACK
        cursor.y -= FONT_SB_LINES * FONT_REAL_HEIGHT;
        unsigned int remove_size = FONT_SB_LINES * FONT_REAL_HEIGHT * get_fb_info ()->pitch;
        unsigned int scroll_size = get_fb_info ()->fb_size - remove_size;
        memcpy ((ptr_t) get_fb (), (ptr_t) get_fb () + remove_size, scroll_size);
        memzero ((ptr_t) get_fb () + scroll_size, remove_size);
#else
        // TODO clear framebuffer here...?
        cursor.y = 0;
#endif
    }
}

void font_set_normal (void) {
    font_fg = font_normal_fg;
}
void font_set_error (void) {
    font_fg = font_error_fg;
}

void putc_screen (void * p, char c) {
    printc (c);
}
