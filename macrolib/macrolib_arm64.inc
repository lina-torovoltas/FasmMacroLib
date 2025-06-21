macro clr reg { mov reg, #0 } ; clears the specified register using eor

macro push [arg] { str arg, [sp, -16] } ; saves multiple registers onto the stack

macro pop [arg] { ldr arg, [sp, -16] } ; restores multiple registers from the stack

macro exit value {
    mov x8, #93 ; sets syscall number for exit
    mov x0, value ; sets exit code
    svc 0 ; performs the syscall
}

macro print str, str_len {
    push x0 ; saves x0 register
    push x1 ; saves x1 register
    push x2 ; saves x2 register

    mov x8, #64 ; sets syscall number for write
    mov x0, #1 ; sets file descriptor to stdout (1)
    adr x1, str ; sets pointer to string to write
    mov x2, str_len ; sets length of string
    svc 0 ; performs the syscall

    pop x2 ; saves x2 register
    pop x1 ; saves x1 register
    pop x0 ; saves x0 register
}

macro printtim times, str, str_len {
    push x4 ; saves x4 register
    push x5 ; saves x5 register
    push x0 ; saves x0 register
    push x1 ; saves x1 register
    push x2 ; saves x2 register

    local .loop ; declares local label .loop

    mov x4, #0 ; clears x4 (counter)
    mov x5, times ; moves times to x5 (loop counter)

    .loop: ; .loop label start
        mov x8, #64 ; sets syscall number for write
        mov x0, #1 ; sets file descriptor to stdout (1)
        adr x1, str ; sets pointer to string to write
        mov x2, str_len ; sets length of string
        svc 0 ; performs the syscall

        add x4, x4, x8 ; adds number of bytes written to x4

        sub x5, x5, #1 ; decrements x5
        cmp x5, #0 ; compare x5 with 0
        b.ne .loop ; jumps to .loop if x5 not zero

    mov x8, x4 ; moves total bytes written from x4 to x8

    pop x2 ; restores x2 register
    pop x1 ; restores x1 register
    pop x0 ; restores x0 register
    pop x5 ; restores x5 register
    pop x4 ; restores x4 register
}

macro mkdir dir_name, permissions {
    push x0 ; saves x0 register
    push x1 ; saves x1 register
    push x2 ; saves x2 register

    mov x8, #34 ; sets syscall number for mkdirat
    mov x0, #-100 ; AT_FDCWD (current working directory)
    adr x1, dir_name ; sets path to directory
    mov x2, permissions ; sets permissions
    svc 0 ; performs the syscall

    pop x2 ; restores x2 register
    pop x1 ; restores x1 register
    pop x0 ; restores x0 register
}

macro rmdir dir_name {
    push x0 ; saves x0 register
    push x1 ; saves x1 register
    push x2 ; saves x2 register

    mov x8, #35 ; sets syscall number for unlinkat
    mov x0, #-100 ; AT_FDCWD (current working directory)
    adr x1, dir_name ; sets path to directory
    mov x2, #512 ; AT_REMOVEDIR (rmdir)
    svc 0 ; performs the syscall

    pop x2 ; restores x2 register
    pop x1 ; restores x1 register
    pop x0 ; restores x0 register
}


newline db 10
buffer rb 32
