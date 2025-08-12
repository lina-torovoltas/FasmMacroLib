; This code works only on 32-bit FreeBSD!!!

format ELF executable 9
include '../../../macrolib/FreeBSD/freebsd_x86.inc'
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
    push 0
    push eax
    int 0x80



segment readable writeable

buffer rb 10
number dd 4294967295
