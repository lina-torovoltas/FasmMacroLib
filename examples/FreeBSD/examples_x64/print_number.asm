; This code works only on 64-bit FreeBSD!!!

format ELF64 executable 9
include '../../../macrolib/FreeBSD/freebsd_x64.inc'
entry start



segment readable executable

start:
    printnum 1234
    printnum 18446744073709551615
    printnum 0
    printnum 244939252

    mov rax, 1
    xor rdi, rdi
    syscall