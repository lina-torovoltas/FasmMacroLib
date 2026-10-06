; Auxiliary Macros

macro clr [reg] { xor reg, reg }

macro exit value {
    mov rax, 1
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

macro itoa number, buffer { ; string length -> rax
    push rcx r8 rdi rsi rdx rbx
    
    local .loop, .reverse, .skip_neg

    clr rcx
    clr r8
    mov rdi, buffer
    mov rsi, number

    test rsi, rsi
    jns .loop
    neg rsi
    mov r8, 1
    mov byte [rdi], '-'
	inc rdi
	
    .loop:
    	xor rdx, rdx
        mov rax, rsi
        mov rbx, 10
        div rbx
        add dl, '0'
        push dx
        inc rcx
        mov rsi, rax
        test rax, rax
        jnz .loop

    mov rdx, rcx

    .reverse:
        pop ax
        stosb
        loop .reverse

    mov byte [rdi], 0

    test r8, r8
    jz .skip_neg
    inc rdx

    .skip_neg:
    mov rax, rdx
    
    pop rbx rdx rsi rdi r8 rcx
}

macro utoa number, buffer { ; string length -> rax
    push rcx rdi rsi rdx rbx

    local .loop, .reverse

    clr rcx
    mov rdi, buffer
    mov rsi, number

    .loop:
        clr rdx
        mov rax, rsi
        mov rbx, 10
        div rbx
        add dl, '0'
        push dx
        inc rcx
        mov rsi, rax
        test rax, rax
        jnz .loop

    mov rdx, rcx

    .reverse:
        pop ax
        stosb
        loop .reverse

    mov rax, rdx

    mov byte [rdi], 0

    pop rbx rdx rsi rdi rcx
}



; Directory Management Macros

macro mkdir dir_name, permissions { ; 0 or error code -> rax
    push rdi rsi rcx r11 r8 r9 r10

    mov rax, 136
    mov rdi, dir_name
    mov rsi, permissions
    syscall

    pop r10 r9 r8 r11 rcx rsi rdi
}

macro rmdir dir_name { ; 0 or error code -> rax
    push rdi rcx r11 r8 r9 r10

    mov rax, 137
    mov rdi, dir_name
    syscall

    pop r10 r9 r8 r11 rcx rdi
}



; Console Output Macros

macro print str, str_len { ; total bytes written -> rax
    push rdi rsi rdx rcx r8 r9 r10 r11

    mov rax, 4
    mov rdi, 1
    mov rsi, str
    mov rdx, str_len
    syscall

    pop r11 r10 r9 r8 rcx rdx rsi rdi
}

macro println str, str_len { ; total bytes written -> rax
    push rdi rsi rdx rbx rcx r8 r9 r10 r11

    local .newline, .done

    mov rax, 4
    mov rdi, 1
    mov rsi, str
    mov rdx, str_len
    syscall

    mov rbx, rax

    mov rax, 4
    mov rdi, 1
    mov rsi, .newline
    mov rdx, 1
    syscall

    add rax, rbx

    jmp .done
    .newline db 0xA
    .done:

    pop r11 r10 r9 r8 rcx rbx rdx rsi rdi
}

macro printn times, str, str_len { ; total bytes written -> rax
    push rbx rcx

    local .loop

    xor rbx, rbx
    mov rcx, times

    .loop:
        println str, str_len

        add rbx, rax
        dec rcx
        jnz .loop

    mov rax, rbx

    pop rcx rbx
}



; Console Input Macros

macro input buffer, size { ; bytes read -> rax
    push rdi rsi rdx rcx r8 r9 r10 r11

    mov rax, 3
    mov rdi, 0
    mov rsi, buffer
    mov rdx, size
    syscall

    pop r11 r10 r9 r8 rcx rdx rsi rdi
}



; Process Macros

macro fork { ; PID or error code -> rax, 0=parent/1=child -> rdx
    push rcx r8 r9 r10 r11

    mov rax, 2
    syscall

    pop r11 r10 r9 r8 rcx
}

macro waitpid pid { ; PID or error code -> rax
    push rdi rsi rdx rcx r8 r9 r10 r11

    mov rax, 7
    mov rdi, pid
    xor rsi, rsi
    xor rdx, rdx
    syscall

    pop r11 r10 r9 r8 rcx rdx rsi rdi
}



; Misc Macros

macro run command {
    push rdx rbx

    local .child, .error, .done

    fork
    test rax, rax
    js .error
    test rdx, rdx
    jnz .child

    mov rbx, rax
    waitpid rbx
    jmp .done

    .child:
        exec command
    .error:
        exit 1
    .done:

    pop rbx rdx
}

macro exec command { ; error code -> rax
    local .path, .arg2, .arg3, .argv

    mov rax, 59
    lea rdi, [.path]
    lea rsi, [.argv]
    xor rdx, rdx
    syscall

    exit rax

    .path  db "/bin/sh", 0
    .arg2  db "-c", 0
    .arg3  db command, 0
    .argv  dq .path, .arg2, .arg3, 0
}

macro get_rand { ; random number -> rax
    push rdx

    local .seed_retry, .rand_retry

    .seed_retry:
        rdseed rdx
        jnc .seed_retry

    .rand_retry:
        rdrand rax
        jnc .rand_retry

    xor rax, rdx

    pop rdx
}
