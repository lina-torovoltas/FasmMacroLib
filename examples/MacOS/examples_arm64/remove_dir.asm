; This code works only on ARM 64-bit MacOS!!!

format ELF64
include '../../../macrolib/MacOS/macos_arm64.inc'
processor cpu64_v8

public start as '_main'

section '.text' executable
align 4

start:
    rmdir name

    mov x0, #0
    mov x16, #1
    movk x16, #0x0200, lsl 16
    svc 80h

align 4

name db "test", 0x0