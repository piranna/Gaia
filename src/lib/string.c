/*
 * string.h
 *
 *  Created on: 21/12/2011
 *      Author: piranna
 */

// Write len copies of val into dest.
void memset(unsigned char* dest, unsigned char val, unsigned int len)
{
    for(; len; len--) *dest++ = val;
}
