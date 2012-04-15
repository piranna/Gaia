#ifndef STDIO_H
#define STDIO_H

#include "types.h"

int  putchar (int c);
void printf  (const char *format, ...);
int  snprintf(char *str, size_t size, const char *format,...);

#endif
