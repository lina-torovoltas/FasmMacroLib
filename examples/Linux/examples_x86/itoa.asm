; This code works only on 32-bit Linux!!!

format ELF executable 3
include '../../../macrolib/Linux/linux_x86.inc'
entry start



segment readable executable

start:
    itoa -1, buffer 
    mov edx, eax ; When using print/println/printn with itoa, move the length of the string from register eax to register edx
    println buffer, edx
    
    mov eax, 42
    itoa eax, buffer 
    mov edx, eax
    println buffer, edx

    itoa [number], buffer 
    mov edx, eax
    println buffer, edx

    itoa -12345, buffer
    mov edx, eax
    mov byte [buffer + edx], 0xA
    inc edx
    printn 2, buffer, edx

    mov eax, 1
    xor ebx, ebx
    int 80h



segment readable writeable

buffer rb 10
number dd 42949672
