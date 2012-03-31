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
#define IRQ0  32
#define IRQ1  33
#define IRQ2  34
#define IRQ3  35
#define IRQ4  36
#define IRQ5  37
#define IRQ6  38
#define IRQ7  39
#define IRQ8  40
#define IRQ9  41
#define IRQ10 42
#define IRQ11 43
#define IRQ12 44
#define IRQ13 45
#define IRQ14 46
#define IRQ15 47

// Enables registration of callbacks for interrupts or IRQs.
// For IRQs, to ease confusion, use the #defines above as the
// first parameter.
typedef void (*isr_t)(registers_t*);
void irq_register_handler(u8int n, isr_t handler);

#endif /* IRQ_H_ */
