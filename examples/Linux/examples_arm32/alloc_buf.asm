; This code works only on ARM 32-bit Linux!!!

format ELF executable 3
processor cpu32_v1 +cpu32_t2
include '../../../macrolib/Linux/linux_arm32.inc'
entry start



segment readable executable
align 4

start:
    alloc_buf 50
    mov r11, r0

    mov r10, 'b'
    strb r10, [r11, #0]
    mov r10, 'u'
    strb r10, [r11, #1]
    mov r10, 'f'
    strb r10, [r11, #2]
    mov r10, 'f'
    strb r10, [r11, #3]
    mov r10, 'e'
    strb r10, [r11, #4]
    mov r10, 'r'
    strb r10, [r11, #5]
    mov r10, 0xA
    strb r10, [r11, #6]

    mov r7, #4
    mov r0, #1
    mov r1, r11
    mov r2, #7
    svc 0

    alloc_buf 32
    mov r9, #42
    str r9, [r11]
    ldr r0, [r11]
    mov r7, #1
    svc 0
