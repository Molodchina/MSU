%include "io.inc"

extern scanf
extern printf
CEXTERN malloc
CEXTERN realloc
CEXTERN free

section .bss
    p resd 1

section .data
    s dd 1
    iform db `%u `, 0

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    sub esp, 12
    mov esi, 0
    mov eax, 4
    
    mul dword[s]
    mov dword[esp], eax
    call malloc
    mov dword[p], eax; p - pointer
    
    .for:
        mov ebx, dword[p]
        lea eax, [ebx+4*esi]
        mov dword[esp+4], eax
        mov dword[esp], iform
        call scanf
        
        mov eax, esi
        mov edx, 4
        mul edx
        add eax, dword[p]
        cmp dword[eax], 0
        je .start
        
        inc esi
    .more:
        cmp dword[s], esi
        jg .for
        mov eax, dword[s]
        mov ebx, 3
        mul ebx
        mov dword[s], eax
        mov edx, 4
        mul edx
        
        mov ebx, dword[p]
        mov dword[esp], ebx
        mov dword[esp+4], eax
        call realloc
        mov dword[p], eax
        jmp .for
    .start:
        mov ecx, 0
        cmp esi, 0
        je .end
        dec esi
        mov eax, esi
        mov edx, 4
        mul edx
        add eax, dword[p]
        mov edi, [eax]
    .sr:
        cmp edx, esi
        je .end
        mov ebx, dword[p]
        lea eax, [ebx+4*edx]
        mov eax, [eax]
        cmp eax, edi
        jge .next
        inc ecx
    .next:
        inc edx
        jmp .sr        
    .end:
        mov dword[esp], iform
        mov dword[esp+4], ecx
        call printf
    mov ebx, dword[p]
    mov dword[esp], ebx
    call free
    add esp, 12
    xor eax, eax
    ret