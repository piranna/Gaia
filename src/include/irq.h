/*
 * irq.h
 *
 *  Created on: 06/12/2011
 *      Author: piranna
 */

#ifndef IRQ_H_
#define IRQ_H_

#include "isr.h"

// A few defines to make life a little easier
#define IRQ0  32	// PIT
#define IRQ1  33	// keyboard
#define IRQ2  34
#define IRQ3  35	// COM2/COM4
#define IRQ4  36	// COM1/COM3
#define IRQ5  37	// LPT2
#define IRQ6  38	// Diskette
#define IRQ7  39	// LPT1
#define IRQ8  40	// RTC
#define IRQ9  41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44	// mouse
#define IRQ13 45	// 80287 co-processor
#define IRQ14 46	// IDE primary controller
#define IRQ15 47	// IDE secondary controller

// Enables registration of callbacks for interrupts or IRQs.
// For IRQs, to ease confusion, use the #defines above as the
// first parameter.
typedef void (*isr_t)(registers_t*);

void irq_init(void);
void irq_handler_register(u8int n, isr_t handler);

#endif /* IRQ_H_ */
