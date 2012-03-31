/* Convert the integer D to a string and save the string in BUF. If
	BASE is equal to 'd', interpret that D is decimal, and if BASE is
	equal to 'x', interpret that D is hexadecimal. */
char* itoa(int value, char* str, int base)
{
	char *p = str;
	char *p1, *p2;
	unsigned long ud = value;
	int divisor = 10;

	/* If %d is specified and D is minus, put `-' in the head. */
	if(base == 'd' && value < 0)
	{
		*p++ = '-';
		str++;
		ud = -value;
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
	p1 = str;
	p2 = p - 1;
	while (p1 < p2)
	{
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return str;
}
