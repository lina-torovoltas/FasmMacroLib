; This code works only on 32-bit Linux!!!

format ELF executable 3
include '../../../macrolib/Linux/linux_x86.inc'
entry start



segment readable executable

start:
    get_rand
    mov ebx, eax

    mov eax, 1
    int 80h