//
// isr.c -- High level interrupt service routines.
//          Part of this code is modified from JamesM's kernel development tutorials.
//

#include "isr.h"

#include <stdio.h>


// This gets called from our ASM interrupt handler stub.
void isr_handler(registers_t regs)
{
	printf("received interrupt: %d\n", regs.int_no);
}
