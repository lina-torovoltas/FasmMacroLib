; Auxiliary Macros

macro clr [reg] { mov reg, #0 } ; clears the specified registers using mov

macro push [reg] { ; saves multiple registers onto the stack
    sub sp, sp, #4
    str reg, [sp]
}

macro pop [reg] { ; restores multiple registers from the stack
    ldr reg, [sp]
    add sp, sp, #4
}

macro exit value {
    mov r7, #1
    mov r0, value
    svc 0
}



; Directory Management Macros

macro mkdir dir_name, permissions { ; error code -> r0
    push r7, r1

    mov r7, #39
    mov r0, dir_name
    mov r1, permissions
    svc 0

    pop r1, r7
}

macro rmdir dir_name {  ; error code -> r0
    push r7, r1

    mov r7, #40
    mov r0, dir_name
    svc 0

    pop r1, r7
}



; Console Output Macros

macro print str, str_len { ; total bytes written -> r0
    push r1, r2, r7, r1
    
    mov r1, str
    mov r2, str_len
    mov r7, #4
    mov r0, #1
    svc 0

    pop r1, r7, r2, r1
}

macro println str, str_len { ; total bytes written -> r0
    push r1, r2, r7, r3

    local .newline, .done

    mov r1, str
    mov r2, str_len
    mov r7, #4
    mov r0, #1
    svc 0

    mov r3, r0

    b .done
    .newline db 0xA
    align 4
    .done:

    mov r7, #4
    mov r0, #1
    adr r1, .newline
    mov r2, #1
    svc 0

    add r0, r0, r3

    pop r3, r7, r2, r1
}

macro printn times, str, str_len { ; total bytes written -> r0
    push r3, r4

    local .loop

    mov r3, #0
    mov r4, times

    .loop:
        println str, str_len

        add r3, r3, r0

        sub r4, r4, #1
        cmp r4, #0
        bne .loop

    mov r0, r3

    pop r4, r3
}