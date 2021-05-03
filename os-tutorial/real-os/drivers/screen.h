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
    FB_COLOR_RED        = 0x4,
    FB_COLOR_WHITE      = 0xF
} fb_color;

void clear_screen (void);
void kprint_at (char* message, int row, int col);
void kprint (char* message);
#endif // __SCREEN_H__
