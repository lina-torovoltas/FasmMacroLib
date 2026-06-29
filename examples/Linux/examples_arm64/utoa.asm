; This code works only on ARM 64-bit Linux!!!

format ELF64 executable 3
processor cpu64_v8
include '../../../macrolib/Linux/linux_arm64.inc'
entry start



segment readable executable
align 4

start:
    utoa #0, buffer
    println buffer, x0

    ; large numbers can't be loaded directly, must be split into 16-bit parts
    ; 244939252 -> 0xE9979F4
    movz x0, 0x79F4          ; lower 16 bits
    movk x0, 0x0E99, lsl 16  ; upper 16 bits
    utoa x0, buffer
    mov x2, x0 ; when using println/print/printn with utoa, move the length of the string from register x0 to register x2
    println buffer, x2

    ldr x0, number 
    utoa x0, buffer
    mov x2, x0
    println buffer, x2
    
    mov x0, #1234
    utoa x0, buffer
    mov x2, x0
    printn 2, buffer, x2

    mov x8, #93
    mov x0, #0
    svc 0



segment readable writeable

buffer rb 20
number dd 18446744073709551615
