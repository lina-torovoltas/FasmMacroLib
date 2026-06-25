; This code works only on 32-bit Linux!!!

format ELF executable 3
include '../../../macrolib/Linux/linux_x86.inc'
entry start



segment readable executable

start:
    print msg, msg_len

    mov eax, 1
    xor ebx, ebx
    int 80h



segment readable writeable

msg db 'Test output string', 0xA
msg_len = $ - msg
