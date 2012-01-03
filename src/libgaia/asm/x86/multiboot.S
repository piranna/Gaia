/* multiboot.S - bootstrap the kernel */
/* Copyright (C) 1999, 2001  Free Software Foundation, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA. */

#define ASM_FILE 1
#include "multiboot.h"

/* C symbol format. HAVE_ASM_USCORE is defined by configure. */
#ifdef HAVE_ASM_USCORE
#   define EXT_C(sym)   _ ## sym
#else
#   define EXT_C(sym)   sym
#endif

/* The size of our stack (16KB). */
#define STACK_SIZE  0x4000

/* The flags for the Multiboot header. */
#ifdef __ELF__
#   define MULTIBOOT_HEADER_FLAGS   MULTIBOOT_PAGE_ALIGN  |\
                                    MULTIBOOT_MEMORY_INFO |\
                                    MULTIBOOT_VIDEO_MODE
#else
#   define MULTIBOOT_HEADER_FLAGS   MULTIBOOT_PAGE_ALIGN  |\
                                    MULTIBOOT_MEMORY_INFO |\
                                    MULTIBOOT_VIDEO_MODE  |\
                                    MULTIBOOT_AOUT_KLUDGE
#endif


.text
.globl  start, _start

start:
_start:
    jmp     multiboot_entry

    .align  4   /* Align 32 bits boundary. */

/* Multiboot header. */
multiboot_header:
    .long   MULTIBOOT_HEADER_MAGIC                              /* magic */
    .long   MULTIBOOT_HEADER_FLAGS                              /* flags */
    .long   -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)  /* checksum */

    #ifndef __ELF__
        .long   multiboot_header    /* header_addr */
        .long   _start              /* load_addr */
        .long   _edata              /* load_end_addr */
        .long   _end                /* bss_end_addr */
        .long   multiboot_entry     /* entry_addr */
    #endif /* ! __ELF__ */

    .long   1   /* mode_type */
    .long   0   /* width */
    .long   0   /* height */
    .long   0   /* depth */

multiboot_entry:
    /* Initialize the stack pointer. */
    movl    $(stack + STACK_SIZE), %esp

    /* Reset EFLAGS. */
    pushl   $0
    popf

    /* Push the pointer to the Multiboot information structure. */
    pushl   %ebx
    /* Push the magic value. */
    pushl   %eax

    /* Now enter the C main function... */
    call    EXT_C(gaia_main)

    /* Halt. */
    pushl   $halt_message
    call    EXT_C(printf)

halt:
//    cli             // Disable interruptions
    hlt             // Halt CPU
    jmp     halt    // Repeat if for whatever reason CPU is still working

halt_message:
    .asciz  "Halted."


.comm   stack, STACK_SIZE   /* Our stack area. */
