BITS 64
DEFAULT REL

section .text
global efi_main
extern MCS_SYSTEM

efi_main:
    call MCS_SYSTEM
.hang:
    jmp .hang
