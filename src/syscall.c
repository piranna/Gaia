// syscall.c -- Defines the implementation of a system call system.
//              Written for JamesM's kernel development tutorials.

#include "syscall.h"
#include "irq.h"


static void syscall_handler(registers_t* regs);


static void* syscalls[] =
{
	&inb,
    &outb,
};
u32int num_syscalls = 2;


void syscall_init(void)
{
    // Register our syscall handler.
    irq_register_handler(0x80, &syscall_handler);
}

void syscall_handler(registers_t* regs)
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
      : "r" (regs->edi), "r" (regs->esi), "r" (regs->edx), "r" (regs->ecx), "r" (regs->ebx), "r" (location));
    regs->eax = ret;
}
