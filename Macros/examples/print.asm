; This macro only works on Linux!!!

format ELF64 executable 3
entry start



segment readable executable

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


start:
    print msg, msg_len

    mov rax, 60
    xor rdi, rdi
    syscall



segment readable writeable

msg db 'Test output string', 10
msg_len = $ - msg