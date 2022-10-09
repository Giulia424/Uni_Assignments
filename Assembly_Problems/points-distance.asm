%include "../include/io.mac"

struc point
    .x: resw 1
    .y: resw 1
endstruc

section .text
    global points_distance
    extern printf

points_distance:
    ;; DO NOT MODIFY
    
    push ebp
    mov ebp, esp
    pusha

    mov ebx, [ebp + 8]      ; points
    mov eax, [ebp + 12]     ; distance
    ;; DO NOT MODIFY
   
    ;; Your code starts here
    xor ecx, ecx
    xor edx, edx
    mov   ecx, [ebx+4]
    cmp  WORD [ebx], cx  
    jne yegal
    ;PRINTF32 `x egal \n\x0`
    mov dx, word  [ebx+2]
    cmp dx, word  [ebx+6]
    jg x1maimare
    jl x2maimare

x2maimare:
    mov dx, word [ebx+6]
    sub dx,word  [ebx+2]
    jmp exit

x1maimare:
    sub dx,word [ebx+6]
    jmp exit

yegal:
    ;PRINTF32 `y egal \n\x0`
    mov dx, word [ebx]
    cmp dx, word [ebx+4]
    jg y1maimare
    jl y2maimare

y2maimare:
    mov dx, word[ebx+4]
    sub dx, word [ebx]
    jmp exit

y1maimare:
    sub dx, word[ebx+4] 
    jmp exit

exit:
    mov [eax],  edx
    ;PRINTF32 `%hd \n\x0`, eax


    ;PRINTF32 `%hd \n\x0`, [ebx]
    ;PRINTF32 `%hd \n\x0`, [ebx+2]
    ;PRINTF32 `%hd \n\x0`, [ebx+4]
    ;PRINTF32 `%hd \n\x0`, [ebx+6]



    ;; Your code ends here
    
    ;; DO NOT MODIFY
    popa
    leave
    ret

    ;; DO NOT MODIFY