#include <kernel/irq.h>
#include <kernel/idt.h>
#include <kernel/pic.h>
#include <kernel/tty.h>


/*
 * Install hardware IRQ handlers
 */
void irq_install(void)
{
    /*
     * IRQ0-IRQ7 -> IDT 32-39
     */
    idt_set_gate(32, (uint32_t)irq0, 0x08, 0x8E);
    idt_set_gate(33, (uint32_t)irq1, 0x08, 0x8E);
    idt_set_gate(34, (uint32_t)irq2, 0x08, 0x8E);
    idt_set_gate(35, (uint32_t)irq3, 0x08, 0x8E);
    idt_set_gate(36, (uint32_t)irq4, 0x08, 0x8E);
    idt_set_gate(37, (uint32_t)irq5, 0x08, 0x8E);
    idt_set_gate(38, (uint32_t)irq6, 0x08, 0x8E);
    idt_set_gate(39, (uint32_t)irq7, 0x08, 0x8E);


    /*
     * IRQ8-IRQ15 -> IDT 40-47
     */
    idt_set_gate(40, (uint32_t)irq8, 0x08, 0x8E);
    idt_set_gate(41, (uint32_t)irq9, 0x08, 0x8E);
    idt_set_gate(42, (uint32_t)irq10, 0x08, 0x8E);
    idt_set_gate(43, (uint32_t)irq11, 0x08, 0x8E);
    idt_set_gate(44, (uint32_t)irq12, 0x08, 0x8E);
    idt_set_gate(45, (uint32_t)irq13, 0x08, 0x8E);
    idt_set_gate(46, (uint32_t)irq14, 0x08, 0x8E);
    idt_set_gate(47, (uint32_t)irq15, 0x08, 0x8E);
}


/*
 * Called from irq.s
 */
void irq_handler(registers_t *regs)
{
    /*
     * IRQ numbers are 0-15.
     *
     * The CPU sees them as:
     *
     * IRQ0  = interrupt 32
     * IRQ1  = interrupt 33
     * ...
     */
    uint32_t irq = regs->int_no;


    switch (irq)
    {
        case 0:
            // Timer interrupt
            //kprint("Timer tick\n");
            break;

        case 1:
            // Keyboard interrupt
            uint8_t scancode = inb(0x60);
            kprint("KEY ");
            kprint_hex(scancode);
            kprint("| Keyboard IRQ\n");
            break;

        default:
            break;
    }


    /*
     * Tell the PIC we handled it.
     */
    pic_send_eoi(irq);
}
