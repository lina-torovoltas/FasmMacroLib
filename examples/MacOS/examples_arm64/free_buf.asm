; This code works only on ARM 64-bit MacOS!!!

format ELF64
include '../../../macrolib/MacOS/macos_arm64.inc'
processor cpu64_v8

public start as '_main'

section '.text' executable
align 4

start:
    alloc_buf 50
    mov x19, x0

    free_buf x19, 50 ; frees the buffer allocated with alloc_buf

    mov w9, 'b'
    strb w9, [x19, #0]
    ; ^ this instruction will cause a segfault, since the buffer has already been unmapped by clear_buf above

    mov x16, #1
    movk x16, #0x0200, lsl 16
    mov x0, #0
    svc 80h