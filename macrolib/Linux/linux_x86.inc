; Auxiliary Macros

macro clr [reg] { xor reg, reg } ; clears the specified registers using xor

macro push [reg] { push reg } ; saves multiple registers onto the stack

macro pop [reg] { pop reg } ; restores multiple registers from the stack

macro exit value {
    mov eax, 1 ; sets syscall number for exit
    mov ebx, value ; sets exit code
    int 80h ; performs the syscall
}



; Convert Macros

macro itoa number, buffer { ; eax -> count
    push ecx, edi, esi, edx, ebx

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

    pop ebx, edx, esi, edi, ecx
}



; Directory Management Macros

macro mkdir dir_name, permissions {
    push ebx, ecx ; saves ebx and ecx registers

    mov eax, 39 ; sets syscall number for mkdir
    mov ebx, dir_name ; sets path to directory
    mov ecx, permissions ; sets permissions
    int 80h ; performs the syscall

    pop ecx, ebx ; restores ecx and ebx registers
}

macro rmdir dir_name {
    push ebx ; saves ebx register

    mov eax, 40 ; sets syscall number for rmdir
    mov ebx, dir_name ; sets path to directory
    int 80h ; performs the syscall

    pop ebx ; restores ebx register
}



; Console Output Macros

macro print str, str_len {
    push ecx, edx, ebx, edi ; saves ebx, ecx and edx registers

    mov ecx, str ; sets pointer to string to write
    mov edx, str_len ; sets length of string
    mov eax, 4 ; sets syscall number for write
    mov ebx, 1 ; sets file descriptor to stdout (1)
    int 80h ; performs the syscall

    xor edi, edi
    add edi, eax

    mov eax, 4 ; sets syscall number for write
    mov ebx, 1 ; sets file descriptor to stdout (1)
    mov ecx, print_newline_char ; pointer to newline char
    mov edx, 1 ; length 1 byte
    int 80h ; performs the syscall

    add eax, edi

    pop edi, ebx, edx, ecx ; restores edx, ecx and ebx registers
}

macro printl times, str, str_len {
    push esi, edi, ecx, ebx, edx ; saves esi, edi, ecx, ebx and edx registers

    local .loop ; declares local label .loop

    xor esi, esi ; clears esi (counter)
    mov edi, times ; moves times to edi (loop counter)

    .loop: ; .loop label start
        mov eax, 4 ; sets syscall number for write
        mov ebx, 1 ; sets file descriptor to stdout (1)
        mov ecx, str ; sets pointer to string to write
        mov edx, str_len ; sets length of string
        int 80h ; performs the syscall

        add esi, eax

        mov eax, 4
        mov ebx, 1
        mov ecx, print_newline_char
        mov edx, 1
        int 80h

        add esi, eax ; adds number of bytes written to esi

        dec edi ; decrements edi
        jnz .loop ; jumps to .loop if edi not zero

    mov eax, esi ; moves total bytes written from esi to eax

    pop edx, ebx, ecx, edi, esi ; restores edx, ebx, ecx, edi and esi registers
}



; Misc Macros

macro time {
    push ebx ; saves ebx register

    mov eax, 13 ; sets syscall number for time
    xor ebx, ebx ; sets argument to NULL (store time in eax)
    int 80h ; performs the syscall

    pop ebx ; restores ebx register

}

macro run command {
    local .path, .arg2str, .arg3str, .argv

    mov eax, 11 ; sets syscall number for execve
    lea ebx, [.path] ; loads pointer to program path "/bin/sh"
    lea ecx, [.argv] ; loads pointer to argument vector array
    xor edx, edx ; clears edx (envp pointer set to NULL)
    int 80h ; performs the syscall

    .path db "/bin/sh", 0 ; defines path string "/bin/sh" null-terminated
    .arg2str db "-c", 0 ; defines second argument "-c" null-terminated
    .arg3str db command, 0 ; defines third argument as the command string null-terminated
    .argv dd .path, .arg2str, .arg3str, 0 ; defines argv array with pointers to path, arg2str, arg3str, and NULL terminator
}



; Data Section

print_newline_char db 10
