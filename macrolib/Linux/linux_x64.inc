; Auxiliary Macros

macro clr [reg] { xor reg, reg }

macro exit value {
    mov rax, 60
    mov rdi, value
    syscall
}



; Convert Macros

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
    push rdi rsi

    mov rax, 83
    mov rdi, dir_name
    mov rsi, permissions
    syscall

    pop rsi rdi
}

macro rmdir dir_name { ; 0 or error code -> rax
    push rdi

    mov rax, 84
    mov rdi, dir_name
    syscall

    pop rdi
}



; Console Output Macros

macro print str, str_len { ; total bytes written -> rax
    push rdi rsi rdx rcx

    mov rax, 1
    mov rdi, 1
    mov rsi, str
    mov rdx, str_len
    syscall

    pop rcx rdx rsi rdi
}

macro println str, str_len { ; total bytes written -> rax
    push rdi rsi rdx rbx rcx

    local .newline, .done

	mov rax, 1
	mov rdi, 1
    mov rsi, str
    mov rdx, str_len
    syscall

    xor rbx, rbx
    mov rbx, rax

    mov rax, 1
    mov rdi, 1
    mov rsi, .newline
    mov rdx, 1
    syscall

    add rax, rbx
    
    jmp .done
    .newline db 10
    
    .done:
    
    pop rcx rbx rdx rsi rdi
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

    pop rbx rcx
}



; Console Input Macros

macro input buffer, size { ; bytes read -> rax
    push rdi rsi rdx

    mov rax, 0
    mov rdi, 0
    mov rsi, buffer
    mov rdx, size
    syscall

    pop rdx rsi rdi 
}



; Process Macros

macro fork { ; child PID, 0 or error code -> rax
    mov rax, 57
    syscall
}

macro waitpid pid { ; PID or error code -> rax
	push rdi rsi rdx
	
    mov rdi, pid
    mov rax, 61
    xor rsi, rsi
    xor rdx, rdx
    syscall
    
	pop rdx rsi rdi
}



; Memory macros

macro alloc_buf size { ; pointer to allocated buffer -> rax
    push rdi rsi rdx r10 r8 r9

    mov rax, 9
    mov rdi, 0
    mov rsi, size
    mov rdx, 3
    mov r10, 34
    mov r8, -1
    mov r9, 0
    syscall

    pop r9 r8 r10 rdx rsi rdi
}



; Misc Macros

macro time { ; current time -> rax
    push rdi

    mov rax, 201
    xor rdi, rdi
    syscall

    pop rdi

}

macro run command {
	push rbx 
	
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

    pop rbx
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

macro delay_ms ms { ; 0 or error code -> rax
    push rcx rdx rdi rsi

    sub rsp, 16

    mov rax, ms
    mov rcx, 1000
    xor rdx, rdx
    div rcx

    mov qword [rsp], rax

    mov rax, rdx
    imul rax, 1000000
    mov qword [rsp+8], rax

    mov rax, 35
    mov rdi, rsp
    xor rsi, rsi
    syscall

    add rsp,16

    pop rsi rdi rdx rcx
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