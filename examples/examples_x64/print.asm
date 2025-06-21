; This code works only on 64-bit Linux!!!

format ELF64 executable 3
include '../../macrolib/macrolib_x64.inc'
entry start



segment readable executable

start:
    print msg, msg_len

    mov rax, 60
    xor rdi, rdi
    syscall



segment readable writeable

msg db 'Test output string', 10
msg_len = $ - msg