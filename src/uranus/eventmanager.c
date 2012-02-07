/*
 * eventamanager.c
 *
 *  Created on: 20/12/2011
 *      Author: piranna
 */

#include "eventmanager.h"

#include <stdio.h>
#include <string.h>

#include "fixedDict.h"
#include "fixedQueue.h"
#include "syscall.h"


static pairKeyValue eventmanager_events_pairs[10];
static fixedDict eventmanager_events;

static fixedQueue eventmanager_queue;


void eventmanager_init(void)
{
	fixedDict_init(&eventmanager_events, eventmanager_events_pairs);
}


void eventmanager_attach(char* event, event_func func)
{
	fixedDict_set(&eventmanager_events, event, func);
}

void eventmanager_deattach(char* event)
{
	fixedDict_del(&eventmanager_events, event);
}


void eventmanager_send(char* event, int data)
{
	fixedQueue_append(&eventmanager_queue, );

//	event_func func = fixedDict_get(&eventmanager_events, event);
//	if(func) func(data);
}


void eventmanager_pumpEvents(void)
{
	// Don't start pumping if we are doing it yet
	// TestAndSet() code found at
	// http://comsci.liu.edu/~jrodriguez/testandset2.html
	if(TestAndSet(&pumping)) return;

	while(!fixedQueue_isEmpty(&eventmanager_queue))
	{
		pair = fixedQueue_head(&eventmanager_queue);

	//	event_func func = fixedDict_get(&eventmanager_events, pair->event);
	//	if(func) func(pair->data);

		fixedQueue_pop(&eventmanager_queue);
	}

	// Say we finished to pump events
	pumping = false;
}
