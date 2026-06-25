; This code works only on 64-bit Linux!!!

format ELF64 executable 3
include '../../../macrolib/Linux/linux_x64.inc'
entry start



segment readable executable

start:
    mov rax, 1
    mov rdi, 1
    mov rsi, msg1
    mov rdx, msg1_len
    syscall

    delay_ms 500

    mov rax, 1
    mov rsi, msg2
    mov rdx, msg2_len
    syscall

    mov rax, 60
    xor rdi, rdi
    syscall



segment readable writeable

msg1 db "Print number one", 0xA
msg1_len = $ - msg1

msg2 db "Print number two after pause", 0xA
msg2_len = $ - msg2
