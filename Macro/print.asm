; This macro only works on Linux!!!

format ELF64 executable 3
entry start



segment readable executable

macro print str, str_len {
    push rax
    push rdi
    push rsi
    push rdx

    xor rax, rax
    inc rax
    xor rdi, rdi
    inc rdi
    mov rsi, str
    mov rdx, str_len
    syscall

    pop rdx
    pop rsi
    pop rdi
    pop rax
}


start:
    print msg, msg_len

    mov     rax, 60
    xor     rdi, rdi
    syscall



segment readable writeable

msg db 'Test output string', 10
msg_len = $ - msg