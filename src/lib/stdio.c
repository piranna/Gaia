#include <stdio.h>

#include <stdlib.h>

#include "interruptmanager.h"
//#include "syscall.h"


extern t_em_send uranus_em_send;
static int putchar(int c)
{
	if(uranus_em_send)
		uranus_em_send("VGA/text/putchar", c);
//		//return uranus_em_send("VGA/text/putchar", c);

	// We should raise some kind of exception to userspace...
	return 0;
}


/* Format a string and print it on the screen, just like the libc
	function printf. */
void printf(const char* format, ...)
{
	char** arg = (char**)&format;
	int c;

	arg++;

	while((c = *format++) != 0)
	{
		if(c == '%')
		{
			char* p;
			char buf[20];

			c = *format++;
			switch(c)
			{
				// character
				case 'c':
					p = *arg++;
					putchar(*p);
					break;

				// integer (decimal, unsigned or hexadecimal)
				case 'd':
				case 'u':
				case 'x':
					p = itoa(*((int*)arg++), buf, c=='x' ?16 :10);

					goto string;

				// string
				case 's':
					p = *arg++;
					if(!p)
						p = "(null)";

					string:
						while(*p)
							putchar(*p++);
					break;

				// No recognized specifier
				default:
					putchar('%');
					putchar(c);
					break;
			}
		}

		// Normal character
		else
			putchar(c);
	}
}


int snprintf(char* str, size_t size, const char* format,...)
{
	char** arg = (char**)&format;
	int c;

	size_t s = size;

	arg++;

	while((c = *format++) && size)
	{
		if(c == '%')
		{
			char* p;
			char buf[20];

			c = *format++;
			switch(c)
			{
				// character
				case 'c':
					p = *arg++;
					putchar(*p);
					break;

				// integer (decimal, unsigned or hexadecimal)
				case 'd':
				case 'u':
				case 'x':
					p = itoa(*((int*)arg++), buf, c=='x' ?16 :10);

					goto string;

				// string
				case 's':
					p = *arg++;
					if(!p)
						p = "(null)";

					string:
						while(*p && size)
						{
							*str = *p++;
							str++;
							size--;
						}
					break;

				// No recognized specifier
				default:
					*str = '%';
					str++;
					size--;

					*str = c;
					str++;
					size--;
					break;
			}
		}

		// Normal character
		else
		{
			*str = c;
			str++;
			size--;
		}
	}

	*str = '\0';

	return s - size;
}
