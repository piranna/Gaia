// io.h -- Defines ports input/output functions
//         Based on code from JamesM's kernel development tutorials.

#ifndef IO_H
#define IO_H

#include "common.h"

// Write data to the specified port.
void outb(u16int port, u8int value);
void outw(u16int port, u16int value);
void outl(u16int port, u32int value);

// Read data from the specified port.
u8int inb(u16int port);
u16int inw(u16int port);
u32int inl(u16int port);

#endif // IO_H
