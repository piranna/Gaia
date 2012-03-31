/*
 * eventmanager.h
 *
 *  Created on: 20/12/2011
 *      Author: piranna
 */

#ifndef EVENTMANAGER_H_
#define EVENTMANAGER_H_

void eventmanager_attach(char* event, void*);
void eventmanager_deattach(char* event);

void eventmanager_send(char* key, int data);

#endif /* EVENTMANAGER_H_ */
