; This macro only works on Linux!!!

format ELF64 executable 3
entry start



segment readable executable

macro rmdir dir_name {
    push rdi

    mov rax, 84
    mov rdi, dir_name
    syscall

    pop rdi
}


start:
    rmdir name

    mov rax, 60
    xor rdi, rdi
    syscall



segment readable writeable

name db "test", 0