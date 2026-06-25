; This code works only on 64-bit Linux!!!

format ELF64 executable 3
include '../../../macrolib/Linux/linux_x64.inc'
entry start



segment readable executable

start:
    alloc_buf 50
    mov rbx, rax

    mov byte [rbx+0], 'b'
    mov byte [rbx+1], 'u'
    mov byte [rbx+2], 'f'
    mov byte [rbx+3], 'f'
    mov byte [rbx+4], 'e'
    mov byte [rbx+5], 'r'
    mov byte [rbx+6], 0xA

    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    mov rdx, 7
    syscall
    
    alloc_buf 32
    mov qword [rax], 42
    mov rdi, [rax]
    mov rax, 60
    syscall
