; This macro only works on Linux!!!

format ELF64 executable 3
entry start



segment readable executable

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


start:
    printtim 2, msg1, msg1_len
    printtim 3, msg2, msg2_len

    mov rax, 60
    xor rdi, rdi
    syscall



segment readable writeable

msg1 db 'This message will be repeated two times', 10
msg1_len = $ - msg1

msg2 db 'This message will be repeated three times', 10
msg2_len = $ - msg2