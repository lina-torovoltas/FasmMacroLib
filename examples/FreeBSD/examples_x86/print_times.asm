; This code works only on 32-bit FreeBSD!!!

format ELF executable 9
include '../../../macrolib/FreeBSD/freebsd_x86.inc'
entry start



segment readable executable

start:
    printtim 2, msg1, msg1_len
    printtim 3, msg2, msg2_len

    mov eax, 1
    push 0
    push eax
    int 0x80



segment readable writeable

msg1 db 'This message will be repeated two times', 10
msg1_len = $ - msg1

msg2 db 'This message will be repeated three times', 10
msg2_len = $ - msg2