; This code works only on ARM 64-bit Linux!!!

format ELF64 executable 3
processor cpu64_v8
include '../../../macrolib/Linux/linux_arm64.inc'
entry start



segment readable executable
align 4

start:
    alloc_buf 50
    mov x19, x0

    mov w9, 'b'
    strb w9, [x19, #0]
    mov w9, 'u'
    strb w9, [x19, #1]
    mov w9, 'f'
    strb w9, [x19, #2]
    mov w9, 'f'
    strb w9, [x19, #3]
    mov w9, 'e'
    strb w9, [x19, #4]
    mov w9, 'r'
    strb w9, [x19, #5]
    mov w9, 0xA
    strb w9, [x19, #6]

    mov x8, #64
    mov x0, #1
    mov x1, x19
    mov x2, #7
    svc 0

    alloc_buf 32
    
    mov x9, #42
    str x9, [x0]
    ldr x0, [x0]
    mov x8, #93
    svc 0
