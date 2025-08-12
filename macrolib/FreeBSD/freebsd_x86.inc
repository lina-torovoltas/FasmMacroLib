; Auxiliary Macros

macro clr [reg] { xor reg, reg } ; clears the specified registers using xor

macro exit value {
    mov eax, 1 ; sets syscall number for exit
    push value ; sets exit code
    push eax
    int 80h ; performs the syscall
}



; Convert Macros

macro itoa number, buffer { ; eax -> count
    local .loop, .reverse
    xor ecx, ecx
    mov edi, buffer
    mov esi, number

    .loop:
        xor edx, edx
        mov eax, esi
        mov ebx, 10
        div ebx
        add dl, '0'
        push dx
        inc ecx
        mov esi, eax
        test eax, eax
        jnz .loop

    mov edx, ecx

    .reverse:
        pop ax
        stosb
        loop .reverse

    mov eax, edx

    mov byte [edi], 0
}



; Console Output Macros

macro print str, str_len {
    mov eax, 4 ; sets syscall number for write
    push str_len ; sets length of string
    push str ; sets pointer to string to write
    push 1 ; sets file descriptor to stdout (1)
    push eax
    int 80h ; performs the syscal

    mov eax, 4
    push 1
    push print_newline_char
    push 1
    push eax
    int 80h
}

macro printl times, str, str_len {
    local .loop ; declares local label .loop

    mov edi, times ; moves times to edi (loop counter)

    .loop: ; .loop label start
        mov eax, 4 ; sets syscall number for write
        push str_len ; sets length of string
        push str ; sets pointer to string to write
        push 1 ; sets file descriptor to stdout (1)
        push eax
        int 80h ; performs the syscal

        mov eax, 4
        push 1
        push print_newline_char
        push 1
        push eax
        int 80h

        dec edi ; decrements edi
        jnz .loop ; jumps to .loop if edi not zero
}



; Data Section

print_newline_char db 10
