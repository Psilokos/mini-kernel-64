SUBDIRS = kernel

if HAVE_BOOTLOADER
endif

if HAVE_MULTIBOOT
endif

if HAVE_MULTIBOOT2
.iso:
	mkdir -p iso/boot/grub
	cp $(top_srcdir)/grub.cfg iso/boot/grub
	cp kernel/kernel.bin iso/boot
	grub-mkrescue -o os.iso iso
endif
