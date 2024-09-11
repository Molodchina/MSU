%include "io.inc"

section .data
    base dd l2022, l2023, l2024, l2025

section .text
global CMAIN
CMAIN:
    mov ebp, esp; for correct debugging
    ;GET_UDEC 4, esi
    ;GET_UDEC 4, ebx
    ;GET_UDEC 4, ecx
    mov esi, 5
    mov eax, 4
    mov ebx, 2
    sub esi, 5
    jmp dword[base + 4*esi]
    l2022:
        add eax, ebx
        jmp end
    l2023:
        xor eax, ebx
        jmp end
    l2024:
        imul ebx
        jmp end
    l2025:
        xor edx, edx
        idiv ebx
    end:
        PRINT_DEC 4, eax
        xor eax, eax
        ret