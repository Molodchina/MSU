%include "io.inc"

section .bss
    a11 resd 1
    a12 resd 1
    a21 resd 1
    a22 resd 1
    b1 resd 1
    b2 resd 1

section .data
    x dd 0
    y dd 0
    ;a11 dd 0x11111
    ;a12 dd 0x10101
    ;a21 dd 0x00000
    ;a22 dd 0x11111
    ;b1 dd 0x01010
    ;b2 dd 0x00011

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;write your code here
    
    GET_UDEC 4, [a11]
    GET_UDEC 4, [a12]
    GET_UDEC 4, [a21]
    GET_UDEC 4, [a22]
    GET_UDEC 4, [b1]
    GET_UDEC 4, [b2]
    XOR eax, eax
    XOR ebx, ebx
    XOR esi, esi
    
    MOV eax, [a11]
    MOV ebx, [a12]
    AND eax, [x]
    AND ebx, [y]
    XOR eax, ebx
    XOR eax, [b1]
    MOV esi, eax
    
    MOV eax, [a21]
    MOV ebx, [a22]
    AND eax, [x]
    AND ebx, [y]
    XOR eax, ebx
    XOR eax, [b2]
    OR eax, esi
    XOR [x], eax
    ;PRINT_DEC 4, [x]
    ;PRINT_CHAR ' '
    ;SSSSSSSSSSSSSSSSS
    
    MOV eax, [a11]
    MOV ebx, [a12]
    AND eax, [x]
    AND ebx, [y]
    XOR eax, ebx
    XOR eax, [b1]
    MOV esi, eax
    
    MOV eax, [a21]
    MOV ebx, [a22]
    AND eax, [x]
    AND ebx, [y]
    XOR eax, ebx
    XOR eax, [b2]
    OR eax, esi
    XOR [y], eax
    ;PRINT_DEC 4, [y]
    ;PRINT_CHAR '; '
    ;SSSSSSSSSSSSSSSSS
    
    MOV eax, [a11]
    MOV ebx, [a12]
    AND eax, [x]
    AND ebx, [y]
    XOR eax, ebx
    XOR eax, [b1]
    MOV esi, eax
    
    MOV eax, [a21]
    MOV ebx, [a22]
    AND eax, [x]
    AND ebx, [y]
    XOR eax, ebx
    XOR eax, [b2]
    OR eax, esi
    XOR [x], eax
    ;PRINT_DEC 4, [x]
    ;PRINT_CHAR '; '
    ;SSSSSSSSSSSSSSSSS
    
    MOV eax, [a11]
    MOV ebx, [a12]
    AND eax, [x]
    AND ebx, [y]
    XOR eax, ebx
    XOR eax, [b1]
    MOV esi, eax
    
    MOV eax, [a21]
    MOV ebx, [a22]
    AND eax, [x]
    AND ebx, [y]
    XOR eax, ebx
    XOR eax, [b2]
    OR eax, esi
    XOR [y], eax
    ;PRINT_DEC 4, [y]
    ;PRINT_CHAR '; '
    ;SSSSSSSSSSSSSSSSS
    ;PRINT_CHAR '|'
    PRINT_UDEC 4, [x]
    PRINT_CHAR ' '
    PRINT_UDEC 4, [y]
    
    XOR eax, eax
    ret
