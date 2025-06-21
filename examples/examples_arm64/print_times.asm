; This code works only on arm64 Linux!!!

format ELF64 executable 3
processor cpu64_v8
include '../../macrolib/macrolib_arm64.inc'
entry start



segment readable executable
align 4

start:
    printtim 2, msg1, msg1_len
    printtim 3, msg2, msg2_len

    mov x8, #93
    mov x0, #0
    svc 0



segment readable writeable

msg1 db 'This message will be repeated two times', 10
msg1_len = $ - msg1

msg2 db 'This message will be repeated three times', 10
msg2_len = $ - msg2
