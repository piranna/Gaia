/*
 * interruptmanager.c
 *
 *  Created on: 09/01/2012
 *      Author: piranna
 */

#include "interruptmanager.h"

#include "isr.h"


t_em_send uranus_em_send = 0;
void set_eventmanager_send(t_em_send em_send)
{
	uranus_em_send = em_send;
}


void interruptmanager_int_handler(registers_t* regs)
{
//    printf("interruptmanager_int_handler: %d\n",regs->int_no);
}

void interruptmanager_exc_handler(registers_t* regs)
{
//    printf("interruptmanager_exc_handler: %d\n",regs->int_no);
}


void interruptmanager_init(void)
{
//	int i = 0;
//	for(; i < 16; i++)
//		irq_handler_register(i, &interruptmanager_exc_handler);
}
