; Auxiliary Macros

macro clr [reg] { xor reg, reg }

macro exit value {
    mov eax, 1 ; same as mov rax, 1
    mov rdi, value
    syscall
}



; Algo Macros

macro xorshift number {
    push rdx

    mov rax, number
    mov rdx, rax
    shl rax, 13
    xor rax, rdx

    mov rdx, rax
    shr rax, 7
    xor rax, rdx

    mov rdx, rax
    shl rax, 17
    xor rax, rdx

    pop rdx
}

macro xoroshiro128pp s0_addr, s1_addr { ; string result -> rax
    push rcx
    push rdx

    mov rax, [s0_addr]
    mov rcx, [s1_addr]
    lea rdx, [rax + rcx]
    rol rdx, 17
    add rdx, rax
    xor rcx, rax
    rol rax, 49
    xor rax, rcx
    mov [s0_addr], rax
    mov rax, rcx
    shl rax, 21
    xor [s0_addr], rax
    rol rcx, 28
    mov [s1_addr], rcx
    mov rax, rdx

    pop rdx
    pop rcx    
}

macro utohex number, buffer { ; string length -> rax
    push rcx rdx rdi rsi

    local .loop, .store, .reverse

    mov rdi, buffer
    mov rsi, number
    clr ecx ; same as clr rcx

    .loop:
        mov eax, esi
        and eax, 0xF
        add al, '0'
        cmp al, '9'
        jbe .store
        add al, 'a' - '9' - 1
    .store:
        push ax
        inc ecx ; same as inc rcx
        shr rsi, 4
        jnz .loop

    mov rdx, rcx

    .reverse:
        pop ax
        stosb
        loop .reverse

    mov byte [rdi], 0
    mov rax, rdx
    
    pop rsi rdi rdx rcx
}

macro utoHEX number, buffer { ; string length -> rax
    push rcx rdx rdi rsi

    local .loop, .store, .reverse

    mov rdi, buffer
    mov rsi, number
    clr ecx ; same as clr rcx

    .loop:
        mov eax, esi
        and eax, 0xF
        add al, '0'
        cmp al, '9'
        jbe .store
        add al, 'A' - '9' - 1
    .store:
        push ax
        inc ecx ; same as inc rcx
        shr rsi, 4
        jnz .loop

    mov rdx, rcx

    .reverse:
        pop ax
        stosb
        loop .reverse

    mov byte [rdi], 0
    mov rax, rdx
    
    pop rsi rdi rdx rcx
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
