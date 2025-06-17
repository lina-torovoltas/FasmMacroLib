; This macro only works on Linux!!!

format ELF64 executable 3
entry start



segment readable executable

macro printnum buffer, value {
    push r8
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
    add dl, '0'stra
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


start:
    printnum buffer, 1234
    printnum buffer, 18446744073709551615
    printnum buffer, 0
    printnum buffer, 244939252

    mov rax, 60
    xor rdi, rdi
    syscall



segment readable writeable

newline db 10
buffer rb 32