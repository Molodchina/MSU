%include "io.inc"

extern scanf
extern printf
CEXTERN malloc
CEXTERN free
CEXTERN strcmp

section .bss
    p resd 500
    x resd 1
    temp resd 1

section .data
    s dd 1001
    iname db 'input.txt', 0
    imode db 'r', 0
    form db "%d", 0
    form2 db ` `, 0
    oname db 'output.txt', 0
    omode db 'w', 0

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    sub esp,16
    mov esi, 0
    mov eax, 4
    
    mul dword[s]
    mov dword[esp], eax
    call malloc
    mov dword[p], eax; p - pointer
    
    mov dword[esp+4], imode
    mov dword[esp], iname
    call fopen
    
    cmp eax,0
    je exit
    mov dword[x], eax
    .for:
        mov ecx, dword[x]
        mov ebx, dword[p]
        lea eax, [ebx+4*esi]

        mov dword[esp], ecx
        mov dword[esp+4], form
        mov dword[esp+8], eax
        call fscanf

        cmp eax, 1
        jne end
        
        inc esi
        jmp .for
    end:
        mov ebx, dword[x]
        mov dword[esp], ebx
        call fclose
    
    cmp esi, 0
    je exit
    
    mov ebx, dword[p]
    mov dword[esp+12], comporator
    mov dword[esp+8], 4
    mov dword[esp+4], esi
    mov dword[esp], ebx
    call qsort
    
    mov dword[esp+4], omode
    mov dword[esp], oname
    call fopen
    
    mov dword[x], eax
    mov edi, 0
    l2:
        mov ebx, dword[x]
        mov eax, edi
        mov edx, 4
        mul edx
        add eax, dword[p]
        mov eax, [eax]
        
        mov dword[esp], ebx
        mov dword[esp+4], form
        mov dword[esp+8], eax
        call fprintf
        
        mov dword[esp+4], form2
        call fprintf
        
        inc edi
        cmp edi, esi
        jl l2
        
    mov ebx, dword[x]
    mov dword[esp], ebx
    call fclose
    exit:
    mov eax, dword[p]
    mov dword[esp], eax
    call free
    add esp, 16    
    xor eax, eax
    ret