/*
 * eventamanager.c
 *
 *  Created on: 20/12/2011
 *      Author: piranna
 */

#include "eventmanager.h"

#include <stdio.h>
#include <string.h>

#include "fixedQueue.h"
#include "syscall.h"
#include "TestAndSet.h"


static fixedDict eventmanager_events;
static fixedDict eventmanager_events_delegated;
static fixedQueue eventmanager_queue;


void eventmanager_init(void)
{
	static pairKeyValue eventmanager_events_pairs[10];
	static pairKeyValue eventmanager_events_delegated_pairs[10];
	static pairEventData eventmanager_queue_items[10];

	fixedDict_init(&eventmanager_events, eventmanager_events_pairs);
	fixedDict_init(&eventmanager_events_delegated, eventmanager_events_delegated_pairs);
	fixedQueue_init(&eventmanager_queue, eventmanager_queue_items,
					sizeof(pairEventData));
	eventmanager_queue.capacity = 10;	// Hugly hack
}


void eventmanager_attach(char* event, event_func func)
{
	fixedDict_set(&eventmanager_events, event, func);
}

void eventmanager_deattach(char* event)
{
	fixedDict_del(&eventmanager_events, event);
}


void eventmanager_attach_delegated(char* event, fixedDict* events)
{
	fixedDict_set(&eventmanager_events_delegated, event, events);
}

void eventmanager_deattach_delegated(char* event)
{
	fixedDict_del(&eventmanager_events_delegated, event);
}


static void eventmanager_dispatch(pairEventData* pair)
{
	event_func func = fixedDict_get(&eventmanager_events, pair->event);
	if(func)
		func(pair->data);

	fixedDict* dict = fixedDict_get(&eventmanager_events_delegated,
									pair->event);
	if(dict)
	{
		func = fixedDict_get(dict, pair->event);
		if(func)
			func(pair->data);
	}
}


void eventmanager_send(char* event, int data)
{
	pairEventData pair;
	strncpy(pair.event, event, sizeof(pair.event));
	pair.data = data;

	fixedQueue_append(&eventmanager_queue, &pair);

	// This should not be here, eventmanager_pumpEvents() should be used for
	// real queued events, but since i have problems with 'VGA/text/putchar'
	// events (race condition?) and would need some kind of locking for the
	// queue, i dispatch it here directly by the moment
	eventmanager_dispatch(&pair);
}


void eventmanager_pumpEvents(void)
{
	static int pumping = 0;

	// Don't start pumping if we are doing it yet
	if(TestAndSet(&pumping)) return;

	// Pump events until there's no more
	while(!fixedQueue_isEmpty(&eventmanager_queue))
	{
		pairEventData* pair = fixedQueue_head(&eventmanager_queue);

//		eventmanager_dispatch(pair);

		fixedQueue_pop(&eventmanager_queue);
	}

	// Say we finished to pump events
	pumping = 0;
}
