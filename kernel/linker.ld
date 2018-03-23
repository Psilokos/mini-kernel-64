ENTRY(_start)

SECTIONS
{
    . = 0x100000;

    .text ALIGN(0x1000):
    {
        libboot.a:multiboot2.o(.multiboot2)
        *(.text)
        _etext = .;
        PROVIDE(etext = .);
    }

    .rodata ALIGN(0x1000):
    {
        *(.rodata)
    }

    .data ALIGN(0x1000):
    {
        *(.data)
        _edata = .;
        PROVIDE(edata = .);
    }

    .bss ALIGN(0x1000):
    {
        *(COMMON)
        *(.bss)
        _end = .;
        PROVIDE(end = .);
    }
}
