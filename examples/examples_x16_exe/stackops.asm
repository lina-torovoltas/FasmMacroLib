; This code works only on 16-bit DOS!!!

include '../../macrolib/macrolib_x16.inc'
format MZ
org 100h



macro print msg {
    push dx, ax

    mov ah, 9
    mov dx, msg
    int 21h

    pop ax, dx
}


start:
    print msg

    mov ah, 4Ch
    int 21h



msg db 'Test output string', 0Ah, '$'