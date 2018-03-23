#include <stdint.h>
#include "serial.h"

void kmain(void)
{
    if (serial_init(COM1, 38400))
    {
        *((uint16_t *)0xB8000) = 0x2A | (7 | 0 << 4) << 8;
        return;
    }

    char test[] = "Hello kworld!\n";
    serial_write(COM1, test, sizeof(test) / sizeof(char));
}
