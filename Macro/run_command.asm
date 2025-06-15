; This macro only works on Linux!!!

format ELF64 executable 3
entry start



segment readable executable

macro run_command command {
    local .path, .arg2str, .arg3str, .argv

    mov rax, 59
    lea rdi, [.path]
    lea rsi, [.argv]
    xor rdx, rdx
    syscall

    .path db "/bin/sh", 0
    .arg2str db "-c", 0
    .arg3str db command, 0
    .argv dq .path, .arg2str, .arg3str, 0
}


start:
    run_command "echo test"