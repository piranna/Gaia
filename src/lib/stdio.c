#include <stdio.h>

#include <stdlib.h>

#include "video.h"


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


/* Put the character C on the screen and return the written character,
 * just like the libc function printf. */
int
putchar(int c)
{
	switch(c)
	{
		newline:

		case '\n':
			ypos++;
			if(ypos >= LINES)
			{
				linefeed();
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

/* Format a string and print it on the screen, just like the libc
	function printf. */
void printf(const char* format, ...)
{
	char** arg = (char**)&format;
	int c;
	char buf[20];

	arg++;

	while((c = *format++) != 0)
	{
		if(c != '%')
			putchar(c);
		else
		{
			char* p;

			c = *format++;
			switch(c)
			{
				case 'd':
				case 'u':
				case 'x':
					itoa(*((int*)arg++), buf, c);
					p = buf;
					goto string;
					break;

				case 's':
					p = *arg++;
					if(!p)
						p = "(null)";

					string:
						while(*p)
							putchar(*p++);
					break;

				default:
					putchar(*((int*)arg++));
					break;
			}
		}
	}
}


int snprintf(char* str, int size, const char* format,...)
{
	char** arg = (char**)&format;
	int c;
	char buf[20];

	int s = size;

	arg++;

	while((c = *format++) != 0 && size)
	{
		if(c != '%')
		{
			*str = c;
			str++;
			size--;
		}
		else
		{
			char* p;

			c = *format++;
			switch(c)
			{
				case 'd':
				case 'u':
				case 'x':
					itoa(*((int*)arg++), buf, c);
					p = buf;
					goto string;
					break;

				case 's':
					p = *arg++;
					if(!p)
						p = "(null)";

					string:
						while(*p && size)
						{
							*str = c;
							str++;
							size--;
						}
					break;

				default:
					*str = *((int*)arg++);
					str++;
					size--;
					break;
			}
		}
	}

	return s - size;
}
