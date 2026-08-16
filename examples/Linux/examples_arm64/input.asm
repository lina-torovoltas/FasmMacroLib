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
    adr x1, msg
    mov x2, msg_len
    svc 0

    input buffer, 128
    mov x9, x0

    mov x8, #64
    mov x0, #1
    adr x1, msg2
    mov x2, msg2_len
    svc 0

    mov x8, #64
    mov x0, #1
    adr x1, buffer
    mov x2, x9
    svc 0

    mov x8, #93
    mov x0, #0
    svc 0



segment readable writeable

buffer rb 128
msg db "Enter text: "
msg_len = $ - msg
msg2 db "You entered: "
msg2_len = $ - msg2
