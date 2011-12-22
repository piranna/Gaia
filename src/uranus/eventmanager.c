/*
 * eventamanager.c
 *
 *  Created on: 20/12/2011
 *      Author: piranna
 */

#include "eventmanager.h"

#include <string.h>

#include "fixedDict.h"


static pairKeyValue eventmanager_events_pairs[10];
static fixedDict eventmanager_events;


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
	event_func func = fixedDict_get(&eventmanager_events, event);
	if(func) func(data);
}
