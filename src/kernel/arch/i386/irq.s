.section .text

.extern irq_handler


/*
 * IRQ without error code.
 *
 * Hardware interrupts never push an error code,
 * so we only push the IRQ number.
 */
.macro IRQ num

.global irq\num

irq\num:
    cli

    pushl $0              # fake error code
    pushl $\num           # IRQ number

    jmp irq_common

.endm



/*
 * IRQ0-IRQ15
 */
IRQ 0
IRQ 1
IRQ 2
IRQ 3
IRQ 4
IRQ 5
IRQ 6
IRQ 7
IRQ 8
IRQ 9
IRQ 10
IRQ 11
IRQ 12
IRQ 13
IRQ 14
IRQ 15



.global irq_common

irq_common:

    /*
     * Save general registers
     */
    pusha


    /*
     * Save segment registers
     */
    push %ds
    push %es
    push %fs
    push %gs


    /*
     * Switch to kernel data segment
     */
    mov $0x10, %ax

    mov %ax, %ds
    mov %ax, %es


    /*
     * Pass registers_t*
     */
    push %esp

    call irq_handler

    add $4, %esp


    /*
     * Restore segments
     */
    pop %gs
    pop %fs
    pop %es
    pop %ds


    /*
     * Restore registers
     */
    popa


    /*
     * Remove:
     *
     * irq number
     * fake error code
     */
    add $8, %esp


    sti
    iret
