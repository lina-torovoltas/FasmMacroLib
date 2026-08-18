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

    free_buf r11, 50 ; frees the buffer allocated with alloc_buf

    mov r10, 'b'
    strb r10, [r11, #0]
    ; ^ this instruction will cause a segfault, since the buffer has already been unmapped by clear_buf above

    mov r7, #1
    mov r0, #0
    svc 0
