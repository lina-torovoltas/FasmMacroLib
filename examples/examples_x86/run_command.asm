; This code works only on 64-bit Linux!!!

format ELF executable 3
include '../../macrolib/macrolib_x86.inc'
entry start



segment readable executable

start:
    run "echo test"