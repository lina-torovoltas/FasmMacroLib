; This code works only on arm32 Linux!!!

format ELF executable 3
processor cpu32_v1 +cpu32_t2
include '../../macrolib/macrolib_arm32.inc'
entry start



segment readable executable
align 4

macro print str, str_len {
    push r7, r1, r2

    mov r7, #4
    mov r0, #1
    mov r1, str
    mov r2, str_len
    svc 0

    pop r2, r1, r7
}


start:
    print msg, msg_len

    mov r7, #1
    mov r0, #0
    svc 0



segment readable writeable

msg db 'Test output string', 10
msg_len = $ - msg