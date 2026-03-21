[BITS 64]

SECTION .text

global kInPortByte, kOutPortByte

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
