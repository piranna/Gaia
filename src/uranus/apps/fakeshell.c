/*
 * fakeshell.c
 *
 *  Created on: 01/04/2012
 *      Author: piranna
 */

// Fake shell app that store a line and print it


#include <stdio.h>

#include "eventmanager.h"
#include "fixedQueue.h"

#include "echo.h"


// Local app event manager
static fixedDict eventmanager_events;
//static fixedQueue eventmanager_queue;

static void eventmanager_attach_app(char* event, event_func func)
//static void eventmanager_attach(char* event, event_func func)
{
	fixedDict_set(&eventmanager_events, event, func);
	eventmanager_attach_delegated(event, &eventmanager_events);
}


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
	// Init local app event manager
	static pairKeyValue eventmanager_events_pairs[10];
//	static pairEventData eventmanager_queue_items[10];

	fixedDict_init(&eventmanager_events, eventmanager_events_pairs);
//	fixedQueue_init(&eventmanager_queue, eventmanager_queue_items,
//					sizeof(pairEventData));
//	eventmanager_queue.capacity = 10;	// Hugly hack

	// Set events
	eventmanager_attach_app("term/press/character", press_handler);
//	eventmanager_attach("term/press/character", press_handler);

	// Init buffer
	buffer[0] = '\0';
}

void fakeshell_run(void)
{
	printf("###\n");
	printf("### fakeshell started ###\n");
	printf("###\n");
	printf("Type anything and press return, and i will print it again\n");
	prompt();
}
