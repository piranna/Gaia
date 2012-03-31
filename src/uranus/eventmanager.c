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
#include "TestAndSet.h"


typedef struct
{
	char event[32];
	int data;
} pairEventData;


static fixedDict eventmanager_events;
static fixedQueue eventmanager_queue;


void eventmanager_init(void)
{
	static pairKeyValue eventmanager_events_pairs[10];
	static pairEventData eventmanager_queue_items[10];

	fixedDict_init(&eventmanager_events, eventmanager_events_pairs);
	fixedQueue_init(&eventmanager_queue, eventmanager_queue_items,
					sizeof(pairEventData));
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
	pairEventData pair;
	strncpy(pair.event, event, sizeof(pair.event));
	pair.data = data;

	fixedQueue_append(&eventmanager_queue, &pair);

	event_func func = fixedDict_get(&eventmanager_events, event);
	if(func) func(data);
}


void eventmanager_pumpEvents(void)
{
//	static int pumping = 0;
//
//	// Don't start pumping if we are doing it yet
//	if(TestAndSet(&pumping)) return;
//
//	// Pump events until there's no more
//	while(!fixedQueue_isEmpty(&eventmanager_queue))
//	{
//		pairEventData* pair = fixedQueue_head(&eventmanager_queue);
//
//		event_func func = fixedDict_get(&eventmanager_events, pair->event);
//		if(func) func(pair->data);
//
//		fixedQueue_pop(&eventmanager_queue);
//	}
//
//	// Say we finished to pump events
//	pumping = 0;
}
