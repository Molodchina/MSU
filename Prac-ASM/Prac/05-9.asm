%include "io.inc"

extern scanf
extern printf
CEXTERN malloc
CEXTERN realloc
CEXTERN free

section .bss
    p resd 1
    ans resq 1
    a resd 1
    asize resd 1
    temp resd 1
    t resq 1
    sign resd 1

section .data
    s dd 1
    x dd 0
    iform db '%d ', 0
    oform1 db '%d ', 0
    oform2 db `\n`, 0

section .text
global CMAIN
CMAIN:
    push ebp
    mov ebp, esp; for correct debugging
    and esp, -16
    sub esp, 16
    mov esi, 0
    
    mov dword[esp+4], x
    mov dword[esp], iform
    call scanf
    
    mov eax, [x]
    test eax, eax
    jz .exit
    .for:
        mov dword[esp+4], s
        mov dword[esp], iform
        call scanf
        
        mov eax, dword[s]
        mul eax
        mov edx, 4
        mul edx
        mov dword[esp], eax
        call malloc
        mov dword[p], eax; p - pointer
        
        mov edi, 0     ; current pos = 0
        mov dword[temp], 0  ; current line = 0
        mov dword[t], 0     ; current trace = 0
    .input:
        cmp edi, dword[s]
        je .nextline
        
        mov ecx, dword[temp]
        imul ecx, dword[s]
        add ecx, edi
        mov ebx, dword[p]
        lea eax, [ebx+4*ecx]
        mov dword[esp+4], eax
        mov dword[esp], iform
        call scanf
        
        inc edi
        jmp .input
    .nextline:     ; line < size? ++line; goto(trace)
        mov ecx, dword[temp]
        mov dword[temp], 0
        inc ecx
        cmp ecx, dword[s]
        je .trace
        
        mov edi, 0
        mov dword[temp], ecx
        jmp .input
    .trace:      ; find trace
        mov ecx, dword[temp]
        cmp ecx, dword[s]
        je .next
        
        mov eax, dword[temp]
        mul dword[s]
        add eax, dword[temp]
        mov edx, 4
        mul edx
        add eax, dword[p]
        mov eax, dword[eax]
        
        cmp eax, 0
        jnl .pos
            mov dword[sign], -1
        jmp .step
        .pos:
            mov dword[sign], 0
        .step:
            add dword[t+4], eax
            mov eax, [sign]
            adc dword[t], eax
        
        inc dword[temp]
        jmp .trace
    .next:
        test esi, esi
        jz .change
        
        mov eax, dword[t+4]
        mov ebx, dword[t]
        
        cmp ebx, dword[ans]
        jg .change
        cmp eax, dword[ans+4]
        jg .change
        mov dword[t], 0
        mov dword[t+4], 0
        mov dword[temp], 0
        jmp .end
    .change:
        mov dword[ans], 0   ; free(a) and trace(a) = 0
        
        mov eax, dword[p]
        mov dword[a], eax   ; a = p (pointer)
        
        mov ebx, [t]
        mov eax, [t+4]
        mov dword[ans+4], eax
        mov dword[ans], ebx   ; trace(a) = trace(p)
        
        mov eax, dword[s]
        mov dword[asize], eax ; size(a) = size(p)
        
        mov dword[t], 0
        mov dword[t+4], 0
        mov dword[temp], 0
        ;mov eax, [p]
        ;mov dword[esp], eax
        ;call free
    .end:
        inc esi
        cmp esi, dword[x]
        jne .for
    
    mov edi, 0
    mov dword[temp], 0
    .output:   ; printf (matrix a)
        cmp edi, dword[asize]
        je .outnextline
        
        mov eax, dword[temp]
        mul dword[asize]
        add eax, edi
        mov edx, 4
        mul edx
        add eax, dword[a]
        mov eax, dword[eax]
        mov dword[esp+4], eax
        mov dword[esp], oform1
        call printf
        
        inc edi
        jmp .output
    .outnextline:     ; line < size? ++line; goto(trace)
        mov dword[esp], oform2
        call printf
        mov ecx, dword[temp]
        mov edi, 0
        inc ecx
        cmp ecx, dword[asize]
        je .exit
        
        mov dword[temp], ecx
        jmp .output
    .exit:
        mov eax, [a]
        mov dword[esp], eax
        call free
    mov esp, ebp
    pop ebp
    xor eax, eax
    ret