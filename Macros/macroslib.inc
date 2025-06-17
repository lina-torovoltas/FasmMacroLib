macro clr reg { xor reg,reg }

macro exit value {
    mov rax, 60
    mov rdi, value
    syscall
}

macro mkdir dir_name, permissions {
    push rdi
    push rsi

    mov rax, 83
    mov rdi, dir_name
    mov rsi, permissions
    syscall

    pop rsi
    pop rdi
}

macro time {
    push rdi

    mov rax, 201
    xor rdi, rdi
    syscall

    pop rdi

}

macro printnum value {
    push rdi
    push rcx
    push rbx
    push rdx
    push rsi
    push r8

    local .convert

    mov rax, value
    mov rdi, buffer
    add rdi, 31
    mov byte [rdi], 0

    mov rcx, 10
    mov rbx, rax

.convert:
    dec rdi
    xor rdx, rdx
    div rcx
    add dl, '0'
    mov [rdi], dl
    test rax, rax
    jnz .convert

    mov rsi, rdi
    mov rax, 1
    mov rdi, 1
    mov rdx, buffer
    add rdx, 32
    sub rdx, rsi
    syscall

    xor r8, r8
    mov r8, rax

    mov rax, 1
    mov rdi, 1
    mov rsi, newline
    mov rdx, 1
    syscall

    add rax, r8

    pop r8
    pop rsi
    pop rdx
    pop rbx
    pop rcx
    pop rdi
}

macro printtim times, str, str_len {
    local .loop

    push r8
    push rbx
    push rdi
    push rsi
    push rdx

    xor r8, r8
    mov rbx, times

    .loop:
        mov rax, 1
        mov rdi, 1
        mov rsi, str
        mov rdx, str_len
        syscall

        add r8, rax

        dec rbx
        jnz .loop

    mov rax, r8

    pop rdx
    pop rsi
    pop rdi
    pop rbx
    pop r8
}

macro print str, str_len {
    push rdi
    push rsi
    push rdx

    mov rax, 1
    mov rdi, 1
    mov rsi, str
    mov rdx, str_len
    syscall

    pop rdx
    pop rsi
    pop rdi
}

macro rmdir dir_name {
    push rdi

    mov rax, 84
    mov rdi, dir_name
    syscall

    pop rdi
}

macro run command {
    local .path, .arg2str, .arg3str, .argv

    mov rax, 59
    lea rdi, [.path]
    lea rsi, [.argv]
    xor rdx, rdx
    syscall

    .path db "/bin/sh", 0
    .arg2str db "-c", 0
    .arg3str db command, 0
    .argv dq .path, .arg2str, .arg3str, 0
}

macro push [arg] { push arg }

macro pop [arg] { pop arg }

newline db 10
buffer rb 32