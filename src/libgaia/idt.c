//
// descriptor_tables.c - Initialises the GDT and IDT, and defines the
//                       default ISR and IRQ handler.
//                       Based on code from Bran's kernel development tutorials.
//                       Rewritten for JamesM's kernel development tutorials.
//

#include "idt.h"

#include <string.h>

#include "irq.h"
#include "sys/io.h"


// Lets us access our ASM functions from our C code.
extern void idt_flush(u32int);


idt_entry_t idt_entries[256];
idt_ptr_t   idt_ptr;

extern isr_t irq_entries[256];


#include <stdio.h>
void _idt_handler(registers_t* regs)
{
	isr_t handler = irq_entries[regs->int_no];
    if(handler)
    {
    	int aux = regs->int_no;
    	if(aux == 0x80)
    		printf("[1] _idt_handler %x %x %d\n", regs, &(regs->eax), regs->eax);

        handler(regs);

    	if(aux == 0x80)
    		printf("[2] _idt_handler %x %x %d\n", regs, &(regs->eax), regs->eax);
    }
    else
        printf("unhandled interrupt: %d\n", regs->int_no);
}


void idt_init(void)
{
    idt_ptr.limit = sizeof(idt_entry_t) * 256 -1;
    idt_ptr.base  = (u32int)&idt_entries;

    // Remap the irq table.
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	outb(0x21, 0x0);
	outb(0xA1, 0x0);

    memset((u8int*)&idt_entries, 0, sizeof(idt_entry_t)*256);

    isr_init();	// Interruptions - entries  0-31
    irq_init();	// IRQs          - entries 32-47

    idt_flush((u32int)&idt_ptr);
}

void idt_set_gate(u8int num, u32int base, u16int sel, u8int flags)
{
    idt_entries[num].base_lo = base & 0xFFFF;
    idt_entries[num].base_hi = (base >> 16) & 0xFFFF;

    idt_entries[num].sel     = sel;
    idt_entries[num].always0 = 0;
    idt_entries[num].flags   = flags | 0x60;
}
