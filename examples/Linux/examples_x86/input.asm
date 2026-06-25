; This code works only on 32-bit Linux!!!

format ELF executable 3
include '../../../macrolib/Linux/linux_x86.inc'
entry start



segment readable executable

start:
    mov eax, 4
    mov ebx, 1
    mov ecx, msg
    mov edx, msg_len
    int 80h

    input buffer, 128
    mov esi, eax

    mov eax, 4
    mov ebx, 1
    mov ecx, msg2
    mov edx, msg2_len
    int 80h

    mov eax, 4
    mov ebx, 1
    mov ecx, buffer
    mov edx, esi
    int 80h

    mov eax, 1
    xor ebx, ebx
    int 80h



segment readable writeable

buffer rb 128
msg db "Enter text: "
msg_len = $ - msg
msg2 db "You entered: "
msg2_len = $ - msg2