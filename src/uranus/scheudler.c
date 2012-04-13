/*
 * scheudler.c
 *
 * Basic Round-Robin task scheudler
 *
 *  Created on: 13/04/2012
 *      Author: piranna
 */

#include "scheudler.h"

#include <stdio.h>

#include "eventmanager.h"


static void tenth_handler(u32int tick)
{
	printf("Tick: %d\n", tick);
}


void scheudler_init(void)
{
	eventmanager_attach("PIT/second/tenth", tenth_handler);
}
