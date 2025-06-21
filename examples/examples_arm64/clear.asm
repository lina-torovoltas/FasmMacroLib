; This code works only on arm64 Linux!!!

format ELF64 executable 3
processor cpu64_v8
include '../../macrolib/macrolib_arm64.inc'
entry start



segment readable executable
align 4

start:
    mov x8, #93
    clr x0
    svc 0
