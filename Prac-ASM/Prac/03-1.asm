%include "io.inc"

section .bss
    x resd 1

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here

    mov edi, 0x80000000
    mov edx, 0x80000000

    GET_UDEC 4, x
    MOV ecx, [x]
    dec ecx
    GET_DEC 4, [x]
    mov esi, [x]

    start:
        GET_DEC 4, [x]
        mov eax, [x]
        cmp eax, esi
        jl l1
        mov edi, edx
        mov edx, esi
        mov esi, eax
        jmp exit
    l1:
        cmp eax, edx
        jl l2
        mov edi, edx
        mov edx, eax
        jmp exit
    l2:
        cmp eax, edi
        jl exit
        mov edi, eax
        jmp exit
    exit:
        dec ecx
        cmp ecx, 0
        jg start
    
    PRINT_DEC 4, esi
    PRINT_CHAR ' '
    PRINT_DEC 4, edx
    PRINT_CHAR ' '
    PRINT_DEC 4, edi
    PRINT_CHAR ' '
    XOR eax, eax
    ret