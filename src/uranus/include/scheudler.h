/*
 * scheudler.h
 *
 *  Created on: 13/04/2012
 *      Author: piranna
 */

#ifndef SCHEUDLER_H_
#define SCHEUDLER_H_

typedef void (*pumpEvents_func)(void);

typedef struct
{
	pumpEvents_func pumpEvents;
} Process;


void scheudler_init(void);

void scheudler_load(Process* process);
void scheudler_yield(void);

#endif /* SCHEUDLER_H_ */
