[BITS 64]

global kInPortByte, kOutPortByte, kLoadGDTR, kLoadTR, kLoadIDTR

SECTION .text

; PARAM: port number
kInPortByte:
    push rdx

    mov rdx, rdi
    mov rax, 0
    in al, dx
    
    pop rdx
    ret

; PARAM: port number, data
kOutPortByte:
    push rdx
    push rax

    mov rdx, rdi
    mov rax, rsi
    out dx, al
    
    pop rax
    pop rdx
    ret

kLoadGDTR:
    lgdt [rdi]
    ret

kLoadTR:
    ltr di
    ret

kLoadIDTR:
    lidt [rdi]
    ret
