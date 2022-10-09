%include "../include/io.mac"

section .text
    global is_square
    extern printf


is_square:
    ;; DO NOT MODIFY
    push ebp
    mov ebp, esp
    pusha

    mov ebx, [ebp + 8]      ; dist
    mov eax, [ebp + 12]     ; nr
    mov ecx, [ebp + 16]     ; sq
    ;; DO NOT MODIFY
   
    ;; Your code starts here
    xor esi, esi
    mov esi, eax
    xor edi, edi
    
    push eax
parcurgerevector:
    mov eax, [ebx+4*edi]
    xor edx, edx
label:
    push edx
    imul edx, edx
    cmp eax, edx
    je gasit
    jl negasit 
    pop edx
    inc edx
    jmp label

gasit:
    mov dword [ecx+4*edi], 1
    pop edx
    cmp esi, edi
    je exit
    add edi, 1
    jmp parcurgerevector   
negasit:
    pop edx
    mov dword [ecx+4*edi], 0
    cmp esi, edi
    je exit
    add edi, 1
    jmp parcurgerevector
 exit:
    add esp, 4
    ;; Your code ends here
    
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY