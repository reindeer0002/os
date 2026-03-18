[BITS 32]

global kReadCPUID, kSwtichAndExecute64bitKernel

SECTION .text

; params: DWORD dwEAXx, DWORD* pdwEAXx, pdwEAX, pdwECX, pdwEDX
kReadCPUID:
    push ebp
    mov ebp, esp
    push eax
    push ebx
    push ecx
    push edx
    push esi
    mov eax, dword [ebp + 8]
    cpuid

    ; *pdwEAX
    mov esi, dword [ebp + 12]
    mov dword [esi], eax

    ; *pdwEBX
    mov esi, dword [ebp + 16]
    mov dword [esi], ebx

    ; *pdwECX
    mov esi, dword [ebp + 20]
    mov dword [esi], ecx

    ; *pdwEDX
    mov esi, dword [ebp + 24]
    mov dword [esi], edx

    pop esi
    pop edx
    pop ecx
    pop ebx
    pop eax
    pop ebp
    ret

; no params
kSwtichAndExecute64bitKernel:
    ; set 1 in cr4 PAE bit
    mov eax, cr4
    or eax, 0x20
    mov cr4, eax

    ; activate cr3 PML4 table and caching
    mov eax, 0x100000
    mov cr3, eax

    ; set 1 in IA32_EFER.LME bit for activate IA-32e mode
    mov ecx, 0xC0000080
    rdmsr

    or eax, 0x0100

    wrmsr

    ; set 0 in NW bit and CD bit, set 1 in PG bit at cr0
    mov eax, cr0
    or eax, 0xE0000000
    xor eax, 0x60000000
    mov cr0, eax

    ; jump to kernel cs selector
    jmp 0x08:0x2000000

    ; this code is not executed
    jmp $