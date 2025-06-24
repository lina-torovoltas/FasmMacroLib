; Auxiliary Macros

macro clr [reg] { xor reg, reg } ; clears the specified registers using xor

macro push [reg] { push reg } ; saves multiple registers onto the stack

macro pop [reg] { pop reg } ; restores multiple registers from the stack

macro exit code {
    mov ah, 4Ch
    mov al, code
    int 21h
}



; Directory Management Macros

macro mkdir dir_name {
    push dx

    mov ah, 39h
    mov dx, dir_name
    int 21h

    pop dx
}

macro rmdir dir_name {
    push dx

    mov ah, 3Ah
    mov dx, dir_name
    int 21h

    pop dx
}



; Console Output Macros

macro print msg {
    push dx

    mov ah, 9
    mov dx, msg
    int 21h

    pop dx
}

macro printtim times, str {
    push dx, cx

    local .loop

    mov cx, times

    .loop:
    mov ah, 9
    mov dx, str
    int 21h

    loop .loop

    pop cx, dx
}