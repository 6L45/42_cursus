section .data

msg db "hello world",0

section .text

global _start

_start:
    ; write the message to the console
    mov rax, 1 ; syscall number for write
    mov rdi, 1 ; file descriptor for stdout
    mov rsi, msg ; address of the message
    mov rdx, 12 ; length of the message
    syscall ; call the kernel

    ; exit the program
    mov rax, 60 ; syscall number for exit
    xor rdi, rdi ; exit code 0
    syscall ; call the kernel

