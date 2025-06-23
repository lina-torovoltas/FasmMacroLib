; This code works only on arm32 Linux!!!

format ELF executable 3
processor cpu32_v1 +cpu32_t2
include '../../macrolib/macrolib_arm32.inc'
entry start



segment readable executable
align 4

start:
    mkdir name, 777o

    mov r7, #1
    mov r0, #0
    svc 0



segment readable writeable

name db "test", 0