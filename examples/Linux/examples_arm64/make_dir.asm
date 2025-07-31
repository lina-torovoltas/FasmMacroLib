; This code works only on ARM 64-bit Linux!!!

format ELF64 executable 3
processor cpu64_v8
include '../../../macrolib/Linux/linux_arm64.inc'
entry start



segment readable executable
align 4

start:
    mkdir name, 777o

    mov x8, #93
    mov x0, #0
    svc 0



segment readable writeable

name db "test", 0