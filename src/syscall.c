// syscall.c -- Defines the implementation of a system call system.
//              Written for JamesM's kernel development tutorials.

#include "syscall.h"

#include "idt.h"
#include "irq.h"


int in(const u8int bytepower, const u16int port)
{
	switch(bytepower)
	{
		case 0:	return inb(port);
		case 1:	return inw(port);
	}

	// We should raise some kind of exception to userspace...
	return 0;
}

void out(const u8int bytepower, const u16int port, const u8int value)
{
	switch(bytepower)
	{
		case 0:	return outb(port, value);
		case 1:	return outw(port, value);
	}

	// We should raise some kind of exception to userspace...
}


static void* syscalls[] =
{
	&in,
    &out,
    &irq_handler_register,
};
u32int num_syscalls = 3;


static void syscall_handler(registers_t* regs)
{
	// Firstly, check if the requested syscall number is valid.
    // The syscall number is found in EAX.
    if(regs->eax >= num_syscalls)
        return;

    // Get the required syscall location.
    void* location = syscalls[regs->eax];

    // We don't know how many parameters the function wants, so we just
    // push them all onto the stack in the correct order. The function will
    // use all the parameters it wants, and we can pop them all back off afterwards.
    int ret;
    asm volatile(" \
      push %1; \
      push %2; \
      push %3; \
      push %4; \
      push %5; \
      \
      call *%6; \
      \
      pop %%ebx; \
      pop %%ebx; \
      pop %%ebx; \
      pop %%ebx; \
      pop %%ebx; \
    " : "=a" (ret)
      : "r" (regs->edi), "r" (regs->esi), "r" (regs->edx), "r" (regs->ecx), "r" (regs->ebx),
        "r" (location));
    regs->eax = ret;
}

extern void isr128(void);

void syscall_init(void)
{
	// Enable the syscall ISR (int 0x80)
    idt_set_gate(0x80, (u32int)isr128, 0x08, 0x8E);

    // Register our syscall handler.
    irq_handler_register(0x80, &syscall_handler);
}
