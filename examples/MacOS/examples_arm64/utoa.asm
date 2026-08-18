; This code works only on ARM 64-bit MacOS!!!

format ELF64
include '../../../macrolib/MacOS/macos_arm64.inc'
processor cpu64_v8

public start as '_main'

section '.text' executable
align 4

start:
    alloc_buf 20
    mov x19, x0

    utoa #0, x19
    mov x2, x0
    println x19, x2

    ; large numbers can't be loaded directly, must be split into 16-bit parts
    ; 244939252 -> 0xE9979F4
    movz x0, 0x79F4          ; lower 16 bits
    movk x0, 0x0E99, lsl 16  ; upper 16 bits
    utoa x0, x19
    mov x2, x0
    println x19, x2

    movz x0, 0xFFFF
    movk x0, 0xFFFF, lsl 16
    movk x0, 0xFFFF, lsl 32
    movk x0, 0xFFFF, lsl 48   ; 18446744073709551615 (max u64)
    utoa x0, x19
    mov x2, x0
    println x19, x2

    mov x0, #1234
    utoa x0, x19
    mov x2, x0
    printn 2, x19, x2

    mov x16, #1
    movk x16, #0x0200, lsl 16
    mov x0, #0
    svc 80h