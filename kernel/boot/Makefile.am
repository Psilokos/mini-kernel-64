kernel_bootdir = $(top_srcdir)/kernel/boot

noinst_LIBRARIES = libboot.a

libboot_a_SOURCES =

if HAVE_ARCH32
libboot_a_SOURCES += bootstrap32.asm
endif
if HAVE_ARCH64
libboot_a_SOURCES += bootstrap64.asm realm64.asm
endif

if HAVE_BOOTLOADER
libboot_a_SOURCES +=
endif
if HAVE_MULTIBOOT
libboot_a_SOURCES +=
endif
if HAVE_MULTIBOOT2
libboot_a_SOURCES += multiboot/multiboot2.asm
endif

NASMFLAGS += -I $(kernel_bootdir)/
if HAVE_MULTIBOOT2
NASMFLAGS += -I $(kernel_bootdir)/multiboot/
NASMFLAGS += -D MULTIBOOT2
endif

.asm.o:
	$(NASM) $(NASMFLAGS) -o $@ $<
