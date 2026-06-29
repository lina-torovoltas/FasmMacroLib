; This code works only on 64-bit FreeBSD!!!

format ELF64 executable 9
include '../../../macrolib/FreeBSD/freebsd_x64.inc'
entry start



segment readable executable

start:
    mov rax, 4
    mov rdi, 1
    mov rsi, msg
    mov rdx, msg_len
    syscall

    input buffer, 128
    mov r12, rax

    mov rax, 4
    mov rdi, 1
    mov rsi, msg2
    mov rdx, msg2_len
    syscall

    mov rax, 4
    mov rdi, 1
    mov rsi, buffer
    mov rdx, r12
    syscall

    mov rax, 1
    xor rdi, rdi
    syscall



segment readable writeable

buffer rb 128
msg db "Enter text: "
msg_len = $ - msg
msg2 db "You entered: "
msg2_len = $ - msg2
