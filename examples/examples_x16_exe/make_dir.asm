; This code works only on 16-bit DOS!!!

include '../../macrolib/macrolib_x16.inc'
EXE



mkdir name

mov ah, 4Ch
int 21h



name db 'test',0 