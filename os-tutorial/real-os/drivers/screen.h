#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "kernel_types.h"

#define FRAMEBUFFER_START   (0xB8000)
#define MAX_ROWS            (25)
#define MAX_COLS            (80)
#define PORT_SCREEN_CTRL    (0x3D4)
#define PORT_SCREEN_CTRL_HI (14)
#define PORT_SCREEN_CTRL_LO (15)
#define PORT_SCREEN_DATA    (0x3D5)

/* FB COLORS */
typedef enum {
    FB_COLOR_BLACK      = 0x0,
    FB_COLOR_BLUE       = 0x1,
    FB_COLOR_GREEN      = 0x2,
    FB_COLOR_CYAN       = 0x3,
    FB_COLOR_RED        = 0x4,
    FB_COLOR_DARK_GREY  = 0x8,
    FB_COLOR_WHITE      = 0xF
} fb_color;

#define FB_ATTR_WHITE_ON_BLACK ((FB_COLOR_BLACK << 4) | FB_COLOR_WHITE)
#define FB_ATTR_GREEN_ON_DARK_GREY ((FB_COLOR_DARK_GREY << 4) | FB_COLOR_GREEN)
#define FB_ATTR_RED_ON_BLACK ((FB_COLOR_BLACK << 4) | FB_COLOR_RED)

void clear_screen (void);
void kprint_at (char* message, int row, int col);
void kprint (char* message);
void kprint_dec (int val);
#endif // __SCREEN_H__
