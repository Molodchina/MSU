%include "io.inc"

section .bss
    x resd 1

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    
    xor eax, eax
    xor edi, edi
    
    mov ecx, 31

    GET_UDEC 4, [x]
    mov esi, dword[x]
    
    start:
        bt esi, edi
        jc l1
        jmp exit
    l1:
        inc eax
        jmp exit
    exit:
        inc edi
        dec ecx
        cmp ecx, 0
        jg start
    
    PRINT_UDEC 4, eax
    
    XOR eax, eax
    ret