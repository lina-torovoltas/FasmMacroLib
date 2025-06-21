; This code works only on 64-bit Linux!!!

format ELF64 executable 3
include '../../macrolib/macrolib_x64.inc'
entry start



segment readable executable

start:
    mkdir name, 777o

    mov rax, 60
    xor rdi, rdi
    syscall



segment readable writeable

name db "test", 0