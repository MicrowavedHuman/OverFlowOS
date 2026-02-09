#include <kernel/tty.h>
#include <vga.h>

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

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
    /* Initialize terminal interface */
    terminal_initialize();

    /* Newline support is left as an exercise. */
    terminal_writestring("OverFlowOS Booting!\n");

    /* Set up rest of important stuff. */


    if(succesfully_booted == 1){
        print_logo();
    } else {
        terminal_writestring("OverFlowOS ran into an Issue during Boot.\n");
    }
}
