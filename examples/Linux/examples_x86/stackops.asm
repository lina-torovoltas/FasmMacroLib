; This code works only on 32-bit Linux!!!

format ELF executable 3
include '../../../macrolib/Linux/linux_x86.inc'
entry start



segment readable executable

macro print str, str_len {
    push ebx, ecx, edx

    mov eax, 4
    mov ebx, 1
    mov ecx, str
    mov edx, str_len
    int 80h

    pop edx, ecx, ebx
}


start:
    print msg, msg_len

    mov eax, 1
    xor ebx, ebx
    int 80h



segment readable writeable

msg db 'Test output string', 10
msg_len = $ - msg
