#!/bin/bash

BOOT_L="kernel/arch/i386/boot.s"

KERNEL_L="kernel/kernel/kernel.c"

LINKER_L="kernel/arch/i386/linker.ld"

TTY_L="kernel/arch/i386/tty.c"

INIT_L="kernel/arch/i386/kernel_init.c"

SERIAL_L="kernel/arch/i386/serial.c"

SYSIO_L="kernel/arch/i386/C-Recreations/sysio.c"

GDT_C="kernel/arch/i386/gdt.c"
GDT_S="kernel/arch/i386/gdt.s"

IDT_C="kernel/arch/i386/idt.c"
IDT_S="kernel/arch/i386/idt.s"

ISR_C="kernel/arch/i386/isr.c"
ISR_S="kernel/arch/i386/isr.s"

IRQ_C="kernel/arch/i386/irq.c"
IRQ_S="kernel/arch/i386/irq.s"

PIC_C="kernel/arch/i386/pic.c"


# -------------------------
# Assembly
# -------------------------

i686-elf-as ${BOOT_L} -o ../build/boot.o

i686-elf-as ${GDT_S} -o ../build/gdt.o

i686-elf-as ${IDT_S} -o ../build/idt_asm.o

i686-elf-as ${ISR_S} -o ../build/isr_asm.o

i686-elf-as ${IRQ_S} -o ../build/irq_asm.o



# -------------------------
# C files
# -------------------------

i686-elf-gcc -c ${TTY_L} \
    -o ../build/tty.o \
    -std=gnu99 -ffreestanding -O2 -Wall -Wextra \
    -I kernel/include -I kernel/arch/i386


i686-elf-gcc -c ${KERNEL_L} \
    -o ../build/kernel.o \
    -std=gnu99 -ffreestanding -O2 -Wall -Wextra \
    -I kernel/include -I kernel/arch/i386


i686-elf-gcc -c ${INIT_L} \
    -o ../build/init.o \
    -std=gnu99 -ffreestanding -O2 -Wall -Wextra \
    -I kernel/include -I kernel/arch/i386


i686-elf-gcc -c ${SYSIO_L} \
    -o ../build/sysio.o \
    -std=gnu99 -ffreestanding -O2 -Wall -Wextra \
    -I kernel/include -I kernel/arch/i386


i686-elf-gcc -c ${SERIAL_L} \
    -o ../build/serial.o \
    -std=gnu99 -ffreestanding -O2 -Wall -Wextra \
    -I kernel/include -I kernel/arch/i386


i686-elf-gcc -c ${GDT_C} \
    -o ../build/gdt_c.o \
    -std=gnu99 -ffreestanding -O2 -Wall -Wextra \
    -I kernel/include -I kernel/arch/i386


i686-elf-gcc -c ${IDT_C} \
    -o ../build/idt.o \
    -std=gnu99 -ffreestanding -O2 -Wall -Wextra \
    -I kernel/include -I kernel/arch/i386


i686-elf-gcc -c ${ISR_C} \
    -o ../build/isr.o \
    -std=gnu99 -ffreestanding -O2 -Wall -Wextra \
    -I kernel/include -I kernel/arch/i386


i686-elf-gcc -c ${IRQ_C} \
    -o ../build/irq.o \
    -std=gnu99 -ffreestanding -O2 -Wall -Wextra \
    -I kernel/include -I kernel/arch/i386


i686-elf-gcc -c ${PIC_C} \
    -o ../build/pic.o \
    -std=gnu99 -ffreestanding -O2 -Wall -Wextra \
    -I kernel/include -I kernel/arch/i386



# -------------------------
# Link kernel
# -------------------------

i686-elf-gcc \
    -T ${LINKER_L} \
    -o ../build/OverFlowOS \
    -ffreestanding \
    -O2 \
    -nostdlib \
    ../build/boot.o \
    ../build/init.o \
    ../build/kernel.o \
    ../build/tty.o \
    ../build/sysio.o \
    ../build/serial.o \
    ../build/gdt.o \
    ../build/gdt_c.o \
    ../build/idt_asm.o \
    ../build/idt.o \
    ../build/isr_asm.o \
    ../build/isr.o \
    ../build/irq_asm.o \
    ../build/irq.o \
    ../build/pic.o \
    -lgcc



# -------------------------
# Build ISO and run QEMU
# -------------------------

cd ..

cd build

./bootable.sh

qemu-system-i386 \
    -cdrom OverFlowOS.iso \
    -boot d \
    -display gtk \
    -serial stdio
