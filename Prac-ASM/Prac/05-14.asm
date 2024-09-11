%include "io.inc"

CEXTERN malloc
CEXTERN free
CEXTERN fopen
CEXTERN fclose
CEXTERN fscanf
CEXTERN fprintf

section .rodata
    iform db '%d', 0
    oform db '%d ', 0
    iname db 'input.txt', 0
    imode db 'r', 0
    oname db 'output.txt', 0
    omode db 'w', 0

section .bss
    node_key resd 1
    head resd 1


section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp
    and esp, -16
    sub esp, 16
    
    mov dword[esp+4], imode
    mov dword[esp], iname
    call fopen
    
    mov ebx, eax
    mov dword[head], 0
    
    mov dword[esp], ebx
    mov dword[esp+4], iform
    mov dword[esp+8], node_key
    call fscanf
        
    cmp eax, -1
    je .exit
    
    mov dword[esp], 12
    call malloc
    
    mov ecx, [node_key]
    mov dword[eax], ecx
    mov dword[eax+4], 0
    mov dword[eax+8], 0
    
    mov dword[head], eax
    .loop:    
    mov dword[esp+8], node_key
    mov dword[esp+4], iform
    mov dword[esp], ebx
    call fscanf
    
    cmp eax, -1
    je .exit
    
    mov eax, [node_key]
    mov dword[esp], eax
    call node_insert

    jmp .loop
    .exit:
    mov dword[esp], ebx
    call fclose
    
    mov dword[esp+4], omode
    mov dword[esp], oname
    call fopen
    
    mov ebx, eax
    
    mov dword[esp], ebx
    call node_cut
    
    mov dword[esp], ebx
    call fclose
    
    mov esp, ebp
    pop ebp
    xor eax, eax
    ret
    
    
node_insert:   ; void f(int key)
    push ebp
    mov ebp, esp
    push edi
    push esi
    push ebx
    sub esp, 16
    
    mov ebx, dword[ebp+8]   ; ebx - node_key
    
    mov esi, [head]    ; tmp_ptr
    mov edi, 0    ; pr_ptr
    .node_last:   ; find end of node
    cmp esi, 0
    je .insert
    
    mov eax, dword[esi]
    cmp ebx, eax
    jge .insert

    mov edi, esi
    mov esi, [esi+4]
    jmp .node_last
    .insert:
    mov dword[esp], 12
    call malloc
    
    mov dword[eax], ebx
    mov dword[eax+4], esi
    mov dword[eax+8], edi
    
    test esi, esi
    jz .next
    mov dword[esi+8], eax
    .next:
    test edi, edi
    jz .null
    mov dword[edi+4], eax
    
    add esp, 16
    pop ebx
    pop esi
    pop edi
    
    mov esp, ebp
    pop ebp
    xor eax, eax
    ret
    .null:
    mov dword[head], eax
    
    add esp, 16
    pop ebx
    pop esi
    pop edi
    
    mov esp, ebp
    pop ebp
    xor eax, eax
    ret
    
node_cut: ;void f(struct* ptr, FILE*)
    push ebp
    mov ebp, esp
    sub esp, 16
    push esi
    
    mov ebx, dword[ebp+8]
    mov esi, [head]
    .node_last:
    mov ecx, [esi+4]
    test ecx, ecx
    jz .output
    mov esi, ecx
    jmp .node_last
    .output:
    test esi, esi
    jz .exit
    
    mov eax, [esi]
    ;PRINT_STRING `EAX: `
    ;PRINT_DEC 4, eax
    ;PRINT_STRING `\n`
     
    mov dword[esp+8], eax
    mov dword[esp+4], oform
    mov dword[esp], ebx
    call fprintf
    
    mov ecx, esi
    mov esi, [esi+8]
    mov dword[esp], ecx
    call free
    jmp .output
    .exit:
    pop esi
    mov esp, ebp
    pop ebp
    xor eax, eax
    ret
