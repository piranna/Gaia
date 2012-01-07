//
// descriptor_tables.c - Initialises the GDT and IDT, and defines the 
//                       default ISR and IRQ handler.
//                       Based on code from Bran's kernel development tutorials.
//                       Rewritten for JamesM's kernel development tutorials.
//

#include "gdt.h"

#include "string.h"
#include "tss.h"


// Lets us access our ASM functions from our C code.
extern void gdt_flush(u32int);
extern void tss_flush(void);

// Internal function prototypes.
static void gdt_set_gate(s32int,u32int,u32int,u8int,u8int);
static void tss_write(s32int,u16int,u32int);

gdt_entry_t gdt_entries[6];
gdt_ptr_t   gdt_ptr;
tss_entry_t tss_entry;


void gdt_init(void)
{
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 6) - 1;
    gdt_ptr.base  = (u32int)&gdt_entries;

    gdt_set_gate(0, 0, 0,          0,    0   ); // Null segment
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment

    tss_write(5, 0x10, 0x0);

    gdt_flush((u32int)&gdt_ptr);
    tss_flush();
}

// Set the value of one GDT entry.
static void gdt_set_gate(s32int num, u32int base, u32int limit, u8int access, u8int gran)
{
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;
    
    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access       = access;
}


// Initialise our task state segment structure.
static void tss_write(s32int num, u16int ss0, u32int esp0)
{
	// Firstly, let's compute the base and limit of our entry into the GDT.
	u32int base = (u32int)&tss_entry;
	u32int limit = base + sizeof(tss_entry);

	// Now, add our TSS descriptor's address to the GDT.
	gdt_set_gate(num, base, limit, 0xE9, 0x00);

	// Ensure the descriptor is initially zero.
	memset((u8int*)&tss_entry, 0, sizeof(tss_entry));

	tss_entry.ss0  = ss0;  // Set the kernel stack segment.
	tss_entry.esp0 = esp0; // Set the kernel stack pointer.

	// Here we set the cs, ss, ds, es, fs and gs entries in the TSS. These
	// specify what segments should be loaded when the processor switches to
	// kernel mode. Therefore they are just our normal kernel code/data segments
	// - 0x08 and 0x10 respectively, but with the last two bits set, making 0x0b
	// and 0x13. The setting of these bits sets the RPL (requested privilege
	// level) to 3, meaning that this TSS can be used to switch to kernel mode
	// from ring 3.
	tss_entry.cs = 0x0b;
	tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x13;
}

void set_kernel_stack(u32int stack)
{
   tss_entry.esp0 = stack;
}
