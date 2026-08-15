; This code works only on ARM 64-bit Linux!!!

format ELF64 executable 3
processor cpu64_v8
include '../../../macrolib/Linux/linux_arm64.inc'
entry start



segment readable executable
align 4

start:
    mov x8, #64
    mov x0, #1
    adr x1, msg1
    mov x2, msg1_len
    svc 0

    delay_ms 500

    mov x8, #64
    adr x1, msg2
    mov x2, msg2_len
    svc 0

    mov x8, #93
    mov x0, #0
    svc 0



segment readable writeable

msg1 db "Print number one", 0xA
msg1_len = $ - msg1

msg2 db "Print number two after pause", 0xA
msg2_len = $ - msg2
