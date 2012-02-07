// types.h -- Defines typedefs and some global functions.
//             Based on code from JamesM's kernel development tutorials.

#ifndef TYPES_H
#define TYPES_H

// Some nice typedefs, to standardise sizes across platforms.
// These typedefs are written for 32-bit X86.
typedef unsigned int   u32int;
typedef          int   s32int;
typedef unsigned short u16int;
typedef          short s16int;
typedef unsigned char  u8int;
typedef          char  s8int;

typedef unsigned int size_t;

typedef int bool;
#define false 0
#define true !false

#endif // TYPES_H
