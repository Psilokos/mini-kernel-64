kerneldir = $(top_srcdir)/kernel

SUBDIRS = boot

bin_PROGRAMS = kernel.bin

kernel_bin_SOURCES = kmain.c serial.c
kernel_bin_CFLAGS = $(AM_CFLAGS) -ffreestanding
kernel_bin_LDFLAGS = $(AM_LDFLAGS) -T $(kerneldir)/linker.ld -nostdlib -lgcc
kernel_bin_LDADD = $(AM_LDADD) boot/libboot.a
