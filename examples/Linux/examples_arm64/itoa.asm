; This code works only on ARM 64-bit Linux!!!

format ELF64 executable 3
processor cpu64_v8
include '../../../macrolib/Linux/linux_arm64.inc'
entry start



segment readable executable
align 4

start:
    itoa #0, buffer
    print buffer, x0

    ; large numbers can't be loaded directly, must be split into 16-bit parts
    ; 244939252 -> 0xE9979F4
    movz x0, 0x79F4          ; lower 16 bits
    movk x0, 0x0E99, lsl 16  ; upper 16 bits
    itoa x0, buffer
    print buffer, x0

    ldr x0, number 
    itoa x0, buffer
    print buffer, x0
    
    mov x0, #1234
    itoa x0, buffer
    mov x5, x0 ; when using printl with itoa, move the length of the string from register x0 to register x5
    printl 2, buffer, x5

    mov x8, #93
    mov x0, #0
    svc 0



segment readable writeable

buffer rb 20
number dd 18446744073709551615
