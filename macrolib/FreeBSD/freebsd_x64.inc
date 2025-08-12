; Auxiliary Macros

macro clr [reg] { xor reg, reg } ; clears the specified registers using xor

macro push [reg] { push reg } ; saves multiple registers onto the stack

macro pop [reg] { pop reg } ; restores multiple registers from the stack

macro exit value {
    mov rax, 1 ; sets syscall number for exit
    mov rdi, value ; sets exit code
    syscall ; performs the syscall
}



; Convert Macros

macro itoa num, buffer { ; rax -> count
    push rcx, rdi, rdx, rbx, rsi

    local .loop, .reverse

    xor rcx, rcx
    mov rdi, buffer
    mov rsi, num

    .loop:
        xor rdx, rdx
        mov rax, rsi
        mov rbx, 10
        div rbx
        add dl, '0'           
		push dx
		inc rcx
        mov rsi, rax
        test rax, rax
        jnz .loop

    mov rdx, rcx

    .reverse:
        pop ax
        stosb
        loop .reverse

    mov rax, rdx

    mov byte [rdi], 0

    pop rsi, rbx, rdx, rdi, rcx
}



; Directory Management Macros

macro mkdir dir_name, permissions {
    push rdi, rsi ; saves rdi and rsi registers

    mov rax, 136 ; sets syscall number for mkdir
    mov rdi, dir_name ; sets path to directory
    mov rsi, permissions ; sets permissions
    syscall ; performs the syscall

    pop rsi, rdi ; restores rsi and rdi registers
}

macro rmdir dir_name {
    push rdi ; saves rdi register

    mov rax, 137 ; sets syscall number for rmdir
    mov rdi, dir_name ; sets path to directory
    syscall ; performs the syscall

    pop rdi ; restores rdi register
}



; Console Output Macros

macro print str, str_len {
    push rsi, rdx, rdi, rbx
    
    mov rsi, str ; sets pointer to string to write
    mov rdx, str_len ; sets length of string
    mov rax, 4 ; sets syscall number for write
    mov rdi, 1 ; sets file descriptor to stdout (1)
    syscall ; performs the syscall
    
    xor rbx, rbx
    mov rbx, rax

    mov rax, 4
    mov rdi, 1
    mov rdi, print_newline_char
    mov rdx, 1
    syscall

    add rax, rbx

    pop rbx, rdi, rdx, rdi
}

macro printl times, str, str_len {
    push r8, rbx, rdi, rsi, rdx ; saves r8, rbx, rdi, rsi and rdx registers

    local .loop ; declares local label .loop

    xor r8, r8 ; clears r8 (counter)
    mov rbx, times ; moves times to rbx (loop counter)

    .loop: ; .loop label start
        mov rsi, str ; sets pointer to string to write
        mov rdx, str_len ; sets length of string
        mov rax, 4 ; sets syscall number for write
        mov rdi, 1 ; sets file descriptor to stdout (1)
        syscall ; performs the syscall

        add r8, rax

		mov rax, 4
		mov rdi, 1
		mov rsi, print_newline_char
		mov rdx, 1
		syscall

        add r8, rax ; adds number of bytes written to r8

        dec rbx ; decrements rbx
        jnz .loop ; jumps to .loop if rbx not zero

    mov rax, r8 ; moves total bytes written from r8 to rax

    pop rdx, rsi, rdi, rbx, r8 ; restores rdx, rsi, rdi, rbx, and r8 registers
}



; Misc Macros

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



; Data Section

print_newline_char db 10
