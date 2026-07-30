.section .text

.extern isr_handler


/*
 * Macro for exceptions WITHOUT an automatic error code.
 *
 * CPU does not push an error code, so we push a fake one.
 */
.macro ISR_NOERR num
.global isr\num

isr\num:
    cli

    pushl $0          # fake error code
    pushl $\num       # interrupt number

    jmp isr_common
.endm


/*
 * Macro for exceptions WITH an automatic error code.
 *
 * CPU already pushed the error code.
 */
.macro ISR_ERR num
.global isr\num

isr\num:
    cli

    pushl $\num       # interrupt number

    jmp isr_common
.endm



/*
 * Exceptions 0-7 do NOT push error codes
 */
ISR_NOERR 0
ISR_NOERR 1
ISR_NOERR 2
ISR_NOERR 3
ISR_NOERR 4
ISR_NOERR 5
ISR_NOERR 6
ISR_NOERR 7


/*
 * Exceptions 8-14:
 *
 * 8  Double Fault       - error code
 * 9  Coprocessor        - no error code (old CPUs)
 * 10 Invalid TSS        - error code
 * 11 Segment Not Present- error code
 * 12 Stack Fault        - error code
 * 13 General Protection - error code
 * 14 Page Fault         - error code
 */
ISR_ERR   8
ISR_NOERR 9
ISR_ERR   10
ISR_ERR   11
ISR_ERR   12
ISR_ERR   13
ISR_ERR   14


/*
 * Exceptions 15-31
 */
ISR_NOERR 15
ISR_NOERR 16
ISR_NOERR 17
ISR_NOERR 18
ISR_NOERR 19
ISR_NOERR 20
ISR_NOERR 21
ISR_NOERR 22
ISR_NOERR 23
ISR_NOERR 24
ISR_NOERR 25
ISR_NOERR 26
ISR_NOERR 27
ISR_NOERR 28
ISR_NOERR 29
ISR_NOERR 30
ISR_NOERR 31



/*
 * Common ISR handler
 */
.global isr_common

isr_common:

    /*
     * Save general purpose registers
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
     * Load kernel data segment
     */
    mov $0x10, %ax

    mov %ax, %ds
    mov %ax, %es


    /*
     * Pass pointer to registers_t
     *
     * ESP now points at the saved register structure
     */
    push %esp

    call isr_handler

    add $4, %esp


    /*
     * Restore segment registers
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
     * int_no
     * err_code
     */
    add $8, %esp


    sti
    iret
