#ifndef _KERNEL_TTY_H
#define _KERNEL_TTY_H

#include <stddef.h>
#include <C-Recreations/sysio.h>

#include <stdint.h>
void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void terminal_scroll(void);
void print_logo();
size_t strlen(const char* str);
void kprint(const char* str, ...);
void kprint_char(const char chr);
void kprint_int(const int x);
void kprint_dec(int value);
void kprint_hex(uint32_t value);
#endif
