#include <stdio.h>

#include <stdlib.h>

#include "interruptmanager.h"
//#include "syscall.h"


typedef int (*t_func_printf)(int, char**, unsigned int*);

extern t_em_send uranus_em_send;


static int _snprintf_putchar(int c, char** str, unsigned int* size)
{
	**str = c;
	(*str)++;
	(*size)--;

	return c;
}


/* Put the character C on the screen and return the written character */
int putchar(int c)
{
	if(uranus_em_send)
		uranus_em_send("VGA/text/putchar", c);
//		//return uranus_em_send("VGA/text/putchar", c);

	// We should raise some kind of exception to userspace...
	return 0;
}


static void _printf(const char** format, t_func_printf func_putchar,
					char** str, unsigned int* size)
{
	char** arg = (char**)format + 1;

	char stack[3];
	char index = 0;

	while((stack[index] = *(*format)++) && *size)
	{
		if(stack[index] == '%')
		{
			index++;

			char* p;
			char buf[20];

			stack[index] = *(*format)++;
			switch(stack[index])
			{
				// character
				case 'c':
					func_putchar(*((int*)arg++), str,size);
					break;

				// long integer
				case 'l':
					index++;
					stack[index] = *(*format)++;

				// integer (decimal, unsigned or hexadecimal)
				case 'd':
				case 'i':
				case 'u':
				case 'x':
					p = itoa(*((int*)arg++), buf, stack[index]=='x' ?16 :10);

					goto string;

				// string
				case 's':
					p = *arg++;
					if(!p)
						p = "(null)";

					string:
						while(*p && *size)
							func_putchar(*p++, str,size);
					break;

				// No recognized specifier
				default:
				{
					int i = 0;
					for(; i <= index; i++)
						func_putchar(stack[i], str,size);
					break;
				}
			}

			index = 0;
		}

		// Normal character
		else
			func_putchar(stack[index], str,size);
	}
}


/* Format a string and print it on the screen, just like the libc
	function printf. */
void printf(const char* format, ...)
{
	unsigned int size = 1;
	_printf(&format, putchar, 0, &size);
}


int snprintf(char* str, size_t size, const char* format,...)
{
	unsigned int s = size;

	_printf(&format, _snprintf_putchar, &str, &size);

	*str = '\0';

	return s - size;
}
