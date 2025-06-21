; This code works only on arm64 Linux!!!

format ELF64 executable 3
processor cpu64_v8
include '../../macrolib/macrolib_arm64.inc'
entry start



segment readable executable
align 4

start:
    rmdir name

    mov x8, #93
    mov x0, #0
    svc 0



segment readable writeable

name db "test", 0
