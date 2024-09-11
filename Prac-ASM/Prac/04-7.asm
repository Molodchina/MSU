%include "io.inc"

section .data
    d dd 2011
    c dd 1
    i dd 0

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    
    xor esi, esi
    GET_DEC 4, [c]
    GET_DEC 4, edi
    GET_DEC 4, eax
    ;mov dword[c], 10
    ;mov edi, 1
    ;mov eax, 444
    
    xor edx, edx
    div dword[d]
    mov eax, edx
  
.find:
    push eax
    push eax
    
    call prog
    add esp, 8
    
    xor edx, edx
    div dword[d]
    mov eax, edx
    
    dec edi
    cmp edi, 0
    jne .find
    
    PRINT_DEC 4, edx
    
    xor eax, eax
    ret

prog:
    push ebp
    mov ebp, esp
    
    mov eax, dword[ebp+8]
    mov ebx, dword[ebp+12]
    mov ecx, 1
    mul ebx

    .get_num:
        xor edx, edx
        div dword[c]
        push edx
        imul ecx, dword[c]
        
        cmp eax, 0
        jne .get_num
    
    mov ebx, 0
    mov eax, ecx
    xor edx, edx
    div dword[c]
    mov dword[i], eax
    mov ecx, 1
    .get_back:
        pop eax
        mul ecx
        add ebx, eax
        imul ecx, dword[c]
        
        cmp dword[i], ecx
        jge .get_back
    
    mov eax, ebx
    mov esp, ebp
    pop ebp
    ret