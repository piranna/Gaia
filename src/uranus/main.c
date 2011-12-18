/*
 * main.c
 *
 *  Gaia (example) userspace kernel
 *
 *  Created on: 17/12/2011
 *      Author: piranna
 */


#include "drivers/PIT.h"

void uranus_init()
{
    // Drivers
    PIT_init(100);	// Initialise the PIT to 100Hz
}

void kmain()
{
	uranus_init();
}
