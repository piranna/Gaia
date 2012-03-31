// panic.c -- Defines some panic functions
//            Based on code from JamesM's kernel development tutorials.

#include "panic.h"

#include <stdio.h>


extern void panic(const char *message, const char *file, u32int line)
{
    // We encountered a massive problem and have to stop.
    asm volatile("cli"); // Disable interrupts.

    printf("PANIC(%s) at %s:%d\n",message,file,line);
    // Halt by going into an infinite loop.
    for(;;);
}

extern void panic_assert(const char *file, u32int line, const char *desc)
{
    // An assertion failed, and we have to panic.
    asm volatile("cli"); // Disable interrupts.

    printf("ASSERTION-FAILED(%s) at %s:%d\n", desc,file,line);
    // Halt by going into an infinite loop.
    for(;;);
}
