; This code works only on ARM 64-bit MacOS!!!

format ELF64
include '../../../macrolib/MacOS/macos_arm64.inc'
processor cpu64_v8

public start as '_main'

section '.text' executable
align 4

start:
    mov x0, #1
    adr x1, msg
    mov x2, msg_len
    mov x16, #4
    movk x16, #0x0200, lsl 16
    svc 80h

    alloc_buf 128
    mov x19, x0

    input x19, 128
    mov x9, x0

    mov x0, #1
    adr x1, msg2
    mov x2, msg2_len
    mov x16, #4
    movk x16, #0x0200, lsl 16
    svc 80h

    mov x0, #1
    mov x1, x19
    mov x2, x9
    mov x16, #4
    movk x16, #0x0200, lsl 16
    svc 80h

    mov x0, #0
    mov x16, #1
    movk x16, #0x0200, lsl 16
    svc 80h

align 4

msg db "Enter text: "
msg_len = $ - msg
msg2 db "You entered: "
msg2_len = $ - msg2