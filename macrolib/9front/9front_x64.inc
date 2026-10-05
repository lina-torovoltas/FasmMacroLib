; Auxiliary Macros

macro clr [reg] { xor reg, reg }

macro be32 v {
    db (v) shr 24 and 0xFF, (v) shr 16 and 0xFF, (v) shr 8 and 0xFF, (v) and 0xFF
}

macro format arg& {
    match =9front, arg \{
        use64
        org 0x200000
        be32 0x8A97
        be32 _9front.text_size
        be32 0
        be32 0
        be32 0
        be32 _9front.entry
        be32 0
        be32 0
        be32 0
        be32 _9front.entry
        _9front.entry:
        postpone \{
            _9front.text_end:
            _9front.text_size = _9front.text_end - _9front.entry
        \}
    \}
    match =binary any, arg \{ purge format
        format binary any \}
}

macro exit status_msg {
    sub rsp, 16
    mov qword [rsp+8], status_msg
    mov ebp, 8
    syscall
}



; Console Output Macros

macro print str, str_len { ; total bytes written -> rax
    sub rsp, 40
    
    mov qword [rsp+24], str_len
    lea rax, [str]
    mov [rsp+16], rax
    mov qword [rsp+8], 1
    mov qword [rsp+32], -1
    mov ebp, 51
    syscall

    add rsp, 40
}
