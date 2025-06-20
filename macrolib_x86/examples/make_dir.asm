; This code works only on 64-bit Linux!!!

format ELF executable 3
include '../macrolib.inc'
entry start



segment readable executable

start:
    mkdir name, 777o

    mov eax, 1
    xor ebx, ebx
    int 0x80



segment readable writeable

name db "test", 0