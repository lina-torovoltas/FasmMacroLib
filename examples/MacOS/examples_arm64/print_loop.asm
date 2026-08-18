; This code works only on ARM 64-bit MacOS!!!

format ELF64
include '../../../macrolib/MacOS/macos_arm64.inc'
processor cpu64_v8

public start as '_main'

section '.text' executable
align 4

start:
    adr x18, msg1
    printn 2, x18, msg1_len

    adr x18, msg2
    printn 3, x18, msg2_len

    mov x0, #0
    mov x16, #1
    movk x16, #0x0200, lsl 16
    svc 80h

align 4

msg1 db 'This message will be repeated two times'
msg1_len = $ - msg1

msg2 db 'This message will be repeated three times'
msg2_len = $ - msg2