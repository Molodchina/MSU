%include "io.inc"

section .bss
    a resd 1
    b resd 1

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    
    xor eax, eax
    xor edi, edi
    
    mov ecx, 1

    GET_UDEC 4, [a]
    GET_UDEC 4, [b]
    mov esi, dword[a]
    mov edi, dword[b]
    
    start:
        cmp esi, edi
        jl switch
        sub esi, edi
        jmp exit
    switch:
        mov eax, esi
        mov esi, edi
        mov edi, eax
        sub esi, edi
        jmp exit
    exit:
        cmp esi, edi
        jne start
    
    PRINT_UDEC 4, esi
    
    XOR eax, eax
    ret