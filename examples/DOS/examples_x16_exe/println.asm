; This code works only on 16-bit DOS!!!

include '../../../macrolib/DOS/dos_x16.inc'
format MZ
org 100h



start:
    println msg

    mov ah, 76
    int 21h



msg db 'Test output string', '$'