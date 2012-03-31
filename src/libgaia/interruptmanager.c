/*
 * interruptmanager.c
 *
 *  Created on: 09/01/2012
 *      Author: piranna
 */

#include "interruptmanager.h"

#include "isr.h"
#include <stdio.h>


/* hardcoded */
#define IRQ0 32
/* hardcoded */


t_em_send uranus_em_send = 0;
void set_eventmanager_send(t_em_send em_send)
{
	uranus_em_send = em_send;
}

t_em_pumpEvents uranus_em_pumpEvents = 0;
void set_eventmanager_pumpEvents(t_em_pumpEvents em_pumpEvents)
{
	uranus_em_pumpEvents = em_pumpEvents;
}


void interruptmanager_int_handler(registers_t* regs)
{
	if(uranus_em_send)
	{
		char event[7];
		snprintf(event, sizeof(event)-1, "irq/%d", regs->int_no - IRQ0);

		uranus_em_send(event, regs->err_code);
	}

	if(uranus_em_pumpEvents)
		uranus_em_pumpEvents();
}

void interruptmanager_exc_handler(registers_t* regs)
{
    printf("interruptmanager_exc_handler: %d\n",regs->int_no);
}


void interruptmanager_init(void)
{
	int i = 0;

	// Exceptions
	for(; i < 32; i++)
		irq_handler_register(i, &interruptmanager_exc_handler);

	// IRQs
	for(; i < 48; i++)
		irq_handler_register(i, &interruptmanager_int_handler);
}
