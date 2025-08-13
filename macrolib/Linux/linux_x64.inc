; Auxiliary Macros

macro clr [reg] { xor reg, reg } ; clears the specified registers using xor

macro push [reg] { push reg } ; saves multiple registers onto the stack

macro pop [reg] { pop reg } ; restores multiple registers from the stack

macro exit value {
    mov rax, 60 ; sets syscall number for exit
    mov rdi, value ; sets exit code
    syscall ; performs the syscall
}



; Convert Macros

macro itoa number, buffer { ; string length -> rax
    push rcx, rdi, rsi, rdx, rbx ; saves rcx, rdi, rsi, rdx and rbx registers

    local .loop, .reverse ; declares local labels .loop and .reverse

    xor rcx, rcx ; clears rcx (loop counter)
    mov rdi, buffer ; sets rdi to point to buffer start
    mov rsi, number ; moves input number to rsi 

    .loop: ; .loop label start
        xor rdx, rdx ; clears rdx (high dividend part)
        mov rax, rsi ; moves number to rax for division
        mov rbx, 10 ; sets divisor to 10 (decimal base)
        div rbx ; divides combined value in rdx:rax by rbx, quotient stored in rax, remainder stored in rdx
        add dl, '0' ; converts remainder to ASCII digit
        push dx ; pushes digit to stack
        inc rcx ; increments loop counter
        mov rsi, rax ; updates number with quotient
        test rax, rax ; tests if quotient is zero
        jnz .loop ; continues loop if not zero

    mov rdx, rcx ; moves string length to rdx

    .reverse: ; .reverse label start
        pop ax ; pops digit from stack into ax
        stosb ; stores al at [rdi] and increments rdi
        loop .reverse ; loops rcx times to write digits in order

    mov rax, rdx ; moves string length to rax

    mov byte [rdi], 0 ; writes null terminator at end of string

    pop rbx, rdx, rsi, rdi, rcx ; restores rbx, rdx, rsi, rdi and rcx registers
}



; Directory Management Macros

macro mkdir dir_name, permissions { ; error code -> rax
    push rdi, rsi ; saves rdi and rsi registers

    mov rax, 83 ; sets syscall number for mkdir
    mov rdi, dir_name ; sets path to directory
    mov rsi, permissions ; sets permissions
    syscall ; performs the syscall

    pop rsi, rdi ; restores rsi and rdi registers
}

macro rmdir dir_name { ; error code -> rax
    push rdi ; saves rdi register

    mov rax, 84 ; sets syscall number for rmdir
    mov rdi, dir_name ; sets path to directory
    syscall ; performs the syscall

    pop rdi ; restores rdi register
}



; Console Output Macros

macro print str, str_len { ; total bytes written -> rax
    push rsi, rdx, rdi, rbx ; saves rsi, rdx, rdi and rbx registers

    mov rsi, str ; sets pointer to string to write
    mov rdx, str_len ; sets length of string
    mov rax, 1 ; sets syscall number for write
    mov rdi, 1 ; sets file descriptor to stdout (1)
    syscall ; performs the syscall

    xor rbx, rbx ; clears rbx (counter)
    mov rbx, rax ; adds number of bytes written to rbx

    mov rax, 1 ; sets syscall number for write
    mov rdi, 1 ; sets file descriptor to stdout (1)
    mov rsi, print_newline_char ; pointer to newline char
    mov rdx, 1 ; length 1 byte
    syscall ; performs the syscall

    add rax, rbx ; adds number of bytes written to rax

    pop rbx, rdi, rdx, rsi ; restores rbx, rdi, rdx and rsi registers
}

macro printl times, str, str_len { ; total bytes written -> rax
    push r8, rbx, rsi, rdx, rdi ; saves r8, rbx, rsi, rdx and rdi registers

    local .loop ; declares local label .loop

    xor r8, r8 ; clears r8 (counter)
    mov rbx, times ; moves times to rbx (loop counter)

    .loop: ; .loop label start
        mov rsi, str ; sets pointer to string to write
        mov rdx, str_len ; sets length of string
        mov rax, 1 ; sets syscall number for write
        mov rdi, 1 ; sets file descriptor to stdout (1)
        syscall ; performs the syscall

        add r8, rax ; adds number of bytes written to r8

        mov rax, 1 ; sets syscall number for write
        mov rdi, 1 ; sets file descriptor to stdout (1)
        mov rsi, print_newline_char ; pointer to newline char
        mov rdx, 1 ; length 1 byte
        syscall ; performs the syscall

        add r8, 1 ; adds 1 byte written to r8

        dec rbx ; decrements rbx
        jnz .loop ; jumps to .loop if rbx not zero

    mov rax, r8 ; moves total bytes written from r8 to rax

    pop rdi, rdx, rsi, rbx, r8 ; restores rdi, rdx, rsi, rbx and r8 registers
}



; Misc Macros

macro time { ; current time -> rax
    push rdi ; saves rdi register

    mov rax, 201 ; sets syscall number for time
    xor rdi, rdi ; sets argument to NULL (store time in rax)
    syscall ; performs the syscall

    pop rdi ; restores rdi register

}

macro run command { ; error code -> rax
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
