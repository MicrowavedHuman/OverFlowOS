#include <kernel/tty.h>
#include <stdio.h>

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

/* Hardware text mode color constants. */
enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg)
{
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
    return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

#define VGA_WIDTH   80
#define VGA_HEIGHT  25
#define VGA_MEMORY  0xB8000

void terminal_scroll(void)
{
    //////////////////
    // Needs major fix
    /////////////////
    for(size_t y = 0; y < VGA_HEIGHT; y++){
        for(size_t x = 0; x < VGA_WIDTH; x++){
            // Hopefully this works, it should just copy over the characters
            const size_t src_index = y * VGA_WIDTH + x;
            const size_t dest_index = (y-1) * VGA_WIDTH + x;
            terminal_buffer[dest_index] = terminal_buffer[src_index];
        }
    }

    // Clear it?
    const uint16_t blank = vga_entry(' ', terminal_color);
    for (size_t x = 0; x < VGA_WIDTH; x++){
        terminal_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = blank;
    }

    // Check the cursor and go up
    terminal_row = VGA_HEIGHT - 1;
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

void kernel_main(void)
{
    int succesfully_booted = 1;
    terminal_initialize();
    terminal_writestring("OverFlowOS Booting!\n");

    /* Set up rest of important stuff. */
    if(succesfully_booted == 1){
        print_logo();
    } else {
        terminal_writestring("OverFlowOS ran into an Issue during Boot.\n");
    }
}
