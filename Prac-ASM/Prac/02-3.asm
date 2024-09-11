%include "io.inc"

section .bss
    a resd 1
    b resd 1
    c resd 1
    d resd 1
    e resd 1
    f resd 1

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    
    GET_UDEC 4, [a]
    GET_UDEC 4, [b]
    GET_UDEC 4, [c]
    GET_UDEC 4, [d]
    GET_UDEC 4, [e]
    GET_UDEC 4, [f]
    XOR eax, eax
    XOR esi, esi
    
    MOV ebx, [a]
    MOV eax, [e]
    MUL ebx
    ADD esi, eax
    MOV eax, [f]
    MUL ebx
    ADD esi, eax
    
    MOV ebx, [b]
    MOV eax, [d]
    MUL ebx
    ADD esi, eax
    MOV eax, [f]
    MUL ebx
    ADD esi, eax
    
    MOV ebx, [c]
    MOV eax, [d]
    MUL ebx
    ADD esi, eax
    MOV eax, [e]
    MUL ebx
    ADD esi, eax
    
    PRINT_DEC 4, esi
    
    XOR eax, eax
    ret