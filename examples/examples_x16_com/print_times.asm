; This code works only on 16-bit DOS!!!

include '../../macrolib/macrolib_x16.inc'
COM



printtim 2, msg1
printtim 3, msg2

mov ah, 4Ch
int 21h



msg1 db 'This message will be repeated two times', 0Ah, '$'
msg2 db 'This message will be repeated three times', 0Ah, '$'