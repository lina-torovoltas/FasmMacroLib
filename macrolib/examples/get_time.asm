; This code works only on 64-bit Linux!!!

format ELF64 executable 3
include '../macrolib.inc'
entry start



segment readable executable

start:
    time

    mov rax, 60
    xor rdi, rdi
    syscall