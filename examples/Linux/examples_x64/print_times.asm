; This code works only on 64-bit Linux!!!

format ELF64 executable 3
include '../../../macrolib/Linux/linux_x64.inc'
entry start



segment readable executable

start:
    printtim 2, msg1, msg1_len
    printtim 3, msg2, msg2_len

    mov rax, 60
    xor rdi, rdi
    syscall



segment readable writeable

msg1 db 'This message will be repeated two times', 10
msg1_len = $ - msg1

msg2 db 'This message will be repeated three times', 10
msg2_len = $ - msg2