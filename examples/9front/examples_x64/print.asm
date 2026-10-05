; This code works only on 64-bit 9front!!!

include  '../../../macrolib/9front/9front_x64.inc'
format 9front



print msg, msg_len

sub rsp, 16
mov qword [rsp+8], 0
mov ebp, 8
syscall



msg db 'Test output string', 0xA
msg_len = $ - msg
