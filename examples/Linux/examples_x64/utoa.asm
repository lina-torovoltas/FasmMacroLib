; This code works only on 64-bit Linux!!!

format ELF64 executable 3
include '../../../macrolib/Linux/linux_x64.inc'
entry start



segment readable executable

start:
    utoa 0, buffer
    mov r9, rax  ; When using print/println/printn with utoa, move the length of the string from register rax to register r9
    println buffer, r9

    mov rax, 42
    utoa rax, buffer
    mov r9, rax
    println buffer, r9

    utoa [number], buffer
    mov r9, rax
    println buffer, r9

    utoa 12345, buffer
    mov r9, rax
    printn 2, buffer, r9

    mov rax, 60
    xor rdi, rdi
    syscall



segment readable writeable

buffer rb 20
number dq 1844674407