; This code works only on 64-bit FreeBSD!!!

format ELF64 executable 9
include '../../../macrolib/FreeBSD/freebsd_x64.inc'
entry start



segment readable executable

start:
    printl 2, msg1, msg1_len
    printl 3, msg2, msg2_len

    mov rax, 1
    xor rdi, rdi
    syscall



segment readable writeable

msg1 db 'This message will be repeated two times'
msg1_len = $ - msg1

msg2 db 'This message will be repeated three times'
msg2_len = $ - msg2
