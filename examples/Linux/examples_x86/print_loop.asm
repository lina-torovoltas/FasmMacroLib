; This code works only on 32-bit Linux!!!

format ELF executable 3
include '../../../macrolib/Linux/linux_x86.inc'
entry start



segment readable executable

start:
    printl 2, msg1, msg1_len
    printl 3, msg2, msg2_len

    mov eax, 1
    xor ebx, ebx
    int 80h



segment readable writeable

msg1 db 'This message will be repeated two times'
msg1_len = $ - msg1

msg2 db 'This message will be repeated three times'
msg2_len = $ - msg2
