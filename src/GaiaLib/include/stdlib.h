/*
 * stdlib.h
 *
 *  Created on: 19/12/2011
 *      Author: piranna
 */

#ifndef STDLIB_H_
#define STDLIB_H_

/* Convert the integer D to a string and save the string in BUF. If
	BASE is equal to 'd', interpret that D is decimal, and if BASE is
	equal to 'x', interpret that D is hexadecimal. */
char* itoa(int value, char* str, int base);

#endif /* STDLIB_H_ */
