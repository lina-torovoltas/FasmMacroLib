; This code works only on 32-bit Linux!!!

format ELF executable 3
include '../../../macrolib/Linux/linux_x86.inc'
entry start



segment readable executable

start:
    alloc_buf 50
    mov edi, eax

    mov byte [edi+0], 'b'
    mov byte [edi+1], 'u'
    mov byte [edi+2], 'f'
    mov byte [edi+3], 'f'
    mov byte [edi+4], 'e'
    mov byte [edi+5], 'r'
    mov byte [edi+6], 0xA

    mov eax, 4
    mov ebx, 1
    mov ecx, edi
    mov edx, 7
    int 80h

    alloc_buf 32
    mov dword [eax], 42
    mov ebx, [eax]
    mov eax, 1
    int 80h
