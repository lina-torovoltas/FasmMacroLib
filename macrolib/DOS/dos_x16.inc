; Auxiliary Macros

macro clr [reg] { xor reg, reg } ; clears the specified registers using xor

macro push [reg] { push reg } ; saves multiple registers onto the stack

macro pop [reg] { pop reg } ; restores multiple registers from the stack

macro exit code {
    mov ah, 4Ch ; sets syscall number for exit
    mov al, code ; sets exit code
    int 21h ; performs the syscall
}



; Directory Management Macros

macro mkdir dir_name { ; error code -> ax
    push dx ; saves dx register

    mov ah, 39h ; sets syscall number for mkdir
    mov dx, dir_name ; sets path to directory
    int 21h ; performs the syscall

    pop dx ; restores dx register
}

macro rmdir dir_name { ; error code -> ax
    push dx ; saves dx register

    mov ah, 3Ah ; sets syscall number for rmdir
    mov dx, dir_name ; sets path to directory
    int 21h ; performs the syscall

    pop dx ; restores dx register
}



; Console Output Macros

macro print msg {
    push dx ; saves dx registerx

    mov ah, 9 ; sets syscall number for write
    mov dx, msg ; sets pointer to string to write
    int 21h ; performs the syscall

    pop dx ; restores dx register
}

macro printl times, str {
    push dx, cx       ; saves dx and cx registers

    local .loop       ; declares local loop label

    mov cx, times     ; sets loop counter

    .loop:
    mov ah, 9         ; sets syscall number for write
    mov dx, str       ; sets pointer to string to write
    int 21h           ; performs the syscall

    loop .loop        ; decrements cx and jumps if cx not 0

    pop cx, dx        ; restores cx and dx registers
}
