%define _SYM_SZ(sym)    (sym %+ .end - sym %+ .start)

; https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#OS-image-format

%define MULTIBOOT2_MAGIC                            0xE85250D6
%define MULTIBOOT2_ARCH_I386                        0
%define MULTIBOOT2_ARCH_MIPS                        4
%define MULTIBOOT2_HDR_LEN(hdr)                     _SYM_SZ(hdr)
%define MULTIBOOT2_CHECKSUM(magic, arch, hdr_len)   -(magic + arch + hdr_len)

%define MULTIBOOT2_TAG_TYPE_NULL                    0
%define MULTIBOOT2_TAG_TYPE_INFORMATION_REQUEST     1
%define MULTIBOOT2_TAG_TYPE_ADDRESS                 2
%define MULTIBOOT2_TAG_TYPE_ENTRY_ADDRESS           3

%define MULTIBOOT2_TAG_FLAG_REQUIRED                0
%define MULTIBOOT2_TAG_FLAG_OPTIONAL                1

%define MULTIBOOT2_TAG_SIZE(tag)                    _SYM_SZ(tag)

%macro _multiboot2_tag_const_base 3
%1 %+ .type     equ %2
%1 %+ .flags    equ %3
%1 %+ .size     equ MULTIBOOT2_TAG_SIZE(%1)
%endmacro

%macro _multiboot2_tag_const_null 5
%endmacro

%macro _multiboot2_tag_const_address 5
%1 %+ .header_addr      equ %2
%1 %+ .load_addr        equ %3
%1 %+ .load_end_addr    equ %4
%1 %+ .bss_end_addr     equ %5
%endmacro

%macro _multiboot2_tag_const_entry_address 5
%1 %+ .entry_addr   equ %2
%endmacro

%macro _multiboot2_tag_base 1
align 8
%1 %+ .start:
    dw  %1 %+ .type
    dw  %1 %+ .flags
    dd  %1 %+ .size
%endmacro

%macro _multiboot2_tag_null 1
%endmacro

%macro _multiboot2_tag_address 1
    dd  %1 %+ .header_addr
    dd  %1 %+ .load_addr
    dd  %1 %+ .load_end_addr
    dd  %1 %+ .bss_end_addr
%endmacro

%macro _multiboot2_tag_entry_address 1
    dd  %1 %+ .entry_addr
%endmacro

%macro _multiboot2_tag_end 1
%1 %+ .end:
%endmacro

%macro _multiboot2_tag 8
_multiboot2_tag_const_base      %1 %+ .%2, %3, %4
_multiboot2_tag_const_ %+ %2    %1 %+ .%2, %5, %6, %7, %8

_multiboot2_tag_base    %1 %+ .%2
_multiboot2_tag_ %+ %2  %1 %+ .%2
_multiboot2_tag_end     %1 %+ .%2
%endmacro

%define MULTIBOOT2_TAG_NULL(tags_sym)                                                           _multiboot2_tag     tags_sym,   null,           MULTIBOOT2_TAG_TYPE_NULL,           MULTIBOOT2_TAG_FLAG_REQUIRED,   0, 0, 0, 0
%define MULTIBOOT2_TAG_ADDRESS(tags_sym, header_addr, load_addr, load_end_addr, bss_end_addr)   _multiboot2_tag     tags_sym,   address,        MULTIBOOT2_TAG_TYPE_ADDRESS,        MULTIBOOT2_TAG_FLAG_OPTIONAL,   header_addr, load_addr, load_end_addr, bss_end_addr
%define MULTIBOOT2_TAG_ENTRY_ADDRESS(tags_sym, entry_addr)                                      _multiboot2_tag     tags_sym,   entry_address,  MULTIBOOT2_TAG_TYPE_ENTRY_ADDRESS,  MULTIBOOT2_TAG_FLAG_OPTIONAL,   entry_addr, 0, 0, 0
