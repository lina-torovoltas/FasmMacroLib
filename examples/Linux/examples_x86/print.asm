; This code works only on 32-bit Linux!!!

format ELF executable 3
include '../../../macrolib/Linux/linux_x86.inc'
entry start



segment readable executable

start:
    print msg, msg_len

    mov eax, 1
    xor ebx, ebx
    int 0x80



segment readable writeable

msg db 'Test output string', 10
msg_len = $ - msg