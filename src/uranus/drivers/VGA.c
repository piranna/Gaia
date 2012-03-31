/*
 * vga.c
 *
 *  Created on: 19/12/2011
 *      Author: piranna
 */

#include "syscall_userspace.h"


/* Some screen stuff. */
#define COLUMNS   80		/* The number of columns. */
#define LINES     25		/* The number of lines. */
#define ATTRIBUTE 7			/* The attribute of an character. */
#define VIDEO     0xB8000	/* The video memory address. */

/* Variables. */
extern int xpos;	/* Save the X position. */
extern int ypos;	/* Save the Y position. */

/* Point to the video memory. */
static volatile unsigned char* video = (unsigned char*)VIDEO;


/* Clear the screen and initialize VIDEO, XPOS and YPOS. */
static void VGA_text_cls(void)
{
	int i;
	for(i = 0; i < COLUMNS * LINES * 2; i++)
		*(video + i) = 0;

	xpos = 0;
	ypos = 0;
}


void VGA_init(void)
{
	VGA_text_cls();
}
