; This code works only on 32-bit Linux!!!

format ELF executable 3
include '../../../macrolib/Linux/linux_x86.inc'
entry start



segment readable executable

start:
    mov eax, 4
    mov ebx, 1
    mov ecx, msg1
    mov edx, msg1_len
    int 80h

    delay_ms 500

    mov eax, 4
    mov ebx, 1
    mov ecx, msg2
    mov edx, msg2_len
    int 80h

    mov eax, 1
    xor ebx, ebx
    int 80h




segment readable writeable

msg1 db "Print number one", 0xA
msg1_len = $ - msg1

msg2 db "Print number two after pause", 0xA
msg2_len = $ - msg2