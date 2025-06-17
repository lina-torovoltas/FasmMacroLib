; This macro only works on Linux!!!

format ELF64 executable 3
entry start



segment readable executable

macro time {
    push rdi

    mov rax, 201
    xor rdi, rdi
    syscall

    pop rdi

}


start:
    time

    mov rax, 60
    xor rdi, rdi
    syscall