; This macro only works on Linux!!!

format ELF64 executable 3
entry start



segment readable executable

macro exit {
    mov rax, 60
    xor rdi, rdi
    syscall
    }


start:
    exit