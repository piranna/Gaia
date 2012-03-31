;
; idt.s -- Interrupt Descriptor Table setup code.
;          Based on code from JamesM's kernel development tutorials.

[GLOBAL idt_flush]    ; Allows the C code to call idt_flush().

idt_flush:
    mov eax, [esp+4]  ; Get the pointer to the IDT, passed as a parameter. 
    lidt [eax]        ; Load the IDT pointer.
    ret
