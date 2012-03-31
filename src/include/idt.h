// 
// descriptor_tables.h - Defines the interface for initialising the GDT and IDT.
//                       Also defines needed structures.
//                       Based on code from Bran's kernel development tutorials.
//                       Rewritten for JamesM's kernel development tutorials.
//

#include "common.h"


void idt_init(void);
void idt_set_gate(u8int,u32int,u16int,u8int);


// A struct describing an interrupt gate.
struct idt_entry_struct
{
    u16int base_lo;             // The lower 16 bits of the address to jump to when this interrupt fires.
    u16int sel;                 // Kernel segment selector.
    u8int  always0;             // This must always be zero.
    u8int  flags;               // More flags. See documentation.
    u16int base_hi;             // The upper 16 bits of the address to jump to.
} __attribute__((packed));

typedef struct idt_entry_struct idt_entry_t;

// A struct describing a pointer to an array of interrupt handlers.
// This is in a format suitable for giving to 'lidt'.
struct idt_ptr_struct
{
    u16int limit;
    u32int base;                // The address of the first element in our idt_entry_t array.
} __attribute__((packed));

typedef struct idt_ptr_struct idt_ptr_t;
