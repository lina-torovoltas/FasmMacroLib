; This code works only on 64-bit Linux!!!

format ELF64 executable 3
include '../../../macrolib/Linux/linux_x64.inc'
entry start



segment readable executable

start:
    alloc_buf 50
    mov rbx, rax

    free_buf rbx, 50 ; frees the buffer allocated with alloc_buf

    mov byte [rbx+0], 'b'
    ; ^ this instruction will cause a segfault, since the buffer has already been unmapped by clear_buf above

    mov rax, 60
    xor rdi, rdi
    syscall