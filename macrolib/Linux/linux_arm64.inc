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
    mov x8, #93
    mov x0, value
    svc 0
}



; Convert Macros

macro itoa number, buffer { ; string length -> x0
    push x2, x3
    push x4, x1
    push x5, x6
    push x7, x8

    local .loop, .reverse, .skip_neg

    mov x2, #0
    adr x3, buffer
    mov x4, number
    mov x7, #0

    cmp x4, #0
    b.ge .loop
    neg x4, x4
    mov x7, #1

    .loop:
        mov x1, #10
        udiv x5, x4, x1
        msub x6, x5, x1, x4
        add x6, x6, #'0'
        push w6
        add x2, x2, #1
        mov x4, x5
        cbnz x4, .loop

    cbz x7, .skip_neg
    mov w8, #'-'
    push w8
    add x2, x2, #1

    .skip_neg:
        mov x0, x2

    .reverse:
        pop w6
        strb w6, [x3], #1
        subs x2, x2, #1
        b.ne .reverse

    mov w6, #0
    strb w6, [x3]

    pop x7, x8
    pop x5, x6
    pop x4, x1
    pop x2, x3
}

macro utoa number, buffer { ; string length -> x0
    push x2, x3
    push x4, x1
    push x5, x6

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

    pop x5, x6
    pop x4, x1
    pop x2, x3
}



; Directory Management Macros

macro mkdir dir_name, permissions { ; error code -> x0
    push x8, x1
    push x2

    mov x8, #34
    mov x0, #-100
    adr x1, dir_name
    mov x2, permissions
    svc 0

    pop x2
    pop x8, x1
}

macro rmdir dir_name { ; error code -> x0
    push x8, x1
    push x2

    mov x8, #35
    mov x0, #-100
    adr x1, dir_name
    mov x2, #512
    svc 0

    pop x2
    pop x8, x1
}



; Console Output Macros

macro print str, str_len { ; total bytes written -> x0
    push x8, x1
    push x2

    mov x8, #64
    mov x0, #1
    adr x1, str
    mov x2, str_len
    svc 0

    pop x2
    pop x8, x1
}

macro println str, str_len { ; total bytes written -> x0
    push x1, x2
    push x8, x3

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

    pop x8, x3
    pop x1, x2
}

macro printn times, str, str_len { ; total bytes written -> x0
    push x9, x10
    push x11, x12
    push x13, x14
    push x15, x1
    push x2, x3

    local .exp_fill_loop, .fill_remainder, .write, .exit, .str_to_buf, .exp_buf, .rem_to_buf

    mov x9, str_len
    mov x10, times
    mul x9, x9, x10

    cbz x9, .exit

    alloc_buf x9

    cbz x0, .exit

    mov x11, x0

    adr x1, str
    mov x2, x11
    mov x3, str_len

    .str_to_buf:
        ldrb w4, [x1], #1
        strb w4, [x2], #1
        subs x3, x3, #1
        b.ne .str_to_buf

    mov x12, str_len

    .exp_fill_loop:
        mov x13, x9
        sub x13, x13, x12

        cmp x13, x12
        b.lt .fill_remainder

        mov x1, x11
        mov x2, x11
        add x2, x2, x12
        mov x3, x12

        .exp_buf:
            ldrb w4, [x1], #1
            strb w4, [x2], #1
            subs x3, x3, #1
            b.ne .exp_buf

        add x12, x12, x12
        b .exp_fill_loop

    .fill_remainder:
        cbz x13, .write

        mov x1, x11
        mov x2, x11
        add x2, x2, x12
        mov x3, x13

        .rem_to_buf:
            ldrb w4, [x1], #1
            strb w4, [x2], #1
            subs x3, x3, #1
            b.ne .rem_to_buf

    .write:
        mov x8, #64
        mov x0, #1
        mov x1, x11
        mov x2, x9
        svc 0

        mov x14, x0
        free_buf x11, x9
        mov x0, x14

    .exit:

    pop x2, x3
    pop x15, x1
    pop x13, x14
    pop x11, x12
    pop x9, x10
}



; Console Input Macros

macro input buffer, size { ; bytes read -> x0
    push x1, x2
    push x8

    mov x8, #63
    mov x0, #0
    adr x1, buffer
    mov x2, size
    svc 0

    pop x8
    pop x1, x2 
}



; Process Macros

macro fork { ; child PID, 0 or error code -> x0
    push x1, x2
    push x3, x4
    push x8

    mov x8, #220
    mov x0, #17
    mov x1, #0
    mov x2, #0
    mov x3, #0
    mov x4, #0
    svc 0

    pop x8
    pop x3, x4
    pop x1, x2
}

macro waitpid pid { ; PID or error code -> x0
    push x1, x2
    push x8

    mov x8, #260
    mov x0, pid
    mov x1, #0
    mov x2, #0
    svc 0

    pop x8
    pop x1, x2
}



; Memory macros

macro alloc_buf size { ; pointer to allocated buffer -> x0
    push x1, x2
    push x3, x4
    push x5, x8

    mov x8, #222
    mov x0, #0
    mov x1, size
    mov x2, #3
    mov x3, #34
    mov x4, #-1
    mov x5, #0
    svc 0

    pop x5, x8
    pop x3, x4
    pop x1, x2
}

macro free_buf addr, size { ; 0 or -1 -> r0
    push x8, x1
    
    mov x8, #215
    mov x0, addr
    mov x1, size
    svc 0
    
    pop x8, x1
}



; Misc Macros

macro time { ; seconds -> x0, microseconds -> x1
    push x8
    sub sp, sp, #16

    mov x8, #113
    mov x0, #0
    mov x1, sp
    svc 0

    ldr x0, [sp]
    ldr x1, [sp, #8]

    add sp, sp, #16
    pop x8
}

macro run command { ; error code -> r0
    push x19

    local .child, .error, .done

    fork
    cmp x0, #0
    b.eq .child
    b.lt .error

    mov x19, x0
    waitpid x19
    b .done

    .child:
        exec command
    .error:
        exit 1
    .done:

    pop x19
}

macro exec command { ; error code -> x0
    local .path, .arg2, .arg3, .argv

    mov x8, #221
    adr x0, .path
    adr x1, .argv
    mov x2, #0
    svc 0

    exit x0

    .path  db "/bin/sh", 0
    .arg2  db "-c", 0
    .arg3  db command, 0
    
    align 8
    .argv  dd .path, .arg2, .arg3, 0
    align 4
}

macro delay_ms ms { ; 0 or error code -> x0
    push x1, x2
    push x19, x20
    push x8

    mov x8, ms
    mov x19, #1000
    udiv x20, x8, x19
    msub x2, x20, x19, x8

    movz x19, #0x4240
    movk x19, #0x000F, lsl 16
    mul x2, x2, x19

    stp x20, x2, [sp, #-16]!

    mov x8, #101
    mov x0, sp
    mov x1, #0
    svc 0

    add sp, sp, #16

    pop x8
    pop x19, x20
    pop x1, x2
}


macro get_rand { ; random number -> x0
    push x2, x8

    local .seed_retry, .rand_retry

    .seed_retry:
        mrs x2, rndrrs
        b.cs .seed_retry

    .rand_retry:
        mrs x8, rndr
        b.cs .rand_retry

    eor x0, x8, x2

    pop x2, x8
}



; Сustom Mnemonics

rndr equ s3_3_c2_c4_0
rndrrs equ s3_3_c2_c4_1