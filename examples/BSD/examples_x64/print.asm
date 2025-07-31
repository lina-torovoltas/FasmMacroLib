; This code works only on 64-bit BSD!!!

format ELF64 executable 3
include '../../../macrolib/BSD/bsd_x64.inc'
entry start



segment readable executable

start:
    print msg, msg_len

    mov rax, 1
    xor rdi, rdi
    syscall



segment readable writeable

msg db 'Test output string', 10
msg_len = $ - msg