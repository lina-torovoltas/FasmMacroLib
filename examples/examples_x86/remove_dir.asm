; This code works only on 64-bit Linux!!!

format ELF executable 3
include '../../macrolib/macrolib_x86.inc'
entry start



segment readable executable

start:
    rmdir name

    mov eax, 1
    xor ebx, ebx
    int 0x80



segment readable writeable

name db "test", 0