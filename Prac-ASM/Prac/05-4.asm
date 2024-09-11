%include "io.inc"

CEXTERN fopen
CEXTERN fclose
CEXTERN fscanf
extern printf

section .bss
    temp resd 1

section .rodata
    fname db 'data.in', 0
    fin db 'r', 0
    fout db `%d`, 0

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    sub esp, 16
    mov esi, 0
    
    mov dword[esp+4], fin
    mov dword[esp], fname
    call fopen
    mov ebx, eax
    
    mov dword[esp], ebx
    mov dword[esp+4], fout
    mov dword[esp+8], temp
    
    l:
        call fscanf
        
        cmp eax, 1
        jne .end
        
        add esi, eax
        jmp l
    .end:
        call fclose
        
        mov dword[esp], fout
        mov dword[esp+4], esi
        call printf
    
    add esp, 16
    xor eax, eax
    ret