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

macro mkdir dir_name, permissions { ; error code -> r0
    push r7, r1 ; saves r7 and r1 registers

    mov r7, #39 ; sets syscall number for mkdir
    mov r0, dir_name ; sets path to directory
    mov r1, permissions ; sets permissions
    svc 0 ; performs the syscall

    pop r1, r7 ; restores r1 and r7 registers
}

macro rmdir dir_name {  ; error code -> r0
    push r7 ; saves r7 register

    mov r7, #40 ; sets syscall number for rmdir
    mov r0, dir_name ; sets path to directory
    svc 0 ; performs the syscall

    pop r7 ; restores r7 register
}



; Console Output Macros

macro print str, str_len { ; total bytes written -> r0
    push r1, r2, r3, r7 ; saves r1, r2, r3 and r7 registers
    
    mov r1, str ; sets pointer to string to write
    mov r2, str_len ; sets length of string
    mov r7, #4 ; sets syscall number for write
    mov r0, #1 ; sets file descriptor to stdout (1) 
    svc 0 ; performs the syscall

    mov r3, #0 ; clears r3 (counter)
    add r3, r3, r0 ; adds number of bytes written to r3

    mov r7, #4 ; sets syscall number for write
    mov r0, #1 ; sets file descriptor to stdout (1)
    mov r1, print_newline_char ; pointer to newline char
    mov r2, 1 ; length 1 byte
    svc 0 ; performs the syscall

    add r0, r0, r3 ; adds number of bytes written to r0

    pop r7, r3, r2, r1 ; restores r7, r3, r2 and r1 registers
}

macro printl times, str, str_len { ; total bytes written -> r0
    push r3, r4, r1, r2, r7 ; saves r3, r4, r1, r2 and r7 registers

    local .loop ; declares local label .loop

    mov r3, #0 ; clears r3 (counter)
    mov r4, times ; moves times to r4 (loop counter)

    .loop: ; .loop label start
        mov r1, str ; sets pointer to string to write
        mov r2, str_len ; sets length of string
        mov r7, #4 ; sets syscall number for write
        mov r0, #1 ; sets file descriptor to stdout (1) 
        svc 0 ; performs the syscall

        add r3, r3, r0 ; adds number of bytes written to r3

        mov r7, #4 ; sets syscall number for write
        mov r0, #1 ; sets file descriptor to stdout (1)
        mov r1, print_newline_char ; pointer to newline char
        mov r2, 1 ; length 1 byte
        svc 0 ; performs the syscall

        add r3, r3, r0 ; adds number of bytes written to r3

        sub r4, r4, #1 ; decrements r4
        cmp r4, #0 ; compare r4 with 0
        bne .loop ; jumps to .loop if r4 not zero

    mov r0, r3 ; moves total bytes written from r3 to r0

    pop r7, r2, r1, r4, r3 ; restores r7, r2, r1, r4 and r3 register
}



; Data Section

print_newline_char db 10
