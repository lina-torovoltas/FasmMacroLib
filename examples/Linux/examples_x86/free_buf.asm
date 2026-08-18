; This code works only on 32-bit Linux!!!

format ELF executable 3
include '../../../macrolib/Linux/linux_x86.inc'
entry start



segment readable executable

start:
    alloc_buf 50
    mov ebx, eax

    free_buf ebx, 50 ; frees the buffer allocated with alloc_buf

    mov byte [ebx+0], 'b'
    ; ^ this instruction will cause a segfault, since the buffer has already been unmapped by clear_buf above

    mov eax, 1
    xor ebx, ebx
    int 80h