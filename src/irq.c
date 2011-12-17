//
// irq.c -- High level interrupt request handlers.
//          Part of this code is modified from JamesM's kernel development tutorials.
//

#include "irq.h"

#include "idt.h"


// These extern directives let us access the addresses of our ASM IRQ handlers.
extern void irq0 (void);
extern void irq1 (void);
extern void irq2 (void);
extern void irq3 (void);
extern void irq4 (void);
extern void irq5 (void);
extern void irq6 (void);
extern void irq7 (void);
extern void irq8 (void);
extern void irq9 (void);
extern void irq10(void);
extern void irq11(void);
extern void irq12(void);
extern void irq13(void);
extern void irq14(void);
extern void irq15(void);


isr_t interrupt_handlers[256];


void irq_handler_register(u8int n, isr_t handler)
{
  interrupt_handlers[n] = handler;
}

void irq_handler_unregister(u8int n)
{
  interrupt_handlers[n] = 0;
}


// This gets called from our ASM interrupt handler stub.
void irq_handler(registers_t regs)
{
   // Send an EOI (end of interrupt) signal to the PICs.
   // If this interrupt involved the slave.
   if (regs.int_no >= 40)
   {
       // Send reset signal to slave.
       outb(0xA0, 0x20);
   }
   // Send reset signal to master. (As well as slave, if necessary).
   outb(0x20, 0x20);

   if (interrupt_handlers[regs.int_no] != 0)
   {
       isr_t handler = interrupt_handlers[regs.int_no];
       handler(&regs);
   }
}


void irq_init(void)
{
    idt_set_gate(IRQ0,  (u32int)irq0 , 0x08, 0x8E);
    idt_set_gate(IRQ1,  (u32int)irq1 , 0x08, 0x8E);
    idt_set_gate(IRQ2,  (u32int)irq2 , 0x08, 0x8E);
    idt_set_gate(IRQ3,  (u32int)irq3 , 0x08, 0x8E);
    idt_set_gate(IRQ4,  (u32int)irq4 , 0x08, 0x8E);
    idt_set_gate(IRQ5,  (u32int)irq5 , 0x08, 0x8E);
    idt_set_gate(IRQ6,  (u32int)irq6 , 0x08, 0x8E);
    idt_set_gate(IRQ7,  (u32int)irq7 , 0x08, 0x8E);
    idt_set_gate(IRQ8,  (u32int)irq8 , 0x08, 0x8E);
    idt_set_gate(IRQ9,  (u32int)irq9 , 0x08, 0x8E);
    idt_set_gate(IRQ10, (u32int)irq10, 0x08, 0x8E);
    idt_set_gate(IRQ11, (u32int)irq11, 0x08, 0x8E);
    idt_set_gate(IRQ12, (u32int)irq12, 0x08, 0x8E);
    idt_set_gate(IRQ13, (u32int)irq13, 0x08, 0x8E);
    idt_set_gate(IRQ14, (u32int)irq14, 0x08, 0x8E);
    idt_set_gate(IRQ15, (u32int)irq15, 0x08, 0x8E);
}
