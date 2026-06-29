format ELF64
include '../../../macrolib/MacOS/macos_arm64.inc'
processor cpu64_v8

public start as '_main'

section '.text' executable
align 4

start:
    printn 2, msg1, msg1_len
    printn 3, msg2, msg2_len

    mov x0, #0
    mov x16, #1
    movk x16, #0x0200, lsl 16
    svc 80h

align 4

msg1 db 'This message will be repeated two times'
msg1_len = $ - msg1

msg2 db 'This message will be repeated three times'
msg2_len = $ - msg2