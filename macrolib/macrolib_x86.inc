; Auxiliary Macros 

macro clr [reg] { xor reg, reg } ; clears the specified registers using xor

macro push [reg] { push reg } ; saves multiple registers onto the stack

macro pop [reg] { pop reg } ; restores multiple registers from the stack

macro exit value {
    mov eax, 1 ; sets syscall number for exit
    mov ebx, value ; sets exit code
    int 0x80 ; performs the syscall
}



; Directory Management Macros

macro mkdir dir_name, permissions {
    push ebx, ecx ; saves ebx and ecx registers

    mov eax, 39 ; sets syscall number for mkdir
    mov ebx, dir_name ; sets path to directory
    mov ecx, permissions ; sets permissions
    int 0x80 ; performs the syscall

    pop ecx, ebx ; restores ecx and ebx registers
}

macro rmdir dir_name {
    push ebx ; saves ebx register

    mov eax, 40 ; sets syscall number for rmdir
    mov ebx, dir_name ; sets path to directory
    int 0x80 ; performs the syscall

    pop ebx ; restores ebx register
}



; Console Output Macros

macro print str, str_len {
    push ebx, ecx, edx ; saves ebx, ecx and edx registers

    mov eax, 4 ; sets syscall number for write
    mov ebx, 1 ; sets file descriptor to stdout (1)
    mov ecx, str ; sets pointer to string to write
    mov edx, str_len ; sets length of string
    int 0x80 ; performs the syscall

    pop edx, ecx, ebx ; restores edx, ecx and ebx registers
}

macro printtim times, str, str_len {
    push esi, edi, ecx, ebx, edx ; saves esi, edi, ecx, ebx and edx registers

    local .loop ; declares local label .loop

    xor esi, esi ; clears esi (counter)
    mov edi, times ; moves times to edi (loop counter)

    .loop: ; .loop label start
        mov eax, 4 ; sets syscall number for write
        mov ebx, 1 ; sets file descriptor to stdout (1)
        mov ecx, str ; sets pointer to string to write
        mov edx, str_len ; sets length of string
        int 0x80 ; performs the syscall

        add esi, eax ; adds number of bytes written to esi

        dec edi ; decrements edi
        jnz .loop ; jumps to .loop if edi not zero

    mov eax, esi ; moves total bytes written from esi to eax

    pop edx, ebx, ecx, edi, esi ; restores edx, ebx, ecx, edi and esi registers
}

macro printnum value {
    push edi, ecx, ebx, edx, esi ; saves edi, ecx, ebx, edx and esi registers

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

    mov ecx, edi ; sets ecx to current string start
    mov eax, 4 ; sets syscall number for write
    mov ebx, 1 ; sets file descriptor to stdout (1)
    mov edx, buffer ; buffer start address
    add edx, 32 ; buffer end address
    sub edx, edi ; calculates length of number string
    int 0x80 ; performs syscall

    xor esi, esi ; clears esi
    mov esi, eax ; saves number of bytes written

    mov eax, 4 ; sets syscall number for write
    mov ebx, 1 ; sets file descriptor to stdout (1)
    mov ecx, newline ; pointer to newline char
    mov edx, 1 ; length 1 byte
    int 0x80 ; performs the syscall

    add eax, esi ; adds bytes written (number + newline)

    pop esi, edx, ebx, ecx, edi ; restores esi, edx, ebx, ecx and edi registers
}



; Misc Macros

macro time {
    push ebx ; saves ebx register

    mov eax, 13 ; sets syscall number for time
    xor ebx, ebx ; sets argument to NULL (store time in eax)
    int 0x80 ; performs the syscall

    pop ebx ; restores ebx register

}

macro run command {
    local .path, .arg2str, .arg3str, .argv

    mov eax, 11 ; sets syscall number for execve
    lea ebx, [.path] ; loads pointer to program path "/bin/sh"
    lea ecx, [.argv] ; loads pointer to argument vector array
    xor edx, edx ; clears edx (envp pointer set to NULL)
    int 0x80 ; performs the syscall

    .path db "/bin/sh", 0 ; defines path string "/bin/sh" null-terminated
    .arg2str db "-c", 0 ; defines second argument "-c" null-terminated
    .arg3str db command, 0 ; defines third argument as the command string null-terminated
    .argv dd .path, .arg2str, .arg3str, 0 ; defines argv array with pointers to path, arg2str, arg3str, and NULL terminator
}



; Data Section

newline db 10
buffer rb 32