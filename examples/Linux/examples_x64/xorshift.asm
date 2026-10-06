; This code works only on 64-bit Linux!!!

format ELF64 executable 3
include '../../../macrolib/Linux/linux_x64.inc'
entry start



segment readable executable

start:
    get_rand
    xorshift rax

    utohex rax, buffer
    mov r9, rax

    println buffer, r9

    mov rax, 60
    xor rdi, rdi
    syscall



segment readable writeable

buffer rb 20
