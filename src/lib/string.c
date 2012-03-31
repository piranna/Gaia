/*
 * string.h
 *
 *  Created on: 21/12/2011
 *      Author: piranna
 */

#include <string.h>


// Write len copies of val into dest.
void memset(unsigned char* dest, unsigned char val, unsigned int len)
{
    for(; len; len--) *dest++ = val;
}

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

//const void* memchr(const void* ptr, int value, int num)
//{
//	for(; num; num--, ptr++)
//		if(*((unsigned char*)ptr) == (unsigned char)value)
//			return ptr;
//
//	return 0;
//}

//int memcmp(const void* ptr1, const void* ptr2, int num)
//{
//	for(; num; num--)
//	{
//		int cmp = *((char*)ptr1) - *((char*)ptr2);
//		if(cmp) return cmp;
//
//		ptr1++; ptr2++;
//	}
//
//	return 0;
//}

// Copy len bytes from src to dest.
void memcpy(u8int* dest, const u8int* src, u32int len)
{
    for(; len; len--) *dest++ = *src++;
}

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

// Copy the NULL-terminated string src into dest up to num, and return dest.
char* strncpy(char* dest, const char* src, size_t num)
{
	char* dp = dest;
    for(; num; --num)
    	*dp++ = *src ? *src++ : '\0';
    return dest;
}
