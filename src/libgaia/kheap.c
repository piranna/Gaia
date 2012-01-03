// kheap.c -- Kernel heap functions, also provides
//            a placement malloc() for use before the heap is 
//            initialised.
//            Written for JamesM's kernel development tutorials.

#include "heap.h"
#include "kheap.h"
#include "paging.h"

// end is defined in the linker script.
extern u32int end;
u32int placement_address = (u32int)&end;
extern page_directory_t* kernel_directory;
heap_t* kheap=0;

/**
   Allocate a chunk of memory, sz in size. If align == 1,
   the chunk must be page-aligned. If phys != 0, the physical
   location of the allocated chunk will be stored into phys.

   This is the internal version of kmalloc. More user-friendly
   parameter representations are available in kmalloc, kmalloc_a,
   kmalloc_ap, kmalloc_p.
**/
static u32int kmalloc_int(u32int sz, int align, u32int* phys)
{
    if(kheap)
    {
        void *addr = alloc(sz, (u8int)align, kheap);
        if (phys)
        {
            page_t *page = paging_page_get((u32int)addr, 0, kernel_directory);
            *phys = page->frame*0x1000 + ((u32int)addr&0xFFF);
        }
        return (u32int)addr;
    }
    else
    {
        if (align == 1 && (placement_address & 0xFFFFF000) )
        {
            // Align the placement address;
            placement_address &= 0xFFFFF000;
            placement_address += 0x1000;
        }

        if(phys)
            *phys = placement_address;

        u32int tmp = placement_address;
        placement_address += sz;

        return tmp;
    }
}

void kfree(void* p)
{
    free(p, kheap);
}

u32int kmalloc_a(u32int sz)
{
    return kmalloc_int(sz, 1, 0);
}

u32int kmalloc_p(u32int sz, u32int* phys)
{
    return kmalloc_int(sz, 0, phys);
}

u32int kmalloc_ap(u32int sz, u32int* phys)
{
    return kmalloc_int(sz, 1, phys);
}

u32int kmalloc(u32int sz)
{
    return kmalloc_int(sz, 0, 0);
}
