; This code works only on 64-bit FreeBSD!!!

format ELF64 executable 9
include '../../../macrolib/FreeBSD/freebsd_x64.inc'
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
    
    mov rax, 1
    xor rdi, rdi
    syscall



segment readable writeable

buffer rb 20
number dq 18446744073709551