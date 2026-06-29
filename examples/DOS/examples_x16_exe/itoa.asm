; This code works only on 16-bit DOS!!!

include '../../../macrolib/DOS/dos_x16.inc'
format MZ
org 100h



start:
    itoa -1, buffer
    println buffer

    mov ax, 42
    itoa ax, buffer
    println buffer

    itoa [number], buffer
    println buffer

    itoa -12345, buffer
    printn 2, buffer

    mov ah, 76
    xor al, al
    int 21h



buffer rb 10
number dw -32768