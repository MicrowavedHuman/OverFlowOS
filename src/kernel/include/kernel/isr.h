#ifndef KERNEL_ISR_H
#define KERNEL_ISR_H

#include <stdint.h>

/*
 * Register state pushed by isr.s
 *
 * The order must match the order in assembly.
 */
typedef struct registers
{
    // Pushed manually by our ISR stub
    uint32_t gs;
    uint32_t fs;
    uint32_t es;
    uint32_t ds;

    // Pushed by pusha
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;

    // Interrupt information
    uint32_t int_no;
    uint32_t err_code;

    // Pushed by the CPU automatically
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
    uint32_t useresp;
    uint32_t ss;

} registers_t;


/*
 * Called from the assembly interrupt handler.
 */
void isr_handler(registers_t *regs);


/*
 * ISR stubs from isr.s
 */
extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);

#endif
