; This code works only on 64-bit FreeBSD!!!

format ELF64 executable 9
include '../../../macrolib/FreeBSD/freebsd_x64.inc'
entry start



segment readable executable

start:
    itoa 0, buffer
    print buffer, rax

    mov rax, 244939252
    itoa rax, buffer
    print buffer, rax

    itoa [number], buffer
    print buffer, rax

    itoa 1234, buffer
    mov r9, rax ; When using printl with itoa, move the length of the string from register rax to register r9
    printl 2, buffer, 4

    mov rax, 1
    xor rdi, rdi
    syscall



segment readable writeable

buffer rb 20
number dq 18446744073709551615
