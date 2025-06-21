macro clr reg { xor reg, reg } ; clears the specified register using xor

macro exit value {
    mov rax, 60 ; sets syscall number for exit
    mov rdi, value ; sets exit code
    syscall ; performs the syscall
}

macro mkdir dir_name, permissions {
    push rdi ; saves rdi register
    push rsi ; saves rsi register

    mov rax, 83 ; sets syscall number for mkdir
    mov rdi, dir_name ; sets path to directory
    mov rsi, permissions ; sets permissions
    syscall ; performs the syscall

    pop rsi ; restores rsi register
    pop rdi ; restores rdi register
}

macro time {
    push rdi ; saves rdi register

    mov rax, 201 ; sets syscall number for time
    xor rdi, rdi ; sets argument to NULL (store time in rax)
    syscall ; performs the syscall

    pop rdi ; restores rdi register

}

macro printnum value {
    push rdi ; saves rdi register
    push rcx ; saves rcx register
    push rbx ; saves rbx register
    push rdx ; saves rdx register
    push rsi ; saves rsi register
    push r8 ; saves r8 register

    local .convert ; declares local label .convert

    mov rax, value ; moves value to rax
    mov rdi, buffer ; sets rdi to point to buffer start
    add rdi, 31 ; moves rdi to end of buffer
    mov byte [rdi], 0 ; writes null terminator at buffer end

    mov rcx, 10 ; sets divisor to 10 (decimal base)
    mov rbx, rax ; copies value to rbx for division

    .convert: ; .convert label start
        dec rdi ; moves pointer one byte left
        xor rdx, rdx ; clears rdx (high part of dividend)
        div rcx ; divides rax by rcx, quotient in rax, remainder in rdx
        add dl, '0' ; converts remainder to ASCII digit
        mov [rdi], dl ; stores digit at current rdi
        test rax, rax ; tests if quotient is zero
        jnz .convert ; loops if quotient not zero

    mov rsi, rdi ; sets rsi to current string start
    mov rax, 1 ; sets syscall number for write
    mov rdi, 1 ; sets file descriptor to stdout (1)
    mov rdx, buffer ; buffer start address
    add rdx, 32 ; buffer end address
    sub rdx, rsi ; calculates length of number string
    syscall ; performs syscall

    xor r8, r8 ; clears r8
    mov r8, rax ; saves number of bytes written

    mov rax, 1 ; sets syscall number for write
    mov rdi, 1 ; sets file descriptor to stdout (1)
    mov rsi, newline ; pointer to newline char
    mov rdx, 1 ; length 1 byte
    syscall ; performs the syscall

    add rax, r8 ; adds bytes written (number + newline)

    pop r8 ; restores r8 register
    pop rsi ; restores rsi register
    pop rdx ; restores rdx register
    pop rbx ; restores rbx register
    pop rcx ; restores rcx register
    pop rdi ; restores rdi register
}

macro printtim times, str, str_len {
    push r8 ; saves r8 register
    push rbx ; saves rbx register
    push rdi ; saves rdi register
    push rsi ; saves rsi register
    push rdx ; saves rdx register

    local .loop ; declares local label .loop

    xor r8, r8 ; clears r8 (counter)
    mov rbx, times ; moves times to rbx (loop counter)

    .loop: ; .loop label start
        mov rax, 1 ; sets syscall number for write
        mov rdi, 1 ; sets file descriptor to stdout (1)
        mov rsi, str ; sets pointer to string to write
        mov rdx, str_len ; sets length of string
        syscall ; performs the syscall

        add r8, rax ; adds number of bytes written to r8

        dec rbx ; decrements rbx
        jnz .loop ; jumps to .loop if rbx not zero

    mov rax, r8 ; moves total bytes written from r8 to rax

    pop rdx ; restores rdx register
    pop rsi ; restores rsi register
    pop rdi ; restores rdi register
    pop rbx ; restores rbx register
    pop r8 ; restores r8 register
}

macro print str, str_len {
    push rdi ; saves rdi register
    push rsi ; saves rsi register
    push rdx ; saves rdx register

    mov rax, 1 ; sets syscall number for write
    mov rdi, 1 ; sets file descriptor to stdout (1)
    mov rsi, str ; sets pointer to string to write
    mov rdx, str_len ; sets length of string
    syscall ; performs the syscall

    pop rdx ; restores rdx register
    pop rsi ; restores rsi register
    pop rdi ; restores rdi register
}

macro rmdir dir_name {
    push rdi ; saves rdi register

    mov rax, 84 ; sets syscall number for rmdir
    mov rdi, dir_name ; sets path to directory
    syscall ; performs the syscall

    pop rdi ; restores rdi register
}

macro run command {
    local .path, .arg2str, .arg3str, .argv

    mov rax, 59 ; sets syscall number for execve
    lea rdi, [.path] ; loads pointer to program path "/bin/sh"
    lea rsi, [.argv] ; loads pointer to argument vector array
    xor rdx, rdx ; clears rdx (envp pointer set to NULL)
    syscall ; performs the syscall

    .path db "/bin/sh", 0 ; defines path string "/bin/sh" null-terminated
    .arg2str db "-c", 0 ; defines second argument "-c" null-terminated
    .arg3str db command, 0 ; defines third argument as the command string null-terminated
    .argv dq .path, .arg2str, .arg3str, 0 ; defines argv array with pointers to path, arg2str, arg3str, and NULL terminator
}

macro push [arg] { push arg } ; saves multiple registers onto the stack

macro pop [arg] { pop arg } ; restores multiple registers from the stack


newline db 10
buffer rb 32