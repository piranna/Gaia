/*
 * main.c
 *
 *  Gaia (example) userspace kernel
 *
 *  Created on: 17/12/2011
 *      Author: piranna
 */


#include "eventmanager.h"
#include "syscall.h"

#include "drivers/PIT.h"
#include "drivers/VGA.h"
#include "drivers/keyboard.h"
#include "drivers/term.h"

void init(void)
{
	// Let the exokernel know where the event manager is
	eventmanager_init();
	syscall_set_eventmanager_send(eventmanager_send);
	syscall_set_eventmanager_pumpEvents(eventmanager_pumpEvents);

	// Drivers
    VGA_init();

//    PIT_init(100);	// Initialise the PIT to 100Hz
    keyboard_init();

    term_init();
}

void main(void)
{
	init();
}
