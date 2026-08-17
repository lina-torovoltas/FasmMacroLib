; This code works only on ARM 64-bit Linux!!!

format ELF64 executable 3
processor cpu64_v8
include '../../../macrolib/Linux/linux_arm64.inc'
entry start



segment readable executable
align 4

start:
    run "echo test"

    adr x1, msg
    mov x2, msg_len
    mov x8, #64
    mov x0, #1
    svc 0
    
    mov x8, #93
    mov x0, #0
    svc 0



segment readable writeable

msg db 'Print after run', 0xA
msg_len = $ - msg