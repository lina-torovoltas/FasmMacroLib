; This macro only works on Linux!!!

format ELF64 executable 3
entry start



segment readable executable

macro print_times times, str, str_len {
    push rax
    push rbx
    push rdi
    push rsi
    push rdx

    local .loop

    mov rbx, times
  .loop:
    xor rax, rax
    inc rax
    xor rdi, rdi
    inc rdi
    mov rsi, str
    mov rdx, str_len
    syscall

    dec rbx
    jnz .loop

    pop rdx
    pop rsi
    pop rdi
    pop rbx
    pop rax
}


start:
    print_times 2, msg1, msg1_len
    print_times 3, msg2, msg2_len

    mov rax, 60
    xor rdi, rdi
    syscall



segment readable writeable

msg1 db 'This message will be repeated two times', 10
msg1_len = $ - msg1

msg2 db 'This message will be repeated three times', 10
msg2_len = $ - msg2