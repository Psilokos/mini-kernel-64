; -----------------------------------------------------------------------------
section .multiboot2
; -------------------------------------

%include "multiboot2.inc"

extern _edata
extern _end

multiboot2_header:
.magic      equ MULTIBOOT2_MAGIC
.arch       equ MULTIBOOT2_ARCH_I386
.hdr_len    equ MULTIBOOT2_HDR_LEN(multiboot2_header)
.checksum   equ MULTIBOOT2_CHECKSUM(.magic, .arch, .hdr_len)

align 8
.start:

    dd  .magic
    dd  .arch
    dd  .hdr_len
    dd  .checksum

MULTIBOOT2_TAG_NULL(.tags)

.end:
; -----------------------------------------------------------------------------

%include "_start.inc"
