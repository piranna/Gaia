// io.c -- Defines ports input/output functions
//         Based on code from JamesM's kernel development tutorials.

#include "sys/io.h"


static void _pause(void)
{
	asm("outb %0, %1" : : "a"(0), "Nd"(0x80));
}


// Write data to the specified port.
void out(const u8int bytepower, const u16int port, const u32int value)
{
	switch(bytepower)
	{
		case 0:	outb(port, value);
		case 1:	outw(port, value);
		case 2:	outl(port, value);

		case 3:	outb_p(port, value);
		case 4:	outw_p(port, value);
		case 5:	outl_p(port, value);

//		case 6:	outsb(port, value);
//		case 7:	outsw(port, value);
//		case 8:	outsl(port, value);
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
	asm volatile("outl %0, %1" : : "a"(value), "Nd" (port));
}

void outb_p(u16int port, u8int value) /* byte - paused */
{
	outb(port, value);
	_pause();
}

void outw_p(u16int port, u16int value) /* word - paused */
{
	outw(port, value);
	_pause();
}

void outl_p(u16int port, u32int value) /* double word - paused */
{
	outl(port, value);
	_pause();
}

//void outsb(u16int port, u8int value) /* byte */
//{
//	asm volatile("outb %1, %0" : : "dN" (port), "a" (value));
//}
//
//void outsw(u16int port, u16int value) /* word */
//{
//	asm volatile("outw %1, %0" : : "dN" (port), "a" (value));
//}
//
//void outsl(u16int port, u32int value) /* double word */
//{
//	asm ("outl %0, %1" : : "a"(value), "Nd" (port));
//}


// Read data from the specified port.
u32int in(const u8int bytepower, const u16int port)
{
	switch(bytepower)
	{
		case 0:	return inb(port);
		case 1:	return inw(port);
		case 2:	return inl(port);

		case 3:	return inb_p(port);
		case 4:	return inw_p(port);
		case 5:	return inl_p(port);

//		case 6:	return insb(port);
//		case 7:	return insw(port);
//		case 8:	return insl(port);
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

u8int inb_p(u16int port) /* byte - paused */
{
	u8int ret;
	asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
	_pause();
	return ret;
}

u16int inw_p(u16int port) /* word - paused */
{
	u16int ret;
	asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
	_pause();
	return ret;
}

u32int inl_p(u16int port) /* double word - paused */
{
	u32int ret;
	asm volatile("inl %1, %0" : "=a"(ret) : "Nd"(port));
	_pause();
	return ret;
}
