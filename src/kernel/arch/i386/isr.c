#include <kernel/isr.h>
#include <kernel/tty.h>

static const char *exception_messages[] =
{
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "x87 Floating Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating Point Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    "Reserved"
};


void isr_handler(registers_t *regs)
{
    kprint("\n*** CPU EXCEPTION ***\n");

    if (regs->int_no < 32)
    {
        kprint("Exception: %s\n", exception_messages[regs->int_no]);
    }
    else
    {
        kprint("Unknown interrupt: %i\n", regs->int_no);
    }

    kprint("Interrupt number: %i\n", regs->int_no);
    kprint("Error code: %i\n", regs->err_code);

    kprint("EIP: ");
    kprint_hex(regs->eip);
    kprint("\n");

    kprint("CS: ");
    kprint_hex(regs->cs);
    kprint("\n");

    kprint("EFLAGS: ");
    kprint_hex(regs->eflags);
    kprint("\n");


    /*
     * For now, stop execution.
     * Later you could:
     * - kill the current process
     * - switch tasks
     * - enter a kernel debugger
     */
    for (;;)
    {
        asm volatile("hlt");
    }
}
