; This code works only on 32-bit FreeBSD!!!

format ELF executable 9
include '../../../macrolib/FreeBSD/freebsd_x86.inc'
entry start



segment readable executable

start:
    clr eax, ebx
    mov eax, 1
    push ebx
    push eax
    int 0x80