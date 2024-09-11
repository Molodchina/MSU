%include "io.inc"

extern scanf
extern printf

section .bss
    temp resd 1

section .rodata
    fin db "%u", 0
    fout db `0x%08X\n`, 0

section .text
global CMAIN
CMAIN:
    sub esp, 16
    while:
    mov dword[esp+4], temp
    mov dword[esp], fin
    call scanf
    
    cmp eax, -1
    je .end
    
    mov eax, dword[temp]
    mov dword[esp+4], eax
    mov dword[esp], fout
    call printf
    
    jmp while
    .end:
    
    add esp, 16
    
    xor eax, eax
    ret