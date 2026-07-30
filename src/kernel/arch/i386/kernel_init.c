#include <kernel/tty.h>
#include <kernel/serial.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/pic.h>
#include <kernel/irq.h>

void kernel_init(void)
{
    terminal_initialize();
    kprint("[Kernel] Terminal loaded.\n");
    gdt_init();

    idt_init();

    pic_remap(0x20, 0x28);

    irq_install();

    serial_init();

    asm volatile("sti");
    kprint("[Kernel] Interrupts enabled.\n");
}
