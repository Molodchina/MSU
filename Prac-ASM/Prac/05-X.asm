%include "io.inc"

extern scanf
extern printf

section .bss
    temp resd 101
    cur resd 101

section .rodata
    fin db "%100s", 0
    fout db `%s`, 0

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    sub esp, 16
    while:
    mov dword[esp+4], temp
    mov dword[esp], fin
    call scanf
    
    cmp eax, -1
    je .end
    
    mov eax, [temp]
    
    .next: 
	cmp	byte [eax], 1	
	inc	eax		
	jnc	.next
	sbb	eax, [temp]
	ret
    mov dword[esp+4], eax
    mov dword[esp], fout
    call printf
    
    jmp while
    .end:
    
    add esp, 16
    
    xor eax, eax
    ret