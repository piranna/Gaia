/*
 * fakeshell.c
 *
 *  Created on: 01/04/2012
 *      Author: piranna
 */

// Fake shell app that store a line and print it


#include <stdio.h>

#include "eventmanager_app.h"
#include "scheudler.h"

#include "echo.h"


#define BUFFER_SIZE 1024


static char buffer[BUFFER_SIZE];
static int index = 0;


static void prompt(void)
{
	printf("> ");
}


static void press_handler(char key)
{
	if(key == '\n')
	{
		printf("\n");

		echo_run(buffer);

		buffer[0] = '\0';
		index = 0;

		prompt();
	}
	else if(index < BUFFER_SIZE)
		buffer[index++] = key;
}

void fakeshell_init(void)
{
	eventmanager_init();

	// Set events
	eventmanager_attach("term/press/character", press_handler);

	// Init buffer
	buffer[0] = '\0';

	// Register the app on the task manager
	Process process;
	process.send = eventmanager_send;
	process.pumpEvents = eventmanager_pumpEvents;

	scheudler_load(&process);
}

void fakeshell_run(void)
{
	printf("###\n");
	printf("### fakeshell started ###\n");
	printf("###\n");
	printf("Type anything and press return, and i will print it again\n");
	prompt();
}
