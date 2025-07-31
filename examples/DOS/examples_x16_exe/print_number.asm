; This code works only on 16-bit DOS!!!

include '../../../macrolib/DOS/dos_x16.inc'
format MZ
org 100h



start:
    printnum 1234
    printnum 65535
    printnum 0
    printnum 24493

    mov ah, 4Ch
    int 21h