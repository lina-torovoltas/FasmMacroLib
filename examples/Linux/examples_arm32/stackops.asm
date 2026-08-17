; This code works only on ARM 32-bit Linux!!!

format ELF executable 3
processor cpu32_v1 +cpu32_t2
include '../../../macrolib/Linux/linux_arm32.inc'
entry start



segment readable executable
align 4

start:
    mov r7, #1
    mov r0, #42
    mov r1, #492

    push r7, r0
    push r1

    mov r7, #42
    mov r0, #42
    mov r1, #42

    pop r1
    pop r7, r0

    eor r0, r0, r1 

    svc 0