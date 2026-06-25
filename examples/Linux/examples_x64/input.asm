; This code works only on 64-bit Linux!!!

format ELF64 executable 3
include '../../../macrolib/Linux/linux_x64.inc'
entry start



segment readable executable

start:
    mov rax, 1
    mov rdi, 1
    mov rsi, msg
    mov rdx, msg_len
    syscall

    input buffer, 128
    mov r10, rax

    mov rax, 1
    mov rdi, 1
    mov rsi, msg2
    mov rdx, msg2_len
    syscall

    mov rax, 1
    mov rdi, 1
    mov rsi, buffer
    mov rdx, r10
    syscall

    mov rax, 60
    xor rdi, rdi
    syscall



segment readable writeable

buffer rb 128
msg db "Enter text: "
msg_len = $ - msg
msg2 db "You entered: "
msg2_len = $ - msg2
