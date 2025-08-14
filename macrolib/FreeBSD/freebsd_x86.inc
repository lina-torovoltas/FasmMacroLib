; WARNING: This code is experimental and may behave unpredictably

; Auxiliary Macros

macro clr [reg] { xor reg, reg } ; clears the specified registers using xor

macro push [reg] { push reg } ; saves multiple registers onto the stack

macro pop [reg] { pop reg } ; restores multiple registers from the stack

macro exit value {
    mov eax, 1 ; sets syscall number for exit
    push value ; sets exit code
    push eax
    int 80h ; performs the syscall
}



; Convert Macros

macro itoa number, buffer { ; string length -> eax
    push ecx, edi, esi, edx, ebx ; saves ecx, edi, esi, edx and ebx registers

    local .loop, .reverse ; declares local labels .loop and .reverse
    xor ecx, ecx ; clears ecx (loop counter)
    mov edi, buffer ; sets edi to point to buffer start
    mov esi, number ; moves input number to esi 

    .loop: ; .loop label start
        xor edx, edx ; clears edx (high dividend part)
        mov eax, esi ; moves number to eax for division
        mov ebx, 10 ; sets divisor to 10 (decimal base)
        div ebx ; divides combined value in edx:eax by ebx, quotient stored in eax, remainder stored in edx
        add dl, '0' ; converts remainder to ASCII digit
        push dx ; pushes digit to stack
        inc ecx ; increments loop counter
        mov esi, eax ; updates number with quotient
        test eax, eax ; tests if quotient is zero
        jnz .loop ; continues loop if not zero

    mov edx, ecx ; moves string length to edx

    .reverse: ; .reverse label start
        pop ax ; pops digit from stack into ax
        stosb ; stores al at [edi] and increments edi
        loop .reverse ; loops ecx times to write digits in order

    mov eax, edx ; moves string length to eax

    mov byte [edi], 0 ; writes null terminator at end of string 

    pop ebx, edx, esi, edi, ecx ; restores ebx, edx, esi, edi, and ecx registers
}



; Console Output Macros

macro print str, str_len { ; total bytes written -> eax
    push ecx, edx, ebx, edi ; saves ebx, ecx and edx registers

    push str_len ; sets length of string
    push str ; sets pointer to string to write
    push 1 ; sets file descriptor to stdout (1)
    mov eax, 4 ; sets syscall number for write
    push eax
    int 80h ; performs the syscal

    xor edi, edi ; clears edi (counter)
    add edi, eax ; adds number of bytes written to edi

    mov eax, 4 ; sets syscall number for write
    push 1 ; length 1 byte
    push print_newline_char ; pointer to newline char
    push 1 ; sets file descriptor to stdout (1)
    push eax
    int 80h ; performs the syscal

    add eax, edi ; adds number of bytes written to eax

    pop edi, ebx, edx, ecx ; restores edx, ecx and ebx registers
}

macro printl times, str, str_len { ; total bytes written -> eax
    push esi, edi, ecx, ebx, edx ; saves esi, edi, ecx, ebx and edx registers

    local .loop ; declares local label .loop

    xor esi, esi ; clears esi (counter)
    mov edi, times ; moves times to edi (loop counter)

    .loop: ; .loop label start
        push str_len ; sets length of string
        push str ; sets pointer to string to write
        push 1 ; sets file descriptor to stdout (1)
        mov eax, 4 ; sets syscall number for write
        push eax
        int 80h ; performs the syscal

        add esi, 1 ; adds 1 byte written to esi

        mov eax, 4 ; sets syscall number for write
        push 1 ; length 1 byte
        push print_newline_char ; pointer to newline char
        push 1 ; sets file descriptor to stdout (1)
        push eax
        int 80h ; performs the syscal

        add esi, 1 ; adds 1 byte written to esi

        dec edi ; decrements edi
        jnz .loop ; jumps to .loop if edi not zero

    mov eax, esi ; moves total bytes written from esi to eax

    pop edx, ebx, ecx, edi, esi ; restores edx, ebx, ecx, edi and esi registers
}



; Data Section

print_newline_char db 10
