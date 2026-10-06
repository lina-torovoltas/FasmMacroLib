; This code works only on 32-bit Linux!!!

format ELF executable 3
include '../../../macrolib/Linux/linux_x86.inc'
entry start



segment readable executable

start:
    utohex 0xDEADBEEF, buffer
    mov edx, eax ; When using print/println/printn with utohex, move the length of the string from register eax to register edx
    println buffer, edx

    mov eax, [number]
    utohex eax, buffer
    mov edx, eax
    println buffer, edx

    mov eax, 0x2A2A2A2A
    utohex eax, buffer
    mov edx, eax
    println buffer, edx

    ; If you need uppercase, then use utoHEX
    mov eax, 0xCAFEF00D
    utoHEX eax, buffer
    mov edx, eax
    println buffer, edx

    mov eax, 1
    xor ebx, ebx
    int 80h



segment readable writeable

buffer rb 10
number dd 4294967295
