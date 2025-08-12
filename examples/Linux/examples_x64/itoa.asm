; This code works only on 64-bit Linux!!!

format ELF64 executable 3
include '../../../macrolib/Linux/linux_x64.inc'
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

    mov rax, 60
    xor rdi, rdi
    syscall



segment readable writeable

buffer rb 20
number dq 18446744073709551615
