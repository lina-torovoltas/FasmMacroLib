; This macro only works on Linux!!!

format ELF64 executable 3
entry start



segment readable executable

macro exit value {
    mov rax, 60
    mov rdi, value
    syscall
}


start:
    exit 0