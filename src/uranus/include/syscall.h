/*
 * Gaia system calls
 * Piranna, 2011-12-17
 */

#ifndef SYSCALL_H
#define SYSCALL_H

#include "syscall_defines.h"
#include "types.h"

DECL_SYSCALL2(in,  const u8int, const u16int)
DECL_SYSCALL3(out, const u8int, const u16int, const u8int)

int syscall_inb(const u16int port);
int syscall_outb(const u16int port, const u8int value);

/* hardcoded */
typedef struct registers
{
    u32int ds;                  // Data segment selector
    u32int edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
    u32int int_no, err_code;    // Interrupt number and error code (if applicable)
    u32int eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers_t;
typedef void (*isr_t)(registers_t*);
/* hardcoded */

DECL_SYSCALL2(irq_handler_register, const u8int, const isr_t)

#include "eventmanager.h"

/* hardcoded */
typedef void (*t_em_send)(char*,int);
/* hardcoded */

DECL_SYSCALL1(set_eventmanager_send, const t_em_send)

#endif
