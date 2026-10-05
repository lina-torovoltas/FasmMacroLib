; This code works only on 64-bit Illumos!!!

format ELF64 executable 6
include '../../../macrolib/Illumos/illumos_x64.inc'
entry start



segment readable executable

start:
    print msg, msg_len

    mov rax, 1
    xor rdi, rdi
    syscall



segment readable writeable

msg db 'Test output string', 0xA
msg_len = $ - msg
