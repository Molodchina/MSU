%include "io.inc"

extern scanf
extern printf
CEXTERN malloc
CEXTERN realloc
CEXTERN free
CEXTERN qsort

section .bss
    p resd 1

section .rodata
    s dd 100
    input db "%d", 0
    output db "%i,%i,%i,%i",13,10,0
    iname db 'input.txt', 0
    iform db 'r', 0
    itype db `%d`, 0
    otype db ` `, 0
    oname db 'output.txt', 0
    oform db 'w', 0

comp:
    mov eax, dword[esp+4]
    mov edx, dword[esp+8]
    mov eax, dword[eax]
    sub eax, dword[edx]
    ret

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
        
        cmp eax, 1
        jne .sr
        
        mov eax, esi
        mov edx, 4
        mul edx
        add eax, dword[p]
        
        inc esi
        jmp .for
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
    .sr:
        mov eax, dword[p]
        mov dword[esp+12], comp
        mov dword[esp+8], esi
        mov dword[esp+4], 4
        mov dword[esp], eax
        call qsort
        
        mov dword[esp+4], output
        mov dword[esp], eax
        call printf
    add esp, 12
    xor eax, eax
    ret