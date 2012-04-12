/*
 * eventmanager.h
 *
 *  Created on: 20/12/2011
 *      Author: piranna
 */

#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

#include "fixedDict.h"


typedef int (*event_func)(int);

typedef struct
{
	char event[32];
	int data;
} pairEventData;


void eventmanager_init(void);

void eventmanager_attach(char* event, event_func func);
void eventmanager_deattach(char* event);

void eventmanager_attach_delegated(char* event, fixedDict* events);
void eventmanager_deattach_delegated(char* event);

void eventmanager_send(char* event, int data);
void eventmanager_pumpEvents(void);

#endif /* EVENTMANAGER_H_ */
