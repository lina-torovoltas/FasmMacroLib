; This code works only on ARM 64-bit Linux!!!

format ELF64 executable 3
processor cpu64_v8
include '../../../macrolib/Linux/linux_arm64.inc'
entry start



segment readable executable
align 4

start:
    printl 2, msg1, msg1_len
    printl 3, msg2, msg2_len

    mov x8, #93
    mov x0, #0
    svc 0



segment readable writeable

msg1 db 'This message will be repeated two times'
msg1_len = $ - msg1

msg2 db 'This message will be repeated three times'
msg2_len = $ - msg2
