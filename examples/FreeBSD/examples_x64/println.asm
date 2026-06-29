; This code works only on 64-bit FreeBSD!!!

format ELF64 executable 9
include '../../../macrolib/FreeBSD/freebsd_x64.inc'
entry start



segment readable executable

start:
    println msg, msg_len

    mov rax, 1
    xor rdi, rdi
    syscall



segment readable writeable

msg db 'Test output string'
msg_len = $ - msg
