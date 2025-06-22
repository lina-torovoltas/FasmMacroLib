; Auxiliary Macros 

macro clr [reg] { mov reg, #0 } ; clears the specified registers using mov

macro push [reg] { str reg, [sp, #-8]! } ; saves multiple registers onto the stack

macro pop [reg] { ldr reg, [sp], #8 } ; restores multiple registers from the stack

macro exit value {
    mov x8, #93 ; sets syscall number for exit
    mov x0, value ; sets exit code
    svc 0 ; performs the syscall
}



; Directory Management Macros

macro mkdir dir_name, permissions {
    push x8, x1, x2 ; saves x0, x1 and x2 registers

    mov x8, #34 ; sets syscall number for mkdirat
    mov x0, #-100 ; AT_FDCWD (current working directory)
    adr x1, dir_name ; sets path to directory
    mov x2, permissions ; sets permissions
    svc 0 ; performs the syscall

    pop x2, x1, x8 ; restores x2, x1 and x0 registers
}

macro rmdir dir_name {
    push x8, x1, x2 ; saves x0, x1 and x2 registers

    mov x8, #35 ; sets syscall number for unlinkat
    mov x0, #-100 ; AT_FDCWD (current working directory)
    adr x1, dir_name ; sets path to directory
    mov x2, #512 ; AT_REMOVEDIR (rmdir)
    svc 0 ; performs the syscall

    pop x2, x1, x8 ; restores x2, x1 and x0 registers
}



; Console Output Macros

macro print str, str_len {
    push x8, x1, x2 ; saves x0, x1 and x2 registers

    mov x8, #64 ; sets syscall number for write
    mov x0, #1 ; sets file descriptor to stdout (1)
    adr x1, str ; sets pointer to string to write
    mov x2, str_len ; sets length of string
    svc 0 ; performs the syscall

    pop x2, x1, x8 ; saves x2, x1 and x0 registers
}

macro printtim times, str, str_len {
    push x4, x5, x8, x1, x2 ; saves x4, x5, x0, x1 and x2 registers

    local .loop ; declares local label .loop

    mov x4, #0 ; clears x4 (counter)
    mov x5, times ; moves times to x5 (loop counter)

    .loop: ; .loop label start
        mov x8, #64 ; sets syscall number for write
        mov x0, #1 ; sets file descriptor to stdout (1)
        adr x1, str ; sets pointer to string to write
        mov x2, str_len ; sets length of string
        svc 0 ; performs the syscall

        add x4, x4, x0 ; adds number of bytes written to x4

        sub x5, x5, #1 ; decrements x5
        cmp x5, #0 ; compare x5 with 0
        b.ne .loop ; jumps to .loop if x5 not zero

    mov x0, x4 ; moves total bytes written from x4 to x8

    pop x2, x1, x8, x5, x4 ; restores x2, x1, x0, x5 and x4 register
}



; Data Section

newline db 10
buffer rb 32
