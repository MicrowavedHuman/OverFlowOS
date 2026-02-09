#!/bin/bash

BOOT_L="kernel/arch/i386/boot.s"
KERNEL_L="kernel/kernel/kernel.c"
LINKER_L="kernel/arch/i386/linker.ld"
TTY_L="kernel/arch/i386/tty.c"


i686-elf-as ${BOOT_L} -o ../build/boot.o
i686-elf-gcc -c ${TTY_L} -o ../build/tty.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I kernel/include -I kernel/arch/i386
i686-elf-gcc -c ${KERNEL_L} -o ../build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I kernel/include -I kernel/arch/i386
i686-elf-gcc -T ${LINKER_L} -o ../build/OverFlowOS -ffreestanding -O2 -nostdlib \
    ../build/boot.o ../build/kernel.o ../build/tty.o -lgcc

cd ..
cd build
./bootable_creation.sh
