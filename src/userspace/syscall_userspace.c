/*
 * Gaia system calls
 * Piranna, 2011-12-17
 */

#include "syscall_userspace.h"

DEFN_SYSCALL2(in,  0, const u8int, const u16int);
DEFN_SYSCALL3(out, 1, const u8int, const u16int, const u8int);

DEFN_SYSCALL2(irq_register_handler, 2, const u8int, const isr_t);
