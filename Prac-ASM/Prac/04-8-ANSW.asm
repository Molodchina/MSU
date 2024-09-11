prog:
    push ebp
    mov ebp, esp
    
    mov eax, dword[ebp+8]
    mov ebx, dword[ebp+12]
    
    xor ecx, ecx
    mov edx, eax
    push eax
    .get_num:
        mov dword[s1], edx
        xor edx, edx
        div ebx
        add ecx, edx
        cmp eax, 0
        jne .get_num
    .cmp_num:
        inc dword[c]
        push ecx
        
        mov eax, ecx
        mov edx, ecx
        xor ecx, ecx
        
        cmp eax, dword[s1]
        jne .get_num
    
    mov ecx, dword[c]
    xor eax, eax
    .sum_num:
        pop edx
        add eax, edx
        dec ecx
        cmp ecx, 0
        jne .sum_num
    
    PRINT_DEC 4, eax
    mov esp, ebp
    pop ebp
    ret