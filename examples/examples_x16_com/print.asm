; This code works only on 16-bit DOS!!!

include '../../macrolib/macrolib_x16.inc'
org 100h
use16



start:
    print msg

    mov ah, 4Ch
    int 21h



msg db 'Test output string', 0Ah, '$'