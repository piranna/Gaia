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
#include "interruptmanager.h"
//#include "paging.h"
#include "syscall.h"


// Initialisation routine - zeroes all the interrupt service routines,
// initialises the GDT and IDT.
void gaia_init(void)
{
    // Start paging. For the moment we assume memory is 16MB big.
    paging_init(0x1000000);

    gdt_init();	// Initialise the global descriptor table.
    idt_init();	// Initialise the interrupt descriptor table.

    syscall_init();

    interruptmanager_init();

    // Enable interruptions
    asm volatile("sti");
}

void main(void);

void gaia_main(unsigned long magic, unsigned long addr)
{
	// Initialise all the ISRs and segmentation
	gaia_init();

//	switch_to_user_mode();

	// Start the userspace kernel
	main();

	printf("Hello, user world!\n");
}
