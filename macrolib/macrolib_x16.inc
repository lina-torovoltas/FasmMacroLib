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

macro printnum value {
    local .buf, .print_loop, .print_end, .convert

    .buf db 6 dup(0)

    mov ax, value
    mov si, .buf + 5
    mov cx, 0

  .convert:
    xor dx, dx
    mov bx, 10
    div bx
    add dl, '0'
    dec si
    mov [si], dl
    inc cx
    test ax, ax
    jnz .convert

  .print_loop:
    mov dl, [si]
    mov ah, 02h
    int 21h
    inc si
    loop .print_loop

    mov dl, 13
    mov ah, 02h
    int 21h
    mov dl, 10
    int 21h
}