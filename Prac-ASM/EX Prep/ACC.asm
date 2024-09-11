%include "io.inc"

section .data
    L4 dd L2022, L2023, L2024, L2025
    
section .text
global CMAIN
CMAIN:
    mov ebp, esp
    ;GET_DEC 4, ebx
    ;GET_DEC 4, eax
    ;GET_DEC 4, ecx
    mov ebx, 2025
    mov eax, 2
    mov ecx, 5
    sub ebx, 2022
    jmp dword[L4+ebx*4]
    L2022:
        add eax, ecx
        PRINT_DEC 4, eax
        jmp end
    L2023:
        xor eax, ecx
        PRINT_DEC 4, eax
        jmp end
    L2024:
        imul ecx
        PRINT_DEC 4, eax
        jmp end
    L2025:
        CDQ
        idiv ecx
        PRINT_DEC 4, edx
        jmp end
    end:
        xor eax, eax
        ret