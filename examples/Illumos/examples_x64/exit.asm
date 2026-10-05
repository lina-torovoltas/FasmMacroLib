; This code works only on 64-bit Illumos!!!

format ELF64 executable 6
include '../../../macrolib/Illumos/illumos_x64.inc'
entry start



segment readable executable

start:
    exit 0
