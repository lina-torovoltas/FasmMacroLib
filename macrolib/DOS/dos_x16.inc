; Auxiliary Macros

macro clr [reg] { xor reg, reg }

macro exit code {
    mov ah, 76
    mov al, code
    int 21h
}



; Convert Macros

macro utoa number, buffer {
    push ax bx cx dx di

    local .loop, .reverse

    mov ax, number
    mov cx, 0
    mov di, buffer

    .loop:
        xor dx, dx
        mov bx, 10
        div bx
        add dl, '0'
        push dx
        inc cx
        test ax, ax
        jnz .loop

    .reverse:
        pop ax
        mov [di], al
        inc di
        loop .reverse

    mov byte [di], '$'

    pop di dx cx bx ax
}

macro itoa number, buffer {
    push ax bx cx dx di

    local .loop, .reverse, .skip_neg

    mov ax, number
    xor cx, cx
    mov di, buffer

    test ax, ax
    jns .skip_neg
    neg ax
    mov byte [di], '-'
    inc di

    .skip_neg:
    .loop:
        xor dx, dx
        mov bx, 10
        div bx
        add dl, '0'
        push dx
        inc cx
        test ax, ax
        jnz .loop

    .reverse:
        pop ax
        mov [di], al
        inc di
        loop .reverse

    mov byte [di], '$'

    pop di dx cx bx ax
}



; Directory Management Macros

macro mkdir dir_name { ; error code -> ax
    push dx

    mov ah, 57
    mov dx, dir_name
    int 21h

    pop dx
}

macro rmdir dir_name { ; error code -> ax
    push dx

    mov ah, 58
    mov dx, dir_name
    int 21h

    pop dx
}



; Console Output Macros

macro print msg {
    push ax dx

    mov ah, 9
    mov dx, msg
    int 21h

    pop dx ax
}

macro println msg {
    push ax dx

    mov ah, 9
    mov dx, msg
    int 21h

    mov ah, 2
    mov dl, 0xD
    int 21h

    mov ah, 2
    mov dl, 0xA
    int 21h

    pop dx ax
}

macro printn times, msg {
    push cx

    local .loop

    mov cx, times

    .loop:
        println msg
    loop .loop

    pop cx
}