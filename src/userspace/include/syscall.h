// syscall.h -- Defines the interface for and structures relating to the syscall dispatch system.
//              Written for JamesM's kernel development tutorials.

#ifndef SYSCALL_H
#define SYSCALL_H

#include "common.h"

#define DECL_SYSCALL0(fn) int syscall_##fn();
#define DECL_SYSCALL1(fn,p1) int syscall_##fn(p1);
#define DECL_SYSCALL2(fn,p1,p2) int syscall_##fn(p1,p2);
#define DECL_SYSCALL3(fn,p1,p2,p3) int syscall_##fn(p1,p2,p3);
#define DECL_SYSCALL4(fn,p1,p2,p3,p4) int syscall_##fn(p1,p2,p3,p4);
#define DECL_SYSCALL5(fn,p1,p2,p3,p4,p5) int syscall_##fn(p1,p2,p3,p4,p5);

DECL_SYSCALL1(inb,  const u16int)
DECL_SYSCALL2(outb, const u16int, const u8int)

#endif
