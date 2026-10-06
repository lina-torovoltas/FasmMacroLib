; This code works only on 32-bit Linux!!!

format ELF executable 3
include '../../../macrolib/Linux/linux_x86.inc'
entry start



segment readable executable

start:
    get_rand
    xorshift eax
    
    utohex eax, buffer 
    mov edx, eax ; When using print/println/printn with utoa, move the length of the string from register eax to register edx
    
    println buffer, edx

    mov eax, 1
    xor ebx, ebx
    int 80h



segment readable writeable

buffer rb 10
