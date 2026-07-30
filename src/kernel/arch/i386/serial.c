#include <kernel/serial.h>

int serial_init(void)
{
    outb(COM1 + 1, 0x00); // Disable interrupts
    outb(COM1 + 3, 0x80); // Enable DLAB
    outb(COM1 + 0, 0x03); // Baud divisor low (38400)
    outb(COM1 + 1, 0x00); // Baud divisor high
    outb(COM1 + 3, 0x03); // 8 bits, no parity, one stop bit
    outb(COM1 + 2, 0xC7); // Enable FIFO
    outb(COM1 + 4, 0x0B); // Enable RTS/DSR

    // Test UART
    outb(COM1 + 4, 0x1E);
    outb(COM1 + 0, 0xAE);

    if (inb(COM1 + 0) != 0xAE)
        return 1;

    // Normal mode
    outb(COM1 + 4, 0x0F);

    return 0;
}

static int serial_ready(void)
{
    return inb(COM1 + 5) & 0x20;
}

int serial_received() {
    return inb(COM1 + 5) & 1;
}
void serial_write_string(const char *str)
{
    while (*str)
    {
        serial_putchar(*str);
        str++;
    }
}

void klog(const char *msg)
{
    serial_write_string("[KERNEL] ");
    serial_write_string(msg);
    serial_write_string("\n");
}

void serial_putchar(char c)
{
    while (!serial_ready());
    outb(COM1, c);
}
