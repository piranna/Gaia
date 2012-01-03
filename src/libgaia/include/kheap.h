// kheap.h -- Interface for kernel heap functions, also provides
//            a placement malloc() for use before the heap is 
//            initialised.
//            Written for JamesM's kernel development tutorials.

#ifndef KHEAP_H
#define KHEAP_H

#include "types.h"

#define KHEAP_START         0xC0000000
#define KHEAP_INITIAL_SIZE  0x100000

/**
   Allocate a chunk of memory, sz in size. The chunk must be
   page aligned.
**/
u32int kmalloc_a(u32int sz);

/**
   Allocate a chunk of memory, sz in size. The physical address
   is returned in phys. Phys MUST be a valid pointer to u32int!
**/
u32int kmalloc_p(u32int sz, u32int *phys);

/**
   Allocate a chunk of memory, sz in size. The physical address 
   is returned in phys. It must be page-aligned.
**/
u32int kmalloc_ap(u32int sz, u32int *phys);

/**
   General allocation function.
**/
u32int kmalloc(u32int sz);

/**
   General deallocation function.
**/
void kfree(void *p);

#endif // KHEAP_H
