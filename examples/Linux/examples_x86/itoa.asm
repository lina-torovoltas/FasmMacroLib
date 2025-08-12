; This code works only on 32-bit Linux!!!

format ELF executable 3
include '../../../macrolib/Linux/linux_x86.inc'
entry start



segment readable executable

start:
    itoa 0, buffer 
    print buffer, eax
    
    mov eax, 244939252
    itoa eax, buffer 
    print buffer, eax

    itoa [number], buffer 
    print buffer, eax

    mov eax, 1
    xor ebx, ebx
    int 80h



segment readable writeable

buffer rb 10
number dd 4294967295
