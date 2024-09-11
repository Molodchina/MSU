%include "io.inc"

section .bss
    m resd 1
    d resd 1

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    
    GET_DEC 4, [m]
    GET_DEC 4, [d]
    XOR eax, eax
    XOR edx, edx
    
    MOV eax, [m]
    SUB eax, 1
    MOV ebx, 2
    DIV ebx
    MOV esi, eax
    MOV eax, [m]
    SUB eax, 1
    MOV ebx, 41
    MUL ebx
    ADD eax, esi
    ADD eax, [d]
    
    PRINT_DEC 4, eax
    
    XOR eax, eax
    ret