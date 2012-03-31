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
int syscall_inb_p(const u16int port);
int syscall_outb(const u16int port, const u8int value);

#include "eventmanager.h"

/* hardcoded */
typedef void (*t_em_send)(char*,int);
typedef void (*t_em_pumpEvents)(void);
/* hardcoded */

DECL_SYSCALL1(set_eventmanager_send, const t_em_send)
DECL_SYSCALL1(set_eventmanager_pumpEvents, const t_em_pumpEvents)

#endif
