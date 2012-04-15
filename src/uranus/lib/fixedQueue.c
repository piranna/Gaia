/*
 * fixedQueue.c
 *
 *  Created on: 06/02/2012
 *      Author: piranna
 */

#include "fixedQueue.h"

#include <string.h>


void fixedQueue_init(fixedQueue* queue, void* items, unsigned int itemSize)
{
	queue->items = items;
	queue->length = 0;
	queue->capacity = sizeof(*items)/itemSize;

	queue->first = 0;
	queue->itemSize = itemSize;
}


bool fixedQueue_isEmpty(fixedQueue* queue)
{
	return !queue->length;
}


void fixedQueue_append(fixedQueue* queue, void* item)
{
	if(queue->length < queue->capacity)
	{
		unsigned int pos = (queue->first + queue->length) % queue->capacity;

		memcpy((unsigned char*)&queue->items[pos], item, queue->itemSize);

		queue->length++;
	}
}

void* fixedQueue_head(fixedQueue* queue)
{
	if(queue->length)
		return &queue->items[queue->first];

	return 0;
}

void fixedQueue_pop(fixedQueue* queue)
{
	if(queue->length)
	{
		queue->first = (queue->first + 1) % queue->capacity;
		queue->length--;
	}
}
