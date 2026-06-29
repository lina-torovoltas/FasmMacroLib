; This code works only on 16-bit DOS!!!

include '../../../macrolib/DOS/dos_x16.inc'
org 100h
use16



start:
    print msg

    mov ah, 76
    int 21h



msg db 'Test output string', 0xD, 0xA, '$'