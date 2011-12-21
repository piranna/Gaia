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
	eventmanager_events.pairs = eventmanager_events_pairs;
	eventmanager_events.length = 0;
}


void eventmanager_attach(char* event, void* func)
{
//	eventmanager_events
}
void eventmanager_deattach(char* event)
{
	fixedDict_del(eventmanager_events, event);
}


void eventmanager_send(char* key, int data)
{
	if(!strcmp(key, "putchar"))	VGA_text_putchar(data);
}
