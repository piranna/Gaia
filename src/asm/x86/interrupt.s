global restore_registers

restore_registers:
    pop ebx         ; reload the original data segment descriptor
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa            ; Pops edi,esi,ebp...
    add esp, 8      ; Cleans up the pushed error code and pushed ISR number
    sti
    iret            ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP
