/*
 * timer.c
 *
 * Initialises the PIT, and handles clock updates.
 * Based on code from JamesM's kernel development tutorials.
 *
 *  Created on: 05/12/2011
 *      Author: piranna
 */


#include "syscall.h"


static void PIT_handler(void)
{
	static u32int tick = 0;

	tick++;

//	if(!(tick % 100))
//		printf("Tick: %d\n", tick);

    switch_task();
}

void PIT_init(u32int frequency)
{
    // Firstly, register our timer callback.
    eventmanager_attach("IRQ/0", &PIT_handler);

    // The value we send to the PIT is the value to divide it's input clock
    // (1193180 Hz) by, to get our required frequency. Important to note is
    // that the divisor must be small enough to fit into 16-bits.
    u32int divisor = 1193180 / frequency;

    // Send the command byte.
    syscall_outb(0x43, 0x36);

    // Divisor has to be sent byte-wise, so split here into upper/lower bytes.
    // Send the frequency divisor.
    syscall_outb(0x40, (u8int)(divisor & 0xFF));
    syscall_outb(0x40, (u8int)((divisor>>8) & 0xFF));
}