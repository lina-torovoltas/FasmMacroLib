; Auxiliary Macros

macro clr [reg] { mov reg, #0 }

macro push reg1, reg2 {
  if reg2 eq
    str reg1, [sp, #-16]!
  else
    stp reg1, reg2, [sp, #-16]!
  end if
}

macro pop reg1, reg2 {
  if reg2 eq
    ldr reg1, [sp], #16
  else
    ldp reg1, reg2, [sp], #16
  end if
}

macro exit code {
    mov x0, code
    mov x16, #1
    movk x16, #0x0200, lsl 16
    svc 80h
}



; Convert Macros

macro utoa number, addr { ; string length -> x0
    push x2, x3
    push x4, x1
    push x5, x6

    local .loop, .reverse

    mov x2, #0
    mov x3, addr
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

    pop x5, x6
    pop x4, x1
    pop x2, x3
}



; Directory Management Macros

macro mkdir dir_name, permissions { ; error code -> x0
    push x16, x1
    push x2

    mov x8, #-2
    mov x0, x8
    adr x1, dir_name
    mov x2, permissions
    mov x16, #475
    movk x16, #0x0200, lsl 16
    svc 80h

    pop x2
    pop x16, x1
}

macro rmdir dir_name { ; error code -> x0
    push x16, x1
    push x2

    mov x8, #-2
    mov x0, x8
    adr x1, dir_name
    mov x2, #0x0080
    mov x16, #472
    movk x16, #0x0200, lsl 16
    svc 80h

    pop x2
    pop x16, x1
}

; Console Output Macros

macro print str, str_len {
    push x1, x2
    push x16

    mov x0, #1
    mov x1, str
    mov x2, str_len
    mov x16, #4
    movk x16, #0x0200, lsl 16
    svc 80h

    pop x16
    pop x1, x2
}

macro println str, str_len {
    push x1, x2
    push x16, x3

    local .newline, .done

    mov x0, #1
    mov x1, str
    mov x2, str_len
    mov x16, #4
    movk x16, #0x0200, lsl 16
    svc 80h

    mov x3, x0

    b .done
    .newline db 0xA
    align 4
    .done:

    mov x0, #1
    adr x1, .newline
    mov x2, #1
    mov x16, #4
    movk x16, #0x0200, lsl 16
    svc 80h

    add x0, x0, x3

    pop x16, x3
    pop x1, x2
}

macro printn times, str, str_len {
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

    pop x3, x4
}



; Console Input Macros

macro input buffer, size { ; bytes read -> x0
    push x1, x2
    push x16

    mov x0, #0
    mov x1, buffer
    mov x2, size
    mov x16, #3
    movk x16, #0x0200, lsl 16
    svc 80h

    pop x16
    pop x1, x2
}



; Memory macros

macro alloc_buf size { ; pointer to allocated buffer -> x0
    push x1, x2
    push x3, x4
    push x5, x16

    mov x0, #0
    mov x1, size
    mov x2, #3
    mov x3, #4098
    mov x4, #-1
    mov x5, #0
    mov x16, #197
    movk x16, #0x0200, lsl 16
    svc 80h

    pop x5, x16
    pop x3, x4
    pop x1, x2
}

macro free_buf addr, size { ; 0 or -1 -> x0
    push x16, x1

    mov x0, addr
    mov x1, size
    mov x16, #73
    movk x16, #0x0200, lsl 16
    svc 80h

    pop x16, x1
}



; Misc Macros

macro get_rand { ; random number -> x0
    push x1, x2
    push x16

    sub sp, sp, #16
    mov x0, sp

    mov x1, #8
    mov x16, #500
    movk x16, #0x0200, lsl 16
    svc 80h

    ldr x0, [sp]
    add sp, sp, #16

    pop x16
    pop x1, x2
}