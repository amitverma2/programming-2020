#include "kernel_types.h"
#include "ports.h"
#include "screen.h"

static inline uint32_t get_fb_cell_offset (uint32_t row, uint32_t col) {
    return col + MAX_COLS*row;
}

static inline uint16_t get_fb_mem_offset (uint32_t row, uint32_t col) {
    return 2 * get_fb_cell_offset(row, col);
}

static inline uint8_t* get_fb_loc (uint32_t row, uint32_t col) {
    return (uint8_t*)(FRAMEBUFFER_START) + get_fb_mem_offset(row, col);
}

static inline void set_fb_cell (uint32_t cell, uint8_t data, uint8_t fg, uint8_t bg)
{
    *(uint8_t*)(FRAMEBUFFER_START + 2*cell) = data;
    *(uint8_t*)(FRAMEBUFFER_START + 2*cell + 1) = (fg & 0xF) << 4 | (bg & 0xF);
}

static inline void set_fb (uint8_t row, uint8_t col, uint8_t data, uint8_t fg, uint8_t bg)
{
    set_fb_cell(get_fb_cell_offset(row,col),
                data,
                fg,
                bg);
}

static uint16_t get_cursor_offset (void)
{   uint8_t hi = 0;
    uint8_t lo = 0;
    port_byte_out(PORT_SCREEN_CTRL, PORT_SCREEN_CTRL_HI);
    hi = port_byte_in(PORT_SCREEN_DATA);
    port_byte_out(PORT_SCREEN_CTRL, PORT_SCREEN_CTRL_LO);
    lo = port_byte_in(PORT_SCREEN_DATA);
    return (hi << 8 | lo);
}

static void set_cursor_offset (uint32_t offset) {
    port_byte_out(PORT_SCREEN_CTRL, PORT_SCREEN_CTRL_HI);
    port_byte_out(PORT_SCREEN_DATA, (offset & 0xFF00) >> 8);
    port_byte_out(PORT_SCREEN_CTRL, PORT_SCREEN_CTRL_LO);
    port_byte_out(PORT_SCREEN_DATA, (offset & 0xFF));
}

static void set_cursor (uint32_t row, uint32_t col)
{
    set_cursor_offset(get_fb_cell_offset(row, col));
}

void clear_screen (void)
{
    /* low level api to clear all screen */
    for (uint32_t r = 0; r < MAX_ROWS; ++r) {
        for (uint32_t c = 0 ; c < MAX_COLS; ++c) {
            set_fb(r, c,
                   ' ',
                   FB_COLOR_BLACK,
                   FB_COLOR_WHITE);
        }
    }
    /* set cursor position at 0,0 */
    set_cursor(0, 0);
}

void kprint_at (char* message, int row, int col)
{
    uint32_t r = 0;
    uint32_t c = 0;

    /* find starting position */
    if (col < 0 || row < 0) {
        uint16_t cursor_pos = get_cursor_offset();
        r = cursor_pos/MAX_COLS;
        c = cursor_pos - r*MAX_COLS;
    } else {
        r = (uint32_t)row;
        c = (uint32_t)col;
    }

    /* print the message starting at r, c */
    while (*message) {
        set_fb(r, c,
               (uint8_t)*message,
               FB_COLOR_BLACK,
               FB_COLOR_WHITE);
        message++;
        c++;
        if (c >= MAX_COLS) { c = 0; r++; }
        if (r >= MAX_ROWS) {
            /* todo: screen needs scrolling */
        }
        set_cursor(r, c);
    }
}

void kprint (char* str)
{
    kprint_at(str, -1, -1);
}

