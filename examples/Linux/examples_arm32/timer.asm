; This code works only on ARM 32-bit Linux!!!

format ELF executable 3
processor cpu32_v1 +cpu32_t2 +cpu32_div +cpu32_7M +cpu32_v4t +cpu32_ve +cpu32_v2
include '../../../macrolib/Linux/linux_arm32.inc'
entry start



segment readable executable
align 4

start:
    mov r7, #4
    mov r0, #1
    mov r1, msg1
    mov r2, msg1_len
    svc 0

    delay_ms 500

    mov r7, #4
    mov r1, msg2
    mov r2, msg2_len
    svc 0

    mov r7, #1
    mov r0, #0
    svc 0



segment readable writeable

msg1 db "Print number one", 0xA
msg1_len = $ - msg1

msg2 db "Print number two after pause", 0xA
msg2_len = $ - msg2
