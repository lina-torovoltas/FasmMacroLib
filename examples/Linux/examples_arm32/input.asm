; This code works only on ARM 32-bit Linux!!!

format ELF executable 3
processor cpu32_v1 +cpu32_t2
include '../../../macrolib/Linux/linux_arm32.inc'
entry start



segment readable executable
align 4

start:
    mov r7, #4
    mov r0, #1
    mov r1, msg
    mov r2, msg_len
    svc 0

    input buffer, 128
    mov r9, r0

    mov r7, #4
    mov r0, #1
    mov r1, msg2
    mov r2, msg2_len
    svc 0

    mov r7, #4
    mov r0, #1
    mov r1, buffer
    mov r2, r9
    svc 0

    mov r7, #1
    mov r0, #0
    svc 0



segment readable writeable

buffer rb 128
msg db "Enter text: "
msg_len = $ - msg
msg2 db "You entered: "
msg2_len = $ - msg2
