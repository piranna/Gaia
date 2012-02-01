/*
 * Gaia system calls
 * Piranna, 2011-12-17
 */

#include "syscall.h"

DEFN_SYSCALL2(in,  0, const u8int, const u16int);
DEFN_SYSCALL3(out, 1, const u8int, const u16int, const u8int);

int syscall_inb(const u16int port)
{
	return syscall_in(0, port);
}
int syscall_outb(const u16int port, const u8int value)
{
	return syscall_out(0, port,value);
}

DEFN_SYSCALL1(set_eventmanager_send, 2, const t_em_send)
