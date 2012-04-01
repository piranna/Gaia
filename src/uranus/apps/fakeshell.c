/*
 * fakeshell.c
 *
 *  Created on: 01/04/2012
 *      Author: piranna
 */

// Fake shell app that store a line and print it


#include <stdio.h>

#include "eventmanager.h"


#define BUFFER_SIZE 1024


static char buffer[BUFFER_SIZE];
static int index = 0;


static void prompt(void)
{
	printf("> ");
}


static void echo(char* line)
{
	printf("%s\n", line);
}


static void press_handler(char key)
{
	if(key == '\n')
	{
		printf("\n");

		echo(buffer);

		buffer[0] = '\0';
		index = 0;

		prompt();
	}
	else if(index < BUFFER_SIZE)
		buffer[index++] = key;
}

void fakeshell_init(void)
{
	eventmanager_attach("term/press/character", press_handler);

	buffer[0] = '\0';

	printf("### fakeshell started ###\n");
	prompt();
}
