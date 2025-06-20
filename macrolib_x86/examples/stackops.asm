; This code works only on 64-bit Linux!!!

format ELF executable 3
include '../macrolib.inc'
entry start



segment readable executable

macro print str, str_len {
    push ebx, ecx, edx

    mov eax, 4
    mov ebx, 1
    mov ecx, str
    mov edx, str_len
    int 0x80

    pop edx, ecx, ebx
}


start:
    print msg, msg_len

    mov eax, 1
    xor ebx, ebx
    int 0x80



segment readable writeable

msg db 'Test output string', 10
msg_len = $ - msg