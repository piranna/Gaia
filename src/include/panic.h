// panic.h -- Defines some panic functions.
//            Based on code from JamesM's kernel development tutorials.

#ifndef PANIC_H
#define PANIC_H

#include "common.h"

#define PANIC(msg) panic(msg, __FILE__, __LINE__);
#define ASSERT(b) ((b) ? (void)0 : panic_assert(__FILE__, __LINE__, #b))

extern void panic(const char *message, const char *file, u32int line);
extern void panic_assert(const char *file, u32int line, const char *desc);

#endif // PANIC_H
