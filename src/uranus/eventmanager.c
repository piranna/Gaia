/*
 * eventamanager.c
 *
 *  Created on: 20/12/2011
 *      Author: piranna
 */

#include "eventmanager.h"

#include <string.h>

void eventmanager_send(char* key, int data)
{
	if(!strcmp(key, "putchar"))	VGA_text_putchar(data);
}
