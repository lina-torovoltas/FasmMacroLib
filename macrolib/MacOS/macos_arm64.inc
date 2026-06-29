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



; Console Output Macros

macro print str, str_len {
    push x1, x2
    push x16

    mov x0, #1
    adr x1, str
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
    adr x1, str
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