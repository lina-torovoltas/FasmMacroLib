; This code works only on 64-bit FreeBSD ARM!!!

format ELF64 executable 9
processor cpu64_v8
include '../../../macrolib/FreeBSD/freebsd_arm64.inc'
entry start



segment readable executable
align 4

start:
    print msg, msg_len

    mov x8, #1
    mov x0, #0
    svc 0



segment readable writeable

msg db 'Test output string', 0xA
msg_len = $ - msg