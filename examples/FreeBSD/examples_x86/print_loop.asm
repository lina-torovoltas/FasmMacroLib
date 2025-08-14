; WARNING: This code is experimental and may behave unpredictably

; This code works only on 32-bit FreeBSD!!!

format ELF executable 9
include '../../../macrolib/FreeBSD/freebsd_x86.inc'
entry start



segment readable executable

start:
    printl 2, msg1, msg1_len
    printl 3, msg2, msg2_len

    mov eax, 1
    push 0
    push eax
    int 80h



segment readable writeable

msg1 db 'This message will be repeated two times'
msg1_len = $ - msg1

msg2 db 'This message will be repeated three times'
msg2_len = $ - msg2
