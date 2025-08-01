; Auxiliary Macros

macro clr [reg] { xor reg, reg } ; clears the specified registers using xor

macro exit value {
    mov eax, 1 ; sets syscall number for exit
    push value ; sets exit code
    push eax
    int 0x80 ; performs the syscall
}



; Console Output Macros

macro print str, str_len {
    mov eax, 4 ; sets syscall number for write
    push str_len ; sets length of string
    push str ; sets pointer to string to write
    push 1 ; sets file descriptor to stdout (1)
    push eax
    int 0x80 ; performs the syscal
}

macro printtim times, str, str_len {
    local .loop ; declares local label .loop

    mov edi, times ; moves times to edi (loop counter)

    .loop: ; .loop label start
        mov eax, 4 ; sets syscall number for write
        push str_len ; sets length of string
        push str ; sets pointer to string to write
        push 1 ; sets file descriptor to stdout (1)
        push eax
        int 0x80 ; performs the syscal

        dec edi ; decrements edi
        jnz .loop ; jumps to .loop if edi not zero
}

macro printnum value {
    local .convert ; declares local label .convert

    mov eax, value ; moves value to eax
    mov edi, buffer ; sets edi to point to buffer start
    add edi, 31 ; moves edi to end of buffer
    mov byte [edi], 0 ; writes null terminator at buffer end

    mov ecx, 10 ; sets divisor to 10 (decimal base)
    mov ebx, eax ; copies value to ebx for division

    .convert: ; .convert label start
        dec edi ; moves pointer one byte left
        xor edx, edx ; clears edx (high part of dividend)
        div ecx ; divides eax by ecx, quotient in eax, remainder in edx
        add dl, '0' ; converts remainder to ASCII digit
        mov [edi], dl ; stores digit at current edi
        test eax, eax ; tests if quotient is zero
        jnz .convert ; loops if quotient not zero

    mov eax, 4 ; sets syscall number for write
    mov edx, buffer ; buffer start address
    add edx, 32 ; buffer end address
    sub edx, edi ; calculates length of number string
    push edx
    push edi
    push 1 ; sets file descriptor to stdout (1)
    push eax
    int 0x80 ; performs the syscal

    mov eax, 4 ; sets syscall number for write
    push 1 ; length 1 byte
    push newline ; pointer to newline char
    push 1 ; sets file descriptor to stdout (1)
    push eax
    int 0x80 ; performs the syscal
}



; Data Section

newline db 10
buffer rb 32