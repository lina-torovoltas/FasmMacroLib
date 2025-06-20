; This code works only on 64-bit Linux!!!

format ELF executable 3
include '../macrolib.inc'
entry start



segment readable executable

start:
    time

    mov eax, 1
    xor ebx, ebx
    int 0x80