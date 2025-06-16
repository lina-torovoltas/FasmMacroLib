; This macro only works on Linux!!!

format ELF64 executable 3
entry start



segment readable executable

macro print_number buffer {
    push rdi
    push rsi
    push rdx
    push rcx
    push rbx
    push rax

    local .convert

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
    xor rax, rax
    inc rax
    xor rdi, rdi
    inc rdi
    mov rdx, buffer
    add rdx, 32
    sub rdx, rsi
    syscall

    xor rax, rax
    inc rax
    xor rdi, rdi
    inc rdi
    mov rsi, newline
    mov rdx, newline_len
    syscall

    pop rax
    pop rbx
    pop rcx
    pop rdx
    pop rsi
    pop rdi
}


start:
    mov rax, 1234
    print_number buffer

    mov rax, 18446744073709551615
    print_number buffer

    mov rax, 0
    print_number buffer

    mov rax, 244939252
    print_number buffer

    mov rax, 60
    xor rdi, rdi
    syscall



segment readable writeable

newline db 10
newline_len = $ - newline

buffer rb 32