/*
 * eventmanager_app.h
 *
 * Functions to manage events on the apps side
 *
 *  Created on: 15/04/2012
 *      Author: piranna
 */

#ifndef EVENTMANAGER_APP_H_
#define EVENTMANAGER_APP_H_

#include "eventmanager.h"
#include "fixedDict.h"
#include "fixedQueue.h"


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

static void eventmanager_init_app(void)
{
	// Init local app event manager
	static pairKeyValue eventmanager_events_pairs[10];
	static pairEventData eventmanager_queue_items[10];

	fixedDict_init(&eventmanager_events, eventmanager_events_pairs);
	fixedQueue_init(&eventmanager_queue, eventmanager_queue_items,
					sizeof(pairEventData));
	eventmanager_queue.capacity = 10;	// Hugly hack
}


// defines 'magic' to have the same func names for apps and OS functions
#define eventmanager_init       eventmanager_init_app
#define eventmanager_attach     eventmanager_attach_app
#define eventmanager_send       eventmanager_send_app
#define eventmanager_pumpEvents eventmanager_pumpEvents_app

#endif /* EVENTMANAGER_APP_H_ */
