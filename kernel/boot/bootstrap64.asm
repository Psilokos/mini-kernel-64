; -----------------------------------------------------------------------------
section .text
bits 32
; -------------------------------------

global start
extern klaunch

start:
    mov     esp, stack.top
%ifdef MULTIBOOT
%elifdef MULTIBOOT2
    call    assert_multiboot2
%endif
    call    assert_cpuid
    call    assert_longmode
    call    setup_longmode
    call    enter_realm64
.end:

%ifdef MULTIBOOT
%elifdef MULTIBOOT2
assert_multiboot2:
    cmp     eax, 0x36D76289
    jne     .err
    ret
.err:
    mov     al, 1
    jmp     error
%endif

assert_cpuid:
    pushfd
    pushfd
    xor     dword [esp], 1 << 21
    popfd
    pushfd
    pop     eax
    xor     eax, [esp]
    test    eax, 1 << 21
    jz      .err
    popfd
    ret
.err:
    mov     al, 2
    jmp     error

assert_longmode:
    mov     eax, 0x80000000
    cpuid
    cmp     eax, 0x80000001
    jb      .err
    mov     eax, 0x80000001
    cpuid
    test    edx, 1 << 29
    jz      .err
    xor     al, al
    ret
.err:
    mov     eax, 3
    jmp     error

setup_longmode:
    call    init_identity_paging
; disable paging
    mov     eax, cr0
    and     eax, ~(1 << 31)
    mov     cr0, eax
; enable physical addr ext
    mov     eax, cr4
    or      eax, 1 << 5
    mov     cr4, eax
; load page map lvl 4
    mov     eax, PML4_table
    or      eax, 1 << 3
    mov     cr3, eax
; enable long mode
    mov     ecx, 0xC0000080
    rdmsr
    or      eax, 1 << 8
;   or      eax, 1 << 11
    wrmsr
; enable paging
    mov     eax, cr0
    or      eax, 1 << 31
    mov     cr0, eax
    ret

init_identity_paging:
; init PML4[0]
    mov     eax, PDP_table
    or      eax, 01011b             ; use macros
    mov     [PML4_table], eax
; init PDP[0]
    mov     eax, PD_table
    or      eax, 01011b
    mov     [PDP_table], eax
; init PD[0]
    mov     eax, PT_table
    or      eax, 01011b
    mov     [PD_table], eax
; init PT
    mov     ecx, 0x200
.loop:
    dec     ecx
    mov     eax, 0x1000
    mul     ecx
    or      eax, 01011b
    mov     [PT_table + ecx * 8], eax
    or      ecx, 0
    jnz     .loop
    ret

enter_realm64:
    lgdt    [GDT64.addr]
    call    GDT64.code:klaunch

error:
    mov     word [0xB8000], 0x0F65
    mov     word [0xB8002], 0x0F72
    mov     word [0xB8004], 0x0F72
    mov     word [0xB8006], 0x0F6F
    mov     word [0xB8008], 0x0F72
    mov     word [0xB800A], 0x0F20
    mov     byte [0xB800C], 0x0F
    add     al, '0'
    mov     [0xB800B], al
.halt:
    hlt
    jmp     .halt
; -----------------------------------------------------------------------------



; -----------------------------------------------------------------------------
section .bss
; -------------------------------------
stack: align 16
.bottom:
    resb    0x1000
.top:

align 0x1000
PML4_table:
    resb    0x1000
PDP_table:
    resb    0x1000
PD_table:
    resb    0x1000
PT_table:
    resb    0x1000
; -----------------------------------------------------------------------------



; -----------------------------------------------------------------------------
section .rodata
; -------------------------------------
GDT64:
    dq  0
.code: equ $ - GDT64
    dq  1 << 53 | 1 << 47 | 1 << 44 | 1 << 43
;.data: equ $ - GDT64
;    dq  1 << 47 | 1 << 44
.addr:
    dw  $ - GDT64 - 1
    dq  GDT64
; -----------------------------------------------------------------------------
