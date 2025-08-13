; Auxiliary Macros

macro clr [reg] { mov reg, #0 } ; clears the specified registers using mov

macro push [reg] { str reg, [sp, #-8]! } ; saves multiple registers onto the stack

macro pop [reg] { ldr reg, [sp], #8 } ; restores multiple registers from the stack

macro exit value {
    mov x8, #93 ; sets syscall number for exit
    mov x0, value ; sets exit code
    svc 0 ; performs the syscall
}



; Convert Macros

macro itoa number, buffer { ; string length -> x0
    push x2, x3, x4, x1, x5, x6 ; saves x2, x3, x4, x1, x5 and x6 registers

    local .loop, .reverse ; declares local labels .loop and .reverse

    mov x2, #0 ; clears x2 (loop counter)
    adr x3, buffer ; sets x3 to point to buffer start
    mov x4, number ; moves input number to x4

    .loop: ; .loop label start
        mov x1, #10 ; sets divisor to 10 (decimal base)
        udiv x5, x4, x1 ; divides number by 10, quotient in x5
        msub x6, x5, x1, x4 ; x6 = x4 - (x5 * 10) (remainder)
        add x6, x6, #'0' ; converts remainder to ASCII digit
        push w6 ; pushes digit to stack
        add x2, x2, #1 ; increments loop counter
        mov x4, x5 ; updates number with quotient
        cbnz x4, .loop ; continues loop if not zero

    mov x0, x2 ; moves string length to x0

    .reverse: ; .reverse label start
        pop w6 ; pops digit from stack
        strb w6, [x3], #1 ; stores byte at [x3] and increments x3
        subs x2, x2, #1 ; decrements counter
        b.ne .reverse ; loops until counter is zero

    mov w6, #0 ; sets null terminator
    strb w6, [x3] ; writes null terminator at end of string

    pop x6, x5, x1, x4, x3, x2 ; restores x6, x5, x1, x4, x3 and x2 registers
}



; Directory Management Macros

macro mkdir dir_name, permissions { ; error code -> x0
    push x8, x1, x2 ; saves x8, x1 and x2 registers
    mov x8, #34 ; sets syscall number for mkdirat
    mov x0, #-100 ; AT_FDCWD (current working directory)
    adr x1, dir_name ; sets path to directory
    mov x2, permissions ; sets permissions
    svc 0 ; performs the syscall

    pop x2, x1, x8 ; restores x2, x1 and x8 registers
}

macro rmdir dir_name { ; error code -> x0
    push x8, x1, x2 ; saves x8, x1 and x2 registers

    mov x8, #35 ; sets syscall number for unlinkat
    mov x0, #-100 ; AT_FDCWD (current working directory)
    adr x1, dir_name ; sets path to directory
    mov x2, #512 ; AT_REMOVEDIR (rmdir)
    svc 0 ; performs the syscall

    pop x2, x1, x8 ; restores x2, x1 and x8 registers
}



; Console Output Macros

macro print str, str_len { ; total bytes written -> x0
    push x1, x2, x8, x3 ; saves x1, x2, x8 and x3 registers

    adr x1, str ; sets pointer to string to write
    mov x2, str_len ; sets length of string
    mov x8, #64 ; sets syscall number for write
    mov x0, #1 ; sets file descriptor to stdout (1)
    svc 0 ; performs the syscall

    mov x3, #0 ; clears x3 (counter)
    add x3, x3, x0 ; adds number of bytes written to x3

    mov x8, #64 ; sets syscall number for write
    mov x0, #1 ; sets file descriptor to stdout (1)
    adr x1, print_newline_char ; pointer to newline char
    mov x2, 1 ; length 1 byte
    svc 0 ; performs the syscall

    add x0, x0, x3 ; adds number of bytes written to x0

    pop x3, x8, x2, x1 ; saves x2, x1 and x8 registers
}

macro printl times, str, str_len { ; total bytes written -> x0
    push x3, x4, x1, x2, x8 ; saves x3, x4, x1, x2 and x8 registers

    local .loop ; declares local label .loop

    mov x3, #0 ; clears x3 (counter)
    mov x4, times ; moves times to x4 (loop counter)

    .loop: ; .loop label start
        adr x1, str ; sets pointer to string to write
        mov x2, str_len ; sets length of string
        mov x8, #64 ; sets syscall number for write
        mov x0, #1 ; sets file descriptor to stdout (1)  
        svc 0 ; performs the syscall

        add x3, x3, x0 ; adds number of bytes written to x3

        mov x8, #64 ; sets syscall number for write
        mov x0, #1 ; sets file descriptor to stdout (1)
        adr x1, print_newline_char ; pointer to newline char
        mov x2, 1 ; length 1 byte
        svc 0 ; performs the syscall

        add x3, x3, x0 ; adds number of bytes written to x3

        sub x4, x4, #1 ; decrements x4
        cmp x4, #0 ; compare x4 with 0
        b.ne .loop ; jumps to .loop if x4 not zero

    mov x0, x3 ; moves total bytes written to x0

    pop x8, x2, x1, x4, x3 ; restores x8, x2, x1, x4 and x3 register
}



; Data Section

print_newline_char db 10
