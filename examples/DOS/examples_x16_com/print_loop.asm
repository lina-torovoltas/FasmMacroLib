; This code works only on 16-bit DOS!!!

include '../../../macrolib/DOS/dos_x16.inc'
org 100h
use16



start:
    printn 2, msg1
    printn 3, msg2

    mov ah, 76
    int 21h



msg1 db 'This message will be repeated two times', '$'
msg2 db 'This message will be repeated three times', '$'
