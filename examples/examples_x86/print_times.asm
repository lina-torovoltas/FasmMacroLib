; This code works only on 64-bit Linux!!!

format ELF executable 3
include '../../macrolib/macrolib_x86.inc'
entry start



segment readable executable

start:
    printtim 2, msg1, msg1_len
    printtim 3, msg2, msg2_len

    mov eax, 1
    xor ebx, ebx
    int 0x80



segment readable writeable

msg1 db 'This message will be repeated two times', 10
msg1_len = $ - msg1

msg2 db 'This message will be repeated three times', 10
msg2_len = $ - msg2