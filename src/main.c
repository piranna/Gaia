/*
# This file is Copyright 2011, Jesús Leganés Combarro "Piranna".
#
# The multiboot code is based on the multiboot specification example code,
# Copyright (C) 1999  Free Software Foundation, Inc. with GPL license.
*/


#include "multiboot.h"
#include <stdio.h>

#include "gdt.h"
#include "idt.h"
#include "paging.h"
#include "syscall.h"


void switch_to_user_mode(void)
{
	// Set up a stack structure for switching to user mode.
	asm volatile("\
		cli;\
		mov $0x23, %ax;\
		mov %ax, %ds;\
		mov %ax, %es;\
		mov %ax, %fs;\
		mov %ax, %gs;\
		\
		mov %esp, %eax;\
		pushl $0x23;\
		pushl %eax;\
		pushf;\
		pushl $0x1B;\
		push $1f;\
		iret;\
		1:\
		");
}

// Initialisation routine - zeroes all the interrupt service routines,
// initialises the GDT and IDT.
void gaia_init(void)
{
    gdt_init();	// Initialise the global descriptor table.
    idt_init();	// Initialise the interrupt descriptor table.

    // The size of physical memory. For the moment we assume it is 16MB big.
//    paging_init(0x1000000);
//    u32int* ptr = (u32int*)0xA0000000;
//    u32int do_page_fault = *ptr;

    syscall_init();

    // Enable interruptions
    asm volatile("sti");
}

void main(void);

void gaia_main(unsigned long magic, unsigned long addr)
{
	// Initialise all the ISRs and segmentation
	gaia_init();

//    switch_to_user_mode();
//    printf("Hello, user world!\n");

	// Start the userspace kernel
	main();
    paging_init(0x1000000);

	// Show multiboot info
//	multiboot_print_info(magic, addr);
}
