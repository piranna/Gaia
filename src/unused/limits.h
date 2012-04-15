/*
 * limits
 *
 *  Created on: 02/10/2011
 *      Author: piranna
 */

#ifndef LIMITS_
#define LIMITS_

/* Number of bits in a `char'.  */
#  define CHAR_BIT      8

/* Minimum and maximum values a `signed long int' can hold.  */
#  if __WORDSIZE == 64
#   define LONG_MAX     9223372036854775807L
#  else
#   define LONG_MAX     2147483647L
#  endif
#  define LONG_MIN      (-LONG_MAX - 1L)

#endif /* LIMITS_ */
