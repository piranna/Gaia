/*
 * main.c
 *
 *  Gaia (example) userspace kernel
 *
 *  Created on: 17/12/2011
 *      Author: piranna
 */


#include "eventmanager.h"
#include "syscall_userspace.h"

#include "drivers/PIT.h"
#include "drivers/VGA.h"

void init(void)
{
	syscall_set_eventmanager_send(eventmanager_send);

	// Drivers
    PIT_init(100);	// Initialise the PIT to 100Hz
    VGA_init();
}

void main(void)
{
	init();
}
