; This code works only on arm32 Linux!!!

format ELF executable 3
processor cpu32_v1 +cpu32_t2
include '../../macrolib/macrolib_arm32.inc'
entry start



segment readable executable
align 4

start:
    printtim 2, msg1, msg1_len
    printtim 3, msg2, msg2_len

    mov r7, #1
    mov r0, #0
    svc 0



segment readable writeable

msg1 db 'This message will be repeated two times', 10
msg1_len = $ - msg1

msg2 db 'This message will be repeated three times', 10
msg2_len = $ - msg2