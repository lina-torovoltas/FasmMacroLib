; This code works only on 64-bit Linux!!!

format ELF64 executable 3
include '../../../macrolib/Linux/linux_x64.inc'
entry start



segment readable executable

start:
    utohex 0xDEADBEEF, buffer
    mov r9, rax  ; When using print/println/printn with itoa, move the length of the string from register rax to register r9
    println buffer, r9

    mov rax, [number]
    utohex rax, buffer
    mov r9, rax
    println buffer, r9

    mov rax, 0x2A2A2A2A2A2A2A2A
    utohex rax, buffer
    mov r9, rax
    println buffer, r9

    ; If you need uppercase, then use utoHEX
    mov rax, 0xCAFEBABEDEADF00D
    utoHEX rax, buffer
    mov r9, rax
    println buffer, r9

    mov rax, 60
    xor rdi, rdi
    syscall



segment readable writeable

buffer rb 20
number dq 18446744073709551615
