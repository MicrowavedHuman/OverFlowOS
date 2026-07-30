#ifndef _KERNEL_SERIAL_H
#define _KERNEL_SERIAL_H
#include <C-Recreations/sysio.h>
#define COM1 0x3f8 // Com 1

int serial_init();
int serial_received();
void serial_write_string(const char *str);
void klog(const char *msg);
void serial_putchar(char c);
#endif
