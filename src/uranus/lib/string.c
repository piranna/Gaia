/*
 * string.c
 *
 *  Created on: 20/12/2011
 *      Author: piranna
 */

// Compare two strings. Should return -1 if
// str1 < str2, 0 if they are equal or 1 otherwise.
int strcmp(const char* str1, const char* str2)
{
	// Loop over str1 & str2 comparing its bytes until they end or differ
	int i = -1;
	do
	{
		int diff;
		i++;
		diff = (unsigned char)str1[i] - (unsigned char)str2[i];
		if(diff) return diff;
	} while(str1[i] && str2[i]);

	// str1 and str2 are equal
	return 0;
}

//// Copy the NULL-terminated string src into dest, and
//// return dest.
//char *strcpy(char *dest, const char *src)
//{
//    do
//    {
//      *dest++ = *src++;
//    }
//    while (*src != 0);
//}
//
//// Concatenate the NULL-terminated string src onto
//// the end of dest, and return dest.
//char *strcat(char *dest, const char *src)
//{
//    while (*dest != 0)
//    {
//        *dest = *dest++;
//    }
//
//    do
//    {
//        *dest++ = *src++;
//    }
//    while (*src != 0);
//    return dest;
//}
