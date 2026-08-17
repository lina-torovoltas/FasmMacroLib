; This code works only on ARM 64-bit Linux!!!

format ELF64 executable 3
processor cpu64_v8
include '../../../macrolib/Linux/linux_arm64.inc'
entry start



segment readable executable
align 4

start:
    mov x8, #93
    mov x0, #42
    mov x1, #492

    push x8, x0
    push x1

    mov x8, #42
    mov x0, #42
    mov x1, #42

    pop x1
    pop x8, x0

    eor x0, x0, x1 

    svc 0