%include "io.inc"

section .bss
    a resd 1
    b resd 1
    c resd 1
    v resd 1

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    
    GET_DEC 4, [a]
    GET_DEC 4, [b]
    GET_DEC 4, [c]
    GET_DEC 4, [v]
    XOR eax, eax
    XOR edx, edx
    
    MOV eax, [a]
    MOV ebx, [v]
    DIV ebx
    MOV esi, edx
    MUL dword[b]
    MUL dword[c]
    
    MOV ecx, eax
    MOV eax, esi
    MUL dword[b]
    MUL dword[c]
    DIV ebx
    ADD eax, ecx
    
    PRINT_DEC 4, eax
    
    XOR eax, eax
    ret