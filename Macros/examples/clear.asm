; This macro only works on Linux!!!

format ELF64 executable 3
entry start



segment readable executable

macro clr reg { xor reg,reg }


start:
    mov rax, 60
    clr rdi
    syscall