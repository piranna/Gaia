// io.c -- Defines ports input/output functions
//         Based on code from JamesM's kernel development tutorials.

#include "sys/io.h"


// Write data to the specified port.
void out(const u8int bytepower, const u16int port, const u32int value)
{
	switch(bytepower)
	{
		case 0:	outb(port, value);
		case 1:	outw(port, value);
		case 2:	outl(port, value);
	}

	// We should raise some kind of exception to userspace...
}

void outb(u16int port, u8int value) /* byte */
{
	asm volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

void outw(u16int port, u16int value) /* word */
{
	asm volatile("outw %1, %0" : : "dN" (port), "a" (value));
}

void outl(u16int port, u32int value) /* double word */
{
	asm ("outl %0, %1" : : "a"(value), "Nd" (port));
}
// Read data from the specified port.
u32int in(const u8int bytepower, const u16int port)
{
	switch(bytepower)
	{
		case 0:	return inb(port);
		case 1:	return inw(port);
		case 2:	return inl(port);
	}

	// We should raise some kind of exception to userspace...
	return 0;
}

u8int inb(u16int port) /* byte */
{
	u8int ret;
	asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}

u16int inw(u16int port) /* word */
{
	u16int ret;
	asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}

u32int inl(u16int port) /* double word */
{
	u32int ret;
	asm volatile("inl %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}
