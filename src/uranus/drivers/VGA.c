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
static int xpos;	/* Save the X position. */
static int ypos;	/* Save the Y position. */

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


static void VGA_text_linefeed(void)
{
	int i = 0;

	// Copy all video buffer one line up
	for(; i < COLUMNS * (LINES-1) * 2; i++)
		*(video + i) = *(video + i + COLUMNS * 2);

	// Empty last line
	for(; i < COLUMNS * LINES * 2; i++)
		*(video + i) = 0;
}


/* Put the character C on the screen and return the written character,
 * just like the libc function printf. */
int VGA_text_putchar(int c)
{
	switch(c)
	{
		newline:

		case '\n':
			ypos++;
			if(ypos >= LINES)
			{
				VGA_text_linefeed();
				ypos = LINES-1;
			}

		case '\r':
			xpos = 0;
			return c;
	}

	*(video + (xpos + ypos * COLUMNS) * 2) = c & 0xFF;
	*(video + (xpos + ypos * COLUMNS) * 2 + 1) = ATTRIBUTE;

	xpos++;
	if(xpos >= COLUMNS)
		goto newline;

	return c;
}


void VGA_init(void)
{
	VGA_text_cls();

	eventmanager_attach("putchar", VGA_text_putchar);
}
