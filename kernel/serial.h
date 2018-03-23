#ifndef SERIAL_H
# define SERIAL_H

# include <stddef.h>

enum
{
    COM1 = 0x3F8,
    COM2 = 0x2F8,
    COM3 = 0x3E8,
    COM4 = 0x2E8
};

int serial_init(int port, int speed);
int serial_write(int port, char const *s, size_t len);

#endif
