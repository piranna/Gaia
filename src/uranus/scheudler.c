/*
 * scheudler.c
 *
 * Basic Round-Robin task scheudler
 *
 *  Created on: 13/04/2012
 *      Author: piranna
 */

#include "scheudler.h"

#include <stdio.h>

#include "eventmanager.h"
#include "fixedQueue.h"


static fixedQueue scheudler_queue;


//static void scheudler_mili_handler(u32int tick)
//{
//}

static void scheudler_tenth_handler(u32int tick)
{
//	printf("Tick: %d\n", tick);

	if(!fixedQueue_isEmpty(&scheudler_queue))
	{
		// Get first process on the queue
		Process* process = fixedQueue_head(&scheudler_queue);

		// Run process
		process->pumpEvents();

//		// Put the process at the end
//		fixedQueue_append(&scheudler_queue, process);
//		fixedQueue_pop(&scheudler_queue);
	}
}


void scheudler_load(Process* process)
{
	fixedQueue_append(&scheudler_queue, process);
}


void scheudler_yield(void)
{

}


void scheudler_init(void)
{
	static Process scheudler_queue_items[10];

	fixedQueue_init(&scheudler_queue, scheudler_queue_items, sizeof(Process));
	scheudler_queue.capacity = 10;	// Hugly hack

	// Set events
//	eventmanager_attach("PIT/second/mili", scheudler_mili_handler);
	eventmanager_attach("PIT/second/tenth", scheudler_tenth_handler);
}
