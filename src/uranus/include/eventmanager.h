/*
 * eventmanager.h
 *
 *  Created on: 20/12/2011
 *      Author: piranna
 */

#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

typedef int (*event_func)(int);

void eventmanager_init(void);

void eventmanager_attach(char* event, event_func);
void eventmanager_deattach(char* event);

void eventmanager_send(char* event, int data);
void eventmanager_pumpEvents(void);

#endif /* EVENTMANAGER_H_ */
