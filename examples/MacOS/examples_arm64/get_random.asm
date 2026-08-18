; This code works only on ARM 64-bit MacOS!!!

format ELF64
include '../../../macrolib/MacOS/macos_arm64.inc'
processor cpu64_v8

public start as '_main'

section '.text' executable
align 4

start:
    get_rand

    mov x16, #1
    movk x16, #0x0200, lsl 16
    svc 80h