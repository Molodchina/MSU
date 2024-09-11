%include "io.inc"

section .data
    x dw 0xf1b2, 0x6342, 0x6ae6
    y dd 0x2bad4d8
    z db 0xda, 0xf2, 0xbe, 0x00, 0x1e, 0x4f

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    movzx ebx, word[z]
    mov eax, dword[x+3]
    shr eax, 24
.l1:
    cmp bx, 0
    jl .l2
    je .success
.fail:
    mov eax, 1
    ret ;Error
.l2:
    movzx ecx, byte[y+4]
    xor ecx, eax
    mov word[z+2*ecx], bx
    mov bx, word[z+3]
    cmp ecx, 4
    jb .l1
    jae .fail
.success:
    xor eax, eax 
    ret