; Auxiliary Macros

macro clr [reg] { xor reg, reg }

macro exit value {
    mov eax, 1
    push value eax
    int 80h
}



; Convert Macros

macro itoa number, buffer { ; string length -> eax
    push ecx edi esi edx ebx

    local .loop, .reverse, .skip_neg

    xor ecx, ecx
    xor ebx, ebx
    mov edi, buffer
    mov esi, number

    test esi, esi
    jns .loop
    neg esi
    mov ebx, 1
    mov byte [edi], '-'
    inc edi

    .loop:
        xor edx, edx
        mov eax, esi
        push ecx
        mov ecx, 10
        div ecx
        pop ecx
        add dl, '0'
        push dx
        inc ecx
        mov esi, eax
        test eax, eax
        jnz .loop

    mov edx, ecx

    .reverse:
        pop ax
        stosb
        loop .reverse

    mov byte [edi], 0

    test ebx, ebx
    jz .skip_neg
    inc edx

    .skip_neg:
    mov eax, edx

    pop ebx edx esi edi ecx
}

macro utoa number, buffer { ; string length -> eax
    push ecx edi esi edx ebx

    local .loop, .reverse

    xor ecx, ecx
    mov edi, buffer
    mov esi, number

    .loop:
        xor edx, edx
        mov eax, esi
        mov ebx, 10
        div ebx
        add dl, '0'
        push dx
        inc ecx
        mov esi, eax
        test eax, eax
        jnz .loop

    mov edx, ecx

    .reverse:
        pop ax
        stosb
        loop .reverse

    mov eax, edx

    mov byte [edi], 0

    pop ebx edx esi edi ecx
}



; Console Output Macros

macro print str, str_len { ; total bytes written -> eax
    push str_len str 1
    mov eax, 4
    push eax
    int 80h
    add esp, 16
}

macro println str, str_len { ; total bytes written -> eax
    push ecx

    local .newline, .done

    push str_len str 1
    mov eax, 4
    push eax
    int 80h
    add esp, 16

    mov ecx, eax

    push 1 .newline 1
    mov eax, 4
    push eax
    int 80h
    add esp, 16

    add eax, ecx

    jmp .done
    .newline db 10
    .done:

    pop ecx
}

macro printn times, str, str_len { ; total bytes written -> eax
    push ebx ecx

    local .loop

    xor ebx, ebx
    mov ecx, times

    .loop:
        println str, str_len

        add ebx, eax
        dec ecx
        jnz .loop

    mov eax, ebx

    pop ecx ebx
}



; Misc Macros

macro get_rand { ; random number -> eax
    push edx

    local .seed_retry, .rand_retry

    .seed_retry:
        rdseed edx
        jnc .seed_retry

    .rand_retry:
        rdrand eax
        jnc .rand_retry

    xor eax, edx

    pop edx
}