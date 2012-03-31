#include "stdio.h"


/* Some screen stuff. */
#define COLUMNS   80		/* The number of columns. */
#define LINES     24		/* The number of lines. */
#define ATTRIBUTE 7			/* The attribute of an character. */
#define VIDEO     0xB8000	/* The video memory address. */

/* Variables. */
static int xpos;	/* Save the X position. */
static int ypos;	/* Save the Y position. */

/* Point to the video memory. */
static volatile unsigned char* video = (unsigned char*)VIDEO;


/* Clear the screen and initialize VIDEO, XPOS and YPOS. */
void
cls(void)
{
	int i;
	for(i = 0; i < COLUMNS * LINES * 2; i++)
		*(video + i) = 0;

	xpos = 0;
	ypos = 0;
}

/* Convert the integer D to a string and save the string in BUF. If
	BASE is equal to 'd', interpret that D is decimal, and if BASE is
	equal to 'x', interpret that D is hexadecimal. */
static void
itoa(char *buf, int base, int d)
{
	char *p = buf;
	char *p1, *p2;
	unsigned long ud = d;
	int divisor = 10;

	/* If %d is specified and D is minus, put `-' in the head. */
	if(base == 'd' && d < 0)
	{
		*p++ = '-';
		buf++;
		ud = -d;
	}
	else if(base == 'x')
		divisor = 16;

	/* Divide UD by DIVISOR until UD == 0. */
	do
	{
		int remainder = ud % divisor;

		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'a' - 10;
	}
	while(ud /= divisor);

	/* Terminate BUF. */
	*p = 0;

	/* Reverse BUF. */
	p1 = buf;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}
}


static void linefeed()
{
	int i;

	// Copy all video buffer one line up
	for(i = 0; i < COLUMNS * (LINES-1) * 2; i++)
		*(video + i) = *(video + i + COLUMNS * 2);

	// Empty last line
	for(; i < COLUMNS * LINES * 2; i++)
		*(video + i) = 0;
}


/* Put the character C on the screen and return the written character,
 * just like the libc function printf. */
int
putchar(int c)
{
	if (c == '\n' || c == '\r')
	{
		newline:
		xpos = 0;
		ypos++;
		if(ypos >= LINES)
		{
			linefeed();
			ypos = LINES-1;
		}
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
					itoa(buf, c, *((int*) arg++));
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
					itoa(buf, c, *((int*) arg++));
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
