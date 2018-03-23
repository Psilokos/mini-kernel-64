#ifndef IO_PORT_H
# define IO_PORT_H

# define cli()   __asm__ volatile ("cli")
# define sti()   __asm__ volatile ("sti")

# define inb(port, ret)      __asm__ volatile ("in   al, dx" : "=a"(ret) : "d"(port))
# define inw(port, ret)      __asm__ volatile ("in   ax, dx" : "=a"(ret) : "d"(port))
# define indw(port, ret)     __asm__ volatile ("in   eax, dx" : "=a"(ret) : "d"(port))

# define outb(port, value)   __asm__ volatile ("out  dx, al" : : "d"(port), "a"(value))
# define outw(port, value)   __asm__ volatile ("out  dx, ax" : : "d"(port), "a"(value))
# define outdw(port, value)  __asm__ volatile ("out  dx, eax" : : "d"(port), "a"(value))

# define io_wait()   outb(0x80, 0x0)

#endif
