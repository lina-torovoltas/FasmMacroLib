; This code works only on 64-bit BSD!!!

format ELF64 executable 3
include '../../../macrolib/BSD/bsd_x64.inc'
entry start



segment readable executable

start:
    mkdir name, 777o

    mov rax, 1
    xor rdi, rdi
    syscall



segment readable writeable

name db "test", 0