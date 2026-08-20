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

macro exit value {
    mov x8, #1
    mov x0, value
    svc 0
}



; Console Output Macros

macro print str, str_len { ; total bytes written -> x0
    push x8, x1
    push x2

    mov x8, #4
    mov x0, #1
    adr x1, msg
    mov x2, msg_len
    svc 0

    pop x2
    pop x8, x1
}