; This code works only on ARM 64-bit Linux!!!

format ELF64 executable 3
processor cpu64_v8
include '../../../macrolib/Linux/linux_arm64.inc'
entry start



segment readable executable
align 4

start:
    itoa #-1, buffer
    mov x2, x0
    println buffer, x2

    mov x0, #42
    itoa x0, buffer
    mov x2, x0 ; when using println/print/printn with itoa, move the length of the string from register x0 to register x2
    println buffer, x2

    ldr x0, number
    itoa x0, buffer
    mov x2, x0
    println buffer, x2

    mov x0, #-12345
    itoa x0, buffer
    mov x2, x0
    println buffer, x2

    mov x8, #93
    mov x0, #0
    svc 0



segment readable writeable

buffer rb 20
number dd 18446744073