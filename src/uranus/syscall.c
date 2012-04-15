/*
 * Gaia system calls
 * Piranna, 2011-12-17
 */

#include "syscall.h"

DEFN_SYSCALL2(in,  0, const u8int, const u16int);
DEFN_SYSCALL3(out, 1, const u8int, const u16int, const u8int);

int inb(const u16int port)
{
	return in(0, port);
}
int inb_p(const u16int port)
{
	return in(3, port);
}
int outb(const u16int port, const u8int value)
{
	return out(0, port,value);
}

DEFN_SYSCALL1(set_eventmanager_send, 2, const t_em_send)
DEFN_SYSCALL1(set_eventmanager_pumpEvents, 3, const t_em_pumpEvents)
