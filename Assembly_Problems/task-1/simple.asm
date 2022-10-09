%include "../include/io.mac"

section .text
    global simple
    extern printf

simple:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    pusha

    mov     ecx, [ebp + 8]  ; len
    mov     esi, [ebp + 12] ; plain
    mov     edi, [ebp + 16] ; enc_string
    mov     edx, [ebp + 20] ; step

    ;; DO NOT MODIFY
   
    ;; Your code starts here
    ;PRINTF32 `%d \n\x0`, esi
    xor ebx, ebx
    xor eax, eax
label:     
    mov bl, [esi+eax]
    mov [edi+eax],  bl
    add byte [edi+eax],dl
    cmp BYTE [edi+eax], 90
    jle aiurea 
    sub byte [edi+eax],26
    
aiurea:
    add  eax, 1
    loop label 
    
exit:
    ;; Your code ends here
    
    ;; DO NOT MODIFY

    popa
    leave
    ret
    
    ;; DO NOT MODIFY
