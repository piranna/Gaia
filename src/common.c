// common.c -- Defines some global functions.
//             From JamesM's kernel development tutorials.

#include "common.h"

#include <stdio.h>


// Write a byte out to the specified port.
void outb(u16int port, u8int value)
{
    asm volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

void outw(u16int port, u16int value)
{
    asm volatile("outw %1, %0" : : "dN" (port), "a" (value));
}

u8int inb(u16int port)
{
    u8int ret;
    asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

u16int inw(u16int port)
{
    u16int ret;
    asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
    return ret;
}

//// Copy len bytes from src to dest.
//void memcpy(u8int *dest, const u8int *src, u32int len)
//{
//    const u8int *sp = (const u8int *)src;
//    u8int *dp = (u8int *)dest;
//    for(; len != 0; len--) *dp++ = *sp++;
//}

// Write len copies of val into dest.
void memset(u8int* dest, u8int val, u32int len)
{
    u8int *temp = (u8int *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}


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
