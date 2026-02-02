#!/bin/bash
mkdir -p isodir/boot/grub
cp OverFlowOS isodir/boot/OverFlowOS
cp grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o OverFlowOS.iso isodir
