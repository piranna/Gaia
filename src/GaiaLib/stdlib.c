/* Converts an integer value to a null-terminated string using the specified
 * base and stores the result in the array given by str parameter.
 *
 * If `base` is 10 and `value` is negative, the resulting string is preceded
 * with a minus sign (-). With any other `base`, `value` is always considered
 * unsigned.
 *
 * `str` should be an array long enough to contain any possible value:
 * (sizeof(int)*8+1) for radix=2, i.e. 17 bytes in 16-bits platforms and 33 in
 * 32-bits platforms.
 */
char* itoa(int value, char* str, int base)
{
	char* p1 = str;
	char* p2 = str;

	/* If `base` is 10 and `value` is minus, put '-' in the head. */
	if(base == 10 && value < 0)
	{
		p1++;
		*p2++ = '-';
		value = -value;
	}

	/* Divide `value` by `base` until `value` == 0. */
	do
	{
		int remainder = value % base;

		*p2++ = remainder + (remainder < 10 ?'0' :'a' - 10);
	}
	while(value /= base);

	/* Terminate and reverse`str`. */
	*p2-- = '\0';

	while(p1 < p2)
	{
		char tmp = *p1;
		*p1++ = *p2;
		*p2-- = tmp;
	}

	return str;
}
