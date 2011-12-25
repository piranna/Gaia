/*
 * eventamanager.c
 *
 *  Created on: 20/12/2011
 *      Author: piranna
 */

#include "eventmanager.h"

#include <string.h>

#include "fixedDict.h"
#include "syscall.h"

/* hardcoded */
#define IRQ1  33	// keyboard
/* hardcoded */

static pairKeyValue eventmanager_events_pairs[10];
static fixedDict eventmanager_events;

#include "drivers/keyboard.h"
static void eventmanager_irq_handler(registers_t* regs)
{
////	char event[7];
////	snprintf("IRQ/%d", regs->int_no);
////	eventmanager_send(event, regs->err_code);
	eventmanager_send("IRQ/1", regs->err_code);
}


void eventmanager_init(void)
{
	fixedDict_init(&eventmanager_events, eventmanager_events_pairs);

	syscall_irq_register_handler(IRQ1, &eventmanager_irq_handler);
}


void eventmanager_attach(char* event, event_func func)
{
	fixedDict_set(&eventmanager_events, event, func);
}

void eventmanager_deattach(char* event)
{
	fixedDict_del(&eventmanager_events, event);
}


void eventmanager_send(char* event, int data)
{
	event_func func = fixedDict_get(&eventmanager_events, event);
	if(func) func(data);
}
