; This macro only works on Linux!!!

format ELF64 executable 3
entry start



segment readable executable

macro mkdir dir_name, permissions {
    push rdi
    push rsi

    mov rax, 83
    mov rdi, dir_name
    mov rsi, permissions
    syscall

    pop rsi
    pop rdi
}


start:
    mkdir name, 777o

    mov rax, 60
    xor rdi, rdi
    syscall



segment readable writeable

name db "test", 0