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
    push ebx ecx edx edi

    local .newline, .done

    mov eax, 4
    mov ebx, 1
    mov ecx, str
    mov edx, str_len
    int 80h

    xor edi, edi
    mov edi, eax

    mov eax, 4
    mov ebx, 1
    mov ecx, .newline
    mov edx, 1
    int 80h

    add eax, edi

    jmp .done
    .newline db 0xA
    
    .done:

    pop edi edx ecx ebx
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



; Console Input Macros

macro input buffer, size { ; bytes read -> eax
    push ebx ecx edx

    mov eax, 3
    mov ebx, 0
    mov ecx, buffer
    mov edx, size
    int 0x80

    pop edx ecx ebx
}



; Process Macros

macro fork { ; child PID, 0 or error code -> eax
    mov eax, 2
    int 0x80
}

macro waitpid pid { ; PID or error code -> eax
    push ebx ecx edx

    mov eax, 7
    mov ebx, pid
    xor ecx, ecx
    xor edx, edx
    int 0x80

    pop edx ecx ebx
}



; Memory macros

macro alloc_buf size { ; pointer to allocated buffer -> eax
    push ebx ecx edx esi edi ebp

    mov eax, 192
    mov ebx, 0
    mov ecx, size
    mov edx, 3
    mov esi, 34
    mov edi, -1
    mov ebp, 0
    int 0x80

    pop ebp edi esi edx ecx ebx
}



; Misc Macros

macro time { ; current time -> eax
    push ebx

    mov eax, 13
    xor ebx, ebx
    int 80h

    pop ebx

}

macro run command {
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
    int 0x80

    exit eax

    .path    db "/bin/sh", 0
    .arg2    db "-c", 0
    .arg3    db command, 0
    .argv    dd .path, .arg2, .arg3, 0
}

macro delay_ms ms { ; 0 or error code -> eax
    push ebx ecx edx esi

    sub esp, 8

    mov eax, ms
    mov ecx, 1000
    xor edx, edx
    div ecx

    mov dword [esp], eax
    mov eax, edx
    imul eax, 1000000
    mov dword [esp+4], eax

    mov eax, 162
    mov ebx, esp
    xor ecx, ecx
    int 0x80

    add esp, 8

    pop esi edx ecx ebx
}

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