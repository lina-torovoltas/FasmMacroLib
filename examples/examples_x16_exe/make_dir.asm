format MZ
org 100h

start:
    mov ah, 39h         ; функция создания каталога
    mov dx, name        ; путь к папке
    int 21h             ; вызов DOS

    mov ah, 4Ch
    int 21h

name db 'test', 0