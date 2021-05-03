#include "kernel_types.h"
#include "ports.h"
#include "screen.h"
#include "utils.h"

static inline uint8_t fb_attr_to_fg(uint8_t attr)
{
    return (attr & 0xF);
}

static inline uint8_t fb_attr_to_bg(uint8_t attr)
{
    return (attr & 0xF0) >> 4;
}

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
    *(uint8_t*)(FRAMEBUFFER_START + 2*cell + 1) = ((bg & 0xF) << 4 | (fg & 0xF));
}

static inline void set_fb (uint8_t row, uint8_t col, uint8_t data, uint8_t fg, uint8_t bg)
{
    set_fb_cell(get_fb_cell_offset(row,col),
                data,
                fg,
                bg);
}

/* this returns a cell offset */
static uint16_t get_cursor_offset (void)
{   uint8_t hi = 0;
    uint8_t lo = 0;
    port_byte_out(PORT_SCREEN_CTRL, PORT_SCREEN_CTRL_HI);
    hi = port_byte_in(PORT_SCREEN_DATA);
    port_byte_out(PORT_SCREEN_CTRL, PORT_SCREEN_CTRL_LO);
    lo = port_byte_in(PORT_SCREEN_DATA);
    return (hi << 8 | lo);
}

/* this takes a cell offset */
static void set_cursor_offset (uint32_t offset) {
    port_byte_out(PORT_SCREEN_CTRL, PORT_SCREEN_CTRL_HI);
    port_byte_out(PORT_SCREEN_DATA, (offset & 0xFF00) >> 8);
    port_byte_out(PORT_SCREEN_CTRL, PORT_SCREEN_CTRL_LO);
    port_byte_out(PORT_SCREEN_DATA, (offset & 0xFF));
}

static uint32_t get_cell_offset_row (uint16_t cell_offset)
{
    return cell_offset/MAX_COLS;
}

static uint32_t get_cell_offset_col (uint16_t cell_offset)
{
    return cell_offset - (cell_offset/MAX_COLS)*MAX_COLS;
}

static void set_cursor (uint32_t row, uint32_t col)
{
    set_cursor_offset(get_fb_cell_offset(row, col));
}

/* this returns the cell offset of next position to print */
static uint16_t print_char (char ch, int row, int col, int flags)
{
    uint8_t attr = FB_ATTR_WHITE_ON_BLACK;
    if (flags != -1) {
        attr = flags;
    }

    if (row >= MAX_ROWS || col >= MAX_COLS) {
        /* display an E in the last row, col, in red bg */
        set_fb(MAX_ROWS-1, MAX_COLS-1,
               'E',
               FB_COLOR_RED,
               FB_COLOR_WHITE);
        return get_fb_cell_offset(row, col);
    }

    int r = row;
    int c = col;
    if (row < 0 || col < 0) {
        /* fetch the current row & col */
        uint16_t cell_offset = get_cursor_offset();
        r = get_cell_offset_row(cell_offset);
        c = get_cell_offset_col(cell_offset);
    }

    uint16_t next_offset = 0;
    if (ch == '\n') {
        next_offset = get_fb_cell_offset(r + 1, 0);
    } else {
        set_fb(r, c,
               ch,
               fb_attr_to_fg(attr),
               fb_attr_to_bg(attr));
        next_offset = get_fb_cell_offset(r, c) + 1;
    }

    /* handle screen scroll */
    if (next_offset >= MAX_COLS * MAX_ROWS) {
        memory_move((uint8_t*)FRAMEBUFFER_START,                    /* copy to the start of framebuffer memory */
                    (uint8_t*)(FRAMEBUFFER_START + 2 * MAX_COLS),   /* copy from the second line of the screen */
                    2 * (MAX_ROWS-1) * MAX_COLS);
        /* clear last row of the framebuffer */
        for (int i = 0 ; i < MAX_COLS; ++i) {
            *(uint8_t*)(FRAMEBUFFER_START + 2 * (MAX_ROWS-1) * MAX_COLS + 2 * i) = ' ';
            *(uint8_t*)(FRAMEBUFFER_START + 2 * (MAX_ROWS-1) * MAX_COLS + 2 * i + 1) = FB_ATTR_WHITE_ON_BLACK;
        }
        next_offset = get_fb_cell_offset(MAX_ROWS - 1, 0);
    }
    set_cursor_offset(next_offset);
    return next_offset;
}

void clear_screen (void)
{
    /* low level api to clear all screen */
    for (uint32_t r = 0; r < MAX_ROWS; ++r) {
        for (uint32_t c = 0 ; c < MAX_COLS; ++c) {
            set_fb(r, c,
                   ' ',
                   FB_COLOR_WHITE,
                   FB_COLOR_BLACK);
        }
    }
    /* set cursor position at 0,0 */
    set_cursor(0, 0);
}

void kprint_at (char* message, int row, int col)
{
    while (*message) {
        uint16_t next_offset = print_char(*message,
                                          row, col,
                                          -1);
        message++;
        row = get_cell_offset_row(next_offset);
        col = get_cell_offset_col(next_offset);
    }
}

void kprint (char* str)
{
    kprint_at(str, -1, -1);
}

