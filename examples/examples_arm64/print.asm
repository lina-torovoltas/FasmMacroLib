; This code works only on arm64 Linux!!!

format ELF64 executable 3
processor cpu64_v8
include '../../macrolib/macrolib_arm64.inc'
entry start



segment readable executable
align 4

start:
    print msg, msg_len

    mov x8, #93
    mov x0, #0
    svc 0



segment readable writeable

msg db 'Test output string', 10
msg_len = $ - msg
