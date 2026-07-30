#ifndef KERNEL_PIC_H
#define KERNEL_PIC_H

#include <stdint.h>

/*
 * Remap the PIC interrupt vectors.
 *
 * Master PIC:
 *   IRQ0-IRQ7  -> offset1
 *
 * Slave PIC:
 *   IRQ8-IRQ15 -> offset2
 */
void pic_remap(int offset1, int offset2);


/*
 * Tell the PIC that an interrupt has been handled.
 *
 * irq 0-7  = master PIC
 * irq 8-15 = slave PIC
 */
void pic_send_eoi(uint8_t irq);

#endif
