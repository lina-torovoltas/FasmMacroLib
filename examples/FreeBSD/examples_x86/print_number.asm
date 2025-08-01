; This code works only on 32-bit FreeBSD!!!

format ELF executable 9
include '../../../macrolib/FreeBSD/freebsd_x86.inc'
entry start



segment readable executable

start:
    printnum 1234
    printnum 4294967295
    printnum 0
    printnum 244939252

    mov eax, 1
    push 0
    push eax
    int 0x80