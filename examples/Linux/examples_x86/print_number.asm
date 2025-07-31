; This code works only on 32-bit Linux!!!

format ELF executable 3
include '../../../macrolib/Linux/linux_x86.inc'
entry start



segment readable executable

start:
    printnum 1234
    printnum 4294967295
    printnum 0
    printnum 244939252

    mov eax, 1
    xor ebx, ebx
    int 0x80