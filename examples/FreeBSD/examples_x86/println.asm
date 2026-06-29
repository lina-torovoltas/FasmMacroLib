; This code works only on 32-bit FreeBSD!!!

format ELF executable 9
include '../../../macrolib/FreeBSD/freebsd_x86.inc'
entry start



segment readable executable

start:
    println msg, msg_len

    mov eax, 1
    push 0 eax
    int 80h



segment readable writeable

msg db 'Test output string'
msg_len = $ - msg
