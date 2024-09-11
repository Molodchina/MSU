%include "io.inc"

section .bss
    n resd 1

section .data
    val db '2','3','4','5','6','7','8','9','T','J','Q','K','A' 
    s db 'S', 'C', 'D', 'H'

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    
    GET_DEC 4, [n]
    XOR eax, eax
    XOR edx, edx
    
    MOV eax, [n]
    SUB eax, 1
    MOV ebx, 13
    DIV ebx
    
    movzx edx, byte[edx+val]
    movzx eax, byte[eax+s]
    
    PRINT_CHAR edx
    PRINT_CHAR eax    
    
    XOR eax, eax
    ret
