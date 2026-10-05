; This code works only on 64-bit Redox!!!

format ELF64 executable
include '../../../macrolib/Redox/redox_x64.inc'
entry start



segment readable executable

start:
    print msg, msg_len

    mov eax, 1
    xor edi, edi
    syscall



segment readable writeable

msg db 'Test output string', 0xA
msg_len = $ - msg
