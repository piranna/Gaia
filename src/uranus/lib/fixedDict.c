/*
 * fixeddict->c
 *
 * Implements a fixed-size dictionary sorted alphabetically
 *
 *  Created on: 21/12/2011
 *      Author: piranna
 */

#include "fixedDict.h"

#include <string.h>	// memset, strcmp, strncpy


void fixedDict_init(fixedDict* dict, pairKeyValue* pairs)
{
	dict->pairs = pairs;
	dict->length = 0;
}


void fixedDict_del(fixedDict* dict, char* key)
{
	// Look for the element
	int i = 0;
	for(; i < dict->length; ++i)
	{
		int cmp = strcmp(dict->pairs[i].key, key);

		// We have found the dict entry, remove it and move the next ones
		if(cmp == 0)
		{
			// Put on every entry the content of the next one
			for(; i < dict->length-1; ++i)
				dict->pairs[i] = dict->pairs[i+1];

			// Remove the last one
			memset((unsigned char*)&dict->pairs[dict->length-1], 0,
					sizeof(pairKeyValue));
			dict->length--;
		}

		// Dict entry was not on the dict, do nothing
		else if(cmp > 0)
			return;
	}
}

void* fixedDict_get(fixedDict* dict, char* key)
{
	// Look for the element
	int i = 0;
	for(; i < dict->length; ++i)
	{
		int cmp = strcmp(dict->pairs[i].key, key);

		// We have found the dict entry, return it
		if(cmp == 0)
			return dict->pairs[i].value;

		// We found a dict entry greater than the one we wanted, exit loop
		else if(cmp > 0)
			break;
	}

	// Dict entry was not on the dict, return nothing
	return 0;
}

void fixedDict_set(fixedDict* dict, char* key, void* value)
{
	// Look for the element
	int i = 0;
	for(; i < dict->length; ++i)
	{
		int cmp = strcmp(dict->pairs[i].key, key);

		// We have found the dict entry, update it
		if(cmp == 0)
		{
			dict->pairs[i].value = value;
			return;
		}

		// We have found the dict entry position, move the next ones
		else if(cmp > 0)
		{
			// Get capacity of the dict
			unsigned int capacity = sizeof(*(dict->pairs))/sizeof(void*);

			// Check if we have enought space to add the new entry
			if(dict->length == capacity)
				// We should raise an exception...
				return;

			// Put on every entry the content of the next one
			int j = dict->length;
			for(; j > i; --j)
				dict->pairs[j] = dict->pairs[j-1];

			break;
		}
	}

	// Set the new entry
	strncpy(dict->pairs[i].key, key, sizeof(dict->pairs[i].key));
	dict->pairs[i].value = value;
	dict->length++;
}
