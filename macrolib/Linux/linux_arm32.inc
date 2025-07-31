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
    mov r7, #1 ; sets syscall number for exit
    mov r0, value ; sets exit code
    svc 0 ; performs the syscall
}



; Directory Management Macros

macro mkdir dir_name, permissions {
    push r7, r1 ; saves r7 and r1 registers

    mov r7, #39 ; sets syscall number for mkdir
    mov r0, dir_name ; sets path to directory
    mov r1, permissions ; sets permissions
    svc 0 ; performs the syscall

    pop r1, r7 ; restores r1 and r7 registers
}

macro rmdir dir_name {
    push r7 ; saves r7 register

    mov r7, #40 ; sets syscall number for rmdir
    mov r0, dir_name ; sets path to directory
    svc 0 ; performs the syscall

    pop r7 ; restores r7 register
}



; Console Output Macros

macro print str, str_len {
    push r7, r1, r2 ; saves r7, r1 and r2 registers

    mov r7, #4 ; sets syscall number for write
    mov r0, #1 ; sets file descriptor to stdout (1)
    mov r1, str ; sets pointer to string to write
    mov r2, str_len ; sets length of string
    svc 0 ; performs the syscall

    pop r2, r1, r7 ; saves r2, r1 and r7 registers
}

macro printtim times, str, str_len {
    push r4, r5, r7, r1, r2 ; saves r4, r5, r7, r1 and r2 registers

    local .loop ; declares local label .loop

    mov r4, #0 ; clears r4 (counter)
    mov r5, times ; moves times to r5 (loop counter)

    .loop: ; .loop label start
        mov r7, #4 ; sets syscall number for write
        mov r0, #1 ; sets file descriptor to stdout (1)
        mov r1, str ; sets pointer to string to write
        mov r2, str_len ; sets length of string
        svc 0 ; performs the syscall

        add r4, r4, r0 ; adds number of bytes written to r4

        sub r5, r5, #1 ; decrements r5
        cmp r5, #0 ; compare r5 with 0
        bne .loop ; jumps to .loop if r5 not zero

    mov r0, r4 ; moves total bytes written from r4 to r0

    pop r2, r1, r7, r5, r4 ; restores r2, r1, r7, r5 and r4 register
}