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
#include "scheudler.h"

#include "echo.h"


// Local app event manager
static fixedDict eventmanager_events;
static fixedQueue eventmanager_queue;

static void eventmanager_dispatch_app(pairEventData* pair)
{

}

static void eventmanager_send_app(char* event, int data)
//void eventmanager_send(char* event, int data)
{
	pairEventData pair;
//	strncpy(pair.event, event, sizeof(pair.event));
	pair.data = data;

//	fixedQueue_append(&eventmanager_queue, &pair);

	// This should not be here, eventmanager_pumpEvents() should be used for
	// real queued events, but since i have problems with 'VGA/text/putchar'
	// events (race condition?) and would need some kind of locking for the
	// queue, i dispatch it here directly by the moment
//	eventmanager_dispatch_app(&pair);
}

static void eventmanager_attach_app(char* event, event_func func)
//static void eventmanager_attach(char* event, event_func func)
{
	fixedDict_set(&eventmanager_events, event, func);
	eventmanager_attach_delegated(event, &eventmanager_events);
//	eventmanager_attach(event, eventmanager_send_app);
}

static void eventmanager_pumpEvents_app(void)
//static void eventmanager_pumpEvents(void)
{
	// Pump events until there's no more
	while(!fixedQueue_isEmpty(&eventmanager_queue))
	{
		pairEventData* pair = fixedQueue_head(&eventmanager_queue);

		eventmanager_dispatch_app(pair);

		fixedQueue_pop(&eventmanager_queue);
	}

	// Say we finished to pump events
	scheudler_yield();
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
	static pairEventData eventmanager_queue_items[10];

	fixedDict_init(&eventmanager_events, eventmanager_events_pairs);
	fixedQueue_init(&eventmanager_queue, eventmanager_queue_items,
					sizeof(pairEventData));
	eventmanager_queue.capacity = 10;	// Hugly hack

	// Set events
	eventmanager_attach_app("term/press/character", press_handler);

	// Init buffer
	buffer[0] = '\0';

	// Register the app on the task manager
	Process process;
	process.send = eventmanager_send_app;
	process.pumpEvents = eventmanager_pumpEvents_app;
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
