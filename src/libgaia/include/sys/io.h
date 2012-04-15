// io.h -- Defines ports input/output functions
//         Based on code from JamesM's kernel development tutorials.

#ifndef IO_H
#define IO_H

#include "types.h"

// Write data to the specified port.
void out(const u8int bytepower, const u16int port, const u32int value);
void outb(u16int port, u8int value);
void outw(u16int port, u16int value);
void outl(u16int port, u32int value);
void outb_p(u16int port, u8int value);
void outw_p(u16int port, u16int value);
void outl_p(u16int port, u32int value);

// Read data from the specified port.
u32int in(const u8int bytepower, const u16int port);
u8int  inb(u16int port);
u16int inw(u16int port);
u32int inl(u16int port);
u8int  inb_p(u16int port);
u16int inw_p(u16int port);
u32int inl_p(u16int port);

#endif // IO_H
