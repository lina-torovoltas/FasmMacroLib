; Auxiliary Macros

macro clr [reg] { mov reg, #0 }

macro push reg1, reg2 {
    if reg2 eq
        str reg1, [sp, #-8]!
    else
        sub sp, sp, #8
        str reg1, [sp]
        str reg2, [sp, #4]
    end if
}

macro pop reg1, reg2 {
    if reg2 eq
        ldr reg1, [sp], #8
    else
        ldr reg1, [sp]
        ldr reg2, [sp, #4]
        add sp, sp, #8
    end if
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
    push r1, r2
    push r7
    
    mov r1, str
    mov r2, str_len
    mov r7, #4
    mov r0, #1
    svc 0

    pop r7
    pop r2, r1
}

macro println str, str_len { ; total bytes written -> r0
    push r1, r2
    push r7, r3

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

    pop r3, r7
    pop r2, r1
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



; Console Input Macros

macro input buffer, size { ; bytes read -> r0
    push r1, r2
    push r7

    mov r7, #3
    mov r0, #0
    mov r1, buffer
    mov r2, size
    svc 0

    pop r7
    pop r1, r2 
}



; Process Macros

macro fork { ; child PID, 0 or error code -> r0
    push r1, r2
    push r3, r4
    push r7

    mov r7, #120
    mov r0, #17
    mov r1, #0
    mov r2, #0
    mov r3, #0
    mov r4, #0
    svc 0

    pop r7
    pop r3, r4
    pop r1, r2
}

macro waitpid pid { ; PID or error code -> r0
    push r1, r2
    push r7

    mov r0, pid
    mov r7, #114
    mov r1, #0
    mov r2, #0
    svc 0

    pop r7
    pop r1, r2
}



; Memory macros

macro alloc_buf size { ; pointer to allocated buffer -> r0
    push r1, r2
    push r3, r4
    push r5, r7

    mov r7, #192
    mov r0, #0
    mov r1, size
    mov r2, #3
    mov r3, #34
    mov r4, #-1
    mov r5, #0
    svc 0

    pop r5, r7
    pop r3, r4
    pop r1, r2
}

macro clear_buf addr, size { ; 0 or -1 -> r0
    push r7, r1
    
    mov r7, #91
    mov r0, addr
    mov r1, size
    svc 0
    
    pop r7, r1
}



; Misc Macros

macro time { ; seconds -> r0, microseconds -> r1
    push r7
    sub sp, sp, #16

    mov r7, #263
    mov r0, #0
    mov r1, sp
    svc 0

    ldr r0, [sp]
    ldr r1, [sp, #8]

    add sp, sp, #16
    pop r7
}

macro run command { ; error code -> r0
    push r11

    local .child, .error, .done

    fork
    cmp r0, #0
    beq .child
    blt .error

    mov r11, r0
    waitpid r11
    b .done

    .child:
        exec command
    align 4
    .error:
        exit 1
    .done:

    pop r11
}

macro exec command { ; error code -> r0
    local .path, .arg2, .arg3

    adr r4, .path
    adr r5, .arg2
    adr r6, .arg3

    mov r2, #0

    str r4, [sp, #-16]!
    str r5, [sp, #4]
    str r6, [sp, #8]
    str r2, [sp, #12]

    mov r7, #11
    mov r0, r4
    mov r1, sp
    mov r2, #0
    svc 0

    add sp, sp, #16

    exit r0

    .path db "/bin/sh", 0
    .arg2 db "-c", 0
    .arg3 db command, 0
}

macro delay_ms ms { ; 0 or error code -> r0
    push r1, r2
    push r4, r5
    push r6, r7
    push r10

    mov  r6, ms

    mov  r5, #1000
    udiv r4, r6, r5

    mls  r2, r4, r5, r6

    movw r5, #0x4240
    movt r5, #0x000F
    mul  r10, r2, r5
    mov r2, r10

    str  r4, [sp, #-8]!
    str  r2, [sp, #4]

    mov  r7, #162
    mov  r0, sp
    mov  r1, #0
    svc  0

    add  sp, sp, #8

    pop r10
    pop r6, r7
    pop r4, r5
    pop r1, r2
}

macro get_rand { ; random number -> r0
    push r7, r1
    push r2

    sub sp, sp, #4
    mov r0, sp
    
    mov r7, #384
    mov r1, #4
    mov r2, #0
    svc 0

    ldr r0, [sp]
    add sp, sp, #4

    pop r2
    pop r7, r1
}
