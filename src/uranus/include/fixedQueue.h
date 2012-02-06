/*
 * fixedQueue.h
 *
 *  Created on: 06/02/2012
 *      Author: piranna
 */

#ifndef FIXEDQUEUE_H_
#define FIXEDQUEUE_H_

typedef struct
{
	void* items;
	unsigned int length;
	unsigned int capacity;

	unsigned int first;
	unsigned int itemSize;
} fixedQueue;

void fixedQueue_init(fixedQueue* queue, void* items, unsigned int itemSize);

void  fixedQueue_append(fixedQueue* queue, void* item);
void* fixedQueue_head  (fixedQueue* queue);
void  fixedQueue_pop   (fixedQueue* queue);

#endif /* FIXEDQUEUE_H_ */
