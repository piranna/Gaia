/*
 * Gaia system calls
 * Piranna, 2011-12-17
 */

#ifndef SYSCALL_H_USERSPACE
#define SYSCALL_H_USERSPACE

#include "common.h"
#include "syscall_defines.h"

DECL_SYSCALL2(in,  const u8int, const u16int)
DECL_SYSCALL3(out, const u8int, const u16int, const u8int)

#include "irq.h"
DECL_SYSCALL2(irq_register_handler, const u8int, const isr_t)

#endif
