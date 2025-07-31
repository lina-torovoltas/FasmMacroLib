; This code works only on ARM 64-bit Linux!!!

format ELF64 executable 3
processor cpu64_v8
include '../../../macrolib/Linux/linux_arm64.inc'
entry start



segment readable executable
align 4

macro print str, str_len {
    push x8, x0, x1, x2

    mov x8, #64
    mov x0, #1
    adr x1, str
    mov x2, str_len
    svc 0

    pop x2, x1, x0, x8
}


start:
    print msg, msg_len

    mov x8, #93
    mov x0, #0
    svc 0



segment readable writeable

msg db 'Test output string', 10
msg_len = $ - msg