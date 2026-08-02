#include <kernel/tty.h>
#include <vga.h>

#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif

void kernel_main(void)
{
    /* Newline support is left as an exercise. */
    terminal_writestring("OverFlowOS Booting!\n");
    print_logo();
    kprint("System online in %i.", 10);
    while 1
    {
        asm volatile("hlt");
    }
}
