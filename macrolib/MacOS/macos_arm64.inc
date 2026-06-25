; Auxiliary Macros

macro clr [reg] { mov reg, #0 } ; clears the specified registers using mov

macro exit code {
    mov x0, code
    mov x16, #1
    movk x16, #0x0200, lsl 16
    svc 80h
}



; Console Output Macros

macro print str, str_len {
    mov x0, #1
    adr x1, str
    mov x2, str_len
    mov x16, #4
    movk x16, #0x0200, lsl 16
    svc 80h
}

