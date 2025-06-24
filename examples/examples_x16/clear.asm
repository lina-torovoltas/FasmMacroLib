; This code works only on 16-bit DOS!!!

include '../../macrolib/macrolib_x16.inc'
org 100h
use16



clr ah
mov ah, 4Ch
int 21h