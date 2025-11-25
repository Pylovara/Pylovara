BITS 64
SECTION .text
GLOBAL _start

_start:
    mov rax, 60
    mov rdi, 0
    syscall
