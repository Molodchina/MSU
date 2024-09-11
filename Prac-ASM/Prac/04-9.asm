%include "io.inc"

section .bss
    c resd 1

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    
    GET_DEC 4, eax
    ;mov eax, 14
    
    push eax
    
    call prog
    add esp, 4
    
    PRINT_UDEC 4, eax
    
    xor eax, eax
    ret

prog:
    push ebp
    mov ebp, esp
    
    push edi
    push esi
    
    mov edi, dword[ebp+8]
    
    mov esi, 0
    .get_num:
        inc esi
        
        mov ecx, 1
        mov ebx, esi
        dec ebx
        
        cmp edi, 0
        jne .find
    .find:
        mov eax, esi
        xor edx, edx
        div 
        
        inc ebx
        cmp
        jmp .get_num
    
    .exit:
        
    
    mov eax, edi
    pop edi
    pop esi
    mov esp, ebp
    pop ebp
    ret