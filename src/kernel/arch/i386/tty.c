#include <kernel/tty.h>
#include "vga.h"
#include <stdarg.h>
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static uint16_t* const VGA_MEMORY = (uint16_t*) 0xB8000;
static size_t terminal_row;
static size_t terminal_column;
static uint8_t terminal_color;
static uint16_t* terminal_buffer;
void terminal_initialize(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = VGA_MEMORY;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}
void terminal_setcolor(uint8_t color) {
    terminal_color = color;
}
void terminal_putentryat(unsigned char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}
size_t strlen(const char* str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}
void terminal_scroll(void)
{
    for (size_t y = 1; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            size_t src_index = y * VGA_WIDTH + x;
            size_t dest_index = (y - 1) * VGA_WIDTH + x;

            terminal_buffer[dest_index] = terminal_buffer[src_index];
        }
    }

    uint16_t blank = vga_entry(' ', terminal_color);

    for (size_t x = 0; x < VGA_WIDTH; x++)
    {
        terminal_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = blank;
    }

    terminal_row = VGA_HEIGHT - 1;
}
void terminal_putchar(char c) {
    unsigned char uc = c;
    if(c == '\n'){
        if (terminal_row+1 != VGA_HEIGHT){
            terminal_row += 1;
            terminal_column = 0;
        } else {
            terminal_scroll();
            terminal_column = 0;
        }
    } else
    {
        terminal_putentryat(uc, terminal_color, terminal_column, terminal_row);
        if (++terminal_column == VGA_WIDTH) {
            terminal_column = 0;
            if (terminal_row == VGA_HEIGHT)
            {
                terminal_scroll();
            }
        }
    }
}
void terminal_write(const char* data, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        terminal_putchar(data[i]);
    }
}
void terminal_writestring(const char* data) {
    terminal_write(data, strlen(data));
}

void print_logo()
{
    terminal_writestring("OverFlowOS has Booted.\n");
    terminal_setcolor(VGA_COLOR_LIGHT_BLUE);
    terminal_writestring("____________________________________________________________________________\n");
    terminal_setcolor(VGA_COLOR_MAGENTA);
    terminal_writestring("|");
    terminal_writestring("   ___  _      _ ___  ___  ____  _      ___   _    _    _ |   ___    ___  ");
    terminal_writestring("|\n");
    terminal_setcolor(VGA_COLOR_WHITE);
    terminal_writestring("|");
    terminal_writestring("  /   \\  \\    /  |    |__\\ |     |     /   \\  |    |    | |  /   \\  /     ");
    terminal_writestring("|\n");
    terminal_writestring("| |     |  \\  /   |--  | \\  |---  |    |     |  \\  / \\  /  | |     | |___  ");
    terminal_writestring("|\n");
    terminal_setcolor(VGA_COLOR_MAGENTA);
    terminal_writestring("|");
    terminal_writestring("  \\___/    \\/    |__  |  \\ |     |___  \\___/    \\/   \\/   |  \\___/   ___/ ");
    terminal_writestring("|\n");
    terminal_setcolor(VGA_COLOR_LIGHT_BLUE);
    terminal_writestring("|__________________________________________________________________________|\n");
}

void kprint(const char* str, ...)
{
    /*
     * %i = int
     * %d = dec
     * %c = char
     */
    va_list args;

    va_start(args, str);

    int in_flag = 0;
    size_t strlength = strlen(str);
    for(size_t i=0; i < strlength; i++)
    {
        if(str[i] == '%')
        {
            in_flag = 1;
        }
        else if(in_flag == 1)
        {
            in_flag = 0;
            if(str[i] == 'i')
            {
                kprint_int(va_arg(args, int));
            } else if(str[i] == 'd')
            {
                float plc = va_arg(args, double);
                kprint_dec(plc);
            } else if(str[i] == 'c')
            {
                char c = va_arg(args, int);
                kprint_char(c);
            }
        } else
        {
            terminal_putchar(str[i]);
        }
    }
}
void kprint_char(const char chr)
{
    terminal_putchar(chr);
}
void kprint_int(const int value)
{
    kprint_dec(value);
}

void kprint_hex(uint32_t value)
{
    char *hex = "0123456789ABCDEF";

    terminal_writestring("0x");

    for(int i = 7; i >= 0; i--)
    {
        terminal_putchar(hex[(value >> (i * 4)) & 0xF]);
    }
}

void kprint_dec(int value)
{
    char buffer[32];
    int i = 0;

    if (value == 0)
    {
        terminal_putchar('0');
        return;
    }

    // Handle negative numbers
    if (value < 0)
    {
        terminal_putchar('-');
        value = -value;
    }

    // Convert digits into reverse order
    while (value > 0)
    {
        buffer[i++] = '0' + (value % 10);
        value /= 10;
    }

    // Print them backwards
    while (i > 0)
    {
        terminal_putchar(buffer[--i]);
    }
}
