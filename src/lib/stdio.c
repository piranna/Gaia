#include <stdio.h>

#include <stdlib.h>

#include "video.h"


#define putchar(p1) video_putchar(p1)


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
