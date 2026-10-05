; Auxiliary Macros

macro clr [reg] { xor reg, reg }

macro exit value {
    mov eax, 1 ; same as mov rax, 1
    mov rdi, value
    syscall
}



; Console Output Macros

macro print str, str_len { ; total bytes written -> rax
    push rdi rsi rdx rcx r11

    mov rax, 0x21000004
    mov edi, 1 ; same as mov rdi, 1
    mov rsi, str
    mov rdx, str_len
    syscall

    pop r11 rcx rdx rsi rdi
}
