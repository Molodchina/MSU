%include "io.inc"

section .bss
    sum resd 1

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here

    GET_UDEC 4, eax
    
    push eax
    mov dword[sum], 0
    
    call prog
    
    add esp, 4
    
    PRINT_UDEC 4, [sum]
    
    xor eax, eax
    ret
    
    
prog:
    push ebp
    mov ebp, esp
    
    mov eax, dword[ebp+8]
    mov ecx, 3
    start:
        xor edx, edx
        div ecx
        cmp edx, 1
        je rec
        jmp exit
    rec:
        push eax
        add dword[sum], 1
        call prog
        jmp exit
    exit:
        cmp eax, 0
        jne start
        
    mov esp, ebp
    pop ebp
    ret