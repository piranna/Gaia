/*
 * vga.c
 *
 *  Created on: 19/12/2011
 *      Author: piranna
 */

#include "string.h"
#include "syscall.h"


/* Some screen stuff. */
#define COLUMNS   80		/* The number of columns. */
#define LINES     25		/* The number of lines. */
#define ATTRIBUTE 7			/* The attribute of an character. */
#define VIDEO     0xB8000	/* The video memory address. */
#define TAB_WIDTH 4

/* Variables. */
static int xpos = 0;	/* Save the X position. */
static int ypos = 0;	/* Save the Y position. */

/* Point to the video memory. */
static unsigned char* video = (unsigned char*)VIDEO;


// Updates the hardware cursor.
static void VGA_text_moveCursor(void)
{
    u16int cursorLocation = ypos * COLUMNS + xpos;

    syscall_outb(0x3D4, 14);                  // Tell the VGA board we are setting the high cursor byte.
    syscall_outb(0x3D5, cursorLocation >> 8); // Send the high cursor byte.
    syscall_outb(0x3D4, 15);                  // Tell the VGA board we are setting the low cursor byte.
    syscall_outb(0x3D5, cursorLocation);      // Send the low cursor byte.
}


/* Clear the screen and initialize VIDEO, XPOS and YPOS. */
static void VGA_text_cls(void)
{
	memset(video, 0, COLUMNS * LINES * 2);

	xpos = 0;
	ypos = 0;

	VGA_text_moveCursor();
}


// Scrolls the text on the screen up by one line.
static void VGA_text_linefeed(void)
{
	// Copy all video buffer one line up
	memcpy(video, video + COLUMNS, COLUMNS*(LINES-1)*2);

	// Empty last line
	memset(video + COLUMNS*(LINES-1)*2, 0, COLUMNS * 2);
}


/* Put the character C on the screen and return the written character,
 * just like the `putchar` libc function. */
int VGA_text_putchar(int c)
{
	int pos;

	switch(c)
	{
		case '\0':
			return c;

		// Backspace
		case '\b':
		{
			xpos--;
			if(xpos < 0)
			{
				ypos--;
				if(ypos < 0)
				{
					xpos = 0;
					ypos = 0;
				}
				else
					xpos = COLUMNS - 1;
			}

			pos = (xpos + ypos * COLUMNS) * 2;
			video[pos] = ' ' & 0xFF;
			video[pos + 1] = ATTRIBUTE;

			VGA_text_moveCursor();
			return c;
		}

		// Tab
		case '\t':
			xpos += TAB_WIDTH;
			xpos &=  ~(TAB_WIDTH-1);

			if(xpos < COLUMNS)
			{
				VGA_text_moveCursor();
				return c;
			}

		newline:

		// Line feed
		case '\n':
			ypos++;
			if(ypos >= LINES)
			{
				VGA_text_linefeed();
				ypos = LINES-1;
			}

		// Carriage return
		case '\r':
			xpos = 0;
			VGA_text_moveCursor();
			return c;
	}

	// Regular character
	pos = (xpos + ypos * COLUMNS) * 2;
	video[pos] = c & 0xFF;
	video[pos + 1] = ATTRIBUTE;

	xpos++;
	if(xpos >= COLUMNS)
		goto newline;

	VGA_text_moveCursor();
	return c;
}


void VGA_init(void)
{
	VGA_text_cls();

	eventmanager_attach("VGA/text/putchar", VGA_text_putchar);
}
