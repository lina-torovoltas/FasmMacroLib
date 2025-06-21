; This code works only on 32-bit Linux!!!

format ELF executable 3
include '../../macrolib/macrolib_x86.inc'
entry start



segment readable executable

start:
    mov eax, 1
    clr ebx
    int 0x80