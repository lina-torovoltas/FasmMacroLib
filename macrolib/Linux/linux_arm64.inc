; Auxiliary Macros

macro clr [reg] { mov reg, #0 }

macro push [reg] { str reg, [sp, #-8]! }

macro pop [reg] { ldr reg, [sp], #8 }

macro exit value {
    mov x8, #93
    mov x0, value
    svc 0
}



; Convert Macros

macro utoa number, buffer { ; string length -> x0
    push x2, x3, x4, x1, x5, x6

    local .loop, .reverse

    mov x2, #0
    adr x3, buffer
    mov x4, number

    .loop:
        mov x1, #10
        udiv x5, x4, x1
        msub x6, x5, x1, x4
        add x6, x6, #'0'
        push w6
        add x2, x2, #1
        mov x4, x5
        cbnz x4, .loop

    mov x0, x2

    .reverse:
        pop w6
        strb w6, [x3], #1
        subs x2, x2, #1
        b.ne .reverse

    mov w6, #0
    strb w6, [x3]

    pop x6, x5, x1, x4, x3, x2
}



; Directory Management Macros

macro mkdir dir_name, permissions { ; error code -> x0
    push x8, x1, x2, xzr
    mov x8, #34
    mov x0, #-100
    adr x1, dir_name
    mov x2, permissions
    svc 0

    pop xzr, x2, x1, x8
}

macro rmdir dir_name { ; error code -> x0
    push x8, x1, x2, xzr

    mov x8, #35
    mov x0, #-100
    adr x1, dir_name
    mov x2, #512
    svc 0

    pop xzr, x2, x1, x8
}



; Console Output Macros

macro print str, str_len { ; total bytes written -> x0
    push x1, x2, x8, xzr

    adr x1, str
    mov x2, str_len
    mov x8, #64
    mov x0, #1
    svc 0

    pop xzr, x8, x2, x1
}

macro println str, str_len { ; total bytes written -> x0
    push x1, x2, x8, x3

    local .newline, .done

    mov x8, #64
    mov x0, #1
    adr x1, str
    mov x2, str_len
    svc 0

    mov x3, x0

    b .done
    .newline db 0xA
    align 4
    .done:

    mov x8, #64
    mov x0, #1
    adr x1, .newline
    mov x2, #1
    svc 0

    add x0, x0, x3

    pop x3, x8, x2, x1
}

macro printn times, str, str_len { ; total bytes written -> x0
    push x3, x4

    local .loop

    mov x3, #0
    mov x4, times

    .loop:
        println str, str_len

        add x3, x3, x0

        sub x4, x4, #1
        cmp x4, #0
        b.ne .loop

    mov x0, x3

    pop x4, x3
}