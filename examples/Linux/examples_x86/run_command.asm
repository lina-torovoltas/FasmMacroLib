; This code works only on 32-bit Linux!!!

format ELF executable 3
include '../../../macrolib/Linux/linux_x86.inc'
entry start



segment readable executable

start:
    run "echo test"

    mov eax, 4
    mov ebx, 1
    mov ecx, msg
    mov edx, msg_len
    int 80h

    mov eax, 1
    xor ebx, ebx
    int 80h



segment readable writeable

msg db 'Print after run', 0xA
msg_len = $ - msg