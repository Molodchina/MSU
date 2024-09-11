%include "io.inc"

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    
    GET_DEC 4, eax
    GET_DEC 4, ebx
    ;mov eax, 7
    ;mov ebx, 2
    
    push ebx
    push eax
    
    call prog
    add esp, 8
    
    PRINT_UDEC 4, eax
    
    xor eax, eax
    ret

prog:
    push ebp
    mov ebp, esp
    push esi
    push edi
    
    mov eax, dword[ebp+8]
    mov ebx, dword[ebp+12]
    
    mov ecx, 0
    mov edi, eax
    .get_num:
        xor edx, edx
        idiv ebx
        add ecx, edx
        cmp eax, 0
        jne .get_num
    .cmp_num:
        add edi, ecx
        mov eax, ecx
        mov ecx,0
        mov edx, esi
        mov esi, eax
        
        cmp eax, edx
        jne .get_num
    
    mov eax, edi
    pop edi
    pop esi
    mov esp, ebp
    pop ebp
    ret