; Auxiliary Macros

macro clr [reg] { xor reg, reg }

macro exit value {
    mov eax, 1
    mov ebx, value
    int 80h
}



; Convert Macros

macro itoa number, buffer { ; string length -> eax
    push ecx edi esi edx ebx

    local .loop, .reverse, .skip_neg

    clr ecx, ebx
    mov edi, buffer
    mov esi, number

    test esi, esi
    jns .loop
    neg esi
    mov ebx, 1
    mov byte [edi], '-'
    inc edi

    .loop:
        clr edx
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

    clr ecx
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



; Directory Management Macros

macro mkdir dir_name, permissions { ; 0 or error code -> eax
    push ebx ecx

    mov eax, 39
    mov ebx, dir_name
    mov ecx, permissions
    int 80h

    pop ecx ebx
}

macro rmdir dir_name { ; 0 or error code -> eax
    push ebx

    mov eax, 40
    mov ebx, dir_name
    int 80h

    pop ebx
}



; Console Output Macros

macro print str, str_len { ; total bytes written -> eax
    push ebx ecx edx

    mov eax, 4
    mov ebx, 1
    mov ecx, str
    mov edx, str_len
    int 80h

    pop edx ecx ebx
}

macro println str, str_len { ; total bytes written -> eax
    push edx esi edi ecx ebx

    mov edx, str_len
    inc edx

    sub esp, edx

    dec edx

    mov esi, str
    mov edi, esp
    mov ecx, edx
    rep movsb

    mov byte [esp + edx], 0xA

    mov eax, 4
    mov ebx, 1
    mov ecx, esp
    inc edx
    int 80h

    add esp, edx

    pop ebx ecx edi esi edx
}

macro printn times, str, str_len {
    push edx ebx edi esi ecx

    local .exp_fill_loop, .fill_remainder, .write, .exit

    mov edx, str_len
    imul edx, times

    test edx, edx
    jz .exit

    alloc_buf edx 

    test eax, eax
    je .exit

    mov ebx, eax

    mov edi, ebx
    mov esi, str
    mov ecx, str_len
    rep movsb

    mov eax, str_len

    .exp_fill_loop:
        mov ecx, edx
        sub ecx, eax

        cmp ecx, eax
        jb .fill_remainder

        push eax
        
        mov esi, ebx
        mov edi, ebx
        add edi, eax

        mov ecx, eax
        rep movsb
        
        pop eax
        add eax, eax
        jmp .exp_fill_loop

    .fill_remainder:
        test ecx, ecx
        jz .write

        mov esi, ebx
        mov edi, ebx
        add edi, eax
        rep movsb

    .write:
        mov ecx, ebx
        mov ebx, 1
        mov eax, 4
        int 80h

    push eax
    free_buf ecx, edx
    pop eax

    .exit:

    pop ecx esi edi ebx edx
}



; Console Input Macros

macro input buffer, size { ; bytes read -> eax
    push ebx ecx edx

    mov eax, 3
    clr ebx
    mov ecx, buffer
    mov edx, size
    int 80h

    pop edx ecx ebx
}



; Process Macros

macro fork { ; child PID, 0 or error code -> eax
    mov eax, 2
    int 80h
}

macro waitpid pid { ; PID or error code -> eax
    push ebx ecx edx

    mov eax, 7
    mov ebx, pid
    xor ecx, ecx
    xor edx, edx
    int 80h

    pop edx ecx ebx
}



; Memory macros

macro alloc_buf size { ; pointer to allocated buffer -> eax
    push ebx ecx edx esi edi ebp

    mov eax, 192
    clr ebx
    mov ecx, size
    mov edx, 3
    mov esi, 34
    mov edi, -1
    clr ebp
    int 80h

    pop ebp edi esi edx ecx ebx
}

macro free_buf addr, size { ; 0 or -1 -> eax
    push ebx ecx

    mov eax, 91
    mov ebx, addr
    mov ecx, size
    int 80h

    pop ecx ebx
}

; Misc Macros

macro time { ; current time -> eax
    push ebx

    mov eax, 13
    clr ebx
    int 80h

    pop ebx

}

macro run command { ; error code -> eax
	push ebx 
	
    local .child, .error, .done
    
    fork
    test eax, eax
    jz .child
    js .error
    
    mov ebx, eax
    waitpid ebx
    jmp .done
    
    .child:
        exec command
    .error:
        exit 1
    .done:

    pop ebx
}

macro exec command { ; error code -> eax
    local .path, .arg2, .arg3, .argv

    mov eax, 11
    lea ebx, [.path]
    lea ecx, [.argv]
    xor edx, edx
    int 80h

    exit eax

    .path    db "/bin/sh", 0
    .arg2    db "-c", 0
    .arg3    db command, 0
    .argv    dd .path, .arg2, .arg3, 0
}

macro delay_ms ms { ; 0 or error code -> eax
    push ecx edx ebx

    sub esp, 8

    mov eax, ms
    mov ecx, 1000
    clr edx
    div ecx

    mov dword [esp], eax
    mov eax, edx
    imul eax, 1000000
    mov dword [esp+4], eax

    mov eax, 162
    mov ebx, esp
    clr ecx
    int 80h

    add esp, 8

    pop ebx edx ecx ebx
}

macro get_rand { ; random number -> eax
    push ebx ecx

    sub esp, 4
    mov ebx, esp

    mov eax, 355
    mov ecx, 4
    xor edx, edx
    int 80h

    mov eax, [esp]
    add esp, 4

    pop ecx ebx
}