#include <stdint.h>
#include "kstatus.h"
#include "serial.h"
#include "io_port.h"

enum
{
    THR = 0,
    DLLR = 0,
    DLHR = 1,
    LCR = 3,
    LSR = 5,
};

enum
{
    LCR_DLAB = 1 << 7
};

enum
{
    LSR_EMPTY_THR = 1 << 5
};

#define MAX_BAUD_RATE   115200

static inline int check_port(int port)
{
#define check(x) port == x
    return check(COM1) || check(COM2) || check(COM3) || check(COM4);
#undef check
}

int serial_init(int port, int speed)
{
    if (!check_port(port))
        return KFAILURE;

    uint16_t dividor = MAX_BAUD_RATE / speed;
    if (!dividor)
        return KFAILURE;

    char line_ctrl;
    inb(port + LCR, line_ctrl);
    outb(port + LCR, line_ctrl | LCR_DLAB);
    outb(port + DLLR, (uint8_t)(dividor >> 0));
    outb(port + DLHR, (uint8_t)(dividor >> 8));
    outb(port + LCR, line_ctrl);

    return KSUCCESS;
}

int serial_write(int port, char const *str, size_t len)
{
    if (!check_port(port))
        return KFAILURE;

    while (len--)
    {
        char line_status;
        do
            inb(port + LSR, line_status);
        while (!(line_status & LSR_EMPTY_THR));
        outb(port + THR, *str++);
    }

    return KSUCCESS;
}
