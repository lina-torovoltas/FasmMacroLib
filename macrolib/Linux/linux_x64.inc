; Auxiliary Macros

macro clr [reg] { xor reg, reg }

macro exit value {
    mov eax, 60 ; same as mov rax, 60
    mov rdi, value
    syscall
}



; Convert Macros

macro itoa number, buffer { ; string length -> rax
    push rcx r8 rdi rsi rdx rbx
    
    local .loop, .reverse, .skip_neg

    clr ecx ; same as clr rcx
    clr r8
    mov rdi, buffer
    mov rsi, number

    test rsi, rsi
    jns .loop
    neg rsi
    inc r8
    mov byte [rdi], '-'
	inc rdi
	
    .loop:
    	clr edx ; same as clr rdx
        mov rax, rsi
        mov ebx, 10 ; same as mov rbx, 10

        div rbx
        add dl, '0'

        push dx
        inc ecx ; same as inc rcx
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

    clr ecx ; same as clr rcx
    mov rdi, buffer
    mov rsi, number

    .loop:
        clr edx ; same as clr rdx
        mov rax, rsi
        mov ebx, 10 ; same as mov rbx, 10

        div rbx
        add dl, '0'

        push dx
        inc ecx ; same as inc rcx
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
    push rdi rsi rcx r11

    mov eax, 83 ; same as mov rax, 83
    mov rdi, dir_name
    mov rsi, permissions
    syscall

    pop r11 rcx rsi rdi
}

macro rmdir dir_name { ; 0 or error code -> rax
    push rdi rcx r11

    mov eax, 84 ; same as mov rax, 84
    mov rdi, dir_name
    syscall

    pop r11 rcx rdi
}



; Console Output Macros

macro print str, str_len { ; total bytes written -> rax
    push rdi rsi rdx rcx r11

    mov eax, 1 ; same as mov rax, 1
    mov edi, 1 ; same as mov rdi, 1
    mov rsi, str
    mov rdx, str_len
    syscall

    pop r11 rcx rdx rsi rdi
}

macro println str, str_len { ; total bytes written -> rax
    push r8 rdi rsi rdx rcx r11

    mov r8, str_len
    inc r8

    sub rsp, r8

    dec r8

    mov rsi, str
    mov rdi, rsp
    mov rcx, r8
    rep movsb

    mov byte [rsp + r8], 0xA

    mov eax, 1 ; same as mov rax, 1
    mov edi, 1 ; same as mov rdi, 1
    mov rsi, rsp
    inc r8
    mov rdx, r8
    syscall

    add rsp, r8
    
    pop r11 rcx rdx rsi rdi r8
}

macro printn times, str, str_len { ; total bytes written -> rax
    push rbx rcx rdx rsi rdi r8 r9 r10

    local .exp_fill_loop, .fill_remainder, .write, .exit

    mov r8, str_len
    imul r8, times

    test r8, r8
    jz .exit

    alloc_buf r8

    test rax, rax
    je .exit

    mov rbx, rax

    mov rdi, rbx
    mov rsi, str
    mov rcx, str_len
    rep movsb

    mov r9, str_len

    .exp_fill_loop:
        mov r10, r8
        sub r10, r9

        cmp r10, r9
        jb .fill_remainder

        mov rsi, rbx
        mov rdi, rbx
        add rdi, r9

        mov rcx, r9
        rep movsb

        add r9, r9
        jmp .exp_fill_loop

    .fill_remainder:
        test r10, r10
        jz .write

        mov rsi, rbx
        mov rdi, rbx
        add rdi, r9
        mov rcx, r10
        rep movsb

    .write:
        mov eax, 1 ; same as mov rax, 1
        mov edi, 1 ; same as mov rdi, 1
        mov rsi, rbx
        mov rdx, r8
        syscall

    mov rdi, rax
    free_buf rbx, r8
    mov rax, rdi

    .exit:

    pop r10 r9 r8 rdi rsi rdx rcx rbx
}



; Console Input Macros

macro input buffer, size { ; bytes read -> rax
    push rdi rsi rdx rcx r11

    clr eax ; same as clr rax
    clr edi ; same as clr rax
    mov rsi, buffer
    mov rdx, size
    syscall

    pop r11 rcx rdx rsi rdi 
}



; Process Macros

macro fork { ; child PID, 0 or error code -> rax
    mov rax, 57
    syscall
}

macro waitpid pid { ; PID or error code -> rax
	push rdi rsi rdx
	
    mov rax, 61
    mov rdi, pid
    clr esi ; same as clr rsi
    clr edx ; same as clr rdx
    syscall
    
	pop rdx rsi rdi
}



; Memory macros

macro alloc_buf size { ; pointer to allocated buffer -> rax
    push rdi rsi rdx r10 r8 r9 rcx r11

    mov eax, 9 ; same as mov rax, 9
    clr edi ; same as clr rdi
    mov rsi, size
    mov edx, 3 ; same as mov rdx, 3
    mov r10, 34
    mov r8, -1
    clr r9
    syscall

    pop r11 rcx r9 r8 r10 rdx rsi rdi
}

macro free_buf addr, size { ; 0 or -1 -> rax
    push rdi rsi rcx r11

    mov eax, 11 ; same as mov rax, 11
    mov rdi, addr
    mov rsi, size
    syscall

    pop r11 rcx rsi rdi
}


; Misc Macros

macro time { ; current time -> rax
    push rdi rcx r11

    mov eax, 201 ; same as mov rax, 201
    clr edi ; same as clr rdi
    syscall

    pop r11 rcx rdi

}

macro run command { ; error code -> rax
	push rbx rcx r11
	
    local .child, .error, .done
    
    fork
    test rax, rax
    jz .child
    js .error
    
    mov rbx, rax
    waitpid rbx
    jmp .done
    
    .child:
        exec command
    .error:
        exit 1
    .done:

    pop r11 rcx rbx
}

macro exec command { ; error code -> rax
    local .path, .arg2, .arg3, .argv

    mov eax, 59 ; same as mov rax, 59
    lea rdi, [.path]
    lea rsi, [.argv]
    clr edx ; same as clr rdx
    syscall

    exit rax

    .path  db "/bin/sh", 0
    .arg2  db "-c", 0
    .arg3  db command, 0
    .argv  dq .path, .arg2, .arg3, 0
}

macro delay_ms ms { ; 0 or error code -> rax
    push rcx rdx rdi rsi r11

    sub rsp, 16

    mov rax, ms
    mov ecx, 1000 ; same as mov rcx, 1000
    clr edx ; same as clr rdx
    div rcx

    mov qword [rsp], rax

    mov rax, rdx
    imul rax, 1000000
    mov qword [rsp+8], rax

    mov eax, 35 ; same as mov rax, 35
    mov rdi, rsp
    clr ecx ; same as clr rcx
    syscall

    add rsp, 16

    pop r11 rsi rdi rdx rcx
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