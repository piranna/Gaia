/*
 * string.h
 *
 *  Created on: 20/12/2011
 *      Author: piranna
 */

#ifndef STRING_H_
#define STRING_H_

// Compare two strings. Should return -1 if
// str1 < str2, 0 if they are equal or 1 otherwise.
int strcmp(const char* str1, const char* str2);

//const void* memchr(const void* ptr, int value, int num);
//int memcmp(const void* ptr1, const void* ptr2, int num);

//// Copy len bytes from src to dest.
//void memcpy(u8int *dest, const u8int *src, u32int len);

//// Concatenate the NULL-terminated string src onto
//// the end of dest, and return dest.
//char *strcat(char *dest, const char *src)

//// Copy the NULL-terminated string src into dest, and
//// return dest.
//char *strcpy(char *dest, const char *src)

#endif /* STRING_H_ */
