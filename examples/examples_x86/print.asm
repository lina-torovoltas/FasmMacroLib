; This code works only on 64-bit Linux!!!

format ELF executable 3
include '../../macrolib/macrolib_x86.inc'
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