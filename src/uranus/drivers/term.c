/*
 * term.c
 *
 *  Created on: 28/12/2011
 *      Author: piranna
 */

#include "eventmanager.h"


static void term_handler(char c)
{
	eventmanager_send("VGA/text/putchar", c);
}

void term_init(void)
{
	eventmanager_attach("keyboard/press/character", &term_handler);
}
