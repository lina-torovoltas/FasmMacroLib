; This code works only on 16-bit DOS!!!

include '../../../macrolib/DOS/dos_x16.inc'
org 100h
use16



start:
    utoa 0, buffer
    println buffer

    mov ax, 42
    utoa ax, buffer
    println buffer

    utoa [number], buffer
    println buffer

    utoa 12345, buffer
    printn 2, buffer

    mov ah, 76
    xor al, al
    int 21h



buffer rb 10
number dw 65535