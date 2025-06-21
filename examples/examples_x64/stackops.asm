; This code works only on 64-bit Linux!!!

format ELF64 executable 3
include '../../macrolib/macrolib_x64.inc'
entry start



segment readable executable

macro print str, str_len {
    push rax, rdi, rsi, rdx

    mov rax, 1
    mov rdi, 1
    mov rsi, str
    mov rdx, str_len
    syscall

    pop rdx, rsi, rdi, rax
}


start:
    print msg, msg_len

    mov rax, 60
    xor rdi, rdi
    syscall



segment readable writeable

msg db 'Test output string', 10
msg_len = $ - msg