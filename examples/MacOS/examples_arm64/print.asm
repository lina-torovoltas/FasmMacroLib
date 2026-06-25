format ELF64
include '../../../macrolib/MacOS/macos_arm64.inc'
processor cpu64_v8

public start as '_main'

section '.text' executable
align 4

start: 
    print msg, msg_len
    
    mov x0, #0
    mov x16, #1
    movk x16, #0x0200, lsl 16
    svc 80h

align 4
msg db 'Test output string', 0xA
msg_len = $ - msg